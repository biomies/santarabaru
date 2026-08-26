#if defined _MODULE_OWNERSHIP_INC
    #endinput
#endif
#define _MODULE_OWNERSHIP_INC

// ============================================================
//  SantaraBaru Roleplay - Player Vehicle Ownership & Garages
// ============================================================

forward TogglePlayerVehicleEngine(playerid);
forward TogglePlayerVehicleLock(playerid);

//    1. Database Nama Kendaraan GTA SA (Model 400 - 611)     
stock const gVehicleModelNames[][32] = {
    "Landstalker", "Bravura", "Buffalo", "Linerunner", "Perennial", "Sentinel", "Dumper", "Firetruck",
    "Trashmaster", "Stretch", "Manana", "Infernus", "Voodoo", "Pony", "Mule", "Cheetah", "Ambulance",
    "Leviathan", "Moonbeam", "Esperanto", "Taxi", "Washington", "Bobcat", "Mr Whoopee", "BF Injection",
    "Hunter", "Premier", "Enforcer", "Securicar", "Banshee", "Predator", "Bus", "Rhino", "Barracks",
    "Hotknife", "Article Trailer 1", "Previon", "Coach", "Cabbie", "Stallion", "Rumpo", "RC Bandit",
    "Romero", "Packer", "Monster", "Admiral", "Squalo", "Seasparrow", "Pizzaboy", "Tram", "Article Trailer 2",
    "Turismo", "Speeder", "Reefer", "Tropic", "Flatbed", "Yankee", "Caddy", "Solair", "Berkleys RC Van",
    "Skimmer", "PCJ-600", "Faggio", "Freeway", "RC Baron", "RC Raider", "Glendale", "Oceanic", "Sanchez",
    "Sparrow", "Patriot", "Quad", "Coastguard", "Dinghy", "Hermes", "Sabre", "Rustler", "ZR-350",
    "Walton", "Regina", "Comet", "BMX", "Burrito", "Camper", "Marquis", "Baggage", "Dozer", "Maverick",
    "SAN News Maverick", "Rancher", "FBI Rancher", "Virgo", "Greenwood", "Jetmax", "Hotring Racer",
    "Sandking", "Blista Compact", "Police Maverick", "Boxville", "Benson", "Mesa", "RC Goblin",
    "Hotring Racer A", "Hotring Racer B", "Bloodring Banger", "Rancher Lure", "Super GT", "Elegant",
    "Journey", "Bike", "Mountain Bike", "Beagle", "Cropduster", "Stuntplane", "Tanker", "Roadtrain",
    "Nebula", "Majestic", "Buccaneer", "Shamal", "Hydra", "FCR-900", "NRG-500", "HPV-1000", "Cement Truck",
    "Towtruck", "Fortune", "Cadrona", "FBI Truck", "Willard", "Forklift", "Tractor", "Combine Harvester",
    "Feltzer", "Remington", "Slamvan", "Blade", "Freight", "Streak", "Vortex", "Vincent", "Bullet",
    "Clover", "Sadler", "Firetruck LA", "Hustler", "Intruder", "Primo", "Cargobob", "Tampa", "Sunrise",
    "Merit", "Utility Van", "Nevada", "Yosemite", "Windsor", "Monster A", "Monster B", "Uranus", "Jester",
    "Sultan", "Stratum", "Elegy", "Raindance", "RC Tiger", "Flash", "Tahoma", "Savanna", "Bandito",
    "Freight Flat", "Streak Carriage", "Kart", "Mower", "Dune", "Sweeper", "Broadway", "Tornado",
    "AT-400", "DFT-30", "Huntley", "Stafford", "BF-400", "Newsvan", "Tug", "Petrol Trailer", "Emperor",
    "Wayfarer", "Euros", "Hotdog", "Club", "Freight Box", "Article Trailer 3", "Andromada", "Dodo",
    "RC Cam", "Launch", "Police Car (LSPD)", "Police Car (SFPD)", "Police Car (LVPD)", "Police Ranger",
    "Picador", "SWAT Tank", "Alpha", "Phoenix", "Glendale Damaged", "Sadler Damaged", "Luggage Trailer A",
    "Luggage Trailer B", "Stairs Trailer", "Boxville Mission", "Farm Trailer", "Street Clean Trailer"
};

stock GetModelFullName(modelid, name[], maxlen) {
    if (modelid >= 400 && modelid <= 611) {
        format(name, maxlen, "%s", gVehicleModelNames[modelid - 400]);
    } else {
        format(name, maxlen, "Vehicle %d", modelid);
    }
}

//    2. Struktur Data 10 Titik Garasi Publik 3 Kota (LS, SF, LV)   
enum E_PUBLIC_GARAGE {
    g_Name[48],
    g_City[24],
    Float:g_MarkerX,
    Float:g_MarkerY,
    Float:g_MarkerZ,
    Float:g_CamX,
    Float:g_CamY,
    Float:g_CamZ,
    Float:g_LookX,
    Float:g_LookY,
    Float:g_LookZ,
    Float:g_SpawnX,
    Float:g_SpawnY,
    Float:g_SpawnZ,
    Float:g_SpawnA
};

new const gPublicGarages[][E_PUBLIC_GARAGE] = {
    //    KOTA 1: LOS SANTOS (Los Santos Parking Lot)
    {
        "Los Santos Parking Lot", "Los Santos",
        1637.6439, -1103.1943, 23.9062,
        1637.0166, -1131.0000, 25.5000,
        1637.0166, -1137.5103, 24.2000,
        1637.0166, -1137.5103, 23.9062, 179.7309
    }
};
#define PUBLIC_GARAGE_COUNT (sizeof(gPublicGarages))

public GetGarageInfo(garageId, name[], city[], &Float:camX, &Float:camY, &Float:camZ, &Float:lookX, &Float:lookY, &Float:lookZ, &Float:spX, &Float:spY, &Float:spZ, &Float:spA) {
    if (garageId < 0 || garageId >= PUBLIC_GARAGE_COUNT) garageId = 0;
    format(name, 48, "%s", gPublicGarages[garageId][g_Name]);
    format(city, 24, "%s", gPublicGarages[garageId][g_City]);
    camX = gPublicGarages[garageId][g_CamX];
    camY = gPublicGarages[garageId][g_CamY];
    camZ = gPublicGarages[garageId][g_CamZ];
    lookX = gPublicGarages[garageId][g_LookX];
    lookY = gPublicGarages[garageId][g_LookY];
    lookZ = gPublicGarages[garageId][g_LookZ];
    spX = gPublicGarages[garageId][g_SpawnX];
    spY = gPublicGarages[garageId][g_SpawnY];
    spZ = gPublicGarages[garageId][g_SpawnZ];
    spA = gPublicGarages[garageId][g_SpawnA];
    return 1;
}

stock InitPublicGarages() {
    for (new i = 0; i < PUBLIC_GARAGE_COUNT; i++) {
        new labelText[256];
        format(labelText, sizeof(labelText),
            "{00EEFF}[ %s ]\n{FFFFFF}%s - Parkiran Resmi Kota\n{FFFF00}Simpan Mobil: Tekan [ H ]\n{A0AEC0}Ambil Mobil: Tekan [ H ] atau /garasi",
            gPublicGarages[i][g_Name], gPublicGarages[i][g_City]);
        Create3DTextLabel(labelText, 0xFFFFFFFF,
            gPublicGarages[i][g_MarkerX], gPublicGarages[i][g_MarkerY], gPublicGarages[i][g_MarkerZ] + 0.8,
            20.0, 0, true);

        // Buat Red Marker Cylinder (Model 19197 / Pickup 1318) - Tanpa ikon di peta
        CreatePickup(1318, 1, gPublicGarages[i][g_MarkerX], gPublicGarages[i][g_MarkerY], gPublicGarages[i][g_MarkerZ], 0);
        CreateObject(19197, gPublicGarages[i][g_MarkerX], gPublicGarages[i][g_MarkerY], gPublicGarages[i][g_MarkerZ] - 0.4, 0.0, 0.0, 0.0);
    }
    printf("[Garasi] Inisialisasi %d Gedung Parkir Kota di 3 Kota (LS, SF, LV) berhasil.", PUBLIC_GARAGE_COUNT);
    return 1;
}

enum E_INSURANCE_BRANCH {
    ins_Name[48],
    ins_City[32],
    Float:ins_X,
    Float:ins_Y,
    Float:ins_Z
};

new const gInsuranceBranches[][E_INSURANCE_BRANCH] = {
    {"Kantor Asuransi Los Santos",   "Commerce, Los Santos",         1766.4250, -1700.5420, 13.5469},
    {"Kantor Asuransi San Fierro",   "Financial District, SF",      -1571.2000,   661.1000,  7.1800},
    {"Kantor Asuransi Las Venturas", "The Strip Financial, LV",      2026.8000,  1008.2000, 10.8200}
};
#define INSURANCE_BRANCH_COUNT (sizeof(gInsuranceBranches))

