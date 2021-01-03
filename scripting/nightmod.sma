#include <amxmodx>
#include <amxmisc>
#include <official_base>
#define ACCESSFLAG ADMIN_LEVEL_C

/*
******* - Change list - **************************

	- Version 1.0
		* This plugin is a work of S3ekEr 
		*http://www.extreamcs.com/forum/cereri-pluginuri/cerere-plugin-program-noapte-t140653.html
	- Version 1.1 
		* Last round when number of rounds meets the amx_restart_maxrounds and reload map
 
	- Version 2.0 20-06-2020
		* Added galileo to pause list
		* Added auto pausing plugins in pause list when switching to nightmode 
 
	- Version 2.0 20-06-2020
		* Added Autoexecconfig to execute own config for this plugin you can find config in (cstrike/addons/amxmodx/configs/plugins/plugin-Nightmod.cfg)
	- Version 2.0.1 26-06-2020
		* Removed some plugins from pause
		* Timeout 999 during night
		
		
	** TO DO **
		* add comp to lower amxmodx verions
*********************************************
*/

#define PLUGIN	"Nightmod"
#define VERSION	"2.0.1"
#define AUTHOR	"S3ekEr & UNU"



new a[6],b[4],minutes[3],hours[3], g_roundCountT, g_roundCountCT

new bool:delaymaptrue = false;

public plugin_init()
{
	register_plugin(PLUGIN, VERSION, AUTHOR)
	create_cvar("nightmod_version", VERSION, FCVAR_SERVER|FCVAR_EXTDLL|FCVAR_UNLOGGED|FCVAR_SPONLY, "Plugin version^nDo not edit this cvar")

	#if AMXX_VERSION_NUM < 183
		set_fail_state("Plugins failed AmxModx version is < 1.8.3")
	#endif

	register_concmd("amx_unlag_plugins", "pause_lagplugins", ACCESSFLAG,"Put plugins in pause or unpause" );
	register_srvcmd("amx_unlag_plugins", "pause_lagplugins", -1, "Put plugins in pause or unpause");
	register_concmd("amx_unpauseall", "unpauseall_plugins", ACCESSFLAG,"Unpause plugins" );
	register_srvcmd("amx_unpauseall", "unpauseall_plugins", -1, "Unpause plugins");
	
	set_task(5.0, "task_check_time", 38427236, _, _, "b")	
	
	register_event( "SendAudio", "eT_win" , "a", "2&%!MRAD_terwin" );
	register_event( "SendAudio", "eCT_win", "a", "2&%!MRAD_ctwin"  );
	
	register_event("TextMsg","Night_RoundRestart","a","2&#Game_w")
	register_event("TextMsg","Night_RoundRestart","a","2&#Game_C")
	
	create_cvar("amx_restart_maxrounds", "50", FCVAR_NONE, "This sets after how many rounds in a map the map will reload, <min/max 10/100>", .has_min = true, .min_val= 10.0, .has_max = true, .max_val = 100.0)
	create_cvar("amx_night_start", "22", FCVAR_NONE, "Sets plugin cvar start night time to apply settings for the night", .has_min = true, .min_val = 0.0, .has_max = true, .max_val = 23.0)
	create_cvar("amx_night_end", "11", FCVAR_NONE, "Sets plugin cvar end night time and apply day settings", .has_min = true, .min_val = 0.0, .has_max = true, .max_val = 23.0)
	
	//register_cvar("amx_restart_maxrounds", "30")	
	//register_cvar("amx_night_start", "22")
	//register_cvar("amx_night_end", "11")
		
	get_time("%H:%M:", a, 5)
	get_time("%S", b, 3)
	get_time("%M", minutes, 2)
	get_time("%H", hours, 2)
	
	
	if ((str_to_num(hours) >= get_cvar_num("amx_night_start")) || ( str_to_num(hours) < get_cvar_num("amx_night_end")))
	{
		set_task(10.0, "setsetting_Night")
		setsetting_pauseplugins();
	}else
	{
		if (( str_to_num(hours) >= get_cvar_num("amx_night_end")) && ( str_to_num(hours) < get_cvar_num("amx_night_start")))
		{
			set_task(10.0, "setsetting_Day")
			setsetting_unpause();
		}	
	}
	
	g_roundCountCT = 0
	g_roundCountT  = 0
	
	AutoExecConfig(true)
}




