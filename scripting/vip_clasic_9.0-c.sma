#include amxmodx
#include amxmisc
#include cstrike
#include fun
#include hamsandwich
#include engine
#include fakemeta
#include csx
	#if AMXX_VERSION_NUM < 183
#include colorchat
	#endif

#define p. "VIP Clasic"
#define v. "9.0-c"
#define a. "Jică Măcelaru'"

#define VIP_FLAG "t"

new const Float: g_flCoords[][] = 
{
	{ 0.50, 0.40 },
	{ 0.56, 0.44 },
	{ 0.60, 0.50 },
	{ 0.56, 0.56 },
	{ 0.50, 0.60 },
	{ 0.44, 0.56 },
	{ 0.40, 0.50 },
	{ 0.44, 0.44 }
};

new const g_szBeginning[] = "Membrii VIP";

new g_Cvar[30],
	g_Round[33] = 0,
	g_JumpNum[33], bool:g_DoJump[33],
	g_iPosition[33], g_iSize,
	g_szMessage[256], SyncHudMessage,
	g_VipConfig[] = "vipConfig.cfg",
	g_VipMaps[] = "vipMaps.ini",
	g_File1[128], g_File2[128], 
	bool:g_Use[33],
	bool:g_Menu[33],
	o, m, s;

enum
{
	Primary = 1,
	Secondary,
	Knife,
	Grenades,
	C4
};

public plugin_init()
{
	register_plugin p., v., a.;

	register_clcmd "say", "sayCommand";
	register_clcmd "say_team", "sayCommand";
	
	g_Cvar[0] = register_cvar("vip_mode", "1");
	g_Cvar[1] = register_cvar("vip_tag", "VIP");
	g_Cvar[2] = register_cvar("vip_start_hp", "150");
	g_Cvar[3] = register_cvar("vip_start_ap", "150");
	g_Cvar[4] = register_cvar("vip_start_money", "1000");
	g_Cvar[5] = register_cvar("vip_jump", "1");
	g_Cvar[6] = register_cvar("vip_hp_kill", "5");
	g_Cvar[7] = register_cvar("vip_ap_kill", "5");
	g_Cvar[8] = register_cvar("vip_hp_hs", "10");	
	g_Cvar[9] = register_cvar("vip_ap_hs", "10");
	g_Cvar[10] = register_cvar("vip_hp_kill_knife", "15");	
	g_Cvar[11] = register_cvar("vip_ap_kill_knife", "15");
	g_Cvar[12] = register_cvar("vip_hp_hs_knife", "20");
	g_Cvar[13] = register_cvar("vip_ap_hs_knife", "20");
	g_Cvar[14] = register_cvar("vip_bulletdmg", "1");
	g_Cvar[16] = register_cvar("vip_in_out", "1");
	g_Cvar[17] = register_cvar("vip_show_chat", "1");
	g_Cvar[18] = register_cvar("vip_show_hud", "1");
	g_Cvar[19] = register_cvar("vip_max_hp", "200");
	g_Cvar[20] = register_cvar("vip_max_ap", "200");
	g_Cvar[21] = register_cvar("vip_parachute", "1");
	g_Cvar[22] = register_cvar("vip_money_kill", "400");
	g_Cvar[23] = register_cvar("vip_money_hs", "600");
	g_Cvar[24] = register_cvar("vip_bulletdmg_mode", "1");
	g_Cvar[25] = register_cvar("vip_tab", "1");
	g_Cvar[26] = register_cvar("vip_defusekit", "1");
	g_Cvar[27] = register_cvar("vip_free", "1");
	g_Cvar[28] = register_cvar("vip_free_start", "22");
	g_Cvar[29] = register_cvar("vip_free_end", "08");

	set_task 300.0, "msgInfo", _, _, _, "b";
	set_task 1.0, "showVipsH", _, _, _, "b", 0;
	set_task 1.0, "GiveVIP" ,_,_,_, "b";
	
	RegisterHam Ham_Spawn, "player", "Spawn", 1;
	
	SyncHudMessage = CreateHudSyncObj();
	g_iSize = sizeof(g_flCoords);
	
	register_event "HLTV", "newRound", "a", "1=0", "2=0";
	register_event "ResetHUD", "resetModel", "b";
	register_event "ResetHUD", "vipTab", "be";
}

