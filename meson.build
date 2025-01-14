project(
    'cWicked',
    ['cpp', 'c'],
    version: '0.71.652',
    default_options: ['cpp_std=c++20', 'c_std=c23', 'cpp_rtti=false'],
)

add_global_arguments(
    '-gsplit-dwarf',
    '-fms-extensions',
    '-DSDL2',
    '-march=native',
    # '-sanitize=address',
    language: ['cpp', 'c'],
)

dep_sdl2 = dependency('SDL2', include_type: 'system', static: false)
dep_pthread = dependency('threads')

compiler = meson.get_compiler('cpp')
wi_build_dir = get_option('WICKED_BUILD_DIR')
dep_wicked = compiler.find_library(
    'WickedEngine_Linux',
    dirs: [meson.project_source_root() / wi_build_dir / 'WickedEngine'],
    required: true,
    static: true,
)
dep_jolt = compiler.find_library(
    'Jolt',
    dirs: [meson.project_source_root() / wi_build_dir / 'WickedEngine'],
    required: true,
    static: true,
)
dep_lua = compiler.find_library(
    'LUA',
    dirs: [meson.project_source_root() / wi_build_dir / 'WickedEngine/LUA'],
    required: true,
    static: true,
)
dep_faudio = compiler.find_library(
    'FAudio',
    dirs: [
        meson.project_source_root() / wi_build_dir / 'WickedEngine/Utility/FAudio',
    ],
    required: true,
    static: true,
)
dep_utility = compiler.find_library(
    'Utility',
    dirs: [meson.project_source_root() / wi_build_dir / 'WickedEngine/Utility'],
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
    sources: [
        'src/wi_various.cpp',
        'src/wi_application.cpp',
        'src/wi_graphics.cpp',
        'src/wi_renderer.cpp',
    ],
)

executable(
    'cWickedDemo.exec',
    dependencies: [dep_sdl2, dep_pthread],
    link_with: [lib_cwicked],
    implicit_include_directories: true,
    link_language: 'c',
    sources: ['src/demos/main.c'],
)
