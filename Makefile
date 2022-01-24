clear:
	del .\bin\*.o
	del .\bin\*.exe

all: clear
	g++ -c src/Input/*.cpp -std=c++14 -m64 -g -Wall -I include
	g++ -c src/Asset/*.cpp -std=c++14 -m64 -g -Wall -I include
	g++ -c src/Sound/*.cpp -std=c++14 -m64 -g -Wall -I include
	g++ -c src/Animation/*.cpp -std=c++14 -m64 -g -Wall -I include
	g++ -c src/Sprites/*.cpp -std=c++14 -m64 -g -Wall -I include
	g++ -c src/*.cpp -std=c++14 -m64 -g -Wall -I include
	move *.o bin
	g++ bin/*.o -o main -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
	move *.exe bin

run:
	bin/main.exe

build_and_run: all run