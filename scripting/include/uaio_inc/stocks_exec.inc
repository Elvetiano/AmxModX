////////////////////////////////////////////////////////////////////////////////////////////
//   stocks_exec.inc                    Version 1.51                       Date: AUG/01/2006
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

//X y POSITION 
// - - - - - - - - - - - - - - - - - - - - - - -
//  (0.0,0.0) ↑y  (0.0,1.0)    syntax : x y
//            │            (default: -1.0 0.2)
//      ← ————┼———— → x
//            │             center: (-1.0,-1.0)
//  (0.0,1.0) ↓  (1.0,1.0)
// - - - - - - - - - - - - - - - - - - - - - - -
//        0.0 ---------------- X ---------------- 1.0
//          _________________________________________
//   0.0   |                                         |
//    |    |                                         |
//    |    |                                         |
//    |    |                                         |
//    |    |                                         |
//    |    |                                         |
//    |    |                                         |
//         |                                         |
//    Y    |                                         |
//         |                                         |
//    |    |                                         |
//    |    |                                         |
//    |    |                                         |
//    |    |                                         |
//    |    |                                         |
//    |    |                                         |
//   1.0   |_________________________________________|

#if defined _UAIO_EXEC_STOCKS_INCLUDED
  #endinput
#endif
#define _UAIO_EXEC_STOCKS_INCLUDED

