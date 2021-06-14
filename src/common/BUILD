load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
#指定该包对其他包可见
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "common",
    hdrs = [
        "queue.h",
        "thread_pool_interface.h",
        "thread_pool.h",
        "string_utils.h",
    ],
    linkopts = ["-pthread"],
    alwayslink = 1,
)