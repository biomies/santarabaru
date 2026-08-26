#if defined _MODULE_CMD_ADMIN_INC
    #endinput
#endif
#define _MODULE_CMD_ADMIN_INC

// ============================================================
//  SantaraBaru Roleplay - In-Game Admin Management Module
//  Tingkatan Level Admin:
//    Level 0 : Regular Player
//    Level 1 : Admin (Operasional, Utilitas, Uang, & Mobil)
//    Level 2 : Owner / SuperAdmin (Akses Penuh + Kelola Staff)
// ============================================================

stock IsAdmin(playerid, minLevel = 1) {
    if (IsPlayerAdmin(playerid)) return 1; // RCON Admin bypass
    if (gPlayerData[playerid][p_AdminLevel] >= minLevel) return 1;
    return 0;
}

//    1. Bantuan Perintah Admin (/ahelp)                       

CMD:ahelp(playerid, params[]) {
    #pragma unused params
    if (!IsAdmin(playerid, 1)) {
        SendClientMessage(playerid, COL_RED, "  [Error] Anda tidak memiliki izin untuk menggunakan perintah administrator!");
        return 1;
    }

    SendClientMessage(playerid, COL_WHITE, "  [ {E69958}PANEL PERINTAH ADMINISTRATOR SANTARA {FFFFFF}]");
    SendClientMessage(playerid, COL_WHITE, "  > {E69958}Level 1 - Staff Administrator:");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/aduty                   {A0AEC0}- Aktifkan / nonaktifkan mode On-Duty Admin");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/a {FFFFFF}[pesan]            {A0AEC0}- Chat internal sesama admin");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/givemoney {FFFFFF}[id] [jml] {A0AEC0}- Beri / tambah uang ke karakter pemain");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/setmoney {FFFFFF}[id] [jml]  {A0AEC0}- Atur saldo uang karakter pemain");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/vehlist {FFFFFF}[id/target]  {A0AEC0}- Lihat daftar DB ID & kendaraan milik pemain");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/delveh {FFFFFF}[db_id/here]  {A0AEC0}- Hapus kendaraan dari kepemilikan pemain & DB");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/goto {FFFFFF}[id]            {A0AEC0}- Teleport langsung ke lokasi pemain");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/gethere {FFFFFF}[id]         {A0AEC0}- Tarik pemain langsung ke hadapan admin");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/tpgps (atau /tp)        {A0AEC0}- Menu teleport instan ke seluruh titik GPS peta");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/veh {FFFFFF}[model] [c1] [c2]{A0AEC0}- Spawn kendaraan dinamis admin");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/destroyveh              {A0AEC0}- Hapus kendaraan yang sedang dinaiki admin");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/heal {FFFFFF}[id]            {A0AEC0}- Pulihkan 100% darah & armor pemain");

    if (IsAdmin(playerid, 2)) {
        SendClientMessage(playerid, COL_WHITE, "  > {E69958}Level 2 - Owner / SuperAdmin:");
        SendClientMessage(playerid, COL_WHITE, "     {F1C40F}/setadmin {FFFFFF}[id/user] [0-2]{A0AEC0}- Mengangkat / mengubah level admin akun pemain");
    }
    return 1;
}

//    2. Admin Duty & Admin Chat                               

CMD:aduty(playerid, params[]) {
    #pragma unused params
    if (!IsAdmin(playerid, 1)) return 1;

    gPlayerData[playerid][p_AdminDuty] = !gPlayerData[playerid][p_AdminDuty];

    new msg[144], name[MAX_PLAYER_NAME + 1];
    GetPlayerName(playerid, name, sizeof(name));

    if (gPlayerData[playerid][p_AdminDuty]) {
        SetPlayerHealth(playerid, 100.0);
        SetPlayerArmour(playerid, 100.0);
        format(msg, sizeof(msg), "  [Admin Duty] {00EEFF}%s {FFFFFF}sekarang sedang {2ECC71}ON-DUTY {FFFFFF}sebagai Administrator Server.", name);
        SendClientMessageToAll(COL_CYAN, msg);
    } else {
        format(msg, sizeof(msg), "  [Admin Duty] {00EEFF}%s {FFFFFF}sekarang {E74C3C}OFF-DUTY {FFFFFF}dari tugas Administrator Server.", name);
        SendClientMessageToAll(COL_GREY, msg);
    }
    return 1;
}

CMD:a(playerid, params[]) {
    if (!IsAdmin(playerid, 1)) return 1;
    if (!strlen(params)) {
        SendClientMessage(playerid, COL_YELLOW, "  Gunakan: /a [pesan admin chat]");
        return 1;
    }

    new name[MAX_PLAYER_NAME + 1], rankStr[32], aMsg[256];
    GetPlayerName(playerid, name, sizeof(name));

    if (gPlayerData[playerid][p_AdminLevel] >= 2) {
        format(rankStr, sizeof(rankStr), "Owner");
    } else {
        format(rankStr, sizeof(rankStr), "Admin");
    }

    format(aMsg, sizeof(aMsg), "  [ADMIN CHAT] (%s) %s: {FFFFFF}%s", rankStr, name, params);

    for (new i = 0; i < MAX_PLAYERS; i++) {
        if (IsPlayerConnected(i) && IsAdmin(i, 1)) {
            SendClientMessage(i, 0xF39C12FF, aMsg);
        }
    }
    return 1;
}

//    3. Manajemen Ekonomi Uang Pemain                         

