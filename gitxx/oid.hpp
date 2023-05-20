#ifndef GITSTORY_OID_HPP
#define GITSTORY_OID_HPP

#include "gitxx/unique_ptr.hpp"
#include "gitxx/oid_static_string.hpp"

#include <span>

struct git_oid;

namespace gitxx {
class oid {
public:
    explicit oid(git_oid const* oid)
        : oid_{oid} {}

    template <std::size_t N>
    [[nodiscard]] auto format() const -> static_oid_string<N>;
    [[nodiscard]] auto format(std::size_t n = internal::OID_MAX_HEXSIZE) const -> std::string;

private:
    void formatInto(std::span<char> chars) const;

    git_oid const* oid_;
};

template <std::size_t N>
auto oid::format() const -> static_oid_string<N> {
    std::array<char, N> buffer;
    formatInto(buffer);
    return static_oid_string<N>{std::move(buffer)};
}

inline auto oid::format(std::size_t n) const -> std::string {
    std::string buffer{};
    buffer.resize(n);
    formatInto(buffer);
    return buffer;
}
} // namespace gitxx

#endif // GITSTORY_OID_HPP