stock IsPlayerNearInsurance(playerid) {
    for (new i = 0; i < INSURANCE_BRANCH_COUNT; i++) {
        if (IsPlayerInRangeOfPoint(playerid, 3.5, gInsuranceBranches[i][ins_X], gInsuranceBranches[i][ins_Y], gInsuranceBranches[i][ins_Z])) {
            return 1;
        }
    }
    return 0;
}

stock InitInsuranceCenter() {
    for (new i = 0; i < INSURANCE_BRANCH_COUNT; i++) {
        new labelText[256];
        format(labelText, sizeof(labelText),
            "{2ECC71}[ %s ]\n{FFFFFF}%s\n{FFFF00}Tekan [ H ] atau [ F ] atau ketik /asuransi\n{A0AEC0}[ Klaim dan Tebus Kendaraan ]",
            gInsuranceBranches[i][ins_Name], gInsuranceBranches[i][ins_City]);
        Create3DTextLabel(labelText, 0xFFFFFFFF,
            gInsuranceBranches[i][ins_X], gInsuranceBranches[i][ins_Y], gInsuranceBranches[i][ins_Z] + 0.8,
            20.0, 0, true);
        CreatePickup(1239, 1, gInsuranceBranches[i][ins_X], gInsuranceBranches[i][ins_Y], gInsuranceBranches[i][ins_Z], 0);
    }
    printf("[Asuransi] Inisialisasi %d Kantor Cabang Asuransi di 3 Kota (LS, SF, LV) berhasil.", INSURANCE_BRANCH_COUNT);
    return 1;
}

stock SyncVehiclesOnServerStart() {
    // Otomatis pindahkan seluruh kendaraan yang tertinggal di luar (status 0) ke status Asuransi (status 2)
    // sehingga saat server restart, kendaraan yang tidak disimpan di garasi harus diambil di kantor asuransi.
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "UPDATE `player_vehicles` SET `status`=2 WHERE `status`=0"));
    print("[Kendaraan] Seluruh kendaraan di luar dipindahkan ke status Asuransi karena server restart.");
    return 1;
}

//    3. Manajemen Kendaraan Aktif Pemain (Maksimal 5 Kendaraan Aktif per Pemain)

stock GetPlayerActiveVehCount(playerid) {
    new count = 0;
    for (new v = 0; v < MAX_PLAYER_SPAWNED_VEHICLES; v++) {
        if (gPlayerData[playerid][p_ActiveVehID][v] != INVALID_VEHICLE_ID) count++;
    }
    return count;
}

stock bool:IsPlayerActiveVeh(playerid, vehicleid) {
    if (vehicleid == INVALID_VEHICLE_ID || vehicleid <= 0) return false;
    for (new v = 0; v < MAX_PLAYER_SPAWNED_VEHICLES; v++) {
        if (gPlayerData[playerid][p_ActiveVehID][v] == vehicleid) return true;
    }
    return false;
}

stock GetPlayerActiveVehSlot(playerid, vehicleid) {
    if (vehicleid == INVALID_VEHICLE_ID || vehicleid <= 0) return -1;
    for (new v = 0; v < MAX_PLAYER_SPAWNED_VEHICLES; v++) {
        if (gPlayerData[playerid][p_ActiveVehID][v] == vehicleid) return v;
    }
    return -1;
}

stock GetPlayerActiveVehSlotByDBID(playerid, dbId) {
    if (dbId <= 0) return -1;
    for (new v = 0; v < MAX_PLAYER_SPAWNED_VEHICLES; v++) {
        if (gPlayerData[playerid][p_ActiveVehDBID][v] == dbId) return v;
    }
    return -1;
}

stock GetPlayerEmptyVehSlot(playerid) {
    for (new v = 0; v < MAX_PLAYER_SPAWNED_VEHICLES; v++) {
        if (gPlayerData[playerid][p_ActiveVehID][v] == INVALID_VEHICLE_ID) return v;
    }
    return -1;
}

stock DestroyPlayerActiveVehicle(playerid) {
    for (new v = 0; v < MAX_PLAYER_SPAWNED_VEHICLES; v++) {
        new vehId = gPlayerData[playerid][p_ActiveVehID][v];
        if (vehId != INVALID_VEHICLE_ID) {
            new dbId = gPlayerData[playerid][p_ActiveVehDBID][v];
            if (dbId > 0) {
                new Float:vx, Float:vy, Float:vz, Float:va, Float:vhp;
                GetVehiclePos(vehId, vx, vy, vz);
                GetVehicleZAngle(vehId, va);
                GetVehicleHealth(vehId, vhp);

                new q[256];
                format(q, sizeof(q),
                    "UPDATE `player_vehicles` SET `x`=%f, `y`=%f, `z`=%f, `angle`=%f, `health`=%f WHERE `id`=%d",
                    vx, vy, vz, va, vhp, dbId);
                DB_FreeResultSet(DB_ExecuteQuery(gDB, q));
            }
            DestroyVehicle(vehId);
            gPlayerData[playerid][p_ActiveVehID][v] = INVALID_VEHICLE_ID;
            gPlayerData[playerid][p_ActiveVehDBID][v] = 0;
        }
    }
}

stock StoreVehicleInGarage(playerid, garageId) {
    new curVeh = GetPlayerVehicleID(playerid);
    new slot = GetPlayerActiveVehSlot(playerid, curVeh);
    if (slot == -1) {
        SendClientMessage(playerid, COL_RED, "  [Garasi] Anda harus menaiki kendaraan pribadi milik Anda sendiri!");
        return 0;
    }

    new dbId = gPlayerData[playerid][p_ActiveVehDBID][slot];
    if (dbId <= 0) return 0;

    new Float:vhp;
    GetVehicleHealth(curVeh, vhp);

    // Simpan ke DB dengan status tersimpan di garasi
    new q[256];
    format(q, sizeof(q),
        "UPDATE `player_vehicles` SET `status`=%d, `garage_id`=%d, `health`=%f WHERE `id`=%d",
        VEH_STATUS_GARAGE, garageId, vhp, dbId);
    DB_FreeResultSet(DB_ExecuteQuery(gDB, q));

    DestroyVehicle(curVeh);
    gPlayerData[playerid][p_ActiveVehID][slot] = INVALID_VEHICLE_ID;
    gPlayerData[playerid][p_ActiveVehDBID][slot] = 0;

    // Keluarkan pemain dan posisikan di marker garasi
    SetPlayerPos(playerid, gPublicGarages[garageId][g_MarkerX], gPublicGarages[garageId][g_MarkerY], gPublicGarages[garageId][g_MarkerZ]);

    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
    SendClientMessage(playerid, COL_GREEN, "====================================================================");
    SendClientMessage(playerid, COL_CYAN,  "  [Garasi Publik] Kendaraan pribadi Anda berhasil disimpan!");
    new msg[144];
    format(msg, sizeof(msg), "  > Disimpan di: {FFFFFF}%s (%s) {A0AEC0}| Sisa kendaraan aktif: {2ECC71}%d/5",
        gPublicGarages[garageId][g_Name], gPublicGarages[garageId][g_City], GetPlayerActiveVehCount(playerid));
    SendClientMessage(playerid, COL_WHITE, msg);
    SendClientMessage(playerid, COL_YELLOW, "  > Anda dapat mengambilnya kembali di SEMUA titik Garasi Kota (/garasi).");
    SendClientMessage(playerid, COL_GREEN, "====================================================================");
    return 1;
}

