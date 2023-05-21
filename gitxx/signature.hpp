#ifndef GITSTORY_SIGNATURE_HPP
#define GITSTORY_SIGNATURE_HPP

#include <chrono>

struct git_signature;

namespace gitxx {

struct signature {
    using system_clock = std::chrono::system_clock;

    [[nodiscard]] auto when() const -> system_clock::time_point;

    [[nodiscard]] auto name() const -> std::string_view;
    [[nodiscard]] auto email() const -> std::string_view;

    git_signature const* sig_;
};

} // namespace gitxx

#endif // GITSTORY_SIGNATURE_HPP
