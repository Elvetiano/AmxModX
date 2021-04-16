#include <amxmodx>
#include <amxmisc>
#include <official_base>

#define PLUGIN "SLAY/Slap Chat"
#define VERSION "2.0.1"
#define AUTHOR "Anakin & UNU"
#define ACCESS ADMIN_SLAY
#define ACCESSSLAY ADMIN_SLAY


public plugin_init() {
	register_plugin(PLUGIN, VERSION, AUTHOR)   
	register_concmd("amx_slayteam","slay_cmd",ACCESSSLAY,"amx_slay <player|@team> - kill a player or team @CT/@T")
	register_concmd("amx_slapteam","slap_cmd",ACCESS,"amx_slap <player|@team> - Slap a player or team @CT/@T")
	//register_clcmd("say", "funcslay", ACCESSSLAY, "slay/kill a team ct/t/all <slay #team>")
	
	register_clcmd("say slaytr", "slaytr", ACCESSSLAY, "slay/kill a team ct/t/all <slay #team>")	
	register_clcmd("say slayct", "slayct", ACCESSSLAY, "slay/kill a team ct/t/all <slay #team>")
	register_clcmd("say slayall", "slayall", ACCESSSLAY, "slay/kill a team ct/t/all <slay #team>")
	register_clcmd("say", "slayplayer", ACCESS, "slay/kill a team ct/t/all <slay #team>")	
	register_clcmd("say slaptr", "slaptr", ACCESS, "slap a team tr <slaptr damage>")
	register_clcmd("say slapct", "slapct", ACCESS, "slap a team ct <slapct damage>")
	register_clcmd("say slapall", "slapall", ACCESS, "slap all players <slapall damage>")
	register_clcmd("say", "slapplayer", ACCESS, "slap a player <slap name damage>")
	register_clcmd("say", "slapplayer10", ACCESS, "slap a player many times <mslap name>")
}




/*
public funcslay(id) 
{	
	if (!access(id, ACCESS))
	{
		return PLUGIN_CONTINUE
	}
	new arg[192],dmg[5], arg2[7]
	read_argv(1,arg, 191)
	//01
	new arglen = strlen(arg[0]);
	new arg2len, dmglen
	
	for (i=0; i<arglen; i++)
	{
		if(isspace(arg[i]))
		{
			arg2len = i
		}		
	}
	
	dmglen = arglen - arg2len	
	argbreak(arg,arg2,arg2len,dmg,dmglen)	
	new damage = str_to_num(dmg)
	
	if (damage<0)
		damage = 0
	
	new name[32]
	
	switch (arg2)
	{
		case (containi(arg2, "slaptr")!= -1):
		{
			
		}
		default:
		{
			//This code will run if all other cases fail
		}
	}
	
	
	
	
	if (containi(arg2, "slaptr")!= -1)
	{
		if (strcmp(arg2, "slaptr",true) == 0)
		{
			get_user_name(id,name,31)
			new players[32], num
			get_players(players, num)	
			new i
			for (i=0; i<num; i++)
			{
				if (get_user_team(players[i]) == 1)
				{
					//user_kill(players[i])
					user_slap (players[i], damage, 1)
				}
			}
			chat_color(0, "!g[OFFICIAL] ADMIN !team%s !g: has slaped !yTR !g Team with damage !y%d", name, damage)
			//chat_color(0, "!g[OFFICIAL] ADMIN !team%s !g: has killed !yTR !g Team", name)
			//emit_sound(0,CHAN_VOICE, "ambience/thunder_clap.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);
		}
	}
	return PLUGIN_CONTINUE
}

*/


























