#define PLUGIN 	"Invizible Spectator"
#define AUTHOR 	"ConnorMcLeod & UNU"
#define VERSION 	"v0.4"
#define PDATE 	"6 th Sep 2015"

#include <amxmodx>
#include <amxmisc>
#include <cstrike>
#include <fakemeta>

#if AMXX_VERSION_NUM < 180
	#define charsmax(%1)	sizeof(%1) - 1
#endif

#define MAX_PLAYERS	32

#define DEAD_FLAG   (1<<0)

#define OFFSET_TEAM 	114    //win
//#define OFFSET_TEAM 139    //linux

#define OFFSET_LINUX	5

#define ACCESS ADMIN_BAN

#define TASK_AFK_CHECK 		142500
#define FREQ_AFK_CHECK 		1.0
#define MAX_WARN 		5


enum {
 	CS_TEAM_UNASSIGNED,
 	CS_TEAM_T,
 	CS_TEAM_CT,
 	CS_TEAM_SPECTATOR
}

new bool:g_roundend
new pcvar_percent
new g_invisible[MAX_PLAYERS+1][2]
new gmsgScoreAttrib, gmsgTeamInfo


new bool:g_bSpec[33]
new Float:g_fLastActivity[33]
new g_iAFKCheck
new g_iAFKTime[33]
new g_iMaxPlayers
new g_iSpecTransfer
new g_iTransferTime
new g_iWarn[33]
new g_vOrigin[33][3]
new CVAR_afk_check
new CVAR_afk_Spec
new CVAR_afk_transfer_time
new g_specteam[33]

public plugin_init() {
	register_plugin(PLUGIN, VERSION, AUTHOR)

	pcvar_percent = register_cvar("amx_inv_dead_percent", "40")

	register_clcmd("amx_spectate", "make_invis", ADMIN_BAN, "Helps admins to spectate but players dont se them as spectators")
	//register_clcmd("amx_spectators", "playersnr",ADMIN_BAN,"Show a list of Invizible Spectators[DEV TESTS]")

	gmsgScoreAttrib = get_user_msgid("ScoreAttrib")
	gmsgTeamInfo = get_user_msgid("TeamInfo")

	register_message( gmsgScoreAttrib, "msg_ScoreAttrib")
	register_message( gmsgTeamInfo, "msg_TeamInfo")

	register_event("HLTV", "eNewRound", "a", "1=0", "2=0")
	register_logevent("eRoundEnd", 2, "1=Round_End")
	register_event("ResetHUD", "eResetHUD", "be")
	register_event("DeathMsg", "eDeathMsg", "a")
	register_dictionary("admin_spec_transfer.txt")
	register_logevent("event_round_end", 2, "0=World triggered", "1=Round_End")
	register_logevent("event_round_start", 2, "0=World triggered", "1=Round_Start")
	// Support of the old menus
	register_clcmd("jointeam", "cmd_jointeam") // new menu
	register_menucmd(register_menuid("Team_Select", 1), 511, "cmd_jointeam") // old menu
	register_clcmd("joinclass", "cmd_joinclass") // new menu
	register_menucmd(register_menuid("Terrorist_Select", 1), 511, "cmd_joinclass") // old menu
	register_menucmd(register_menuid("CT_Select", 1), 511, "cmd_joinclass") // old menu
	CVAR_afk_check = register_cvar("afk_check", "1")
	CVAR_afk_transfer_time = register_cvar("afk_transfer_time", "60")
	//CVAR_afk_Spec = register_cvar("afk_Spec", "1")   //transfer on/off
	
	
	
	
	CVAR_afk_Spec = create_cvar("afk_Spec", "1", FCVAR_NONE, "(0|1) - If admin is AFK will be transfered to inv.spectator", .has_min = true, .min_val = 0.0, .has_max = true, .max_val = 1.0)
	//CVAR_afk_transfer_time = create_cvar("afk_transfer_time", "6", FCVAR_NONE, "(0|1) - If admin is AFK will be transfered to inv.spectator", .has_min = true, .min_val = 6.0, .has_max = true, .max_val = 100.0)
	
	
	
	
	
	
	
	
	AutoExecConfig(true)
}


