////////////////////////////////////////////////////////////////////////////////////////////
//   global.inc                    Version 1.51                       Date: AUG/01/2006
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

#if defined _UAIO_GLOBAL_INCLUDED
  #endinput
#endif
#define _UAIO_GLOBAL_INCLUDED

//    ________________________
//___/ UAIO Specific Settings \_____________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Plugin State
new bool:g_bPluginEnabled = true

// Game State (Round Start/End)
new bool:g_bGameOn = false

// Plugin State Text Modes
new g_szMode[2][] = { "MODE_DISABLED", "MODE_ENABLED" }

// CS Player Models
new g_szCTSkins[4][] = { "sas", "gsg9", "urban", "gign" }
new g_szTSkins[4][] =  { "arctic", "leet", "guerilla", "terror" }
new g_szVIPSkin[] = "vip"

// Gravity Settings (1.0 = 800 = Normal Gravity)
new Float:g_fGravity[] = { 1.0, 0.25 }

// Color of Beams for Seer      (T)           (CT)
//                           (r,g,b,a)
new g_iBeamColor[2][4] = { {255,0,0,100}, {0,0,255,100} }

// Crosshair Sizes
new g_szCHSizes[3][] = { "small", "medium", "large" }

// Titles of Command Types used in Menu
new g_szCmdTypeTitles[MAX_CMD_TYPES][] = { "V_CMD_TYPE", "G_CMD_TYPE", "E_CMD_TYPE", "M_CMD_TYPE" }

// Variable Command Arguments (for use in Menus)
new g_szVarCmdArgs[3][] = { "@ALL", "@T", "@CT" }

// Common Color Names (and associated rgb values)
new g_szColors[MAX_COLORS][] = { "Red", "Green", "Blue", "Cyan", "Magenta", "Yellow", "Orange", "Purple", "Random" }
new g_iColors[MAX_COLORS][3] =
{
    {255, 0, 0},    // Red
    {0, 255, 0},    // Green
    {0, 0, 255},    // Blue
    {0, 255, 255},  // Cyan
    {255, 0, 255},  // Magenta
    {255, 255, 0},  // Yellow
    {255, 153, 0},  // Orange
    {255, 0, 250},  // Purple
    {0, 0, 0}       // Random
}

//    __________________________
//___/ Player Specific Settings \___________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Current Player Command/Effect
new g_szCmdArgs[MAX_PLAYERS][STR_M]
new g_iHasEffect[MAX_PLAYERS][MAX_CMD_TYPES]
new g_iRocket_Z[MAX_PLAYERS]
new g_iCurWeapon[MAX_PLAYERS][2] // Tracks players Shots-Fired: [0]=WeaponID, [1]=Ammo
new Float:g_fSpeeds[MAX_PLAYERS]

// Tracks Joining Players for First ResetHUD Event
new bool:g_bIsJoining[MAX_PLAYERS] = false

//    ________________
//___/ Arena Specific \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Current Arena Type
//new g_iCurrArenaType = UAIO_NULL
new bool:g_bArenaEnabled = false;
new bool:g_bArenaGrenades = true;
new bool:g_bArenaVote[MAX_PLAYERS] = false
new g_iArenaCustom[AR_MAX_GUNS] = { UAIO_NULL , ...}
new g_iWepCount = 0

// Old FreezeTime (FreezeTime Set to 1 for Arenas)
new g_iOldFreezeTime = 0

// Arena Menu 
new g_szArenaMenuTxt[AR_MAX_MAIN][] = {
    "WMENU_PISTOL", "WMENU_SHOTTY", "WMENU_SMG", "WMENU_RIFLE", "WMENU_MGUN"
}

//Equipment Menu
new g_szArenaEquipMenuTxt[AR_MAX_EQUIP][] = {
    "WMENU_E_FLASH", "WMENU_E_HENADE", "WMENU_E_SNADE", "WMENU_E_SHIELD"
}

// Weapon Constants
// Pistols Constants
new g_iPistolConst[AR_MAX_PISTOL] = {
    CSW_USP, CSW_GLOCK18, CSW_DEAGLE, CSW_P228, CSW_ELITE, CSW_FIVESEVEN
}
// Shotguns Constants
new g_iShotgunConst[AR_MAX_SHOTGUN] = {
    CSW_M3, CSW_XM1014
}
// SMG Constants
new g_iSmgConst[AR_MAX_SMG] = {
    CSW_MP5NAVY, CSW_TMP, CSW_P90, CSW_MAC10, CSW_UMP45
}
// Rifles Constants
new g_iRifleConst[AR_MAX_RIFLE] = {
    CSW_FAMAS, CSW_SG552, CSW_AK47, CSW_M4A1, CSW_AUG,
    CSW_SCOUT, CSW_AWP, CSW_SG550, CSW_G3SG1, CSW_GALIL
}
//Machine Guns Constants
new g_iMachineConst = CSW_M249

