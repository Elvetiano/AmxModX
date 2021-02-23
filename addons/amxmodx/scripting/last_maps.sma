#include <amxmodx>
#include <amxmisc>
#include <dhudmessage>
#include <official_base>

#define HartiMaxime	15

new NumeHarti[HartiMaxime][34]
static const COLOR[] = "^x04" //green
static const COLOR2[] = "^x03" //Team

new g_AdminKick = ADMIN_KICK;
new g_AdminRcon = ADMIN_RCON;


public plugin_init() {
	register_plugin("Ultimele Harti", "1.0", "M@$t3r_@dy")
	register_clcmd("say /harti", "HartiJucateCuSay")
	register_clcmd("say_team /harti", "HartiJucateCuSay")
	register_clcmd("say /maps", "HartiJucateCuSay")
	register_clcmd("say_team /maps", "HartiJucateCuSay")
	register_clcmd("say /last", "last_function", ADMIN_CHAT, "Chat command folositi doar pentru last");
	register_clcmd("say_team /last", "last_function", ADMIN_CHAT, "Chat command folositi doar pentru last");
	register_clcmd("say /ORB", "orb_function", ADMIN_RCON, "Chat command Suji ORB");
	register_clcmd("say_team /ORB", "orb_function", ADMIN_RCON, "Chat command Suji ORB");
	register_clcmd("say", "chat_function", ADMIN_CHAT, "<message> - sends BIG message to all players");
	register_clcmd("say_team", "chat_function", ADMIN_CHAT, "<message> - sends BIG message to all players");
	register_concmd("amx_lastround", "last_function", ADMIN_CHAT, "Comanda pentru a afisa Last Last Last mare");
	register_concmd("amx_dhud", "console_function", ADMIN_CHAT, "<message> - sends BIG message to all players", -1, false);
}

public plugin_cfg() {
	new FisierHartiJucate[64]
	
	get_localinfo("amxx_configsdir", FisierHartiJucate, 63)
	format(FisierHartiJucate, 63, "%s/hartianterioare.txt", FisierHartiJucate)

	new Fisier = fopen(FisierHartiJucate, "rt")
	new i
	new Temporar[34]
	if(Fisier)
	{
		for(i=0; i<HartiMaxime; i++)
		{
			if(!feof(Fisier))
			{
				fgets(Fisier, Temporar, 33)
				replace(Temporar, 33, "^n", "")
				formatex(NumeHarti[i], 33, Temporar)
			}
		}
		fclose(Fisier)
	}

	delete_file(FisierHartiJucate)

	new CurrentMap[34]
	get_mapname(CurrentMap, 33)

	Fisier = fopen(FisierHartiJucate, "wt")
	if(Fisier)
	{
		formatex(Temporar, 33, "%s^n", CurrentMap)
		fputs(Fisier, Temporar)
		for(i=0; i<HartiMaxime-1; i++)
		{
			CurrentMap = NumeHarti[i]
			if(!CurrentMap[0])
				break
			formatex(Temporar, 33, "%s^n", CurrentMap)
			fputs(Fisier, Temporar)
		}
		fclose(Fisier)
	}
}

public HartiJucateCuSay(id) {
	new HartiAnterioare[256], n
	n += formatex(HartiAnterioare[n], 255-n, "%s [OFFICIAL] Hartile jucate anterior sunt:",COLOR2)
	for(new i; i<HartiMaxime; i++)
	{
		if(!NumeHarti[i][0])
		{
			n += formatex(HartiAnterioare[n-1], 255-n+1, ".")
			break
		}
		n += formatex(HartiAnterioare[n], 255-n, "%s %s%s",COLOR ,NumeHarti[i] ,i+1 == HartiMaxime ? "." : ",")		
		if(n > 96 ) {
				print_message(id, HartiAnterioare)
				n = format(HartiAnterioare, 255, "%s ",COLOR)
			}
	}
	//client_print(id, print_chat, "%s^n",HartiAnterioare)
	print_message(id, HartiAnterioare)
	return PLUGIN_CONTINUE
}


print_message(id, msg[]) {
	message_begin(MSG_ONE, get_user_msgid("SayText"), {0,0,0}, id)
	write_byte(id)
	write_string(msg)
	message_end()
}

public last_function( id )
{
	if(get_user_flags(id) & g_AdminKick)
	{
		new  name[33];		
		get_user_name(id, name, charsmax(name));
		set_dhudmessage( 0, 160, 0, -1.0, 0.25, 2, 6.0, 3.0, 0.1, 1.5 );
		show_dhudmessage( 0, "[%s]: %s", name[0],"Boys......Last..." );
	}
}

public orb_function( id )
{
	if(get_user_flags(id) & g_AdminRcon)
	{
		new  name[33];		
		get_user_name(id, name, charsmax(name));
		set_dhudmessage( 255, 0, 255, -1.0, 0.25, 2, 6.0, 3.0, 0.1, 1.5 );
		show_dhudmessage( 0, "[%s]: %s", name[0],"ORB......SUJI...NINO,NINO,NINO" );
	}
}



public chat_function(id)
{
	if (!access(id, ADMIN_CHAT))
	{
		return PLUGIN_CONTINUE;
	}
	
	new message[128], name[33];
	read_args(message, charsmax(message));
	remove_quotes(message);
	if (containi(message,"/dhud")!=-1)
	{
		new count = 1, players[32]
		get_players(players, count, "ch")
	
		if(strlen(message) <= 6)
			return PLUGIN_CONTINUE;
		get_user_name(id, name, charsmax(name));
		set_dhudmessage( 0, 160, 0, -1.0, 0.25, 2, 6.0, 3.0, 0.1, 1.5 );
		show_dhudmessage( 0, "[%s]: %s", name[0],message[5]);

		return PLUGIN_HANDLED_MAIN	
	}else
		return PLUGIN_CONTINUE
}


public console_function( id, level, cid )
{
	if (!cmd_access(id, level, cid, 2))
		return PLUGIN_HANDLED
	
	new message[128], name[33];
	read_args(message, charsmax(message));
	get_user_name(id, name, charsmax(name));
	
	set_dhudmessage( 0, 160, 0, -1.0, 0.25, 2, 6.0, 3.0, 0.1, 1.5 );
	show_dhudmessage(0, "[%s]: %s", name[0],message[0]);			
	
	return PLUGIN_HANDLED ;
}