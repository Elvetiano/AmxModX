////////////////////////////////////////////////////////////////////////////////////////////
//   effects.inc                    Version 1.51                       Date: AUG/01/2006
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

#if defined _UAIO_EFFECTS_INCLUDED
  #endinput
#endif
#define _UAIO_EFFECTS_INCLUDED

//    _______________________
//___/ UAIO_AutoExecServer() \______________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Executes an Auto-Exec Command on the Server.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_AutoExecServer( p_szCommand[] )
{
    server_cmd( p_szCommand )
    server_exec()
    return PLUGIN_HANDLED
}
//    _______________________
//___/ UAIO_AutoExecClient() \______________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Executes an Auto-Exec Command on a Client.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_AutoExecClient( p_szCommand[] )
{
    new szData[2][STR_M]
    UAIO_ExplodeString( szData, 2, p_szCommand, STR_M-1, '|' )
    client_cmd( str_to_num(szData[0]), szData[1] )
    return PLUGIN_HANDLED
}
//    __________________
//___/ UAIO_SpeedLoop() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Recursive 1 Second Loop Contolling the Speed of Players with Turbo Mode.
// Only runs if 1 or more players have Turbo Mode.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_SpeedLoop( p_aCmdArgs[] )
{
    new id = p_aCmdArgs[0]
    if( UAIO_HasEffect( id, CMDTYPE_GOOD, UAIO_G_TURBO ) && is_user_alive( id ) && g_bGameOn )
    {
        set_user_maxspeed( id, float(get_cvar_num( "sv_uaio_turbo_speed" )) )
    }else if( is_user_alive( id ) )
    {
        set_user_maxspeed( id, g_fSpeeds[id-1] )
        g_fSpeeds[id-1] = 0.0
        return
    }
    set_task( 1.0, "UAIO_SpeedLoop", TASK_COMMON + TASK_G_TURBO + id, p_aCmdArgs, 1 )
    return
}
//    ____________________
//___/ UAIO_GrenadeLoop() \_________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Recursive 1 Second Loop Contolling Free HE Grenades of Players with Infinite Grenades.
// Only runs if 1 or more players have Infinite Grenades.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_GrenadeLoop( p_aCmdArgs[] )
{
    new id = p_aCmdArgs[0]
    new bool:bHasHE = UAIO_HasEffect( id, CMDTYPE_GOOD, UAIO_G_NADES )
    new bool:bHasFB = UAIO_HasEffect( id, CMDTYPE_GOOD, UAIO_G_FBANGS )
    new bool:bHasSM = UAIO_HasEffect( id, CMDTYPE_GOOD, UAIO_G_SMOKE )   
    
    if( bHasHE || bHasFB || bHasSM )
    {
        if( is_user_alive(id) && g_bGameOn )
        {
            new i, nNum, nWeapon[32]
            new bool:hasNade[3] = false
            get_user_weapons( id, nWeapon, nNum )
            for( i = 0; i < nNum; i++ )
            {
                if( nWeapon[i] == CSW_HEGRENADE ) hasNade[0] = true
                if( nWeapon[i] == CSW_FLASHBANG ) hasNade[1] = true
                if( nWeapon[i] == CSW_SMOKEGRENADE ) hasNade[2] = true
            }
            if( !hasNade[0] && bHasHE ) give_item( id, "weapon_hegrenade" )
            if( !hasNade[1] && bHasFB ) give_item( id, "weapon_flashbang" )
            if( !hasNade[2] && bHasSM ) give_item( id, "weapon_smokegrenade" )
        }
        set_task( 1.0, "UAIO_GrenadeLoop", TASK_COMMON + TASK_G_NADES + id, p_aCmdArgs, 1 )
    }
    return
}
//    _____________________
//___/ UAIO_GrenadeTrail() \________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Only runs when a grenade is thrown.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_GrenadeTrail( p_iUserID )
{
    new iNadeID = get_grenade( p_iUserID )
    if( iNadeID ) UAIO_DrawTrail( iNadeID, 10, 5, g_iBeamColor[get_user_team(p_iUserID)-1] )
    return
}
//    _________________
//___/ UAIO_SeerLoop() \____________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Recursive 1 Second Loop Contolling the Beams of Players with Seer Mode.
// Only runs if 1 or more players have Seer Mode.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_SeerLoop( p_aCmdArgs[] )
{
    new id = p_aCmdArgs[0]
    if( UAIO_HasEffect( id, CMDTYPE_GOOD, UAIO_G_SEER ) )
    {
        if( is_user_alive(id) && g_bGameOn )
        {
            new i, iNum = 0, iPlayers[MAX_PLAYERS]
            if( get_user_team( id ) == TEAM_T )
                get_players( iPlayers, iNum, "ae", "CT" )
            else if( get_user_team( id ) == TEAM_CT )
                get_players( iPlayers, iNum, "ae", "TERRORIST" )
            
            if( iNum > 0 )
                for( i = 0; i < iNum; i++ )
                    UAIO_DrawBeam( id, iPlayers[i], g_iBeamColor[get_user_team(iPlayers[i])-1] )
        }
        set_task( 1.0, "UAIO_SeerLoop", TASK_COMMON + TASK_G_SEER + id, p_aCmdArgs, 1 )
    }
    return
}
//    __________________
//___/ UAIO_TrailLoop() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Recursive 3 Second Loop Contolling the Trails of Entities.
// Only runs if 1 or more players have Player Trails.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_TrailLoop( p_aCmdArgs[] )
{
    new id = p_aCmdArgs[0]
    if( UAIO_HasEffect( id, CMDTYPE_EVIL, UAIO_E_PTRAILS ) )
    {
        if( is_user_alive(id) && g_bGameOn )
        {
            new Float:vVelocity[3]
            get_user_velocity( id, vVelocity )
            if( (vVelocity[0] == 0.0) && (vVelocity[1] == 0.0) && (vVelocity[2] == 0.0) )
            {
            	UAIO_KillTrail( id )
            	UAIO_DrawTrail( id, 45, 8, g_iBeamColor[get_user_team(id)-1] )
            }
        }
        set_task( 3.0, "UAIO_TrailLoop", TASK_COMMON + TASK_E_PTRAILS + id, p_aCmdArgs, 1 )
    }
    return
}
//    ___________________
//___/ UAIO_ShadesLoop() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Recursive 0.2 Second Loop Contolling the Screen Color of Players with Sun Glasses.
// Only runs if 1 or more players have Sun Glasses.
// Sunglasses (Shades) Effect Originally By AssKicR (Slightly Modified)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_ShadesLoop( p_aCmdArgs[] )
{
    new id = p_aCmdArgs[0]
    new iArgs[7] = {15, 15, 12, 0, 0, 0, 0}

    if( UAIO_HasEffect( id, CMDTYPE_GOOD, UAIO_G_SHADES ) )
    {
        if( is_user_alive( id ) && g_bGameOn )
            iArgs[6] = clamp( get_cvar_num( "sv_uaio_shades_alpha" ), 100, 200 )
        set_task( 0.2, "UAIO_ShadesLoop", TASK_COMMON + TASK_G_SHADES + id, p_aCmdArgs, 1 )
    }
    UAIO_FadeScreen( id, iArgs )
    return
}
//    __________________
//___/ UAIO_DrugsLoop() \___________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Recursive Loop Contolling the Effects of the Bad Drugs.
// Only runs if 1 or more players have been Drugged.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_DrugsLoop( p_aCmdArgs[] )
{
    new id = p_aCmdArgs[0]
    if( UAIO_HasEffect( id, CMDTYPE_EVIL, UAIO_E_DRUGS ) )
    {
        if( is_user_alive(id) && g_bGameOn )
        {
            UAIO_AlterFOV( id )
            UAIO_ShakeScreen( id )
        }
        set_task( float(random_num(2,4)), "UAIO_DrugsLoop", TASK_COMMON + TASK_E_DRUGS + id, p_aCmdArgs, 1 )
    }
    return
}
//    ______________________
//___/ UAIO_CrosshairLoop() \_______________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Recursive 0.5 Second Loop Contolling the Effects of Crazy Crosshairs.
// Only runs if 1 or more players have Crazy Crosshairs.
// Original by v3x (Mad Dog), Modified for UAIO
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_CrosshairLoop( p_aCmdArgs[] )
{
    new id = p_aCmdArgs[0]
    if( UAIO_HasEffect( id, CMDTYPE_EVIL, UAIO_E_CRAZYCH ) )
    {
        if( is_user_alive( id ) )
        {
            new iRed =   random_num( 0, 250 )
            new iGreen = random_num( 0, 250 )
            new iBlue =  random_num( 0, 250 )
            client_cmd( id, "cl_crosshair_color ^"%i %i %i^"", iRed, iGreen, iBlue )
            client_cmd( id, "cl_crosshair_size %s", g_szCHSizes[random_num(0,2)] )
            client_cmd( id, "cl_crosshair_translucent %i", random_num(0,1) )
        }
        set_task( 0.5, "UAIO_CrosshairLoop", TASK_COMMON + TASK_E_CRAZYCH + id, p_aCmdArgs, 1 )
    }
    return PLUGIN_HANDLED
}
//    ______________________
//___/ UAIO_IgniteEffects() \_______________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Recursive 0.2 Second Loop Contolling the Flames of Players who are Burning.
// Only runs if 1 or more players are Burning.
// Fire Effects Originally By f117bomb (Slightly Modified)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_IgniteEffects( p_aCmdArgs[] )
{
    new iTarget = p_aCmdArgs[0]

    if( is_user_alive(iTarget) && UAIO_HasEffect( iTarget, CMDTYPE_EVIL, UAIO_E_FIRE ) )
    {
        new iOrigin[3]
        get_user_origin( iTarget, iOrigin )

        message_begin( MSG_BROADCAST, SVC_TEMPENTITY )
        write_byte( TE_SPRITE )
        write_coord( iOrigin[0] )  // coord, coord, coord (position)
        write_coord( iOrigin[1] )
        write_coord( iOrigin[2] )
        write_short( g_sprMFlash ) // short (sprite index)
        write_byte( 20 )           // byte (scale in 0.1's)
        write_byte( 200 )          // byte (brightness)
        message_end()

        message_begin( MSG_BROADCAST, SVC_TEMPENTITY, iOrigin )
        write_byte( TE_SMOKE )
        write_coord( iOrigin[0] )  // coord coord coord (position)
        write_coord( iOrigin[1] )
        write_coord( iOrigin[2] )
        write_short( g_sprSmoke )  // short (sprite index)
        write_byte( 20 )           // byte (scale in 0.1's)
        write_byte( 15 )           // byte (framerate)
        message_end()

        set_task( 0.2, "UAIO_IgniteEffects", TASK_COMMON + TASK_E_FIRE + iTarget, p_aCmdArgs, 1 )
    }
    else
    {
        if( UAIO_HasEffect( iTarget, CMDTYPE_EVIL, UAIO_E_FIRE ) )
        {
            emit_sound( iTarget, CHAN_AUTO, g_szSndScream2, 0.6, ATTN_NORM, 0, PITCH_HIGH )
            client_print( iTarget, print_chat, "%L", LANG_PLAYER, "FLAME_DEATH", PLUGIN_MOD, PLUGIN_NAME )
            UAIO_RemoveEffect( iTarget, CMDTYPE_EVIL, UAIO_E_FIRE )
        }
    }
    return
}
//    _____________________
//___/ UAIO_IgnitePlayer() \________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Recursive 2 Second Loop Igniting Players who get to close to a Burning Player.
// Only runs if 1 or more players are Burning.
// Fire Effects Originally By f117bomb (Slightly Modified)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_IgnitePlayer( p_aCmdArgs[] )
{
    new iTarget = p_aCmdArgs[0]

    if( is_user_alive(iTarget) && UAIO_HasEffect( iTarget, CMDTYPE_EVIL, UAIO_E_FIRE ) )
    {
        new iOrigin[2][3]
        new szTargetName[STR_T], szVictimName[STR_T]
        new i, iPlayers[32], iNum = 0
        new iHealth = get_user_health( iTarget )
        new iDmgAmount = get_cvar_num( "sv_uaio_fire_dmg" )
        get_user_origin( iTarget, iOrigin[0] )

        //create some damage
        set_user_health( iTarget, (iHealth - iDmgAmount) )

        message_begin( MSG_ONE_UNRELIABLE, g_iMsgDamage, _, iTarget )
        write_byte( 30 )             // dmg_save
        write_byte( 30 )             // dmg_take
        write_long( 1<<21 )          // visibleDamageBits
        write_coord( iOrigin[0][0] ) // damageOrigin.x
        write_coord( iOrigin[0][1] ) // damageOrigin.y
        write_coord( iOrigin[0][2] ) // damageOrigin.z
        message_end()

        //create some sound
        emit_sound( iTarget, CHAN_ITEM, g_szSndFlames, 0.6, ATTN_NORM, 0, PITCH_NORM )

        //Ignite Others
        get_players( iPlayers, iNum, "a" )
        for( i = 0; i < iNum; i++ )
        {
            get_user_origin( iPlayers[i], iOrigin[1] )
            if( get_distance( iOrigin[0], iOrigin[1] ) < 100  )
            {
                if( !UAIO_HasEffect( iPlayers[i], CMDTYPE_EVIL, UAIO_E_FIRE ) )
                {
                    get_user_name( iTarget, szTargetName, 31 )
                    get_user_name( iPlayers[i], szVictimName, 31 )
                    emit_sound( iPlayers[i], CHAN_WEAPON, g_szSndScream1, 1.0, ATTN_NORM, 0, PITCH_HIGH )
                    client_print( 0, print_chat, "%L", LANG_PLAYER, "FLAME_SHARE", PLUGIN_MOD, PLUGIN_NAME, szTargetName, szVictimName )
                    UAIO_SetEffect( iPlayers[i], CMDTYPE_EVIL, UAIO_E_FIRE )
                    UAIO_IgnitePlayer( iPlayers[i] )
                    UAIO_IgniteEffects( iPlayers[i] )
                }
            }
        }

        //Call Again in 2 seconds
        set_task( 2.0, "UAIO_IgnitePlayer", TASK_COMMON + TASK_E_FIRE + iTarget + 32, p_aCmdArgs, 1 )
    }
    return
}
//    ______________________
//___/ UAIO_RocketEffects() \_______________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Recursive 0.2 Second Loop Contolling the Rocket of Players who have been Launched!
// Only runs if 1 or more players are Launched as a Human Rocket.
// Rocket Effects Originally By f117bomb (Slightly Modified)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_RocketEffects( p_aCmdArgs[] )
{
    new iTarget = p_aCmdArgs[0]

    if( is_user_alive(iTarget) )
    {
        new iOrigin[3]
        get_user_origin( iTarget, iOrigin )

        message_begin( MSG_ONE_UNRELIABLE, g_iMsgDamage, _, iTarget )
        write_byte( 30 )          // dmg_save
        write_byte( 30 )          // dmg_take
        write_long( 1<<16 )       // visibleDamageBits
        write_coord( iOrigin[0] ) // damageOrigin.x
        write_coord( iOrigin[1] ) // damageOrigin.y
        write_coord( iOrigin[2] ) // damageOrigin.z
        message_end()

        if( g_iRocket_Z[iTarget-1] == iOrigin[2] )
            UAIO_RocketExplode( p_aCmdArgs )
        g_iRocket_Z[iTarget-1] = iOrigin[2]

        //Draw Trail and effects
        message_begin( MSG_BROADCAST, SVC_TEMPENTITY )
        write_byte( TE_SPRITETRAIL )
        write_coord( iOrigin[0] )        // coord, coord, coord (start)
        write_coord( iOrigin[1] )
        write_coord( iOrigin[2] )
        write_coord( iOrigin[0] )        // coord, coord, coord (end)
        write_coord( iOrigin[1] )
        write_coord( iOrigin[2] - 30 )
        write_short( g_sprBFlare )       // short (sprite index)
        write_byte( 5 )                  // byte (count)
        write_byte( 1 )                  // byte (life in 0.1's)
        write_byte( 1 )                  // byte (scale in 0.1's)
        write_byte( 10 )                 // byte (velocity along vector in 10's)
        write_byte( 5 )                  // byte (randomness of velocity in 10's)
        message_end()

        message_begin( MSG_BROADCAST,SVC_TEMPENTITY )
        write_byte( TE_SPRITE )
        write_coord( iOrigin[0] )        // coord, coord, coord (position)
        write_coord( iOrigin[1] )
        write_coord( iOrigin[2] - 30 )
        write_short( g_sprMFlash )       // short (sprite index)
        write_byte( 15 )                 // byte (scale in 0.1's)
        write_byte( 255 )                // byte (brightness)
        message_end()

        set_task( 0.2, "UAIO_RocketEffects", TASK_COMMON + TASK_E_ROCKET + iTarget, p_aCmdArgs, 1 )
    }
    return
}
//    ______________________
//___/ UAIO_RocketExplode() \_______________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Explodes Player when they reach a ceiling or top of map.
// Only runs if 1 or more players are Launched as a Human Rocket.
// Rocket Effects Originally By f117bomb (Slightly Modified)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stock UAIO_RocketExplode( p_aCmdArgs[] )
{
    new iTarget = p_aCmdArgs[0]

    if( is_user_alive(iTarget) ) // If user is alive create effects and user_kill
    {
        new iOrigin[3]
        get_user_origin( iTarget, iOrigin )

        // blast circles
        message_begin( MSG_BROADCAST, SVC_TEMPENTITY, iOrigin )
        write_byte( TE_BEAMCYLINDER )
        write_coord( iOrigin[0] )
        write_coord( iOrigin[1] )
        write_coord( iOrigin[2] - 10 )
        write_coord( iOrigin[0] )
        write_coord( iOrigin[1] )
        write_coord( iOrigin[2] + 1910 )
        write_short( g_sprWhite )
        write_byte( 0 )              // startframe
        write_byte( 0 )              // framerate
        write_byte( 2 )              // life
        write_byte( 16 )             // width
        write_byte( 0 )              // noise
        write_byte( 188 )            // r
        write_byte( 220 )            // g
        write_byte( 255 )            // b
        write_byte( 255 )            //brightness
        write_byte( 0 )              // speed
        message_end()

        message_begin( MSG_BROADCAST, SVC_TEMPENTITY )
        write_byte( TE_EXPLOSION2 )
        write_coord( iOrigin[0] )
        write_coord( iOrigin[1] )
        write_coord( iOrigin[2] )
        write_byte( 188 )            // byte (scale in 0.1's)
        write_byte( 10 )             // byte (framerate)
        message_end()

        message_begin( MSG_BROADCAST, SVC_TEMPENTITY, iOrigin )
        write_byte( TE_SMOKE )
        write_coord( iOrigin[0] )
        write_coord( iOrigin[1] )
        write_coord( iOrigin[2] )
        write_short( g_sprSmoke )
        write_byte( 2 )
        write_byte( 10 )
        message_end()

        user_kill( iTarget, 1 )
    }

    //stop_sound
    emit_sound( iTarget, CHAN_VOICE, g_szSndRocket2, 0.0, 0.0, (1<<5), PITCH_NORM )

    set_user_maxspeed( iTarget, 1.0 )
    set_user_gravity( iTarget, 1.0 )
    return
}
//    ___________________
//___/ UAIO_PoisonLoop() \__________________________________________________________________
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Todo...
// Poison Effects Originally By AssKicR (Slightly Modified)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public UAIO_PoisonLoop( p_aCmdArgs[] )
{
    new iTarget = p_aCmdArgs[0]
    if( is_user_alive(iTarget) && UAIO_HasEffect( iTarget, CMDTYPE_EVIL, UAIO_E_POISON ) )
    {
        new iHealth = get_user_health( iTarget )
        new iDmgAmount = get_cvar_num( "sv_uaio_poison_dmg" )
        new iNewHP = clamp( (iHealth - iDmgAmount), 0, 255 )
        set_user_health( iTarget, iNewHP )
        if( !iNewHP )
        {
            message_begin( MSG_BROADCAST, g_iMsgDeath )
            write_byte( iTarget )
            write_byte( iTarget )
            write_byte( 0 )
            write_string( "infection" )
            message_end()
        }else
        {
	        new iOrigin[3]
	        get_user_origin( iTarget, iOrigin )
	        message_begin( MSG_ONE_UNRELIABLE, g_iMsgDamage, _, iTarget )
	        write_byte( 30 )             // dmg_save
	        write_byte( 30 )             // dmg_take
	        write_long( 1<<21 )          // visibleDamageBits  (1<<21) or (1<<16)
	        write_coord( iOrigin[0] )    // damageOrigin.x
	        write_coord( iOrigin[1] )    // damageOrigin.y
	        write_coord( iOrigin[2] )    // damageOrigin.z
	        message_end()

	        emit_sound( iTarget, CHAN_AUTO, g_szSndPoison, 0.6, ATTN_NORM, 0, PITCH_HIGH )
		}
		
        set_task( 1.0, "UAIO_PoisonLoop", TASK_COMMON + TASK_E_POISON + iTarget, p_aCmdArgs, 1 )
    }
    else
    {
        if( UAIO_HasEffect( iTarget, CMDTYPE_EVIL, UAIO_E_POISON ) )
        {
            emit_sound( iTarget, CHAN_AUTO, g_szSndScream2, 0.6, ATTN_NORM, 0, PITCH_HIGH )
            UAIO_RemoveEffect( iTarget, CMDTYPE_EVIL, UAIO_E_POISON )
        }
    }
    return
}


