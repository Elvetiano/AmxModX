////////////////////////////////////////////////////////////////////////////////////////////
//   stocks_player.inc                   Version 1.51                       Date: AUG/01/2006
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

#if defined _UAIO_PLAYER_STOCKS_INCLUDED
  #endinput
#endif
#define _UAIO_PLAYER_STOCKS_INCLUDED

//
//     ______________________________________________
//    /         Player Specific Routines             \_____________
//___/                                                \            \________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    _____________________
//___/ UAIO_RevivePlayer() \________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Revives a Dead Player
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_RevivePlayer( p_aCmdArgs[] )
{
    if( (get_user_team( p_aCmdArgs[0] ) == TEAM_SPEC) || is_user_alive( p_aCmdArgs[0] ) )
        return

    //entity_set_int( p_aCmdArgs[0], EV_INT_deadflag, 3 )
    //DispatchSpawn( p_aCmdArgs[0] )
    //spawn( p_aCmdArgs[0] )
    set_task(0.5 , "UAIO_SpawnPlayer" , (3453451) + p_aCmdArgs[0] )
    set_task(0.7 , "UAIO_SpawnPlayer" , (3453451) + p_aCmdArgs[0] )
    set_task(1.0 , "UAIO_GiveWep" ,  (3453451) + p_aCmdArgs[0] )
    return
}

//    ____________________
//___/  UAIO_SpawnPlayer  \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Spawns a player
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_SpawnPlayer( id )
{
    id -= 3453451
    spawn( id )

    return
}

