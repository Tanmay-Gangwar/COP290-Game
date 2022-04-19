Libraries required to compile and run the game: `SDL.h`, `SDL_image.h` and `SDL_ttf.h`

Procedure to install SDL libraries:
Open terminal and type the following commands
```
sudo apt-get update
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
sudo libsdl2-ttf-dev
```

Download and extract zip file
Open `client.hpp` in any text editor of your choice and change `SERVER_IP` to the IP address of the server

run the following commands for compiling and running server
```
make
./server.out
```

run the following commands for compiling and running client and game
```
make
./main.out
```

https://lazyfoo.net/tutorials/SDL/index.php helped in learning SDL and game development
Among us sprites are taken from https://www.artstation.com/artwork/eJJLQX
Trees and other building images are taken from google image search
