#ifndef GITSTORY_OID_HPP
#define GITSTORY_OID_HPP

#include "gitxx/unique_ptr.hpp"
#include "gitxx/oid_static_string.hpp"

#include <span>

struct git_oid;

namespace gitxx {
class oid {
    friend class std::hash<gitxx::oid>;

public:
    explicit oid(git_oid const* oid)
        : oid_{oid} {}

    template <std::size_t N>
    [[nodiscard]] auto format() const -> static_oid_string<N>;
    [[nodiscard]] auto format(std::size_t n = internal::OID_MAX_HEXSIZE) const -> std::string;

    [[nodiscard]] git_oid const* get() const { return oid_; }

private:
    void formatInto(std::span<char> chars) const;

    git_oid const* oid_;
};

git_oid& operator<<(git_oid& lhs, oid const& rhs);

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

template <>
struct std::hash<gitxx::oid> {
    size_t operator()(gitxx::oid const& oid) const;
};

#endif // GITSTORY_OID_HPP