public playersnr(id)
{
	new players[MAX_PLAYERS], tnum, ctnum
	//get_players(players, tnum, "e", "TERRORIST")
	//get_players(players, ctnum, "e", "CT")
	//client_print(id, print_console, "Terorists number found = %d",tnum)
	//client_print(id, print_console, "Counter number found = %d",ctnum)
	//new team = get_pdata_int(id,OFFSET_TEAM,OFFSET_LINUX)
	//client_print(id, print_console, "Team found pdata = %d",team)
	//client_print(id, print_console, "CS_TEAM_T constant is  = %d",CS_TEAM_T)
	//client_print(id, print_console, "CS_TEAM_CT  constant is  = %d",CS_TEAM_CT)
	new inum, player,pname[33]
	get_players(players, inum)
	tnum=0
	ctnum=0
	for(new i; i < inum; i++)
	{
		player = players[i]
		//userTeam = cs_get_user_team(player);
		//if (cs_get_user_team(player) == CS_TEAM_CT)
		if (_:cs_get_user_team(player)== _:CS_TEAM_CT)
			ctnum++
		if (_:cs_get_user_team(player)== _:CS_TEAM_T)
			tnum++
		if( g_specteam[player] == 1 )
		{
			tnum=tnum + 1
			get_user_name(player, pname, 32)
			client_print(id, print_console, "Found >>>>>>>>>> %s spectator on team Tero",pname)
		}
		if(g_specteam[player] == 2 )
		{
			ctnum=ctnum + 1
			get_user_name(player, pname, 32)
			client_print(id, print_console, "Found >>>>>>>>>> %s spectator on team Counter",pname)
		}
	}
	client_print(id, print_console, "Terorists ++ number found = %d",tnum)
	client_print(id, print_console, "Counter ++ number found = %d",ctnum)
	

	
}












/*
public make_invis(id) {
	if( !(get_user_flags(id) & ADMIN_KICK) )
		return PLUGIN_CONTINUE

	if(g_invisible[id][0])
	{
		client_print(id, print_console, "You're not invisible anymore")
		g_invisible[id][0] = 0
		return PLUGIN_HANDLED
	}
	

	if( is_user_alive(id) )
	{
		client_print(id, print_console, "You have to be dead first to be an invisible spectator !")
		return PLUGIN_HANDLED
	}





	g_invisible[id][0] = 1
	client_print(id, print_console, "You're now an invisible spectator")
	new team = get_pdata_int(id,OFFSET_TEAM,OFFSET_LINUX)
	//client_print(id, print_console, "Numarul tero este = %d,  Numarul counter este = %d",tnum, ctnum)
	//client_print(id, print_console, "Echipa este %d",team)
	new inum, player, players[MAX_PLAYERS], tnum, ctnum
	get_players(players, inum)
	tnum=0
	ctnum=0
	for(new i; i < inum; i++)
		{
			player = players[i]
			//userTeam = cs_get_user_team(player);
			//if (cs_get_user_team(player) == CS_TEAM_CT)
			if (_:cs_get_user_team(player)== CS_TEAM_CT)
				ctnum++
			if (_:cs_get_user_team(player)== CS_TEAM_T)
				tnum++
			if( g_specteam[player] == 1 )
			{
				tnum=tnum + 1
				//get_user_name(player, pname, 32)
				//client_print(id, print_console, "Fund %s spectator on team Tero",pname)
			}
			if(g_specteam[player] == 2 )
			{
				ctnum=ctnum + 1
				//get_user_name(player, pname, 32)
				//client_print(id, print_console, "Fund %s spectator on team Counter",pname)
			}
		}
	if (ctnum < tnum)
		team= 2
	if (tnum < ctnum)
		team= 1
	if (tnum == ctnum)
		team = random(3)
	if( CS_TEAM_T <= team <= CS_TEAM_CT )
	{
		g_invisible[id][1] = team
		set_pdata_int(id, OFFSET_TEAM, CS_TEAM_SPECTATOR)
		g_specteam[id] = team
		//set_pdata_int(id, OFFSET_TEAM, _:CS_TEAM_SPECTATOR,OFFSET_LINUX)
	}
	else
	{	//new players[MAX_PLAYERS], tnum, ctnum
		//get_players(players, tnum, "e", "TERRORIST")
		//get_players(players, ctnum, "e", "CT")
		g_invisible[id][1] = team //ctnum > tnum ? 1 : 2
		g_specteam[id] = team
		
	}
	
	
	
	
	
	
	
	
	send_ScoreAttrib(id, 0)

	new teamname[12]
	switch( g_invisible[id][1] )
	{
		case 1:formatex(teamname, charsmax(teamname), "TERRORIST")
		case 2:formatex(teamname, charsmax(teamname), "CT")
	}
	send_TeamInfo(id, teamname)

	return PLUGIN_HANDLED
}

*/















