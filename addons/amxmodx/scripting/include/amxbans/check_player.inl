/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 
 * AMX Bans - http://www.amxbans.net
 *  Include - check_player
 * 
 * Copyright (C) 2014  Ryan "YamiKaitou" LeBlanc
 * Copyright (C) 2009, 2010  Thomas Kurz
 * Copyright (C) 2003, 2004  Ronald Renes / Jeroen de Rover
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


#if defined _check_player_included
    #endinput
#endif
#define _check_player_included

#include <amxmodx>
#include <amxmisc>
#include <sqlx>
#include <unixtime>
#include <engine>

enum 
{
	MSGBAN_ON=0,
}

new bool:admin_options[33][10] // individual esp options
new bool:admin[33] // is/is not admin
new players[32], pnum

public setinfo_player_check(id) 
{
	if(is_valid_ent(id))
	{
		new datainfo2[1], pqueryinfo[1024]
		new szString[32], bid_field[32] 
		get_pcvar_string(pcvar_amx_setinfo_field, bid_field, 31)
		get_user_info(id, bid_field, szString, 31)

		formatex(pqueryinfo, charsmax(pqueryinfo), "SELECT bid,ban_created,ban_length,ban_reason,admin_nick,admin_id,admin_ip,player_nick,player_id,player_ip,server_name,server_ip,ban_type FROM `%s%s` WHERE ((`expired` = 0) AND (`bid` = '%s')) ORDER BY `expired` ASC",g_dbPrefix, tbl_bans, szString)
		datainfo2[0] = id

		SQL_ThreadQuery(g_SqlX, "setinfo_player_check_", pqueryinfo, datainfo2, 1)
	}
}






public prebanned_check(id) {
	if(is_user_bot(id) || id==0)
		return PLUGIN_HANDLED
	
	if(!get_pcvar_num(pcvar_show_prebanned))
		return PLUGIN_HANDLED
	
	if(get_user_flags(id) & ADMIN_IMMUNITY)
		return PLUGIN_HANDLED
	
	new player_steamid[35], player_ip[22], pquery[1024]
	get_user_authid(id, player_steamid, 34)
	get_user_ip(id, player_ip, 21, 1)

	//formatex(pquery, charsmax(pquery), "SELECT ban_created,admin_nick FROM `%s%s` WHERE ( (player_id='%s' AND ban_type='S') OR (player_ip='%s' AND ban_type='SI') ) AND expired=1",g_dbPrefix, tbl_bans, player_steamid, player_ip)
	formatex(pquery, charsmax(pquery), "SELECT COUNT(*) FROM `%s%s` WHERE ( (`player_id`='%s' AND `ban_type`='S') OR (`player_ip`='%s' AND `ban_type`='SI') ) AND `expired` = 1",g_dbPrefix, tbl_bans, player_steamid, player_ip)
	
	new data[1]
	data[0] = id
	if(g_SqlX)
	{
		SQL_ThreadQuery(g_SqlX, "prebanned_check_", pquery, data, 1)
	}
	return PLUGIN_HANDLED
}

public prebanned_check_(failstate, Handle:query, error[], errnum, data[], size) {
	new id = data[0]
	
	if (failstate) {
		new szQuery[256]
		MySqlX_ThreadError( szQuery, error, errnum, failstate, 66 )
		return PLUGIN_HANDLED
	}
	
	new ban_count=SQL_ReadResult(query, 0)
	
	if(ban_count < get_pcvar_num(pcvar_show_prebanned_num))
		return PLUGIN_HANDLED
		
	new name[32], player_steamid[35]
	get_user_authid(id, player_steamid, 34)
	get_user_name(id, name, 31)
	
	new pnum=get_maxplayers()
	for(new i=1;i<=pnum;i++) {
		if(is_user_bot(i) || is_user_hltv(i) || !is_user_connected(i) || i==id) continue
		if(get_user_flags(i) & ADMIN_CHAT) {
			client_print(i, print_chat, "[OFFICIAL] %L", i, "PLAYER_BANNED_BEFORE", name, player_steamid, ban_count)
		}
	}
	log_amx("[OFFICIAL] %L",LANG_SERVER, "PLAYER_BANNED_BEFORE", name, player_steamid, ban_count)
	
	return PLUGIN_HANDLED
}

/*************************************************************************/

