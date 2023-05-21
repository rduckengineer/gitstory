#include "blame.hpp"
#include "errors.hpp"
#include "signature.hpp"
#include "repository.hpp"

extern "C" {
#include <git2/blame.h>
}

namespace gitxx {
blame blame::byPath(repository& repo, std::string_view path, options opts) {
    git_blame* gitBlame{};
    auto       gitOpts = opts.apply();
    throwOnError << git_blame_file(&gitBlame, repo.get(), path.data(), &gitOpts);
    return blame{gitBlame};
}

blame::blame(git_blame* blame) noexcept
    : blame_{blame, git_blame_free} {}

std::uint32_t blame::getHunkCount() {
    return git_blame_get_hunk_count(blame_.get());
}

blame::hunk blame::getHunkByIndex(std::uint32_t index) {
    return {git_blame_get_hunk_byindex(blame_.get(), index)};
}

git_blame_options blame::options::apply() const {
    git_blame_options options;
    throwOnError << git_blame_options_init(&options, 1);

    throwOnError << (git_oid_is_zero(&options.oldest_commit));
    options.oldest_commit << oldest_commit;
    options.newest_commit << newest_commit;

    if (useMailMap)
        options.flags |= GIT_BLAME_USE_MAILMAP;
    if (ignoreWhitespace)
        options.flags |= GIT_BLAME_IGNORE_WHITESPACE;

    return options;
}

std::size_t blame::hunk::linesInHunk() const {
    return hunk_->lines_in_hunk;
}

oid blame::hunk::finalCommitId() const {
    return oid{&hunk_->final_commit_id};
}

std::size_t blame::hunk::finalStartLineNumber() const {
    return hunk_->final_start_line_number;
}

std::size_t blame::hunk::origStartLineNumber() const {
    return hunk_->orig_start_line_number;
}

oid blame::hunk::origCommitId() const {
    return oid{&hunk_->orig_commit_id};
}

std::string_view blame::hunk::origPath() const {
    return hunk_->orig_path;
}

bool blame::hunk::boundary() const {
    return static_cast<bool>(hunk_->boundary);
}

signature blame::hunk::finalSignature() const {
    return signature{hunk_->final_signature};
}
} // namespace gitxx
