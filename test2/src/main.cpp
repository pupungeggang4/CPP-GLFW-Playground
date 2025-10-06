#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

int main(int argc, char *argv[]) {
    glfwInit();
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GL_TRUE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Test", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("font/neodgm.ttf", 32);
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surfaceUI = SDL_CreateRGBSurface(0, 800, 600, 32, 0, 0, 0, 0);
    SDL_Surface* surfaceText = TTF_RenderText_Blended(font, "Hello GLFW Mesh and SDL Text!", color);
    SDL_Rect rect = {10, 10, surfaceText->w, surfaceText->h};
    SDL_BlitSurface(surfaceText, NULL, surfaceUI, &rect);
    
    glEnable(GL_TEXTURE_2D);
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_COLOR);
        glDisable(GL_TEXTURE_2D);
        glBegin(GL_TRIANGLES);
        glColor4f(1.0, 0.0, 0.0, 1.0);
        glVertex2f(0.0, 0.0);
        glColor4f(0.0, 1.0, 0.0, 1.0);
        glVertex2f(1.0, 0.0);
        glColor4f(0.0, 0.0, 1.0, 1.0);
        glVertex2f(1.0, 1.0);
        glEnd();

        glDisable(GL_COLOR);
        glEnable(GL_TEXTURE_2D);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surfaceUI->w, surfaceUI->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surfaceUI->pixels);
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);
        glVertex2f(-1.0, -1.0);
        glTexCoord2f(1.0, 1.0);
        glVertex2f(1.0, -1.0);
        glTexCoord2f(1.0, 0.0);
        glVertex2f(1.0, 1.0);
        glTexCoord2f(0.0, 0.0);
        glVertex2f(-1.0, 1.0);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}