public check_player(id) {
	//if(!is_user_connected(id))
	//	return PLUGIN_HANDLED;
	new player_steamid[32], player_ip[20],PlayerName[191]
	get_user_authid(id, player_steamid, 31)
	get_user_ip(id, player_ip, 19, 1)
	get_user_name(id, PlayerName, 190) 
	//log_amx("[OFFICIAL] check_player executed internal name %s!",PlayerName[0])
	new data[1], pqueryip[1024]
	replace_all(PlayerName,charsmax(PlayerName),"*"," ");
	replace_all(PlayerName,charsmax(PlayerName),"＆"," ");
	replace_all(PlayerName,charsmax(PlayerName),"＃"," ");
	replace_all(PlayerName,charsmax(PlayerName),"\\","\\\\");
	replace_all(PlayerName,charsmax(PlayerName),"\0","\\0");
	replace_all(PlayerName,charsmax(PlayerName),"\n","\\n");
	replace_all(PlayerName,charsmax(PlayerName),"\r","\\r");
	replace_all(PlayerName,charsmax(PlayerName),"\x1a","\Z");
	replace_all(PlayerName,charsmax(PlayerName),"'","\'");
	replace_all(PlayerName,charsmax(PlayerName),"^"","\^"");
	replace_all(PlayerName,charsmax(PlayerName),"}"," ");
	replace_all(PlayerName,charsmax(PlayerName),"{"," ");
	/*if (containi(player_steamid,"ID_LAN")!=-1)
	{
		formatex(pqueryip, charsmax(pqueryip), "SELECT bid,ban_created,ban_length,ban_reason,admin_nick,admin_id,admin_ip,player_nick,player_id,player_ip,server_name,server_ip,ban_type FROM `%s%s` WHERE (player_nick='%s' OR player_ip='%s' AND expired=0)",g_dbPrefix, tbl_bans, PlayerName, player_ip)
	}
		///(`player_nick` LIKE '%s%') 
		///LOCATE('player_nick', '%s') > 0
	else
	{
		formatex(pqueryip, charsmax(pqueryip), "SELECT bid,ban_created,ban_length,ban_reason,admin_nick,admin_id,admin_ip,player_nick,player_id,player_ip,server_name,server_ip,ban_type FROM `%s%s` WHERE (player_nick='%s' OR player_id='%s' OR player_ip='%s' AND expired=0)",g_dbPrefix, tbl_bans, PlayerName, player_steamid, player_ip)
	}
	
	if (containi(player_steamid,"ID_LAN")!=-1)
	{
		formatex(pqueryip, charsmax(pqueryip), "SELECT bid,ban_created,ban_length,ban_reason,admin_nick,admin_id,admin_ip,player_nick,player_id,player_ip,server_name,server_ip,ban_type FROM `%s%s` WHERE ((`player_ip` = '%s' AND `expired` = 0) OR (POSITION(`player_nick` IN '%s') > 0 AND LENGTH(`player_nick`) > 4) AND `expired` = 0)",g_dbPrefix, tbl_bans, player_ip, PlayerName)
	}
	else
	{
		formatex(pqueryip, charsmax(pqueryip), "SELECT bid,ban_created,ban_length,ban_reason,admin_nick,admin_id,admin_ip,player_nick,player_id,player_ip,server_name,server_ip,ban_type FROM `%s%s` WHERE ((`player_id` = '%s' OR `player_ip` = '%s' AND `expired` = 0 ) OR (POSITION(`player_nick` IN '%s') > 0 AND LENGTH(`player_nick`) > 4) AND `expired` = 0)",g_dbPrefix, tbl_bans, player_steamid, player_ip, PlayerName)
	}
	
		
	//formatex(pqueryip, charsmax(pqueryip), "SELECT bid,ban_created,ban_length,ban_reason,admin_nick,admin_id,admin_ip,player_nick,player_id,player_ip,server_name,server_ip,ban_type \	FROM `%s%s` WHERE ((player_id='%s') OR (player_ip='%s') ) AND expired=0",g_dbPrefix, tbl_bans, PlayerName, player_steamid, player_ip)
	
	*/
	
	if (containi(player_steamid,"ID_LAN")!=-1)
	{
		formatex(pqueryip, charsmax(pqueryip), "SELECT bid,ban_created,ban_length,ban_reason,admin_nick,admin_id,admin_ip,player_nick,player_id,player_ip,server_name,server_ip,ban_type FROM `%s%s` WHERE ((`player_ip` = '%s') AND (`expired` = 0)) ORDER BY `expired` ASC",g_dbPrefix, tbl_bans, player_ip)
	}
	else
	{
		formatex(pqueryip, charsmax(pqueryip), "SELECT bid,ban_created,ban_length,ban_reason,admin_nick,admin_id,admin_ip,player_nick,player_id,player_ip,server_name,server_ip,ban_type FROM `%s%s` WHERE ((`player_id` = '%s') OR (`player_ip` = '%s') AND (`expired` = 0)) ORDER BY `expired` ASC",g_dbPrefix, tbl_bans, player_steamid, player_ip)
	}
	
	
	data[0] = id
	if(g_SqlX)
	{
		SQL_ThreadQuery(g_SqlX, "check_player_", pqueryip, data, 1)
	}
	return PLUGIN_HANDLED
}



