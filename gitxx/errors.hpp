#ifndef GITSTORY_ERRORS_HPP
#define GITSTORY_ERRORS_HPP

#include <stdexcept>

namespace gitxx {
struct git_exception : std::runtime_error {
    git_exception(int klass, char const* message);
};

namespace internal {
struct error_checker {};
inline error_checker check;
void                 operator<<(error_checker, int);
} // namespace internal
} // namespace gitxx

#endif // GITSTORY_ERRORS_HPP
