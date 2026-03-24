#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>


class Utility
{

public:
    Utility(unsigned int width, unsigned int height) : utilityWindow(nullptr) { }
    ~Utility() {}


private:
    GLFWwindow* utilityWindow;


};
