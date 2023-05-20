#ifndef GITSTORY_ERRORS_HPP
#define GITSTORY_ERRORS_HPP

#include <stdexcept>

namespace gitxx {
/**
 * Error codes returned by individual functions.
 * Refer to git2/errors.h for individual error code explanations
 */
enum class error_code {
    Ok             = 0,
    Error          = -1,
    Notfound       = -3,
    Exists         = -4,
    Ambiguous      = -5,
    BufShort       = -6,
    User           = -7, // For user callbacks
    BareRepo       = -8,
    UnbornBranch   = -9,
    Unmerged       = -10,
    NonFastForward = -11,
    InvalidSpec    = -12,
    Conflict       = -13,
    Locked         = -14,
    Modified       = -15,
    Auth           = -16,
    Certificate    = -17,
    Applied        = -18,
    Peel           = -19,
    EndOfFile      = -20,
    Invalid        = -21,
    Uncommitted    = -22,
    Directory      = -23,
    MergeConflict  = -24,
    Passthrough    = -30,
    IterOver       = -31,
    Retry          = -32,
    Mismatch       = -33,
    IndexDirty     = -34,
    ApplyFail      = -35,
    Owner          = -36,
};

enum class error_category {
    None = 0,
    NoMemory,
    OS,
    Invalid,
    Reference,
    Zlib,
    Repository,
    Config,
    Regex,
    ODB,
    Index,
    Object,
    Net,
    Tag,
    Tree,
    Indexer,
    SSL,
    Submodule,
    Thread,
    Stash,
    Checkout,
    FetchHead,
    Merge,
    SSH,
    Filter,
    Revert,
    Callback,
    CherryPick,
    Describe,
    Rebase,
    Filesystem,
    Patch,
    Worktree,
    SHA,
    HTTP,
    Internal,
};

class git_exception : public std::runtime_error {
public:
    explicit git_exception(error_code code, error_category category, std::string_view message);
};

namespace internal {
struct error_checker {};
void operator<<(error_checker, int);
} // namespace internal
inline internal::error_checker throwOnError;
} // namespace gitxx

#endif // GITSTORY_ERRORS_HPP