public make_invis(id, level) {
	if( ~get_user_flags(id) & level )
		return PLUGIN_CONTINUE

	if(g_invisible[id][0])
	{
		client_print(id, print_console, "You're not invisible anymore")
		g_invisible[id][0] = 0
		return PLUGIN_HANDLED
	}
		
	if( is_user_alive(id) )
	{
		new teams = get_user_team(id)
		new frags = get_user_frags ( id )
		new deaths = get_user_deaths ( id )
		//client_print(id, print_console, "You have to be dead first to be an invisible spectator !")
		//return PLUGIN_HANDLED
		user_silentkill(id)
		message_begin( MSG_ONE, get_user_msgid("ScoreAttrib"), _, id ) 
		write_byte( id ) 
		write_byte( 0 )  // 0 - nothing, 1 - dead, 2 - bomb 
		message_end()
		
		message_begin(MSG_ALL, get_user_msgid("ScoreInfo"), _, id )
		write_byte( id ) 
		write_short(frags) 
		write_short(deaths) 
		write_short(0) 
		write_short(teams) 
		message_end() 
	}
	

	g_invisible[id][0] = 1
	client_print(id, print_console, "You're now an invisible spectator")
	/*
	if( callfunc_begin("handle_afkadmin","voteban1_2.amxx") == 1 ) 
    {
        callfunc_push_int(id)
		callfunc_push_int(1)
        callfunc_end()
    }
	
	if( callfunc_begin("handle_afkadmin","afk_manager.amxx") == 1 ) 
    {
        callfunc_push_int(id)
		callfunc_push_int(1)
        callfunc_end()
    }*/
	
	Plugin_Forwards(id, 1);	
	
	

	new team = get_pdata_int(id, OFFSET_TEAM)
	if( _:CS_TEAM_T <= team <= _:CS_TEAM_CT )
	{
		g_invisible[id][1] = team
		set_pdata_int(id, OFFSET_TEAM, _:CS_TEAM_SPECTATOR)
	}
	else
	{
		new players[MAX_PLAYERS], tnum, ctnum
		get_players(players, tnum, "e", "TERRORIST")
		get_players(players, ctnum, "e", "CT")
		g_invisible[id][1] = ctnum > tnum ? 1 : 2
	}

	send_ScoreAttrib(id, 0)

	new teamname[12]
	switch( g_invisible[id][1] )
	{
		case 1:formatex(teamname, charsmax(teamname), "TERRORIST")
		case 2:formatex(teamname, charsmax(teamname), "CT")
	}
	send_TeamInfo(id, teamname)

	return PLUGIN_HANDLED
}


