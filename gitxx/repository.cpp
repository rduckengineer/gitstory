#include "repository.hpp"
#include "errors.hpp"
#include "refs.hpp"
#include "blame.hpp"

extern "C" {
#include "git2/repository.h"
#include "git2/blame.h"
}

namespace gitxx {
repository::repository(git_repository* repo) noexcept
    : repo_{repo, git_repository_free} {}

repository repository::open(std::string_view path) {
    git_repository* ptr{};
    throwOnError << git_repository_open(&ptr, path.data());

    return repository{ptr};
}

bool repository::isEmpty() const {
    int code = git_repository_is_empty(repo_.get());
    throwOnError << code;
    return static_cast<bool>(code);
}

reference repository::head() const {
    git_reference* ref{};
    throwOnError << git_repository_head(&ref, repo_.get());
    return reference{ref};
}
} // namespace gitxx
