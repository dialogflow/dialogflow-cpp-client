#include <iostream>

#include "StreamThreadSafetyCheck.h"

int main(int argc, const char *argv[]) {
    ai::io::StreamThreadSafetyCheck::startChecking();

    return 0;
}