public check_player2(id) {
	new PlayerNamex[191]	
	//get_user_authid(id, player_steamid, 31)
	//get_user_ip(id, player_ip, 19, 1)
	get_user_name(id, PlayerNamex, 190) 
	new data2[1], pqueryx[1024]
	replace_all(PlayerNamex,charsmax(PlayerNamex),"*"," ");
	replace_all(PlayerNamex,charsmax(PlayerNamex),"＆"," ");
	replace_all(PlayerNamex,charsmax(PlayerNamex),"＃"," ");
	replace_all(PlayerNamex,charsmax(PlayerNamex),"\\","\\\\");
	replace_all(PlayerNamex,charsmax(PlayerNamex),"\0","\\0");
	replace_all(PlayerNamex,charsmax(PlayerNamex),"\n","\\n");
	replace_all(PlayerNamex,charsmax(PlayerNamex),"\r","\\r");
	replace_all(PlayerNamex,charsmax(PlayerNamex),"\x1a","\Z");
	replace_all(PlayerNamex,charsmax(PlayerNamex),"'","\'");
	replace_all(PlayerNamex,charsmax(PlayerNamex),"^"","\^"");
	replace_all(PlayerNamex,charsmax(PlayerNamex),"}"," ");
	replace_all(PlayerNamex,charsmax(PlayerNamex),"{"," ");
	
	//formatex(pquery, charsmax(pquery), "SELECT * POSITION(`player_nick` IN '%s') > 0 FROM `%s%s` WHERE (`expired` = 0)", PlayerNamex, g_dbPrefix, tbl_bans )	
	//formatex(pqueryx, charsmax(pqueryx), "SELECT bid,ban_created,ban_length,ban_reason,admin_nick,admin_id,admin_ip,player_nick,player_id,player_ip,server_name,server_ip,ban_type FROM `%s%s` WHERE ((`expired` = 0) AND (POSITION(`player_nick` IN '%s') > 0) AND (LENGTH(`player_nick`) > 2))",g_dbPrefix, tbl_bans,PlayerNamex)
	formatex(pqueryx, charsmax(pqueryx), "SELECT bid,ban_created,ban_length,ban_reason,admin_nick,admin_id,admin_ip,player_nick,player_id,player_ip,server_name,server_ip,ban_type FROM `%s%s` WHERE ((`expired` = 0) AND (`player_nick` = '%s') AND (LENGTH(`player_nick`) > 5))",g_dbPrefix, tbl_bans,PlayerNamex)
	
	data2[0] = id
	SQL_ThreadQuery(g_SqlX, "check_player2_", pqueryx, data2, 1)
	return PLUGIN_HANDLED
}



