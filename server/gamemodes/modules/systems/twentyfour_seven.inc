#if defined _MODULE_TWENTYFOUR_SEVEN_INC
    #endinput
#endif
#define _MODULE_TWENTYFOUR_SEVEN_INC

// ============================================================
//  SantaraBaru Roleplay - Supermarket System
//  5 Lokasi Pilihan: Willowfield, Juniper Hill, Whetstone, Fort Carson, The Strip
//  Interior ID 17 dengan Virtual World Terpisah
// ============================================================

enum E_247_LOC {
    tfs_Name[32],
    tfs_City[24],
    Float:tfs_X,
    Float:tfs_Y,
    Float:tfs_Z,
    Float:tfs_A
};

// 5 Lokasi Resmi Supermarket San Andreas
new const gTwentyFourSeven[][E_247_LOC] = {
    {"Supermarket Willowfield",   "Los Santos",     1832.9170, -1843.5580, 13.5469, 180.0},
    {"Supermarket Juniper Hill",  "San Fierro",    -2442.5000,   754.2000, 35.1719, 180.0},
    {"Supermarket Whetstone",     "Whetstone",     -1561.3480, -2733.4880, 48.7435,   0.0},
    {"Supermarket Fort Carson",   "Bone County",    -181.3323,  1034.3410, 19.7422, 180.0},
    {"Supermarket The Strip",     "Las Venturas",   2546.2610,  1971.9530, 10.8203, 180.0}
};
#define TWENTYFOUR_SEVEN_COUNT (sizeof(gTwentyFourSeven))

// 4 Item yang Dijual di Supermarket
static const g247Items[] = {
    ITEM_PICKAXE,       // 1. Beliung Tambang (Rp 75.000)
    ITEM_TOOLBOX,       // 2. Kotak Perkakas (Rp 120.000)
    ITEM_MINERAL_WATER, // 3. Air Mineral (Rp 5.000)
    ITEM_COLA           // 4. Cola (Rp 10.000)
};
#define TWENTYFOUR_SEVEN_ITEMS_COUNT (sizeof(g247Items))

stock InitTwentyFourSeven() {
    // 1. Pintu Masuk Eksterior di 5 Cabang Supermarket
    for (new i = 0; i < TWENTYFOUR_SEVEN_COUNT; i++) {
        CreatePickup(1239, 1, gTwentyFourSeven[i][tfs_X], gTwentyFourSeven[i][tfs_Y], gTwentyFourSeven[i][tfs_Z], 0);

        new labelText[160];
        format(labelText, sizeof(labelText),
            "{2ECC71}[ SUPERMARKET ]\n{FFFFFF}%s (%s)\n{FFFF00}Tekan [ F / ENTER ] untuk masuk",
            gTwentyFourSeven[i][tfs_Name], gTwentyFourSeven[i][tfs_City]);

        Create3DTextLabel(labelText, 0xFFFFFFFF,
            gTwentyFourSeven[i][tfs_X], gTwentyFourSeven[i][tfs_Y], gTwentyFourSeven[i][tfs_Z] + 0.5,
            18.0, 0, false);
    }

    // 2. Pintu Keluar Interior Supermarket (Interior ID 17, VW -1 agar berlaku untuk semua cabang)
    CreatePickup(1318, 1, TWENTYFOUR_SEVEN_INT_X, TWENTYFOUR_SEVEN_INT_Y, TWENTYFOUR_SEVEN_INT_Z, -1);
    Create3DTextLabel(
        "{2ECC71}[ PINTU KELUAR ]\n{FFFFFF}Tekan {FFFF00}[ F / ENTER ]{FFFFFF} untuk keluar ke kota",
        0xFFFFFFFF,
        TWENTYFOUR_SEVEN_INT_X, TWENTYFOUR_SEVEN_INT_Y, TWENTYFOUR_SEVEN_INT_Z + 0.5,
        12.0, -1, false
    );

    // 3. Kasir 1 & Kasir 2 Supermarket (Interior ID 17, VW -1)
    CreatePickup(1239, 1, TWENTYFOUR_SEVEN_CASH1_X, TWENTYFOUR_SEVEN_CASH1_Y, TWENTYFOUR_SEVEN_CASH1_Z, -1);
    Create3DTextLabel(
        "{2ECC71}[ KASIR SUPERMARKET 1 ]\n{FFFFFF}Tekan {FFFF00}[ F / ENTER ]{FFFFFF} atau ketik {FFFF00}/buy{FFFFFF}\n{AAAAAA}Untuk membeli perkakas & kebutuhan",
        0xFFFFFFFF,
        TWENTYFOUR_SEVEN_CASH1_X, TWENTYFOUR_SEVEN_CASH1_Y, TWENTYFOUR_SEVEN_CASH1_Z + 0.5,
        10.0, -1, false
    );

    CreatePickup(1239, 1, TWENTYFOUR_SEVEN_CASH2_X, TWENTYFOUR_SEVEN_CASH2_Y, TWENTYFOUR_SEVEN_CASH2_Z, -1);
    Create3DTextLabel(
        "{2ECC71}[ KASIR SUPERMARKET 2 ]\n{FFFFFF}Tekan {FFFF00}[ F / ENTER ]{FFFFFF} atau ketik {FFFF00}/buy{FFFFFF}\n{AAAAAA}Untuk membeli perkakas & kebutuhan",
        0xFFFFFFFF,
        TWENTYFOUR_SEVEN_CASH2_X, TWENTYFOUR_SEVEN_CASH2_Y, TWENTYFOUR_SEVEN_CASH2_Z + 0.5,
        10.0, -1, false
    );
}