public plugin_cfg()
{	
	new File[64];
	
	get_configsdir File, charsmax(File);
	formatex g_File1, charsmax(g_File1), "%s/%s", File, g_VipConfig;
	formatex g_File2, charsmax(g_File2), "%s/%s", File, g_VipMaps;
	
	if(!file_exists(g_File1))
	{
		write_file(g_File1, "; Plugin VIP creat de Jică Măcelaru' (aka. StefaN@CS, Devil., joker`)");
		write_file(g_File1, "; Plugin publicat pe www.indungi.ro/forum");
		write_file(g_File1, "; https://www.indungi.ro/forum/topic/829508-vip-clasic-90-vip_clasicamxx/");
		write_file(g_File1, "; Suport Counter-Strike 1.6 contra-cost");
		write_file(g_File1, "; Contact");
		write_file(g_File1, "; PM forum: https://www.indungi.ro/forum/profile/349550-jică-măcelaru/");
		write_file(g_File1, "; Steam: https://steamcommunity.com/id/baulesscs161/");
		write_file(g_File1, "; Paypal: paypal.me/sacotia");
		write_file(g_File1, "; Cine considera ca l-am ajutat si ca merit. Multumesc!");
		write_file(g_File1, "");
		write_file(g_File1, "");
		write_file(g_File1, "");
		write_file(g_File1, "/////// Vip Configuration File");
		write_file(g_File1, "");
		write_file(g_File1, "//// VIP Mode");
		write_file(g_File1, "// Setati modul de aparitie al meniului");
		write_file(g_File1, "// 0 - dezactivat");
		write_file(g_File1, "// 1 - meniu prin comanda /vmenu");
		write_file(g_File1, "// 2 - meniu din a 3-a runda");
		write_file(g_File1, "// Default: '1'");
		write_file(g_File1, "vip_mode ^"1^"");
		write_file(g_File1, "");
		write_file(g_File1, "//// VIP Tag");
		write_file(g_File1, "// Setati tagul ce va aparea in chat in mesaje");
		write_file(g_File1, "// Default: 'VIP'");
		write_file(g_File1, "vip_tag ^"VIP^"");
		write_file(g_File1, "");
		write_file(g_File1, "//// VIP Start");
		write_file(g_File1, "// Setati viata, armura si banii cu care va incepe vipul fiecare runda");
		write_file(g_File1, "// La bani setati cu cati bani in plus va incepe");
		write_file(g_File1, "// EX: VIP-ul are 800 bani si la spawn i se vor mai adauga inca 1000");
		write_file(g_File1, "// Default: 150, 150, 1000");
		write_file(g_File1, "vip_start_hp ^"150^"");
		write_file(g_File1, "vip_start_ap ^"150^"");
		write_file(g_File1, "vip_start_money ^"1000^"");
		write_file(g_File1, "");
		write_file(g_File1, "//// VIP HP/AP/BANI per kill/hs");
		write_file(g_File1, "// Setati cat hp/ap/bani sa primeasca vip-ul pe fiecare kill/hs facut in functie de cum este facut kill-ul/hs-ul");
		write_file(g_File1, "// Default: 5, 5, 10, 10, 15, 15, 20, 20, 400, 600");
		write_file(g_File1, "vip_hp_kill ^"5^"");
		write_file(g_File1, "vip_ap_kill ^"5^"");
		write_file(g_File1, "vip_hp_hs ^"10^"");
		write_file(g_File1, "vip_ap_hs ^"10^"");
		write_file(g_File1, "vip_hp_kill_knife ^"15^"");
		write_file(g_File1, "vip_ap_kill_knife ^"15^"");
		write_file(g_File1, "vip_hp_hs_knife ^"20^"");
		write_file(g_File1, "vip_ap_hs_knife ^"20^"");
		write_file(g_File1, "vip_money_kill ^"400^"");
		write_file(g_File1, "vip_money_hs ^"600^"");
		write_file(g_File1, "");
		write_file(g_File1, "//// VIP Max HP/AP");
		write_file(g_File1, "// Setati maximul de hp/ap pe care il poate avea vipul");
		write_file(g_File1, "// Default: 200, 200");
		write_file(g_File1, "vip_max_hp ^"200^"");
		write_file(g_File1, "vip_max_ap ^"200^"");
		write_file(g_File1, "");
		write_file(g_File1, "//// VIP Jump");
		write_file(g_File1, "// Setati cat poate sari vipul");
		write_file(g_File1, "// 0 - dezactivat");
		write_file(g_File1, "// 1 - 2x jump");
		write_file(g_File1, "// 2 - 3x jump");
		write_file(g_File1, "// 3 - 4x jump");
		write_file(g_File1, "// ...");
		write_file(g_File1, "// z - yx jump");
		write_file(g_File1, "Default: 1");
		write_file(g_File1, "vip_jump ^"1^"");
		write_file(g_File1, "");
		write_file(g_File1, "//// VIP Parachute");
		write_file(g_File1, "// Setati daca vip-ul va avea sau nu parasuta");
		write_file(g_File1, "// 0 - dezactivat");
		write_file(g_File1, "// 1 - activat");
		write_file(g_File1, "// Default: 1");
		write_file(g_File1, "vip_parachute ^"1^"");
		write_file(g_File1, "");
		write_file(g_File1, "//// VIP Defuse Kit (Only CT)");
		write_file(g_File1, "// 0 - dezactivat");
		write_file(g_File1, "// 1 - activat");
		write_file(g_File1, "// Default: 1");
		write_file(g_File1, "vip_defusekit ^"1^"");
		write_file(g_File1, "");
		write_file(g_File1, "//// VIP Show");
		write_file(g_File1, "// Setati momentele in care vor fi afisati vipii");
		write_file(g_File1, "// 0 - dezactivat");
		write_file(g_File1, "// 1 - activat");
		write_file(g_File1, "// Cand intra/iese de pe server cu mesaj in chat");
		write_file(g_File1, "// Default: 1");
		write_file(g_File1, "vip_in_out ^"1^"");
		write_file(g_File1, "");
		write_file(g_File1, "// Cand tastezi comanda /vips apare in chat");
		write_file(g_File1, "// Default: 1");
		write_file(g_File1, "vip_show_chat ^"1^"");
		write_file(g_File1, "");
		write_file(g_File1, "// Afisare in hud in coltul stang, sus");
		write_file(g_File1, "// Default: 1");
		write_file(g_File1, "vip_show_hud ^"1^"");
		write_file(g_File1, "");
		write_file(g_File1, "// Afisare in TAB (ScoreBoard)");
		write_file(g_File1, "// Default: 1");
		write_file(g_File1, "vip_tab ^"1^"");
		write_file(g_File1, "");
		write_file(g_File1, "//// VIP Bulletdamage + mode");
		write_file(g_File1, "// Setati daca vipul va avea bulletdamage");
		write_file(g_File1, "// 0 - dezactivat");
		write_file(g_File1, "// 1 - activat");
		write_file(g_File1, "// Default: 1");
		write_file(g_File1, "vip_bulletdmg ^"1^"");
		write_file(g_File1, "");
		write_file(g_File1, "// Setati modul de aparitie al bulletdamageului");
		write_file(g_File1, "// vip_bulletdmg trebuie sa fie setat pe 1");
		write_file(g_File1, "// 0 - dezactivat");
		write_file(g_File1, "// 1 - cerc multi color pentru ambele echipe");
		write_file(g_File1, "// 2 - cerc albastru/rosu (CT - albastru / T - rosu)");
		write_file(g_File1, "// 3 - centru multi color pentru ambele echipe");
		write_file(g_File1, "// 4 - centru albastru/rosu (CT - albastru / T - rosu)");
		write_file(g_File1, "// Default: 1");
		write_file(g_File1, "vip_bulletdmg_mode ^"1^"");
		write_file(g_File1, "");
		write_file(g_File1, "//// VIP Model");
		write_file(g_File1, "// Setati daca vip-ul va avea model sau nu");
		write_file(g_File1, "// 0 - dezactivat");
		write_file(g_File1, "// 1 - activat");
		write_file(g_File1, "// Daca doriti sa activati modelul, setati valoarea 1 si schimbati mapa de 2 ori ca sa se descarce modelele");
		write_file(g_File1, "// Daca doriti sa dezactivati modelul, setati valoarea 0 si schimbati mapa de 2 ori ca sa nu se mai descarce modelele");
		write_file(g_File1, "Default: 1");
		write_file(g_File1, "vip_model ^"1^"");
		write_file(g_File1, "");
		write_file(g_File1, "//// VIP Free");
		write_file(g_File1, "// Setati daca va fi vip free sau nu pe server");
		write_file(g_File1, "// 0 - dezactivat");
		write_file(g_File1, "// 1 - activat");
		write_file(g_File1, "vip_free ^"1^"");
		write_file(g_File1, "");
		write_file(g_File1, "// Setati orele intre care va fi vip free");
		write_file(g_File1, "// Ore disponibile");
		write_file(g_File1, "// 01, 02, 03, 04, 05, 06, 07, 08, 09, 10, 11, 12");
		write_file(g_File1, "// 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 00");
		write_file(g_File1, "// Default: 22, 08");
		write_file(g_File1, "vip_free_start ^"22^"");
		write_file(g_File1, "vip_free_end ^"08^"");
	}
	
	server_cmd "exec %s", g_File1;
	
	if(!file_exists(g_File2))
	{
		write_file(g_File2, ";--------------- | Lista hartilor pe care meniul vipului este restrictionat | ---------------");
		write_file(g_File2, "");
		write_file(g_File2, ";Adaugati mapele una sub alta");
		write_file(g_File2, "");
		write_file(g_File2, "35hp");
		write_file(g_File2, "awp_india");
	}
}

