CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wshadow -ansi -pedantic -std=c++11 
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
EXEC = main

all : display

display: project
	display result/result.ppm &

project: exec
	@echo "Executing binary..."
	./bin/main

exec: src/$(EXEC).cpp
	@echo "Compiling the project..."
	$(CXX) $(CXXFLAGS) src/$(EXEC).cpp -o bin/$(EXEC)

clean: 
	rm result/*.ppm
	rm bin/*

preprocessing: $(EXEC).cpp
	$(CXX) -c src/$(EXEC).cpp

sfml: preprocessing-tests
	@echo "Compiling tests sfml..."
	$(CXX) sfml.test.o -o bin/sfml.test $(CXXFLAGS) $(LDFLAGS)
	rm sfml.test.o

preprocessing-tests:
	@echo "Preprocessing tests..."
	$(CXX) -c src/sfml.test.cpp
