#include "utils.h"

long get_filesize(FILE* f) {
    int fs;
    fseek(f, 0, SEEK_END);
    fs = ftell(f);
    rewind(f);
    return fs;
}
