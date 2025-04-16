CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
UTILS = utils/readFile.cpp utils/split.cpp

build-%:
	$(CXX) $(CXXFLAGS) ./$*/$*.cpp $(UTILS) -o ./$*/$*.exe

run-%: build-%
	./$*/$*.exe

01: run-01
02: run-02
03: run-03
04: run-04
05: run-05;
06: run-06;
07: run-07;