package(default_visibility = ["//visibility:public"])

cc_library(
    name = "ftxui",
    deps = [":dom", ":component", ":screen"],
)

cc_library(
    name = "component",
    srcs = glob(
        include = ["src/ftxui/component/*.cpp"],
        exclude = [
            "src/ftxui/component/*test*",
            "src/ftxui/component/*fuzzer*",
        ],
    ),
    hdrs = glob(["include/ftxui/component/*.hpp"]),
    strip_include_prefix = "include",
    implementation_deps = [
        ":component_internal_headers",
        ":dom",
        ":dom_internal_headers",
        ":screen",
        ":screen_internal_headers",
        ":util",
    ],
)

cc_library(
    name = "component_internal_headers",
    hdrs = glob(["src/ftxui/component/*.hpp"]),
    strip_include_prefix = "src",
)

cc_library(
    name = "dom",
    srcs = glob(
        include = ["src/ftxui/dom/*.cpp"],
        exclude = ["src/ftxui/dom/*_test.cpp"],
    ),
    hdrs = glob(["include/ftxui/dom/*.hpp"]),
    strip_include_prefix = "include",
    implementation_deps = [
        ":dom_internal_headers",
        ":screen",
        ":util",
    ],
)

cc_library(
    name = "dom_internal_headers",
    hdrs = glob(["src/ftxui/dom/*.hpp"]),
    strip_include_prefix = "src",
)

cc_library(
    name = "screen",
    srcs = glob(
        include = ["src/ftxui/screen/*.cpp"],
        exclude = ["src/ftxui/screen/*_test.cpp"],
    ),
    hdrs = glob(["include/ftxui/screen/*.hpp"]),
    strip_include_prefix = "include",
    implementation_deps = [
        ":screen_internal_headers",
    ],
)

cc_library(
    name = "screen_internal_headers",
    hdrs = glob(["src/ftxui/screen/*.hpp"]),
    strip_include_prefix = "src",
)

cc_library(
    name = "util",
    hdrs = glob(["include/ftxui/util/*.hpp"]),
    strip_include_prefix = "include",
)
