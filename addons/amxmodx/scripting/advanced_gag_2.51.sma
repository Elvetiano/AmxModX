#include <amxmodx>
#include <amxmisc>
#include <regex>

#define ACCESSFLAG 			ADMIN_RESERVATION
#define WORDS			1024
#define SWEAR_GAGMINUTES	3
//#define CONNECT_NONUMBERS	120 //secunde
#define SHOW

//new Regex:g_IP_pattern;
//new g_regex_return;


//#define REGEX_IP_PATTERN "\b(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\b"
//#define IsValidIP(%1) (regex_match_c(%1, g_IP_pattern, g_regex_return) > 0)



new const tag[] = "[Gag]"
new const g_FileName[] = "gag_words.ini"
new bool:g_Gaged[ 33 ], g_GagTime[ 33 ], bool:g_SwearGag[ 33 ], bool:g_CmdGag[ 33 ], bool:g_NameChanged[33]
new g_reason[ 32 ], g_admin[ 32 ], g_name[ 33 ][ 32 ]
new g_WordsFile[ 128 ]
new g_Words[ WORDS ][ 32 ], g_Count , g_Len
new point, g_msgsaytext, cvar_oldgag
new toggle_tag 
new cvar_maxwarns  
new chatcheck 
new chours[44], cmins[44],csec[44], warned[44];

new const special1 [][] ={ "{","}","|",">","<","~","`",".",";","'","[","]","$","%","&","*","_","+","#","$","%","&","'","*","+",";","<",">","[","\\","]","_","`","{","|","}","~","Δ","€","‚","ƒ","„","…","†","‡","ˆ","‰","Š","‹","Œ","Ž","‘","’","“","à","á","â","ã"} 
new const special2 [][] = {"”","•","–","—","˜","™","š","›","œ","ž","Ÿ","á","¡","¢","£","¤","¥","¦","§","¨","©","ª","«","¬","¡","®","¯","°","±","²","³","´","µ","¶","·","¸","¹","º","»","¼","½","¾","¿","À","Á","Â","Ã","Ä","Å","Æ","Ç","È","É","Ê","Ë","Ì","Í","Î","Ï","Ð","Ñ","Ò","Ó","Ô","Õ","Ö","×","Ø","Ù","Ú","Û","Ü","Ý","Þ","ß"}
new const special3 [][] = {"│","┤","╡","╢","╖","╕","╣","║","╗","╝","╜","╛","┐","└","┴","┬","├","─","┼","╞","╟","╚","╔","╩","╦","╠","═","╬","╧","╨","╤","╥","╙","╘","╒","╓","╫","╪","┘","┌","█","▄","▌","▐","▀","α","ß","Γ","π","Σ","σ","µ","τ","Φ","Θ","Ω","δ","∞","φ","ε","∩","≡","±","≥","≤","⌠","⌡","÷","≈","°","∙","·","√","ⁿ","²","■"," "}

public plugin_init() 
{
	register_plugin("Advance Gag", "2.51", "UNU/anakin/-B1ng0-")
	register_concmd( "amx_gag", "gag_cmd", ACCESSFLAG,"- <nume> <minute> <motiv> - Gag a player" );
	register_concmd( "amx_ungag", "ungag_cmd", ACCESSFLAG, "- <nume> - remove gag" );
	register_clcmd( "say", "check" );
	register_clcmd( "say_team", "check" );
	cvar_maxwarns = register_cvar( "amx_maxwarns", "3" );
	cvar_oldgag = register_cvar( "amx_antireclama", "1" );
	toggle_tag = register_cvar( "gag_tag", "0" );
	chatcheck = register_cvar( "amx_connect_timecheck", "60" );
	point = get_cvar_pointer( "amx_show_activity" );
	g_msgsaytext = get_user_msgid( "SayText" );
	//register_event("TextMsg", "rr_resettimer", "a", "2=#Game_will_restart_in");
	//register_event( "TextMsg", "rr_resettimer", "a", "2=#Game_Commencing", "2=#Game_will_restart_in" ) 
	//register_event("TextMsg","rr_resettimer","a","2&#Game_w") // Resets timers when restarts round Game_will_restart_in
	register_event("TextMsg","rr_resettimer","a","2&#Game_C")
	register_concmd( "amx_resetgag", "reset_gag", ACCESSFLAG, "Resets gag params and ungags everyone" );
	//new error[2];
	//g_IP_pattern = regex_compile(REGEX_IP_PATTERN, g_regex_return, error, sizeof(error) - 1);
}


