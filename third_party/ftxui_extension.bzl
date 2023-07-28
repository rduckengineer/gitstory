load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def declare_ftxui(ctx):
    FTXUI_VERSION = "5094b5f3fb9a59dda77090960cf868d08f915a29"
    FTXUI_SHA256 = "c96b93713206ea7cbee550a7d6d17a1efef2632413b6fc0aea5538e828e59b54"

    http_archive(
        name = "ftxui",
        build_file = "//third_party:ftxui.BUILD",
        sha256 = FTXUI_SHA256,
        strip_prefix = "FTXUI-{}".format(FTXUI_VERSION),
        url = "https://github.com/ArthurSonzogni/FTXUI/archive/{}.tar.gz".format(FTXUI_VERSION),
    )

ftxui = module_extension(
    implementation = declare_ftxui,
)
