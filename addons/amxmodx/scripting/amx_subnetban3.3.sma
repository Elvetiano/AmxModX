//3.2 - Added Voxility net range ban 
//3.3 - Added name spaces and bug fix special chars function

#include <amxmodx>
#include <amxmisc>
#include <cstrike>
#include <fun>
#include <hamsandwich>
#include <official_base>

new gmsgScoreInfo

new const PLUGIN[]   = "Block Networks & Name Cheker"
new const VERSION[]  = "3.3"
new const AUTHOR[]   = "UNU"

#define subnetmsg2 "Your network is banned, You can contact catalin1bingo@yahoo.com for any abuse and unban"
#define lista_rang (1<<0)|(1<<9) // Keys: 1,0
#define block_rang (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<9)// Keys: 1,2,3,4,5,0
#define MIN_ADMIN_LEVEL ADMIN_RESERVATION 

//#pragma ctrlchar '\'

new g_plik_rang[64],g_exept[64],view_more[32];
new g_rcsrds_rang[64]
new g_upc_rang[64]
new g_cbs_rang[64]
new g_orange_rang[64]
new g_tele_rang[64]
new g_voxi_rang[64]

new g_file[64]
new bool:g_rcsmata[33]
new bool:g_cbs[33]
new bool:g_orange[33]
new bool:g_upc[33]
new bool:g_tele[33]
new bool:g_voxi[33]
new bool:g_other[33]
new g_coloredMenus

new const list [][] = 
{
	"INDUNGI RO",
	"INDUNGI RO",
	"INDUNGI RO"
}

new const sTochangeFix[][] = 
{
	"TOP-B | ",
	"MegaB | ",
	"TOP-BOOST",
	""
}
new const sTochange[][] = 
{
	".ru",
	"www",
	"-lt",
	"boost", 
//	"player", 
	".cz", 
	".lt", 
	".com",
	".info",
	"free",
	".net",
	".org",
	".ro",	
	"gametracker",
	"Ms_Pro",
	"SERVERA",
	"admine",
	"admins",
	"faralag",
	"unnamed",
	"TraficZone",
	"PlAy3R",
	"C[0]M",
	"bacau",
	"bluecs",
	"Bluelytning",
	"Warrior",
	"[ro]",
	"Blackghost",
	"2k18",
	"(.)"
}


new pcvar_namecheck
new pcvar_namespaces

public plugin_init()
{	
	register_plugin(PLUGIN, VERSION, AUTHOR)	
	pcvar_namecheck = create_cvar("amx_connect_namecheck", "0.0", FCVAR_NONE, "This cvar controls names and change them!", true, 0.0, true, 1.0);
	pcvar_namespaces = create_cvar("amx_no_namespaces", "0.0", FCVAR_NONE, "This is the cvar that controsl names for spaces", true, 0.0, true, 1.0);	
	register_concmd("amx_bansubnet", "cmdAddSubnet", ADMIN_BAN, " - Ban range ip ^"IP_start IP_end^"")
	register_concmd("amx_addexcept", "cmdAddException", ADMIN_BAN, "Adauga un ip/steam in lista cu ipuri fara restrictie pentru a se poate conecta, Usage: amx_addexcept ^"127.0.0.0 UNU ^"")
	register_concmd("amx_remexcept", "cmdRemoveException", ADMIN_BAN, "Sterge un ip din lista celor cu excepti,Usage: amx_remexcept 127.0.0.0 sau amx_remexcept UNU")
	register_concmd("amx_bannedlist", "admin_rangi", ADMIN_BAN, "Shows the status of the IP banned NonSteam")
	register_concmd("amx_blockmenu", "block_rangi", ADMIN_LEVEL_A, "Shows block menu")
	register_clcmd("amx_chscore","chscore",ADMIN_MENU," - amx_chscore <nick/@CT/@TERRORIST> <frags #> <deaths #>")
	register_clcmd("giveme", "namechange")
	gmsgScoreInfo = get_user_msgid("ScoreInfo")
	register_menucmd(register_menuid("lista_rang_menu"), lista_rang, "Wcisniety")
	register_menucmd(register_menuid("block_rang_menu"), block_rang, "NewWcisniety")
	register_logevent("RoundStartBot", 2, "1=Round_Start" )
	register_event("ResetHUD", "hook_name", "be")	
	g_coloredMenus = colored_menus()
	set_task(6.1,"delayedstart")
}

public RoundStartBot()
{
	set_task(1.0, "autobotadd")
}

public client_authorized(id)
{
	//RcsRdsCheck(id)
	check_subnet(id)	
}

public client_putinserver(id)
{
	//RcsRdsCheck(id)	
	check_subnet(id);
	set_task(1.0, "autobotadd")
}

public client_discconnect(id)
{
	set_task(1.0, "autobotadd")
}

public scanforbots()
{
	new bots[32], botnum
	get_players(bots, botnum, "d")
	return botnum
}

public addbotfunc()
{
	server_cmd("amx_addfake")
}

public removebotfunc()
{
	server_cmd("amx_removefake")
}