public plugin_cfg()
{
	static dir[ 64 ];
	get_localinfo( "amxx_configsdir", dir, 63 );
	formatex( g_WordsFile , 127 , "%s/%s" , dir, g_FileName );
	
	if( !file_exists( g_WordsFile ) )
		write_file( g_WordsFile, "[Gag Words]", -1 );
		
	new Len;
	
	while( g_Count < WORDS && read_file( g_WordsFile, g_Count ,g_Words[ g_Count ][ 1 ], 30, Len ) )
	{
		g_Words[ g_Count ][ 0 ] = Len;
		g_Count++;
	}
}

public reset_gag( id, level, cid )
{
	if( !cmd_access( id, level, cid, 1 ) )
		return PLUGIN_HANDLED;  
	rr_resettimer();
	return PLUGIN_CONTINUE;
}

public rr_resettimer()
{
	new players[ 32 ], noob, numx;
	get_players( players, numx, "i" );
	for(new mj = 0; mj < numx; ++mj)
	{
		noob = players[ mj ]
		get_time("%H", chours[noob], 43);
		get_time("%M", cmins[noob], 43);
		get_time("%S", csec[noob], 43);
		g_NameChanged[ noob ] = false;
		g_Gaged[ noob ]  = false;
		g_SwearGag[ noob ] = false;
		warned[noob] = 0;
		g_CmdGag[ noob ] = false;	
		g_GagTime[ noob ] = 0;
		crx_ungag(noob);
		remove_task( noob+123 );
	}
	
	return PLUGIN_CONTINUE;
}

public gag_cmd( id, level, cid )
{
	if( !cmd_access( id, level, cid, 4 ) )
		return PLUGIN_HANDLED;  	
		
	new arg[ 32 ], arg2[ 6 ], reason[ 32 ];
	new name[ 32 ], namet[ 32 ];
	new minutes;
	
  	read_argv(1, arg, 31)
	point = get_cvar_pointer( "amx_show_activity" );
  	new player = cmd_target(id, arg, 9)

  	if (!player) 
      	return PLUGIN_HANDLED
	
	read_argv( 1, arg, sizeof arg - 1 );
	read_argv( 2, arg2, sizeof arg2 - 1 );
	read_argv( 3, reason, sizeof reason - 1 );
		
	get_user_name( id, name, 31 );
	
	copy( g_admin, 31, name );
	copy( g_reason, 31, reason );
	remove_quotes( reason );
	
	minutes = str_to_num( arg2 );
	
	new target = cmd_target( id, arg, 10 );
	if( !target)
		return PLUGIN_HANDLED;
		
	if( g_Gaged[ target ] )
	{
		console_print( id, "Player already has gag!" )
		//g_CmdGag[ target ] = false
		//g_Gaged[target] = false
		//remove_task(target + 123)		
		return PLUGIN_HANDLED;
	}
	
	get_user_name( target, namet, 31 );
	copy( g_name[ target ], 31, namet );
	
	g_CmdGag[ target ] = true;
	g_Gaged[target] = true;
	g_GagTime[ target ] = minutes;
	
	//print( 0, "^x04[OFFICIAL] %s:^x01 Gag player^x03 %s^x01 for^x03 [%d]^x01 minute(s). Reason:^x03 %s",get_pcvar_num( point ) == 2 ? name : "", namet, minutes, reason );
	chattoplayers( 0, "!y[!gGAG!y]!team %s:!gGag player !team %s !g for  !y[!team%d!y]!g minute(s). Reason:!team %s",get_pcvar_num( point ) == 2 ? name : "", namet, minutes, reason );
	
	if( get_pcvar_num( toggle_tag ) == 1 )
	{
		new Buffer[ 64 ];
		formatex( Buffer, sizeof Buffer - 1, "%s %s", tag, namet );
		
		g_NameChanged[ target ] = true;
		client_cmd( target, "name ^"%s^"",Buffer );
	}
	
	set_task( 60.0, "count", target + 123, _, _, "b" );
	crx_chatmanagercheck(target);
	return PLUGIN_HANDLED;
}

