#if defined _MODULE_CHAT_RP_INC
    #endinput
#endif
#define _MODULE_CHAT_RP_INC

// ============================================================
//  SantaraBaru Roleplay — Roleplay Chat System & Proximity
// ============================================================

stock DoProximitySay(playerid, const text[], Float:radius, color, bool:shout) {
    new Float:px, Float:py, Float:pz;
    GetPlayerPos(playerid, px, py, pz);
    new charname[48], msg[256];
    GetCharName(playerid, charname);
    if (shout) {
        format(msg, sizeof(msg), "%s berteriak: %s", charname, text);
    } else {
        format(msg, sizeof(msg), "%s berkata: %s", charname, text);
    }

    for (new i = 0; i < MAX_PLAYERS; i++) {
        if (!IsPlayerConnected(i)) continue;
        if (!gPlayerData[i][p_LoggedIn] || !gPlayerData[i][p_Spawned]) continue;
        new Float:tx, Float:ty, Float:tz;
        GetPlayerPos(i, tx, ty, tz);
        if (GetPlayerVirtualWorld(i) != GetPlayerVirtualWorld(playerid)) continue;
        if (GetPlayerInterior(i) != GetPlayerInterior(playerid)) continue;
        if (VectorSize(px - tx, py - ty, pz - tz) <= radius) {
            SendClientMessage(i, color, msg);
        }
    }
}

stock DoProximityRaw(playerid, const msg[], Float:radius, color) {
    new Float:px, Float:py, Float:pz;
    GetPlayerPos(playerid, px, py, pz);

    for (new i = 0; i < MAX_PLAYERS; i++) {
        if (!IsPlayerConnected(i)) continue;
        if (!gPlayerData[i][p_LoggedIn] || !gPlayerData[i][p_Spawned]) continue;
        new Float:tx, Float:ty, Float:tz;
        GetPlayerPos(i, tx, ty, tz);
        if (GetPlayerVirtualWorld(i) != GetPlayerVirtualWorld(playerid)) continue;
        if (GetPlayerInterior(i) != GetPlayerInterior(playerid)) continue;
        if (VectorSize(px - tx, py - ty, pz - tz) <= radius) {
            SendClientMessage(i, color, msg);
        }
    }
}
