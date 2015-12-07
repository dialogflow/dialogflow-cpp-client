#include <iostream>

#include "StreamThreadSafetyCheck.h"

#include <boost/test/unit_test.hpp>

int main(int argc, const char *argv[]) {
    ai::io::StreamThreadSafetyCheck::startChecking();

    return 0;
}
