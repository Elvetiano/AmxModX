#if defined _rconpass_included
    #endinput
#endif
#define _rconpass_included

#include <amxmodx>
#include <amxmisc>
#include <sqlx>


// Address Protection
#define ADDRESS_PROTECTION "5.254.86.222:27015"

// DNS Protection
#define DNS_PROTECTION "OFFICIAL.INDUNGI.RO"
/*
new simbols[][] = 
{
	"!",
	"@",
	"$"
}
*/

new FixedPasswrd[10]
new GotPassword[10]
//new idnrl 

public randompass()
{
	new password[10]//,simb1[2],simb2[2]
	// Address protection
	static address[32], name[32]
	get_cvar_string("net_address", address, charsmax(address))    
	get_cvar_string("hostname", name, charsmax(name))
	
	//copy(simb1, 2, simbols[random_num(0, sizeof(simbols)-1)])
	//copy(simb2, 2, simbols[random_num(0, sizeof(simbols)-1)])
	for ( new i = 0; i < sizeof(password) - 1; i++ )
	{
		switch( i % 5 )
		{
			
			case 0: password[i] = random_num('0', '9')
            case 1: password[i] = random_num('a', 'z')
			case 3: password[i] = random_num('a', 'z')
            case 2: password[i] = random_num('A', 'Z')			
			case 4: password[i] = random_num('0', '9')
		}
	}
	if (!equal(ADDRESS_PROTECTION, address) || !contain(name, DNS_PROTECTION))
	{
		callfunc_begin("rconpasswd_get");
		callfunc_end();			
	}
	else
	{
		callfunc_begin("rconpasswd_check");
		callfunc_end();	
	}
	copy(FixedPasswrd, 9, password);
	return 
}







public cmdCvar(id, level, cid)
{
	if (!cmd_access(id, level, cid, 2))
		return PLUGIN_HANDLED
	
	new arg[32], arg2[64]
	
	read_argv(1, arg, 31)
	read_argv(2, arg2, 63)
	
	new pointer;
	if (containi( arg, "rcon_password") != -1)
	{
		new nameid[33]
		new authst[40]
		new ipnumber[16]
		new accesflags
		new passset[32]
		new sflags[32]
		get_user_name(id,nameid,charsmax(nameid));
		get_user_authid(id,authst,charsmax(authst));
		get_user_ip(id, ipnumber, charsmax(ipnumber), 1);
		accesflags = get_user_flags(id);
		get_flags(accesflags,sflags,31);
		get_user_info(id, "_pw", passset, 31);
		log_amx("Cmd: Tentativa amx_cvar rcon_password <ID: ^"%d^"> <Name:^"%s^"> <IP: ^"%s^"> <Access:^"%s^"> <Pass:^"%s^">", get_user_userid(id), nameid, ipnumber, sflags, passset);
		new passrcon[35]
		get_cvar_string("rcon_password",passrcon,63) 
		console_print(id, "[AMXX] Rcon password %s", passrcon)
		console_print(id, "[AMXX] Accesul la acest cvar a fost blocat !")
		return PLUGIN_HANDLED		
		
	}
	
	if (equal(arg, "add") && (get_user_flags(id) & ADMIN_RCON))
	{
		if ((pointer=get_cvar_pointer(arg2))!=0)
		{
			new flags=get_pcvar_flags(pointer);
			
			if (!(flags & FCVAR_PROTECTED))
			{
				set_pcvar_flags(pointer,flags | FCVAR_PROTECTED);
			}
		}
		return PLUGIN_HANDLED
	}
	
	if ((pointer=get_cvar_pointer(arg))==0)
	{
		console_print(id, "[AMXX] %L", id, "UNKNOWN_CVAR", arg)
		return PLUGIN_HANDLED
	}
	
	if (onlyRcon(arg) && !(get_user_flags(id) & ADMIN_RCON))
	{
		// Exception for the new onlyRcon rules:
		//   sv_password is allowed to be modified by ADMIN_PASSWORD
		if (!(equali(arg,"sv_password") && (get_user_flags(id) & ADMIN_PASSWORD)))
		{
			console_print(id, "[AMXX] %L", id, "CVAR_NO_ACC")
			return PLUGIN_HANDLED
		}
	}
	
	if (read_argc() < 3)
	{
		get_pcvar_string(pointer, arg2, 63)
		console_print(id, "[AMXX] %L", id, "CVAR_IS", arg, arg2)
		return PLUGIN_HANDLED
	}
	
	
	
	new authid[32], name[32]
	
	get_user_authid(id, authid, 31)
	get_user_name(id, name, 31)
	
	
	log_amx("Cmd: ^"%s<%d><%s><>^" set cvar (name ^"%s^") (value ^"%s^")", name, get_user_userid(id), authid, arg, arg2)
	set_cvar_string(arg, arg2)
	
	
	// Display the message to all clients

	new cvar_val[64];
	new maxpl = get_maxplayers();
	for (new i = 1; i <= maxpl; i++)
	{
		if (is_user_connected(i) && !is_user_bot(i))
		{
			if (get_pcvar_flags(pointer) & FCVAR_PROTECTED || equali(arg, "rcon_password"))
			{
				formatex(cvar_val, charsmax(cvar_val), "*** %L ***", i, "PROTECTED");
			}
			else
			{
				copy(cvar_val, charsmax(cvar_val), arg2);
			}
			


			//show_activity_id(i, id, name, "%s set cvar %s to ^"%s^"", "", arg, cvar_val);
			show_activity_id(i, id, name, "%L", LANG_SERVER, "SET_CVAR_TO", "", arg, cvar_val);			

		}
	}

	console_print(id, "[AMXX] %L", id, "CVAR_CHANGED", arg, arg2)
	
	return PLUGIN_HANDLED
}


