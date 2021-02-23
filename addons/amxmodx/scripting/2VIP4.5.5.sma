//TO DOO: 
//DONE Posibilitate Respawn \\ GOLD only basa + pozitie
//DONE Multi JUmp 
// Adaugare Regenerare \\ GOLD only
//DONE Vipi stralucesc
// Damage DOne x 2 ???
// Damage +10% HE \\ GOLD only
// Munitie infinita \\ GOLD only
//DONE Mesaj de conectare VIP

//version 2.4.3 Added mysql_get_username_safe
//version 4.4.3 Optimaized Menus + Vipsmotd, Removed duble weapons

//Some weapons share ammo types and therefore ammo backpack pools. List
//of ammo types:
//ammo_338magnum  - awp
//ammo_762nato    - scout, ak47, g3sg1
//ammo_556natobox - m249
//ammo_556nato    - famas, m4a1, aug, sg550, galil, sg552
//ammo_buckshot   - m3, xm1014
//ammo_45acp      - usp, ump45, mac10
//ammo_57mm       - fiveseven, p90
//ammo_50ae       - deagle
//ammo_357sig     - p228
//ammo_9mm        - glock, mp5, tmp, elites
//               - hegrenade
//               - flashbang
//               - smokegrenade



/*****************************change list*****************
-- Version 1.4 to version 4.0 
* Added Multi jumpnu
* Added Delay Set healh on respawn so map wont cut the seted healt from before freze
* Added infinit munition
* Added Vip enter announce on chat
* Removed Glow ont Vips Gold (to many complains)
* Removed Respawn for Vip Gold (to many complains)
* Removed infinit munition (to many complains)
-- Version 4.4.3  
 * set_user_health_check added
-- Version 4.4.5  20-06-2020
* Added bomb effects smoke + cylinder
* Added reapi code for faster processing
* Added timeout g_pTime
-- Version 4.5.2  20-06-2020
* Added new cvar_crate funcions from 1.8.3 Amxmodx
* Created cvar's for connecting to db to get acces expiration
* Added config Autoexecconfig to execute own config for this plugin you can find config in (cstrike/addons/amxmodx/configs/plugins/plugin-Vip.cfg)
-- Version 4.5.3  29-06-2020
* Added timeout on menu VIP
* Added tasks ID unique ID
* Added Menu close with Display new Menu
* Code cleanup
-- Version 4.5.4 06-10-2020
* La cerere ORB scoaterea VIP SILVER
		if (containi(sflags, MyVar) != -1)
		{
			//orb a cerut scoaterea VIP silver
			//return 1
			return -1
		}
* La cerere ORB Removed HP advantage double jump
* La cerere ORB Removed double jump
		
-To DO maybe
 * Adaugare Regenerare \\ GOLD only
 * Create map file to disable plugin from cfg
 * Create High Level CMD to add map to disabled map file
 
 -- Version 4.5.5 25-10-2020
 * La cerere ORB Added DubleJump
 
*/



#define DAMAGE_RECIEVED
#include <amxmodx>
#include <amxmisc>
#include <cstrike>
#include <fun>
#include <hamsandwich>
#include <engine>
#include <csx>
#include <fakemeta>
#include <fakemeta_util>
#include <official_base>
#include <unixtime.inc>
#include <sqlx>
#include <reapi>


#define ADMINACCESS ADMIN_CHAT
#define TASKID  6587
#define TASKIDMENU 2000
#define TASKIVIPTXT 3000
#define TASKIDCONNCT 4000
#define TASKIDDROPW 5000
#define MENUGETTASK 6000
#define FREEVIPTASK 4587945
#define TASKIDSCORE 7000
#define TASKIDVIPLIST 8000

new Handle:g_SqlXVIP;
new g_dbPrefix[32];
new pcvar_prefix;


new tbl_admins[33]
new Host[16]
new User[33] 
new Pass[33] 
new Dbase[33] 

new jumpnum[33] = 0
new bool:dojump[33] = false

new const Plugin[] = "VIP plugin"
new const Author[] = "Dunno & UNU"
new const Version[]	= "4.5.3"

new g_pTime;



/* Id of weapons in CS */

#define CSW_P228            1
#define CSW_SCOUT        3
#define CSW_HEGRENADE        4
#define CSW_XM1014        5
#define CSW_C4            6
#define CSW_MAC10        7
#define CSW_AUG            8
#define CSW_SMOKEGRENADE    9
#define CSW_ELITE        10
#define CSW_FIVESEVEN        11
#define CSW_UMP45        12
#define CSW_SG550        13
#define CSW_GALIL        14
#define CSW_FAMAS        15
#define CSW_USP            16
#define CSW_GLOCK18        17
#define CSW_AWP            18
#define CSW_MP5NAVY        19
#define CSW_M249        20
#define CSW_M3            21
#define CSW_M4A1        22
#define CSW_TMP            23
#define CSW_G3SG1        24
#define CSW_FLASHBANG        25
#define CSW_DEAGLE        26
#define CSW_SG552        27
#define CSW_AK47        28
#define CSW_KNIFE        29
#define CSW_P90            30
#define CSW_VEST        31
#define CSW_VESTHELM        32

const GUNS_BITSUM = 1<<CSW_P228 | 1<<CSW_ELITE | 1<<CSW_FIVESEVEN | 1<<CSW_USP | 1<<CSW_GLOCK18 
const SHOTGUNS_BITSUM = 1<<CSW_XM1014 | 1<<CSW_M3 
const SMGS_BITSUM = 1<<CSW_MAC10 | 1<<CSW_UMP45 | 1<<CSW_MP5NAVY | 1<<CSW_TMP | 1<<CSW_P90 
const RIFFLES_BITSUM = 1<<CSW_AUG | 1<<CSW_GALIL | 1<<CSW_FAMAS | 1<<CSW_M249 | 1<<CSW_M4A1 | 1<<CSW_SG552 | 1<<CSW_AK47 
const SNIPERS_BITSUM = 1<<CSW_SCOUT | 1<<CSW_SG550 | 1<<CSW_AWP | 1<<CSW_G3SG1 
const WEAPONS_BITSUM = GUNS_BITSUM | SHOTGUNS_BITSUM | SMGS_BITSUM | RIFFLES_BITSUM | SNIPERS_BITSUM
const NOAMMO_BITSSUM = 1<<CSW_C4 | 1<<CSW_KNIFE | 1<<CSW_VEST | 1<<CSW_VESTHELM  | 1<<CSW_SHIELDGUN
 
const REMOVE_PISTOLS = 1<<CSW_P228 | 1<<CSW_ELITE | 1<<CSW_FIVESEVEN | 1<<CSW_USP | 1<<CSW_GLOCK18

const SOME_WEAPONS_I_WANT =  1 << CSW_C4  |  1 << CSW_KNIFE ;

const ScoreAttrib_PlayerID = 1
#define ScoreAttrib_Flags 2

#define FLAG_SCOREATTRIB_VIP (1<<2)

#define get_team(%0)	( get_offset_int(%0,114) )
#define CT 2


