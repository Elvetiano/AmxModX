#include <amxmodx>
#include <amxmisc>

#define ACCESS 			ADMIN_KICK
#define WORDS			64
#define SWEAR_GAGMINUTES	3
#define SHOW

new const tag[] = "[Gag]";
new const g_FileName[] = "gag_words.ini";

new 
bool:g_Gaged[ 33 ], g_GagTime[ 33 ],
bool:g_SwearGag[ 33 ], bool:g_CmdGag[ 33 ],
bool:g_NameChanged[33];

new g_reason[ 32 ], g_admin[ 32 ], g_name[ 33 ][ 32 ];

new g_WordsFile[ 128 ];
new g_Words[ WORDS ][ 32 ], g_Count, g_Len;

new point, g_msgsaytext;
new toggle_tag

public plugin_init() 
{
	register_plugin("Advance Gag", "2.2", "anakin_cstrike/ update -B1ng0-")
	
	register_concmd( "amx_gag", "gag_cmd", ACCESS,"- <nume> <minute> <motiv> - Da gag jucatorului" );
	register_concmd( "amx_ungag", "ungag_cmd", ACCESS, "- <nume> - Scoate gagul" );
	register_clcmd( "say", "check" );
	register_clcmd( "say_team", "check" );
	
	toggle_tag = register_cvar( "gag_tag", "0" );
	point = get_cvar_pointer( "amx_show_activity" );
	g_msgsaytext = get_user_msgid( "SayText" );
	
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

public client_putinserver(id)
{  	
	 g_Gaged[ id ] = false;
	 g_SwearGag[ id ] = false;	
}

public gag_cmd( id, level, cid )
{
	if( !cmd_access( id, level, cid, 4 ) )
		return PLUGIN_HANDLED;  	
		
	new arg[ 32 ], arg2[ 6 ], reason[ 32 ];
	new name[ 32 ], namet[ 32 ];
	new minutes;
	
  	read_argv(1, arg, 31)

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
		console_print( id, "Jucatorul are deja gag!" );
		return PLUGIN_HANDLED;
	}
	
	get_user_name( target, namet, 31 );
	copy( g_name[ target ], 31, namet );
	
	g_CmdGag[ target ] = true;
	g_Gaged[target] = true;
	g_GagTime[ target ] = minutes;
	
	print( 0, "^x03[RangForT]^x01 ^x04%s:^x01 Gag jucatorului ^x04 %s^x01 pentru^x04 [%d]^x01 minut(e). Motiv:^x04 %s",get_pcvar_num( point ) == 2 ? name : "", namet, minutes, reason );
	
	if( get_pcvar_num( toggle_tag ) == 1 )
	{
		new Buffer[ 64 ];
		formatex( Buffer, sizeof Buffer - 1, "%s %s", tag, namet );
		
		g_NameChanged[ target ] = true;
		client_cmd( target, "name ^"%s^"",Buffer );
	}
	
	set_task( 60.0, "count", target + 123, _, _, "b" );
	
	return PLUGIN_HANDLED;
}

public ungag_cmd( id,level, cid )
{
	if( !cmd_access( id, level, cid, 2 ) )
		return PLUGIN_HANDLED;
		
	new arg[ 32 ], reason[ 32 ], name[ 32 ];
	read_argv( 1, arg, sizeof arg - 1 );
	read_argv( 2, reason, sizeof reason - 1 );
	get_user_name( id, name, sizeof name - 1 );
	remove_quotes( reason );
	
	new target = cmd_target( id, arg, 11 );
	if( !target )
		return PLUGIN_HANDLED;
	new namet[ 32 ];
	get_user_name( target, namet, sizeof namet - 1 );
	
	if( !g_Gaged[ target ] )
	{
		console_print( id, "Jucatorul %s nu are gag.", namet );
		return PLUGIN_HANDLED;
	}
	
	g_Gaged[ target ] = false;
	g_SwearGag[ target ] = false;
	
	if( g_NameChanged[ target ] )
		client_cmd( target, "name ^"%s^"", g_name[ target ] );
		
	g_NameChanged[ target ] = false;
	
	remove_task( target + 123 );
	
	print( 0, "^x03[RangForT]^x01 ^x04%s:^x01 UnGag jucatorului^x04 %s",get_pcvar_num( point ) == 2 ? name : "", namet );
	
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
		
		print( index, "^x01Ai primit ^x04UnGag^x01 cu succes!" );
		g_Gaged[ index ] = false;
	
		if( g_NameChanged[ index ] )
			client_cmd( index, "name ^"%s^"", g_name[ index ] );
		
		return 0;
	}
	
	return 1;
}

public check( id )
{
	new said[ 192 ];
	read_args( said, sizeof said - 1 );
	
	if( !strlen( said ) )
		return PLUGIN_CONTINUE;
		
	if( g_Gaged[ id ] )
	{
		if( g_CmdGag[ id ] )
		{
			print( id,"Ai primit Gag de la: %s. Au mai ramas %d minut(e)" ,g_admin, g_GagTime[ id ], g_GagTime[ id ] == 1 ? "" : "s" );
			print( id,"Motivul Gagului: %s", g_reason );
			
			return PLUGIN_HANDLED;
		
		} else if( g_SwearGag[ id ] ) {
          		print( id, "Ai gag pentru limbaj vulgar sau reclama.")
			print( id, "Au mai ramas %d minut(e)",  g_GagTime[ id ], g_GagTime[ id ] == 1 ? "" : "s" );
			return PLUGIN_HANDLED;
		}
	} else {
		
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

public client_disconnect(id) 
{ 
	if(g_Gaged[id]) 
	{
	 new Nick[32],Authid[35],usrip[32]
	 get_user_name(id,Nick,31)
	 get_user_ip(id,usrip,31);
	 get_user_authid(id,Authid,34) 
	 print(0, "^x04[RangForT]^x01 Jucatorul cu gag^x04 %s^x01 [Ip:^x04 %s^x04] a parasit serverul.",Nick,usrip)		
				
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
/* AMXX-Studio Notes - DO NOT MODIFY BELOW HERE
*{\\ rtf1\\ ansi\\ deff0{\\ fonttbl{\\ f0\\ fnil Tahoma;}}\n\\ viewkind4\\ uc1\\ pard\\ lang1049\\ f0\\ fs16 \n\\ par }
*/