public check_subnet(id)
{
	
	new exeptdata[70]
	new sipaddrex1[32], thenewsipaddr[16]	
	new username[33]
	new len, pos
	new userip[16]	
	get_user_ip(id,userip,16,1)
	new szSteamId[35]
	get_user_authid(id,  szSteamId,  sizeof (szSteamId) -1);
	while(read_file(g_exept,pos++,exeptdata,69,len)) 
	{
		if(exeptdata[0] == ';' || exeptdata[0] == '#') continue
		replace(exeptdata, 69, "/", " ")
		remove_quotes(exeptdata)
		parse(exeptdata, sipaddrex1, 20, username, 32)	
		new testuserip[16]
		new testnewuserip[16]

		if (containi(sipaddrex1, "steam") !=-1)
		{
			if(equal(szSteamId,  sipaddrex1))
			{
				return PLUGIN_CONTINUE
			}
		}
		else
		{
			copy(thenewsipaddr, 16, sipaddrex1)
			format(testuserip, sizeof(testuserip),"%s", thenewsipaddr[0])
			format(testnewuserip, sizeof(testnewuserip),"%s", userip[0])
			if (ip_to_number(testuserip) == ip_to_number(testnewuserip))
			{
				return PLUGIN_CONTINUE
			}
		}			
	}
	
	if (g_rcsmata[0] || g_cbs[0] || g_upc[0] || g_tele[0] || g_orange[0] || g_voxi[0] || g_other[0])
	{
		if (g_rcsmata[0])
			check_ip(id,g_rcsrds_rang)
		if (g_cbs[0])
			check_ip(id,g_cbs_rang)
		if (g_upc[0])
			check_ip(id,g_upc_rang)
		if (g_tele[0])
			check_ip(id,g_tele_rang)
		if (g_orange[0])
			check_ip(id,g_orange_rang)
		if (g_voxi[0])
			check_ip(id,g_voxi_rang)
		if (g_other[0])
			check_ip(id,g_plik_rang)	
				
	}
	return PLUGIN_CONTINUE
}

public check_ip(id, file[64])
{
	new readdata[50]
	new len, iline
	new sipaddr1[16], sipaddr2[16],userip[16]
	get_user_ip(id,userip,16,1)
	while (read_file(file, iline++, readdata, 50,len))
	{
		if (readdata[0] == ';' || !readdata[0])
		{
			continue
		}
		replace(readdata, 50, "/", " ")
		parse(readdata, sipaddr1, 16, sipaddr2, 16)
		if (((ip_to_number(sipaddr1) <= ip_to_number(userip) <= ip_to_number(sipaddr2))) && !((get_user_flags(id) & ADMIN_USER)) && !((get_user_flags(id) & ADMIN_RESERVATION)))
		{
			client_cmd(id,"wait;wait;wait;wait")
			client_cmd (id , "echo ^" [OFFICIAL] ********************************^"")
			client_cmd (id , "echo ^" [OFFICIAL] Your network IP is banned^"")
			client_cmd (id , "echo ^" [OFFICIAL] For any questions or reclamations^"")
			client_cmd (id , "echo ^" [OFFICIAL] Follow this link if you think you are banned unfairly^"")
			client_cmd (id , "echo ^" [OFFICIAL] www.official.panelcs.ro^"")
			client_cmd (id , "echo ^" [OFFICIAL] ********************************^"")
			set_task(0.2, "kick_player", id)
		
		}
	}
}

public kick_player(id)
{ 
server_cmd("wait;wait;wait;wait;wait;kick #%d ^"%s^"", get_user_userid(id), subnetmsg2)
}

public autobotadd()
{
	new players[32], inum //, a,b
	//new cvarminplayers = get_cvar_num("amx_min_players")
	new cvarminplayers = 26
	get_players(players, inum, "c")
	new botnumber = 0
	botnumber = scanforbots();
	if (cvarminplayers!=-1)
	{
		new pluginloaded = is_plugin_loaded("fakefull_original.amxx", true);
		if((inum < cvarminplayers) && (pluginloaded != -1) && (botnumber < 2))
		{
			
			if (botnumber == 1)
			{
				set_task(1.0,"addbotfunc")
			}
			if (botnumber == 0)
			{
				set_task(1.0,"addbotfunc")
				//set_task(2.0,"addbotfunc")				
			}				
			
		}
		if (botnumber > 2)
		{
			set_task(1.0,"removebotfunc")	
		}			
		
		if((inum > cvarminplayers -1) && (pluginloaded != -1) && (botnumber > 0))
		{			
			set_task(1.0,"removebotfunc")
			set_task(1.0,"removebotfunc")
		}
	}
}

