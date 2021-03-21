#include <string>
#include <vector>

#include "reaper_imgui_functions.h"

#include "api.hpp"
#include "api_vararg.hpp"

#include <imgui.h>

auto init_imgui(ImGui_Context* ctx) -> bool;
auto FRAME_GUARD(ImGui_Context* ctx) -> bool;
auto generate_reascript_apidef_string(const std::string& return_type,
                                      const std::vector<std::pair<std::string, std::string>>& args,
                                      const std::string& description) -> std::string;

template <auto F> struct APIBuilder
{
    const char* name;

    auto create(const std::string& type, const std::vector<std::pair<std::string, std::string>>& args,
                const std::string& help)
    {
        static const std::string& definition{generate_reascript_apidef_string(type, args, help)};
        return API{name, reinterpret_cast<void*>(F), reinterpret_cast<void*>(&InvokeReaScriptAPI<F>),
                   definition.c_str()};
    }
};

#define DEFINE_API(name) static const API API##name = APIBuilder<name>{#name}.create