public sayCommand(id)
{
	new Said[10];
	read_args Said, charsmax(Said);
	remove_quotes(Said);
	
	if(equal(Said, "/vips")) showVipsC(id);
	else if(equal(Said, "/vip")) vipInfo(id);
	else if(equal(Said, "/vmenu"))
		if(get_pcvar_num(g_Cvar[0]) == 1)
			if(g_Menu[id] == true)
				vipMenu(id);

	return 0;
}

public client_putinserver(id)
{
	if(!(get_user_flags(id) & read_flags(VIP_FLAG)))
		return 1;
		
	set_task 2.0, "vipIn", id;
	
	g_JumpNum[id] = 0;
	g_DoJump[id] = false;
	g_Round[id] = 0;
	g_Use[id] = false;
	g_Menu[id] = true;
	return 1;
}

	#if AMXX_VERSION_NUM < 183
public client_disconnect(id)
	#else
public client_disconnected(id)
	#endif
{
	if(!(get_user_flags(id) & read_flags(VIP_FLAG)))
		return 1;
		
	set_task 2.0, "vipOut", id;
	
	g_JumpNum[id] = 0;
	g_DoJump[id] = false;
	g_Round[id] = 0;
	g_Use[id] = false;
	
	return 1;
}

public vipInfo(id) show_motd(id, "/addons/amxmodx/configs/vipInfo.txt");

public msgInfo()
{
	new tag[32];
	get_pcvar_string g_Cvar[1], tag, charsmax(tag);

		#if AMXX_VERSION_NUM < 183
	ColorChat 0, GREEN, "^3[%s] ^1Tastati in chat ^4/vip ^1pentru a vedea beneficiile si pretul vip-ului.", tag;
		#else
	client_print_color 0, print_team_default, "^3[%s] ^1Tastați în chat ^4/vip ^1pentru a vedea beneficiile și prețul vip-ului.", tag;
		#endif
}

public plugin_precache()
{
	g_Cvar[15] = register_cvar("vip_model", "1");
	
	if(get_pcvar_num(g_Cvar[15]) == 0)
		return 1;

	precache_model "models/player/vip_tero/vip_tero.mdl";
	precache_model "models/player/vip_ct/vip_ct.mdl";

	return 1;
}

