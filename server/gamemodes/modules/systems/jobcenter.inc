#if defined _MODULE_JOBCENTER_INC
    #endinput
#endif
#define _MODULE_JOBCENTER_INC

// ============================================================
//  SantaraBaru Roleplay - Job Center (Pusat Tenaga Kerja)
//  Lokasi: Balai Kota Los Santos Interior (Int: 3, VW: 0)
//  Koordinat: 361.1137, 171.3065, 1008.3828 (Job Center Desk)
// ============================================================

new Text3D:gJobCenterLabel;
new gJobCenterPickup;

stock InitJobCenterSystem() {
    // 3D Text Label di meja Job Center Balai Kota
    gJobCenterLabel = Create3DTextLabel(
        "{00EEFF}[ PUSAT TENAGA KERJA / JOB CENTER ]\n" \
        "{FFFFFF}Daftar Lowongan Pekerjaan Resmi Kota\n" \
        "{FFFF00}Tekan [ F / ENTER ] atau ketik {00EEFF}/job",
        COL_CYAN,
        JOBCENTER_X, JOBCENTER_Y, JOBCENTER_Z + 0.6,
        15.0, JOBCENTER_VW_ID, 1
    );

    // Pickup Information (ID 1239)
    gJobCenterPickup = CreatePickup(1239, 1, JOBCENTER_X, JOBCENTER_Y, JOBCENTER_Z, JOBCENTER_VW_ID);

    print("[Job Center] Pusat Tenaga Kerja di Balai Kota berhasil diinisialisasi.");
    return 1;
}

stock bool:IsPlayerAtJobCenter(playerid) {
    if (!IsPlayerConnected(playerid) || !gPlayerData[playerid][p_Spawned]) return false;
    if (GetPlayerInterior(playerid) != JOBCENTER_INT_ID || GetPlayerVirtualWorld(playerid) != JOBCENTER_VW_ID) return false;
    return IsPlayerInRangeOfPoint(playerid, 1.8, JOBCENTER_X, JOBCENTER_Y, JOBCENTER_Z);
}

stock ShowJobCenterMenu(playerid) {
    if (!CheckSpawned(playerid)) return 0;

    new curJobName[32];
    if (gPlayerData[playerid][p_Job] == 1) format(curJobName, sizeof(curJobName), "Penambang (Miner)");
    else format(curJobName, sizeof(curJobName), "Pengangguran");

    new dialogStr[1024];
    format(dialogStr, sizeof(dialogStr),
        "Pekerjaan Resmi\tGaji Pokok\tKeterangan\n" \
        "{FF6666}1. Pengangguran{FFFFFF}\tRp. 0\tMengundurkan diri dari pekerjaan saat ini\n" \
        "{00EEFF}2. Penambang (Miner){FFFFFF}\tHasil Tambang\tAkses GPS Tambang Hunter Quarry & Smelter Peleburan");

    new headerStr[128];
    format(headerStr, sizeof(headerStr), "{00EEFF}Pusat Tenaga Kerja - Pekerjaan Anda: {FFFF00}%s", curJobName);

    ShowPlayerDialog(playerid, DLG_JOBCENTER_MAIN, DIALOG_STYLE_TABLIST_HEADERS,
        headerStr, dialogStr, "Pilih", "Batal");
    return 1;
}

stock HandleJobCenterDialog(playerid, dialogid, response, listitem) {
    if (dialogid != DLG_JOBCENTER_MAIN) return 0;
    if (!response) return 1;

    switch (listitem) {
        case 0: { // Pengangguran / Keluar Pekerjaan
            if (gPlayerData[playerid][p_Job] == 0) {
                SendClientMessage(playerid, COL_YELLOW, "  [Job Center] Anda saat ini memang berstatus sebagai Pengangguran.");
                return 1;
            }

            gPlayerData[playerid][p_Job] = 0;

            // Update SQLite
            new query[128];
            format(query, sizeof(query), "UPDATE `characters` SET `job_id`=0 WHERE `id`=%d", gPlayerData[playerid][p_CharID]);
            DB_FreeResultSet(DB_ExecuteQuery(gDB, query));

            UpdatePlayerMoneyHUD(playerid);
            PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);

            SendClientMessage(playerid, COL_GREEN, "  [Job Center] Anda telah mengundurkan diri dan kini berstatus {FF6666}Pengangguran{FFFFFF}.");
            
            new charname[48], rpMsg[144];
            GetCharName(playerid, charname);
            format(rpMsg, sizeof(rpMsg), "* %s menandatangani formulir pengunduran diri di meja Job Center.", charname);
            DoProximitySay(playerid, rpMsg, DIST_RP, COL_PURPLE, false);
        }
        case 1: { // Penambang (Miner)
            if (gPlayerData[playerid][p_Job] == 1) {
                SendClientMessage(playerid, COL_YELLOW, "  [Job Center] Anda sudah bekerja sebagai Penambang (Miner).");
                return 1;
            }

            gPlayerData[playerid][p_Job] = 1;

            // Update SQLite
            new query[128];
            format(query, sizeof(query), "UPDATE `characters` SET `job_id`=1 WHERE `id`=%d", gPlayerData[playerid][p_CharID]);
            DB_FreeResultSet(DB_ExecuteQuery(gDB, query));

            UpdatePlayerMoneyHUD(playerid);
            PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);

            SendClientMessage(playerid, COL_GREEN, "  [Job Center] Selamat! Anda resmi diterima bekerja sebagai {00EEFF}Penambang (Miner){FFFFFF}!");
            SendClientMessage(playerid, COL_CYAN, "  [Job Center] Lokasi {FFFF00}Hunter Quarry{00EEFF} dan {FF6600}Smelter Pabrik{00EEFF} kini dapat Anda akses via {FFFF00}/gps{00EEFF}.");

            new charname[48], rpMsg[144];
            GetCharName(playerid, charname);
            format(rpMsg, sizeof(rpMsg), "* %s mendaftarkan diri dan mengambil surat kontrak kerja Penambang di Job Center.", charname);
            DoProximitySay(playerid, rpMsg, DIST_RP, COL_PURPLE, false);
        }
    }
    return 1;
}