public delayedstart()
{
	new pos =0,len,  somedata[50]
	while(read_file(g_file,pos++,somedata,50,len))
	{
		if(somedata[0] == ';' || somedata[0] == '#') continue
		replace(somedata, 50, "/", " ")
		if(containi(somedata, "g_rcsmata")!=-1)
		{
			g_rcsmata[0] = true
		}
		if(containi(somedata, "g_cbs")!=-1)
		{
			g_cbs[0] = true
		}
		if(containi(somedata, "g_upc")!=-1)
		{
			g_upc[0] = true
		}
		if(containi(somedata, "g_tele")!=-1)
		{
			g_tele[0] = true
		}
		if(containi(somedata, "g_orange")!=-1)
		{
			g_orange[0] = true
		}
		if(containi(somedata, "g_voxi")!=-1)
		{
			g_voxi[0] = true
		}
		if(containi(somedata, "g_other")!=-1)
		{
			g_other[0] = true
		}
	}
}

public kickidname(id)
{
	server_cmd("wait;wait;wait;wait;wait; kick #%d ^"%s^"", get_user_userid(id), "Banned for Advertisements");
	return PLUGIN_HANDLED;	
}

public namechange(params[],idfunc)
{
	new name[128] 
	
	new id = params[0]
	get_user_name(id, name, 127)
	
	new rand = random_num ( 0, sizeof(list)-1 )
	new formated[25], formateddeci[10]
	new randdeci = random_num ( 1000, 99999 )
	format(formateddeci, sizeof(formateddeci)-1, "[%d",randdeci)
	format( formated , sizeof(formated)-1 , "%s - %s]" , list[rand], formateddeci)
		
	new namesafed[128],nospaces[128]	
	new has_result = get_user_name_safe(name,namesafed,charsmax(name))	
	new Float:cheknamespaces = get_pcvar_float(pcvar_namespaces)
	if (has_result > 0)
	{	
		if (cheknamespaces > 0)
		{
			new has_space = get_name_nospaces(namesafed,nospaces,charsmax(namesafed))

			
			if(has_space > 0)
			{
				client_cmd(id, "name ^"%s^"",nospaces)
				set_user_info(id, "name", namesafed)
				client_cmd(id, "setinfo name ^"%s^"",namesafed)
				chat_color_single(id, "!g[!n:::!tOFFICIAL!n:::!g] !n Your name !t%s !nwas replaced with !g%s !nbecause is not allowed",name,nospaces)				
			}else
			{
				client_cmd(id, "name ^"%s^"",namesafed)
				set_user_info(id, "name", namesafed)
				client_cmd(id, "setinfo name ^"%s^"",namesafed)
				chat_color_single(id, "!g[!n:::!tOFFICIAL!n:::!g] !n Your name !t%s !nwas replaced with !g%s !nbecause is not allowed",name,namesafed)
	
			}
		}
		else
		{
			client_cmd(id, "name ^"%s^"",namesafed)
			set_user_info(id, "name", namesafed)
			client_cmd(id, "setinfo name ^"%s^"",namesafed)	
			chat_color_single(id, "!g[!n:::!tOFFICIAL!n:::!g] !n Your name !t%s !nwas replaced with !g%s !nbecause is not allowed",name,namesafed)	
		}
	}
	else
	{
		for(new i = 0; i < sizeof(sTochangeFix)-1; i++)
		{new nametoworkwith[33],	sTochangeFixWork[33]
				copy(sTochangeFixWork,charsmax(sTochangeFixWork),sTochangeFix[i])
				copy(nametoworkwith,charsmax(nametoworkwith), name);				
				
				while( replace(nametoworkwith, charsmax(nametoworkwith), "  ", " ") ) {}
				while( replace(nametoworkwith, charsmax(nametoworkwith), " ", "_"))	{}				
				while( replace(sTochangeFixWork, charsmax(sTochangeFixWork), " ", "_")) {}
				
				//"TOP-B |  MA-TA"  ==> "TOP-B_|__MA-TA"				
				new lentofix = strlen(sTochangeFixWork);
				
				if (containi(nametoworkwith,sTochangeFixWork)!=-1)
				{
					new garbage[33];
					new newname[33]
					
					new nameformated[33]					
					//split(const szInput[], szLeft[], pL_Max, szRight[], pR_Max, const szDelim[])					
					split(nametoworkwith, garbage, lentofix, newname, charsmax(newname), garbage)
					
					while( replace(newname, charsmax(newname), "_", " ") ) {}
					
					format( nameformated , sizeof(nameformated)-1 , "%s" , newname)			
					chat_color_single(id, "!g[!n:::!tOFFICIAL!n:::!g] !n Your name !t%s !nwas replaced with !g%s !nbecause is not allowed",name,nameformated)
					client_cmd(id, "name ^"%s^"",nameformated)
					set_user_info(id, "name", nameformated)	
					client_cmd(id, "setinfo name ^"%s^"",nameformated)
					
					//chat_color_admins(0, "!g[!n:::!tOFFICIAL!n:::!g] !nAm schimbat numele lui !t%s !nin nume: !g%s",name,nameformated)	
					//log_amx("Numele %s este DETECTAT numele formatate sunt nametoworkwith = %s  si sTochangeFixWork = %s si nameformated = %s",name, nametoworkwith, sTochangeFixWork, nameformated)					
				}//else
					//log_amx("Numele %s nu este detectat cu %s, numele formatate sunt nametoworkwith = %s  si sTochangeFixWork = %s",name, sTochangeFix[i], nametoworkwith, sTochangeFixWork)
								
		}

		if (cheknamespaces > 0)
		{
			new has_space = get_name_nospaces(name,nospaces,charsmax(name))
				
			if(has_space > 0)
			{
				client_cmd(id, "name ^"%s^"",nospaces)
				set_user_info(id, "name", nospaces)
				client_cmd(id, "setinfo name ^"%s^"",nospaces)	
				chat_color_single(id, "!g[!n:::!tOFFICIAL!n:::!g] !n Your name !t%s !nwas replaced with !g%s !nbecause is not allowed",name,nospaces)				
			}			
		}

	}
		
	for(new i = 0; i < sizeof(sTochange)-1; i++)
	{
		
		if (containi(name,sTochange[i])!=-1 )
		{
			chat_color_single(id, "!g[!n:::!tOFFICIAL!n:::!g] !n Your name !t%s !nwas replaced with !g%s !nbecause is not allowed",name,formated)
			client_cmd(id, "name ^"%s^"",formated)
			set_user_info(id, "name", formated)	
			client_cmd(id, "setinfo name ^"%s^"",formated)				
			
		}
		if (strlen(name) < 3)
		{
			chat_color_single(id, "!g[!n:::!tOFFICIAL!n:::!g] !n Your name !t%s !nwas replaced with !g%s !nbecause is to small and not allowed, min 3 chars",name,formated)
			client_cmd(id, "name ^"%s^"",formated)
			set_user_info(id, "name", formated)
			client_cmd(id, "setinfo name ^"%s^"",formated)			
		}				
	}
	
}

