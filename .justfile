build:
	g++ decrypt.cpp -std=c++17 -o grimparse

run:
	./grimparse testfiles/player.gdc output.txt
