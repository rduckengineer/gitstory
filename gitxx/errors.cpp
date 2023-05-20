#include "errors.hpp"
#include "errors_mapping.inl"

namespace gitxx {
git_exception::git_exception(error_code errorCode, error_category errorClass,
                             std::string_view message)
    : std::runtime_error([=] {
        auto category = internal::toStr(errorClass);
        auto errCode  = internal::toStr(errorCode);
        return fmt::format("Error: {}. Category: {}. Reason: {}", errCode, category, message);
    }()) {}

namespace internal {
void operator<<(error_checker, int errorCode) {
    if (errorCode < GIT_OK) {
        git_error const* err = git_error_last();

        throw git_exception(internal::fromLibGit2(static_cast<git_error_code>(errorCode)),
                            internal::fromLibGit2(static_cast<git_error_t>(err->klass)),
                            err->message);
    }
}
} // namespace internal
} // namespace gitxx