public hook_name(id)
{
	new Float:chekname = get_pcvar_float(pcvar_namecheck);
	
	new paramsx[1];
	paramsx[0] = id;
	
	if (chekname > 0.0)
	//if(floatround(chekname, floatround_round) > 0)
	{
		set_task(1.0, "namechange", 0, paramsx, 1,_,_);
	}	
}

public admin_rangi( id,level,cid ) {

	if ( !cmd_access(id,level,cid,1) )
		return PLUGIN_CONTINUE
	//show_motd( id, g_plik_rang, "Zbanowane rangi" )
	Wcisniety(id,0)
	return PLUGIN_CONTINUE
}

public Wcisniety(id, key)
{
	switch (key)
	{
		case 0: {
			new mssge[1300], temp[1000], iLen = formatex(mssge, 5, "<pre>"), file = fopen(g_plik_rang, "rt"), view_more_cache = view_more[id];
		
			view_more[id] = 0;
			if (view_more_cache)
				fseek(file, view_more_cache, SEEK_SET);
		
			while (fgets(file, temp, 999))
				if (iLen + strlen(temp) > 1299)
				{
					view_more[id] = view_more_cache + iLen;
					break;
				}
				else
					iLen += formatex(mssge[iLen], 1294 - iLen, "%s", temp);
			fclose(file);
		
			mssge[1298] = mssge[1299] = '^n';
		
			show_motd(id, mssge, "BANNED IP Range's list");
			rangi_menu(id);
		}
	}
	return PLUGIN_HANDLED;
}

public rangi_menu(id) {
	//show_menu(id, lista_rang, "Lista zbanowanych rang^n1. Zobacz/Dalej ^n0. Wyjscie^n",-1, "lista_rang_menu") // Display menu
	show_menu(id, lista_rang, "List of banned range ^n1. View/Next ^n0. Exit^n",-1, "lista_rang_menu") // Display menu
}

public block_rangi( id,level,cid ) {

	if ( !cmd_access(id,level,cid,1) )
		return PLUGIN_CONTINUE
	NewWcisniety(id,7)
	return PLUGIN_HANDLED
}

