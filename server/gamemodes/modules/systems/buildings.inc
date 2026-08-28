#if defined _MODULE_BUILDINGS_INC
    #endinput
#endif
#define _MODULE_BUILDINGS_INC

// ============================================================
//  SantaraBaru Roleplay - Buildings, Interiors & Restaurants
//  Balai Kota & 10 Cabang Restoran Burger Shot (WikiGTA)
// ============================================================

enum E_BURGER_SHOT_LOC {
    bs_Name[32],
    bs_City[24],
    Float:bs_X,
    Float:bs_Y,
    Float:bs_Z,
    Float:bs_A
};

// 10 Lokasi Cabang Resmi Burger Shot San Andreas (WikiGTA)
new const gBurgerShots[][E_BURGER_SHOT_LOC] = {
    {"Burger Shot Marina",            "Los Santos",     811.2437, -1615.9070, 13.5469, 270.0},
    {"Burger Shot Temple",            "Los Santos",    1199.0400,  -918.8413, 43.1172, 180.0},
    {"Burger Shot Garcia",            "San Fierro",   -2357.0920,  1006.4530, 50.6953,  90.0},
    {"Burger Shot Financial",         "San Fierro",   -1911.0780,   830.4195, 35.1562, 270.0},
    {"Burger Shot Juniper Hollow",    "San Fierro",   -2336.1310,  -166.6878, 35.5547, 180.0},
    {"Burger Shot Redsands East",     "Las Venturas",  1873.9290,  2071.9140, 11.0625,   0.0},
    {"Burger Shot Whitewood",         "Las Venturas",  1159.7700,  2072.3150, 11.0625,   0.0},
    {"Burger Shot Old Venturas Strip","Las Venturas", 2365.7260,  2071.9950, 11.0625,   0.0},
    {"Burger Shot Spinybed",          "Las Venturas",  2472.1230,  2035.0550, 11.0625,   0.0},
    {"Burger Shot Emerald Isle",      "Las Venturas",  2170.5610,  2794.5830, 10.8203,  90.0}
};
#define BURGER_SHOT_COUNT (sizeof(gBurgerShots))

stock InitBuildings() {
    // ─── 1. Balai Kota Los Santos (Pershing Square) ───
    CreatePickup(1239, 1, CITYHALL_EXT_X, CITYHALL_EXT_Y, CITYHALL_EXT_Z, 0);
    Create3DTextLabel(
        "{33CCFF}[ BALAI KOTA LOS SANTOS ]\n{FFFFFF}Tekan {FFFF00}[ F / ENTER ]{FFFFFF} untuk masuk",
        0xFFFFFFFF,
        CITYHALL_EXT_X, CITYHALL_EXT_Y, CITYHALL_EXT_Z + 0.5,
        15.0, 0, false
    );

    // Pintu Keluar Balai Kota (Interior Planning Dept)
    CreatePickup(1318, 1, CITYHALL_INT_X, CITYHALL_INT_Y, CITYHALL_INT_Z, 0);
    Create3DTextLabel(
        "{33CCFF}[ PINTU KELUAR ]\n{FFFFFF}Tekan {FFFF00}[ F / ENTER ]{FFFFFF} untuk keluar",
        0xFFFFFFFF,
        CITYHALL_INT_X, CITYHALL_INT_Y, CITYHALL_INT_Z + 0.5,
        12.0, 0, false
    );

    // Loket Catatan Sipil & e-KTP Balai Kota
    CreatePickup(1239, 1, KTP_DESK_X, KTP_DESK_Y, KTP_DESK_Z, 0);
    Create3DTextLabel(
        "{33CCFF}[ LOKET CATATAN SIPIL & E-KTP ]\n{FFFFFF}Tekan {FFFF00}[ F / ENTER ]{FFFFFF} atau ketik {FFFF00}/ktp{FFFFFF}\n{AAAAAA}Untuk membuat / menerbitkan e-KTP Anda",
        0xFFFFFFFF,
        KTP_DESK_X, KTP_DESK_Y, KTP_DESK_Z + 0.5,
        10.0, 0, false
    );

    // ─── 2. 10 Cabang Restoran Burger Shot (Eksterior) ───
    for (new i = 0; i < BURGER_SHOT_COUNT; i++) {
        CreatePickup(1239, 1, gBurgerShots[i][bs_X], gBurgerShots[i][bs_Y], gBurgerShots[i][bs_Z], 0);

        new labelText[160];
        format(labelText, sizeof(labelText),
            "{FFA500}[ RESTORAN BURGER SHOT ]\n{FFFFFF}%s (%s)\n{FFFF00}Tekan [ F / ENTER ] untuk masuk",
            gBurgerShots[i][bs_Name], gBurgerShots[i][bs_City]);

        Create3DTextLabel(labelText, 0xFFFFFFFF,
            gBurgerShots[i][bs_X], gBurgerShots[i][bs_Y], gBurgerShots[i][bs_Z] + 0.5,
            18.0, 0, false);
    }

    // ─── 3. Interior Restoran Burger Shot (Interior ID 10) ───
    // Pintu Keluar Interior Burger Shot (VW -1 agar berlaku untuk semua dimensi cabang)
    CreatePickup(1318, 1, BURGER_SHOT_INT_X, BURGER_SHOT_INT_Y, BURGER_SHOT_INT_Z, -1);
    Create3DTextLabel(
        "{FFA500}[ PINTU KELUAR ]\n{FFFFFF}Tekan {FFFF00}[ F / ENTER ]{FFFFFF} untuk keluar ke kota",
        0xFFFFFFFF,
        BURGER_SHOT_INT_X, BURGER_SHOT_INT_Y, BURGER_SHOT_INT_Z + 0.5,
        12.0, -1, false
    );

    // Kasir & Loket Pemesanan Makanan / Minuman (VW -1 agar berlaku untuk semua dimensi cabang)
    CreatePickup(1239, 1, BURGER_SHOT_COUNTER_X, BURGER_SHOT_COUNTER_Y, BURGER_SHOT_COUNTER_Z, -1);
    Create3DTextLabel(
        "{FFA500}[ KASIR BURGER SHOT ]\n{FFFFFF}Tekan {FFFF00}[ F / ENTER ]{FFFFFF} atau ketik {FFFF00}/buy{FFFFFF}\n{AAAAAA}Untuk memesan makanan & minuman",
        0xFFFFFFFF,
        BURGER_SHOT_COUNTER_X, BURGER_SHOT_COUNTER_Y, BURGER_SHOT_COUNTER_Z + 0.5,
        10.0, -1, false
    );

    // ─── 4. Satpas DMV Driving School (San Fierro) ───
    InitDrivingSchool();
}

