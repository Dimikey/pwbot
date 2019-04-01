#include "address.h"

/** Addresses */
/**
  NOTES:
  - The static base address never changes on every program startup;
  - Square brackets [] mean data, stored by address

  INSTRUCTIONS:
  Data in [[addr_base_static] + 0x20 offset] is
  the address for character's structure which holds
  hp, mp, etc.

  The actual hp and mp values are stored by address
  [[[addr_base_static] + 0x20 offset] + char_structure_offset_here]

  (Well, that shit is kinda complicated... But finally it works.)

  Base address and char structure offsets can be obtained using
  Cheat Engine or MHS-Retriever.

  TODO: automatically obtain offsets (without any other tools)
*/
// The following addresses are essential. Obtained from tools
DWORD addr_base_static = 0x009B4594;//0x0092764C;
DWORD offset_from_base_for_coords = 0x14;
DWORD offset_hp = 1104;
DWORD offset_mp = 1108;
DWORD offset_maxhp = 1144;
DWORD offset_maxmp = 1148;
DWORD offset_target = 2800;//2584;
DWORD offset_exp = 1104;
DWORD offset_maxexp = 1104;

// This one seems to be static
DWORD addr_character_offset = 0x20;

// Storage for future actual addresses in running process
DWORD addr_character_struc; // pointer to pointer
DWORD addr_character_struc_actual;
DWORD addr_hp;
DWORD addr_mp;
DWORD addr_maxhp;
DWORD addr_maxmp;
DWORD addr_target;
DWORD addr_exp;
DWORD addr_maxexp;
