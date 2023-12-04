project('limine', 'c', license : 'BSD-2-Clause')

arch = get_option('arch')

this_dir = meson.current_source_dir()

limine_binaries = [
    this_dir / 'limine-uefi-cd.bin',
]

if arch == 'x86_64'
    limine_binaries += [
        this_dir / 'limine-bios.sys',
        this_dir / 'limine-bios-cd.bin',
        this_dir / 'BOOTX64.EFI',
        this_dir / 'BOOTIA32.EFI'
    ]
elif arch == 'aarch64'
    limine_binaries += [
        this_dir / 'BOOTAA64.EFI'
    ]
elif arch == 'riscv64'
    limine_binaries += [
        this_dir / 'BOOTRISCV64.EFI'
    ]
endif

run_command(meson.get_compiler('c').get_id(), this_dir / 'limine.c', '-Wall', '-Wextra', '-std=c99', '-O2', '-o', this_dir / 'limine', check : true)
limine_exec = this_dir / 'limine'

limine_dep = declare_dependency(include_directories : include_directories('.'))

if meson.version().version_compare('>=0.54.0')
    meson.override_dependency('limine', limine_dep)
endif