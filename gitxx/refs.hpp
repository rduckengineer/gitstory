#ifndef GITSTORY_REFS_HPP
#define GITSTORY_REFS_HPP

#include "gitxx/unique_ptr.hpp"

struct git_reference;

namespace gitxx {
class oid;

class reference {
public:
    explicit reference(git_reference* ref);

    [[nodiscard]] auto name() const -> std::string_view;
    [[nodiscard]] oid  target() const;
    [[nodiscard]] bool isBranch() const;

private:
    internal::unique_ptr<git_reference> ref_;
};
} // namespace gitxx

#endif // GITSTORY_REFS_HPP