CMD:givemoney(playerid, params[]) {
    if (!IsAdmin(playerid, 1)) {
        SendClientMessage(playerid, COL_RED, "  [Error] Anda tidak memiliki izin untuk menggunakan perintah ini!");
        return 1;
    }

    new targetid, amount;
    if (sscanf(params, "ud", targetid, amount)) {
        SendClientMessage(playerid, COL_YELLOW, "  Gunakan: /givemoney [playerid/nama] [jumlah uang]");
        return 1;
    }

    if (!IsPlayerConnected(targetid) || !gPlayerData[targetid][p_Spawned]) {
        SendClientMessage(playerid, COL_RED, "  [Error] Pemain target tidak ditemukan atau belum login!");
        return 1;
    }

    gPlayerData[targetid][p_Cash] += amount;
    if (gPlayerData[targetid][p_Cash] < 0) gPlayerData[targetid][p_Cash] = 0;

    // Simpan ke database karakter target
    new query[128];
    format(query, sizeof(query), "UPDATE `characters` SET `cash`=%d WHERE `id`=%d",
        gPlayerData[targetid][p_Cash], gPlayerData[targetid][p_CharID]);
    DB_FreeResultSet(DB_ExecuteQuery(gDB, query));

    // Update HUD uang pemain target
    UpdatePlayerMoneyHUD(targetid);
    PlayerPlaySound(targetid, 1052, 0.0, 0.0, 0.0);

    // Format Rupiah
    new amtFmt[32], totalFmt[32], targetName[48], adminName[MAX_PLAYER_NAME + 1];
    FormatRupiah(amount, amtFmt, sizeof(amtFmt));
    FormatRupiah(gPlayerData[targetid][p_Cash], totalFmt, sizeof(totalFmt));
    GetCharName(targetid, targetName);
    GetPlayerName(playerid, adminName, sizeof(adminName));

    new msgAdmin[144], msgTarget[144];
    format(msgAdmin, sizeof(msgAdmin), "  [Admin] Anda memberikan %s ke %s (Saldo baru: %s).", amtFmt, targetName, totalFmt);
    SendClientMessage(playerid, COL_GREEN, msgAdmin);

    format(msgTarget, sizeof(msgTarget), "  [Admin] Administrator %s telah menambahkan %s ke saldo dompet Anda (Total: %s).", adminName, amtFmt, totalFmt);
    SendClientMessage(targetid, COL_GREEN, msgTarget);
    return 1;
}

CMD:setmoney(playerid, params[]) {
    if (!IsAdmin(playerid, 1)) {
        SendClientMessage(playerid, COL_RED, "  [Error] Anda tidak memiliki izin untuk menggunakan perintah ini!");
        return 1;
    }

    new targetid, amount;
    if (sscanf(params, "ud", targetid, amount)) {
        SendClientMessage(playerid, COL_YELLOW, "  Gunakan: /setmoney [playerid/nama] [jumlah uang]");
        return 1;
    }

    if (!IsPlayerConnected(targetid) || !gPlayerData[targetid][p_Spawned]) {
        SendClientMessage(playerid, COL_RED, "  [Error] Pemain target tidak ditemukan atau belum login!");
        return 1;
    }

    if (amount < 0) amount = 0;
    gPlayerData[targetid][p_Cash] = amount;

    // Simpan ke database karakter target
    new query[128];
    format(query, sizeof(query), "UPDATE `characters` SET `cash`=%d WHERE `id`=%d",
        gPlayerData[targetid][p_Cash], gPlayerData[targetid][p_CharID]);
    DB_FreeResultSet(DB_ExecuteQuery(gDB, query));

    // Update HUD uang pemain target
    UpdatePlayerMoneyHUD(targetid);
    PlayerPlaySound(targetid, 1052, 0.0, 0.0, 0.0);

    new amtFmt[32], targetName[48], adminName[MAX_PLAYER_NAME + 1];
    FormatRupiah(amount, amtFmt, sizeof(amtFmt));
    GetCharName(targetid, targetName);
    GetPlayerName(playerid, adminName, sizeof(adminName));

    new msgAdmin[144], msgTarget[144];
    format(msgAdmin, sizeof(msgAdmin), "  [Admin] Anda mengatur saldo dompet %s menjadi %s.", targetName, amtFmt);
    SendClientMessage(playerid, COL_GREEN, msgAdmin);

    format(msgTarget, sizeof(msgTarget), "  [Admin] Administrator %s telah mengatur saldo dompet Anda menjadi %s.", adminName, amtFmt);
    SendClientMessage(targetid, COL_GREEN, msgTarget);
    return 1;
}

//    4. Manajemen Kendaraan Pribadi Pemain In-Game             

