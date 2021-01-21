/* AMX Mod script. 
* 
* (c) 2002-2003, OLO 
* modified by shadow
* This file is provided as is (no warranties). 
* 
* Players with immunity won't be checked 
*/ 

#include <amxmodx> 
#include <amxmisc>

new g_Ping[33]
new g_Samples[33]

public plugin_init()
{
  register_plugin("High Ping Kicker (WON)","0.16.3","OLO/shadow/UNU")
  register_concmd("amx_hpk","cmdHpk",ADMIN_KICK,"- configures high_ping_kicker plugin")
  register_concmd("amx_redirectall","redirect_all",ADMIN_RCON,"- Redirectioneaza pe alt server")
  register_cvar("amx_hpk_ping","300")
  register_cvar("amx_hpk_check","12")
  register_cvar("amx_hpk_tests","5")
  register_cvar("amx_hpk_delay","60")
  register_cvar("amx_hpk_redirect", "0")
  register_cvar("amx_hpk_redirect_address", "5.254.86.222")
  
  if ( get_cvar_num( "amx_hpk_check" ) < 5 ) set_cvar_num( "amx_hpk_check" , 5 )
  if ( get_cvar_num( "amx_hpk_tests" ) < 3 ) set_cvar_num( "amx_hpk_tests" , 3 )
}

public client_disconnected(id) 
  remove_task( id )

public client_putinserver(id) 
{    
  g_Ping[id] = 0 
  g_Samples[id] = 0

  if ( !is_user_bot(id) ) 
  {
    new param[1]
    param[0] = id 
    set_task( 10.0 , "showWarn" , id , param , 1 )
    
    if (get_cvar_num("amx_hpk_tests") != 0) {
	    set_task( float(get_cvar_num("amx_hpk_delay")), "taskSetting", id, param , 1)
    }
    else {	    
    	set_task( float(get_cvar_num( "amx_hpk_tests" )) , "checkPing" , id , param , 1 , "b" )
	}
	
  }
} 

public showWarn(param[])
{
	if (get_cvar_num( "amx_hpk_redirect" ) != 0)
	{
		client_print( param[0] ,print_chat,"* Players with ping higher than %d will be redirected!", get_cvar_num( "amx_hpk_ping" ) )
	}
	else
	{
		client_print( param[0] ,print_chat,"* Players with ping higher than %d will be kicked!", get_cvar_num( "amx_hpk_ping" ) )
	}
}		

public taskSetting(param[]) {
	new name[32]
	get_user_name(param[0],name,31)
	set_task( float(get_cvar_num( "amx_hpk_tests" )) , "checkPing" , param[0] , param , 1 , "b" )
}

kickPlayer( id ) 
{ 
	new name[32],authid[32],sFullAddress[64]
	get_user_name(id,name,31)
	get_user_authid(id,authid,31)		
	get_cvar_string("amx_hpk_redirect_address",sFullAddress,63) 
 	if (get_cvar_num( "amx_hpk_redirect" ) != 0)
	{
		client_print(0,print_chat,"** Player %s redirected due to high ping",name)
		client_cmd(id,"echo ^"** Sorry but you have too high ping, try later...^";")
		client_cmd(id, "wait;wait;wait;wait;wait;^"connect^" %s", sFullAddress)
		server_cmd("amx_exec3 %s ^"connect %s^"", name,sFullAddress);
		server_cmd("amx_exec3 %s ^"Connect %s^"", name,sFullAddress);
		remove_task(id)
		log_amx("HighpingRedirect: ^"%s<%d><%s>^" was redirected due to high ping (Average Ping ^"%d^")", name,get_user_userid(id),authid,(g_Ping[id] / g_Samples[id]))
	}
	else
	{
		client_print(0,print_chat,"** Player %s disconnected due to high ping",name)
		client_cmd(id,"echo ^"** Sorry but you have too high ping, try later...^";disconnect")
		remove_task(id)
		log_amx("Highpingkick: ^"%s<%d><%s>^" was kicked due highping (Average Ping ^"%d^")",  name,get_user_userid(id),authid,(g_Ping[id] / g_Samples[id]))
		

	}
} 


public redirect_all(id,level,cid)
{
	if (!cmd_access(id,level,cid,1))
		return PLUGIN_HANDLED
	new count = 1, players[32]
	new name[32],authid[32],sFullAddress[64]	
	get_cvar_string("amx_hpk_redirect_address",sFullAddress,63)
	get_players(players, count, "ch")
	for (new i = 0; i < count; i++)
	{
		get_user_name(players[i],name,31)
		get_user_authid(players[i],authid,31)
		if (is_user_connected(players[i]))
		{
			//client_print(0,print_chat,"** Player %s redirected due to high ping",name)
			log_amx("HighpingRedirect: ^"%s<%d><%s>^" was redirected With command", name,get_user_userid(players[i]),authid)
			client_cmd(players[i],"echo ^"** Sorry redirecting you to our new server, Connecting 5.254.86.222:27015...^";")
			client_cmd(players[i], "wait;wait;wait;wait;wait;^"connect^" %s", sFullAddress)
			server_cmd("amx_exec3 %s wait;wait;wait;wait;wait;^"connect^" %s", name,sFullAddress);
			server_cmd("amx_exec3 %s wait;wait;wait;wait;wait;^"Connect^" %s", name,sFullAddress);
		}
	}	
	return PLUGIN_HANDLED 
}


public checkPing(param[]) 
{ 
  new id = param[ 0 ] 

  if ( get_user_flags(id) & ADMIN_IMMUNITY ) return

  new p, l 

  get_user_ping( id , p , l ) 

  g_Ping[ id ] += p
  ++g_Samples[ id ]

  if ( (g_Samples[ id ] > get_cvar_num( "amx_hpk_tests" )) && (g_Ping[id] / g_Samples[id] > get_cvar_num( "amx_hpk_ping" ))  )    
    kickPlayer(id) 
}

  
public cmdHpk(id,level,cid){
  if (!cmd_access(id,level,cid,1))
    return PLUGIN_HANDLED
    
  new ping[5]
  new check_arr[5]
  new tests_arr[5]
  new delay_arr[5]
  read_argv(1,ping,4)
  read_argv(2,check_arr,4)
  read_argv(3,tests_arr,4)
  read_argv(4,delay_arr,4)
  
  new check = str_to_num(check_arr)
  new tests = str_to_num(tests_arr)
  new delay = str_to_num(delay_arr)
  
  
  if ( check < 5 ) check = 5
  if ( tests < 3 ) tests = 3
  

  if (read_argc() > 1){
    set_cvar_string("amx_hpk_ping",ping)
  }
  if (read_argc() > 2) {
	set_cvar_num("amx_hpk_check",check)
  }
  if (read_argc() > 3) {
	set_cvar_num("amx_hpk_tests",tests)
  }
  if (read_argc() > 4) {
	  set_cvar_num("amx_hpk_delay",delay)
 }

  console_print(id,"Syntax: amx_hpk <ping to get kicked> <checks before kicks> <time between checks> <delay before first check in sec.>")
  console_print(id,"Current High_Ping_Kicker Settings:")
  console_print(id,"Maxping: %d  Time between checks: %d Checkcount: %d Delay: %d",get_cvar_num("amx_hpk_ping"),get_cvar_num("amx_hpk_check"),get_cvar_num("amx_hpk_tests"),get_cvar_num("amx_hpk_delay"))
  return PLUGIN_HANDLED    
}