/*;ADMIN_ALL		0				//Everyone 
;ADMIN_IMMUNITY		1	(1<<0)  	//Flag "a", immunity
;ADMIN_RESERVATION	2	(1<<1)		//Flag "b", reservation
;ADMIN_KICK			4	(1<<2)		//Flag "c", kick
;ADMIN_BAN			8	(1<<3)		//Flag "d", ban
;ADMIN_SLAY			16	(1<<4)		//Flag "e", slay
;ADMIN_MAP			32	(1 etc )		//Flag "f", map change
;ADMIN_CVAR			64			//Flag "g", cvar change
;ADMIN_CFG			128			//Flag "h", config execution
;ADMIN_CHAT			256			//Flag "i", chat
;ADMIN_VOTE			512			//Flag "j", vote
;ADMIN_PASSWORD		1024		//Flag "k", sv_password
;ADMIN_RCON			2048		//Flag "l", rcon access
;ADMIN_LEVEL_A		4096		//Flag "m", custom
;ADMIN_LEVEL_B		8192		//Flag "n", custom
;ADMIN_LEVEL_C		16384		//Flag "o", custom
;ADMIN_LEVEL_D		32768		//Flag "p", custom
;ADMIN_LEVEL_E		65536		//Flag "q", custom
;ADMIN_LEVEL_F		131072		//Flag "r", custom
;ADMIN_LEVEL_G		262144		//Flag "s", custom
;ADMIN_LEVEL_H		524288		//Flag "t", custom
;ADMIN_MENU			1048576		//Flag "u", menus
;ADMIN_ADMIN		16777216 (1<<24)	//Flag "y", default admin
;ADMIN_USER			33554432 (1<<25)	//Flag "z", default user
;ADAUGAT w   		4194304 (1<<22)		//flag "w" custom
;ADAUGAT w			8388608 (1<<23) 	//flag "x" custom
;NEADAUGAT			67108864 (1<<26) 	//flag "?" custom ???
;#define ADMIN_ALL           0       /* everyone 
;#define ADMIN_IMMUNITY      (1<<0)  /* flag "a" 
;#define ADMIN_RESERVATION   (1<<1)  /* flag "b" 
;#define ADMIN_KICK          (1<<2)  /* flag "c" 
;#define ADMIN_BAN           (1<<3)  /* flag "d" 
;#define ADMIN_SLAY          (1<<4)  /* flag "e" 
;#define ADMIN_MAP           (1<<5)  /* flag "f" 
;#define ADMIN_CVAR          (1<<6)  /* flag "g" 
;#define ADMIN_CFG           (1<<7)  /* flag "h" 
;#define ADMIN_CHAT          (1<<8)  /* flag "i" 
;#define ADMIN_VOTE          (1<<9)  /* flag "j" 
;#define ADMIN_PASSWORD      (1<<10) /* flag "k" 
;#define ADMIN_RCON          (1<<11) /* flag "l" 
;#define ADMIN_LEVEL_A       (1<<12) /* flag "m" 
;#define ADMIN_LEVEL_B       (1<<13) /* flag "n" 
;#define ADMIN_LEVEL_C       (1<<14) /* flag "o" 
;#define ADMIN_LEVEL_D       (1<<15) /* flag "p" 
;#define ADMIN_LEVEL_E       (1<<16) /* flag "q"
;#define ADMIN_LEVEL_F       (1<<17) /* flag "r" 
;#define ADMIN_LEVEL_G       (1<<18) /* flag "s" 
;#define ADMIN_LEVEL_H       (1<<19) /* flag "t" 
;#define ADMIN_MENU          (1<<20) /* flag "u" 
;#define ADMIN_BAN_TEMP      (1<<21) /* flag "v" 
;#define ADMIN_ADMIN         (1<<24) /* flag "y" 
;#define ADMIN_USER          (1<<25) /* flag "z" 
*/ 


