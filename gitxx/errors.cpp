#include "errors.hpp"

extern "C" {
#include <git2/errors.h>
}

#include <fmt/format.h>

namespace gitxx {
git_exception::git_exception(int klass, char const* message)
    : std::runtime_error(fmt::format("Code {}: {}", klass, message)) {}

namespace internal {
void operator<<(error_checker, int errorCode) {
    if (errorCode != 0) {
        git_error const* err = git_error_last();
        throw git_exception(err->klass, err->message);
    }
}
} // namespace internal
} // namespace gitxx
