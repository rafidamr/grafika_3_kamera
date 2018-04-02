CC = g++

main:
	$(CC) shader.cpp main.cpp controls.cpp -I. -framework OpenGL -lglfw -lglew

clean:
	rm -f *.o
