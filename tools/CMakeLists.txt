add_executable(StringDecryptor
    hex-st/main.cpp
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

target_include_directories(StringDecryptor
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(StringDecryptor PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

target_link_libraries(StringDecryptor PRIVATE hexplore Qt5::Widgets)