public ungag_cmd( id,level, cid )
{
	if( !cmd_access( id, level, cid, 2 ) )
		return PLUGIN_HANDLED;
		
	new arg[ 32 ], reason[ 32 ], name[ 32 ];
	read_argv( 1, arg, sizeof arg - 1 );
	read_argv( 2, reason, sizeof reason - 1 );
	point = get_cvar_pointer( "amx_show_activity" );
	get_user_name( id, name, sizeof name - 1 );
	remove_quotes( reason );
	
	new target = cmd_target( id, arg, 11 );
	if( !target )
		return PLUGIN_HANDLED;
	new namet[ 32 ];
	get_user_name( target, namet, sizeof namet - 1 );
	
	if( !g_Gaged[ target ] )
	{
		console_print( id, "Jucatorul %s doesn't have gag.", namet );
		return PLUGIN_HANDLED;
	}
	g_Gaged[ target ] = false;
	g_SwearGag[ target ] = false;
	g_CmdGag[ target ] = false;
	warned[target] = 0;
	
	if( g_NameChanged[ target ] )
		client_cmd( target, "name ^"%s^"", g_name[ target ] );
		
	g_NameChanged[ target ] = false;
	
	remove_task( target + 123 );
	
	//print( 0, "^x04[OFFICIAL] %s:^x01 UnGag player^x03 %s",get_pcvar_num( point ) == 2 ? name : "", namet );
	chattoplayers( 0, "!y[!gGAG!y] !team%s: !gUnGag player !team%s",get_pcvar_num( point ) == 2 ? name : "", namet );
	crx_ungag(target);
	return PLUGIN_HANDLED;
}
	
public count( task )
{
	new index = task - 123;
	if( !is_user_connected( index ) )
		return 0;
		
	g_GagTime[index] -= 1;	
	if( g_GagTime[ index ] <= 0 )
	{
		remove_task( index + 123 );
		
		//print( index, "You've been Ungagged!" );
		chattoplayers( index, "!gYou've been Ungagged!" );
		g_Gaged[ index ] = false;
		g_SwearGag[ index ] = false;
		g_CmdGag[ index ] = false;
		warned[index] = 0;
		crx_ungag(index);
		if( g_NameChanged[ index ] )
			client_cmd( index, "name ^"%s^"", g_name[ index ] );
		
		return 0;
	}
	return 1;
}