//Equipment Constants
new g_iEquipConst[AR_MAX_EQUIP] = {
    CSW_FLASHBANG, CSW_HEGRENADE, CSW_SMOKEGRENADE, 34
}

new g_iArenaWeaponConst[AR_ALL_GUNS] = {
    CSW_USP, CSW_GLOCK18, CSW_DEAGLE, CSW_P228, CSW_ELITE, CSW_FIVESEVEN,
    CSW_M3, CSW_XM1014,
    CSW_MP5NAVY, CSW_TMP, CSW_P90, CSW_MAC10, CSW_UMP45,
    CSW_FAMAS, CSW_SG552, CSW_AK47, CSW_M4A1, CSW_AUG,
    CSW_SCOUT, CSW_AWP, CSW_SG550, CSW_G3SG1, CSW_GALIL,
    CSW_M249,
    CSW_FLASHBANG, CSW_HEGRENADE, CSW_SMOKEGRENADE, 34
}
new g_iArenaWeaponNum[AR_ALL_GUNS] = {
    11, 12, 13, 14, 15, 16,
    21, 22,
    31, 32, 33, 34, 35,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
    51,
    73, 74, 75, 78
}

// Parallel Array for Weapon Titles (Parellel to Weapon Codes Above)
new g_szArenaWeaponTitles[AR_ALL_GUNS][] = {
    "WMENU_MSG_USP", "WMENU_MSG_GLOCK", "WMENU_MSG_DGL", "WMENU_MSG_228", "WMENU_MSG_DUAL", "WMENU_MSG_57",
    "WMENU_MSG_PUMP", "WMENU_MSG_AUTO", "WMENU_MSG_MP5", "WMENU_MSG_TMP", "WMENU_MSG_C90", "WMENU_MSG_MAC10",
    "WMENU_MSG_UMP", "WMENU_MSG_CLARI", "WMENU_MSG_KRIEG", "WMENU_MSG_AK47", "WMENU_MSG_M4A1", "WMENU_MSG_AUG",
    "WMENU_MSG_SCOUT", "WMENU_MSG_AWP", "WMENU_MSG_CTAUTO", "WMENU_MSG_TAUTO", "WMENU_MSG_GALIL",
    "WMENU_MSG_PARA", "WMENU_MSG_FLASH", "WMENU_MSG_HENADE", "WMENU_MSG_SNADE", "WMENU_MSG_SHIELD"
}

#define NADE_TYPE_NUM 3

new const NADE_ID_WEAPON[NADE_TYPE_NUM] = {CSW_HEGRENADE, CSW_FLASHBANG, CSW_SMOKEGRENADE}

//    ___________________________
//___/ HL Engine Message Indexes \__________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
new g_iMsgDamage
new g_iMsgDeath
new g_iMsgSetFOV
new g_iMsgScreenFade
new g_iMsgScreenShake

//    _________
//___/ Sprites \____________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
new g_sprBeam
new g_sprLaser
new g_sprWhite
new g_sprSmoke
new g_sprMFlash
new g_sprBFlare

//    _______________
//___/ Menu Tracking \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
new g_iMenuPlayers[MAX_PLAYERS][MAX_PLAYERS]
new g_iMenuPlayersNum[MAX_PLAYERS]
new g_iMenuPosition[MAX_PLAYERS]
new g_iMenuOrder[MAX_PLAYERS]
new g_iCurrPlayer[MAX_PLAYERS]
new g_iCurrCommand[MAX_PLAYERS]
new g_iCurrType[MAX_PLAYERS]
new g_iSettingsType[MAX_PLAYERS]
new g_iWeaponMenuType[MAX_PLAYERS]
new g_iWeaponMenuPos[MAX_PLAYERS]


//    _______________
//___/ Vote Tracking \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
new g_iVoteCount[2] = 0         // [0]=Against, [1]=For
new g_szVoteCmd[STR_T]
new g_szVoteCmdLen = 0

new Float:g_fVoteRatio = 0.0
new Float:g_fVoteTimer = 0.0

