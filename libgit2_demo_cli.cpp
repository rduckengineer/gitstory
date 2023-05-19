#include "gitxx/repository.hpp"

extern "C" {
#include "git2/repository.h"
#include "git2/global.h"
#include "git2/refs.h"
#include "git2/oid.h"
}

#include <iostream>
#include <array>

template <size_t N>
    requires(N < GIT_OID_MAX_HEXSIZE)
struct static_oid_string {
    std::array<char, N> buffer;

    explicit static_oid_string(git_oid const* oid) {
        git_oid_nfmt(buffer.data(), buffer.size(), oid);
    }

    // NOLINTNEXTLINE (google-explicit-constructor)
    operator std::string_view() const { return sv(); }
    [[nodiscard]] std::string_view sv() const { return {buffer.data(), buffer.size()}; }
};

int main(int argc, char const* argv[]) {
    if (argc == 1) {
        std::cerr << "Please provide a git repository path" << std::endl;
        return -1;
    }

    struct libInit {
        libInit() { git_libgit2_init(); }
        ~libInit() { git_libgit2_shutdown(); }
    };

    [[maybe_unused]] libInit lib_init{};

    auto repo = gitxx::repository::open(argv[1]);

    git_reference* ref;
    git_repository_head(&ref, static_cast<git_repository*>(repo));

    std::cout << git_reference_name(ref) << "\t"
              << static_oid_string<6>{git_reference_target(ref)}.sv() << std::endl;
    git_reference_free(ref);

    return 0;
}
