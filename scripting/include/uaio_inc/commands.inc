////////////////////////////////////////////////////////////////////////////////////////////
//   commands.inc                    Version 1.51                       Date: AUG/01/2006
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

#if defined _UAIO_COMMANDS_INCLUDED
  #endinput
#endif
#define _UAIO_COMMANDS_INCLUDED

//    __________________
//___/ ClCmd_UAIOMode() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Toggles Plugin On & Off.  COMMAND = uaio_mode   ACCESS = UAIO_LVL_SUPER
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ClCmd_UAIOMode( id, lvl, cid )
{
    if( !cmd_access( id, lvl, cid, 1 ) )
        return PLUGIN_HANDLED

    if( g_bFileError[ERROR_GROUPS] )
    {
        console_print( id, "%L", LANG_PLAYER, "ERR_MODE_GROUPS", PLUGIN_MOD, PLUGIN_NAME )
        return PLUGIN_HANDLED
    }
    if( g_bFileError[ERROR_ADMINS] )
    {
        console_print( id, "%L", LANG_PLAYER, "ERR_MODE_ADMINS", PLUGIN_MOD, PLUGIN_NAME )
        return PLUGIN_HANDLED
    }

    new szArg[5]
    read_argv( 1, szArg, 4 )
    new nOnOff = UAIO_InputSwitch( szArg )

    UAIO_PluginEnabled( nOnOff )
    new szMode[STR_T]
    format( szMode, STR_T-1, "%L", LANG_PLAYER, g_szMode[nOnOff] )
    console_print( id, "%s %s %s!", PLUGIN_MOD, PLUGIN_NAME, szMode )

    return PLUGIN_HANDLED
}
//    __________________
//___/ ClCmd_UAIOHelp() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays Help Info on UAIO.  COMMAND = uaio_help   ACCESS = UAIO_LVL_USER
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ClCmd_UAIOHelp( id, lvl, cid )
{
    if( !cmd_access( id, lvl, cid, 0 ) )
        return PLUGIN_HANDLED

    if( !UAIO_PluginEnabled( UAIO_NULL ) )
    {
        console_print( id, "%L", LANG_PLAYER, "PLUGIN_DISABLED", PLUGIN_MOD, PLUGIN_NAME )
        if( access( id, UAIO_LVL_SUPER ) )
            console_print( id, "%L", LANG_PLAYER, "ENABLE_PLUGIN", PLUGIN_MOD, PLUGIN_NAME )
        return PLUGIN_HANDLED
    }

    if( !UAIO_HasAdmin( id ) )
    {
        if( access( id, UAIO_LVL_SUPER ) )
        {
            console_print( id, "%L", LANG_PLAYER, "HELP_MSG_NOADMIN1", PLUGIN_MOD, PLUGIN_NAME )
            console_print( id, "%L", LANG_PLAYER, "HELP_MSG_NOADMIN2", PLUGIN_MOD, PLUGIN_NAME, g_szFileAdmins )
            console_print( id, "%L", LANG_PLAYER, "HELP_MSG_NOADMIN3", PLUGIN_MOD, PLUGIN_NAME, g_szFileGroups )
            console_print( id, "%L", LANG_PLAYER, "HELP_MSG_NOADMIN4", PLUGIN_MOD, PLUGIN_NAME )
        }
        else
            console_print( id, "%L", LANG_PLAYER, "HELP_MSG_NOADMIN5", PLUGIN_MOD, PLUGIN_NAME )
        return PLUGIN_HANDLED
    }
    
    new i, iMaxCmds, iCmdType, szArg[6]
    read_argv( 1, szArg, 5 )
    if( containi( szArg, "vote" ) > -1 )
    {
        iCmdType = CMDTYPE_VOTE
        iMaxCmds = MAX_V_COMMANDS
    }
    else if( containi( szArg, "good" ) > -1 )
    {
        iCmdType = CMDTYPE_GOOD
        iMaxCmds = MAX_G_COMMANDS
    }
    else if( containi( szArg, "evil" ) > -1 )
    {
        iCmdType = CMDTYPE_EVIL
        iMaxCmds = MAX_E_COMMANDS
    }
    else if( containi( szArg, "misc" ) > -1 )
    {
        iCmdType = CMDTYPE_MISC
        iMaxCmds = MAX_M_COMMANDS
    }
    else
    {
        console_print( id, "%L", LANG_PLAYER, "HELP_MSG1", PLUGIN_MOD, PLUGIN_NAME )
        console_print( id, "----------------------------------------" )
       
        console_print( id, "%L", LANG_PLAYER, "HELP_MSG2", PLUGIN_MOD, PLUGIN_NAME )
        console_print( id, "%L", LANG_PLAYER, "HELP_MSG3" )
        console_print( id, "%L", LANG_PLAYER, "HELP_MSG4" )
        console_print( id, "%L", LANG_PLAYER, "HELP_MSG5" )
        console_print( id, "%L", LANG_PLAYER, "HELP_MSG6" )
        console_print( id, "%L", LANG_PLAYER, "HELP_MSG7" )
        
        console_print( id, "%L", LANG_PLAYER, "HELP_MSG8" )
        console_print( id, "%L", LANG_PLAYER, "HELP_MSG9" )
        if( get_user_flags( id ) & UAIO_LVL_ADMIN )
        {
            console_print( id, "%L", LANG_PLAYER, "HELP_MSG10" )
            console_print( id, "%L", LANG_PLAYER, "HELP_MSG11" )
        }
        if( get_user_flags( id ) & UAIO_LVL_SUPER )
        {
            console_print( id, "%L", LANG_PLAYER, "HELP_MSG12" )
            console_print( id, "%L", LANG_PLAYER, "HELP_MSG13" )
            console_print( id, "%L", LANG_PLAYER, "HELP_MSG14" )
        }
        console_print( id, "----------------------------------------" )
        return PLUGIN_HANDLED
    }
        
    // Check for Access to Commands
    new szType[STR_T], szUsage[STR_L]
    format( szType, STR_T-1, "%L", LANG_PLAYER, g_szCmdTypeTitles[iCmdType] )
        
    if( g_iAdminCmdBits[id-1][iCmdType] > 0 )
    {
        console_print( id, "%L", LANG_PLAYER, "HELP_MSG15", PLUGIN_NAME, szType )
        console_print( id, "----------------------------------------" )
        console_print( id, "%L", LANG_PLAYER, "HELP_MSG16" )
        console_print( id, "----------------------------------------" )
        for( i = 0; i < iMaxCmds; i++ )
        {
            if( UAIO_HasCmdAccess( id, iCmdType, (1<<i) ) )
            {
                switch( iCmdType )
                {
                    case CMDTYPE_VOTE: 
                    {
                        format( szUsage, STR_L-1, "%L", LANG_PLAYER, g_szVCmdUsage[i] )
                        console_print( id, "%s  %s", g_szVCmdConsole[i], szUsage )
                    }
                    case CMDTYPE_GOOD: 
                    {
                        format( szUsage, STR_L-1, "%L", LANG_PLAYER, g_szGCmdUsage[i] )
                        console_print( id, "%s  %s", g_szGCmdConsole[i], szUsage )
                    }
                    case CMDTYPE_EVIL: 
                    {
                        format( szUsage, STR_L-1, "%L", LANG_PLAYER, g_szECmdUsage[i] )
                        console_print( id, "%s  %s", g_szECmdConsole[i], szUsage )
                    }
                    case CMDTYPE_MISC: 
                    {
                        format( szUsage, STR_L-1, "%L", LANG_PLAYER, g_szMCmdUsage[i] )
                        console_print( id, "%s  %s", g_szMCmdConsole[i], szUsage )
                    }
                } 
            }
        }
        console_print( id, "----------------------------------------" )
    }else
    {
        console_print( id, "----------------------------------------" )
        console_print( id, "%L", LANG_PLAYER, "HELP_MSG17", szType )
        console_print( id, "----------------------------------------" )
    }
    return PLUGIN_HANDLED
}
//    ___________________
//___/ ClCmd_UAIOOrder() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Toggles Menu Display Order.  COMMAND = uaio_order    ACCESS = UAIO_LVL_ADMIN
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ClCmd_UAIOOrder( id, lvl, cid )
{
    if( !cmd_access( id, lvl, cid, 0 ) )
        return PLUGIN_HANDLED

    if( !UAIO_PluginEnabled( UAIO_NULL ) )
    {
        console_print( id, "%L", LANG_PLAYER, "PLUGIN_DISABLED", PLUGIN_MOD, PLUGIN_NAME )
        if( access( id, UAIO_LVL_SUPER ) )
            console_print( id, "%L", LANG_PLAYER, "ENABLE_PLUGIN", PLUGIN_MOD, PLUGIN_NAME )
        return PLUGIN_HANDLED
    }

    if( g_iMenuOrder[id-1] == MO_PLAYERS )
    {
        g_iMenuOrder[id-1] = MO_COMMANDS
        console_print( id, "%L", LANG_PLAYER, "MENU_ORDER_CMDS", PLUGIN_MOD, PLUGIN_NAME )
    }else
    {
        g_iMenuOrder[id-1] = MO_PLAYERS
        console_print( id, "%L", LANG_PLAYER, "MENU_ORDER_PLRS", PLUGIN_MOD, PLUGIN_NAME )
    }
    return PLUGIN_HANDLED
}
//    ___________________
//___/ ClCmd_UAIOGroup() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Displays Players Group Data.   COMMAND = uaio_group   ACCESS = UAIO_LVL_ADMIN
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ClCmd_UAIOGroup( id, lvl, cid )
{
    if( !cmd_access( id, lvl, cid, 0 ) )
        return PLUGIN_HANDLED

    if( !UAIO_PluginEnabled( UAIO_NULL ) )
    {
        console_print( id, "%L", LANG_PLAYER, "PLUGIN_DISABLED", PLUGIN_MOD, PLUGIN_NAME )
        if( access( id, UAIO_LVL_SUPER ) )
            console_print( id, "%L", LANG_PLAYER, "ENABLE_PLUGIN", PLUGIN_MOD, PLUGIN_NAME )
        return PLUGIN_HANDLED
    }

    new i, iTarget, szUsername[STR_T], szArg[STR_T], szFlags[STR_T]
    if( read_argc() < 1 )
    {
        iTarget = id
    }else
    {
        read_argv( 1, szArg, STR_T-1 )
        if( strlen(szArg) > 0 )
            iTarget = cmd_target( id, szArg, 2 )
        else
            iTarget = id
    }

    if( iTarget > 0 )
    {
        //if( !UAIO_HasAdmin( iTarget ) ) UAIO_AdminGroups( iTarget )

        get_user_name( iTarget, szUsername, STR_T-1 )
        console_print( id, "%L", LANG_PLAYER, "PLAYER_GROUP_DATA1", szUsername, UAIO_HasAdmin(iTarget)?"1":"0" )
        new szType[STR_T]
        for( i = 0; i < MAX_CMD_TYPES; i++ )
        {
            get_flags( g_iAdminCmdBits[iTarget-1][i], szFlags, STR_T-1 )
            format( szType, STR_T-1, "%L", LANG_PLAYER, g_szCmdTypeTitles[i] )
            console_print( id, "%L", LANG_PLAYER, "PLAYER_GROUP_DATA2", szType, szFlags )
        }
    }else
    {
        console_print( id, "%L", LANG_PLAYER, "PLAYER_GROUP_DATA3", PLUGIN_MOD, szArg )
    }

    return PLUGIN_HANDLED
}
//    ____________________
//___/ ClCmd_UAIOGroups() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Note: Used For Debugging Only..
// Displays Loaded Groups Information.   COMMAND = uaio_groups   ACCESS = UAIO_LVL_SUPER
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ClCmd_UAIOGroups( id, lvl, cid )
{
    if( !cmd_access( id, lvl, cid, 0 ) )
        return PLUGIN_HANDLED

    if( !UAIO_PluginEnabled( UAIO_NULL ) )
    {
        console_print( id, "%L", LANG_PLAYER, "PLUGIN_DISABLED", PLUGIN_MOD, PLUGIN_NAME )
        if( access( id, UAIO_LVL_SUPER ) )
            console_print( id, "%L", LANG_PLAYER, "ENABLE_PLUGIN", PLUGIN_MOD, PLUGIN_NAME )
        return PLUGIN_HANDLED
    }

    new i
    console_print( id, "%L", LANG_PLAYER, "MISC_DATA1" )
    for( i = 0; i < g_iGroupCount[CMDTYPE_VOTE]; i++ )
        console_print( id, "---> %s = %d", g_szVGroupNames[i], g_iVGroupFlags[i] )

    console_print( id, "--------------------------------------------" )
    console_print( id, "%L", LANG_PLAYER, "MISC_DATA2" )
    for( i = 0; i < g_iGroupCount[CMDTYPE_GOOD]; i++ )
        console_print( id, "---> %s = %d", g_szGGroupNames[i], g_iGGroupFlags[i] )

    console_print( id, "--------------------------------------------" )
    console_print( id, "%L", LANG_PLAYER, "MISC_DATA3" )
    for( i = 0; i < g_iGroupCount[CMDTYPE_EVIL]; i++ )
        console_print( id, "---> %s = %d", g_szEGroupNames[i], g_iEGroupFlags[i] )

    console_print( id, "--------------------------------------------" )
    console_print( id, "%L", LANG_PLAYER, "MISC_DATA4" )
    for( i = 0; i < g_iGroupCount[CMDTYPE_MISC]; i++ )
        console_print( id, "---> %s = %d", g_szMGroupNames[i], g_iMGroupFlags[i] )

    return PLUGIN_HANDLED
}
//    ____________________
//___/ ClCmd_UAIOAdmins() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Note: Used For Debugging Only..
// Displays Loaded Admins Information.   COMMAND = uaio_admins   ACCESS = UAIO_LVL_SUPER
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ClCmd_UAIOAdmins( id, lvl, cid )
{
    if( !cmd_access( id, lvl, cid, 0 ) )
        return PLUGIN_HANDLED

    if( !UAIO_PluginEnabled( UAIO_NULL ) )
    {
        console_print( id, "%L", LANG_PLAYER, "PLUGIN_DISABLED", PLUGIN_MOD, PLUGIN_NAME )
        if( access( id, UAIO_LVL_SUPER ) )
            console_print( id, "%L", LANG_PLAYER, "ENABLE_PLUGIN", PLUGIN_MOD, PLUGIN_NAME )
        return PLUGIN_HANDLED
    }

    console_print( id, "%L", LANG_PLAYER, "MISC_DATA5" )
    for( new i = 0; i < g_iAdminCount; i++ )
        console_print( id, "---> %s = %s", g_szAdminID[i], g_szAdminGroup[i] )

    return PLUGIN_HANDLED
}
//    __________________
//___/ ClCmd_CheckSay() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Hooks Client Say Commands to Process Said Text.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ClCmd_CheckSay( id )
{
    new szSayCmd[STR_T], szSpeech[STR_M]
    read_argv( 0, szSayCmd, STR_T-1 )
    read_args( szSpeech, STR_M-1 )
    
    if( !UAIO_PluginEnabled( UAIO_NULL ) )
        return PLUGIN_CONTINUE
        
    // Check for Help Request
    if( containi( szSpeech, "/uaio" ) > -1 )
    {
        client_print( id, print_chat, "%L", LANG_PLAYER, "PLUGIN_DESC", PLUGIN_MOD, PLUGIN_NAME, PLUGIN_AUTHOR )
        client_print( id, print_chat, "%L", LANG_PLAYER, "PLUGIN_HELP", PLUGIN_MOD )
        return PLUGIN_HANDLED        
    }

    if( UAIO_HasEffect( id, CMDTYPE_EVIL, UAIO_E_GAG ) )
    {
        client_print( id, print_chat, "%L", LANG_PLAYER, "USER_IS_GAGGED", PLUGIN_MOD )
        return PLUGIN_HANDLED
    }

    new i, iNum, iPlayers[MAX_PLAYERS], szPlayerName[STR_T]
    get_players( iPlayers, iNum, "c" )

    for( i = 0; i < iNum; i++ )
    {
        if( UAIO_HasEffect( iPlayers[i], CMDTYPE_GOOD, UAIO_G_EYE ) )
        {
            if( (is_user_alive(id) != is_user_alive(iPlayers[i])) || ((get_user_team(id) != get_user_team(iPlayers[i])) && equali(szSayCmd, "say_team")) )
            {
                get_user_name( id, szPlayerName, STR_T-1 )
                client_print( iPlayers[i], print_chat, "%s [%s] %s: %s", PLUGIN_MOD, PLUGIN_NAME, szPlayerName, szSpeech )
            }
        }
    }
    return PLUGIN_CONTINUE
}
//    _______________
//___/ ClCmd_NoBuy() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Hooks Client Buy Commands.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ClCmd_NoBuy( id )
{
    if( UAIO_HasEffect( id, CMDTYPE_EVIL, UAIO_E_NOBUY ) )
        return PLUGIN_HANDLED
    return PLUGIN_CONTINUE
}
//    _________________
//___/ ClCmd_VoteCmd() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Handles All Vote Commands, Calls Appropriate Function, Stores Parameters Globally
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ClCmd_VoteCmd( id )
{
    // Check if plugin is enabled
    if( !UAIO_PluginEnabled( UAIO_NULL ) )
    {
        client_print( id, print_console, "%L", LANG_PLAYER, "PLUGIN_DISABLED", PLUGIN_MOD, PLUGIN_NAME )
        client_print( id, print_chat, "%L", LANG_PLAYER, "PLUGIN_DISABLED", PLUGIN_MOD, PLUGIN_NAME )
        if( access( id, UAIO_LVL_SUPER ) )
            console_print( id, "%L", LANG_PLAYER, "ENABLE_PLUGIN", PLUGIN_MOD, PLUGIN_NAME )
        return PLUGIN_HANDLED
    }

    // Determine which command was called
    new iCmdIdx, szCurrCmd[16], szLogMsg[STR_L]
    read_argv( 0, szCurrCmd, 15 )
    for( iCmdIdx = 0; iCmdIdx < MAX_V_COMMANDS; iCmdIdx++ )
        if( equali( szCurrCmd, g_szVCmdConsole[iCmdIdx] ) )
            break

    // Check if command was not found
    if( iCmdIdx == MAX_V_COMMANDS )
    {
        format( szLogMsg, STR_L-1, "%L", LANG_PLAYER, "VOTE_CMD_NOTFOUND", PLUGIN_MOD, PLUGIN_NAME, szCurrCmd )
        client_print( id, print_console, szLogMsg )
        UAIO_WriteLog( szLogMsg )
        return PLUGIN_HANDLED
    }

    // Check if a Vote is Allowed
    if( g_fVoteTimer > get_gametime() )
    {
        client_print( id, print_chat, "%L", LANG_PLAYER, "ALREADY_VOTING", PLUGIN_MOD, PLUGIN_NAME )
        return PLUGIN_HANDLED
    }
    if( g_fVoteTimer && ((g_fVoteTimer + get_cvar_float("sv_uaio_vote_delay")) > get_gametime()) )
    {
        client_print( id, print_chat, "%L", LANG_PLAYER, "VOTE_NOT_ALLOWED", PLUGIN_MOD, PLUGIN_NAME )
        return PLUGIN_HANDLED
    }
    
    // Check if user has access to specific command
    if( !UAIO_HasCmdAccess( id, CMDTYPE_VOTE, (1<<iCmdIdx) ) )
    {
        console_print( id, "%L", LANG_PLAYER, "CMD_NO_ACCESS", PLUGIN_MOD, PLUGIN_NAME, g_szVCmdConsole[iCmdIdx] )
        return PLUGIN_HANDLED
    }

    // Check if the command requires arguments when called
    if( g_iVCmdArgCount[iCmdIdx] > 0 )
    {
        // Check if the user passed the right number of arguments
        if( read_argc() < (g_iVCmdArgCount[iCmdIdx] + 1) )
        {
            new szUsage[STR_L]
            format( szUsage, STR_L-1, "%L", LANG_PLAYER, g_szVCmdUsage[iCmdIdx] )
            console_print( id, "%L", LANG_PLAYER, "CMD_USAGE", PLUGIN_MOD, PLUGIN_NAME, g_szVCmdConsole[iCmdIdx], szUsage )
            return PLUGIN_HANDLED
        }
        // Store arguments in global buffer for later use in task-action
        read_args( g_szCmdArgs[id-1], STR_M-1 )
    }

    // Call Task-Action function
    new aTaskArgs[2]
    aTaskArgs[0] = id
    set_task( 0.1, g_szVCmdFunc[iCmdIdx], (TASK_COMMON + id), aTaskArgs, 1 )

    return PLUGIN_HANDLED
}
//    _________________
//___/ ClCmd_GoodCmd() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Handles All Good Commands, Calls Appropriate Function, Stores Parameters Globally
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ClCmd_GoodCmd( id )
{
    // Check if plugin is enabled
    if( !UAIO_PluginEnabled( UAIO_NULL ) )
    {
        client_print( id, print_console, "%L", LANG_PLAYER, "PLUGIN_DISABLED", PLUGIN_MOD, PLUGIN_NAME )
        client_print( id, print_chat, "%L", LANG_PLAYER, "PLUGIN_DISABLED", PLUGIN_MOD, PLUGIN_NAME )
        if( access( id, UAIO_LVL_SUPER ) )
            console_print( id, "%L", LANG_PLAYER, "ENABLE_PLUGIN", PLUGIN_MOD, PLUGIN_NAME )
        return PLUGIN_HANDLED
    }

    // Determine which command was called
    new iCmdIdx, szCurrCmd[16], szLogMsg[STR_L]
    read_argv( 0, szCurrCmd, 15 )
    for( iCmdIdx = 0; iCmdIdx < MAX_G_COMMANDS; iCmdIdx++ )
        if( equali( szCurrCmd, g_szGCmdConsole[iCmdIdx] ) )
            break

    // Check if command was not found
    if( iCmdIdx == MAX_G_COMMANDS )
    {
        format( szLogMsg, STR_L-1, "%L", LANG_PLAYER, "GOOD_CMD_NOTFOUND", PLUGIN_MOD, PLUGIN_NAME, szCurrCmd )
        client_print( id, print_console, szLogMsg )
        UAIO_WriteLog( szLogMsg )
        return PLUGIN_HANDLED
    }

    // Check if user has access to specific command
    if( !UAIO_HasCmdAccess( id, CMDTYPE_GOOD, (1<<iCmdIdx) ) )
    {
        console_print( id, "%L", LANG_PLAYER, "CMD_NO_ACCESS", PLUGIN_MOD, PLUGIN_NAME, g_szGCmdConsole[iCmdIdx] )
        return PLUGIN_HANDLED
    }

    // Check if the command requires arguments when called
    if( g_iGCmdArgCount[iCmdIdx] > 0 )
    {
        // Check if the user passed the right number of arguments
        if( read_argc() < (g_iGCmdArgCount[iCmdIdx] + 1) )
        {
            new szUsage[STR_L]
            format( szUsage, STR_L-1, "%L", LANG_PLAYER, g_szGCmdUsage[iCmdIdx] )
            console_print( id, "%L", LANG_PLAYER, "CMD_USAGE", PLUGIN_MOD, PLUGIN_NAME, g_szGCmdConsole[iCmdIdx], szUsage )
            return PLUGIN_HANDLED
        }
        // Store arguments in global buffer for later use in task-action
        read_args( g_szCmdArgs[id-1], STR_M-1 )
    }

    // Call Task-Action function
    new aTaskArgs[2]
    aTaskArgs[0] = id
    set_task( 0.1, g_szGCmdFunc[iCmdIdx], (TASK_COMMON + id), aTaskArgs, 1 )

    return PLUGIN_HANDLED
}
//    _________________
//___/ ClCmd_EvilCmd() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Handles All Evil Commands, Calls Appropriate Function, Stores Parameters Globally
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ClCmd_EvilCmd( id )
{
    // Check if plugin is enabled
    if( !UAIO_PluginEnabled( UAIO_NULL ) )
    {
        client_print( id, print_console, "%L", LANG_PLAYER, "PLUGIN_DISABLED", PLUGIN_MOD, PLUGIN_NAME )
        client_print( id, print_chat, "%L", LANG_PLAYER, "PLUGIN_DISABLED", PLUGIN_MOD, PLUGIN_NAME )
        if( access( id, UAIO_LVL_SUPER ) )
            console_print( id, "%L", LANG_PLAYER, "ENABLE_PLUGIN", PLUGIN_MOD, PLUGIN_NAME )
        return PLUGIN_HANDLED
    }

    // Determine which command was called
    new iCmdIdx, szCurrCmd[16], szLogMsg[STR_L]
    read_argv( 0, szCurrCmd, 15 )
    for( iCmdIdx = 0; iCmdIdx < MAX_E_COMMANDS; iCmdIdx++ )
        if( equali( szCurrCmd, g_szECmdConsole[iCmdIdx] ) )
            break

    // Check if command was not found
    if( iCmdIdx == MAX_E_COMMANDS )
    {
        format( szLogMsg, STR_L-1, "%L", LANG_PLAYER, "EVIL_CMD_NOTFOUND", PLUGIN_MOD, PLUGIN_NAME, szCurrCmd )
        client_print( id, print_console, szLogMsg )
        UAIO_WriteLog( szLogMsg )
        return PLUGIN_HANDLED
    }

    // Check if user has access to specific command
    if( !UAIO_HasCmdAccess( id, CMDTYPE_EVIL, (1<<iCmdIdx) ) )
    {
        console_print( id, "%L", LANG_PLAYER, "CMD_NO_ACCESS", PLUGIN_MOD, PLUGIN_NAME, g_szECmdConsole[iCmdIdx] )
        return PLUGIN_HANDLED
    }

    // Check if the command requires arguments when called
    if( g_iECmdArgCount[iCmdIdx] > 0 )
    {
        // Check if the user passed the right number of arguments
        if( read_argc() < (g_iECmdArgCount[iCmdIdx] + 1) )
        {
            new szUsage[STR_L]
            format( szUsage, STR_L-1, "%L", LANG_PLAYER, g_szECmdUsage[iCmdIdx] )
            console_print( id, "%L", LANG_PLAYER, "CMD_USAGE", PLUGIN_MOD, PLUGIN_NAME, g_szECmdConsole[iCmdIdx], szUsage )
            return PLUGIN_HANDLED
        }
        // Store arguments in global buffer for later use in task-action
        read_args( g_szCmdArgs[id-1], STR_M-1 )
    }

    // Call Task-Action function
    new aTaskArgs[2]
    aTaskArgs[0] = id
    set_task( 0.1, g_szECmdFunc[iCmdIdx], (TASK_COMMON + id), aTaskArgs, 1 )

    return PLUGIN_HANDLED
}
//    _________________
//___/ ClCmd_MiscCmd() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Handles All Misc Commands, Calls Appropriate Function, Stores Parameters Globally
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ClCmd_MiscCmd( id )
{
    // Check if plugin is enabled
    if( !UAIO_PluginEnabled( UAIO_NULL ) )
    {
        client_print( id, print_console, "%L", LANG_PLAYER, "PLUGIN_DISABLED", PLUGIN_MOD, PLUGIN_NAME )
        client_print( id, print_chat, "%L", LANG_PLAYER, "PLUGIN_DISABLED", PLUGIN_MOD, PLUGIN_NAME )
        if( access( id, UAIO_LVL_SUPER ) )
            console_print( id, "%L", LANG_PLAYER, "ENABLE_PLUGIN", PLUGIN_MOD, PLUGIN_NAME )
        return PLUGIN_HANDLED
    }

    // Determine which command was called
    new iCmdIdx, szCurrCmd[16], szLogMsg[STR_L]
    read_argv( 0, szCurrCmd, 15 )
    for( iCmdIdx = 0; iCmdIdx < MAX_M_COMMANDS; iCmdIdx++ )
        if( equali( szCurrCmd, g_szMCmdConsole[iCmdIdx] ) )
            break

    // Check if command was not found
    if( iCmdIdx == MAX_M_COMMANDS )
    {
        format( szLogMsg, STR_L-1, "%L", LANG_PLAYER, "MISC_CMD_NOTFOUND", PLUGIN_MOD, PLUGIN_NAME, szCurrCmd )
        client_print( id, print_console, szLogMsg )
        UAIO_WriteLog( szLogMsg )
        return PLUGIN_HANDLED
    }

    // Check if user has access to specific command
    if( !UAIO_HasCmdAccess( id, CMDTYPE_MISC, (1<<iCmdIdx) ) )
    {
        console_print( id, "%L", LANG_PLAYER, "CMD_NO_ACCESS", PLUGIN_MOD, PLUGIN_NAME, g_szMCmdConsole[iCmdIdx] )
        return PLUGIN_HANDLED
    }

    // Check if the command requires arguments when called
    if( g_iMCmdArgCount[iCmdIdx] > 0 )
    {
        // Check if the user passed the right number of arguments
        if( read_argc() < (g_iMCmdArgCount[iCmdIdx] + 1) )
        {
            new szUsage[STR_L]
            format( szUsage, STR_L-1, "%L", LANG_PLAYER, g_szMCmdUsage[iCmdIdx] )
            console_print( id, "%L", LANG_PLAYER, "CMD_USAGE", PLUGIN_MOD, PLUGIN_NAME, g_szMCmdConsole[iCmdIdx], szUsage )
            return PLUGIN_HANDLED
        }
        // Store arguments in global buffer for later use in task-action
        read_args( g_szCmdArgs[id-1], STR_M-1 )
    }

    // Call Task-Action function
    new aTaskArgs[2]
    aTaskArgs[0] = id
    set_task( 0.1, g_szMCmdFunc[iCmdIdx], (TASK_COMMON + id), aTaskArgs, 1 )

    return PLUGIN_HANDLED
}
