// Copyright 2023 Elias Rammos
#include <SDL2/SDL.h>

#include "glad/glad.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <iostream>

#include "fluffy/shader.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

SDL_Window *window = nullptr;
SDL_Event event;
SDL_GLContext glContext = nullptr;

void loop() {
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        std::cout << "wtf\n";
        exit(0);
        break;
      default:
        break;
    }
  }
}

int main(int argc, char **argv) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Couldn't initialize SDL " << SDL_GetError();
    exit(1);
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                      SDL_GL_CONTEXT_PROFILE_CORE | SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  window =
      SDL_CreateWindow("Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
  if (!window) {
    std::cout << "Failed to open window" << SDL_GetError();
    exit(1);
  }

  glContext = SDL_GL_CreateContext(window);
  if (glContext == nullptr) {
    std::cout << "Opengl Context error " << SDL_GetError();
    exit(0);
  }

  gladLoadGLLoader(SDL_GL_GetProcAddress);
  std::cout << glGetString(GL_VENDOR) << "\n";
  std::cout << glGetString(GL_RENDERER) << "\n";
  std::cout << glGetString(GL_VERSION) << "\n";
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(loop, 0, true);
#else
  while (true) loop();
#endif
  SDL_DestroyWindow(window);
  SDL_Quit();
}
