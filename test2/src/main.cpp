#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

int main(int argc, char *argv[]) {
    glfwInit();
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GL_TRUE);
    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "Test", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("font/neodgm.ttf", 32);
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surfaceText = TTF_RenderText_Blended(font, "Hello GLFW Mesh and SDL Text", 0, color);
    //SDL_Surface* surfaceText = SDL_ConvertSurface(TTF_RenderText_Blended(font, "Hello GLFW Mesh and SDL Text", 0, color), SDL_PIXELFORMAT_ARGB8888);
    
    glEnable(GL_TEXTURE_2D);
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    std::cout << std::hex << surfaceText->format << std::endl;
    Uint8 r, g, b, a;
    SDL_ReadSurfacePixel(surfaceText, 100, 10, &r, &g, &b, &a);
    std::cout << std::dec << int(r) << int(g) << int(b) << int(a) << std::endl;

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
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surfaceText->w, surfaceText->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surfaceText->pixels);
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);
        glVertex2f(-0.9, 0.8);
        glTexCoord2f(1.0, 1.0);
        glVertex2f(-0.2, 0.8);
        glTexCoord2f(1.0, 0.0);
        glVertex2f(-0.2, 0.9);
        glTexCoord2f(0.0, 0.0);
        glVertex2f(-0.9, 0.9);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}