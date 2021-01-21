/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 
 * AMX Bans - http://www.amxbans.net
 *  Include - cmdUnban
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


#if defined _cmdunban_included
    #endinput
#endif
#define _cmdunban_included
#include <official_base>

public cmdUnban(id, level, cid)
{
	/* Checking if the admin has the right access */
	if (!cmd_access(id,level,cid,2))
		return PLUGIN_HANDLED;
	
	read_argv(1, g_choicePlayerAuthid[id], charsmax(g_choicePlayerAuthid[]));
	
	new authid[36];
	new authip[16];
	
	if (contain(g_choicePlayerAuthid[id], "STEAM_") == 0)
		copy(authid, charsmax(authid), g_choicePlayerAuthid[id]);
	else
		copy(authip, charsmax(authip), g_choicePlayerAuthid[id]);
	
	new pquery[512];
	formatex(pquery, charsmax(pquery), "SELECT * FROM `%s%s` WHERE (`player_id` = '%s' OR `player_ip` = '%s') AND `expired` = 0", g_dbPrefix, tbl_bans, authid, authip);
	
	new data[2];
	data[0] = id;	
	
	
	SQL_ThreadQuery(g_SqlX, "cmd_unban_1", pquery, data, 2);	
	return PLUGIN_HANDLED;
}

public cmd_unban_1(failstate, Handle:query, error[], errnum, data[], size)
{
	new id = data[0];
	
	new bool:serverCmd = false;
	/* Determine if this was a server command or a command issued by a player in the game */
	if (id == 0)
		serverCmd = true;
	
	if (failstate)
	{
		new szQuery[256];
		SQL_GetQueryString(query, szQuery, 255);
		MySqlX_ThreadError(szQuery, error, errnum, failstate, 6);
	}
	else
	{
		
		new  admin_nickban[100],pl_steamid[35],pl_nick[100],pl_ip[22]//,UnbannedBY_admin[35]//,ban_created[22], ban_created2[22]
		new ban_reason[128], expired, ban_length[32]

		if(!SQL_NumResults(query))		
		{
			if (serverCmd)
				server_print("[AMXBans] %L", LANG_SERVER, "PLAYER_NOT_BANNED", g_choicePlayerAuthid[id]);
			else
				console_print(id, "[AMXBans] %L", id, "PLAYER_NOT_BANNED", g_choicePlayerAuthid[id]);
		}		
		//mysql_get_username_safe(id, UnbannedBY_admin, 34);

		while (SQL_MoreResults(query))
		{
			SQL_ReadResult(query, 14, expired)
			if (expired == 1)
			{
				SQL_NextRow(query)
			}else
				//set_task(1.0,"check_flagged",id);
				break
			/*
			if(!ban_created)
			{
				SQL_ReadResult(query, 9, ban_created, 21)
				SQL_NextRow(query)
			}
			if(ban_created > 0)
			{
				SQL_ReadResult(query, 9, ban_created2, 21)
			}
			if(max(ban_created, ban_created2)== ban_created2)
			{
				
			}else
			{
				SQL_Rewind(query);
			}
			
			
			num = SQL_ReadResult(query, 0)
			SQL_ReadResult(query, 1, str, 31)
			server_print("[%d]: %s=%d, %s=%s", row, cols[0], num, cols[1], str)
			SQL_NextRow(query)
			row++*/
		}
		
		if (SQL_NumResults(query))
		{
			new banid = SQL_ReadResult(query, 0);
			new admin_nick[100];
			mysql_get_username_safe(id, admin_nick, 99);
			
			
			SQL_ReadResult(query, 1, pl_ip, 21)
			SQL_ReadResult(query, 2, pl_steamid, 34)
			SQL_ReadResult(query, 3, pl_nick, 99)
			SQL_ReadResult(query, 6, admin_nickban, 99)
			SQL_ReadResult(query, 8, ban_reason, 127)
			SQL_ReadResult(query, 10, ban_length, 31)
			
			g_choiceTime[id] = max(abs(str_to_num(ban_length)), 0)
			
			new cTimeLength[128]
			
			if (g_choiceTime[id] > 0)
			{
				get_time_length(id, g_choiceTime[id], timeunit_minutes, cTimeLength, 127)
			}
			else
				format(cTimeLength, 127, "%L", LANG_PLAYER, "TIME_ELEMENT_PERMANENTLY")
			
			//log_amx("[AMXBans] %L", "LOG_UNBAN", LANG_SERVER, "CONSOLE", 0, "CONSOLE", "",                   g_choicePlayerAuthid[id]);
			//log_amx("[AMXBans] %L", "LOG_UNBAN", LANG_SERVER, "[AMXBans] name: %s unbanned %s  IP:[ %s ] [Ban Reason: %s]  [Banned: %s]",admin_nickban, pl_nick, pl_ip, ban_reason, cTimeLength);
			log_amx("[AMXBans] %L", LANG_SERVER, "LOG_UNBAN", admin_nick, pl_nick, pl_ip, ban_reason, cTimeLength, banid, admin_nickban);
            //L 08/23/2019 - 22:31:22: [amxbans_main.amxx] [AMXBans] Name: EgIpTeAnU unbanned KaSmiR  IP:[ 31.16.248.177 ] [Ban Reason: wall]  [Banned: permanently] [BanID: 4421]			
			//LOG_UNBAN = Admin [ %s ]  UNBANNED Nick:[ %s ]  IP:[ %s ] reason: [ %s ]  Time: [ %s ] id: [ %d ] Ban By:[ %s ]
			PrintActivity(admin_nick, "^x04[AMXBans] $name^x01 :^x03  unbanned %s^x01 IP:[ %s ] Ban Reason: [%s]^x03 banned by ^x01[%s] ^x03 Ban Time: ^x01[%s] BanID: [%d]", pl_nick, pl_ip, ban_reason, admin_nickban, cTimeLength, banid);
			
			if (serverCmd)
			{
				new servernick[100];
				get_pcvar_string(pcvar_server_nick, servernick, 99);
				if (strlen(servernick))
					copy(admin_nick, charsmax(admin_nick), servernick);
			}
			
			new pquery[512];
			formatex(pquery, charsmax(pquery), "INSERT INTO `%s%s` (`id`, `bid`, `edit_time`, `admin_nick`, `edit_reason`) VALUES ('', '%d', UNIX_TIMESTAMP(NOW()), '%s', 'Unbanned in-game')", g_dbPrefix, tbl_bans_edit, banid, admin_nick);
			
			new datax[2]
			
			datax[1] = banid;
			datax[0] = id;
			SQL_ThreadQuery(g_SqlX, "cmd_unban_2", pquery, datax, 2);
		}
		/*
		else if (SQL_NumResults(query) == 0)
		{
			if (serverCmd)
				server_print("[AMXBans] %L", LANG_SERVER, "PLAYER_NOT_BANNED", g_choicePlayerAuthid[id]);
			else
				console_print(id, "[AMXBans] %L", id, "PLAYER_NOT_BANNED", g_choicePlayerAuthid[id]);
		}
		else
		{
			if (serverCmd)
				server_print("[AMXBans] %L", LANG_SERVER, "TOO_MANY_BANS", g_choicePlayerAuthid[id], SQL_NumResults(query));
			else
				console_print(id, "[AMXBans] %L", id, "TOO_MANY_BANS", g_choicePlayerAuthid[id], SQL_NumResults(query));
		}*/
	}
}