public SpawnPlayerVehicleFromGarage(playerid, dbVehId, garageId) {
    if (garageId < 0 || garageId >= PUBLIC_GARAGE_COUNT) garageId = 0;

    // Cek jika mobil ini sudah aktif di luar
    if (GetPlayerActiveVehSlotByDBID(playerid, dbVehId) != -1) {
        SendClientMessage(playerid, COL_YELLOW, "  [Garasi] Kendaraan ini sudah aktif di luar garasi! Gunakan /v untuk melacak GPS.");
        return 0;
    }

    // Cek kuota batas maksimal 5 kendaraan aktif
    if (GetPlayerActiveVehCount(playerid) >= MAX_PLAYER_SPAWNED_VEHICLES) {
        SendClientMessage(playerid, COL_RED, "  [Garasi] Anda telah mencapai batas maksimal 5 kendaraan aktif di luar garasi!");
        SendClientMessage(playerid, COL_YELLOW, "  > Simpan salah satu kendaraan Anda terlebih dahulu ke garasi (/garasi)!");
        return 0;
    }

    new slot = GetPlayerEmptyVehSlot(playerid);
    if (slot == -1) {
        SendClientMessage(playerid, COL_RED, "  [Garasi] Slot kendaraan aktif penuh (maksimal 5 kendaraan).");
        return 0;
    }

    new query[128];
    format(query, sizeof(query), "SELECT * FROM `player_vehicles` WHERE `id`=%d LIMIT 1", dbVehId);
    new DBResult:res = DB_ExecuteQuery(gDB, query);
    if (!res || DB_GetRowCount(res) == 0) {
        if (res) DB_FreeResultSet(res);
        SendClientMessage(playerid, COL_RED, "  [Garasi] Data kendaraan tidak ditemukan di database.");
        return 0;
    }

    new modelid = DB_GetFieldIntByName(res, "model_id");
    new color1  = DB_GetFieldIntByName(res, "color1");
    new color2  = DB_GetFieldIntByName(res, "color2");
    new Float:vhp = DB_GetFieldFloatByName(res, "health");
    new plate[16];
    DB_GetFieldStringByName(res, "plate", plate, sizeof(plate));
    DB_FreeResultSet(res);

    new Float:spX = gPublicGarages[garageId][g_SpawnX];
    new Float:spY = gPublicGarages[garageId][g_SpawnY];
    new Float:spZ = gPublicGarages[garageId][g_SpawnZ];
    new Float:spA = gPublicGarages[garageId][g_SpawnA];

    new vehId = CreateVehicle(modelid, spX, spY, spZ, spA, color1, color2, -1);
    if (vehId != INVALID_VEHICLE_ID) {
        SetVehicleNumberPlate(vehId, plate);
        SetVehicleToRespawn(vehId);
        SetVehiclePos(vehId, spX, spY, spZ);
        SetVehicleZAngle(vehId, spA);
        SetVehicleHealth(vehId, vhp);
        SetVehicleParamsEx(vehId, 1, 0, 0, 0, 0, 0, 0); // Mesin langsung menyala

        gPlayerData[playerid][p_ActiveVehID][slot] = vehId;
        gPlayerData[playerid][p_ActiveVehDBID][slot] = dbVehId;

        // Update database: status = VEH_STATUS_OUTSIDE
        new qUp[256];
        format(qUp, sizeof(qUp),
            "UPDATE `player_vehicles` SET `status`=%d, `garage_id`=%d, `x`=%f, `y`=%f, `z`=%f, `angle`=%f WHERE `id`=%d",
            VEH_STATUS_OUTSIDE, garageId, spX, spY, spZ, spA, dbVehId);
        DB_FreeResultSet(DB_ExecuteQuery(gDB, qUp));

        // Langsung masukkan pemain ke kursi pengemudi
        PutPlayerInVehicle(playerid, vehId, 0);
    }

    new vehName[32];
    GetModelFullName(modelid, vehName, sizeof(vehName));

    SendClientMessage(playerid, COL_GREEN, "====================================================================");
    SendClientMessage(playerid, COL_CYAN,  "  [Garasi Publik] Kendaraan Anda telah dikeluarkan ke slot garasi!");
    new infoMsg[144];
    format(infoMsg, sizeof(infoMsg), "  > Unit: {FFFFFF}%s {A0AEC0}| Plat: {00EEFF}%s {A0AEC0}| Aktif: {2ECC71}%d/5",
        vehName, plate, GetPlayerActiveVehCount(playerid));
    SendClientMessage(playerid, COL_WHITE, infoMsg);
    SendClientMessage(playerid, COL_YELLOW, "  > Gunakan {FFFFFF}/lock {FFFF00}untuk kunci, {FFFFFF}/engine {FFFF00}untuk mesin, dan {FFFFFF}/v {FFFF00}untuk manajemen.");
    SendClientMessage(playerid, COL_GREEN, "====================================================================");
    return 1;
}

//    4. Sistem Dealership Pembelian Kendaraan                  

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

    if (gPlayerData[playerid][p_Cash] < price) {
        PlayerPlaySound(playerid, 1055, 0.0, 0.0, 0.0);
        SendClientMessage(playerid, COL_RED, "  [Rodeo Dealership] Uang tunai Anda tidak mencukupi untuk membeli kendaraan ini!");
        return 0;
    }

    gPlayerData[playerid][p_Cash] -= price;
    UpdatePlayerMoneyHUD(playerid);

    new qMoney[128];
    format(qMoney, sizeof(qMoney), "UPDATE `characters` SET `cash`=%d WHERE `id`=%d",
        gPlayerData[playerid][p_Cash], gPlayerData[playerid][p_CharID]);
    DB_FreeResultSet(DB_ExecuteQuery(gDB, qMoney));

    new plate[16];
    format(plate, sizeof(plate), "SAN-%03d", random(900) + 100);
    new chosenColor = gDealerColors[colorIdx];

    new bool:canSpawn = (GetPlayerActiveVehCount(playerid) < MAX_PLAYER_SPAWNED_VEHICLES);
    new vehStatus = canSpawn ? VEH_STATUS_OUTSIDE : VEH_STATUS_GARAGE;

    new qInsert[384];
    format(qInsert, sizeof(qInsert),
        "INSERT INTO `player_vehicles` (`char_id`, `model_id`, `plate`, `color1`, `color2`, `price`, `x`, `y`, `z`, `angle`, `health`, `locked`, `status`, `garage_id`, `insurance_cost`) " \
        "VALUES (%d, %d, '%s', %d, %d, %d, %f, %f, %f, %f, 1000.0, 0, %d, 1, 1500000)",
        gPlayerData[playerid][p_CharID], modelid, plate, chosenColor, chosenColor, price,
        DEALER_DELIVER_X, DEALER_DELIVER_Y, DEALER_DELIVER_Z, DEALER_DELIVER_A, vehStatus);

    new DBResult:res = DB_ExecuteQuery(gDB, qInsert);
    if (res) DB_FreeResultSet(res);

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

    CloseDealership(playerid);

    if (canSpawn) {
        new slot = GetPlayerEmptyVehSlot(playerid);
        if (slot != -1) {
            new vehId = CreateVehicle(modelid, DEALER_DELIVER_X, DEALER_DELIVER_Y, DEALER_DELIVER_Z, DEALER_DELIVER_A, chosenColor, chosenColor, -1);
            if (vehId != INVALID_VEHICLE_ID) {
                SetVehicleNumberPlate(vehId, plate);
                SetVehicleToRespawn(vehId);
                SetVehiclePos(vehId, DEALER_DELIVER_X, DEALER_DELIVER_Y, DEALER_DELIVER_Z);
                SetVehicleZAngle(vehId, DEALER_DELIVER_A);
                SetVehicleParamsEx(vehId, 1, 0, 0, 0, 0, 0, 0); // Mesin langsung menyala

                gPlayerData[playerid][p_ActiveVehID][slot] = vehId;
                gPlayerData[playerid][p_ActiveVehDBID][slot] = vehDbId;

                // Langsung masukkan pemain ke kursi pengemudi
                PutPlayerInVehicle(playerid, vehId, 0);
            }
        }
    }

    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);

    new priceFmt[32];
    FormatRupiah(price, priceFmt, sizeof(priceFmt));

    SendClientMessage(playerid, COL_GREEN, "====================================================================");
    SendClientMessage(playerid, COL_CYAN,  "  [Coutt & Schutz Showroom] SELAMAT! Transaksi Pembelian Kendaraan Berhasil.");
    
    new infoMsg[144];
    format(infoMsg, sizeof(infoMsg), "  > Unit: {FFFFFF}%s (%s) {A0AEC0}| Warna: {FFFFFF}%s {A0AEC0}| Harga: {2ECC71}%s",
        name, type, gDealerColorNames[colorIdx], priceFmt);
    SendClientMessage(playerid, COL_WHITE, infoMsg);

    format(infoMsg, sizeof(infoMsg), "  > Plat Nomor: {00EEFF}%s {A0AEC0}| Kunci: {2ECC71}Tersedia di saku Anda", plate);
    SendClientMessage(playerid, COL_WHITE, infoMsg);

    if (canSpawn) {
        format(infoMsg, sizeof(infoMsg), "  > Status: {2ECC71}Dikeluarkan di depan dealer {A0AEC0}(Kendaraan aktif: %d/5)", GetPlayerActiveVehCount(playerid));
        SendClientMessage(playerid, COL_WHITE, infoMsg);
    } else {
        SendClientMessage(playerid, COL_YELLOW, "  > Status: {F1C40F}Disimpan langsung di Garasi Rodeo (karena kuota 5 mobil aktif penuh).");
    }

    SendClientMessage(playerid, COL_YELLOW, "  > Gunakan {FFFFFF}/lock {FFFF00}untuk kunci, {FFFFFF}/engine {FFFF00}untuk mesin, {FFFFFF}/garasi {FFFF00}untuk simpan.");
    SendClientMessage(playerid, COL_GREEN, "====================================================================");
    return 1;
}