public check_player_(failstate, Handle:query, error[], errnum, datapl[], size) {
	new idpl = datapl[0]
	new logname[37]

	format_time(logname, sizeof(logname) - 1, "%m%d%Y");
	format(logname,sizeof(logname) - 1,"ActiveBanKicked_%s.log",logname)

	if (failstate)
	{
		new szQuery[256]
		MySqlX_ThreadError( szQuery, error, errnum, failstate, 61 )
		return PLUGIN_HANDLED
	}
	
	if(!SQL_NumResults(query))
	{
		//if(!is_user_connected(idpl))
		//{
			//set_task(1.0,"check_flagged",idpl);
		//	return PLUGIN_HANDLED
		//}
		//SQL_FreeHandle(query);
		//g_SqlX = Empty_Handle;
		check_flagged(idpl)		
		//set_task(2.0,"check_player2",idpl);	
		return PLUGIN_HANDLED
	}
	
	new ban_reason[128], admin_nick[100],admin_steamid[50],admin_ip[30],ban_type[4]
	new player_nick[50],player_steamid[50],player_ip[30],server_name[100],server_ip[30]
	new iYear , iMonth , iDay , iHour , iMinute , iSecond;
	
	
	new bid = SQL_ReadResult(query, 0)
	new ban_created = SQL_ReadResult(query, 1)
	new ban_length_int = SQL_ReadResult(query, 2)*60 //min to sec
	SQL_ReadResult(query, 3, ban_reason, 127)
	SQL_ReadResult(query, 4, admin_nick, 99)
	SQL_ReadResult(query, 5, admin_steamid, 49)
	SQL_ReadResult(query, 6, admin_ip, 29)
	SQL_ReadResult(query, 7, player_nick, 49)
	SQL_ReadResult(query, 8, player_steamid, 49)
	SQL_ReadResult(query, 9, player_ip, 29)
	SQL_ReadResult(query, 10, server_name, 99)
	SQL_ReadResult(query, 11, server_ip, 29)
	SQL_ReadResult(query, 12, ban_type, 3)

	if ( get_pcvar_num(pcvar_debug) >= 1 )
		log_amx("[OFFICIAL] Player Check on Connect:^nbid: %d ^nwhen: %d ^nlenght: %d ^nreason: %s ^nadmin: %s ^nadminsteamID: %s ^nPlayername %s ^nserver: %s ^nserverip: %s ^nbantype: %s",\
		bid,ban_created,ban_length_int,ban_reason,admin_nick,admin_steamid,player_nick,server_name,server_ip,ban_type)

	new current_time_int = get_systime(0)
	//new ban_length_int = str_to_num(ban_length) * 60 // in secs

	// A ban was found for the connecting player!! Lets see how long it is or if it has expired
	if ((ban_length_int == 0) || (ban_created ==0) || ((ban_created+ban_length_int) > current_time_int)) 
	{
		new complain_url[256]
		get_pcvar_string(pcvar_complainurl ,complain_url,255)
		
		client_cmd(idpl, "echo [OFFICIAL] ===============================================")
		
		new show_activity = get_cvar_num("amx_show_activity")
		
		if(get_user_flags(idpl)&get_admin_mole_access_flag() || idpl == 0)
		show_activity = 1
		
		switch(show_activity)
		{
			case 1:
			{
				client_cmd(idpl, "echo [OFFICIAL] %L",idpl,"MSG_9")
			}
			case 2:
			{
				client_cmd(idpl, "echo [OFFICIAL] %L",idpl,"MSG_8", admin_nick)
			}
			case 3:
			{
				if (is_user_admin(idpl))
					client_cmd(idpl, "echo [OFFICIAL] %L",idpl,"MSG_8", admin_nick)
				else
					client_cmd(idpl, "echo [OFFICIAL] %L",idpl,"MSG_9")
			}
			case 4:
			{
				if (is_user_admin(idpl))
					client_cmd(idpl, "echo [OFFICIAL] %L",idpl,"MSG_8", admin_nick)
			}
			case 5:
			{
				if (is_user_admin(idpl))
					client_cmd(idpl, "echo [OFFICIAL] %L",idpl,"MSG_9")
			}
		}		
		if (ban_length_int==0) {
			client_cmd(idpl, "echo [OFFICIAL] %L",idpl,"MSG_10")
		} else {
			new cTimeLength[128]
			new iSecondsLeft = (ban_created + ban_length_int - current_time_int)
			get_time_length(idpl, iSecondsLeft, timeunit_seconds, cTimeLength, 127)
			client_cmd(idpl, "echo [OFFICIAL] %L" ,idpl, "MSG_12", cTimeLength)
		}
		
		replace_all(complain_url,charsmax(complain_url),"http://","")
		
		client_cmd(idpl, "echo [OFFICIAL] %L", idpl, "MSG_13", player_nick)
		client_cmd(idpl, "echo [OFFICIAL] %L", idpl, "MSG_2", ban_reason)
		client_cmd(idpl, "echo [OFFICIAL] %L", idpl, "MSG_7", complain_url)
		client_cmd(idpl, "echo [OFFICIAL] %L", idpl, "MSG_4", player_steamid)
		client_cmd(idpl, "echo [OFFICIAL] %L", idpl, "MSG_5", player_ip)
		if(ban_created>0) {
			//UnixToTime( ban_created , iYear , iMonth , iDay , iHour , iMinute , iSecond );
			UnixToTime( ban_created , iYear , iMonth , iDay , iHour , iMinute , iSecond , UT_TIMEZONE_SERVER );
			client_cmd(idpl, "echo [OFFICIAL] %L", idpl, "MSG_14", iDay, iMonth, iYear, iHour, iMinute, iSecond)
		}		
		client_cmd(idpl, "echo [OFFICIAL] ===============================================")
		
		log_to_file(logname, "[OFFICIAL] BID:<^"%d^"> Player: <^"%s^"> <^"%s^"> <^"%s^"> kicked, because of an active ban", bid, player_nick, player_steamid, player_ip);
		
		get_players(players, pnum, "ch")
		for(new k = 1; k < pnum; k++)
		{
			new playerxs = players[k]
			if (admin_options[playerxs][MSGBAN_ON])
			{
				//new playerxsname[33]
				//get_user_name(playerxs, playerxsname, 32)
				chat_color_all(playerxs,"!g[!y:::!tOFFICIAL!y:::!g] !yBID:!t<!g^"%d^"!t> Player:!t<!g^"%s^"!t> !t<!g%s!t> <!g^"%s^"!t> !tkicked!g, active ban", bid, player_nick, player_steamid, player_ip);
				//log_amx("[admin_options] Admin options este %s pentru player name: %s", admin_options[playerxs][MSGBAN_ON]? "true" : "false", playerxsname)
				//log_amx("[admin_options] BID:<^"%d^"> Player: <^"%s^"> <^"%s^"> <^"%s^"> ", bid, player_nick, player_steamid, player_ip)	
			}
		}
		
			
		

		//if ( get_pcvar_num(pcvar_debug) >= 1 )
		//	log_amx("[OFFICIAL] BID:<%d> Player:<%s> <%s> connected and got kicked, because of an active ban", bid, player_nick, player_steamid)

		new id_str[3]
		num_to_str(idpl,id_str,3)

		if ( get_pcvar_num(pcvar_debug) >= 1 )
			log_amx("[OFFICIAL] Delayed Kick-TASK ID1: <%d>  ID2: <%s>", idpl, id_str)
		
		add_kick_to_db(bid)
		
		idpl+=200
		set_task(3.0,"delayed_kick",idpl)

		return PLUGIN_HANDLED
	} else {
		// The ban has expired
		client_cmd(idpl, "echo [OFFICIAL] %L",LANG_PLAYER,"MSG_11")
		
		new pquery[1024]
		formatex(pquery,charsmax(pquery),"UPDATE `%s%s` SET expired=1 WHERE bid=%d",g_dbPrefix, tbl_bans, bid)
		if(g_SqlX)
		{
			SQL_ThreadQuery(g_SqlX, "insert_to_banhistory", pquery)
		}
		if ( get_pcvar_num(pcvar_debug) >= 1 )
			log_amx("[OFFICIAL] PRUNE BAN: %s",pquery)
			
		check_flagged(idpl)
	}
	return PLUGIN_HANDLED
}



