#define GLFW_INCLUDE_NONE // prevent glfw including opengl headers. Glad takes care of this

#include "Core/Application.h"

#include <iostream>

using namespace GameCore;

int main(int argc, char **argv)
{
    Application app;
    std::cout << "Application Running" << std::endl;
    return app.run(argc, argv);
}