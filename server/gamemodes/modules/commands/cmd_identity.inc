#if defined _MODULE_CMD_IDENTITY_INC
    #endinput
#endif
#define _MODULE_CMD_IDENTITY_INC

// ============================================================
//  SantaraBaru Roleplay — Identity & KTP Commands (/getktp, /ktp, /showktp)
// ============================================================

CMD:getktp(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;

    // Cek apakah pemain berada di dekat loket KTP di Balai Kota
    if (!IsPlayerInRangeOfPoint(playerid, 2.5, KTP_DESK_X, KTP_DESK_Y, KTP_DESK_Z) || GetPlayerInterior(playerid) != KTP_DESK_INT_ID) {
        SendClientMessage(playerid, COL_RED, "  [!] Anda harus berada di Loket Catatan Sipil di dalam Balai Kota untuk membuat e-KTP!");
        return 1;
    }

    if (gPlayerData[playerid][p_HasKTP]) {
        SendClientMessage(playerid, COL_YELLOW, "  [!] Anda sudah memiliki e-KTP aktif. Gunakan {00EEFF}/ktp{FFFF00} untuk melihatnya.");
        return 1;
    }

    // Terbitkan e-KTP untuk karakter ini
    gPlayerData[playerid][p_HasKTP] = true;

    new query[256];
    format(query, sizeof(query), "UPDATE `characters` SET `has_ktp` = 1 WHERE `id` = %d", gPlayerData[playerid][p_CharID]);
    DB_FreeResultSet(DB_ExecuteQuery(gDB, query));

    // Efek suara & notifikasi
    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
    GameTextForPlayer(playerid, "~g~e-KTP Berhasil Diterbitkan!", 4000, 3);

    SendClientMessage(playerid, COL_GREEN, "  [✓] Selamat! e-KTP Anda telah berhasil diterbitkan oleh Dinas Kependudukan Balai Kota.");
    SendClientMessage(playerid, COL_WHITE, "  [!] Gunakan perintah {00EEFF}/ktp{FFFFFF} untuk melihat KTP atau {00EEFF}/showktp [id]{FFFFFF} untuk memperlihatkannya ke orang lain.");

    // RP Proximity action
    new charname[48], rpMsg[160];
    GetCharName(playerid, charname);
    format(rpMsg, sizeof(rpMsg), "%s menerima fisik kartu e-KTP resmi yang baru diterbitkan dari petugas loket catatan sipil.", charname);
    DoProximityRaw(playerid, rpMsg, DIST_RP, COL_PURPLE);

    // Langsung buka kartu e-KTP
    ShowPlayerKTPCard(playerid, playerid);
    return 1;
}

CMD:ktp(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    if (!gPlayerData[playerid][p_HasKTP]) {
        SendClientMessage(playerid, COL_RED, "  [!] Karakter Anda belum memiliki e-KTP!");
        SendClientMessage(playerid, COL_WHITE, "  [!] Silakan kunjungi {33CCFF}Balai Kota (Pershing Square){FFFFFF} dan buat KTP di Loket Catatan Sipil.");
        return 1;
    }
    ShowPlayerKTPCard(playerid, playerid);
    SendClientMessage(playerid, COL_GREEN, "  [KTP] Membuka Kartu Tanda Penduduk (e-KTP) Anda.");
    return 1;
}

CMD:myktp(playerid, params[]) {
    return cmd_ktp(playerid, params);
}

CMD:showktp(playerid, params[]) {
    if (!CheckSpawned(playerid)) return 1;
    if (!gPlayerData[playerid][p_HasKTP]) {
        SendClientMessage(playerid, COL_RED, "  [!] Karakter Anda belum memiliki e-KTP!");
        SendClientMessage(playerid, COL_WHITE, "  [!] Silakan kunjungi {33CCFF}Balai Kota (Pershing Square){FFFFFF} dan buat KTP di Loket Catatan Sipil.");
        return 1;
    }
    new targetid;
    if (sscanf(params, "u", targetid)) {
        return SendClientMessage(playerid, COL_ORANGE, "  [Gunakan] /showktp [Player ID / Nama]");
    }
    if (!IsPlayerConnected(targetid) || !gPlayerData[targetid][p_LoggedIn] || !gPlayerData[targetid][p_Spawned]) {
        return SendClientMessage(playerid, COL_RED, "  [!] Pemain target tidak ditemukan atau sedang offline.");
    }
    if (targetid == playerid) {
        return cmd_ktp(playerid, params);
    }
    new Float:tx, Float:ty, Float:tz;
    GetPlayerPos(targetid, tx, ty, tz);
    if (!IsPlayerInRangeOfPoint(playerid, 4.0, tx, ty, tz)) {
        return SendClientMessage(playerid, COL_RED, "  [!] Pemain tersebut berada terlalu jauh dari Anda (maks. 4 meter).");
    }

    // Tampilkan KTP pengirim ke layar target dan ke layar pengirim
    ShowPlayerKTPCard(targetid, playerid);
    ShowPlayerKTPCard(playerid, playerid);

    new msg[160], myName[48], targetName[48];
    GetCharName(playerid, myName);
    GetCharName(targetid, targetName);

    format(msg, sizeof(msg), "* %s mengambil KTP miliknya dan memperlihatkannya kepada %s.", myName, targetName);
    DoProximitySay(playerid, msg, DIST_VOICE, COL_PURPLE, false);
    return 1;
}
