#include <amxmodx>
#include <amxmisc>
#include <engine>
#include <time>

#define PLUGIN "Super Gag"
#define VERSION "1.5"
#define AUTHOR "Numb"

#define GAGGED_SAY 1
#define GAGGED_SAY_TEAM 2
#define GAGGED_VOICE 3
#define GAGGED_NAME 4
#define GAG_TIME_LIMIT SECONDS_IN_DAY

new dataDir[64];
new amx_defaut_gag_time;
new amx_gag_by_authid;

new bool:wasgagged[33];
new bool:wasmuted[33];

public plugin_init()
{
	register_plugin(PLUGIN, VERSION, AUTHOR);
	register_dictionary("common.txt");
	register_dictionary("time.txt");
	register_concmd("amx_gag", "cmdGag", ADMIN_LEVEL_B, "<name or #userid> <time (1m/60)> <flags abcd> [reason]");
	register_concmd("amx_ungag", "cmdUnGag", ADMIN_LEVEL_B, "<name or #userid / ip or authid> <ip/authid=1> [reason]");
	register_concmd("say", "cmdSay", -1, " - check gagged player");
	register_concmd("say_team", "cmdSayTeam", -1, " - check gagged player");
	amx_defaut_gag_time = register_cvar("amx_defaut_gag_time", "20");
	amx_gag_by_authid = register_cvar("amx_gag_by_authid", "1")
	register_message(get_user_msgid("SayText"), "block_namechange_msg");
	get_datadir(dataDir, 63);
}
/*
public plugin_modules()
	require_module("engine");
*/

public cmdGagInfo(id)
{
	new filename[128], playerip[32], gagtime[128], fileDir[96];
	fileDir = get_gagsdir();
	if( get_pcvar_num(amx_gag_by_authid) )
	{
		get_user_authid(id, playerip, 31);
		replace_all(playerip, 31, ":", "_");
		format(filename, 127, "%s/%s.txt", fileDir, playerip);
	}
	else
	{
		get_user_ip(id, playerip, 31, 1);
		format(filename, 127, "%s/%s.txt", fileDir, playerip);
		if( !file_exists(filename) )
		{
			new server_ip[32];
			get_user_ip(0, server_ip, 31, 1);
			if( equal(playerip, server_ip) )
				format(filename, 127, "%s/loopback.txt", fileDir);
			else if( equal(playerip, "loopback") )
				format(filename, 127, "%s/%s.txt", fileDir, server_ip);
		}
	}
	
	if( file_exists(filename) )
	{
		new gag_say, gag_say_team, gag_voice, gag_name, authid_gags = get_pcvar_num(amx_gag_by_authid);
		gag_say = is_user_gagged(id, GAGGED_SAY, authid_gags);
		gag_say_team = is_user_gagged(id, GAGGED_SAY_TEAM, authid_gags);
		gag_voice = is_user_gagged(id, GAGGED_VOICE, authid_gags);
		gag_name = is_user_gagged(id, GAGGED_NAME, authid_gags);
		if( gag_say && gag_say_team )
			client_print(id, print_chat, "* You are gagged by: say(_team)%s%s.", (gag_voice) ? " voice" : "", (gag_name) ? " namechange" : "");
		else
			client_print(id, print_chat, "* You are gagged by:%s%s%s%s.", (gag_say) ? " say" : "", (gag_say_team) ? " say_team" : "", (gag_voice) ? " voice" : "", (gag_name) ? " namechange" : "");
		
		new reason[64], txtsize, time;
		read_file(filename, 7, reason, 63, txtsize);
		if( reason[0] )
			client_print(id, print_chat, "* Reason why you are gagged: %s.", reason);
		else
			client_print(id, print_chat, "* Reason why you are gagged: Unspecified.");
			
		read_file(filename, 1, gagtime, 127, txtsize);
		time = str_to_num(gagtime)-get_systime(1);
		client_print(id, print_chat, "* You will be ungagged in %s.", convert_time(time));
	}
	else
		client_print(id, print_chat, "* You are not gagged.");
}

