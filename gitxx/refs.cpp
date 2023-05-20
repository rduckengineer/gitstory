#include "refs.hpp"

#include "gitxx/oid.hpp"

extern "C" {
#include <git2/refs.h>
}

namespace gitxx {
reference::reference(git_reference* ref)
    : ref_{ref, git_reference_free} {}

std::string_view reference::name() const {
    return git_reference_name(ref_.get());
}

oid reference::target() const {
    return oid{git_reference_target(ref_.get())};
}
} // namespace gitxx
