#ifndef GITSTORY_ERRORS_MAPPING_INL
#define GITSTORY_ERRORS_MAPPING_INL

#include "errors.hpp"

extern "C" {
#include <git2/errors.h>
};

#include <fmt/format.h>

namespace gitxx::internal {
error_code       fromLibGit2(::git_error_code err);
error_category   fromLibGit2(::git_error_t category);
std::string_view toStr(error_category category);
std::string_view toStr(error_code errCode);

error_category fromLibGit2(::git_error_t category) {
    switch (category) {
    case ::git_error_t::GIT_ERROR_NONE: return error_category::None;
    case ::git_error_t::GIT_ERROR_NOMEMORY: return error_category::NoMemory;
    case ::git_error_t::GIT_ERROR_OS: return error_category::OS;
    case ::git_error_t::GIT_ERROR_INVALID: return error_category::Invalid;
    case ::git_error_t::GIT_ERROR_REFERENCE: return error_category::Reference;
    case ::git_error_t::GIT_ERROR_ZLIB: return error_category::Zlib;
    case ::git_error_t::GIT_ERROR_REPOSITORY: return error_category::Repository;
    case ::git_error_t::GIT_ERROR_CONFIG: return error_category::Config;
    case ::git_error_t::GIT_ERROR_REGEX: return error_category::Regex;
    case ::git_error_t::GIT_ERROR_ODB: return error_category::ODB;
    case ::git_error_t::GIT_ERROR_INDEX: return error_category::Index;
    case ::git_error_t::GIT_ERROR_OBJECT: return error_category::Object;
    case ::git_error_t::GIT_ERROR_NET: return error_category::Net;
    case ::git_error_t::GIT_ERROR_TAG: return error_category::Tag;
    case ::git_error_t::GIT_ERROR_TREE: return error_category::Tree;
    case ::git_error_t::GIT_ERROR_INDEXER: return error_category::Indexer;
    case ::git_error_t::GIT_ERROR_SSL: return error_category::SSL;
    case ::git_error_t::GIT_ERROR_SUBMODULE: return error_category::Submodule;
    case ::git_error_t::GIT_ERROR_THREAD: return error_category::Thread;
    case ::git_error_t::GIT_ERROR_STASH: return error_category::Stash;
    case ::git_error_t::GIT_ERROR_CHECKOUT: return error_category::Checkout;
    case ::git_error_t::GIT_ERROR_FETCHHEAD: return error_category::FetchHead;
    case ::git_error_t::GIT_ERROR_MERGE: return error_category::Merge;
    case ::git_error_t::GIT_ERROR_SSH: return error_category::SSH;
    case ::git_error_t::GIT_ERROR_FILTER: return error_category::Filter;
    case ::git_error_t::GIT_ERROR_REVERT: return error_category::Revert;
    case ::git_error_t::GIT_ERROR_CALLBACK: return error_category::Callback;
    case ::git_error_t::GIT_ERROR_CHERRYPICK: return error_category::CherryPick;
    case ::git_error_t::GIT_ERROR_DESCRIBE: return error_category::Describe;
    case ::git_error_t::GIT_ERROR_REBASE: return error_category::Rebase;
    case ::git_error_t::GIT_ERROR_FILESYSTEM: return error_category::Filesystem;
    case ::git_error_t::GIT_ERROR_PATCH: return error_category::Patch;
    case ::git_error_t::GIT_ERROR_WORKTREE: return error_category::Worktree;
    case ::git_error_t::GIT_ERROR_SHA: return error_category::SHA;
    case ::git_error_t::GIT_ERROR_HTTP: return error_category::HTTP;
    case ::git_error_t::GIT_ERROR_INTERNAL: return error_category::Internal;
    }
    // When we don't know what to do with it, just pass it along
    return static_cast<error_category>(category);
}

std::string_view toStr(error_category category) {
    switch (category) {
    case error_category::None: return "None";
    case error_category::NoMemory: return "NoMemory";
    case error_category::OS: return "OS";
    case error_category::Invalid: return "Invalid";
    case error_category::Reference: return "Reference";
    case error_category::Zlib: return "Zlib";
    case error_category::Repository: return "Repository";
    case error_category::Config: return "Config";
    case error_category::Regex: return "Regex";
    case error_category::ODB: return "ODB";
    case error_category::Index: return "Index";
    case error_category::Object: return "Object";
    case error_category::Net: return "Net";
    case error_category::Tag: return "Tag";
    case error_category::Tree: return "Tree";
    case error_category::Indexer: return "Indexer";
    case error_category::SSL: return "SSL";
    case error_category::Submodule: return "Submodule";
    case error_category::Thread: return "Thread";
    case error_category::Stash: return "Stash";
    case error_category::Checkout: return "Checkout";
    case error_category::FetchHead: return "FetchHead";
    case error_category::Merge: return "Merge";
    case error_category::SSH: return "SSH";
    case error_category::Filter: return "Filter";
    case error_category::Revert: return "Revert";
    case error_category::Callback: return "Callback";
    case error_category::CherryPick: return "CherryPick";
    case error_category::Describe: return "Describe";
    case error_category::Rebase: return "Rebase";
    case error_category::Filesystem: return "Filesystem";
    case error_category::Patch: return "Patch";
    case error_category::Worktree: return "Worktree";
    case error_category::SHA: return "SHA";
    case error_category::HTTP: return "HTTP";
    case error_category::Internal: return "Internal";
    }
    return "unknown error";
}

error_code fromLibGit2(::git_error_code errCode) {
    switch (errCode) {
    case ::git_error_code::GIT_OK: return error_code::Ok;
    case ::git_error_code::GIT_ERROR: return error_code::Error;
    case ::git_error_code::GIT_ENOTFOUND: return error_code::Notfound;
    case ::git_error_code::GIT_EEXISTS: return error_code::Exists;
    case ::git_error_code::GIT_EAMBIGUOUS: return error_code::Ambiguous;
    case ::git_error_code::GIT_EBUFS: return error_code::BufShort;
    case ::git_error_code::GIT_EUSER: return error_code::User;
    case ::git_error_code::GIT_EBAREREPO: return error_code::BareRepo;
    case ::git_error_code::GIT_EUNBORNBRANCH: return error_code::UnbornBranch;
    case ::git_error_code::GIT_EUNMERGED: return error_code::Unmerged;
    case ::git_error_code::GIT_ENONFASTFORWARD: return error_code::NonFastForward;
    case ::git_error_code::GIT_EINVALIDSPEC: return error_code::InvalidSpec;
    case ::git_error_code::GIT_ECONFLICT: return error_code::Conflict;
    case ::git_error_code::GIT_ELOCKED: return error_code::Locked;
    case ::git_error_code::GIT_EMODIFIED: return error_code::Modified;
    case ::git_error_code::GIT_EAUTH: return error_code::Auth;
    case ::git_error_code::GIT_ECERTIFICATE: return error_code::Certificate;
    case ::git_error_code::GIT_EAPPLIED: return error_code::Applied;
    case ::git_error_code::GIT_EPEEL: return error_code::Peel;
    case ::git_error_code::GIT_EEOF: return error_code::EndOfFile;
    case ::git_error_code::GIT_EINVALID: return error_code::Invalid;
    case ::git_error_code::GIT_EUNCOMMITTED: return error_code::Uncommitted;
    case ::git_error_code::GIT_EDIRECTORY: return error_code::Directory;
    case ::git_error_code::GIT_EMERGECONFLICT: return error_code::MergeConflict;
    case ::git_error_code::GIT_PASSTHROUGH: return error_code::Passthrough;
    case ::git_error_code::GIT_ITEROVER: return error_code::IterOver;
    case ::git_error_code::GIT_RETRY: return error_code::Retry;
    case ::git_error_code::GIT_EMISMATCH: return error_code::Mismatch;
    case ::git_error_code::GIT_EINDEXDIRTY: return error_code::IndexDirty;
    case ::git_error_code::GIT_EAPPLYFAIL: return error_code::ApplyFail;
    case ::git_error_code::GIT_EOWNER: return error_code::Owner;
    }
    // When we don't know what to do with it, just pass it along
    return static_cast<error_code>(errCode);
}
std::string_view toStr(error_code errCode) {
    switch (errCode) {
    case error_code::Ok: return "Ok";
    case error_code::Error: return "Error";
    case error_code::Notfound: return "Notfound";
    case error_code::Exists: return "Exists";
    case error_code::Ambiguous: return "Ambiguous";
    case error_code::BufShort: return "BufShort";
    case error_code::User: return "User";
    case error_code::BareRepo: return "BareRepo";
    case error_code::UnbornBranch: return "UnbornBranch";
    case error_code::Unmerged: return "Unmerged";
    case error_code::NonFastForward: return "NonFastForward";
    case error_code::InvalidSpec: return "InvalidSpec";
    case error_code::Conflict: return "Conflict";
    case error_code::Locked: return "Locked";
    case error_code::Modified: return "Modified";
    case error_code::Auth: return "Auth";
    case error_code::Certificate: return "Certificate";
    case error_code::Applied: return "Applied";
    case error_code::Peel: return "Peel";
    case error_code::EndOfFile: return "EndOfFile";
    case error_code::Invalid: return "Invalid";
    case error_code::Uncommitted: return "Uncommitted";
    case error_code::Directory: return "Directory";
    case error_code::MergeConflict: return "MergeConflict";
    case error_code::Passthrough: return "Passthrough";
    case error_code::IterOver: return "IterOver";
    case error_code::Retry: return "Retry";
    case error_code::Mismatch: return "Mismatch";
    case error_code::IndexDirty: return "IndexDirty";
    case error_code::ApplyFail: return "ApplyFail";
    case error_code::Owner: return "Owner";
    }
    return "unknown code";
}
} // namespace gitxx::internal

#endif // GITSTORY_ERRORS_MAPPING_INL
