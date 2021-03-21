#include "../utils.hpp"
#include <imgui.h>

void FooBarNew(ImGui_Context* ctx, const char* text)
{
    if (!FRAME_GUARD(ctx))
    {
        return;
    };
    ImGui::Text("%s", text);
}

DEFINE_API(FooBarNew)
("void", {{"ImGui_Context*", "ctx"}, {"const char*", "text"}}, "Lorem ipsum, here is my description");
