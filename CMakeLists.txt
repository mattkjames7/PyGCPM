cmake_minimum_required(VERSION 3.20)

project(PyGCPM LANGUAGES C Fortran)

set(LIBGCPM_DIR "${CMAKE_CURRENT_SOURCE_DIR}/PyGCPM/__data/libgcpm")
file(GLOB IRI_SOURCES CONFIGURE_DEPENDS "${LIBGCPM_DIR}/iri/*.for")
file(GLOB XFORM_SOURCES CONFIGURE_DEPENDS
    "${LIBGCPM_DIR}/xform/*.for"
    "${LIBGCPM_DIR}/xform/*.FOR"
)
file(GLOB GCPM_SOURCES CONFIGURE_DEPENDS "${LIBGCPM_DIR}/gcpm/*.for")

add_library(gcpm SHARED
    "${LIBGCPM_DIR}/libgcpm.c"
    ${IRI_SOURCES}
    ${XFORM_SOURCES}
    ${GCPM_SOURCES}
)
if(UNIX)
    target_link_libraries(gcpm PRIVATE m)
endif()
set_target_properties(gcpm PROPERTIES
    OUTPUT_NAME "gcpm"
    PREFIX "lib"
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)

if(CMAKE_Fortran_COMPILER_ID STREQUAL "GNU")
    target_compile_options(gcpm PRIVATE
        $<$<COMPILE_LANGUAGE:Fortran>:-w;-fno-automatic;-std=legacy;-ffixed-line-length-none>
    )
endif()

install(
    TARGETS gcpm
    LIBRARY DESTINATION PyGCPM/__data/libgcpm COMPONENT Python
    RUNTIME DESTINATION PyGCPM/__data/libgcpm COMPONENT Python
)
