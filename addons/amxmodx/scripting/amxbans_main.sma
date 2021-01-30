/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 
 * AMX Bans - http://www.amxbans.net
 *  Plugin - Main
 * 
 * Copyright (C) 2014  Ryan "YamiKaitou" LeBlanc
 * Copyright (C) 2009, 2010  Thomas Kurz
 * Copyright (C) 2003, 2004  Ronald Renes / Jeroen de Rover
 * Forked from "Admin Base (SQL)" in AMX Mod X (version 1.8.1)
 * 
 * 
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 2 of the License, or (at
 *  your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 *  In addition, as a special exception, the author gives permission to
 *  link the code of this program with the Half-Life Game Engine ("HL
 *  Engine") and Modified Game Libraries ("MODs") developed by Valve,
 *  L.L.C ("Valve"). You must obey the GNU General Public License in all
 *  respects for all of the code used other than the HL Engine and MODs
 *  from Valve. If you modify this file, you may extend this exception
 *  to your version of the file, but you are not obligated to do so. If
 *  you do not wish to do so, delete this exception statement from your
 *  version.
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */  

#define PLUGINNAME "AMXBans Main"
#define PLUGINAUTHOR "YamiKaitou"
new const PLUGINVERSION[] = "6.15-a";

#include <amxmodx>
#include <amxmisc>
#include <sqlx>
#include <time>

// Amxbans Core natives
#include "include/amxbans_core.inc"

// Amxbans .inl files
#include "include/amxbans/global_vars.inl"
//#include "include/amxbans/color_chat.inl"
#include "include/amxbans/init_functions.inl"
#include "include/amxbans/check_player.inl"
#include "include/amxbans/check_flag.inl"
#include "include/amxbans/menu_stocks.inl"
#include "include/amxbans/menu_ban.inl"
#include "include/amxbans/menu_disconnected.inl"
#include "include/amxbans/menu_history.inl"
#include "include/amxbans/menu_flag.inl"
#include "include/amxbans/cmdBan.inl"
#include "include/amxbans/cmdUnban.inl"
#include "include/amxbans/web_handshake.inl"
#include "include/amxbans/rconpass.inl"
#include <official_base>
// 16k * 4 = 64k stack size
#pragma dynamic 18432 		// Give the plugin some extra memory to use
 
public plugin_init()
{
	register_plugin(PLUGINNAME, PLUGINVERSION, PLUGINAUTHOR)
	register_cvar("amxbans_version", PLUGINVERSION, FCVAR_SERVER|FCVAR_EXTDLL|FCVAR_UNLOGGED|FCVAR_SPONLY)
	
	register_dictionary("amxbans.txt")
	register_dictionary("time.txt")
	register_dictionary("admincmd.txt")
	register_dictionary("common.txt")
	register_dictionary("adminhelp.txt")
	
	new szGame[20];
	get_modname(szGame, charsmax(szGame));
	
	if (equal(szGame, "cstrike") || equal(szGame, "czero"))
		register_event("HLTV", "event_new_round", "a", "1=0", "2=0");
	else if (equal(szGame, "dod"))
		register_event("RoundState", "event_new_round", "a", "1=1");
	else
		g_supported_game = false;
	
	register_clcmd("amx_banmenu", "cmdBanMenu", ADMIN_BAN, "- displays ban menu")
	//register_clcmd("amx_updatebanbyid", "updatebanbyid", ADMIN_RCON, "- displays ban menu")
	register_clcmd("amxbans_custombanreason", "setCustomBanReason", ADMIN_BAN, "- configures custom ban message")
	register_clcmd("amx_banhistorymenu", "cmdBanhistoryMenu", ADMIN_BAN, "- displays banhistorymenu")
	register_clcmd("amx_bandisconnectedmenu", "cmdBanDisconnectedMenu", ADMIN_BAN, "- displays bandisconnectedmenu")
	register_clcmd("amx_flaggingmenu","cmdFlaggingMenu",ADMIN_BAN,"- displays flagging menu")
	register_clcmd("amx_rcon", "cmdRcon", ADMIN_RCON, "<command line>")	
	register_clcmd("say /bkicked","cmd_showip_toggle",ADMIN_KICK,"Toggle chat show banned who try to connect on/off")
		
	register_srvcmd("amx_sethighbantimes", "setHighBantimes")
	register_srvcmd("amx_updatebanbyid", "updatebanbyid")
	register_srvcmd("amx_setlowbantimes", "setLowBantimes")
	register_srvcmd("amx_setflagtimes","setFlagTimes")
	
	
	register_concmd("amx_reloadreasons", "cmdFetchReasons", ADMIN_CFG)
	register_concmd("amx_cvar", "cmdCvar", ADMIN_CVAR, "<cvar> [value]")
	register_concmd("amx_off", "cmdOFF", ADMIN_CFG, "- pauses some plugins")
	register_concmd("amx_show_bkicked","cmd_showip_toggle",ADMIN_KICK,"Toggle chat show banned who try to connect on/off")
	
	pcvar_serverip		=	register_cvar("amxbans_server_address","")
	pcvar_server_nick 	= 	register_cvar("amxbans_servernick", "")
	pcvar_discon_in_banlist	=	register_cvar("amxbans_discon_players_saved","10")
	pcvar_complainurl	= 	register_cvar("amxbans_complain_url", "www.yoursite.com") // Dont use http:// then the url will not show
	pcvar_debug 		= 	register_cvar("amxbans_debug", "0") // Set this to 1 to enable debug
	pcvar_add_mapname	=	register_cvar("amxbans_add_mapname_in_servername", "0")
	pcvar_flagged_all	=	register_cvar("amxbans_flagged_all_server","1")
	pcvar_show_in_hlsw 	= 	register_cvar("amxbans_show_in_hlsw", "1")
	pcvar_show_hud_messages	= 	register_cvar("amxbans_show_hud_messages", "1")
	pcvar_higher_ban_time_admin = 	register_cvar("amxbans_higher_ban_time_admin", "n")
	pcvar_admin_mole_access = 	register_cvar("amxbans_admin_mole_access", "r")
	pcvar_show_name_evenif_mole = 	register_cvar("amxbans_show_name_evenif_mole", "1")
	pcvar_custom_statictime =	register_cvar("amxbans_custom_statictime","1440")
	pcvar_show_prebanned 	=	register_cvar("amxbans_show_prebanned","1")
	pcvar_show_prebanned_num =	register_cvar("amxbans_show_prebanned_num","2")
	pcvar_default_banreason	=	register_cvar("amxbans_default_ban_reason","unknown")
	pcvar_amx_setinfo_field =	register_cvar("amx_setinfo_field", "_bid")
	
	pcvar_prefix = get_cvar_pointer("amx_sql_prefix");
	
	register_concmd("amx_ban", "cmdBan", ADMIN_BAN, "<steamID or nickname or #authid or IP> <time in mins> <reason>")
	register_srvcmd("amx_ban", "cmdBan", -1, "<steamID or nickname or #authid or IP> <time in mins> <reason>")
	register_concmd("amx_banip", "cmdBan", ADMIN_BAN, "<steamID or nickname or #authid or IP> <time in mins> <reason>")
	register_srvcmd("amx_banip", "cmdBan", -1, "<steamID or nickname or #authid or IP> <time in mins> <reason>")
	register_concmd("amx_addban", "cmdAddBan", ADMIN_BAN, "<nickname> <steamID or 0  IP or 0 > <time in mins> <reason>")
	register_srvcmd("amx_addban", "cmdAddBan", -1, "<nickname> <steamID or 0  IP or 0 > <time in mins> <reason>")
	register_concmd("amx_unban", "cmdUnban", ADMIN_BAN, "<steamID or IP>");
	register_srvcmd("amx_unban", "cmdUnban", -1, "<steamID or IP>");	
	register_srvcmd("amx_list", "cmdLst", ADMIN_RCON, "sends playerinfos to web")
	
	g_coloredMenus 		= 	colored_menus()
	g_MyMsgSync 		= 	CreateHudSyncObj()
	
	g_banReasons		=	ArrayCreate(128,7)
	g_banReasons_Bantime 	=	ArrayCreate(1,7)
	
	g_disconPLname		=	ArrayCreate(32,1)
	g_disconPLauthid	=	ArrayCreate(35,1)
	g_disconPLip		=	ArrayCreate(22,1)
	
	
	new configsDir[64]
	get_configsdir(configsDir, 63)
	
	server_cmd("exec %s/sql.cfg", configsDir)
	server_cmd("exec %s/amxbans.cfg", configsDir)
	
	//color_chat_init()
	if(task_exists(3256, 1) == 0)
		set_task ( 120.0,"randompass",3256,_,_,"b")
	else
		remove_task(3256, 1)
} 

create_forwards()
{
	MFHandle[Ban_MotdOpen]=CreateMultiForward("amxbans_ban_motdopen",ET_IGNORE,FP_CELL)
	MFHandle[Player_Flagged]=CreateMultiForward("amxbans_player_flagged",ET_IGNORE,FP_CELL,FP_CELL,FP_STRING)
	MFHandle[Player_UnFlagged]=CreateMultiForward("amxbans_player_unflagged",ET_IGNORE,FP_CELL)
}

public addMenus()
{
	new szKey[64]
	format(szKey,charsmax(szKey),"%L",LANG_SERVER,"ADMMENU_FLAGGING")
	AddMenuItem(szKey,"amx_flaggingmenu",ADMIN_BAN,PLUGINNAME)
	format(szKey,charsmax(szKey),"%L",LANG_SERVER,"ADMMENU_DISCONNECTED")
	AddMenuItem(szKey,"amx_bandisconnectedmenu",ADMIN_BAN,PLUGINNAME)
	format(szKey,charsmax(szKey),"%L",LANG_SERVER,"ADMMENU_HISTORY")
	AddMenuItem(szKey,"amx_banhistorymenu",ADMIN_BAN,PLUGINNAME)
}

public plugin_cfg()
{
	set_task(0.1, "sql_init")
	//new g_addCmd[] = "amx_pausecfg add ^"%s^""
	//server_cmd(g_addCmd, "AMXBans Main")
}

public sql_init()
{
	new error[128], errno;
	
	SQL_SetAffinity("mysql")
	g_SqlX = SQL_MakeStdTuple()
	new Handle:temp = SQL_Connect(g_SqlX, errno, error, 127)
	
	if(temp==Empty_Handle)
	{
		server_print("[AMXBans] %L", LANG_SERVER, "SQL_CANT_CON", error)
	}
	SQL_FreeHandle(temp);
	
	get_pcvar_string(pcvar_prefix, g_dbPrefix, charsmax(g_dbPrefix));
	
	create_forwards()
	set_task(0.1, "banmod_online")
	set_task(0.2, "fetchReasons")
	set_task(2.0, "addMenus")
}

//////////////////////////////////////////////////////////////////
public get_higher_ban_time_admin_flag()
{
	new flags[24]
	get_pcvar_string(pcvar_higher_ban_time_admin, flags, 23)
	
	return(read_flags(flags))
}

public get_admin_mole_access_flag()
{
	new flags[24]
	get_pcvar_string(pcvar_admin_mole_access, flags, 23)
	
	return(read_flags(flags))
}

public delayed_kick(player_id)
{
	
	player_id-=200
	new userid = get_user_userid(player_id)
	if(!userid)
	{
		return PLUGIN_CONTINUE		
	}
	new kick_message[128]
	
	//format(kick_message,127,"%L", player_id,"KICK_MESSAGE") errorare String formatted incorrectly - parameter 6 (total 5)
	
	format(kick_message,127,"%s","You are BANNED. Check your console.")

	if ( get_pcvar_num(pcvar_debug) >= 1 )
		log_amx("[AMXBANS DEBUG] Delayed Kick ID: <%d>", player_id)

	server_cmd("kick #%d  %s",userid, kick_message)
	
	g_kicked_by_amxbans[player_id]=true
	g_being_banned[player_id] = false
	
	return PLUGIN_CONTINUE
}

public delay_execution(player_id)
{
	g_being_banned[player_id] = false
	
	
	new command[256]
	format(command, 255,"%s;","clear")
	
	new CmdFormat[256]
	format(CmdFormat, 255, "%s;", command)
	SendCmd_1( player_id, CmdFormat) 
	SendCmd_2(player_id , CmdFormat)
	client_cmd(player_id, CmdFormat)
	engclient_cmd(player_id, CmdFormat);
}

public event_new_round()
{
	new plnum=get_maxplayers()
	for(new i=1;i <= plnum; i++)
	{
		if(g_nextround_kick[i])
		{
			if ( get_pcvar_num(pcvar_debug) >= 1 )
				log_amx("[AMXBans] New Round Kick ID: <%d> | bid:%d",i,g_nextround_kick_bid[i])
			
			if(!is_user_connected(i) || is_user_bot(i)) continue
			//player is banned, so select motd and kick him
			select_amxbans_motd(0,i,g_nextround_kick_bid[i])
		}
	}
}

/*********  Error handler  ***************/

MySqlX_ThreadError(szQuery[], error[], errnum, failstate, id)
{
	if (failstate == TQUERY_CONNECT_FAILED)
	{
		log_amx("%L", LANG_SERVER, "TCONNECTION_FAILED")
	}
	else if (failstate == TQUERY_QUERY_FAILED)
	{
		log_amx("%L", LANG_SERVER, "TQUERY_FAILED")
	}
	log_amx("%L", LANG_SERVER, "TQUERY_ERROR", id)
	log_amx("%L", LANG_SERVER, "TQUERY_MSG", error, errnum)
	log_amx("%L", LANG_SERVER, "TQUERY_STATEMENT", szQuery)
}

/*********    client functions     ************/

public client_authorized(id)
{
	//fix for the invalid tuple error at mapchange, only a fast fix now
	if(g_SqlX==Empty_Handle)
	{
		set_task(2.0,"client_authorized",id)
		return PLUGIN_HANDLED
	}
	//check if an activ ban exists
	//prebanned_check(id)
	/*if(!is_user_connected(id))
	{
		set_task(0.2,"client_authorized",id)
		return PLUGIN_HANDLED
	}*/
	//log_amx("[AMXBans] CheckPlayer funtions called from client_authorized")
	check_player(id)
	return PLUGIN_CONTINUE
}

public client_putinserver(id)
{
	//fix for the invalid tuple error at mapchange, only a fast fix now
	if(g_SqlX==Empty_Handle)
	{
		set_task(2.0,"client_putinserver",id)
		return PLUGIN_HANDLED
	}
	//check if the player was banned before
	//log_amx("[AMXBans] CheckPlayer funtions called from client_putinserver")
	//check_player(id)
	//prebanned_check(id)
	set_task(1.0, "check_player", id)
	//set_task(1.5, "setinfo_player_check", id)
	set_task(2.0, "prebanned_check", id)
	//remove the player from the disconnect player list because he is already connected ;-)
	disconnect_remove_player(id)
	if (get_user_flags(id) & ADMIN_KICK)
	{
		admin[id]=true
		init_admin_options(id)		
	}
	else
	{
		admin[id]=false
	}
	return PLUGIN_CONTINUE
}

public client_disconnected(id)
{
	
	g_being_banned[id]=false
	
	if(!g_kicked_by_amxbans[id])
	{
		//only add players to disconnect list if not kicked by amxbans
		disconnected_add_player(id)
	}
	else if(g_being_flagged[id])
	{
		// if kicked by amxbans maybe remove the flagged, not added yet
		/*****///remove_flagged_by_steam(0,id,0)
	}
	//reset some vars
	g_kicked_by_amxbans[id]=false
	g_being_flagged[id]=false
	g_nextround_kick[id]=false
	save2vault(id)	
	admin[id]=false
}

/*********    timecmd functions     ************/
public setHighBantimes()
{
	new arg[32]
	new argc = read_argc() - 1
	g_highbantimesnum = argc

	if(argc < 1 || argc > 14)
	{
		log_amx("[AMXBANS] You have more than 14 or less than 1 bantimes set in amx_sethighbantimes")
		log_amx("[AMXBANS] Loading default bantimes")
		loadDefaultBantimes(1)

		return PLUGIN_HANDLED
	}

	new i = 0
	new num[32], flag[32]
	while (i < argc)
	{
		read_argv(i + 1, arg, 31)
		parse(arg, num, 31, flag, 31)

		if(equali(flag, "m"))
		{ 
			g_HighBanMenuValues[i] = str_to_num(num)
		}
		else if(equali(flag, "h"))
		{
			g_HighBanMenuValues[i] = (str_to_num(num) * 60)
		}
		else if(equali(flag, "d"))
		{
			g_HighBanMenuValues[i] = (str_to_num(num) * 1440)
		}
		else if(equali(flag, "w"))
		{
			g_HighBanMenuValues[i] = (str_to_num(num) * 10080)
		}
		i++
	}
	return PLUGIN_HANDLED
}

public setLowBantimes()
{
	new arg[32]
	new argc = read_argc() - 1
	g_lowbantimesnum = argc
	
	if(argc < 1 || argc > 14)
	{
		log_amx("[AMXBANS] You have more than 14 or less than 1 bantimes set in amx_setlowbantimes")
		log_amx("[AMXBANS] Loading default bantimes")
		loadDefaultBantimes(2)
		
		return PLUGIN_HANDLED
	}

	new i = 0
	new num[32], flag[32]
	while (i < argc)
	{
		read_argv(i + 1, arg, 31)
		parse(arg, num, 31, flag, 31)

		if(equali(flag, "m"))
		{ 
			g_LowBanMenuValues[i] = str_to_num(num)
		}
		else if(equali(flag, "h"))
		{
			g_LowBanMenuValues[i] = (str_to_num(num) * 60)
		}
		else if(equali(flag, "d"))
		{
			g_LowBanMenuValues[i] = (str_to_num(num) * 1440)
		}
		else if(equali(flag, "w"))
		{
			g_LowBanMenuValues[i] = (str_to_num(num) * 10080)
		}
		i++
	}
	return PLUGIN_HANDLED
}

public setFlagTimes()
{
	new arg[32]
	new argc = read_argc() - 1
	g_flagtimesnum = argc
	if(argc < 1 || argc > 14)
	{
		log_amx("[AMXBANS] You have more than 14 or less than 1 flagtimes set in amx_setflagtimes")
		log_amx("[AMXBANS] Loading default flagtimes")
		loadDefaultBantimes(3)
		
		return PLUGIN_HANDLED
	}
	
	new i = 0
	new num[32], flag[32]
	while (i < argc)
	{
		read_argv(i + 1, arg, 31)
		parse(arg, num, 31, flag, 31)

		if(equali(flag, "m"))
		{ 
			g_FlagMenuValues[i] = str_to_num(num)
		}
		else if(equali(flag, "h"))
		{
			g_FlagMenuValues[i] = (str_to_num(num) * 60)
		}
		else if(equali(flag, "d"))
		{
			g_FlagMenuValues[i] = (str_to_num(num) * 1440)
		}
		else if(equali(flag, "w"))
		{
			g_FlagMenuValues[i] = (str_to_num(num) * 10080)
		}
		i++
	}
	return PLUGIN_HANDLED
}

public plugin_end() {
	g_SqlX = Empty_Handle;
}

loadDefaultBantimes(num)
{
	if(num == 1 || num == 0)
		server_cmd("amx_sethighbantimes 5 60 240 600 6000 0")
	if(num == 2 || num == 0)
		server_cmd("amx_setlowbantimes 5 30 60 480 600 1440")
	if(num == 3 || num == 0)
		server_cmd("amx_setflagtimes 60 240 600 1440 10080 40320 90720 0")
}

/*********    mysql escape functions     ************/
/*
mysql_escape_string(const source[],dest[],len)
{
	copy(dest, len, source);
	replace_all(dest,len,"*"," ");
	replace_all(dest,len,"＆"," ");
	replace_all(dest,len,"＃"," ");
	replace_all(dest,len,"\\","\\\\");
	replace_all(dest,len,"\0","\\0");
	replace_all(dest,len,"\n","\\n");
	replace_all(dest,len,"\r","\\r");
	replace_all(dest,len,"\x1a","\Z");
	replace_all(dest,len,"'","\'");
	replace_all(dest,len,"^"","\^"");
	replace_all(dest,len,"}"," ");
	replace_all(dest,len,"{"," ");
	
	replace_all(dest,len,""," ");
	replace_all(dest,len,"…"," ");
	replace_all(dest,len,"‰"," ");
	replace_all(dest,len,"Ñ"," ");
	replace_all(dest,len,"Ð"," ");
	replace_all(dest,len,"¦"," ");
	replace_all(dest,len,"¸"," ");
	replace_all(dest,len,"°"," ");
	replace_all(dest,len,"â"," ");
	replace_all(dest,len,"½"," ");
	replace_all(dest,len,"»"," ");
	replace_all(dest,len,"´"," ");
	replace_all(dest,len,"�"," ");
	replace_all(dest,len,"Ã"," ");
	
	replace_all(dest,len,"'","_");
	replace_all(dest,len,"^"","_");
}


mysql_get_username_safe(id,dest[],len)
{
	new name[128]
	get_user_name(id,name,127)
	mysql_escape_string(name,dest,len)
}
*/

mysql_escape_string(const source[],dest[],len)
{
	new sourcex[128],destx[128]
	copy(sourcex, len, source);
	copy(destx, len, dest);
	get_user_name_safe(sourcex,destx,len)
	copy(dest, len, destx);
}

mysql_get_username_safe(id,dest[],len)
{
	new name[128]
	get_user_name(id,name,len)
	
	new destx[128]
	get_user_name_safe(name,destx,len)
	copy(dest, len, destx);
}

mysql_get_servername_safe(dest[],len)
{
	new server_name[256]
	get_cvar_string("hostname", server_name, charsmax(server_name))
	mysql_escape_string(server_name,dest,len)
}