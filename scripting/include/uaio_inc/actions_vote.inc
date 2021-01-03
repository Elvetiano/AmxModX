////////////////////////////////////////////////////////////////////////////////////////////
//   actions_vote.inc                    Version 1.51                       Date: AUG/01/2006
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

#if defined _UAIO_VOTEACTIONS_INCLUDED
  #endinput
#endif
#define _UAIO_VOTEACTIONS_INCLUDED

//     ______________________________________________
//    /          Action Routines Section             \_____________
//___/          (Initializes Vote System)             \ Type: Vote \________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    _________________
//___/ ActionVoteMap() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionVoteMap( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Task-Action: 'ActionVoteMap' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteVoteCmd( aCmdArgs[0], TASK_V_MAP, "V_CMD_MAP", "changelevel" )
    return PLUGIN_HANDLED
}
//    __________________
//___/ ActionVoteGrav() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionVoteGrav( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Task-Action: 'ActionVoteGrav' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteVoteCmd( aCmdArgs[0], TASK_V_GRAV, "V_CMD_GRAV", "sv_gravity" )
    return PLUGIN_HANDLED
}
//    ________________
//___/ ActionVoteFF() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionVoteFF( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Task-Action: 'ActionVoteFF' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteVoteCmd( aCmdArgs[0], TASK_V_FF, "V_CMD_FF", "mp_friendlyfire", false, true )
    return PLUGIN_HANDLED
}
//    _____________________
//___/ ActionVoteC4Timer() \________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionVoteC4Timer( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Task-Action: 'ActionVoteC4Timer' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteVoteCmd( aCmdArgs[0], TASK_V_C4TIMER, "V_CMD_C4", "mp_c4timer" )
    return PLUGIN_HANDLED
}
//    ________________
//___/ ActionVoteRR() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionVoteRR( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Task-Action: 'ActionVoteRR' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteVoteCmd( aCmdArgs[0], TASK_V_RR, "V_CMD_RR", "sv_restartround" )
    return PLUGIN_HANDLED
}
//    _____________________
//___/ ActionVoteAlltalk() \________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionVoteAlltalk( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Task-Action: 'ActionVoteAlltalk' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteVoteCmd( aCmdArgs[0], TASK_V_ALLTALK, "V_CMD_ALLTALK", "sv_alltalk", false, true )
    return PLUGIN_HANDLED
}
//    __________________
//___/ ActionVoteKick() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionVoteKick( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Task-Action: 'ActionVoteKick' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif
    
    ExecuteVotePlayer( aCmdArgs[0], TASK_V_KICK, "V_CMD_KICK", "ActionKick", false )
    return PLUGIN_HANDLED
}
//    __________________
//___/ ActionVoteSlap() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionVoteSlap( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Task-Action: 'ActionVoteSlap' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteVotePlayer( aCmdArgs[0], TASK_V_SLAP, "V_CMD_SLAP", "ActionSlap", true, "ACTION_WITH", "ACTION_HEALTH" )
    return PLUGIN_HANDLED
}
//    __________________
//___/ ActionVoteSlay() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionVoteSlay( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Task-Action: 'ActionVoteSlay' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteVotePlayer( aCmdArgs[0], TASK_V_SLAY, "V_CMD_SLAY", "ActionSlay", true )
    return PLUGIN_HANDLED
}
//    __________________
//___/ ActionVoteGlow() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionVoteGlow( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Task-Action: 'ActionVoteGlow' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteVotePlayer( aCmdArgs[0], TASK_V_GLOW, "V_CMD_GLOW", "ActionGlow", true, "ACTION_WITH", "ACTION_COLOR" )
    return PLUGIN_HANDLED
}
//    _________________
//___/ ActionVoteGag() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionVoteGag( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Task-Action: 'ActionVoteGag' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    ExecuteVotePlayer( aCmdArgs[0], TASK_V_GAG, "V_CMD_GAG", "ActionGag", true, "ACTION_FOR", "ACTION_SECONDS" )
    return PLUGIN_HANDLED
}
//    ____________________
//___/ ActionVoteArena() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ActionVoteArena( aCmdArgs[] )
{
    #if defined UAIO_DEBUG_MODE
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Task-Action: 'ActionVoteArena' Called!", PLUGIN_MOD )
        client_print( aCmdArgs[0], print_chat, "%s {VOTE} Parameters: %s", PLUGIN_MOD, g_szCmdArgs[aCmdArgs[0]-1] )
    #endif

    new id = aCmdArgs[0]

    new szWeapons[AR_MAX_GUNS][STR_M]

    new szCmdArgs[2][STR_M]
    argbreak(g_szCmdArgs[id-1] , szCmdArgs[0] , STR_S-1 , szCmdArgs[1] , STR_S-1)
    if(str_to_num(szCmdArgs[1]) == (-1))
        UAIO_CommenceArenaVote( id , AR_END)
    else
    {
        if(!str_to_num(szCmdArgs[0]))
            g_bArenaGrenades = false
        else
            g_bArenaGrenades = true

        g_iWepCount = (1 + UAIO_ExplodeString( szWeapons , AR_MAX_GUNS, szCmdArgs[1] , STR_M-1 , ' ' ))
        for( new i = 0 ; i < AR_MAX_GUNS ; i++ )
        {
            g_iArenaCustom[i] = UAIO_WeaponConst( str_to_num(szWeapons[i]) )
        }
        UAIO_CommenceArenaVote( id , AR_START )
    }
    return PLUGIN_HANDLED
}