public NewWcisniety(id, key)
{
	new pos =0,len,  menudata[50]
	switch (key)
	{
		case 0: {
			if (g_upc[0])
			{
				while(read_file(g_file,pos++,menudata,50,len))
				{
					if(menudata[0] == ';' || menudata[0] == '#') continue
					replace(menudata, 50, "/", " ")
					if(containi(menudata, "g_upc")!=-1)
					{
						write_file(g_file, "", pos-1)
					}
				}
				g_upc[0] = false
			}
			else
			{
				g_upc[0] = true	
				write_file(g_file, "g_upc", -1)
				chat_rangi(0, "!g[OFFICIAL] Activata restrictia reteaua !yUPC!g, Actualizare lista exceptii cu jucatorii prezenti!")
				somename();
			}
			set_task(0.3, "block_menu", id)			
		}
		case 1: {
			if (g_cbs[0])
			{
				while(read_file(g_file,pos++,menudata,50,len))
				{
					if(menudata[0] == ';' || menudata[0] == '#') continue
					replace(menudata, 50, "/", " ")
					if(containi(menudata, "g_cbs")!=-1)
					{
						write_file(g_file, "", pos-1)
					}
				}
				g_cbs[0] = false
			}
			else
			{
				g_cbs[0] = true
				write_file(g_file, "g_cbs", -1)
				chat_rangi(0, "!g[OFFICIAL] Activata restrictia reteaua !yDIGITAL CABLE SYSTEMS!g, Actualizare lista exceptii cu jucatorii prezenti!")
				somename();
			}
			set_task(0.3, "block_menu", id)
			//block_menu(id)
		}
		case 2: {
			if (g_tele[0])
			{
				while(read_file(g_file,pos++,menudata,50,len))
				{
					if(menudata[0] == ';' || menudata[0] == '#') continue
					replace(menudata, 50, "/", " ")
					if(containi(menudata, "g_tele")!=-1)
					{
						write_file(g_file, "", pos-1)
					}
				}
				g_tele[0] = false
			}
			else
			{
				g_tele[0] = true
				write_file(g_file, "g_tele", -1)
				chat_rangi(0, "!g[OFFICIAL] Activata restrictia reteaua !yRomTelecom!g, Actualizare lista exceptii cu jucatorii prezenti!")
				somename();
			}
			set_task(0.3, "block_menu", id)
			//block_menu(id)
		}
		case 3: {
			if (g_rcsmata[0])
			{
				while(read_file(g_file,pos++,menudata,50,len))
				{
					if(menudata[0] == ';' || menudata[0] == '#') continue
					replace(menudata, 50, "/", " ")
					if(containi(menudata, "g_rcsmata")!=-1)
					{
						write_file(g_file, "", pos-1)
					}
				}
				g_rcsmata[0] = false
			}
			else
			{
				g_rcsmata[0] = true
				write_file(g_file, "g_rcsmata", -1)
				chat_rangi(0, "!g[OFFICIAL] Activata restrictia reteaua !yRCS&RDS!g, Actualizare lista exceptii cu jucatorii prezenti!")
				somename();
			}
			set_task(0.3, "block_menu", id)
			//block_menu(id)
		}
		case 4: {
			if (g_orange[0])
			{
				while(read_file(g_file,pos++,menudata,50,len))
				{
					if(menudata[0] == ';' || menudata[0] == '#') continue
					replace(menudata, 50, "/", " ")
					if(containi(menudata, "g_orange")!=-1)
					{
						write_file(g_file, "", pos-1)
					}
				}
				g_orange[0] = false
			}
			else
			{
				g_orange[0] = true
				write_file(g_file, "g_orange", -1)
				chat_rangi(0, "!g[OFFICIAL] Activata restrictia reteaua !yOrange Romania!g, Actualizare lista exceptii cu jucatorii prezenti!")
				somename();
			}
			set_task(0.3, "block_menu", id)
			//block_menu(id)
		}
				
		case 5: {
			if (g_voxi[0])
			{
				while(read_file(g_file,pos++,menudata,50,len))
				{
					if(menudata[0] == ';' || menudata[0] == '#') continue
					replace(menudata, 50, "/", " ")
					if(containi(menudata, "g_voxi")!=-1)
					{
						write_file(g_file, "", pos-1)
					}
				}
				g_voxi[0] = false
			}
			else
			{
				g_voxi[0] = true
				write_file(g_file, "g_voxi", -1)
				chat_rangi(0, "!g[OFFICIAL] Activata restrictia reteaua !yVoxility Romania!g, Actualizare lista exceptii cu jucatorii prezenti!")
				somename();
			}
			set_task(0.3, "block_menu", id)
			//block_menu(id)
		}		
		
		case 6: {			
			if (g_other[0])
			{
				while(read_file(g_file,pos++,menudata,50,len))
				{
					if(menudata[0] == ';' || menudata[0] == '#') continue
					replace(menudata, 50, "/", " ")
					if(containi(menudata, "g_other")!=-1)
					{
						write_file(g_file, " ", pos-1)
					}
				}
				g_other[0] = false
			}
			else
			{
				g_other[0] = true
				write_file(g_file, "g_other", -1)
				chat_rangi(0, "!g[OFFICIAL] Activata restrictia !yIP'uri definite manual!g, Actualizare lista exceptii cu jucatorii prezenti!")
				somename();
			}
			set_task(0.3, "block_menu", id)
			//block_menu(id)
		}
		
		case 7: {
			set_task(0.3, "block_menu", id)
			//block_menu(id)
		}
			default: {
			
		}
	}
	return PLUGIN_HANDLED;
}