//    ______________________
//___/ Global Effects State \_______________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Good Commands Granted to Everyone/T/CT/Spec
new g_iCmdsForAll[MAX_TEAM_SETS] = 0
new g_iCmdsForAllDur[MAX_TEAM_SETS][MAX_BITS]
new g_iCmdsForAllTeam = TEAM_NONE

//    ___________
//___/ Maps Data \__________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Maps List
new g_szMapNames[MAX_MAPS][STR_T]
new g_iMapCount = 0

//    _______________
//___/ INI File Data \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Client Exec Commands Data
new g_szCExecTitles[MAX_EXEC][STR_T]
new g_szCExecCmds[MAX_EXEC][STR_T]
new g_iCExecFlags[MAX_EXEC] = UAIO_NULL
new g_iCExecCount = 0

// Server Exec Commands Data
new g_szSExecTitles[MAX_EXEC][STR_T]
new g_szSExecCmds[MAX_EXEC][STR_T]
new g_iSExecFlags[MAX_EXEC] = UAIO_NULL
new g_iSExecCount = 0

// Auto Exec Commands Data
new g_szAExecUser[MAX_EXEC][STR_T]
new g_szAExecCmds[MAX_EXEC][STR_M]
new g_iAExecFlags[MAX_EXEC] = UAIO_NULL
new g_iAExecCount = 0
new Float:g_fAExecInterval[MAX_PLAYERS] = 0.0

//    _______________________________
//___/ UAIO Files (set in files.inc) \______________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HTML File For Warn MOTD
new g_szFileWarn[STR_M]

// HTML File For Recruit Info MOTD
new g_szFileRecruit[STR_M]

// AMX(X) Maps.ini (or mapcycle.txt) File for Maps Menu
new g_szFileMaps[STR_M]

// Files for Loading Admins/Groups
new g_szFileAdmins[STR_M]
new g_szFileGroups[STR_M]

// INI File for Client/Server/Auto Exec Commands
new g_szFileCExec[STR_M]
new g_szFileSExec[STR_M]
new g_szFileAExec[STR_M]

// File Load Errors
new bool:g_bFileError[ERROR_TYPES] = false

// Sound Files
new g_szSndFlames[]  = "ambience/flameburst1.wav"
new g_szSndScream1[] = "scientist/scream07.wav"
new g_szSndScream2[] = "scientist/scream21.wav"
new g_szSndRocket1[] = "weapons/rocketfire1.wav"
new g_szSndRocket2[] = "weapons/rocket1.wav"
new g_szSndPoison[]  = "player/bhit_kevlar-1.wav"
new g_szSndBeep[]    = "weapons/c4_beep1.wav"
new g_szSndThunder[] = "ambience/thunder_clap.wav"

//    ___________________
//___/ Command Flag Bits \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Connected Admins/Players Complete Flag-Bits, Populated on client_connect
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
new g_iAdminCmdBits[MAX_PLAYERS][MAX_CMD_TYPES]
new bool:g_bIsAdmin[MAX_PLAYERS] = false

//    ______________
//___/ Admins Count \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Loaded Admin Count (Admin List from File)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
new g_iAdminCount = 0

//    _____________
//___/ Admins Data \________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Parallel Arrays (Admin STEAMID/Group), Populated on plugin_cfg
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
new g_szAdminID[MAX_ADMINS][STR_T]
new g_szAdminGroup[MAX_ADMINS][STR_X]

//    ______________
//___/ Groups Count \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Loaded Group Count (Group List from File)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
new g_iGroupCount[MAX_CMD_TYPES] = 0

//    _____________
//___/ Groups Data \________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Parallel Arrays (Group Name/Flags), Populated on plugin_cfg
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
new g_szVGroupNames[MAX_GROUPS][STR_T]  // Vote Command Groups
new g_iVGroupFlags[MAX_GROUPS]

new g_szGGroupNames[MAX_GROUPS][STR_T]  // Good Command Groups
new g_iGGroupFlags[MAX_GROUPS]

new g_szEGroupNames[MAX_GROUPS][STR_T]  // Evil Command Groups
new g_iEGroupFlags[MAX_GROUPS]

new g_szMGroupNames[MAX_GROUPS][STR_T]  // Misc Command Groups
new g_iMGroupFlags[MAX_GROUPS]