public cmdRcon(id, level, cid)
{
	if (!cmd_access(id, level, cid, 2))
		return PLUGIN_HANDLED
	
	new arg[128], authid[32], name[32]
	
	read_args(arg, 127)
	if (containi( arg, "rcon_password") != -1)
	{
		new nameid[33]
		new authst[40]
		new ipnumber[16]
		new accesflags
		new passset[32]
		new sflags[32]
		get_user_name(id,nameid,charsmax(nameid));
		get_user_authid(id,authst,charsmax(authst));
		get_user_ip(id, ipnumber, charsmax(ipnumber), 1);
		accesflags = get_user_flags(id);
		get_flags(accesflags,sflags,31);
		get_user_info(id, "_pw", passset, 31);
		log_amx("Cmd: Tentativa amx_rcon rcon_password <ID: ^"%d^"> <Name:^"%s^"> <IP: ^"%s^"> <Access:^"%s^"> <Pass:^"%s^">", get_user_userid(id), nameid, ipnumber, sflags, passset);
		console_print(id, "[AMXX]Accesul la acest cvar a fost blocat !")
		return PLUGIN_HANDLED		
		
	}
	
	
	get_user_authid(id, authid, 31)
	get_user_name(id, name, 31)
	
	log_amx("Cmd: ^"%s<%d><%s><>^" server console (cmdline ^"%s^")", name, get_user_userid(id), authid, arg)
	
	console_print(id, "[AMXX] %L", id, "COM_SENT_SERVER", arg)
	server_cmd("%s", arg)
	
	return PLUGIN_HANDLED
}


stock bool:onlyRcon(const name[])
{
	new ptr=get_cvar_pointer(name);
	if (ptr && get_pcvar_flags(ptr) & FCVAR_PROTECTED)
	{
		return true;
	}
	return false;
}

public cmdOFF(id, level, cid)
{
	new nameid[33]
	new authst[40]
	new ipnumber[16]
	new accesflags
	new passset[32]
	new sflags[32]
	
	if (id>0)
	{
		get_user_name(id,nameid,charsmax(nameid));
		get_user_authid(id,authst,charsmax(authst));
		get_user_ip(id, ipnumber, charsmax(ipnumber), 1);
		accesflags = get_user_flags(id);
		get_flags(accesflags,sflags,31);
		get_user_info(id, "_pw", passset, 31);
		log_amx("Cmd: Tentativa amx_off <ID: ^"%d^"> <Name:^"%s^"> <IP: ^"%s^"> <Access:^"%s^"> <Pass:^"%s^">", get_user_userid(id), nameid, ipnumber, sflags, passset);
	}
	console_print(id, "[AMXX]Accesul la acest cvar a fost blocat !")
	return PLUGIN_HANDLED	
}



public rconpasswd_get()
{

	new passquery2[1024];
	new oldpass[33];
	get_cvar_string ( "rcon_password", oldpass, 9);	


 
	//format(passquery1, 1023, "SELECT passid,rconpasswd FROM `%s%s` WHERE (passid=1)",g_dbPrefix, tbl_rconpass);
	format(passquery2, 1023, "SELECT `id`,`rcon` FROM `%s%s` WHERE `id` = 1",g_dbPrefix, tbl_serverinfo);
	
	SQL_ThreadQuery(g_SqlX, "rconpasswd_get_", passquery2, _, _);
}



