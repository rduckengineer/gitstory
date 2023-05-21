#ifndef GITSTORY_BLAME_HPP
#define GITSTORY_BLAME_HPP

#include "gitxx/unique_ptr.hpp"

#include "oid.hpp"
#include <chrono>

struct git_blame;
struct git_blame_options;
struct git_blame_hunk;

namespace gitxx {
class repository;
struct signature;

class blame {
public:
    struct options {
        oid  newest_commit{nullptr};
        oid  oldest_commit{nullptr};
        bool useMailMap       = false;
        bool ignoreWhitespace = false;

        [[nodiscard]] git_blame_options apply() const;
    };

    static blame byPath(repository& repo, std::string_view path, options opts);

    explicit blame(git_blame* blame) noexcept;

    struct hunk {
        [[nodiscard]] std::size_t      linesInHunk() const;
        [[nodiscard]] oid              finalCommitId() const;
        [[nodiscard]] std::size_t      finalStartLineNumber() const;
        [[nodiscard]] std::size_t      origStartLineNumber() const;
        [[nodiscard]] oid              origCommitId() const;
        [[nodiscard]] std::string_view origPath() const;
        [[nodiscard]] bool             boundary() const;
        [[nodiscard]] signature        finalSignature() const;
        git_blame_hunk const*          hunk_;
    };

    std::uint32_t getHunkCount();
    hunk          getHunkByIndex(std::uint32_t index);

private:
    internal::unique_ptr<git_blame> blame_;
};
} // namespace gitxx

#endif // GITSTORY_BLAME_HPP
