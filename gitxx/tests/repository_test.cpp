#include "gitxx/repository.hpp"
#include "gitxx/global.hpp"
#include "gitxx/errors.hpp"
#include "gitxx/refs.hpp"

#include "test/check_invoke_nothrow.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include <fmt/format.h>

constexpr std::string_view resource_path = "external/_main~ext~libgit2/tests/resources";

SCENARIO("Gitxx can open and explore repositories") {
    gitxx::init_guard g{};

    GIVEN("A non-existing repository") {
        std::string_view path = "non_existing_path.git";

        THEN("Trying to open it throws") {
            using Catch::Matchers::Message;

            CHECK_THROWS_MATCHES(gitxx::repository::open(path), gitxx::git_exception,
                                 Message("Error: failed to resolve path 'non_existing_path.git': "
                                         "No such file or directory. (Err: Notfound Cat: OS)"));
        }
    }

    GIVEN("An existing empty repository") {
        auto        repoInRes = GENERATE("empty_bare.git", "empty_standard_repo/.gitted");
        std::string path      = fmt::format("{}/{}", resource_path, repoInRes);

        THEN("It can successfully be opened but is empty") {
            auto repository = CHECK_INVOKE_NOTHROW(gitxx::repository::open(path));

            CHECK(repository.isEmpty());
        }
    }

    GIVEN("An existing non-empty repository") {
        std::string path = fmt::format("{}/blametest.git", resource_path);

        THEN("It can be opened and has a HEAD pointing to master") {
            auto repository = CHECK_INVOKE_NOTHROW(gitxx::repository::open(path));

            REQUIRE_FALSE(repository.isEmpty());
            CHECK(repository.head().name() == "refs/heads/master");
        }
    }
}