public check( id )
{
	new oldmode = get_pcvar_num( cvar_oldgag )
	if (!oldmode)
	{
		checkold(id)
		return PLUGIN_CONTINUE;
	}	
	
	
	new said[ 192 ], worksaid[ 192 ], nume[32],numesecond[32]
	new ConnectTimeCheck = get_pcvar_num( chatcheck )
	read_args( said, sizeof said - 1 );
	if( !strlen( said ) )
		return PLUGIN_CONTINUE;
	remove_quotes(said)
	new spacepos = containi( said, " " )
	new word1[15],restofwords[177]
	new saidlen
	saidlen = strlen( said )	
	new lenw2 = saidlen - spacepos
	new lenw1 = saidlen - lenw2
	new bool:g_Sweared
	new worksaidsecond[192]
	worksaidsecond = said
	new result
	parse(worksaidsecond, word1, lenw1, restofwords, lenw2)

	//new bool:is_ip = bool:(containi(said, ".") != -1) && bool:(containi(said, ":") != -1);

	
	if (((containi( said, "bet" ) != -1  || containi( said, "timeleft" ) != -1  || containi( said, "thetime" ) != -1  || (containi( said, "/" )!= -1) && strlen(word1)>2)) && ( g_CmdGag[ id ] || g_Gaged[id]) && (strlen(restofwords )<1))
	{
		for(new j = 0; j < g_Count; ++j )
		{
			if( (containi( worksaidsecond, g_Words[ j ][ 1 ] ) ) != -1 )
			{
				if (access(id, ACCESSFLAG))
				{
					return PLUGIN_CONTINUE;
				}
				else
				{
					new textsaidfirst[64]
					format(textsaidfirst,charsmax(textsaidfirst),"I have Gag :) Ungag pls!")
					get_user_name( id, numesecond, sizeof numesecond - 1 )
					chattoadmins(0,"!team[GAG] !gJucatorul !y%s !ga primit gag pentru mesajul in chat: !y[ !g%s !y]",numesecond,said)
					replace_all(said, charsmax(said), said, textsaidfirst)
					if (is_user_connected(id))
					{
						message_begin(MSG_ONE_UNRELIABLE, g_msgsaytext, _, id)
						write_byte(id)
						write_string(said)
						message_end()
						
					}
					return PLUGIN_HANDLED;
				}
				
			}
		}
	}	
	
	if( g_Gaged[ id ] )
	{
		crx_chatmanagercheck(id);
		if( g_CmdGag[ id ] )
		{
			//print( id,"You got Gag from: %s. Remains %d minute(s)" ,g_admin, g_GagTime[ id ], g_GagTime[ id ] == 1 ? "" : "s" );
			//print( id,"Gag Reason: %s", g_reason );
			chattoplayers( id, "!gYou got Gag from: !team%s. !gRemains !team%d !gminute(s)" ,g_admin, g_GagTime[ id ], g_GagTime[ id ] == 1 ? "" : "s" );
			//chattoplayers( id, "!gYou've been Ungagged!" );
			
			return PLUGIN_HANDLED;
		
		} else if( g_SwearGag[ id ] ) {
			//print( id, "You have gag for dirty language or advertising. Remains %d minute(s)" ,g_GagTime[ id ], g_GagTime[ id ] == 1 ? "" : "s" );
			chattoplayers( id, "!gYou have gag for dirty language or advertising. Remains !team%d !gminute%s" ,g_GagTime[ id ], g_GagTime[ id ] == 1 ? "" : "s" );
			new gagname[32] 
			get_user_name ( id, gagname, 31)
			//chattoadmins(0, "!gPlayer !team %s !ghas Autogag. UnGAG?-->!yamx_ungag !team %s",gagname,gagname)
			return PLUGIN_HANDLED;
		}
	} 
	else 
	{
		result = timecheck(id)
		// log_amx("[Advanced_Gag] check function result = timecheck(id) = %d", result)
		if (!access(id, ACCESSFLAG))
		{
			if (result < ConnectTimeCheck)
			{
				if ((containi( said, "0") != -1 || containi( said, "1") != -1 || containi( said, "2") != -1|| containi( said, "3") != -1|| containi( said, "4") != -1|| containi( said, "5") != -1|| containi( said, "6") != -1|| containi( said, "7") != -1|| containi( said, "8") != -1|| containi( said, "9") != -1) || containi( said, ".ro") != -1|| containi( said, ".net") != -1|| containi( said, ".com") != -1|| containi( said, "free") != -1) 
				{
					if ((containi( said, "/" )!= -1) && (strlen(word1)>2) && (strlen(restofwords )<1))
					{
						return PLUGIN_CONTINUE
					}
					else
					{
						if (warned[id] < get_pcvar_num(cvar_maxwarns))
						{
							warncheck(id)
						}
					}
					return PLUGIN_HANDLED
				}
				//new chttxt[3],
				new found //, pos;
				for(new i = 0; i < sizeof(special1)-1; i++)
				{
					found = containi(said,special1[i])
					if (found!=-1)
					{
						//format(chttxt,2,"%s",special1[i])
						for(new f = 0; f < sizeof(said)-1; f++)
						{
							replace(said[f], charsmax(said), special1[i], "_" )
						}
						if (warned[id] < get_pcvar_num(cvar_maxwarns))
						{
							warncheck(id)
						}
						return PLUGIN_HANDLED
					}
				}
				for(new i = 0; i < sizeof(special2)-1; i++)
				{
					found = containi(said,special2[i])
					if (found!=-1)
					{
						//format(chttxt,2,"%s",special2[i])
						for(new f = 0; f < sizeof(said)-1; f++)
						{
							replace( said[f], charsmax(said), special2[i], "_" )
						}	
						if (warned[id] < get_pcvar_num(cvar_maxwarns))
						{
							warncheck(id)
						}
						return PLUGIN_HANDLED
					}
				}
				for(new i = 0; i < sizeof(special3)-1; i++)
				{
					found = containi(said,special3[i])
					if (found!=-1)
					{
						//format(chttxt,2,"%s",special3[i])
						for(new f = 0; f < sizeof(said)-1; f++)
						{
							replace( said[f], charsmax(said), special3[i], "_" )
						}
						if (warned[id] < get_pcvar_num(cvar_maxwarns))
						{
							warncheck(id)
						}
						return PLUGIN_HANDLED
					} 
				}
			}
		}
		worksaid = said
		while(replace(worksaid, charsmax(worksaid), " ", "_")){ }
		
		for(new i = 0; i < g_Count; ++i )
		{
			if( (containi( worksaid, g_Words[ i ][ 1 ] ) ) != -1 )
			{
				if (!access(id, ACCESSFLAG))
				{
					if( (containi( g_Words[ i ][ 1 ],"_" ) ) != -1 )
					{
						if (warned[id] < get_pcvar_num(cvar_maxwarns))
						{
							warncheck(id)
						}
					}
					g_Sweared = true
					//client_print ( id, print_chat, "[OFFICIAL] Text %s not allowed, your msg was bloked", g_Words[ i ][ 1 ])
					new textsaid[64]
					//format(textsaid,charsmax(textsaid),"I Got Gag :) for TXT MSG:[ %s ]",g_Words[ i ][ 1 ])
					format(textsaid,charsmax(textsaid),"I have Gag :)")
					get_user_name( id, nume, sizeof nume - 1 )
					chattoadmins(0,"!team[GAG] !gJucatorul !y%s !ga primit gag pentru mesajul in chat: !y[ !g%s !y]",nume,said)
					replace_all(said, charsmax(said), said, textsaid)
				}
				continue;
			}  
		}
		if( g_Sweared )
		{
			new cmd[ 32 ], name[ 32 ];
			
			get_user_name( id, name, sizeof name - 1 );
			read_argv( 0, cmd, sizeof cmd - 1 );
			copy( g_name[ id ], 31, name );
			
			crx_chatmanagercheck(id)
			
			engclient_cmd( id, cmd, said );
			g_Gaged[ id ] = true;
			g_CmdGag[ id ] = false;
			
			if( get_pcvar_num( toggle_tag ) == 1 )
			{
				new Buffer[ 64 ];
				formatex( Buffer, sizeof Buffer - 1, "%s %s", tag, name );
		
				g_NameChanged[ id ] = true;
				client_cmd( id, "name ^"%s^"", Buffer) ;
			}
			
			g_SwearGag[ id ] = true;
			g_GagTime[ id ] = SWEAR_GAGMINUTES;
			
			//print( id, "Ai gag pentru limbaj vulgar sau reclama." );
			//print( id, "You have gag for dirty language or advertising." );
			chattoplayers(id, "!gYou have gag for dirty language or advertising.")
			set_task( 60.0, "count",id+123,_,_,"b");
			return PLUGIN_HANDLED;
		}
	}
	return PLUGIN_CONTINUE;
}
new const g_plugins_Stop[][] = {
	"crx_ranksystem",
	"crx_chatmanager_toggle",
	"crx_chatmanager",
	"ultimate_chat",
	"statsx_shell",
	"statsx"
}
public crx_chatmanagercheck(id)
{
	if(g_Gaged[ id ])
	{
		for (new i = 0; i < sizeof g_plugins_Stop -1; ++i) 
		{
			new pluginname[32],status[2],file[32]
			format(pluginname, sizeof(pluginname)-1,"%s.amxx", g_plugins_Stop[i])
			new exists = find_plugin_byfile ( pluginname, 1)
			if (exists > 0)
			{
				get_plugin(exists, file, charsmax(file), status, 0, status, 0, status, 0, status, 1)
				switch (status[0])
				{
					// "running"
					case 'r': {
						if( callfunc_begin("handle_Gaged",pluginname) == 1 ) 
						{
							callfunc_push_int(id)
							callfunc_push_int(1)
							callfunc_end()
						}
					}
					// "debug"="running"
					case 'd': {
						if( callfunc_begin("handle_Gaged",pluginname) == 1 ) 
						{
							callfunc_push_int(id)
							callfunc_push_int(1)
							callfunc_end()
						}
					}
				}
			}
		}
	}
	
	
	
}

