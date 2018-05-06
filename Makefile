CC = g++
DEPS =
LDFLAGS = -framework GLUT -framework OpenGL -Wno-deprecated

all: brickbreak

brickbreak: main.cpp
	$(CC) $(LDFLAGS) main.cpp -o brickbreak

clean:
	rm brickbreak

run: brickbreak
	./brickbreak