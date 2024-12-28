CFLAGS=$(pkg-config --cflags gtk+-3.0)
LIBS=$(pkg-config --libs gtk+-3.0) -mwindows
g++ $CFLAGS -o fm main.cpp $LIBS