#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>

#include "Game.h"
#include "MazeGeneratorType.h"
#include "RenderType.h"

struct Args {
    int width;
    int height;
    bool valid = true;
    MazeGeneratorType generator;

    Args(int w, int h, MazeGeneratorType g) : width(w), height(h), generator(g) {}
    Args() : Args(-1, -1, MazeGeneratorType::PRIMS) {}
    bool isValid() { return width > 0 && height > 0 && valid; }
};

Args processArgs(int argc, char* argv[]);
void processIntArg(char* argv[], int& current, Args& a);
void processOptionArg(char* argv[], int& current, Args& a);
void processMGTArg(char* argv[], int& current, Args& a);

int main(int argc, char* argv[]) {
    bool win;

    {
        Args a = processArgs(argc, argv);
        Game game(RenderType::ConsoleRender, a.width, a.height, a.generator);
        game.run();
        win = game.win();
    }

    if (win) {
        std::cout << "You win!" << std::endl;
    } else {
        std::cout << "Quitter!" << std::endl;
    }
}

Args processArgs(int argc, char* argv[]) {
    Args a;

    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] != '-') processIntArg(argv, i, a);
        else                   processOptionArg(argv, i, a);
    }

    if (!a.isValid()) {
        std::cout << "Usage: " << argv[0] << " <width> <height>" << std::endl;
        exit(1);
    }

    return a;
}

//assumes current < argc
void processIntArg(char* argv[], int& current, Args& a) {
    char* p;
    int output = strtol(argv[current], &p, 10);

    if (*p != 0 || output <= 0 || (a.width != -1 && a.height != -1)) {
        std::cout << "Invalid " << (a.width == -1 ? "width" : a.height == -1 ? "height" : "parameter") << ": \"" << argv[current] << "\"" << std::endl;
        a.valid = false;
    } else {
        if (a.width == -1) {
            a.width = output;
        } else {
            a.height = output;
        }
    }
}

//assumes current < argc
//        argv[current][0] == '-'
void processOptionArg(char* argv[], int& current, Args& a) {
    if (argv[current][1] != '-') { //short args
        if (argv[current][2] != 0) { //flag combining not currently supported
            std::cout << "Short option combination not supported. Please put each as a seperate argument." << std::endl;
            a.valid = false;
        } else if (argv[current][1] == 'g') {
            ++current;
            processMGTArg(argv, current, a);
        } else {
            std::cout << "Unrecognized option: \"" << argv[current][1] << "\"" << std::endl;
            a.valid = false;
        }
    } else {
        if (strcmp(argv[current], "--generator") == 0) {
            ++current;
            processMGTArg(argv, current, a);
        } else {
            std::cout << "Unrecognized option: \"" << argv[current] << "\"" << std::endl;
            a.valid = false;
        }
    }
}

//assumes current < argc
//        argc[current] refers to the argument of a generator flag
void processMGTArg(char* argv[], int& current, Args& a) {
    if (strcmp(argv[current], "prim") == 0) {
        a.generator = MazeGeneratorType::PRIMS;
    } else if (strcmp(argv[current], "dfs") == 0) {
        a.generator = MazeGeneratorType::DFS;
    } else {
        std::cout << "Unrecognized generator type: \"" << argv[current] << "\"" << std::endl;
        std::cout << "Recognized options are: prim, dfs" << std::endl;
        a.valid = false;
    }
}