public cmdSay(id)
{
	new text[192], gagged, text_len;
	read_argv(1, text, 191);
	text_len = strlen(text);
	if( text_len > 2 )
	{
		if( text[0] == '"' && text[text_len-1] == '"' )
			format(text, text_len-2, "%s", text[1]);
	}
	
	gagged = is_user_gagged(id, GAGGED_SAY, get_pcvar_num(amx_gag_by_authid));
	if( (equal(text, "/gaginfo") || equal(text, ".gaginfo")) && read_argc() == 2 )
	{
		cmdGagInfo(id);
		if( gagged )
			return PLUGIN_HANDLED;
	}
	if( gagged )
	{
		client_print(id, print_chat, "* You are gagged. Type /gaginfo, 4 more information.");
		return PLUGIN_HANDLED;
	}
	return PLUGIN_CONTINUE;
}

public cmdSayTeam(id)
{
	new text[192], gagged, text_len;
	read_argv(1, text, 191);
	text_len = strlen(text);
	if( text_len > 2 )
	{
		if( text[0] == '"' && text[text_len-1] == '"' )
			format(text, text_len-2, "%s", text[1]);
	}
	
	gagged = is_user_gagged(id, GAGGED_SAY_TEAM, get_pcvar_num(amx_gag_by_authid));
	if( (equal(text, "/gaginfo") || equal(text, ".gaginfo")) && read_argc() == 2 )
	{
		cmdGagInfo(id);
		if( gagged )
			return PLUGIN_HANDLED;
	}
	if( gagged )
	{
		client_print(id, print_chat, "* You are gagged. Type /gaginfo, 4 more information.");
		return PLUGIN_HANDLED;
	}
	return PLUGIN_CONTINUE;
}

public client_putinserver(id)
{
	set_task(1.0, "client_connected", id);
	if( is_user_gagged(id, 0, get_pcvar_num(amx_gag_by_authid)) )
		wasgagged[id] = true;
	else
		wasgagged[id] = false;
}

public client_connected(id)
{
	if( is_user_gagged(id, GAGGED_VOICE, get_pcvar_num(amx_gag_by_authid)) )
	{
		client_cmd(id, "-voicerecord");
		set_speak(id, SPEAK_MUTED);
		wasmuted[id] = true;
	}
	else
		wasmuted[id] = false;
	check_gagged_name(id, 0);
}

public block_namechange_msg(msgid, msgdest, msgent)
{
	new msgtype[32];
	get_msg_arg_string(2, msgtype, 31);
	if( equal(msgtype, "#Cstrike_Name_Change") )
	{
		new player, newname[32], custom_newname[32];
		get_msg_arg_string(4, newname, 31);
		for( player = 1; player < 33; player++ )
		{
			if( is_valid_ent(player) && is_user_connected(player) && is_user_alive(player) )
			{
				custom_newname = "";
				get_user_info(player, "name", custom_newname, 31);
				if( equal(newname, custom_newname) )
					break;
			}
			
			if( player == 32 )
			{
				player = 0;
				break;
			}
		}
		
		if( player )
		{
			if( is_user_gagged(player, GAGGED_NAME, get_pcvar_num(amx_gag_by_authid)) )
				return PLUGIN_HANDLED;
		}
	}
	return PLUGIN_CONTINUE;
}

public client_infochanged(id)
{
	if( is_user_gagged(id, GAGGED_NAME, get_pcvar_num(amx_gag_by_authid)) )
	{
		check_gagged_name(id, 1);
		return PLUGIN_HANDLED;
	}
	return PLUGIN_CONTINUE;
}

