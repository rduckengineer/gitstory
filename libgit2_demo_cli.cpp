#include "gitxx/repository.hpp"
#include "gitxx/global.hpp"
#include "gitxx/oid.hpp"
#include "gitxx/refs.hpp"

#include <iostream>
#include <fmt/std.h>

int main(int argc, char const* argv[]) {
    if (argc == 1) {
        fmt::print(std::cerr, "Please provide a git repository path\n");
        return -1;
    }

    [[maybe_unused]] gitxx::init_guard g{};

    auto repo = gitxx::repository::open(argv[1]);
    auto head = repo.head();
    fmt::print(std::cout, "{}\t{}\n", head.name(), head.target().format<6>());

    return 0;
}
