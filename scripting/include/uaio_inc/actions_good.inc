////////////////////////////////////////////////////////////////////////////////////////////
//   actions_good.inc                    Version 1.51                       Date: AUG/01/2006
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

#if defined _UAIO_GOODACTIONS_INCLUDED
  #endinput
#endif
#define _UAIO_GOODACTIONS_INCLUDED

//     ______________________________________________
//    /          Action Routines Section             \_____________
//___/        (Enables Individual Commands)           \ Type: Good \________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    _____________
//___/ ActionGod() \________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a God-Mode Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionGod( aCmdArgs[] ) // aCmdArgs[0] = Admin ID
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Task-Action: 'ActionGod' Called", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    // Execute "Duration Command" (common.inc)
    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_GOOD, UAIO_G_GOD, TASK_G_GOD, "G_CMD_GOD", "InitGod", "ReactionGod", "ACTION_G_GOD1", "ACTION_G_GOD2" )
    return PLUGIN_HANDLED
}
//    ______________
//___/ ActionGrav() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Low-Gravity Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionGrav( aCmdArgs[] ) // aCmdArgs[0] = Admin ID
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Task-Action: 'ActionGrav' Called", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    // Execute "Duration Command" (common.inc)
    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_GOOD, UAIO_G_GRAV, TASK_G_GRAV, "G_CMD_GRAV", "InitGrav", "ReactionGrav", "ACTION_G_GRAV1", "ACTION_G_GRAV2" )
    return PLUGIN_HANDLED
}
//    ________________
//___/ ActionNoclip() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a No-Clip Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionNoclip( aCmdArgs[] ) // aCmdArgs[0] = Admin ID
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Task-Action: 'ActionNoclip' Called", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    // Execute "Duration Command" (common.inc)
    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_GOOD, UAIO_G_NOCLIP, TASK_G_NOCLIP, "G_CMD_NOCLIP", "InitNoclip", "ReactionNoclip", "ACTION_G_NOCLIP1", "ACTION_G_NOCLIP2" )
    return PLUGIN_HANDLED
}
//    _______________
//___/ ActionTurbo() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Turbo-Speed Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionTurbo( aCmdArgs[] ) // aCmdArgs[0] = Admin ID
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Task-Action: 'ActionTurbo' Called", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    // Execute "Duration Command" (common.inc)
    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_GOOD, UAIO_G_TURBO, TASK_G_TURBO, "G_CMD_TURBO", "InitTurbo", "ReactionTurbo", "ACTION_G_TURBO1", "ACTION_G_TURBO2" )
    return PLUGIN_HANDLED
}
//    ________________
//___/ ActionSilent() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Silent-Mode Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionSilent( aCmdArgs[] ) // aCmdArgs[0] = Admin ID
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Task-Action: 'ActionSilent' Called", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    // Execute "Duration Command" (common.inc)
    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_GOOD, UAIO_G_SILENT, TASK_G_SILENT, "G_CMD_SILENT", _, "ReactionSilent", "ACTION_G_SILENT1", "ACTION_G_SILENT2" )
    return PLUGIN_HANDLED
}
//    _______________
//___/ ActionInvis() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts an Invisibility Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionInvis( aCmdArgs[] ) // aCmdArgs[0] = Admin ID
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Task-Action: 'ActionInvis' Called", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    // Execute "Duration Command" (common.inc)
    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_GOOD, UAIO_G_INVIS, TASK_G_INVIS, "G_CMD_INVIS", "InitInvis", "ReactionInvis", "ACTION_G_INVIS1", "ACTION_G_INVIS2" )
    return PLUGIN_HANDLED
}
//    _____________
//___/ ActionSpy() \________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Spy-Mode Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionSpy( aCmdArgs[] ) // aCmdArgs[0] = Admin ID
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Task-Action: 'ActionSpy' Called", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    // Execute "Duration Command" (common.inc)
    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_GOOD, UAIO_G_SPY, TASK_G_SPY, "G_CMD_SPY", "InitSpy", "ReactionSpy", "ACTION_G_SPY1", "ACTION_G_SPY2" )
    return PLUGIN_HANDLED
}
//    _________________
//___/ ActionHENades() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts an Infinite HE Grenades Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionHENades( aCmdArgs[] ) // aCmdArgs[0] = Admin ID
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Task-Action: 'ActionHENades' Called", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    // Execute "Duration Command" (common.inc)
    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_GOOD, UAIO_G_NADES, TASK_G_NADES, "G_CMD_HENADES", "InitNades", "ReactionHENades", "ACTION_G_HENADES1", "ACTION_G_HENADES2" )
    return PLUGIN_HANDLED
}
//    _________________
//___/ ActionFBNades() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts an Infinite Flashbang Grenades Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionFBNades( aCmdArgs[] ) // aCmdArgs[0] = Admin ID
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Task-Action: 'ActionFBNades' Called", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    // Execute "Duration Command" (common.inc)
    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_GOOD, UAIO_G_FBANGS, TASK_G_FBANGS, "G_CMD_FLASHES", "InitNades", "ReactionFBNades", "ACTION_G_FLASH1", "ACTION_G_FLASH2" )
    return PLUGIN_HANDLED
}
//    _________________
//___/ ActionSMNades() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts an Infinite Smoke Grenades Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionSMNades( aCmdArgs[] ) // aCmdArgs[0] = Admin ID
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Task-Action: 'ActionSMNades' Called", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    // Execute "Duration Command" (common.inc)
    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_GOOD, UAIO_G_SMOKE, TASK_G_SMOKE, "G_CMD_SNADES", "InitNades", "ReactionSMNades", "ACTION_G_SMOKE1", "ACTION_G_SMOKE2" )
    return PLUGIN_HANDLED
}
//    ______________
//___/ ActionAmmo() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts an Infinite Ammo Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionAmmo( aCmdArgs[] ) // aCmdArgs[0] = Admin ID
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Task-Action: 'ActionAmmo' Called", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    // Execute "Duration Command" (common.inc)
    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_GOOD, UAIO_G_AMMO, TASK_G_AMMO, "G_CMD_AMMO", _, "ReactionAmmo", "ACTION_G_AMMO1", "ACTION_G_AMMO2" )
    return PLUGIN_HANDLED
}
//    _____________
//___/ ActionEye() \________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts an All-Seeing-Eye Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionEye( aCmdArgs[] ) // aCmdArgs[0] = Admin ID
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Task-Action: 'ActionEye' Called", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    // Execute "Duration Command" (common.inc)
    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_GOOD, UAIO_G_EYE, TASK_G_EYE, "G_CMD_EYE", _, "ReactionEye", "ACTION_G_EYE1", "ACTION_G_EYE2" )
    return PLUGIN_HANDLED
}
//    _______________
//___/ ActionBcash() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Bonus Cash for Kill Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionBcash( aCmdArgs[] ) // aCmdArgs[0] = Admin ID
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Task-Action: 'ActionBcash' Called", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    // Execute "Duration Command" (common.inc)
    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_GOOD, UAIO_G_BCASH, TASK_G_BCASH, "G_CMD_BCASH", _, "ReactionBcash", "ACTION_G_BCASH1", "ACTION_G_BCASH2" )
    return PLUGIN_HANDLED
}
//    _______________
//___/ ActionIcash() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts an Inifinte Cash Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionIcash( aCmdArgs[] ) // aCmdArgs[0] = Admin ID
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Task-Action: 'ActionIcash' Called", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    // Execute "Duration Command" (common.inc)
    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_GOOD, UAIO_G_ICASH, TASK_G_ICASH, "G_CMD_ICASH", "InitIcash", "ReactionIcash", "ACTION_G_ICASH1", "ACTION_G_ICASH2" )
    return PLUGIN_HANDLED
}
//    ________________
//___/ ActionMirror() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Mirror Damage Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionMirror( aCmdArgs[] ) // aCmdArgs[0] = Admin ID
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Task-Action: 'ActionMirror' Called", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    // Execute "Duration Command" (common.inc)
    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_GOOD, UAIO_G_MIRROR, TASK_G_MIRROR, "G_CMD_MIRROR", _, "ReactionMirror", "ACTION_G_MIRROR1", "ACTION_G_MIRROR2" )
    return PLUGIN_HANDLED
}
//    ___________________
//___/ ActionTrueArmor() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a True Armor Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionTrueArmor( aCmdArgs[] ) // aCmdArgs[0] = Admin ID
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Task-Action: 'ActionTrueArmor' Called", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    // Execute "Duration Command" (common.inc)
    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_GOOD, UAIO_G_TRUEAP, TASK_G_TRUEAP, "G_CMD_TRUEAP", _, "ReactionTrueArmor", "ACTION_G_TRUEAP1", "ACTION_G_TRUEAP2" )
    return PLUGIN_HANDLED
}
//    _________________
//___/ ActionDiveKit() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Diving Kit Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionDiveKit( aCmdArgs[] ) // aCmdArgs[0] = Admin ID
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Task-Action: 'ActionDiveKit' Called", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    // Execute "Duration Command" (common.inc)
    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_GOOD, UAIO_G_DIVER, TASK_G_DIVER, "G_CMD_DIVER", _, "ReactionDiveKit", "ACTION_G_DIVER1", "ACTION_G_DIVER2" )
    return PLUGIN_HANDLED
}
//    ________________
//___/ ActionShades() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Sun Glasses Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionShades( aCmdArgs[] ) // aCmdArgs[0] = Admin ID
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Task-Action: 'ActionShades' Called", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    // Execute "Duration Command" (common.inc)
    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_GOOD, UAIO_G_SHADES, TASK_G_SHADES, "G_CMD_SHADES", "InitShades", "ReactionShades", "ACTION_G_SHADES1", "ACTION_G_SHADES2" )
    return PLUGIN_HANDLED
}
//    ______________
//___/ ActionSeer() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Seer-Mode Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionSeer( aCmdArgs[] ) // aCmdArgs[0] = Admin ID
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Task-Action: 'ActionSeer' Called", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {GOOD} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    // Execute "Duration Command" (common.inc)
    ExecuteDurCmd( aCmdArgs[0], CMDTYPE_GOOD, UAIO_G_SEER, TASK_G_SEER, "G_CMD_SEER", "InitSeer", "ReactionSeer", "ACTION_G_SEER1", "ACTION_G_SEER2" )
    return PLUGIN_HANDLED
}
//
//     ______________________________________________
//    /           Init Routines Section              \_____________
//___/       (Initializes Individual Commands)        \ Type: Good \________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    ___________
//___/ InitGod() \__________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Grants God-Mode to an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitGod( aCmdArgs[] )
{
    set_user_godmode( aCmdArgs[0], 1 )
    return PLUGIN_HANDLED
}
//    ____________
//___/ InitGrav() \_________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Grants Low-Gravity to an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitGrav( aCmdArgs[] )
{
    set_user_gravity( aCmdArgs[0], g_fGravity[1] )
    return PLUGIN_HANDLED
}
//    ______________
//___/ InitNoclip() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Grants No-Clip to an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitNoclip( aCmdArgs[] )
{
    set_user_noclip( aCmdArgs[0], 1 )
    return PLUGIN_HANDLED
}
//    _____________
//___/ InitTurbo() \________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Grants Turbo-Speed to an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitTurbo( aCmdArgs[] )
{
    new iTarget = aCmdArgs[0]
    new iSpeed = get_cvar_num( "sv_uaio_turbo_speed" )

    //client_cmd( iTarget, "cl_forwardspeed %d", iSpeed )
    g_fSpeeds[iTarget-1] = get_user_maxspeed( iTarget )
    set_user_maxspeed( iTarget, float(iSpeed) )
    //engclient_cmd( iTarget, "weapon_knife" )
    UAIO_SpeedLoop( aCmdArgs[0] )

    return PLUGIN_HANDLED
}
//    _____________
//___/ InitInvis() \________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Grants Invisibility to an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitInvis( aCmdArgs[] )
{
    //set_user_rendering( aCmdArgs[0], kRenderFxNone, 0,0,0, kRenderTransTexture, 1 )
    set_user_rendering( aCmdArgs[0], kRenderFxGlowShell, 0,0,0, kRenderTransAlpha, 1 )
    return PLUGIN_HANDLED
}
//    ___________
//___/ InitSpy() \__________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Grants Spy-Mode to an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitSpy( aCmdArgs[] )
{
    new iTarget = aCmdArgs[0]
    if( get_user_team( iTarget ) == TEAM_T )
        UAIO_SetModel( iTarget, random_num(0,3), TEAM_CT )
    else
        UAIO_SetModel( iTarget, random_num(0,3), TEAM_T )
    return PLUGIN_HANDLED
}
//    _____________
//___/ InitNades() \________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Grants Infinite Nades to an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitNades( aCmdArgs[] )
{
    UAIO_GrenadeLoop( aCmdArgs )
    return PLUGIN_HANDLED
}
//    _____________
//___/ InitIcash() \________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Grants Inifite Cash to an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitIcash( aCmdArgs[] )
{
    UAIO_SetMoney( aCmdArgs[0], clamp( get_cvar_num( "sv_uaio_max_icash" ), 100, 16000 ) )
    return PLUGIN_HANDLED
}
//    ______________
//___/ InitShades() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Grants Sunn Glasses to an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitShades( aCmdArgs[] )
{
    UAIO_ShadesLoop( aCmdArgs )
    return PLUGIN_HANDLED
}
//    ____________
//___/ InitSeer() \_________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Grants Seer-Mode to an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitSeer( aCmdArgs[] )
{
    UAIO_SeerLoop( aCmdArgs )
    return PLUGIN_HANDLED
}
//
//     ______________________________________________
//    /         Reaction Routines Section            \_____________
//___/        (Disables Individual Commands)          \ Type: Good \________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    _______________
//___/ ReactionGod() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes God-Mode from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionGod( aCmdArgs[] )
{
    new iTarget = aCmdArgs[0]
    client_print( iTarget, print_chat, "%L", LANG_PLAYER, "REACTION_G_GOD", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( iTarget, CMDTYPE_GOOD, UAIO_G_GOD )
    if( is_user_alive( iTarget ) ) set_user_godmode( iTarget, 0 )
    return PLUGIN_HANDLED
}
//    ________________
//___/ ReactionGrav() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Low-Gravity from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionGrav( aCmdArgs[] )
{
    new iTarget = aCmdArgs[0]
    client_print( iTarget, print_chat, "%L", LANG_PLAYER, "REACTION_G_GRAV", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( iTarget, CMDTYPE_GOOD, UAIO_G_GRAV )
    if( is_user_alive( iTarget ) ) set_user_gravity( iTarget, g_fGravity[0] )
    return PLUGIN_HANDLED
}
//    __________________
//___/ ReactionNoclip() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes No-Clip from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionNoclip( aCmdArgs[] )
{
    new iTarget = aCmdArgs[0]
    client_print( iTarget, print_chat, "%L", LANG_PLAYER, "REACTION_G_NOCLIP", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( iTarget, CMDTYPE_GOOD, UAIO_G_NOCLIP )
    if( is_user_alive( iTarget ) ) set_user_noclip( iTarget, 0 )
    return PLUGIN_HANDLED
}
//    _________________
//___/ ReactionTurbo() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Turbo-Speed from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionTurbo( aCmdArgs[] )
{
    new iTarget = aCmdArgs[0]
    client_print( iTarget, print_chat, "%L", LANG_PLAYER, "REACTION_G_TURBO", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( iTarget, CMDTYPE_GOOD, UAIO_G_TURBO )
    return PLUGIN_HANDLED
}
//    __________________
//___/ ReactionSilent() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Silent-Mode from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionSilent( aCmdArgs[] )
{
    new iTarget = aCmdArgs[0]
    client_print( iTarget, print_chat, "%L", LANG_PLAYER, "REACTION_G_SILENT", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( iTarget, CMDTYPE_GOOD, UAIO_G_SILENT )
    return PLUGIN_HANDLED
}
//    _________________
//___/ ReactionInvis() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Invisibility from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionInvis( aCmdArgs[] )
{
    new iTarget = aCmdArgs[0]
    client_print( iTarget, print_chat, "%L", LANG_PLAYER, "REACTION_G_INVIS", PLUGIN_MOD, PLUGIN_NAME )
    if( is_user_alive( iTarget ) ) 
        set_user_rendering( iTarget, kRenderFxGlowShell, 0,0,0, kRenderTransAlpha, 255 )
    //set_user_rendering( iTarget, kRenderFxNone, 255,255,255, kRenderNormal, 255 )
    UAIO_RemoveEffect( iTarget, CMDTYPE_GOOD, UAIO_G_INVIS )
    return PLUGIN_HANDLED
}
//    _______________
//___/ ReactionSpy() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Spy-Mode from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionSpy( aCmdArgs[] )
{
    new iTarget = aCmdArgs[0]
    client_print( iTarget, print_chat, "%L", LANG_PLAYER, "REACTION_G_SPY", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_SetModel( iTarget, 0, UAIO_NULL )
    UAIO_RemoveEffect( iTarget, CMDTYPE_GOOD, UAIO_G_SPY )
    return PLUGIN_HANDLED
}
//    ___________________
//___/ ReactionHENades() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Infinite HE Nades from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionHENades( aCmdArgs[] )
{
    new iTarget = aCmdArgs[0]
    client_print( iTarget, print_chat, "%L", LANG_PLAYER, "REACTION_G_HENADES", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( iTarget, CMDTYPE_GOOD, UAIO_G_NADES )
    return PLUGIN_HANDLED
}
//    ___________________
//___/ ReactionFBNades() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Infinite Flashbangs from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionFBNades( aCmdArgs[] )
{
    new iTarget = aCmdArgs[0]
    client_print( iTarget, print_chat, "%L", LANG_PLAYER, "REACTION_G_FLASH", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( iTarget, CMDTYPE_GOOD, UAIO_G_FBANGS )
    return PLUGIN_HANDLED
}
//    ___________________
//___/ ReactionSMNades() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Infinite Smoke Grenades from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionSMNades( aCmdArgs[] )
{
    new iTarget = aCmdArgs[0]
    client_print( iTarget, print_chat, "%L", LANG_PLAYER, "REACTION_G_SMOKE", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( iTarget, CMDTYPE_GOOD, UAIO_G_SMOKE )
    return PLUGIN_HANDLED
}
//    ________________
//___/ ReactionAmmo() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Infinite Ammo from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionAmmo( aCmdArgs[] )
{
    new iTarget = aCmdArgs[0]
    client_print( iTarget, print_chat, "%L", LANG_PLAYER, "REACTION_G_AMMO", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( iTarget, CMDTYPE_GOOD, UAIO_G_AMMO )
    return PLUGIN_HANDLED
}
//    _______________
//___/ ReactionEye() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes All-Seeing-Eye from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionEye( aCmdArgs[] )
{
    new iTarget = aCmdArgs[0]
    client_print( iTarget, print_chat, "%L", LANG_PLAYER, "REACTION_G_EYE", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( iTarget, CMDTYPE_GOOD, UAIO_G_EYE )
    return PLUGIN_HANDLED
}
//    _________________
//___/ ReactionBcash() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Bunos Cash from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionBcash( aCmdArgs[] )
{
    new iTarget = aCmdArgs[0]
    client_print( iTarget, print_chat, "%L", LANG_PLAYER, "REACTION_G_BCASH", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( iTarget, CMDTYPE_GOOD, UAIO_G_BCASH )
    return PLUGIN_HANDLED
}
//    _________________
//___/ ReactionIcash() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Infinite Cash from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionIcash( aCmdArgs[] )
{
    new iTarget = aCmdArgs[0]
    client_print( iTarget, print_chat, "%L", LANG_PLAYER, "REACTION_G_ICASH", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( iTarget, CMDTYPE_GOOD, UAIO_G_ICASH )
    return PLUGIN_HANDLED
}
//    __________________
//___/ ReactionMirror() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Mirror Damage from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionMirror( aCmdArgs[] )
{
    new iTarget = aCmdArgs[0]
    client_print( iTarget, print_chat, "%L", LANG_PLAYER, "REACTION_G_MIRROR", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( iTarget, CMDTYPE_GOOD, UAIO_G_MIRROR )
    return PLUGIN_HANDLED
}
//    _____________________
//___/ ReactionTrueArmor() \________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes True Armor from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionTrueArmor( aCmdArgs[] )
{
    new iTarget = aCmdArgs[0]
    client_print( iTarget, print_chat, "%L", LANG_PLAYER, "REACTION_G_TRUEAP", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( iTarget, CMDTYPE_GOOD, UAIO_G_TRUEAP )
    return PLUGIN_HANDLED
}
//    ___________________
//___/ ReactionDiveKit() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Diving Kit from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionDiveKit( aCmdArgs[] )
{
    new iTarget = aCmdArgs[0]
    client_print( iTarget, print_chat, "%L", LANG_PLAYER, "REACTION_G_DIVER", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( iTarget, CMDTYPE_GOOD, UAIO_G_DIVER )
    return PLUGIN_HANDLED
}
//    __________________
//___/ ReactionShades() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Sun Glasses from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionShades( aCmdArgs[] )
{
    new iTarget = aCmdArgs[0]
    client_print( iTarget, print_chat, "%L", LANG_PLAYER, "REACTION_G_SHADES", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( iTarget, CMDTYPE_GOOD, UAIO_G_SHADES )
    return PLUGIN_HANDLED
}
//    ________________
//___/ ReactionSeer() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Seer-Mode from an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionSeer( aCmdArgs[] )
{
    new iTarget = aCmdArgs[0]
    client_print( iTarget, print_chat, "%L", LANG_PLAYER, "REACTION_G_SEER", PLUGIN_MOD, PLUGIN_NAME )
    UAIO_RemoveEffect( iTarget, CMDTYPE_GOOD, UAIO_G_SEER )
    return PLUGIN_HANDLED
}