public eT_win()
{
	g_roundCountT++
}

public eCT_win()
{
	g_roundCountCT++
}

public Night_RoundRestart()
{
	g_roundCountCT = 0
	g_roundCountT = 0	
}


public PrintTextLast()
{
	if (get_cvar_num("amx_restart_maxrounds"))
	{
		switch (random(6))
		{
			case 5:
			set_hudmessage(255, 0, 0 , 0.45, 0.10, 2, 0.1, 5.0, 0.1, 0.1, -1)
			//set_hudmessage ( 1, 2, 3, 4, 5, 6, Float:fxtime=6.0, Float:holdtime=12.0, Float:fadeintime=0.1, Float:fadeouttime=0.2, channel=4 )
			case 4:
			set_hudmessage(36, 143, 36 , 0.45, 0.10, 2, 0.1, 5.0, 0.1, 0.1, -1)
			case 3:
			set_hudmessage(255, 255, 0 , 0.45, 0.10, 2, 0.1, 5.0, 0.1, 0.1, -1)
			case 2:
			set_hudmessage(230, 0, 230 , 0.45, 0.10, 2, 0.1, 5.0, 0.1, 0.1, -1)
			case 1:
			set_hudmessage(0, 230, 230 , 0.45, 0.10, 2, 0.1, 5.0, 0.1, 0.1, -1)
			default:
			set_hudmessage(255, 255, 255 , 0.45, 0.10, 2, 0.1, 5.0, 0.1, 0.1, -1)
		}
		show_hudmessage(0, "!!! LAST - ROUND !!! ");
	}
}


public task_check_time()
{
	
	get_time("%H:%M:", a, 5)
	get_time("%S", b, 3)
	get_time("%M", minutes, 2)
	get_time("%H", hours, 2)
	
	//new themapname[33]	
	//get_mapname(themapname,32)

	if ( str_to_num(hours) == get_cvar_num("amx_night_start") && str_to_num(b) < 5 && str_to_num(minutes) < 1)
	{
		chat_color_all(0, "!g[!n:::!tOFFICIAL!n:::!g] !nEste ora !t%s !nserverul trece pe setarile de noapte.!t(de_dust2 only)",a)
		chat_color_all(0, "!g[!n:::!tOFFICIAL!n:::!g] !nEste ora !t%s !nserverul trece pe setarile de noapte.!t(de_dust2 only)",a)
		chat_color_all(0, "!g[!n:::!tOFFICIAL!n:::!g] !nEste ora !t%s !nserverul trece pe setarile de noapte.!t(de_dust2 only)",a)
		chat_color_all(0, "!g[!n:::!tOFFICIAL!n:::!g] !nEste ora !t%s !nserverul trece pe setarile de noapte.!t(de_dust2 only)",a)
		chat_color_all(0, "!g[!n:::!tOFFICIAL!n:::!g] !nEste ora !t%s !nserverul trece pe setarile de noapte.!t(de_dust2 only)",a)
		g_roundCountT = g_roundCountCT = (get_cvar_num("amx_restart_maxrounds") / 2)
		delaymaptrue = true

		log_amx("[:::OFFICIAL:::] Este ora !t%s serverul trece pe setarile de noapte.(de_dust2 only)",a)
	}

     //amx_night_start 21
     //amx_night_end 9
  /*
	if ((str_to_num(hours) >= get_cvar_num("amx_night_start")))
	{
		set_task(10.0, "setsetting_Night")
	}
	else
	{
		if (( str_to_num(hours) < get_cvar_num("amx_night_end")))
		{
			set_task(10.0, "setsetting_Night")
		}
	}
	
	
	
	if (( str_to_num(hours) >= get_cvar_num("amx_night_end")) && ( str_to_num(hours) < get_cvar_num("amx_night_start")))
	{
		set_task(10.0, "setsetting_Day")
		setsetting_unpause();
	}




	
	 
	if ((str_to_num(hours) >= get_cvar_num("amx_night_start")) && (str_to_num(b) < 5) && (str_to_num(minutes) < 1))
	{
		set_task(10.0, "setsetting_Night")
	}
	if (( str_to_num(hours) < get_cvar_num("amx_night_end")) && (str_to_num(b) < 5) && (str_to_num(minutes) < 1))
	{
		set_task(10.0, "setsetting_Night")
	}	
	
	
	
	if (( str_to_num(hours) >= get_cvar_num("amx_night_end")) && (str_to_num(b) < 5) && (str_to_num(minutes) < 1))
	{
		set_task(10.0, "setsetting_Day")
		setsetting_unpause();
	}
	if (( str_to_num(hours) < get_cvar_num("amx_night_start")) && (str_to_num(b) < 5) && (str_to_num(minutes) < 1))
	{
		set_task(10.0, "setsetting_Day")
		setsetting_unpause();
	}*/
	
	
	if ( str_to_num(hours) == get_cvar_num("amx_night_end") && str_to_num(b) < 5 && str_to_num(minutes) < 1)
	{
		chat_color_all(0, "!g[!n:::!tOFFICIAL!n:::!g] !nEste ora !t%s !nserverul trece pe setarile de zi. Multumim",a)
		chat_color_all(0, "!g[!n:::!tOFFICIAL!n:::!g] !nEste ora !t%s !nserverul trece pe setarile de zi. Multumim",a)
		chat_color_all(0, "!g[!n:::!tOFFICIAL!n:::!g] !nEste ora !t%s !nserverul trece pe setarile de zi. Multumim",a)
		chat_color_all(0, "!g[!n:::!tOFFICIAL!n:::!g] !nEste ora !t%s !nserverul trece pe setarile de zi. Multumim",a)
		chat_color_all(0, "!g[!n:::!tOFFICIAL!n:::!g] !nEste ora !t%s !nserverul trece pe setarile de zi. Multumim",a)
		log_amx("[:::OFFICIAL:::] Este ora !t%s serverul trece pe setarile de zi. Multumim",a)
		g_roundCountT = g_roundCountCT = (get_cvar_num("amx_restart_maxrounds") / 2)
	}
	
	if (((g_roundCountCT + g_roundCountT) == get_cvar_num("amx_restart_maxrounds")) && get_cvar_num("amx_restart_maxrounds") > 0 )
	{
		PrintTextLast();
	}
	
	if (((g_roundCountCT + g_roundCountT) > get_cvar_num("amx_restart_maxrounds")) && get_cvar_num("amx_restart_maxrounds") > 0 )
	{
		//server_cmd("amx_cvar sv_restart 3")
		new mapname[64],srvcmd[128]
		get_mapname(mapname, sizeof(mapname));
		
		format(srvcmd, sizeof(srvcmd), "amx_map %s", mapname)
		if (delaymaptrue)
		{
			chat_color_all(0, "!g[!n:::!tOFFICIAL!n:::!g] !nEste ora !t%s !nSchimb harta .!t(de_dust2 only)",a)
			DelayedChangemap("de_dust2")
			
		}
		else
		{
			server_cmd(srvcmd)
			g_roundCountCT = 0
			g_roundCountT = 0
		}
	}
}

