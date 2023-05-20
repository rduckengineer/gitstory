#include "gitxx/repository.hpp"
#include "gitxx/global.hpp"
#include "gitxx/errors.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include <fmt/format.h>

constexpr std::string_view resource_path = "external/_main~ext~libgit2/tests/resources";

SCENARIO("Gitxx can open and explore repositories") {
    gitxx::init_guard g{};

    GIVEN("A non-existing repository") {
        std::string_view path = "non_existing_path.git";

        THEN("Trying to open it throws") {
            using Catch::Matchers::Message;

            CHECK_THROWS_MATCHES(
                gitxx::repository::open(path), gitxx::git_exception,
                Message("Error: Notfound. Category: OS. Reason: failed to resolve path "
                        "'non_existing_path.git': No such file or directory"));
        }
    }

    GIVEN("An existing repository") {
        std::string path = fmt::format("{}/empty_bare.git", resource_path);

        THEN("It can successfully be opened") {
            CHECK_NOTHROW(gitxx::repository::open(path));
        }
    }
}