CMD:vehlist(playerid, params[]) {
    if (!IsAdmin(playerid, 1)) {
        SendClientMessage(playerid, COL_RED, "  [Error] Anda tidak memiliki izin untuk menggunakan perintah ini!");
        return 1;
    }

    new targetid;
    if (sscanf(params, "u", targetid)) {
        SendClientMessage(playerid, COL_YELLOW, "  Gunakan: /vehlist [playerid/nama]");
        return 1;
    }

    if (!IsPlayerConnected(targetid) || !gPlayerData[targetid][p_Spawned]) {
        SendClientMessage(playerid, COL_RED, "  [Error] Pemain target tidak ditemukan atau belum login!");
        return 1;
    }

    new targetName[48];
    GetCharName(targetid, targetName);

    new query[256];
    format(query, sizeof(query),
        "SELECT `id`, `model_id`, `plate`, `status`, `garage_id` FROM `player_vehicles` WHERE `char_id`=%d ORDER BY `id` ASC",
        gPlayerData[targetid][p_CharID]);

    new DBResult:res = DB_ExecuteQuery(gDB, query);
    new count = 0;
    if (res) count = DB_GetRowCount(res);

    if (count == 0) {
        if (res) DB_FreeResultSet(res);
        SendClientMessage(playerid, COL_RED, "  [Kendaraan] Pemain target tidak memiliki kendaraan terdaftar di database.");
        return 1;
    }

    SendClientMessage(playerid, COL_WHITE, " ");
    new headerMsg[128];
    format(headerMsg, sizeof(headerMsg), "  [ {E69958}DAFTAR KENDARAAN PEMAIN: {FFFFFF}%s (Char ID: %d) ]", targetName, gPlayerData[targetid][p_CharID]);
    SendClientMessage(playerid, COL_CYAN, headerMsg);

    for (new i = 0; i < count; i++) {
        new dbId     = DB_GetFieldIntByName(res, "id");
        new modelId  = DB_GetFieldIntByName(res, "model_id");
        new vStatus  = DB_GetFieldIntByName(res, "status");
        new gid      = DB_GetFieldIntByName(res, "garage_id");
        new plate[16];
        DB_GetFieldStringByName(res, "plate", plate, sizeof(plate));

        new vName[32];
        GetModelFullName(modelId, vName, sizeof(vName));

        new statusStr[48];
        if (vStatus == VEH_STATUS_GARAGE) {
            format(statusStr, sizeof(statusStr), "{2ECC71}Garasi #%d", gid + 1);
        } else if (vStatus == VEH_STATUS_OUTSIDE) {
            format(statusStr, sizeof(statusStr), "{F1C40F}Di Luar / Aktif");
        } else {
            format(statusStr, sizeof(statusStr), "{E74C3C}Asuransi");
        }

        new rowMsg[144];
        format(rowMsg, sizeof(rowMsg), "  > {FFFF00}[DB ID: %d]{FFFFFF} %s | Plat: {00EEFF}%s{FFFFFF} | Status: %s",
            dbId, vName, plate, statusStr);
        SendClientMessage(playerid, COL_WHITE, rowMsg);
        DB_SelectNextRow(res);
    }
    DB_FreeResultSet(res);
    SendClientMessage(playerid, COL_GREY, "  * Tip: Gunakan {FFFFFF}/delveh [DB ID]{A0AEC0} untuk menghapus kepemilikan kendaraan secara permanen.");
    return 1;
}

CMD:delveh(playerid, params[]) {
    if (!IsAdmin(playerid, 1)) {
        SendClientMessage(playerid, COL_RED, "  [Error] Anda tidak memiliki izin untuk menggunakan perintah ini!");
        return 1;
    }

    if (!strlen(params)) {
        SendClientMessage(playerid, COL_YELLOW, "  Gunakan: /delveh [db_id / 'here']");
        SendClientMessage(playerid, COL_GREY, "  > /delveh [db_id]  : Hapus kendaraan berdasarkan Database ID (Cek /vehlist)");
        SendClientMessage(playerid, COL_GREY, "  > /delveh here     : Hapus kendaraan pemain yang sedang Anda naiki");
        return 1;
    }

    new targetDBID = 0;

    if (!strcmp(params, "here", true)) {
        if (!IsPlayerInAnyVehicle(playerid)) {
            SendClientMessage(playerid, COL_RED, "  [Error] Anda harus berada di dalam kendaraan pemain yang ingin dihapus!");
            return 1;
        }

        new currentVeh = GetPlayerVehicleID(playerid);
        // Cari DB ID kendaraan aktif dari pemain yang sedang online
        for (new p = 0; p < MAX_PLAYERS; p++) {
            if (IsPlayerConnected(p)) {
                new slot = GetPlayerActiveVehSlot(p, currentVeh);
                if (slot != -1) {
                    targetDBID = gPlayerData[p][p_ActiveVehDBID][slot];
                    break;
                }
            }
        }

        if (targetDBID == 0) {
            SendClientMessage(playerid, COL_RED, "  [Error] Kendaraan ini bukan kendaraan pribadi pemain (atau gunakan ID database langsung).");
            return 1;
        }
    } else {
        targetDBID = strval(params);
    }

    if (targetDBID <= 0) {
        SendClientMessage(playerid, COL_RED, "  [Error] Database ID kendaraan tidak valid!");
        return 1;
    }

    // Periksa apakah kendaraan terdaftar di database
    new checkQ[128];
    format(checkQ, sizeof(checkQ), "SELECT `char_id`, `model_id`, `plate` FROM `player_vehicles` WHERE `id`=%d LIMIT 1", targetDBID);
    new DBResult:res = DB_ExecuteQuery(gDB, checkQ);
    if (!res || DB_GetRowCount(res) == 0) {
        if (res) DB_FreeResultSet(res);
        SendClientMessage(playerid, COL_RED, "  [Error] Kendaraan dengan Database ID tersebut tidak ditemukan di database!");
        return 1;
    }

    new ownerCharID = DB_GetFieldIntByName(res, "char_id");
    new modelId     = DB_GetFieldIntByName(res, "model_id");
    new plate[16];
    DB_GetFieldStringByName(res, "plate", plate, sizeof(plate));
    DB_FreeResultSet(res);

    // Jika pemilik sedang online dan kendaraan aktif, hancurkan objeknya
    for (new p = 0; p < MAX_PLAYERS; p++) {
        if (IsPlayerConnected(p) && gPlayerData[p][p_CharID] == ownerCharID) {
            new slot = GetPlayerActiveVehSlotByDBID(p, targetDBID);
            if (slot != -1) {
                new veh = gPlayerData[p][p_ActiveVehID][slot];
                if (veh != INVALID_VEHICLE_ID) DestroyVehicle(veh);
                gPlayerData[p][p_ActiveVehID][slot] = INVALID_VEHICLE_ID;
                gPlayerData[p][p_ActiveVehDBID][slot] = 0;
            }
            SendClientMessage(p, COL_RED, "  [Kendaraan] Kepemilikan kendaraan Anda telah dicabut / dihapus oleh Administrator.");
            break;
        }
    }

    // Hapus permanen dari database
    new delQ[128];
    format(delQ, sizeof(delQ), "DELETE FROM `player_vehicles` WHERE `id`=%d", targetDBID);
    DB_FreeResultSet(DB_ExecuteQuery(gDB, delQ));

    new vName[32], successMsg[160];
    GetModelFullName(modelId, vName, sizeof(vName));
    format(successMsg, sizeof(successMsg), "  [Admin] Sukses menghapus permanen kendaraan %s (Plat: %s, DB ID: %d) dari database!",
        vName, plate, targetDBID);
    SendClientMessage(playerid, COL_GREEN, successMsg);
    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
    return 1;
}

