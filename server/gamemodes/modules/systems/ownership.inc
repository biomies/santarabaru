#if defined _MODULE_OWNERSHIP_INC
    #endinput
#endif
#define _MODULE_OWNERSHIP_INC

// ============================================================
//  SantaraBaru Roleplay — Player Vehicle Ownership & Management
// ============================================================

stock DestroyPlayerActiveVehicle(playerid) {
    if (gPlayerData[playerid][p_ActiveVehID] != INVALID_VEHICLE_ID) {
        // Simpan koordinat dan kondisi terakhir ke database jika ada DB ID
        if (gPlayerData[playerid][p_ActiveVehDBID] > 0) {
            new Float:vx, Float:vy, Float:vz, Float:va, Float:vhp;
            GetVehiclePos(gPlayerData[playerid][p_ActiveVehID], vx, vy, vz);
            GetVehicleZAngle(gPlayerData[playerid][p_ActiveVehID], va);
            GetVehicleHealth(gPlayerData[playerid][p_ActiveVehID], vhp);

            new q[256];
            format(q, sizeof(q),
                "UPDATE `player_vehicles` SET `x`=%f, `y`=%f, `z`=%f, `angle`=%f, `health`=%f WHERE `id`=%d",
                vx, vy, vz, va, vhp, gPlayerData[playerid][p_ActiveVehDBID]);
            DB_FreeResultSet(DB_ExecuteQuery(gDB, q));
        }
        DestroyVehicle(gPlayerData[playerid][p_ActiveVehID]);
        gPlayerData[playerid][p_ActiveVehID] = INVALID_VEHICLE_ID;
        gPlayerData[playerid][p_ActiveVehDBID] = 0;
    }
}

