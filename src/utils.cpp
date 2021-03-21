#include <string>
#include <vector>

#include "api.hpp"
#include "api_vararg.hpp"

#include "reaper_imgui_functions.h"
#include <imgui.h>

// Grab handles to internal ReaImGui functions
ReaImGuiFunc<bool(const char* version, size_t sz_io, size_t sz_style, size_t sz_vec2, size_t sz_vec4, size_t sz_vert,
                  size_t sz_idx, char** p_error)>
    ImGui_CheckVersionAndDataLayout{"ImGui_CheckVersionAndDataLayout"};

ReaImGuiFunc<void(ImGuiMemAllocFunc* p_alloc_func, ImGuiMemFreeFunc* p_free_func, void** p_user_data)>
    ImGui_GetAllocatorFunctions{"ImGui_GetAllocatorFunctions"};

ReaImGuiFunc<ImGuiContext*(ImGui_Context* ctx, bool enterFrame)> ImGui_GetInternalContext{"ImGui_GetInternalContext"};

// Handles setting allocators and checking memory layouts + versions
auto init_imgui(ImGui_Context* ctx) -> bool
{
    static bool init;
    if (init)
    {
        return true;
    }

    // This fails if the ImGui versions or memory layouts of structures differs between the .dll's (dynamic libs)
    char* error;
    if (!ImGui_CheckVersionAndDataLayout(IMGUI_VERSION, sizeof(ImGuiIO), sizeof(ImGuiStyle), sizeof(ImVec2),
                                         sizeof(ImVec4), sizeof(ImDrawVert), sizeof(ImDrawIdx), &error))
    {
        return false;
    }

    // Initialize empty placeholders for allocator and userdata to be set below
    void* userData;
    ImGuiMemAllocFunc allocFunc;
    ImGuiMemFreeFunc freeFunc;

    ImGui_GetAllocatorFunctions(&allocFunc, &freeFunc, &userData);
    ImGui::SetAllocatorFunctions(allocFunc, freeFunc, userData);

    return init = true;
}

auto FRAME_GUARD(ImGui_Context* ctx) -> bool
{
    if (!init_imgui(ctx))
    {
        return false; // TODO: handle error (mismatched imgui)
    }

    ImGuiContext* imgui{ImGui_GetInternalContext(ctx, true)};

    if (imgui == nullptr)
    {
        return false; // TODO: handle error (ctx is likely invalid)
    }

    ImGui::SetCurrentContext(imgui);
    return true;
}

auto generate_reascript_apidef_string(const std::string& return_type,
                                      const std::vector<std::pair<std::string, std::string>>& args,
                                      const std::string& description) -> std::string
{
    using namespace std::string_literals;

    std::string ReaScriptAPIDef;
    std::string null_terminator = "\0"s;

    // Make required ReaScript definition string, of format:
    // "void\0ImGui_Context*\0ctx\0Lorem ipsum dolor sit amet"
    // "<return type>\0<comma-separated arg types>\0<comma-separated arg names>\0<description>"

    // <return type>\0
    ReaScriptAPIDef.append(return_type + null_terminator);

    // <comma-separated arg types>\0
    auto first_arg_type_added = false;
    for (const auto& [key, _] : args)
    {
        if (first_arg_type_added)
        {
            ReaScriptAPIDef.append(",");
        }
        else
        {
            first_arg_type_added = true;
        }
        ReaScriptAPIDef.append(key);
    }
    ReaScriptAPIDef.append(null_terminator);

    // <comma-separated arg names>\0
    auto first_arg_value_added = false;
    for (const auto& [_, value] : args)
    {
        if (first_arg_value_added)
        {
            ReaScriptAPIDef.append(",");
        }
        else
        {
            first_arg_value_added = true;
        }
        ReaScriptAPIDef.append(value);
    }
    ReaScriptAPIDef.append(null_terminator);

    // <description>
    ReaScriptAPIDef.append(description);
    return ReaScriptAPIDef;
}