#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "console.h"
#include "char.h"
#include "utils.h"
#include "address.h"

/**
    BOT NOTE:
    The bot is designed to work under Perfect World 1.3.6, Relax750 server,
    in my case.
    Maybe there's a chance to port it to a newer version, but i'm not sure.

    Well, this bot released too late... It should have been released about
    7 years ago (July 7 2017)
*/

/* Essential variables */
HWND hwnd;
LPCSTR windowName = "Element Client";
DWORD pid;
int i;

/* MobList stuff */
int moblist_filesize;
const char* moblist_filename = "moblist.dat";
int target_list[255];
int target_num;

void addr_init() {
    /*
       Find Perfect World's window
    */
    hwnd = FindWindow(NULL, windowName);

    if(!hwnd) {
        console_error("Unable to find Perfect World window! FindWindow() error.");
        exit(0);
    }

    /*
       Get permissions to read data (On Vista, 7 and newer requires administrator rights)
    */
    GetWindowThreadProcessId(hwnd, &pid);
    pw_pHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);

    if(!pw_pHandle) {
        console_error("OpenProcess() error");
        exit(0);
    }

    // Read pointer from the base address (static address)
    ReadProcessMemory(pw_pHandle,(void*)addr_base_static, &addr_character_struc, sizeof(addr_character_struc), 0);

    // Got pointer, apply offset (0x20 by default)
    addr_character_struc += addr_character_offset;

    // Ok, we've got pointer, which points to the character structure actual location (dynamic, changes every program startup)
    ReadProcessMemory(pw_pHandle,(void*)addr_character_struc, &addr_character_struc_actual, sizeof(addr_character_struc_actual), 0);

    // The actual address in process is ready. It's time to apply offsets for hp, mp, exp, etc.
    if(!addr_character_struc_actual) {
        console_error("There's probably more than one Perfect World's window! Sorry, no multi-window support yet.");
        exit(0);
    }

    console_log_1num_hex("Actual address of character structure", (int)addr_character_struc_actual);

    // Applying offsets
    addr_hp     = addr_character_struc_actual + offset_hp;
    addr_mp     = addr_character_struc_actual + offset_mp;
    addr_maxhp  = addr_character_struc_actual + offset_maxhp;
    addr_maxmp  = addr_character_struc_actual + offset_maxmp;
    addr_target = addr_character_struc_actual + offset_target;
    addr_exp    = addr_character_struc_actual + offset_exp;
    addr_maxexp = addr_character_struc_actual + offset_maxexp;
}

void moblist_init() {

    FILE* moblist = fopen(moblist_filename, "a+b");
    if(!moblist) {
        console_error("Error opening moblist!");
        exit(0);
    }

    moblist_filesize = get_filesize(moblist);

    console_log_1str("Moblist filename", moblist_filename);
    console_log_1num("Moblist initial filesize", moblist_filesize);

    // Check whether moblist is empty or not
    if(moblist_filesize > 0) {
        // Moblist is not empty!
        // Check file integrity
        if((moblist_filesize % sizeof(int)) != 0) {
            console_error("Moblist file integrity check failed.");
            exit(0);
        }

        // Each target is 4 byte
        target_num = moblist_filesize / sizeof(int);

        console_log_1num("Mobs in file", target_num);

        for(i = 0; i < target_num; i++) {
            fread(&target_list[i], 4, 1, moblist);
            console_log_1num_hex("Read mob", target_list[i]);
        }

        console_log("Moblist read success");
    }
    else if(moblist_filesize == 0) {
        // Moblist is empty. Let's fill it up
        int prev_target = 0x0;

        // Let's store 5 mobs for now
        for(target_num = 0; target_num < 5; target_num++) {

            console_log_1num("Awaiting target", target_num + 1);

            // Don't let empty targets (0x0) go through
            while(char_get_target() == 0x0) {
                Sleep(500);
            }

            // Don't accept the same target again
            // Skip for the first time
            if(target_num != 0x0) {
                while(char_get_target() == prev_target) {
                    Sleep(500);
                }
            }

            target_list[target_num] = char_get_target();
            prev_target = target_list[target_num];

            console_log_1num_hex("Added target", target_list[target_num]);
        }

        console_log_1str("Done! Now writing targets into file", moblist_filename);
        // (Optional step) Write to file
        fwrite(target_list, sizeof(int), target_num, moblist);

    }
    else {
        console_error("Strange moblist filesize! Ny nnnaher...");
        exit(0);
    }
    fclose(moblist);
}

void bot_start() {

    while(1) {

        // Go through all mobs in list
        for(i = 0; i < target_num; i++) {

            // Attempting to set target
            char_set_target(target_list[i]);

            // If target is still 0x0, then mob is out of range. Try next one
            if(char_get_target() == 0x0) {
                console_log_1num_hex("Target set failed at mob", target_list[i]);
                continue;
            }

            // Kill the target, while it's alive (remains the same)
            while(char_get_target() == target_list[i]) {

                console_log_1num_hex("I attack", target_list[i]);
                char_attack();

                Sleep(1000);
            }

            console_log_1num_hex("Mob killed", target_list[i]);
        }

        console_log("Moblist is over. Repeating...");

		Sleep(1000);
    }
}

int main() {

    addr_init();
    moblist_init();

    console_confirm("Bot is ready to start!");

    bot_start();

    return 0;
}
