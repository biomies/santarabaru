#if defined _MODULE_CMD_IDENTITY_INC
    #endinput
#endif
#define _MODULE_CMD_IDENTITY_INC

// ============================================================
//  SantaraBaru Roleplay - Identity Command (/buatktp)
// ============================================================

CMD:buatktp(playerid, params[]) {
    #pragma unused params
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
            SendClientMessage(playerid, COL_WHITE, "  [!] Gunakan {00EEFF}/dokumen{FFFFFF} untuk melihat atau memperlihatkan ke orang lain.");

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
                SendClientMessage(playerid, COL_GREEN, "  [KTP] Anda sudah memiliki e-KTP resmi terdaftar dan membawa fisik kartunya di tas.");
                return 1;
            }
        }
    } else {
        SendClientMessage(playerid, COL_RED, "  [!] Anda harus berada di Loket Catatan Sipil Balai Kota untuk membuat KTP!");
        return 1;
    }
}