//"abcdefghijklmnopqrstuv",	//fondator 		biti = 4194303
//"abcdefghijklmnoprstu",  	//manager 		biti = 2031615
//"abcdefhijklmnoprs",   	//owner 		biti = 458687
//"abcdefhijklmnpqrs",    	//co-owner 		biti = 507839
//"bcdefhijmnot",   		//loyality 		biti = 553918
//"bcdefhijmn",   			//Veteran 		biti = 13246
//"bcdefhijm",    			//Maresal 		biti =  5054
//"bcdefhijr",    			//General 		biti = 132030
//"bcdefhijx",    			//night staff 	biti = 8389566  -w = 4194304 = 4195262
//"bcdefhij",     			//Colonel 		biti = 958
//"bcdefij",      			//Maior 		biti = 830
//"bit",          			// vip gold 	biti = 524546
//"biw",          			// vip silver 	biti = 4194562
//"b"            			// slot 		biti = 2



/*=======================================================
Changes 
- V 3.0 
	*Removed VIP Silver / VIP GOLD from list and addaed aside names
TO DO
Add Expiration time for admins and vips






=========================
                  [1] Founder  
  [VIP] GOLD       UNU            
                  [2] Manager 
                  [3] Owner 
                  [4] Co-Owner 
                  [5] Loyalty 
                  [6] Veteran 
                  [7] Maresal 
                  [8] General 
                  [9] Maior 
                    INNA                                    
                  [10] Reserved Name 
  [VIP] Silver      ABC          
                    kNd.Satana 
                       kNd.Satana
  [VIP] GOLD       tralala      
  [VIP] Silver      SeBaN       
=========================
 >>>  Hidden Access
=========================
                        kNd.Satana
                    kNd.Satana
*/


#include <amxmodx>
#include <amxmisc>
#include <official_base>

#define MAX_GROUPS 10

#define SHOWHIDEN	ADMIN_PASSWORD

/*
new const restricted[][] = {
	"Zangetsu cde" 
}
*/

new playerok[44] = 0

new g_groupNames[MAX_GROUPS][] = {
"Founder ",
"Manager",
"Owner",
"Co-Owner",
"Loyalty",
"Veteran",
"Maresal",
"General",
"Maior",
"Reserved Name"
}

new g_groupFlags[MAX_GROUPS][] = {
"bcdefghijkmnopqrsuv",  //fondator
"bcdefghijkmnopqrsu",   //manager
"bcdefhijkmnopqrs",   	  //owner
"bcdefhijkmnpqrs",      //co-owner
"bcdefhijmnp",   //loyality
"bcdefhijmn",   //Veteran
"bcdefhijm",    //Maresal
"bcdefhij",     //General
"bcdefij",      //Maior
"b"             // slot
}



//static steamardei[35]  = "STEAM_0:1:84367986"
//static steamanyela[35] = "STEAM_0:1:63615078"
//static steamunu[35] = "STEAM_0:1:50702360"

new g_groupFlagsValue[MAX_GROUPS]
public plugin_init() 
{
	register_plugin("Lista admini (amx_who)", "3.0", "UNU")
	register_concmd("amx_who", "cmdWho", 0)
	register_concmd("admin_who", "cmdWho", 0)
	register_clcmd("say /who", "cmdWhoSay", 0)
	register_clcmd("say /WHO", "cmdWhoSay", 0)
	register_clcmd("say /ADMIN", "cmdWhoSay", 0)
	register_clcmd("say /admin", "cmdWhoSay", 0)
	register_clcmd("say /admins", "cmdWhoSay", 0)
	//register_concmd("amx_test", "test", 0)
	for(new i = 0; i < MAX_GROUPS; i++) 
	{
		g_groupFlagsValue[i] = read_flags(g_groupFlags[i])
	}
}

public cmdWhoSay(id)
{
	if(!is_user_connected(id))
		return PLUGIN_CONTINUE 
	
	cmdWho(id)
	client_cmd(id, "toggleconsole");
	set_task(5.0,"funccmd",id)
	return PLUGIN_CONTINUE
}
public funccmd(id)
{
	client_cmd(id, "cancelselect");
}

public client_disconnected(id) 
{
	playerok[id] = 0
}

public client_infochanged(id)
{
	playerok[id] = 0
}




