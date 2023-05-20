#include "global.hpp"

extern "C" {
#include <git2/global.h>
}

namespace gitxx {
init_guard::init_guard() {
    git_libgit2_init();
}
init_guard::~init_guard() {
    git_libgit2_shutdown();
}
} // namespace gitxx