//
//     ______________________________________________
//    /            Execution  Routines               \_____________
//___/                                                \            \________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    __________________
//___/ UAIO_UserAExec() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Finds Auto-Exec Commands for Connecting/Leaving Clients to Execute
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_UserAExec( p_iUserID, p_iFlag )
{
    new i, szAuthID[STR_T], szUserName[STR_T]
    get_user_authid( p_iUserID, szAuthID, STR_T-1 )
    get_user_name( p_iUserID, szUserName, STR_T-1 )

    // Match Steam IDs
    for( i = 0; i < g_iAExecCount; i++ )
    {
        if( g_iAExecFlags[i] & p_iFlag )
        {
            // TODO: Check Matching STEAMID using equali() and ensure correct length
            if( (containi( szAuthID, g_szAExecUser[i] ) > -1) || (containi( szUserName, g_szAExecUser[i] ) > -1) || equali( "default", g_szAExecUser[i] ) ) 		 
            {
		new szCommand[STR_M];
		copy(szCommand , STR_M-1 , g_szAExecCmds[i]);
                UAIO_CmdAExec( p_iUserID, g_iAExecFlags[i], szCommand ) 
            }
        }
    }
    return UAIO_NULL
}
//    _________________
//___/ UAIO_CmdAExec() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Executes an Auto-Exec Command on Specified Player
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_CmdAExec( p_iUserID, p_iFlags, p_szCommand[] )
{
    new szUID[8], szUserName[STR_T]
    
    //get_user_name( p_iUserID, szUserName, STR_T-1 )
    get_user_info( p_iUserID, "name", szUserName, STR_T-1 )
    format( szUID, 7, "#%d", get_user_userid( p_iUserID ) )

    // Replace Command Variables
    while( replace( p_szCommand, STR_M-1, "{userid}", szUID ) ) { }
    while( replace( p_szCommand, STR_M-1, "{username}", szUserName ) ) { }
    
    // Execute Command According to Flags
    if( p_iFlags & AUTOEXEC_HUDMSG )
    {
        new szHudColor[16], aHudColors[3][5]
        get_cvar_string( "sv_uaio_hud_color", szHudColor, 15 )
        UAIO_ExplodeString( aHudColors, 3, szHudColor, 4, ' ' )
        set_hudmessage( str_to_num(aHudColors[0]), str_to_num(aHudColors[1]), str_to_num(aHudColors[2]), 0.35, 0.05, _, 3.0, 7.0, _, _, 3 )
        show_hudmessage( 0, p_szCommand )
    }
    else if( p_iFlags & EXEC_SERVER )
    {
        set_task( g_fAExecInterval[p_iUserID-1], "UAIO_AutoExecServer", (TASK_COMMON+(p_iUserID*2)), p_szCommand, strlen(p_szCommand) )
    }
    else if( (p_iFlags & EXEC_ADMIN) || (p_iFlags & EXEC_CLIENT) )
    {
        new szCommand[STR_M]
        format( szCommand, (STR_M-1), "%d|%s", p_iUserID, p_szCommand )
        set_task( g_fAExecInterval[p_iUserID-1], "UAIO_AutoExecClient", (TASK_COMMON+(p_iUserID*2)), szCommand, strlen(szCommand) )
    }
    g_fAExecInterval[p_iUserID-1] = floatadd( g_fAExecInterval[p_iUserID-1], 0.5 )
    return
}
//    _________________
//___/ ExecuteDurCmd() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Prepares a Duration Command on Specified Player (Only lasts for a specified time)
// Actual action performed is called as a call-back passed in as 'szCmdInit'
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock ExecuteDurCmd( iAdminID, iCmdType, iCmdIdx, iCmdTask, szCmdTitle[], szCmdInit[]="", szCmdEnd[]="", szCmdMsgA[]="", szCmdMsgB[]="" )
{
    new szVictimName[STR_T], szVictimTitle[STR_T], szActionMsg[STR_M]
    
    // Parse Command Arguments
    new szCmdArgs[2][STR_T]
    UAIO_ExplodeString( szCmdArgs, 2, g_szCmdArgs[iAdminID-1], STR_T-1, ' ' )

    // Find Player Targets From First Command Argument
    new i, iTargets[MAX_PLAYERS]
    new iTargetNum = UAIO_PlayerList( iAdminID, szCmdArgs[0], iTargets )
    
    // Check if Targets were found
    if( !iTargetNum )
    {   // No Targets Found
        new szTitle[STR_M]
        format( szTitle, STR_M-1, "%L", iAdminID, szCmdTitle )
        console_print( iAdminID, "%L", iAdminID, "NO_TARGET", PLUGIN_MOD, PLUGIN_NAME, szCmdArgs[0], szTitle )
        return
    }

    // Find Effect Duration From Second Command Argument
    new iDuration = str_to_num( szCmdArgs[1] )

    // Check for Good Commands set on Teams/Everyone
    if( iCmdType == CMDTYPE_GOOD )
        UAIO_CmdsForAll( g_iCmdsForAllTeam, iCmdIdx, iDuration )
    
    // Announce Action
    UAIO_PlayerTitle( iAdminID, szCmdArgs[0], szVictimTitle, STR_T-1 )
    new szCmdMsg[STR_M]
    if( iDuration )
    {   format( szCmdMsg, STR_M-1, "%L", LANG_PLAYER, szCmdMsgA )
        format( szActionMsg, STR_M-1, "%L", LANG_PLAYER, "EXEC_DUR_CMD1", szVictimTitle, szCmdMsg, iDuration )
    }else
    {
        format( szCmdMsg, STR_M-1, "%L", LANG_PLAYER, szCmdMsgB )
        format( szActionMsg, STR_M-1, "%L", LANG_PLAYER, "EXEC_DUR_CMD2", szVictimTitle, szCmdMsg )
    }
    UAIO_AnnounceAction( iAdminID, szActionMsg )

    // 1 or More Targets Found, Loop Through All Targets
    for( i = 0; i < iTargetNum; i++ )
    {
        // Obey Immunity Flags
        if( UAIO_HasImmunity( iTargets[i], iCmdType ) )
        {
            get_user_name( iTargets[i], szVictimName, STR_T-1 )
            console_print( iAdminID, "%L", iAdminID, "TARGET_IMMUNE", PLUGIN_MOD, PLUGIN_NAME, szVictimName )
            continue
        }
        if( !is_user_connected( iTargets[i] ) ) continue

        // Check if we are turning Duration Command On
        if( iDuration )
        {
            // If Client Already Has Duration Command
            if( UAIO_HasEffect( iTargets[i], iCmdType, iCmdIdx ) )
            {
                // Remove Old Task
                UAIO_RemoveTask( iTargets[i], iCmdTask )
            }

            // Set Duration Command on Target
            UAIO_SetEffect( iTargets[i], iCmdType, iCmdIdx )

            // Initialize Duration Command
            if( szCmdInit[0] )
                set_task( 0.1, szCmdInit, (iCmdTask + iTargets[i]), iTargets[i], 1 )

            // Delayed-Removal
            if( szCmdEnd[0] )
                set_task( float(iDuration), szCmdEnd, (iCmdTask + iTargets[i]), iTargets[i], 1 )

        }else // We are turning Duration Command Off
        {
            // Check if Target Has Duration Command already to turn Off
            if( UAIO_HasEffect( iTargets[i], iCmdType, iCmdIdx ) )
            {
                // Remove Old Task
                UAIO_RemoveTask( iTargets[i], iCmdTask )

                // Remove Duration Command from Target
                set_task( 0.1, szCmdEnd, (iCmdTask + iTargets[i]), iTargets[i], 1 )
            }else
            {
                // Client Doesn't Have Duration Command to Turn OFf
                new szTitle[STR_M]
                format( szTitle, STR_M-1, "%L", iAdminID, szCmdTitle )
                get_user_name( iTargets[i], szVictimName, STR_T-1 )
                console_print( iAdminID, "%L", iAdminID, "TARGET_NOFX", PLUGIN_MOD, PLUGIN_NAME, szVictimName, szTitle )
            }
        }
    }
    return
}
//    __________________
//___/ ExecuteInstCmd() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Prepares an Instant Command on Specified Player
// Actual action performed is called as a call-back passed in as 'szCmdInit'
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock ExecuteInstCmd( iAdminID, iCmdType, iCmdTask, szCmdTitle[], szCmdInit[]="", szCmdMsgA[]="", szCmdMsgB[]="" )
{
    new szVictimName[STR_T], szVictimTitle[STR_T], szActionMsg[STR_M]

    // Parse Command Arguments
    new szCmdArgs[2][STR_T], szInitCmdArgs[3]
    UAIO_ExplodeString( szCmdArgs, 2, g_szCmdArgs[iAdminID-1], STR_T-1, ' ' )

    // Find Player Targets From First Command Argument
    new i, iTargets[MAX_PLAYERS]
    new iTargetNum

    if(iCmdTask == TASK_E_BAN_P || iCmdTask == TASK_E_BAN_T)
    {
        iTargets[0] = cmd_target( iAdminID , szCmdArgs[0] , 0)
	iTargetNum = 1
        if(iTargets[0] > 0) get_user_name(iTargets[0] , szVictimTitle , STR_T-1)
        else return
    }
    else
    {
        iTargetNum = UAIO_PlayerList( iAdminID, szCmdArgs[0], iTargets )
        UAIO_PlayerTitle( iAdminID, szCmdArgs[0], szVictimTitle, STR_T-1 )
    }
    // Check if Targets were found
    if( !iTargetNum )
    {   // No Targets Found
        new szTitle[STR_M]
        format( szTitle, STR_M-1, "%L", iAdminID, szCmdTitle )
        console_print( iAdminID, "%L", iAdminID, "NO_TARGET", PLUGIN_MOD, PLUGIN_NAME, szCmdArgs[0], szTitle )
        return
    }

    // Find Extra Parameters from Second Command Argument
    new iExtra = (!szCmdArgs[1][0]) ? 0 : str_to_num( szCmdArgs[1] )

    // Announce Action
    new szCmdMsg1[STR_M], szCmdMsg2[STR_M]
    format( szCmdMsg1, STR_M-1, "%L", LANG_PLAYER, szCmdMsgA )
    if( szCmdMsgB[0] ) format( szCmdMsg2, STR_M-1, "%L", LANG_PLAYER, szCmdMsgB )
    
    if( iCmdTask == TASK_M_WEAPON )
    {
        new szWeaponTitle[STR_T] , szWeaponString[STR_T]
        UAIO_WeaponTitle( iExtra, szWeaponTitle, STR_T-1 )
        format( szWeaponString , STR_T-1 , "%L" , LANG_PLAYER , szWeaponTitle)
        format( szActionMsg, STR_M-1, "%L", LANG_PLAYER, "EXEC_INST_CMD1", szVictimTitle, szCmdMsg1, szWeaponString )
    }
    else if( szCmdMsgB[0] ) // if( iExtra )
        format( szActionMsg, STR_M-1, "%L", LANG_PLAYER, "EXEC_INST_CMD2", szVictimTitle, szCmdMsg1, iExtra, szCmdMsg2 )
    else
        format( szActionMsg, STR_M-1, "%L", LANG_PLAYER, "EXEC_INST_CMD3", szVictimTitle, szCmdMsg1 )
    UAIO_AnnounceAction( iAdminID, szActionMsg )

    // 1 or More Targets Found, Loop Through All Targets
    for( i = 0; i < iTargetNum; i++ )
    {
        // Obey Immunity Flags
        if( UAIO_HasImmunity( iTargets[i], iCmdType ) )
        {
            get_user_name( iTargets[i], szVictimName, STR_T-1 )
            console_print( iAdminID, "%L", iAdminID, "TARGET_IMMUNE", PLUGIN_MOD, PLUGIN_NAME, szVictimName )
            continue
        }
        if( !is_user_connected( iTargets[i] ) ) continue

        // Initialize Command
        if( szCmdInit[0] )
        {
            szInitCmdArgs[0] = iTargets[i]
            szInitCmdArgs[1] = iExtra
            set_task( 0.1, szCmdInit, (iCmdTask + iTargets[i]), szInitCmdArgs, 2 )
        }
    }
    return
}
//    _________________
//___/ ExecuteTogCmd() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Prepares a Toggle Command on Specified Player (Turns a Command On or Off)
// Actual action performed is called as a call-back passed in as 'szCmdInit'
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock ExecuteTogCmd( iAdminID, iCmdType, iCmdIdx, iCmdTask, szCmdTitle[], szCmdInit[]="", szCmdMsgA[]="", szCmdMsgB[]="" )
{
    new szVictimName[STR_T], szVictimTitle[STR_T], szActionMsg[STR_M]

    // Parse Command Arguments
    new szCmdArgs[2][STR_T], szInitCmdArgs[3]
    UAIO_ExplodeString( szCmdArgs, 2, g_szCmdArgs[iAdminID-1], STR_T-1, ' ' )

    // Find Player Targets From First Command Argument
    new i, iTargets[MAX_PLAYERS]
    new iTargetNum = UAIO_PlayerList( iAdminID, szCmdArgs[0], iTargets )

    // Check if Targets were found
    if( !iTargetNum )
    {   // No Targets Found
        new szTitle[STR_M]
        format( szTitle, STR_M-1, "%L", iAdminID, szCmdTitle )
        console_print( iAdminID, "%L", iAdminID, "NO_TARGET", PLUGIN_MOD, PLUGIN_NAME, szCmdArgs[0], szTitle )
        return
    }

    // Find Toggle Switch From Second Command Argument
    new iToggle = UAIO_InputSwitch( szCmdArgs[1] )

    // Announce Action
    UAIO_PlayerTitle( iAdminID, szCmdArgs[0], szVictimTitle, STR_T-1 )
    new szCmdMsg[STR_M]
    if( iToggle )
    {   format( szCmdMsg, STR_M-1, "%L", LANG_PLAYER, szCmdMsgA )
        format( szActionMsg, STR_M-1, "%L", LANG_PLAYER, "EXEC_TOG_CMD1", szVictimTitle, szCmdMsg )
    }else
    {
        format( szCmdMsg, STR_M-1, "%L", LANG_PLAYER, szCmdMsgB )
        format( szActionMsg, STR_M-1, "%L", LANG_PLAYER, "EXEC_TOG_CMD1", szVictimTitle, szCmdMsg )
    }
    UAIO_AnnounceAction( iAdminID, szActionMsg )
    
    // 1 or More Targets Found, Loop Through All Targets
    for( i = 0; i < iTargetNum; i++ )
    {
        // Obey Immunity Flags
        if( UAIO_HasImmunity( iTargets[i], iCmdType ) )
        {
            get_user_name( iTargets[i], szVictimName, STR_T-1 )
            console_print( iAdminID, "%L", iAdminID, "TARGET_IMMUNE", PLUGIN_MOD, PLUGIN_NAME, szVictimName )
            continue
        }
        if( !is_user_connected( iTargets[i] ) ) continue

        // Check if we are turning Command On
        if( iToggle )
        {
            // If Client Already Has Command
            if( UAIO_HasEffect( iTargets[i], iCmdType, iCmdIdx ) )
            {
                get_user_name( iTargets[i], szVictimName, STR_T-1 )
                format( szCmdMsg, STR_M-1, "%L", iAdminID, szCmdMsgA )
                format( szActionMsg, STR_M-1, "%L", iAdminID, "EXEC_TOG_CMD2", PLUGIN_MOD, PLUGIN_NAME, szVictimName, szCmdMsg )
                console_print( iAdminID, szActionMsg )
                continue
            }

            // Set Command on Target
            UAIO_SetEffect( iTargets[i], iCmdType, iCmdIdx )

            // Initialize Command
            if( szCmdInit[0] )
            {
                szInitCmdArgs[0] = iTargets[i]
                szInitCmdArgs[1] = iToggle
                set_task( 0.1, szCmdInit, (iCmdTask + iTargets[i]), szInitCmdArgs, 2 )
            }

        }else // We are turning Command Off
        {
            // If Client Doesn't Have Command
            if( !UAIO_HasEffect( iTargets[i], iCmdType, iCmdIdx ) )
            {
                get_user_name( iTargets[i], szVictimName, STR_T-1 )
                format( szCmdMsg, STR_M-1, "%L", iAdminID, szCmdMsgA )
                format( szActionMsg, STR_M-1, "%L", iAdminID, "EXEC_TOG_CMD3", PLUGIN_MOD, PLUGIN_NAME, szVictimName, szCmdMsg )
                console_print( iAdminID, szActionMsg )
                continue
            }

            // Remove Command from Target
            UAIO_RemoveEffect( iTargets[i], iCmdType, iCmdIdx )

            // Uninitialize Command
            if( szCmdInit[0] )
            {
                szInitCmdArgs[0] = iTargets[i]
                szInitCmdArgs[1] = iToggle
                set_task( 0.1, szCmdInit, (iCmdTask + iTargets[i]), szInitCmdArgs, 2 )
            }
        }
    }
    return
}
//    _________________
//___/ ExecuteMapCmd() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Prepares a Map Command
// Actual action performed is called as a call-back passed in as 'szCmdInit'
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock ExecuteMapCmd( iAdminID, iCmdType, iCmdTask, szCmdInit[] )
{
    // Parse Command Arguments
    new szCmdArgs[2][STR_T]
    UAIO_ExplodeString( szCmdArgs, 2, g_szCmdArgs[iAdminID-1], STR_T-1, ' ' )

    // Check if Map From First Command Argument is Valid
    if( !is_map_valid( szCmdArgs[0] ) )
    {
        console_print( iAdminID, "%L", iAdminID, "MAP_NOT_FOUND", PLUGIN_MOD, PLUGIN_NAME, szCmdArgs[0] )
        return
    }

    // Announce Action
    new szActionMsg[STR_M]
    if( iCmdType == CMDTYPE_VOTE )
        format( szActionMsg, STR_M-1, "%L", LANG_PLAYER, "EXEC_MAP_CMD1", szCmdArgs[0] )
    else
        format( szActionMsg, STR_M-1, "%L", LANG_PLAYER, "EXEC_MAP_CMD2", szCmdArgs[0] )
    UAIO_AnnounceAction( iAdminID, szActionMsg )

    // Initialize Command
    set_task( 0.2, szCmdInit, (iCmdTask + iAdminID), szCmdArgs[0], strlen(szCmdArgs[0]) )

    return
}
//    __________________
//___/ ExecuteTeamCmd() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Prepares an Team-Change Command on Specified Player
// Actual action performed is called as a call-back passed in as 'szCmdInit'
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock ExecuteTeamCmd( iAdminID, szCmdInit[] )
{
    // Parse Command Arguments
    new szCmdArgs[2][STR_T]
    UAIO_ExplodeString( szCmdArgs, 2, g_szCmdArgs[iAdminID-1], STR_T-1, ' ' )

    // Find Player Targets From First Command Argument
    new i, iTargets[MAX_PLAYERS]
    new iTargetNum = UAIO_PlayerList( iAdminID, szCmdArgs[0], iTargets )

    // Check if Targets were found
    if( !iTargetNum )
    {   // No Targets Found
        new szTemp[STR_T]
        format( szTemp, STR_T-1, "%L", iAdminID, "ACTION_M_TEAM" )
        console_print( iAdminID, "%L", iAdminID, "NO_TARGET", PLUGIN_MOD, PLUGIN_NAME, szCmdArgs[0], szTemp )
        return
    }

    // Find Team ID From Second Command Argument
    new iTeamID = str_to_num( szCmdArgs[1] ) + 1

    // Announce Action
    new szVictimTitle[STR_T], szActionMsg[STR_M], szInitCmdArgs[2]
    UAIO_PlayerTitle( iAdminID, szCmdArgs[0], szVictimTitle, STR_T-1 )
    switch( iTeamID )
    {
        case TEAM_T: format( szActionMsg, STR_M-1, "%L", LANG_PLAYER, "EXEC_TEAM_CMD1", szVictimTitle )
        case TEAM_CT: format( szActionMsg, STR_M-1, "%L", LANG_PLAYER, "EXEC_TEAM_CMD2", szVictimTitle )
        case TEAM_SPEC: format( szActionMsg, STR_M-1, "%L", LANG_PLAYER, "EXEC_TEAM_CMD3", szVictimTitle )
    }
    UAIO_AnnounceAction( iAdminID, szActionMsg )

    // 1 or More Targets Found, Loop Through All Targets
    for( i = 0; i < iTargetNum; i++ )
    {
        // Obey Immunity Flags
        if( UAIO_HasImmunity( iTargets[i], CMDTYPE_MISC ) )
        {
            get_user_name( iTargets[i], szVictimTitle, STR_T-1 )
            console_print( iAdminID, "%L", iAdminID, "TARGET_IMMUNE", PLUGIN_MOD, PLUGIN_NAME, szVictimTitle )
            continue
        }
        if( !is_user_connected( iTargets[i] ) ) continue

        // Initialize Command
        if( szCmdInit[0] )
        {
            szInitCmdArgs[0] = iTargets[i]
            szInitCmdArgs[1] = iTeamID - 1
            set_task( 0.1, szCmdInit, (TASK_M_TEAM + iTargets[i]), szInitCmdArgs, 2 )
        }
    }
    return
}
//    ___________________
//___/ ExecuteModelCmd() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Prepares a Model-Change Command on a Specified Player
// Actual action performed is called as a call-back passed in as 'szCmdInit'
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock ExecuteModelCmd( iAdminID, szCmdInit[] )
{
    // Parse Command Arguments
    new szCmdArgs[2][STR_T]
    UAIO_ExplodeString( szCmdArgs, 2, g_szCmdArgs[iAdminID-1], STR_T-1, ' ' )

    // Find Player Targets From First Command Argument
    new i, iTargets[MAX_PLAYERS]
    new iTargetNum = UAIO_PlayerList( iAdminID, szCmdArgs[0], iTargets )

    // Check if Targets were found
    if( !iTargetNum )
    {   // No Targets Found
        console_print( iAdminID, "%L", iAdminID, "NO_TARGET", PLUGIN_MOD, PLUGIN_NAME, szCmdArgs[0], "Model Change" )
        return
    }

    // Find Model ID From Second Command Argument
    new iModelID = str_to_num( szCmdArgs[1] )

    // Announce Action
    new szVictimTitle[STR_T], szActionMsg[STR_M], szInitCmdArgs[2]
    UAIO_PlayerTitle( iAdminID, szCmdArgs[0], szVictimTitle, STR_T-1 )
    format( szActionMsg, STR_M-1, "%L", LANG_PLAYER, "EXEC_MODEL_CMD", szVictimTitle )
    UAIO_AnnounceAction( iAdminID, szActionMsg )

    // 1 or More Targets Found, Loop Through All Targets
    for( i = 0; i < iTargetNum; i++ )
    {
        // Obey Immunity Flags
        if( UAIO_HasImmunity( iTargets[i], CMDTYPE_MISC ) )
        {
            get_user_name( iTargets[i], szVictimTitle, STR_T-1 )
            console_print( iAdminID, "%L", iAdminID, "TARGET_IMMUNE", PLUGIN_MOD, PLUGIN_NAME, szVictimTitle )
            continue
        }
        if( !is_user_connected( iTargets[i] ) ) continue

        // Initialize Command
        if( szCmdInit[0] )
        {
            szInitCmdArgs[0] = iTargets[i]
            szInitCmdArgs[1] = iModelID
            set_task( 0.1, szCmdInit, (TASK_M_MODEL + iTargets[i]), szInitCmdArgs, 2 )
        }
    }
    return
}
//    __________________
//___/ ExecuteGlowCmd() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Prepares a Glow Command on a Specified Player
// Actual action performed is called as a call-back passed in as 'szCmdInit'
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock ExecuteGlowCmd( iAdminID, szCmdInit[] )
{
    // Parse Command Arguments
    new szCmdArgs[2][STR_T]
    UAIO_ExplodeString( szCmdArgs, 2, g_szCmdArgs[iAdminID-1], STR_T-1, ' ' )

    // Find Player Targets From First Command Argument
    new i, iColor, iTargets[MAX_PLAYERS]
    new iTargetNum = UAIO_PlayerList( iAdminID, szCmdArgs[0], iTargets )

    // Check if Targets were found
    if( !iTargetNum )
    {   // No Targets Found
        console_print( iAdminID, "%L", iAdminID, "NO_TARGET", PLUGIN_MOD, PLUGIN_NAME, szCmdArgs[0], "Glow" )
        return
    }

    // Announce Action
    new szVictimTitle[STR_T], szActionMsg[STR_M], szInitCmdArgs[2]
    UAIO_PlayerTitle( iAdminID, szCmdArgs[0], szVictimTitle, STR_T-1 )

    if( equali( szCmdArgs[1], "none" ) || equali( szCmdArgs[1], "off" ) )
    {
        format( szActionMsg, STR_M-1, "%L", LANG_PLAYER, "EXEC_GLOW_CMD1", szVictimTitle )
        iColor = 1000
    }
    else
    {
        // Find Color From Second Command Argument
        for( iColor = 0; iColor < MAX_COLORS; iColor++ )
            if( equali( szCmdArgs[1], g_szColors[iColor] ) )
                break
        
        format( szActionMsg, STR_M-1, "%L", LANG_PLAYER, "EXEC_GLOW_CMD2", szVictimTitle, g_szColors[iColor] )
    }
    UAIO_AnnounceAction( iAdminID, szActionMsg )
    
    // 1 or More Targets Found, Loop Through All Targets
    for( i = 0; i < iTargetNum; i++ )
    {
        // Obey Immunity Flags
        if( UAIO_HasImmunity( iTargets[i], CMDTYPE_MISC ) )
        {
            get_user_name( iTargets[i], szVictimTitle, STR_T-1 )
            console_print( iAdminID, "%L", iAdminID, "TARGET_IMMUNE", PLUGIN_MOD, PLUGIN_NAME, szVictimTitle )
            continue
        }
        if( !is_user_connected( iTargets[i] ) ) continue

        // Initialize Command
        if( szCmdInit[0] )
        {
            szInitCmdArgs[0] = iTargets[i]
            szInitCmdArgs[1] = iColor
            set_task( 0.1, szCmdInit, (TASK_M_GLOW + iTargets[i]), szInitCmdArgs, 2 )
        }
    }
    return
}
//    __________________
//___/ ExecuteExecCmd() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Prepares an Client/Server Exec Command on Specified Player
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock ExecuteExecCmd( iAdminID, iCmdIdx, szCmdTitle[] )
{
    // Parse Command Arguments
    new szCmdArgs[2][STR_T]
    UAIO_ExplodeString( szCmdArgs, 2, g_szCmdArgs[iAdminID-1], STR_T-1, ' ' )

    // Fix Command
    while ( replace( szCmdArgs[1], STR_T-1, "\'", "^"" ) ) { }
    
    if( iCmdIdx == UAIO_M_CEXEC ) // Client Execute
    {
        // Find Player Targets From First Command Argument
        new i, iTargets[MAX_PLAYERS], szVictimName[STR_T]
        new iTargetNum = UAIO_PlayerList( iAdminID, szCmdArgs[0], iTargets )
    
        // Check if Targets were found
        if( !iTargetNum )
        {   // No Targets Found
            new szTitle[STR_M]
            format( szTitle, STR_M-1, "%L", iAdminID, szCmdTitle )
            console_print( iAdminID, "%L", iAdminID, "NO_TARGET", PLUGIN_MOD, PLUGIN_NAME, szCmdArgs[0], szTitle )
            return
        }
        
        // 1 or More Targets Found, Loop Through All Targets
        for( i = 0; i < iTargetNum; i++ )
        {
            // Obey Immunity Flags
            if( UAIO_HasImmunity( iTargets[i], CMDTYPE_MISC ) )
            {
                get_user_name( iTargets[i], szVictimName, STR_T-1 )
                console_print( iAdminID, "%L", iAdminID, "TARGET_IMMUNE", PLUGIN_MOD, PLUGIN_NAME, szVictimName )
                continue
            }
            if( !is_user_connected( iTargets[i] ) ) continue
    
            // Execute Command
            if( is_user_bot( iTargets[i] ) )
                engclient_cmd( iTargets[i], szCmdArgs[1] ) 
            else 
                client_cmd( iTargets[i], szCmdArgs[1] ) 
        }
        
    }else // Server Execute
    {
        server_cmd( szCmdArgs[1] ) 
    }
    return
}
//    __________________
//___/ ExecuteVoteCmd() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Prepares a Voting System for a Server Command
// Actual vote is determined in as 'ReactionVoteCmd' (misc_actions.inc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock ExecuteVoteCmd( iAdminID, iCmdTask, szVoteTitle[], szVoteCmd[], bool:bArena = false, bool:bToggled = false )
{
    // Parse Command Arguments
    new szCmdArgs[2][STR_T]
    UAIO_ExplodeString( szCmdArgs, 2, g_szCmdArgs[iAdminID-1], STR_T-1, ' ' )
    new iToggle

    // Announce Action
    new szActionMsg[STR_M], szAdminTitle[STR_T], szMode[STR_S], szTitle[STR_M]
    get_user_name( iAdminID, szAdminTitle, STR_T-1 )
    format( szTitle, STR_M-1, "%L", LANG_PLAYER, szVoteTitle )
    if( bToggled )
    {
        iToggle = UAIO_InputSwitch( szCmdArgs[0] )
        format( szMode, STR_S-1, "%L", LANG_PLAYER, g_szMode[iToggle] )
        format( szActionMsg, STR_M-1, "%L", LANG_PLAYER, "EXEC_VOTE_CMD1", PLUGIN_MOD, szAdminTitle, szTitle, szMode )
    }else
    {
        format( szActionMsg, STR_M-1, "%L", LANG_PLAYER, "EXEC_VOTE_CMD1", PLUGIN_MOD, szAdminTitle, szTitle, szCmdArgs[0] )
    }
    UAIO_AnnounceAction( iAdminID, szActionMsg )

    // Display Menu to All Players
    new szMenuBody[MENU_SIZE]
    new iKeys = (1<<0|1<<1)
    new iLen = format( szMenuBody, MENU_SIZE-1, "\yUAIO Vote Menu\w^n" )
    if( bArena )
    {
        format( szMode, STR_S-1, "%L", LANG_PLAYER, g_szMode[str_to_num(szCmdArgs[0])] )
        iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "EXEC_VOTE_CMD2", szTitle, szMode )
    }else
    {
        iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "EXEC_VOTE_CMD2", szTitle, szCmdArgs[0] )
    }
    iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "EXEC_VOTE_CMD3" )
    iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "EXEC_VOTE_CMD4" )

    // Reset Vote Counters
    g_iVoteCount[0] = g_iVoteCount[1] = 0
    
    // Get Vote Time
    new Float:iNewVoteTime = get_cvar_float("sv_uaio_vote_time") + 2.0
    g_fVoteTimer = get_gametime() + iNewVoteTime
    g_fVoteRatio = get_cvar_float("sv_uaio_vote_ratio")
    g_szVoteCmdLen = format( g_szVoteCmd, STR_T-1, "%s %s", szVoteCmd, szCmdArgs[0] )

    // Send Vote
    new aCmdArgs[4]
    aCmdArgs[1] = iToggle
    aCmdArgs[2] = (bArena) ? 1 : 0
    set_task( iNewVoteTime, "ReactionVoteCmd", iCmdTask, aCmdArgs, 3 )
    show_menu( 0, iKeys, szMenuBody, floatround(iNewVoteTime) )
    return
}

