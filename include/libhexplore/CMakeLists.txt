add_library(libhexplore SHARED 
    io/IOWrapper.hpp
    io/StandardIO.hpp
)

target_include_directories(libhexplore 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(libhexplore PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${CMAKE_SOURCE_DIR}/include/hexplore.h"

)

if(MINGW)
    # For MinGW, we need to explicitly export symbols
    set_target_properties(hexplore PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS ON
    )
endif()


include(GenerateExportHeader)
generate_export_header(hexplore
    BASE_NAME HEXPLORE
    EXPORT_MACRO_NAME HEXPLORE_EXPORT
    EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/include/hexplore_export.h
    STATIC_DEFINE HEXPLORE_STATIC
)

target_include_directories(hexplore PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
)

install(FILES ${CMAKE_BINARY_DIR}/include/hexplore_export.h
    DESTINATION include
)

# Install the target and create export-set
install(TARGETS hexplore
    EXPORT hexplore-targets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)
