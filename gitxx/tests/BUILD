cc_test(
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

cc_test(
    name = "refs_test",
    srcs = ["refs_test.cpp"],
    data = ["@libgit2//:test_resources"],
    deps = [
        "//gitxx",
        "//test:check_invoke_nothrow",
        "@catch2//:catch2_main",
        "@fmt",
    ],
)
