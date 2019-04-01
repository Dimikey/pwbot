#include "input.h"

void key_press(BYTE key) {

    keybd_event( key,
                0x45,
                KEYEVENTF_EXTENDEDKEY | 0,
                0 );

    // Simulate a key release
    keybd_event( key,
                      0x45,
                      KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
                      0);
}