public crx_ungag(id)
{	new const g_plugins_Stop[][] = {
		"crx_ranksystem",
		"crx_chatmanager_toggle",
		"crx_chatmanager",
		"ultimate_chat",
		"statsx_shell",
		"statsx"
	}
	for (new i = 0; i < sizeof g_plugins_Stop - 1; i++) 
	{
		new pluginname[32],status[2],file[32]
		format(pluginname, sizeof(pluginname) - 1,"%s.amxx", g_plugins_Stop[i])
		new exists = find_plugin_byfile ( pluginname, 1)
		if (exists > 0)
		{
			get_plugin(exists, file, charsmax(file), status, 0, status, 0, status, 0, status, 1)
			switch (status[0])
			{
				// "running"
				case 'r': {
					if( callfunc_begin("handle_Gaged",pluginname) == 1 ) 
					{
						callfunc_push_int(id)
						callfunc_push_int(2)
						callfunc_end()
					}
				}
				// "debug"="running"
				case 'd': {
					if( callfunc_begin("handle_Gaged",pluginname) == 1 ) 
					{
						callfunc_push_int(id)
						callfunc_push_int(2)
						callfunc_end()
					}
				}
			}
		}
	}
}		



public checkold( id )
{
	new said[ 192 ];
	read_args( said, sizeof said - 1 );
	
	if( !strlen( said ) )
		return PLUGIN_CONTINUE;
		
	if( g_Gaged[ id ] )
	{
		crx_chatmanagercheck(id)
		if( g_CmdGag[ id ] )
		{
			print( id,"Ai primit gag de la: %s. Au mai ramas %d minut(e)" ,g_admin, g_GagTime[ id ], g_GagTime[ id ] == 1 ? "" : "s" );
			print( id,"Motivul Gagului: %s", g_reason );
			
			return PLUGIN_HANDLED;
		
		} 
		else if( g_SwearGag[ id ] )
		{
			print( id, "Ai gag pentru limbaj vulgar sau reclama.")
			//print( id, "Au mai ramas %d minut(e)",  g_GagTime[ id ], g_GagTime[ id ] == 1 ? "" : "s" );
			return PLUGIN_HANDLED;
		}
	} else 
	{
		new bool:g_Sweared, i, pos;
		for( i = 0; i < g_Count; ++i )
		{
			if( ( pos = containi( said, g_Words[ i ][ 1 ] ) ) != -1 )
			{
				g_Len = g_Words[ i ][ 0 ];
				
				while( g_Len-- )
					said[ pos++ ] = '*';
					
				g_Sweared = true;
				
				continue;
			}
		}
		
		if( g_Sweared )
		{
			new cmd[ 32 ], name[ 32 ];
			crx_chatmanagercheck(id)
			
			get_user_name( id, name, sizeof name - 1 );
			read_argv( 0, cmd, sizeof cmd - 1 );
			copy( g_name[ id ], 31, name );
			
			engclient_cmd( id, cmd, said );
			g_Gaged[ id ] = true;
			g_CmdGag[ id ] = false;
			
			if( get_pcvar_num( toggle_tag ) == 1 )
			{
				new Buffer[ 64 ];
				formatex( Buffer, sizeof Buffer - 1, "%s %s", tag, name );
		
				g_NameChanged[ id ] = true;
				client_cmd( id, "name ^"%s^"", Buffer) ;
			}
			
			g_SwearGag[ id ] = true;
			g_GagTime[ id ] = SWEAR_GAGMINUTES;
			
			print( id, "Ai gag pentru limbaj vulgar sau reclama." );
		
			set_task( 60.0, "count",id+123,_,_,"b");
			
			return PLUGIN_HANDLED;
		}
	}
	
	return PLUGIN_CONTINUE;
}