//    __________________________
//___/ UAIO_CommenceArenaVote() \___________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Prepares to start an Arena Mode Vote
// Actual action performed is called as a call-back passed in as 'szCmdInit'
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UAIO_CommenceArenaVote( iAdminID , iSorE )
{
    new szMenu[STR_L] , iLen , szAction[STR_S] , szAdminTitle[STR_T] , szState[STR_T]
    new szArena[STR_T] , iKeys = (1<<0) | (1<<1)
    get_user_name( iAdminID , szAdminTitle , STR_T)
    iLen = format(szMenu , STR_L-1 , "\yUAIO Vote Menu:^n")
    if(iSorE)
    {
        //Start Arena
        format(szState , STR_T-1 , "%L" , LANG_SERVER , "ARENA_VOTE_START")
        iLen += format(szMenu[iLen] , STR_L-1-iLen , "%L" , LANG_SERVER , "EXEC_VOTE_CMD_ARENA1" , szState)
        iLen += format(szMenu[iLen] , STR_L-1-iLen , "%L" , LANG_SERVER , "EXEC_VOTE_CMD_ARENA2")
        new szWeapons[AR_MAX_GUNS][STR_S]
        for( new i = 0 ; i < g_iWepCount ; i++ )
        {
            UAIO_ArenaWeaponTitle( g_iArenaWeaponConst[i] , szWeapons[i] , STR_S)
            if( i > 5 )
                iLen += format(szMenu[iLen] , STR_L-1-iLen , "^n")
            if( i != (g_iWepCount-1))
                iLen += format(szMenu[iLen] , STR_L-1-iLen , "%L, " , LANG_SERVER , szWeapons[i])
            else
                iLen += format(szMenu[iLen] , STR_L-1-iLen , "and %L" , LANG_SERVER , szWeapons[i])
        }
        format(szState , STR_T-1 , "%L" , LANG_SERVER , g_bArenaGrenades ? "MODE_ENABLED" : "MODE_DISABLED")
        iLen += format(szMenu[iLen] , STR_L-1-iLen , "%L" , LANG_SERVER , "EXEC_VOTE_CMD_ARENA3" , szState)
        iLen += format(szMenu[iLen] , STR_L-1-iLen , "%L" , LANG_SERVER , "EXEC_VOTE_CMD3")
        iLen += format(szMenu[iLen] , STR_L-1-iLen , "%L" , LANG_SERVER , "EXEC_VOTE_CMD4")
        format(szState , STR_T-1 , "%L" , LANG_SERVER , "ARENA_STARTING")
    }
    else
    {
        format(szState , STR_T-1 , "%L" , LANG_SERVER , "ARENA_VOTE_END")
        iLen += format(szMenu[iLen] , STR_L-1-iLen , "%L", LANG_SERVER , "EXEC_VOTE_CMD_ARENA1" , szState)
        iLen += format(szMenu[iLen] , STR_L-1-iLen , "%L", LANG_SERVER , "EXEC_VOTE_CMD3")
        iLen += format(szMenu[iLen] , STR_L-1-iLen , "%L", LANG_SERVER , "EXEC_VOTE_CMD4")
        format(szState , STR_T-1 , "%L" , LANG_SERVER , "ARENA_ENDING")
        
    }
    format(szArena , STR_T-1 , "%L" , LANG_SERVER , "ARENA_ANNOUNCE")
    format(szAction , STR_S-1 , "%L" , LANG_SERVER , "EXEC_VOTE_CMD1" , PLUGIN_MOD , szAdminTitle , szState , szArena)

    // Reset Vote Counters
    g_iVoteCount[0] = g_iVoteCount[1] = 0
    
    // Get Vote Time
    new Float:iNewVoteTime = get_cvar_float("sv_uaio_vote_time") + 2.0
    g_fVoteTimer = get_gametime() + iNewVoteTime
    g_fVoteRatio = get_cvar_float("sv_uaio_vote_ratio")
    g_szVoteCmdLen = format( g_szVoteCmd, STR_T-1, "%s", "ActionVote" )

    // Send Vote
    new aCmdArgs[3]
    aCmdArgs[0] = iAdminID
    aCmdArgs[1] = TASK_V_ARENA
    aCmdArgs[2] = 1
    set_task( iNewVoteTime, "ReactionVoteCmd", TASK_V_ARENA , aCmdArgs, 3 )
    show_menu( 0, iKeys, szMenu, floatround(iNewVoteTime) )
}

