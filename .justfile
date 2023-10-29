set shell :=["cmd.exe", "/c"]

build:
	g++ decrypt.cpp -std=c++17

run:
	a testfiles/player.gdc output.txt
