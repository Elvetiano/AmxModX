/* AMX Mod X
*   Admin Chat Plugin
*
* by the AMX Mod X Development Team
*  originally developed by OLO
*
* This file is part of AMX Mod X.
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
*/
//"abcdefghijklmnopqrstuv",	//fondator 		biti = 4194303
//"abcdefghijklmnopqrstu",  //manager 		biti = 2097151
//"abcdefhijklmnopqrs",   	//owner 		biti = 524223
//"abcdefhijklmnpqrs",    	//co-owner 		biti = 507839
//"bcdefhijmnot",   		//loyality 		biti = 553918
//"bcdefhijmn",   			//Veteran 		biti = 13246
//"bcdefhijm",    			//Maresal 		biti =  5054
//"bcdefhijr",    			//General 		biti = 132030
//"bcdefhijx",    			//night staff 	biti = 8389566  -w = 4195262
//"bcdefhij",     			//Colonel 		biti = 958
//"bcdefij",      			//Maior 		biti = 830
//"bit",          			// vip gold 	biti = 524546
//"biw",          			// vip silver 	biti = 4194562
//"b"            			// slot 		biti = 2


#include <amxmodx>
#include <amxmisc>
#include <official_base>

#define SHOW_CHAT_ADMINS ADMIN_CHAT
#define SHOW_CHAT_SLOTS ADMIN_RESERVATION
#define SHOW_CHAT_HIGHSTAFF ADMIN_LEVEL_D

#define MAX_GROUPS 12

new g_groupNames[MAX_GROUPS][] = 
{
	"^1(^4Founder^1)",
	"^1(^4Manager^1)",
	"^1(^4Owner^1)",
	"^1(^4Co-Owner^1)",
	"^1(^4Loyalty^1)",
	"^1(^4Veteran^1)",
	"^1(^4Maresal^1)",
	"^1(^4General^1)",
	"^1(^4Maior^1)",
	"^1(^4V.I.P GOLD^1)",
	"^1(^4V.I.P Silver^1)",
	"^1(^4SLOT^1)"
}

new g_groupFlags[MAX_GROUPS][] = 
{
	"bcdefghijkmnopqrsuv",  //fondator
	"bcdefghijkmnopqrsu",   //manager
	"bcdefhijkmnopqrs",   	  //owner
	"bcdefhijkmnpqrs",      //co-owner
	"bcdefhijmnp",   //loyality
	"bcdefhijmn",   //Veteran
	"bcdefhijm",    //Maresal
	"bcdefhij",     //General
	"bcdefij",      //Maior
	"bit",          // vip gold
	"biw",          // vip silver
	"b"             // slot
}


new g_msgChannel

#define MAX_CLR 10

new g_Colors[MAX_CLR][] = {"COL_WHITE", "COL_RED", "COL_GREEN", "COL_BLUE", "COL_YELLOW", "COL_MAGENTA", "COL_CYAN", "COL_ORANGE", "COL_OCEAN", "COL_MAROON"}
new g_Values[MAX_CLR][] = {{255, 255, 255}, {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 0}, {255, 0, 255}, {0, 255, 255}, {227, 96, 8}, {45, 89, 116}, {103, 44, 38}}
new Float:g_Pos[4][] = {{0.0, 0.0}, {0.05, 0.55}, {-1.0, 0.2}, {-1.0, 0.7}}

new amx_show_activity;
new g_AdminChatFlag = ADMIN_CHAT;
new g_AdminHighStaff = ADMIN_LEVEL_D;

new g_groupFlagsValue[MAX_GROUPS]