//    5. Spawn Kendaraan Dinamis Admin                         

CMD:veh(playerid, params[]) {
    if (!IsAdmin(playerid, 1)) {
        SendClientMessage(playerid, COL_RED, "  [Error] Anda tidak memiliki izin untuk menggunakan perintah ini!");
        return 1;
    }

    new model, color1, color2;
    if (sscanf(params, "dI(1)I(1)", model, color1, color2)) {
        SendClientMessage(playerid, COL_YELLOW, "  Gunakan: /veh [model_id 400-611] [color1] [color2]");
        return 1;
    }

    if (model < 400 || model > 611) {
        SendClientMessage(playerid, COL_RED, "  [Error] Model kendaraan harus antara ID 400 sampai 611!");
        return 1;
    }

    new Float:x, Float:y, Float:z, Float:a;
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, a);

    new vehId = CreateVehicle(model, x + (2.0 * floatsin(-a, degrees)), y + (2.0 * floatcos(-a, degrees)), z + 0.5, a, color1, color2, -1);
    if (vehId == INVALID_VEHICLE_ID) {
        SendClientMessage(playerid, COL_RED, "  [Error] Gagal men-spawn kendaraan dinamis!");
        return 1;
    }

    SetVehicleNumberPlate(vehId, "ADMIN");
    SetVehicleToRespawn(vehId);
    SetVehiclePos(vehId, x, y, z + 0.5);
    SetVehicleParamsEx(vehId, 1, 0, 0, 0, 0, 0, 0); // Mesin langsung menyala
    PutPlayerInVehicle(playerid, vehId, 0);

    new vName[32], msg[128];
    GetModelFullName(model, vName, sizeof(vName));
    format(msg, sizeof(msg), "  [Admin] Anda men-spawn %s (ID Model: %d, Kendaraan ID: %d).", vName, model, vehId);
    SendClientMessage(playerid, COL_GREEN, msg);
    return 1;
}

CMD:destroyveh(playerid, params[]) {
    #pragma unused params
    if (!IsAdmin(playerid, 1)) return 1;

    if (!IsPlayerInAnyVehicle(playerid)) {
        SendClientMessage(playerid, COL_RED, "  [Error] Anda harus berada di dalam kendaraan dinamis yang ingin dihancurkan!");
        return 1;
    }

    new vehId = GetPlayerVehicleID(playerid);
    DestroyVehicle(vehId);
    SendClientMessage(playerid, COL_GREEN, "  [Admin] Kendaraan dinamis berhasil dihapus dari dunia game.");
    return 1;
}

//    6. Teleportasi & Utilitas Admin                          

CMD:goto(playerid, params[]) {
    if (!IsAdmin(playerid, 1)) return 1;

    new targetid;
    if (sscanf(params, "u", targetid)) {
        SendClientMessage(playerid, COL_YELLOW, "  Gunakan: /goto [playerid/nama]");
        return 1;
    }

    if (!IsPlayerConnected(targetid) || !gPlayerData[targetid][p_Spawned]) {
        SendClientMessage(playerid, COL_RED, "  [Error] Pemain target tidak ditemukan atau belum spawn!");
        return 1;
    }

    new Float:tx, Float:ty, Float:tz;
    GetPlayerPos(targetid, tx, ty, tz);
    SetPlayerInterior(playerid, GetPlayerInterior(targetid));
    SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));
    SetPlayerPos(playerid, tx + 1.0, ty + 1.0, tz + 0.5);

    new targetName[48], msg[128];
    GetCharName(targetid, targetName);
    format(msg, sizeof(msg), "  [Admin] Anda teleport ke posisi %s.", targetName);
    SendClientMessage(playerid, COL_GREEN, msg);
    return 1;
}

