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
 * 
 * C++ 23, CMAKE, OPENGL, GLFW
*************************/




int main() 
{
    // Initialize GLFW with glfwInit()
    if (!glfwInit())
    {
        // Handle Initialization failure
    }

    // Set window hints (OpenGL version 4.1, Core profile)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create a GLFWwindow* with glfwCreateWindow()
    GLFWwindow* window = glfwCreateWindow(640, 480, "TextWizard", NULL, NULL);

    // Make the window the current context with glfwMakeContextCurrent()
    glfwMakeContextCurrent(window);

    // Initialize GLAD with gladLoadGLLoader()
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // -------------------------------------------------------
    // VERTEX SHADER

    // Store our vertex shader in a const C string
    const char *vertexShaderSource = "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    // Create Vertex Shader and assign it an ID
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    /* Attach the shader source code to the shader object and compile the shader
        Order of arguments: takes the shader object to compile to, 
        Specifies how many strings we're passing as source code,
        The actual source code of the vertex shader, NULL 
    */
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);


    // Check for successful compilation
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // -------------------------------------------------------
    // FRAGMENT SHADER







    // -------------------------------------------------------
    
    // Triangle Vertices
    float vertices[]
    {
       -0.5f, -0.5f, -0.0f,
        0.5f, -0.5f,  0.0f,
        0.0f,  0.5f,  0.0f
    };

    // Assign a unique ID to the vertex buffer object
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // Assign our VBO to a buffer type (ARRAY_BUFFER)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    /* Call glBufferData to copy our vertex data into the buffer's memory
        Order of arguments: Type of Buffer, Specifies size of data in bytes,
        actual data we want to send, specifies how we want the GPU to manage
        the given data
    */   
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    // Main render loop - run while !glfwWindowShouldClose()
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(2.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    } 

    // Cleanup - glfwDestroyWindow() and glfwTerminate()
    glfwDestroyWindow(window);
    glfwTerminate();
}