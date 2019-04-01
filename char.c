#include "char.h"
#include "console.h"
#include "address.h"
#include "input.h"

HANDLE pw_pHandle;

int char_get_target() {

    int target;
    ReadProcessMemory(pw_pHandle, (void*)addr_target, &target, sizeof(target), 0);
    return target;
}

void char_set_target(int target) {

    console_log_1num_hex("Setting target", target);
    WriteProcessMemory(pw_pHandle, (void*)addr_target, &target, sizeof(target), 0);
    Sleep(500);
}

int char_get_hp() {

    int hp;
    ReadProcessMemory(pw_pHandle, (void*)addr_hp, &hp, sizeof(hp), 0);
    return hp;
}

int char_get_maxhp() {

    int maxhp;
    ReadProcessMemory(pw_pHandle, (void*)addr_maxhp, &maxhp, sizeof(maxhp), 0);
    return maxhp;
}

int char_get_mp() {

    int mp;
    ReadProcessMemory(pw_pHandle, (void*)addr_mp, &mp, sizeof(mp), 0);
    return mp;
}

int char_get_maxmp() {

    int maxmp;
    ReadProcessMemory(pw_pHandle, (void*)addr_maxmp, &maxmp, sizeof(maxmp), 0);
    return maxmp;
}

void char_attack() {

    key_press(VK_F1);
}