//    5. Sistem Asuransi Kendaraan (OnVehicleDeath & Klaim)    

stock OnPlayerVehicleDeath(vehicleid, killerid) {
    #pragma unused killerid
    for (new i = 0; i < MAX_PLAYERS; i++) {
        if (!IsPlayerConnected(i)) continue;
        new slot = GetPlayerActiveVehSlot(i, vehicleid);
        if (slot != -1) {
            new dbId = gPlayerData[i][p_ActiveVehDBID][slot];
            if (dbId > 0) {
                // Update database ke status asuransi
                new q[256];
                format(q, sizeof(q),
                    "UPDATE `player_vehicles` SET `status`=%d, `health`=300.0 WHERE `id`=%d",
                    VEH_STATUS_INSURANCE, dbId);
                DB_FreeResultSet(DB_ExecuteQuery(gDB, q));
            }

            gPlayerData[i][p_ActiveVehID][slot] = INVALID_VEHICLE_ID;
            gPlayerData[i][p_ActiveVehDBID][slot] = 0;

            PlayerPlaySound(i, 1084, 0.0, 0.0, 0.0);
            SendClientMessage(i, COL_RED, "====================================================================");
            SendClientMessage(i, COL_RED, "  [ASURANSI KOTA] Kendaraan pribadi Anda telah hancur / meledak!");
            SendClientMessage(i, COL_WHITE,"  > Data kendaraan telah diamankan di {00EEFF}Kantor Asuransi Los Santos{FFFFFF}.");
            SendClientMessage(i, COL_YELLOW,"  > Silakan datang ke loket Kantor Asuransi ({00EEFF}/asuransi{FFFF00}) untuk klaim & tebus.");
            SendClientMessage(i, COL_RED, "====================================================================");
            break;
        }
    }
    return 1;
}

stock ShowInsuranceMenu(playerid) {
    if (!gPlayerData[playerid][p_LoggedIn] || !gPlayerData[playerid][p_Spawned]) return 0;
    if (gPlayerData[playerid][p_CharID] <= 0) return 0;

    new query[256];
    format(query, sizeof(query),
        "SELECT `id`, `model_id`, `plate`, `insurance_cost` FROM `player_vehicles` WHERE `char_id`=%d AND `status`=%d",
        gPlayerData[playerid][p_CharID], VEH_STATUS_INSURANCE);

    new DBResult:res = DB_ExecuteQuery(gDB, query);
    new count = 0;
    new listStr[512] = "Nama Kendaraan\tPlat Nomor\tBiaya Klaim\n";

    if (res) {
        count = DB_GetRowCount(res);
        if (count > 0) {
            for (new i = 0; i < count && i < 32; i++) {
                new dbId = DB_GetFieldIntByName(res, "id");
                new modelid = DB_GetFieldIntByName(res, "model_id");
                new cost = DB_GetFieldIntByName(res, "insurance_cost");
                new plate[16];
                DB_GetFieldStringByName(res, "plate", plate, sizeof(plate));

                gPlayerData[playerid][p_VehListDBIDs][i] = dbId;

                new vName[32], costFmt[32];
                GetModelFullName(modelid, vName, sizeof(vName));
                FormatRupiah(cost, costFmt, sizeof(costFmt));

                format(listStr, sizeof(listStr), "%s{FFFFFF}%s\t{00EEFF}%s\t{2ECC71}%s\n", listStr, vName, plate, costFmt);
                DB_SelectNextRow(res);
            }
        }
        DB_FreeResultSet(res);
    }

    gPlayerData[playerid][p_VehListCount] = count;

    if (count <= 0) {
        SendClientMessage(playerid, COL_GREEN, "  [Asuransi] Anda tidak memiliki kendaraan yang hancur / berada dalam asuransi.");
        return 1;
    }

    ShowPlayerDialog(playerid, DLG_INSURANCE_MAIN, DIALOG_STYLE_TABLIST_HEADERS,
        "{2ECC71}Kantor Asuransi Los Santos - Klaim Kendaraan", listStr, "Tebus / Klaim", "Batal");
    return 1;
}

stock HandleInsuranceDialog(playerid, dialogid, response, listitem) {
    if (dialogid == DLG_INSURANCE_MAIN) {
        if (!response) return 1;
        if (listitem < 0 || listitem >= gPlayerData[playerid][p_VehListCount]) return 1;

        new dbId = gPlayerData[playerid][p_VehListDBIDs][listitem];
        gPlayerData[playerid][p_SelectedVehDBID] = dbId;

        new query[128];
        format(query, sizeof(query), "SELECT * FROM `player_vehicles` WHERE `id`=%d LIMIT 1", dbId);
        new DBResult:res = DB_ExecuteQuery(gDB, query);
        if (!res || DB_GetRowCount(res) == 0) {
            if (res) DB_FreeResultSet(res);
            return 1;
        }

        new modelid = DB_GetFieldIntByName(res, "model_id");
        new cost = DB_GetFieldIntByName(res, "insurance_cost");
        new plate[16];
        DB_GetFieldStringByName(res, "plate", plate, sizeof(plate));
        DB_FreeResultSet(res);

        new vName[32], costFmt[32];
        GetModelFullName(modelid, vName, sizeof(vName));
        FormatRupiah(cost, costFmt, sizeof(costFmt));

        new confStr[300];
        format(confStr, sizeof(confStr),
            "{FFFFFF}Anda akan melakukan klaim asuransi untuk kendaraan:\n\n" \
            "  > Model: {FFFF00}%s\n" \
            "  > Plat Nomor: {00EEFF}%s\n" \
            "  > Biaya Klaim: {2ECC71}%s\n\n" \
            "{FFFFFF}Setelah ditebus, kondisi kendaraan kembali prima (1000 HP) dan\n" \
            "dapat langsung diambil di seluruh {00EEFF}Garasi Publik Kota{FFFFFF}.\n\n" \
            "Apakah Anda yakin ingin membayar dan memulihkan kendaraan ini?",
            vName, plate, costFmt);

        ShowPlayerDialog(playerid, DLG_INSURANCE_CONFIRM, DIALOG_STYLE_MSGBOX,
            "{2ECC71}Konfirmasi Klaim Asuransi", confStr, "Bayar & Klaim", "Batal");
        return 1;
    }

    if (dialogid == DLG_INSURANCE_CONFIRM) {
        if (!response) return 1;
        new dbId = gPlayerData[playerid][p_SelectedVehDBID];
        if (dbId <= 0) return 1;

        new query[128];
        format(query, sizeof(query), "SELECT * FROM `player_vehicles` WHERE `id`=%d LIMIT 1", dbId);
        new DBResult:res = DB_ExecuteQuery(gDB, query);
        if (!res || DB_GetRowCount(res) == 0) {
            if (res) DB_FreeResultSet(res);
            return 1;
        }

        new cost = DB_GetFieldIntByName(res, "insurance_cost");
        new modelid = DB_GetFieldIntByName(res, "model_id");
        new plate[16];
        DB_GetFieldStringByName(res, "plate", plate, sizeof(plate));
        DB_FreeResultSet(res);

        if (gPlayerData[playerid][p_Cash] < cost) {
            PlayerPlaySound(playerid, 1055, 0.0, 0.0, 0.0);
            SendClientMessage(playerid, COL_RED, "  [Asuransi] Uang tunai Anda tidak mencukupi untuk membayar biaya klaim asuransi!");
            return 1;
        }

        // Potong uang dan update database
        gPlayerData[playerid][p_Cash] -= cost;
        UpdatePlayerMoneyHUD(playerid);

        new qMoney[128];
        format(qMoney, sizeof(qMoney), "UPDATE `characters` SET `cash`=%d WHERE `id`=%d",
            gPlayerData[playerid][p_Cash], gPlayerData[playerid][p_CharID]);
        DB_FreeResultSet(DB_ExecuteQuery(gDB, qMoney));

        // Pulihkan status kendaraan ke Garasi Los Santos Parking Lot
        new qUp[256];
        format(qUp, sizeof(qUp),
            "UPDATE `player_vehicles` SET `status`=%d, `health`=1000.0, `garage_id`=0 WHERE `id`=%d",
            VEH_STATUS_GARAGE, dbId);
        DB_FreeResultSet(DB_ExecuteQuery(gDB, qUp));

        PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);

        new vName[32];
        GetModelFullName(modelid, vName, sizeof(vName));

        SendClientMessage(playerid, COL_GREEN, "====================================================================");
        SendClientMessage(playerid, COL_CYAN,  "  [Asuransi Kota] Klaim asuransi kendaraan berhasil diproses!");
        new msg[144];
        format(msg, sizeof(msg), "  > Unit: {FFFFFF}%s {A0AEC0}| Plat: {00EEFF}%s {A0AEC0}| Kondisi: {2ECC71}100%% Prima", vName, plate);
        SendClientMessage(playerid, COL_WHITE, msg);
        SendClientMessage(playerid, COL_YELLOW, "  > Kendaraan siap diambil di Los Santos Parking Lot ({00EEFF}/garasi{FFFF00}).");
        SendClientMessage(playerid, COL_GREEN, "====================================================================");
        return 1;
    }
    return 0;
}

