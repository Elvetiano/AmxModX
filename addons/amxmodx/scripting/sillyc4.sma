#include <amxmodx>
#include <cstrike>
#include <engine>
#include <csx>
#include <xs>
#include <fakemeta>
#include <fakemeta_util>

#define MAX_PLAYERS 32

new DEFUSING_SOUND[] = "weapons/c4_click.wav"
new g_NumberID = 0
new g_iRandomNumbers[11]
new g_Defusing[MAX_PLAYERS+1]
new Float:g_fDelay[MAX_PLAYERS+1] 
new cvar_restrict, cvar_numbers, cvar_wallplant 

enum _:m_BombSiteDatas
{
	m_iEntity,
    Float:m_fVecMins[3],
    Float:m_fVecMaxs[3],
}

new Array:g_aBombSites
//new CvarDistance

static const PLUGIN_NAME[] 	= "Silly C4"
static const PLUGIN_AUTHOR[] 	= "Cheap_Suit & UNU"
static const PLUGIN_VERSION[]	= "1.3"

public plugin_init()
{
	register_plugin(PLUGIN_NAME, PLUGIN_VERSION, PLUGIN_AUTHOR)
	register_cvar(PLUGIN_NAME, PLUGIN_VERSION, FCVAR_SPONLY|FCVAR_SERVER)

	//CvarDistance = register_cvar("gb_distance", "300.0");
			
	register_event("BarTime", 	"Event_BarTime", "b", "1=0")
	register_logevent("Spawn_plantzone", 2, "1=Round_Start" )
	cvar_numbers 	= register_cvar("amx_sc_rannumber", "1")
	cvar_restrict 	= register_cvar("amx_sc_removeres", "1")
	cvar_wallplant 	= register_cvar("amx_sc_wallplant", "1")
	g_aBombSites = ArrayCreate(m_BombSiteDatas, 2)
	new mDatas[m_BombSiteDatas],iEnt
	new const szClasses[][] = { "func_bomb_target" , "info_bomb_target" }
	for(new i; i<sizeof(szClasses); i++)
	{
		iEnt = FM_NULLENT
		while( (iEnt = engfunc(EngFunc_FindEntityByString, iEnt, "classname", szClasses[i])))
		{
			set_pev(iEnt, pev_modelindex, 0)
			mDatas[m_iEntity] = iEnt
			pev(iEnt, pev_mins, mDatas[m_fVecMins])
			pev(iEnt, pev_maxs, mDatas[m_fVecMaxs])
			ArrayPushArray(g_aBombSites, mDatas)
		}
	}
	
	UTIL_CheckMapType( )
}

public Spawn_plantzone()
{
	//if(!get_pcvar_num(cvar_plantzone))
	//	return
	set_task(5.0, "enlarge_bombtarget")
}

public plugin_precache()
	precache_sound(DEFUSING_SOUND)

public Event_BarTime(id) if(g_Defusing[id])
{	
	g_NumberID = 0
	g_Defusing[id] = 0
}

public bomb_defused(id)
{
	g_NumberID = 0
	g_Defusing[id] = 0
}

public bomb_defusing(id)
{
	if(get_pcvar_num(cvar_restrict))
		entity_set_float(id, EV_FL_maxspeed, 240.0)
		
	g_Defusing[id] = 1
}
	
public bomb_planting(id) if(get_pcvar_num(cvar_restrict))
	entity_set_float(id, EV_FL_maxspeed, 240.0)

public bomb_planted(id)
{
	if(!get_pcvar_num(cvar_wallplant))
		return
	
	g_NumberID = 0
	for(new i = 0; i < 11; ++i)
		g_iRandomNumbers[i] = rn()
	
	new Float:fOrigin[3]
	entity_get_vector(id, EV_VEC_origin, fOrigin)
		
	new Float:fVelocity[3]
	VelocityByAim(id, 54, fVelocity)
	
	if(fVelocity[2] < -28.0)
		return 

	new Float:fTraceEnd[3]
	xs_vec_add(fVelocity, fOrigin, fTraceEnd)
		
	new Float:fTraceResult[3]
	trace_line(id, fOrigin, fTraceEnd, fTraceResult)

	new Float:fNormal[3]
	if(trace_normal(id, fOrigin, fTraceEnd, fNormal) < 1)
		return

	new c4 = -1
	while((c4 = find_ent_by_model(c4, "grenade", "models/w_c4.mdl")))
	{
		if(entity_get_int(c4, EV_INT_movetype) == MOVETYPE_FLY 
		|| (get_entity_flags(c4) & FL_ONGROUND))
			continue
			
		entity_set_int(c4, EV_INT_movetype, MOVETYPE_FLY)
		entity_set_vector(c4, EV_VEC_velocity, Float:{0.0, 0.0, 0.0})
		new Float:fNewOrigin[3]
		fNewOrigin[0] = fTraceResult[0] + (fNormal[0] * -0.01)
		fNewOrigin[1] = fTraceResult[1] + (fNormal[1] * -0.01)
		fNewOrigin[2] = fTraceResult[2] +  fNormal[2] + 8.000
		
		entity_set_origin(c4, fNewOrigin)
		
		new Float:fAngles[3]
		vector_to_angle(fNormal, fAngles)
		fAngles[0] -= 180.0, fAngles[1] -= 90.0, fAngles[2] -= 90.0
		entity_set_vector(c4, EV_VEC_angles, fAngles)
	}
}

