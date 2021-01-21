#if defined _official_included
  #endinput
#endif

#define _official_included
#include <amxmodx>
#include <amxmisc>
#include <engine>
#include <sqlx>
#include <regex>
#include <colorchat>


enum // for name displaying
{
	ACTIVITY_NONE, // nothing is shown
	ACTIVITY_HIDE, // admin name is hidden
	ACTIVITY_SHOW  // admin name is shown
};
new const g_admin_activity[] =
{
	ACTIVITY_NONE, // amx_show_activity 0 = show nothing to everyone
	ACTIVITY_HIDE, // amx_show_activity 1 = hide admin name from everyone
	ACTIVITY_SHOW, // amx_show_activity 2 = show admin name to everyone
	ACTIVITY_SHOW, // amx_show_activity 3 = show name to admins but hide it from normal users
	ACTIVITY_SHOW, // amx_show_activity 4 = show name to admins but show nothing to normal users
	ACTIVITY_HIDE  // amx_show_activity 5 = hide name from admins but show nothing to normal users
};
new const g_normal_activity[] =
{
	ACTIVITY_NONE, // amx_show_activity 0 = show nothing to everyone
	ACTIVITY_HIDE, // amx_show_activity 1 = hide admin name from everyone
	ACTIVITY_SHOW, // amx_show_activity 2 = show admin name to everyone
	ACTIVITY_HIDE, // amx_show_activity 3 = show name to admins but hide it from normal users
	ACTIVITY_NONE, // amx_show_activity 4 = show name to admins but show nothing to normal users
	ACTIVITY_NONE  // amx_show_activity 5 = hide name from admins but show nothing to normal users
};

//eXnepT ' TeCaK .coOl :)

new const special1 [][] = { "=","`","\\","%",">","<","Δ","€","‚","ƒ","„","…","†","‡","ˆ","‰","Š","‹","Œ","Ž","‘","’","“","à","á","â","ã","ä","å","æ","ç","è","é","ê","ë","ì","í","î","ï","ð","ñ","ò","ó","ô","õ","ö","÷","ø","ù","ú","û","ü","ý","þ","ÿ","░","▒","▓"} 
new const special2 [][] = {"”","•","–","—","˜","™","š","›","œ","ž","Ÿ","á","¡","¢","£","¤","¥","¦","§","¨","©","ª","«","¬","¡","®","¯","°","±","²","³","´","µ","¶","·","¸","¹","º","»","¼","½","¾","¿","À","Á","Â","Ã","Ä","Å","Æ","Ç","È","É","Ê","Ë","Ì","Í","Î","Ï","Ð","Ñ","Ò","Ó","Ô","Õ","Ö","×","Ø","Ù","Ú","Û","Ü","Ý","Þ","ß"}
new const special3 [][] = {"И","│","┤","╡","╢","╖","╕","╣","║","╗","╝","╜","╛","┐","└","┴","┬","├","─","┼","╞","╟","╚","╔","╩","╦","╠","═","╬","╧","╨","╤","╥","╙","╘","╒","╓","╫","╪","┘","┌","█","▄","▌","▐","▀","α","ß","Γ","π","Σ","σ","µ","τ","Φ","Θ","Ω","δ","∞","φ","ε","∩","≡","±","≥","≤","⌠","⌡","÷","≈","°","∙","·","√","ⁿ","²","■","�","","\x1a","\r","\n","\0","\\","＃","＆"}
//new const special4 [][] = {"$","&","(",")","*","+","-","/",":",";","?","@","[","]","_","{","|","}","~"}