public check_gagged_name(id, namechange)
{
	new authid_gags = get_pcvar_num(amx_gag_by_authid);
	if( is_user_gagged(id, GAGGED_NAME, authid_gags) )
	{
		new filename[128], fileDir[96], playerip[32], gaggedname[32], newname[32];
		fileDir = get_gagsdir();
		if( authid_gags )
		{
			get_user_authid(id, playerip, 31);
			replace_all(playerip, 31, ":", "_");
		}
		else
			get_user_ip(id, playerip, 31, 1);
		
		format(filename, 127, "%s/%s.txt", fileDir, playerip);
		
		if( !file_exists(filename) && !authid_gags )
		{
			new server_ip[32];
			get_user_ip(0, server_ip, 31, 1);
			if( equal(playerip, server_ip) )
				format(filename, 127, "%s/loopback.txt", fileDir);
			else if( equal(playerip, "loopback") )
				format(filename, 127, "%s/%s.txt", fileDir, server_ip);
			
			if( !file_exists(filename) )
				return;
		}
		
		new txtsize;
		read_file(filename, 5, gaggedname, 31, txtsize);
		get_user_info(id, "name", newname, 31);
		
		if( !equal(gaggedname, newname) )
		{
			if( namechange )
			{
				client_print(id, print_chat, "* You are geged. You cannot change your name.");
				set_user_info(id, "name", gaggedname);
			}
			else
				client_cmd(id, "name ^"%s^"", gaggedname);
		}
	}
}

public client_PreThink(id)
{
	if( is_user_connected(id) )
	{
		static authid_gags;
		authid_gags = get_pcvar_num(amx_gag_by_authid);
		if( !is_user_gagged(id, GAGGED_VOICE, authid_gags) && wasmuted[id] )
		{
			set_speak(id, SPEAK_NORMAL);
			wasmuted[id] = false;
		}
		
		if( is_user_gagged(id, 0, authid_gags) )
			wasgagged[id] = true;
		else if( wasgagged[id] )
		{
			wasgagged[id] = false;
			if( get_user_time(id, 0) > 2 )
				client_print(id, print_chat, "* You are ungagged.");
		}
	}
}

