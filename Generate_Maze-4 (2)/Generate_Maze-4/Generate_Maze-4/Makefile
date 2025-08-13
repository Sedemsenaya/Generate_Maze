output: main.o UnionFind.o
	g++ main.o UnionFind.o -o output

main.o: main.cpp
	g++ -c main.cpp

UnionFind.o: UnionFind.cpp UnionFind.h
	g++ -c UnionFind.cpp

clean:
	rm *.o output