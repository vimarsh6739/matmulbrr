CXX=g++
CXXFLAGS=-O3 -Wall -g
LDFLAGS= -lm

.PHONY: all
all: matmul

matmul: matmul.o main.o
	$(CXX) $^ -o $@ $(LDFLAGS)

matmul.o: matmul.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@ 

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@ 

.PHONY: clean
clean:
	rm -f main.o matmul.o matmul
