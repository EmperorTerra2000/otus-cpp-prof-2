cmake_minimum_required(VERSION 3.15)

set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VESRION})

set(CMAKE_BUILD_TYPE Debug)

add_executable(ip_filter_cli ip_filter.cpp)

set_target_properties(ip_filter_cli PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(ip_filter_cli PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ip_filter_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)