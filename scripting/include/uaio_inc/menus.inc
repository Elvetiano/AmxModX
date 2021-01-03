////////////////////////////////////////////////////////////////////////////////////////////
//   menus.inc                    Version 1.51                       Date: AUG/01/2006
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

#if defined _UAIO_MENUS_INCLUDED
  #endinput
#endif
#define _UAIO_MENUS_INCLUDED

//    __________________
//___/ ClCmd_UAIOMenu() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Starts the UAIO Menu System.  COMMAND = uaio_menu   ACCESS = UAIO_LVL_USER
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ClCmd_UAIOMenu( id, lvl, cid )
{
    if( !cmd_access( id, lvl, cid, 0 ) )
        return PLUGIN_HANDLED

    if( !UAIO_PluginEnabled( UAIO_NULL ) )
    {
        client_print( id, print_console, "%L", LANG_PLAYER, "PLUGIN_DISABLED", PLUGIN_MOD, PLUGIN_NAME )
        client_print( id, print_chat, "%L", LANG_PLAYER, "PLUGIN_DISABLED", PLUGIN_MOD, PLUGIN_NAME )
        if( access( id, UAIO_LVL_SUPER ) )
            console_print( id, "%L", LANG_PLAYER, "ENABLE_PLUGIN", PLUGIN_MOD, PLUGIN_NAME )
        return PLUGIN_HANDLED
    }

    #if defined UAIO_DEBUG_MENU
        client_print( id, print_console, "^n[DEBUG] ClCmd_UAIOMenu Called! (Menu Started)^n" )
    #endif

    g_iCurrCommand[id-1] = UAIO_NULL
    g_iCurrPlayer[id-1] = UAIO_NULL
    g_iCurrType[id-1] = UAIO_NULL
    g_iSettingsType[id-1] = UAIO_NULL

    if( !g_bIsAdmin[id-1] )
        g_iMenuOrder[id-1] = MO_COMMANDS

    if( g_iMenuOrder[id-1] == MO_PLAYERS )
        Menu_UAIOPlayer( id, g_iMenuPosition[id-1] = 0 )
    else
        Menu_UAIOCommandType( id )

    return PLUGIN_HANDLED
}
//    ___________________
//___/ Menu_UAIOPlayer() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the In-Game Players Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Menu_UAIOPlayer( id, pos )
{
    #if defined UAIO_DEBUG_MENU
        client_print( id, print_console, "^n[DEBUG] Menu_UAIOPlayer Called!" )
        client_print( id, print_console, "^n[DEBUG] [Player:%d][Command:%d][Type:%d]^n", g_iCurrPlayer[id-1], g_iCurrCommand[id-1], g_iCurrType[id-1] )
    #endif

    if( pos < 0 ) return

    g_iCurrPlayer[id-1] = UAIO_NULL

    get_players( g_iMenuPlayers[id-1], g_iMenuPlayersNum[id-1] )

    new i, j, iCurrKey = 0
    new szUserName[STR_T]
    new szMenuBody[MENU_SIZE]
    new iStart = (pos) ? pos * MENU_DISPLAY - 3 : 0

    if( iStart >= g_iMenuPlayersNum[id-1] )
        iStart = pos = g_iMenuPosition[id-1] = 0

    new iLen = format( szMenuBody, MENU_SIZE-1, "\yUAIO Player Menu\R%d/%d^n\w^n", (pos+1), (g_iMenuPlayersNum[id-1] / MENU_DISPLAY + ((g_iMenuPlayersNum[id-1] % MENU_DISPLAY) ? 1 : 0 )) )
    new iEnd = (pos) ? iStart + MENU_DISPLAY : iStart + MENU_DISPLAY - 3
    new iKeys = (1<<9)

    if( iEnd > g_iMenuPlayersNum[id-1] )
        iEnd = g_iMenuPlayersNum[id-1]

    if( !pos )
    {
        iCurrKey += 3
        if( (g_iCurrCommand[id-1] == UAIO_GetBitPosition(UAIO_M_CEXEC)) || (g_iCurrCommand[id-1] == UAIO_GetBitPosition(UAIO_E_BAN_P)) || (g_iCurrCommand[id-1] == UAIO_GetBitPosition(UAIO_E_BAN_T)) )
        {
            iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "\d%L\w", LANG_PLAYER, "MENU_TEAMS" )
        }else
        {
            iKeys |= (1<<0|1<<1|1<<2)
            iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_TEAMS" )
        }
    }

    for( i = iStart; i < iEnd; i++ )
    {
        j = g_iMenuPlayers[id-1][i]
        get_user_name( j, szUserName, STR_T-1 )

        if( (g_iCurrType[id-1] != UAIO_NULL) && UAIO_HasImmunity( j, g_iCurrType[id-1] ) )
        {
            iCurrKey++
            iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "\d%d. %s^n\w", iCurrKey, szUserName )
        }else
        {
            iKeys |= (1<<iCurrKey++)
            iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%d. %s^n", iCurrKey, szUserName )
        }
    }

    if( iEnd != g_iMenuPlayersNum[id-1] )
    {
        if( g_iMenuOrder[id-1] == MO_PLAYERS )
        {
            if( pos )
                format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_MORE_BACK" )
            else
                format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_MORE_EXIT" )
        }else
            format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_MORE_BACK" )
        iKeys |= (1<<8)
    }
    else
    {
        if( g_iMenuOrder[id-1] == MO_PLAYERS )
        {
            if( pos )
                format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_BACK" )
            else
                format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_EXIT" )
        }else
            format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_BACK" )
    }
    show_menu( id, iKeys, szMenuBody )
    return
}
//    ________________________
//___/ Menu_UAIOCommandType() \_____________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Command Types Menu (Vote/Good/Evil/Misc).
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Menu_UAIOCommandType( id )
{
    #if defined UAIO_DEBUG_MENU
        client_print( id, print_console, "^n[DEBUG] Menu_UAIOCommandType Called!" )
        client_print( id, print_console, "^n[DEBUG] [Player:%d][Command:%d][Type:%d]^n", g_iCurrPlayer[id-1], g_iCurrCommand[id-1], g_iCurrType[id-1] )
    #endif

    g_iCurrCommand[id-1] = UAIO_NULL
    g_iCurrType[id-1] = UAIO_NULL
    g_iSettingsType[id-1] = UAIO_NULL
    g_iMenuPosition[id-1] = 0

    new i, iKeys = (1<<9)
    new szMenuBody[MENU_SIZE], szType[STR_T]
    new iLen = format( szMenuBody, MENU_SIZE-1, "\yUAIO Command Types\w^n" )

    if( (g_iCurrPlayer[id-1] != UAIO_NULL) )
    {
        for( i = 0; i < MAX_CMD_TYPES; i++ )
        {
            format( szType, STR_T-1, "%L", LANG_PLAYER, g_szCmdTypeTitles[i] )
            if( UAIO_HasImmunity( g_iCurrPlayer[id-1], i ) )
            {
                iLen += format( szMenuBody[iLen], MENU_SIZE-1-iLen, "\d%L\w", LANG_PLAYER, "MENU_COMMANDS", (i+1), szType )
            }else
            {
                iKeys |= (1<<i)
                iLen += format( szMenuBody[iLen], MENU_SIZE-1-iLen, "%L", LANG_PLAYER, "MENU_COMMANDS", (i+1), szType )
            }
        }
    }else
    {
        for( i = 0; i < MAX_CMD_TYPES; i++ )
        {
            format( szType, STR_T-1, "%L", LANG_PLAYER, g_szCmdTypeTitles[i] )
            if( g_iAdminCmdBits[id-1][i] < 1 )
            {
                iLen += format( szMenuBody[iLen], MENU_SIZE-1-iLen, "\d%L\w", LANG_PLAYER, "MENU_COMMANDS", (i+1), szType )
            }else
            {
                iKeys |= (1<<i)
                iLen += format( szMenuBody[iLen], MENU_SIZE-1-iLen, "%L", LANG_PLAYER, "MENU_COMMANDS", (i+1), szType )
            }
        }
    }
    if( g_iMenuOrder[id-1] == MO_PLAYERS )
        format( szMenuBody[iLen], MENU_SIZE-1-iLen, "^n%L", id, "MENU_BACK" )
    else
        format( szMenuBody[iLen], MENU_SIZE-1-iLen, "^n%L", id, "MENU_EXIT" )

    show_menu( id, iKeys, szMenuBody )

    return
}
//    ____________________
//___/ Menu_UAIOCommand() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Commands Menu According to Command Type.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Menu_UAIOCommand( id, pos )
{
    #if defined UAIO_DEBUG_MENU
        client_print( id, print_console, "^n[DEBUG] Menu_UAIOCommand Called!" )
        client_print( id, print_console, "^n[DEBUG] [Player:%d][Command:%d][Type:%d]^n", g_iCurrPlayer[id-1], g_iCurrCommand[id-1], g_iCurrType[id-1] )
    #endif

    g_iCurrCommand[id-1] = UAIO_NULL

    switch( g_iCurrType[id-1] )
    {
        case CMDTYPE_VOTE: UAIO_VoteCmdMenu( id, pos )
        case CMDTYPE_GOOD: UAIO_GoodCmdMenu( id, pos )
        case CMDTYPE_EVIL: UAIO_EvilCmdMenu( id, pos )
        case CMDTYPE_MISC: UAIO_MiscCmdMenu( id, pos )
    }
    return
}
//    ____________________
//___/ UAIO_VoteCmdMenu() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Vote Type Commands Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_VoteCmdMenu( id, pos )
{
    new i, iCurrKey = 0
    new iKeys = (1<<9)
    new iStart, iEnd
    new szMenuBody[MENU_SIZE], szTitle[STR_L]
    new iLen = format( szMenuBody, MENU_SIZE-1, "\yUAIO Command Menu\w^n^n" )

    iStart = pos * MENU_DISPLAY
    iEnd = iStart + MENU_DISPLAY
    if( iEnd > MAX_V_COMMANDS ) iEnd = MAX_V_COMMANDS

    for( i = iStart; i < iEnd; i++ )
    {
        format( szTitle, STR_L-1, "%L", LANG_PLAYER, g_szVCmdTitle[i] )
        if( !UAIO_HasCmdAccess( id, CMDTYPE_VOTE, (1<<i) ) )
        {
            iCurrKey++
            iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "\d%d. %s^n\w", iCurrKey, szTitle )
        }else
        {
            iKeys |= (1<<iCurrKey++)
            iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%d. %s^n", iCurrKey, szTitle )
        }
    }

    if( iEnd != MAX_V_COMMANDS )
    {
        iKeys |= (1<<8)
        format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_MORE_BACK" )
    }else
        format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_BACK" )

    show_menu( id, iKeys, szMenuBody )

    return
}
//    ____________________
//___/ UAIO_GoodCmdMenu() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Good Type Commands Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_GoodCmdMenu( id, pos )
{
    new i, iCurrKey = 0
    new iKeys = (1<<9)
    new iStart, iEnd
    new szMenuBody[MENU_SIZE], szTitle[STR_L]
    new iLen = format( szMenuBody, MENU_SIZE-1, "\yUAIO Command Menu\w^n^n" )

    iStart = pos * MENU_DISPLAY
    iEnd = iStart + MENU_DISPLAY
    if( iEnd > MAX_G_COMMANDS ) iEnd = MAX_G_COMMANDS

    for( i = iStart; i < iEnd; i++ )
    {
        format( szTitle, STR_L-1, "%L", LANG_PLAYER, g_szGCmdTitle[i] )
        if( !UAIO_HasCmdAccess( id, CMDTYPE_GOOD, (1<<i) ) )
        {
            iCurrKey++
            iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "\d%d. %s^n\w", iCurrKey, szTitle )
        }else
        {
            iKeys |= (1<<iCurrKey++)
            iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%d. %s^n", iCurrKey, szTitle )
        }
    }

    if( iEnd != MAX_G_COMMANDS )
    {
        iKeys |= (1<<8)
        format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_MORE_BACK" )
    }else
        format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_BACK" )

    show_menu( id, iKeys, szMenuBody )

    return
}
//    ____________________
//___/ UAIO_EvilCmdMenu() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Evil Type Commands Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_EvilCmdMenu( id, pos )
{
    new i, iCurrKey = 0
    new iKeys = (1<<9)
    new iStart, iEnd
    new szMenuBody[MENU_SIZE], szTitle[STR_L]
    new iLen = format( szMenuBody, MENU_SIZE-1, "\yUAIO Command Menu\w^n^n" )

    iStart = pos * MENU_DISPLAY
    iEnd = iStart + MENU_DISPLAY
    if( iEnd > MAX_E_COMMANDS ) iEnd = MAX_E_COMMANDS

    for( i = iStart; i < iEnd; i++ )
    {
        format( szTitle, STR_L-1, "%L", LANG_PLAYER, g_szECmdTitle[i] )
        if( !UAIO_HasCmdAccess( id, CMDTYPE_EVIL, (1<<i) ) )
        {
            iCurrKey++
            iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "\d%d. %s^n\w", iCurrKey, szTitle )
        }else
        {
            iKeys |= (1<<iCurrKey++)
            iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%d. %s^n", iCurrKey, szTitle )
        }
    }

    if( iEnd != MAX_E_COMMANDS )
    {
        iKeys |= (1<<8)
        format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_MORE_BACK" )
    }else
        format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_BACK" )

    show_menu( id, iKeys, szMenuBody )

    return
}
//    ____________________
//___/ UAIO_MiscCmdMenu() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Misc Type Commands Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_MiscCmdMenu( id, pos )
{
    new i, iCurrKey = 0
    new iKeys = (1<<9)
    new iStart, iEnd
    new szMenuBody[MENU_SIZE], szTitle[STR_L]
    new iLen = format( szMenuBody, MENU_SIZE-1, "\yUAIO Command Menu\w^n^n" )

    iStart = pos * MENU_DISPLAY
    iEnd = iStart + MENU_DISPLAY
    if( iEnd > MAX_M_COMMANDS ) iEnd = MAX_M_COMMANDS

    for( i = iStart; i < iEnd; i++ )
    {
        format( szTitle, STR_L-1, "%L", LANG_PLAYER, g_szMCmdTitle[i] )
        if( !UAIO_HasCmdAccess( id, CMDTYPE_MISC, (1<<i) ) || ((g_iCurrPlayer[id-1] >= 1000) && ((1<<i) & UAIO_M_CEXEC)) )
        {
            iCurrKey++
            iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "\d%d. %s^n\w", iCurrKey, szTitle )
        }else
        {
            iKeys |= (1<<iCurrKey++)
            iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%d. %s^n", iCurrKey, szTitle )
        }
    }

    if( iEnd != MAX_M_COMMANDS )
    {
        iKeys |= (1<<8)
        format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_MORE_BACK" )
    }else
        format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_BACK" )

    show_menu( id, iKeys, szMenuBody )

    return
}
//    _________________
//___/ UAIO_MapsMenu() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Server Maps Menu (From maps.ini or mapcycle.txt).
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_MapsMenu( id, pos )
{
    new szMenuBody[MENU_SIZE]
    new i, iStart, iEnd, iCurrKey = 0
    new iKeys = (1<<9), iLen = format( szMenuBody, MENU_SIZE-1, "\yUAIO Settings Menu\w^n" )

    if( g_bFileError[ERROR_MAPS] )
    {
        iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "ERR_MENU_MAPS", g_szFileMaps )
        format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "^n%L", id, "MENU_BACK" )
    }else
    {
        iStart = pos * MENU_DISPLAY
        iEnd = iStart + MENU_DISPLAY
        if( iEnd > g_iMapCount ) iEnd = g_iMapCount

        for( i = iStart; i < iEnd; i++ )
        {
            iKeys |= (1<<iCurrKey++)
            iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%d. %s^n", iCurrKey, g_szMapNames[i] )
        }

        if( iEnd != g_iMapCount )
        {
            iKeys |= (1<<8)
            format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_MORE_BACK" )
        }else
            format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_BACK" )
    }
    show_menu( id, iKeys, szMenuBody )
    return
}
//    __________________
//___/ UAIO_CvarsMenu() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Command CVARs Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_CvarsMenu( id )
{
    new szSetting[MAX_CMD_CVARS][STR_T]
    new szCvarName[STR_T], szCvarVal[STR_M], szMenuBody[MENU_SIZE]
    new i, iKeys = (1<<9), iLen = format( szMenuBody, MENU_SIZE-1, "\yUAIO Settings Menu\w^n" )

    switch( g_iCurrType[id-1] )
    {
        case CMDTYPE_VOTE: format( szCvarName, STR_T-1, "%s", g_szVCmdCvar[g_iCurrCommand[id-1]] )
        case CMDTYPE_GOOD: format( szCvarName, STR_T-1, "%s", g_szGCmdCvar[g_iCurrCommand[id-1]] )
        case CMDTYPE_EVIL: format( szCvarName, STR_T-1, "%s", g_szECmdCvar[g_iCurrCommand[id-1]] )
        case CMDTYPE_MISC: format( szCvarName, STR_T-1, "%s", g_szMCmdCvar[g_iCurrCommand[id-1]] )
    }

    get_cvar_string( szCvarName, szCvarVal, STR_M-1 )
    UAIO_ExplodeString( szSetting, MAX_CMD_CVARS, szCvarVal, STR_T-1, ' ' )

    for( i = 0; i < MAX_CMD_CVARS; i++ )
    {
        if( szSetting[i][0] != 0 )
        {
            iKeys |= (1<<i)
            iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "^n%d. %s", (i+1), szSetting[i] )
        }else
            break
    }
    format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "^n%L", id, "MENU_BACK" )
    show_menu( id, iKeys, szMenuBody )
    return
}
//    ___________________
//___/ UAIO_WeaponMenu() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Weapons Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_WeaponMenu( id )
{
    new szMenuBody[MENU_SIZE], szWeapon[STR_M]
    new i, iKeys = (1<<9), iLen = format( szMenuBody, (MENU_SIZE-1), "\yUAIO Weapons Menu:\w^n" )
    for( i = 0; i < MO_MAX_MAIN; i++ )
    {
        iKeys |= (1<<i)
        format( szWeapon, STR_M-1, "%L", LANG_PLAYER, g_szWeaponMenuTxt[i] )
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%d. %s^n", (i+1), szWeapon )
    }
    format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L", LANG_PLAYER, "MENU_EXIT" )
    show_menu( id, iKeys, szMenuBody, -1 )
    return
}
//    ___________________
//___/ UAIO_PistolMenu() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Pistols Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_PistolMenu( id )
{
    new szMenuBody[MENU_SIZE], szWeapon[STR_M]
    new i, iKeys = (1<<9), iLen = format( szMenuBody, (MENU_SIZE-1), "\yUAIO Pistols Menu:\w^n" )
    for( i = 0; i < MO_MAX_PISTOL; i++ )
    {
        iKeys |= (1<<i)
        format( szWeapon, STR_M-1, "%L", LANG_PLAYER, g_szPistolMenuTxt[i] )
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%d. %s^n", (i+1), szWeapon )
    }
    format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L", LANG_PLAYER, "MENU_BACK" )
    show_menu( id, iKeys, szMenuBody, -1 )
    return
}
//    ____________________
//___/ UAIO_ShotgunMenu() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Shotguns Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_ShotgunMenu( id )
{
    new szMenuBody[MENU_SIZE], szWeapon[STR_M]
    new i, iKeys = (1<<9), iLen = format( szMenuBody, (MENU_SIZE-1), "\yUAIO Shotguns Menu:\w^n" )
    for( i = 0; i < MO_MAX_SHOTGUN; i++ )
    {
        iKeys |= (1<<i)
        format( szWeapon, STR_M-1, "%L", LANG_PLAYER, g_szShotgunMenuTxt[i] )
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%d. %s^n", (i+1), szWeapon )
    }
    format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L", LANG_PLAYER, "MENU_BACK" )
    show_menu( id, iKeys, szMenuBody, -1 )
    return
}
//    ________________
//___/ UAIO_SmgMenu() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Sub-Machine Guns Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_SmgMenu( id )
{
    new szMenuBody[MENU_SIZE], szWeapon[STR_M]
    new i, iKeys = (1<<9), iLen = format( szMenuBody, (MENU_SIZE-1), "\yUAIO SMGs Menu:\w^n" )
    for( i = 0; i < MO_MAX_SMG; i++ )
    {
        iKeys |= (1<<i)
        format( szWeapon, STR_M-1, "%L", LANG_PLAYER, g_szSmgMenuTxt[i] )
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%d. %s^n", (i+1), szWeapon )
    }
    format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L", LANG_PLAYER, "MENU_BACK" )
    show_menu( id, iKeys, szMenuBody, -1 )
    return
}
//    __________________
//___/ UAIO_RifleMenu() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Rifles Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_RifleMenu( id, pos )
{
    if( pos < 0 ) return

    new i, j = 0, iStart, iEnd, iLen, iKeys = (1<<9)
    new szMenuBody[MENU_SIZE], szWeapon[STR_M]

    iStart = pos * MENU_DISPLAY

    if( iStart >= MO_MAX_RIFLE )
        iStart = pos = g_iWeaponMenuPos[id-1] = 0

    iLen = format( szMenuBody, (MENU_SIZE-1), "\yUAIO Rifles Menu:\R%d/2^n\w^n", pos + 1 )

    iEnd = iStart + MENU_DISPLAY
    if( iEnd > MO_MAX_RIFLE ) iEnd = MO_MAX_RIFLE

    for( i = iStart; i < iEnd; i++ )
    {
        iKeys |= (1<<j++)
        format( szWeapon, STR_M-1, "%L", LANG_PLAYER, g_szRifleMenuTxt[i] )
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%d. %s^n", j, szWeapon )
    }

    if( iEnd != MO_MAX_RIFLE )
    {
        format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L", LANG_PLAYER, "MENU_MORE_BACK" )
        iKeys |= (1<<8)
    }
    else format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L", LANG_PLAYER, "MENU_BACK" )

    show_menu( id, iKeys, szMenuBody, -1 )
    return
}
//    ____________________
//___/ UAIO_MachineMenu() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Machine Guns Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_MachineMenu( id )
{
    new szMenuBody[MENU_SIZE], szWeapon[STR_M]
    new iKeys = (1<<0|1<<9), iLen = format( szMenuBody, (MENU_SIZE-1), "\yUAIO Machine Guns Menu:\w^n" )
    format( szWeapon, STR_M-1, "%L", LANG_PLAYER, g_szMachineMenuTxt )
    iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%d. %s^n", 1, szWeapon )
    format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L", LANG_PLAYER, "MENU_BACK" )
    show_menu( id, iKeys, szMenuBody, -1 )
    return
}
//    __________________
//___/ UAIO_EquipMenu() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Equipment Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_EquipMenu( id )
{
    new szMenuBody[MENU_SIZE], szItem[STR_M]
    new i, iKeys = (1<<9), iLen = format( szMenuBody, (MENU_SIZE-1), "\yUAIO Equipment Menu:\w^n" )
    for( i = 0; i < MO_MAX_EQUIP; i++ )
    {
        iKeys |= (1<<i)
        format( szItem, STR_M-1, "%L", LANG_PLAYER, g_szEquipMenuTxt[i] )
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%d. %s^n", (i+1), szItem )
    }
    format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L", LANG_PLAYER, "MENU_BACK" )
    show_menu( id, iKeys, szMenuBody, -1 )
    return
}
//    __________________
//___/ UAIO_ExtraMenu() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Weapon Sets Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_ExtraMenu( id, pos )
{
    if( pos < 0 ) return

    new i, j = 0, iStart, iEnd, iLen, iKeys = (1<<9)
    new szMenuBody[MENU_SIZE], szItem[STR_M]

    iStart = pos * MENU_DISPLAY

    if( iStart >= MO_MAX_EXTRA )
        iStart = pos = g_iWeaponMenuPos[id-1] = 0

    iLen = format( szMenuBody, (MENU_SIZE-1), "\yUAIO Extras Menu:\R%d/2^n\w^n", pos + 1 )

    iEnd = iStart + MENU_DISPLAY
    if( iEnd > MO_MAX_EXTRA ) iEnd = MO_MAX_EXTRA

    for( i = iStart; i < iEnd; i++ )
    {
        iKeys |= (1<<j++)
        format( szItem, STR_M-1, "%L", LANG_PLAYER, g_szExtraMenuTxt[i] )
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%d. %s^n", j, szItem )
    }

    if( iEnd != MO_MAX_EXTRA )
    {
        format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L", LANG_PLAYER, "MENU_MORE_BACK" )
        iKeys |= (1<<8)
    }
    else format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L", LANG_PLAYER, "MENU_BACK" )

    show_menu( id, iKeys, szMenuBody, -1 )
    return
}
//    _________________
//___/ UAIO_FileMenu() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Client/Server Execute Commands from File Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_FileMenu( id, pos )
{
    new szMenuBody[MENU_SIZE]
    new i, iCount, iStart, iEnd, iCurrKey = 0
    new iKeys = (1<<9), iLen = format( szMenuBody, MENU_SIZE-1, "\yUAIO Settings Menu\w^n" )

    if( ((1<<g_iCurrCommand[id-1]) == UAIO_M_CEXEC) && g_bFileError[ERROR_CEXEC] )
    {
        iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "ERR_MENU_CEXEC" )
        format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "^n%L", id, "MENU_BACK" )
    }
    else if( ((1<<g_iCurrCommand[id-1]) == UAIO_M_SEXEC) && g_bFileError[ERROR_SEXEC] )
    {
        iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "ERR_MENU_SEXEC" )
        format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "^n%L", id, "MENU_BACK" )
    }
    else
    {
        iCount = ((1<<g_iCurrCommand[id-1]) == UAIO_M_CEXEC) ? g_iCExecCount : g_iSExecCount
        iStart = pos * MENU_DISPLAY
        iEnd = iStart + MENU_DISPLAY
        if( iEnd > iCount ) iEnd = iCount

        for( i = iStart; i < iEnd; i++ )
        {
            iKeys |= (1<<iCurrKey++)
            if( (1<<g_iCurrCommand[id-1]) == UAIO_M_CEXEC )
                iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%d. %s^n", iCurrKey, g_szCExecTitles[i] )
            else
                iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%d. %s^n", iCurrKey, g_szSExecTitles[i] )
        }

        if( iEnd != iCount )
        {
            iKeys |= (1<<8)
            format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_MORE_BACK" )
        }else
            format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_BACK" )
    }
    show_menu( id, iKeys, szMenuBody )
    return
}
//    _________________
//___/ UAIO_TeamMenu() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the CS Teams Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_TeamMenu( id )
{
    new szMenuBody[MENU_SIZE]
    new iKeys, iLen = format( szMenuBody, MENU_SIZE-1, "\yUAIO Settings Menu\w^n" )

    iKeys = ((1<<0)|(1<<1)|(1<<2)|(1<<9))
    iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "^n1. %L", id, "TEAM_TITLE2_T" )
    iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "^n2. %L", id, "TEAM_TITLE2_CT" )
    iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "^n3. %L", id, "TEAM_TITLE2_SPEC" )
    format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "^n%L", id, "MENU_BACK" )

    show_menu( id, iKeys, szMenuBody )
    return
}
//    __________________
//___/ UAIO_ModelMenu() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the CS Models Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_ModelMenu( id )
{
    new szMenuBody[MENU_SIZE]
    new i, iKeys = (1<<0|1<<1|1<<2|1<<3|1<<4|1<<5|1<<6|1<<7|1<<8|1<<9)
    new iLen = format( szMenuBody, MENU_SIZE-1, "\yUAIO Settings Menu\w^n" )

    for( i = 0; i < 4; i++ )
        iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "^n%d. %s", (i+1), g_szCTSkins[i] )

    for( i = 0; i < 4; i++ )
        iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "^n%d. %s", (i+5), g_szTSkins[i] )

    iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "^n9. VIP" )
    format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "^n%L", id, "MENU_BACK" )

    show_menu( id, iKeys, szMenuBody )
    return
}
//    _________________
//___/ UAIO_BuryMenu() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Bury-Type Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_BuryMenu( id )
{
    new szMenuBody[MENU_SIZE]
    new iKeys, iLen = format( szMenuBody, MENU_SIZE-1, "\yUAIO Settings Menu\w^n" )

    iKeys = ((1<<0)|(1<<1)|(1<<9))
    iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_UNBURY" )
    iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_BURY" )
    format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "^n%L", id, "MENU_BACK" )

    show_menu( id, iKeys, szMenuBody )
    return
}
//    __________________
//___/ UAIO_StackMenu() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Stack-Type Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_StackMenu( id )
{
    new szMenuBody[MENU_SIZE]
    new iKeys, iLen = format( szMenuBody, MENU_SIZE-1, "\yUAIO Settings Menu\w^n" )

    iKeys = ((1<<0)|(1<<1)|(1<<9))
    iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_STACK_T" )
    iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_STACK_F" )
    format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "^n%L", id, "MENU_BACK" )

    show_menu( id, iKeys, szMenuBody )
    return
}
//    ___________________
//___/ UAIO_ToggleMenu() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Toggle On/Off Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_ToggleMenu( id )
{
    new szMenuBody[MENU_SIZE]
    new iKeys, iLen = format( szMenuBody, MENU_SIZE-1, "\yUAIO Settings Menu\w^n" )

    iKeys = ((1<<0)|(1<<1)|(1<<9))
    iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_TOGG_ON" )
    iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "MENU_TOGG_OFF" )
    format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "^n%L", id, "MENU_BACK" )

    show_menu( id, iKeys, szMenuBody )
    return
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    _________________
//___/ Menu_UAIOType() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Handles the Command-Types Menu.  Redirects to Command Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Menu_UAIOType( id, key )
{
    if( key == 9 )
    {
        if( g_iMenuOrder[id-1] == MO_PLAYERS )
            Menu_UAIOPlayer( id, g_iMenuPosition[id-1] = 0 )
        return
    }
    g_iCurrType[id-1] = key
    Menu_UAIOCommand( id, g_iMenuPosition[id-1] = 0 )

    return
}
//    _________________
//___/ Menu_UAIONext() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Handles Command and Players Menus.  Determines which menu to display next.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Menu_UAIONext( id, key )
{
    new iHasPMenu
    if( (g_iMenuOrder[id-1] == MO_PLAYERS) && (g_iCurrPlayer[id-1] == UAIO_NULL) ) // Picked a player 1st
    {
        switch( key )
        {
            case 8: Menu_UAIOPlayer( id, ++g_iMenuPosition[id-1] )
            case 9: Menu_UAIOPlayer( id, --g_iMenuPosition[id-1] )
            default:
            {
                if( !g_iMenuPosition[id-1] && (key < 3) )
                    g_iCurrPlayer[id-1] = 1000 + key
                else
                    g_iCurrPlayer[id-1] = g_iMenuPlayers[id-1][g_iMenuPosition[id-1] * MENU_DISPLAY + key - 3]
                Menu_UAIOCommandType( id )
            }
        }
    }
    else if( (g_iMenuOrder[id-1] == MO_PLAYERS) && (g_iCurrPlayer[id-1] != UAIO_NULL) ) // Picked a command 2nd
    {
        switch( key )
        {
            case 8: Menu_UAIOCommand( id, ++g_iMenuPosition[id-1] )
            case 9:
            {
                if( g_iMenuPosition[id-1] )
                    Menu_UAIOCommand( id, --g_iMenuPosition[id-1] )
                else
                    Menu_UAIOCommandType( id )
            }
            default:
            {
                g_iCurrCommand[id-1] = (g_iMenuPosition[id-1] * MENU_DISPLAY + key)
                Menu_UAIOSettings( id )
            }
        }
    }
    else if( (g_iMenuOrder[id-1] == MO_COMMANDS) && (g_iCurrCommand[id-1] == UAIO_NULL) ) // Picked a command 1st
    {
        switch( key )
        {
            case 8: Menu_UAIOCommand( id, ++g_iMenuPosition[id-1] )
            case 9:
            {
                if( g_iMenuPosition[id-1] )
                    Menu_UAIOCommand( id, --g_iMenuPosition[id-1] )
                else
                    Menu_UAIOCommandType( id )
            }
            default:
            {
                g_iCurrCommand[id-1] = (g_iMenuPosition[id-1] * MENU_DISPLAY + key)

                switch( g_iCurrType[id-1] )
                {
                    case CMDTYPE_VOTE: iHasPMenu = g_iVUsesPMenu[g_iCurrCommand[id-1]]
                    case CMDTYPE_GOOD: iHasPMenu = g_iGUsesPMenu[g_iCurrCommand[id-1]]
                    case CMDTYPE_EVIL: iHasPMenu = g_iEUsesPMenu[g_iCurrCommand[id-1]]
                    case CMDTYPE_MISC: iHasPMenu = g_iMUsesPMenu[g_iCurrCommand[id-1]]
                }
                if( iHasPMenu )
                    Menu_UAIOPlayer( id, g_iMenuPosition[id-1] = 0 )
                else
                    Menu_UAIOSettings( id )
            }
        }
    }
    else if( (g_iMenuOrder[id-1] == MO_COMMANDS) && (g_iCurrCommand[id-1] != UAIO_NULL) ) // Picked a player 2nd
    {
        switch( key )
        {
            case 8: Menu_UAIOPlayer( id, ++g_iMenuPosition[id-1] )
            case 9:
            {
                if( g_iMenuPosition[id-1] )
                    Menu_UAIOPlayer( id, --g_iMenuPosition[id-1] )
                else
                    Menu_UAIOCommandType( id )
            }
            default:
            {
                if( !g_iMenuPosition[id-1] && (key < 3) )
                    g_iCurrPlayer[id-1] = 1000 + key
                else
                    g_iCurrPlayer[id-1] = g_iMenuPlayers[id-1][g_iMenuPosition[id-1] * MENU_DISPLAY + key - 3]
                Menu_UAIOSettings( id )
            }
        }
    }
    return
}
//    _____________________
//___/ Menu_UAIOSettings() \________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Handles All Settings-Type Menus (Issues Command for Instant-Actions)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Menu_UAIOSettings( id )
{
    #if defined UAIO_DEBUG_MENU
        client_print( id, print_console, "^n[DEBUG] Menu_UAIOSettings Called!" )
        client_print( id, print_console, "^n[DEBUG] [Player:%d][Command:%d][Type:%d]^n", g_iCurrPlayer[id-1], g_iCurrCommand[id-1], g_iCurrType[id-1] )
    #endif

    // Get Settings Menu Type
    switch( g_iCurrType[id-1] )
    {
        case CMDTYPE_VOTE: g_iSettingsType[id-1] = g_iVCmdSetFlags[g_iCurrCommand[id-1]]
        case CMDTYPE_GOOD: g_iSettingsType[id-1] = g_iGCmdSetFlags[g_iCurrCommand[id-1]]
        case CMDTYPE_EVIL: g_iSettingsType[id-1] = g_iECmdSetFlags[g_iCurrCommand[id-1]]
        case CMDTYPE_MISC: g_iSettingsType[id-1] = g_iMCmdSetFlags[g_iCurrCommand[id-1]]
    }

    // Display Settings Menu for Type
    switch( g_iSettingsType[id-1] )
    {
        case SM_MAPS:   UAIO_MapsMenu( id, g_iMenuPosition[id-1] = 0 )
        case SM_CVAR:   UAIO_CvarsMenu( id )
        case SM_WEAPON: UAIO_WeaponMenu( id ) //client_cmd( id, "amx_weaponmenu" )
        case SM_FILE:   UAIO_FileMenu( id, g_iMenuPosition[id-1] = 0 )
        case SM_TEAM:   UAIO_TeamMenu( id )
        case SM_MODEL:  UAIO_ModelMenu( id )
        case SM_BURY:   UAIO_BuryMenu( id )
        case SM_STACK:  UAIO_StackMenu( id )
        case SM_TOGGLE: UAIO_ToggleMenu( id )
	case SM_ARENA:	UAIO_ArenaWeaponMenu( id )
        default:
        {
            // Instant Action (No Settings Required)
            if( g_iCurrPlayer[id-1] >= 1000 )
            {
                switch( g_iCurrType[id-1] )
                {
                    case CMDTYPE_VOTE: client_cmd( id, "%s %s", g_szVCmdConsole[g_iCurrCommand[id-1]], g_szVarCmdArgs[g_iCurrPlayer[id-1]-1000] )
                    case CMDTYPE_GOOD: client_cmd( id, "%s %s", g_szGCmdConsole[g_iCurrCommand[id-1]], g_szVarCmdArgs[g_iCurrPlayer[id-1]-1000] )
                    case CMDTYPE_EVIL: client_cmd( id, "%s %s", g_szECmdConsole[g_iCurrCommand[id-1]], g_szVarCmdArgs[g_iCurrPlayer[id-1]-1000] )
                    case CMDTYPE_MISC: client_cmd( id, "%s %s", g_szMCmdConsole[g_iCurrCommand[id-1]], g_szVarCmdArgs[g_iCurrPlayer[id-1]-1000] )
                }
            }else
            {
                switch( g_iCurrType[id-1] )
                {
                    case CMDTYPE_VOTE: client_cmd( id, "%s #%d", g_szVCmdConsole[g_iCurrCommand[id-1]], get_user_userid(g_iCurrPlayer[id-1]) )
                    case CMDTYPE_GOOD: client_cmd( id, "%s #%d", g_szGCmdConsole[g_iCurrCommand[id-1]], get_user_userid(g_iCurrPlayer[id-1]) )
                    case CMDTYPE_EVIL: client_cmd( id, "%s #%d", g_szECmdConsole[g_iCurrCommand[id-1]], get_user_userid(g_iCurrPlayer[id-1]) )
                    case CMDTYPE_MISC: client_cmd( id, "%s #%d", g_szMCmdConsole[g_iCurrCommand[id-1]], get_user_userid(g_iCurrPlayer[id-1]) )
                }
            }

            // Show Menu Again
            if( g_iMenuOrder[id-1] == MO_PLAYERS )
                Menu_UAIOCommandType( id )
            else
                Menu_UAIOPlayer( id, g_iMenuPosition[id-1] = 0 )
        }
    }
    return
}
//    ___________________
//___/ Menu_UAIOAction() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Handles Completion of UAIO Menu System. Issues Command for Non-Instant Actions.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Menu_UAIOAction( id, key )
{
    #if defined UAIO_DEBUG_MENU
        client_print( id, print_console, "^n[DEBUG] Menu_UAIOAction Called!" )
        client_print( id, print_console, "^n[DEBUG] [Player:%d][Command:%d][Type:%d]^n", g_iCurrPlayer[id-1], g_iCurrCommand[id-1], g_iCurrType[id-1] )
    #endif

    new iHasPMenu
    switch( g_iCurrType[id-1] )
    {
        case CMDTYPE_VOTE: iHasPMenu = g_iVUsesPMenu[g_iCurrCommand[id-1]]
        case CMDTYPE_GOOD: iHasPMenu = g_iGUsesPMenu[g_iCurrCommand[id-1]]
        case CMDTYPE_EVIL: iHasPMenu = g_iEUsesPMenu[g_iCurrCommand[id-1]]
        case CMDTYPE_MISC: iHasPMenu = g_iMUsesPMenu[g_iCurrCommand[id-1]]
    }

    if( g_iSettingsType[id-1] == SM_MAPS )
    {
        if( key == 8 )
        {
            UAIO_MapsMenu( id, ++g_iMenuPosition[id-1] )
            return
        }else if( key == 9 )
        {
            if( g_iMenuPosition[id-1] > 0 )
            {
                UAIO_MapsMenu( id, --g_iMenuPosition[id-1] )
            }else
            {
                Menu_UAIOCommandType( id )
            }
            return
        }
    }else if( g_iSettingsType[id-1] == SM_FILE )
    {
        if( key == 8 )
        {
            UAIO_FileMenu( id, ++g_iMenuPosition[id-1] )
            return
        }else if( key == 9 )
        {
            if( g_iMenuPosition[id-1] > 0 )
            {
                UAIO_FileMenu( id, --g_iMenuPosition[id-1] )
            }else
            {
                if( g_iMenuOrder[id-1] == MO_PLAYERS )
                    Menu_UAIOCommandType( id )
                else
                    Menu_UAIOPlayer( id, g_iMenuPosition[id-1] = 0 )
            }
            return
        }
    }else
    {
        if( key == 9 )
        {
            if( g_iMenuOrder[id-1] == MO_PLAYERS )
                Menu_UAIOCommandType( id )
            else
            {
                if( iHasPMenu )
                    Menu_UAIOPlayer( id, g_iMenuPosition[id-1] = 0 )
                else
                    Menu_UAIOCommandType( id )
            }
            return
        }
    }

    new i, iSettingsIdx, iFlags
    new szCommand[STR_T], szCvarVal[STR_S], szTemp[8]

    switch( g_iCurrType[id-1] )
    {
        case CMDTYPE_VOTE:
        {
            format( szCommand, STR_T-1, "%s", g_szVCmdConsole[g_iCurrCommand[id-1]] )
            if( g_iSettingsType[id-1] == SM_CVAR )
                get_cvar_string( g_szVCmdCvar[g_iCurrCommand[id-1]], szCvarVal, STR_S-1 )
        }
        case CMDTYPE_GOOD:
        {
             format( szCommand, STR_T-1, "%s", g_szGCmdConsole[g_iCurrCommand[id-1]] )
             if( g_iSettingsType[id-1] == SM_CVAR )
                get_cvar_string( g_szGCmdCvar[g_iCurrCommand[id-1]], szCvarVal, STR_S-1 )
        }
        case CMDTYPE_EVIL:
        {
             format( szCommand, STR_T-1, "%s", g_szECmdConsole[g_iCurrCommand[id-1]] )
             if( g_iSettingsType[id-1] == SM_CVAR )
                get_cvar_string( g_szECmdCvar[g_iCurrCommand[id-1]], szCvarVal, STR_S-1 )
        }
        case CMDTYPE_MISC:
        {
             format( szCommand, STR_T-1, "%s", g_szMCmdConsole[g_iCurrCommand[id-1]] )
             if( g_iSettingsType[id-1] == SM_CVAR )
                get_cvar_string( g_szMCmdCvar[g_iCurrCommand[id-1]], szCvarVal, STR_S-1 )
        }
    }

    if( g_iSettingsType[id-1] == SM_MAPS )
    {
        iSettingsIdx = g_iMenuPosition[id-1] * MENU_DISPLAY + key
        client_cmd( id, "%s %s", szCommand, g_szMapNames[iSettingsIdx] )

        // Return Directly to Commands Menu (If not Vote Command)
        if( g_iCurrType[id-1] != CMDTYPE_VOTE )
            Menu_UAIOCommandType( id )
        return
    }
    else if( g_iSettingsType[id-1] == SM_CVAR )
    {
        new szSetting[MAX_CMD_CVARS][STR_T]
        UAIO_ExplodeString( szSetting, MAX_CMD_CVARS, szCvarVal, STR_S-1, ' ' )
        if( iHasPMenu )
        {
            if( g_iCurrPlayer[id-1] >= 1000 )
                client_cmd( id, "%s %s %s", szCommand, g_szVarCmdArgs[g_iCurrPlayer[id-1]-1000], szSetting[key] )
            else
                client_cmd( id, "%s #%d %s", szCommand, get_user_userid(g_iCurrPlayer[id-1]), szSetting[key] )
        }
        else
            client_cmd( id, "%s %s", szCommand, szSetting[key] )
    }
    else if( g_iSettingsType[id-1] == SM_FILE )
    {
        iSettingsIdx = g_iMenuPosition[id-1] * MENU_DISPLAY + key

        if( (1<<g_iCurrCommand[id-1]) == UAIO_M_CEXEC )
        {
            iFlags = g_iCExecFlags[iSettingsIdx]
            format( szCommand, STR_T-1, "%s", g_szCExecCmds[iSettingsIdx]  )
        }else
        {
            iFlags = g_iSExecFlags[iSettingsIdx]
            format( szCommand, STR_T-1, "%s", g_szSExecCmds[iSettingsIdx]  )
        }
        if( g_iCurrPlayer[id-1] >= 1000 )
            format( szTemp, 7, "%s", g_szVarCmdArgs[g_iCurrPlayer[id-1]-1000] )
        else
            format( szTemp, 7, "#%d", get_user_userid( g_iCurrPlayer[id-1] ) )
        replace( szCommand, STR_T-1, "{userid}", szTemp )

        if( iFlags & EXEC_SERVER )
            server_cmd( szCommand )
        else if( iFlags & EXEC_ADMIN )
            client_cmd( id, szCommand  )
        else if( iFlags & EXEC_CLIENT )
            client_cmd( g_iCurrPlayer[id-1], "%s", szCommand  )
        else if( iFlags & EXEC_ALLCL )
        {
            get_players( g_iMenuPlayers[id-1], g_iMenuPlayersNum[id-1] )
            for( i = 0; i < g_iMenuPlayersNum[id-1]; i++ )
                client_cmd( g_iMenuPlayers[id-1][i], "%s", szCommand  )
        }
    }
    else if( g_iSettingsType[id-1] == SM_TOGGLE )
    {
        client_cmd( id, "%s %d", szCommand, (key)?0:1 )
    }
    else if( g_iSettingsType[id-1] == SM_MODEL )
    {
        if( g_iCurrPlayer[id-1] >= 1000 )
            client_cmd( id, "%s %s %d", szCommand, g_szVarCmdArgs[g_iCurrPlayer[id-1]-1000], (key + 1) )
        else
            client_cmd( id, "%s #%d %d", szCommand, get_user_userid(g_iCurrPlayer[id-1]), (key + 1) )
    }
    else
    {
        if( iHasPMenu )
        {
            if( g_iCurrPlayer[id-1] >= 1000 )
                client_cmd( id, "%s %s %d", szCommand, g_szVarCmdArgs[g_iCurrPlayer[id-1]-1000], key )
            else
                client_cmd( id, "%s #%d %d", szCommand, get_user_userid(g_iCurrPlayer[id-1]), key )
        }
        else
            client_cmd( id, "%s %d", szCommand, key )
    }

    // Show Menu Again (If not Vote Command)
    if( g_iCurrType[id-1] != CMDTYPE_VOTE )
    {
        if( g_iMenuOrder[id-1] == MO_PLAYERS )
        {
            Menu_UAIOCommandType( id )
        }else
        {
            if( iHasPMenu )
                Menu_UAIOPlayer( id, g_iMenuPosition[id-1] = 0 )
            else
                Menu_UAIOCommandType( id )
        }
    }

    return
}
//     ______________________________________________
//    /        UAIO Arena Weapon Menu System         \_____________
//___/                                                \ Type: Misc \________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//
//    ________________________
//___/ UAIO_ArenaWeaponMenu() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Weapons Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_ArenaWeaponMenu( id )
{
    if( g_iCurrType[id-1] == CMDTYPE_VOTE) g_bArenaVote[id-1] = true

    else g_bArenaVote[id-1] = false

    new szMenuBody[MENU_SIZE], szWeapon[STR_M]
    new i, iKeys = (1<<7)|(1<<9), iLen = format( szMenuBody, (MENU_SIZE-1), "\yUAIO Arena Menu:\w^n" )
    for( i = 0; i < AR_MAX_MAIN; i++ )
    {
        if(!g_bArenaEnabled)
             iKeys |= (1<<i)
        format( szWeapon, STR_M-1, "%L", LANG_PLAYER, g_szArenaMenuTxt[i] )
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%s%d. %s^n", g_bArenaEnabled ? "\d" : "", (i+1), szWeapon )
    }
    iKeys |= (1<<AR_MAX_MAIN)
    iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "^n%d. %L\R\y%L\w^n", (AR_MAX_MAIN+1) , LANG_PLAYER , "ARENA_GRENADES" , LANG_PLAYER , g_bArenaGrenades ? "MODE_ENABLED" : "MODE_DISABLED")
    if(!g_bArenaVote[id-1])
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L" , LANG_PLAYER , g_bArenaEnabled ? "ARENA_END" : "ARENA_START" )
    else
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L" , LANG_PLAYER , g_bArenaEnabled ? "MENU_VOTE_ARENA_END" : "MENU_VOTE_ARENA_START" )
    format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L", LANG_PLAYER, "MENU_EXIT" )
    show_menu( id, iKeys, szMenuBody, -1 )
    return
}
//    ________________________
//___/ UAIO_ArenaPistolMenu() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Pistols Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_ArenaPistolMenu( id )
{
    new szMenuBody[MENU_SIZE], szWeapon[STR_M]
    new szInUse[STR_M]
    new i, iKeys = (1<<7)|(1<<9), iLen = format( szMenuBody, (MENU_SIZE-1), "\yUAIO Arena Pistols Menu:\w^n" )
    for( i = 0; i < AR_MAX_PISTOL; i++ )
    {
	if( (g_iWepCount < AR_MAX_GUNS) || UAIO_IsInArena(g_iPistolConst[i]) && !g_bArenaEnabled)
	        iKeys |= (1<<i)
        format( szWeapon, STR_M-1, "%s%L",( (g_iWepCount < AR_MAX_GUNS) || UAIO_IsInArena(g_iPistolConst[i])) ? "\w" : "\d" , LANG_PLAYER, g_szPistolMenuTxt[i] )
	format( szInUse , STR_M-1 , "%L" , LANG_PLAYER , UAIO_IsInArena( g_iPistolConst[i] ) ? "ARENA_REMOVE" : "ARENA_ADD")
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%s%d. %s\R\y%s\w^n", g_bArenaEnabled ? "\d" : "", (i+1), szWeapon , szInUse)
    }
    if(!g_bArenaVote[id-1])
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L" , LANG_PLAYER , g_bArenaEnabled ? "ARENA_END" : "ARENA_START" )
    else
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L" , LANG_PLAYER , g_bArenaEnabled ? "MENU_VOTE_ARENA_END" : "MENU_VOTE_ARENA_START" )
    format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L", LANG_PLAYER, "MENU_BACK" )
    show_menu( id, iKeys, szMenuBody, -1 )
    return
}
//    _________________________
//___/ UAIO_ArenaShotgunMenu() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Shotguns Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_ArenaShotgunMenu( id )
{
    new szMenuBody[MENU_SIZE], szWeapon[STR_M]
    new szInUse[STR_M]
    new i, iKeys = (1<<7)|(1<<9), iLen = format( szMenuBody, (MENU_SIZE-1), "\yUAIO Arena Shotguns Menu:\w^n" )
    for( i = 0; i < AR_MAX_SHOTGUN; i++ )
    {
        if( (g_iWepCount < AR_MAX_GUNS) || UAIO_IsInArena(g_iShotgunConst[i]) && !g_bArenaEnabled)
	    iKeys |= (1<<i)
        format( szWeapon, STR_M-1, "%s%L",( (g_iWepCount < AR_MAX_GUNS) || UAIO_IsInArena(g_iShotgunConst[i])) ? "\w" : "\d" , LANG_PLAYER, g_szShotgunMenuTxt[i] )
	format( szInUse , STR_M-1 , "%L" , LANG_PLAYER , UAIO_IsInArena( g_iShotgunConst[i] ) ? "ARENA_REMOVE" : "ARENA_ADD")
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%s%d. %s\R\y%s\w^n", g_bArenaEnabled ? "\d" : "", (i+1), szWeapon , szInUse)
    }
    if(!g_bArenaVote[id-1])
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L" , LANG_PLAYER , g_bArenaEnabled ? "ARENA_END" : "ARENA_START" )
    else
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L" , LANG_PLAYER , g_bArenaEnabled ? "MENU_VOTE_ARENA_END" : "MENU_VOTE_ARENA_START" )
    format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L", LANG_PLAYER, "MENU_BACK" )
    show_menu( id, iKeys, szMenuBody, -1 )
    return
}
//    _____________________
//___/ UAIO_ArenaSmgMenu() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Sub-Machine Guns Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_ArenaSmgMenu( id )
{
    new szMenuBody[MENU_SIZE], szWeapon[STR_M]
    new szInUse[STR_M]
    new i, iKeys = (1<<7)|(1<<9), iLen = format( szMenuBody, (MENU_SIZE-1), "\yUAIO Arena SMGs Menu:\w^n" )
    for( i = 0; i < AR_MAX_SMG; i++ )
    {
        if( (g_iWepCount < AR_MAX_GUNS) || UAIO_IsInArena(g_iSmgConst[i]) && !g_bArenaEnabled)
	    iKeys |= (1<<i)
        format( szWeapon, STR_M-1, "%s%L",( (g_iWepCount < AR_MAX_GUNS) || UAIO_IsInArena(g_iSmgConst[i])) ? "\w" : "\d" , LANG_PLAYER, g_szSmgMenuTxt[i] )
	format( szInUse , STR_M-1 , "%L" , LANG_PLAYER , UAIO_IsInArena( g_iSmgConst[i] ) ? "ARENA_REMOVE" : "ARENA_ADD")
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%s%d. %s\R\y%s\w^n", g_bArenaEnabled ? "\d" : "", (i+1), szWeapon , szInUse)
    }
    if(!g_bArenaVote[id-1])
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L" , LANG_PLAYER , g_bArenaEnabled ? "ARENA_END" : "ARENA_START" )
    else
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L" , LANG_PLAYER , g_bArenaEnabled ? "MENU_VOTE_ARENA_END" : "MENU_VOTE_ARENA_START" )
    format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L", LANG_PLAYER, "MENU_BACK" )
    show_menu( id, iKeys, szMenuBody, -1 )
    return
}
//    _______________________
//___/ UAIO_ArenaRifleMenu() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Rifles Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_ArenaRifleMenu( id, pos )
{
    if( pos < 0 ) return

    new i, j = 0, iStart, iEnd, iLen, iKeys = (1<<7)|(1<<9)
    new szMenuBody[MENU_SIZE], szWeapon[STR_M]
    new szInUse[STR_M]

    iStart = pos * AR_RIFLE_DISPLAY

    if( iStart >= AR_MAX_RIFLE )
        iStart = pos = g_iWeaponMenuPos[id-1] = 0

    iLen = format( szMenuBody, (MENU_SIZE-1), "\yUAIO Arena Rifles Menu:\R%d/2^n\w^n", pos + 1 )

    iEnd = iStart + AR_RIFLE_DISPLAY
    if( iEnd > AR_MAX_RIFLE ) iEnd = AR_MAX_RIFLE

    for( i = iStart; i < iEnd; i++ )
    {
        if( (g_iWepCount < AR_MAX_GUNS) || UAIO_IsInArena(g_iRifleConst[i]) && !g_bArenaEnabled)
	    iKeys |= (1<<j++)
        format( szWeapon, STR_M-1, "%s%L",( (g_iWepCount < AR_MAX_GUNS) || UAIO_IsInArena(g_iRifleConst[i])) ? "\w" : "\d" , LANG_PLAYER, g_szRifleMenuTxt[i] )
	format( szInUse , STR_M-1 , "%L" , LANG_PLAYER , UAIO_IsInArena( g_iRifleConst[i] ) ? "ARENA_REMOVE" : "ARENA_ADD")
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%s%d. %s\R\y%s\w^n", g_bArenaEnabled ? "\d" : "", j, szWeapon , szInUse)
    }

    if(!g_bArenaVote[id-1])
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L" , LANG_PLAYER , g_bArenaEnabled ? "ARENA_END" : "ARENA_START" )
    else
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L" , LANG_PLAYER , g_bArenaEnabled ? "MENU_VOTE_ARENA_END" : "MENU_VOTE_ARENA_START" )
    if( iEnd != AR_MAX_RIFLE )
    {
        format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L", LANG_PLAYER, "MENU_MORE_BACK" )
        iKeys |= (1<<8)
    }
    else format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L", LANG_PLAYER, "MENU_BACK" )

    show_menu( id, iKeys, szMenuBody, -1 )
    return
}
//    _________________________
//___/ UAIO_ArenaMachineMenu() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Machine Guns Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_ArenaMachineMenu( id )
{
    new szMenuBody[MENU_SIZE], szWeapon[STR_M]
    new szInUse[STR_M]
    new iKeys = (1<<7)|(1<<9), iLen = format( szMenuBody, (MENU_SIZE-1), "\yUAIO Arena Machine Guns Menu:\w^n" )
    if( (g_iWepCount < AR_MAX_GUNS) || UAIO_IsInArena(g_iMachineConst) && !g_bArenaEnabled)
        iKeys |= (1<<0)
    format( szWeapon, STR_M-1, "%s%L",( (g_iWepCount < AR_MAX_GUNS) || UAIO_IsInArena(g_iMachineConst)) ? "\w" : "\d" , LANG_PLAYER, g_szMachineMenuTxt )
    format( szInUse , STR_M-1 , "%L" , LANG_PLAYER , UAIO_IsInArena( g_iMachineConst ) ? "ARENA_REMOVE" : "ARENA_ADD")
    iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%s%d. %s\R\y%s^n\w", g_bArenaEnabled ? "\d" : "", 1, szWeapon , szInUse)
    if(!g_bArenaVote[id-1])
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L" , LANG_PLAYER , g_bArenaEnabled ? "ARENA_END" : "ARENA_START" )
    else
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L" , LANG_PLAYER , g_bArenaEnabled ? "MENU_VOTE_ARENA_END" : "MENU_VOTE_ARENA_START" )
    format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L", LANG_PLAYER, "MENU_BACK" )
    show_menu( id, iKeys, szMenuBody, -1 )
    return
}
//    _______________________
//___/ UAIO_ArenaEquipMenu() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays the Equipment Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_ArenaEquipMenu( id )
{
    new szMenuBody[MENU_SIZE], szItem[STR_M]
    new szInUse[STR_M]
    new i, iKeys = (1<<7)|(1<<9), iLen = format( szMenuBody, (MENU_SIZE-1), "\yUAIO Arena Equipment Menu:\w^n" )
    for( i = 0; i < AR_MAX_EQUIP; i++ )
    {
        if( g_iWepCount < AR_MAX_GUNS)
	    iKeys |= (1<<i)
        format( szItem, STR_M-1, "%s%L",( (g_iWepCount < AR_MAX_GUNS) || UAIO_IsInArena(g_iEquipConst[i])) ? "\w" : "\d" , LANG_PLAYER, g_szArenaEquipMenuTxt[i] )
	format( szInUse , STR_M-1 , "%L" , LANG_PLAYER , UAIO_IsInArena( g_iEquipConst[i] ) ? "ARENA_REMOVE" : "ARENA_ADD")
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%d. %s\R\y%s^n\w", (i+1), szItem , szInUse)
    }
    if(!g_bArenaVote[id-1])
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L" , LANG_PLAYER , g_bArenaEnabled ? "ARENA_END" : "ARENA_START" )
    else
        iLen += format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L" , LANG_PLAYER , g_bArenaEnabled ? "MENU_VOTE_ARENA_END" : "MENU_VOTE_ARENA_START" )
    format( szMenuBody[iLen], ((MENU_SIZE-1)-iLen), "%L", LANG_PLAYER, "MENU_BACK" )
    show_menu( id, iKeys, szMenuBody, -1 )
    return
}

