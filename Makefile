CC = g++
DEPS =
LDFLAGS = -framework GLUT -framework OpenGL -Wno-deprecated

all: breakout

brickbreak: main.cpp
	$(CC) $(LDFLAGS) main.cpp -o breakout

clean:
	rm breakout

run: brickbreak
	./breakout