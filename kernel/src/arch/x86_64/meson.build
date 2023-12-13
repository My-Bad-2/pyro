sources += files(
    'x86.cpp'
)

subdir('cpu')
subdir('dev')

args += [
    '-march=x86-64',
    '-msoft-float',
    '-mno-mmx',
    '-mno-sse',
    '-mno-sse2',
    '-mno-red-zone',
    '-mcmodel=kernel',
]

ld_args += ['-Wl,-z,noexecstack']