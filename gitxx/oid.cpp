#include "oid.hpp"
#include "errors.hpp"

extern "C" {
#include <git2/oid.h>
}

namespace gitxx {
static_assert(internal::OID_MAX_HEXSIZE == GIT_OID_MAX_HEXSIZE,
              "Max OID hex sizes don't match! Have you switched to SHA256?");

void oid::formatInto(std::span<char> chars) const {
    throwOnError << git_oid_nfmt(chars.data(), chars.size(), oid_);
}

git_oid& operator<<(git_oid& lhs, oid const& rhs) {
    if (rhs.get())
        throwOnError << git_oid_cpy(&lhs, rhs.get());
    return lhs;
}
} // namespace gitxx
