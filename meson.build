project('fm',
    'cpp',
    default_options : ['cpp_std=c++17']
)

gtkdep = dependency('gtk+-3.0')

executable('fm',
    'main.cpp',
    win_subsystem: 'windows',
    dependencies : gtkdep
)