CMD:gethere(playerid, params[]) {
    if (!IsAdmin(playerid, 1)) return 1;

    new targetid;
    if (sscanf(params, "u", targetid)) {
        SendClientMessage(playerid, COL_YELLOW, "  Gunakan: /gethere [playerid/nama]");
        return 1;
    }

    if (!IsPlayerConnected(targetid) || !gPlayerData[targetid][p_Spawned]) {
        SendClientMessage(playerid, COL_RED, "  [Error] Pemain target tidak ditemukan atau belum spawn!");
        return 1;
    }

    new Float:ax, Float:ay, Float:az;
    GetPlayerPos(playerid, ax, ay, az);
    SetPlayerInterior(targetid, GetPlayerInterior(playerid));
    SetPlayerVirtualWorld(targetid, GetPlayerVirtualWorld(playerid));
    SetPlayerPos(targetid, ax + 1.0, ay + 1.0, az + 0.5);

    new targetName[48], adminName[MAX_PLAYER_NAME + 1];
    GetCharName(targetid, targetName);
    GetPlayerName(playerid, adminName, sizeof(adminName));

    new msgAdmin[128], msgTarget[128];
    format(msgAdmin, sizeof(msgAdmin), "  [Admin] Anda menarik %s ke hadapan Anda.", targetName);
    SendClientMessage(playerid, COL_GREEN, msgAdmin);

    format(msgTarget, sizeof(msgTarget), "  [Admin] Anda telah diteleport ke hadapan Administrator %s.", adminName);
    SendClientMessage(targetid, COL_YELLOW, msgTarget);
    return 1;
}

CMD:heal(playerid, params[]) {
    if (!IsAdmin(playerid, 1)) return 1;

    new targetid;
    if (sscanf(params, "U(-1)", targetid)) {
        targetid = playerid;
    }
    if (targetid == -1) targetid = playerid;

    if (!IsPlayerConnected(targetid) || !gPlayerData[targetid][p_Spawned]) {
        SendClientMessage(playerid, COL_RED, "  [Error] Pemain target tidak ditemukan!");
        return 1;
    }

    SetPlayerHealth(targetid, 100.0);
    SetPlayerArmour(targetid, 100.0);

    new targetName[48];
    GetCharName(targetid, targetName);

    new msg[128];
    format(msg, sizeof(msg), "  [Admin] Memulihkan 100 persen Health & Armour untuk %s.", targetName);
    SendClientMessage(playerid, COL_GREEN, msg);
    return 1;
}

//    7. Pengelolaan Staff Admin (/setadmin) - Level 2 (Owner)  

CMD:setadmin(playerid, params[]) {
    if (!IsAdmin(playerid, 2)) {
        SendClientMessage(playerid, COL_RED, "  [Error] Hanya Owner / SuperAdmin yang dapat mengatur level administrator!");
        return 1;
    }

    new targetid, level;
    if (sscanf(params, "ud", targetid, level)) {
        SendClientMessage(playerid, COL_YELLOW, "  Gunakan: /setadmin [playerid/nama] [level 0-2]");
        SendClientMessage(playerid, COL_GREY, "  > Level 0: Regular Player | Level 1: Admin | Level 2: Owner");
        return 1;
    }

    if (!IsPlayerConnected(targetid) || !gPlayerData[targetid][p_LoggedIn]) {
        SendClientMessage(playerid, COL_RED, "  [Error] Pemain target tidak ditemukan atau belum login!");
        return 1;
    }

    if (level < 0 || level > 2) {
        SendClientMessage(playerid, COL_RED, "  [Error] Level admin harus antara 0 sampai 2!");
        return 1;
    }

    gPlayerData[targetid][p_AdminLevel] = level;

    // Simpan ke tabel parent accounts
    new query[128];
    format(query, sizeof(query), "UPDATE `accounts` SET `admin_level`=%d WHERE `id`=%d",
        level, gPlayerData[targetid][p_AccountID]);
    DB_FreeResultSet(DB_ExecuteQuery(gDB, query));

    new targetUser[MAX_PLAYER_NAME + 1], adminName[MAX_PLAYER_NAME + 1];
    GetPlayerName(targetid, targetUser, sizeof(targetUser));
    GetPlayerName(playerid, adminName, sizeof(adminName));

    new levelTitle[32];
    if (level == 2) format(levelTitle, sizeof(levelTitle), "Owner / SuperAdmin");
    else if (level == 1) format(levelTitle, sizeof(levelTitle), "Administrator");
    else format(levelTitle, sizeof(levelTitle), "Regular Player");

    new msgAdmin[144], msgTarget[144];
    format(msgAdmin, sizeof(msgAdmin), "  [Admin] Anda mengatur level admin akun %s menjadi Level %d (%s).", targetUser, level, levelTitle);
    SendClientMessage(playerid, COL_GREEN, msgAdmin);

    format(msgTarget, sizeof(msgTarget), "  [Admin] Administrator %s telah mengubah status akun Anda menjadi: {00EEFF}%s (Level %d).", adminName, levelTitle, level);
    SendClientMessage(targetid, COL_CYAN, msgTarget);
    return 1;
}

//    8. Server Console RCON Commands (Terminal Live Sync)     