public UAIO_GiveWep( id )
{
    id -= 3453451
    switch( cs_get_user_team( id ) )
    {
         case CS_TEAM_T: {
              give_item(id , "weapon_knife")
              give_item(id , "weapon_glock18")
         }
         case CS_TEAM_CT: {
              give_item(id , "weapon_knife")
              give_item(id , "weapon_usp")
         }
    }
    return
}
//    _________________
//___/ UAIO_SetModel() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Sets a Players CS Player Model
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_SetModel( p_iPlayerIdx, p_iModelIdx, p_iTeam )
{
    switch( p_iTeam )
    {
        case UAIO_NULL: cs_reset_user_model( p_iPlayerIdx )
        case TEAM_T: cs_set_user_model( p_iPlayerIdx, g_szTSkins[p_iModelIdx] )
        case TEAM_CT: cs_set_user_model( p_iPlayerIdx, g_szCTSkins[p_iModelIdx] )
        case TEAM_NONE: cs_set_user_model( p_iPlayerIdx, g_szVIPSkin )
    }
    return
}
//    _________________
//___/ UAIO_AddFrags() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Adds Frags to a Players Frag Count
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_AddFrags( p_iPlayerIdx, p_iFrags )
{
    entity_set_float( p_iPlayerIdx, EV_FL_frags, entity_get_float( p_iPlayerIdx, EV_FL_frags ) + float( p_iFrags ) )
    return
}
//    __________________
//___/ UAIO_AddDeaths() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Adds Deaths to a Players Death Count
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_AddDeaths( p_iPlayerIdx, p_iDeaths )
{
    cs_set_user_deaths( p_iPlayerIdx, cs_get_user_deaths( p_iPlayerIdx ) + p_iDeaths )
    return
}
//    _________________
//___/ UAIO_SetMoney() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Set a Players CS Money Amount
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_SetMoney( p_iPlayerIdx, p_iMoney )
{
    cs_set_user_money( p_iPlayerIdx, clamp( p_iMoney, 0, 16000 ) )
    return
}
//    _________________
//___/ UAIO_AddMoney() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Adds Money to a Players CS Money Amount
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_AddMoney( p_iPlayerIdx, p_iMoney )
{
    new iMoney = cs_get_user_money( p_iPlayerIdx )
    cs_set_user_money( p_iPlayerIdx, clamp( iMoney + p_iMoney, 0, 16000 ) )
    return
}
//    _____________________
//___/ UAIO_StackPlayers() \________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Stacks Player Origins close together (Style = Top or Side)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_StackPlayers( p_iPlayer, p_iStyle  )
{
    new iOrigin[3], i, iNum
    new iPlayers[MAX_PLAYERS]
    new iOffsetY = 36, iOffsetZ = 96

    get_user_origin( p_iPlayer, iOrigin )
    get_players( iPlayers, iNum, "a" )

    if( p_iStyle ) iOffsetZ = 0
    else iOffsetY = 0

    for( i = 0; i < iNum; i++ )
    {
        if( (iPlayers[i] == p_iPlayer) || UAIO_HasImmunity( iPlayers[i], CMDTYPE_MISC ) )
            continue

        iOrigin[1] += iOffsetY
        iOrigin[2] += iOffsetZ
        set_user_origin( iPlayers[i], iOrigin )
    }
    return
}
//    _____________________
//___/ UAIO_DamagePlayer() \________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Damages a Player; similar to getting shot.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_DamagePlayer( p_iPlayerIdx, p_iDamage, p_iKill = 0 )
{
    new iOrigin[3]
    get_user_origin( p_iPlayerIdx, iOrigin )

    if( !p_iKill && (get_user_health(p_iPlayerIdx) <= p_iDamage) )
        p_iDamage = get_user_health(p_iPlayerIdx) - 1
    user_slap( p_iPlayerIdx, p_iDamage )

    message_begin( MSG_ONE_UNRELIABLE, g_iMsgDamage, _, p_iPlayerIdx )
    write_byte( 1 )           // dmg_save
    write_byte( 1 )           // dmg_take
    write_long( DMG_BULLET )  // visibleDamageBits
    write_coord( iOrigin[0] ) // damageOrigin.x
    write_coord( iOrigin[1] ) // damageOrigin.y
    write_coord( iOrigin[2] ) // damageOrigin.z
    message_end()

    return
}
//    ___________________
//___/ UAIO_PlayerList() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Builds an Array of Requested Player IDs according to Console Input Arguments
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_PlayerList( p_iAdminID, p_szArg[], p_iPlayers[] )
{
    new i, iNum = 0, aPlayers[MAX_PLAYERS]
    if( p_szArg[0] == '@' )
    {
        if( equali(p_szArg[1], "T") || equali(p_szArg[1], "TERRORIST") )
        {
            g_iCmdsForAllTeam = TEAM_T
            get_players( aPlayers, iNum, "e", "TERRORIST" )
        }
        else if( equali(p_szArg[1], "C") || equali(p_szArg[1], "CT") )
        {
            g_iCmdsForAllTeam = TEAM_CT
            get_players( aPlayers, iNum, "e", "CT" )
        }
        else if( equali(p_szArg[1], "A") || equali(p_szArg[1], "ALL") )
        {
            g_iCmdsForAllTeam = TEAM_ALL
            get_players( aPlayers, iNum )
        }
        for( i = 0; i < iNum; i++ ) p_iPlayers[i] = aPlayers[i]
    }
    else if( p_szArg[0] == '*' )
    {
        g_iCmdsForAllTeam = TEAM_ALL
        get_players( aPlayers, iNum )
        for( i = 0; i < iNum; i++ ) p_iPlayers[i] = aPlayers[i]
    }
    else
    {
        g_iCmdsForAllTeam = TEAM_NONE
        p_iPlayers[0] = cmd_target( p_iAdminID, p_szArg, 2 )
        if( p_iPlayers[0] > 0 )
            iNum = 1
    }
    return iNum
}
//    ____________________
//___/ UAIO_PlayerTitle() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Determines the Title of Players for Announcements
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_PlayerTitle( p_iAdminID, p_szArg[], p_szTitle[], p_iSize )
{
    new iTarget
    format( p_szTitle, p_iSize, "<Title Not Found>" )
    if( p_szArg[0] == '@' )
    {
        if( equali(p_szArg[1], "T") || equali(p_szArg[1], "TERRORIST") )
            format( p_szTitle, p_iSize, "%L", LANG_PLAYER, "TEAM_TITLE_T" )
        else if( equali(p_szArg[1], "C") || equali(p_szArg[1], "CT") )
            format( p_szTitle, p_iSize, "%L", LANG_PLAYER, "TEAM_TITLE_CT" )
        else if( equali(p_szArg[1], "A") || equali(p_szArg[1], "ALL") )
            format( p_szTitle, p_iSize, "%L", LANG_PLAYER, "TEAM_TITLE_ALL" )
    }
    else if( p_szArg[0] == '*' )
    {
        format( p_szTitle, p_iSize, "%L", LANG_PLAYER, "TEAM_TITLE_ALL" )
    }
    else
    {
        iTarget = cmd_target( p_iAdminID, p_szArg, 2 )
        if( iTarget > 0 ) get_user_name( iTarget, p_szTitle, p_iSize )
    }
    return
}
//    ___________________
//___/ UAIO_GiveWeapon() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Equips a Player with a Specified Weapon
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_GiveWeapon( p_iUserID, iWeaponIdx )
{   
    if( !is_user_alive(p_iUserID) || (iWeaponIdx < 0) || (iWeaponIdx >= WMENU_WEAPONS) )
        return // Invalid User or Weapon

    give_item( p_iUserID, g_szWeaponList[iWeaponIdx] )
    for( new i = 0; i < g_iWeaponData[iWeaponIdx][1]; i++ )
        give_item( p_iUserID, g_szAmmoList[g_iWeaponData[iWeaponIdx][0]] )

    return
}
//    _________________
//___/ UAIO_GiveItem() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Equips a Player with a Specified Item
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_GiveItem( p_iUserID, iItemIdx )
{
    if( !is_user_alive(p_iUserID) || (iItemIdx < 0) || (iItemIdx >= WMENU_ITEMS) )
        return // Invalid User or Item

    if( (iItemIdx == 4) && !get_cvar_num("sv_uaio_smoke_nades") )
        return // Smoke Nades Restricted

    if( iItemIdx == 6 ) // If item is NVGs
    {
        cs_set_user_nvg( p_iUserID, 1 )
        return
    }
    if( !g_bArenaGrenades && ( iItemIdx == 2 || iItemIdx == 3 || iItemIdx == 4 ))
        return
        
    if( iItemIdx == 2 ) // If item is Flashbang, give it twice
        give_item( p_iUserID, g_szItemsList[iItemIdx] )
    give_item( p_iUserID, g_szItemsList[iItemIdx] )

    return
}
//    __________________
//___/ UAIO_GivePAmmo() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Equips a Player with a Primary Ammo
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_GivePAmmo( p_iUserID )
{
    new iWeapons[32], iNum, i, j, k
    new szWeaponName[32]

    // Only give Primary Ammo for Guns Carried
    get_user_weapons( p_iUserID, iWeapons, iNum )
    for( i = 0; i < iNum; i++ )
    {
        get_weaponname( iWeapons[i], szWeaponName, 31 )
        for( j = OFFSET_SHOTGUN; j < WMENU_WEAPONS; j++ )
        {
            if( equali( szWeaponName, g_szWeaponList[j] ) )
            {
                for( k = 0; k < g_iWeaponData[j][1]; k++ )
                    give_item( p_iUserID, g_szAmmoList[g_iWeaponData[j][0]] )
            }
        }
    }
    return
}
//    __________________
//___/ UAIO_GiveSAmmo() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Equips a Player with a Secondary Ammo
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_GiveSAmmo( p_iUserID )
{
    new iWeapons[32], iNum, i, j, k
    new szWeaponName[32]

    // Only give Secondary Ammo for Pistols Carried
    get_user_weapons( p_iUserID, iWeapons, iNum )
    for( i = 0; i < iNum; i++ )
    {
        get_weaponname( iWeapons[i], szWeaponName, 31 )
        for( j = 0; j < OFFSET_SHOTGUN; j++ )
        {
            if( equali( szWeaponName, g_szWeaponList[j] ) )
            {
                for( k = 0; k < g_iWeaponData[j][1]; k++ )
                    give_item( p_iUserID, g_szAmmoList[g_iWeaponData[j][0]] )
            }
        }
    }
    return
}
//    __________________
//___/ UAIO_GiveExtra() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Equips a Player with a Specified Weapon Set (Weapons, Armor, Grenades, Kit)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_GiveExtra( p_iUserID, iExtraIdx )
{
    if( !is_user_alive(p_iUserID) || (iExtraIdx < 0) || (iExtraIdx >= MO_MAX_EXTRA) )
        return

    new i, j
    switch( iExtraIdx )
    {
        case 0:   // Give Player All Weapons (+Ammo)
        {
            for( i = 0; i < WMENU_WEAPONS; i++ )
            {
                give_item( p_iUserID, g_szWeaponList[i] )
                for( j = 0; j < g_iWeaponData[i][1]; j++ )
                    give_item( p_iUserID, g_szAmmoList[g_iWeaponData[i][0]] )
            }
        }
        case 1:   // Give Player M3 Set
        {
            UAIO_GiveWeapon( p_iUserID, 6 )   // [6] = M3
            UAIO_GiveWeapon( p_iUserID, 2 )   // [2] = Deagle
            for( i = 1; i < 6; i++ )
                UAIO_GiveItem( p_iUserID, i ) // Kevlar, Flash/HE/Smoke Grenade, Defuse Kit
        }
        case 2:   // Give Player MP5 Navy Set
        {
            UAIO_GiveWeapon( p_iUserID, 8 )   // [8] = MP5 Navy
            UAIO_GiveWeapon( p_iUserID, 2 )   // [2] = Deagle
            for( i = 1; i < 6; i++ )
                UAIO_GiveItem( p_iUserID, i ) // Kevlar, Flash/HE/Smoke Grenade, Defuse Kit
        }
        case 3:   // Give Player Clarion Set
        {
            UAIO_GiveWeapon( p_iUserID, 13 )  // [13] = Clarion (Famas)
            UAIO_GiveWeapon( p_iUserID, 2 )   // [2]  = Deagle
            for( i = 1; i < 6; i++ )
                UAIO_GiveItem( p_iUserID, i ) // Kevlar, Flash/HE/Smoke Grenade, Defuse Kit
        }
        case 4:   // Give Player Galil Set
        {
            UAIO_GiveWeapon( p_iUserID, 22 )  // [22] = Galil
            UAIO_GiveWeapon( p_iUserID, 2 )   // [2]  = Deagle
            for( i = 1; i < 6; i++ )
                UAIO_GiveItem( p_iUserID, i ) // Kevlar, Flash/HE/Smoke Grenade, Defuse Kit
        }
        case 5:   // Give Player M4A1 Set
        {
            UAIO_GiveWeapon( p_iUserID, 16 )  // [16] = M4A1
            UAIO_GiveWeapon( p_iUserID, 2 )   // [2]  = Deagle
            for( i = 1; i < 6; i++ )
                UAIO_GiveItem( p_iUserID, i ) // Kevlar, Flash/HE/Smoke Grenade, Defuse Kit
        }
        case 6:   // Give Player AK47 Set
        {
            UAIO_GiveWeapon( p_iUserID, 15 )  // [15] = AK47
            UAIO_GiveWeapon( p_iUserID, 2 )   // [2]  = Deagle
            for( i = 1; i < 6; i++ )
                UAIO_GiveItem( p_iUserID, i ) // Kevlar, Flash/HE/Smoke Grenade, Defuse Kit
        }
        case 7:   // Give Player Krieg SG552 Set
        {
            UAIO_GiveWeapon( p_iUserID, 14 )  // [14] = Krieg SG552
            UAIO_GiveWeapon( p_iUserID, 2 )   // [2]  = Deagle
            for( i = 1; i < 6; i++ )
                UAIO_GiveItem( p_iUserID, i ) // Kevlar, Flash/HE/Smoke Grenade, Defuse Kit
        }
        case 8:   // Give Player Bullpup Set
        {
            UAIO_GiveWeapon( p_iUserID, 17 )  // [17] = Bullpup
            UAIO_GiveWeapon( p_iUserID, 2 )   // [2]  = Deagle
            for( i = 1; i < 6; i++ )
                UAIO_GiveItem( p_iUserID, i ) // Kevlar, Flash/HE/Smoke Grenade, Defuse Kit
        }
        case 9:   // Give Player M249 Set
        {
            UAIO_GiveWeapon( p_iUserID, 23 )  // [23] = M249
            UAIO_GiveWeapon( p_iUserID, 2 )   // [2]  = Deagle
            for( i = 1; i < 6; i++ )
                UAIO_GiveItem( p_iUserID, i ) // Kevlar, Flash/HE/Smoke Grenade, Defuse Kit
        }
        case 10:   // Give Player Scout Set
        {
            UAIO_GiveWeapon( p_iUserID, 16 )  // [18] = Scout
            UAIO_GiveWeapon( p_iUserID, 2 )   // [2]  = Deagle
            for( i = 1; i < 6; i++ )
                UAIO_GiveItem( p_iUserID, i ) // Kevlar, Flash/HE/Smoke Grenade, Defuse Kit
        }
        case 11:   // Give Player AutoSniper Set
        {
            UAIO_GiveWeapon( p_iUserID, 20 )    // [20] = CT AutoSniper (G3SG1)
            //UAIO_GiveWeapon( p_iUserID, 21 )  // [21] = T AutoSniper (SG550)
            UAIO_GiveWeapon( p_iUserID, 2 )     // [2]  = Deagle
            for( i = 1; i < 6; i++ )
                UAIO_GiveItem( p_iUserID, i ) // Kevlar, Flash/HE/Smoke Grenade, Defuse Kit
        }
        case 12:   // Give Player AWP Set
        {
            UAIO_GiveWeapon( p_iUserID, 19 )  // [19] = AWP
            UAIO_GiveWeapon( p_iUserID, 2 )   // [2]  = Deagle
            for( i = 1; i < 6; i++ )
                UAIO_GiveItem( p_iUserID, i ) // Kevlar, Flash/HE/Smoke Grenade, Defuse Kit
        }
        case 13:   // Give Player Nades Set
        {
            for( i = 2; i < 5; i++ )
                UAIO_GiveItem( p_iUserID, i ) // Flash/HE/Smoke Grenades
        }
    }
    return
}
//    _____________________
//___/ UAIO_StripWeapons() \________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes All Weapons from a Player and Buries the weapons far underground
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_StripWeapons( p_iUserID )
{
    new iWeapons[MAX_WEAPONS], iNum
    new szWeaponName[STR_T]
    new iOrigin[3]

    get_user_origin( p_iUserID, iOrigin )
    iOrigin[2] -= 1024
    set_user_origin( p_iUserID, iOrigin )

    get_user_weapons( p_iUserID, iWeapons, iNum )
    for( new i = 0; i < iNum; i++ )
    {
        get_weaponname( iWeapons[i], szWeaponName, STR_T-1 )
        engclient_cmd( p_iUserID, "drop", szWeaponName )
    }
    engclient_cmd( p_iUserID, "weapon_knife" )

    iOrigin[2] += 1028
    set_user_origin( p_iUserID, iOrigin )

    return
}
//    ___________________
//___/ UAIO_DropWeapon() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Removes Current Weapon from a Player and Buries the weapon far underground
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_DropWeapon( p_iUserID, p_iWeaponID )
{
    new iOrigin[3], szWeaponName[STR_T]
    get_user_origin( p_iUserID, iOrigin )
    iOrigin[2] -= 1024
    set_user_origin( p_iUserID, iOrigin )
    get_weaponname( p_iWeaponID, szWeaponName, STR_T-1 )
    client_cmd( p_iUserID, "drop", szWeaponName )
    iOrigin[2] += 1028
    set_user_origin( p_iUserID, iOrigin )
    return
}
//    _________________
//___/ UAIO_DrawBeam() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Draws a Beam Sprite between 2 Players
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_DrawBeam( p_iUser1, p_iUser2, p_iColor[] )
{
    message_begin( MSG_ONE_UNRELIABLE, SVC_TEMPENTITY, _, p_iUser1 )
    write_byte( TE_BEAMENTS )		// Beam attached to 2 entities (eg. Players)
    write_short( p_iUser1 )         // entity 1
    write_short( p_iUser2 )         // entity 2
    write_short( g_sprBeam )        // sprite
    write_byte( 0 )                 // start frame
    write_byte( 10 )                // framerate
    write_byte( BEAM_LIFE )         // life
    write_byte( 10 )                // width
    write_byte( 0 )                 // noise
    write_byte( p_iColor[0] )       // red
    write_byte( p_iColor[1] )       // green
    write_byte( p_iColor[2] )       // blue
    write_byte( p_iColor[3] )       // alpha
    write_byte( 0 )                 // speed
    message_end()
    return
}
//    __________________
//___/ UAIO_DrawTrail() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Draws a Trailing Sprite behind an Entity while moving.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_DrawTrail( p_iEntity, p_iLife, p_iWidth, p_iColor[] )
{
    message_begin( MSG_BROADCAST, SVC_TEMPENTITY )
    write_byte( TE_BEAMFOLLOW )     // Beam following an entity
    write_short( p_iEntity )        // Entity to follow
    write_short( g_sprLaser )       // sprite
    write_byte( p_iLife )           // life (in 0.1's)
    write_byte( p_iWidth )          // width (in 0.1's)
    write_byte( p_iColor[0] )       // red
    write_byte( p_iColor[1] )       // green
    write_byte( p_iColor[2] )       // blue
    write_byte( p_iColor[3] )       // alpha
    message_end()
    return
}
//    ____________________
//___/ UAIO_WeaponTrail() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Draws Weapon Tracer Sprites for each bullet shot.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_WeaponTrail( p_iUserID )
{
    // Get bullet origins
    new vOrigin[3], vHitPoint[3]
    get_user_origin( p_iUserID, vOrigin, 1 )
    get_user_origin( p_iUserID, vHitPoint, 4 )
    vOrigin[2] -= 6;
    
    // Get color index
    new iIdx = get_user_team( p_iUserID ) - 1
    
    // Draw tracers
    message_begin( MSG_ALL, SVC_TEMPENTITY, vOrigin, 0 )
    write_byte( TE_BEAMPOINTS )         // Beam between 2 points
    write_coord( vOrigin[0] )         // Start Origin
    write_coord( vOrigin[1] )
    write_coord( vOrigin[2] )
    write_coord( vHitPoint[0] )       // End Origin
    write_coord( vHitPoint[1] )
    write_coord( vHitPoint[2] )
    write_short( g_sprLaser )	        // sprite
    write_byte( 0 )                     // starting frame
    write_byte( 0 )                     // frame rate
    write_byte( 4 )                     // life in 0.1s
    write_byte( 1 )                     // line width in 0.1u
    write_byte( 0 )                     // noise in 0.1u
    write_byte( g_iBeamColor[iIdx][0] ) // red
    write_byte( g_iBeamColor[iIdx][1] ) // green
    write_byte( g_iBeamColor[iIdx][2] ) // blue
    write_byte( g_iBeamColor[iIdx][3] ) // alpha
    write_byte( 50 )                    // scroll speed
    message_end()
    return
}
//    __________________
//___/ UAIO_KillTrail() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Kills a Trailing Sprite behind a player.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_KillTrail( p_iUser )
{
    message_begin( MSG_BROADCAST, SVC_TEMPENTITY )
    write_byte( TE_KILLBEAM )
    write_short( p_iUser )
    message_end()
    return
}
//    ___________________
//___/ UAIO_FadeScreen() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Fades a Players Screen; Similar to a FlashBang, but Time and Color may be altered
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_FadeScreen( p_iUser, p_iArgs[] )
{
    message_begin( MSG_ONE_UNRELIABLE, g_iMsgScreenFade, _, p_iUser )
    write_short( p_iArgs[0] )     // Fade Time
    write_short( p_iArgs[1] )     // Fade Hold
    write_short( p_iArgs[2] )     // Fade Type (in/out)
    write_byte ( p_iArgs[3] )     // Red
    write_byte ( p_iArgs[4] )     // Green
    write_byte ( p_iArgs[5] )     // Blue
    write_byte ( p_iArgs[6] )     // Alpha
    message_end()
    return
}
//    ____________________
//___/ UAIO_ShakeScreen() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Shakes a Players Screen; Similar to an Explosion Shake
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_ShakeScreen( p_iUser )
{
    message_begin( MSG_ONE_UNRELIABLE, g_iMsgScreenShake, _, p_iUser )
    write_short( 1<<14 )   // amplitude
    write_short( 1<<15 )   // duration
    write_short( 1<<14 )   // frequency
    message_end()
    return
}
//    _________________
//___/ UAIO_AlterFOV() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Randomly alters a Players Field-of-view
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_AlterFOV( p_iUser )
{
    message_begin( MSG_ONE_UNRELIABLE, g_iMsgSetFOV, _, p_iUser )
    write_byte( 170 )
    message_end()
    return
}
//    _________________
//___/ UAIO_ResetFOV() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Resets a Players Field-of-view
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_ResetFOV( p_iUser )
{
    message_begin( MSG_ONE_UNRELIABLE, g_iMsgSetFOV, _, p_iUser )
    write_byte( 90 )
    message_end()
    return
}