//    ________________________________
//___/  UAIO Arena Weapon Selections  \__________________________________________________________
//
//    ________________________
//___/ Menu_UAIOArenaWeapon() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Handles Completion of UAIO Arena Weapons Menu - First Page - Weapon Type
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Menu_UAIOArenaWeapon( id, key )
{
    #if defined UAIO_DEBUG_MENU
        client_print( id, print_console, "^n[DEBUG] Menu_UAIOArenaWeapon Called!" )
        client_print( id, print_console, "^n[DEBUG] [Player:%d][Command:%d][Type:%d][Weapon:%d]^n", g_iCurrPlayer[id-1], g_iCurrCommand[id-1], g_iCurrType[id-1], key )
    #endif
    
    // Track which Menu Type was chosen
    g_iWeaponMenuType[id-1] = key

    switch( key )
    {
        case 0: UAIO_ArenaPistolMenu( id )
        case 1: UAIO_ArenaShotgunMenu( id )
        case 2: UAIO_ArenaSmgMenu( id )
        case 3: UAIO_ArenaRifleMenu( id, g_iWeaponMenuPos[id-1] = 0 )
        case 4: UAIO_ArenaMachineMenu( id )
        case AR_MAX_MAIN:
        {
            if(g_bArenaGrenades)
	            g_bArenaGrenades = false
            else
	            g_bArenaGrenades = true

            UAIO_ArenaWeaponMenu( id )
        }
        case 7: 
        {
            if(g_bArenaVote[id-1])
            {
                g_bArenaVote[id-1] = false
                if(g_bArenaEnabled)
	                UAIO_CommenceArenaVote( id , AR_END)
                else
	                UAIO_CommenceArenaVote( id , AR_START)
            }
            else
            {
                if(g_bArenaEnabled)
                    UAIO_EndArena()
                else
                    UAIO_StartArena()
            }
        }
        default: Menu_UAIOCommandType( id )
    }
    return PLUGIN_HANDLED
}
//    _____________________
//___/ Menu_UAIOArenaReg() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Handles Completion of UAIO Arena Weapons Menu - All but Rifles and Extra
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Menu_UAIOArenaReg( id, key )
{
    if( key != 7 && key != 9 )
    switch( g_iWeaponMenuType[id-1] )
    {
        case 0: {
            if(!UAIO_IsInArena(g_iPistolConst[key]) )
	        g_iArenaCustom[g_iWepCount++] = g_iPistolConst[key]
            else
            {
                for(new i = 0 ; i < AR_MAX_GUNS ; i++ )
                {
                    if(g_iArenaCustom[i] == g_iPistolConst[key])
                    {
                        g_iArenaCustom[i] = UAIO_NULL
                        for(new x = i ; x < AR_MAX_GUNS-1 ; x++ )
                            g_iArenaCustom[x] = g_iArenaCustom[x+1]
                        g_iWepCount--
                        break
                    }
                }
            }
            UAIO_ArenaPistolMenu( id )
        }
        case 1: {
            if(!UAIO_IsInArena(g_iShotgunConst[key]) )
	        g_iArenaCustom[g_iWepCount++] = g_iShotgunConst[key]
            else
            {
                for(new i = 0 ; i < AR_MAX_GUNS ; i++ )
                {
                    if(g_iArenaCustom[i] == g_iShotgunConst[key])
                    {
                        g_iArenaCustom[i] = UAIO_NULL
                        for(new x = i ; x < AR_MAX_GUNS-1 ; x++ )
                            g_iArenaCustom[x] = g_iArenaCustom[x+1]
                        g_iWepCount--
                        break
                    }
                }
            }
            UAIO_ArenaShotgunMenu( id )
        }
        case 2: {
            if(!UAIO_IsInArena(g_iSmgConst[key]) )
	        g_iArenaCustom[g_iWepCount++] = g_iSmgConst[key]
            else
            {
                for(new i = 0 ; i < AR_MAX_GUNS ; i++ )
                {
                    if(g_iArenaCustom[i] == g_iSmgConst[key])
                    {
                        g_iArenaCustom[i] = UAIO_NULL
                        for(new x = i ; x < AR_MAX_GUNS-1 ; x++ )
                            g_iArenaCustom[x] = g_iArenaCustom[x+1]
                        g_iWepCount--
                        break
                    }
                }
            }
            UAIO_ArenaSmgMenu( id )
        }
        case 4: {
            if(!UAIO_IsInArena(g_iMachineConst) )
	        g_iArenaCustom[g_iWepCount++] = g_iMachineConst
            else
            {
                for(new i = 0 ; i < AR_MAX_GUNS ; i++ )
                {
                    if(g_iArenaCustom[i] == g_iMachineConst)
                    {
                        g_iArenaCustom[i] = UAIO_NULL
                        for(new x = i ; x < AR_MAX_GUNS-1 ; x++ )
                            g_iArenaCustom[x] = g_iArenaCustom[x+1]
                        g_iWepCount--
                        break
                    }
                }
            }
            UAIO_ArenaMachineMenu( id )
        }
        case 5: {
            if(!UAIO_IsInArena(g_iEquipConst[key]) )
	        g_iArenaCustom[g_iWepCount++] = g_iEquipConst[key]
            else
            {
                for(new i = 0 ; i < AR_MAX_GUNS-1 ; i++ )
                {
                    if(g_iArenaCustom[i] == g_iEquipConst[key])
                    {
                        g_iArenaCustom[i] = UAIO_NULL
                        for(new x = i ; x < AR_MAX_GUNS-1 ; x++ )
                            g_iArenaCustom[x] = g_iArenaCustom[x+1]
                        g_iWepCount--
                        break
                    }
                }
            }
            UAIO_ArenaEquipMenu( id )
        }
    }
    
    switch( key )
    {
        case 7: 
        {
            if(g_bArenaVote[id-1])
            {
                g_bArenaVote[id-1] = false
                if(g_bArenaEnabled)
	                UAIO_CommenceArenaVote( id , AR_END)
                else
	                UAIO_CommenceArenaVote( id , AR_START)
            }
            else
            {
                if(g_bArenaEnabled)
                    UAIO_EndArena()
                else
                    UAIO_StartArena()
            }
        }
        case 9:
        {
            // User wants to go Back to Previous Menu
            UAIO_ArenaWeaponMenu( id )
        }
    }
    return PLUGIN_HANDLED
}
//    _______________________
//___/ Menu_UAIOArenaRifle() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Handles Completion of UAIO Arena Weapons Menu - Rifles
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Menu_UAIOArenaRifle( id, key )
{
    switch( key )
    {
        case 7: 
        {
            if(g_bArenaVote[id-1])
            {
                g_bArenaVote[id-1] = false
                if(g_bArenaEnabled)
	                UAIO_CommenceArenaVote( id , AR_END)
                else
	                UAIO_CommenceArenaVote( id , AR_START)
            }
            else
            {
                if(g_bArenaEnabled)
                    UAIO_EndArena()
                else
                    UAIO_StartArena()
            }
        }
        case 8:
        {
            // User Selected "More..." Option
            UAIO_ArenaRifleMenu( id, ++g_iWeaponMenuPos[id-1] )
        }
        case 9:
        {
            // User Chose to go Back to Previous Menu
            if( g_iWeaponMenuPos[id-1] )
            {
                UAIO_ArenaRifleMenu( id, --g_iWeaponMenuPos[id-1] )
            }else
            {
                UAIO_ArenaWeaponMenu( id )
            }
        }
        default:
        {
            if(!UAIO_IsInArena(g_iRifleConst[g_iWeaponMenuPos[id-1] * AR_RIFLE_DISPLAY + key]) )
	            g_iArenaCustom[g_iWepCount++] = g_iRifleConst[ g_iWeaponMenuPos[id-1] * AR_RIFLE_DISPLAY + key]
            else
            {
                for(new i = 0 ; i < AR_MAX_GUNS-1 ; i++ )
                {
                    if(g_iArenaCustom[i] == g_iRifleConst[g_iWeaponMenuPos[id-1] * AR_RIFLE_DISPLAY + key])
                    {
                        g_iArenaCustom[i] = UAIO_NULL
                        for(new x = i ; x < AR_MAX_GUNS-1 ; x++ )
                            g_iArenaCustom[x] = g_iArenaCustom[x+1]
                        g_iWepCount--
                        break
                    }
                }
            }
            UAIO_ArenaRifleMenu( id, g_iWeaponMenuPos[id-1] )
        }
    }
    return PLUGIN_HANDLED
}
//    _______________________
//___/ Menu_UAIOArenaSets() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Handles Completion of UAIO Arena Weapons Menu - Extra Weapon Sets
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Menu_UAIOArenaSets( id, key )
{
    switch( key )
    {
        case 7: 
        {
            if(g_bArenaVote[id-1])
            {
                g_bArenaVote[id-1] = false
                if(g_bArenaEnabled)
	                UAIO_CommenceArenaVote( id , AR_END)
                else
	                UAIO_CommenceArenaVote( id , AR_START)
            }
            else
            {
                if(g_bArenaEnabled)
                    UAIO_EndArena()
                else
                    UAIO_StartArena()
             }
        }
        case 8:
        {
            // User Selected "More..." Option
            UAIO_ExtraMenu( id, ++g_iWeaponMenuPos[id-1] )
        }
        case 9:
        {
            // User Chose to go Back to Previous Menu
            if( g_iWeaponMenuPos[id-1] )
            {
                UAIO_ExtraMenu( id, --g_iWeaponMenuPos[id-1] )
            }else
            {
                UAIO_WeaponMenu( id )
            }
        }
        default:
        {
            
        }
    }
    return PLUGIN_HANDLED
}

