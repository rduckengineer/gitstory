#ifndef GITSTORY_COMMIT_HPP
#define GITSTORY_COMMIT_HPP

#include "unique_ptr.hpp"

struct git_commit;

namespace gitxx {
class repository;
class oid;
class tree;

class commit {
public:
    explicit commit(git_commit* commit);

    static commit lookup(repository& repo, oid id);

    [[nodiscard]] std::string_view summary() const;
    [[nodiscard]] gitxx::tree      tree() const;

private:
    internal::unique_ptr<git_commit> commit_;
};
} // namespace gitxx

#endif // GITSTORY_COMMIT_HPP
