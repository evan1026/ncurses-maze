#include <iostream>
#include <string>

#include "Game.h"
#include "MazeGeneratorType.h"
#include "RenderType.h"

extern "C" {
    #include <argp.h>
    const char* version    = "mazegame 1.0";
    static char doc[]      = "Mazegame -- an interactive terminal-based maze written with ncurses";
    static char args_doc[] = "WIDTH HEIGHT";
    static struct argp_option options[] = {
        {"generator", 'g', "GENERATOR", 0, "Changes maze generation. Accepted values are \"DFS\" (hard) and \"PRIMS\" (easy)" },
        {"color",     'c', 0,           0, "Forces color rendering (overrides --no-color if used after)"},
        {"no-color",  'n', 0,           0, "Forces no color rendering (overrides --color if used after)"},
        { 0 }
    };
    static error_t parse_opt(int key, char *arg, struct argp_state *state);
    static struct argp argp = { options, parse_opt, args_doc, doc };
}

struct Args {
    int width;
    int height;
    MazeGeneratorType generator;
    RenderType renderer;

    Args(int w, int h, MazeGeneratorType g, RenderType r) : width(w), height(h), generator(g), renderer(r) {}
    Args() : Args(-1, -1, MazeGeneratorType::PRIMS, RenderType::CONSOLE_RENDER_DEFAULT) {}
    bool valid() { return width > 0 && height > 0; }
};

MazeGeneratorType getMGTypeFromName(char* arg);
void handleArg(struct argp_state* state, char* arg, Args& a);

int main(int argc, char* argv[]) {
    bool win;

    {
        Args a;
        argp_parse(&argp, argc, argv, 0, 0, &a);
        Game game(a.renderer, a.width, a.height, a.generator);
        game.run();
        win = game.win();
    }

    if (win) {
        std::cout << "You win!" << std::endl;
    } else {
        std::cout << "Quitter!" << std::endl;
    }

    std::cout << Stats::getInst();
}

static error_t parse_opt(int key, char* arg, struct argp_state* state) {
    Args& a = *((Args*)state->input);

    switch (key) {
        case 'g':
            a.generator = getMGTypeFromName(arg);
            if (a.generator == MazeGeneratorType::UNKNOWN) {
                argp_error(state, "unknown generator -- '%s'", arg);
            }
            break;
        case 'c':
            a.renderer = RenderType::CONSOLE_RENDER_COLOR;
            break;
        case 'n':
            a.renderer = RenderType::CONSOLE_RENDER_NO_COLOR;
            break;
        case ARGP_KEY_ARG:
            handleArg(state, arg, a);
            break;
        case ARGP_KEY_END:
            if (!a.valid()) argp_error(state, "too few arguments");
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

MazeGeneratorType getMGTypeFromName(char* arg) {
    std::string s(arg);
    for (int i = 0; i < s.size(); ++i) {
        s.at(i) = toupper(s.at(i));
    }

    if (s == "PRIMS") {
        return MazeGeneratorType::PRIMS;
    } else if (s == "DFS") {
        return MazeGeneratorType::DFS;
    } else {
        return MazeGeneratorType::UNKNOWN;
    }
}

void handleArg(struct argp_state *state, char* arg, Args& a) {
    char* p = nullptr; //initialized to suppress warnings; the program exits before it's used w/o initialization

    if (a.width == -1) {
        a.width = strtol(arg, &p, 10);
        if (a.width <= 0) argp_error(state, "width must be greater than 0");
    } else if (a.height == -1) {
        a.height = strtol(arg, &p, 10);
        if (a.height <= 0) argp_error(state, "height must be greater than 0");
    } else {
        argp_error(state, "too many args");
    }

    if (*p != 0) {
        argp_error(state, "invalid arg -- '%s'", arg);
    }
}
