main.o: main.cpp
	g++ main.cpp -o main.o -c

main: main.o
	g++ main.o -o main

run: main
	./main

clean:
	rm ./main.o
	rm ./main