#include "repository.hpp"
#include "errors.hpp"
#include "refs.hpp"

extern "C" {
#include "git2/repository.h"
}

namespace gitxx {
repository::repository(git_repository* repo) noexcept
    : repo_{repo, git_repository_free} {}

repository repository::open(std::string_view path) {
    git_repository* ptr{};
    throwOnError << git_repository_open(&ptr, path.data());

    return repository{ptr};
}

reference repository::head() const {
    git_reference* ref{};
    throwOnError << git_repository_head(&ref, repo_.get());
    return reference{ref};
}
} // namespace gitxx
