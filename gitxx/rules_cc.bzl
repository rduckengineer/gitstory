def gitxx_cc_library(
        name,
        copts = [],
        srcs = [],
        hdrs = [],
        deps = [],
        **kwargs):
    native.cc_library(
        name = name,
        srcs = srcs,
        hdrs = hdrs,
        deps = deps,
        copts = ["-Werror", "-Wall", "-Wextra"],
        **kwargs
    )