stock ShowBurgerShotMenu(playerid) {
    if (!CheckSpawned(playerid)) return 0;

    new menuStr[512];
    format(menuStr, sizeof(menuStr),
        "Menu Makanan / Minuman\tKategori\tKhasiat\tHarga Satuan\n" \
        "{FFFFFF}Burger\t{2ECC71}Makanan\t{33CCFF}Lapar +40%%\t{00EEFF}Rp 25.000\n" \
        "{FFFFFF}Hotdog\t{2ECC71}Makanan\t{33CCFF}Lapar +35%%\t{00EEFF}Rp 20.000\n" \
        "{FFFFFF}Pizza\t{2ECC71}Makanan\t{33CCFF}Lapar +50%%\t{00EEFF}Rp 40.000\n" \
        "{FFFFFF}Air Mineral\t{33CCFF}Minuman\t{2ECC71}Haus +35%%\t{00EEFF}Rp 5.000\n" \
        "{FFFFFF}Cola\t{33CCFF}Minuman\t{2ECC71}Haus +40%%\t{00EEFF}Rp 10.000\n" \
        "{FFFFFF}Milkshake\t{33CCFF}Minuman\t{2ECC71}Haus +45%%, Lapar +10%%\t{00EEFF}Rp 20.000");

    ShowPlayerDialog(playerid, DLG_BURGER_SHOT, DIALOG_STYLE_TABLIST_HEADERS,
        "{FFA500}Kasir Restoran Burger Shot - Pilih Menu", menuStr, "Pesan", "Batal");
    return 1;
}