static const COLOR[] = "^x04" //green
static const CONTACT[] = "catalin1bingo@yahoo.com"
new maxplayers
new gmsgSayText
new g_MsgSync
new nKiller
new nKiller_hp
new nHp_add
new nHp_max
new g_awp_active
new g_menu_active
new g_vipgold_everyone
new g_vipfree_everyone
new g_maxjumps
new CurrentRound
new g_usedb_connection

new iOrigin[33][3]
//new g_Timer[33];
new g_TCountTimer[33];

new g_Error[512]

enum scoreAttribFlags ( <<= 1 ) {
    SA_NONE = 0,
    SA_DEAD = 1,
    SA_BOMB,
    SA_VIP
}


#if defined DAMAGE_RECIEVED
	new g_MsgSync2
#endif

#define MAX_PLAYERSVIP             32 + 1

new g_izSpecMode[MAX_PLAYERSVIP]                       = {0, ...}
new g_MsgSyncStuff
new g_MsgSyncStuff2

//new menuid

public plugin_init()
{
	register_plugin(Plugin,Version,Author)
	
	new pcvar = create_cvar("amx_usedb", "0", FCVAR_NONE, "Daca folositi bazadate activati cvarul si completati datele", .has_min = true, .min_val= 0.0, .has_max = true, .max_val = 1.0)
	bind_pcvar_num(pcvar, g_usedb_connection)	
	pcvar = create_cvar("no_awp_active", "0", FCVAR_NONE, "Cvar pentru a bloca Awp la jucatori!", .has_min = true, .min_val= 0.0, .has_max = true, .max_val = 1.0)
	bind_pcvar_num(pcvar, g_awp_active)
	pcvar = create_cvar("menu_active", "1", FCVAR_NONE, "Cvar pentru a porni sau nu meniul vip !", .has_min = true, .min_val= 0.0, .has_max = true, .max_val = 1.0)
	bind_pcvar_num(pcvar, g_menu_active)
	pcvar = create_cvar("amx_vipgold_everyone", "0", FCVAR_NONE, "Cvar pentru a seta VIP free !", .has_min = true, .min_val= 0.0, .has_max = true, .max_val = 1.0)
	bind_pcvar_num(pcvar, g_vipgold_everyone)
	pcvar = create_cvar("amx_vipfree_everyone", "0", FCVAR_NONE, "Cvar pentru a seta vip free varianta usoara! ", .has_min = true, .min_val= 0.0, .has_max = true, .max_val = 1.0)
	bind_pcvar_num(pcvar, g_vipfree_everyone)
	pcvar = create_cvar("amx_maxjumps", "1", FCVAR_NONE, "Cvar pentru a seta numar maxim de sarituri!", .has_min = true, .min_val= 1.0, .has_max = true, .max_val = 10.0)
	bind_pcvar_num(pcvar, g_maxjumps)	
	pcvar = create_cvar("amx_menu_timeout", "15", FCVAR_NONE, "Cvar pentru a seta dupa cate secunde meniul nu mai are efect!", .has_min = true, .min_val= 5.0, .has_max = true, .max_val = 100.0)
	bind_pcvar_num(pcvar, g_pTime)
	
	pcvar = create_cvar("amx_vip_table_db", "gsp_160_database", FCVAR_NONE, "Baza de date unde se afla tabelul de unde preia infromatia vip!")
	bind_pcvar_string(pcvar, Dbase, charsmax(Dbase))
	pcvar = create_cvar("amx_vip_table", "_amxadmins", FCVAR_NONE, "Tabel de unde preia infromatia vip!")
	bind_pcvar_string(pcvar, tbl_admins, charsmax(tbl_admins))
	pcvar = create_cvar("amx_vip_table_host", "116.203.131.166", FCVAR_NONE, "Ip-ul unde este hostul bazei de date!")
	bind_pcvar_string(pcvar, Host, charsmax(Host))
	pcvar = create_cvar("amx_vip_table_user", "gspuser_160", FCVAR_NONE, "Utilizator folosit la accesarea bazei de date!")
	bind_pcvar_string(pcvar, User, charsmax(User))
	pcvar = create_cvar("amx_vip_table_pass", "doovqay0", FCVAR_NONE, "Parola folosita la accesarea bazei de date!")
	bind_pcvar_string(pcvar, Pass, charsmax(Pass))

	create_cvar("amx_contactinfo", CONTACT, FCVAR_SERVER, "Contact Info for players !")
	create_cvar("amx_vip_silverflags", "w", FCVAR_NONE, "Flag pentru Vip Silver")
	create_cvar("amx_vip_goldflags", "t", FCVAR_NONE, "Flag pentru VIP")
	create_cvar("amx_passadmins", "ne_setat", FCVAR_NONE, "Parola forum admins only")
	create_cvar("amx_passowners", "ne_setat", FCVAR_NONE, "Parola forum Owners only")
	create_cvar("amx_passbanlist", "ne_setat", FCVAR_NONE, "Parola forum Banlist")
	
	
	
	
	register_event("DeathMsg","death_msg","a")
	register_clcmd("awp","HandleCmd")
	register_clcmd("sg550","HandleCmd")
	register_clcmd("g3sg1","HandleCmd")

	maxplayers = get_maxplayers()
	gmsgSayText = get_user_msgid("SayText")
	
	register_clcmd("say", "handle_say")
	register_logevent("LogEvent_RoundStart", 2, "1=Round_Start" )
	register_logevent("Logevent_RoundEnd", 2, "1=Round_End")  
	register_event("TextMsg","Event_RoundRestart","a","2&#Game_w")
	register_event("TextMsg","Event_RoundRestart","a","2&#Game_C")
	register_event("DeathMsg", "hook_death", "a", "1>0")
	register_event("Damage", "on_damage", "b", "2!0", "3=0", "4!0")
	register_event("Damage","DamagedoneEvent","b")
	register_event("WeapPickup", "eWeapPickup", "be", "1=13", "1=18", "1=24" );
	register_event("TextMsg", "iSpecmodeis", "bd", "2&ec_Mod")
	
	RegisterHam(Ham_Spawn,"player","playerSpawn",1)
	
	g_MsgSyncStuff = CreateHudSyncObj()	
	g_MsgSync = CreateHudSyncObj()
#if defined DAMAGE_RECIEVED
	g_MsgSync2 = CreateHudSyncObj()
	g_MsgSyncStuff2 = CreateHudSyncObj()	
#endif 

	set_task(3.0, "PrintTextVip" ,FREEVIPTASK, _, _, "b")
	if(g_usedb_connection)
	{
		pcvar_prefix = get_cvar_pointer("amx_sql_prefix");
		get_pcvar_string(pcvar_prefix, g_dbPrefix, charsmax(g_dbPrefix));	
		set_task(1.0, "MySql_Init")	
	}
	AutoExecConfig(true)
}


public PrintTextVip()
{
	if (g_vipgold_everyone)
	{
		set_hudmessage(255, 0, 0, 0.45, 0.85, 2, 0.1, 4.0, 0.1, 0.1, -1)
		show_hudmessage(0, "Free == VIP")
	}
}

public iSpecmodeis(id)
{
	new sData[12]
	read_data(2, sData, 11)
	g_izSpecMode[id] = (sData[10] == '4')	
	return PLUGIN_CONTINUE
} 