public client_PreThink(id)
{
	if(!get_pcvar_num(cvar_numbers) || !is_user_alive(id) || !g_Defusing[id])
		return PLUGIN_CONTINUE

	if(g_fDelay[id] + get_delay(id) < get_gametime())
	{
		g_NumberID += 1
		client_cmd(id, "spk %s", DEFUSING_SOUND)
		g_fDelay[id] = get_gametime()
	}
	
	set_hudmessage(255, 255, 255, -1.0, 0.4, 0, 0.0, 10.0, 0.0, 0.0, 2)
	switch(g_NumberID)
	{
		case 1: show_hudmessage(id, "%d%d%d%d%d%d%d%d%d%d%d", n(0), rn(), rn(), rn(), rn(), rn(), rn(), rn(), rn(), rn(), rn()) 
		case 2: show_hudmessage(id, "%d%d%d%d%d%d%d%d%d%d%d", n(0), n(1), rn(), rn(), rn(), rn(), rn(), rn(), rn(), rn(), rn())
		case 3: show_hudmessage(id, "%d%d%d%d%d%d%d%d%d%d%d", n(0), n(1), n(2), rn(), rn(), rn(), rn(), rn(), rn(), rn(), rn())
		case 4: show_hudmessage(id, "%d%d%d%d%d%d%d%d%d%d%d", n(0), n(1), n(2), n(3), rn(), rn(), rn(), rn(), rn(), rn(), rn())
		case 5: show_hudmessage(id, "%d%d%d%d%d%d%d%d%d%d%d", n(0), n(1), n(2), n(3), n(4), rn(), rn(), rn(), rn(), rn(), rn())
		case 6: show_hudmessage(id, "%d%d%d%d%d%d%d%d%d%d%d", n(0), n(1), n(2), n(3), n(4), n(5), rn(), rn(), rn(), rn(), rn())
		case 7: show_hudmessage(id, "%d%d%d%d%d%d%d%d%d%d%d", n(0), n(1), n(2), n(3), n(4), n(5), n(6), rn(), rn(), rn(), rn())
		case 8: show_hudmessage(id, "%d%d%d%d%d%d%d%d%d%d%d", n(0), n(1), n(2), n(3), n(4), n(5), n(6), n(7), rn(), rn(), rn())
		case 9: show_hudmessage(id, "%d%d%d%d%d%d%d%d%d%d%d", n(0), n(1), n(2), n(3), n(4), n(5), n(6), n(7), n(8), rn(), rn())
		case 10:show_hudmessage(id, "%d%d%d%d%d%d%d%d%d%d%d", n(0), n(1), n(2), n(3), n(4), n(5), n(6), n(7), n(8), n(9), rn())
		case 11:show_hudmessage(id, "%d%d%d%d%d%d%d%d%d%d%d", n(0), n(1), n(2), n(3), n(4), n(5), n(6), n(7), n(8), n(9),n(10)) 
		default:show_hudmessage(id, "%d%d%d%d%d%d%d%d%d%d%d", n(0), n(1), n(2), n(3), n(4), n(5), n(6), n(7), n(8), n(9),n(10))
	}
	return PLUGIN_CONTINUE
}



public enlarge_bombtarget() 
{
	new old_bomtarget = fm_find_ent_by_class(-1, "func_bomb_target")
	new old_infobomtarget = fm_find_ent_by_class(-1, "info_bomb_target")
	if(old_bomtarget > 0 || old_infobomtarget > 0)
	{		
		new iBombeSitesNum = ArraySize(g_aBombSites)
		new Float:centre_origin[3]
		new mDatas[m_BombSiteDatas]
		
		new map[33]
		get_mapname(map,32)
		
		for(new i; i<iBombeSitesNum; i++)
		{
			ArrayGetArray(g_aBombSites, i, mDatas)
			new iEnt = mDatas[m_iEntity]
			if (!iEnt)
				client_print(0,print_chat,"**********No entity found on this map **********") 
			if(pev_valid( iEnt ))
			{
				fm_get_brush_entity_origin(iEnt, centre_origin)
				new bombtarget = create_entity("func_bomb_target")
				if(bombtarget > 0)
				{
					DispatchKeyValue(bombtarget, "classname", "func_bomb_target")
					DispatchSpawn(bombtarget)
					entity_set_size(bombtarget, Float:{-250.0,-250.0,-100.0}, Float:{250.0,250.0,100.0})
					if(equali(map, "de_dust2"))
					{
						entity_set_size(bombtarget, Float:{-600.0,-450.0,-100.0}, Float:{350.0,550.0,50.0})
					}
					if(equali(map, "de_inferno"))
					{
						entity_set_size(bombtarget, Float:{-250.0,-250.0,-100.0}, Float:{250.0,250.0,100.0})
					}
					if(equali(map, "de_kabul_32"))
					{
						entity_set_size(bombtarget, Float:{-500.0,-500.0,-100.0}, Float:{750.0,750.0,800.0}) 
					}
					if(equali(map, "de_barcelona"))
					{
						entity_set_size(bombtarget, Float:{-350.0,-350.0,-100.0}, Float:{250.0,250.0,100.0})
					}
					if(equali(map, "de_mirage_32"))
					{
						entity_set_size(bombtarget, Float:{-550.0,-550.0,-100.0}, Float:{450.0,450.0,100.0})
					}
					if(equali(map, "de_train32"))
					{
						entity_set_size(bombtarget, Float:{-1500.0,-250.0,-100.0}, Float:{1000.0,400.0,100.0})
					}
					entity_set_string(bombtarget, EV_SZ_classname, "func_bomb_target")
					entity_set_origin(bombtarget, centre_origin)
					//set_task(1.0, "enlarge_defusetarget")	
				}
			}			
		}
	}
	else
		client_print(0,print_chat,"**********No Bomb target function found on this map **********")
}