stock HandleBuildingKeys(playerid, KEY:newkeys, KEY:oldkeys) {
    #pragma unused oldkeys
    if (!gPlayerData[playerid][p_LoggedIn] || !gPlayerData[playerid][p_Spawned]) return 1;
    if (IsPlayerInAnyVehicle(playerid)) return 1;

    // Deteksi jika pemain menekan tombol F / ENTER (KEY_SECONDARY_ATTACK)
    if (newkeys & KEY_SECONDARY_ATTACK) {
        // ─── 1. Balai Kota Masuk & Keluar ───
        if (IsPlayerInRangeOfPoint(playerid, 2.5, CITYHALL_EXT_X, CITYHALL_EXT_Y, CITYHALL_EXT_Z) && GetPlayerInterior(playerid) == 0) {
            SetPlayerInterior(playerid, CITYHALL_INT_ID);
            SetPlayerPos(playerid, CITYHALL_INT_X, CITYHALL_INT_Y, CITYHALL_INT_Z);
            SetPlayerFacingAngle(playerid, CITYHALL_INT_A);
            SetCameraBehindPlayer(playerid);
            GameTextForPlayer(playerid, "~w~Selamat Datang di ~g~Balai Kota", 3000, 3);
            PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
            return 1;
        }

        if (IsPlayerInRangeOfPoint(playerid, 2.5, CITYHALL_INT_X, CITYHALL_INT_Y, CITYHALL_INT_Z) && GetPlayerInterior(playerid) == CITYHALL_INT_ID) {
            SetPlayerInterior(playerid, 0);
            SetPlayerPos(playerid, CITYHALL_EXT_X, CITYHALL_EXT_Y, CITYHALL_EXT_Z);
            SetPlayerFacingAngle(playerid, CITYHALL_EXT_A);
            SetCameraBehindPlayer(playerid);
            GameTextForPlayer(playerid, "~w~Keluar dari ~g~Balai Kota", 3000, 3);
            PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
            return 1;
        }

        // Interaksi Loket Pembuatan e-KTP di Balai Kota (Radius 1.6m agar tidak tumpang tindih)
        if (IsPlayerInRangeOfPoint(playerid, 1.6, KTP_DESK_X, KTP_DESK_Y, KTP_DESK_Z) && GetPlayerInterior(playerid) == KTP_DESK_INT_ID) {
            new emptyParam[1];
            cmd_buatktp(playerid, emptyParam);
            return 1;
        }

        // Interaksi Loket Pusat Tenaga Kerja / Job Center di Balai Kota (Radius 1.6m)
        if (IsPlayerInRangeOfPoint(playerid, 1.6, JOBCENTER_X, JOBCENTER_Y, JOBCENTER_Z) && GetPlayerInterior(playerid) == JOBCENTER_INT_ID) {
            ShowJobCenterMenu(playerid);
            return 1;
        }

        // Interaksi Loket Satpas DMV Driving School (San Fierro)
        if (IsPlayerInRangeOfPoint(playerid, 3.0, DMV_DESK_X, DMV_DESK_Y, DMV_DESK_Z) && GetPlayerInterior(playerid) == 0) {
            ShowDMVDialog(playerid);
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
            return 1;
        }

        // Interaksi Meja Kerja Rakit Senjata (Flint County Hideout)
        if (IsPlayerInRangeOfPoint(playerid, 2.5, CRAFT_BENCH_X, CRAFT_BENCH_Y, CRAFT_BENCH_Z) && GetPlayerInterior(playerid) == 0) {
            ShowCraftingMainMenu(playerid);
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
            return 1;
        }

        // Interaksi Menambang Batu di Hunter Quarry (Tekan F di dekat batu aktif)
        if (GetPlayerInterior(playerid) == 0 && TryStartMining(playerid)) {
            return 1;
        }

        // Interaksi Meja Smelter / Tungku Peleburan (Ocean Docks LS)
        if (GetPlayerInterior(playerid) == 0 && IsPlayerNearSmelter(playerid)) {
            ShowSmelterDialog(playerid);
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
            return 1;
        }

        // ─── 2. Burger Shot: Masuk Dari Salah Satu 10 Cabang Eksterior ───
        if (GetPlayerInterior(playerid) == 0) {
            for (new i = 0; i < BURGER_SHOT_COUNT; i++) {
                if (IsPlayerInRangeOfPoint(playerid, 2.5, gBurgerShots[i][bs_X], gBurgerShots[i][bs_Y], gBurgerShots[i][bs_Z])) {
                    // Simpan koordinat pintu masuk cabang ini agar nanti keluarnya pas
                    gPlayerData[playerid][p_LastExtX]  = gBurgerShots[i][bs_X];
                    gPlayerData[playerid][p_LastExtY]  = gBurgerShots[i][bs_Y];
                    gPlayerData[playerid][p_LastExtZ]  = gBurgerShots[i][bs_Z];
                    gPlayerData[playerid][p_LastExtA]  = gBurgerShots[i][bs_A];
                    gPlayerData[playerid][p_LastExtVW] = GetPlayerVirtualWorld(playerid);

                    // Setiap cabang dialokasikan Virtual World uniknya sendiri (101 - 110)
                    SetPlayerInterior(playerid, BURGER_SHOT_INT_ID);
                    SetPlayerVirtualWorld(playerid, BURGER_SHOT_VW_BASE + i);
                    SetPlayerPos(playerid, BURGER_SHOT_INT_X, BURGER_SHOT_INT_Y, BURGER_SHOT_INT_Z);
                    SetPlayerFacingAngle(playerid, BURGER_SHOT_INT_A);
                    SetCameraBehindPlayer(playerid);

                    new gtMsg[64];
                    format(gtMsg, sizeof(gtMsg), "~w~Selamat Datang di ~y~Burger Shot~n~~g~%s", gBurgerShots[i][bs_City]);
                    GameTextForPlayer(playerid, gtMsg, 3000, 3);
                    PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
                    return 1;
                }
            }
        }

        // ─── 3. Burger Shot: Keluar Dari Interior ID 10 Kembali ke Cabang Eksterior ───
        if (GetPlayerInterior(playerid) == BURGER_SHOT_INT_ID && IsPlayerInRangeOfPoint(playerid, 2.5, BURGER_SHOT_INT_X, BURGER_SHOT_INT_Y, BURGER_SHOT_INT_Z)) {
            new Float:outX = (gPlayerData[playerid][p_LastExtX] != 0.0) ? gPlayerData[playerid][p_LastExtX] : 811.2437;
            new Float:outY = (gPlayerData[playerid][p_LastExtY] != 0.0) ? gPlayerData[playerid][p_LastExtY] : -1615.9070;
            new Float:outZ = (gPlayerData[playerid][p_LastExtZ] != 0.0) ? gPlayerData[playerid][p_LastExtZ] : 13.5469;
            new Float:outA = (gPlayerData[playerid][p_LastExtA] != 0.0) ? gPlayerData[playerid][p_LastExtA] : 270.0000;

            SetPlayerInterior(playerid, 0);
            SetPlayerVirtualWorld(playerid, gPlayerData[playerid][p_LastExtVW]);
            SetPlayerPos(playerid, outX, outY, outZ);
            SetPlayerFacingAngle(playerid, outA);
            SetCameraBehindPlayer(playerid);

            GameTextForPlayer(playerid, "~w~Keluar dari ~y~Burger Shot", 3000, 3);
            PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
            return 1;
        }

        // ─── 4. Burger Shot: Interaksi Kasir / Counter Pemesanan ───
        if (GetPlayerInterior(playerid) == BURGER_SHOT_INT_ID && IsPlayerInRangeOfPoint(playerid, 3.0, BURGER_SHOT_COUNTER_X, BURGER_SHOT_COUNTER_Y, BURGER_SHOT_COUNTER_Z)) {
            ShowBurgerShotMenu(playerid);
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
            return 1;
        }
    }
    return 1;
}