public on_damage(id)
{
	

	new attacker = get_user_attacker(id)
	new damage 
	
#if defined DAMAGE_RECIEVED	
	if (is_user_connected(id) && (vip_check(id) != -1 ))
	{
		damage = read_data(2)
		set_hudmessage(255, 0, 0, 0.45, 0.50, 2, 0.1, 4.0, 0.1, 0.1, -1)
		ShowSyncHudMsg(id, g_MsgSync2, "%i^n", damage)
		
	}	
#endif

	if ( is_user_connected(attacker) && (vip_check(attacker) != -1))
	{
		damage = read_data(2)
		set_hudmessage(0, 100, 200, -1.0, 0.55, 2, 0.1, 4.0, 0.02, 0.02, -1)		
		ShowSyncHudMsg(attacker, g_MsgSync, "%i^n", damage)		
	}	

}

//BLOCK TEAM MENU WHILE ALIVE
/*
public cmdChooseTeam(id)
{
	if (is_user_alive( id ))
	{
		if (cs_get_user_team(id) == CS_TEAM_T || cs_get_user_team(id) == CS_TEAM_CT)
		{
			chat_color_all(id,"!g[!y:::!tOFFICIAL!y:::!g] You don't have access to choose team while alive!")
			return PLUGIN_HANDLED;
		}
	}
	return PLUGIN_CONTINUE;
}
*/



public DamagedoneEvent(id)
{
	
	new weapon, hitpoint, attacker = get_user_attacker(id,weapon,hitpoint)
	new dmgdone = read_data(2)
	new jucatori[32], numar, jucatorul, flagsjucator
	get_players(jucatori, numar, "b")
	
	new AttName[33], VictimAtt[33]
	get_user_name(attacker, AttName, 32)
	get_user_name(id, VictimAtt, 32)
	
	for(new j = 1; j < numar; j++)
	{
		jucatorul = jucatori[j]
		flagsjucator = get_user_flags(jucatorul)
#if defined DAMAGE_RECIEVED
		if ((pev(jucatorul,pev_iuser2) == id) && (dmgdone > 0) && (g_izSpecMode[jucatorul] && (flagsjucator & ADMIN_KICK)))
		{
			set_hudmessage(255, 0, 0, -0.89, 0.19, 2, 0.1, 4.0, 0.1, 0.1, -1)
			ShowSyncHudMsg(jucatorul, g_MsgSyncStuff2, "%s [%i]^n",AttName, dmgdone)
		}
#endif

		if ((pev(jucatorul,pev_iuser2) == attacker) && (dmgdone > 0) && (g_izSpecMode[jucatorul] && (flagsjucator & ADMIN_KICK)))
		{
			
			set_hudmessage(0, 100, 200, -0.89, 0.17, 2, 0.1, 4.0, 0.02, 0.02, -1)
			ShowSyncHudMsg(jucatorul, g_MsgSyncStuff, "%s [%i]^n",VictimAtt, dmgdone)
		}
	}	
	
	
	if(attacker<=maxplayers && is_user_alive(attacker) && attacker!=id)
	if (get_user_flags(attacker) & ADMIN_LEVEL_H) 
	{		
		new money = dmgdone * 3 //get_pcvar_num(mpd)		
		if(hitpoint==1) money += 300 //get_pcvar_num(mhb)
		cs_set_user_money(attacker,cs_get_user_money(attacker) + money)
	}
	else
	{
		if (attacker<=maxplayers && is_user_alive(attacker) && attacker!=id && g_vipgold_everyone)
		{
			new money = dmgdone * 3 //get_pcvar_num(mpd)
			if(hitpoint==1) money += 300 //get_pcvar_num(mhb)
			cs_set_user_money(attacker,cs_get_user_money(attacker) + money)
		}	
	}
}

public death_msg()
{
	new data1 = read_data(1)
	new data2 = read_data(2)
	if(data1<=maxplayers && data1 && data1!=data2)
	{
		new result = vip_check(data1)
		if (result == 0)
		{
			cs_set_user_money(data1,cs_get_user_money(data1) + 250) //*get_pcvar_num(mkb) - 300)
		}
		else
		{
			if (g_vipgold_everyone)
			{
				cs_set_user_money(data1,cs_get_user_money(data1) + 250)//get_pcvar_num(mkb) - 300)
			}
		}
	}	
}

public LogEvent_RoundStart()
{
	CurrentRound++;	
	if(g_vipgold_everyone && g_vipfree_everyone)
		server_cmd("amx_cvar amx_vipfree_everyone 0")
}


public Logevent_RoundEnd() 
{
	new jucatoriend[32], numarend,jucatorulend
	get_players(jucatoriend, numarend, "h")	
	for(new id = 0; id < numarend; id++)
	{
		jucatorulend = jucatoriend[id]
		if(task_exists(jucatorulend) || task_exists(MENUGETTASK + jucatorulend) || /*task_exists(TASKIDCONNCT + jucatorulend) || task_exists(TASKIVIPTXT + jucatorulend) ||*/ task_exists(TASKIDMENU + jucatorulend) || task_exists(TASKIDDROPW + jucatorulend) || task_exists(TASKIDVIPLIST + jucatorulend))
		{			
			remove_task(jucatorulend)	
			remove_task(MENUGETTASK + jucatorulend)
			//remove_task(TASKIDCONNCT + jucatorulend)
			//remove_task(TASKIVIPTXT + jucatorulend)
			remove_task(TASKIDMENU + jucatorulend)
			remove_task(TASKIDDROPW + jucatorulend)
			remove_task(TASKIDVIPLIST + jucatorulend)	
		}
	}
}