public plugin_init()
{
	new admin_chat_id,admin_chat_idhigh

	register_plugin("Admin Chat", AMXX_VERSION_STR, "AMXX Dev Team")
	register_dictionary("adminchat.txt")
	register_dictionary("common.txt")
	register_clcmd("say", "cmdSayChat", ADMIN_CHAT, "@[@|@|@][w|r|g|b|y|m|c]<text> - displays hud message")
	register_clcmd("say_team", "cmdSayAdmin", 0, "@<text> - displays message to admins")
	register_concmd("amx_say", "cmdSay", ADMIN_CHAT, "<message> - sends message to all players")
	admin_chat_id = register_concmd("amx_chat", "cmdChat", ADMIN_CHAT, "<message> - sends message to admins")
	admin_chat_idhigh = register_concmd("amx_highchat", "cmdChathigh", ADMIN_LEVEL_D, "<message> - sends message to High staff admins");
	register_concmd("amx_psay", "cmdPsay", ADMIN_CHAT, "<name or #userid> <message> - sends private message")
	register_concmd("amx_tsay", "cmdTsay", ADMIN_CHAT, "<color> <message> - sends left side hud message to all players")
	register_concmd("amx_csay", "cmdTsay", ADMIN_CHAT, "<color> <message> - sends center hud message to all players")
	
	amx_show_activity = get_cvar_pointer("amx_show_activity");
	
	if (amx_show_activity == 0)
	{
		amx_show_activity = register_cvar("amx_show_activity", "2");
	}
	
	for(new i = 0; i < MAX_GROUPS; i++) 
	{
		g_groupFlagsValue[i] =
		read_flags(g_groupFlags[i])
	}

	new str[1],strhigh[1];
	get_concmd(admin_chat_id, str, 0, g_AdminChatFlag, str, 0, -1);
	get_concmd(admin_chat_idhigh, strhigh, 0, g_AdminHighStaff, strhigh, 0, -1);
}

public cmdSayChat(id)
{
	if (!access(id, g_AdminChatFlag))
	{
		return PLUGIN_CONTINUE
	}
	
	new said[6], i = 0
	read_argv(1, said, 5)
	
	while (said[i] == '@')
	{
		i++
	}
	
	if (!i || i > 3)
	{
		return PLUGIN_CONTINUE
	}
	
	new message[192], a = 0
	read_args(message, 191)
	remove_quotes(message)
	
	switch (said[i])
	{
		case 'r': a = 1
		case 'g': a = 2
		case 'b': a = 3
		case 'y': a = 4
		case 'm': a = 5
		case 'c': a = 6
		case 'o': a = 7
	}
	
	new n, s = i
	if (a)
	{
		n++
		s++
	}
	while (said[s] && isspace(said[s]))
	{
		n++
		s++
	}
	

	new name[32], authid[32], userid
	
	get_user_authid(id, authid, 31)
	get_user_name(id, name, 31)
	userid = get_user_userid(id)
	
	log_amx("Chat: ^"%s<%d><%s><>^" tsay ^"%s^"", name, userid, authid, message[i + n])
	log_message("^"%s<%d><%s><>^" triggered ^"amx_tsay^" (text ^"%s^") (color ^"%L^")", name, userid, authid, message[i + n], "en", g_Colors[a])
	
	if (++g_msgChannel > 6 || g_msgChannel < 3)
	{
		g_msgChannel = 3
	}
	
	new Float:verpos = g_Pos[i][1] + float(g_msgChannel) / 35.0
	
	set_hudmessage(g_Values[a][0], g_Values[a][1], g_Values[a][2], g_Pos[i][0], verpos, 0, 6.0, 6.0, 0.5, 0.15, -1)

	switch ( get_pcvar_num(amx_show_activity) )
	{
		case 3, 4:
		{
			new maxpl = get_maxplayers();
			for (new pl = 1; pl <= maxpl; pl++)
			{
				if (is_user_connected(pl) && !is_user_bot(pl))
				{
					if (is_user_admin(pl))
					{
						show_hudmessage(pl, "%s :   %s", name, message[i + n])
						client_print(pl, print_notify, "%s :   %s", name, message[i + n])
					}
					else
					{
						show_hudmessage(pl, "%s", message[i + n])
						client_print(pl, print_notify, "%s", message[i + n])
					}
				}
			}
		}
		case 2:
		{
			show_hudmessage(0, "%s :   %s", name, message[i + n])
			client_print(0, print_notify, "%s :   %s", name, message[i + n])
		}
		default:
		{
			show_hudmessage(0, "%s", message[i + n])
			client_print(0, print_notify, "%s", message[i + n])
		}
	}

	return PLUGIN_HANDLED
}

