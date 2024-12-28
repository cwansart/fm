# FileManager (fm)

FileManager (fm) is a simple command-line tool written in C++ with GTK3 for listing files in a directory. This is a hobby project aimed at learning new things. Currently, `fm` can list files within a specified directory. If no directory is specified, it defaults to the current directory. Note that passing files as parameters is not supported and will result in an error.

## Features

- List files in a specified directory
- Default to current directory if no parameter is provided

## Preparation

To compile the project, some preparations are required on Windows:

1. Install MSYS2 x64.
1. Start the MSYS2 UCRT64 console.
1. Run the following command:

```bash
pacman -S mingw-w64-ucrt-x86_64-meson \
          mingw-w64-ucrt-x86_64-python \
          mingw-w64-ucrt-x86_64-gtk3 \
		  mingw-w64-ucrt-x86_64-glade \
          mingw-w64-ucrt-x86_64-toolchain \
          base-devel
```

## Compile and run

1. Open the MSYS2 UCRT64 terminal.
1. Change into the `fm` folder.
1. Run the following commands:

```bash
meson setup build
meson compile -vC build
```

## Compile release build

1. Open the MSYS2 UCRT64 terminal.
1. Change into the `fm` folder.
1. Run the following commands:

```bash
meson setup build --buildtype=release
meson compile -C build
```

The exe file needs some dlls that can be found in `C:\msys64\ucrt64\bin`:

- `libatk-1.0-0.dll`
- `libbrotlicommon.dll`
- `libbrotlidec.dll`
- `libcairo-2.dll`
- `libcairo-gobject-2.dll`
- `libdatrie-1.dll`
- `libdeflate.dll`
- `libepoxy-0.dll`
- `libfontconfig-1.dll`
- `libfreetype-6.dll`
- `libfribidi-0.dll`
- `libgdk_pixbuf-2.0-0.dll`
- `libgdk-3-0.dll`
- `libgio-2.0-0.dll`
- `libglib-2.0-0.dll`
- `libgmodule-2.0-0.dll`
- `libgobject-2.0-0.dll`
- `libgraphite2.dll`
- `libgtk-3-0.dll`
- `libharfbuzz-0.dll`
- `libjbig-0.dll`
- `libjpeg-8.dll`
- `libLerc.dll`
- `libpango-1.0-0.dll`
- `libpangocairo-1.0-0.dll`
- `libpangoft2-1.0-0.dll`
- `libpangowin32-1.0-0.dll`
- `libpcre2-8-0.dll`
- `libpixman-1-0.dll`
- `libpng16-16.dll`
- `libsharpyuv-0.dll`
- `libstdc++-6.dll`
- `libthai-0.dll`
- `libtiff-6.dll`
- `libwebp-7.dll`

Copy them along with the exe file.

## Links

Resources used for installation and development:

- https://www.gtk.org/docs/installations/windows/
- https://docs.gtk.org/gtk3/getting_started.html#building-user-interfaces
- https://docs.gtk.org/gtk3/treeview-tutorial.html
- https://mesonbuild.com/Tutorial.html
- https://mesonbuild.com/Builtin-options.html
- https://github.com/GNOME/gimp/blob/master/meson.build
- https://github.com/msys2/setup-msys2
