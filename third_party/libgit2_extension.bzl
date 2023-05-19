load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

ext = module_extension(
    implementation = lambda ctx: http_archive(
        name = "libgit2",
        url = "https://github.com/libgit2/libgit2/archive/refs/tags/v1.6.4.tar.gz",
        strip_prefix = "libgit2-1.6.4",
        sha256 = "d25866a4ee275a64f65be2d9a663680a5cf1ed87b7ee4c534997562c828e500d",
        build_file_content = """
package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all_srcs",
    srcs = glob(["**"]),
)

filegroup(
    name = "test_resources",
    srcs = glob(["tests/resources/**"]),
)
""",
    ),
)