public playerSpawn(id)
{
	//new hpawp, hpknife
	new hpmap = hpmapcheck()
	if(!is_user_alive(id))
		return PLUGIN_HANDLED;
	if(!is_valid_ent(id))
		return PLUGIN_HANDLED;		
	new result = vip_check(id)
	//hpawp =  100 //get_pcvar_num(hpawpadvatage)
	//hpknife = 35 //get_pcvar_num(hpknifeadvatage)
			
// hpmap:  3 = deagle, 2=awp,  0 =de_ bomb maps, 1=35hp
// result 1=vip silevr, 0=vip gold, -1= normal player 2= free gold 3=free vip

	switch (hpmap)
	{
		case 0:{
			switch (result){
				case 0:{
					set_task(1.0, "setscoreboarbvip" ,TASKIDSCORE + id)				
					
					nadecheck(id);				

					rg_give_item(id, "item_assaultsuit", GT_REPLACE);
					rg_give_item(id, "item_thighpack", GT_REPLACE);
					rg_give_item(id, "weapon_deagle", GT_REPLACE);
					
					if (!g_menu_active)
						return PLUGIN_CONTINUE
					if(CurrentRound >= 3)
					{
						g_TCountTimer[id] = get_cvar_num("amx_menu_timeout");
						//Showrod(id)
						set_task( 1.0, "TaskFunction", TASKIDMENU + id, _, _,"b");
					}
				}
				case 1:{
					nadecheck(id);
					rg_give_item(id, "weapon_deagle", GT_REPLACE);					
				}
				case 2:{
					set_task(1.0, "setscoreboarbvip" ,TASKIDSCORE + id)
					nadecheck(id);					
					rg_give_item(id, "item_assaultsuit", GT_REPLACE);
					rg_give_item(id, "item_thighpack", GT_REPLACE);
					rg_give_item(id, "weapon_deagle", GT_REPLACE);
					if (!g_menu_active)
						return PLUGIN_CONTINUE
					if(CurrentRound >= 3)
					{
						g_TCountTimer[id] = get_cvar_num("amx_menu_timeout");
						//Showrod(id)
						set_task( 1.0, "TaskFunction", TASKIDMENU + id, _, _,"b");
					}
				}
				case 3:{
					nadecheck(id);
					rg_give_item(id, "weapon_deagle", GT_REPLACE);					
				}
				
			}			
		}
		case 1:{
			switch (result)
			{
				case 0,2:{
					// delayed_Hp_set(id, hpknife)
					rg_give_item(id, "item_assaultsuit", GT_REPLACE);
				}
			}
		}
		case 2:{
			switch (result)
			{
				case 0,2:{
					// delayed_Hp_set(id, hpawp)
					rg_give_item(id, "item_assaultsuit", GT_REPLACE);
					rg_give_item(id, "weapon_deagle", GT_REPLACE);
					rg_give_item(id, "weapon_awp", GT_REPLACE);	
				}		
			}
		}
		case 3:{
			switch (result)
			{
				case 0,2:{
					rg_give_item(id, "item_assaultsuit", GT_REPLACE);
					rg_give_item(id, "weapon_deagle", GT_REPLACE);					
				}				
			}
		}
	}
	new Weapons[32] 
	new numWeapons, i, weapon
	new weapname[50];
	get_user_weapons(id, Weapons, numWeapons)
	
	for (i=0; i<numWeapons; i++) 
	{
		weapon = Weapons[i]
		if (!(( 1 << weapon ) & NOAMMO_BITSSUM )){
			new weaponRgName[50]			
			rg_get_weapon_info(weapon, WI_NAME, weaponRgName, 49);			
			rg_set_user_bpammo(id, WeaponIdType:get_weaponid(weaponRgName), rg_get_weapon_info(weapon, WI_MAX_ROUNDS))
		}
		// result 1=vip silevr, 0=vip gold, -1= normal player 2= free gold 3=free vip
		switch (result){
			case 0,1,2,3:{
				if( ( 1 << weapon ) & REMOVE_PISTOLS ){
					get_weaponname(weapon, weapname, 49);
					rg_drop_item(id, weapname)
				}
			}
		}		
	}		
	return PLUGIN_CONTINUE
}
/*
public delayed_Hp_set(id, nHp) 

{
	new Data[ 7 ];
	Data[ 0 ] = id;
	Data[ 1 ] = nHp;	
	set_task(3.0, "delayed_set_user_health" , _ , Data , sizeof( Data ) );
}

public delayed_set_user_health(Data[])
{
	new playerid = Data[0]
	if (!is_user_connected(playerid) && !is_valid_ent(playerid))
		return PLUGIN_HANDLED
	
	set_user_health_check(playerid, Data[1])
	new name[32];
	get_user_name(playerid, name, sizeof name - 1);
	chat_color_all(playerid,"!g[!y:::!tOFFICIAL!y:::!g] !t[!yVIP!t] !g%s !tYour HP set to !y%d !g!",name,Data[1])
	return PLUGIN_CONTINUE
}
*/

public set_user_health_check(id,hphealth)
{
	if (!is_user_connected(id))
		return PLUGIN_HANDLED
	if (!is_valid_ent(id))
		return PLUGIN_HANDLED

	set_user_health(id, hphealth)
	
	return PLUGIN_CONTINUE
}

public Event_RoundRestart()
{
	CurrentRound=0
}
public hook_death()
{	
	new nMortul = read_data(2)	
	get_user_origin( nMortul, iOrigin[nMortul], 0)
	iOrigin[nMortul][2] += 50

	new hpmap, hpawp, hpknife 
	//Killer id
	nKiller = read_data(1)
	
	new data5 = read_data(5)
	new data3 = read_data(3)
	
	nHp_max = 100 //get_pcvar_num (health_max)
	
	switch (data3) {
		case 1:{
			switch (data5) {
				case 0:{ nHp_add = 15; }
			}		
		}
		default:{
			nHp_add = 10;
		}
	}
	
	
	new result = vip_check(nKiller)
	if ( result != 0  && result != 2)
		return

	hpmap = hpmapcheck()
	hpawp = 100 //get_pcvar_num(hpawpadvatage)
	hpknife = 35 //get_pcvar_num(hpknifeadvatage)	
	switch (result)	{
		case 0,2:{
			switch (hpmap){
				case 1:{ nHp_max = hpknife; }
				case 2:{ nHp_max = hpawp; }
			}
			nKiller_hp = get_user_health(nKiller)
			nKiller_hp += nHp_add
			// Maximum HP check
			if (nKiller_hp > nHp_max) nKiller_hp = nHp_max
			set_user_health_check(nKiller, nKiller_hp)
			// Hud message "Healed +10/+15 hp"
			set_hudmessage(0, 255, 0, -1.0, 0.15, 0, 1.0, 1.0, 0.1, 0.1, -1)
			show_hudmessage(nKiller, "Healed +%d hp", nHp_add)			
		}
		default :{return;}
	}
	// Screen fading		
	message_begin(MSG_ONE, get_user_msgid("ScreenFade"), {0,0,0}, nKiller)
	write_short(1<<10)
	write_short(1<<10)
	write_short(0x0000)
	write_byte(0)
	write_byte(0)
	write_byte(200)
	write_byte(75)
	message_end()	
}

public Showrod(id)
{
	if(!is_user_alive(id))
		return 1;
	new result = vip_check(id)
	new menu, dataid[9];
	dataid[0] = id
	
	new szMenu[53];
	formatex( szMenu, charsmax(szMenu), "\r[\dMenu\r] \yFree VIP Guns Time Left \r[\d%i\r]", g_TCountTimer[id] )
	
	
	switch (result)
	{
		case 0,2:{
			switch(cs_get_user_team(id))
			{
				case CS_TEAM_T:
				{
					menu = menu_create(szMenu, "Ammunition");
					menu_additem menu, "M4A1+Deagle+Set grenade", "0";
					menu_additem menu, "AK47+Deagle+Set grenade", "1";
					menu_additem menu, "Awp+Deagle+Set grenade", "2";
				}
				case CS_TEAM_CT:
				{
					menu = menu_create(szMenu, "Ammunition");
					menu_additem menu, "M4a1+Deagle+Set grenade", "0";
					menu_additem menu, "AK47+Deagle+Set grenade", "1";
					menu_additem menu, "Awp+Deagle+Set grenade", "2";
				}
			}	
			menu_display( id, menu, 0);
			menu_setprop( menu, MPROP_EXIT, MEXIT_ALL )			
		}
	}
	if(!task_exists(TASKIDMENU + id))
	{
		set_task( 1.0, "TaskFunction", TASKIDMENU + id, _, _,"b");
		//log_amx("[VIP Menu TASK] Setting task id : %d ",TASKIDMENU + id)		
	}
	return PLUGIN_CONTINUE
}




