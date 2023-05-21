#include "blob.hpp"

#include "oid.hpp"
#include "errors.hpp"

extern "C" {
#include <git2/blob.h>
}

namespace gitxx {
blob::blob(git_blob* blob)
    : blob_{blob, git_blob_free} {}

buf blob::filter(std::string_view path, oid const& id) const {
    buf                     result{};
    git_blob_filter_options options;
    throwOnError << git_blob_filter_options_init(&options, GIT_BLOB_FILTER_OPTIONS_VERSION);
    options.attr_commit_id = *id.get();
    throwOnError << git_blob_filter(&result.buffer_, blob_.get(), path.data(), &options);
    return result;
}

} // namespace gitxx
