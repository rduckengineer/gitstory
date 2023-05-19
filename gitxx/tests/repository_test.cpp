#include "gitxx/repository.hpp"

extern "C" {
#include <git2/global.h>
}

#include <catch2/catch_test_macros.hpp>

#include <fmt/format.h>

constexpr std::string_view resource_path = "external/_main~ext~libgit2/tests/resources";

SCENARIO("LEL") {
    git_libgit2_init();

    std::string path = fmt::format("{}/empty_bare.git", resource_path);

    gitxx::repository repo = gitxx::repository::open(path.c_str());
}