//    _____________________
//___/ ExecuteVotePlayer() \________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Prepares a Voting System for a Specifeid Player
// Actual vote is determined in as 'ReactionVotePlayer' (misc_actions.inc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock ExecuteVotePlayer( iAdminID, iCmdTask, szVoteTitle[], szVoteCmd[], bool:bAtTeams = false, szCmdMsgA[]="", szCmdMsgB[]="" )
{
    // Parse Command Arguments
    new szCmdArgs[2][STR_T]
    UAIO_ExplodeString( szCmdArgs, 2, g_szCmdArgs[iAdminID-1], STR_T-1, ' ' )

    new szTitle[STR_M]
    format( szTitle, STR_M-1, "%L", LANG_PLAYER, szVoteTitle )
    
    // Validate Command Parameters
    if( !bAtTeams && (szCmdArgs[0][0] == '@' || szCmdArgs[0][0] == '*') )
    {
        client_print( iAdminID, print_chat, "%L", iAdminID, "EXEC_VOTE_ERROR", PLUGIN_MOD, szTitle )
        return
    }
    
    // Check for Immunity
    new szVictimTitle[STR_T], szActionMsg[STR_M], szAdminTitle[STR_T]
    new iTarget = cmd_target( iAdminID, szCmdArgs[0], 2 )
    if( iTarget > 0 )
    {
        if( UAIO_HasImmunity( iTarget, CMDTYPE_VOTE ) )
        {
            get_user_name( iTarget, szVictimTitle, STR_T-1 )
            console_print( iAdminID, "%L", iAdminID, "EXEC_VOTE_IMMUNE", PLUGIN_MOD, PLUGIN_NAME, szVictimTitle )
            return
        }
    }

    // Announce Action
    new szMsg1[STR_M], szMsg2[STR_M]
    get_user_name( iAdminID, szAdminTitle, STR_T-1 )
    format( szMsg1, STR_M-1, "%L", LANG_PLAYER, szCmdMsgA )
    format( szMsg2, STR_M-1, "%L", LANG_PLAYER, szCmdMsgB )
    
    UAIO_PlayerTitle( iAdminID, szCmdArgs[0], szVictimTitle, STR_T-1 )
    if( szCmdMsgB[0] )
        format( szActionMsg, STR_M-1, "%L", LANG_PLAYER, "EXEC_VOTE_PLAYER1", PLUGIN_MOD, szAdminTitle, szTitle, szVictimTitle, szMsg1, szCmdArgs[1], szMsg2 )
    else
        format( szActionMsg, STR_M-1, "%L", LANG_PLAYER, "EXEC_VOTE_PLAYER2", PLUGIN_MOD, szAdminTitle, szTitle, szVictimTitle )
    UAIO_AnnounceAction( iAdminID, szActionMsg )

    // Display Menu to All Players
    new szMenuBody[MENU_SIZE]
    new iKeys = (1<<0|1<<1)
    new iLen = format( szMenuBody, MENU_SIZE-1, "\yUAIO Vote Menu\w^n" )
    if( szCmdArgs[1][0] )
        iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "^n\r%s %s %s %s %s?\w^n", szTitle, szVictimTitle, szMsg1, szCmdArgs[1], szMsg2 )
    else
        iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "^n\r%s %s?\w^n", szTitle, szVictimTitle )
    iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "EXEC_VOTE_CMD3" )
    iLen += format( szMenuBody[iLen], (MENU_SIZE-1-iLen), "%L", LANG_PLAYER, "EXEC_VOTE_CMD4" )

    // Reset Vote Counters
    g_iVoteCount[0] = g_iVoteCount[1] = 0
    
    // Get Vote Time
    new Float:iNewVoteTime = get_cvar_float("sv_uaio_vote_time") + 2.0
    g_fVoteTimer = get_gametime() + iNewVoteTime
    g_fVoteRatio = get_cvar_float("sv_uaio_vote_ratio")
    g_szVoteCmdLen = format( g_szVoteCmd, STR_T-1, "%s", szVoteCmd )

    // Send Vote
    new aCmdArgs[3]
    aCmdArgs[0] = iAdminID
    aCmdArgs[1] = iCmdTask
    set_task( iNewVoteTime, "ReactionVotePlayer", iCmdTask, aCmdArgs, 2 )
    show_menu( 0, iKeys, szMenuBody, floatround(iNewVoteTime) )
    return
}