public newRound()
	for(new i = 0; i < 32; i++)
		g_Use[i] = false;

public vipMenu(id)
{
	if(!is_user_alive(id) || !(get_user_flags(id) & read_flags(VIP_FLAG)) || g_Use[id])
		return 1;
	
	new menu;
	switch(cs_get_user_team(id))
	{
		case CS_TEAM_T:
		{
			menu = menu_create("\r[\dMenu\r] \yTerrorists", "Ammunition");
			menu_additem menu, "Ak47+Deagle+Set grenade", "1";
			menu_additem menu, "Galil+Deagle+Set grenade", "2";
			menu_additem menu, "Awp+Deagle+Set grenade", "3";
		}

		case CS_TEAM_CT:
		{
			menu = menu_create("\r[\dMenu\r] \yCounter-Terorists", "Ammunition");
			menu_additem menu, "M4a1+Deagle+Set grenade", "1";
			menu_additem menu, "Famas+Deagle+Set grenade", "2";
			menu_additem menu, "Awp+Deagle+Set grenade", "3";
		}
	}
	menu_display id, menu, 0;
	return 1;
}

public Ammunition(id, menu, item)
{
	if(item == MENU_EXIT)
		return 1;

	new access, callback, data[6], szName[64], tag[32];
	menu_item_getinfo(menu, item, access, data, charsmax(data), szName, charsmax(szName), callback);
	get_pcvar_string g_Cvar[1], tag, charsmax(tag);
	new key = str_to_num(data);
		
	if(cs_get_user_team(id) == CS_TEAM_T)
	{
		switch(key)
		{
			case 1:
			{
				StripWeapons id, Primary;
				StripWeapons id, Secondary;
				give_item id, "weapon_knife";
				give_item id, "weapon_ak47";
				give_item id, "weapon_deagle";
				give_item id, "weapon_hegrenade";
				give_item id, "weapon_flashbang";
				give_item id, "weapon_smokegrenade";
				cs_set_user_bpammo id, CSW_FLASHBANG, 2;
				cs_set_user_bpammo id, CSW_AK47, 90;
				cs_set_user_bpammo id, CSW_DEAGLE, 35;
					#if AMXX_VERSION_NUM < 183
				ColorChat id, GREEN, "^3[%s] ^1Ai ales ^4Ak47^1+^4Deagle^1+^4Set grenade^1.", tag;
					#else
				client_print_color id, print_team_default, "^3[%s] ^1Ai ales ^4Ak47^1+^4Deagle^1+^4Set grenade^1.", tag;
					#endif
				g_Use[id] = true;
			}
			
			case 2:
			{
				StripWeapons id, Primary;
				StripWeapons id, Secondary;
				give_item id, "weapon_knife";
				give_item id, "weapon_galil";
				give_item id, "weapon_deagle";
				give_item id, "weapon_hegrenade";
				give_item id, "weapon_flashbang";
				give_item id, "weapon_smokegrenade";
				cs_set_user_bpammo id, CSW_FLASHBANG, 2;
				cs_set_user_bpammo id, CSW_GALIL, 90;
				cs_set_user_bpammo id, CSW_DEAGLE, 35;
					#if AMXX_VERSION_NUM < 183
				ColorChat id, GREEN, "^3[%s] ^1Ai ales ^4Galil^1+^4Deagle^1+^4Set grenade^1.", tag;
					#else
				client_print_color id, print_team_default, "^3[%s] ^1Ai ales ^4Galil^1+^4Deagle^1+^4Set grenade^1.", tag;
					#endif
				g_Use[id] = true;
			}
			
			case 3:
			{
				StripWeapons id, Primary;
				StripWeapons id, Secondary;
				give_item id, "weapon_knife";
				give_item id, "weapon_awp";
				give_item id, "weapon_deagle";
				give_item id, "weapon_hegrenade";
				give_item id, "weapon_flashbang";
				give_item id, "weapon_smokegrenade";
				cs_set_user_bpammo id, CSW_FLASHBANG, 2;
				cs_set_user_bpammo id, CSW_AWP, 30;
				cs_set_user_bpammo id, CSW_DEAGLE, 35;
					#if AMXX_VERSION_NUM < 183
				ColorChat id, GREEN, "^3[%s] ^1Ai ales ^4Awp^1+^4Deagle^1+^4Set grenade^1.", tag;
					#else
				client_print_color id, print_team_default, "^3[%s] ^1Ai ales ^4Awp^1+^4Deagle^1+^4Set grenade^1.", tag;
					#endif
				g_Use[id] = true;
			}
		}
	}
	
	if(cs_get_user_team(id) == CS_TEAM_CT)
	{
		switch(key)
		{
			case 1:
			{
				StripWeapons id, Primary;
				StripWeapons id, Secondary;
				give_item id, "weapon_knife";
				give_item id, "weapon_m4a1";
				give_item id, "weapon_deagle";
				give_item id, "weapon_hegrenade";
				give_item id, "weapon_flashbang";
				give_item id, "weapon_smokegrenade";
				cs_set_user_bpammo id, CSW_FLASHBANG, 2;
				cs_set_user_bpammo id, CSW_M4A1, 90;
				cs_set_user_bpammo id, CSW_DEAGLE, 35;
					#if AMXX_VERSION_NUM < 183
				ColorChat id, GREEN, "^3[%s] ^1Ai ales ^4M4a1^1+^4Deagle^1+^4Set grenade^1.", tag;
					#else
				client_print_color id, print_team_default, "^3[%s] ^1Ai ales ^4M4a1^1+^4Deagle^1+^4Set grenade^1.", tag;
					#endif
				g_Use[id] = true;
			}
			
			case 2:
			{
				StripWeapons id, Primary;
				StripWeapons id, Secondary;
				give_item id, "weapon_knife";
				give_item id, "weapon_famas";
				give_item id, "weapon_deagle";
				give_item id, "weapon_hegrenade";
				give_item id, "weapon_flashbang";
				give_item id, "weapon_smokegrenade";
				cs_set_user_bpammo id, CSW_FLASHBANG, 2;
				cs_set_user_bpammo id, CSW_FAMAS, 90;
				cs_set_user_bpammo id, CSW_DEAGLE, 35;
					#if AMXX_VERSION_NUM < 183
				ColorChat id, GREEN, "^3[%s] ^1Ai ales ^4Famas^1+^4Deagle^1+^4Set grenade^1.", tag;
					#else
				client_print_color id, print_team_default, "^3[%s] ^1Ai ales ^4Famas^1+^4Deagle^1+^4Set grenade^1.", tag;
					#endif
				g_Use[id] = true;
			}
			
			case 3:
			{
				StripWeapons id, Primary;
				StripWeapons id, Secondary;
				give_item id, "weapon_knife";
				give_item id, "weapon_awp";
				give_item id, "weapon_deagle";
				give_item id, "weapon_hegrenade";
				give_item id, "weapon_flashbang";
				give_item id, "weapon_smokegrenade";
				cs_set_user_bpammo id, CSW_FLASHBANG, 2;
				cs_set_user_bpammo id, CSW_AWP, 30;
				cs_set_user_bpammo id, CSW_DEAGLE, 35;
					#if AMXX_VERSION_NUM < 183
				ColorChat id, GREEN, "^3[%s] ^1Ai ales ^4Awp^1+^4Deagle^1+^4Set grenade^1.", tag;
					#else
				client_print_color id, print_team_default, "^3[%s] ^1Ai ales ^4Awp^1+^4Deagle^1+^4Set grenade^1.", tag;
					#endif
				g_Use[id] = true;
			}      
		}
	}
	
	menu_destroy(menu);
	return 1;  
}

