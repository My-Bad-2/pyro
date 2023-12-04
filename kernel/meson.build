sources = files()

ld_args = [
  '-Wl,-T,' + meson.current_source_dir() / 'arch' / arch / 'linker.ld',
  '-Wl,-z,max-page-size=0x1000',
  '-nostdlib',
  '-static'
]

args = []
subdir('src')

kernel_elf = executable(
  'kernel.elf', 
  include_directories: incs,
  sources: sources,
  dependencies: [deps],
  c_args: [args],
  cpp_args : [args],
  link_args: ld_args,
  install: false
)