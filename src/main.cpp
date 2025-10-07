#define GLFW_INCLUDE_NONE // prevent glfw including opengl headers. Glad takes care of this

#include "Core/Application.h"

#include <iostream>
#include <exception>

using namespace GameCore;

int main(int argc, char **argv)
{
    Application app;
    std::cout << "Application Running" << std::endl;
    try {
        app.run(argc, argv);
    } catch(std::exception e)
    {
        std::cout << e.what();
    }
    
    return 1;
}