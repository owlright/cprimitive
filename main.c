#include <glad/glad.h> // Include the glad header file
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "util.h"
#define LOG_COLOR (-1)
#include "log.h"
#include "stb_image.h"
#include "stb_image_write.h"

typedef struct _GlobalContext {
    GLFWwindow* window;
} GlobalContext;

static GlobalContext g_context;
static GlobalContext* g = &g_context;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void create_window(int hidden);
int check_glfw();

int main(int argc, char** argv)
{
    create_window(1);
    if (check_glfw() == -1) {
        exit(EXIT_FAILURE);
    }
    GLuint shaderProgram = load_program("../../shaders/vertex.glsl", "../../shaders/fragment.glsl");
    GLint color_location = glGetUniformLocation(shaderProgram, "ourColor");
    if (color_location == -1) {
        log_error("Could not find uniform variable 'ourColor'");
        exit(EXIT_FAILURE);
    }
    glUseProgram(shaderProgram);
    glUniform3f(color_location, 1.0f, 0.0f, 0.0f);
    /* -------------------------------------------------------------------------- */
    /*     set up vertex data (and buffer(s)) and configure vertex attributes     */
    /* -------------------------------------------------------------------------- */
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
        0.0f, 0.5f, 0.0f // top
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glClearColor(0, 0, 0, 1);
    // draw our first triangle
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glFinish();
    GLubyte* pixels = (GLubyte*)calloc(4, WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(GLubyte));
    glReadPixels(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    GLsizei nrChannels = 4;
    GLsizei stride = nrChannels * WINDOW_WIDTH;
    stride += (stride % 4) ? (4 - stride % 4) : 0;
    stbi_flip_vertically_on_write(1);
    stbi_write_png("output3.png", WINDOW_WIDTH, WINDOW_HEIGHT, 4, pixels, stride);
    glfwDestroyWindow(g->window);
    int totalPixels = WINDOW_WIDTH * WINDOW_HEIGHT * 4; // 4 for RGBA channels
    // for (int i = 0; i < totalPixels; i += 4) {
    //     if (pixels[i + 3] != 0)
    //     printf("Pixel at index %d: R=%d, G=%d, B=%d, A=%d\n", i / 4, pixels[i], pixels[i + 1], pixels[i + 2], pixels[i + 3]);
    // }
    free(pixels);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void create_window(int hidden)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    if (hidden > 0) {
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    }

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
        log_error("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(g->window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        log_error("Failed to initialize GLAD");
        return -1;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(g->window, framebuffer_size_callback);
    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    log_info("Max Number of vetex attribs: %d", nrAttributes);
    return 0;
}
