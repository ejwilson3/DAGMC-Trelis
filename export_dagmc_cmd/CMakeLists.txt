project(SDK_CommandPluginExample)

# cmake_minimum_required(VERSION 3.1)
cmake_minimum_required(VERSION 2.8)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DHAVE_IGEOM_CONE -fPIC" )

# adjust compiler setting for Linux using gcc version 5.0 and higher
if(CMAKE_SYSTEM_NAME MATCHES Linux AND CMAKE_COMPILER_IS_GNUCXX)
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "5.0")
    if(NOT CMAKE_CXX_FLAGS MATCHES _GLIBCXX_USE_CXX11_ABI)
      set(CMAKE_CXX_FLAGS "-D_GLIBCXX_USE_CXX11_ABI=0 ${CMAKE_CXX_FLAGS}")
    endif()
  endif()
endif()

# Get the packages needed to use the SDK
find_package(Cubit REQUIRED CONFIG)
include_directories(${CUBIT_INCLUDE_DIRS})

find_package(MOAB REQUIRED)
include_directories(${MOAB_INCLUDE_DIRS})

include_directories("${DAGMC_DIR}/../include/")

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
#qt4_wrap_ui(ui_src ${GUI_UI})

#include_directories("${CMAKE_SOURCE_DIR}")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR})

option(SKD_BUILD_HDF5 "Use hdf5 libraries when building the SDK examples." OFF)
if(SDK_BUILD_HDF5)
  include_directories(${HDF5_SOURCE_DIR}/src
                      ${HDF5_SOURCE_DIR}/hl/src
                      ${HDF5_SOURCE_DIR}/hl/c++/src
                      ${HDF5_BINARY_DIR})
  add_definitions(-DSDK_BUILD_HDF5)
endif()

set(SRC
    iGeom_test.cpp
    iGeom_test.hpp
    iGeom_funcs.cpp
    iGeom_funcs.hpp
    MyPlugin.cpp
    MyPlugin.hpp
    DAGMCExportCommand.cpp
    DAGMCExportCommand.hpp
    mcnp2cad.cpp
    mcnp2cad.hpp
    mcnp2cad/MCNPInput.cpp
    mcnp2cad/MCNPInput.hpp
    mcnp2cad/geometry.cpp
    mcnp2cad/geometry.hpp
    mcnp2cad/volumes.cpp
    mcnp2cad/volumes.hpp
    mcnp2cad/iGeomError.cc)

add_library(dagmc_export_plugin SHARED ${SRC})
target_link_libraries(dagmc_export_plugin cubiti cubit_util cubit_geom ${DAGMC_DIR}/libmakeWatertight.so ${MOAB_LIBRARIES})

set(COMPONENT_SRC
    DagComp.cpp
    DagComp.hpp
    DAGMCExportGUI.cpp
    DAGMCExportGUI.hpp)

add_library(dagmc_export_component STATIC ${COMPONENT_SRC})
target_link_libraries(dagmc_export_component clarogui navigation clarofw pickwidget Qt4::QtGui dagmc_export_plugin)
set_target_properties(dagmc_export_component PROPERTIES AUTOMOC 1)



find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_PATH})

set(DOT_I_DEPENDS DagComp.hpp)
set(CMAKE_SWIG_FLAGS "")
set(CMAKE_SWIG_OUTDIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set_source_files_properties(dagcomp.i PROPERTIES CPLUSPLUS ON OBJECT_DEPENDS "${DOT_I_DEPENDS}")
set(SWIG_MODULE_dagcomp_EXTRA_DEPS ${DOT_I_DEPENDS})

get_target_property(COMPONENT_INCLUDE component INTERFACE_INCLUDE_DIRECTORIES)
include_directories(${COMPONENT_INCLUDE})

swig_add_module(dagcomp python dagcomp.i DagComp.cpp DagComp.hpp)

swig_link_libraries(dagcomp component dagmc_export_component ${PYTHON_LIBRARIES})
