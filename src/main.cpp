#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    // Vertices and indices
    float vertices[] = {
        0.5f,  0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f    // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };

    // -------------------------------------------------------
    // SHADERS

    const char *vertexShaderSource = "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

    int success;
    char infoLog[512];

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // -------------------------------------------------------
    // VAO -> VBO -> EBO -> Vertex Attributes

    unsigned int VAO, VBO, EBO;

    // 1. Generate and bind VAO first
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // 2. Generate, bind, and fill VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 3. Generate, bind, and fill EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 4. Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind VAO
    glBindVertexArray(0);

    // -------------------------------------------------------
    // Render loop

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.53f, 0.812f, 0.941f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
}