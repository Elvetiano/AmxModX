#if defined _weapon_skin_system_included
  #endinput
#endif
#define _weapon_skin_system_included

#if AMXX_VERSION_NUM >= 175
	#pragma reqlib weapon_skin_system
	#if !defined AMXMODX_NOAUTOLOAD
		#pragma loadlib weapon_skin_system
	#endif
#else
	#pragma library weapon_skin_system
#endif

/**
 * Called when load skins from file.
 * 
 * @param index						Skin index
 * @param weaponid					Skin CSW_ const
 * @param name						Skin name
 */
forward wss_loaded_skin(index, weaponid, name[]);

/**
 * Get weapon skin.
 * 
 * @param weapon					Weapon enity index
 */
native wss_get_weapon_skin_index(weapon);

/**
 * Get skin name by index.
 * 
 * @param skin						Skin index
 * @param name						String for name
 * @param len						Max string len
 */
native wss_get_skin_name(skin, name[], len);

/**
 * Change player weapon skin.
 * If weaponid is NULL then reset all player skins.
 * 
 * @param id						Player index
 * @param weaponid					Weapon CSW_ const
 * @param skin_index				Skin index from wss_loaded_skin()
 */
native wss_set_user_skin(id, weaponid, skin_index = 0);