stock HandleBurgerShotDialog(playerid, dialogid, response, listitem, const inputtext[]) {
    if (dialogid == DLG_BURGER_SHOT) {
        if (!response) return 1;
        // listitem 0..5 memetakan ke Item ID 1..6 (Burger, Hotdog, Pizza, Air Mineral, Cola, Milkshake)
        new itemid = listitem + 1;
        if (itemid < 1 || itemid > 6) return 1;

        gPlayerData[playerid][p_SelectedBuyItem] = itemid;

        new itemName[32], itemPrice, priceFmt[32];
        GetItemNameByID(itemid, itemName, sizeof(itemName));
        itemPrice = GetItemPriceByID(itemid);
        FormatRupiah(itemPrice, priceFmt, sizeof(priceFmt));

        new dialogMsg[256];
        format(dialogMsg, sizeof(dialogMsg),
            "{FFFFFF}Anda memilih pesanan: {FFA500}%s{FFFFFF}\n" \
            "Harga Satuan: {2ECC71}%s\n\n" \
            "{FFFFFF}Masukkan jumlah yang ingin Anda beli {FFFF00}(1 - 20 unit){FFFFFF}:",
            itemName, priceFmt);

        ShowPlayerDialog(playerid, DLG_BURGER_SHOT_QTY, DIALOG_STYLE_INPUT,
            "{FFA500}Burger Shot - Jumlah Pesanan", dialogMsg, "Beli", "Kembali");
        return 1;
    }

    if (dialogid == DLG_BURGER_SHOT_QTY) {
        if (!response) {
            return ShowBurgerShotMenu(playerid);
        }

        new qty = strval(inputtext);
        if (qty <= 0) qty = 1;
        if (qty > 20) qty = 20;

        new itId = gPlayerData[playerid][p_SelectedBuyItem];
        if (itId < 1 || itId > 6) return 1;

        new itemName[32], unitPrice;
        GetItemNameByID(itId, itemName, sizeof(itemName));
        unitPrice = GetItemPriceByID(itId);
        new totalCost = unitPrice * qty;

        // Cek Saldo Uang Tunai Pemain
        if (gPlayerData[playerid][p_Cash] < totalCost) {
            new costFmt[32], cashFmt[32], errMsg[144];
            FormatRupiah(totalCost, costFmt, sizeof(costFmt));
            FormatRupiah(gPlayerData[playerid][p_Cash], cashFmt, sizeof(cashFmt));

            format(errMsg, sizeof(errMsg), "  [Burger Shot] Uang tunai Anda tidak mencukupi! Total biaya: {FF3333}%s{FFFFFF} (Uang Anda: {2ECC71}%s{FFFFFF}).",
                costFmt, cashFmt);
            SendClientMessage(playerid, COL_RED, errMsg);
            PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
            return 1;
        }

        // Tambahkan ke Tas (Inventory)
        if (!Inventory_AddItem(playerid, itId, qty)) {
            SendClientMessage(playerid, COL_RED, "  [Burger Shot] Tas / inventory Anda sudah penuh (Maksimal 64 jenis barang)!");
            PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
            return 1;
        }

        // Potong Uang Tunai & Simpan ke Database
        gPlayerData[playerid][p_Cash] -= totalCost;
        new qCash[128];
        format(qCash, sizeof(qCash), "UPDATE `characters` SET `cash`=%d WHERE `id`=%d", gPlayerData[playerid][p_Cash], gPlayerData[playerid][p_CharID]);
        DB_FreeResultSet(DB_ExecuteQuery(gDB, qCash));

        UpdatePlayerMoneyHUD(playerid);
        PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);

        new charname[48], costFmt[32], rpMsg[160], notifMsg[160];
        GetCharName(playerid, charname);
        FormatRupiah(totalCost, costFmt, sizeof(costFmt));

        format(rpMsg, sizeof(rpMsg), "%s membayar %s ke kasir dan mengambil %d unit %s.",
            charname, costFmt, qty, itemName);
        DoProximityRaw(playerid, rpMsg, DIST_RP, COL_PURPLE);

        format(notifMsg, sizeof(notifMsg),
            "  [Burger Shot] Sukses membeli {FFA500}%d unit %s{FFFFFF} seharga {2ECC71}%s{FFFFFF}. Barang telah dimasukkan ke dalam tas {FFFF00}(/inv){FFFFFF}.",
            qty, itemName, costFmt);
        SendClientMessage(playerid, COL_GREEN, notifMsg);
        return 1;
    }
    return 0;
}