public block_menu(id) 
{
	new menuBody[512]
	new len = format(menuBody,511,g_coloredMenus ? "\yBlock Networks Menu\R^n\w^n" : "Block Networks Menu ^n^n" )
	if (g_coloredMenus)
//Atentie linia meniului este prea lunga pe viitor trebuie facut altfel meniul 
//nu se mai poate adauga nimik pe linie (erroare compilatie )
			len += format(menuBody[len], 511-len, "Type 1 2 3 4 5 to switch On/Off ^n\w1. Block \yUPC   \R %s ^n\w2. Block \yDIGITAL CBS   \R %s ^n\w3. Block \yRomTelecom   \R %s ^n\w4. Block \yRCS&RDS   \R %s ^n\w5. Block \yORANGE   \R %s ^n\w6. Block \yVoxility   \R %s ^n\w7. Block \yother defined \wNetworks \R %s ^n0. \rExit^n", g_upc[0]?"\yOn":"\rOff", g_cbs[0]?"\yOn":"\rOff", g_tele[0]?"\yOn":"\rOff",g_rcsmata[0]?"\yOn":"\rOff",g_orange[0]?"\yOn":"\rOff",g_voxi[0]?"\yOn":"\rOff",g_other[0]?"\yOn":"\rOff")
	else
			len += format(menuBody[len], 511-len, "Type 1 2 3 4 5 to switch On/Off ^n\w1. Block UPC Network [%s]^n\w2. Block DIGITAL CBS Network [%s]^n\w3. Block RomTelecom Network [%s]^n\w4. Block RCS&RDS Network [%s]^n\w5. Block ORANGE Network [%s]^n\w6. Block Voxility Network [%s]^n\w7. Block other defined Networks [%s]^n0. Exit^n", g_upc[0]? "On" :"Off", g_cbs[0] ? "On" :"Off", g_tele[0] ? "On" :"Off",g_rcsmata[0] ? "On" :"Off",g_orange[0] ? "On" :"Off",g_voxi[0] ? "On" :"Off",g_other[0]? "On" :"Off" )
	show_menu(id, block_rang, menuBody,-1, "block_rang_menu") // Display menu

	//show_menu(id, block_rang, "Block Networks Menu ^n1. Block/Unblock RCS&RDS Network ^n2. Block/Unblock UPC Network ^n3. Block/Unblock DIGITAL CBS Network ^n4. Block/Unblock RomTelecom Network ^n0. Exit^n",-1, "block_rang_menu") // Display menu	
}

public client_infochanged(id)
{
	if (!is_user_connected(id))
		return PLUGIN_CONTINUE
	new newname[32], oldname[32]
	new paramsf[1] 	
	paramsf[0]= id	
	
	get_user_name(id, oldname, 31)
	get_user_info(id, "name", newname, 31)
	if (!equal(newname, oldname))
	{
		check_subnet(id);		
		set_task(1.0, "namechange", 0, paramsf, 1,_,_)
		
	}
	//check_subnet(id);
	return PLUGIN_CONTINUE
}

public cmdAddSubnet(id, level, cid)
{
	if (!cmd_access(id, level, cid, 2))
		return PLUGIN_HANDLED

	new arg[32]
	read_argv(1, arg, 31)
	write_file(g_plik_rang, arg, -1)
	console_print(id, "[OFFICIAL] Range %s added to banned list",arg)
	
	return PLUGIN_HANDLED
}

public cmdAddException(id, level, cid)
{
	if (!cmd_access(id, level, cid, 2))
		return PLUGIN_HANDLED
 
	new username[33]
	new arg[32],arg2[33],buffer[60]
	read_argv(1, arg, 31)
	new spacepos = containi( arg, " " )
	new sipaddr1[33]
	parse(arg, sipaddr1, spacepos, arg2, 32)
	format (username, sizeof username - 1, "%s", arg2)
	if (strlen(username)==0)
	{		
		console_print(id, "[OFFICIAL] Argumentul %s trebuie sa contina si un nume",arg)
		return PLUGIN_HANDLED
	}
	strtolower (username)
	format (buffer, sizeof buffer - 1, "%s %s", sipaddr1,username)
	write_file(g_exept, buffer, -1)
	console_print(id, "[OFFICIAL] Ip-ul %s cu numele %s a fost adaugat cu succes la lista cu excepti",sipaddr1,username)
	return PLUGIN_HANDLED
}

public cmdRemoveException(id, level, cid)
{
	if (!cmd_access(id, level, cid, 2))
		return PLUGIN_HANDLED
	new arg[32],len,  remdata[50],sipaddr1[16],username[33]
	new pos = 0
	read_args ( arg, 31)
	remove_quotes(arg) 
	while(read_file(g_exept,pos++,remdata,50,len)){
		if(remdata[0] == ';' || remdata[0] == '#') continue
		replace(remdata, 50, "/", " ")
		if(containi(remdata, arg)!=-1)
		{
			
			write_file(g_exept, "", pos-1)			
			parse(remdata, sipaddr1, 16, username, 32)
			console_print(id, "[OFFICIAL] Ip-ul %s sau numele %s a fost sters din lista cu excepti",sipaddr1,username)
			return PLUGIN_CONTINUE
		}
		
	}
	return PLUGIN_CONTINUE
}

public cmdRemoveSubnet(id, level, cid)
{
	if (!cmd_access(id, level, cid, 2))
		return PLUGIN_HANDLED
	
	new arg[32]
	read_argv(1, arg, 31)
	new len, pos
	new subdatarem[50]
	while(read_file(g_plik_rang,pos++,subdatarem,50,len)){
		if(subdatarem[0] == ';' || subdatarem[0] == '#') continue
		if(containi(subdatarem, arg)!=-1)
		{
			write_file(g_plik_rang, "", pos-1)
			console_print(id, "[OFFICIAL] Range %s removed from banned list",arg)
		}
	}
	return PLUGIN_HANDLED
}


