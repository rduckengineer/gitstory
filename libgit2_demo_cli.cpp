#include "gitxx/gitxx.hpp"

#include <fmt/std.h>
#include <fmt/chrono.h>
#include <fmt/ranges.h>

#include <iostream>
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

int  performBlame(Arguments args);
void presentHunk(gitxx::repository& repo, gitxx::blame::hunk const& hunk,
                 gitxx::tree::entry const& hunkEntry, gitxx::commit const& commit);
} // namespace

int main(int argc, char const* argv[]) {
    return performBlame({argc, argv});
}

namespace {
int performBlame(Arguments args) {
    gitxx::init_guard g{};

    auto repo = gitxx::repository::open(args.repositoryPath);

    auto blame
        = gitxx::blame::byPath(repo, args.blameSubPath, {.newest_commit = repo.head().target()});

    for (std::uint32_t i = 0; i < blame.getHunkCount(); ++i) {
        auto               hunk   = blame.getHunkByIndex(i);
        auto               commit = gitxx::commit::lookup(repo, hunk.finalCommitId());
        gitxx::tree        tree   = commit.tree();
        gitxx::tree::entry entry  = tree.entryByPath(hunk.origPath());

        presentHunk(repo, hunk, entry, commit);
    }

    return 0;
}

auto rangeToStringView = [](auto&& rng)
    requires std::same_as<char, std::ranges::range_value_t<decltype(rng)>>
{
    return std::string_view{rng.begin(), rng.end()};
};

void presentHunk(gitxx::repository& repo, gitxx::blame::hunk const& hunk,
                 gitxx::tree::entry const& hunkEntry, gitxx::commit const& commit) {

    size_t origStart = hunk.origStartLineNumber();

    fmt::print("\033[1m - {} \"{}\"\n\033[m", hunk.finalCommitId().format<6>(), commit.summary());
    fmt::print("\033[1m   lines {}-{} (remapped from {}-{}) ({})\033[m\n",
               hunk.finalStartLineNumber(), hunk.finalStartLineNumber() + hunk.linesInHunk() - 1,
               hunk.origStartLineNumber(), hunk.origStartLineNumber() + hunk.linesInHunk() - 1,
               (hunk.boundary() ? "boundary" : "not boundary"));

    if (hunkEntry && hunkEntry.isBlob()) {
        gitxx::blob blob    = hunkEntry.asBlob(repo);
        gitxx::buf  buffer  = blob.filter(hunk.origPath(), hunk.finalCommitId());
        auto        bufView = buffer.sv();

        size_t lineCount = hunk.linesInHunk();

        using namespace std::ranges;
        auto lines = bufView | views::split('\n') | views::drop(origStart - 1)
                   | views::transform(rangeToStringView) | views::take(lineCount);

        fmt::print("\033[32m{}\033[m\n", fmt::join(lines, "\n"));
    }
}
} // namespace