public eDeathMsg() {
	if(g_roundend)
		return

	new players[MAX_PLAYERS], dead, inum, player, Float:percent = get_pcvar_float(pcvar_percent) / 100.0
	get_players(players, dead, "bh")
	get_players(players, inum, "h")

	if( float(dead) / float(inum) < percent) 
		return

	for(new i; i < inum; i++)
	{
		player = players[i]
		if( g_invisible[player][0] )
			send_ScoreAttrib(player, DEAD_FLAG)
	}
}

public eNewRound() {
	g_roundend = false
	new players[MAX_PLAYERS], inum, player
	get_players(players, inum)
	for(new i; i < inum; i++)
	{
		player = players[i]
		if( g_invisible[player][0] )
			send_ScoreAttrib(player, 0)
	}
}

public eRoundEnd() {
	g_roundend = true
	new players[MAX_PLAYERS], inum, player
	get_players(players, inum)
	for(new i; i < inum; i++)
	{
		player = players[i]
		if( g_invisible[player][0] )
			send_ScoreAttrib(player, DEAD_FLAG)
	}
}

public eResetHUD(id) {
	if( g_invisible[id][0] )
	{
		g_invisible[id][0] = 0
		g_specteam[id] = 0
	}
	/*
	if( callfunc_begin("handle_afkadmin","voteban1_2.amxx") == 1 ) 
    {
        callfunc_push_int(id)
		callfunc_push_int(0)
        callfunc_end()
    }*/
	Plugin_Forwards(id, 0);	
}

// Doesn't seem to work so set flag to 0 at NewRound event.
public msg_ScoreAttrib(msg_type, msg_dest, target) {
	if(!g_invisible[get_msg_arg_int(1)][0])
		return PLUGIN_CONTINUE

	new flags = get_msg_arg_int(2)
	if(flags & DEAD_FLAG)
		set_msg_arg_int(2, 0, flags & ~DEAD_FLAG)

	return PLUGIN_CONTINUE 
}

public msg_TeamInfo(msg_type, msg_dest, target) {
	new id = get_msg_arg_int(1)
	if(!g_invisible[id][0])
		return PLUGIN_CONTINUE

	new teamname[12]
	get_msg_arg_string(2, teamname, charsmax(teamname))
	if( g_invisible[id][1] == _:CS_TEAM_T && strcmp(teamname, "TERRORIST") != 0 )
		set_msg_arg_string(2, "TERRORIST")
	else if( g_invisible[id][1] == _:CS_TEAM_CT && strcmp(teamname, "CT") != 0 )
		set_msg_arg_string(2, "CT")

	return PLUGIN_CONTINUE
}

public plugin_cfg(){
	g_iMaxPlayers = get_maxplayers()
}

public client_connect(id){

	// Deselect player as Spectator
	g_bSpec[id] = false

	// Reset positions
	g_vOrigin[id] = {0, 0, 0}

	// Counter reset
	g_iAFKTime[id] = 0
	g_iWarn[id] = 0
}

public client_disconnected(id)
{
	g_invisible[id][0] = 0
	g_iAFKTime[id] = 0
	g_iWarn[id] = 0
	g_bSpec[id] = false
	g_vOrigin[id] = {0, 0, 0}
	g_specteam[id] = 0

}

public event_round_start(){

	// AFK check switched on
	g_iAFKCheck = get_pcvar_num(CVAR_afk_check)
	
	if (g_iAFKCheck)
	{
		// Update spawn positions
		new iPlayers[32], pNum
		get_players(iPlayers, pNum, "a")
		for (new p = 0; p < pNum; p++)
		{
			get_user_origin(iPlayers[p], g_vOrigin[iPlayers[p]])
		}
		// Create loop if not available
		if (!task_exists(TASK_AFK_CHECK)) set_task(FREQ_AFK_CHECK, "func_afk_check", TASK_AFK_CHECK, _, _, "b")
		// Set kick and transfer times
		if (get_pcvar_num(CVAR_afk_transfer_time) < 6) set_pcvar_num(CVAR_afk_transfer_time, 6)
		g_iSpecTransfer = get_pcvar_num(CVAR_afk_Spec)
		g_iTransferTime = get_pcvar_num(CVAR_afk_transfer_time)
	}
	// AFK check switched off
	else
	{
		// Delete loop if available
		if (task_exists(TASK_AFK_CHECK)) remove_task(TASK_AFK_CHECK)
	}
}