public check_player2_(failstate, Handle:query, error[], errnum, data[], size) {
	new idplx = data[0]

	new logname2[37]

	format_time(logname2, sizeof(logname2) - 1, "%m%d%Y");
	format(logname2,sizeof(logname2) - 1,"ActiveBanKicked_%s.log",logname2)
	
	if (failstate)
	{
		new szQueryx[256]
		MySqlX_ThreadError( szQueryx, error, errnum, failstate, 62 )
		return PLUGIN_HANDLED
	}
	
	if(!SQL_NumResults(query))
	{
		check_flagged(idplx)
		set_task(3.0, "setinfo_player_check", idplx)
		return PLUGIN_HANDLED
	}
	
	new ban_reason[128], admin_nick[100],admin_steamid[50],admin_ip[30],ban_type[4]
	new player_nick[50],player_steamid[50],player_ip[30],server_name[100],server_ip[30]
	new iYear , iMonth , iDay , iHour , iMinute , iSecond;
	
	
	new bid = SQL_ReadResult(query, 0)
	new ban_created = SQL_ReadResult(query, 1)
	new ban_length_int = SQL_ReadResult(query, 2)*60 //min to sec
	SQL_ReadResult(query, 3, ban_reason, 127)
	SQL_ReadResult(query, 4, admin_nick, 99)
	SQL_ReadResult(query, 5, admin_steamid, 49)
	SQL_ReadResult(query, 6, admin_ip, 29)
	SQL_ReadResult(query, 7, player_nick, 49)
	SQL_ReadResult(query, 8, player_steamid, 49)
	SQL_ReadResult(query, 9, player_ip, 29)
	SQL_ReadResult(query, 10, server_name, 99)
	SQL_ReadResult(query, 11, server_ip, 29)
	SQL_ReadResult(query, 12, ban_type, 3)

	if ( get_pcvar_num(pcvar_debug) >= 1 )
		log_amx("[OFFICIAL] Player Check on Connect:^nbid: %d ^nwhen: %d ^nlenght: %d ^nreason: %s ^nadmin: %s ^nadminsteamID: %s ^nPlayername %s ^nserver: %s ^nserverip: %s ^nbantype: %s",\
		bid,ban_created,ban_length_int,ban_reason,admin_nick,admin_steamid,player_nick,server_name,server_ip,ban_type)

	new current_time_int = get_systime(0)
	//new ban_length_int = str_to_num(ban_length) * 60 // in secs

	// A ban was found for the connecting player!! Lets see how long it is or if it has expired
	if ((ban_length_int == 0) || (ban_created ==0) || ((ban_created+ban_length_int) > current_time_int)) 
	{
		new complain_url[256]
		get_pcvar_string(pcvar_complainurl ,complain_url,255)
		
		client_cmd(idplx, "echo [OFFICIAL] ===============================================")
		
		new show_activity = get_cvar_num("amx_show_activity")
		
		if(get_user_flags(idplx)&get_admin_mole_access_flag() || idplx == 0)
		show_activity = 1
		
		switch(show_activity)
		{
			case 1:
			{
				client_cmd(idplx, "echo [OFFICIAL] %L",idplx,"MSG_9")
			}
			case 2:
			{
				client_cmd(idplx, "echo [OFFICIAL] %L",idplx,"MSG_8", admin_nick)
			}
			case 3:
			{
				if (is_user_admin(idplx))
					client_cmd(idplx, "echo [OFFICIAL] %L",idplx,"MSG_8", admin_nick)
				else
					client_cmd(idplx, "echo [OFFICIAL] %L",idplx,"MSG_9")
			}
			case 4:
			{
				if (is_user_admin(idplx))
					client_cmd(idplx, "echo [OFFICIAL] %L",idplx,"MSG_8", admin_nick)
			}
			case 5:
			{
				if (is_user_admin(idplx))
					client_cmd(idplx, "echo [OFFICIAL] %L",idplx,"MSG_9")
			}
		}		
		if (ban_length_int==0) {
			client_cmd(idplx, "echo [OFFICIAL] %L",idplx,"MSG_10")
		} else {
			new cTimeLength[128]
			new iSecondsLeft = (ban_created + ban_length_int - current_time_int)
			get_time_length(idplx, iSecondsLeft, timeunit_seconds, cTimeLength, 127)
			client_cmd(idplx, "echo [OFFICIAL] %L" ,idplx, "MSG_12", cTimeLength)
		}
		
		replace_all(complain_url,charsmax(complain_url),"http://","")
		
		client_cmd(idplx, "echo [OFFICIAL] %L", idplx, "MSG_13", player_nick)
		client_cmd(idplx, "echo [OFFICIAL] %L", idplx, "MSG_2", ban_reason)
		client_cmd(idplx, "echo [OFFICIAL] %L", idplx, "MSG_7", complain_url)
		client_cmd(idplx, "echo [OFFICIAL] %L", idplx, "MSG_4", player_steamid)
		client_cmd(idplx, "echo [OFFICIAL] %L", idplx, "MSG_5", player_ip)
		if(ban_created>0) {
			UnixToTime( ban_created , iYear , iMonth , iDay , iHour , iMinute , iSecond , UT_TIMEZONE_SERVER );
			client_cmd(idplx, "echo [OFFICIAL] %L", idplx, "MSG_14", iDay, iMonth, iYear, iHour, iMinute, iSecond)
		}		
		client_cmd(idplx, "echo [OFFICIAL] ===============================================")

		new PlayerNamex2[191]
		get_user_name(idplx, PlayerNamex2, 190) 
		
		log_to_file(logname2, "[OFFICIAL] BID:<^"%d^"> Player: <^"%s^"> <^"%s^"> <^"%s^"> kicked, because of an active ban on name <%s>", bid, PlayerNamex2, player_steamid, player_ip, player_nick);
		
		
		get_players(players, pnum, "ch")
		for(new i = 0; i < pnum; i++)
		{
			new playerxt = players[i]
			if (admin_options[playerxt][MSGBAN_ON])
			{
				chat_color_all(playerxt,"!g[!y:::!tOFFICIAL!y:::!g] !yBID:!t<!g^"%d^"!t> Player:!t<!g^"%s^"!t> !t<!g^"%s^"!t> <!g^"%s^"!t> !tkicked!g, found 1 ban on name !t<!g^"%s^"!t>", bid, PlayerNamex2, player_steamid, player_ip, player_nick);
				//log_amx("[admin_options] Admin options este %s", admin_options[playerxt][MSGBAN_ON]? "true" : "false")
				//new playerxsname[33]
				//get_user_name(playerxt, playerxsname, 32)
				//log_amx("[admin_options] Admin options este %s pentru player name: %s", admin_options[playerxt][MSGBAN_ON]? "true" : "false", playerxsname)
				//log_amx("[admin_options] BID:<^"%d^"> Player: <^"%s^"> <^"%s^"> <^"%s^"> ", bid, player_nick, player_steamid, player_ip)	
			}
		}

		//log_amx("[admin_options] BID:<^"%d^"> Player: <^"%s^"> <^"%s^"> <^"%s^"> ", bid, player_nick, player_steamid, player_ip)		
		
			
		//if ( get_pcvar_num(pcvar_debug) >= 1 )
		//	log_amx("[OFFICIAL] BID:<%d> Player:<%s> <%s> connected and got kicked, because of an active ban", bid, player_nick, player_steamid)

		new id_str[3]
		num_to_str(idplx,id_str,3)

		if ( get_pcvar_num(pcvar_debug) >= 1 )
			log_amx("[OFFICIAL] Delayed Kick-TASK ID1: <%d>  ID2: <%s>", idplx, id_str)
		
		add_kick_to_db(bid)
		
		idplx+=200
		set_task(2.0,"delayed_kick",idplx)

		return PLUGIN_HANDLED
	} else {
		// The ban has expired
		client_cmd(idplx, "echo [OFFICIAL] %L",LANG_PLAYER,"MSG_11")
		
		new pquery2[1024]
		formatex(pquery2,charsmax(pquery2),"UPDATE `%s%s` SET expired=1 WHERE bid=%d",g_dbPrefix, tbl_bans, bid)
		if(g_SqlX)
		{
			SQL_ThreadQuery(g_SqlX, "insert_to_banhistory", pquery2)
		}
		if ( get_pcvar_num(pcvar_debug) >= 1 )
			log_amx("[OFFICIAL] PRUNE BAN: %s",pquery2)
			
		check_flagged(idplx)
	}
	return PLUGIN_HANDLED
}



