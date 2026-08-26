#if defined _MODULE_CMD_IDENTITY_INC
    #endinput
#endif
#define _MODULE_CMD_IDENTITY_INC

// ============================================================
//  SantaraBaru Roleplay - Identity & KTP Command (/ktp)
// ============================================================

CMD:ktp(playerid, params[]) {
    if (!CheckSpawned(playerid)) return 1;

    // 1. Jika pemain berada di dekat Loket Catatan Sipil Balai Kota: Proses Pembuatan / Penerbitan e-KTP
    if (IsPlayerInRangeOfPoint(playerid, 2.5, KTP_DESK_X, KTP_DESK_Y, KTP_DESK_Z) && GetPlayerInterior(playerid) == KTP_DESK_INT_ID) {
        if (gPlayerData[playerid][p_HasKTP]) {
            ShowPlayerKTPCard(playerid, playerid);
            SendClientMessage(playerid, COL_GREEN, "  [KTP] Anda sudah memiliki e-KTP resmi terdaftar di database.");
            return 1;
        }

        // Terbitkan e-KTP baru untuk karakter ini
        gPlayerData[playerid][p_HasKTP] = true;

        new query[256];
        format(query, sizeof(query), "UPDATE `characters` SET `has_ktp` = 1 WHERE `id` = %d", gPlayerData[playerid][p_CharID]);
        DB_FreeResultSet(DB_ExecuteQuery(gDB, query));

        // Efek suara & notifikasi
        PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
        GameTextForPlayer(playerid, "~g~e-KTP Berhasil Diterbitkan!", 4000, 3);

        SendClientMessage(playerid, COL_GREEN, "  [[OK]] Selamat! e-KTP Anda telah berhasil diterbitkan oleh Dinas Kependudukan Balai Kota.");
        SendClientMessage(playerid, COL_WHITE, "  [!] Gunakan {00EEFF}/ktp{FFFFFF} untuk melihat atau {00EEFF}/ktp [id]{FFFFFF} untuk memperlihatkan ke pemain lain.");

        // RP Proximity action
        new charname[48], rpMsg[160];
        GetCharName(playerid, charname);
        format(rpMsg, sizeof(rpMsg), "%s menerima fisik kartu e-KTP resmi yang baru diterbitkan dari petugas loket catatan sipil.", charname);
        DoProximityRaw(playerid, rpMsg, DIST_RP, COL_PURPLE);

        // Langsung buka kartu e-KTP
        ShowPlayerKTPCard(playerid, playerid);
        return 1;
    }

    // 2. Cek apakah karakter sudah memiliki KTP
    if (!gPlayerData[playerid][p_HasKTP]) {
        SendClientMessage(playerid, COL_RED, "  [!] Karakter Anda belum memiliki e-KTP!");
        SendClientMessage(playerid, COL_WHITE, "  [!] Silakan kunjungi {33CCFF}Balai Kota (Pershing Square){FFFFFF} dan buat KTP di Loket Catatan Sipil.");
        return 1;
    }

    // 3. Jika ada parameter: Tunjukkan KTP ke pemain terdekat (/ktp [id])
    if (strlen(params) > 0) {
        new targetid;
        if (sscanf(params, "u", targetid)) {
            return SendClientMessage(playerid, COL_ORANGE, "  [Petunjuk] Gunakan: /ktp (lihat sendiri) atau /ktp [Player ID / Nama] (tunjukkan)");
        }
        if (!IsPlayerConnected(targetid) || !gPlayerData[targetid][p_LoggedIn] || !gPlayerData[targetid][p_Spawned]) {
            return SendClientMessage(playerid, COL_RED, "  [!] Pemain target tidak ditemukan atau sedang offline.");
        }
        if (targetid == playerid) {
            ShowPlayerKTPCard(playerid, playerid);
            SendClientMessage(playerid, COL_GREEN, "  [KTP] Membuka Kartu Tanda Penduduk (e-KTP) Anda.");
            return 1;
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

    // 4. Jika tanpa parameter: Buka kartu e-KTP milik sendiri
    ShowPlayerKTPCard(playerid, playerid);
    SendClientMessage(playerid, COL_GREEN, "  [KTP] Membuka Kartu Tanda Penduduk (e-KTP) Anda.");
    return 1;
}