public TaskFunction( Taskid )
{
	new id = Taskid - TASKIDMENU
	new menu, keys;
	g_TCountTimer[id]-- ;
	
	new result = vip_check(id)
	
	new szMenu[53];
	
	if( g_TCountTimer[id] <= 0 ) // if for some reason it glitches and gets below zero
	{
		if(get_user_menu(id, menu, keys) > 0)
		{
			formatex( szMenu, charsmax(szMenu), "\r[\dMenu\r] \yMenu Closed \r[\d%i\r]", g_TCountTimer[id] )
			menu_cancel(id)
			#define Keysrod (1<<9)
			new menuid = register_menuid("rod")
			register_menucmd(menuid, Keysrod, "FakeAmmunition")
			show_menu(id,Keysrod,szMenu, 10, "rod");

			g_TCountTimer[id] = 0;
			client_print( id, print_chat, "The timer has reached 0! Vip Menu Closed!" )
		}
		remove_task(TASKIDMENU + id);
	}
	else
	{
		formatex( szMenu, charsmax(szMenu), "\r[\dMenu\r] \yFree VIP Guns Time Left \r[\d%i\r]", g_TCountTimer[id] )
		switch (result)
		{
			case 0,2:{
				switch(cs_get_user_team(id))
				{
					case CS_TEAM_T:
					{
						menu = menu_create(szMenu, "Ammunition");
						menu_additem menu, "M4A1+Deagle+Set grenade", "0";
						menu_additem menu, "AK47+Deagle+Set grenade", "1";
						//menu_additem menu, "Awp+Deagle+Set grenade", "2";
					}
					case CS_TEAM_CT:
					{
						menu = menu_create(szMenu, "Ammunition");
						menu_additem menu, "M4a1+Deagle+Set grenade", "0";
						menu_additem menu, "AK47+Deagle+Set grenade", "1";
						//menu_additem menu, "Awp+Deagle+Set grenade", "2";
					}
				}	
				menu_display( id, menu, 0);
				menu_setprop( menu, MPROP_EXIT, MEXIT_ALL )	
			}
		}
	}		
}


public Ammunition(id, menu, item)
{
	/* Menu:
	* VIP Menu GolD
	* 1. Get M4A+Deagle
	* 2. Get AK47+Deagle
	* 3. Get AWP+Deagle
	* 0. Exit
	*/
		/* Menu:
	* VIP Silver Menu free(dezactivat)
	* 1. Get M4A1+Deagle
	* 2. Get AK47+Deagle
	* 0. Exit
	*/
	
	if(item == MENU_EXIT)
	{
		//remove_task(TASKIDMENU + id);
		new szMenu[53];
		formatex( szMenu, charsmax(szMenu), "\r[\dMenu\r] \yMenu Closed \r[\d%i\r]", g_TCountTimer[id] )
		menu_cancel(id)
		#define Keysrod (1<<9)
		new menuid = register_menuid("rod")
		register_menucmd(menuid, Keysrod, "FakeAmmunition")
		show_menu(id,Keysrod,szMenu, 10, "rod");
		g_TCountTimer[id] = 0;
		//client_print( id, print_chat, "[OFFICIAL] You chose to close the menu !" )
		return PLUGIN_CONTINUE;
	}
	
	new accessx, callback, data[6], szName[64];
	
	menu_item_getinfo(menu, item, accessx, data, charsmax(data), szName, charsmax(szName), callback);
	new key = str_to_num(data);
	
	//DropWeapon(id);	
	new result = vip_check(id)	
	
	switch (result) {
		//Gold VIP + Free GOLD
		case 0,2: {
			switch (key) {
				case 0: {					
					nadecheck(id)
					set_task(0.3, "casem4a1ak47" ,MENUGETTASK + id)							
					client_print(id, print_center, "You Taked Free M4A1 and Deagle")
					remove_task(TASKIDMENU + id);				
				}
				
				case 1: {					
					nadecheck(id)
					set_task(0.3, "caseak47awp" ,MENUGETTASK + id)
					client_print(id, print_center, "You Taked Free AK47 and Deagle")
					remove_task(TASKIDMENU + id);
				}/*
				case 1: {					
					nadecheck(id)	
					set_task(0.3, "casem4a1awp" ,MENUGETTASK + id)					
					client_print(id, print_center, "You Taked Free AWP and Deagle")
					remove_task(TASKIDMENU + id);
				}*/	
				case 9: { 	
				}
			}
		}
		//Free vip silver kinda with menu
		case 3: {
			switch (key) {
				case 0: {					
					give_item(id, "weapon_flashbang")
					give_user_weapon(id , CSW_DEAGLE , 7 , 35 );
					give_user_weapon(id , CSW_M4A1 , 30 , 90 );
					client_print(id, print_center, "You Taked Free M4A1 and Deagle")
					}				
				case 1: {	
					give_item(id, "weapon_flashbang")
					give_user_weapon(id , CSW_DEAGLE , 7 , 35 );
					give_user_weapon(id , CSW_AK47 , 30 , 90 );
					client_print(id, print_center, "You Taked Free Ak47 and Deagle")
				}
			}				
		}
	}
	return PLUGIN_CONTINUE
}

public FakeAmmunition(id, menu, item)
{
	if(item == MENU_EXIT)
		return PLUGIN_CONTINUE;
	
	return PLUGIN_CONTINUE	
}


public HandleCmd(id){
	if (! g_awp_active)
	{
		client_print(id, print_center, "Sniper's are bloked")
		return PLUGIN_CONTINUE
	}
	return PLUGIN_HANDLED
}

public ShowMotd(id)
{
	//show_motd(id, "http://official.ueuo.com/vip.html") 
	show_motd(id, "/addons/amxmodx/configs/vipInfo.txt")
}
public client_authorized(id)
{
	set_task(10.0, "PrintText" ,TASKIVIPTXT + id)
	if(g_usedb_connection)
	{
		set_task(12.0, "playerConnected" ,TASKIDCONNCT + id)	
	}
}

public client_putinserver( id )
{	
	jumpnum[id] = 0
	dojump[id] = false		
	new name[32];
	get_user_name(id, name, sizeof name - 1);	
	new result = vip_check(id)
	//result 1=vip silevr, 0=vip gold, -1= normal player 2= free gold 3=free vip
	switch (result) {
		case 0: {
			chat_color_all(0,"!g[!y:::!tOFFICIAL!y:::!g] !t[!yVIP!t] !g%s !tjoined on the server !g!",name)
		}
		case 1: {
			chat_color_all(0,"!g[!y:::!tOFFICIAL!y:::!g] !t[!yVIP Silver!t] !g%s !tjoined on the server !g!",name)
		}
	}	
}


public setscoreboarbvip(Taskid)
{
	new id = Taskid - TASKIDSCORE
	new mapnamecs[31]
	get_mapname(mapnamecs,31)
	if (containi(mapnamecs,"as_")!=-1)
		return PLUGIN_CONTINUE
	
	message_begin (MSG_ALL, get_user_msgid ( "ScoreAttrib"),_,0); 
	write_byte (id); 
	write_byte (4); 
	message_end();	
	return PLUGIN_CONTINUE	
}



