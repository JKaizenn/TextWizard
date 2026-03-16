#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaders/shader.h"

#include <iostream>

/***********************
 * PROGRAM SPECIFICATION AND DESCRIPTION:
 * A user can create, edit, save, and open text files using the text editor, 
 * a straightforward program. In addition to a user interface for the user to interact with, 
 * it uses classes and objects to store and alter the content. 
 * Basic text editing functions including 
 * copying, pasting, deleting, searching, and printing text are all available in the text editor. 
 * Text Editor is a simple application that is built into C++ programming language. 
 * We can use Graphical User Interface (GUI) Libraries such as QT, and GTK+ for creating a graphical user interface. 
 * Libraries such as Pango or Cairo are required to display text on the screen.
 * 
 * C++ 23, CMAKE, OPENGL, GLFW
*************************/

int main() 
{
    // Initialize GLFW
    if (!glfwInit())
    {
        // Handle Initialization failure
    }

    // Set window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create window and context
    GLFWwindow* window = glfwCreateWindow(640, 480, "TextWizard", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


    float triangle1[] = 
    {
        // Triangle 1

        // POSITIONS           // COLORS
        -0.25f, -0.25f, 0.0f,  1.0f, 0.0f, 0.0f, // Bottom right
        0.0f, 0.25f, 0.0f,     0.0f, 1.0f, 0.0f, // Bottom Left
        0.25f, -0.25f, 0.0f,   0.0f, 0.0f, 1.0f, // Top
    };

    float triangle2[] =
    {
        // Triangle 2
        0.25f, -0.25f, 0.0f,  1.0f, 0.0f, 0.0f, // Bottom right
        0.50f, 0.25f, 0.0f,   0.0f, 1.0f, 0.0f, // Bottom Left// Top
        0.75f, -0.25f, 0.0f,   0.0f, 0.0f, 1.0f, // Top// Bottom Right
    };

    float triangle3[] = 
    {
        // Triangle 3
        0.0f, 0.25f, 0.0f,    1.0f, 0.0f, 0.0f,// Bottom Left
        0.25f, 0.75f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.50f, 0.25f, 0.0f,   0.0f, 0.0f, 1.0f, // Top// Bottom Right
    };

    // -------------------------------------------------------
    // SHADERS

    Shader shader("shaders/vertex/vertex.glsl", "shaders/fragment/fragment.glsl");


    // -------------------------------------------------------
    // VAO -> VBO -> Vertex Attributes

    unsigned int VAO1, VBO1, VAO2, VBO2, VAO3, VBO3;

    // VAO1 Setup
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);
    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    // 2. Generate, bind, and fill VBO
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    glGenVertexArrays(1, &VAO3);
    glBindVertexArray(VAO3);
    glGenBuffers(1, &VBO3);
    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle3), triangle3, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    // -------------------------------------------------------

    // Render loop

    // Check our max allowed vertex attributes
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;


    while (!glfwWindowShouldClose(window))
    {
        // Clear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Activate shader
        shader.use();

        shader.setFloat("offset",0.5f);

        // Draw
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(VAO3);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // Cleanup 
    glfwDestroyWindow(window);
    glfwTerminate();

}