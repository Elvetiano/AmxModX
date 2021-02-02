#include <amxmodx>
#include <amxmisc>
#include <csstats>
#include <nvault>

#if AMXX_VERSION_NUM < 190
    #assert "This plugin requires AMXX 1.9 or above"
#endif

//#define SKIPADMINS // Coment if you wanna count admins on topX list

new VarRank, VarFlags[MAX_NAME_LENGTH], VarRestrict[MAX_NAME_LENGTH], VarDaysToReset, VarReset

new bool:isTop[MAX_PLAYERS + 1]

public plugin_init()
{
	register_plugin( "Top Flags", "1.8", "iceeedR" )
	register_cvar("TopFlags", "1.8", FCVAR_SERVER | FCVAR_SPONLY)

	bind_pcvar_num(create_cvar("tf_ranks", "5", .description = "Range of players that will receive the flags^nbased on rank. (Top 1, 2, 5, 10, 15 etc"), VarRank)
	bind_pcvar_string(create_cvar("tf_flags", "t", .description = "The flags that TOP players will receive."), VarFlags, charsmax(VarFlags ))
	bind_pcvar_string(create_cvar("tf_restricted", "y", .description = "Players with any of the flags set there will be ignored."), VarRestrict, charsmax(VarRestrict))
	bind_pcvar_num(create_cvar("tf_days_toreset", "31", .description = "Set an interval in days for resetting cs stats.", .has_min = true, .min_val = 1.0), VarDaysToReset)
	bind_pcvar_num(create_cvar("tf_rank_reset", "0", .description = "A simple way to choose if you wanna reset^nyour rank or not", .has_min = true, .min_val = 0.0, .has_max = true, .max_val = 1.0), VarReset)

	set_task_ex(120.0, "UpdateRanks", .flags = SetTask_Repeat)

	AutoExecConfig(.autoCreate = true, .name = "TopFlags")
}

public plugin_cfg()
{
	if(VarReset)
		CheckDate()
}

public UpdateRanks()
{
	new flags = read_flags(VarFlags), iRankPos

	new izStats[STATSX_MAX_STATS] = {0, ...}, izBody[MAX_BODYHITS], iPlayers[MAX_PLAYERS], iNum, id

	get_players_ex(iPlayers, iNum, GetPlayers_ExcludeBots | GetPlayers_ExcludeHLTV)

	for(new i; i < iNum; i++)
	{
		id = iPlayers[i]

		iRankPos = get_user_stats(id, izStats, izBody)

		if(has_flag(id, VarRestrict))
		      continue

		#if defined SKIPADMINS
		if(iRankPos && iRankPos <= VarRank + getAdminCount())
		#else
		if(iRankPos && iRankPos <= VarRank)
		#endif
		{
			if(!isTop[id])
			{
				client_print_color(id, print_team_red, "^x04[OFFICIAL]^x03: You are on^x04 TOP%d^x03 and have won the^x04 VIP flags.", VarRank)
				client_print_color(0, print_team_red,"^x04[OFFICIAL]^x03: %n is in^x04 TOP%d^x03 and won the^x04 VIP flags.", id, VarRank)   
				remove_user_flags(id, ADMIN_USER)
				set_user_flags(id, flags)
				isTop[id] = true
				return PLUGIN_HANDLED
			}
		}
		else
		{
			if(isTop[id])
			{
				client_print_color(id, print_team_red,"^x04[OFFICIAL]^x03: You left the^x04 TOP%d^x03 and lost the^x04 VIP flags.", VarRank)
				client_print_color(0, print_team_red,"^x04[OFFICIAL]^x03: %n left the^x04 TOP%d^x03 and lost the^x04 VIP flags.", id, VarRank)
				remove_user_flags(id, flags)
				set_user_flags(id, ADMIN_USER)
				isTop[id] = false
				return PLUGIN_HANDLED
			}
		}
	}
	return PLUGIN_HANDLED
}
public client_infochanged(id)
{
	if (!is_user_connected(id))
	{
		isTop[id] = false
		UpdateRanks();
	}
	return PLUGIN_CONTINUE
}

public client_putinserver(id)
	isTop[id] = false

public CheckDate()
{
	new iVault , iTimeStamp , iRecordExists
	    
	iVault = nvault_open( "TopFlags" )
	    
	iRecordExists = nvault_lookup( iVault , "StatsReset" , "" , 0 , iTimeStamp )
	    
	if ( !iRecordExists || ( iRecordExists && ( ( get_systime() - iTimeStamp ) >= ( VarDaysToReset * 86400 ) ) ) )
	{
		server_cmd( "amx_cvar csstats_reset 1" )
		nvault_set( iVault , "StatsReset" , "" )
	}
	    
	nvault_close( iVault )
}  

#if defined SKIPADMINS
getAdminCount()
{
        new AdminCount = 0
        new izStats[STATSX_MAX_STATS], izBody[MAX_BODYHITS], iRankPos

        new iPlayers[MAX_PLAYERS], iNum
        get_players_ex(iPlayers, iNum, GetPlayers_ExcludeBots | GetPlayers_ExcludeHLTV)

        for(new i; i < iNum; i++)
        {
                iRankPos = get_user_stats(iPlayers[i], izStats, izBody)

                if(has_flag(iPlayers[i], VarRestrict) && 1 < iRankPos <= VarRank)
                {
                        AdminCount ++
                }
        }

        return AdminCount
}
#endif
