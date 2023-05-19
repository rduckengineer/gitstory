#ifndef GITSTORY_REPOSITORY_HPP
#define GITSTORY_REPOSITORY_HPP

#include "gitxx/unique_ptr.hpp"

struct git_repository;

namespace gitxx {
class repository {
public:
    static repository open(char const* path);

    explicit repository(git_repository* repo);

    explicit operator git_repository*() { return repo_.get(); }
    explicit operator git_repository const*() const { return repo_.get(); }

private:
    internal::unique_ptr<git_repository> repo_;
};
} // namespace gitxx

#endif // GITSTORY_REPOSITORY_HPP
