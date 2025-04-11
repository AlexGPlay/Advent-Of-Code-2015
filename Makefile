compile-problem-01: ./01/01.cpp
	g++ -std=c++17 -Wall -Wextra ./01/01.cpp ./utils/readFile.cpp -o ./01/01.exe

run-problem-01: compile-problem-01
	./01/01.exe