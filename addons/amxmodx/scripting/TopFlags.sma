#include <amxmodx>
#include <amxmisc>
#include <nvault>
#include <csstats>

#if AMXX_VERSION_NUM < 190
    #assert "This plugin requires AMXX 1.9 or above"
#endif

// We define a taskid and a simple 1 hour calculation in seconds
#define TASK_RESET		100
#define HOURINSECONDS 		3600.0
#define DAYINSECONDS 		86400

// We create the enum of cvars
enum cVars 
{
	VarRankRange,
	VarDaysToReset,
	VarFlags[MAX_NAME_LENGTH],
	VarRestrictedFlags[MAX_NAME_LENGTH],
	Float:VarUpdateTime,
	bool:VarRankReset,
	bool:VarSkipAdmins
}

new gCvars[cVars]

// And a global boolean to save top players
new bool:isInTop[MAX_PLAYERS + 1]

public plugin_init()
{
	register_plugin( "Top Flags", "3.3", "iceeedR" )
	register_cvar("TopFlags", "3.3", FCVAR_SERVER | FCVAR_SPONLY)
	register_dictionary("TopFlags.txt")
	
	bind_pcvar_num(create_cvar("tf_ranks", "10", .description = "Range of players that will receive the flags^nbased on rank. (Top 1, 2, 5, 10, 15 etc"), gCvars[VarRankRange])
	bind_pcvar_string(create_cvar("tf_flags", "a", .description = "The flags that TOP players will receive."), gCvars[VarFlags], charsmax(gCvars[VarFlags]))
	bind_pcvar_string(create_cvar("tf_restricted_flags", "bcdefghijkltuv", .description = "Players with any of the flags set there will be ignored."), gCvars[VarRestrictedFlags], charsmax(gCvars[VarRestrictedFlags]))
	bind_pcvar_float(create_cvar("tf_update_rank_time", "120", .description = "Time interval to update ranks", .has_min = true, .min_val = 40.0), gCvars[VarUpdateTime])
	bind_pcvar_num(create_cvar("tf_rank_reset", "1", .description = "A simple way to choose if you wanna reset^nyour rank or not", .has_min = true, .min_val = 0.0, .has_max = true, .max_val = 1.0), gCvars[VarRankReset])
	bind_pcvar_num(create_cvar("tf_days_to_reset", "30", .description = "Set an interval in days for resetting cs stats.", .has_min = true, .min_val = 1.0), gCvars[VarDaysToReset])
	bind_pcvar_num(create_cvar("tf_skip_admins", "1", .description = "SkipAdmins to count topX ?", .has_min = true, .min_val = 0.0, .has_max = true, .max_val = 1.0), gCvars[VarSkipAdmins])

	set_task_ex(gCvars[VarUpdateTime], "UpdateTopPlayers", .flags = SetTask_Repeat)

	AutoExecConfig()
}

public plugin_cfg()
{
	// If the reset rank cvar is active, let's check if it's time to reset rank
	if(gCvars[VarRankReset])
		set_task_ex(0.1, "CheckDate", TASK_RESET, .flags = SetTask_Repeat)
}

public CheckDate()
{
	new iVault , iTimeStamp , iRecordExists

	// We open the Vault
	iVault = nvault_open("TopFlags")
	
	// And check if there is already a recording in the vault
	iRecordExists = nvault_lookup(iVault , "StatsReset" , "" , 0 , iTimeStamp)
	
	// If there is no data in the vault or if there is data but it is time to reset, we will reset this rank.
	if (!iRecordExists || (iRecordExists && ((get_systime() - iTimeStamp) >= (gCvars[VarDaysToReset] * DAYINSECONDS))))
	{
		server_cmd( "amx_cvar csstats_reset 1" )
		nvault_set( iVault , "StatsReset" , "" )
	}

	// We closed the Vault as we won't be using it for now
	nvault_close( iVault )
	
	// We changed the task from 0.1 seconds previously to perform the 1st check to 1 hour (to deal with servers that don't change maps)
	change_task(TASK_RESET, HOURINSECONDS)
}

public client_disconnected(id)
{
	// reset variable id
	isInTop[id] = false
}

public UpdateTopPlayers()
{
	new izStats[STATSX_MAX_STATS], izBody[MAX_BODYHITS], iPlayers[MAX_PLAYERS], iNum, id, iRankPos, MaxRange

	// If the cvar that ignores topX admins is active, add the amount relative to the admins to the maximum range, if not, just take the value of the cvar
	if(gCvars[VarSkipAdmins])
		MaxRange = (gCvars[VarRankRange] + GetAdminsInTopCount())
	else
		MaxRange = gCvars[VarRankRange]

	get_players_ex(iPlayers, iNum, GetPlayers_ExcludeBots | GetPlayers_ExcludeHLTV)
	for(new i = 0; i < iNum; i++)
	{
		id = iPlayers[i]

		// Loop through all players, if the player has restricted flags (it's already admin/vip) ignore it, remembering that we don't ignore TopFlagPlayers here
		if(has_flag(id, gCvars[VarRestrictedFlags]))
		      continue

		// Take the rank position of each
		iRankPos = get_user_stats(id, izStats, izBody)
		
		// If the rank exists and is less than/equal to the one configured in cvar
		if(iRankPos && iRankPos <= MaxRange)
		{
			// We check if it is not a TopFlagPlayer yet, if not, we give the benefit
			if(!isInTop[id])
			{
				client_print_color(0, print_team_default,"%L", 0, "ONTOP", id, gCvars[VarRankRange])
				remove_user_flags(id, ADMIN_USER)
				set_user_flags(id, read_flags(gCvars[VarFlags]))
				isInTop[id] = true
				return PLUGIN_HANDLED
			}
		}
		// If the player is not inside TopX, but is a TopFlagPlayer, we remove its benefit
		else
		{
			if(isInTop[id])
			{
				client_print_color(0, print_team_default,"%L", 0, "TOPOUT", id, gCvars[VarRankRange])
				remove_user_flags(id, read_flags(gCvars[VarFlags]))
				set_user_flags(id, ADMIN_USER)
				isInTop[id] = false
				return PLUGIN_HANDLED
			}
		}
	}
	
	return PLUGIN_HANDLED
}

// We loop through all players, we check among them which ones are admins and among them which ones are inside TopX, returning the value
public GetAdminsInTopCount()
{
        new AdminCount = 0
        new izStats[STATSX_MAX_STATS], izBody[MAX_BODYHITS], iRankPos

        new iPlayers[MAX_PLAYERS], iNum
        get_players_ex(iPlayers, iNum, GetPlayers_ExcludeBots | GetPlayers_ExcludeHLTV)

        for(new i; i < iNum; i++)
        {
                iRankPos = get_user_stats(iPlayers[i], izStats, izBody)

                if(has_flag(iPlayers[i], gCvars[VarRestrictedFlags]) && iRankPos && iRankPos <= gCvars[VarRankRange])
                {
                        AdminCount ++
                }
        }

        return AdminCount
}