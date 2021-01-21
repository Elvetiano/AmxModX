/*
* Whois Module
* Copyright (c) 2014 AGHL.RU Dev Team
*
* http://aghl.ru/forum/ - Russian Half-Life and Adrenaline Gamer Community
*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*    In addition, as a special exception, the author gives permission to
*    link the code of this program with the Half-Life Game Engine ("HL
*    Engine") and Modified Game Libraries ("MODs") developed by Valve,
*    L.L.C ("Valve").  You must obey the GNU General Public License in all
*    respects for all of the code used other than the HL Engine and MODs
*    from Valve.  If you modify this file, you may extend this exception
*    to your version of the file, but you are not obligated to do so.  If
*    you do not wish to do so, delete this exception statement from your
*    version.
*
*/


#if defined _whois_included
	#endinput
#endif
#define _whois_included

#if AMXX_VERSION_NUM >= 175
	#pragma reqlib whois
#if !defined AMXMODX_NOAUTOLOAD
	#pragma loadlib whois
#endif
#else
	#pragma library whois
#endif


/* Result of WHOIS query */
enum WhoisQueryResult
{
	WHOIS_NO_ERROR = 0,				// Success
	WHOIS_ERR_SERVER_ADDRESS = 1,	// Unable to resolve WHOIS server address
	WHOIS_ERR_CONNECT = 2,			// Failed to connect to WHOIS server
	WHOIS_ERR_QUERY = 3,			// Failed to send query to WHOIS server
	WHOIS_ERR_RECEIVE = 4,			// Failed to receive WHOIS answer
	WHOIS_ERR_PARSE = 5,			// Failed to parse WHOIS answer
};


/*
* Starts whois query for the given IP address.
*
* @param handler - The forward to call upon the query is complete. Signature: public WhoisIpQueryComplete(WhoisQueryResult:result, const ip[], const startIp[], const endIp[], const asNumber[], const descr[], const data[], dataSize, const rawAnswer[]).
*/
native WhoisIpQuery(const ip[], const handler[], const data[] = "", dataSize = 0);