public client_disconnected(id)
{
	remove_task(id)
	remove_task(TASKIDVIPLIST + id)
	remove_task(MENUGETTASK + id)
	remove_task(TASKIDCONNCT + id)
	remove_task(TASKIVIPTXT + id)
	remove_task(TASKIDMENU + id)
	remove_task(TASKIDDROPW + id)
	jumpnum[id] = 0
	dojump[id] = false

}

public PrintText(Taskid)
{
	new id = Taskid - TASKIVIPTXT
	if (id == 0)
		return PLUGIN_CONTINUE
	
	new sMaiorVar[64]
	new sOwnerVar[64]
	new sBanListVar[64]
	get_cvar_string("amx_passadmins", sMaiorVar, charsmax(sMaiorVar))
	get_cvar_string("amx_passowners", sOwnerVar, charsmax(sOwnerVar))
	get_cvar_string("amx_passbanlist", sBanListVar, charsmax(sBanListVar))
	
	new name[32];
	get_user_name(id, name, sizeof name - 1);
	
	chat_color_all(id,"!g[!y:::!tOFFICIAL!y:::!g] Type !y/wantvip !gfor pricing and a detailed list of vip advantages !")
	if (g_vipfree_everyone)
	{
		chat_color_all(id,"!g[!y:::!tOFFICIAL!y:::!g] Welcome !g%s !t this server gives you free Deagle/He/Fb and show damage per shot !g!",name)
	}
	if (access(id, ADMIN_KICK))
	{
		chat_color_admins(id,"!g[!y:::!tOFFICIAL!y:::!g] !yBun venit pe !tOFFICIAL.INDUNGI.RO, !gAcestea sunt parolele de acces pentru FORUM")
		if( contain(sBanListVar, "ne_setat") == -1 )
			chat_color_admins(id,"!g[!y:::!tOFFICIAL!y:::!g] !yBanlist-Forum: !t%s",sBanListVar)		
		chat_color_admins(id,"!g[!y:::!tOFFICIAL!y:::!g] !yStaff-Forum: !t%s",sMaiorVar)
	}
	if (access(id, ADMIN_LEVEL_D))
		if( contain(sOwnerVar, "ne_setat") == -1 )
			chat_color_admins(id,"!g[!y:::!tOFFICIAL!y:::!g] !yHighStaff-Forum: !t%s",sOwnerVar)
	return PLUGIN_CONTINUE	
}

public handle_say(id) {
	new said[192]
	read_args(said,192)
	if ( containi(said, "/vips") != -1 )
		set_task(0.1,"print_viplist",TASKIDVIPLIST + id)
	else 
		if(containi(said, "/wantvip") != -1 || containi(said, "/vip") != -1 || containi(said, "/buyvip") != -1 || containi(said, "/buy") != -1)
			ShowMotd(id)
		
	return PLUGIN_CONTINUE
}

public print_viplist(Taskid) 
{
	new user = Taskid - TASKIDVIPLIST
	new adminnames[33][32]
	new message[256]
	new contactinfo[256], contact[112]
	new id, count, x, len
	
	for(id = 1 ; id <= maxplayers ; id++)
		if(is_user_connected(id))
			if(get_user_flags(id) & ADMIN_LEVEL_H || vip_check(id)==1)
				get_user_name(id, adminnames[count++], 31)
			else
				if (g_vipgold_everyone)
				{
					get_user_name(id, adminnames[count++], 31)
				}
			 

	len = format(message, 255, "%s VIP ONLINE: ",COLOR)
	if(count > 0) {
		for(x = 0 ; x < count ; x++) {
			len += format(message[len], 255-len, "%s%s ", adminnames[x], x < (count-1) ? ", ":"")
			if(len > 96 ) {
				print_message(user, message)
				len = format(message, 255, "%s ",COLOR)
			}
		}
		print_message(user, message)
	}
	else {
		len += format(message[len], 255-len, "No VIP online.")
		print_message(user, message)
	}
	
	get_cvar_string("amx_contactinfo", contact, 63)
	if(contact[0])  {
		format(contactinfo, 111, "%s Contact Server Admin -- %s", COLOR, contact)
		print_message(user, contactinfo)
	}
}

print_message(id, msg[]) {
	message_begin(MSG_ONE, gmsgSayText, {0,0,0}, id)
	write_byte(id)
	write_string(msg)
	message_end()
}

public vip_check(id) 
{
	new vipGoldp_cvar_result = g_vipgold_everyone
	new vipfree_cvar_result = g_vipfree_everyone

	if (is_user_connected(id))
	{
		if(	vipGoldp_cvar_result !=0)
		{
			return 2
		}		
		new nflags = get_user_flags(id)
		new sflags[32]
		get_flags(nflags,sflags,31)
		new MyVar[8]
		new MyVar2[8]
		get_cvar_string("amx_vip_silverflags", MyVar, charsmax(MyVar))
		
		if (containi(sflags, MyVar) != -1)
		{
			//orb a cerut scoaterea VIP silver
			//return 1
			return -1
		}			
		get_cvar_string("amx_vip_goldflags", MyVar2, charsmax(MyVar2))
		if (containi(sflags, MyVar2) != -1)
		{
			return 0
		}
		if(	vipfree_cvar_result !=0)
		{
			return 3
		}		
	}
	return -1
}
public nadecheck(id)
{
	if (!is_user_connected(id) || !is_valid_ent(id))
		return PLUGIN_HANDLED

	rg_give_item(id, "weapon_hegrenade", GT_REPLACE);
	rg_give_item(id, "weapon_flashbang", GT_APPEND);
	rg_give_item(id, "weapon_flashbang", GT_APPEND);
	return PLUGIN_CONTINUE
} 

public casem4a1ak47(Taskid)
{
	new id  = Taskid - MENUGETTASK
	if (!is_user_connected(id) || !is_valid_ent(id))
		return PLUGIN_HANDLED
	
	rg_remove_all_items_x(id);
	nadecheck(id)
	give_user_weapon(id , CSW_M4A1 , 30 , 90 );
	give_user_weapon(id , CSW_DEAGLE , 7 , 35 );
	give_item(id, "item_assaultsuit")
	give_item(id, "item_thighpack")
	return PLUGIN_CONTINUE
}
public caseak47awp(Taskid)
{
	new id  = Taskid - MENUGETTASK
	if (!is_user_connected(id) || !is_valid_ent(id))
		return PLUGIN_HANDLED
	rg_remove_all_items_x(id);
	nadecheck(id)
	give_user_weapon(id , CSW_AK47 , 30 , 90 );
	give_user_weapon(id , CSW_DEAGLE , 7 , 35 );
	give_item(id, "item_assaultsuit")
	give_item(id, "item_thighpack")
	return PLUGIN_CONTINUE
}
public casem4a1awp(Taskid)
{
	new id  = Taskid - MENUGETTASK
	if (!is_user_connected(id) || !is_valid_ent(id))
		return PLUGIN_HANDLED
	
	rg_remove_all_items_x(id);
	nadecheck(id)
	give_user_weapon(id , CSW_AWP , 10 , 30 );
	give_user_weapon(id , CSW_DEAGLE , 7 , 35 );
	give_item(id, "item_assaultsuit")
	give_item(id, "item_thighpack")
	return PLUGIN_CONTINUE
}


