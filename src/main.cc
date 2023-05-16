// Copyright 2023 Elias Rammos
#include <SDL2/SDL.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <iostream>

#include "fluffy/shader.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;

void loop() {
  if (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        std::cout << "wtf\n";
        exit(0);
        break;
      default:
        break;
    }
    SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }
}

int main(int argc, char **argv) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Couldn't initialize SDL " << SDL_GetError();
    exit(1);
  }
  window =
      SDL_CreateWindow("Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  if (!window) {
    std::cout << "Failed to open window" << SDL_GetError();
    exit(1);
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (!renderer) {
    std::cout << "Failed to create renderer " << SDL_GetError();
    exit(1);
  }
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(loop , 0, true);
#else
while(true)
    loop();
#endif
}
