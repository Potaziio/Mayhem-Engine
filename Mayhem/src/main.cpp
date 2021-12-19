#include "window/Window.hpp"

int main(int argc, char *argv[])
{
    Mayhem::Window window = Mayhem::Window("Mayhem Engine 0.0.1", 1600, 1000);
    window.update();
    window.freeMemory();

    return 0;
}
