#ifndef REAIMGUI_EXTRA_API_HPP
#define REAIMGUI_EXTRA_API_HPP

#include <string>
#include <tuple>

class API
{
  public:
    static void registerAll();
    static void unregisterAll();

    API(const char* name, void* cImpl, void* reascriptImpl, const char* definition);
    ~API();

  private:
    struct RegInfo
    {
        std::string key;
        void* value;
        void announce() const;
    } m_regs[3];
};

#endif
