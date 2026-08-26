#if defined _MODULE_CMD_RP_INC
    #endinput
#endif
#define _MODULE_CMD_RP_INC

// ============================================================
//  SantaraBaru Roleplay - Roleplay Chat Commands (/s, /sh, /w, /me, /do, /ooc)
// ============================================================

CMD:s(playerid, params[]) {
    if (!CheckSpawned(playerid)) return 1;
    if (!strlen(params)) return SendClientMessage(playerid, COL_RED, "  Penggunaan: /s [pesan]");
    DoProximitySay(playerid, params, DIST_VOICE, COL_WHITE, false);
    return 1;
}

CMD:sh(playerid, params[]) {
    if (!CheckSpawned(playerid)) return 1;
    if (!strlen(params)) return SendClientMessage(playerid, COL_RED, "  Penggunaan: /sh [pesan]");
    StrToUpper(params);
    DoProximitySay(playerid, params, DIST_SHOUT, COL_YELLOW, true);
    return 1;
}

CMD:w(playerid, params[]) {
    if (!CheckSpawned(playerid)) return 1;
    if (!strlen(params)) return SendClientMessage(playerid, COL_RED, "  Penggunaan: /w [pesan]");
    DoProximitySay(playerid, params, DIST_WHISPER, 0xAAAAAAFF, true);
    return 1;
}

CMD:me(playerid, params[]) {
    if (!CheckSpawned(playerid)) return 1;
    if (!strlen(params)) return SendClientMessage(playerid, COL_RED, "  Penggunaan: /me [aksi]");
    new charname[48], msg[200];
    GetCharName(playerid, charname);
    format(msg, sizeof(msg), "* %s %s", charname, params);
    DoProximityRaw(playerid, msg, DIST_RP, COL_PURPLE);
    return 1;
}

CMD:do(playerid, params[]) {
    if (!CheckSpawned(playerid)) return 1;
    if (!strlen(params)) return SendClientMessage(playerid, COL_RED, "  Penggunaan: /do [deskripsi]");
    new charname[48], msg[200];
    GetCharName(playerid, charname);
    format(msg, sizeof(msg), "** %s (( %s ))", params, charname);
    DoProximityRaw(playerid, msg, DIST_RP, COL_CYAN);
    return 1;
}

CMD:ooc(playerid, params[]) {
    if (!CheckSpawned(playerid)) return 1;
    if (!strlen(params)) return SendClientMessage(playerid, COL_RED, "  Penggunaan: /ooc [pesan]");
    new charname[48], msg[200];
    GetCharName(playerid, charname);
    format(msg, sizeof(msg), "(( {AAAAAA}OOC | %s: %s {AAAAAA}))", charname, params);
    SendClientMessageToAll(0xAAAA00FF, msg);
    return 1;
}

CMD:b(playerid, params[]) {
    return cmd_ooc(playerid, params);
}
