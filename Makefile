executavel: main.cpp algorithms.cpp render.cpp
	g++ $^ -o $@ -lraylib

clean:
	rm -f executavel *.o