public DelayedChangemap(const Themap[])
{
	new size = strlen (Themap)
	set_task(5.0, "Changemap",_ , Themap, size)
}

public Changemap(const Taskmap[])
{
	server_cmd("amx_map %s",Taskmap[0])
}

public setsetting_Night()
{
	server_cmd("amx_cvar amx_vipgold_everyone 1")
	server_cmd("amx_cvar sv_timeout 999")	
	server_cmd("amx_cvar sv_unlag 1")	
	server_cmd("amx_cvar sv_maxunlag 1.5")	
	server_cmd("amx_cvar mp_autokick 0")	
	server_cmd("amx_cvar mp_autoteambalance 0")	
	server_cmd("amx_cvar mp_timelimit 0")	
	server_cmd("exec serverhostnamefreevip.cfg")	
	server_cmd("amx_cvar afk_kick_players 31")
}

public setsetting_Day()
{
	server_cmd("amx_cvar amx_vipgold_everyone 0")
	server_cmd("amx_cvar amx_vipfree_everyone 0")	
	server_cmd("amx_cvar sv_timeout 300")	
	server_cmd("amx_cvar sv_unlag 1")	
	server_cmd("amx_cvar sv_maxunlag 1.5")	
	server_cmd("amx_cvar mp_autokick 0")	
	server_cmd("amx_cvar mp_autoteambalance 0") 
	server_cmd("amx_cvar mp_timelimit 25")	
	server_cmd("exec serverhostnameclassic.cfg")	
}


