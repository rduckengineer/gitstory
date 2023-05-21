#ifndef GITSTORY_TREE_HPP
#define GITSTORY_TREE_HPP

#include "unique_ptr.hpp"
#include "gitxx/repository.hpp"

struct git_tree;
struct git_tree_entry;

namespace gitxx {
class oid;
class blob;

class tree {
public:
    explicit tree(git_tree* tree);

    template <typename EntryPtr>
    class entry_common {
    public:
        explicit entry_common(EntryPtr* entry)
            : entry_{entry} {}

        // NOLINTNEXTLINE
        [[nodiscard]] operator bool() const { return static_cast<bool>(entry_); }

        [[nodiscard]] bool isBlob() const;
        [[nodiscard]] blob asBlob(gitxx::repository& repo) const;

    protected:
        EntryPtr* entry_;
    };

    struct entry_view : entry_common<git_tree_entry const> {
        explicit entry_view(git_tree_entry const* entry)
            : entry_common{entry} {}
    };

    struct entry : entry_common<git_tree_entry> {
    public:
        explicit entry(git_tree_entry* entry)
            : entry_common{entry} {}
        ~entry();
    };

    entry_view entryById(oid const& id);
    entry      entryByPath(std::string_view path);

private:
    internal::unique_ptr<git_tree> tree_;
};

} // namespace gitxx

#endif // GITSTORY_TREE_HPP