public cmdSayAdmin(id)
{
	new said[2];
	read_argv(1, said, 1);
	new count = 1, players[32]
	get_players(players, count, "ch")
	
	new message[192], authid[32], userid, name[32];
	
	
	read_args(message, charsmax(message));
	remove_quotes(message);
	get_user_authid(id, authid, 31);
	get_user_name(id, name, 31);
	userid = get_user_userid(id);
	
	new bool:mFound = false;
	for(new i = 0; i < MAX_GROUPS; i++)
	{
		new flag = nCleanFlags(id);
		if(flag == g_groupFlagsValue[i])
		{
			format(message, 191, "%s ^4%s ^1:  !y%s", g_groupNames[i], name, message[1]);
			mFound = true;
		}
	}
	if (!mFound && (get_user_flags(id) & SHOW_CHAT_ADMINS))
	{
		format(message, 191, "%s ^4%s ^1:  !y%s", "^1(^4UNKNOWN^1)", name, message[1]);
	}
	
	if (said[0] != '@')
	{
		if ((said[0] == '$') && (get_user_flags(id) & g_AdminHighStaff))
		{
			format(message, 191, "^1(^3High-STAFF^1) %s",message[1]);			
			chat_color_highadmins(0, id, message[1]);
			
			//replace_all(message, 190, "!g", "")
			//replace_all(message, 190, "!y", "")
			//replace_all(message, 190, "!t", "")
			//replace_all(message, 190, "!n", "")
			//replace_all(message, 190, "^4", "")
			//replace_all(message, 190, "^1", "")
			//replace_all(message, 190, "^3", "")
			//replace_all(message, 190, "^0", "")
			message = remove_colors(0,message)
			log_amx("Chat HIGH STAFF: ^"%s<%d><%s><>^" chat ^"%s^"", name, userid, authid, message[1])
			log_message("^"%s<%d><%s><>^" triggered ^"amx_highchat^" (text ^"%s^")", name, userid, authid, message[1]);
			return PLUGIN_HANDLED;
		}
		else
		{
			return PLUGIN_CONTINUE;
		}
	}	
	
	
	if((get_user_flags(id) & SHOW_CHAT_SLOTS) && !(get_user_flags(id) & SHOW_CHAT_ADMINS))
	{
		chat_color_single(id, "!g%s", message);
	}
	if (!is_user_admin(id))
	{
		format(message, 191, "(%L) %s :  !y%s", id, "PLAYER", name, message[1]);
		chat_color_single(id, "!g%s", message);
	}	
	chat_color_admins(0, "!g%s", message);
	
	message = remove_colors(0,message)
	log_amx("Chat: ^"%s<%d><%s><>^" chat ^"%s^"", name, userid, authid, message[1]);
	log_message("^"%s<%d><%s><>^" triggered ^"amx_chat^" (text ^"%s^")", name, userid, authid, message[1]);
	return PLUGIN_HANDLED;
}

public cmdChat(id, level, cid)
{
	if (!cmd_access(id, level, cid, 2))
		return PLUGIN_HANDLED

	new message[192], name[32], authid[32], userid
	
	read_args(message, 191)
	remove_quotes(message)
	get_user_authid(id, authid, 31)
	get_user_name(id, name, 31)
	userid = get_user_userid(id)
	
	new count = 1, players[32]
	get_players(players, count, "ch")
	
	
	
	/*if((get_user_flags(id) & SHOW_CHAT_HIGHSTAFF))
	{		
		for (new i = 0; i < count; i++)
		{
			if (is_user_connected(players[i]))
			{
				//len = get_user_name(players[i], name[1], charsmax(name)-1) + 1
				//name[len] = sender == players[i] ? '^1' : '^3'
				
				if ((get_user_flags(players[i]) & SHOW_CHAT_ADMINS))
				{
					if (get_user_userid(id) < 1)
						client_print_color(players[i], Red, "^1(^4ADMIN^1) ^3SERVER ^1: ^4%s", message)
					else
						client_print_color(players[i], Red, "^1(^3O^4W^3N^4E^3R^4S^1)^4 %s ^1: %s", name, message)

				}
			}
		}
	}
	else	
	{
		format(message, 191, "!y(!gADMIN!y) !g%s :   !y%s", name, message)
		if (get_user_userid(id) < 1)
			format(message, 191, "!y(!gSERVER!y) :   !g%s", message)
		console_print(id, "%s", message)
		chat_color_admins(0, "!g%s", message)
	}	*/
	for(new i = 0; i < MAX_GROUPS; i++)
	{
		new flag = nCleanFlags(id);
		if(flag == g_groupFlagsValue[i])
		{
			format(message, 191, "%s ^4%s ^1:  !y%s", g_groupNames[i], name, message);			
		}
	}
	if (get_user_userid(id) < 1)
		format(message, 191, "!y(!gSERVER!y) :   !g%s", message)
	console_print(id, "%s", message)
	chat_color_admins(0, "!g%s", message)
	
	message = remove_colors(0,message)
	log_amx("Chat: ^"%s<%d><%s><>^" chat ^"%s^"", name, userid, authid, message)
	log_message("^"%s<%d><%s><>^" triggered ^"amx_chat^" (text ^"%s^")", name, userid, authid, message)
	return PLUGIN_HANDLED
}