stock HandleRconAdminCommand(cmd[]) {
    new command[32], params[128];
    if (sscanf(cmd, "s[32]S()[128]", command, params)) {
        return 0;
    }

    if (!strcmp(command, "givemoney", true)) {
        new targetid, amount;
        if (sscanf(params, "ud", targetid, amount)) {
            print("[Console] Gunakan: givemoney [playerid/nama] [jumlah]");
            return 1;
        }
        if (IsPlayerConnected(targetid) && gPlayerData[targetid][p_Spawned]) {
            gPlayerData[targetid][p_Cash] += amount;
            if (gPlayerData[targetid][p_Cash] < 0) gPlayerData[targetid][p_Cash] = 0;
            new q[128];
            format(q, sizeof(q), "UPDATE `characters` SET `cash`=%d WHERE `id`=%d", gPlayerData[targetid][p_Cash], gPlayerData[targetid][p_CharID]);
            DB_FreeResultSet(DB_ExecuteQuery(gDB, q));
            UpdatePlayerMoneyHUD(targetid);
            PlayerPlaySound(targetid, 1052, 0.0, 0.0, 0.0);

            new amtFmt[32], totFmt[32], tName[48];
            FormatRupiah(amount, amtFmt, sizeof(amtFmt));
            FormatRupiah(gPlayerData[targetid][p_Cash], totFmt, sizeof(totFmt));
            GetCharName(targetid, tName);

            printf("[Console] Berhasil memberikan %s kepada %s (Saldo: %s).", amtFmt, tName, totFmt);
            new msg[144];
            format(msg, sizeof(msg), "  [Console Admin] Server Console telah menambahkan %s ke saldo Anda (Total: %s).", amtFmt, totFmt);
            SendClientMessage(targetid, COL_GREEN, msg);
            return 1;
        } else {
            print("[Console] Pemain target tidak ditemukan atau belum login.");
            return 1;
        }
    }
    else if (!strcmp(command, "setmoney", true)) {
        new targetid, amount;
        if (sscanf(params, "ud", targetid, amount)) {
            print("[Console] Gunakan: setmoney [playerid/nama] [jumlah]");
            return 1;
        }
        if (IsPlayerConnected(targetid) && gPlayerData[targetid][p_Spawned]) {
            if (amount < 0) amount = 0;
            gPlayerData[targetid][p_Cash] = amount;
            new q[128];
            format(q, sizeof(q), "UPDATE `characters` SET `cash`=%d WHERE `id`=%d", amount, gPlayerData[targetid][p_CharID]);
            DB_FreeResultSet(DB_ExecuteQuery(gDB, q));
            UpdatePlayerMoneyHUD(targetid);
            PlayerPlaySound(targetid, 1052, 0.0, 0.0, 0.0);

            new amtFmt[32], tName[48];
            FormatRupiah(amount, amtFmt, sizeof(amtFmt));
            GetCharName(targetid, tName);

            printf("[Console] Berhasil mengatur saldo %s menjadi %s.", tName, amtFmt);
            new msg[144];
            format(msg, sizeof(msg), "  [Console Admin] Server Console telah mengatur saldo dompet Anda menjadi %s.", amtFmt);
            SendClientMessage(targetid, COL_GREEN, msg);
            return 1;
        } else {
            print("[Console] Pemain target tidak ditemukan atau belum login.");
            return 1;
        }
    }
    else if (!strcmp(command, "heal", true)) {
        new targetid;
        if (sscanf(params, "u", targetid)) {
            print("[Console] Gunakan: heal [playerid/nama]");
            return 1;
        }
        if (IsPlayerConnected(targetid) && gPlayerData[targetid][p_Spawned]) {
            SetPlayerHealth(targetid, 100.0);
            SetPlayerArmour(targetid, 100.0);
            new tName[48];
            GetCharName(targetid, tName);
            printf("[Console] Sukses memulihkan 100 persen Health & Armour %s.", tName);
            SendClientMessage(targetid, COL_GREEN, "  [Console Admin] Darah dan Armour Anda telah dipulihkan 100% oleh Server Console.");
            return 1;
        } else {
            print("[Console] Pemain target tidak ditemukan atau belum login.");
            return 1;
        }
    }
    else if (!strcmp(command, "setadmin", true)) {
        new targetid, level;
        if (sscanf(params, "ud", targetid, level)) {
            print("[Console] Gunakan: setadmin [playerid/username] [level 0-2]");
            return 1;
        }
        if (level < 0 || level > 2) {
            print("[Console] Level admin harus antara 0 sampai 2.");
            return 1;
        }
        if (IsPlayerConnected(targetid) && gPlayerData[targetid][p_LoggedIn]) {
            gPlayerData[targetid][p_AdminLevel] = level;
            new q[128];
            format(q, sizeof(q), "UPDATE `accounts` SET `admin_level`=%d WHERE `id`=%d", level, gPlayerData[targetid][p_AccountID]);
            DB_FreeResultSet(DB_ExecuteQuery(gDB, q));
            new tUser[MAX_PLAYER_NAME + 1];
            GetPlayerName(targetid, tUser, sizeof(tUser));
            printf("[Console] Berhasil mengatur level admin akun %s menjadi Level %d.", tUser, level);
            new msg[144];
            format(msg, sizeof(msg), "  [Console Admin] Server Console telah mengubah status admin akun Anda menjadi Level %d.", level);
            SendClientMessage(targetid, COL_CYAN, msg);
            return 1;
        } else {
            print("[Console] Pemain target tidak sedang online.");
            return 1;
        }
    }
    return 0;
}

//    9. Admin GPS Waypoint Teleport System                    

