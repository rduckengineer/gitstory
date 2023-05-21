#ifndef GITSTORY_REPOSITORY_HPP
#define GITSTORY_REPOSITORY_HPP

#include "gitxx/unique_ptr.hpp"
#include "gitxx/blame.hpp"

#include <string_view>

struct git_repository;

namespace gitxx {
class reference;
class blame;

class repository {
public:
    [[nodiscard]] static repository open(std::string_view path);

    explicit repository(git_repository* repo) noexcept;

    [[nodiscard]] bool      isEmpty() const;
    [[nodiscard]] reference head() const;

    [[nodiscard]] auto get() { return repo_.get(); }
    [[nodiscard]] auto get() const { return repo_.get(); }

private:
    internal::unique_ptr<git_repository> repo_;
};
} // namespace gitxx

#endif // GITSTORY_REPOSITORY_HPP
