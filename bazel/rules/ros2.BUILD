load("@rules_cc//cc:defs.bzl", "cc_import", "cc_library")
package(default_visibility = ["//visibility:public"])
cc_import(name = "ament_index_cpp_so", shared_library = "lib/libament_index_cpp.so")
cc_import(name = "builtin_interfaces__rosidl_generator_c_so", shared_library = "lib/libbuiltin_interfaces__rosidl_generator_c.so")
cc_import(name = "fmt_so", shared_library = "lib/libfmt.so")
cc_import(name = "fmt_9_so", shared_library = "lib/libfmt.so.9")
cc_import(name = "libstatistics_collector_so", shared_library = "lib/liblibstatistics_collector.so")
cc_import(name = "rcl_so", shared_library = "lib/librcl.so")
cc_import(name = "rcl_interfaces__rosidl_generator_c_so", shared_library = "lib/librcl_interfaces__rosidl_generator_c.so")
cc_import(name = "rcl_interfaces__rosidl_typesupport_c_so", shared_library = "lib/librcl_interfaces__rosidl_typesupport_c.so")
cc_import(name = "rcl_interfaces__rosidl_typesupport_cpp_so", shared_library = "lib/librcl_interfaces__rosidl_typesupport_cpp.so")
cc_import(name = "rcl_logging_interface_so", shared_library = "lib/librcl_logging_interface.so")
cc_import(name = "rcl_logging_spdlog_so", shared_library = "lib/librcl_logging_spdlog.so")
cc_import(name = "rcl_yaml_param_parser_so", shared_library = "lib/librcl_yaml_param_parser.so")
cc_import(name = "rclcpp_so", shared_library = "lib/librclcpp.so")
cc_import(name = "rcpputils_so", shared_library = "lib/librcpputils.so")
cc_import(name = "rcutils_so", shared_library = "lib/librcutils.so")
cc_import(name = "rmw_so", shared_library = "lib/librmw.so")
cc_import(name = "rmw_implementation_so", shared_library = "lib/librmw_implementation.so")
cc_import(name = "rosgraph_msgs__rosidl_generator_c_so", shared_library = "lib/librosgraph_msgs__rosidl_generator_c.so")
cc_import(name = "rosgraph_msgs__rosidl_typesupport_cpp_so", shared_library = "lib/librosgraph_msgs__rosidl_typesupport_cpp.so")
cc_import(name = "rosidl_dynamic_typesupport_so", shared_library = "lib/librosidl_dynamic_typesupport.so")
cc_import(name = "rosidl_runtime_c_so", shared_library = "lib/librosidl_runtime_c.so")
cc_import(name = "rosidl_typesupport_c_so", shared_library = "lib/librosidl_typesupport_c.so")
cc_import(name = "rosidl_typesupport_cpp_so", shared_library = "lib/librosidl_typesupport_cpp.so")
cc_import(name = "rosidl_typesupport_introspection_cpp_so", shared_library = "lib/librosidl_typesupport_introspection_cpp.so")
cc_import(name = "service_msgs__rosidl_generator_c_so", shared_library = "lib/libservice_msgs__rosidl_generator_c.so")
cc_import(name = "spdlog_so", shared_library = "lib/libspdlog.so")
cc_import(name = "spdlog_1_12_so", shared_library = "lib/libspdlog.so.1.12")
cc_import(name = "statistics_msgs__rosidl_generator_c_so", shared_library = "lib/libstatistics_msgs__rosidl_generator_c.so")
cc_import(name = "statistics_msgs__rosidl_typesupport_cpp_so", shared_library = "lib/libstatistics_msgs__rosidl_typesupport_cpp.so")
cc_import(name = "std_msgs__rosidl_generator_c_so", shared_library = "lib/libstd_msgs__rosidl_generator_c.so")
cc_import(name = "std_msgs__rosidl_typesupport_cpp_so", shared_library = "lib/libstd_msgs__rosidl_typesupport_cpp.so")
cc_import(name = "tracetools_so", shared_library = "lib/libtracetools.so")
cc_import(name = "type_description_interfaces__rosidl_generator_c_so", shared_library = "lib/libtype_description_interfaces__rosidl_generator_c.so")
cc_import(name = "type_description_interfaces__rosidl_typesupport_c_so", shared_library = "lib/libtype_description_interfaces__rosidl_typesupport_c.so")

# rclcpp library: all ROS2 headers + transitive .so deps
cc_library(
    name = "rclcpp",
    hdrs = glob(
        [
            "include_flat/**/*.h",
            "include_flat/**/*.hpp",
        ],
        exclude = [
            "include_flat/features.h",
            "include_flat/time.h",
            "include_flat/string.h",
            "include_flat/signal.h",
            "include_flat/stdio.h",
            "include_flat/stdlib.h",
            "include_flat/math.h",
            "include_flat/assert.h",
            "include_flat/errno.h",
            "include_flat/unistd.h",
            "include_flat/pthread.h",
            "include_flat/stddef.h",
            "include_flat/stdint.h",
        ],
        allow_empty = False,
    ),
    strip_include_prefix = "include_flat",
    deps = [
        ":ament_index_cpp_so",
        ":builtin_interfaces__rosidl_generator_c_so",
        ":fmt_so",
        ":fmt_9_so",
        ":libstatistics_collector_so",
        ":rcl_so",
        ":rcl_interfaces__rosidl_generator_c_so",
        ":rcl_interfaces__rosidl_typesupport_c_so",
        ":rcl_interfaces__rosidl_typesupport_cpp_so",
        ":rcl_logging_interface_so",
        ":rcl_logging_spdlog_so",
        ":rcl_yaml_param_parser_so",
        ":rclcpp_so",
        ":rcpputils_so",
        ":rcutils_so",
        ":rmw_so",
        ":rmw_implementation_so",
        ":rosgraph_msgs__rosidl_generator_c_so",
        ":rosgraph_msgs__rosidl_typesupport_cpp_so",
        ":rosidl_dynamic_typesupport_so",
        ":rosidl_runtime_c_so",
        ":rosidl_typesupport_c_so",
        ":rosidl_typesupport_cpp_so",
        ":rosidl_typesupport_introspection_cpp_so",
        ":service_msgs__rosidl_generator_c_so",
        ":spdlog_so",
        ":spdlog_1_12_so",
        ":statistics_msgs__rosidl_generator_c_so",
        ":statistics_msgs__rosidl_typesupport_cpp_so",
        ":std_msgs__rosidl_generator_c_so",
        ":std_msgs__rosidl_typesupport_cpp_so",
        ":tracetools_so",
        ":type_description_interfaces__rosidl_generator_c_so",
        ":type_description_interfaces__rosidl_typesupport_c_so",
    ],
)