/*
#include <sdkhooks>

public Plugin:myinfo =
{
    name = "CreateEntityReport",
    author = "Raska",
    description = "",
    version = "0.1",
    url = ""
}

public OnEntityCreated(entity, const String:classname[])
{
    PrintToChatAll("[NewEntity] '%s' '%d'", classname, entity);
}

public whatisonPVS(id) 
{ 
    static next, chain 
    static class[32] 
     
    next = engfunc(EngFunc_EntitiesInPVS, id) 
    while(next) 
    { 
        pev(next, pev_classname, class, charsmax(class)) 
        chain = pev(next, pev_chain) 
         
        server_print("Found entity in player (%i) PVS: ent(%i) class(%s)", id, next, class) 
         
        if(!chain) 
            break 
     
        next = chain 
    } 
} 




public enlarge_defusetarget() 
{
	new Float:fOrigin[ 3 ] , weapbox, bomb , id , playersList[32] , playersCount;
    
    bomb = fm_find_ent_by_class( -1 , "weapon_c4" );
    
    if ( bomb && !( 1 <= ( weapbox = pev( bomb , pev_owner ) ) <= MAX_PLAYERS ) && pev_valid( weapbox ) )
    {
        pev( weapbox , pev_origin , fOrigin );

        playersCount = find_sphere_class( 0 , "player" , get_pcvar_float( CvarDistance ) , playersList , sizeof( playersList ) , fOrigin );
            
        for ( new i = 0 ; i < playersCount ; i++ )
        {
			id = playersList[ i ];
			cs_set_c4_defusing(bomb, true);
			cs_set_user_defuse(id, 1, 0, 160, 0,"defuser", 1);
		}
	}
	
	
	
	
	new old_bomtarget = fm_find_ent_by_class(-1, "info_bomb_target")
	if(old_bomtarget > 0)
	{		
		new iBombeSitesNum = ArraySize(g_aBombSites)
		new Float:centre_origin[3]
		new mDatas[m_BombSiteDatas]
		for(new i; i<iBombeSitesNum+1; i++)
		{
			ArrayGetArray(g_aBombSites, i, mDatas)
			new iEnt = mDatas[m_iEntity]
			fm_get_brush_entity_origin(iEnt, centre_origin)	
			new bombtarget = create_entity("info_bomb_target")
			if(bombtarget > 0)
			{
				DispatchKeyValue(bombtarget, "classname", "info_bomb_target")
				DispatchSpawn(bombtarget)
				entity_set_size(bombtarget, Float:{-550.0,-550.0,-300.0}, Float:{350.0,550.0,300.0})
				entity_set_string(bombtarget, EV_SZ_classname, "info_bomb_target")
				entity_set_origin(bombtarget, centre_origin)			
			}				
		}
	}
	
	
	
}*/

UTIL_CheckMapType( )
{
	if( !find_ent_by_class( -1, "func_bomb_target" ) && !find_ent_by_class( -1, "info_bomb_target") )
	{
		log_amx( "Plugin paused, this is not a bomb map" )
		pause( "a" )		
	}	
}

stock rn() return random_num(0, 9)
stock n(value) return g_iRandomNumbers[value]
stock Float:get_delay(id) return cs_get_user_defuse(id) ? 0.4999 : 0.9999
/* AMXX-Studio Notes - DO NOT MODIFY BELOW HERE
*{\\ rtf1\\ ansi\\ ansicpg1252\\ deff0\\ deflang1033{\\ fonttbl{\\ f0\\ fnil Tahoma;}}\n\\ viewkind4\\ uc1\\ pard\\ f0\\ fs16 \n\\ par }
*/
