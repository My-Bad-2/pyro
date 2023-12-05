project('pyro', ['c', 'cpp'],
  version : '0.1',
  license: 'MIT',
  meson_version: '>=1.2.0',
  default_options : [
    'c_std=gnu2x',
    'cpp_std=gnu++26',
    'warning_level=3'
  ]
)

c = meson.get_compiler('c')
cxx = meson.get_compiler('cpp')
ld = cxx.get_linker_id()
arch = host_machine.cpu_family()

logfile = meson.global_source_root() / 'log.txt'

iso_dir = '/tmp/tmp_iso_dir'
iso_files = [
    meson.global_source_root() / 'meta/limine.cfg'
]

qemu_args = [
    '-cpu', 'max', '-smp', '1', '-m', '512M',
    '-rtc', 'base=localtime', '-serial', 'stdio',
    '-boot', 'order=d,menu=on,splash-time=100',
]

# { arch : [ ovmf_name, bios, xorriso_args, qemu_args ] }
supported_archs = {
    'x86_64' : [
        'X64', true,
        [
            '-b', 'limine-bios-cd.bin',
            '-no-emul-boot', '-boot-load-size', '4', '-boot-info-table',
            '--efi-boot', 'limine-uefi-cd.bin',
            '-efi-boot-part', '--efi-boot-image', '--protective-msdos-label'
        ],
        [
            '-M', 'q35', '-audiodev', 'id=audio,driver=alsa',
            '-machine', 'pcspk-audiodev=audio',
        ]
    ],
}

if not supported_archs.has_key(arch)
    error('Unknown architecture ' + arch)
endif

ovmf_id = supported_archs[arch][0]
supports_bios = supported_archs[arch][1]
xorriso_args = supported_archs[arch][2]
qemu_args += supported_archs[arch][3]
qemu = 'qemu-system-' + arch

qemu_dbg_args = [
  '-no-reboot', '-no-shutdown',
  '-d', 'int', '-D', logfile,
]

if arch == 'x86_64'
    qemu_dbg_args += ['-M', 'smm=off']
endif

incs = [
  include_directories('kernel/include'),
  include_directories('kernel/include/libc')
]

add_global_arguments(
  '-ffreestanding',
  '-fno-stack-protector',
  '-fno-omit-frame-pointer',
  '-fno-pic',
  '-fno-pie',
  '-Ofast',
  language: ['c', 'cpp']
)

if get_option('build_docs')
  doxygen = find_program('doxygen', required: false)

  if doxygen.found()
    custom_target('build-docs', 
      input: meson.current_source_dir() / 'Doxyfile',
      output: 'docs',
      command: [ doxygen, meson.current_source_dir() / 'Doxyfile']
    )
  endif
endif

add_global_arguments(
  '-fno-rtti',
  '-fno-exceptions',
  '-fsized-deallocation',
  language: 'cpp'
)

limine = subproject('limine', default_options : 'arch=' + arch)

deps = [
  dependency('limine')
]

deps_inc = []

foreach dep : deps
  deps_inc += dep.partial_dependency(includes: true)
endforeach

kernel_elf = []
subdir('kernel')

iso_files += limine.get_variable('limine_binaries')
iso = custom_target('iso', 
  input: kernel_elf,
  output: 'image.iso',
  command: ['rm', '-rf', iso_dir, '&&',
            'mkdir', '-p', iso_dir, '&&',
            'cp', '@INPUT@', iso_dir / 'kernel.elf', '&&',
            'cp', iso_files, iso_dir, '&&',
            'xorriso', '-as', 'mkisofs', xorriso_args, iso_dir, '-o', '@OUTPUT@', '&&',
            limine.get_variable('limine_exec'), 'bios-install', '@OUTPUT@', '&&',
            'rm', '-rf', iso_dir
      ],
  build_by_default: true,
  console: true,
  install: false,
  depends: kernel_elf
)

custom_target('run_bios',
    input : iso,
    output : 'run_bios',
    command : [qemu, qemu_args, '-cdrom', '@INPUT@'],
    build_by_default : false,
    console : true,
    install : false,
    depends : iso
)

ovmf_binaries = subproject('ovmf_binaries')
ovmf = ovmf_binaries.get_variable(ovmf_id)

custom_target('run_uefi',
    input : iso,
    output : 'run_uefi',
    command : [qemu, qemu_args, '-cdrom', '@INPUT@', '-bios', ovmf],
    build_by_default : true,
    console : true,
    install : false,
    depends : iso
)