public cmd_jointeam(id){

	// Mark player as spectator, otherwise you can avoid the kick by not joining a class.
	g_bSpec[id] = true
	
	new teams = get_user_team(id)
	new frags = get_user_frags ( id )
	new deaths = get_user_deaths ( id )
	
	message_begin(MSG_ALL, get_user_msgid("ScoreInfo"), _, id )
	write_byte( id )
	write_short(frags) 
	write_short(deaths) 
	write_short(0) 
	write_short(teams) 
	message_end() 
}

public cmd_joinclass(id){

	// Deselect player as Spectator
	g_bSpec[id] = false

	// Reset positions
	g_vOrigin[id] = {0, 0, 0}

	// Reset counter
	g_iAFKTime[id] = 0
	g_iWarn[id] = 0
	
	new teams = get_user_team(id)
	new frags = get_user_frags ( id )
	new deaths = get_user_deaths ( id )
	
	message_begin(MSG_ALL, get_user_msgid("ScoreInfo"), _, id )
	write_byte( id )
	write_short(frags) 
	write_short(deaths) 
	write_short(0) 
	write_short(teams) 
	message_end() 
}

public event_round_end(){

	// Check must not be carried out
	g_iAFKCheck = 0
}


public func_afk_check(taskid){
	if (g_iAFKCheck){
		// Check all players
		for (new id = 1; id <= g_iMaxPlayers; id++){

			// Bots don't check
			if (is_user_bot(id)) continue
			
			
			// AFK functions for specs
			if (is_user_connected(id) && !is_user_hltv(id)){
				
				if ((_:cs_get_user_team(id) == _:CS_TEAM_SPECTATOR || _:cs_get_user_team(id) == _:CS_TEAM_UNASSIGNED || g_bSpec[id]) && (g_invisible[id][0] == 0))
				{

					// Increase counter
					g_iAFKTime[id]++

					// Spec-Kick reconverted to invisible spec
					if (g_iAFKTime[id] >= g_iTransferTime - MAX_WARN){
						if (access(id, ACCESS))
						{
							func_transfer_player(id)
						}						
						g_iAFKTime[id] = 0
					}				
				}
			}

			// AFK functions for live players
			if (is_user_alive(id)){

				// Check positions
				if (g_iAFKCheck == 1){
					new vOrigin[3]
					get_user_origin(id, vOrigin)

					if (g_vOrigin[id][0] != vOrigin[0] || g_vOrigin[id][1] != vOrigin[1]){
						g_vOrigin[id][0] = vOrigin[0]
						g_vOrigin[id][1] = vOrigin[1]
						g_vOrigin[id][2] = vOrigin[2]
						g_iAFKTime[id] = 0
						g_iWarn[id] = 0
					}
					else{
						g_iAFKTime[id]++
					}
				}

				// Determine last activity
				else{
					new Float:fLastActivity
					fLastActivity = cs_get_user_lastactivity(id)

					if (fLastActivity != g_fLastActivity[id]){
						g_fLastActivity[id] = fLastActivity
						g_iAFKTime[id] = 0
						g_iWarn[id] = 0
					}
					else{
						g_iAFKTime[id] = floatround((get_gametime() - fLastActivity) / FREQ_AFK_CHECK)
					}
				}

				// Spec switch g_iSpecTransfer
				if (g_iSpecTransfer == 1 && (g_invisible[id][0] == 0))
				{
					if (g_iAFKTime[id] >= g_iTransferTime - MAX_WARN) //6-3 = 3s = 1 loop /15 s (FREQ_AFK_CHECK) = 3+15 = 18s loop = (g_iWarn[id] < MAX_WARN = 3) 3 * 18
					{
						if (access(id, ACCESS))
						{
							func_transfer_player(id)
						}		
					}
				}				
			}
		}
	}
	return PLUGIN_CONTINUE
}



