project(
    'printf',
    'c',
    license: 'MIT'
)

args = [
    '-DPRINTF_SUPPORT_DECIMAL_SPECIFIERS=0',
    '-DPRINTF_SUPPORT_EXPONENTIAL_SPECIFIERS=0'
]

printf_dep = declare_dependency(compile_args: args, include_directories : include_directories('src'), sources: ['src/printf/printf.c'])

if meson.version().version_compare('>=0.54.0')
    meson.override_dependency('printf', printf_dep)
endif