#include "gitxx/repository.hpp"
#include "gitxx/global.hpp"
#include "gitxx/oid.hpp"
#include "gitxx/refs.hpp"
#include "gitxx/blame.hpp"
#include "gitxx/signature.hpp"
#include "gitxx/commit.hpp"
#include "gitxx/tree.hpp"
#include "gitxx/blob.hpp"

#include <iostream>
#include <fmt/std.h>
#include <fmt/chrono.h>
#include <fmt/ranges.h>

#include <ranges>

int main(int argc, char const* argv[]) {
    if (argc < 3) {
        fmt::print(std::cerr, "Please provide a git repository path and a path to blame\n");
        return -1;
    }

    gitxx::init_guard g{};

    auto repo = gitxx::repository::open(argv[1]);
    auto head = repo.head();
    fmt::print(std::cout, "{}\t{}\n", head.name(), head.target().format<6>());

    auto blame = gitxx::blame::byPath(
        repo, argv[2],
        gitxx::blame::options{
            .newest_commit    = head.target(),
            .oldest_commit    = gitxx::oid{nullptr},
            .useMailMap       = false,
            .ignoreWhitespace = false,
        });
    fmt::print(std::cout, "{} hunks!\n", blame.getHunkCount());
    for (std::uint32_t i = 0; i < blame.getHunkCount(); ++i) {
        gitxx::blame::hunk hunk          = blame.getHunkByIndex(i);
        gitxx::signature   hunkSignature = hunk.finalSignature();
        auto               commit        = gitxx::commit::lookup(repo, hunk.finalCommitId());

        gitxx::tree        tree  = commit.tree();
        gitxx::tree::entry entry = tree.entryByPath(hunk.origPath());

        size_t lineCount = hunk.linesInHunk();
        size_t origStart = hunk.origStartLineNumber();

        fmt::print(" - {} \"{}\" {}\n", hunk.finalCommitId().format<6>(), commit.summary(),
                   hunkSignature.when());
        fmt::print("   lines {}-{} (remapped from {}-{}) ({})\n", hunk.finalStartLineNumber(),
                   hunk.finalStartLineNumber() + hunk.linesInHunk() - 1, hunk.origStartLineNumber(),
                   hunk.origStartLineNumber() + hunk.linesInHunk() - 1,
                   (hunk.boundary() ? "boundary" : "not boundary"));

        if (entry && entry.isBlob()) {
            gitxx::blob blob    = entry.asBlob(repo);
            gitxx::buf  buffer  = blob.filter(hunk.origPath(), hunk.finalCommitId());
            auto        bufView = buffer.sv();

            auto rngToSV = [](auto&& rng)
                requires std::same_as<char, std::ranges::range_value_t<decltype(rng)>>
            {
                return std::string_view{rng.begin(), rng.end()};
            };

            using namespace std::ranges;
            auto lines = bufView | views::split('\n') | views::drop(origStart - 1)
                       | views::transform(rngToSV) | views::take(lineCount);

            fmt::print("{}\n", fmt::join(lines, "\n"));
            // fmt::print("{}", linesView);
        }
    }

    return 0;
}