//    6. Menu Manajemen Kendaraan Pribadi (/v)                  

stock ShowVehicleMenu(playerid) {
    if (!gPlayerData[playerid][p_LoggedIn] || !gPlayerData[playerid][p_Spawned]) return 0;
    if (gPlayerData[playerid][p_CharID] <= 0) return 0;

    new query[256];
    format(query, sizeof(query),
        "SELECT `id`, `model_id`, `plate`, `status`, `health`, `garage_id` FROM `player_vehicles` WHERE `char_id`=%d ORDER BY `id` ASC",
        gPlayerData[playerid][p_CharID]);

    new DBResult:res = DB_ExecuteQuery(gDB, query);
    new count = 0;
    new listStr[600] = "Nama Kendaraan\tPlat Nomor\tStatus Lokasi\n";

    if (res) {
        count = DB_GetRowCount(res);
        if (count > 0) {
            for (new i = 0; i < count && i < 32; i++) {
                new dbId = DB_GetFieldIntByName(res, "id");
                new modelid = DB_GetFieldIntByName(res, "model_id");
                new vStatus = DB_GetFieldIntByName(res, "status");
                new gid = DB_GetFieldIntByName(res, "garage_id");
                new plate[16];
                DB_GetFieldStringByName(res, "plate", plate, sizeof(plate));

                gPlayerData[playerid][p_VehListDBIDs][i] = dbId;

                new vName[32], statusTxt[48];
                GetModelFullName(modelid, vName, sizeof(vName));

                if (vStatus == VEH_STATUS_GARAGE) {
                    if (gid >= 0 && gid < PUBLIC_GARAGE_COUNT) {
                        format(statusTxt, sizeof(statusTxt), "{2ECC71}Garasi %s", gPublicGarages[gid][g_City]);
                    } else {
                        format(statusTxt, sizeof(statusTxt), "{2ECC71}Garasi Publik");
                    }
                } else if (vStatus == VEH_STATUS_OUTSIDE) {
                    if (GetPlayerActiveVehSlotByDBID(playerid, dbId) != -1) {
                        format(statusTxt, sizeof(statusTxt), "{00EEFF}Aktif Digunakan");
                    } else {
                        format(statusTxt, sizeof(statusTxt), "{F1C40F}Terparkir di Luar");
                    }
                } else {
                    format(statusTxt, sizeof(statusTxt), "{E74C3C}Dalam Asuransi");
                }

                format(listStr, sizeof(listStr), "%s{FFFFFF}%s\t{00EEFF}%s\t%s\n", listStr, vName, plate, statusTxt);
                DB_SelectNextRow(res);
            }
        }
        DB_FreeResultSet(res);
    }

    gPlayerData[playerid][p_VehListCount] = count;

    if (count <= 0) {
        SendClientMessage(playerid, COL_RED, "  [Kendaraan] Anda belum memiliki kendaraan pribadi terdaftar!");
        SendClientMessage(playerid, COL_YELLOW, "  > Silakan beli kendaraan di Rodeo Luxury Dealership ({00EEFF}/dealer{FFFF00}).");
        return 1;
    }

    ShowPlayerDialog(playerid, DLG_VEH_MAIN, DIALOG_STYLE_TABLIST_HEADERS,
        "{00EEFF}Koleksi Kendaraan Pribadi", listStr, "Kelola", "Tutup");
    return 1;
}

stock HandleVehicleMenuDialog(playerid, dialogid, response, listitem) {
    if (dialogid == DLG_VEH_MAIN) {
        if (!response) return 1;
        if (listitem < 0 || listitem >= gPlayerData[playerid][p_VehListCount]) return 1;

        new dbId = gPlayerData[playerid][p_VehListDBIDs][listitem];
        gPlayerData[playerid][p_SelectedVehDBID] = dbId;

        new query[128];
        format(query, sizeof(query), "SELECT * FROM `player_vehicles` WHERE `id`=%d LIMIT 1", dbId);
        new DBResult:res = DB_ExecuteQuery(gDB, query);
        if (!res || DB_GetRowCount(res) == 0) {
            if (res) DB_FreeResultSet(res);
            return 1;
        }

        new modelid = DB_GetFieldIntByName(res, "model_id");
        new plate[16];
        DB_GetFieldStringByName(res, "plate", plate, sizeof(plate));
        DB_FreeResultSet(res);

        new vName[32];
        GetModelFullName(modelid, vName, sizeof(vName));

        new menuTitle[64], actionsStr[512];
        format(menuTitle, sizeof(menuTitle), "{00EEFF}%s {FFFFFF}(%s)", vName, plate);

        format(actionsStr, sizeof(actionsStr),
            "Opsi Aksi\tKeterangan\n" \
            "{00EEFF}1. Lacak Lokasi (GPS)\tTandai lokasi kendaraan di radar map\n" \
            "{2ECC71}2. Kunci / Buka Pintu (Remote)\tKunci atau buka pintu kendaraan\n" \
            "{F1C40F}3. Kontrol Mesin\tNyalakan / matikan mesin\n" \
            "{FFFFFF}4. Informasi Detail\tCek status lengkap kendaraan");

        ShowPlayerDialog(playerid, DLG_VEH_ACTION, DIALOG_STYLE_TABLIST_HEADERS, menuTitle, actionsStr, "Pilih", "Kembali");
        return 1;
    }

    if (dialogid == DLG_VEH_ACTION) {
        if (!response) {
            return ShowVehicleMenu(playerid);
        }

        new dbId = gPlayerData[playerid][p_SelectedVehDBID];
        if (dbId <= 0) return 1;

        new query[128];
        format(query, sizeof(query), "SELECT * FROM `player_vehicles` WHERE `id`=%d LIMIT 1", dbId);
        new DBResult:res = DB_ExecuteQuery(gDB, query);
        if (!res || DB_GetRowCount(res) == 0) {
            if (res) DB_FreeResultSet(res);
            return 1;
        }

        new modelid = DB_GetFieldIntByName(res, "model_id");
        new vStatus = DB_GetFieldIntByName(res, "status");
        new gid     = DB_GetFieldIntByName(res, "garage_id");
        new Float:vx = DB_GetFieldFloatByName(res, "x");
        new Float:vy = DB_GetFieldFloatByName(res, "y");
        new Float:vz = DB_GetFieldFloatByName(res, "z");
        new Float:vhp = DB_GetFieldFloatByName(res, "health");
        new plate[16];
        DB_GetFieldStringByName(res, "plate", plate, sizeof(plate));
        DB_FreeResultSet(res);

        new vName[32];
        GetModelFullName(modelid, vName, sizeof(vName));

        switch (listitem) {
            case 0: { // 1. Lacak GPS
                if (vStatus == VEH_STATUS_GARAGE) {
                    if (gid < 0 || gid >= PUBLIC_GARAGE_COUNT) gid = 0;
                    SetGPSWaypoint(playerid, gPublicGarages[gid][g_MarkerX], gPublicGarages[gid][g_MarkerY], gPublicGarages[gid][g_MarkerZ], 4.0);
                    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);

                    new msg[144];
                    format(msg, sizeof(msg), "  [GPS] Menandai lokasi: {00EEFF}%s {FFFFFF}(%s).",
                        gPublicGarages[gid][g_Name], gPublicGarages[gid][g_City]);
                    SendClientMessage(playerid, COL_GREEN, msg);
                    SendClientMessage(playerid, COL_YELLOW, "  > Ikuti tanda waypoint di radar map. Gunakan {FFFFFF}/cp {FFFF00}untuk mematikan GPS.");
                } else if (vStatus == VEH_STATUS_INSURANCE) {
                    SetGPSWaypoint(playerid, INSURANCE_X, INSURANCE_Y, INSURANCE_Z, 4.0);
                    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);

                    SendClientMessage(playerid, COL_RED, "  [GPS] Kendaraan ini berada di {00EEFF}Kantor Asuransi Los Santos{FFFFFF}.");
                    SendClientMessage(playerid, COL_YELLOW, "  > Silakan datangi loket asuransi untuk klaim & tebus kendaraan.");
                    SendClientMessage(playerid, COL_YELLOW, "  > Ikuti tanda waypoint di radar map. Gunakan {FFFFFF}/cp {FFFF00}untuk mematikan GPS.");
                } else {
                    // Terparkir di luar
                    new actSlot = GetPlayerActiveVehSlotByDBID(playerid, dbId);
                    if (actSlot != -1 && gPlayerData[playerid][p_ActiveVehID][actSlot] != INVALID_VEHICLE_ID) {
                        GetVehiclePos(gPlayerData[playerid][p_ActiveVehID][actSlot], vx, vy, vz);
                    }
                    SetGPSWaypoint(playerid, vx, vy, vz, 4.0);
                    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);

                    new msg[144];
                    format(msg, sizeof(msg), "  [GPS] Menandai posisi kendaraan {00EEFF}%s {FFFFFF}(%s).", vName, plate);
                    SendClientMessage(playerid, COL_GREEN, msg);
                    SendClientMessage(playerid, COL_YELLOW, "  > Ikuti tanda waypoint di radar map. Gunakan {FFFFFF}/cp {FFFF00}untuk mematikan GPS.");
                }
            }
            case 1: { // 2. Kunci / Buka Pintu
                new actSlot = GetPlayerActiveVehSlotByDBID(playerid, dbId);
                if (actSlot == -1 || gPlayerData[playerid][p_ActiveVehID][actSlot] == INVALID_VEHICLE_ID) {
                    SendClientMessage(playerid, COL_RED, "  [Kendaraan] Kendaraan ini sedang tidak aktif / tersimpan di garasi.");
                    return 1;
                }
                new vehId = gPlayerData[playerid][p_ActiveVehID][actSlot];
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
            }
            case 2: { // 3. Kontrol Mesin
                new emptyParams[1];
                cmd_engine(playerid, emptyParams);
            }
            case 3: { // 4. Informasi Detail
                new statusStr[64];
                if (vStatus == VEH_STATUS_GARAGE) {
                    if (gid >= 0 && gid < PUBLIC_GARAGE_COUNT) {
                        format(statusStr, sizeof(statusStr), "Tersimpan di Garasi (%s)", gPublicGarages[gid][g_Name]);
                    } else {
                        format(statusStr, sizeof(statusStr), "Tersimpan di Garasi Publik");
                    }
                } else if (vStatus == VEH_STATUS_OUTSIDE) {
                    format(statusStr, sizeof(statusStr), "Terparkir di Luar (Aktif)");
                } else {
                    format(statusStr, sizeof(statusStr), "Hancur di Kantor Asuransi");
                }

                new hpPct = floatround((vhp / 1000.0) * 100.0);
                if (hpPct > 100) hpPct = 100;
                if (hpPct < 0) hpPct = 0;

                new detailStr[350];
                format(detailStr, sizeof(detailStr),
                    "{FFFFFF}Informasi Kendaraan Pribadi:\n\n" \
                    "  > Model Unit: {FFFF00}%s\n" \
                    "  > Plat Nomor: {00EEFF}%s\n" \
                    "  > Kondisi Darah Mesin: {2ECC71}%d%% {A0AEC0}(%.1f HP)\n" \
                    "  > Status Penyimpanan: {FFFFFF}%s\n" \
                    "  > Kunci Fisik: {2ECC71}Tersedia di Saku Anda",
                    vName, plate, hpPct, vhp, statusStr);

                ShowPlayerDialog(playerid, 9999, DIALOG_STYLE_MSGBOX, "{00EEFF}Detail Kendaraan", detailStr, "Tutup", "");
            }
        }
        return 1;
    }
    return 0;
}