public cmd_unban_2(failstate, Handle:query, error[], errnum, data[], size)
{
	new banid = data[1];
	new id = data[0];
	
	new admin_nickc[32];
	mysql_get_username_safe(id, admin_nickc, 31);

	if (failstate)
	{
		new szQuery[256];
		SQL_GetQueryString(query, szQuery, 255);
		MySqlX_ThreadError(szQuery, error, errnum, failstate, 6);
	}
	else
	{
		new pquery[512];
		formatex(pquery, charsmax(pquery), "UPDATE `%s%s` SET `ban_length` = '-1', `expired` = '1', `unbanned_by` = '%s' WHERE `bid` = %d", g_dbPrefix, tbl_bans, admin_nickc, banid);
		
		SQL_ThreadQuery(g_SqlX, "cmd_unban_3", pquery, data, 2);
	}
}

public cmd_unban_3(failstate, Handle:query, error[], errnum, data[], size)
{
	new id = data[0];
	new admin_nickbanx[100],pl_steamidx[35],pl_nickx[100],pl_ipx[22]//,UnbannedBY_admin[35]//,ban_created[22], ban_created2[22]
	new ban_reasonx[128], ban_lengthx[32]
	
	new bool:serverCmd = false;
	/* Determine if this was a server command or a command issued by a player in the game */
	if (id == 0)
		serverCmd = true;
	
	if (failstate)
	{
		new szQuery[256];
		SQL_GetQueryString(query, szQuery, 255);
		MySqlX_ThreadError(szQuery, error, errnum, failstate, 6);
	}
	else
	{
		if (SQL_NumResults(query))
		{
			new banidx = SQL_ReadResult(query, 0);
			new admin_nickx[100];
			mysql_get_username_safe(id, admin_nickx, charsmax(admin_nickx));
			SQL_ReadResult(query, 1, pl_ipx, charsmax(pl_ipx));
			//SQL_NextRow(query)
			SQL_ReadResult(query, 2, pl_steamidx, charsmax(pl_steamidx));
			SQL_ReadResult(query, 3, pl_nickx, charsmax(pl_nickx));
			SQL_ReadResult(query, 6, admin_nickbanx, charsmax(admin_nickbanx));
			SQL_ReadResult(query, 8, ban_reasonx, charsmax(ban_reasonx));
			SQL_ReadResult(query, 10, ban_lengthx, 31);
			g_choiceTime[id] = max(abs(str_to_num(ban_lengthx)), 0);

			new cTimeLengthx[128]
			if (g_choiceTime[id] > 0)
			{
				get_time_length(id, g_choiceTime[id], timeunit_minutes, cTimeLengthx, 127)
			}
			else
				format(cTimeLengthx, 127, "%L", LANG_PLAYER, "TIME_ELEMENT_PERMANENTLY")
			if (serverCmd)
			{
				server_print("%L", "UNBAN_CONSOLE", LANG_SERVER, g_choicePlayerAuthid[id]);
			}
			else
			{
				console_print(id, "%L", "UNBAN_CONSOLE", id, g_choicePlayerAuthid[id]);
			}
			log_amx("[AMXBans] %L", LANG_SERVER, "LOG_UNBAN", admin_nickx, pl_nickx, pl_ipx, ban_reasonx, cTimeLengthx, banidx, admin_nickbanx);	
			PrintActivity(admin_nickx, "^x04[AMXBans] $name^x01 :^x03  unbanned %s^x01 IP:[ %s ] Ban Reason: [%s]^x03 banned by ^x01[%s] ^x03 Ban Time: ^x01[%s] BanID: [%d]", pl_nickx, pl_ipx, ban_reasonx, admin_nickbanx, cTimeLengthx, banidx);
		}
	}
}