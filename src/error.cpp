#include "error.h"

namespace cppjlox
{

bool Error::hadError = false;

void Error::resetError() {
    Error::hadError = false;
}

bool Error::getError() {
    return Error::hadError;
}

void Error::report(int line, std::string where, std::string message) {
    std::cerr << "[line " << line << "] Error " << where << ": " << message << std::endl;
    Error::hadError = true;
}

}
