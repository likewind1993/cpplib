load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
#指定该包对其他包可见
package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "consumer",
    srcs = ["consumer.cc"],
    deps = [
        "//src/common:common",
    ],
)