public Spawn(id)
{ 
	if(!is_user_alive(id) || !(get_user_flags(id) & read_flags(VIP_FLAG)))
		return 1;
		
	if(get_pcvar_num(g_Cvar[0]) == 2)
	{
		if(g_Menu[id] == true)
			if(g_Round[id] > 2)
				vipMenu(id);
		
		g_Round[id]++;	
	}

	if(get_pcvar_num(g_Cvar[26]) == 1) if(cs_get_user_team(id) == CS_TEAM_CT) give_item id, "item_thighpack";
	give_item id, "item_assaultsuit";
	set_user_health id, get_pcvar_num(g_Cvar[2]);
	set_user_armor id, get_pcvar_num(g_Cvar[3]);
	cs_set_user_money id, clamp(cs_get_user_money(id) + get_pcvar_num(g_Cvar[4]), 0, 16000);	
	
	new MapName[32],
		szLine[128],
		iLen;
	new Size = file_size(g_File2, 1)	

	get_mapname(MapName, sizeof(MapName));
	for(new i = 0; i < Size; i ++)
	{
		read_file(g_File2, i, szLine, charsmax(szLine), iLen);
		if(equali(MapName, szLine))
			g_Menu[id] = false;
	}
	
	return 1;
}

public GiveVIP()
{
	if(get_pcvar_num(g_Cvar[27]) == 1)
	{
		time(o, m, s);
		
		if(o >= get_pcvar_num(g_Cvar[28]) && o < 24 || o >= 00 && o < get_pcvar_num(g_Cvar[29]))
		{
			for(new i = 1; i <= get_maxplayers(); i++)
				if(is_user_connected(i) || !is_user_bot(i) || !is_user_hltv(i) || !(get_user_flags(i) & read_flags(VIP_FLAG)))
					set_user_flags i, read_flags(VIP_FLAG)

			set_hudmessage random_num(0, 255), random_num(0, 255), random_num(0, 255), -1.0, 0.02, 0, 1.0, 1.0;
			show_hudmessage 0, "EVENT VIP FREE %i:00 - %i:00", get_pcvar_num(g_Cvar[28]), get_pcvar_num(g_Cvar[29]);
		}
		
		if(o == get_pcvar_num(g_Cvar[29]) && m == 00 && s == 00) server_cmd("amx_reloadadmins");
	}
}

public vipIn(id)
{
	if(!(get_user_flags(id) & read_flags(VIP_FLAG)))
		return 1;
		
	if(get_pcvar_num(g_Cvar[16]) == 1)
	{
		new tag[32], name[32];

		get_pcvar_string g_Cvar[1], tag, charsmax(tag); 
		get_user_name id, name, charsmax(name);

			#if AMXX_VERSION_NUM < 183
		ColorChat 0, GREEN, "^3[%s] ^4%s ^1s-a conectat pe server.", tag, name;
			#else
		client_print_color 0, print_team_default, "^3[%s] ^4%s ^1s-a conectat pe server.", tag, name;
			#endif
	}
	
	return 1;
}	