//     ______________________________________________
//    /          UAIO Weapon Menu System             \_____________
//___/                                                \ Type: Misc \________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//    ___________________
//___/ Menu_UAIOWeapon() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Handles Completion of UAIO Weapons Menu - First Page - Weapon Type
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Menu_UAIOWeapon( id, key )
{
    #if defined UAIO_DEBUG_MENU
        client_print( id, print_console, "^n[DEBUG] Menu_UAIOWeapon Called!" )
        client_print( id, print_console, "^n[DEBUG] [Player:%d][Command:%d][Type:%d][Weapon:%d]^n", g_iCurrPlayer[id-1], g_iCurrCommand[id-1], g_iCurrType[id-1], key )
    #endif
    
    // Track which Menu Type was chosen
    g_iWeaponMenuType[id-1] = key

    switch( key )
    {
        case 0: UAIO_PistolMenu( id )
        case 1: UAIO_ShotgunMenu( id )
        case 2: UAIO_SmgMenu( id )
        case 3: UAIO_RifleMenu( id, g_iWeaponMenuPos[id-1] = 0 )
        case 4: UAIO_MachineMenu( id )
        case 5: Menu_UAIOReg( id, 0 )
        case 6: Menu_UAIOReg( id, 1 )
        case 7: UAIO_EquipMenu( id )
        case 8: UAIO_ExtraMenu( id, g_iWeaponMenuPos[id-1] = 0 )
        default: Menu_UAIOCommandType( id )
    }
    return PLUGIN_HANDLED
}
//    ________________
//___/ Menu_UAIOReg() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Handles Completion of UAIO Weapons Menu - All but Rifles and Extra
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Menu_UAIOReg( id, key )
{
    new iOption = 0
    switch( g_iWeaponMenuType[id-1] )
    {
        case 0: iOption = key
        case 1: iOption = key + OFFSET_SHOTGUN
        case 2: iOption = key + OFFSET_SMG
        case 4: iOption = key + OFFSET_MACHINE
        case 5: iOption = key + OFFSET_AMMO
        case 6: iOption = key + OFFSET_AMMO
        case 7: iOption = key + OFFSET_EQUIP
    }
    
    switch( key )
    {
        case 9:
        {
            // User wants to go Back to Previous Menu
            UAIO_WeaponMenu( id )
        }
        default:
        {
            new szCmd[STR_T]
            if( g_iCurrPlayer[id-1] >= 1000 )
                format( szCmd, STR_T-1, "uaio_weapon %s %d", g_szVarCmdArgs[g_iCurrPlayer[id-1]-1000], g_iWeaponNum[iOption] )
            else
                format( szCmd, STR_T-1, "uaio_weapon #%d %d", get_user_userid(g_iCurrPlayer[id-1]), g_iWeaponNum[iOption] )
            client_cmd( id, szCmd )
        }
    }
    return PLUGIN_HANDLED
}
//    __________________
//___/ Menu_UAIORifle() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Handles Completion of UAIO Weapons Menu - Rifles
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Menu_UAIORifle( id, key )
{
    switch( key )
    {
        case 8:
        {
            // User Selected "More..." Option
            UAIO_RifleMenu( id, ++g_iWeaponMenuPos[id-1] )
        }
        case 9:
        {
            // User Chose to go Back to Previous Menu
            if( g_iWeaponMenuPos[id-1] )
            {
                UAIO_RifleMenu( id, --g_iWeaponMenuPos[id-1] )
            }else
            {
                UAIO_WeaponMenu( id )
            }
        }
        default:
        {
            new iOption = g_iWeaponMenuPos[id-1] * MENU_DISPLAY + key + OFFSET_RIFLE
            new szCmd[STR_T]
            if( g_iCurrPlayer[id-1] >= 1000 )
                format( szCmd, STR_T-1, "uaio_weapon %s %d", g_szVarCmdArgs[g_iCurrPlayer[id-1]-1000], g_iWeaponNum[iOption] )
            else
                format( szCmd, STR_T-1, "uaio_weapon #%d %d", get_user_userid(g_iCurrPlayer[id-1]), g_iWeaponNum[iOption] )
            client_cmd( id, szCmd )
        }
    }
    return PLUGIN_HANDLED
}
//    __________________
//___/ Menu_UAIOExtra() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Handles Completion of UAIO Weapons Menu - Extra Weapon Sets
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Menu_UAIOExtra( id, key )
{
    switch( key )
    {
        case 8:
        {
            // User Selected "More..." Option
            UAIO_ExtraMenu( id, ++g_iWeaponMenuPos[id-1] )
        }
        case 9:
        {
            // User Chose to go Back to Previous Menu
            if( g_iWeaponMenuPos[id-1] )
            {
                UAIO_ExtraMenu( id, --g_iWeaponMenuPos[id-1] )
            }else
            {
                UAIO_WeaponMenu( id )
            }
        }
        default:
        {
            new iOption = g_iWeaponMenuPos[id-1] * MENU_DISPLAY + key + OFFSET_EXTRA
            new szCmd[STR_T]
            if( g_iCurrPlayer[id-1] >= 1000 )
                format( szCmd, STR_T-1, "uaio_weapon %s %d", g_szVarCmdArgs[g_iCurrPlayer[id-1]-1000], g_iWeaponNum[iOption] )
            else
                format( szCmd, STR_T-1, "uaio_weapon #%d %d", get_user_userid(g_iCurrPlayer[id-1]), g_iWeaponNum[iOption] )
            client_cmd( id, szCmd )
        }
    }
    return PLUGIN_HANDLED
}

//     ______________________________________________
//    /          UAIO Vote Menu System               \_____________
//___/                                                \ Type: Misc \________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//    ___________________
//___/ Menu_UAIOVoting() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Handles Individual Player Votes from Vote Menu.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Menu_UAIOVoting( id, key )
{
    new szPlayer[STR_T]
    get_user_name( id, szPlayer, STR_T-1 )
    
    // Reverse Key
    key = (key) ? 0 : 1
    
    // Check which option was selected
    if( get_cvar_num("sv_uaio_vote_answers") )
    {
        new szOption[STR_T]
        format( szOption, STR_T-1, "%L", LANG_PLAYER, (key)?"EXEC_VOTE_OPT1":"EXEC_VOTE_OPT2" )
        client_print( 0, print_chat, "%L", LANG_PLAYER, "EXEC_VOTE_INFO", PLUGIN_MOD, szPlayer, szOption )
    }
    g_iVoteCount[key]++
    return PLUGIN_HANDLED
}

