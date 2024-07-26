cmake_minimum_required(VERSION 3.4...3.18)
project(mstmap)

# Add the pybind11 include directories
set(pybind11_DIR /home/amohs002/miniconda3/envs/mstwrap/lib/python3.12/site-packages/pybind11/share/cmake/pybind11)

# Find pybind11 package
find_package(pybind11 REQUIRED)

add_library(mstmap MODULE
    mstmap_wrapper.cpp
    mstmap.cpp
    constants.h
    genetic_map_DH.cpp
    genetic_map_RIL.cpp
    linkage_group_DH.cpp
    linkage_group_RIL.cpp
    MSTOpt.cpp
)

target_link_libraries(mstmap PRIVATE pybind11::module)
set_target_properties(mstmap PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}" SUFFIX "${PYTHON_MODULE_EXTENSION}")