public somename()
{
	new players[32], player, pnum
	get_players(players, pnum, "c")
	for(new i = 0; i < pnum; i++)
	{
		player = players[i]
		set_task(0.1, "chekfile", player)
	}
} 

public chekfile(id)
{
	new ingamename[33], ingameip[16]
	new buffer[60]
	new sz = file_size(g_exept, 1);
	get_user_ip(id,ingameip,16,1)
	get_user_name(id,ingamename,32)
	for (new i; i < sz; i++)
	{
		new text[128]
		new ln
		read_file(g_exept, i, text, sizeof (text), ln);
		while( contain ( ingamename, "<" ) != -1 )
			replace( ingamename, charsmax(ingamename), "<", "_" )
		while( contain ( ingamename, ">" ) != -1 )
			replace( ingamename, charsmax(ingamename), ">", "_" )
		if(containi(text, ingamename)!=-1 || containi(text, ingameip)!=-1)
		{
			return PLUGIN_CONTINUE
		}
	}

	strtolower (ingamename)
	format (buffer, sizeof buffer - 1, "%s %s", ingameip,ingamename)			
	write_file(g_exept, buffer, -1)
	return PLUGIN_CONTINUE
}



public plugin_cfg()
{
	new sConfigsDir[64]
	get_configsdir(sConfigsDir, sizeof sConfigsDir - 1)
	new newDir[]="NetBlock";
	new g_directory[64]
	formatex(g_directory, sizeof g_directory - 1, "%s/%s", sConfigsDir,newDir)
	if(!dir_exists(g_directory))
		mkdir(g_directory);
	
	formatex(g_plik_rang, sizeof g_plik_rang - 1, "%s/other_ranges.txt", g_directory)
	if(!file_exists(g_plik_rang))
   	write_file(g_plik_rang, ";Range IP LIST file^n;For deletion of the ban, delete the line or put^";^" in front of the range", -1)

	formatex(g_rcsrds_rang, sizeof g_rcsrds_rang - 1, "%s/range_rcsrds.txt", g_directory)
	if(!file_exists(g_rcsrds_rang))	
	write_file(g_rcsrds_rang, ";Network RCS&RDS IP's RANGE LIST file", -1)

	formatex(g_upc_rang, sizeof g_upc_rang - 1, "%s/range_upc.txt", g_directory)
	if(!file_exists(g_upc_rang))	
	write_file(g_upc_rang, ";Network UPC IP's RANGE LIST file", -1)

	formatex(g_cbs_rang, sizeof g_cbs_rang - 1, "%s/range_CBS.txt", g_directory)
	if(!file_exists(g_cbs_rang))	
	write_file(g_cbs_rang, ";Network DIGITAL CABLE SYSTEMS IP's RANGE LIST file", -1)

	formatex(g_tele_rang, sizeof g_tele_rang - 1, "%s/range_Romtelecom.txt", g_directory)
	if(!file_exists(g_tele_rang))	
	write_file(g_tele_rang, ";Network RomTelecom IP's RANGE LIST file", -1)

	formatex(g_orange_rang, sizeof g_orange_rang - 1, "%s/range_orange.txt", g_directory)
	if(!file_exists(g_orange_rang))	
	write_file(g_orange_rang, ";Network Orange IP's RANGE LIST file", -1)

	formatex(g_file, sizeof g_file - 1, "%s/truefalse.txt", g_directory)
	if(!file_exists(g_file))	
	write_file(g_file, ";Acest fisier este necesar pentru stocarea setarilor", -1)

	formatex(g_voxi_rang, sizeof g_voxi_rang - 1, "%s/range_voxi.txt", g_directory)
	if(!file_exists(g_voxi_rang))	
	write_file(g_voxi_rang, ";Network Voxility IP's RANGE LIST file", -1)

	formatex(g_exept, sizeof g_exept - 1, "%s/exception.txt", g_directory)
	if(!file_exists(g_exept))	
	write_file(g_exept, ";IP LIST of players you want to exclude from ban ^n; Add here only ips if you want them not to be banned", -1)	
}

public chscore(id,level,cid)
{
	if (!cmd_access(id,level,cid,2)) 
	{ 
      return PLUGIN_HANDLED 
	}
	new victim[32],deathsI[32],fragsI[32]
	read_argv(1,victim,31)

	read_argv(2,fragsI,31) 
	new frags = str_to_num(fragsI) 
	   
	read_argv(3,deathsI,31) 
	new deaths = str_to_num(deathsI) 
	
	if (victim[0]=='@')
	{ 
		new team[32], inum 
		get_players(team,inum,"e",victim[1]) 
		if (inum==0)
		{ 
			console_print(id,"[AMX] No clients found on such team.") 
			return PLUGIN_HANDLED 
		} 
		for (new i=0;i<inum;++i)
		{
		    new teams = get_user_team(team[i])  
		    set_user_frags(team[i],frags)
		    cs_set_user_deaths(team[i],deaths)
		    message_begin(MSG_ALL,gmsgScoreInfo)
		    write_byte( team[i] )  
		    write_short(frags) 
		    write_short(deaths) 
		    write_short(0) 
		    write_short(teams) 
		    message_end() 
		} 
	} 
	else
	{
		new user = cmd_target(id,victim,0)
		new authid[32]
		get_user_authid(user,authid,31)  
		if (!user)
		{
			console_print(id,"[AMX] No such client found.") 
			return PLUGIN_HANDLED 
		}
		new teams = get_user_team(user)
		set_user_frags(user,frags)
		cs_set_user_deaths(user,deaths)
		message_begin(MSG_ALL,gmsgScoreInfo) 
	  	write_byte(user) 
	  	write_short(frags) 
	  	write_short(deaths) 
	  	write_short(0) 
	  	write_short(teams) 
	  	message_end()
  	}
	return PLUGIN_HANDLED 
}

