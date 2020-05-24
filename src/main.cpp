#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "scanner.h"
#include "error.h"
#include "token.h"

void run(std::string source) {
    cppjlox::Scanner scanner {source};
    std::vector<cppjlox::Token> tokens = scanner.scanTokens();

    for (cppjlox::Token & token : tokens) {
        std::cout << token << std::endl;
    }
}

void runFile(char * path) {
    std::ifstream ifs {path};
    if (ifs.fail()) {
        std::cerr << "Failed to open: " << path << std::endl;
        return;
    }

    std::stringstream ss;
    ss << ifs.rdbuf();
    run(ss.str());

    if (cppjlox::Error::getError()) {
        return;
    }
}

void runPrompt() {
    std::string line;
    for (;;) {
        std::cout << "> ";
        getline(std::cin, line);

        run(line);
        cppjlox::Error::resetError();
    }
}

int main(int argc, char* argv[]) {
    if (argc > 2) {
        std::cout << "Usage: cppjlox [script]" << std::endl;
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        runPrompt();
    }
}