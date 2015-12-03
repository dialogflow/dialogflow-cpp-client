#include "indent_stream.h"

using namespace ai::utils;

indent_stream::indent_stream(std::ostream &source_stream): source_stream(source_stream), std::ostream(this) {

}

int indent_stream::overflow(int c) {
    source_stream.put(c);

    if (c == '\n') {
        source_stream << "    ";
    }

    return 0;
}


