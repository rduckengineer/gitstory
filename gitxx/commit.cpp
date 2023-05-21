#include "commit.hpp"

#include "repository.hpp"
#include "oid.hpp"
#include "errors.hpp"
#include "tree.hpp"

extern "C" {
#include <git2/commit.h>
}

namespace gitxx {
commit::commit(git_commit* commit)
    : commit_{commit, git_commit_free} {}

commit commit::lookup(gitxx::repository& repo, gitxx::oid id) {
    git_commit* commit{};
    throwOnError << git_commit_lookup(&commit, repo.get(), id.get());
    return gitxx::commit{commit};
}

std::string_view commit::summary() const {
    return git_commit_summary(commit_.get());
}

gitxx::tree commit::tree() const {
    git_tree* gitTree{};
    git_commit_tree(&gitTree, commit_.get());
    return gitxx::tree{gitTree};
}
} // namespace gitxx
