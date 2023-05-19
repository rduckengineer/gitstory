#include "repository.hpp"
#include "errors.hpp"

extern "C" {
#include "git2/repository.h"
}

namespace gitxx {
repository::repository(git_repository* repo)
    : repo_{repo, git_repository_free} {}

repository repository::open(char const* path) {
    git_repository* ptr{};
    internal::check << git_repository_open(&ptr, path);

    return repository{ptr};
}
} // namespace gitxx