public BuyCurrentDealerVehicle(playerid) {
    if (!gPlayerData[playerid][p_InDealership]) return 0;
    if (gPlayerData[playerid][p_CharID] <= 0) {
        SendClientMessage(playerid, COL_RED, "  [Error] Karakter Anda belum terdaftar di database.");
        return 0;
    }

    new cat = gPlayerData[playerid][p_DealerCat];
    new idx = gPlayerData[playerid][p_DealerIndex];
    new colorIdx = gPlayerData[playerid][p_DealerColorIdx];

    new modelid, name[28], type[28], price, topspeed, seats;
    GetDealerVehicleData(cat, idx, modelid, name, type, price, topspeed, seats);

    // Cek kecukupan uang tunai
    if (gPlayerData[playerid][p_Cash] < price) {
        PlayerPlaySound(playerid, 1055, 0.0, 0.0, 0.0);
        SendClientMessage(playerid, COL_RED, "  [Rodeo Dealership] Uang tunai Anda tidak mencukupi untuk membeli kendaraan ini!");
        return 0;
    }

    // Kurangi uang pemain & update HUD
    gPlayerData[playerid][p_Cash] -= price;
    UpdatePlayerMoneyHUD(playerid);

    // Update uang karakter di database
    new qMoney[128];
    format(qMoney, sizeof(qMoney), "UPDATE `characters` SET `cash`=%d WHERE `id`=%d",
        gPlayerData[playerid][p_Cash], gPlayerData[playerid][p_CharID]);
    DB_FreeResultSet(DB_ExecuteQuery(gDB, qMoney));

    // Generate plat nomor acak unik: SAN-XXX
    new plate[16];
    format(plate, sizeof(plate), "SAN-%03d", random(900) + 100);

    new chosenColor = gDealerColors[colorIdx];

    // Simpan kendaraan ke database player_vehicles
    new qInsert[384];
    format(qInsert, sizeof(qInsert),
        "INSERT INTO `player_vehicles` (`char_id`, `model_id`, `plate`, `color1`, `color2`, `price`, `x`, `y`, `z`, `angle`, `health`, `locked`) " \
        "VALUES (%d, %d, '%s', %d, %d, %d, %f, %f, %f, %f, 1000.0, 0)",
        gPlayerData[playerid][p_CharID], modelid, plate, chosenColor, chosenColor, price,
        DEALER_DELIVER_X, DEALER_DELIVER_Y, DEALER_DELIVER_Z, DEALER_DELIVER_A);

    new DBResult:res = DB_ExecuteQuery(gDB, qInsert);
    if (res) DB_FreeResultSet(res);

    // Ambil ID kendaraan yang baru diinsert
    new vehDbId = 0;
    new qGetId[128];
    format(qGetId, sizeof(qGetId), "SELECT `id` FROM `player_vehicles` WHERE `char_id`=%d ORDER BY `id` DESC LIMIT 1",
        gPlayerData[playerid][p_CharID]);
    new DBResult:resId = DB_ExecuteQuery(gDB, qGetId);
    if (resId && DB_GetRowCount(resId) > 0) {
        vehDbId = DB_GetFieldIntByName(resId, "id");
        DB_FreeResultSet(resId);
    } else {
        if (resId) DB_FreeResultSet(resId);
    }

    // Hapus kendaraan aktif pemain yang lama jika ada
    DestroyPlayerActiveVehicle(playerid);

    // Tutup menu Dealership (menghapus preview car & merestore kontrol)
    CloseDealership(playerid);

    // Spawn kendaraan baru di tempat penyerahan luar showroom
    new vehId = CreateVehicle(
        modelid,
        DEALER_DELIVER_X, DEALER_DELIVER_Y, DEALER_DELIVER_Z, DEALER_DELIVER_A,
        chosenColor, chosenColor, -1
    );

    if (vehId != INVALID_VEHICLE_ID) {
        SetVehicleNumberPlate(vehId, plate);
        SetVehicleToRespawn(vehId); // Menerapkan plat nomor baru
        SetVehiclePos(vehId, DEALER_DELIVER_X, DEALER_DELIVER_Y, DEALER_DELIVER_Z);
        SetVehicleZAngle(vehId, DEALER_DELIVER_A);

        // Kunci terbuka & mesin mati secara default
        SetVehicleParamsEx(vehId, 0, 0, 0, 0, 0, 0, 0);

        gPlayerData[playerid][p_ActiveVehID] = vehId;
        gPlayerData[playerid][p_ActiveVehDBID] = vehDbId;

        // Posisikan pemain di samping mobil baru
        SetPlayerPos(playerid, DEALER_DELIVER_X + 2.5, DEALER_DELIVER_Y, DEALER_DELIVER_Z);
        SetPlayerFacingAngle(playerid, DEALER_DELIVER_A + 90.0);
    }

    // Mainkan sound efek sukses
    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);

    new priceFmt[32];
    FormatRupiah(price, priceFmt, sizeof(priceFmt));

    // Kirim notifikasi transaksi pembelian
    SendClientMessage(playerid, COL_GREEN, "====================================================================");
    SendClientMessage(playerid, COL_CYAN,  "  [Rodeo Dealership] SELAMAT! Transaksi Pembelian Kendaraan Berhasil.");
    
    new infoMsg[144];
    format(infoMsg, sizeof(infoMsg), "  » Unit: {FFFFFF}%s (%s) {A0AEC0}| Warna: {FFFFFF}%s {A0AEC0}| Harga: {2ECC71}%s",
        name, type, gDealerColorNames[colorIdx], priceFmt);
    SendClientMessage(playerid, COL_WHITE, infoMsg);

    format(infoMsg, sizeof(infoMsg), "  » Plat Nomor: {00EEFF}%s {A0AEC0}| Kunci: {2ECC71}Tersedia di saku Anda", plate);
    SendClientMessage(playerid, COL_WHITE, infoMsg);

    SendClientMessage(playerid, COL_YELLOW, "  » Gunakan {FFFFFF}/lock {FFFF00}untuk kunci, {FFFFFF}/engine {FFFF00}untuk mesin, {FFFFFF}/park {FFFF00}untuk simpan parkir.");
    SendClientMessage(playerid, COL_GREEN, "====================================================================");
    return 1;
}