stock ShowTwentyFourSevenMenu(playerid) {
    if (!CheckSpawned(playerid)) return 0;

    new menuStr[512];
    format(menuStr, sizeof(menuStr), "Nama Barang / Alat\tKategori\tHarga Satuan\n");

    for (new i = 0; i < TWENTYFOUR_SEVEN_ITEMS_COUNT; i++) {
        new itId = g247Items[i];
        new itName[32], itPrice, priceFmt[32];
        GetItemNameByID(itId, itName, sizeof(itName));
        itPrice = GetItemPriceByID(itId);
        FormatRupiah(itPrice, priceFmt, sizeof(priceFmt));

        new itCategory[24];
        if (itId == ITEM_PICKAXE || itId == ITEM_TOOLBOX) format(itCategory, sizeof(itCategory), "{FFA500}Peralatan");
        else format(itCategory, sizeof(itCategory), "{33CCFF}Minuman");

        format(menuStr, sizeof(menuStr), "%s{FFFFFF}%s\t%s\t{2ECC71}%s\n",
            menuStr, itName, itCategory, priceFmt);
    }

    ShowPlayerDialog(playerid, DLG_247_STORE, DIALOG_STYLE_TABLIST_HEADERS,
        "{2ECC71}Kasir Supermarket - Pilih Barang", menuStr, "Beli", "Tutup");
    return 1;
}

stock HandleTwentyFourSevenDialog(playerid, dialogid, response, listitem, const inputtext[]) {
    if (dialogid == DLG_247_STORE) {
        if (!response) return 1;
        if (listitem < 0 || listitem >= TWENTYFOUR_SEVEN_ITEMS_COUNT) return 1;

        new itId = g247Items[listitem];
        gPlayerData[playerid][p_SelectedBuyItem] = itId;

        new itName[32], itPrice, priceFmt[32];
        GetItemNameByID(itId, itName, sizeof(itName));
        itPrice = GetItemPriceByID(itId);
        FormatRupiah(itPrice, priceFmt, sizeof(priceFmt));

        new dialogMsg[256];
        format(dialogMsg, sizeof(dialogMsg),
            "{FFFFFF}Anda memilih barang: {2ECC71}%s{FFFFFF}\n" \
            "Harga Satuan: {00EEFF}%s\n\n" \
            "{FFFFFF}Masukkan jumlah yang ingin Anda beli {FFFF00}(1 - 10 unit){FFFFFF}:",
            itName, priceFmt);

        ShowPlayerDialog(playerid, DLG_247_STORE_QTY, DIALOG_STYLE_INPUT,
            "{2ECC71}Supermarket - Jumlah Pembelian", dialogMsg, "Bayar", "Kembali");
        return 1;
    }

    if (dialogid == DLG_247_STORE_QTY) {
        if (!response) {
            return ShowTwentyFourSevenMenu(playerid);
        }

        new qty = strval(inputtext);
        if (qty <= 0) qty = 1;
        if (qty > 10) qty = 10;

        new itId = gPlayerData[playerid][p_SelectedBuyItem];
        new itPrice = GetItemPriceByID(itId);
        new totalCost = itPrice * qty;

        if (gPlayerData[playerid][p_Cash] < totalCost) {
            new costFmt[32];
            FormatRupiah(totalCost, costFmt, sizeof(costFmt));
            new errMsg[144];
            format(errMsg, sizeof(errMsg), "  [Supermarket] Uang Anda tidak cukup! Total biaya: {2ECC71}%s{FFFFFF}.", costFmt);
            SendClientMessage(playerid, COL_RED, errMsg);
            PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
            return 1;
        }

        // Potong Uang & Tambah Item ke Inventory
        gPlayerData[playerid][p_Cash] -= totalCost;
        new qCash[128];
        format(qCash, sizeof(qCash), "UPDATE `characters` SET `cash`=%d WHERE `id`=%d", gPlayerData[playerid][p_Cash], gPlayerData[playerid][p_CharID]);
        DB_FreeResultSet(DB_ExecuteQuery(gDB, qCash));
        UpdatePlayerMoneyHUD(playerid);

        Inventory_AddItem(playerid, itId, qty);

        new itName[32], totalFmt[32];
        GetItemNameByID(itId, itName, sizeof(itName));
        FormatRupiah(totalCost, totalFmt, sizeof(totalFmt));

        new notifMsg[144];
        format(notifMsg, sizeof(notifMsg),
            "  [Supermarket] Berhasil membeli {00EEFF}%d unit %s{FFFFFF} seharga {2ECC71}%s{FFFFFF} (dimasukkan ke tas).",
            qty, itName, totalFmt);
        SendClientMessage(playerid, COL_GREEN, notifMsg);
        PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);

        new charname[48], rpMsg[144];
        GetCharName(playerid, charname);
        format(rpMsg, sizeof(rpMsg), "%s membayar %s di kasir supermarket dan mengantongi %d unit %s.", charname, totalFmt, qty, itName);
        DoProximityRaw(playerid, rpMsg, DIST_RP, COL_PURPLE);
        return 1;
    }
    return 0;
}

