add_library(hexplore SHARED 
    io/StandardIO.cpp
)

target_include_directories(hexplore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(hexplore PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

target_compile_definitions(hexplore PRIVATE LIBHEXPLORE_EXPORTS)
