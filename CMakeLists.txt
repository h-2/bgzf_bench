cmake_minimum_required (VERSION 3.4)
project (bgzf_bench CXX)

##########################################
## BIO
##########################################

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/submodules/b.i.o./build_system")
find_package (bio REQUIRED)

add_executable(bio bio.cpp)
target_link_libraries (bio bio::bio seqan3::seqan3)

##########################################
## SHRINKWRAP
##########################################

add_subdirectory(submodules/shrinkwrap)

add_executable(shrwrp shrinkwrap.cpp)
target_link_libraries (shrwrp shrinkwrap)

##########################################
## SeqAn2
##########################################

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/submodules/seqan/util/cmake")
set(SEQAN_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/submodules/seqan/include")
find_package(SeqAn REQUIRED)

message(${SEQAN_INCLUDE_DIRS})

add_executable(seqan2 seqan2.cpp)
target_include_directories(seqan2 PRIVATE ${SEQAN_INCLUDE_DIRS})
target_compile_definitions(seqan2 PRIVATE ${SEQAN_DEFINITIONS})
target_compile_options(seqan2 PRIVATE ${SEQAN_CXX_FLAGS})
target_link_libraries (seqan2 PUBLIC ${SEQAN_LIBRARIES})

add_executable(seqan2_4threads seqan2.cpp)
target_include_directories(seqan2_4threads PRIVATE ${SEQAN_INCLUDE_DIRS})
target_compile_definitions(seqan2_4threads PRIVATE ${SEQAN_DEFINITIONS} "SEQAN_BGZF_NUM_THREADS=3")
target_compile_options(seqan2_4threads PRIVATE ${SEQAN_CXX_FLAGS})
target_link_libraries (seqan2_4threads PUBLIC ${SEQAN_LIBRARIES})

##########################################
## HTSLib
##########################################

include(ExternalProject)

ExternalProject_Add(
    project_htslib
    BUILD_IN_SOURCE 1
    SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/htslib
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/htslib
    CONFIGURE_COMMAND cp -a ${CMAKE_CURRENT_SOURCE_DIR}/submodules/htslib ${CMAKE_CURRENT_BINARY_DIR}/ COMMAND autoheader COMMAND autoconf COMMAND ${CMAKE_CURRENT_BINARY_DIR}/htslib/configure --disable-libcurl --disable-gcs --disable-lzma --disable-bz2 --without-libdeflate
        "CFLAGS=${CMAKE_C_FLAGS_RELEASE}"
        "LDFLAGS=${CMAKE_EXE_LINKER_FLAGS}"
        "CC=${CMAKE_C_COMPILER}"
    BUILD_COMMAND $(MAKE) -C ${CMAKE_CURRENT_BINARY_DIR}/htslib libhts.a
    INSTALL_COMMAND ""
)

add_library(htslib STATIC IMPORTED)

set(htslib_location ${CMAKE_CURRENT_BINARY_DIR}/htslib/libhts.a)
message(STATUS "htslib target location is ${htslib_location}")
set_property(TARGET htslib PROPERTY IMPORTED_LOCATION ${htslib_location})
add_dependencies(htslib project_htslib)

add_executable(hts hts.cpp)
target_include_directories(hts PUBLIC SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/submodules/htslib)
target_link_libraries(hts PUBLIC htslib z)