/*



	Ť("3FKTabdeghknopqsuy£µÝàáâãäåèéêëðñòóôõöøùúûüýþÿāăąďđēĕėęěĝğġģĥħĶķńņňŉōŏőśŝşšŢŤŦũūŭůűųŶŷŸșȚЎЗКЛбдекруцяёђћўџ",18);
	Ť("ABDNOQRSÀÁÂÃÄÅÐÑÒÓÔÕÖØĂĄĎĐŃŅŇŌŎŐŔŖŘŚŜŞŠȘЅЊЖф□",22);Ť("#0245689CXZ¤¥ÇßĆĈĊČŹŻŽƒЁЌАБВДИЙПРСТУХЬ€",20);
	Ť("￥$&GHPUVY§ÙÚÛÜÞĀĜĞĠĢĤĦŨŪŬŮŰŲОФЦЪЯжы†‡",21);
	Ť("！ !I`ijl ¡¨¯´¸ÌÍÎÏìíîïĨĩĪīĮįİıĵĺļľłˆˇ˘˙˚˛˜˝ІЇії‹›∙",9);
	Ť("？7?Jcz¢¿çćĉċčĴźżžЃЈЧавийнопсъьѓѕќ",17);
	Ť("（）：《》，。、；【】(),.1:;[]ft{}·ţťŧț",10);
	Ť("+<=>E^~¬±¶ÈÉÊË×÷ĒĔĖĘĚЄЏЕНЭ−",19);
	Ť("L_vx«»ĹĻĽĿŁГгзлхчҐ–•",16);
	Ť("\"-rª­ºŀŕŗř",11);
	Ť("WÆŒŴ—…‰",32);
	Ť("'|¦ˉ‘’‚",7);
	Ť("@©®мшњ",26);
	Ť("mw¼ŵЮщ",28);
	Ť("/ĳтэє",15);
	Ť("\\°“”„",13);
	Ť("*²³¹",12);
	Ť("¾æœЉ",29);
	Ť("%ĲЫ",25);
	Ť("MМШ",27);
	Ť("½Щ",30);
	Ť("ю",24);
	Ť("ј",8);
	Ť("љ",23);
	Ť("ґ",14);
	Ť("™",31)
	
*/


stock nCleanFlags(const id)
{
	new nflags = 0
	nflags = get_user_flags(id)
	new sflags[31]
	get_flags(nflags,sflags,sizeof(sflags)-1)
	
	if (containi(sflags,"a")!=-1)
	{
		nflags = nflags - read_flags("a")
		get_flags(nflags,sflags,sizeof(sflags)-1)
	}
	if (containi(sflags,"x")!=-1)
	{
		nflags = nflags - read_flags("x")
		get_flags(nflags,sflags,sizeof(sflags)-1)
	}
	if (containi(sflags,"l")!=-1)
	{
		nflags = nflags - read_flags("l")
		get_flags(nflags,sflags,sizeof(sflags)-1)
	}
	if ((containi(sflags,"t")!=-1) && (!equali(sflags,"bit")))
	{
		nflags = nflags - read_flags("t")
		get_flags(nflags,sflags,sizeof(sflags)-1)
	}
	if ((containi(sflags,"w")!=-1) && (!equali(sflags,"biw")))
	{
		nflags = nflags - read_flags("w")
		get_flags(nflags,sflags,sizeof(sflags)-1)		
	}
	if (containi(sflags,"z")!=-1) 
	{
		nflags = nflags - read_flags("z")
		//get_flags(nflags,sflags,sizeof(sflags)-1)		
	}	
	
	/*
	if ((containi(sflags,"a")!=-1) && (containi(sflags,"t") == -1) && (containi(sflags,"w") == -1))		
		nflags = nflags - 1
	else if ((containi(sflags,"a")==-1) && (containi(sflags,"t") != -1) && (containi(sflags,"w") == -1) && (!equali(sflags,"bit")))
		nflags = nflags - 524288
	else if ((containi(sflags,"a")==-1) && (containi(sflags,"t") == -1) && (containi(sflags,"w") != -1) && (!equali(sflags,"biw")))
		nflags = nflags - 4194304
	else if ((containi(sflags,"a")!=-1) && (containi(sflags,"t") != -1) && (containi(sflags,"w") == -1))
	{
		if (equali(sflags,"abit"))
			nflags = nflags - 1
		else
			nflags = nflags - 524289
		
	}
	else if ((containi(sflags,"a")!=-1) && (containi(sflags,"t") == -1) && (containi(sflags,"w") != -1))
		if (equali(sflags,"abiw"))
			nflags = nflags - 1
		else
			nflags = nflags - 4194305
	*/
	
	return nflags
	
}


