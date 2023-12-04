project('ovmf_binaries')

this_dir = meson.current_source_dir()
AA64 = this_dir / 'bin/RELEASEOVMF_AA64.fd'
ARM = this_dir / 'bin/RELEASEOVMF_ARM.fd'
X64 = this_dir / 'bin/RELEASEOVMF_X64.fd'
IA32 = this_dir / 'bin/RELEASEOVMF_IA32.fd'

ovmf_binaries_dep = declare_dependency()

if meson.version().version_compare('>=0.54.0')
    meson.override_dependency('ovmf_binaries', ovmf_binaries_dep)
endif