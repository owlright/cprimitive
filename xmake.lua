add_rules("mode.debug", "mode.release")
add_requires("glad 0.1.36", "glfw 3.4", "opencl")

on_config(function (target)
    if target:has_tool("cxx", "cl", "clang_cl") then
        target:add("cxflags", "/utf-8") -- 对于 cl.exe，当你编译 C++ 代码时，add_cxxflags() 添加的标志和 add_cxflags() 添加的标志都会被使用。当你编译 C 代码时，只有 add_cxflags() 添加的标志会被使用。
    end
end)

target("primitive")
    set_kind("binary")
    add_files("*.c")
    add_packages("glad", "glfw")
    set_targetdir("$(projectdir)/bin/$(mode)")

target("opcl")
    set_kind("binary")
    add_files("test_opencl.cc")
    add_packages("opencl")
    set_targetdir("$(projectdir)/bin/$(mode)")

target("shape")
    set_kind("binary")
    -- add_headerfiles("shape.h", "triangle.h")
    add_files("test_shape.c", "shape.c", "triangle.c", "rasterizer.c")

includes("examples")
--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

