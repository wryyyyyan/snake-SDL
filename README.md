# snake-SDL

### Dependencias
    SDL2
    SDL2_ttf
    SDL2_mixer

### Compilação
    gcc -I libs -o snake src/game.c src/audio.c src/fruit.c src/render.c src/snake.c `sdl2-config --cflags --libs` -lSDL2_mixer -lSDL2_ttf