public slay_cmd(id,level,cid) 
{
	if(!(get_user_flags(id) & ACCESS))
	{
		console_print(id,"No Access !")
		return PLUGIN_HANDLED
	}
	new arg[32]
	read_argv(1,arg,31)
	new name[32]
	get_user_name(id,name,31)
	if (arg[0] == '@')
	{
		new Team = 0
		if (equali(arg[1], "CT"))
		{
			Team = 2
		} else if (equali(arg[1], "T"))
		{
			Team = 1
		}
		new players[32], num
		get_players(players, num)
		new i
		for (i=0; i<num; i++)
		{
			if (!Team)
			{
				user_kill(players[i])
				chat_color(0, "!g[OFFICIAL] ADMIN !team%s !g: has killed !y all", name)
				//emit_sound(0,CHAN_VOICE, "ambience/thunder_clap.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);
			} else 
			{
				if (get_user_team(players[i]) == Team)
				{
					user_kill(players[i])
					chat_color(0, "!g[OFFICIAL] ADMIN !team%s !g: has killed team !y%s ", name,arg[1])
					//emit_sound(0,CHAN_VOICE, "ambience/thunder_clap.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);
				}
			}
		}
	} else 
	{
		new player = cmd_target(id,arg,5)
		if(!player)
		{
			client_print(id,print_console,"Player %s not found !",arg)
			return PLUGIN_HANDLED
		} else
		{
			new levelcmd = check_levelcmd(id, player)
			if(levelcmd > 0)
			{
				return PLUGIN_HANDLED
			}			
			user_kill(player)
			chat_color(0, "!g[OFFICIAL] ADMIN !team%s !g: has killed player !y%s ", name,arg)
			//emit_sound(0,CHAN_VOICE, "ambience/thunder_clap.wav", 1.0, ATTN_NORM, 0, PITCH_NORM)
		}
	}
	return PLUGIN_HANDLED
}
public slayct(id)
{
		if (!access(id, ACCESSSLAY))
		{
			return PLUGIN_CONTINUE
		}
		new name[32]
		get_user_name(id,name,31)
		new players[32], num
		get_players(players, num)	
		new i
		for (i=0; i<num; i++)
		{
		   if (get_user_team(players[i]) == 2)
		   {
			   user_kill(players[i])			   
            }
	  }
		chat_color(0, "!g[OFFICIAL] ADMIN !team%s !g: has killed !yCT !g Team", name)
		//emit_sound(0,CHAN_VOICE, "ambience/thunder_clap.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);
		return PLUGIN_CONTINUE
}

public slaytr(id) 
	{	
		if (!access(id, ACCESSSLAY))
		{
			return PLUGIN_CONTINUE
		}
		new name[32]
		get_user_name(id,name,31)
		new players[32], num
		get_players(players, num)	
		new i
		for (i=0; i<num; i++){
		   if (get_user_team(players[i]) == 1)
		   {
			   user_kill(players[i])			   
            }
	  }
		chat_color(0, "!g[OFFICIAL] ADMIN !team%s !g: has killed !yTR !g Team", name)
		//emit_sound(0,CHAN_VOICE, "ambience/thunder_clap.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);
		return PLUGIN_CONTINUE
}
public slayall(id) 
	{	
		if (!access(id, ACCESSSLAY))
		{
			return PLUGIN_CONTINUE
		}
		new name[32]
		get_user_name(id,name,31)
		new players[32], num
		get_players(players, num)	
		new i
		for (i=0; i<num; i++)
		{
			user_kill(players[i])			
		}
		chat_color(0, "!g[OFFICIAL] ADMIN !team%s !g: has killed !yAll !g players", name)
		//emit_sound(0,CHAN_VOICE, "ambience/thunder_clap.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);			
		return PLUGIN_CONTINUE
}

















