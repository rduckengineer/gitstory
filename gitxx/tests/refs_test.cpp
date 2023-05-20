#include "gitxx/refs.hpp"
#include "gitxx/repository.hpp"
#include "gitxx/oid.hpp"
#include "gitxx/global.hpp"

#include <catch2/catch_test_macros.hpp>

#include <fmt/format.h>

constexpr std::string_view resource_path = "external/_main~ext~libgit2/tests/resources";

SCENARIO("Given a reference ") {
    gitxx::init_guard g{};

    auto repo = gitxx::repository::open(fmt::format("{}/blametest.git", resource_path));

    GIVEN("A reference to HEAD pointing to the master branch") {
        gitxx::reference head = repo.head();

        THEN("It has a name") {
            CHECK(head.name() == "refs/heads/master");
        }

        THEN("It has an OID") {
            CHECK(head.target().format() == "d93e87a0863c7ec5e772f99e72ca9efddf0ca718");
        }

        THEN("It is a branch") {
            CHECK(head.isBranch());
        }
    }
}