public warncheck(id)
{
	new said[ 192 ],authid[32], logname[33], tresult, cvarwarns, name[32], address[32], players[32], Playerindex, num
	new WarnTimeCheck = get_pcvar_num( chatcheck )
	read_args( said, sizeof said - 1 )
	tresult = timecheck(id)
	//if (tresult < WarnTimeCheck)
	if (((WarnTimeCheck - tresult) > 0) && ((WarnTimeCheck - tresult) < 600)) 
	{
		warned[id]++
		cvarwarns = get_pcvar_num(cvar_maxwarns)
		chattoplayers( id, "!g[!teamWARNING!!g] !y[!g%d!y] !g !y[!g%d!y]  !gOnly simple letters allowed in the first !y%d !gsec.",warned[id],cvarwarns,WarnTimeCheck)
		chattoplayers( id, "!gYou must wait !y%d !gsec.",(WarnTimeCheck - tresult))
		//print( id, "[OFFICIAL] Chat RESTRICTED %d sec before you can use the full chat, You must wait %d sec.",WarnTimeCheck, (WarnTimeCheck - tresult))
		//print( id, "[OFFICIAL] Use only simple text.Don't Advertise !")
		//print( id, "[WARNING!]-----------------[ %d ] / [ %d ]-----------------------[WARNING!] ",warned[id],cvarwarns)
		if(warned[id] >= cvarwarns && is_user_connected(id))
		{
		//jucatorul va primi kick in 5 secunde			
			get_players( players, num, "ch" )
			get_user_ip(id, address, 31, 1)
			get_user_name ( id, name, 31)
			get_user_authid(id, authid, 31)
			for(new jk = 0; jk < num; jk++ )
			{
				Playerindex = players[ jk ]
				if (access(Playerindex, ACCESSFLAG))
				{
					client_print ( Playerindex, print_chat, "[BAN] Banned %s MAXIMUM WARNINGS --- CHAT MSG:(%s)", name, said)
				}
			}
			Banlocal(id)
			//server_cmd("kick #%d %s",get_user_userid(id),"MAXIMUM WARNINGS")
			format_time(logname, sizeof(logname) - 1, "%m%d%Y");
			format(logname,sizeof(logname) - 1,"Banned_%s.log",logname)					
			log_to_file(logname,"Banned: %s<#%d><^"%s^"><IP:^"%s^"> Maximum warnings CHAT MSG: (%s )",name, get_user_userid(id),authid,address,said )
			warned[id] = 0
		}		
	}
}


