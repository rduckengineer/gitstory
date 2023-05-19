load("@rules_foreign_cc//foreign_cc:cmake.bzl", "cmake")
load("//gitxx:rules_cc.bzl", "gitxx_cc_library")

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

gitxx_cc_library(
    name = "gitxx",
    srcs = [
        "errors.cpp",
        "repository.cpp",
    ],
    hdrs = [
        "errors.hpp",
        "repository.hpp",
        "unique_ptr.hpp",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":libgit2",
        "@fmt",
    ],
)
