CC = g++

main:
	$(CC) shader.cpp mainaya.cpp controls.cpp -o main -I. -framework OpenGL -lglfw -lglew

clean:
	rm -f *.o
