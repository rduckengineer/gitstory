package(default_visibility = ["//visibility:private"])

load("@rules_foreign_cc//foreign_cc:cmake.bzl", "cmake")

cmake(
    name = "libgit2",
    cache_entries = {
        "BUILD_CLI": "OFF",
        "BUILD_SHARED_LIBS": "OFF",
        "BUILD_TESTS": "OFF",
    },
    generate_args = ["-G Ninja"],
    lib_source = "@libgit2//:all_srcs",
    linkopts = ["-lssl -lcrypto -lz"],
    out_static_libs = ["libgit2.a"],
)

cc_library(
    name = "gitxx",
    srcs = ["global.cpp"],
    hdrs = ["global.hpp"],
    visibility = ["//visibility:public"],
    deps = [
        ":blame",
        ":commit",
        ":repository",
        "@fmt",
    ],
)

cc_library(
    name = "commit",
    srcs = ["commit.cpp"],
    hdrs = ["commit.hpp"],
    deps = [
        "repository",
        ":tree",
        ":unique_ptr",
    ],
)

cc_library(
    name = "tree",
    srcs = ["tree.cpp"],
    hdrs = ["tree.hpp"],
    deps = [
        "repository",
        ":blob",
        ":unique_ptr",
    ],
)

cc_library(
    name = "blob",
    srcs = ["blob.cpp"],
    hdrs = ["blob.hpp"],
    deps = [
        ":oid",
        ":unique_ptr",
    ],
)

cc_library(
    name = "blame",
    srcs = ["blame.cpp"],
    hdrs = ["blame.hpp"],
    deps = [
        ":oid",
        ":repository",
        ":signature",
        ":unique_ptr",
    ],
)

cc_library(
    name = "repository",
    srcs = ["repository.cpp"],
    hdrs = ["repository.hpp"],
    deps = [
        ":refs",
        ":unique_ptr",
    ],
)

cc_library(
    name = "refs",
    srcs = ["refs.cpp"],
    hdrs = ["refs.hpp"],
    deps = [
        ":oid",
        ":unique_ptr",
    ],
)

cc_library(
    name = "oid",
    srcs = ["oid.cpp"],
    hdrs = [
        "oid.hpp",
        "oid_static_string.hpp",
    ],
    deps = [
        ":errors",
        ":unique_ptr",
    ],
)

cc_library(
    name = "errors",
    srcs = [
        "errors.cpp",
    ],
    hdrs = [
        "errors.hpp",
        "errors_mapping.inl",
    ],
    deps = [
        ":libgit2",
        "@fmt",
    ],
)

cc_library(
    name = "unique_ptr",
    hdrs = ["unique_ptr.hpp"],
)

cc_library(
    name = "signature",
    srcs = ["signature.cpp"],
    hdrs = ["signature.hpp"],
    deps = [":libgit2"],
)
