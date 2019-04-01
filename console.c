#include "console.h"

void console_error(const char* text) {
    printf("ERROR: %s Error code: %d\n", text, (int)(GetLastError()));
    getchar();
}

void console_log(const char* text) {
    printf("INFO: %s\n", text);
}

void console_confirm(const char* text) {
    printf("ASK: %s Press any key to continue...\n", text);
    getchar();
}

void console_log_1num(const char* text, int a) {
    printf("INFO: %s: %d\n", text, a);
}

void console_log_1str(const char* text, const char* a) {
    printf("INFO: %s: %s\n", text, a);
}


void console_log_1num_hex(const char* text, int a) {
    printf("INFO: %s: 0x%x\n", text, a);
}

void console_log_2num(const char* text, int a, int b) {
    printf("INFO: %s: %d, %d\n", text, a, b);
}

void console_print_char_stats() {
    printf("HP: %d/%d, MP: %d/%d, Target: 0x%x\n", char_get_hp(), char_get_maxhp(), char_get_mp(), char_get_maxmp(), char_get_target());
}