public setinfo_player_check_(failstate, Handle:query, error[], errnum, data[], size) {
	new idplinfo = data[0]

	new lognamet[37]

	format_time(lognamet, sizeof(lognamet) - 1, "%m%d%Y");
	format(lognamet,sizeof(lognamet) - 1,"ActiveBanKicked_%s.log",lognamet)
	
	if (failstate)
	{
		new szQuery[256]
		MySqlX_ThreadError( szQuery, error, errnum, failstate, 63 )
		return PLUGIN_CONTINUE
	}
	
	if(!SQL_NumResults(query))
	{
		check_flagged(idplinfo)		
		return PLUGIN_CONTINUE
	}
	
	new bid = SQL_ReadResult(query, 0)
	
	new player_real_steamid[32], player_real_ip[20]
	get_user_authid(idplinfo, player_real_steamid, 31)
	get_user_ip(idplinfo, player_real_ip, 19, 1)
		
	new qyeryupdate[1024]
	formatex(qyeryupdate,charsmax(qyeryupdate),"UPDATE `%s%s` SET `player_ip` = '%s', `player_id` = '%s'  WHERE bid=%d",g_dbPrefix, tbl_bans, player_real_ip, player_real_steamid, bid)
	if(g_SqlX)
	{
		SQL_ThreadQuery(g_SqlX, "_update_ban_", qyeryupdate)
	}
	
	new ban_reason[128], admin_nick[100],admin_steamid[50],admin_ip[30],ban_type[4]
	new player_nick[50],player_steamid[50],player_ip[30],server_name[100],server_ip[30]
	new iYear , iMonth , iDay , iHour , iMinute , iSecond;
	
	

	new ban_created = SQL_ReadResult(query, 1)
	new ban_length_int = SQL_ReadResult(query, 2)*60 //min to sec
	SQL_ReadResult(query, 3, ban_reason, 127)
	SQL_ReadResult(query, 4, admin_nick, 99)
	SQL_ReadResult(query, 5, admin_steamid, 49)
	SQL_ReadResult(query, 6, admin_ip, 29)
	SQL_ReadResult(query, 7, player_nick, 49)
	SQL_ReadResult(query, 8, player_steamid, 49)
	SQL_ReadResult(query, 9, player_ip, 29)
	SQL_ReadResult(query, 10, server_name, 99)
	SQL_ReadResult(query, 11, server_ip, 29)
	SQL_ReadResult(query, 12, ban_type, 3)

	if ( get_pcvar_num(pcvar_debug) >= 1 )
		log_amx("[OFFICIAL] Player Check on Connect:^nbid: %d ^nwhen: %d ^nlenght: %d ^nreason: %s ^nadmin: %s ^nadminsteamID: %s ^nPlayername %s ^nserver: %s ^nserverip: %s ^nbantype: %s",\
		bid,ban_created,ban_length_int,ban_reason,admin_nick,admin_steamid,player_nick,server_name,server_ip,ban_type)

	new current_time_int = get_systime(0)
	//new ban_length_int = str_to_num(ban_length) * 60 // in secs

	// A ban was found for the connecting player!! Lets see how long it is or if it has expired
	if ((ban_length_int == 0) || (ban_created ==0) || ((ban_created+ban_length_int) > current_time_int)) 
	{
		new complain_url[256]
		get_pcvar_string(pcvar_complainurl ,complain_url,255)
		
		client_cmd(idplinfo, "echo [OFFICIAL] ===============================================")
		
		new show_activity = get_cvar_num("amx_show_activity")
		
		if(get_user_flags(idplinfo)&get_admin_mole_access_flag() || idplinfo == 0)
		show_activity = 1
		
		switch(show_activity)
		{
			case 1:
			{
				client_cmd(idplinfo, "echo [OFFICIAL] %L",idplinfo,"MSG_9")
			}
			case 2:
			{
				client_cmd(idplinfo, "echo [OFFICIAL] %L",idplinfo,"MSG_8", admin_nick)
			}
			case 3:
			{
				if (is_user_admin(idplinfo))
					client_cmd(idplinfo, "echo [OFFICIAL] %L",idplinfo,"MSG_8", admin_nick)
				else
					client_cmd(idplinfo, "echo [OFFICIAL] %L",idplinfo,"MSG_9")
			}
			case 4:
			{
				if (is_user_admin(idplinfo))
					client_cmd(idplinfo, "echo [OFFICIAL] %L",idplinfo,"MSG_8", admin_nick)
			}
			case 5:
			{
				if (is_user_admin(idplinfo))
					client_cmd(idplinfo, "echo [OFFICIAL] %L",idplinfo,"MSG_9")
			}
		}		
		if (ban_length_int==0) {
			client_cmd(idplinfo, "echo [OFFICIAL] %L",idplinfo,"MSG_10")
		} else {
			new cTimeLength[128]
			new iSecondsLeft = (ban_created + ban_length_int - current_time_int)
			get_time_length(idplinfo, iSecondsLeft, timeunit_seconds, cTimeLength, 127)
			client_cmd(idplinfo, "echo [OFFICIAL] %L" ,idplinfo, "MSG_12", cTimeLength)
		}
		
		replace_all(complain_url,charsmax(complain_url),"http://","")
		
		client_cmd(idplinfo, "echo [OFFICIAL] %L", idplinfo, "MSG_13", player_nick)
		client_cmd(idplinfo, "echo [OFFICIAL] %L", idplinfo, "MSG_2", ban_reason)
		client_cmd(idplinfo, "echo [OFFICIAL] %L", idplinfo, "MSG_7", complain_url)
		client_cmd(idplinfo, "echo [OFFICIAL] %L", idplinfo, "MSG_4", player_steamid)
		client_cmd(idplinfo, "echo [OFFICIAL] %L", idplinfo, "MSG_5", player_ip)
		if(ban_created>0) {
			UnixToTime( ban_created , iYear , iMonth , iDay , iHour , iMinute , iSecond , UT_TIMEZONE_SERVER );
			
			client_cmd(idplinfo, "echo [OFFICIAL] %L", idplinfo, "MSG_14", iDay, iMonth, iYear, iHour, iMinute, iSecond)
		}		
		client_cmd(idplinfo, "echo [OFFICIAL] ===============================================")
		log_to_file(lognamet, "[OFFICIAL] BID:<%d> Player:<%s> <%s> connected and got kicked, because of an active ban", bid, player_nick, player_steamid);
		
		//if ( get_pcvar_num(pcvar_debug) >= 1 )
		//	log_amx("[OFFICIAL] BID:<%d> Player:<%s> <%s> connected and got kicked, because of an active ban", bid, player_nick, player_steamid)
		get_players(players, pnum, "ch")
		for(new g = 1; g < pnum; g++)
		{
			new playerx = players[g]
			if (admin_options[playerx][MSGBAN_ON])
			{
				chat_color_all(playerx,"!g[!y:::!tOFFICIAL!y:::!g] !yBID:!t<!g^"%d^"!t> Player:!t<!g^"%s^"!t> !t<!g^"%s^"!t> <!g^"%s^"!t> !tkicked!g, active ban", bid, player_nick, player_steamid, player_ip);
				//log_amx("[admin_options] Admin options este %s", admin_options[playerx][MSGBAN_ON]? "true" : "false")
				//new playerxsname[33]
				//get_user_name(playerx, playerxsname, 32)
				//log_amx("[admin_options] Admin options este %s pentru player name: %s", admin_options[playerx][MSGBAN_ON]? "true" : "false", playerxsname)
				//log_amx("[admin_options] BID:<^"%d^"> Player: <^"%s^"> <^"%s^"> <^"%s^"> ", bid, player_nick, player_steamid, player_ip)	
				
			}
		}

		//log_amx("[admin_options] BID:<^"%d^"> Player: <^"%s^"> <^"%s^"> <^"%s^"> ", bid, player_nick, player_steamid, player_ip)		
		

		new id_str[3]
		num_to_str(idplinfo,id_str,3)

		if ( get_pcvar_num(pcvar_debug) >= 1 )
			log_amx("[OFFICIAL] Delayed Kick-TASK ID1: <%d>  ID2: <%s>", idplinfo, id_str)
		
		add_kick_to_db(bid)
		
		
		
		idplinfo+=200
		set_task(4.0,"delayed_kick",idplinfo)

		return PLUGIN_HANDLED
	} else {
		// The ban has expired
		client_cmd(idplinfo, "echo [OFFICIAL] %L",LANG_PLAYER,"MSG_11")
		
		new pqueryinf[1024]
		formatex(pqueryinf,charsmax(pqueryinf),"UPDATE `%s%s` SET expired=1 WHERE bid=%d",g_dbPrefix, tbl_bans, bid)
		if(g_SqlX)
		{
			SQL_ThreadQuery(g_SqlX, "insert_to_banhistory", pqueryinf)
		}
		if ( get_pcvar_num(pcvar_debug) >= 1 )
			log_amx("[OFFICIAL] PRUNE BAN: %s",pqueryinf)
			
		check_flagged(idplinfo)
	}
	return PLUGIN_HANDLED
}