//     ______________________________________________
//    /         Reaction Routines Section            \_____________
//___/         (Determines Voting Results)            \ Type: Vote \________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//    ___________________
//___/ ReactionVoteCmd() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionVoteCmd( p_aCmdArgs[] )
{
    new iNumVotes = g_iVoteCount[0] + g_iVoteCount[1]
    new iRatio = (iNumVotes) ? floatround( g_fVoteRatio * float( iNumVotes ), floatround_ceil) : 1
    new iResult = g_iVoteCount[1]

    // Reset Vote Counters
    g_iVoteCount[0] = g_iVoteCount[1] = 0
    
    // Check Voting Ratio
    if( iResult < iRatio )
    {
        client_print( 0, print_chat, "%L", LANG_PLAYER, "VOTE_FAILED", PLUGIN_MOD, iResult, iRatio )
        return PLUGIN_HANDLED
    }
    client_print( 0, print_chat, "%L", LANG_PLAYER, "VOTE_SUCCEEDED", PLUGIN_MOD, iResult, iRatio )
    
    // Check for Arena Vote
    if( p_aCmdArgs[2] )
    {
        if( g_bArenaEnabled )
            UAIO_EndArena( )
        else
            UAIO_StartArena( )
    }
    else
        set_task( 2.0, "InitVoteCmd", TASK_COMMON, g_szVoteCmd, g_szVoteCmdLen )
        
    return PLUGIN_CONTINUE
}
//
//    ______________________
//___/ ReactionVotePlayer() \_______________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Comments..
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public ReactionVotePlayer( p_aCmdArgs[] )
{
    new iNumVotes = g_iVoteCount[0] + g_iVoteCount[1]
    new iRatio = (iNumVotes) ? floatround( g_fVoteRatio * float( iNumVotes ), floatround_ceil) : 1
    new iResult = g_iVoteCount[1]

    // Reset Vote Counters
    g_iVoteCount[0] = g_iVoteCount[1] = 0
    
    // Check Voting Ratio
    if( iResult < iRatio )
    {
        client_print( 0, print_chat, "%L", LANG_PLAYER, "VOTE_FAILED", PLUGIN_MOD, iResult, iRatio )
        return PLUGIN_HANDLED
    }
    client_print( 0, print_chat, "%L", LANG_PLAYER, "VOTE_SUCCEEDED", PLUGIN_MOD, iResult, iRatio )
    //set_task( 2.0, "InitVoteCmd", TASK_COMMON, g_szVoteCmd, g_szVoteCmdLen )
    set_task( 2.0, g_szVoteCmd, (p_aCmdArgs[0]+p_aCmdArgs[1]), p_aCmdArgs, 1 )
    return PLUGIN_CONTINUE
}
//    _______________
//___/ InitVoteCmd() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Calls a Delayed Vote Command
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public InitVoteCmd( szCmd[] )
{
    server_cmd( szCmd )
    return PLUGIN_HANDLED
}