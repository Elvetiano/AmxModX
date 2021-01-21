////////////////////////////////////////////////////////////////////////////////////////////
//   actions_evil.inc                    Version 1.51                       Date: AUG/01/2006
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

#if defined _UAIO_EVILACTIONS_INCLUDED
  #endinput
#endif
#define _UAIO_EVILACTIONS_INCLUDED

//     ______________________________________________
//    /          Action Routines Section             \_____________
//___/        (Enables Individual Commands)           \ Type: Evil \________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    ______________
//___/ ActionBanP() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Permanent Ban on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionBanP( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionBanP' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteInstCmd( aCmdArgs[0], CMDTYPE_EVIL, TASK_E_BAN_P, "E_CMD_PBAN", "InitBanP", "ACTION_E_PBAN" )
    return PLUGIN_HANDLED
}
//    ______________
//___/ ActionBanT() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Temporary Ban on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionBanT( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionBanT' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteInstCmd( aCmdArgs[0], CMDTYPE_EVIL, TASK_E_BAN_T, "E_CMD_TBAN", "InitBanT", "ACTION_E_TBAN", "ACTION_MINUTES" )
    return PLUGIN_HANDLED
}
//    ______________
//___/ ActionKick() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Kick Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionKick( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionKick' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteInstCmd( aCmdArgs[0], CMDTYPE_EVIL, TASK_E_KICK, "E_CMD_KICK", "InitKick", "ACTION_E_KICK" )
    return PLUGIN_HANDLED
}
//    ______________
//___/ ActionSlap() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Slap Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionSlap( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionSlap' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteInstCmd( aCmdArgs[0], CMDTYPE_EVIL, TASK_E_SLAP, "E_CMD_SLAP", "InitSlap", "ACTION_E_SLAP", "ACTION_HEALTH" )
    return PLUGIN_HANDLED
}
//    _______________
//___/ ActionBslap() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Bitch-Slap Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionBslap( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionBslap' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteInstCmd( aCmdArgs[0], CMDTYPE_EVIL, TASK_E_BSLAP, "E_CMD_BSLAP", "InitBslap", "ACTION_E_BSLAP", "ACTION_TIMES" )
    return PLUGIN_HANDLED
}
//    ______________
//___/ ActionSlay() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Slay Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionSlay( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionSlay' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteInstCmd( aCmdArgs[0], CMDTYPE_EVIL, TASK_E_SLAY, "E_CMD_SLAY", "InitSlay", "ACTION_E_SLAY" )
    return PLUGIN_HANDLED
}
//    ______________
//___/ ActionBury() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Bury Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionBury( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionBury' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteTogCmd( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_BURY, TASK_E_BURY, "E_CMD_BURY", "InitBury", "ACTION_E_BURY1", "ACTION_E_BURY2" )
    return PLUGIN_HANDLED
}
//    _____________
//___/ ActionGag() \________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Gag Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionGag( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionGag' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_GAG, TASK_E_GAG, "E_CMD_GAG", "InitGag", "ReactionGag", "ACTION_E_GAG1", "ACTION_E_GAG2" )
    return PLUGIN_HANDLED
}
//    ______________
//___/ ActionWarn() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Warning Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionWarn( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionWarn' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteInstCmd( aCmdArgs[0], CMDTYPE_EVIL, TASK_E_WARN, "E_CMD_WARN", "InitWarn", "ACTION_E_WARN" )
    return PLUGIN_HANDLED
}
//    ________________
//___/ ActionBlanks() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Blank-Bullets Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionBlanks( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionBlanks' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_BLANKS, TASK_E_BLANKS, "E_CMD_BLANKS", "InitBlanks", "ReactionBlanks", "ACTION_E_BLANKS1", "ACTION_E_BLANKS2" )
    return PLUGIN_HANDLED
}
//    ______________
//___/ ActionFire() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Fire Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionFire( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionFire' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_FIRE, TASK_E_FIRE, "E_CMD_FIRE", "InitFire", "ReactionFire", "ACTION_E_FIRE1", "ACTION_E_FIRE2" )
    return PLUGIN_HANDLED
}
//    ________________
//___/ ActionPoison() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Poison Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionPoison( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionPoison' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_POISON, TASK_E_POISON, "E_CMD_POISON", "InitPoison", "ReactionPoison", "ACTION_E_POISON1", "ACTION_E_POISON2" )
    return PLUGIN_HANDLED
}
//    ________________
//___/ ActionRocket() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Human Rocket Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionRocket( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionRocket' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteInstCmd( aCmdArgs[0], CMDTYPE_EVIL, TASK_E_ROCKET, "E_CMD_ROCKET", "InitRocket", "ACTION_E_ROCKET" )
    return PLUGIN_HANDLED
}
//    _______________
//___/ ActionStrip() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Strip-Weapons Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionStrip( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionStrip' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteInstCmd( aCmdArgs[0], CMDTYPE_EVIL, TASK_E_STRIP, "E_CMD_STRIP", "InitStrip", "ACTION_E_STRIP" )
    return PLUGIN_HANDLED
}
//    __________________
//___/ ActionBlackout() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Screen Black-out Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionBlackout( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionBlackout' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_BLACK, TASK_E_BLACK, "E_CMD_BLACKOUT", "InitBlack", "ReactionBlack", "ACTION_E_BLACKOUT1", "ACTION_E_BLACKOUT2" )
    return PLUGIN_HANDLED
}
//    _______________
//___/ ActionShake() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Screen-Shake Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionShake( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionShake' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteInstCmd( aCmdArgs[0], CMDTYPE_EVIL, TASK_E_SHAKE, "E_CMD_SHAKE", "InitShake", "ACTION_E_SHAKE" )
    return PLUGIN_HANDLED
}
//    __________________
//___/ ActionNameLock() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Name-Lock Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionNameLock( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionNameLock' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_NLOCK, TASK_E_NLOCK, "E_CMD_NLOCK", _, "ReactionNlock", "ACTION_E_NLOCK1", "ACTION_E_NLOCK2" )
    return PLUGIN_HANDLED
}
//    _______________
//___/ ActionNoBuy() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Disables Buying Items for a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionNoBuy( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionNoBuy' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_NOBUY, TASK_E_NOBUY, "E_CMD_BLOCK", _, "ReactionNoBuy", "ACTION_E_BLOCK1", "ACTION_E_BLOCK2" )
    return PLUGIN_HANDLED
}
//    _________________
//___/ ActionPTrails() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Sets Player Trails on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionPTrails( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionPTrails' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_PTRAILS, TASK_E_PTRAILS, "E_CMD_PTRAILS", "InitPTrails", "ReactionPTrails", "ACTION_E_PTRAILS1", "ACTION_E_PTRAILS2" )
    return PLUGIN_HANDLED
}
//    _________________
//___/ ActionGTrails() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Sets Grenade Trails on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionGTrails( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionGTrails' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_GTRAILS, TASK_E_GTRAILS,  "E_CMD_GTRAILS", _, "ReactionGTrails", "ACTION_E_GTRAILS1", "ACTION_E_GTRAILS2" )
    return PLUGIN_HANDLED
}
//    _________________
//___/ ActionWTrails() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Sets Weapon Trails (Tracers) on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionWTrails( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionWTrails' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_WTRAILS, TASK_E_WTRAILS, "E_CMD_WTRAILS", _, "ReactionWTrails", "ACTION_E_WTRAILS1", "ACTION_E_WTRAILS2" )
    return PLUGIN_HANDLED
}
//    _______________
//___/ ActionDrugs() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Sets Drugs on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionDrugs( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionDrugs' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_DRUGS, TASK_E_DRUGS, "E_CMD_DRUGS", "InitDrugs", "ReactionDrugs", "ACTION_E_DRUGS1", "ACTION_E_DRUGS2" )
    return PLUGIN_HANDLED
}
//    _________________
//___/ ActionCrazyCH() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Sets Crazy Crosshairs on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionCrazyCH( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionCrazyCH' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_CRAZYCH, TASK_E_CRAZYCH, "E_CMD_CRAZYCH", "InitCrosshair", "ReactionCrosshair", "ACTION_E_CRAZYCH1", "ACTION_E_CRAZYCH2" )
    return PLUGIN_HANDLED
}
//
//     ______________________________________________
//    /           Init Routines Section              \_____________
//___/       (Initializes Individual Commands)        \ Type: Evil \________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    ____________
//___/ InitBanP() \_________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Permanently Bans an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitBanP( aCmdArgs[] )
{
    new szUserInfo[STR_T], szCmd[STR_S]
    if( get_cvar_num( "sv_uaio_ban_ip" ) )
    {
        get_user_ip( aCmdArgs[0], szUserInfo, STR_T-1, 1 )
        format( szCmd, STR_S-1, "addip ^"0^" ^"%s^";wait;writeip", szUserInfo )
    }else
    {
        get_user_authid( aCmdArgs[0], szUserInfo, STR_T-1 )
        format( szCmd, STR_S-1, "banid ^"0^" ^"%s^" kick;wait;writeid", szUserInfo )
    }

    #if defined UAIO_DEBUG_MODE
        client_print( 0, print_chat, szCmd )
    #else
        server_cmd( szCmd )
    #endif
    return PLUGIN_HANDLED
}
//    ____________
//___/ InitBanT() \_________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Temporarily Bans an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitBanT( aCmdArgs[] )
{
    new szUserInfo[STR_T], szCmd[STR_S]
    if( get_cvar_num( "sv_aio_ban_ip" ) )
    {
        get_user_ip( aCmdArgs[0], szUserInfo, STR_T-1, 1 )
        format( szCmd, STR_S-1, "addip ^"%d^" ^"%s^";wait;writeip", aCmdArgs[1], szUserInfo )
    }else
    {
        get_user_authid( aCmdArgs[0], szUserInfo, STR_T-1 )
        format( szCmd, STR_S-1, "banid ^"%d^" ^"%s^" kick;wait;writeid", aCmdArgs[1], szUserInfo )
    }

    #if defined UAIO_DEBUG_MODE
        client_print( 0, print_chat, szCmd )
    #else
        server_cmd( szCmd )
    #endif
    return PLUGIN_HANDLED
}
//    ____________
//___/ InitKick() \_________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Kicks an Individual Player off the Server, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitKick( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( 0, print_chat, "kick #%d", get_user_userid( aCmdArgs[0] ) )
    #else
        server_cmd( "kick #%d", get_user_userid( aCmdArgs[0] ) )
    #endif
    return PLUGIN_HANDLED
}
//    ____________
//___/ InitSlap() \_________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Slaps an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitSlap( aCmdArgs[] )
{
    user_slap( aCmdArgs[0], aCmdArgs[1] )
    return PLUGIN_HANDLED
}
//    _____________
//___/ InitBslap() \________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Bitch-Slaps an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitBslap( aCmdArgs[] )
{
    if( is_user_alive( aCmdArgs[0] ) && (aCmdArgs[1]-- > 0) )
    {
        user_slap( aCmdArgs[0], clamp( get_cvar_num(  "sv_uaio_bslap_dmg" ), 0, 10 ) )
        set_task( 0.1, "InitBslap", TASK_COMMON + TASK_E_BSLAP + aCmdArgs[0], aCmdArgs, 2 )
    }
    return PLUGIN_HANDLED
}
//    ____________
//___/ InitSlay() \_________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Slays an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitSlay( aCmdArgs[] )
{
    user_kill( aCmdArgs[0] )
    return PLUGIN_HANDLED
}
//    ____________
//___/ InitBury() \_________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Buries an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitBury( aCmdArgs[] )
{
    new iOrigin[3]
    get_user_origin( aCmdArgs[0], iOrigin )
    if( aCmdArgs[1] == 0 )
    {
        iOrigin[2] += 40
        UAIO_RemoveEffect( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_BURY )
    }else
    {
        iOrigin[2] -= 30
        UAIO_SetEffect( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_BURY )
    }
    set_user_origin( aCmdArgs[0], iOrigin )
    return PLUGIN_HANDLED
}
//    ___________
//___/ InitGag() \__________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Gags an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitGag( aCmdArgs[] )
{
    set_speak( aCmdArgs[0], SPEAK_MUTED )
    return PLUGIN_HANDLED
}
//    ____________
//___/ InitWarn() \_________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Warns an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitWarn( aCmdArgs[] )
{
    new szTitle[STR_T], szTitleML[STR_T]
    format( szTitleML, STR_T-1, "%L", LANG_PLAYER, "E_CMD_WARN" )
    format( szTitle, STR_T-1, "%s %s -- %s", PLUGIN_MOD, PLUGIN_NAME, szTitleML )
    show_motd( aCmdArgs[0], g_szFileWarn, szTitle )
    return PLUGIN_HANDLED
}
//    ______________
//___/ InitBlanks() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Live-Ammo from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitBlanks( aCmdArgs[] )
{
    set_user_hitzones( aCmdArgs[0], 0, 0 )
    return PLUGIN_HANDLED
}
//    ____________
//___/ InitFire() \_________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Burns an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitFire( aCmdArgs[] )
{
    UAIO_IgnitePlayer( aCmdArgs )
    UAIO_IgniteEffects( aCmdArgs )
    return PLUGIN_HANDLED
}
//    ______________
//___/ InitPoison() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Poisons an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitPoison( aCmdArgs[] )
{
    UAIO_PoisonLoop( aCmdArgs )
    return PLUGIN_HANDLED
}
//    ______________
//___/ InitRocket() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Launches an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitRocket( aCmdArgs[] )
{
    emit_sound( aCmdArgs[0], CHAN_WEAPON, g_szSndRocket1, 1.0, ATTN_NORM, 0, PITCH_NORM )
    set_user_maxspeed( aCmdArgs[0], 0.01 )
    set_user_gravity( aCmdArgs[0], -0.50 )
    client_cmd( aCmdArgs[0], "+jump;wait;wait;-jump" )
    emit_sound( aCmdArgs[0], CHAN_VOICE, g_szSndRocket2, 1.0, 0.5, 0, PITCH_NORM )
    UAIO_RocketEffects( aCmdArgs )
    return PLUGIN_HANDLED
}
//    _____________
//___/ InitStrip() \________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Strips an Individual Players Weapons, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitStrip( aCmdArgs[] )
{
    UAIO_StripWeapons( aCmdArgs[0] )
    return PLUGIN_HANDLED
}
//    _____________
//___/ InitBlack() \________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Blinds an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitBlack( aCmdArgs[] )
{
    new iArgs[7] = {9000, 1000, 5, 0, 0, 0, 255}
    new szColor[STR_T], szColors[3][5]
    get_cvar_string( "sv_uaio_blackout_color", szColor, STR_T-1 )
    UAIO_ExplodeString( szColors, 3, szColor, 4, ' ' )

    for( new i = 0; i < 3; i++ )
        iArgs[i+3] = str_to_num( szColors[i] )
    UAIO_FadeScreen( aCmdArgs[0], iArgs )

    return PLUGIN_HANDLED
}
//    _____________
//___/ InitShake() \________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Shakes an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitShake( aCmdArgs[] )
{
    UAIO_ShakeScreen( aCmdArgs[0] )
    return PLUGIN_HANDLED
}
//    _______________
//___/ InitPTrails() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Enables Movement Trails on an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitPTrails( aCmdArgs[] )
{
    UAIO_TrailLoop( aCmdArgs )
    return PLUGIN_HANDLED
}
//    _____________
//___/ InitDrugs() \________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Drugs an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitDrugs( aCmdArgs[] )
{
    UAIO_DrugsLoop( aCmdArgs )
    return PLUGIN_HANDLED
}
//    __________________
//___/ InitCrossshair() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts Crazy Crosshairs on an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitCrosshair( aCmdArgs[] )
{
    UAIO_CrosshairLoop( aCmdArgs )
    return PLUGIN_HANDLED
}
//
//     ______________________________________________
//    /         Reaction Routines Section            \_____________
//___/        (Disables Individual Commands)          \ Type: Evil \________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    _______________
//___/ ReactionGag() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Ungags an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionGag( aCmdArgs[] )
{
    client_print( aCmdArgs[0], print_chat, "%L", LANG_PLAYER, "REACTION_E_GAG", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_GAG )
    set_speak( aCmdArgs[0], SPEAK_NORMAL )
    return PLUGIN_HANDLED
}
//    __________________
//___/ ReactionBlanks() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Returns Live-Ammo to an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionBlanks( aCmdArgs[] )
{
    client_print( aCmdArgs[0], print_chat, "%L", LANG_PLAYER, "REACTION_E_BLANKS", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_BLANKS )
    set_user_hitzones( aCmdArgs[0], 0, 255 )
    return PLUGIN_HANDLED
}
//    ________________
//___/ ReactionFire() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Extinguishes an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionFire( aCmdArgs[] )
{
    if( is_user_alive( aCmdArgs[0] ) && UAIO_HasEffect( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_FIRE ) )
        client_print( aCmdArgs[0], print_chat, "%L", LANG_PLAYER, "REACTION_E_FIRE", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_FIRE )
    return PLUGIN_HANDLED
}
//    __________________
//___/ ReactionPoison() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Cures an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionPoison( aCmdArgs[] )
{
    if( is_user_alive( aCmdArgs[0] ) && UAIO_HasEffect( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_POISON ) )
        client_print( aCmdArgs[0], print_chat, "%L", LANG_PLAYER, "REACTION_E_POISON", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_POISON )
    return PLUGIN_HANDLED
}
//    _________________
//___/ ReactionBlack() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Blindness from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionBlack( aCmdArgs[] )
{
    client_print( aCmdArgs[0], print_chat, "%L", LANG_PLAYER, "REACTION_E_BLACKOUT", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_BLACK )
    new iArgs[7] = {9000, 1000, 2, 0, 0, 0, 0}
    UAIO_FadeScreen( aCmdArgs[0], iArgs )
    return PLUGIN_HANDLED
}
//    _________________
//___/ ReactionNlock() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Unlocks Name of an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionNlock( aCmdArgs[] )
{
    client_print( aCmdArgs[0], print_chat, "%L", LANG_PLAYER, "REACTION_E_NLOCK", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_NLOCK )
    return PLUGIN_HANDLED
}
//    _________________
//___/ ReactionNoBuy() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Permits an Individual Player to Buy, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionNoBuy( aCmdArgs[] )
{
    client_print( aCmdArgs[0], print_chat, "%L", LANG_PLAYER, "REACTION_E_BLOCK", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_NOBUY )
    return PLUGIN_HANDLED
}
//    ___________________
//___/ ReactionPTrails() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Movement Trails from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionPTrails( aCmdArgs[] )
{
    client_print( aCmdArgs[0], print_chat, "%L", LANG_PLAYER, "REACTION_E_PTRAILS", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_PTRAILS )
    UAIO_KillTrail( aCmdArgs[0] )
    return PLUGIN_HANDLED
}
//    ___________________
//___/ ReactionGTrails() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Grenade Trails from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionGTrails( aCmdArgs[] )
{
    client_print( aCmdArgs[0], print_chat, "%L", LANG_PLAYER, "REACTION_E_GTRAILS", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_GTRAILS )
    return PLUGIN_HANDLED
}
//    ___________________
//___/ ReactionWTrails() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Weapon Trails from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionWTrails( aCmdArgs[] )
{
    client_print( aCmdArgs[0], print_chat, "%L", LANG_PLAYER, "REACTION_E_WTRAILS", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_WTRAILS )
    return PLUGIN_HANDLED
}
//    _________________
//___/ ReactionDrugs() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Bad Drugs from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionDrugs( aCmdArgs[] )
{
    client_print( aCmdArgs[0], print_chat, "%L", LANG_PLAYER, "REACTION_E_DRUGS", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_DRUGS )
    UAIO_ResetFOV( aCmdArgs[0] )
    return PLUGIN_HANDLED
}
//    _____________________
//___/ ReactionCrosshair() \________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Crazy Crosshairs from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionCrosshair( aCmdArgs[] )
{
    client_print( aCmdArgs[0], print_chat, "%L", LANG_PLAYER, "REACTION_E_CRAZYCH", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( aCmdArgs[0], CMDTYPE_EVIL, UAIO_E_CRAZYCH )
    client_cmd( aCmdArgs[0], "exec uaio_backup.cfg" )
    return PLUGIN_HANDLED
}