public vipOut(id)
{
	if(!(get_user_flags(id) & read_flags(VIP_FLAG)))
		return 1;
		
	if(get_pcvar_num(g_Cvar[16]) == 1)
	{
		new tag[32], name[32];

		get_pcvar_string g_Cvar[1], tag, charsmax(tag); 
		get_user_name id, name, charsmax(name);
		
			#if AMXX_VERSION_NUM < 183
		ColorChat 0, GREEN, "^3[%s] ^4%s ^1s-a deconectat de pe server.", tag, name;
			#else
		client_print_color 0, print_team_default, "^3[%s] ^4%s ^1s-a deconectat de pe server.", tag, name;
			#endif 
	}
	
	return 1;
}

public client_PreThink(id)
{
	if(!is_user_alive(id) || !(get_user_flags(id) & read_flags(VIP_FLAG))) 
		return 1;
		
	new Float:fallspeed = 100.0 * -1.0;
	new BUTTON = get_user_button(id);
	new OLDBUTON = get_user_oldbutton(id);
	new JUMP_VIP = get_pcvar_num(g_Cvar[5]);

	if((BUTTON & IN_JUMP) && !(get_entity_flags(id) & FL_ONGROUND) && !(OLDBUTON & IN_JUMP))
	{
		if(g_JumpNum[id] < JUMP_VIP)
		{
			g_DoJump[id] = true;
			g_JumpNum[id]++
		}
	}

	if((BUTTON & IN_JUMP) && (get_entity_flags(id) & FL_ONGROUND))
		g_JumpNum[id] = 0;
	
	if(get_pcvar_num(g_Cvar[21]) == 1)
	{
		if(BUTTON & IN_USE) 
		{
			new Float:velocity[3];
			entity_get_vector(id, EV_VEC_velocity, velocity);
		
			if(velocity[2] < 0.0) 
			{
				entity_set_int id, EV_INT_sequence, 3;
				entity_set_int id, EV_INT_gaitsequence, 1;
				entity_set_float id, EV_FL_frame, 1.0;
				entity_set_float id, EV_FL_framerate, 1.0;

				velocity[2] = (velocity[2] + 40.0 < fallspeed) ? velocity[2] + 40.0 : fallspeed;
				entity_set_vector id, EV_VEC_velocity, velocity;
			}
		}
	}
	
	return 0;
}

public client_PostThink(id)
{
	if(!is_user_alive(id)) 
		return 1;
		
	if(g_DoJump[id] == true)
	{
		new Float: velocity[3];
		entity_get_vector id, EV_VEC_velocity, velocity;
		velocity[2] = random_float(265.0, 285.0);
		entity_set_vector id, EV_VEC_velocity, velocity;
		g_DoJump[id] = false;
	}

	return 0;
}

public client_death(killer, victim, weapon, hitplace)
{
	if(!(get_user_flags(killer) & read_flags(VIP_FLAG))) 
		return 1;
		
	new VIP_MAXHP = get_pcvar_num(g_Cvar[19]);
	new VIP_HP = get_user_health(killer);
	new VIP_MAXAP = get_pcvar_num(g_Cvar[20]);
	new VIP_AP = get_user_armor(killer);
	
	if(!(hitplace == HIT_HEAD) && !(weapon == CSW_KNIFE))
	{
		if(VIP_HP + get_pcvar_num(g_Cvar[6]) >= VIP_MAXHP) set_user_health killer, VIP_MAXHP;
		else set_user_health killer, VIP_HP + get_pcvar_num(g_Cvar[6]);
	
		if(VIP_AP + get_pcvar_num(g_Cvar[7]) >= VIP_MAXAP) set_user_armor killer, VIP_MAXAP;
		else set_user_armor killer, VIP_AP + get_pcvar_num(g_Cvar[7]);
		
		cs_set_user_money killer, clamp(cs_get_user_money(killer) - 300 + get_pcvar_num(g_Cvar[22]), 0, 16000);
	}
	
	if(hitplace == HIT_HEAD && !(weapon == CSW_KNIFE))
	{
		if(VIP_HP + get_pcvar_num(g_Cvar[8])>= VIP_MAXHP) set_user_health killer, VIP_MAXHP;
		else set_user_health killer, VIP_HP + get_pcvar_num(g_Cvar[8]);
	
		if(VIP_AP + get_pcvar_num(g_Cvar[9]) >= VIP_MAXAP) set_user_armor killer, VIP_MAXAP;
		else set_user_armor killer, VIP_AP + get_pcvar_num(g_Cvar[9]);
		
		cs_set_user_money killer, clamp(cs_get_user_money(killer) - 300 + get_pcvar_num(g_Cvar[23]), 0, 16000);
	}
	
	if(weapon == CSW_KNIFE && !(hitplace == HIT_HEAD))
	{
		if(VIP_HP + get_pcvar_num(g_Cvar[10]) >= VIP_MAXHP) set_user_health killer, VIP_MAXHP;
		else set_user_health killer, VIP_HP + get_pcvar_num(g_Cvar[10]);
	
		if(VIP_AP + get_pcvar_num(g_Cvar[11]) >= VIP_MAXAP) set_user_armor killer, VIP_MAXAP;
		else set_user_armor killer, VIP_AP + get_pcvar_num(g_Cvar[11]);

		cs_set_user_money killer, clamp(cs_get_user_money(killer) - 300 + get_pcvar_num(g_Cvar[22]), 0, 16000);
	}
	
	if(weapon == CSW_KNIFE && (hitplace == HIT_HEAD))
	{
		if(VIP_HP + get_pcvar_num(g_Cvar[12]) >= VIP_MAXHP) set_user_health killer, VIP_MAXHP;
		else set_user_health killer, VIP_HP + get_pcvar_num(g_Cvar[12]);
	
		if(VIP_AP + get_pcvar_num(g_Cvar[13]) >= VIP_MAXAP) set_user_armor killer, VIP_MAXAP;
		else set_user_armor killer, VIP_AP + get_pcvar_num(g_Cvar[13]);
		
		cs_set_user_money killer, clamp(cs_get_user_money(killer) - 300 + get_pcvar_num(g_Cvar[23]), 0, 16000);
	}

	return 1;
}