stock AdminTeleportToPos(playerid, Float:x, Float:y, Float:z, Float:a = 0.0, intId = 0, vwId = 0, const locationName[] = "") {
    new vehId = GetPlayerVehicleID(playerid);
    new pState = GetPlayerState(playerid);

    SetPlayerInterior(playerid, intId);
    SetPlayerVirtualWorld(playerid, vwId);

    if (vehId != 0 && pState == PLAYER_STATE_DRIVER) {
        SetVehiclePos(vehId, x, y, z + 1.0);
        SetVehicleZAngle(vehId, a);
        LinkVehicleToInterior(vehId, intId);
        SetVehicleVirtualWorld(vehId, vwId);
    } else {
        SetPlayerPos(playerid, x, y, z + 0.5);
        SetPlayerFacingAngle(playerid, a);
    }

    SetCameraBehindPlayer(playerid);
    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);

    new msg[144];
    format(msg, sizeof(msg), "  [Admin Teleport] Berhasil teleport ke: {00EEFF}%s{FFFFFF}.", locationName);
    SendClientMessage(playerid, COL_GREEN, msg);
    return 1;
}

stock ShowAdminTeleportMenu(playerid) {
    if (!IsAdmin(playerid, 1)) return 0;

    new menuStr[768];
    format(menuStr, sizeof(menuStr),
        "Lokasi Fasilitas GPS\tWilayah & Keterangan\n" \
        "{33CCFF}[Balai Kota] Eksterior\t{FFFFFF}Pershing Square, Los Santos\n" \
        "{33CCFF}[Balai Kota] Interior Loket e-KTP\t{FFFFFF}Planning Department Interior\n" \
        "{FFA500}[Burger Shot] 10 Cabang Eksterior\t{FFFFFF}Los Santos, San Fierro, Las Venturas\n" \
        "{FFA500}[Burger Shot] Interior Kasir & Dapur\t{FFFFFF}Interior Restoran Burger Shot (Int: 10)\n" \
        "{00EEFF}[Showroom] Coutt & Schutz\t{FFFFFF}Rodeo / Market, Los Santos\n" \
        "{2ECC71}[Kantor Asuransi] 3 Kota\t{FFFFFF}Los Santos, San Fierro, Las Venturas\n" \
        "{F1C40F}[Parkir Kota] Los Santos Parking Lot\t{FFFFFF}Downtown Los Santos");

    ShowPlayerDialog(playerid, DLG_ADMIN_TELEPORT, DIALOG_STYLE_TABLIST_HEADERS,
        "{E69958}Admin Teleport - Titik Fasilitas GPS", menuStr, "Teleport", "Tutup");
    return 1;
}

stock HandleAdminTeleportDialog(playerid, dialogid, response, listitem) {
    if (dialogid == DLG_ADMIN_TELEPORT) {
        if (!response) return 1;

        switch (listitem) {
            case 0: { // Balai Kota Luar
                AdminTeleportToPos(playerid, CITYHALL_EXT_X, CITYHALL_EXT_Y, CITYHALL_EXT_Z, CITYHALL_EXT_A, 0, 0, "Balai Kota Los Santos (Eksterior)");
            }
            case 1: { // Loket KTP Interior
                AdminTeleportToPos(playerid, KTP_DESK_X, KTP_DESK_Y, KTP_DESK_Z, KTP_DESK_A, KTP_DESK_INT_ID, KTP_DESK_VW_ID, "Loket Pembuatan e-KTP (Interior Balai Kota)");
            }
            case 2: { // Burger Shot 10 Cabang Eksterior
                new bsListStr[1024];
                format(bsListStr, sizeof(bsListStr), "Nama Cabang Restoran\tKota / Wilayah\n");
                for (new i = 0; i < BURGER_SHOT_COUNT; i++) {
                    format(bsListStr, sizeof(bsListStr), "%s{FFFFFF}%s\t{FFA500}%s\n",
                        bsListStr, gBurgerShots[i][bs_Name], gBurgerShots[i][bs_City]);
                }
                ShowPlayerDialog(playerid, DLG_ADMIN_TP_BURGER_SHOT, DIALOG_STYLE_TABLIST_HEADERS,
                    "{FFA500}Pilih Teleport Cabang Burger Shot", bsListStr, "Teleport", "Kembali");
            }
            case 3: { // Burger Shot Interior Kasir & Dapur (Default Cabang Marina LS VW: 101)
                AdminTeleportToPos(playerid, BURGER_SHOT_COUNTER_X, BURGER_SHOT_COUNTER_Y, BURGER_SHOT_COUNTER_Z, 0.0, BURGER_SHOT_INT_ID, BURGER_SHOT_VW_BASE, "Interior Kasir Restoran Burger Shot (VW: 101)");
            }
            case 4: { // Coutt and Schutz Showroom
                AdminTeleportToPos(playerid, DEALER_RODEO_X, DEALER_RODEO_Y, DEALER_RODEO_Z, 90.0, 0, 0, "Coutt and Schutz Auto Showroom (Los Santos)");
            }
            case 5: { // Kantor Asuransi
                new insListStr[512];
                format(insListStr, sizeof(insListStr), "Cabang Asuransi\tKota / Wilayah\n");
                for (new i = 0; i < INSURANCE_BRANCH_COUNT; i++) {
                    format(insListStr, sizeof(insListStr), "%s{FFFFFF}%s\t{2ECC71}%s\n",
                        insListStr, gInsuranceBranches[i][ins_Name], gInsuranceBranches[i][ins_City]);
                }
                ShowPlayerDialog(playerid, DLG_ADMIN_TP_INSURANCE, DIALOG_STYLE_TABLIST_HEADERS,
                    "{2ECC71}Pilih Teleport Cabang Asuransi", insListStr, "Teleport", "Kembali");
            }
            case 6: { // Los Santos Parking Lot
                AdminTeleportToPos(playerid, gPublicGarages[0][g_MarkerX], gPublicGarages[0][g_MarkerY], gPublicGarages[0][g_MarkerZ], 0.0, 0, 0, "Los Santos Parking Lot (Downtown Los Santos)");
            }
        }
        return 1;
    }

    if (dialogid == DLG_ADMIN_TP_BURGER_SHOT) {
        if (!response) {
            return ShowAdminTeleportMenu(playerid);
        }
        if (listitem < 0 || listitem >= BURGER_SHOT_COUNT) return 1;

        new locName[96];
        format(locName, sizeof(locName), "%s (%s)", gBurgerShots[listitem][bs_Name], gBurgerShots[listitem][bs_City]);
        AdminTeleportToPos(playerid, gBurgerShots[listitem][bs_X], gBurgerShots[listitem][bs_Y], gBurgerShots[listitem][bs_Z], gBurgerShots[listitem][bs_A], 0, 0, locName);
        return 1;
    }

    if (dialogid == DLG_ADMIN_TP_INSURANCE) {
        if (!response) {
            return ShowAdminTeleportMenu(playerid);
        }
        if (listitem < 0 || listitem >= INSURANCE_BRANCH_COUNT) return 1;

        new locName[96];
        format(locName, sizeof(locName), "%s (%s)", gInsuranceBranches[listitem][ins_Name], gInsuranceBranches[listitem][ins_City]);
        AdminTeleportToPos(playerid, gInsuranceBranches[listitem][ins_X], gInsuranceBranches[listitem][ins_Y], gInsuranceBranches[listitem][ins_Z], 0.0, 0, 0, locName);
        return 1;
    }

    if (dialogid == DLG_ADMIN_TP_GARAGE) {
        if (!response) {
            return ShowAdminTeleportMenu(playerid);
        }
        if (listitem < 0 || listitem >= PUBLIC_GARAGE_COUNT) return 1;

        new locName[96];
        format(locName, sizeof(locName), "%s (%s)", gPublicGarages[listitem][g_Name], gPublicGarages[listitem][g_City]);
        AdminTeleportToPos(playerid, gPublicGarages[listitem][g_MarkerX], gPublicGarages[listitem][g_MarkerY], gPublicGarages[listitem][g_MarkerZ], 0.0, 0, 0, locName);
        return 1;
    }
    return 0;
}

