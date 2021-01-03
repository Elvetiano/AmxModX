////////////////////////////////////////////////////////////////////////////////////////////
//   files.inc                    Version 1.51                       Date: AUG/01/2006
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

#if defined _UAIO_FILES_INCLUDED
  #endinput
#endif
#define _UAIO_FILES_INCLUDED

//    _____________________
//___/ UAIO_BuildFileDir() \________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Builds the List of Path+Filenames of Required UAIO Files.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_BuildFileDir()
{
    new szBase[STR_M], szLogMsg[STR_L]
    get_configsdir( szBase, STR_M-1 )
    format( g_szFileMaps,    STR_M-1, "%s/maps.ini",              szBase )
    format( g_szFileWarn,    STR_M-1, "%s/uaio/uaio_warning.htm", szBase )
    format( g_szFileRecruit, STR_M-1, "%s/uaio/uaio_recruit.htm", szBase )
    format( g_szFileAdmins,  STR_M-1, "%s/uaio/uaio_admins.ini",  szBase )
    format( g_szFileGroups,  STR_M-1, "%s/uaio/uaio_groups.ini",  szBase )
    format( g_szFileCExec,   STR_M-1, "%s/uaio/exec_client.ini",  szBase )
    format( g_szFileSExec,   STR_M-1, "%s/uaio/exec_server.ini",  szBase )
    format( g_szFileAExec,   STR_M-1, "%s/uaio/exec_auto.ini",    szBase )

    if( !file_exists( g_szFileMaps ) )
    {
        format( szLogMsg, STR_L-1, "%L", LANG_SERVER, "ERR_FILE_INIT", PLUGIN_MOD, PLUGIN_NAME, g_szFileMaps )
        UAIO_WriteLog( szLogMsg )
        format( g_szFileMaps, STR_M-1, "mapcycle.txt" )
    }
    return
}
//    _________________
//___/ UAIO_ReadMaps() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Reads the Servers Maps File from either maps.ini or mapcycle.txt.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock bool:UAIO_ReadMaps()
{
    new szMapName[STR_L], szLogMsg[STR_L]
    new l, pos = 0
    g_iMapCount = 0

    // Check for Maps File
    if( !file_exists( g_szFileMaps ) )
    {
        format( szLogMsg, STR_L-1, "%L", LANG_SERVER, "ERR_NO_FILE", PLUGIN_MOD, PLUGIN_NAME, g_szFileMaps )
        UAIO_WriteLog( szLogMsg )
        return false
    }

    // Read Maps File
    while( read_file( g_szFileMaps, pos++, szMapName, STR_L-1, l ) && (g_iMapCount < MAX_MAPS) )
    {
        if( szMapName[0] == ';' || !l ) continue
        if( parse( szMapName, g_szMapNames[g_iMapCount], STR_T-1 ) < 1 ) continue
        if( !is_map_valid( g_szMapNames[g_iMapCount] ) ) continue

        g_iMapCount++
    }
    return ( g_iMapCount > 0 )
}
//    ___________________
//___/ UAIO_ReadGroups() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Reads the List of UAIO Groups found in uaio_groups.ini
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock bool:UAIO_ReadGroups()
{
    new l = 0, pos = 0, idx = 0, iTotalGroups = 0
    new szLine[STR_X], szLogMsg[STR_L], szData[4][STR_L]

    // Check for Groups File
    if( !file_exists( g_szFileGroups ) )
    {
        format( szLogMsg, STR_L-1, "%L", LANG_SERVER, "ERR_NO_FILE", PLUGIN_MOD, PLUGIN_NAME, g_szFileGroups )
        UAIO_WriteLog( szLogMsg )
        return false
    }

    // Read Groups File
    while( read_file( g_szFileGroups, pos++, szLine, STR_X-1, l ) )
    {
        if( szLine[0] == ';' || !l ) continue
        parse( szLine, szData[0], STR_L-1, szData[1], STR_L-1, szData[2], STR_L-1, szData[3], STR_L-1 )
        if( equali( szData[0], "group" ) )
        {
            if( equali( szData[2], "vote" ) && (g_iGroupCount[CMDTYPE_VOTE] < MAX_GROUPS) )
            {
                idx = g_iGroupCount[CMDTYPE_VOTE]++
                format( g_szVGroupNames[idx], STR_T-1, "%s", szData[1] )
                g_iVGroupFlags[idx] = UAIO_ReadFlags( szData[3] )
            }
            else if( equali( szData[2], "good" ) && (g_iGroupCount[CMDTYPE_GOOD] < MAX_GROUPS) )
            {
                idx = g_iGroupCount[CMDTYPE_GOOD]++
                format( g_szGGroupNames[idx], STR_T-1, "%s", szData[1] )
                g_iGGroupFlags[idx] = UAIO_ReadFlags( szData[3] )
            }
            else if( equali( szData[2], "evil" ) && (g_iGroupCount[CMDTYPE_EVIL] < MAX_GROUPS) )
            {
                idx = g_iGroupCount[CMDTYPE_EVIL]++
                format( g_szEGroupNames[idx], STR_T-1, "%s", szData[1] )
                g_iEGroupFlags[idx] = UAIO_ReadFlags( szData[3] )
            }
            else if( equali( szData[2], "misc" ) && (g_iGroupCount[CMDTYPE_MISC] < MAX_GROUPS) )
            {
                idx = g_iGroupCount[CMDTYPE_MISC]++
                format( g_szMGroupNames[idx], STR_T-1, "%s", szData[1] )
                g_iMGroupFlags[idx] = UAIO_ReadFlags( szData[3] )
            }
            iTotalGroups++
        }
    }

    // Check Group Count
    if( iTotalGroups < 1 )
    {
        format( szLogMsg, STR_L-1, "%L", LANG_SERVER, "ERR_NO_GROUPS", PLUGIN_MOD, PLUGIN_NAME )
        UAIO_WriteLog( szLogMsg )
        return false
    }

    // Groups Loaded Successfully
    format( szLogMsg, STR_L-1, "%L", LANG_SERVER, "GROUPS_LOADED", PLUGIN_MOD, PLUGIN_NAME, iTotalGroups )
    UAIO_WriteLogDebug( szLogMsg )
    return true
}
//    ___________________
//___/ UAIO_ReadAdmins() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Reads the List of UAIO Admins found in uaio_admins.ini.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock bool:UAIO_ReadAdmins()
{
    new l = 0, pos = 0
    new szLine[STR_X], szLogMsg[STR_L], szData[3][STR_L]

    // Check for Admins File
    if( !file_exists( g_szFileAdmins ) )
    {
        format( szLogMsg, STR_L-1, "%L", LANG_SERVER, "ERR_NO_FILE", PLUGIN_MOD, PLUGIN_NAME, g_szFileAdmins )
        UAIO_WriteLog( szLogMsg )
        return false
    }

    // Read Admins File
    while( read_file( g_szFileAdmins, pos++, szLine, STR_X-1, l ) && (g_iAdminCount < MAX_ADMINS) )
    {
        if( szLine[0] == ';' || !l ) continue
        parse( szLine, szData[0], STR_L-1, szData[1], STR_L-1, szData[2], STR_L-1 )
        if( equali( szData[0], "admin" ) )
        {
            format( g_szAdminID[g_iAdminCount], STR_T-1, "%s", szData[1] )
            format( g_szAdminGroup[g_iAdminCount], STR_L-1, "%s", szData[2] )
            g_iAdminCount++
        }
    }

    // Check Admin Count
    if( g_iAdminCount == 0 )
    {
        format( szLogMsg, STR_L-1, "%L", LANG_SERVER, "ERR_NO_ADMINS", PLUGIN_MOD, PLUGIN_NAME )
        UAIO_WriteLog( szLogMsg )
        return false
    }

    // Admins Loaded Successfully
    format( szLogMsg, STR_L-1, "%L", LANG_SERVER, "ADMINS_LOADED", PLUGIN_MOD, PLUGIN_NAME, g_iAdminCount )
    UAIO_WriteLogDebug( szLogMsg )
    return true
}
//    __________________
//___/ UAIO_ReadCExec() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Reads the List of Client Execute Commands found in exec_client.ini.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock bool:UAIO_ReadCExec()
{
    new l, pos = 0, szLine[STR_X], szLogMsg[STR_L], szData[3][STR_S]

    // Check for Client Exec File
    if( !file_exists( g_szFileCExec ) )
    {
        format( szLogMsg, STR_L-1, "%L", LANG_SERVER, "ERR_NO_FILE", PLUGIN_MOD, PLUGIN_NAME, g_szFileCExec )
        UAIO_WriteLog( szLogMsg )
        return false
    }

    // Read Client Exec File
    while( read_file( g_szFileCExec, pos++, szLine, STR_X-1, l ) && (g_iCExecCount < MAX_EXEC) )
    {
        if( szLine[0] == ';' || !l ) continue

        // [0] title   [1] command   [2] flags
        parse( szLine, szData[0], STR_S-1, szData[1], STR_S-1, szData[2], STR_S-1 )

        // Store Data Globally
        format( g_szCExecTitles[g_iCExecCount], STR_T-1, "%s", szData[0] )
        format( g_szCExecCmds[g_iCExecCount], STR_T-1, "%s", szData[1] )
        g_iCExecFlags[g_iCExecCount] = UAIO_ReadFlags( szData[2] )

        // Fix Command Strings
        while( replace( g_szCExecCmds[g_iCExecCount], STR_T-1, "\'", "^"" ) ) { }

        g_iCExecCount++
    }
    return ( g_iCExecCount > 0 )
}
//    __________________
//___/ UAIO_ReadSExec() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Reads the List of Server Execute Commands found in exec_server.ini.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock bool:UAIO_ReadSExec()
{
    new l, pos = 0, szLine[STR_X], szLogMsg[STR_L], szData[3][STR_S]

    // Check for Server Exec File
    if( !file_exists( g_szFileSExec ) )
    {
        format( szLogMsg, STR_L-1, "%L", LANG_SERVER, "ERR_NO_FILE", PLUGIN_MOD, PLUGIN_NAME, g_szFileSExec )
        UAIO_WriteLog( szLogMsg )
        return false
    }

    // Read Server Exec File
    while( read_file( g_szFileSExec, pos++, szLine, STR_X-1, l ) && (g_iSExecCount < MAX_EXEC) )
    {
        if( szLine[0] == ';' || !l ) continue

        // [0] title   [1] command   [2] flags
        parse( szLine, szData[0], STR_S-1, szData[1], STR_S-1, szData[2], STR_S-1 )

        // Store Data Globally
        format( g_szSExecTitles[g_iSExecCount], STR_T-1, "%s", szData[0] )
        format( g_szSExecCmds[g_iSExecCount], STR_T-1, "%s", szData[1] )
        g_iSExecFlags[g_iSExecCount] = UAIO_ReadFlags( szData[2] )

        // Fix Command Strings
        while( replace( g_szSExecCmds[g_iSExecCount], STR_T-1, "\'", "^"" ) ) { }

        g_iSExecCount++
    }
    return ( g_iSExecCount > 0 )
}
//    __________________
//___/ UAIO_ReadAExec() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Reads the List of Auto-Execute Commands found in exec_auto.ini.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock bool:UAIO_ReadAExec()
{
    new l, pos = 0, szLine[STR_X], szLogMsg[STR_L], szData[3][STR_M]

    // Check for Auto Exec File
    if( !file_exists( g_szFileAExec ) )
    {
        format( szLogMsg, STR_L-1, "%L", LANG_SERVER, "ERR_NO_FILE", PLUGIN_MOD, PLUGIN_NAME, g_szFileAExec )
        UAIO_WriteLog( szLogMsg )
        return false
    }

    // Read Auto Exec File
    while( read_file( g_szFileAExec, pos++, szLine, STR_X-1, l ) && (g_iAExecCount < MAX_EXEC) )
    {
        if( szLine[0] == ';' || !l ) continue

        // [0] user   [1] command   [2] flags
        parse( szLine, szData[0], STR_M-1, szData[1], STR_M-1, szData[2], STR_M-1 )

        //for( i = 0; i < 3; i++ )
        //    remove_quotes( szData[i] )

        // Store Data Globally
        format( g_szAExecUser[g_iAExecCount], STR_T-1, "%s", szData[0] )
        format( g_szAExecCmds[g_iAExecCount], STR_M-1, "%s", szData[1] )
        g_iAExecFlags[g_iAExecCount] = UAIO_ReadFlags( szData[2] )

        // Fix Command Strings
        while( replace( g_szAExecCmds[g_iAExecCount], STR_M-1, "\'", "^"" ) ){ }

        g_iAExecCount++
    }
    return ( g_iAExecCount > 0 )
}

