#if defined _MODULE_CMD_IDENTITY_INC
    #endinput
#endif
#define _MODULE_CMD_IDENTITY_INC

// ============================================================
//  SantaraBaru Roleplay - Identity & KTP Command (/ktp, /showktp)
//  Integrated with Civil Database & Inventory Physical Card Item
// ============================================================

CMD:ktp(playerid, params[]) {
    if (!CheckSpawned(playerid)) return 1;

    // 1. Jika pemain berada di dekat Loket Catatan Sipil Balai Kota: Proses Pembuatan / Cetak Ulang e-KTP
    if (IsPlayerInRangeOfPoint(playerid, 2.5, KTP_DESK_X, KTP_DESK_Y, KTP_DESK_Z) && GetPlayerInterior(playerid) == KTP_DESK_INT_ID) {
        if (!gPlayerData[playerid][p_HasKTP]) {
            // Pendaftaran Pertama Kali di Database Kependudukan
            gPlayerData[playerid][p_HasKTP] = true;

            new query[256];
            format(query, sizeof(query), "UPDATE `characters` SET `has_ktp` = 1 WHERE `id` = %d", gPlayerData[playerid][p_CharID]);
            DB_FreeResultSet(DB_ExecuteQuery(gDB, query));

            // Berikan fisik kartu e-KTP ke inventory
            Inventory_AddItem(playerid, ITEM_KTP, 1);

            PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
            GameTextForPlayer(playerid, "~g~e-KTP Berhasil Diterbitkan!", 4000, 3);

            SendClientMessage(playerid, COL_GREEN, "  [[OK]] Selamat! Identitas Anda resmi terdaftar di database kependudukan.");
            SendClientMessage(playerid, COL_CYAN,  "  [+] Fisik kartu {00EEFF}e-KTP{FFFFFF} telah dimasukkan ke dalam kantong / tas Anda.");
            SendClientMessage(playerid, COL_WHITE, "  [!] Gunakan {00EEFF}/ktp{FFFFFF} untuk melihat atau {00EEFF}/ktp [id]{FFFFFF} untuk memperlihatkan ke orang lain.");

            new charname[48], rpMsg[160];
            GetCharName(playerid, charname);
            format(rpMsg, sizeof(rpMsg), "%s menerima fisik kartu e-KTP resmi yang baru diterbitkan dari petugas loket catatan sipil.", charname);
            DoProximityRaw(playerid, rpMsg, DIST_RP, COL_PURPLE);

            ShowPlayerKTPCard(playerid, playerid);
            return 1;
        } else {
            // Sudah terdaftar, cek apakah kartu fisiknya ada di tas
            if (!Inventory_HasItem(playerid, ITEM_KTP)) {
                Inventory_AddItem(playerid, ITEM_KTP, 1);
                PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
                SendClientMessage(playerid, COL_GREEN, "  [KTP] Petugas mencetak ulang fisik kartu e-KTP Anda dan memasukkannya ke tas Anda.");

                new charname[48], rpMsg[160];
                GetCharName(playerid, charname);
                format(rpMsg, sizeof(rpMsg), "%s menerima duplikat fisik kartu e-KTP resmi dari petugas loket catatan sipil.", charname);
                DoProximityRaw(playerid, rpMsg, DIST_RP, COL_PURPLE);

                ShowPlayerKTPCard(playerid, playerid);
                return 1;
            } else {
                ShowPlayerKTPCard(playerid, playerid);
                SendClientMessage(playerid, COL_GREEN, "  [KTP] Anda sudah memiliki e-KTP resmi terdaftar dan membawa fisik kartunya di tas.");
                return 1;
            }
        }
    }

    // 2. Cek apakah karakter sudah terdaftar di database kependudukan
    if (!gPlayerData[playerid][p_HasKTP]) {
        SendClientMessage(playerid, COL_RED, "  [!] Karakter Anda belum memiliki e-KTP terdaftar di Balai Kota!");
        SendClientMessage(playerid, COL_WHITE, "  [!] Silakan kunjungi {33CCFF}Balai Kota (Pershing Square){FFFFFF} dan buat KTP di Loket Catatan Sipil.");
        return 1;
    }

    // 3. Cek apakah karakter membawa fisik kartu e-KTP di inventory
    if (!Inventory_HasItem(playerid, ITEM_KTP)) {
        SendClientMessage(playerid, COL_RED, "  [!] Anda tidak membawa fisik kartu e-KTP di kantong/tas Anda!");
        SendClientMessage(playerid, COL_WHITE, "  [!] Kunjungi {33CCFF}Loket Catatan Sipil Balai Kota{FFFFFF} untuk mencetak ulang fisik kartu Anda.");
        return 1;
    }

    // 4. Jika ada parameter: Tunjukkan KTP ke pemain terdekat (/ktp [id])
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

        format(msg, sizeof(msg), "* %s mengambil KTP miliknya dari dompet dan memperlihatkannya kepada %s.", myName, targetName);
        DoProximitySay(playerid, msg, DIST_VOICE, COL_PURPLE, false);
        return 1;
    }

    // 5. Jika tanpa parameter: Buka kartu e-KTP milik sendiri
    ShowPlayerKTPCard(playerid, playerid);
    SendClientMessage(playerid, COL_GREEN, "  [KTP] Membuka fisik Kartu Tanda Penduduk (e-KTP) dari dompet Anda.");
    return 1;
}

CMD:showktp(playerid, params[]) {
    return cmd_ktp(playerid, params);
}
