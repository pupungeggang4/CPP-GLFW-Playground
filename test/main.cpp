#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "ft2build.h"
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#include <FreeImage.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow *window;
int success; GLchar *infoLog;
GLuint program, vShader, fShader, vao, bHUD, texture;
GLint laPosition, laTexcoord;
std::vector<float> bHUDData = {
    0.5, -0.5, 1.0, 1.0, 0.5, 0.5, 1.0, 0.0, -0.5, -0.5, 0.0, 1.0,
    -0.5, -0.5, 0.0, 1.0, 0.5, 0.5, 1.0, 0.0, -0.5, 0.5, 0.0, 0.0
};
FIBITMAP *bitmap, *pimage;

void initGlfw();
void initGL();

int main(int argc, char *argv[]) {
    bitmap = FreeImage_Load(FIF_PNG, "image/a.png", PNG_DEFAULT);
    pimage = FreeImage_ConvertTo32Bits(bitmap);
    FreeImage_FlipVertical(pimage);
    void *imageptr = (void*)FreeImage_GetBits(pimage);
    int width = FreeImage_GetWidth(pimage);
    int height = FreeImage_GetHeight(pimage);
    initGlfw();
    initGL();

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);

        glBindVertexArray(vao);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, imageptr);
        glBindBuffer(GL_ARRAY_BUFFER, bHUD);
        glVertexAttribPointer(laPosition, 2, GL_FLOAT, false, sizeof(float) * 4, (void*)(0));
        glVertexAttribPointer(laTexcoord, 2, GL_FLOAT, false, sizeof(float) * 4, (void*)(sizeof(float) * 2));
        glEnableVertexAttribArray(laPosition);
        glEnableVertexAttribArray(laTexcoord);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

void initGlfw() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

    window = glfwCreateWindow(800, 800, "Image and Text Test", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
}

void initGL() {
    gladLoadGL();
    std::ifstream f;
    f.open("shader/vertex.vert");
    std::stringstream vSourceSS;
    vSourceSS << f.rdbuf();
    std::string vSourceStr = vSourceSS.str();
    vSourceStr.append(1, 0);
    const GLchar *vSource = vSourceStr.c_str();
    f.close();

    f.open("shader/fragment.frag");
    std::stringstream fSourceSS;
    fSourceSS << f.rdbuf();
    std::string fSourceStr = fSourceSS.str();
    fSourceStr.append(1, 0);
    const GLchar *fSource = fSourceStr.c_str();
    f.close();

    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vSource, NULL);
    glCompileShader(vShader);
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fSource, NULL);
    glCompileShader(fShader);
    program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);

    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vShader, 2048, NULL, infoLog);
        std::cout << "v " << infoLog << std::endl;
    }
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fShader, 2048, NULL, infoLog);
        std::cout << "f " << infoLog << std::endl;
    }

    laPosition = glGetAttribLocation(program, "a_position");
    laTexcoord = glGetAttribLocation(program, "a_texcoord");

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &bHUD);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, bHUD);
    glBufferData(GL_ARRAY_BUFFER, bHUDData.size() * sizeof(float), &bHUDData[0], GL_STATIC_DRAW);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}