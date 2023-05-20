#ifndef GITSTORY_OID_STATIC_STRING_HPP
#define GITSTORY_OID_STATIC_STRING_HPP

#include <array>
#include <string_view>

namespace gitxx {
namespace internal {
static constexpr std::size_t OID_MAX_HEXSIZE = 40;
}

template <std::size_t N>
    requires(N < internal::OID_MAX_HEXSIZE)
class static_oid_string {
public:
    explicit static_oid_string(std::array<char, N>&& chars)
        : buffer{chars} {}

    // NOLINTNEXTLINE (google-explicit-constructor)
    operator std::string_view() const { return sv(); }

    [[nodiscard]] std::string_view sv() const { return {buffer.data(), buffer.size()}; }

private:
    std::array<char, N> buffer;
};
} // namespace gitxx

#endif // GITSTORY_OID_STATIC_STRING_HPP