//    _______________
//___/ Commands Data \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Parallel Arrays (Title/Command/Function/Etc..)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Command Titles (ML API)
new g_szVCmdTitle[MAX_V_COMMANDS][] =
{
    "V_CMD_MAP", "V_CMD_GRAV", "V_CMD_FF", "V_CMD_C4", "V_CMD_RR", "V_CMD_ALLTALK",
    "V_CMD_KICK", "V_CMD_SLAP", "V_CMD_SLAY", "V_CMD_GLOW", "V_CMD_GAG", "V_CMD_ARENA"
}
new g_szGCmdTitle[MAX_G_COMMANDS][] =
{
    "G_CMD_GOD", "G_CMD_GRAV", "G_CMD_NOCLIP", "G_CMD_TURBO", "G_CMD_SILENT", "G_CMD_INVIS", 
    "G_CMD_SPY", "G_CMD_HENADES", "G_CMD_FLASHES", "G_CMD_SNADES", "G_CMD_AMMO",
    "G_CMD_EYE", "G_CMD_BCASH", "G_CMD_ICASH", "G_CMD_MIRROR", "G_CMD_TRUEAP", "G_CMD_DIVER",
    "G_CMD_SHADES", "G_CMD_SEER"
}
new g_szECmdTitle[MAX_E_COMMANDS][] =
{
    "E_CMD_PBAN", "E_CMD_TBAN", "E_CMD_KICK", "E_CMD_SLAP", "E_CMD_BSLAP", "E_CMD_SLAY",
    "E_CMD_BURY", "E_CMD_GAG", "E_CMD_WARN", "E_CMD_BLANKS", "E_CMD_FIRE", "E_CMD_POISON",
    "E_CMD_ROCKET", "E_CMD_STRIP", "E_CMD_BLACKOUT", "E_CMD_SHAKE", "E_CMD_NLOCK",
    "E_CMD_BLOCK", "E_CMD_PTRAILS", "E_CMD_GTRAILS", "E_CMD_WTRAILS", "E_CMD_DRUGS", "E_CMD_CRAZYCH"
}
new g_szMCmdTitle[MAX_M_COMMANDS][] =
{
    "M_CMD_MAP", "M_CMD_HP", "M_CMD_AP", "M_CMD_CASH", "M_CMD_TEAM", "M_CMD_MODEL",
    "M_CMD_FRAG", "M_CMD_DEATH", "M_CMD_WEAPON", "M_CMD_RECRUIT", "M_CMD_STACK", "M_CMD_GLOW",
    "M_CMD_CEXEC", "M_CMD_SEXEC", "M_CMD_REVIVE", "M_CMD_ARENA", "M_CMD_MOTD"
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Console Commands
new g_szVCmdConsole[MAX_V_COMMANDS][] =
{
    "uaio_v_map",     "uaio_v_grav",    "uaio_v_ff",      "uaio_v_c4timer",
    "uaio_v_rr",      "uaio_v_alltalk", "uaio_v_kick",    "uaio_v_slap",
    "uaio_v_slay",    "uaio_v_glow",    "uaio_v_gag",     "uaio_v_arena"
}
new g_szGCmdConsole[MAX_G_COMMANDS][] =
{
    "uaio_god", "uaio_grav",  "uaio_noclip", "uaio_turbo",  "uaio_silent", "uaio_invis",
    "uaio_spy", "uaio_he_nades", "uaio_fb_nades", "uaio_sm_nades", "uaio_ammo", "uaio_eye",
    "uaio_bcash", "uaio_icash", "uaio_mirror", "uaio_trueap", "uaio_diver", "uaio_shades",
    "uaio_seer"
}
new g_szECmdConsole[MAX_E_COMMANDS][] =
{
    "uaio_ban_p", "uaio_ban_t", "uaio_kick",   "uaio_slap", "uaio_bslap", "uaio_slay", 
    "uaio_bury", "uaio_gag",   "uaio_warn",  "uaio_blanks", "uaio_fire", "uaio_poison", 
    "uaio_rocket", "uaio_strip", "uaio_blackout", "uaio_shake", "uaio_namelock",
    "uaio_nobuy", "uaio_ptrails", "uaio_gtrails", "uaio_tracers", "uaio_drugs",
    "uaio_crazych"
}
new g_szMCmdConsole[MAX_M_COMMANDS][] =
{
    "uaio_map", "uaio_health", "uaio_armor", "uaio_cash", "uaio_team", "uaio_model",
    "uaio_frags", "uaio_deaths", "uaio_weapon",  "uaio_recruit", "uaio_stack", "uaio_glow",
    "uaio_cexec", "uaio_sexec", "uaio_revive" , "uaio_arena" , "uaio_motd"
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Command Functions
new g_szVCmdFunc[MAX_V_COMMANDS][] =
{
    "ActionVoteMap",     "ActionVoteGrav",    "ActionVoteFF",     "ActionVoteC4Timer",
    "ActionVoteRR",      "ActionVoteAlltalk", "ActionVoteKick",   "ActionVoteSlap",
    "ActionVoteSlay",    "ActionVoteGlow",    "ActionVoteGag",    "ActionVoteArena"
}
new g_szGCmdFunc[MAX_G_COMMANDS][] =
{
    "ActionGod", "ActionGrav",  "ActionNoclip", "ActionTurbo",  "ActionSilent", "ActionInvis",
    "ActionSpy", "ActionHENades", "ActionFBNades", "ActionSMNades", "ActionAmmo",   "ActionEye",
    "ActionBcash", "ActionIcash", "ActionMirror", "ActionTrueArmor", "ActionDiveKit", "ActionShades",
    "ActionSeer"
}
new g_szECmdFunc[MAX_E_COMMANDS][] =
{
    "ActionBanP",  "ActionBanT", "ActionKick",   "ActionSlap", "ActionBslap", "ActionSlay", 
    "ActionBury", "ActionGag",   "ActionWarn", "ActionBlanks", "ActionFire", "ActionPoison", 
    "ActionRocket", "ActionStrip", "ActionBlackout", "ActionShake", "ActionNameLock",
    "ActionNoBuy", "ActionPTrails", "ActionGTrails", "ActionWTrails", "ActionDrugs",
    "ActionCrazyCH"
}
new g_szMCmdFunc[MAX_M_COMMANDS][] =
{
    "ActionMap", "ActionHealth", "ActionArmor", "ActionCash", "ActionTeam", "ActionModel",
    "ActionFrags", "ActionDeaths", "ActionWeapon", "ActionRecruit", "ActionStack", "ActionGlow",
    "ActionCExec", "ActionSExec", "ActionRevive" , "ActionArena" , "ActionMotd"
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Command Configuration Variables
new g_szVCmdCvar[MAX_V_COMMANDS][] =
{
    "_", "sv_uaio_v_grav", "_", "sv_uaio_v_c4timer", "sv_uaio_v_rr", "_",
    "_", "sv_uaio_v_slap", "_", "sv_uaio_v_glow", "sv_uaio_v_gag", "_"
}
new g_szGCmdCvar[MAX_G_COMMANDS][] =
{
    "sv_uaio_god",   "sv_uaio_grav", "sv_uaio_noclip", "sv_uaio_turbo", "sv_uaio_silent",
    "sv_uaio_invis", "sv_uaio_spy",  "sv_uaio_he_nades",  "sv_uaio_fb_nades",  "sv_uaio_sm_nades",
    "sv_uaio_ammo", "sv_uaio_eye", "sv_uaio_bcash", "sv_uaio_icash", "sv_uaio_mirror",
    "sv_uaio_trueap", "sv_uaio_diver", "sv_uaio_shades", "sv_uaio_seer"
}
new g_szECmdCvar[MAX_E_COMMANDS][] =
{
    "_", "sv_uaio_ban_temp", "_", "sv_uaio_slap", "sv_uaio_bslap", "_", "_", "sv_uaio_gag",
    "_", "sv_uaio_blanks", "sv_uaio_fire", "sv_uaio_poison", "_", "_", "sv_uaio_blackout",
    "_", "sv_uaio_nlock", "sv_uaio_nobuy", "sv_uaio_ptrails", "sv_uaio_gtrails", "sv_uaio_wtrails",
    "sv_uaio_drugs", "sv_uaio_crazych"
}
new g_szMCmdCvar[MAX_M_COMMANDS][] =
{
    "_", "sv_uaio_health", "sv_uaio_armor", "sv_uaio_cash",  "_", "_", "sv_uaio_frags",
    "sv_uaio_deaths", "_", "_", "_", "sv_uaio_glow", "_", "_", "_", "_", "sv_uaio_motd"
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Command Configuration Variable Values
new g_szVCmdCvarFlags[MAX_V_COMMANDS][] =
{
    "_",
    "800 700 600 500 400 300 200 100",
    "_",
    "10 15 20",
    "1 2 3 4 5 6 7 8 9",
    "_",
    "_",
    "1 5 10 15 20 50 75 99 100",
    "_",
    "Red Green Blue Cyan Magenta Yellow Orange Purple Random",
    "30 60 90 120 240 300 360 420 480",
    "_"
}
new g_szGCmdCvarFlags[MAX_G_COMMANDS][] =
{
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900"
}
new g_szECmdCvarFlags[MAX_E_COMMANDS][] =
{
    "_",
    "5 15 30 60 90 120 300 600 1440",
    "_",
    "1 5 10 15 20 25 50 75 99",
    "10 20 30 40 50 60 70 80 90",
    "_",
    "_",
    "15 30 60 90 120 300 600 900 1200",
    "_",
    "15 30 60 90 120 300 600 900 1200",
    "2 5 10 11 12 13 14 15 20",
    "2 5 10 11 12 13 14 15 20",
    "_",
    "_",
    "1 2 3 5 10 15 20 25 30",
    "_",
    "15 30 60 90 120 300 600 900 1200",
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900",
    "0 15 30 60 90 120 300 600 900"
}
new g_szMCmdCvarFlags[MAX_M_COMMANDS][] =
{
    "_",
    "25 50 75 100 125 150 175 200 255",
    "25 50 75 100 125 150 175 200 255",
    "0 800 1500 3000 6000 9000 12000 14000 16000",
    "_",
    "_",
    "-3 -2 -1 1 2 3 4 5 6",
    "0 1 2 3 4 5 6 7 10",
    "_",
    "_",
    "_",
    "Red Green Blue Cyan Magenta Yellow Orange Random",
    "_",
    "_",
    "_",
    "_",
    "rules motd tryout help server admin"
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Command Argument Counts
new g_iVCmdArgCount[MAX_V_COMMANDS] = { 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 2, 1 }  //1, 1, 1, 1, 1
new g_iGCmdArgCount[MAX_G_COMMANDS] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }
new g_iECmdArgCount[MAX_E_COMMANDS] = { 1, 2, 1, 2, 2, 1, 2, 2, 1, 2, 2, 2, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2 }
new g_iMCmdArgCount[MAX_M_COMMANDS] = { 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 1, 2, 2 }
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Command Uses Players Menu?  (1=yes, 0=no)
new g_iVUsesPMenu[MAX_V_COMMANDS] = { 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0} //0, 0, 0, 0, 0 
new g_iGUsesPMenu[MAX_G_COMMANDS] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
new g_iEUsesPMenu[MAX_E_COMMANDS] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
new g_iMUsesPMenu[MAX_M_COMMANDS] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1}
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Command Menu Settings Types
new g_iVCmdSetFlags[MAX_V_COMMANDS] =
{
    SM_MAPS, SM_CVAR, SM_TOGGLE, SM_CVAR, SM_CVAR, SM_TOGGLE, SM_NONE, SM_CVAR,
    SM_NONE, SM_CVAR, SM_CVAR, SM_ARENA
}
new g_iGCmdSetFlags[MAX_G_COMMANDS] =
{
    SM_CVAR, SM_CVAR, SM_CVAR, SM_CVAR, SM_CVAR, SM_CVAR, SM_CVAR, SM_CVAR, SM_CVAR, SM_CVAR,
    SM_CVAR, SM_CVAR, SM_CVAR, SM_CVAR, SM_CVAR, SM_CVAR, SM_CVAR, SM_CVAR, SM_CVAR
}
new g_iECmdSetFlags[MAX_E_COMMANDS] =
{
    SM_NONE, SM_CVAR, SM_NONE, SM_CVAR, SM_CVAR, SM_NONE, SM_BURY, SM_CVAR,
    SM_NONE, SM_CVAR, SM_CVAR, SM_CVAR, SM_NONE, SM_NONE, SM_CVAR, SM_NONE, SM_CVAR,
    SM_CVAR, SM_CVAR, SM_CVAR, SM_CVAR, SM_CVAR, SM_CVAR
}
new g_iMCmdSetFlags[MAX_M_COMMANDS] =
{
    SM_MAPS, SM_CVAR, SM_CVAR, SM_CVAR, SM_TEAM, SM_MODEL, SM_CVAR, SM_CVAR,
    SM_WEAPON, SM_NONE, SM_STACK, SM_CVAR, SM_FILE, SM_FILE, SM_NONE, SM_ARENA, SM_CVAR
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Command Usages
new g_szVCmdUsage[MAX_V_COMMANDS][] =
{
    "USAGE_MAP",
    "USAGE_GRAV",
    "USAGE_ONOFF",
    "USAGE_SECS",
    "USAGE_SECS",
    "USAGE_ONOFF",
    "USAGE_PLAYER",
    "USAGE_DAMAGE",
    "USAGE_PLAYER",
    "USAGE_GLOW",
    "USAGE_PL_SECS",
    "USAGE_ARENA"
}
new g_szGCmdUsage[MAX_G_COMMANDS][] =
{
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS"
}
new g_szECmdUsage[MAX_E_COMMANDS][] =
{
    "USAGE_PLAYER",
    "USAGE_MINS",
    "USAGE_PLAYER",
    "USAGE_DAMAGE",
    "USAGE_SLAPS",
    "USAGE_PLAYER",
    "USAGE_PL_ONOFF",
    "USAGE_PL_SECS",
    "USAGE_PLAYER",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PLAYER",
    "USAGE_PLAYER",
    "USAGE_PL_SECS",
    "USAGE_PLAYER",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS",
    "USAGE_PL_SECS"
}
new g_szMCmdUsage[MAX_M_COMMANDS][] =
{
    "USAGE_MAP",
    "USAGE_HP",
    "USAGE_AP",
    "USAGE_CASH",
    "USAGE_TEAM",
    "USAGE_MODEL",
    "USAGE_FRAGS",
    "USAGE_DEATHS",
    "USAGE_WEAPON",
    "USAGE_PLAYER",
    "USAGE_STACK",
    "USAGE_GLOW",
    "USAGE_CEXEC",
    "USAGE_SEXEC",
    "USAGE_PLAYER",
    "USAGE_ARENA",
    "USAGE_MOTD"
}

//    ___________________
//___/ Weapons Menu Text \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Main Weapon Menu
new g_szWeaponMenuTxt[MO_MAX_MAIN][] = {
    "WMENU_PISTOL", "WMENU_SHOTTY", "WMENU_SMG", "WMENU_RIFLE", "WMENU_MGUN",
    "WMENU_PAMMO", "WMENU_SAMMO", "WMENU_EQUIP", "WMENU_EXTRA"
}
// Pistols Menu
new g_szPistolMenuTxt[MO_MAX_PISTOL][] = {
    "WMENU_P_USP", "WMENU_P_GLOCK", "WMENU_P_DGL", "WMENU_P_228", "WMENU_P_DUAL", "WMENU_P_57"
}
// Shotguns Menu
new g_szShotgunMenuTxt[MO_MAX_SHOTGUN][] = {
    "WMENU_SH_PUMP", "WMENU_SH_AUTO"
}
// SMG Menu
new g_szSmgMenuTxt[MO_MAX_SMG][] = {
    "WMENU_SM_MP5", "WMENU_SM_TMP", "WMENU_SM_C90", "WMENU_SM_MAC10", "WMENU_SM_UMP"
}
// Rifles Menu
new g_szRifleMenuTxt[MO_MAX_RIFLE][] = {
    "WMENU_R_CLARI", "WMENU_R_KRIEG", "WMENU_R_AK47", "WMENU_R_M4A1", "WMENU_R_AUG",
    "WMENU_R_SCOUT", "WMENU_R_AWP", "WMENU_R_CTAUTO", "WMENU_R_TAUTO", "WMENU_R_GALIL"
}
//Machine Guns Menu
new g_szMachineMenuTxt[] = "WMENU_M_PARA"

//Equipment Menu
new g_szEquipMenuTxt[MO_MAX_EQUIP][] = {
    "WMENU_E_KEV", "WMENU_E_KEVHELM", "WMENU_E_FLASH", "WMENU_E_HENADE", "WMENU_E_SNADE",
    "WMENU_E_DKIT", "WMENU_E_NVG", "WMENU_E_SHIELD"
}
//Extras Menu
new g_szExtraMenuTxt[MO_MAX_EXTRA][] = {
    "WMENU_X_ALL", "WMENU_X_M3", "WMENU_X_MP5", "WMENU_X_CLARI", "WMENU_X_GALIL",
    "WMENU_X_M4A1", "WMENU_X_AK47", "WMENU_X_KRIEG", "WMENU_X_AUG", "WMENU_X_PARA",
    "WMENU_X_SCOUT", "WMENU_X_AUTO", "WMENU_X_AWP", "WMENU_X_NADES"
}

//    ___________________
//___/ Weapons Menu Code \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Names of Weapons for give_item() native
new g_szWeaponList[WMENU_WEAPONS][] = {
    "weapon_usp", "weapon_glock18", "weapon_deagle", "weapon_p228", "weapon_elite",
    "weapon_fiveseven", "weapon_m3", "weapon_xm1014", "weapon_mp5navy", "weapon_tmp",
    "weapon_p90", "weapon_mac10", "weapon_ump45", "weapon_famas", "weapon_sg552",
    "weapon_ak47", "weapon_m4a1", "weapon_aug", "weapon_scout", "weapon_awp",
    "weapon_g3sg1", "weapon_sg550", "weapon_galil", "weapon_m249"
}
// Names of Equipment Items for give_item() native
new g_szItemsList[WMENU_ITEMS][] = {
    "item_kevlar", "item_assaultsuit", "weapon_flashbang", "weapon_hegrenade",
    "weapon_smokegrenade", "item_thighpack", "item_nvgs", "weapon_shield"
}
// Names of Ammo Packs for give_item() native
new g_szAmmoList[WMENU_AMMO][] = {
    "ammo_45acp", "ammo_9mm", "ammo_50ae", "ammo_357sig",
    "ammo_57mm", "ammo_buckshot", "ammo_556nato", "ammo_762nato",
    "ammo_338magnum", "ammo_308", "ammo_556natobox"
}
// Weapon Aliases used for Buying Weapons
new g_szWeaponAlias[MAX_ALIASES][] = {
    "km45", "9x19mm", "nighthawk", "228compact", "elites", "fiveseven", "12gauge", 
    "autoshotgun", "smg", "mp", "c90", "mac10", "ump45", "cv47", "defender", "clarion",
    "krieg552", "m4a1", "bullup", "scout", "magnum", "d3au1", "krieg550", "m249", "vest",
    "vesthelm", "flash", "hegren", "sgren", "defuser", "nvgs", "shield", "primammo", "secammo"
}
// Weapon Indexing Data (for give_item: ammo-type, amount)
new g_iWeaponData[WMENU_WEAPONS][2] = {
    { 0, 8 }, { 1, 8 }, { 2, 5 }, { 3, 6 }, { 1, 4 },
    { 4, 4 }, { 5, 4 }, { 5, 4 }, { 1, 4 }, { 1, 4 },
    { 4, 4 }, { 0, 6 }, { 0, 6 }, { 6, 3 }, { 6, 3 },
    { 7, 3 }, { 6, 3 }, { 6, 3 }, { 7, 3 }, { 8, 3 },
    { 7, 3 }, { 6, 3 }, { 9, 3 }, { 10, 7 }
}

// Weapon Codes (for console command)
new g_iWeaponNum[WMENU_OPTIONS] = {
    11, 12, 13, 14, 15, 16,
    21, 22,
    31, 32, 33, 34, 35,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
    51,
    61, 62,
    71, 72, 73, 74, 75, 76, 77, 78,
    81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94
}

// Parallel Array for Weapon Titles (Parellel to Weapon Codes Above)
new g_szWeaponTitles[WMENU_OPTIONS][] = {
    "WMENU_MSG_USP",
    "WMENU_MSG_GLOCK",
    "WMENU_MSG_DGL",
    "WMENU_MSG_228",
    "WMENU_MSG_DUAL",
    "WMENU_MSG_57",
    "WMENU_MSG_PUMP",
    "WMENU_MSG_AUTO",
    "WMENU_MSG_MP5",
    "WMENU_MSG_TMP",
    "WMENU_MSG_C90",
    "WMENU_MSG_MAC10",
    "WMENU_MSG_UMP",
    "WMENU_MSG_CLARI",
    "WMENU_MSG_KRIEG",
    "WMENU_MSG_AK47",
    "WMENU_MSG_M4A1",
    "WMENU_MSG_AUG",
    "WMENU_MSG_SCOUT",
    "WMENU_MSG_AWP",
    "WMENU_MSG_CTAUTO",
    "WMENU_MSG_TAUTO",
    "WMENU_MSG_GALIL",
    "WMENU_MSG_PARA",
    "WMENU_MSG_PAMMO",
    "WMENU_MSG_SAMMO",
    "WMENU_MSG_KEV",
    "WMENU_MSG_KEVHELM",
    "WMENU_MSG_FLASH",
    "WMENU_MSG_HENADE",
    "WMENU_MSG_SNADE",
    "WMENU_MSG_DKIT",
    "WMENU_MSG_NVG",
    "WMENU_MSG_SHIELD",
    "WMENU_MSG_ALL",
    "WMENU_MSG_M3SET",
    "WMENU_MSG_MP5SET",
    "WMENU_MSG_CLARISET",
    "WMENU_MSG_GALILSET",
    "WMENU_MSG_M4A1SET",
    "WMENU_MSG_AK47SET",
    "WMENU_MSG_KRIEGSET",
    "WMENU_MSG_AUGSET",
    "WMENU_MSG_PARASET",
    "WMENU_MSG_SCOUTSET",
    "WMENU_MSG_AUTOSET",
    "WMENU_MSG_AWPSET",
    "WMENU_MSG_NADESET"
}