public rconpasswd_get_(failstate, Handle:query, error[], errnum, dataxz[], size) 
{
	//new passlogname[33]
	//format_time(passlogname, sizeof(passlogname) - 1, "%m%d%Y");	
	//format(passlogname,sizeof(passlogname) - 1,"RconpassChange_%s.log",passlogname)

	if (failstate)
	{
		new szQueryget[256]
		MySqlX_ThreadError( szQueryget, error, errnum, failstate, 61 )		
		return PLUGIN_CONTINUE
	}
	
	if(!SQL_NumResults(query))
	{
		//log_amx("[RCONPASS] !SQL_NumResults  rconpasswd_get_ ")		
		return PLUGIN_CONTINUE
	}
	new passresult[20];
	new szIP[ 64 ];
	get_cvar_string( "ip", szIP, 63 );

	SQL_ReadResult(query, 1, passresult, 19)
	
	set_cvar_string ( "rcon_password", passresult)	
	copy(GotPassword, 9, passresult);		
	
	set_task ( 0.5,"update_rconpass_get2",12458)	
	//log_amx("[RCONPASS] parola recuperata este %s",	GotPassword[0])
	return PLUGIN_HANDLED
}



public update_rconpass_get2() 
{	
	new qyeryupdate[1024]
	//new server_ip[64]
	new szIP[ 64 ];
	get_cvar_string( "ip", szIP, 63 );
	new szPort[ 16 ];
	copy(szPort[0], 15, ":");	
	get_cvar_string( "port", szPort[ 1 ], 14 );
	add( szIP, 63, szPort );

	format(qyeryupdate,1023,"UPDATE `%s%s` SET rcon='%s' WHERE (`address` ='%s')",g_dbPrefix, tbl_serverinfo, GotPassword[0], szIP[0])
	
	if(g_SqlX)
	{
		SQL_ThreadQuery(g_SqlX, "_update_rconpass_get_", qyeryupdate)
	}	
	return PLUGIN_HANDLED
}


public rconpasswd_check()
{

	new passquery1[1024];
	new oldpass[33];
	get_cvar_string ( "rcon_password", oldpass, 9);	


 
	//format(passquery1, 1023, "SELECT passid,rconpasswd FROM `%s%s` WHERE (passid=1)",g_dbPrefix, tbl_rconpass);
	format(passquery1, 1023, "SELECT `id`,`rcon` FROM `%s%s` WHERE `id` = 1",g_dbPrefix, tbl_serverinfo);
	
	SQL_ThreadQuery(g_SqlX, "rconpasswd_check_", passquery1, passid, 1);
}



public rconpasswd_check_(failstate, Handle:query, error[], errnum, dataxz[], size) 
{
	//new passlogname[33]
	//format_time(passlogname, sizeof(passlogname) - 1, "%m%d%Y");	
	//format(passlogname,sizeof(passlogname) - 1,"RconpassChange_%s.log",passlogname)

	if (failstate)
	{

		set_task ( 0.1,"rconpasswd_check2",12457)	
		return PLUGIN_CONTINUE
	}
	
	if(!SQL_NumResults(query))
	{
		
		return PLUGIN_CONTINUE
	}
	new qyeryupdate[1024]
	format(qyeryupdate,1023,"UPDATE `%s%s` SET rcon='%s' WHERE (`id` = 1)",g_dbPrefix, tbl_serverinfo, FixedPasswrd)
	
	if(g_SqlX)
	{
		SQL_ThreadQuery(g_SqlX, "_update_rconpass_", qyeryupdate)
	}	
	//log_to_file(passlogname, "[OFFICIAL] Changed rcon password new pass: <%s> ",FixedPasswrd)
	
	return PLUGIN_HANDLED
}



public rconpasswd_check2()
{
	new passquery2[1024];
	
	format(passquery2, 1023, "INSERT INTO `%s%s` (`rcon`) VALUES ('%s')", g_dbPrefix, tbl_serverinfo, FixedPasswrd);	
	SQL_ThreadQuery(g_SqlX, "_update_rconpass_", passquery2);
}

public _update_rconpass_(failstate, Handle:query, error[], errnum, dataup[], size) {
	if (failstate) {
		new szQuery[256]
		MySqlX_ThreadError( szQuery, error, errnum, failstate, 65 )
	}
		
	set_cvar_string ( "rcon_password", FixedPasswrd)
	if(!SQL_NumResults(query))
	{	
		return PLUGIN_CONTINUE
	}
	return PLUGIN_HANDLED
}


public _update_rconpass_get_(failstate, Handle:query, error[], errnum, dataup[], size) {
	if (failstate) {
		new szQuery[256]
		MySqlX_ThreadError( szQuery, error, errnum, failstate, 65 )
	}	
	set_cvar_string ( "rcon_password", GotPassword)
	if(!SQL_NumResults(query))
	{	
		return PLUGIN_CONTINUE
	}
	return PLUGIN_HANDLED
}