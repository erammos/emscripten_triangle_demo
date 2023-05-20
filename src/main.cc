// Copyright 2023 Elias Rammos
#include <SDL2/SDL.h>
#include <glad/glad.h>

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

struct RenderData {
  Shader *shader;
  unsigned int VBO;
  unsigned int VAO;
};
void main_loop(void *data) {
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
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  RenderData *d = (RenderData *)data;
  d->shader->use();
  glBindVertexArrayOES(d->VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  SDL_GL_SwapWindow(window);
}

int main(int argc, char **argv) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Couldn't initialize SDL " << SDL_GetError();
    exit(1);
  }
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
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

  gladLoadGLES2Loader(SDL_GL_GetProcAddress);
  std::cout << glGetString(GL_VENDOR) << "\n";
  std::cout << glGetString(GL_RENDERER) << "\n";
  std::cout << glGetString(GL_VERSION) << "\n";
  Shader *shader = nullptr;
  unsigned int VBO, VAO;
  shader = new Shader();
  glGenVertexArraysOES(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArrayOES(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  float vertices[] = {
      // positions         // colors
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left
      0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f   // top
  };
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  void *data = (void *)(new RenderData{shader, VBO, VAO});
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop_arg(main_loop, data, 0, true);
#else
  while (true) main_loop(data);
#endif
  SDL_DestroyWindow(window);
  SDL_Quit();
}
