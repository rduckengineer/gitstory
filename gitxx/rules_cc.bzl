_WARNINGS = ["-Werror", "-Wall", "-Wextra"]

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
        copts = _WARNINGS + copts,
        **kwargs
    )

def gitxx_cc_test(
        name,
        srcs,
        deps = [],
        data = [],
        copts = [],
        **kwargs):
    native.cc_test(
        name = name,
        srcs = srcs,
        data = data,
        deps = deps,
        copts = _WARNINGS + copts,
        **kwargs
    )
