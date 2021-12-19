#include "window/Window.hpp"

int main(int argc, char *argv[])
{
    Mayhem::Window window = Mayhem::Window("Mayhem Engine 0.0.1", 1920, 1080);
    window.update();
    window.freeMemory();

    return 0;
}
