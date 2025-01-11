project(
    'cWicked',
    ['cpp', 'c'],
    version: '0.71.652',
    default_options: ['cpp_std=c++20', 'c_std=c23', 'cpp_rtti=false'],
)

dep_sdl2 = dependency('SDL2', include_type: 'system', static: false)
dep_pthread = dependency('threads')

compiler = meson.get_compiler('cpp')
dep_wicked = compiler.find_library(
    'WickedEngine_Linux',
    dirs: [meson.project_source_root() / '.wi/.build_RelWithDebInfo/WickedEngine'],
    header_include_directories: include_directories('.wi/WickedEngine'),
    required: true,
    static: true,
)
dep_jolt = compiler.find_library(
    'Jolt',
    dirs: [meson.project_source_root() / '.wi/.build_RelWithDebInfo/WickedEngine'],
    header_include_directories: include_directories('.wi/WickedEngine', '.wi/WickedEngine/Jolt'),
    required: true,
    static: true,
)
dep_lua = compiler.find_library(
    'LUA',
    dirs: [
        meson.project_source_root() / '.wi/.build_RelWithDebInfo/WickedEngine/LUA',
    ],
    header_include_directories: include_directories('.wi/WickedEngine', '.wi/WickedEngine/LUA'),
    required: true,
    static: true,
)
dep_faudio = compiler.find_library(
    'FAudio',
    dirs: [
        meson.project_source_root() / '.wi/.build_RelWithDebInfo/WickedEngine/Utility/FAudio',
    ],
    header_include_directories: include_directories(
        '.wi/WickedEngine',
        '.wi/WickedEngine/Utility',
        '.wi/WickedEngine/Utility/FAudio',
        '.wi/WickedEngine/Utility/FAudio/include',
        '.wi/WickedEngine/Utility/FAudio/src',
    ),
    required: true,
    static: true,
)
dep_utility = compiler.find_library(
    'Utility',
    dirs: [
        meson.project_source_root() / '.wi/.build_RelWithDebInfo/WickedEngine/Utility',
    ],
    header_include_directories: include_directories(
        '.wi/WickedEngine',
        '.wi/WickedEngine/Utility',
        '.wi/WickedEngine/Utility/include',
        '.wi/WickedEngine/Utility/include/spirv',
        '.wi/WickedEngine/Utility/include/spirv/unified1',
        '.wi/WickedEngine/Utility/vulkan',
        '.wi/WickedEngine/Utility/vulkan/vk_video',
        '.wi/WickedEngine/Utility/meshoptimizer',
        '.wi/WickedEngine/Utility/basis_universal',
        '.wi/WickedEngine/Utility/basis_universal/encoder',
        '.wi/WickedEngine/Utility/basis_universal/transcoder',
        '.wi/WickedEngine/Utility/basis_universal/zstd',
    ),
    required: true,
    static: true,
)

lib_cwicked = shared_library(
    'cwicked',
    dependencies: [
        dep_pthread,
        dep_sdl2,
        dep_lua,
        dep_jolt,
        dep_faudio,
        dep_utility,
        dep_wicked,
    ],
    cpp_pch: 'pch/wi_pch.h',
    include_directories: include_directories('.wi/WickedEngine'),
    c_args: ['-gsplit-dwarf', '-fms-extensions', '-Wstrict-prototypes', '-DSDL2'],
    cpp_args: ['-gsplit-dwarf', '-fms-extensions', '-Wstrict-prototypes', '-DSDL2'],
    sources: ['src/cWicked.cpp'],
)

executable(
    'cWickedDemo.exec',
    dependencies: [dep_sdl2, dep_pthread],
    link_with: [lib_cwicked],
    implicit_include_directories: true,
    link_language: 'c',
    c_args: ['-gsplit-dwarf', '-fms-extensions', '-Wstrict-prototypes', '-DSDL2'],
    sources: ['src/demo/main.c'],
)