public mapcheck()
{
	new mapname[31]
	get_mapname(mapname,31)
	if ((containi(mapname,"awp")!=-1)||(containi(mapname,"35hp")!=-1)||(containi(mapname,"deagle")!=-1) || (containi(mapname,"bycastor")!=-1))
	{
		return 1
	}
	else
	{
		return 0
	}
}


public hpmapcheck()
{
	new mapname[31]
	get_mapname(mapname,31)
	if(containi(mapname,"35hp") != -1)
	{
		return 1;
	}
	if(containi(mapname,"bycastor") != -1 || containi(mapname,"awp") != -1)
	{
		return 2;
	}
	if(containi(mapname,"deagle") != -1)
	{
		return 3;
	}
	if(containi(mapname,"de_") != -1 || containi(mapname,"cs_") != -1 || containi(mapname,"css_") != -1 || containi(mapname,"as_") != -1)
	{
		return 0;
	}
	return -1;
}
public client_PreThink(id)
{
	//result 1=vip silevr, 0=vip gold, -1= normal player 2= free gold 3=free vip
	new result = vip_check(id)
	if(result != 0 && result != 2)
		return PLUGIN_CONTINUE
	
	//Duble jump code
	
	new nbut = get_user_button(id)
	new obut = get_user_oldbutton(id)
	if((nbut & IN_JUMP) && !(get_entity_flags(id) & FL_ONGROUND) && !(obut & IN_JUMP))
	{
		if(jumpnum[id] < g_maxjumps) //max jumps
		{
			dojump[id] = true
			jumpnum[id]++
			return PLUGIN_CONTINUE
		}
	}
	if((nbut & IN_JUMP) && (get_entity_flags(id) & FL_ONGROUND))
	{
		jumpnum[id] = 0
		return PLUGIN_CONTINUE
	}
	
	//END Duble jump code 
	
	if (!g_awp_active)
		return PLUGIN_CONTINUE
	if(!is_user_alive(id)) 
		return PLUGIN_CONTINUE
	new Weapons[32],numWeapons
	get_user_weapons(id, Weapons, numWeapons)
	for (new i=0; i<numWeapons; i++)
	{
		DropWeaponawp( Weapons[i], id )
	}	
	return PLUGIN_CONTINUE
}

public client_PostThink(id)
{
	if(!is_user_alive(id)) return PLUGIN_CONTINUE	
	
	if(dojump[id] == true)
	{
		new Float:velocity[3]	
		entity_get_vector(id,EV_VEC_velocity,velocity)
		velocity[2] = random_float(265.0,285.0)
		entity_set_vector(id,EV_VEC_velocity,velocity)
		dojump[id] = false
		return PLUGIN_CONTINUE
	}
	return PLUGIN_CONTINUE
}

public eWeapPickup( id ) 
{
	if (!g_awp_active)
		return PLUGIN_CONTINUE
	new iParam[2]; iParam[0] = read_data( 1 );
	iParam[1] = id
	set_task( 0.1, "DropWeaponawp", TASKIDDROPW + id, iParam, 2 );	
	return PLUGIN_CONTINUE
}


public DropWeaponawp( const i_Param[], id )
{
	if(id == (TASKIDDROPW + i_Param[1]))
		id = i_Param[1];
	
	new weapname[50];
	weapname = GetWeaponName( i_Param[0] ) //GetWeaponName get awp

	if( is_user_alive( id ) )
	{
		if (weapname[0])
		{
			cs_drop_user_weapon(id, weapname, 0);
			fm_strip_user_gun(id, CSW_AWP);
		}
		if(user_has_weapon(id, CSW_AWP))
			fm_strip_user_gun(id, CSW_AWP);
	}
}

GetWeaponName( i_Weaponid )
{
	new sWeapon[13];
	switch ( i_Weaponid )
	{
		case CSW_AWP   : sWeapon = "weapon_awp";
		case CSW_G3SG1 : sWeapon = "weapon_g3sg1";
		case CSW_SG550 : sWeapon = "weapon_sg550";
    }
	return sWeapon;
}

stock cs_drop_user_weapon( const id, const szWeaponName[]="", const bStrip=0 )
{
	new wEnt = -1 , WeaponId = get_weaponid( szWeaponName );
	const NadeBits = ( ( 1 << CSW_HEGRENADE ) | ( 1 << CSW_FLASHBANG ) | ( 1 << CSW_SMOKEGRENADE ) );
	if(( 0 < WeaponId < 30 ) && is_user_alive( id ) && user_has_weapon( id, WeaponId ))
	{
		if( bStrip > 0 )
		{
			while( ( wEnt = engfunc( EngFunc_FindEntityByString , wEnt , "classname" , szWeaponName ) ) && pev( wEnt , pev_owner ) != id ) {}
			
			if( !wEnt )
				return -1;
			
			ExecuteHamB( Ham_Weapon_RetireWeapon , wEnt);
			
			if( !ExecuteHamB( Ham_RemovePlayerItem , id , wEnt ) )
				return -1;
			
			ExecuteHamB( Ham_Item_Kill , wEnt );

			// this is for 'Grenades'.
			
			if( WeaponId == CSW_C4 )
			{
				cs_set_user_plant( id , 0 , 0 );
				cs_set_user_bpammo( id , CSW_C4 , 0 );
			}
			else if ( NadeBits & ( 1 << WeaponId ) )
				cs_set_user_bpammo(id,WeaponId,0);
		}else
			engclient_cmd( id, "drop", szWeaponName );
	// thanks to Connor here:
		user_has_weapon( id, WeaponId, 0 );
	}
	return wEnt
}

give_user_weapon( index , iWeaponTypeID , iClip=0 , iBPAmmo=0 , szWeapon[]="" , maxchars=0 )
{
	if ( !( CSW_P228 <= iWeaponTypeID <= CSW_P90 ) || ( iClip < 0 ) || ( iBPAmmo < 0 ) || !is_user_alive( index ) )
		return -1;
	if (!is_user_connected(index) || !is_valid_ent(index))
		return PLUGIN_HANDLED
		
	new szWeaponName[ 20 ] , iWeaponEntity , bool:bIsGrenade;
	
	const GrenadeBits = ( ( 1 << CSW_HEGRENADE ) | ( 1 << CSW_FLASHBANG ) | ( 1 << CSW_SMOKEGRENADE ) | ( 1 << CSW_C4 ) );
	
	if ( ( bIsGrenade = bool:!!( GrenadeBits & ( 1 << iWeaponTypeID ) ) ) )
		iClip = clamp( iClip ? iClip : iBPAmmo , 1 );
	
	get_weaponname( iWeaponTypeID , szWeaponName , charsmax( szWeaponName ) );
	
	if ( ( iWeaponEntity = user_has_weapon( index , iWeaponTypeID ) ? find_ent_by_owner( -1 , szWeaponName , index ) : rg_give_item(index , szWeaponName , GT_REPLACE) ) > 0 )
	{
		if ( iWeaponTypeID != CSW_KNIFE )
		{
			if ( iClip && !bIsGrenade )
				cs_set_weapon_ammo( iWeaponEntity , iClip );
		
			if ( iWeaponTypeID == CSW_C4 ) 
				cs_set_user_plant( index , 1 , 1 );
			else
			{
				new weaponRgName[50]
				rg_get_weapon_info(iWeaponTypeID, WI_NAME, weaponRgName, 49);				
				rg_set_user_bpammo(index, WeaponIdType:get_weaponid(weaponRgName), rg_get_weapon_info(iWeaponTypeID, WI_MAX_ROUNDS))
				//cs_set_user_bpammo( index , iWeaponTypeID , bIsGrenade ? iClip : iBPAmmo );
			}
		}
		
		if ( maxchars )
			copy( szWeapon , maxchars , szWeaponName[7] );
	}
	
	return iWeaponEntity;
}