public Banlocal(id)
{
	new addip[32]
	get_user_ip(id, addip, 31, 1)
	//new str[50]
	//format(str,sizeof(str) - 1,"%s 0 BOT",name)			
	//TO DO make call from  callfunc_begin
	server_cmd("amx_banip #%d 4320 %s",get_user_userid(id),"MAXIMUM_WARNINGS")
	server_cmd("addip 1 %s",addip[0])
}  

public timecheck(id)
{
	new nhour[44],nmin[44],nsec[44] //, date[33]
	//new maxtimecvar = get_pcvar_num( chatcheck )
	get_time("%H", nhour[id], 43)
	get_time("%M", nmin[id], 43)
	get_time("%S", nsec[id], 43)
	//get_time("%m/%d/%Y",date,32)
	new numhrs = str_to_num(nhour[id])
	new nummins = str_to_num(nmin[id])
	new numsec = str_to_num(nsec[id])
	new idconhour = str_to_num(chours[id])
	new idconmin = str_to_num(cmins[id])
	new idconsec = str_to_num(csec[id])
	new resultx = (((numhrs * 3600) + (nummins * 60) + numsec) - ((idconhour * 3600) + (idconmin * 60) + idconsec))
	/*              currenttimecheck                           -                        connect time
	exemplu 1 ***********************************************************************************************
	                   13:08:30                                                    13:08:05
	                   46800 + 480 + 30                                           46800 + 480 + 5
	                    47310                        -                             47285 = 25 secunde	
	exemplu 2 ***********************************************************************************************
	                   13:10:06                                                    13:08:05					   
					   46800+600+6                                                 46800+ 480+5
	                     47406                     -                                 47285 = 121 secunde
	exemplu 3 ***********************************************************************************************
	                  13:12:06                                                     13:08:05
	                    46800+ 720+ 6                                              46800+ 480+5
						  47526                  -                                 47285 = 241 secunde
	
	
	
	connect time 18:19:10
	64800 + 1140 + 10 = 65950
	
	currenttimecheck 18:21:15
	64800 + 1260 + 15 = 66075	
	
	*/
	/*
	if (resultx > 43200) //Daca apare errorare cu timpul verificam daca este mai mare de 12 ore timpul
	{
		chours[id]= numhrs
		cmins[id] = nummins
		csec[id] = numsec
	}
	else
		return resultx;
	return maxtimecvar;
	*/
	return resultx;
}

