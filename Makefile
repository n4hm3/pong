# compiler
CC = clang
# Go look in this dir to find header files when including things
# for example raylib which was installed via homebrew - as a reminder headerfiles tell us how to verify the code is using functions correctly
# /opt is short for "optional" to store 3rd party packages
CFLAGS = -I/opt/homebrew/include
# LDFLAGS says go look in this dir for the following compiled libraries (LD - linked meaning link the compiled files to the compiled binaries)
LDFLAGS = -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

main: main.c
	$(CC) main.c -o main $(CFLAGS) $(LDFLAGS)

run: main
	./main

clean:
	rm -f main