public client_damage(iAttacker, iVictim, iDamage)
{
	if(!(get_user_flags(iAttacker) & read_flags(VIP_FLAG)))
		return 1;
		
	if(get_pcvar_num(g_Cvar[14]) == 1)
	{
		if(get_pcvar_num(g_Cvar[24]) == 1)
		{
			if(++g_iPosition[iAttacker] == g_iSize)
				g_iPosition[iAttacker] = 0;

			set_hudmessage random_num(0, 255), random_num(0, 255), random_num(0, 255), Float: g_flCoords[g_iPosition[iAttacker]][0], Float: g_flCoords[g_iPosition[iAttacker]][1], 0, 0.1, 2.5, 0.02, 0.02, -1;
			show_hudmessage iAttacker, "%i", iDamage;
		}
		
		else if(get_pcvar_num(g_Cvar[24]) == 2)
		{
			if(++g_iPosition[iAttacker] == g_iSize)
				g_iPosition[iAttacker] = 0;
			
			if(cs_get_user_team(iAttacker) == CS_TEAM_CT)
			{
				set_hudmessage 42, 170, 255, Float: g_flCoords[g_iPosition[iAttacker]][0], Float: g_flCoords[g_iPosition[iAttacker]][1], 0, 0.1, 2.5, 0.02, 0.02, -1;
				show_hudmessage iAttacker, "%i", iDamage;
			}
			
			else if(cs_get_user_team(iAttacker) == CS_TEAM_T)
			{
				set_hudmessage 200, 0, 0, Float: g_flCoords[g_iPosition[iAttacker]][0], Float: g_flCoords[g_iPosition[iAttacker]][1], 0, 0.1, 2.5, 0.02, 0.02, -1;
				show_hudmessage iAttacker, "%i", iDamage;
			}
		}
		
		else if(get_pcvar_num(g_Cvar[24]) == 3)
		{
			set_hudmessage random_num(0, 255), random_num(0, 255), random_num(0, 255), -1.0, 0.5, 0, 0.0, 0.1, 0.1, 0.1;
			show_hudmessage iAttacker, "%i", iDamage;
		}

		else if(get_pcvar_num(g_Cvar[24]) == 4)
		{
			if(cs_get_user_team(iAttacker) == CS_TEAM_CT)
			{
				set_hudmessage 42, 170, 255, -1.0, 0.5, 0, 0.0, 0.1, 0.1, 0.1;
				show_hudmessage iAttacker, "%i", iDamage;
			}
			
			else if(cs_get_user_team(iAttacker) == CS_TEAM_T)
			{
				set_hudmessage 200, 0, 0, -1.0, 0.5, 0, 0.0, 0.1, 0.1, 0.1;
				show_hudmessage iAttacker, "%i", iDamage;
			}
		}
	}
	
	return 1;
}

public showVipsC(user)
{
	if(get_pcvar_num(g_Cvar[17]) == 1)
	{
		new tag[32];
		get_pcvar_string g_Cvar[1], tag, charsmax(tag);
	
		new vipNames[33][32];
		new message[256];
		new id, count, x, len;

		for(id = 0 ; id <= get_maxplayers() ; id++)
			if(is_user_connected(id))
				if(get_user_flags(id) & read_flags(VIP_FLAG))
					get_user_name id, vipNames[count++], charsmax(vipNames[]);
    
		len = format(message, 255, "^3[%s] ^1VIP-ii online sunt:^4 ", tag);
		if(count > 0)
		{
			for(x = 0 ; x < count ; x++)
			{
				len += format(message[len], 255-len, "%s%s ", vipNames[x], x < (count-1) ? ", ":"");
				if(len > 96)
				{
					print_message(user, message);
					len = format(message, 255, " ");
				}
			}
			
			print_message(user, message);
		}
		
		else
		{
				#if AMXX_VERSION_NUM < 183
			ColorChat user, GREEN, "^3[%s] ^1Nu sunt ^4VIP^1-i online.", tag;
				#else
			client_print_color user, print_team_default, "^3[%s] ^1Nu sunt ^4VIP^1-i online.", tag;
				#endif
		}			
	}
	return 0;  
}

print_message(id, msg[])
{
	message_begin(MSG_ONE, get_user_msgid("SayText"), {0,0,0}, id);
	write_byte(id);
	write_string(msg);
	message_end();
}