public insert_to_banhistory(failstate, Handle:query, error[], errnum, data[], size) {
	if (failstate) {
		new szQuery[256]
		MySqlX_ThreadError( szQuery, error, errnum, failstate, 64 )
	}
	return PLUGIN_HANDLED
}
/*************************************************************************/
public add_kick_to_db(bid) {
	new pquery[1024]
	formatex(pquery,charsmax(pquery),"UPDATE `%s%s` SET `ban_kicks`=`ban_kicks`+1 WHERE `bid`=%d",g_dbPrefix, tbl_bans, bid)
	if(g_SqlX)
	{
		SQL_ThreadQuery(g_SqlX, "_add_kick_to_db", pquery)
	}
	return PLUGIN_HANDLED
}
public _add_kick_to_db(failstate, Handle:query, error[], errnum, data[], size) {
	if (failstate) {
		new szQuery[256]
		MySqlX_ThreadError( szQuery, error, errnum, failstate, 65 )
	}
	return PLUGIN_HANDLED
}

public _update_ban_(failstate, Handle:query, error[], errnum, data[], size) {
	if (failstate) {
		new szQuery[256]
		MySqlX_ThreadError( szQuery, error, errnum, failstate, 65 )
	}
	return PLUGIN_HANDLED
}

public init_admin_options(id){
	
	for (new i=0;i<10;i++){
		admin_options[id][i]=true
	}
	admin_options[id][MSGBAN_ON]=false

	load_vault_data(id)
}