stock Fade(index,red,green,blue,alpha)
{
	message_begin(MSG_ONE,get_user_msgid("ScreenFade"),{0,0,0},index);
	write_short(1<<10);
	write_short(1<<10);
	write_short(1<<12);
	write_byte(red);
	write_byte(green);
	write_byte(blue);
	write_byte(alpha);
	message_end();
}

public playerConnected(taskid) 
{
	new id = taskid - TASKIDCONNCT
	if (!g_SqlXVIP)
		return PLUGIN_CONTINUE
	new pqueryinfo[1024],datainfo2[2]
	new szString[32]
	if(is_user_connected(id) && (get_user_flags(id) && (ADMIN_LEVEL_H || ADMIN_KICK)))
	{
		mysql_get_username_safe(id, szString, 31)
		formatex(pqueryinfo, charsmax(pqueryinfo), "SELECT `id`,`username`,`nickname`,`created`,`expired` FROM `%s%s` WHERE (`nickname` = '%s')",g_dbPrefix, tbl_admins, szString)
		datainfo2[0] = id

		SQL_ThreadQuery(g_SqlXVIP, "_playerConnected", pqueryinfo, datainfo2, 2)
	}
	return PLUGIN_CONTINUE
}


public _playerConnected(failstate, Handle:query, error[], errnum, data[], size) {
	
	if (failstate)
	{
		new szQuery[256]
		MySqlX_ThreadError( szQuery, error, errnum, failstate, 63 )
		return PLUGIN_CONTINUE
	}
	
	if(!SQL_NumResults(query))
	{		
		return PLUGIN_CONTINUE
	}
	new usernmd[33],nicknmd[33]
	new idplinfo = data[0]
	new CreatedAcces = SQL_ReadResult(query, 3)
	new expird = SQL_ReadResult(query, 4)
	SQL_ReadResult(query, 1, usernmd, 32)
	SQL_ReadResult(query, 2, nicknmd, 32)
	new  iYear , iMonth , iDay , iHour , iMinute , iSecond;
	new  iYearexp , iMonthexp , iDayexp , iHourexp , iMinuteexp , iSecondexp;
	
	UnixToTime( CreatedAcces , iYear , iMonth , iDay , iHour , iMinute , iSecond );
	if(get_user_flags(idplinfo) && ADMIN_KICK)
		chat_color_all(idplinfo,"!g[!y:::!tOFFICIAL!y:::!g] !y Welcome %s you are admin from : !g%02d-%02d-%02d   %02d:%02d:%02d !",nicknmd, iDay, iMonth, iYear , iHour , iMinute , iSecond)
	else
		if(get_user_flags(idplinfo) && ADMIN_LEVEL_H)
			chat_color_all(idplinfo,"!g[!y:::!tOFFICIAL!y:::!g] !y Welcome %s you are VIP from : !g%02d-%02d-%02d   %02d:%02d:%02d !",nicknmd, iDay, iMonth, iYear , iHour , iMinute , iSecond)
		else
			return PLUGIN_CONTINUE
	
	if (expird != 0)
	{
		UnixToTime( expird , iYearexp , iMonthexp , iDayexp , iHourexp , iMinuteexp , iSecondexp );
		chat_color_all(idplinfo,"!g[!y:::!tOFFICIAL!y:::!g] !y Your acces expires on: !t%02d-%02d-%02d   %02d:%02d:%02d !", iDayexp, iMonthexp, iYearexp , iHourexp , iMinuteexp , iSecondexp)
	}
	else
		chat_color_all(idplinfo,"!g[!y:::!tOFFICIAL!y:::!g] !y Your acces expires on: !tNOEXPIRATION !")
	
	return PLUGIN_CONTINUE
}


MySqlX_ThreadError(szQuery[], error[], errnum, failstate, id)
{
	if (failstate == TQUERY_CONNECT_FAILED)
	{
		log_amx("[VIP PLUGIN] Connection failed!")
	}
	else if (failstate == TQUERY_QUERY_FAILED)
	{
		log_amx("[VIP PLUGIN] Query failed")
	}
	log_amx("[VIP PLUGIN] Threaded Query Error, Place: %d", id)
	log_amx("[VIP PLUGIN] Message: %s (%d)", error, errnum)
	log_amx("[VIP PLUGIN] Query statement: %s", szQuery)
}


public MySql_Init()
{
	if(g_usedb_connection)
	{
		SQL_SetAffinity("mysql")
		g_SqlXVIP = SQL_MakeDbTuple(Host, User, Pass, Dbase)
		new ErrorCode,Handle:temp  = SQL_Connect(g_SqlXVIP,ErrorCode,g_Error,charsmax(g_Error))	
		if(temp==Empty_Handle)
		{
			server_print("[VIP PLUGIN] Cant connect tu Database", g_Error)
		}
		SQL_FreeHandle(temp);
	}
	
	
}

/*********    mysql escape functions     ************/
mysql_escape_string(const source[],dest[],len)
{
	copy(dest, len, source);
	replace_all(dest,len,"*"," ");
	replace_all(dest,len,"＆"," ");
	replace_all(dest,len,"＃"," ");
	replace_all(dest,len,"\\","\\\\");
	replace_all(dest,len,"\0","\\0");
	replace_all(dest,len,"\n","\\n");
	replace_all(dest,len,"\r","\\r");
	replace_all(dest,len,"\x1a","\Z");
	replace_all(dest,len,"'","\'");
	replace_all(dest,len,"^"","\^"");
}


mysql_get_username_safe(id,dest[],len)
{
	len = 191
	new name[32]
	get_user_name(id,name,31)
	mysql_escape_string(name,dest,len)
}


public MySql_Disconnect()
{
	if(g_usedb_connection)
	{
		SQL_FreeHandle(g_SqlXVIP);	
	}
}

public plugin_end() {
	g_SqlXVIP = Empty_Handle;
}


//Work out c4 rmoval on remove all items and knife
public rg_remove_all_items_x(id)
{
	static iWeapons[ 32 ], iNum, i;
	iNum = 0;
	get_user_weapons( id, iWeapons, iNum );
	new wname[33]
	new weaponx
	for( i = 0; i < iNum; i++ )
	{
		weaponx = iWeapons[i]
		 // If this weapon we are currently parsing is contained in SOME_WEAPONS_I_WANT bitsum then:
		if (!(( 1 << weaponx ) & NOAMMO_BITSSUM ))
		{
			get_weaponname(iWeapons[ i ], wname, charsmax( wname ));
			rg_remove_item(id, wname, true);
		}
	}	
	
}