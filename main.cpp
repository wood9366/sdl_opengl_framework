#include <iostream>

#include <SDL.h>
#include <SDL_syswm.h>
#include <glad/glad.h>

using namespace std;

int main(int argc, char *argv[])
{
    int ret = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    if (ret != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl init fail, %s", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window* window = SDL_CreateWindow("sdl_opengl_framework",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_OPENGL);

    if (window == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl create window fail, %s", SDL_GetError());
        return 1;
    }

    SDL_SysWMinfo info;
    SDL_GetVersion(&info.version);
    if (SDL_GetWindowWMInfo(window, &info) == SDL_TRUE)
    {
        SDL_Log("sdl window system %d", info.subsystem);
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);

    if (context == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl create gl context fail, %s", SDL_GetError());
        return 1;
    }

    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
    int glad_version = gladLoadGL();
    SDL_Log("gl version %d.%d", GLVersion.major, GLVersion.minor);

    bool is_running = true;

    while (is_running)
    {
        SDL_Event evt;

        while (SDL_PollEvent(&evt))
        {
            if (evt.type == SDL_QUIT)
            {
                SDL_Log("quit, time %d", evt.quit.timestamp);
                is_running = false;
            }
        }

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
        SDL_Delay(1);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
