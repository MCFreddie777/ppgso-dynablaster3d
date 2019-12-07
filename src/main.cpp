#include "common/scenewindow.h"

int main () {
    SceneWindow window;
    
    while (window.pollEvents()) {}
    
    return EXIT_SUCCESS;
}