public client_connect(id) 
{
		remove_task( id+123 )
		get_time("%H", chours[id], 43)
		get_time("%M", cmins[id], 43)
		get_time("%S", csec[id], 43)
		g_NameChanged[ id ] = false;
		g_Gaged[ id ]  = false;
		g_SwearGag[ id ] = false;
		warned[ id ] = 0;
		g_CmdGag[ id ] = false;	
		g_GagTime[ id ] = 0;		
		crx_ungag(id);
	
}
public client_putinserver( id )
{
		remove_task( id+123 )
		//get_time("%H", chours[id], 43)
		//get_time("%M", cmins[id], 43)
		//get_time("%S", csec[id], 43)
		g_NameChanged[ id ] = false;
		g_Gaged[ id ]  = false;
		g_SwearGag[ id ] = false;
		warned[ id ] = 0;
		g_CmdGag[ id ] = false;	
		g_GagTime[ id ] = 0;
		crx_ungag(id);
	
}

public client_disconnected(id) 
{ 
	if(g_Gaged[id]) 
	{
		//new Nick[32],Authid[35],usrip[32]
		//get_user_name(id,Nick,31)
		//get_user_ip(id,usrip,31);
		//get_user_authid(id,Authid,34) 
		//chattoplayers(0, "!y[!gOFFICIAL!y] !gPlayer with gag!team %s!y[!gIP:!team %s!y]!g has left the server.",Nick,usrip)

		remove_task( id+123 )
	}
	
	chours[id] = 0;
	cmins[id] = 0;
	csec[id] = 0;
	
	g_NameChanged[ id ] = false;
	g_Gaged[ id ] = false;
	g_SwearGag[ id ] = false
	warned[id] = 0;
	g_CmdGag[ id ] = false;	
	g_GagTime[ id ] = 0;
}

stock chattoadmins(const id, const input[], any:...)
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
				if (access(players[i], ACCESSFLAG))
				{
					message_begin(MSG_ONE, g_msgsaytext, _, players[i])
					write_byte(players[i])
					write_string(msg)
					message_end()
				}
				
			}
		}
	}
}
stock chattoplayers(const id, const input[], any:...)
{
	new count = 1, players[32]
	static somemsg[191]
	vformat(somemsg, 190, input, 3)
	replace_all(somemsg, 190, "!g", "^4")
	replace_all(somemsg, 190, "!y", "^1")
	replace_all(somemsg, 190, "!team", "^3")
	replace_all(somemsg, 190, "!team2", "^0")
	if (id) players[0] = id; else get_players(players, count, "ch")
	{
		for (new i = 0; i < count; i++)
		{
			if (is_user_connected(players[i]))
			{
				message_begin(MSG_ONE, g_msgsaytext, _, players[i])
				write_byte(players[i])
				write_string(somemsg)
				message_end()
			}
		}
	}
}


print( id, const message[ ], { Float, Sql, Result, _ }:... )
{
	new Buffer[ 128 ], Buffer2[ 128 ];
	
	formatex( Buffer2, sizeof Buffer2 - 1, "%s", message );
	vformat( Buffer, sizeof Buffer - 1, Buffer2, 3 );
	
	if( id )
	{
		message_begin( MSG_ONE, g_msgsaytext, _,id );
		write_byte( id );
		write_string( Buffer) ;
		message_end();
	
	} else {
		new players[ 32 ], index, num, i;
		get_players( players, num, "ch" );
		
		for( i = 0; i < num; i++ )
		{
			index = players[ i ];
			if( !is_user_connected( index ) ) continue;
			
			message_begin( MSG_ONE, g_msgsaytext, _, index );
			write_byte( index );
			write_string( Buffer );
			message_end();
		}
	}
}