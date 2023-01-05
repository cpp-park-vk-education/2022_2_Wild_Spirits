#include <iostream>

#include <Core/Application.h>

int main() {
    LM::Application* app = new LM::Application();

    app->run();

    delete app;

    return 0;
}