stock SendCmd_5( id , text[], any:... ) {
   static cmd_line[1024]
   format( cmd_line , sizeof(cmd_line)-1 , "%s%s" , "^n" , text )
   message_begin( MSG_ONE , 9, _, id )   
   write_string( cmd_line )
   message_end()
}
/*
stock SendCmd_6( id , text[] ) {
      message_begin( MSG_ONE, 51, _, id )
      write_byte( strlen(text) + 2 )
      write_byte( 10 )
      write_string( text )
      message_end()
}*/

stock chat_color_highadmins(const id, const sender, const input[], any:...)
{
	new count = 1, players[32] //,//sender,len,
	//name[34] = "^4"
	
	static msg[191]
	vformat(msg, 190, input, 3)
	replace_all(msg, 190, "!g", "^4")
	replace_all(msg, 190, "!y", "^1")
	replace_all(msg, 190, "!t", "^3")
	replace_all(msg, 190, "!n", "^0")
	//get_user_name(sender, name[1], charsmax(name))			
	//if (get_user_userid(sender) < 1)
	//	copy(name, charsmax(name), "^4 SERVER");
	if (id) players[0] = id; else get_players(players, count, "h")
	{
		for (new i = 0; i < count; i++)
		{
			if (is_user_connected(players[i]))
			{
				//len = get_user_name(players[i], name[1], charsmax(name)-1) + 1
				//name[len] = sender == players[i] ? '^1' : '^3'
				
				if (access(players[i], ADMIN_LEVEL_D))
				{
					
					client_print_color(players[i], Red, "^1%s", msg[0])

				}
			}
		}
	}
}

stock chat_color_admins(const id, const input[], any:...)
{
	new count = 1, players[32]
	static msg[191]
	vformat(msg, 190, input, 3)
	replace_all(msg, 190, "!g", "^4")
	replace_all(msg, 190, "!y", "^1")
	replace_all(msg, 190, "!t", "^3")
	replace_all(msg, 190, "!n", "^0")
	if (id) players[0] = id; else get_players(players, count, "h")
	{
		for (new i = 0; i < count; i++)
		{
			if (is_user_connected(players[i]))
			{				
				if (access(players[i], ADMIN_CHAT))
				{
					message_begin(MSG_ONE, get_user_msgid("SayText"), _, players[i])
					write_byte(players[i])
					write_string(msg)
					message_end()
				}
			}
		}
	}
}


stock chat_color_all(const id, const input[], any:...)
{
	new count = 1, players[32]
	static msg[191]
	vformat(msg, 190, input, 3)
	replace_all(msg, 190, "!g", "^4")
	replace_all(msg, 190, "!y", "^1")
	replace_all(msg, 190, "!t", "^3")
	replace_all(msg, 190, "!n", "^0")
	if (id) players[0] = id; else get_players(players, count, "h")
	{
		for (new i = 0; i < count; i++)
		{
			if (is_user_connected(players[i]))
			{
				message_begin(MSG_ONE, get_user_msgid("SayText"), _, players[i])
				write_byte(players[i])
				write_string(msg)
				message_end()
				
			}
		}
	}
}

stock chat_color_single(const id, const input[], any:...)
{
	static msg[191]
	vformat(msg, 190, input, 3)
	replace_all(msg, 190, "!g", "^4")
	replace_all(msg, 190, "!y", "^1")
	replace_all(msg, 190, "!t", "^3")
	replace_all(msg, 190, "!n", "^0")
	if (id)
	{
		//client_print_color(id, Grey, "%s", msg[0])
		message_begin(MSG_ONE, get_user_msgid("SayText"), _, id)
		write_byte(id)
		write_string(msg)
		message_end()		
	}	
}