// ── Perintah Kepemilikan Kendaraan ──────────────────────────

CMD:buyveh(playerid, params[]) {
    #pragma unused params
    if (!gPlayerData[playerid][p_LoggedIn]) return 1;

    // Cek apakah pemain berada di dekat area Rodeo Showroom (radius 15 meter)
    if (!IsPlayerInRangeOfPoint(playerid, 15.0, DEALER_RODEO_X, DEALER_RODEO_Y, DEALER_RODEO_Z)) {
        SendClientMessage(playerid, COL_RED, "  [Dealer] Anda harus berada di Rodeo Luxury Dealership (Los Santos) untuk membeli kendaraan!");
        SendClientMessage(playerid, COL_YELLOW, "  » Lokasi: Rodeo Showroom (di peta Los Santos Barat dekat Beverly Hills).");
        return 1;
    }

    OpenDealership(playerid);
    return 1;
}

CMD:dealer(playerid, params[]) {
    return cmd_buyveh(playerid, params);
}

CMD:showroom(playerid, params[]) {
    return cmd_buyveh(playerid, params);
}

CMD:lock(playerid, params[]) {
    #pragma unused params
    if (!gPlayerData[playerid][p_LoggedIn]) return 1;

    new vehId = gPlayerData[playerid][p_ActiveVehID];
    if (vehId == INVALID_VEHICLE_ID) {
        SendClientMessage(playerid, COL_RED, "  [Kendaraan] Anda belum memiliki atau mengeluarkan kendaraan pribadi!");
        return 1;
    }

    new Float:vx, Float:vy, Float:vz;
    GetVehiclePos(vehId, vx, vy, vz);

    // Cek jarak pemain ke kendaraannya (radius 7.5 meter atau sedang di dalam mobil)
    if (!IsPlayerInRangeOfPoint(playerid, 7.5, vx, vy, vz) && GetPlayerVehicleID(playerid) != vehId) {
        SendClientMessage(playerid, COL_RED, "  [Kendaraan] Anda terlalu jauh dari kendaraan pribadi Anda!");
        return 1;
    }

    new engine, lights, alarm, doors, bonnet, boot, objective;
    GetVehicleParamsEx(vehId, engine, lights, alarm, doors, bonnet, boot, objective);

    if (doors == 1) {
        SetVehicleParamsEx(vehId, engine, lights, alarm, 0, bonnet, boot, objective);
        PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
        SendClientMessage(playerid, COL_GREEN, "  [Kendaraan] Kunci pintu: {FFFFFF}TERBUKA (Unlocked).");
    } else {
        SetVehicleParamsEx(vehId, engine, lights, alarm, 1, bonnet, boot, objective);
        PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
        SendClientMessage(playerid, COL_YELLOW, "  [Kendaraan] Kunci pintu: {E74C3C}TERKUNCI (Locked).");
    }
    return 1;
}

CMD:kunci(playerid, params[]) {
    return cmd_lock(playerid, params);
}

CMD:engine(playerid, params[]) {
    #pragma unused params
    if (!gPlayerData[playerid][p_LoggedIn]) return 1;

    if (!IsPlayerInAnyVehicle(playerid)) {
        SendClientMessage(playerid, COL_RED, "  [Kendaraan] Anda harus berada di dalam kendaraan untuk menyalakan mesin!");
        return 1;
    }

    if (GetPlayerVehicleSeat(playerid) != 0) {
        SendClientMessage(playerid, COL_RED, "  [Kendaraan] Anda harus berada di kursi pengemudi!");
        return 1;
    }

    new vehId = GetPlayerVehicleID(playerid);
    new engine, lights, alarm, doors, bonnet, boot, objective;
    GetVehicleParamsEx(vehId, engine, lights, alarm, doors, bonnet, boot, objective);

    if (engine == 1) {
        SetVehicleParamsEx(vehId, 0, lights, alarm, doors, bonnet, boot, objective);
        SendClientMessage(playerid, COL_YELLOW, "  [Kendaraan] Mesin dimatikan.");
    } else {
        SetVehicleParamsEx(vehId, 1, lights, alarm, doors, bonnet, boot, objective);
        SendClientMessage(playerid, COL_GREEN, "  [Kendaraan] Mesin dinyalakan. Silakan berkendara dengan aman!");
    }
    return 1;
}

