////////////////////////////////////////////////////////////////////////////////////////////
//   const.inc                       Version 1.51                       Date: AUG/01/2006
//
//   RS UAIO (Ultimate All-In-One) Admin Menu System (Multilingual)
//   File: UAIO Admin - Main Source File
//
//   Created By:    Rob Secord, B.Sc.
//   Alias: xeroblood (aka; Achilles; sufferer)
//   Email: xeroblood@msn.com
//
//   Updated By:    Dan Weeks
//   Alias: $uicid3
//   Email: suicid3m3@gmail.com
//
//   This File is part of UAIO (Ultimate All-In-One) Admin Menu.
//
////////////////////////////////////////////////////////////////////////////////////////////

#if defined _UAIO_CONST_INCLUDED
  #endinput
#endif
#define _UAIO_CONST_INCLUDED

//    ____________________
//___/ Plugin Information \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
new const PLUGIN_NAME[]    = "UAIO (Admin Menu)"
new const PLUGIN_VERSION[] = "1.50"
new const PLUGIN_AUTHOR[]  = "xeroblood/$uicid3"
new const PLUGIN_MOD[]     = "[AMXX]"

//    __________________
//___/ Plugin Constants \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// UAIO Null
#define UAIO_NULL       (-1)

// String Sizes
#define STR_T           32
#define STR_S           64
#define STR_M           128
#define STR_L           256
#define STR_X           512

//    _______________
//___/ Command Types \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Max Command Types (Vote/Good/Evil/Misc)
#define MAX_CMD_TYPES   4

// Command Type Indexes
#define CMDTYPE_VOTE    0
#define CMDTYPE_GOOD    1
#define CMDTYPE_EVIL    2
#define CMDTYPE_MISC    3

// Command Type Counts
#define MAX_V_COMMANDS  12  // Vote Command Count (Max 32)
#define MAX_G_COMMANDS  19  // Good Command Count (Max 32)
#define MAX_E_COMMANDS  23  // Evil Command Count (Max 32)
#define MAX_M_COMMANDS  17  // Misc Command Count (Max 32)

//    ___________________
//___/ Common Max Values \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Max INI Values (May be Changed & Recompiled)
#define MAX_ADMINS      32  // Max UAIO Admins listed in uaio_admins.ini file
#define MAX_GROUPS      32  // Max UAIO Groups listed in uaio_groups.ini file
#define MAX_MAPS        300  // Max Maps listed in maps.ini or mapcycle.txt file
#define MAX_EXEC        32  // This Applies to Client/Server/Auto Exec INI Files

// UAIO Max Values (Do Not Change)
#define MAX_PLAYERS     32
#define MAX_WEAPONS     32
#define MAX_ALIASES     34
#define MAX_BITS        32

//    _______________________
//___/ HL Specific Constants \______________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define TE_BEAMPOINTS   0
#define TE_SMOKE        5
#define TE_BEAMENTS     8
#define BEAM_LIFE       10  // Not defined by HL but applies to TE_BEAMENTS
#define TE_EXPLOSION2   12
#define TE_SPRITETRAIL  15
#define TE_SPRITE       17
#define TE_BEAMCYLINDER 21
#define TE_BEAMFOLLOW   22
#define TE_KILLBEAM     99
#define DMG_BULLET      (1<<1)

//    ____________________
//___/ Team Set Constants \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define MAX_TEAM_SETS   5
#define TEAM_NONE       0
#define TEAM_T          1
#define TEAM_CT         2
#define TEAM_SPEC       3
#define TEAM_ALL        4

//    _______________________
//___/ Common Menu Constants \______________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Menu Specific Settings
#define MENU_SIZE       400
#define MENU_DISPLAY    8
#define MAX_CMD_CVARS   9  // Note: Increasing this will require re-coding the Cvars Menu
#define MAX_COLORS      9  // Note: Increasing this will require re-coding the Cvars Menu + Color Indexes

// Menu Order Types
#define MO_COMMANDS     0
#define MO_PLAYERS      1

//    _____________________
//___/ Settings Menu Types \________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define SM_NONE       (-1)
#define SM_MAPS         0
#define SM_CVAR         1
#define SM_WEAPON       2
#define SM_FILE         3
#define SM_TEAM         4
#define SM_MODEL        5
#define SM_BURY         6
#define SM_STACK        7
#define SM_TOGGLE       8
#define SM_ARENA	9

//    __________________
//___/ Weapon Constants \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Max Values for Weapon Menus
#define WMENU_OPTIONS   48
#define WMENU_WEAPONS   24
#define WMENU_AMMO      11
#define WMENU_ITEMS      8
#define WMENU_DISPLAY    8

// Weapon Menu Type Indexes
#define MT_PISTOL        0
#define MT_SHOTGUN       1
#define MT_SMG           2
#define MT_RIFLE         3
#define MT_MACHINE       4
#define MT_PAMMO         5
#define MT_SAMMO         6
#define MT_EQUIP         7
#define MT_EXTRA         8