public cmdChathigh(id, level, cid)
{	
	if (!cmd_access(id, level, cid, 2))
		return PLUGIN_HANDLED

	new message[192], numele[32], authid[32], userid 
	
	read_args(message, charsmax(message))
	remove_quotes(message)
	get_user_authid(id, authid, charsmax(authid))
	get_user_name(id, numele, charsmax(numele))
	userid = get_user_userid(id)
	
	

	//format(message, 191, "!y%s",  message)
	for(new i = 0; i < MAX_GROUPS; i++)
	{
		new flag = nCleanFlags(id);
		if(flag == g_groupFlagsValue[i])
		{
			format(message, 191, "^1(^3High-STAFF^1) %s ^4%s ^1: %s", g_groupNames[i], numele, message);			
		}
	}
	console_print(id, "%s", message)
	
	chat_color_highadmins(0, id, message)
	
	message = remove_colors(0,message)
	log_amx("Chat HIGH STAFF: ^"%s<%d><%s><>^" chat ^"%s^"", numele, userid, authid, message)
	log_message("^"%s<%d><%s><>^" triggered ^"amx_highchat^" (text ^"%s^")", numele, userid, authid, message)
	return PLUGIN_HANDLED
}

public cmdSay(id, level, cid)
{
	if (!cmd_access(id, level, cid, 2))
		return PLUGIN_HANDLED

	new message[192], name[32], authid[32], userid
	
	read_args(message, 191)
	remove_quotes(message)
	get_user_authid(id, authid, 31)
	get_user_name(id, name, 31)
	userid = get_user_userid(id)
	client_print(0, print_chat, "%L", LANG_PLAYER, "PRINT_ALL", name, message)
	console_print(id, "%L", LANG_PLAYER, "PRINT_ALL", name, message)
	
	log_amx("Chat: ^"%s<%d><%s><>^" say ^"%s^"", name, userid, authid, message)
	log_message("^"%s<%d><%s><>^" triggered ^"amx_say^" (text ^"%s^")", name, userid, authid, message)
	
	return PLUGIN_HANDLED
}

public cmdPsay(id, level, cid)
{
	if (!cmd_access(id, level, cid, 3))
		return PLUGIN_HANDLED
	
	new name[32]
	read_argv(1, name, 31)
	new priv = cmd_target(id, name, 0)

	if (!priv)
		return PLUGIN_HANDLED
	
	new length = strlen(name) + 1

	get_user_name(priv, name, 31); 
	
	new message[192], name2[32], authid[32], authid2[32], userid, userid2
	
	get_user_authid(id, authid, 31)
	get_user_name(id, name2, 31)
	userid = get_user_userid(id)
	read_args(message, 191)
	
	if (message[0] == '"' && message[length] == '"') // HLSW fix
	{
		message[0] = ' '
		message[length] = ' '
		length += 2
	}
	
	remove_quotes(message[length])
	get_user_name(priv, name, 31)
	
	if (id && id != priv)
		client_print_color(id, Grey, "^1(^4%s^1) ^4%s ^1:^4  %s", name, name2, message[length])
		//client_print(id, print_chat, "(%s) %s :   %s", name, name2, message[length])

	
	//client_print(priv, print_chat, "(%s) %s :   %s", name, name2, message[length])
	
	client_print_color(priv, Grey, "^1(^4%s^1) ^4%s ^1:^4  %s", name, name2, message[length])
	
	console_print(id, "(%s) %s :   %s", name, name2, message[length])
	get_user_authid(priv, authid2, 31)
	userid2 = get_user_userid(priv)
	
	log_amx("Chat: ^"%s<%d><%s><>^" psay ^"%s<%d><%s><>^" ^"%s^"", name2, userid, authid, name, userid2, authid2, message[length])
	log_message("^"%s<%d><%s><>^" triggered ^"amx_psay^" against ^"%s<%d><%s><>^" (text ^"%s^")", name2, userid, authid, name, userid2, authid2, message[length])
	
	return PLUGIN_HANDLED
}