public cmdWho(id) {
// Verificam daca userul este online, daca nu... ne oprim din executie
	if(!is_user_connected(id)) 
	{ 
		return PLUGIN_HANDLED 
	}
	new players[32], inum, player, name[32], i, a,flag , sflags[32]
	get_players(players, inum)	
	
	for(new pl = 0; pl < inum; pl++) 
	{
		playerok[pl] = 0
	}
	//console_print(id, "=========================")
	//console_print(id, "==( OFFICIAL.indungi.RO ) Admin list==")
	//console_print(id, "=========================")

//  ____  ________________________   __ 
// / __ \/ __/ __/  _/ ___/  _/ _ | / / 
/// /_/ / _// _/_/ // /___/ // __ |/ /__
//\____/_/ /_/ /___/\___/___/_/ |_/____/

	console_print(id, "                                                                                          ")
	console_print(id, "                                                                                          ")
	console_print(id, "  OOOOO  FFFFFFF FFFFFFF IIIII  CCCCC  IIIII    AAA      LL")
	console_print(id, " OO   OO  FF          FF          III   CC    C    III   AAAAA    LL")
	console_print(id, " OO   OO  FFFF      FFFF       III   CC          III  AA    AA _LL")
	console_print(id, " OO   OO  FF          FF          III   CC    C    III  AAAAAAA LL")
	console_print(id, "  OOOO0  FF          FF          IIIII  CCCCC  IIIII AA      AA  LLLLLLL") 
	console_print(id, "========================================== ")
	console_print(id, "|_                                                                                          |")
	console_print(id, "|                      ®     OFFICIAL.indungi.RO      ®                       |")
	console_print(id, "|_                                                                                          |")
	console_print(id, "========================================== ")
	console_print(id, "|_                         «»»      Admin List     ««»                           _|")
	console_print(id, "========================================== ")
	for(i = 0; i < MAX_GROUPS; i++) 
	{
		
		new bufferrank[49]
		new buffernamex[85]
		new frontspacex[78]		
		format(bufferrank,40,"[%d] %s ",i+1,g_groupNames[i]);		
		console_print(id, "                  %s", bufferrank)
		
		for(a = 0; a < inum; a++) 
		{			
			player = players[a]
			get_user_name(player, name, 31)			
			flag = nCleanFlags(player)
			
			new nflags = 0
			nflags = get_user_flags(player)
			new sflags2[31]
			get_flags(nflags,sflags2,sizeof(sflags2)-1)
			
			new namelen = strlen( name )
			//new halfname
			
			if (containi(sflags2,"w")!=-1)
			{ 
				/*
				format(buffernamex,namelen + 18,"%s%s","[VIP] Silver      ",name)
				format(frontspacex,20,"%s","  ");
				halfname = floatround(((namelen) / 2.0), floatround_ceil )
				*/
				
			}
			else
			{
				if (containi(sflags2,"t")!=-1)
				{	
					format(buffernamex,namelen + 17,"%s%s","[VIP]            ",name)
					format(frontspacex,20,"%s","  ");
					//halfname = floatround(((namelen) / 2.0), floatround_ceil )		
				}
				else
				{
					format(buffernamex,namelen,"%s",name)
					format(frontspacex,20,"%s","                                     ");
					//halfname = floatround((namelen / 2.0), floatround_ceil )
					//format(buffernamex,25-halfname,"%s%s",buffernamex,"                                          ");
				}				
			}
			
			

			
			
			//format(buffernamex,namelen,"%s",name)
			//format(frontspacex,20,"%s","                                  ");
			
			
			//"bt",          // vip gold
			//"bw",          // vip silver

			
			if(flag == g_groupFlagsValue[i])
			{				
				console_print(id, "%s%s", frontspacex,buffernamex)
				playerok[player] = 1;
			}
		}
	}
	if (access(id, SHOWHIDEN))
	{
		console_print(id, "==========================================")
		console_print(id, " >>>  Hidden Access")	
	}
	for(a = 0; a < inum; ++a) 
		{
			player = players[a]
			if (playerok[player] < 1)
			{
				get_user_name(player, name, 31)
				new namelen = strlen( name )
				new buffername[78], frontspace[78]
				new halfname = floatround((namelen / 2.0), floatround_ceil )
				
				format(buffername,namelen,"%s",name)
				format(frontspace,20-halfname,"%s","                                  ");
				flag = get_user_flags(player)
				get_flags(flag,sflags,31)
				format(buffername,66-halfname,"%s <-> (Flags:[ %s ]) %s",buffername,sflags,"                                        ");
				
				if ((flag != 33554432) && (access(id, SHOWHIDEN)))
				{
					console_print(id, "%s%s", frontspace,buffername)
						
				}
				
			}
			
		}
	
	console_print(id, "==========================================")
	return PLUGIN_HANDLED
}