public showVipsH()
{
	if(get_pcvar_num(g_Cvar[18]) == 1)
	{
		static iPlayers[32];
		static iPlayersNum;
	
		get_players(iPlayers, iPlayersNum, "ch");
		if(!iPlayersNum)
			return 1;
	
		static iVipsConnected, szVipsNames[128], szName[32];
		formatex(szVipsNames, sizeof (szVipsNames) -1, "");
		iVipsConnected = 0;
	
		static id, i;
		for(i = 0; i < iPlayersNum; i++)
		{
			id = iPlayers[i];
			if(get_user_flags(id) & read_flags(VIP_FLAG))
			{
				get_user_name(id, szName, sizeof(szName) -1);
				
				add(szVipsNames, sizeof(szVipsNames) -1, szName);
				add(szVipsNames, sizeof(szVipsNames) -1, "^n");
				
				iVipsConnected++;
			}	
		}
	
		formatex(g_szMessage, sizeof(g_szMessage) -1, "%s (%i)^n%s", g_szBeginning, iVipsConnected, szVipsNames);
		
		set_hudmessage 25, 255, 25, 0.01, 0.15, 0, 0.0, 1.0, 0.1, 0.1, -1;
		ShowSyncHudMsg 0, SyncHudMessage, g_szMessage;
	}
	return 0;	
}

public resetModel(id, level, cid)
{
	if(!is_user_alive(id) || !(get_user_flags(id) & read_flags(VIP_FLAG)) || get_pcvar_num(g_Cvar[15]) == 0)
	   return 1;	

	new CsTeams:userTeam = cs_get_user_team(id)
	if(userTeam == CS_TEAM_T)
		cs_set_user_model id, "vip_tero";
	else if(userTeam == CS_TEAM_CT)
		cs_set_user_model id, "vip_ct";
	else
		cs_reset_user_model(id);

	return 0;
}

public vipTab(id) 
	if(get_pcvar_num(g_Cvar[25]) == 1)
		set_task 0.5, "setVipTab", id + 6910;

public setVipTab(TaskID)
{
    new id = TaskID - 6910;
    
    if(get_user_flags(id) & read_flags(VIP_FLAG))
    {
        message_begin(MSG_ALL, get_user_msgid("ScoreAttrib"));
        write_byte(id);
        write_byte(4);
        message_end();
    }
    
    return 1;
} 

stock StripWeapons(id, Type, bool: bSwitchIfActive = true)
{
    new iReturn;
   
    if(is_user_alive(id))
    {
        new iEntity, iWeapon;
        while((iWeapon = GetWeaponFromSlot(id, Type, iEntity)) > 0)
            iReturn = ham_strip_user_weapon(id, iWeapon, Type, bSwitchIfActive);
    }
   
    return iReturn;
}

stock GetWeaponFromSlot( id , iSlot , &iEntity )
{
    if ( !( 1 <= iSlot <= 5 ) )
        return 0;
   
    iEntity = 0;
    const m_rgpPlayerItems_Slot0 = 367;
    const m_iId = 43;
    const XO_WEAPONS = 4;
    const XO_PLAYER = 5;
       
    iEntity = get_pdata_cbase( id , m_rgpPlayerItems_Slot0 + iSlot , XO_PLAYER );
   
    return ( iEntity > 0 ) ? get_pdata_int( iEntity , m_iId , XO_WEAPONS ) : 0;
}  
 
stock ham_strip_user_weapon(id, iCswId, iSlot = 0, bool:bSwitchIfActive = true)
{
    new iWeapon
    if( !iSlot )
    {
        static const iWeaponsSlots[] = {
            -1,
            2, //CSW_P228
            -1,
            1, //CSW_SCOUT
            4, //CSW_HEGRENADE
            1, //CSW_XM1014
            5, //CSW_C4
            1, //CSW_MAC10
            1, //CSW_AUG
            4, //CSW_SMOKEGRENADE
            2, //CSW_ELITE
            2, //CSW_FIVESEVEN
            1, //CSW_UMP45
            1, //CSW_SG550
            1, //CSW_GALIL
            1, //CSW_FAMAS
            2, //CSW_USP
            2, //CSW_GLOCK18
            1, //CSW_AWP
            1, //CSW_MP5NAVY
            1, //CSW_M249
            1, //CSW_M3
            1, //CSW_M4A1
            1, //CSW_TMP
            1, //CSW_G3SG1
            4, //CSW_FLASHBANG
            2, //CSW_DEAGLE
            1, //CSW_SG552
            1, //CSW_AK47
            3, //CSW_KNIFE
            1 //CSW_P90
        }
        iSlot = iWeaponsSlots[iCswId]
    }
 
    const XTRA_OFS_PLAYER = 5
    const m_rgpPlayerItems_Slot0 = 367
 
    iWeapon = get_pdata_cbase(id, m_rgpPlayerItems_Slot0 + iSlot, XTRA_OFS_PLAYER)
 
    const XTRA_OFS_WEAPON = 4
    const m_pNext = 42
    const m_iId = 43
 
    while( iWeapon > 0 )
    {
        if( get_pdata_int(iWeapon, m_iId, XTRA_OFS_WEAPON) == iCswId )
        {
            break
        }
        iWeapon = get_pdata_cbase(iWeapon, m_pNext, XTRA_OFS_WEAPON)
    }
 
    if( iWeapon > 0 )
    {
        const m_pActiveItem = 373
        if( bSwitchIfActive && get_pdata_cbase(id, m_pActiveItem, XTRA_OFS_PLAYER) == iWeapon )
        {
            ExecuteHamB(Ham_Weapon_RetireWeapon, iWeapon)
        }
 
        if( ExecuteHamB(Ham_RemovePlayerItem, id, iWeapon) )
        {
            user_has_weapon(id, iCswId, 0)
            ExecuteHamB(Ham_Item_Kill, iWeapon)
            return 1
        }
    }
 
    return 0
}