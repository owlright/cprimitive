#include <glad/glad.h> // Include the glad header file
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "util.h"
#include "tlog.h"

typedef struct context {
    GLFWwindow* window;
} GlobalContext;

static GlobalContext g_context;
static GlobalContext* g = &g_context;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void create_window();
int check_glfw();


int main(int argc, char** argv)
{
    tlog_init("example.log", 1024 * 1024, 8, 0, TLOG_SCREEN_COLOR);
    tlog_setlevel(TLOG_DEBUG);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // 创建一个隐藏的窗口，用于 OpenGL 上下文的创建
    // glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    create_window();
    if (check_glfw() == -1) {
        return -1;
    }
    GLuint shaderProgram = load_program("../../shaders/vertex.glsl", "../../shaders/fragment.glsl");

    /* -------------------------------------------------------------------------- */
    /*     set up vertex data (and buffer(s)) and configure vertex attributes     */
    /* -------------------------------------------------------------------------- */
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
        0.0f, 0.5f, 0.0f // top
    };

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 创建 FBO 和渲染缓冲对象
    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(
        GL_RENDERBUFFER, GL_RGB, 800, 600); // Assuming the framebuffer is 800x600 and the color format is RGB
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("ERROR: Framebuffer is not complete!\n");

    glClearColor(0, 0, 0, 1);
    ;
    glClear(GL_COLOR_BUFFER_BIT);
    // draw our first triangle
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll
                            // do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);

    GLubyte* pixels = (GLubyte*)malloc(800 * 600 * 3 * sizeof(GLubyte));
    glReadPixels(0, 0, 800, 600, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    GLsizei nrChannels = 3;
    GLsizei stride = nrChannels * 800;
    stride += (stride % 4) ? (4 - stride % 4) : 0;
    // stbi_flip_vertically_on_write(1);
    // stbi_write_png("output2.png", 800, 600, 3, pixels, stride);
    tlog_exit();
    glfwTerminate();
    return 0;
}

void create_window()
{
    int window_width = WINDOW_WIDTH;
    int window_height = WINDOW_HEIGHT;
    GLFWmonitor* monitor = NULL;
    if (FULLSCREEN) {
        int mode_count;
        monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* modes = glfwGetVideoModes(monitor, &mode_count);
        window_width = modes[mode_count - 1].width;
        window_height = modes[mode_count - 1].height;
    }
    g->window = glfwCreateWindow(window_width, window_height, "primitive", monitor, NULL);
}

int check_glfw()
{
    if (g->window == NULL) {
        tlog_error("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(g->window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        tlog_error("Failed to initialize GLAD");
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(g->window, framebuffer_size_callback);
    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    tlog_debug("Max Number of vetex attribs: %d", nrAttributes);
    return 0;
}