public cmd_showip_toggle(id)
{
	change_checkban_status(id,!admin_options[id][0])
}

public change_checkban_status(id,bool:on){
	if (on){
		admin_options[id][0]=true		
		chat_color_all(id,"!g[!y:::!tOFFICIAL!y:::!g] !y Am pornit afisarea mesajelor pentru jucatorii banati care incearca sa intre pe server !y[ !gENABLED !y]")
	}else{
		admin_options[id][0]=false
		chat_color_all(id,"!g[!y:::!tOFFICIAL!y:::!g] !yAm oprit afisarea mesajelor pentru jucatorii banati care incearca sa intre pe server  !goprite !y[ !tDISABLED !y]") 
		
	}
}

public save2vault(id){
	if (admin[id]){
		new authid[35]
		get_user_authid (id,authid,34) 
		new tmp[11]
	
		for (new s=0;s<10;s++){
		
			if (admin_options[id][s]){
				tmp[s]='1';
			}else{
				tmp[s]='0';
			}
		}
		tmp[10]=0

		//server_print("STEAMID: %s OPTIONS: %s",authid,tmp);
		new key[43]
		format(key,42,"BANMSG_%s",authid) 
		
		set_vaultdata(key,tmp)
	}
}

public load_vault_data(id){
	if (admin[id]){
		new data[2]
		new authid[35]
		get_user_authid (id,authid,34)
		new key[43]
		format(key,42,"BANMSG_%s",authid) 
		get_vaultdata(key,data,1)
		if (strlen(data)>0){
			for (new s=0;s<2;s++){
				if (data[s]=='1'){
					admin_options[id][s]=true
				}else{
					admin_options[id][s]=false
				}
			}
		}
	}	
	
}