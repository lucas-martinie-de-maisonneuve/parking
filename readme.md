<!-- Commande pour compiler -->
g++ -I src/include -L src/lib -o main.exe main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image

<!-- 2nd Commande pour compiler -->

g++ -I src/include -L src/lib -o main.exe src/main.cpp src/Game.cpp src/Window.cpp -lmingw32 -lSDL2main
 -lSDL2 -lSDL2_ttf -lSDL2_image
