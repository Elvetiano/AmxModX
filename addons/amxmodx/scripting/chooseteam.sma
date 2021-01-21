#include <amxmodx>
#include <fakemeta>

#define PLUGIN "Unlimited ChooseTeam"
#define AUTHOR "ConnorMcLeod"
#define VERSION "0.0.1"

public plugin_init()
{
    register_plugin( PLUGIN, VERSION, AUTHOR )
    register_clcmd("chooseteam", "ClientCommand_ChooseTeam")
}

public ClientCommand_ChooseTeam( id )
{
	if(!pev_valid(id))
		return FMRES_IGNORED
	set_pdata_int(id, 125, get_pdata_int(id, 125, 5) &  ~(1<<8), 5)
	return PLUGIN_CONTINUE
}  