CC = g++

main:
	$(CC) shader.cpp mainaya.cpp controls.cpp -I. -framework OpenGL -lglfw -lglew

clean:
	rm -f *.o
