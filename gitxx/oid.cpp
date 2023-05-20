#include "oid.hpp"

extern "C" {
#include <git2/oid.h>
}

namespace gitxx {
static_assert(internal::OID_MAX_HEXSIZE == GIT_OID_MAX_HEXSIZE,
              "Max OID hex sizes don't match! Have you switched to SHA256?");

void oid::formatInto(std::span<char> chars) const {
    git_oid_nfmt(chars.data(), chars.size(), oid_);
}
} // namespace gitxx