//    7. Perintah Standarisasi Tunggal (Single Clean Commands)  

CMD:v(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    ShowVehicleMenu(playerid);
    return 1;
}

CMD:garasi(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;

    // Cari garasi terdekat (radius 8 meter)
    new nearestGarage = -1;
    for (new i = 0; i < PUBLIC_GARAGE_COUNT; i++) {
        if (IsPlayerInRangeOfPoint(playerid, 8.0, gPublicGarages[i][g_MarkerX], gPublicGarages[i][g_MarkerY], gPublicGarages[i][g_MarkerZ])) {
            nearestGarage = i;
            break;
        }
    }

    if (nearestGarage == -1) {
        SendClientMessage(playerid, COL_RED, "  [Garasi] Anda tidak berada di dekat titik Garasi Publik Kota manapun!");
        SendClientMessage(playerid, COL_YELLOW, "  > Gunakan {00EEFF}/v {FFFF00}-> Pilih Kendaraan -> Lacak GPS untuk menuju garasi terdekat.");
        return 1;
    }

    // Jika sedang di dalam kendaraan pribadi miliknya -> Simpan ke garasi
    if (IsPlayerInAnyVehicle(playerid)) {
        new curVeh = GetPlayerVehicleID(playerid);
        if (IsPlayerActiveVeh(playerid, curVeh)) {
            StoreVehicleInGarage(playerid, nearestGarage);
            return 1;
        } else {
            SendClientMessage(playerid, COL_RED, "  [Garasi] Anda hanya dapat menyimpan kendaraan pribadi milik Anda sendiri!");
            return 1;
        }
    }

    // Jika berjalan kaki -> Buka Live 3D Garage Vehicle Selector UI
    OpenGarageUI(playerid, nearestGarage);
    return 1;
}

CMD:asuransi(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;

    if (!IsPlayerInRangeOfPoint(playerid, 5.0, INSURANCE_X, INSURANCE_Y, INSURANCE_Z)) {
        SendClientMessage(playerid, COL_RED, "  [Asuransi] Anda harus berdiri di depan loket Kantor Asuransi Los Santos!");
        SendClientMessage(playerid, COL_YELLOW, "  > Lokasi: Commerce Los Santos (Gunakan {00EEFF}/v{FFFF00} -> Lacak GPS).");
        return 1;
    }

    ShowInsuranceMenu(playerid);
    return 1;
}

CMD:dealer(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;

    if (!IsPlayerInRangeOfPoint(playerid, 5.0, DEALER_RODEO_X, DEALER_RODEO_Y, DEALER_RODEO_Z)) {
        SendClientMessage(playerid, COL_RED, "  [Dealer] Anda harus berdiri di depan mark Coutt and Schutz Auto Showroom!");
        SendClientMessage(playerid, COL_YELLOW, "  > Lokasi: Rodeo / Market, Los Santos (Gunakan /gps).");
        return 1;
    }

    OpenDealership(playerid);
    return 1;
}

CMD:lock(playerid, params[]) {
    #pragma unused params
    TogglePlayerVehicleLock(playerid);
    return 1;
}

CMD:engine(playerid, params[]) {
    #pragma unused params
    TogglePlayerVehicleEngine(playerid);
    return 1;
}

//    8. Map Icons & Sistem Legenda Peta (GPS Navigasi)         

stock SetGPSWaypoint(playerid, Float:x, Float:y, Float:z, Float:size = 4.0) {
    DisablePlayerCheckpoint(playerid);
    DisablePlayerRaceCheckpoint(playerid);
    RemovePlayerMapIcon(playerid, 99);

    // Aktifkan Waypoint Marker (Race Checkpoint dengan penunjuk arah & Dynamic Blip)
    SetPlayerRaceCheckpoint(playerid, 0, x, y, z, 0.0, 0.0, 0.0, size);
    SetPlayerCheckpoint(playerid, x, y, z, size);
    SetPlayerMapIcon(playerid, 99, x, y, z, 0, 0x00EEFFFF, MAPICON_GLOBAL);
    gPlayerData[playerid][p_HasActiveCheckpoint] = true;
    return 1;
}

stock ClearGPSWaypoint(playerid) {
    DisablePlayerCheckpoint(playerid);
    DisablePlayerRaceCheckpoint(playerid);
    RemovePlayerMapIcon(playerid, 99);
    gPlayerData[playerid][p_HasActiveCheckpoint] = false;
    return 1;
}

stock SetupPlayerMapIcons(playerid) {
    #pragma unused playerid
    // Seluruh static icon di map ditiadakan. Navigasi murni mengandalkan /gps waypoint
    return 1;
}

stock ShowGPSMenu(playerid) {
    if (!CheckSpawned(playerid)) return 0;

    new menuStr[512];
    format(menuStr, sizeof(menuStr),
        "Lokasi Fasilitas Publik\tWilayah & Keterangan\n" \
        "{33CCFF}[Balai Kota] Loket e-KTP\t{FFFFFF}Pershing Square, Los Santos\n" \
        "{00EEFF}[Showroom] Coutt & Schutz\t{FFFFFF}Rodeo / Market, Los Santos\n" \
        "{2ECC71}[Kantor Asuransi] 3 Kota\t{FFFFFF}Los Santos, San Fierro, Las Venturas\n" \
        "{F1C40F}[Parkir Kota] Los Santos Parking Lot\t{FFFFFF}Downtown Los Santos");

    ShowPlayerDialog(playerid, DLG_GPS_MENU, DIALOG_STYLE_TABLIST_HEADERS,
        "{E69958}Navigasi GPS Kota SantaraBaru", menuStr, "Navigasi", "Tutup");
    return 1;
}

