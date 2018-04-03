CC = g++

main:
	$(CC) shader.cpp main.cpp controls.cpp -o rahman -I. -framework OpenGL -lglfw -lglew

clean:
	rm -f *.o
