add_library(libhexplore SHARED 
    io/IOWrapper.hpp
)

target_include_directories(libhexplore 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR
)

set_target_properties(libhexplore PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

if (MSVC) 
    target_compile_definitions(libhexplore PRIVATE LIBHEXPLORE_EXPORTS)
else()
    target_compile_options(libhexplore PRIVATE -fvisibility=hidden)
endif()