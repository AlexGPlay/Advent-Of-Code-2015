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
08: run-08;
09: run-09;
10: run-10;
11: run-11;
12: run-12;
13: run-13;
14: run-14;
15: run-15;
16: run-16;
17: run-17;
18: run-18;
19: run-19;
20: run-20;
21: run-21;
22: run-22;
23: run-23;
24: run-24;
25: run-25;