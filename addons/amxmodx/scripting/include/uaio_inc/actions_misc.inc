////////////////////////////////////////////////////////////////////////////////////////////
//   actions_misc.inc                   Version 1.51                       Date: AUG/01/2006
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

#if defined _UAIO_MISCACTIONS_INCLUDED
  #endinput
#endif
#define _UAIO_MISCACTIONS_INCLUDED

//     ______________________________________________
//    /          Action Routines Section             \_____________
//___/        (Enables Individual Commands)           \ Type: Misc \________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    _____________
//___/ ActionMap() \________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionMap( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Task-Action: 'ActionMap' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteMapCmd( aCmdArgs[0], CMDTYPE_MISC, TASK_M_MAP, "InitMap" )
    return PLUGIN_HANDLED
}
//    ________________
//___/ ActionHealth() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionHealth( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Task-Action: 'ActionHealth' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteInstCmd( aCmdArgs[0], CMDTYPE_MISC, TASK_M_HEALTH, "M_CMD_HP", "InitHealth", "ACTION_M_HEAL", "ACTION_HEALTH" )
    return PLUGIN_HANDLED
}
//    _______________
//___/ ActionArmor() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionArmor( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Task-Action: 'ActionArmor' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteInstCmd( aCmdArgs[0], CMDTYPE_MISC, TASK_M_ARMOR, "M_CMD_AP", "InitArmor", "ACTION_M_ARMOR", "ACTION_ARMOR" )
    return PLUGIN_HANDLED
}
//    ______________
//___/ ActionCash() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionCash( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Task-Action: 'ActionCash' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteInstCmd( aCmdArgs[0], CMDTYPE_MISC, TASK_M_CASH, "M_CMD_CASH", "InitCash", "ACTION_SETWITH", "ACTION_CASH" )
    return PLUGIN_HANDLED
}
//    ______________
//___/ ActionTeam() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionTeam( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Task-Action: 'ActionTeam' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteTeamCmd( aCmdArgs[0], "InitTeam" )
    return PLUGIN_HANDLED
}
//    _______________
//___/ ActionModel() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionModel( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Task-Action: 'ActionModel' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteModelCmd( aCmdArgs[0], "InitModel" )
    return PLUGIN_HANDLED
}
//    _______________
//___/ ActionFrags() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionFrags( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Task-Action: 'ActionFrags' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteInstCmd( aCmdArgs[0], CMDTYPE_MISC, TASK_M_FRAG, "M_CMD_FRAG", "InitFrags", "ACTION_M_FRAGS", "ACTION_FRAGS" )
    return PLUGIN_HANDLED
}
//    ________________
//___/ ActionDeaths() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionDeaths( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Task-Action: 'ActionDeaths' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteInstCmd( aCmdArgs[0], CMDTYPE_MISC, TASK_M_DEATH, "M_CMD_DEATH", "InitDeaths", "ACTION_M_DEATHS", "ACTION_DEATHS" )
    return PLUGIN_HANDLED
}
//    ________________
//___/ ActionWeapon() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionWeapon( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Task-Action: 'ActionWeapon' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteInstCmd( aCmdArgs[0], CMDTYPE_MISC, TASK_M_WEAPON, "M_CMD_WEAPON", "InitWeapon", "ACTION_SETWITH" )
    return PLUGIN_HANDLED
}
//    _________________
//___/ ActionRecruit() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts a Recruit Info MOTD Command on a Player or Group of Players.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionRecruit( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Task-Action: 'ActionRecruit' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {EVIL} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteInstCmd( aCmdArgs[0], CMDTYPE_MISC, TASK_M_RECRUIT, "M_CMD_RECRUIT", "InitRecruit", "ACTION_M_RECRUIT" )
    return PLUGIN_HANDLED
}
//    _______________
//___/ ActionStack() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionStack( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Task-Action: 'ActionStack' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteInstCmd( aCmdArgs[0], CMDTYPE_MISC, TASK_M_STACK, "M_CMD_STACK", "InitStack", "ACTION_M_STACK1", "ACTION_M_STACK2" )
    return PLUGIN_HANDLED
}
//    ______________
//___/ ActionGlow() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionGlow( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Task-Action: 'ActionGlow' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteGlowCmd( aCmdArgs[0], "InitGlow" )
    return PLUGIN_HANDLED
}
//    _______________
//___/ ActionCExec() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionCExec( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Task-Action: 'ActionCExec' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteExecCmd( aCmdArgs[0], UAIO_M_CEXEC, "M_CMD_CEXEC" )
    return PLUGIN_HANDLED
}
//    _______________
//___/ ActionSExec() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionSExec( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Task-Action: 'ActionSExec' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteExecCmd( aCmdArgs[0], UAIO_M_SEXEC, "M_CMD_SEXEC" )
    return PLUGIN_HANDLED
}
//    ________________
//___/ ActionRevive() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionRevive( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Task-Action: 'ActionRevive' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteInstCmd( aCmdArgs[0], CMDTYPE_MISC, TASK_M_REVIVE, "M_CMD_REVIVE", "InitRevive", "ACTION_REVIVED" )
    return PLUGIN_HANDLED
}
//    _________________
//___/  ActionArena()  \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionArena( aCmdArgs[] )
{
    new id = aCmdArgs[0]

    new szWeapons[AR_MAX_GUNS][STR_M] , szAction[STR_S] , szState[STR_T] , szArena[STR_T]

    format(szArena , STR_T-1 , "%L" , LANG_PLAYER , "V_CMD_ARENA")

    new szCmdArgs[2][STR_M]
    argbreak(g_szCmdArgs[id-1] , szCmdArgs[0] , STR_S-1 , szCmdArgs[1] , STR_S-1)
    if( (str_to_num(szCmdArgs[0]) == (-1)) || (str_to_num(szCmdArgs[1]) == (-1)))
    {
        if(!g_bArenaEnabled)
        {
            client_print( aCmdArgs[0] , print_console , "%L" , LANG_PLAYER, "EXEC_ARENA_CMD2" , PLUGIN_MOD )
            client_print( aCmdArgs[0] , print_console , "uaio_arena %L" , LANG_PLAYER , "USAGE_ARENA")
            return PLUGIN_HANDLED
        }
        format(szState , STR_T-1 , "%L" , LANG_PLAYER , "MODE_DISABLED")
        format(szAction , STR_S-1 , "%L" , LANG_PLAYER , "EXEC_ARENA_CMD3" , szArena , szState)
        UAIO_AnnounceAction( id , szAction )
        UAIO_EndArena( )
    }
    else
    {
        if(g_bArenaEnabled)
        {
            client_print( aCmdArgs[0] , print_console , "%L" , LANG_PLAYER, "EXEC_ARENA_CMD1" , PLUGIN_MOD )
            client_print( aCmdArgs[0] , print_console , "uaio_arena %L" , LANG_PLAYER , "USAGE_ARENA")
            return PLUGIN_HANDLED
        }
        if(!str_to_num(szCmdArgs[0]))
            g_bArenaGrenades = false

        g_iWepCount = (1 + UAIO_ExplodeString( szWeapons , AR_MAX_GUNS, szCmdArgs[1] , STR_M-1 , ' ' ))
        for( new i = 0 ; i < AR_MAX_GUNS ; i++ )
        {
            g_iArenaCustom[i] = UAIO_WeaponConst( str_to_num(szWeapons[i]) )
        }
        format(szState , STR_T-1 , "%L" , LANG_PLAYER , "MODE_ENABLED")
        format(szAction , STR_S-1 , "%L" , LANG_PLAYER , "EXEC_ARENA_CMD3" , szArena , szState)
        UAIO_AnnounceAction( id , szAction )
        UAIO_StartArena( )
    }
    return PLUGIN_HANDLED
}
//    ________________
//___/  ActionMotd()  \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionMotd( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Task-Action: 'ActionMotd' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {MISC} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteInstCmd( aCmdArgs[0], CMDTYPE_MISC, TASK_M_MOTD, "M_CMD_MOTD", "InitMotd", "ACTION_M_MOTD", "ACTION_MOTD" )
    return PLUGIN_HANDLED
}
//
//     ______________________________________________
//    /           Init Routines Section              \_____________
//___/       (Initializes Individual Commands)        \ Type: Misc \________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    ___________
//___/ InitMap() \__________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitMap( aCmdArgs[] )
{
    server_cmd( "changelevel %s", aCmdArgs )
    return PLUGIN_HANDLED
}
//    ______________
//___/ InitHealth() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitHealth( aCmdArgs[] )
{
    set_user_health( aCmdArgs[0], aCmdArgs[1] )
    return PLUGIN_HANDLED
}
//    _____________
//___/ InitArmor() \________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitArmor( aCmdArgs[] )
{
    set_user_armor( aCmdArgs[0], aCmdArgs[1] )
    return PLUGIN_HANDLED
}
//    ____________
//___/ InitCash() \_________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitCash( aCmdArgs[] )
{
    UAIO_SetMoney( aCmdArgs[0], aCmdArgs[1] )
    return PLUGIN_HANDLED
}
//    ____________
//___/ InitTeam() \_________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitTeam( aCmdArgs[] )
{
    switch( aCmdArgs[1] + 1 )
    {
        case TEAM_T: cs_set_user_team( aCmdArgs[0], CS_TEAM_T, CS_T_TERROR )
        case TEAM_CT: cs_set_user_team( aCmdArgs[0], CS_TEAM_CT, CS_CT_GSG9 )
        case TEAM_SPEC: cs_set_user_team( aCmdArgs[0], CS_TEAM_SPECTATOR )
    }
    return PLUGIN_HANDLED
}
//    _____________
//___/ InitModel() \________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitModel( aCmdArgs[] )
{
    if( aCmdArgs[1] < 4 )
    {
        UAIO_SetModel( aCmdArgs[0], aCmdArgs[1], TEAM_CT )
    }else if( aCmdArgs[1] < 9 )
    {
        UAIO_SetModel( aCmdArgs[0], aCmdArgs[1]-4, TEAM_T )
    }
    else if( aCmdArgs[1] == 9 )
    {
        UAIO_SetModel( aCmdArgs[0], aCmdArgs[1] , TEAM_NONE )
    }
    return PLUGIN_HANDLED
}
//    _____________
//___/ InitFrags() \________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitFrags( aCmdArgs[] )
{
    UAIO_AddFrags( aCmdArgs[0], aCmdArgs[1] )
    return PLUGIN_HANDLED
}
//    ______________
//___/ InitDeaths() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitDeaths( aCmdArgs[] )
{
    UAIO_AddDeaths( aCmdArgs[0], aCmdArgs[1] )
    return PLUGIN_HANDLED
}
//    _______________
//___/ InitRecruit() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Gives Recruit Info to an Individual Player, as a result of Related Action Command Above.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitRecruit( aCmdArgs[] )
{
    new szTitle[STR_T], szTemp[STR_T]
    format( szTemp, STR_T-1, "%L", LANG_PLAYER, "M_CMD_RECRUIT" )
    format( szTitle, STR_T-1, "%s %s -- %s", PLUGIN_MOD, PLUGIN_NAME, szTemp )
    show_motd( aCmdArgs[0], g_szFileRecruit, szTitle )
    return PLUGIN_HANDLED
}
//    _____________
//___/ InitStack() \________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitStack( aCmdArgs[] )
{
    UAIO_StackPlayers( aCmdArgs[0], aCmdArgs[1] )
    return PLUGIN_HANDLED
}
//    ____________
//___/ InitGlow() \_________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitGlow( aCmdArgs[] )
{
    if( aCmdArgs[1] == 1000 ) // Turn Off
        set_user_rendering( aCmdArgs[0], kRenderFxGlowShell, 0,0,0, kRenderTransAlpha, 255 )
    else if( aCmdArgs[1] == MAX_COLORS-1 )
        set_user_rendering( aCmdArgs[0], kRenderFxGlowShell, random_num( 0, 255 ), random_num( 0, 255 ), random_num( 0, 255 ), kRenderNormal, 30 )
    else
        set_user_rendering( aCmdArgs[0], kRenderFxGlowShell, g_iColors[aCmdArgs[1]][0], g_iColors[aCmdArgs[1]][1], g_iColors[aCmdArgs[1]][2], kRenderNormal, 30 )

    return PLUGIN_HANDLED
}
//    ______________
//___/ InitRevive() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitRevive( aCmdArgs[] )
{
    UAIO_RevivePlayer( aCmdArgs )
    return PLUGIN_HANDLED
}
//    ______________
//___/ InitWeapon() \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitWeapon( aCmdArgs[] )
{
    new id = aCmdArgs[0]
    new iWeaponCode = aCmdArgs[1]
    new iRem, iType
    
    if( iWeaponCode < 80 )
    {
        iRem = (iWeaponCode % 10)
        iType = ((iWeaponCode-iRem) / 10)
    }else
    {
        iRem = (iWeaponCode - 80)
        iType = 8
    }
    
    switch( iType )
    {
        case 1: UAIO_GiveWeapon( id, iRem - 1 )
        case 2: UAIO_GiveWeapon( id, OFFSET_SHOTGUN + iRem - 1 )
        case 3: UAIO_GiveWeapon( id, OFFSET_SMG + iRem - 1 )
        case 4: UAIO_GiveWeapon( id, OFFSET_RIFLE + iRem - 1 )
        case 5: UAIO_GiveWeapon( id, OFFSET_MACHINE + iRem - 1 )
        case 6:
        {
            if( iRem == 1 ) UAIO_GivePAmmo( id )
            else UAIO_GiveSAmmo( id )
        }
        case 7: UAIO_GiveItem( id, iRem - 1 )
        case 8: UAIO_GiveExtra( id, iRem - 1 )
    }
    
    return PLUGIN_HANDLED
}
//    _____________
//___/ InitArena() \________________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitArena( aCmdArgs[] )
{
    if( aCmdArgs[1] )
    {
        client_print( 0, print_chat, "%L", LANG_PLAYER, "ACTION_ARENA_BEGIN" )
        g_iOldFreezeTime = get_cvar_num( "mp_freezetime" )
        server_cmd( "mp_freezetime 1" )
    }
    else
    {
        client_print( 0, print_chat, "%L", LANG_PLAYER, "ACTION_ARENA_END" )
        server_cmd( "mp_freezetime %d", g_iOldFreezeTime )
    }
    server_cmd( "sv_restartround 3" )
    server_exec()
    return
}
//    ______________
//___/  InitMotd()  \_______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitMotd( aCmdArgs[] )
{
    new szMotd[STR_M] , szTitle[STR_T]
    new szBase[STR_M] , szCmdArgs[2][STR_S]
    UAIO_ExplodeString( szCmdArgs , 2 , g_szCmdArgs[aCmdArgs[0]-1] , STR_T-1 , ' ')
    get_configsdir(szBase , STR_M-1)
    format(szMotd , STR_M-1 , "%s/uaio/%s.htm" ,szBase, szCmdArgs[1])
    if(!file_exists(szMotd))
        add(szMotd , STR_M-1 , "l")
    if(!file_exists(szMotd))
    {
        #if defined UAIO_DEBUG_MODE
            client_print( aCmdArgs[0], print_chat, "%s {MISC} Task-Init: 'InitMotd' Called!", PLUGIN_MOD )
            client_print( aCmdArgs[0], print_chat, "%s {MISC} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
            client_print( aCmdArgs[0], print_chat, "%s {MISC} File '%s' Not Found." , PLUGIN_MOD , szMotd)
        #endif
        return
    }
    format( szTitle, STR_T-1, "%s %s -- %s", PLUGIN_MOD, PLUGIN_NAME, szCmdArgs[1] )
    show_motd(aCmdArgs[0] , szMotd , szTitle)
    return
}