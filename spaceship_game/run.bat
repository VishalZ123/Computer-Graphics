g++ ./src/main.cpp ./src/background.cpp ./src/spaceship.cpp ./src/controls.cpp ./src/asteroids.cpp ./src/spacestation.cpp ./src/minimap.cpp ./src/game.cpp ./src/utils.cpp -o ./bin/main.exe -LD:/freeglut/lib -lfreeglut -lopengl32 -lglu32 -lwinmm -lgdi32
start ./bin/main.exe