CMD:mesin(playerid, params[]) {
    return cmd_engine(playerid, params);
}

CMD:park(playerid, params[]) {
    #pragma unused params
    if (!gPlayerData[playerid][p_LoggedIn]) return 1;

    new vehId = gPlayerData[playerid][p_ActiveVehID];
    if (vehId == INVALID_VEHICLE_ID || GetPlayerVehicleID(playerid) != vehId) {
        SendClientMessage(playerid, COL_RED, "  [Kendaraan] Anda harus sedang mengendarai kendaraan pribadi Anda untuk menyimpan posisi parkir!");
        return 1;
    }

    new Float:vx, Float:vy, Float:vz, Float:va, Float:vhp;
    GetVehiclePos(vehId, vx, vy, vz);
    GetVehicleZAngle(vehId, va);
    GetVehicleHealth(vehId, vhp);

    new q[256];
    format(q, sizeof(q),
        "UPDATE `player_vehicles` SET `x`=%f, `y`=%f, `z`=%f, `angle`=%f, `health`=%f WHERE `id`=%d",
        vx, vy, vz, va, vhp, gPlayerData[playerid][p_ActiveVehDBID]);
    DB_FreeResultSet(DB_ExecuteQuery(gDB, q));

    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
    SendClientMessage(playerid, COL_GREEN, "  [Kendaraan] Posisi parkir kendaraan pribadi Anda berhasil disimpan!");
    return 1;
}

CMD:parkir(playerid, params[]) {
    return cmd_park(playerid, params);
}

CMD:myveh(playerid, params[]) {
    #pragma unused params
    if (!gPlayerData[playerid][p_LoggedIn] || gPlayerData[playerid][p_CharID] <= 0) return 1;

    new q[256];
    format(q, sizeof(q),
        "SELECT `id`, `model_id`, `plate`, `color1`, `price`, `x`, `y`, `z`, `health` FROM `player_vehicles` WHERE `char_id`=%d ORDER BY `id` DESC LIMIT 1",
        gPlayerData[playerid][p_CharID]);

    new DBResult:res = DB_ExecuteQuery(gDB, q);
    if (!res || DB_GetRowCount(res) == 0) {
        if (res) DB_FreeResultSet(res);
        SendClientMessage(playerid, COL_YELLOW, "  [Kendaraan] Anda belum memiliki kendaraan pribadi. Kunjungi Rodeo Dealership untuk membeli!");
        return 1;
    }

    new vehDbId = DB_GetFieldIntByName(res, "id");
    new modelid = DB_GetFieldIntByName(res, "model_id");
    new plate[16];
    DB_GetFieldStringByName(res, "plate", plate, sizeof(plate));
    new Float:hp = DB_GetFieldFloatByName(res, "health");
    DB_FreeResultSet(res);

    SendClientMessage(playerid, COL_GREEN, "==================================================");
    SendClientMessage(playerid, COL_CYAN,  "  [INFO KENDARAAN PRIBADI]");
    
    new info[128];
    format(info, sizeof(info), "  » Model GTA SA: {FFFFFF}#%d {A0AEC0}| Plat Nomor: {00EEFF}%s", modelid, plate);
    SendClientMessage(playerid, COL_WHITE, info);

    format(info, sizeof(info), "  » Kondisi Mesin: {2ECC71}%.0f%% {A0AEC0}| Database ID: #{FFFFFF}%d", hp / 10.0, vehDbId);
    SendClientMessage(playerid, COL_WHITE, info);

    if (gPlayerData[playerid][p_ActiveVehID] != INVALID_VEHICLE_ID) {
        SendClientMessage(playerid, COL_YELLOW, "  » Status: {2ECC71}Aktif di Kota {A0AEC0}(Ketik /lock untuk kunci, /park untuk parkir)");
    } else {
        SendClientMessage(playerid, COL_YELLOW, "  » Status: {E74C3C}Terparkir di Garasi {A0AEC0}(Ketik /towveh untuk mengeluarkan)");
    }
    SendClientMessage(playerid, COL_GREEN, "==================================================");
    return 1;
}

