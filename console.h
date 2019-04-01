#include <stdio.h>
#include <windows.h>

#include "char.h"

void console_error(const char* text);
void console_log(const char* text);
void console_confirm(const char* text);
void console_log_1num(const char* text, int a);
void console_log_1str(const char* text, const char* a);
void console_log_1num_hex(const char* text, int a);
void console_log_2num(const char* text, int a, int b);
void console_print_char_stats();