public slayplayer(id)
{
	if (!access(id, ACCESS))
	{
		return PLUGIN_CONTINUE
	}
	new name[MAX_NAME_LENGTH]
	get_user_name(id,name,charsmax(name))
	
	new arg[192],arg1[6],arg2[32]
	read_argv(1,arg, 191)
	argbreak(arg, arg1, charsmax(arg1), arg2, charsmax(arg2))
	if ((containi(arg1, "slay")!= -1) && ((containi(arg1, "slayall") == -1) || (containi(arg1, "slayct") == -1) || (containi(arg1, "slaytr") == -1)))
	{
		new players[MAX_PLAYERS], players2[MAX_PLAYERS], num2, num = 0;
		get_players(players, num, "ahf", arg2);

		if(num > 1)
		{
			chat_color(id, "!g[OFFICIAL] More players have this name <^" %s ^"> be more specific !",arg2)
			return PLUGIN_HANDLED
		}
		if(num == 0)
		{
			new player_found = find_player_ex(FindPlayer_MatchNameSubstring | FindPlayer_LastMatched | FindPlayer_CaseInsensitive, arg2);
			if(!player_found){
				
				chat_color(id, "!g[OFFICIAL] Player <^" %s ^"> not found!",arg2)
				return PLUGIN_HANDLED
			}
			if (is_user_alive(player_found) != 1){
				new deadguy[MAX_NAME_LENGTH];
				get_user_name(player_found,deadguy,charsmax(deadguy))
				chat_color(id, "!g[OFFICIAL] Player <^" %s ^"> its dead!",deadguy)
				return PLUGIN_HANDLED
			}
			num = 1;
		}
		if(num == 1)
		{
			get_players(players2, num2);
			for (new i=0; i<num2; i++){
				new trash[MAX_NAME_LENGTH]
				get_user_name(i,trash,charsmax(trash))
				new xs = containi(trash, arg2)
				if(xs != -1){
					new player = cmd_target(id, trash, CMDTARGET_OBEY_IMMUNITY)
					if (!player){
						chat_color(id, "!g[OFFICIAL] Player <^" %s ^"> has IMMUNITY",trash)
						return PLUGIN_HANDLED
					}
					new levelcmd = check_levelcmd(id, player)
					if(levelcmd > 0){
						return PLUGIN_HANDLED
					}	
					if (is_user_alive(player) != 0){
						user_kill(player)
						chat_color(0, "!g[OFFICIAL] ADMIN !team%s !g: has killed player !y%s ", name,trash)
						//emit_sound(0, CHAN_VOICE, "ambience/thunder_clap.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);
					}
				}
			}
		}
	}
	return PLUGIN_CONTINUE
}














/*
public slayplayer(id) 
	{		
		if (!access(id, ACCESS))
		{
			return PLUGIN_CONTINUE
		}		
		new i
		new arg[192],arg1[6], arg2[32]		
		read_argv(1,arg, 191)
		new name[32]
		get_user_name(id,name,31)		
		argbreak(arg,arg1,5,arg2,31)
		if (containi(arg1, "slay")!= -1){
			read_argv(1,arg1, 5)
			if(isspace(arg1[4]))
			{
			read_argv(1,arg1, 4)			
			if (strcmp(arg1, "slay",true) == 0) 
				{							
				new players[32], num
				get_players(players, num)		
				new trash[32]
				for (i=0; i<num; i++){
					get_user_name(i,trash,31)
					new xs = containi(trash, arg2)
					if(xs != -1){
						new player = cmd_target(i, trash, 0)
						
						new levelcmd = check_levelcmd(id, player)
						if(levelcmd > 0)
						{
							return PLUGIN_HANDLED
						}						

						if (is_user_alive(player) != 0){
							if (get_user_flags(player)&ADMIN_IMMUNITY)
							 {
								chat_color(id, "!g[OFFICIAL] Jucatorul !y%s !gare !teamIMUNITATE", trash)
								return PLUGIN_HANDLED
							 }								
							user_kill(player)
							chat_color(0, "!g[OFFICIAL] ADMIN !team%s !g: has killed player !y%s ", name,trash)
							//emit_sound(0, CHAN_VOICE, "ambience/thunder_clap.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);
						} else 
						{
							chat_color(id, "!g[OFFICIAL] player is dead")
							}
						break
						}
					}
				}
			}
		}
		return PLUGIN_CONTINUE
}
*/










































