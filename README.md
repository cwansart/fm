# FileManager (fm)

FileManager (fm) is a simple command-line tool written in C++ with GTK3 for listing files in a directory. This is a hobby project aimed at learning new things. Currently, `fm` can list files within a specified directory. If no directory is specified, it defaults to the current directory. Note that passing files as parameters is not supported and will result in an error.

## Features

- List files in a specified directory
- Default to current directory if no parameter is provided

## Preparation

To compile the project some preparations are required on Windows:

Install MSYS2 x64, start MSYS2 UCRT64 console, run:

```bash
pacman -S mingw-w64-ucrt-x86_64-meson \
          mingw-w64-ucrt-x86_64-python \
          mingw-w64-ucrt-x86_64-gtk3 \
          mingw-w64-ucrt-x86_64-toolchain \
          base-devel
```

## Compile and run

Open the MSYS2 UCRT64 terminal, change into the fm folder and run:

```bash
/ucrt64/bin/meson setup build
/ucrt64/bin/meson compile -vC build
```

## Links

Links that I used for installation and development:

- https://www.gtk.org/docs/installations/windows/
- https://docs.gtk.org/gtk3/getting_started.html#building-user-interfaces
- https://docs.gtk.org/gtk3/treeview-tutorial.html