stock HandleTwentyFourSevenKeys(playerid, KEY:newkeys) {
    if (newkeys & KEY_SECONDARY_ATTACK) {
        // 1. Masuk ke salah satu 5 Cabang Supermarket dari Eksterior
        if (GetPlayerInterior(playerid) == 0) {
            for (new i = 0; i < TWENTYFOUR_SEVEN_COUNT; i++) {
                if (IsPlayerInRangeOfPoint(playerid, 2.5, gTwentyFourSeven[i][tfs_X], gTwentyFourSeven[i][tfs_Y], gTwentyFourSeven[i][tfs_Z])) {
                    gPlayerData[playerid][p_LastExtX]  = gTwentyFourSeven[i][tfs_X];
                    gPlayerData[playerid][p_LastExtY]  = gTwentyFourSeven[i][tfs_Y];
                    gPlayerData[playerid][p_LastExtZ]  = gTwentyFourSeven[i][tfs_Z];
                    gPlayerData[playerid][p_LastExtA]  = gTwentyFourSeven[i][tfs_A];
                    gPlayerData[playerid][p_LastExtVW] = GetPlayerVirtualWorld(playerid);

                    // Setiap toko punya Virtual World unik (201 - 205)
                    SetPlayerInterior(playerid, TWENTYFOUR_SEVEN_INT_ID);
                    SetPlayerVirtualWorld(playerid, TWENTYFOUR_SEVEN_VW_BASE + i);
                    SetPlayerPos(playerid, TWENTYFOUR_SEVEN_INT_X, TWENTYFOUR_SEVEN_INT_Y, TWENTYFOUR_SEVEN_INT_Z);
                    SetPlayerFacingAngle(playerid, TWENTYFOUR_SEVEN_INT_A);
                    SetCameraBehindPlayer(playerid);

                    new gtMsg[64];
                    format(gtMsg, sizeof(gtMsg), "~w~Selamat Datang di ~g~Supermarket~n~~y~%s", gTwentyFourSeven[i][tfs_City]);
                    GameTextForPlayer(playerid, gtMsg, 3000, 3);
                    PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
                    return 1;
                }
            }
        }

        // 2. Keluar dari Interior Supermarket (Interior ID 17)
        if (GetPlayerInterior(playerid) == TWENTYFOUR_SEVEN_INT_ID && IsPlayerInRangeOfPoint(playerid, 2.5, TWENTYFOUR_SEVEN_INT_X, TWENTYFOUR_SEVEN_INT_Y, TWENTYFOUR_SEVEN_INT_Z)) {
            new Float:outX = (gPlayerData[playerid][p_LastExtX] != 0.0) ? gPlayerData[playerid][p_LastExtX] : 1832.9170;
            new Float:outY = (gPlayerData[playerid][p_LastExtY] != 0.0) ? gPlayerData[playerid][p_LastExtY] : -1843.5580;
            new Float:outZ = (gPlayerData[playerid][p_LastExtZ] != 0.0) ? gPlayerData[playerid][p_LastExtZ] : 13.5469;
            new Float:outA = (gPlayerData[playerid][p_LastExtA] != 0.0) ? gPlayerData[playerid][p_LastExtA] : 180.0000;

            SetPlayerInterior(playerid, 0);
            SetPlayerVirtualWorld(playerid, gPlayerData[playerid][p_LastExtVW]);
            SetPlayerPos(playerid, outX, outY, outZ);
            SetPlayerFacingAngle(playerid, outA);
            SetCameraBehindPlayer(playerid);

            GameTextForPlayer(playerid, "~w~Keluar dari ~g~Supermarket", 3000, 3);
            PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
            return 1;
        }

        // 3. Interaksi Kasir 1 atau Kasir 2 Supermarket
        if (GetPlayerInterior(playerid) == TWENTYFOUR_SEVEN_INT_ID) {
            if (IsPlayerInRangeOfPoint(playerid, 2.5, TWENTYFOUR_SEVEN_CASH1_X, TWENTYFOUR_SEVEN_CASH1_Y, TWENTYFOUR_SEVEN_CASH1_Z) ||
                IsPlayerInRangeOfPoint(playerid, 2.5, TWENTYFOUR_SEVEN_CASH2_X, TWENTYFOUR_SEVEN_CASH2_Y, TWENTYFOUR_SEVEN_CASH2_Z)) {
                ShowTwentyFourSevenMenu(playerid);
                PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
                return 1;
            }
        }
    }
    return 0;
}