public cmdGag(id, level, cid)
{
	if( !cmd_access(id, level, cid, 2) )
		return PLUGIN_HANDLED

	new target[32], player;
	read_argv(1, target, 31);
	player = cmd_target(id, target, 9);
	
	if( !player)
		return PLUGIN_HANDLED;
	
	new sgagtime[32], flags[32], reason[64], gagtime;
	read_argv(2, sgagtime, 31);
	read_argv(3, flags, 31);
	read_argv(4, reason, 63);
	remove_quotes(reason);
	
	if( sgagtime[0] )
	{
		if( contain(sgagtime,"m") > 0 )
		{
			new sgagtime2[32];
			copyc(sgagtime2, 31, sgagtime, 'm');
			gagtime = str_to_num(sgagtime2)*60;
		}
		else
			gagtime = str_to_num(sgagtime);
	}
	else
		gagtime = get_pcvar_num(amx_defaut_gag_time)*60;
	if( gagtime < 1 || gagtime > GAG_TIME_LIMIT )
		gagtime = GAG_TIME_LIMIT;
	
	new newflags[32];
	format(flags, 31, "_%s", flags);
	if( contain(flags, "d") > 0 )
		format(newflags, 7, "d");
	if( contain(flags, "c") > 0 )
		format(newflags, 7, "c%s", newflags);
	if( contain(flags, "b") > 0 )
		format(newflags, 7, "b%s", newflags);
	if( contain(flags, "a") > 0 )
		format(newflags, 7, "a%s", newflags);
	if( !newflags[0] )
		newflags = "abcd";
	format(flags, 31, "_%s_", newflags);
	
	new authid[32], authid2[32], playerip[32], playerip2[32], name[32], name2[32], userid, userid2;
	get_user_authid(id, authid, 31);
	get_user_authid(player, authid2, 31);
	get_user_ip(id, playerip, 31, 1);
	get_user_ip(player, playerip2, 31, 1);
	get_user_name(id, name, 31);
	get_user_name(player, name2, 31);
	userid = get_user_userid(id);
	userid2 = get_user_userid(player);
	
	new gag_say, gag_say_team, gag_voice, gag_name;
	gag_say = (contain(flags, "a") > 0);
	gag_say_team = (contain(flags, "b") > 0);
	gag_voice = (contain(flags, "c") > 0);
	gag_name = (contain(flags, "d") > 0);
	if( !reason[0] )
		reason = "Unspecified";
	
	if( gag_voice )
	{
		client_cmd(player, "-voicerecord");
		set_speak(player, SPEAK_MUTED);
		wasmuted[player] = true;
	}
	new gaggedtime, filename[128];
	gaggedtime = gagtime + get_systime(1);
	
	if( get_pcvar_num(amx_gag_by_authid) )
	{
		filename = authid2;
		replace_all(filename, 31, ":", "_");
		format(filename, 127, "%s/%s.txt", get_gagsdir(), filename);
	}
	else
		format(filename, 127, "%s/%s.txt", get_gagsdir(), playerip2);
	
	if( file_exists(filename) )
		delete_file(filename);
		
	new sgagtime3[128];
	num_to_str(gaggedtime, sgagtime3, 127);
	write_file(filename, "Time data:");
	write_file(filename, sgagtime3);
	write_file(filename, "Flags:");
	write_file(filename, flags);
	write_file(filename, "Player name:");
	write_file(filename, name2);
	write_file(filename, "Reason:");
	write_file(filename, reason);
	
	log_amx("Gag: ^"%s<#%d><%s><%s>^" gagged ^"%s<#%d><%s><%s>^" <%s> for <%ds> (reason: ^"%s^")", name, userid, authid, playerip, name2, userid2, authid2, playerip2, newflags, gagtime, reason);
	
	format(reason, 127, "for %s (%s)", convert_time(gagtime), reason);
	
	if( gag_say && gag_say_team )
	{
		switch(get_cvar_num("amx_show_activity"))
		{
			case 2: client_print(0, print_chat, "ADMIN %s : Gagged %s by say(_team)%s%s %s", name, name2, (gag_voice) ? " voice" : "", (gag_name) ? " namechange" : "", reason);
			case 1: client_print(0, print_chat, "ADMIN: Gagged %s by say(_team)%s%s %s", name2, (gag_voice) ? " voice" : "", (gag_name) ? " namechange" : "", reason);
		}
	}
	else
	{
		switch(get_cvar_num("amx_show_activity"))
		{
			case 2: client_print(0, print_chat, "ADMIN %s : Gagged %s by%s%s%s%s %s", name, name2, (gag_say) ? " say" : "", (gag_say_team) ? " say_team" : "", (gag_voice) ? " voice" : "", (gag_name) ? " namechange" : "", reason);
			case 1: client_print(0, print_chat, "ADMIN: Gagged %s by%s%s%s%s %s", name2, (gag_say) ? " say" : "", (gag_say_team) ? " say_team" : "", (gag_voice) ? " voice" : "", (gag_name) ? " namechange" : "", reason);
		}
	}
		
	console_print(id, "[AMXX] Client ^"%s^" gagged", name2);
	
	return PLUGIN_HANDLED;
}

public cmdUnGag(id, level, cid)
{
	if( !cmd_access(id, level, cid, 2) )
		return PLUGIN_HANDLED

	new target[32], player, ip[32], reason[64];
	read_argv(1, target, 31);
	read_argv(2, ip, 31);
	read_argv(3, reason, 63);
	remove_quotes(reason);
	if( !reason[0] )
		reason = "Unspecified";
	
	new authid[32], playerip[32], name[32], userid;
	get_user_authid(id, authid, 31);
	get_user_ip(id, playerip, 31, 1);
	get_user_name(id, name, 31);
	userid = get_user_userid(id);
	if( !str_to_num(ip) )
	{
		player = cmd_target(id, target, 9);
		
		if(!player)
			return PLUGIN_HANDLED;
		
		new authid2[32], playerip2[32], name2[32], userid2;
		get_user_authid(player, authid2, 31);
		get_user_ip(player, playerip2, 31, 1);
		get_user_name(player, name2, 31);
		userid2 = get_user_userid(player);
		
		new filename[128], fileDir[96], authid_gags = get_pcvar_num(amx_gag_by_authid);
		fileDir = get_gagsdir();
		
		if( authid_gags )
		{
			filename = authid2;
			replace_all(filename, 31, ":", "_");
			format(filename, 127, "%s/%s.txt", fileDir, filename);
		}
		else
			format(filename, 127, "%s/%s.txt", fileDir, playerip2);
		
		format(filename, 127, "%s/%s.txt", fileDir, playerip2);
		if( file_exists(filename) )
			delete_file(filename);
		else if( !authid_gags )
		{
			new server_ip[32];
			get_user_ip(0, server_ip, 31, 1);
			if( equal(playerip2, server_ip) )
				format(filename, 127, "%s/loopback.txt", fileDir);
			else if( equal(playerip2, "loopback") )
				format(filename, 127, "%s/%s.txt", fileDir, server_ip);
			if( !file_exists(filename) )
			{
				console_print(id, "[AMXX] Error: Client ^"%s^" is not gagged", name2);
				return PLUGIN_HANDLED;
			}
		}
		else
		{
			console_print(id, "[AMXX] Error: Client ^"%s^" is not gagged", name2);
			return PLUGIN_HANDLED;
		}
		
		log_amx("Gag: ^"%s<#%d><%s><%s>^" ungagged ^"%s<#%d><%s><%s>^" (reason: ^"%s^")", name, userid, authid, playerip, name2, userid2, authid2, playerip2, reason);
		
		switch(get_cvar_num("amx_show_activity"))
		{
			case 2: client_print(0, print_chat, "ADMIN %s : UnGagged %s (%s)", name, name2, reason);
			case 1: client_print(0, print_chat, "ADMIN: UnGagged %s (%s)", name2, reason);
		}
		
		console_print(id, "[AMXX] Client ^"%s^" ungagged", name2);
		return PLUGIN_HANDLED;
	}
	new filename[128], fileDir[96], authid_gags = get_pcvar_num(amx_gag_by_authid);
	fileDir = get_gagsdir();
	
	if( authid_gags )
	{
		filename = target;
		replace_all(filename, 31, ":", "_");
		format(filename, 127, "%s/%s.txt", fileDir, filename);
	}
	else
		format(filename, 127, "%s/%s.txt", fileDir, target);
	
	if( !file_exists(filename) )
	{
		if( !authid_gags )
		{
			new server_ip[32];
			get_user_ip(0, server_ip, 31, 1);
			if( equal(target, server_ip) )
				format(filename, 127, "%s/loopback.txt", fileDir);
			else if( equal(target, "loopback") || equal(target, "localhost") )
				format(filename, 127, "%s/%s.txt", fileDir, server_ip);
			if( !file_exists(filename) )
			{
				console_print(id, "[AMXX] Error: Ip ^"%s^" not found", target);
				return PLUGIN_HANDLED;
			}
		}
		else
		{
			console_print(id, "[AMXX] Error: Ip ^"%s^" not found", target);
			return PLUGIN_HANDLED;
		}
	}
	
	new name2[32], txtsize;
	read_file(filename, 5, name2, 31, txtsize);
	
	new user, playerip2[32], playerip3[32], authid2[32], userid2;
	for( user = 1; user < 33; user++ )
	{
		if( is_user_connected(user) )
		{
			if( authid_gags )
				get_user_authid(user, playerip3, 31);
			else
				get_user_ip(user, playerip3, 31, 1);
			
			if( equal(target, playerip3) > 0 )
			{
				userid2 = get_user_userid(user);
				if( authid_gags )
				{
					authid2 = playerip3;
					get_user_ip(user, playerip2, 31, 1);
				}
				else
				{
					playerip2 = playerip3;
					get_user_authid(user, authid2, 31);
				}	
				if( is_user_gagged(user, GAGGED_NAME, authid_gags) )
					client_cmd(user, "name ^"%s^"", name2);
				else
					get_user_name(user, name2, 31);
			}
		}
	}
	
	delete_file(filename);
	
	log_amx("Gag: ^"%s<#%d><%s><%s>^" ungagged by ip/authid ^"%s<#%d><%s><%s>^" (reason: ^"%s^")", name, userid, authid, playerip, name2, userid2, authid2, playerip2, reason);
	
	switch(get_cvar_num("amx_show_activity"))
	{
		case 2: client_print(0, print_chat, "ADMIN %s : UnGagged ^"%s^" %s (%s)", name, target, name2, reason);
		case 1: client_print(0, print_chat, "ADMIN: UnGagged ^"%s^" %s (%s)", target, name2, reason);
	}
	
	console_print(id, "[AMXX] Client ^"%s^" with ^"%s^" ip/authid ungagged", name2, target);
	
	return PLUGIN_HANDLED;
}

stock is_user_gagged(id, flag, authid_gags)
{
	
	new filename[128], fileDir[96], playerip[32];
	fileDir = get_gagsdir();
	
	if( authid_gags )
	{
		get_user_authid(id, playerip, 31);
		replace_all(playerip, 31, ":", "_");
		format(filename, 127, "%s/%s.txt", fileDir, playerip);
	}
	else
	{
		get_user_ip(id, playerip, 31, 1);
		format(filename, 127, "%s/%s.txt", fileDir, playerip);
	}
	
	if( !file_exists(filename) )
	{
		if( authid_gags )
			return 0;
		
		new server_ip[32];
		get_user_ip(0, server_ip, 31, 1);
		if( equal(playerip, server_ip) )
			format(filename, 127, "%s/loopback.txt", fileDir);
		else if( equal(playerip, "loopback") )
			format(filename, 127, "%s/%s.txt", fileDir, server_ip);
		if( !file_exists(filename) )
			return 0;
	}
	
	new gagtime[128], gagflags[32], txtsize;
	read_file(filename, 1, gagtime, 127, txtsize);
	if( !(str_to_num(gagtime) > get_systime(1)) )
	{
		delete_file(filename);
		return 0;
	}
	
	read_file(filename, 3, gagflags, 31, txtsize);
	new g_say, g_say_team, g_voice, g_name;
	g_say = (contain(gagflags, "a") > 0);
	g_say_team = (contain(gagflags, "b") > 0);
	g_voice = (contain(gagflags, "c") > 0);
	g_name = (contain(gagflags, "d") > 0);
	if( !(g_say || g_say_team || g_voice || g_name ) )
	{
		log_amx("[GAG] Error: No flags found in <^"%s^"> file! Deleting file.", filename);
		delete_file(filename);
		return 0;
	}
	
	if( flag == GAGGED_SAY )
	{
		if( g_say )
			return 1;
	}
	else if( flag == GAGGED_SAY_TEAM )
	{
		if( g_say_team )
			return 1;
	}
	else if( flag == GAGGED_VOICE )
	{
		if( g_voice )
			return 1;
	}
	else if( flag == GAGGED_NAME )
	{
		if( g_name )
			return 1;
	}
	else
		return 1;
	
	return 0;
}

stock convert_time(time)
{
	new TimeMsg[128];
	get_time_length(0, time, timeunit_seconds, TimeMsg, 127);
	return TimeMsg;
}

stock get_gagsdir()
{
	new gagDir[96];
	format(gagDir, 95, "%s/gags", dataDir);
	if( !dir_exists(gagDir) )
		mkdir(gagDir);
	return gagDir;
}
