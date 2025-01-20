project(
    'cWicked',
    ['cpp', 'c'],
    version: '0.71.657',
    default_options: ['cpp_std=c++20', 'c_std=c23', 'cpp_rtti=false'],
)

add_global_arguments(
    '-gsplit-dwarf',
    '-fms-extensions',
    '-msse2',
    '-mfpmath=sse',
    '-DSDL2',
    '-DWI_UNORDERED_MAP_TYPE=2',
    '-march=native',
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

lib_wiso = shared_library(
    'wiso',
    dependencies: [
        dep_pthread,
        dep_sdl2,
        dep_lua,
        dep_jolt,
        dep_faudio,
        dep_utility,
        dep_wicked,
    ],
    cpp_pch: 'pch/wi_full_pch.h',
    sources: [
        'src/wiso/wiso.cpp',
    ],
)

executable(
    'wi01_loadlua.exec',
    dependencies: [dep_sdl2, dep_pthread],
    link_with: [lib_wiso],
    link_language: 'cpp',
    cpp_pch: 'pch/wi_min_pch.h',
    sources: ['src/wi01_loadlua/main.cpp'],
)
executable(
    'wi02_tests.exec',
    dependencies: [dep_sdl2, dep_pthread],
    link_with: [lib_wiso],
    link_language: 'cpp',
    cpp_pch: 'pch/wi_min_pch.h',
    sources: ['src/wi02_tests/main.cpp'],
)
executable(
    'wi03_animteapot.exec',
    dependencies: [dep_sdl2, dep_pthread],
    link_with: [lib_wiso],
    link_language: 'cpp',
    cpp_pch: 'pch/wi_min_pch.h',
    sources: ['src/wi03_animteapot/main.cpp'],
)
executable(
    'wi04_charactercontroller.exec',
    dependencies: [dep_sdl2, dep_pthread],
    link_with: [lib_wiso],
    link_language: 'cpp',
    cpp_pch: 'pch/wi_min_pch.h',
    sources: [
        'src/wi04_charactercontroller/main.cpp',
        'src/wi04_charactercontroller/game.cpp',
        'src/wi04_charactercontroller/character.cpp',
    ],
)