public slap_cmd(id,level,cid) 
{
	if(!(get_user_flags(id) & ACCESS))
	{
		console_print(id,"No Access !")
		return PLUGIN_HANDLED
	}
	new arg[32]
	read_argv(1,arg,31)
	new name[32], spower[32]
	read_argv(2, spower, 31)
	new damage = str_to_num(spower)
	if (damage<0)
		damage = 0
	get_user_name(id,name,31)
	if (arg[0] == '@')
	{
		new Team = 0
		if (equali(arg[1], "CT"))
		{
			Team = 2
		} else if (equali(arg[1], "TR"))
		{
			Team = 1
		}
		new players[32], num
		get_players(players, num)
		new i
		for (i=0; i<num; i++)
		{
			if (!Team)
			{
				//user_kill(players[i])
				user_slap (players[i], damage, 1)
				chat_color(0, "!g[OFFICIAL] ADMIN !team%s !g: has slaped !y all !gwith damage !y%s", name,damage)
				//emit_sound(0,CHAN_VOICE, "ambience/thunder_clap.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);
			} else 
			{
				if (get_user_team(players[i]) == Team)
				{
					//user_kill(players[i])
					user_slap (players[i], damage, 1)
					chat_color(0, "!g[OFFICIAL] ADMIN !team%s !g: has slaped team !y%s !gwith damage !y%s", name,arg[1],damage)
					//emit_sound(0,CHAN_VOICE, "ambience/thunder_clap.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);
				}
			}
		}
	} else 
	{
		new player = cmd_target(id,arg,5)
		if(!player)
		{
			client_print(id,print_console,"Player %s not found !",arg)
			return PLUGIN_HANDLED
		} else
		{
			new levelcmd = check_levelcmd(id, player)
			if(levelcmd > 0)
			{
				return PLUGIN_HANDLED
			}	
			//user_kill(player)
			user_slap (player, damage, 1)
			chat_color(0, "!g[OFFICIAL] ADMIN !team%s !g: has slaped player !y%s !gwith damage !y%d", name,arg,damage)
			//emit_sound(0,CHAN_VOICE, "ambience/thunder_clap.wav", 1.0, ATTN_NORM, 0, PITCH_NORM)
		}
	}
	return PLUGIN_HANDLED
}
public slapct(id)
{
	if (!access(id, ACCESS))
	{
		return PLUGIN_CONTINUE
	}
	new arg[192],dmg[5], arg2[7]
	read_argv(1,arg, 191)	
	argbreak(arg,arg2,6,dmg,4)
	new damage = str_to_num(dmg)
	if (damage<0)
		damage = 0
	new name[32]
	if (containi(arg2, "slapct")!= -1)
	{
		if (strcmp(arg2, "slapct",true) == 0)
		{
			get_user_name(id,name,31)
			new players[32], num
			get_players(players, num)	
			new i
			for (i=0; i<num; i++)
			{
				if (get_user_team(players[i]) == 2)
				{
					//user_kill(players[i])
					user_slap (players[i], damage, 1)
				}
			}
			chat_color(0, "!g[OFFICIAL] ADMIN !team%s !g: has slaped !yCT !g Team with damage !y%d", name, damage)
			//chat_color(0, "!g[OFFICIAL] ADMIN !team%s !g: has killed !yCT !g Team", name)
			//emit_sound(0,CHAN_VOICE, "ambience/thunder_clap.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);
		}		
	}
	return PLUGIN_CONTINUE
}

