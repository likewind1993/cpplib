load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
#指定该包对其他包可见
package(default_visibility = ["//visibility:public"])

cc_library(
  name = "utils",
  hdrs = [
    "quick_sort.h",
  ]
)

cc_binary(
  name = "quick_benchmark_generator",
  srcs = [
    "quick_benchmark_generator.cc",
  ],
  deps = [
    "//src/common:common",
  ]
)

cc_binary (
  name = "quick_sort_test", 
  srcs = [
    "quick_sort_test.cc",
  ],
  deps = [
    ":utils",
  ]
)