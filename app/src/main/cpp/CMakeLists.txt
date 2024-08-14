# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

# Declares the project name.
project("keiimgui")

set(BNM_BUILD_FILES ON)
set(BNM_LINK_LOG OFF)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
add_compile_options(
        -w                         # Suppress all warnings
        -s                         # Strip debug info
        -Wno-error=format-security # Disable error for format security warnings
        -fvisibility=hidden        # Hide all symbols by default
        -fpermissive               # Allow non-conformant code
        -fexceptions               # Enable exception handling
        -Werror                    # Treat all warnings as errors
        -Wno-error=c++11-narrowing # Disable error for C++11 narrowing warnings
        -Wall                      # Enable all warnings
)

# Linker flags
add_link_options(
        -Wl,--gc-sections          # Remove unused sections
        -Wl,--strip-all            # Strip all symbols
        -llog                      # Link with liblog
)

# Include directories
set(PUBLIC_INCLUDE_DIRS
        include
        external/include
)

set(INCLUDE_DIRS
        include
        external/include
        external
        external/utf8
        src/BNM_data
)

# BNM Library
add_library(
        BNM
        STATIC
        src/Class.cpp
        src/ClassesManagement.cpp
        src/Coroutine.cpp
        src/Delegates.cpp
        src/EventBase.cpp
        src/Exceptions.cpp
        src/FieldBase.cpp
        src/Hooks.cpp
        src/Image.cpp
        src/Internals.cpp
        src/Loading.cpp
        src/MethodBase.cpp
        src/MonoStructures.cpp
        src/PropertyBase.cpp
        src/UnityStructures.cpp
        src/Utils.cpp
)

target_include_directories(
        BNM
        PUBLIC
        ${INCLUDE_DIRS}
)

if (${BNM_LINK_LOG})
    target_link_libraries(
            BNM
            PUBLIC
            log
    )
endif ()

# ImGui Library
include_directories(
        ${CMAKE_SOURCE_DIR}/ImGui
        ${CMAKE_SOURCE_DIR}/ImGui/backends
)

add_library(ImGui STATIC
        ImGui/imgui.cpp
        ImGui/imgui_draw.cpp
        ImGui/imgui_widgets.cpp
        ImGui/imgui_tables.cpp
        ImGui/backends/imgui_impl_opengl3.cpp
        ImGui/backends/imgui_impl_android.cpp
        ImGui/imgui_demo.cpp

)

# Main Library
add_library(${CMAKE_PROJECT_NAME} SHARED
        native-lib.cpp
)

# Link libraries to the main project
target_link_libraries(${CMAKE_PROJECT_NAME}
        ImGui
        BNM
        android
        log
        EGL
        GLESv2
)

# Examples Library
if (${BNM_BUILD_FILES})
    add_library(BNM_Examples
            SHARED
            native-lib.cpp
            main.cpp
    )

    target_include_directories(
            BNM_Examples
            PUBLIC
            ${PUBLIC_INCLUDE_DIRS}
    )

    target_link_libraries(
            BNM_Examples
            PUBLIC
            BNM
            ImGui
            android
            log
            EGL
            GLESv2
    )
endif ()

set_property(TARGET BNM PROPERTY BNM_INCLUDE_DIRECTORIES ${PUBLIC_INCLUDE_DIRS})
