////////////////////////////////////////////////////////////////////////////////////////////
//   events.inc                    Version 1.51                       Date: AUG/01/2006
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

#if defined _UAIO_EVENTS_INCLUDED
  #endinput
#endif
#define _UAIO_EVENTS_INCLUDED

//    __________________
//___/ Event_DeathMsg() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Called on Each Player as they Die. Removes Commands not allowed on Dead Players.
// Grants Rewards to Players who have Kill-Rewards.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Event_DeathMsg()
{
    if( !UAIO_PluginEnabled( UAIO_NULL ) )
        return PLUGIN_CONTINUE

    new iKiller = read_data( 1 )
    new iVictim = read_data( 2 )

    // Check for invalid victim id
    if( !is_user_connected(iVictim) || is_user_bot(iVictim) )
        return PLUGIN_CONTINUE

    // Check for invalid attacker id
    if( !is_user_connected(iKiller) || is_user_bot(iKiller) || iVictim == iKiller )
        return PLUGIN_CONTINUE

    // Check if Killer has Bonus Cash Per Kill
    if( UAIO_HasEffect( iKiller, CMDTYPE_GOOD, UAIO_G_BCASH ) )
    {
        new iMax = clamp( get_cvar_num( "sv_uaio_max_bcash" ), 50, 5000 )
        new iMoney = random_num( 50, iMax )
        UAIO_AddMoney( iKiller, iMoney )
        client_print( iKiller, print_chat, "%L", LANG_PLAYER, "BONUS_CASH_AWARD", PLUGIN_MOD, PLUGIN_NAME, iMoney )
    }

    // Remove Bury Effect
    if( UAIO_HasEffect( iVictim, CMDTYPE_EVIL, UAIO_E_BURY ) )
        UAIO_RemoveEffect( iVictim, CMDTYPE_EVIL, UAIO_E_BURY )

    // Remove Player Trails
    if( UAIO_HasEffect( iVictim, CMDTYPE_EVIL, UAIO_E_PTRAILS ) )
        UAIO_KillTrail( iVictim )
    
    return PLUGIN_CONTINUE
}
//    ________________
//___/ Event_Damage() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Called on Each Player as they receive Damage.
// Grants Rewards to Players who have Damage-Rewards.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Event_Damage( id )
{
    if( !UAIO_PluginEnabled( UAIO_NULL ) || !is_user_connected(id) || is_user_bot(id) )
        return PLUGIN_CONTINUE

    new iDamage = read_data( 2 )
    new iWeapon, iAttackerID = get_user_attacker( id, iWeapon )
    //if( !is_user_connected(iAttackerID) || is_user_bot(iAttackerID) || id == iAttackerID )
    //    return PLUGIN_CONTINUE

    // Check if Victim has Mirror Damage; Return Damage to Attacker..
    if( is_user_alive(iAttackerID) && UAIO_HasEffect( id, CMDTYPE_GOOD, UAIO_G_MIRROR ) )
        UAIO_DamagePlayer( iAttackerID, iDamage, get_cvar_num( "sv_uaio_mirror_kill" ) )

    // Check if Victim has True Armor
    if( UAIO_HasEffect( id, CMDTYPE_GOOD, UAIO_G_TRUEAP ) )
    {
        new iAP, iArmor = get_user_armor( id )
        if( iArmor )
        {
            // Armor Takes Half-Damage
            iAP = (iArmor - (iDamage / 2))
            if( iAP < 0 ) iDamage += iAP
            set_user_armor( id, clamp( iAP, 0, 255 ) )
            set_user_health( id, get_user_health( id ) + iDamage )
        }
    }
    return PLUGIN_CONTINUE
}
//    __________________
//___/ Event_ResetHUD() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Called on Each Player when their HUD is Reset. (Could be Beginning/End of round, Spawn, Etc..)
// Determines if they have any Special Effects and Grants them.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Event_ResetHUD( id )
{
    if( !UAIO_PluginEnabled( UAIO_NULL ) )
        return PLUGIN_CONTINUE

    if( UAIO_HasEffect( id, CMDTYPE_GOOD, UAIO_G_GOD ) )
        set_user_godmode( id, 1 )
    if( UAIO_HasEffect( id, CMDTYPE_GOOD, UAIO_G_GRAV ) )
        set_user_gravity( id, g_fGravity[1] )
    if( UAIO_HasEffect( id, CMDTYPE_GOOD, UAIO_G_NOCLIP ) )
        set_user_noclip( id, 1 )
    if( UAIO_HasEffect( id, CMDTYPE_GOOD, UAIO_G_INVIS ) )
        set_user_rendering( id, kRenderFxGlowShell, 0,0,0, kRenderTransAlpha, 1 )
    if( UAIO_HasEffect( id, CMDTYPE_GOOD, UAIO_G_SPY ) )
    {
        if( get_user_team( id ) == TEAM_T )
            UAIO_SetModel( id, random_num(0,3), TEAM_CT )
        else
            UAIO_SetModel( id, random_num(0,3), TEAM_T )
    }
    if( UAIO_HasEffect( id, CMDTYPE_EVIL, UAIO_E_BURY ) )
        UAIO_RemoveEffect( id, CMDTYPE_EVIL, UAIO_E_BURY )
    if( UAIO_HasEffect( id, CMDTYPE_EVIL, UAIO_E_GAG ) )
        set_speak( id, SPEAK_MUTED )
    if( UAIO_HasEffect( id, CMDTYPE_EVIL, UAIO_E_BLANKS ) )
        set_user_hitzones( id, 0, 0 )

    return PLUGIN_CONTINUE
}
//    ___________________
//___/ Event_ChgWeapon() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Called on each player when a weapon animation occurs (shoot, reload, chg weapons, etc..)
// Used to catch very first spawn, and control Arenas.
// Grants Ammo to those with Unlimited Ammo.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Event_ChgWeapon( id )
{
    if( !UAIO_PluginEnabled( UAIO_NULL ) || !is_user_connected( id ) )
        return PLUGIN_CONTINUE

    new i, szCmd[STR_T]
    
    // Catch very first spawn..
    if( g_bIsJoining[id-1] )
    {
        // Call Auto-Exec Delayed Commands
        g_bIsJoining[id-1] = false
        UAIO_UserAExec( id, AUTOEXEC_DELAYED )
        
        // Set Good Commands relating to All/CT/T
        for( i = 0; i < MAX_BITS; i++ )
        {
            // Commands for All
            if( g_iCmdsForAll[TEAM_ALL] & (1<<i) )
            {
                format( szCmd, STR_T-1, "%s #%d %d", g_szGCmdConsole[i], get_user_userid(id), g_iCmdsForAllDur[TEAM_ALL][i] )
                server_cmd( szCmd )
                server_exec()
            }
            // Commands for T
            if( (g_iCmdsForAll[TEAM_T] & (1<<i)) && (get_user_team(id) == TEAM_T) )
            {
                format( szCmd, STR_T-1, "%s #%d %d", g_szGCmdConsole[i], get_user_userid(id), g_iCmdsForAllDur[TEAM_T][i] )
                server_cmd( szCmd )
                server_exec()
            }
            // Commands for CT
            if( (g_iCmdsForAll[TEAM_CT] & (1<<i)) && (get_user_team(id) == TEAM_CT) )
            {
                format( szCmd, STR_T-1, "%s #%d %d", g_szGCmdConsole[i], get_user_userid(id), g_iCmdsForAllDur[TEAM_CT][i] )
                server_cmd( szCmd )
                server_exec()
            }
        }
    }
    
    if( UAIO_HasEffect( id, CMDTYPE_GOOD, UAIO_G_INVIS ) )
        set_user_rendering( id, kRenderFxGlowShell, 0,0,0, kRenderTransAlpha, 1 )

    // Get Weapon Data for Arena & Infinite Ammo
    new iClip, iAmmo
    new iWeaponID = get_user_weapon( id, iClip, iAmmo )
    switch( iWeaponID )
    {   // Allowed in All Arenas:
        case CSW_C4, CSW_KNIFE:            iWeaponID = UAIO_NULL
        case CSW_HEGRENADE , CSW_SMOKEGRENADE , CSW_FLASHBANG:
        {
            if(g_bArenaGrenades)
	            iWeaponID = UAIO_NULL
        }
    }

    // Arena
    if( (g_bArenaEnabled) && (iWeaponID > UAIO_NULL) )
    {
        new bool:bIsValidGun = false
        for( i = 0; i < AR_MAX_GUNS; i++ )
        {
            if( g_iArenaCustom[i] > UAIO_NULL )
            {
                if( iWeaponID == g_iArenaCustom[i] )
                {
                    bIsValidGun = true
                    break
                }
            }else break
        }
        if( !bIsValidGun ) UAIO_DropWeapon( id, iWeaponID )
    }
    
    // Check for Shots Fired
    //
    if( g_iCurWeapon[id-1][0] != iWeaponID ) // User Changed Weapons..
    {
        g_iCurWeapon[id-1][0] = iWeaponID
        g_iCurWeapon[id-1][1] = iClip
        return PLUGIN_CONTINUE
    }
    if( g_iCurWeapon[id-1][1] < iClip ) // User Reloaded..
    {
        g_iCurWeapon[id-1][1] = iClip
        return PLUGIN_CONTINUE
    }
    if( g_iCurWeapon[id-1][1] == iClip ) // User did something else, but didn't shoot..
        return PLUGIN_CONTINUE
    
    // This far means user shot his/her gun..
    // Save new weapon data..
    g_iCurWeapon[id-1][0] = iWeaponID
    g_iCurWeapon[id-1][1] = iClip

    // Weapon Tracers
    if( UAIO_HasEffect( id, CMDTYPE_EVIL, UAIO_E_WTRAILS ) && iWeaponID > UAIO_NULL )
        UAIO_WeaponTrail( id )

    // Infinite Ammo
    if( UAIO_HasEffect( id, CMDTYPE_GOOD, UAIO_G_AMMO ) && iWeaponID > UAIO_NULL )
    {
        new szWeaponName[STR_T]
        if( iClip == 0 )
        {
            get_weaponname( iWeaponID, szWeaponName, STR_T-1 )
            give_item( id, szWeaponName )
            engclient_cmd( id, szWeaponName )
        }
    }
    return PLUGIN_CONTINUE
}
//    _______________
//___/ Event_Money() \______________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Called on each player when their money amount changes; Used for Infinite Cash.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Event_Money( id )
{
    if( !UAIO_PluginEnabled( UAIO_NULL ) || !UAIO_HasEffect( id, CMDTYPE_GOOD, UAIO_G_ICASH ) )
        return PLUGIN_CONTINUE

    UAIO_SetMoney( id, clamp( get_cvar_num( "sv_uaio_max_icash" ), 100, 16000 ) )
    return PLUGIN_CONTINUE
}
//    ___________________
//___/ Event_NadeThrow() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Called on each player when they throw a grenade.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Event_NadeThrow()
{
    new id = read_data( 1 )
    if( !UAIO_PluginEnabled( UAIO_NULL ) || !UAIO_HasEffect( id, CMDTYPE_EVIL, UAIO_E_GTRAILS ) )
        return PLUGIN_CONTINUE

    set_task( 0.3, "UAIO_GrenadeTrail", id )
    return PLUGIN_CONTINUE
}
//    ________________
//___/ Event_SetFOV() \_____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Called on each player when their Field-of-view changes.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Event_SetFOV( id ) 
{ 
    if( !UAIO_PluginEnabled( UAIO_NULL ) || !UAIO_HasEffect( id, CMDTYPE_EVIL, UAIO_E_DRUGS ) )
        return PLUGIN_CONTINUE
    
    UAIO_AlterFOV( id )
    return PLUGIN_CONTINUE
}
//    ____________________
//___/ Event_RoundStart() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Called when the Round Starts (After FreezeTime) triggering UAIO Game-On!
// Used for Arenas to Strip Old Weapons and Grant New ones.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Event_RoundStart()
{
    if( !UAIO_PluginEnabled( UAIO_NULL ) )
        return PLUGIN_CONTINUE

    // Game On
    g_bGameOn = true
    
    // Arena Mode Spawn
    if( g_bArenaEnabled )
    {
        new iPlayers[MAX_PLAYERS], iNum, i
        get_players( iPlayers, iNum )
        for( i = 0; i < iNum; i++ )
        {
            UAIO_StripWeapons( iPlayers[i] )
            UAIO_ArenaWeapon( iPlayers[i] )
        }
    }
    return PLUGIN_CONTINUE
}
//    __________________
//___/ Event_RoundEnd() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Called when the Round Ends (Team Wins, Objective Complete) triggering UAIO Game-Off!
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Event_RoundEnd()
{
    if( !UAIO_PluginEnabled( UAIO_NULL ) )
        return PLUGIN_CONTINUE

    // Game Off
    g_bGameOn = false
    return PLUGIN_CONTINUE
}
//    _____________________
//___/   Event_TextMsg()   \________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Called when "This weapon cannot be dropped" center text message appears.
// Used for Arenas to drop grenades when bought and they arent in arena.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public Event_TextMsg( id )
{
    if(!g_bArenaEnabled && !g_bArenaGrenades)
        return PLUGIN_CONTINUE

    new clip, ammo, weapon = get_user_weapon(id, clip, ammo)
    if (ammo < 1) // if no weapon ammo
        return PLUGIN_CONTINUE

    for (new i = 0; i <= NADE_TYPE_NUM; ++i)
    {
        if(i == NADE_TYPE_NUM) return PLUGIN_CONTINUE

        if (weapon == NADE_ID_WEAPON[i]) break
    }
    cs_set_user_bpammo(id, weapon, --ammo) // reduce nade ammo over one unit
    if (ammo > 1) // if was Flashbang and still has more ammo
        cs_set_user_bpammo(id , weapon, --ammo)
    engclient_cmd(id, "lastinv") // switch to last weapon used
    client_print(id , print_center , "")
    return PLUGIN_CONTINUE
}