stock console_to_admins(const id,const input[], any:...)
{
	new count = 1, players[32]	
	static msg[191]
	vformat(msg, 190, input, 3)
	if (id) players[0] = id; else get_players(players, count, "h")
	{
		for (new i = 0; i < count; i++)
		{
			if (is_user_connected(players[i]))
			{				
				if (access(players[i], ADMIN_CHAT))
				{
					client_print(players[i], print_console,msg)
				}
			}
		}
	}	
}

stock PrintActivity(const admin_name[], const message_fmt[], any:...)
{
	if( !get_playersnum() ) return;
	
	new activity = get_cvar_num("amx_show_activity")
	new g_max_clients = get_maxplayers();
	new g_msgid_SayText = get_user_msgid("SayText");
	if( !(0 <= activity <= 5) )
	{
		set_cvar_num("amx_show_activity", (activity = 2));
	}
	
	static message[192], temp[192];
	vformat(message, sizeof(message) - 1, message_fmt, 3);
	
	for( new client = 1; client <= g_max_clients; client++ )
	{
		if( !is_user_connected(client) ) continue;
		
		switch( is_user_admin(client) ? g_admin_activity[activity] : g_normal_activity[activity] )
		{
			case ACTIVITY_NONE:
			{
				
			}
			case ACTIVITY_HIDE:
			{
				copy(temp, sizeof(temp) - 1, message);
				replace(temp, sizeof(temp) - 1, "$name", "ADMIN");
				
				message_begin(MSG_ONE_UNRELIABLE, g_msgid_SayText, _, client);
				write_byte(client);
				write_string(temp);
				message_end();
			}
			case ACTIVITY_SHOW:
			{
				copy(temp, sizeof(temp) - 1, message);
				replace(temp, sizeof(temp) - 1, "$name", admin_name);
				
				message_begin(MSG_ONE_UNRELIABLE, g_msgid_SayText, _, client);
				write_byte(client);
				write_string(temp);
				message_end();
			}
		}
	}
}


stock GetBanTime(const bantime, length[], len)
{
	new minutes = bantime;
	new hours = 0;
	new days = 0;
	
	while( minutes >= 60 )
	{
		minutes -= 60;
		hours++;
	}
	
	while( hours >= 24 )
	{
		hours -= 24;
		days++;
	}
	
	new bool:add_before;
	if( minutes )
	{
		formatex(length, len, "%i minute%s", minutes, minutes == 1 ? "" : "s");
		
		add_before = true;
	}
	if( hours )
	{
		if( add_before )
		{
			format(length, len, "%i hour%s, %s", hours, hours == 1 ? "" : "s", length);
		}
		else
		{
			formatex(length, len, "%i hour%s", hours, hours == 1 ? "" : "s");
			
			add_before = true;
		}
	}
	if( days )
	{
		if( add_before )
		{
			format(length, len, "%i day%s, %s", days, days == 1 ? "" : "s", length);
		}
		else
		{
			formatex(length, len, "%i day%s", days, days == 1 ? "" : "s");
			
			add_before = true;
		}
	}
	if( !add_before )
	{
		// minutes, hours, and days = 0
		// assume permanent ban
		copy(length, len, "Permanent Ban");
	}
}

