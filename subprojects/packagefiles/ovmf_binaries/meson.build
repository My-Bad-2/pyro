project('ovmf_binaries')

this_dir = meson.current_source_dir()
AA64 = this_dir / 'bin/RELEASEAARCH64_QEMU_EFI.fd'
ARM = this_dir / 'bin/RELEASEARM_QEMU_EFI.fd'
X64 = this_dir / 'bin/RELEASEX64_OVMF.fd'
IA32 = this_dir / 'bin/RELEASEIa32_OVMF.fd'

ovmf_binaries_dep = declare_dependency()

if meson.version().version_compare('>=0.54.0')
    meson.override_dependency('ovmf_binaries', ovmf_binaries_dep)
endif