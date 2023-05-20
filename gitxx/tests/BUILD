load("//gitxx:rules_cc.bzl", "gitxx_cc_test")

gitxx_cc_test(
    name = "repository_test",
    srcs = ["repository_test.cpp"],
    data = ["@libgit2//:test_resources"],
    deps = [
        "//gitxx",
        "//test:check_invoke_nothrow",
        "@catch2//:catch2_main",
        "@fmt",
    ],
)
