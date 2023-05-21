#include "tree.hpp"

#include "oid.hpp"
#include "errors.hpp"
#include "blob.hpp"
#include "repository.hpp"

extern "C" {
#include <git2/tree.h>
}

#define INSTANTIATE_METHOD(RET, NAME, ...)                                          \
    template RET tree::entry_common<git_tree_entry const>::NAME(__VA_ARGS__) const; \
    template RET tree::entry_common<git_tree_entry>::NAME(__VA_ARGS__) const

namespace gitxx {
tree::tree(git_tree* tree)
    : tree_{tree, git_tree_free} {}

tree::entry::~entry() {
    git_tree_entry_free(entry_);
}

tree::entry_view tree::entryById(gitxx::oid const& id) {
    return tree::entry_view{git_tree_entry_byid(tree_.get(), id.get())};
}

tree::entry tree::entryByPath(std::string_view path) {
    git_tree_entry* gitTreeEntry{};
    throwOnError << git_tree_entry_bypath(&gitTreeEntry, tree_.get(), path.data());
    return tree::entry{gitTreeEntry};
}

template <typename EntryPtr>
bool tree::entry_common<EntryPtr>::isBlob() const {
    return git_tree_entry_type(entry_) == GIT_OBJECT_BLOB;
}
INSTANTIATE_METHOD(bool, isBlob);

template <typename EntryPtr>
blob tree::entry_common<EntryPtr>::asBlob(repository& repo) const {
    git_object* object{};
    throwOnError << git_tree_entry_to_object(&object, repo.get(), entry_);
    return blob{reinterpret_cast<git_blob*>(object)};
}
INSTANTIATE_METHOD(blob, asBlob, repository&);
} // namespace gitxx