// Array Index Offsets for Pin-pointing correct Weapon
#define OFFSET_SHOTGUN   6
#define OFFSET_SMG       8
#define OFFSET_RIFLE    13
#define OFFSET_SNIPER   18
#define OFFSET_MACHINE  23
#define OFFSET_AMMO     24
#define OFFSET_EQUIP    26
#define OFFSET_EXTRA    34

// Max Weapon Menu Options for Each Menu
// (Machine Gun Menu is Only 1 Option, so no array needed for it)
#define MO_MAX_MAIN      9
#define MO_MAX_PISTOL    6
#define MO_MAX_SHOTGUN   2
#define MO_MAX_SMG       5
#define MO_MAX_RIFLE    10
#define MO_MAX_EQUIP     8
#define MO_MAX_EXTRA    14

//    _________________
//___/ Arena Constants \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Weapon Arena Types
#define AR_MAX_GUNS      10
#define AR_ALL_GUNS      28
#define AR_MAX_MAIN      5
#define AR_MAX_PISTOL    6
#define AR_MAX_SHOTGUN   2
#define AR_MAX_SMG       5
#define AR_MAX_RIFLE     10
#define AR_RIFLE_DISPLAY 7
#define AR_MAX_EQUIP     4
#define AR_MAX_SETS      6
#define AR_START         1
#define AR_END           0

//#define ARENA_KNIVES    0
//#define ARENA_PISTOLS   1
//#define ARENA_SUBS      2
//#define ARENA_SHOTTIES  3
//#define ARENA_RIFLES    4
//#define ARENA_SNIPERS   5

//    _________________
//___/ Error Constants \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// File Load Error Types
#define ERROR_TYPES     6
#define ERROR_MAPS      0
#define ERROR_GROUPS    1
#define ERROR_ADMINS    2
#define ERROR_CEXEC     3
#define ERROR_SEXEC     4
#define ERROR_AEXEC     5

//    __________________
//___/ Common Bit Types \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Client/Server Exec Types
#define EXEC_SERVER     (1<<0)
#define EXEC_ADMIN      (1<<1)
#define EXEC_CLIENT     (1<<2)
#define EXEC_ALLCL      (1<<3)

// Auto-Exec Types
#define AUTOEXEC_SERVER  (1<<0) // "a" - Execute command from server console
#define AUTOEXEC_ADMIN   (1<<1) // "b" - Execute command from admin console (only works on Admins Registered with UAIO)
#define AUTOEXEC_CLIENT  (1<<2) // "c" - Execute command from client console
#define AUTOEXEC_HUDMSG  (1<<3) // "d" - Execute command as HUD Message
#define AUTOEXEC_INSTANT (1<<4) // "e" - Execute Immediate On Connect   (client_putinserver)
#define AUTOEXEC_DELAYED (1<<5) // "f" - Execute Delayed On Connect     (First ResetHUD)
#define AUTOEXEC_LEAVE   (1<<6) // "g" - Execute On Disconnect          (client_disconnect)

//    __________________
//___/ Command Task IDs \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define TASK_COMMON     10000

// Vote Tasks
#define TASK_V_MAP      11033
#define TASK_V_GRAV     11066
#define TASK_V_FF       11100
#define TASK_V_C4TIMER  11133
#define TASK_V_RR       11166
#define TASK_V_ALLTALK  11200
#define TASK_V_KICK     11233
#define TASK_V_SLAP     11266
#define TASK_V_SLAY     11300
#define TASK_V_GLOW     11333
#define TASK_V_GAG      11366
#define TASK_V_KNIFE    11400
#define TASK_V_PISTOL   11433
#define TASK_V_SHOTTY   14466
#define TASK_V_SUBS     11500
#define TASK_V_RIFLE    11533
#define TASK_V_SNIPER   11566
#define TASK_V_ARENA	11600

// Good Tasks
#define TASK_G_GOD      12000
#define TASK_G_GRAV     12033
#define TASK_G_NOCLIP   12066
#define TASK_G_TURBO    12100
#define TASK_G_SILENT   12133
#define TASK_G_INVIS    12166
#define TASK_G_SPY      12200
#define TASK_G_NADES    12233
#define TASK_G_FBANGS   12266
#define TASK_G_SMOKE    12300
#define TASK_G_AMMO     12333
#define TASK_G_EYE      12366
#define TASK_G_BCASH    12400
#define TASK_G_ICASH    12433
#define TASK_G_MIRROR   12466
#define TASK_G_TRUEAP   12500
#define TASK_G_DIVER    12533
#define TASK_G_SHADES   12566
#define TASK_G_SEER     12600

// Evil Tasks
#define TASK_E_BAN_P    13000
#define TASK_E_BAN_T    13033
#define TASK_E_KICK     13066
#define TASK_E_SLAP     13100
#define TASK_E_BSLAP    13133
#define TASK_E_SLAY     13166
#define TASK_E_BURY     13200
#define TASK_E_GAG      13233
#define TASK_E_WARN     13266
#define TASK_E_BLANKS   13300
#define TASK_E_FIRE     13333
#define TASK_E_POISON   13366
#define TASK_E_ROCKET   13400
#define TASK_E_STRIP    13433
#define TASK_E_BLACK    13466
#define TASK_E_SHAKE    13500
#define TASK_E_NLOCK    13533
#define TASK_E_NOBUY    13566
#define TASK_E_PTRAILS  13600
#define TASK_E_GTRAILS  13633
#define TASK_E_WTRAILS  13666
#define TASK_E_DRUGS    13700
#define TASK_E_CRAZYCH  13733

