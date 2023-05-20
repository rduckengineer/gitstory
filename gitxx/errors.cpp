#include "errors.hpp"
#include "errors_mapping.inl"

namespace gitxx {
git_exception::git_exception(error_code errorCode, error_category errorClass,
                             std::string_view message)
    : std::runtime_error([=] {
        auto category = internal::toStr(errorClass);
        auto errCode  = internal::toStr(errorCode);
        return fmt::format("Error: {}. (Err: {} Cat: {})", message, errCode, category);
    }()) {}

namespace internal {
void operator<<(error_checker, int errorCode) {
    if (errorCode < GIT_OK) {
        using internal::fromLibGit2;
        auto errCode = fromLibGit2(static_cast<git_error_code>(errorCode));

        git_error const* lastError = git_error_last();
        char const*      message   = lastError ? lastError->message : "No reason available";
        auto category = lastError ? fromLibGit2(static_cast<git_error_t>(lastError->klass))
                                  : error_category::Invalid;

        throw git_exception(errCode, category, message);
    }
}
} // namespace internal
} // namespace gitxx