public slaptr(id) 
{	
	if (!access(id, ACCESS))
	{
		return PLUGIN_CONTINUE
	}
	new arg[192],dmg[5], arg2[7]
	read_argv(1,arg, 191)	
	argbreak(arg,arg2,6,dmg,4)
	new damage = str_to_num(dmg)
	if (damage<0)
		damage = 0
	new name[32]
	if (containi(arg2, "slaptr")!= -1)
	{
		if (strcmp(arg2, "slaptr",true) == 0)
		{
			get_user_name(id,name,31)
			new players[32], num
			get_players(players, num)	
			new i
			for (i=0; i<num; i++)
			{
				if (get_user_team(players[i]) == 1)
				{
					//user_kill(players[i])
					user_slap (players[i], damage, 1)
				}
			}
			chat_color(0, "!g[OFFICIAL] ADMIN !team%s !g: has slaped !yTR !g Team with damage !y%d", name, damage)
			//chat_color(0, "!g[OFFICIAL] ADMIN !team%s !g: has killed !yTR !g Team", name)
			//emit_sound(0,CHAN_VOICE, "ambience/thunder_clap.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);
		}
	}
	return PLUGIN_CONTINUE
}
public slapall(id) 
{	
	if (!access(id, ACCESS))
	{
		return PLUGIN_CONTINUE
	}
	new arg[192],dmg[5], arg2[8]
	read_argv(1,arg, 191)	
	argbreak(arg,arg2,7,dmg,4)
	new damage = str_to_num(dmg)
	if (damage<0)
		damage = 0
	new name[32]
	if (containi(arg2, "slapall")!= -1)
	{
		if (strcmp(arg2, "slapall",true) == 0)
		{			
			get_user_name(id,name,31)
			new players[32], num
			get_players(players, num)	
			new i
			for (i=0; i<num; i++)
			{
				//user_kill(players[i])			
				user_slap(players[i], damage, 1)
			}
			chat_color(0, "!g[OFFICIAL] ADMIN !team%s !g: has slaped !yAll !g players with damage !y%d", name, damage)
			//emit_sound(0,CHAN_VOICE, "ambience/thunder_clap.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);
		}
	}
	return PLUGIN_CONTINUE
}


public slapplayer10(id) 
{		
	if (!access(id, ACCESS))
	{
		return PLUGIN_CONTINUE
	}
	new arg[192],arg1[7], chunk[188],arg2[32],dmg[4]
	read_argv(1,arg, 191)
	if (containi(arg, "slapall")!= -1 || containi(arg, "slapct")!= -1 || containi(arg, "slaptr")!= -1)
	{
		return PLUGIN_CONTINUE
	}
	if (containi(arg, "slapm") == -1)
	{
		return PLUGIN_CONTINUE
	}
	new name[32]
	get_user_name(id,name,31)
	argbreak(arg,arg1,6,chunk,188)
	new workstring[192]
	workstring=chunk
	while(replace(workstring, charsmax(workstring), " ", "_")){ }
	new position = containi(workstring,"_" ) 
	parse(chunk,arg2,position,dmg,3)
	new slaps2 = str_to_num(dmg)
	new slaps = power(slaps2,1)
	new player = cmd_target(id, arg2, 4)
	new targetname[32]
	get_user_name(player, targetname, 31)
	if (is_user_alive(player) != 1)
	{
		chat_color(id, "!g[OFFICIAL] Player !y%s !gis dead!!! ", targetname)
		return PLUGIN_CONTINUE
	}
	
	new levelcmd = check_levelcmd(id, player)
	if(levelcmd > 0)
	{
		return PLUGIN_HANDLED
	}
	
	if (!slaps)
		slaps = 10
	if (containi(arg1, "slapm")!= -1)
	{
		if (get_user_flags(player)&ADMIN_IMMUNITY)
		{
			chat_color(id, "!g[OFFICIAL] Jucatorul !y%s !gare !teamIMUNITATE", targetname)
			return PLUGIN_HANDLED
		}								
		new params[1]
		params[0] = player
		//set_task(0.1, "taskslap",player,params,1,"a",10)
		set_task(0.3, "slapTask", 0, params, 1, "a", slaps)		
		chat_color(0, "!g[OFFICIAL] ADMIN !team%s !g: slaps player !y%s !g %s !g times!!! ", name,targetname,slaps)
		//emit_sound(0, CHAN_VOICE, "ambience/thunder_clap.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);
	}
	return PLUGIN_CONTINUE
}