CMD:kendaraan(playerid, params[]) {
    return cmd_myveh(playerid, params);
}

CMD:towveh(playerid, params[]) {
    #pragma unused params
    if (!gPlayerData[playerid][p_LoggedIn] || gPlayerData[playerid][p_CharID] <= 0) return 1;

    // Jika kendaraan sudah aktif di dunia game, hapus terlebih dahulu
    DestroyPlayerActiveVehicle(playerid);

    new q[256];
    format(q, sizeof(q),
        "SELECT `id`, `model_id`, `plate`, `color1`, `color2`, `x`, `y`, `z`, `angle`, `health` FROM `player_vehicles` WHERE `char_id`=%d ORDER BY `id` DESC LIMIT 1",
        gPlayerData[playerid][p_CharID]);

    new DBResult:res = DB_ExecuteQuery(gDB, q);
    if (!res || DB_GetRowCount(res) == 0) {
        if (res) DB_FreeResultSet(res);
        SendClientMessage(playerid, COL_RED, "  [Kendaraan] Anda tidak memiliki catatan kendaraan pribadi di database.");
        return 1;
    }

    new vehDbId = DB_GetFieldIntByName(res, "id");
    new modelid = DB_GetFieldIntByName(res, "model_id");
    new color1 = DB_GetFieldIntByName(res, "color1");
    new color2 = DB_GetFieldIntByName(res, "color2");
    new plate[16];
    DB_GetFieldStringByName(res, "plate", plate, sizeof(plate));
    new Float:vx = DB_GetFieldFloatByName(res, "x");
    new Float:vy = DB_GetFieldFloatByName(res, "y");
    new Float:vz = DB_GetFieldFloatByName(res, "z");
    new Float:va = DB_GetFieldFloatByName(res, "angle");
    new Float:vhp = DB_GetFieldFloatByName(res, "health");
    DB_FreeResultSet(res);

    new vehId = CreateVehicle(modelid, vx, vy, vz, va, color1, color2, -1);
    if (vehId != INVALID_VEHICLE_ID) {
        SetVehicleNumberPlate(vehId, plate);
        SetVehicleToRespawn(vehId);
        SetVehiclePos(vehId, vx, vy, vz);
        SetVehicleZAngle(vehId, va);
        SetVehicleHealth(vehId, vhp);
        SetVehicleParamsEx(vehId, 0, 0, 0, 0, 0, 0, 0);

        gPlayerData[playerid][p_ActiveVehID] = vehId;
        gPlayerData[playerid][p_ActiveVehDBID] = vehDbId;

        // Set checkpoint di posisi mobil
        SetPlayerCheckpoint(playerid, vx, vy, vz, 3.5);

        PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
        SendClientMessage(playerid, COL_GREEN, "  [Kendaraan] Kendaraan pribadi Anda berhasil dikeluarkan di lokasi parkir terakhir.");
        SendClientMessage(playerid, COL_YELLOW, "  » Tanda checkpoint merah telah ditandai di radar Anda.");
    }
    return 1;
}

CMD:panggil(playerid, params[]) {
    return cmd_towveh(playerid, params);
}