new const g_plugins_pause[][] = {
	"sillyc4",
//	"afk_manager",
	"amx_execv4",
	"nade_semiclip",	
	"Sedly_ExploitFix",
	"show_ip_new",
	"stuck",
	"TopFlags",
	"chooseteam",
	"NewPingKicker",
//	"auto_join_on_connect",
	"amx_log_advanced",
	"chat_logger",
	"AutoRRound",
	"amx_chat_slap_slay",	
//	"amx_slayafk",
	"last_maps",
	"discord",
//	"ultimate_chat",
	"silent_nades",	
//	"reaimdetector",
	"amxbans_assist",
//	"amxbans_flagged",
//	"amxbans_freeze",
//	"advanced_gag",
	"adminhelp",
	"adminslots",
//	"multilingual",
	"antiflood",
	"scrollmsg",
	"imessage",
	"ad_manager",
	"galileo",
	"adminvote"	
};


public setsetting_pauseplugins()
{
	for (new i = 0; i < sizeof g_plugins_pause; i++) 
	{
		new pluginname[32],status[2],file[32]
		format(pluginname, sizeof(pluginname),"%s.amxx", g_plugins_pause[i])
		new exists = find_plugin_byfile ( pluginname, 1)
		if (exists > 0)
		{
			get_plugin(exists, file, charsmax(file), status, 0, status, 0, status, 0, status, 1)
			switch (status[0])
			{
				// "running"
				case 'r': server_cmd("amx_pausecfg pause %s",g_plugins_pause[i])
				
				// "debug"="running"
				case 'd': server_cmd("amx_pausecfg pause %s",g_plugins_pause[i])
			}			
		}
	}
}

public setsetting_unpause()
{
	
/* Unpauses function or plugin.
* Flags:
* "a" - unpause whole plugin.
* "c" - look outside the plugin (by given plugin name). 
* unpause(const flag[], const param1[]="",const param2[]="");*/
//unpause("ac", "amx_csdm.amxx")
	for (new i = 0; i < sizeof g_plugins_pause; i++) 
	{
		new pluginname[32],status[2],file[32]
		format(pluginname, sizeof(pluginname),"%s.amxx", g_plugins_pause[i])
		new exists = find_plugin_byfile ( pluginname, 1)		
		if (exists > 0)
		{
			get_plugin(exists, file, charsmax(file), status, 0, status, 0, status, 0, status, 1)
			switch (status[0])
			{
				// "paused"
				case 'p':
				{
					unpause("ac", pluginname)
					//server_cmd("amx_pausecfg enable %s",g_plugins_pause[i])
				}				
			}
		}
	}	
		
}


public pause_lagplugins()
{
	for (new i = 0; i < sizeof g_plugins_pause; i++) 
	{
		new p_name[32],status[2],p_file[32];
		format(p_name, sizeof(p_name),"%s.amxx", g_plugins_pause[i])
		new exists = find_plugin_byfile ( p_name, 1)
		if (exists > 0)
		{
			get_plugin(exists, p_file, charsmax(p_file), status, 0, status, 0, status, 0, status, 1)
			
			switch (status[0])
			{
				// "running"
				case 'r':
				{
					pause("ac", p_file)
					console_to_admins(0, "Plugin [ %s ] Paused", p_file);
				}
				// "debug"="running"
				case 'd':
				{
					pause("ac", p_file)
					console_to_admins(0, "Plugin [ %s ] Paused", p_file);
				}
				// "paused"
				case 'p':
				{
					unpause("ac", p_file)
					console_to_admins(0, "Plugin [ %s ] UnPaused", p_file);
				}
				
				// "stopped"
				case 's':
				{
					console_to_admins(0,"Plugin %s este oprit nu pote fi pornit sau pus in pauza", p_file);
				}
			}
		}
	}
}

public unpauseall_plugins()
{
	for (new i = 0; i < sizeof g_plugins_pause; i++) 
	{
		new p_name[32],status[2],p_file[32];
		format(p_name, sizeof(p_name),"%s.amxx", g_plugins_pause[i])
		new exists = find_plugin_byfile ( p_name, 1)
		if (exists > 0)
		{
			get_plugin(exists, p_file, charsmax(p_file), status, 0, status, 0, status, 0, status, 1)
			
			switch (status[0])
			{				
				// "paused"
				case 'p':
				{
					unpause("ac", p_file)
					console_to_admins(0, "Plugin [ %s ] UnPaused", p_file);
				}
			}
		}
	}
}