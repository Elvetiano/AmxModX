////////////////////////////////////////////////////////////////////////////////////////////
//   stocks_common.inc                    Version 1.51                       Date: AUG/01/2006
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

#if defined _UAIO_COMMON_STOCKS_INCLUDED
  #endinput
#endif
#define _UAIO_COMMON_STOCKS_INCLUDED

//
//     ______________________________________________
//    /        Plugin/Player State Routines          \_____________
//___/                                                \            \________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    ______________________
//___/ UAIO_PluginEnabled() \_______________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Gets/Sets the Plugin Enabled State
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock bool:UAIO_PluginEnabled( p_iSwitch )
{
    if( p_iSwitch > UAIO_NULL )
        g_bPluginEnabled = (p_iSwitch) ? true : false
    return g_bPluginEnabled
}
//    __________________
//___/ UAIO_ReadFlags() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Converts Character Flag Sets to Integer Bit Sum
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_ReadFlags( p_szFlags[] )
{
    new i, j = 0
    new szBit[MAX_BITS][] = { "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","1","2","3","4","5","6" }

    for( i = 0; i < MAX_BITS; i++ )
        if( containi( p_szFlags, szBit[i] ) > UAIO_NULL )
            j |= (1<<i)
    return j
}
//    _______________________
//___/ UAIO_GetBitPosition() \______________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Returns Position of Matching Bit in Byte
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_GetBitPosition( p_iByte )
{
    new bit
    for( bit = 0; bit < MAX_BITS; bit++ )
        if( (1<<bit) & p_iByte )
            break
    return bit
}
//    ____________________
//___/ UAIO_HasImmunity() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Determines if User Has Immunity Depending on Immunity CVARs
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock bool:UAIO_HasImmunity( id, p_iCmdType )
{
    switch( p_iCmdType )
    {
        case CMDTYPE_VOTE:
        {
            if( get_cvar_num("sv_uaio_immunity_vote") == 0 )
                return false
        }
        case CMDTYPE_GOOD:
        {
            if( get_cvar_num("sv_uaio_immunity_good") == 0 )
                return false
        }
        case CMDTYPE_EVIL:
        {
            if( get_cvar_num("sv_uaio_immunity_evil") == 0 )
                return false
        }
        case CMDTYPE_MISC:
        {
            if( get_cvar_num("sv_uaio_immunity_misc") == 0 )
                return false
        }
    }
    if( access( id, ADMIN_IMMUNITY ) )
        return true
    return false
}
//    _________________
//___/ UAIO_HasAdmin() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Determines if Player is a Registered UAIO Admin
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock bool:UAIO_HasAdmin( p_iUserID )
{
    return g_bIsAdmin[p_iUserID-1]
}
//    ___________________
//___/ UAIO_ClearAdmin() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Clears a Specific Admin Command Flags
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_ClearAdmin( p_iAdminID )
{
    for( new i = 0; i < MAX_CMD_TYPES; i++ )
        g_iAdminCmdBits[p_iAdminID-1][i] = UAIO_NULL
    g_bIsAdmin[p_iAdminID-1] = false
    return
}
//    ___________________
//___/ UAIO_NullAdmins() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Resets All UAIO Admins
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_NullAdmins()
{
    for( new i = 1; i < MAX_PLAYERS+1; i++ )
        UAIO_ClearAdmin( i )
    return
}
//    _____________________
//___/ UAIO_HasCmdAccess() \________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Determines if an Admin/Player has Access to a Specific Command
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock bool:UAIO_HasCmdAccess( p_iUserID, p_iCmdType, p_iCmdBit )
{
    return ((g_iAdminCmdBits[p_iUserID-1][p_iCmdType] & p_iCmdBit) == p_iCmdBit)
}
//    __________________
//___/ UAIO_HasEffect() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Determines if a Player has a Specific Command Effect
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock bool:UAIO_HasEffect( p_iPlayerID, p_iCmdType, p_iEffect )
{
    return ((g_iHasEffect[p_iPlayerID-1][p_iCmdType] & p_iEffect) == p_iEffect)
}
//    __________________
//___/ UAIO_SetEffect() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Sets a Specific Command Effect on a Player
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock bool:UAIO_SetEffect( p_iPlayerID, p_iCmdType, p_iEffect )
{
    g_iHasEffect[p_iPlayerID-1][p_iCmdType] |= p_iEffect
    return
}
//    _____________________
//___/ UAIO_RemoveEffect() \________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes a Specific UAIO Command Effect from a Player
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_RemoveEffect( p_iPlayerID, p_iCmdType, p_iEffect )
{
    if( UAIO_HasEffect( p_iPlayerID, p_iCmdType, p_iEffect ) )
        g_iHasEffect[p_iPlayerID-1][p_iCmdType] ^= p_iEffect
    return
}
//    ____________________
//___/ UAIO_RemoveAllFX() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes All UAIO Command Effects from a Player
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_RemoveAllFX( p_iPlayerID )
{
    for( new i = 0; i < MAX_CMD_TYPES; i++ ) g_iHasEffect[p_iPlayerID-1][i] = 0
    g_iMenuOrder[p_iPlayerID-1] = MO_COMMANDS
    return
}
//    ___________________
//___/ UAIO_RemoveTask() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes a Global Task if it exists
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_RemoveTask( p_iPlayerID, p_iTaskID )
{
    if( task_exists( p_iTaskID + p_iPlayerID ) )
        remove_task( p_iTaskID + p_iPlayerID )
    return
}
//    ___________________
//___/ UAIO_AdminIndex() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Finds Admin Index from Global Admins Data, returns NULL if not found
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_AdminIndex( p_iAdminID )
{
    new i, l, szTemp[STR_T], szAuthID[STR_T], szIP[STR_T]
    get_user_authid( p_iAdminID, szTemp, STR_T-1 )
    get_user_ip( p_iAdminID, szIP, STR_T-1, 1 ); // Without Port
    
    l = (!equali( szTemp, "STEAM_ID_PENDING" ) && !equali( szTemp, "VALVE_ID_LOOPBACK" ) && (containi( szTemp, "STEAM" ) > -1) ) ? 10 : 0;
    format( szAuthID, STR_T-1, "%s", szTemp[l] )
    
    for( i = 0; i < g_iAdminCount; i++ )
    {
        // Check for IP stored instead of SteamID
        if( contain( g_szAdminID[i], "." ) > -1 )
        {
            if( strlen(szIP) != strlen(g_szAdminID[i]) )
                continue
            
            // Check for matching IP
            if( equal( szIP, g_szAdminID[i] ) )
            {
                g_bIsAdmin[p_iAdminID-1] = true
                return i
            }
        }else
        {
            if( strlen(szAuthID) != strlen(g_szAdminID[i]) )
                continue
            
            // Check for Matching SteamID
            if( equal( szAuthID, g_szAdminID[i] ) )
            {
                g_bIsAdmin[p_iAdminID-1] = true
                return i
            }
        }
    }
    return UAIO_NULL
}
//    ____________________
//___/ UAIO_AdminGroups() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Determines Each Admins Groupings, Regular Players get 'default' Group
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock bool:UAIO_AdminGroups( p_iAdminID )
{
    new i, idx = UAIO_AdminIndex( p_iAdminID )
    if( idx == UAIO_NULL )
    {
        idx = UAIO_ArrayIdxSearch( g_szAdminID, g_iAdminCount, "default" )
        if( idx == UAIO_NULL )
        {
            UAIO_ClearAdmin( p_iAdminID )
            return false
        }
    }

    for( i = 0; i < g_iGroupCount[CMDTYPE_VOTE]; i++ )
    {
        if( containi( g_szAdminGroup[idx], g_szVGroupNames[i] ) > -1 )
        {
            g_iAdminCmdBits[p_iAdminID-1][CMDTYPE_VOTE] = g_iVGroupFlags[i]
            break
        }
    }
    for( i = 0; i < g_iGroupCount[CMDTYPE_GOOD]; i++ )
    {
        if( containi( g_szAdminGroup[idx], g_szGGroupNames[i] ) > -1 )
        {
            g_iAdminCmdBits[p_iAdminID-1][CMDTYPE_GOOD] = g_iGGroupFlags[i]
            break
        }
    }
    for( i = 0; i < g_iGroupCount[CMDTYPE_EVIL]; i++ )
    {
        if( containi( g_szAdminGroup[idx], g_szEGroupNames[i] ) > -1 )
        {
            g_iAdminCmdBits[p_iAdminID-1][CMDTYPE_EVIL] = g_iEGroupFlags[i]
            break
        }
    }
    for( i = 0; i < g_iGroupCount[CMDTYPE_MISC]; i++ )
    {
        if( containi( g_szAdminGroup[idx], g_szMGroupNames[i] ) > -1 )
        {
            g_iAdminCmdBits[p_iAdminID-1][CMDTYPE_MISC] = g_iMGroupFlags[i]
            break
        }
    }

    return true
}
//    ___________________
//___/ UAIO_CmdsForAll() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Check for Commands set on Teams/Everyone;
// When new players join we can grant those effects automatically
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_CmdsForAll( p_iCmdsTeam, p_iCmdIdx, p_iDuration )
{
    if( p_iCmdsTeam > TEAM_NONE )
    {
        if( p_iDuration > 0 )
            g_iCmdsForAll[p_iCmdsTeam] |= p_iCmdIdx
        else
            g_iCmdsForAll[p_iCmdsTeam] ^= p_iCmdIdx

        new pos = UAIO_GetBitPosition( p_iCmdIdx )
        g_iCmdsForAllDur[p_iCmdsTeam][pos] = p_iDuration
    }
    return   
}
//    ____________________
//___/ UAIO_WeaponTitle() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Determines the Title of Weapons for Announcements
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_WeaponTitle( p_iWeaponCode, p_szTitle[], p_iSize )
{
    new i
    for( i = 0; i < WMENU_OPTIONS; i++ )
    {
        if( g_iWeaponNum[i] == p_iWeaponCode )
        {
            format( p_szTitle, p_iSize, g_szWeaponTitles[i] )
            break
        }
    }
    return
}
//    ____________________
//___/ UAIO_WeaponConst() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Determines the CS Const of Weapons for Arena
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_WeaponConst( p_iWeaponCode )
{
    new i
    for( i = 0 ; i < AR_ALL_GUNS ; i++ )
    {
        if( g_iArenaWeaponNum[i] == p_iWeaponCode )
        {
		return (g_iArenaWeaponConst[i])
        }
    }
    return UAIO_NULL
}
//    ____________________
//___/ UAIO_WeaponConst() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Determines the Weapon name of weapon const for Arena
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_ArenaWeaponTitle( p_iWeaponConst , p_szWeaponTitle[] , p_iSize)
{
    for( new i = 0 ; i < AR_ALL_GUNS ; i++ )
    {
        if( g_iArenaWeaponConst[i] == p_iWeaponConst )
        {
		format(p_szWeaponTitle , p_iSize-1 , g_szArenaWeaponTitles[i])
		return true
        }
    }
    return false
}
//    ____________________
//___/ UAIO_ArenaWeapon() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Grants a User a Random Weapon Corresponding to Current Arena Mode
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_ArenaWeapon( p_iUserID )
{
    if( !is_user_alive(p_iUserID) || !g_bArenaEnabled )
        return // Invalid User or No Arena Enabled

    // Get Random Arena Gun Index
    new iWeaponIdx[AR_MAX_GUNS] , szWeapon[36] , iWepCount = 0
    for( new x = 0 ; x < AR_MAX_GUNS ; x++ )
    {
        if(g_iArenaCustom[x] == UAIO_NULL)
            continue
        get_weaponname( g_iArenaCustom[x] , szWeapon , 35)
        for( new j = 0 ; j < WMENU_WEAPONS ; j++ )
        {
            if(equal( szWeapon , g_szWeaponList[j]))
            {
                iWeaponIdx[ iWepCount++ ] = j
                break
            }
        }
    }
    UAIO_GiveWeapon( p_iUserID , iWeaponIdx[random_num( 0 , iWepCount-1 )] )
    // Give Free Arena Items
    for( new i = 1; i < 6; i++ )
        UAIO_GiveItem( p_iUserID, i ) // Kevlar, Flash/HE/Smoke Grenade, Defuse Kit
    return
}
//    ____________________
//___/  UAIO_IsInArena()  \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Checks to see if weapon supplied is in current arena.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock bool:UAIO_IsInArena( WepID )
{
    for( new i = 0 ; i < AR_MAX_GUNS ; i++)
    {
        if( WepID == g_iArenaCustom[i] )
		return true
    }
    return false
}
//    _____________________
//___/  UAIO_StartArena()  \________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Initializes arena.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_StartArena( )
{
    g_iOldFreezeTime = get_cvar_num( "mp_freezetime" )
    server_cmd( "mp_freezetime 1" )
    g_bArenaEnabled = true

    server_cmd( "sv_restartround 3" )
    server_exec()
}
//    _____________________
//___/   UAIO_EndArena()   \________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Ends arena.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_EndArena( )
{
    server_cmd( "mp_freezetime %d", g_iOldFreezeTime )
    g_bArenaEnabled = false
    g_bArenaGrenades = true
    g_iWepCount = 0
    for(new i = 0 ; i < AR_MAX_GUNS ; i++)
        g_iArenaCustom[i] = UAIO_NULL

    server_cmd( "sv_restartround 3" )
    server_exec()
}
//
//     ______________________________________________
//    /           Misc String  Routines              \_____________
//___/                                                \            \________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    ______________________
//___/ UAIO_ExplodeString() \_______________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Sperates a String into an array by a Delimeter (similar to explode() in PHP)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_ExplodeString( p_szOutput[][], p_iMax, p_szInput[], p_iSize, p_szDelimiter )
{
    new iIdx = 0, l = strlen(p_szInput)
    new iLen = (1 + copyc( p_szOutput[iIdx], p_iSize, p_szInput, p_szDelimiter ))
    while( (iLen < l) && (++iIdx < p_iMax) )
        iLen += (1 + copyc( p_szOutput[iIdx], p_iSize, p_szInput[iLen], p_szDelimiter ))
    return iIdx
}
//    _______________
//___/ UAIO_StrMid() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Returns a portion of a string
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_StrMid( p_szInput[], p_szOutput[], p_iStart, p_iEnd )
{
    new iLen = strlen( p_szInput )

    if( p_iStart < 0 ) p_iStart = 0
    if( p_iEnd <= p_iStart || p_iEnd > iLen ) p_iEnd = iLen

    for( new j = 0, i = p_iStart; i < p_iEnd; j++, i++ )
        p_szOutput[j] = p_szInput[i]

    return
}
//    _______________________
//___/ UAIO_ArrayIdxSearch() \______________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Searches a 2D array for a String Value and returns the Array Index
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_ArrayIdxSearch( p_aInput[][], p_iSize, p_szKey[] )
{
    new i
    for( i = 0; i < p_iSize; i++ )
        if( equali( p_aInput[i], p_szKey ) )
            return i
    return UAIO_NULL
}
//    ____________________
//___/ UAIO_InputSwitch() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Parses a Console Input Switch
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_InputSwitch( p_szArg[] )
{
    return ( equali( p_szArg, "on", 2 ) || equali( p_szArg, "1", 1 ) ) ? 1 : 0
}
//
//     ______________________________________________
//    /         Announcement/Log  Routines           \_____________
//___/                                                \            \________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    _______________________
//___/ UAIO_AnnounceAction() \______________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Announces an Action Message through AMX(X) (Obeys 'amx_show_activity' CVAR Rules)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_AnnounceAction( p_iAdminID, p_szAction[] )
{
    new szAdminName[STR_T], szLevel[STR_T]
    get_user_name( p_iAdminID, szAdminName, (STR_T-1) )
    format( szLevel, STR_T-1, "%L", LANG_PLAYER, is_user_admin(p_iAdminID)?"USER_ADMIN":"USER_PLAYER" )
    switch( get_cvar_num( "sv_uaio_show_activity" ) )
    {
        case 1: client_print( 0, print_chat,"%s: %s", szLevel, p_szAction )
        case 2: client_print( 0, print_chat,"%s %s: %s", szLevel, szAdminName, p_szAction )
    }
    return
}
//    _________________
//___/ UAIO_WriteLog() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Writes a Message to the Log Files
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_WriteLog( szMessage[] )
{
    // Log Message to File
    log_amx( szMessage )
    return
}
//    ______________________
//___/ UAIO_WriteLogDebug() \_______________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Writes a Message to the Log Files Only If Debug Mode is Enabled
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_WriteLogDebug( szMessage[] )
{
#if defined UAIO_DEBUG_MODE
    UAIO_WriteLog( szMessage )
#endif
    szMessage[0] = 0
    return
}