// Misc Tasks
#define TASK_M_MAP      14000
#define TASK_M_HEALTH   14033
#define TASK_M_ARMOR    14066
#define TASK_M_CASH     14100
#define TASK_M_TEAM     14133
#define TASK_M_MODEL    14166
#define TASK_M_FRAG     14200
#define TASK_M_DEATH    14233
#define TASK_M_WEAPON   14266
#define TASK_M_RECRUIT  14300
#define TASK_M_STACK    14333
#define TASK_M_GLOW     14366
#define TASK_M_CEXEC    14400
#define TASK_M_SEXEC    14433
#define TASK_M_REVIVE   14466
#define TASK_M_ARENA    14500
#define TASK_M_MOTD	14533


//    ______________
//___/ Command Bits \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Vote Commands
#define UAIO_V_MAP      (1<<0)
#define UAIO_V_GRAV     (1<<1)
#define UAIO_V_FF       (1<<2)
#define UAIO_V_C4TIMER  (1<<3)
#define UAIO_V_RR       (1<<4)
#define UAIO_V_ALLTALK  (1<<5)
#define UAIO_V_KICK     (1<<6)
#define UAIO_V_SLAP     (1<<7)
#define UAIO_V_SLAY     (1<<8)
#define UAIO_V_GLOW     (1<<9)
#define UAIO_V_GAG      (1<<10)
#define UAIO_V_ARENA    (1<<11)

// Good Commands
#define UAIO_G_GOD      (1<<0)
#define UAIO_G_GRAV     (1<<1)
#define UAIO_G_NOCLIP   (1<<2)
#define UAIO_G_TURBO    (1<<3)
#define UAIO_G_SILENT   (1<<4)
#define UAIO_G_INVIS    (1<<5)
#define UAIO_G_SPY      (1<<6)
#define UAIO_G_NADES    (1<<7)
#define UAIO_G_FBANGS   (1<<8)
#define UAIO_G_SMOKE    (1<<9)
#define UAIO_G_AMMO     (1<<10)
#define UAIO_G_EYE      (1<<11)
#define UAIO_G_BCASH    (1<<12)
#define UAIO_G_ICASH    (1<<13)
#define UAIO_G_MIRROR   (1<<14)
#define UAIO_G_TRUEAP   (1<<15)
#define UAIO_G_DIVER    (1<<16)
#define UAIO_G_SHADES   (1<<17)
#define UAIO_G_SEER     (1<<18)

// Evil Commands
#define UAIO_E_BAN_P    (1<<0)
#define UAIO_E_BAN_T    (1<<1)
#define UAIO_E_KICK     (1<<2)
#define UAIO_E_SLAP     (1<<3)
#define UAIO_E_BSLAP    (1<<4)
#define UAIO_E_SLAY     (1<<5)
#define UAIO_E_BURY     (1<<6)
#define UAIO_E_GAG      (1<<7)
#define UAIO_E_WARN     (1<<8)
#define UAIO_E_BLANKS   (1<<9)
#define UAIO_E_FIRE     (1<<10)
#define UAIO_E_POISON   (1<<11)
#define UAIO_E_ROCKET   (1<<12)
#define UAIO_E_STRIP    (1<<13)
#define UAIO_E_BLACK    (1<<14)
#define UAIO_E_SHAKE    (1<<15)
#define UAIO_E_NLOCK    (1<<16)
#define UAIO_E_NOBUY    (1<<17)
#define UAIO_E_PTRAILS  (1<<18)
#define UAIO_E_GTRAILS  (1<<19)
#define UAIO_E_WTRAILS  (1<<20)
#define UAIO_E_DRUGS    (1<<21)
#define UAIO_E_CRAZYCH  (1<<22)

// Misc Commands
#define UAIO_M_MAP      (1<<0)
#define UAIO_M_HEALTH   (1<<1)
#define UAIO_M_ARMOR    (1<<2)
#define UAIO_M_CASH     (1<<3)
#define UAIO_M_TEAM     (1<<4)
#define UAIO_M_MODEL    (1<<5)
#define UAIO_M_FRAG     (1<<6)
#define UAIO_M_DEATH    (1<<7)
#define UAIO_M_WEAPON   (1<<8)
#define UAIO_M_RECRUIT  (1<<9)
#define UAIO_M_STACK    (1<<10)
#define UAIO_M_GLOW     (1<<11)
#define UAIO_M_CEXEC    (1<<12)
#define UAIO_M_SEXEC    (1<<13)
#define UAIO_M_REVIVE   (1<<14)
#define UAIO_M_ARENA	(1<<15)
#define UAIO_M_MOTD	(1<<16)