CMD:tpgps(playerid, params[]) {
    #pragma unused params
    if (!IsAdmin(playerid, 1)) {
        SendClientMessage(playerid, COL_RED, "  [Error] Anda tidak memiliki izin untuk menggunakan perintah administrator!");
        return 1;
    }
    ShowAdminTeleportMenu(playerid);
    return 1;
}

CMD:gotopos(playerid, params[]) {
    return cmd_tpgps(playerid, params);
}

CMD:tp(playerid, params[]) {
    return cmd_tpgps(playerid, params);
}

// ── 13. Manajemen Pekerjaan Pemain (/setjob) ────────────────

CMD:setjob(playerid, params[]) {
    if (!IsAdmin(playerid, 1)) {
        SendClientMessage(playerid, COL_RED, "  [Error] Anda tidak memiliki izin untuk menggunakan perintah ini!");
        return 1;
    }

    new targetid, jobid;
    if (sscanf(params, "ud", targetid, jobid)) {
        SendClientMessage(playerid, COL_YELLOW, "  Gunakan: /setjob [playerid/nama] [job_id]");
        SendClientMessage(playerid, COL_GREY, "  Daftar Job: 0 = Pengangguran");
        return 1;
    }

    if (!IsPlayerConnected(targetid) || !gPlayerData[targetid][p_Spawned]) {
        SendClientMessage(playerid, COL_RED, "  [Error] Pemain target tidak ditemukan atau belum login!");
        return 1;
    }

    // Cek apakah job_id ada di tabel jobs di santara_master.db
    new qCheck[128], jName[32];
    format(qCheck, sizeof(qCheck), "SELECT `name` FROM `jobs` WHERE `id`=%d LIMIT 1", jobid);
    new DBResult:res = DB_ExecuteQuery(gDB_Master, qCheck);
    if (!res || DB_GetRowCount(res) == 0) {
        if (res) DB_FreeResultSet(res);
        SendClientMessage(playerid, COL_RED, "  [Error] Job ID tersebut tidak terdaftar di database jobs!");
        return 1;
    }
    DB_GetFieldStringByName(res, "name", jName, sizeof(jName));
    DB_FreeResultSet(res);

    gPlayerData[targetid][p_Job] = jobid;

    // Simpan ke database
    new qUpd[128];
    format(qUpd, sizeof(qUpd), "UPDATE `characters` SET `job_id`=%d WHERE `id`=%d", jobid, gPlayerData[targetid][p_CharID]);
    DB_FreeResultSet(DB_ExecuteQuery(gDB, qUpd));

    // Update HUD
    UpdatePlayerMoneyHUD(targetid);

    new targetName[48], adminName[MAX_PLAYER_NAME + 1], msgAdmin[144], msgTarget[144];
    GetCharName(targetid, targetName);
    GetPlayerName(playerid, adminName, sizeof(adminName));

    format(msgAdmin, sizeof(msgAdmin), "  [Admin] Anda telah mengubah pekerjaan %s menjadi: %s (ID: %d).", targetName, jName, jobid);
    SendClientMessage(playerid, COL_GREEN, msgAdmin);

    format(msgTarget, sizeof(msgTarget), "  [Admin] Pekerjaan Anda telah diubah oleh Admin %s menjadi: %s.", adminName, jName);
    SendClientMessage(targetid, COL_CYAN, msgTarget);
    return 1;
}