public slapplayer(id) 
{		
	if (!access(id, ACCESS))
	{
		return PLUGIN_CONTINUE
	}
	new arg[192],arg1[6], chunk[188],arg2[32],dmg[4]
	read_argv(1,arg, 191)
	if (containi(arg, "slapall")!= -1 || containi(arg, "slapct")!= -1 || containi(arg, "slaptr")!= -1 || containi(arg, "slapm") != -1)
	{
		return PLUGIN_CONTINUE
	}
	if (containi(arg, "slap") == -1)
	{
		return PLUGIN_CONTINUE
	}
	new name[32]
	get_user_name(id,name,31)
	argbreak(arg,arg1,5,chunk,188)
	
	new workstring[192]
	workstring=chunk
	new spacepos = containi( chunk, " " )
	new chunklen
	chunklen = strlen( chunk )	 
	new dmglen = chunklen - spacepos
	new namelen = chunklen - dmglen
	parse(workstring,arg2,namelen,dmg,dmglen)
	
	//chat_color(0, "!g[OFFICIAL] PARSED DAMAGE IS %s ",dmg)
	
	
	new damage = str_to_num(dmg)
	//chat_color(0, "!g[OFFICIAL] String to num is %s", damage)
	new player = cmd_target(id, arg2, 4)
	new targetname[32]
	new damageform[4]
	get_user_name(player, targetname, 31)
	if (is_user_alive(player) != 1)
	{
		chat_color(id, "!g[OFFICIAL] Player !y%s !gis dead!!! ", targetname)
		return PLUGIN_HANDLED
	}
	
	new levelcmd = check_levelcmd(id, player)
	if(levelcmd > 0)
	{
		return PLUGIN_HANDLED
	}
	
	if (damage<0)
	{
		damage = 0
		//chat_color(0, "!g[OFFICIAL] Damage mai mic ca 0")
	}
	
	if (dmg[0]==0 || isdigit(dmg[0]))
	{
		//chat_color(0, "!g[OFFICIAL] Damage[0] este 0")		
		format(damageform,3,"%d",damage)
	}else
	{
		format(damageform,3,"%s",damage-48)
	}
		
	if (containi(arg1, "slap")!= -1)
	{
		if (get_user_flags(player)&ADMIN_IMMUNITY)
		{
			chat_color(id, "!g[OFFICIAL] Jucatorul !y%s !gare !teamIMUNITATE", targetname)
			return PLUGIN_HANDLED
		}								
		
		
		user_slap (player,damage, 1)
		chat_color(0, "!g[OFFICIAL] ADMIN !team%s !g: slaps player !y%s !g with damage !y %s !g!!! ", name,targetname,damageform)
		//emit_sound(0, CHAN_VOICE, "ambience/thunder_clap.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);
	}
	return PLUGIN_CONTINUE
}
public slapTask(params[], id)
{
   new player = params[0]
   user_slap(player, 0, 1)
}
/*
public taskslap(id)
{
	user_slap(id,0, 1)
}*/

stock chat_color(const id, const input[], any:...)
{
	new count = 1, players[32]
	static msg[191]
	vformat(msg, 190, input, 3)
	replace_all(msg, 190, "!g", "^4")
	replace_all(msg, 190, "!y", "^1")
	replace_all(msg, 190, "!team", "^3")
	replace_all(msg, 190, "!team2", "^0")
	if (id) players[0] = id; else get_players(players, count, "ch")
	{
		for (new i = 0; i < count; i++)
		{
			if (is_user_connected(players[i]))
			{
				message_begin(MSG_ONE_UNRELIABLE, get_user_msgid("SayText"), _, players[i])
				write_byte(players[i])
				write_string(msg)
				message_end()
			}
		}
	}
}
/*
public plugin_precache() {   
   precache_sound("ambience/thunder_clap.wav")   
}*/
