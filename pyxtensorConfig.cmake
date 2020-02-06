# pyxtensor cmake module
#
# This module sets the target:
#
#     pyxtensor
#
# In addition, it sets the following variables:
#
#     pyxtensor_FOUND - true if pyxtensor found
#     pyxtensor_VERSION - pyxtensor's version
#     pyxtensor_INCLUDE_DIRS - the directory containing pyxtensor headers

include(CMakeFindDependencyMacro)

# Define target "pyxtensor"

if(NOT TARGET pyxtensor)
    include("${CMAKE_CURRENT_LIST_DIR}/pyxtensorTargets.cmake")
    get_target_property(pyxtensor_INCLUDE_DIRS pyxtensor INTERFACE_INCLUDE_DIRECTORIES)
endif()

# Find dependencies

find_dependency(xtensor)