public func_transfer_player(id){

	// Show warning, if not already warned max times
	if (g_iWarn[id] < MAX_WARN){
	//	client_print(id, print_chat, "[ OFFICIAL ] %L", LANG_PLAYER, "AFK_TRANSFER_WARN", floatround(FREQ_AFK_CHECK) * (MAX_WARN - g_iWarn[id]))
		g_iWarn[id]++
		return
	}

	// Actually, the bomb should already have been transferred
	if (pev(id, pev_weapons) & (1 << CSW_C4)){
		engclient_cmd(id, "drop", "weapon_c4")
	}

	// Transfer player
	if (is_user_alive(id)) user_silentkill(id)
	
	/*if (_:cs_get_user_team(id) == CS_TEAM_SPECTATOR || _:cs_get_user_team(id) == CS_TEAM_UNASSIGNED)
	{
		new players[MAX_PLAYERS], tnum, ctnum
			"TERRORIST")
		get_players(players, ctnum, "e", "CT")
		if (tnum > ctnum)
		{
			cs_set_user_team(id, CS_TEAM_CT)
		}
		if (tnum < ctnum)
		{
			cs_set_user_team(id, CS_TEAM_T)
		}
	}*/
		
	

	//engclient_cmd(id, "amx_spectate")
	client_cmd(id, "amx_spectate")


	// Reset positions
	g_vOrigin[id] = {0, 0, 0}

	// Counter Reset
	g_iAFKTime[id] = 0
	g_iWarn[id] = 0

	// View messages
	new szName[32]
	get_user_name(id, szName, 31)
	new players[ 32 ], index, num, i
	get_players( players, num, "ch" )
	for( i = 0; i < num; i++ )
	{
		index = players[ i ]
		if (access(index, ACCESS))
		{
			//client_print ( index, print_chat, "[OFFICIAL] Kicked %s MAXIM AVERTISMENTE --- CHAT MSG:(%s)", name, said)
			client_print(index, print_chat, "[ OFFICIAL ] %L", LANG_PLAYER, "AFK_TRANSFER_PLAYER", szName)
		}
	}
}


send_ScoreAttrib(id, flags)
{
	message_begin(MSG_ALL, gmsgScoreAttrib, _, 0)
	write_byte(id)
	write_byte(flags)
	message_end()
}

send_TeamInfo(id, teamname[])
{
	message_begin(MSG_ALL, gmsgTeamInfo, _, 0)
	write_byte(id)
	write_string(teamname)
	message_end()
}


public Plugin_Forwards(id, param)
{	new const g_plugins_forward[][] = {
		"voteban1_2",		
		"afk_manager"
	}
	for (new i = 0; i < sizeof g_plugins_forward - 1; i++) 
	{
		new pluginname[32],status[2],file[32]
		format(pluginname, sizeof(pluginname) - 1,"%s.amxx", g_plugins_forward[i])
		new exists = find_plugin_byfile ( pluginname, 1)
		if (exists > 0)
		{
			get_plugin(exists, file, charsmax(file), status, 0, status, 0, status, 0, status, 1)
			switch (status[0])
			{
				// "running"
				case 'r': {
					if( callfunc_begin("handle_afkadmin",pluginname) == 1 ) 
					{
						callfunc_push_int(id)
						callfunc_push_int(param)
						callfunc_end()
					}					
				}
				// "debug"="running"
				case 'd': {
					if( callfunc_begin("handle_afkadmin",pluginname) == 1 ) 
					{
						callfunc_push_int(id)
						callfunc_push_int(param)
						callfunc_end()
					}	
				}
			}
		}
	}
}		

