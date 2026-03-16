#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaders/shader.h"

#define STB_IMAGE_IMPLEMENTATION  // IMAGE PROCESSING
#include "image_processing/stb_image.h"

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

    float triangle1[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,    // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,    // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
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

    unsigned int indices[] = {  
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
    };



    // -------------------------------------------------------
    // TEXTURES

    // float texCoords[]
    // {
    //     0.0f, 0.0f, // lower-left corner
    //     1.0f, 0.0f, // lower-right corner
    //     0.5f, 1.0f  // top-center corner
    // };


    // // Arguments: Texture Target, Texture Axis Option, Texture Wrapping Mode
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);


    // // For using the GL_CLAMP_TO_BORDER
    // float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);


    // // Texture Filtering with GL_NEAREST and GL_LINEAR
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // // Set Filtering Method
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    // // Load an image using stb_image.h
    // int width, height, nrChannels;

    // // Arguments: Location of an Image File, width, height, number of color channels, 
    // unsigned char *data = stbi_load("data/textures/container.jpg", &width, &height, &nrChannels, 0);


    // // Generating a texture
    // unsigned int texture;
    // glGenTextures(1, &texture);


    // // Bind Texture
    // glBindTexture(GL_TEXTURE_2D, texture);

    // // Generate a texture using the previously loaded image data

    // /* Arguments: Texture Target, mipmap level, 
    // format of the texture (rgb), width and height of resulting texture, 
    // legacy stuff keep as 0, format and 
    // datatype of the source image, the actual image data  */
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    // glGenerateMipmap(GL_TEXTURE_2D);


    // // Free image memory
    // stbi_image_free(data);



    // PROCESS OF GENERATING A TEXTURE
    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("data/textures/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    // Always default 
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    stbi_image_free(data);


    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    stbi_set_flip_vertically_on_load(true);
    unsigned char *data2 = stbi_load("data/textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    stbi_image_free(data2);

    // -------------------------------------------------------
    // SHADERS

    Shader shader("shaders/vertex/vertex.glsl", "shaders/fragment/fragment.glsl");


    // -------------------------------------------------------
    // VAO -> VBO -> Vertex Attributes

    unsigned int VAO1, VBO1, VAO2, VBO2, VAO3, VBO3, EBO;

    // VAO1 Setup
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);
    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glEnableVertexAttribArray(0);

    // EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindVertexArray(0);


    // VAO 2
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

    shader.use();
    glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0);
    shader.setInt("texture2", 1);

    while (!glfwWindowShouldClose(window))
    {
        // Clear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Activate shader
        // shader.use();

        // shader.setFloat("offset",0.5f);

        // Draw

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        shader.use();
        glBindVertexArray(VAO1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
 


        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // Cleanup 
    glfwDestroyWindow(window);
    glfwTerminate();

}