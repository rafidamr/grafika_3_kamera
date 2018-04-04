CC = g++

main:
	$(CC) shader.cpp main.cpp controls.cpp -o main -I. -framework OpenGL -lglfw -lglew

clean:
	rm -f *.o
