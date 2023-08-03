#include "gitxx/gitxx.hpp"

#include <fmt/std.h>
#include <fmt/chrono.h>
#include <fmt/ranges.h>

#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/component/component.hpp"

#include <ranges>

namespace {
struct Arguments {
    Arguments(int argc, char const* argv[]) {
        if (argc < 3)
            throw std::runtime_error("Please provide a git repository path and a path to blame");

        repositoryPath = argv[1];
        blameSubPath   = argv[2];
    }

    std::string_view repositoryPath;
    std::string_view blameSubPath;
};

int performBlame(Arguments args);

auto rangeToStringView = [](auto&& rng)
    requires std::same_as<char, std::ranges::range_value_t<decltype(rng)>>
{
    return std::string_view{rng.begin(), rng.end()};
};
} // namespace

int main(int argc, char const* argv[]) {
    return performBlame(Arguments{argc, argv});
}

template <std::ranges::input_range Rng>
auto to_vector(Rng&& rng) {
    using value_type = std::ranges::range_value_t<Rng>;
    return std::vector<value_type>{rng.begin(), rng.end()};
}

class ScrollableContainer : public ftxui::ComponentBase {
public:
    ScrollableContainer(ftxui::Components elements) {
        for (auto child : elements) {
            Add(std::move(child));
        }
    }

    [[nodiscard]] bool Focusable() const override { return true; }

    void SetActiveChild(ComponentBase* child) override {
        for (size_t i = 0; i < ChildCount(); ++i) {
            auto& childAt = ChildAt(i);
            if (childAt.get() == child) {
                focused_ = i;
                break;
            }
        }
    }

    ftxui::Component ActiveChild() override { return ChildAt(focused_); }

    ftxui::Element Render() override {
        auto childElements = to_vector(
            children_ | std::ranges::views::transform([](ftxui::Component const& component) {
                return component->Render();
            }));

        auto box = ftxui::vbox(childElements);

        box->ComputeRequirement();
        auto requirements = box->requirement();
        size_             = requirements.min_y;

        return ftxui::vbox(
            ftxui::hbox(ftxui::text(fmt::format(
                "min {} box min {}", requirements.min_y, requirements.selected_box.y_min))),
            box | ftxui::focusPosition(0, requirements.selected_box.y_min)
                | ftxui::vscroll_indicator | ftxui::frame);
    }

    bool OnEvent(ftxui::Event event) override {
        if (event == ftxui::Event::ArrowDown) {
            if (focused_ < ChildCount() - 1) {
                ++focused_;
                return true;
            }
        } else if (event == ftxui::Event::ArrowUp) {
            if (focused_ > 0) {
                --focused_;
                return true;
            }
        }
        return false;
    }

private:
    size_t focused_ = 0;
    int    size_;
};

ftxui::Component Scrollable(ftxui::Components children) {
    return std::make_shared<ScrollableContainer>(std::move(children));
}

class BlameBlobComponent : public ftxui::ComponentBase {
public:
    BlameBlobComponent(gitxx::repository& repo, gitxx::blame::hunk const& hunk,
                       gitxx::tree::entry const& hunkEntry, gitxx::commit const& commit) {
        using ftxui::bold;
        using ftxui::Maybe;
        using ftxui::text;

        firstLine  = fmt::format(" - {} \"{}", hunk.finalCommitId().format<6>(), commit.summary());
        secondLine = fmt::format(
            "   lines {}-{} (remapped from {}-{}) ({})", hunk.finalStartLineNumber(),
            hunk.finalStartLineNumber() + hunk.linesInHunk() - 1, hunk.origStartLineNumber(),
            hunk.origStartLineNumber() + hunk.linesInHunk() - 1,
            (hunk.boundary() ? "boundary" : "not boundary"));

        size_t origStart = hunk.origStartLineNumber();

        if (hunkEntry && hunkEntry.isBlob()) {
            gitxx::blob blob    = hunkEntry.asBlob(repo);
            gitxx::buf  buffer  = blob.filter(hunk.origPath(), hunk.finalCommitId());
            auto        bufView = buffer.sv();

            size_t lineCount = hunk.linesInHunk();

            using namespace std::ranges;
            auto lines = bufView | views::split('\n') | views::drop(origStart - 1)
                       | views::transform(rangeToStringView) | views::take(lineCount);

            lineElements.reserve(lineCount);
            for (std::string_view line : lines) {
                lineElements.push_back(ftxui::text(std::string{line}));
            }
        }
    }

    bool Focusable() const override { return true; }

    ftxui::Element Render() override {
        using ftxui::bold;
        using ftxui::text;
        auto box = ftxui::vbox(/*text(firstLine), bold(text(secondLine)),*/ lineElements);
        if (Active())
            box |= ftxui::color(ftxui::Color::Palette16::GreenLight) | ftxui::focus;
        return box;
    }

private:
    std::string     firstLine;
    std::string     secondLine;
    ftxui::Elements lineElements;
};

namespace {
int performBlame(Arguments args) {
    gitxx::init_guard g{};
    auto              screen = ftxui::ScreenInteractive::Fullscreen();

    auto repo = gitxx::repository::open(args.repositoryPath);

    auto blame
        = gitxx::blame::byPath(repo, args.blameSubPath, {.newest_commit = repo.head().target()});

    auto linesView = std::ranges::views::transform(
        std::ranges::views::iota(0u, blame.getHunkCount()), [&blame, &repo](size_t index) {
            auto               hunk   = blame.getHunkByIndex(index);
            auto               commit = gitxx::commit::lookup(repo, hunk.finalCommitId());
            gitxx::tree        tree   = commit.tree();
            gitxx::tree::entry entry  = tree.entryByPath(hunk.origPath());

            return std::make_shared<BlameBlobComponent>(repo, hunk, entry, commit);
        });

    screen.Loop(Scrollable({linesView.begin(), linesView.end()})
                | ftxui::CatchEvent([&screen](ftxui::Event event) {
                      if (event == ftxui::Event::Character('q')) {
                          screen.ExitLoopClosure()();
                          return true;
                      }
                      return false;
                  }));

    return 0;
}
} // namespace