stock HandleGPSDialog(playerid, dialogid, response, listitem) {
    if (dialogid == DLG_GPS_MENU) {
        if (!response) return 1;

        switch (listitem) {
            case 0: { // Balai Kota
                SetGPSWaypoint(playerid, CITYHALL_EXT_X, CITYHALL_EXT_Y, CITYHALL_EXT_Z, 4.0);
                PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
                SendClientMessage(playerid, COL_GREEN, "  [GPS] Menandai rute menuju: {33CCFF}Balai Kota Los Santos (Pershing Square).");
                SendClientMessage(playerid, COL_YELLOW, "  > Ikuti tanda waypoint di radar map. Gunakan {FFFFFF}/cp {FFFF00}untuk mematikan GPS.");
            }
            case 1: { // Coutt & Schutz Showroom
                SetGPSWaypoint(playerid, DEALER_RODEO_X, DEALER_RODEO_Y, DEALER_RODEO_Z, 4.0);
                PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
                SendClientMessage(playerid, COL_GREEN, "  [GPS] Menandai rute menuju: {00EEFF}Coutt and Schutz Auto Showroom (Los Santos).");
                SendClientMessage(playerid, COL_YELLOW, "  > Ikuti tanda waypoint di radar map. Gunakan {FFFFFF}/cp {FFFF00}untuk mematikan GPS.");
            }
            case 2: { // Kantor Asuransi (Pilih Cabang Kota)
                new insListStr[512];
                format(insListStr, sizeof(insListStr), "Cabang Asuransi\tKota / Wilayah\n");
                for (new i = 0; i < INSURANCE_BRANCH_COUNT; i++) {
                    format(insListStr, sizeof(insListStr), "%s{FFFFFF}%s\t{2ECC71}%s\n",
                        insListStr, gInsuranceBranches[i][ins_Name], gInsuranceBranches[i][ins_City]);
                }
                ShowPlayerDialog(playerid, DLG_GPS_INSURANCE, DIALOG_STYLE_TABLIST_HEADERS,
                    "{2ECC71}Pilih Kantor Cabang Asuransi", insListStr, "Navigasi", "Kembali");
            }
            case 3: { // Langsung Navigasi ke Los Santos Parking Lot
                SetGPSWaypoint(playerid, gPublicGarages[0][g_MarkerX], gPublicGarages[0][g_MarkerY], gPublicGarages[0][g_MarkerZ], 4.0);
                PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
                SendClientMessage(playerid, COL_GREEN, "  [GPS] Menandai rute menuju: {F1C40F}Los Santos Parking Lot (Downtown Los Santos).");
                SendClientMessage(playerid, COL_YELLOW, "  > Ikuti tanda waypoint di radar map. Gunakan {FFFFFF}/cp {FFFF00}untuk mematikan GPS.");
            }
        }
        return 1;
    }

    if (dialogid == DLG_GPS_INSURANCE) {
        if (!response) {
            return ShowGPSMenu(playerid);
        }
        if (listitem < 0 || listitem >= INSURANCE_BRANCH_COUNT) return 1;

        SetGPSWaypoint(playerid, gInsuranceBranches[listitem][ins_X], gInsuranceBranches[listitem][ins_Y], gInsuranceBranches[listitem][ins_Z], 4.0);
        PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);

        new msg[144];
        format(msg, sizeof(msg), "  [GPS] Menandai rute menuju: {2ECC71}%s {FFFFFF}(%s).",
            gInsuranceBranches[listitem][ins_Name], gInsuranceBranches[listitem][ins_City]);
        SendClientMessage(playerid, COL_GREEN, msg);
        SendClientMessage(playerid, COL_YELLOW, "  > Ikuti tanda waypoint di radar map. Gunakan {FFFFFF}/cp {FFFF00}untuk mematikan GPS.");
        return 1;
    }

    if (dialogid == DLG_GPS_GARAGE) {
        if (!response) {
            return ShowGPSMenu(playerid);
        }
        if (listitem < 0 || listitem >= PUBLIC_GARAGE_COUNT) return 1;

        SetGPSWaypoint(playerid, gPublicGarages[listitem][g_MarkerX], gPublicGarages[listitem][g_MarkerY], gPublicGarages[listitem][g_MarkerZ], 4.0);
        PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);

        new msg[144];
        format(msg, sizeof(msg), "  [GPS] Menandai rute menuju: {00EEFF}%s {FFFFFF}(%s).",
            gPublicGarages[listitem][g_Name], gPublicGarages[listitem][g_City]);
        SendClientMessage(playerid, COL_GREEN, msg);
        SendClientMessage(playerid, COL_YELLOW, "  > Ikuti tanda waypoint di radar map. Gunakan {FFFFFF}/cp {FFFF00}untuk mematikan GPS.");
        return 1;
    }
    return 0;
}

CMD:gps(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    ShowGPSMenu(playerid);
    return 1;
}

CMD:lokasi(playerid, params[]) {
    return cmd_gps(playerid, params);
}

CMD:map(playerid, params[]) {
    return cmd_gps(playerid, params);
}

// ============================================================
//  9. Sistem Bagasi Kendaraan (Vehicle Trunk & Storage)
// ============================================================

forward ShowTrunkUI(playerid, vehicleid);

stock GetVehicleDBID(vehicleid) {
    if (vehicleid == INVALID_VEHICLE_ID || vehicleid <= 0) return 0;
    for (new i = 0; i < MAX_PLAYERS; i++) {
        if (!IsPlayerConnected(i)) continue;
        new slot = GetPlayerActiveVehSlot(i, vehicleid);
        if (slot != -1) {
            return gPlayerData[i][p_ActiveVehDBID][slot];
        }
    }
    return 0;
}

stock GetVehiclePlate(vehicleid, plate[], maxlen) {
    new dbId = GetVehicleDBID(vehicleid);
    if (dbId > 0) {
        new query[96];
        format(query, sizeof(query), "SELECT `plate` FROM `player_vehicles` WHERE `id`=%d LIMIT 1", dbId);
        new DBResult:res = DB_ExecuteQuery(gDB, query);
        if (res && DB_GetRowCount(res) > 0) {
            DB_GetFieldStringByName(res, "plate", plate, maxlen);
            DB_FreeResultSet(res);
            return 1;
        }
        if (res) DB_FreeResultSet(res);
    }
    format(plate, maxlen, "SAN-001");
    return 0;
}

stock bool:HasVehicleBoot(modelid) {
    switch (modelid) {
        // Sedans / Coupes / Luxury
        case 405, 410, 412, 419, 420, 421, 426, 436, 438, 439, 445, 458, 466, 467,
             474, 475, 479, 491, 492, 496, 507, 516, 517, 518, 526, 527, 529, 540,
             542, 545, 546, 547, 549, 550, 551, 555, 560, 561, 562, 565, 566, 567,
             575, 576, 580, 585, 602, 603: return true;

        // Sports / Supercars
        case 402, 411, 415, 429, 451, 477, 494, 502, 503, 506, 541, 558, 559: return true;

        // SUVs, Vans, Wagons, Pickups, Hatchbacks
        case 400, 404, 418, 422, 440, 459, 478, 482, 499, 500, 505, 508, 543, 554,
             579, 582, 589, 600, 604, 605: return true;

        // Police & Public Service Cars
        case 427, 490, 528, 596, 597, 598, 599: return true;
    }
    return false;
}

stock bool:IsPlayerAtVehicleBoot(playerid, vehicleid) {
    if (!IsPlayerConnected(playerid) || vehicleid == INVALID_VEHICLE_ID) return false;
    new Float:px, Float:py, Float:pz;
    GetPlayerPos(playerid, px, py, pz);

    new Float:vx, Float:vy, Float:vz, Float:va;
    GetVehiclePos(vehicleid, vx, vy, vz);
    GetVehicleZAngle(vehicleid, va);

    new modelid = GetVehicleModel(vehicleid);
    new Float:sizeX, Float:sizeY, Float:sizeZ;
    GetVehicleModelInfo(modelid, VEHICLE_MODEL_INFO_SIZE, sizeX, sizeY, sizeZ);

    // Titik koordinat bagasi belakang mobil
    new Float:distRear = (sizeY / 2.0) + 0.3;
    new Float:rearX = vx - (distRear * floatsin(-va, degrees));
    new Float:rearY = vy - (distRear * floatcos(-va, degrees));

    // Cek jarak pemain ke titik bagasi belakang (radius 2.8 meter)
    new Float:dx = px - rearX;
    new Float:dy = py - rearY;
    new Float:dz = pz - vz;
    new Float:dist = floatsqroot((dx * dx) + (dy * dy) + (dz * dz));

    return (dist <= 2.8);
}

