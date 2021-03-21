#define REAPERAPI_IMPLEMENT
#include <reaper_plugin_functions.h>

#define REAIMGUIAPI_IMPLEMENT
#include "api.hpp"
#include "api_vararg.hpp"

extern "C" REAPER_PLUGIN_DLL_EXPORT int REAPER_PLUGIN_ENTRYPOINT(REAPER_PLUGIN_HINSTANCE instance,
                                                                 reaper_plugin_info_t* rec)
{
    if (rec == nullptr)
    {
        API::unregisterAll();
        return 0;
    }

    if (rec->caller_version != REAPER_PLUGIN_VERSION)
    {
        return 0;
    }

    plugin_getapi = rec->GetFunc;
    plugin_register = reinterpret_cast<decltype(plugin_register)>(rec->GetFunc("plugin_register"));

    API::registerAll();
    return 1;
}