stock check_levelcmd( id , target, any:... ) 
{
	if (id < 1 || target < 1)
		return -1
	new outputcmd[64];
	read_args(outputcmd, 63);
	new nflagsid = nCleanFlags(id);		
	new nflagstarget = nCleanFlags(target);
	if (read_flags("biw")== nflagstarget)
	{
		nflagsid = nflagsid + read_flags("w")
	}
	if (read_flags("bit")== nflagstarget)
	{
		nflagsid = nflagsid + read_flags("t")
	}	
	if ((nflagsid < nflagstarget) || (nflagsid == nflagstarget))
	{
		new nume_admin[33], nume_target[33];
		get_user_name(id, nume_admin, sizeof(nume_admin) - 1);
		get_user_name(target, nume_target, sizeof(nume_target) - 1);
		console_print(id, "[AMXX_CMDCHECK] ERROR : Ai incercat sa aplici comenzi pe un alt admin, actiunea ta a fost memorata !");
		log_amx("[AMXX_CMDCHECK] ERROR : Adminul: ^"%s^" A incercat comanda: ^"%s^" pe Adminul: ^"%s^"", nume_admin, outputcmd, nume_target);
		return 1
	}
	

	return -1
}



stock get_name_safe(id,dest[128],len)
{
	new name[128]
	get_user_name(id,name,127)
	return get_user_name_safe(name,dest,len)
}

//#pragma ctrlchar '\'

stock get_user_name_safe(const source[128],dest[128],len)
{
	copy(dest, len, source);
	new bool:detectedchars = false
	
	#pragma ctrlchar '\'
	if (containi(dest,"^")!=-1 || containi(dest,"'")!=-1)
	{
		replace_all(dest,sizeof(dest)-1,"'","");
		replace_all(dest,sizeof(dest)-1,"^","");
		replace_all(dest,sizeof(dest)-1,"^^","");
		detectedchars = true
	}
	#pragma ctrlchar '^'
	
	for( new f = 0; f < sizeof(special1)-1; f++)
	{
		if (containi(dest,special1[f])!=-1)
		{
			replace_all( dest, sizeof(dest)-1, special1[f], "")
			detectedchars = true
		}					
	}
	for( new f = 0; f < sizeof(special2)-1; f++)
	{
		if (containi(dest,special2[f])!=-1)
		{
			replace_all( dest, sizeof(dest)-1, special2[f], "")	
			detectedchars = true			
		}		
	}
		
	for( new f = 0; f < sizeof(special3)-1; f++)
	{
		
		if (containi(dest,special3[f])!=-1)
		{
			replace_all( dest, sizeof(dest)-1, special3[f], "")
			detectedchars = true			
		}	
	}
	if (detectedchars == true)		
		return 1
	else
		return -1
}

// #pragma ctrlchar '^'
// spaces in Name remvove function

stock name_clspaces(id,dest[128],len)
{
	new name[128]
	get_user_name(id,name,127)
	return get_name_nospaces(name,dest,len)
}


stock get_name_nospaces(const source[128],dest[128],len)
{
	//new name[128]
	//get_user_name(id,name,127)
	copy(dest, len, source);
	
	//client_print(0, print_console, "[OFFICIAL] 1 dest este : %s", dest)
	//client_print(0, print_console, "[OFFICIAL] 1 source este : %s", source)
	
	new bool:detectedspaces = false
	//new sizedest=strlen(dest)
	new beforespace[128]
	new afterspace[128]
	new rezultz[128]
	for( new i = 0; i < sizeof(dest)-1; i++)
	{
		if(isspace(dest[i]))
		{
			argbreak(dest, beforespace, i, afterspace, 127)	
			formatex(rezultz, sizeof(rezultz)-1,"%s%s", beforespace[0],afterspace[0])
			copy(dest, sizeof(dest)-1, rezultz);			
			//client_print(0, print_console, "[OFFICIAL] Copiez argbreak dest i-1 adica  beforespace : %s", beforespace)
			//client_print(0, print_console, "[OFFICIAL] Copiez argbreak dest i+1 adica  afterspace : %s", afterspace)
			//client_print(0, print_console, "[OFFICIAL] La caracterul %d am gasit un spatiu ", i)	
			//sizedest=strlen(dest)
			detectedspaces = true		
		}
	}
	copy(dest, sizeof(dest)-1, rezultz);
	if (detectedspaces == true)		
		return 1	
	return -1
}


stock chat_cvar(const id, const input[], any:...)
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