stock SetVehicleBootOpen(vehicleid, bool:open) {
    if (vehicleid == INVALID_VEHICLE_ID || vehicleid <= 0) return 0;
    new engine, lights, alarm, doors, bonnet, boot, objective;
    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
    boot = (open) ? (1) : (0);
    SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
    return 1;
}

stock bool:IsVehicleLocked(vehicleid) {
    if (vehicleid == INVALID_VEHICLE_ID || vehicleid <= 0) return false;
    new engine, lights, alarm, doors, bonnet, boot, objective;
    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
    return (doors == 1);
}

// 1. Load isi bagasi mobil ke player cache
stock Trunk_LoadItems(veh_dbid, playerid) {
    gPlayerData[playerid][p_TrunkItemCount] = 0;
    for (new s = 0; s < 64; s++) {
        gPlayerData[playerid][p_TrunkSlotItemID][s] = 0;
        gPlayerData[playerid][p_TrunkSlotAmount][s] = 0;
    }

    if (veh_dbid <= 0) return 0;

    new query[160];
    format(query, sizeof(query), "SELECT `item_id`, `amount` FROM `vehicle_trunk` WHERE `veh_dbid`=%d ORDER BY `id` ASC LIMIT 64", veh_dbid);
    new DBResult:res = DB_ExecuteQuery(gDB, query);
    if (!res) return 0;

    new count = 0;
    new rows = DB_GetRowCount(res);
    for (new r = 0; r < rows; r++) {
        new itId = DB_GetFieldIntByName(res, "item_id");
        new itAmt = DB_GetFieldIntByName(res, "amount");
        if (itId > 0 && itAmt > 0) {
            gPlayerData[playerid][p_TrunkSlotItemID][count] = itId;
            gPlayerData[playerid][p_TrunkSlotAmount][count] = itAmt;
            count++;
        }
        DB_SelectNextRow(res);
    }
    DB_FreeResultSet(res);
    gPlayerData[playerid][p_TrunkItemCount] = count;
    return count;
}

// 2. Tambah barang ke bagasi mobil
stock Trunk_AddItem(veh_dbid, item_id, amount) {
    if (veh_dbid <= 0 || item_id <= 0 || amount <= 0) return 0;

    new query[160];
    format(query, sizeof(query), "SELECT `id`, `amount` FROM `vehicle_trunk` WHERE `veh_dbid`=%d AND `item_id`=%d LIMIT 1", veh_dbid, item_id);
    new DBResult:res = DB_ExecuteQuery(gDB, query);

    if (res && DB_GetRowCount(res) > 0) {
        new rowId = DB_GetFieldIntByName(res, "id");
        new curAmt = DB_GetFieldIntByName(res, "amount");
        DB_FreeResultSet(res);

        new newAmt = curAmt + amount;
        format(query, sizeof(query), "UPDATE `vehicle_trunk` SET `amount`=%d WHERE `id`=%d", newAmt, rowId);
        DB_FreeResultSet(DB_ExecuteQuery(gDB, query));
    } else {
        if (res) DB_FreeResultSet(res);
        format(query, sizeof(query), "INSERT INTO `vehicle_trunk` (`veh_dbid`, `item_id`, `amount`) VALUES (%d, %d, %d)", veh_dbid, item_id, amount);
        DB_FreeResultSet(DB_ExecuteQuery(gDB, query));
    }
    return 1;
}

// 3. Ambil / Hapus barang dari bagasi mobil
stock Trunk_RemoveItem(veh_dbid, item_id, amount) {
    if (veh_dbid <= 0 || item_id <= 0 || amount <= 0) return 0;

    new query[160];
    format(query, sizeof(query), "SELECT `id`, `amount` FROM `vehicle_trunk` WHERE `veh_dbid`=%d AND `item_id`=%d LIMIT 1", veh_dbid, item_id);
    new DBResult:res = DB_ExecuteQuery(gDB, query);

    if (res && DB_GetRowCount(res) > 0) {
        new rowId = DB_GetFieldIntByName(res, "id");
        new curAmt = DB_GetFieldIntByName(res, "amount");
        DB_FreeResultSet(res);

        if (amount >= curAmt) {
            format(query, sizeof(query), "DELETE FROM `vehicle_trunk` WHERE `id`=%d", rowId);
            DB_FreeResultSet(DB_ExecuteQuery(gDB, query));
        } else {
            new newAmt = curAmt - amount;
            format(query, sizeof(query), "UPDATE `vehicle_trunk` SET `amount`=%d WHERE `id`=%d", newAmt, rowId);
            DB_FreeResultSet(DB_ExecuteQuery(gDB, query));
        }
        return 1;
    }
    if (res) DB_FreeResultSet(res);
    return 0;
}

// 4. Hitung jumlah barang di bagasi mobil
stock Trunk_GetItemCount(veh_dbid, item_id) {
    if (veh_dbid <= 0 || item_id <= 0) return 0;

    new query[160];
    format(query, sizeof(query), "SELECT `amount` FROM `vehicle_trunk` WHERE `veh_dbid`=%d AND `item_id`=%d LIMIT 1", veh_dbid, item_id);
    new DBResult:res = DB_ExecuteQuery(gDB, query);
    if (!res || DB_GetRowCount(res) == 0) {
        if (res) DB_FreeResultSet(res);
        return 0;
    }
    new amt = DB_GetFieldIntByName(res, "amount");
    DB_FreeResultSet(res);
    return amt;
}

CMD:trunk(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;

    if (IsPlayerInAnyVehicle(playerid)) {
        SendClientMessage(playerid, COL_RED, "  [Bagasi] Anda harus keluar dari kendaraan dan berdiri di belakang bagasi mobil!");
        return 1;
    }

    // Cari kendaraan terdekat dalam radius 5 meter
    new nearestVeh = INVALID_VEHICLE_ID;
    new Float:nearestDist = 999.0;
    new Float:px, Float:py, Float:pz;
    GetPlayerPos(playerid, px, py, pz);

    for (new v = 1; v < MAX_VEHICLES; v++) {
        if (!IsValidVehicle(v)) continue;
        new Float:vx, Float:vy, Float:vz;
        GetVehiclePos(v, vx, vy, vz);
        new Float:dx = px - vx;
        new Float:dy = py - vy;
        new Float:dz = pz - vz;
        new Float:d = floatsqroot((dx * dx) + (dy * dy) + (dz * dz));
        if (d <= 5.0 && d < nearestDist) {
            nearestDist = d;
            nearestVeh = v;
        }
    }

    if (nearestVeh == INVALID_VEHICLE_ID) {
        SendClientMessage(playerid, COL_RED, "  [Bagasi] Tidak ada kendaraan di dekat Anda!");
        return 1;
    }

    new modelid = GetVehicleModel(nearestVeh);
    if (!HasVehicleBoot(modelid)) {
        SendClientMessage(playerid, COL_RED, "  [Bagasi] Kendaraan jenis ini tidak memiliki ruang bagasi belakang!");
        return 1;
    }

    if (!IsPlayerAtVehicleBoot(playerid, nearestVeh)) {
        SendClientMessage(playerid, COL_YELLOW, "  [Bagasi] Anda harus berdiri di bagian BELAKANG bagasi mobil untuk membukanya!");
        return 1;
    }

    if (IsVehicleLocked(nearestVeh)) {
        SendClientMessage(playerid, COL_RED, "  [Bagasi] Pintu bagasi terkunci! Buka kunci mobil terlebih dahulu (/lock).");
        return 1;
    }

    new vehDbId = GetVehicleDBID(nearestVeh);
    if (vehDbId <= 0) {
        SendClientMessage(playerid, COL_RED, "  [Bagasi] Kendaraan ini bukan kendaraan pribadi yang terdaftar.");
        return 1;
    }

    new charname[48], modelName[32], rpMsg[160];
    GetCharName(playerid, charname);
    GetModelFullName(modelid, modelName, sizeof(modelName));
    format(rpMsg, sizeof(rpMsg), "%s membuka kap bagasi mobil %s.", charname, modelName);
    DoProximityRaw(playerid, rpMsg, DIST_RP, COL_PURPLE);

    ShowTrunkUI(playerid, nearestVeh);
    return 1;
}

CMD:bagasi(playerid, params[]) {
    return cmd_trunk(playerid, params);
}


