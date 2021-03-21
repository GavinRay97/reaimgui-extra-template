-- Requires will try to use either system package manager, or third-party package manages (vcpkg, Conan, etc)
-- To automatically find and wire up library dependencies
add_requires("imgui v1.82", { verify = false })
add_rules("mode.debug", "mode.release")

-- 1. Set the current config: $ xmake config --plat=windows --mode=debug --arch=x64 --verbose --diagnosis --clean
-- 2. Then run the build:     $ xmake build --verbose --diagnosis
-- 3. Generate CMake/Comp DB: $ xmake generate_cmakelists_and_compile_commands
target("reaper_imgui_extra_myaddon_x64")
  set_arch("x64")
  set_kind("shared")
  set_plat(os.host())
  set_optimize("fastest") -- none, faster, fastest, smallest
  set_languages("c99", "cxx17")
  add_files("src/*.cpp")
  add_files("src/widgets/*.cpp")
  add_includedirs("./vendor")
  add_includedirs("./vendor/reaper-sdk/sdk")
  add_packages("imgui")


task("fetch_reaper_sdk")
  on_run(function()
    import("devel.git")

    if os.exists("./vendor/reaper-sdk") then
      print("./vendor/reaper-sdk already exists, not fetching it")
      return
    end

    if not os.exists("./vendor/reaper-sdk") and os.tryrm("./vendor/reaper-sdk") then
      print("Successfully cleaned old ./vendor/reaper-sdk")
    end

    print("Fetching ./vendor/reaper-sdk...")
    git.clone("https://github.com/justinfrankel/reaper-sdk.git", { branch = "main", outputdir = "./vendor/reaper-sdk" })
    -- Maybe git.fetch() here to grab specific SHA?
  end)
  set_menu({
    usage = "xmake fetch_reaper_sdk",
    description = "",
    options = {}
  })


task("generate_cmakelists_and_compile_commands")
  on_run(function ()
    os.exec("xmake project -k cmakelists -a x64 -vD")
    os.exec("xmake project -k compile_commands -a x64 -vD")
  end)
  set_menu({
    usage = "xmake generate_cmakelists_and_compile_commands",
    description = "",
    options = {}
  })
