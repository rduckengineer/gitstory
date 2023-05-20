#ifndef GITSTORY_REPOSITORY_HPP
#define GITSTORY_REPOSITORY_HPP

#include "gitxx/unique_ptr.hpp"

#include <string_view>

struct git_repository;

namespace gitxx {
class reference;

class repository {
public:
    static repository open(std::string_view path);

    explicit repository(git_repository* repo) noexcept;

    [[nodiscard]] reference head() const;

    explicit operator git_repository*() { return repo_.get(); }
    explicit operator git_repository const*() const { return repo_.get(); }

private:
    internal::unique_ptr<git_repository> repo_;
};
} // namespace gitxx

#endif // GITSTORY_REPOSITORY_HPP
