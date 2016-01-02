#include <iostream>
#include <cstdlib>

#include "Game.h"
#include "RenderType.h"

struct Args {
    const int width;
    const int height;
    Args(int w, int h) : width(w), height(h) {}
};

Args processArgs(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    Args a = processArgs(argc, argv);
    Game game(RenderType::ConsoleRender, a.width, a.height);
    game.run();
}

Args processArgs(int argc, char* argv[]) {
    int width, height;
    
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <width> <height>" << std::endl;
        exit(1);
    }
    
    char* p; //Used to see if there are trailing characters in the strtol call, which will leave the pointer at the
    char* q; // char after the last one used to make the number. If this is not the end of the string (\0), there's an issue
    width = strtol(argv[1], &p, 10);
    height = strtol(argv[2], &q, 10);
    
    if (*p != 0 || width <= 0) {
        std::cout << "Invalid width: \"" << argv[1] << "\"." << std::endl;
        exit(1);
    }
    
    if (*q != 0 || height <= 0) {
        std::cout << "Invalid height: \"" << argv[2] << "\"." << std::endl;
        exit(1);
    }
    
    return Args(width, height);    
}