stock check_steam(id,steamidnr[32])
{


	new steamauth[32]
	new userauth[32]
	copy(steamauth, 31, steamidnr)
	get_user_authid(id, userauth, 31)
	log_amx("Fking exept steam  is %s", steamauth)
	log_amx("Fking real steam  is %s", userauth)
	if (equal(steamauth, userauth))
	{
		return 1
	}
	return 0		
}


stock ip_to_number(userip[16]) 
{
	new ipb1[12],ipb2[12],ipb3[12],ipb4[12],uip[16]
	new ip, nipb1,nipb2,nipb3,nipb4
	copy(uip, 16, userip)
	while(replace(uip, 16, ".", " ")){}
	parse(uip, ipb1, 12, ipb2, 12, ipb3, 12, ipb4, 12)
	nipb1 = str_to_num(ipb1)
	nipb2 = str_to_num(ipb2)
	nipb3 = str_to_num(ipb3)
	nipb4 = str_to_num(ipb4)
	ip = nipb1*255*255*255+nipb2*255*255+nipb3*255+nipb4
	return ip
}


stock SendCmd_2( id , text[] ) {
   static cmd_line[1024]
   message_begin( MSG_ONE, 9, _, id )
   format( cmd_line , sizeof(cmd_line)-1 , "%s%s" , "^n" , text )
   write_string( cmd_line )
   message_end()
}

stock chat_rangi(const id, const input[], any:...)
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
				message_begin(MSG_ONE, get_user_msgid("SayText"), _, players[i])
				write_byte(players[i])
				write_string(msg)
				message_end()
			}
		}
	}
}
/*
public cmd_test(id)
{
	new namesafe[128]
	new name[128]
	get_user_name(id,name,127)
	mysql_get_username_safe(id,namesafe,charsmax(namesafe))
	//chat_rangi(id, "!g[OFFICIAL] Activata restrictia reteaua !yOrange Romania!g, Actualizare lista exceptii cu jucatorii prezenti!")
	client_print(id, print_chat, "[OFFICIAL] Your name %s was replaced with %s because is not allowed",name,namesafe)
	client_print(id, print_console, "[OFFICIAL] Your name %s was replaced with %s because is not allowed",name,namesafe)	
}*/


/*
mysql_escape_string(const source[],dest[],len)
{
	copy(dest, len, source);
	
	for( new f = 0; f < sizeof(special1)-1; f++)
	{
			replace_all( dest, len, special1[f], " ");
			//client_print(0, print_console, "[OFFICIAL] New name %s because is not allowed special char [ %s ]", dest,  special1[f])
	}
	for( new f = 0; f < sizeof(special2)-1; f++)
	{
			replace_all( dest, len, special2[f], " ");
			//client_print(0, print_console, "[OFFICIAL] New name %s because is not allowed special char [ %s ]", dest,  special2[f])
	}
	for( new f = 0; f < sizeof(special3)-1; f++)
	{
			replace_all( dest, len, special3[f], " ");
			//client_print(0, print_console, "[OFFICIAL] New name %s because is not allowed special char [ %s ]", dest,  special3[f])
	}
	
	new sizedest=strlen(dest)
	
	new beforespace[128]
	new afterspace[128]
	new rezultz[128]
	for( new i = 0; i < sizedest; i++)
	{
		if(isspace(dest[i]))
		{
			argbreak(dest, beforespace, i, afterspace, 127)			
			format(rezultz, sizeof(rezultz)-1,"%s%s", beforespace[0],afterspace[0])
			copy(dest, sizeof(dest)-1, rezultz);
			//client_print(0, print_console, "[OFFICIAL] Copiez argbreak dest i-1 adica  beforespace : %s", beforespace)
			//client_print(0, print_console, "[OFFICIAL] Copiez argbreak dest i+1 adica  afterspace : %s", afterspace)
			//client_print(0, print_console, "[OFFICIAL] La caracterul %d am gasit un spatiu ", i)	
			sizedest=strlen(dest)
		}
	}	
	replace_all(dest,len,"'","_");
	replace_all(dest,len,"^^","_");
}

mysql_get_username_safe(id,dest[],len)
{
	new name[128]
	get_user_name(id,name,127)
	mysql_escape_string(name,dest,len)
}
*/