public cmdTsay(id, level, cid)
{
	if (!cmd_access(id, level, cid, 3))
		return PLUGIN_HANDLED
	
	new cmd[16], color[16], color2[16], message[192], name[32], authid[32], userid = 0
	
	read_argv(0, cmd, 15)
	new bool:tsay = (tolower(cmd[4]) == 't')
	
	read_args(message, 191)
	remove_quotes(message)
	parse(message, color, 15)
	
	new found = 0, a = 0
	new lang[3], langnum = get_langsnum()

	for (new i = 0; i < MAX_CLR; ++i)
	{
		for (new j = 0; j < langnum; j++)
		{
			get_lang(j, lang)
			format(color2, 15, "%L", lang, g_Colors[i])
			
			if (equali(color, color2))
			{
				a = i
				found = 1
				break
			}
		}
		if (found == 1)
			break
	}
	
	new length = found ? (strlen(color) + 1) : 0
	
	if (++g_msgChannel > 6 || g_msgChannel < 3)
		g_msgChannel = 3

	new Float:verpos = (tsay ? 0.55 : 0.1) + float(g_msgChannel) / 35.0
	
	get_user_authid(id, authid, 31)
	get_user_name(id, name, 31)
	userid = get_user_userid(id)
	set_hudmessage(g_Values[a][0], g_Values[a][1], g_Values[a][2], tsay ? 0.05 : -1.0, verpos, 0, 6.0, 6.0, 0.5, 0.15, -1)

	switch ( get_pcvar_num(amx_show_activity) )
	{
		case 3, 4:
		{
			new maxpl = get_maxplayers();
			for (new pl = 1; pl <= maxpl; pl++)
			{
				if (is_user_connected(pl) && !is_user_bot(pl))
				{
					if (is_user_admin(pl))
					{
						show_hudmessage(pl, "%s :   %s", name, message[length])
						client_print(pl, print_notify, "%s :   %s", name, message[length])
					}
					else
					{
						show_hudmessage(pl, "%s", message[length])
						client_print(pl, print_notify, "%s", message[length])
					}
				}
			}
			console_print(id, "%s :  %s", name, message[length])
		}
		case 2:
		{
			show_hudmessage(0, "%s :   %s", name, message[length])
			client_print(0, print_notify, "%s :   %s", name, message[length])
			console_print(id, "%s :  %s", name, message[length])
		}
		default:
		{
			show_hudmessage(0, "%s", message[length])
			client_print(0, print_notify, "%s", message[length])
			console_print(id, "%s", message[length])
		}
	}

	log_amx("Chat: ^"%s<%d><%s><>^" %s ^"%s^"", name, userid, authid, cmd[4], message[length])
	log_message("^"%s<%d><%s><>^" triggered ^"%s^" (text ^"%s^") (color ^"%s^")", name, userid, authid, cmd, message[length], color2)

	return PLUGIN_HANDLED
}

public remove_colors(id, const input[], any:...)
{
	static messagexy[191]
	vformat(messagexy, 190, input, 3)
	replace_all(messagexy, 190, "!g", "")
	replace_all(messagexy, 190, "!y", "")
	replace_all(messagexy, 190, "!t", "")
	replace_all(messagexy, 190, "!n", "")
	replace_all(messagexy, 190, "^4", "")
	replace_all(messagexy, 190, "^1", "")
	replace_all(messagexy, 190, "^3", "")
	replace_all(messagexy, 190, "^0", "")
	return messagexy
}
