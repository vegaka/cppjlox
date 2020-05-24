#pragma once

#include <iostream>
#include <string>

namespace cppjlox
{

class Error {
private:
    static bool hadError;
public:
    static void resetError();
    static bool getError();
    static void report(int line, std::string where, std::string message);
};


}