// Perintah Membuka Menu Beli Kasir Burger Shot & Supermarket
CMD:buy(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    if (GetPlayerInterior(playerid) == BURGER_SHOT_INT_ID && IsPlayerInRangeOfPoint(playerid, 3.5, BURGER_SHOT_COUNTER_X, BURGER_SHOT_COUNTER_Y, BURGER_SHOT_COUNTER_Z)) {
        ShowBurgerShotMenu(playerid);
        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
        return 1;
    }
    if (GetPlayerInterior(playerid) == TWENTYFOUR_SEVEN_INT_ID) {
        if (IsPlayerInRangeOfPoint(playerid, 3.5, TWENTYFOUR_SEVEN_CASH1_X, TWENTYFOUR_SEVEN_CASH1_Y, TWENTYFOUR_SEVEN_CASH1_Z) ||
            IsPlayerInRangeOfPoint(playerid, 3.5, TWENTYFOUR_SEVEN_CASH2_X, TWENTYFOUR_SEVEN_CASH2_Y, TWENTYFOUR_SEVEN_CASH2_Z)) {
            ShowTwentyFourSevenMenu(playerid);
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
            return 1;
        }
    }
    SendClientMessage(playerid, COL_RED, "  [Error] Anda harus berada di depan kasir restoran / supermarket untuk berbelanja!");
    return 1;
}
