# this is the build file for project 
# it is autogenerated by the xmake build system.
# do not edit by hand.

# project
cmake_minimum_required(VERSION 3.13.0)
project(reaper_reaimgui_myaddon_x64 LANGUAGES C CXX ASM)

# target
add_library(reaper_reaimgui_myaddon_x64 SHARED "")
set_target_properties(reaper_reaimgui_myaddon_x64 PROPERTIES OUTPUT_NAME "reaper_reaimgui_myaddon_x64")
set_target_properties(reaper_reaimgui_myaddon_x64 PROPERTIES LIBRARY_OUTPUT_DIRECTORY "build/windows/x64/debug")
target_include_directories(reaper_reaimgui_myaddon_x64 PRIVATE
    vendor
    vendor/reaper-sdk/sdk
)
target_include_directories(reaper_reaimgui_myaddon_x64 PRIVATE
    C:/Users/rayga/AppData/Local/.xmake/packages/i/imgui/v1.82/8574311f4b544fa89a3d8c3ee79d1929/include
)
set_property(TARGET reaper_reaimgui_myaddon_x64 PROPERTY C_STANDARD 99)
if(MSVC)
    target_compile_options(reaper_reaimgui_myaddon_x64 PRIVATE $<$<COMPILE_LANGUAGE:C>:-TP>)
endif()
set_property(TARGET reaper_reaimgui_myaddon_x64 PROPERTY CXX_STANDARD 17)
target_compile_options(reaper_reaimgui_myaddon_x64 PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:/EHsc>
)
target_compile_features(reaper_reaimgui_myaddon_x64 PRIVATE c_std_99)
target_compile_features(reaper_reaimgui_myaddon_x64 PRIVATE cxx_std_17)
if(MSVC)
    target_compile_options(reaper_reaimgui_myaddon_x64 PRIVATE $<$<CONFIG:Release>:-Ox -fp:fast>)
else()
    target_compile_options(reaper_reaimgui_myaddon_x64 PRIVATE -O3)
endif()
target_link_libraries(reaper_reaimgui_myaddon_x64 PRIVATE
    imgui
)
target_link_directories(reaper_reaimgui_myaddon_x64 PRIVATE
    C:/Users/rayga/AppData/Local/.xmake/packages/i/imgui/v1.82/8574311f4b544fa89a3d8c3ee79d1929/lib
)
target_sources(reaper_reaimgui_myaddon_x64 PRIVATE
    src/api.cpp
    src/main.cpp
    src/utils.cpp
    src/widgets/my-widget.cpp
)

