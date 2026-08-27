#if defined _MODULE_INVENTORY_INC
    #endinput
#endif
#define _MODULE_INVENTORY_INC

// ============================================================
//  SantaraBaru Roleplay - Player Inventory & Item System
//  Pure ASCII, 36 Legal Items, Needs (Hunger, Thirst), Medical HP, /give, /pay
// ============================================================

#define MAX_REGISTERED_ITEMS    200

enum E_ITEM_INFO {
    item_ID,
    item_Name[32],
    item_Category[24],
    Float:item_HungerVal,
    Float:item_ThirstVal,
    Float:item_HealthVal,
    bool:item_IsFullHeal,
    item_AnimLib[32],
    item_AnimName[32],
    item_Price
};

new gItemRegistry[MAX_REGISTERED_ITEMS][E_ITEM_INFO];
new gTotalRegisteredItems = 0;

stock GetItemRegistryIndex(itemid) {
    for (new i = 0; i < gTotalRegisteredItems; i++) {
        if (gItemRegistry[i][item_ID] == itemid) {
            return i;
        }
    }
    return -1;
}

stock GetItemNameByID(itemid, name[], maxlen) {
    new idx = GetItemRegistryIndex(itemid);
    if (idx != -1) {
        format(name, maxlen, "%s", gItemRegistry[idx][item_Name]);
        return 1;
    }
    format(name, maxlen, "Barang Tidak Dikenal");
    return 0;
}

stock GetItemIDByName(const name[]) {
    for (new i = 0; i < gTotalRegisteredItems; i++) {
        if (strfind(gItemRegistry[i][item_Name], name, true) != -1) {
            return gItemRegistry[i][item_ID];
        }
    }
    return 0;
}

stock GetItemPriceByID(itemid) {
    new idx = GetItemRegistryIndex(itemid);
    if (idx != -1) {
        return gItemRegistry[idx][item_Price];
    }
    return 0;
}

stock Inventory_LoadItemsFromDB() {
    gTotalRegisteredItems = 0;
    new DBResult:res = DB_ExecuteQuery(gDB_Master, "SELECT `id`, `name`, `category`, `hunger`, `thirst`, `health`, `is_full_heal`, `anim_lib`, `anim_name`, `price` FROM `items` ORDER BY `id` ASC");
    if (!res || DB_GetRowCount(res) == 0) {
        if (res) DB_FreeResultSet(res);
        return 0;
    }

    new rows = DB_GetRowCount(res);
    for (new i = 0; i < rows && i < MAX_REGISTERED_ITEMS; i++) {
        gItemRegistry[i][item_ID]          = DB_GetFieldIntByName(res, "id");
        DB_GetFieldStringByName(res, "name", gItemRegistry[i][item_Name], 32);
        DB_GetFieldStringByName(res, "category", gItemRegistry[i][item_Category], 24);
        gItemRegistry[i][item_HungerVal]   = DB_GetFieldFloatByName(res, "hunger");
        gItemRegistry[i][item_ThirstVal]   = DB_GetFieldFloatByName(res, "thirst");
        gItemRegistry[i][item_HealthVal]   = DB_GetFieldFloatByName(res, "health");
        gItemRegistry[i][item_IsFullHeal]  = (DB_GetFieldIntByName(res, "is_full_heal") == 1);
        DB_GetFieldStringByName(res, "anim_lib", gItemRegistry[i][item_AnimLib], 32);
        DB_GetFieldStringByName(res, "anim_name", gItemRegistry[i][item_AnimName], 32);
        gItemRegistry[i][item_Price]       = DB_GetFieldIntByName(res, "price");
        gTotalRegisteredItems++;
        DB_SelectNextRow(res);
    }
    DB_FreeResultSet(res);
    printf("[Inventory] Sukses memuat %d barang dari database ke memori RAM.", gTotalRegisteredItems);
    return gTotalRegisteredItems;
}


// ------------------------------------------------------------
//  Database & In-Memory Inventory Helpers
// ------------------------------------------------------------

stock Inventory_GetItemCount(playerid, itemid) {
    if (!gPlayerData[playerid][p_LoggedIn] || gPlayerData[playerid][p_CharID] <= 0) return 0;
    for (new i = 0; i < gPlayerData[playerid][p_InvItemCount]; i++) {
        if (gPlayerData[playerid][p_InvSlotItemID][i] == itemid) {
            return gPlayerData[playerid][p_InvSlotAmount][i];
        }
    }
    return 0;
}

stock bool:Inventory_HasItem(playerid, itemid) {
    return (Inventory_GetItemCount(playerid, itemid) > 0);
}

stock Inventory_LoadPlayerItems(playerid) {
    gPlayerData[playerid][p_InvItemCount] = 0;
    for (new i = 0; i < 64; i++) {
        gPlayerData[playerid][p_InvSlotItemID][i] = 0;
        gPlayerData[playerid][p_InvSlotAmount][i] = 0;
    }

    if (!gPlayerData[playerid][p_LoggedIn] || gPlayerData[playerid][p_CharID] <= 0) return 0;

    new query[256];
    format(query, sizeof(query), "SELECT `item_id`, `amount` FROM `inventory` WHERE `char_id`=%d AND `amount` > 0 ORDER BY `item_id` ASC", gPlayerData[playerid][p_CharID]);
    new DBResult:res = DB_ExecuteQuery(gDB, query);
    if (res) {
        new count = DB_GetRowCount(res);
        for (new i = 0; i < count && i < 64; i++) {
            gPlayerData[playerid][p_InvSlotItemID][i] = DB_GetFieldIntByName(res, "item_id");
            gPlayerData[playerid][p_InvSlotAmount][i] = DB_GetFieldIntByName(res, "amount");
            gPlayerData[playerid][p_InvItemCount]++;
            DB_SelectNextRow(res);
        }
        DB_FreeResultSet(res);
    }
    return gPlayerData[playerid][p_InvItemCount];
}

stock Inventory_AddItem(playerid, itemid, amount) {
    if (!gPlayerData[playerid][p_LoggedIn] || gPlayerData[playerid][p_CharID] <= 0) return 0;
    if (amount <= 0 || GetItemRegistryIndex(itemid) == -1) return 0;

    new currentAmt = Inventory_GetItemCount(playerid, itemid);
    new query[256];

    if (currentAmt > 0) {
        new newAmt = currentAmt + amount;
        format(query, sizeof(query), "UPDATE `inventory` SET `amount`=%d WHERE `char_id`=%d AND `item_id`=%d",
            newAmt, gPlayerData[playerid][p_CharID], itemid);
        DB_FreeResultSet(DB_ExecuteQuery(gDB, query));
    } else {
        format(query, sizeof(query), "INSERT INTO `inventory` (`char_id`, `item_id`, `amount`) VALUES (%d, %d, %d)",
            gPlayerData[playerid][p_CharID], itemid, amount);
        DB_FreeResultSet(DB_ExecuteQuery(gDB, query));
    }

    Inventory_LoadPlayerItems(playerid);
    return 1;
}

stock Inventory_RemoveItem(playerid, itemid, amount) {
    if (!gPlayerData[playerid][p_LoggedIn] || gPlayerData[playerid][p_CharID] <= 0) return 0;
    if (amount <= 0 || GetItemRegistryIndex(itemid) == -1) return 0;

    new currentAmt = Inventory_GetItemCount(playerid, itemid);
    if (currentAmt < amount) return 0;

    new query[256];
    new newAmt = currentAmt - amount;

    if (newAmt <= 0) {
        format(query, sizeof(query), "DELETE FROM `inventory` WHERE `char_id`=%d AND `item_id`=%d",
            gPlayerData[playerid][p_CharID], itemid);
        DB_FreeResultSet(DB_ExecuteQuery(gDB, query));
    } else {
        format(query, sizeof(query), "UPDATE `inventory` SET `amount`=%d WHERE `char_id`=%d AND `item_id`=%d",
            newAmt, gPlayerData[playerid][p_CharID], itemid);
        DB_FreeResultSet(DB_ExecuteQuery(gDB, query));
    }

    Inventory_LoadPlayerItems(playerid);
    return 1;
}

// ------------------------------------------------------------
//  Penggunaan Barang (Konsumsi Makanan, Minuman, Medis, KTP)
// ------------------------------------------------------------

stock UseInventoryItem(playerid, itemid) {
    if (!CheckSpawned(playerid)) return 0;
    if (!Inventory_HasItem(playerid, itemid)) {
        SendClientMessage(playerid, COL_RED, "  [Inventory] Anda tidak memiliki barang tersebut di dalam tas!");
        return 0;
    }

    new itemIdx = GetItemRegistryIndex(itemid);
    if (itemIdx == -1) return 0;

    new charname[48], rpMsg[160];
    GetCharName(playerid, charname);

    // 1. MAKANAN (Murni Mengisi Lapar / Hunger)
    if (itemid >= ITEM_BURGER && itemid <= ITEM_PIZZA) {
        GivePlayerHunger(playerid, gItemRegistry[itemIdx][item_HungerVal]);
        if (gItemRegistry[itemIdx][item_ThirstVal] > 0.0) {
            GivePlayerThirst(playerid, gItemRegistry[itemIdx][item_ThirstVal]);
        }
        ApplyAnimation(playerid, "FOOD", "eat_burger", 4.1, false, false, false, false, 0, 1);
        PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);

        format(rpMsg, sizeof(rpMsg), "%s memakan %s dan merasa lebih kenyang.", charname, gItemRegistry[itemIdx][item_Name]);
        DoProximityRaw(playerid, rpMsg, DIST_RP, COL_PURPLE);

        new msg[128];
        format(msg, sizeof(msg), "  [Makan] Anda memakan {00EEFF}%s{FFFFFF}. Lapar: {2ECC71}+%.0f%%{FFFFFF}.",
            gItemRegistry[itemIdx][item_Name], gItemRegistry[itemIdx][item_HungerVal]);
        SendClientMessage(playerid, COL_GREEN, msg);

        Inventory_RemoveItem(playerid, itemid, 1);
        return 1;
    }

    // 2. MINUMAN (Murni Mengisi Haus / Thirst)
    if (itemid >= ITEM_MINERAL_WATER && itemid <= ITEM_MILKSHAKE) {
        GivePlayerThirst(playerid, gItemRegistry[itemIdx][item_ThirstVal]);
        if (gItemRegistry[itemIdx][item_HungerVal] > 0.0) {
            GivePlayerHunger(playerid, gItemRegistry[itemIdx][item_HungerVal]);
        }
        ApplyAnimation(playerid, "DRINK_cw", "drink_sprank", 4.1, false, false, false, false, 0, 1);
        PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);

        format(rpMsg, sizeof(rpMsg), "%s meminum %s hingga dahaganya reda.", charname, gItemRegistry[itemIdx][item_Name]);
        DoProximityRaw(playerid, rpMsg, DIST_RP, COL_PURPLE);

        new msg[128];
        format(msg, sizeof(msg), "  [Minum] Anda meminum {00EEFF}%s{FFFFFF}. Haus: {33CCFF}+%.0f%%{FFFFFF}.",
            gItemRegistry[itemIdx][item_Name], gItemRegistry[itemIdx][item_ThirstVal]);
        SendClientMessage(playerid, COL_GREEN, msg);

        Inventory_RemoveItem(playerid, itemid, 1);
        return 1;
    }

    // 3. MEDIS (Murni Menambah Darah / HP)
    if (itemid == ITEM_BANDAGE || itemid == ITEM_MEDKIT || itemid == ITEM_FIRST_AID) {
        new Float:curHp;
        GetPlayerHealth(playerid, curHp);

        if (curHp >= 100.0) {
            SendClientMessage(playerid, COL_YELLOW, "  [Medis] Kondisi darah (HP) Anda sudah maksimal (100%)!");
            return 1;
        }

        if (gItemRegistry[itemIdx][item_IsFullHeal]) {
            SetPlayerHealth(playerid, 100.0);
            SendClientMessage(playerid, COL_GREEN, "  [Medis] Anda menggunakan {00EEFF}First Aid Kit{00CC66}. Darah (HP) Anda pulih SEPENUHNYA (100%)!");
        } else {
            new Float:newHp = curHp + gItemRegistry[itemIdx][item_HealthVal];
            if (newHp > 100.0) newHp = 100.0;
            SetPlayerHealth(playerid, newHp);

            new msg[128];
            format(msg, sizeof(msg), "  [Medis] Anda menggunakan {00EEFF}%s{00CC66}. Darah (HP): {2ECC71}+%.0f HP{00CC66} (Total: %.0f HP).",
                gItemRegistry[itemIdx][item_Name], gItemRegistry[itemIdx][item_HealthVal], newHp);
            SendClientMessage(playerid, COL_GREEN, msg);
        }

        UpdatePlayerMoneyHUD(playerid);
        PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);

        format(rpMsg, sizeof(rpMsg), "%s melakukan pertolongan medis pertama menggunakan %s.", charname, gItemRegistry[itemIdx][item_Name]);
        DoProximityRaw(playerid, rpMsg, DIST_RP, COL_PURPLE);

        Inventory_RemoveItem(playerid, itemid, 1);
        return 1;
    }

    // 4. KTP (Buka Kartu Identitas Resmi)
    if (itemid == ITEM_KTP) {
        if (gPlayerData[playerid][p_InInventoryUI]) {
            HideInventoryUI(playerid);
        }
        ShowPlayerKTPCard(playerid, playerid);
        SendClientMessage(playerid, COL_GREEN, "  [KTP] Membuka fisik Kartu Tanda Penduduk (e-KTP) Anda.");
        return 1;
    }

    // 5. SIM A (Buka Kartu SIM A)
    if (itemid == ITEM_SIM_A) {
        if (gPlayerData[playerid][p_InInventoryUI]) {
            HideInventoryUI(playerid);
        }
        ShowPlayerSIMCard(playerid, playerid, 0);
        SendClientMessage(playerid, COL_GREEN, "  [SIM] Membuka fisik Surat Izin Mengemudi (SIM A) Anda.");
        return 1;
    }

    // 6. SIM B (Buka Kartu SIM B)
    if (itemid == ITEM_SIM_B) {
        if (gPlayerData[playerid][p_InInventoryUI]) {
            HideInventoryUI(playerid);
        }
        ShowPlayerSIMCard(playerid, playerid, 1);
        SendClientMessage(playerid, COL_GREEN, "  [SIM] Membuka fisik Surat Izin Mengemudi (SIM B) Anda.");
        return 1;
    }

    // 7. SIM C (Buka Kartu SIM C)
    if (itemid == ITEM_SIM_C) {
        if (gPlayerData[playerid][p_InInventoryUI]) {
            HideInventoryUI(playerid);
        }
        ShowPlayerSIMCard(playerid, playerid, 2);
        SendClientMessage(playerid, COL_GREEN, "  [SIM] Membuka fisik Surat Izin Mengemudi (SIM C) Anda.");
        return 1;
    }

    // 8. PONSEL
    if (itemid == ITEM_PHONE) {
        SendClientMessage(playerid, COL_CYAN, "  [Ponsel] Layar smartphone menyala. (Sistem jaringan telepon aktif).");
        return 1;
    }

    return 1;
}

// ------------------------------------------------------------
//  Dialog Inventory UI
// ------------------------------------------------------------

stock OpenInventoryMenu(playerid) {
    if (!CheckSpawned(playerid)) return 0;
    Inventory_LoadPlayerItems(playerid);

    new count = gPlayerData[playerid][p_InvItemCount];
    if (count == 0) {
        ShowPlayerDialog(playerid, DLG_INV_MAIN, DIALOG_STYLE_MSGBOX,
            "{E69958}SantaraRP - Tas Bawaan (Inventory)",
            "{FFFFFF}Kantong dan tas Anda saat ini {AAAAAA}KOSONG{FFFFFF}.\n\nAnda dapat membeli makanan, minuman, dan obat di toko terdekat.",
            "Tutup", "");
        return 1;
    }

    new dialogStr[2048];
    format(dialogStr, sizeof(dialogStr), "Nama Barang\tKategori\tJumlah\n");

    for (new i = 0; i < count; i++) {
        new itId = gPlayerData[playerid][p_InvSlotItemID][i];
        new itAmt = gPlayerData[playerid][p_InvSlotAmount][i];
        new itIdx = GetItemRegistryIndex(itId);

        if (itIdx != -1) {
            new line[128];
            format(line, sizeof(line), "{FFFFFF}%s\t{A0AEC0}%s\t{00EEFF}%dx\n",
                gItemRegistry[itIdx][item_Name], gItemRegistry[itIdx][item_Category], itAmt);
            strcat(dialogStr, line);
        }
    }

    ShowPlayerDialog(playerid, DLG_INV_MAIN, DIALOG_STYLE_TABLIST_HEADERS,
        "{E69958}SantaraRP - Tas Bawaan (Inventory)", dialogStr, "Pilih", "Tutup");
    return 1;
}

stock HandleInventoryDialog(playerid, dialogid, response, listitem, inputtext[]) {
    // 1. Menu Utama List Barang (/inv)
    if (dialogid == DLG_INV_MAIN) {
        if (!response) return 1;

        if (listitem < 0 || listitem >= gPlayerData[playerid][p_InvItemCount]) return 1;

        gPlayerData[playerid][p_SelectedInvSlot] = listitem;
        new itId = gPlayerData[playerid][p_InvSlotItemID][listitem];
        gPlayerData[playerid][p_SelectedInvItemID] = itId;

        new itName[32];
        GetItemNameByID(itId, itName, sizeof(itName));

        new title[64], actionStr[256];
        format(title, sizeof(title), "{E69958}Aksi Barang: %s", itName);
        format(actionStr, sizeof(actionStr),
            "1. Gunakan / Pakai Barang\n2. Berikan ke Pemain Terdekat\n3. Buang dari Tas");

        ShowPlayerDialog(playerid, DLG_INV_ACTION, DIALOG_STYLE_LIST, title, actionStr, "Pilih", "Kembali");
        return 1;
    }

    // 2. Menu Aksi Barang (Gunakan, Berikan, Buang)
    if (dialogid == DLG_INV_ACTION) {
        if (!response) {
            OpenInventoryMenu(playerid);
            return 1;
        }

        new itId = gPlayerData[playerid][p_SelectedInvItemID];
        if (itId <= 0 || !Inventory_HasItem(playerid, itId)) {
            SendClientMessage(playerid, COL_RED, "  [Inventory] Barang tidak valid atau sudah habis!");
            OpenInventoryMenu(playerid);
            return 1;
        }

        switch (listitem) {
            case 0: { // Gunakan / Pakai
                UseInventoryItem(playerid, itId);
            }
            case 1: { // Berikan ke Pemain
                if (itId == ITEM_KTP || itId == ITEM_SIM_A || itId == ITEM_SIM_B || itId == ITEM_SIM_C) {
                    SendClientMessage(playerid, COL_RED, "  [Inventory] Dokumen resmi (e-KTP / SIM) tidak dapat diberikan ke orang lain!");
                    OpenInventoryMenu(playerid);
                    return 1;
                }

                // Cari pemain dalam radius 3.5 meter
                new playersNear[10], nearCount = 0;
                for (new i = 0; i < MAX_PLAYERS; i++) {
                    if (i != playerid && IsPlayerConnected(i) && gPlayerData[i][p_LoggedIn] && gPlayerData[i][p_Spawned]) {
                        new Float:tx, Float:ty, Float:tz;
                        GetPlayerPos(i, tx, ty, tz);
                        if (IsPlayerInRangeOfPoint(playerid, 3.5, tx, ty, tz)) {
                            playersNear[nearCount] = i;
                            nearCount++;
                            if (nearCount >= 10) break;
                        }
                    }
                }

                if (nearCount == 0) {
                    SendClientMessage(playerid, COL_RED, "  [Inventory] Tidak ada pemain lain di dekat Anda (maks 3.5 meter)!");
                    OpenInventoryMenu(playerid);
                    return 1;
                }

                new pListStr[512];
                format(pListStr, sizeof(pListStr), "ID\tNama Karakter\tJarak\n");
                for (new p = 0; p < nearCount; p++) {
                    new targetId = playersNear[p];
                    new tName[48], line[128];
                    GetCharName(targetId, tName);
                    format(line, sizeof(line), "{00EEFF}%d\t{FFFFFF}%s\t{A0AEC0}Dekat\n", targetId, tName);
                    strcat(pListStr, line);
                }

                ShowPlayerDialog(playerid, DLG_INV_GIVE_PLAYER, DIALOG_STYLE_TABLIST_HEADERS,
                    "{E69958}Pilih Pemain Penerima", pListStr, "Pilih", "Batal");
            }
            case 2: { // Buang dari Tas
                if (itId == ITEM_KTP || itId == ITEM_SIM_A || itId == ITEM_SIM_B || itId == ITEM_SIM_C) {
                    SendClientMessage(playerid, COL_RED, "  [Inventory] Dokumen resmi (e-KTP / SIM) tidak dapat dibuang!");
                    OpenInventoryMenu(playerid);
                    return 1;
                }

                new itName[32];
                GetItemNameByID(itId, itName, sizeof(itName));
                new curAmt = Inventory_GetItemCount(playerid, itId);

                new dropPrompt[256];
                format(dropPrompt, sizeof(dropPrompt),
                    "{FFFFFF}Berapa banyak {00EEFF}%s{FFFFFF} yang ingin Anda buang?\n\n{A0AEC0}(Jumlah saat ini: %d unit)",
                    itName, curAmt);

                ShowPlayerDialog(playerid, DLG_INV_DROP_QTY, DIALOG_STYLE_INPUT,
                    "{E69958}Buang Barang dari Tas", dropPrompt, "Buang", "Batal");
            }
        }
        return 1;
    }

    // 3. Pilih Pemain Penerima
    if (dialogid == DLG_INV_GIVE_PLAYER) {
        if (!response) {
            OpenInventoryMenu(playerid);
            return 1;
        }

        // Ambil target dari list
        new nearIdx = 0, selectedTarget = INVALID_PLAYER_ID;
        for (new i = 0; i < MAX_PLAYERS; i++) {
            if (i != playerid && IsPlayerConnected(i) && gPlayerData[i][p_LoggedIn] && gPlayerData[i][p_Spawned]) {
                new Float:tx, Float:ty, Float:tz;
                GetPlayerPos(i, tx, ty, tz);
                if (IsPlayerInRangeOfPoint(playerid, 3.5, tx, ty, tz)) {
                    if (nearIdx == listitem) {
                        selectedTarget = i;
                        break;
                    }
                    nearIdx++;
                }
            }
        }

        if (selectedTarget == INVALID_PLAYER_ID || !IsPlayerConnected(selectedTarget)) {
            SendClientMessage(playerid, COL_RED, "  [Inventory] Pemain target sudah tidak berada di dekat Anda!");
            return 1;
        }

        gPlayerData[playerid][p_TargetGivePlayerID] = selectedTarget;
        new itId = gPlayerData[playerid][p_SelectedInvItemID];
        new itName[32], tName[48];
        GetItemNameByID(itId, itName, sizeof(itName));
        GetCharName(selectedTarget, tName);
        new curAmt = Inventory_GetItemCount(playerid, itId);

        new qtyPrompt[256];
        format(qtyPrompt, sizeof(qtyPrompt),
            "{FFFFFF}Masukkan jumlah {00EEFF}%s{FFFFFF} yang ingin Anda berikan kepada {FFFF00}%s{FFFFFF}:\n\n{A0AEC0}(Jumlah di tas Anda: %d unit)",
            itName, tName, curAmt);

        ShowPlayerDialog(playerid, DLG_INV_GIVE_QTY, DIALOG_STYLE_INPUT,
            "{E69958}Kuantitas Barang", qtyPrompt, "Kirim", "Batal");
        return 1;
    }

    // 4. Masukkan Jumlah Barang yang Diberikan
    if (dialogid == DLG_INV_GIVE_QTY) {
        if (!response) {
            OpenInventoryMenu(playerid);
            return 1;
        }

        new qty = strval(inputtext);
        new itId = gPlayerData[playerid][p_SelectedInvItemID];
        new targetId = gPlayerData[playerid][p_TargetGivePlayerID];
        new curAmt = Inventory_GetItemCount(playerid, itId);

        if (qty <= 0 || qty > curAmt) {
            SendClientMessage(playerid, COL_RED, "  [Error] Jumlah barang yang dimasukkan tidak valid atau melebihi stok!");
            OpenInventoryMenu(playerid);
            return 1;
        }

        if (targetId == INVALID_PLAYER_ID || !IsPlayerConnected(targetId)) {
            SendClientMessage(playerid, COL_RED, "  [Error] Pemain penerima sudah offline!");
            return 1;
        }

        new Float:tx, Float:ty, Float:tz;
        GetPlayerPos(targetId, tx, ty, tz);
        if (!IsPlayerInRangeOfPoint(playerid, 4.0, tx, ty, tz)) {
            SendClientMessage(playerid, COL_RED, "  [Error] Pemain penerima berada terlalu jauh dari Anda (maks 4m)!");
            return 1;
        }

        Inventory_RemoveItem(playerid, itId, qty);
        Inventory_AddItem(targetId, itId, qty);

        new itName[32], myName[48], targetName[48], rpMsg[160];
        GetItemNameByID(itId, itName, sizeof(itName));
        GetCharName(playerid, myName);
        GetCharName(targetId, targetName);

        format(rpMsg, sizeof(rpMsg), "%s menyerahkan %dx %s kepada %s.", myName, qty, itName, targetName);
        DoProximityRaw(playerid, rpMsg, DIST_RP, COL_PURPLE);

        new sendMsg[144];
        format(sendMsg, sizeof(sendMsg), "  [Inventory] Anda memberikan {00EEFF}%dx %s{FFFFFF} kepada {FFFF00}%s{FFFFFF}.", qty, itName, targetName);
        SendClientMessage(playerid, COL_GREEN, sendMsg);

        format(sendMsg, sizeof(sendMsg), "  [Inventory] Anda menerima {00EEFF}%dx %s{FFFFFF} dari {FFFF00}%s{FFFFFF}.", qty, itName, myName);
        SendClientMessage(targetId, COL_GREEN, sendMsg);

        PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
        PlayerPlaySound(targetId, 1058, 0.0, 0.0, 0.0);

        if (gPlayerData[playerid][p_InInventoryUI]) {
            UpdateInventoryUI(playerid);
        }
        return 1;
    }

    // 5. Masukkan Jumlah Barang yang Dibuang
    if (dialogid == DLG_INV_DROP_QTY) {
        if (!response) {
            if (gPlayerData[playerid][p_InInventoryUI]) UpdateInventoryUI(playerid);
            else OpenInventoryMenu(playerid);
            return 1;
        }

        new qty = strval(inputtext);
        new itId = gPlayerData[playerid][p_SelectedInvItemID];
        new curAmt = Inventory_GetItemCount(playerid, itId);

        if (qty <= 0 || qty > curAmt) {
            SendClientMessage(playerid, COL_RED, "  [Error] Jumlah barang yang dibuang tidak valid!");
            if (gPlayerData[playerid][p_InInventoryUI]) UpdateInventoryUI(playerid);
            else OpenInventoryMenu(playerid);
            return 1;
        }

        Inventory_RemoveItem(playerid, itId, qty);

        new itName[32], charname[48], rpMsg[160];
        GetItemNameByID(itId, itName, sizeof(itName));
        GetCharName(playerid, charname);

        format(rpMsg, sizeof(rpMsg), "%s membuang %dx %s ke tempat sampah.", charname, qty, itName);
        DoProximityRaw(playerid, rpMsg, DIST_RP, COL_PURPLE);

        new msg[128];
        format(msg, sizeof(msg), "  [Inventory] Anda membuang {00EEFF}%dx %s{FFFFFF} dari tas Anda.", qty, itName);
        SendClientMessage(playerid, COL_YELLOW, msg);
        PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);

        if (gPlayerData[playerid][p_InInventoryUI]) {
            UpdateInventoryUI(playerid);
        }
        return 1;
    }

    return 0;
}

// ------------------------------------------------------------
//  Commands (/inv, /give, /pay, /giveitem)
// ------------------------------------------------------------

CMD:inv(playerid, params[]) {
    #pragma unused params
    ShowInventoryUI(playerid);
    return 1;
}

CMD:inventory(playerid, params[]) {
    #pragma unused params
    ShowInventoryUI(playerid);
    return 1;
}

CMD:tas(playerid, params[]) {
    #pragma unused params
    ShowInventoryUI(playerid);
    return 1;
}

CMD:pay(playerid, params[]) {
    if (!CheckSpawned(playerid)) return 1;

    new targetid, amount;
    if (sscanf(params, "ui", targetid, amount)) {
        SendClientMessage(playerid, COL_ORANGE, "  [Petunjuk] Gunakan: /pay [Player ID / Nama] [Jumlah Uang]");
        return 1;
    }

    if (!IsPlayerConnected(targetid) || !gPlayerData[targetid][p_LoggedIn] || !gPlayerData[targetid][p_Spawned]) {
        SendClientMessage(playerid, COL_RED, "  [Error] Pemain target tidak ditemukan atau sedang offline.");
        return 1;
    }

    if (targetid == playerid) {
        SendClientMessage(playerid, COL_RED, "  [Error] Anda tidak dapat mengirim uang ke diri sendiri!");
        return 1;
    }

    if (amount <= 0) {
        SendClientMessage(playerid, COL_RED, "  [Error] Jumlah uang harus lebih dari Rp 0!");
        return 1;
    }

    if (gPlayerData[playerid][p_Cash] < amount) {
        new rup[32];
        FormatRupiah(amount, rup, sizeof(rup));
        new msg[128];
        format(msg, sizeof(msg), "  [Error] Uang tunai Anda tidak mencukupi! Anda butuh Rp %s.", rup);
        SendClientMessage(playerid, COL_RED, msg);
        return 1;
    }

    new Float:tx, Float:ty, Float:tz;
    GetPlayerPos(targetid, tx, ty, tz);
    if (!IsPlayerInRangeOfPoint(playerid, 4.0, tx, ty, tz)) {
        SendClientMessage(playerid, COL_RED, "  [Error] Pemain target berada terlalu jauh dari Anda (maks 4 meter)!");
        return 1;
    }

    GivePlayerMoneyEx(playerid, -amount);
    GivePlayerMoneyEx(targetid, amount);

    new myName[48], targetName[48], amountRup[32], rpMsg[160];
    GetCharName(playerid, myName);
    GetCharName(targetid, targetName);
    FormatRupiah(amount, amountRup, sizeof(amountRup));

    format(rpMsg, sizeof(rpMsg), "%s mengambil sejumlah uang tunai dan menyerahkannya kepada %s.", myName, targetName);
    DoProximityRaw(playerid, rpMsg, DIST_RP, COL_PURPLE);

    new sendMsg[144];
    format(sendMsg, sizeof(sendMsg), "  [Transaksi] Anda membayar {2ECC71}Rp %s{FFFFFF} kepada {FFFF00}%s{FFFFFF}.", amountRup, targetName);
    SendClientMessage(playerid, COL_GREEN, sendMsg);

    format(sendMsg, sizeof(sendMsg), "  [Transaksi] Anda menerima {2ECC71}Rp %s{FFFFFF} dari {FFFF00}%s{FFFFFF}.", amountRup, myName);
    SendClientMessage(targetid, COL_GREEN, sendMsg);

    PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
    PlayerPlaySound(targetid, 1058, 0.0, 0.0, 0.0);
    return 1;
}

CMD:give(playerid, params[]) {
    if (!CheckSpawned(playerid)) return 1;

    new targetid, itemName[32], amount;
    if (sscanf(params, "us[32]I(1)", targetid, itemName, amount)) {
        SendClientMessage(playerid, COL_ORANGE, "  [Petunjuk] Gunakan: /give [Player ID / Nama] [Nama Barang] [Jumlah]");
        SendClientMessage(playerid, COL_GREY,   "  * Contoh: /give 2 Burger 1 atau /give 2 Mineral 2");
        return 1;
    }

    if (!IsPlayerConnected(targetid) || !gPlayerData[targetid][p_LoggedIn] || !gPlayerData[targetid][p_Spawned]) {
        SendClientMessage(playerid, COL_RED, "  [Error] Pemain target tidak ditemukan atau sedang offline.");
        return 1;
    }

    if (targetid == playerid) {
        SendClientMessage(playerid, COL_RED, "  [Error] Anda tidak dapat memberikan barang ke diri sendiri!");
        return 1;
    }

    new itId = GetItemIDByName(itemName);
    if (itId <= 0) {
        // Cek jika user input itemid secara angka
        itId = strval(itemName);
        if (GetItemRegistryIndex(itId) == -1) {
            SendClientMessage(playerid, COL_RED, "  [Error] Nama barang tidak valid! Buka /inv untuk melihat nama barang.");
            return 1;
        }
    }

    if (itId == ITEM_KTP || itId == ITEM_SIM_A || itId == ITEM_SIM_B || itId == ITEM_SIM_C) {
        SendClientMessage(playerid, COL_RED, "  [Error] Dokumen resmi (e-KTP / SIM) tidak dapat dipindahtangankan!");
        return 1;
    }

    if (amount <= 0) amount = 1;

    new curAmt = Inventory_GetItemCount(playerid, itId);
    if (curAmt < amount) {
        new fullItemName[32];
        GetItemNameByID(itId, fullItemName, sizeof(fullItemName));
        new msg[128];
        format(msg, sizeof(msg), "  [Error] Stok %s Anda tidak mencukupi! (Anda memiliki %d unit).", fullItemName, curAmt);
        SendClientMessage(playerid, COL_RED, msg);
        return 1;
    }

    new Float:tx, Float:ty, Float:tz;
    GetPlayerPos(targetid, tx, ty, tz);
    if (!IsPlayerInRangeOfPoint(playerid, 4.0, tx, ty, tz)) {
        SendClientMessage(playerid, COL_RED, "  [Error] Pemain target berada terlalu jauh dari Anda (maks 4 meter)!");
        return 1;
    }

    Inventory_RemoveItem(playerid, itId, amount);
    Inventory_AddItem(targetid, itId, amount);

    new fullItemName[32], myName[48], targetName[48], rpMsg[160];
    GetItemNameByID(itId, fullItemName, sizeof(fullItemName));
    GetCharName(playerid, myName);
    GetCharName(targetid, targetName);

    format(rpMsg, sizeof(rpMsg), "%s menyerahkan %dx %s kepada %s.", myName, amount, fullItemName, targetName);
    DoProximityRaw(playerid, rpMsg, DIST_RP, COL_PURPLE);

    new sendMsg[144];
    format(sendMsg, sizeof(sendMsg), "  [Inventory] Anda memberikan {00EEFF}%dx %s{FFFFFF} kepada {FFFF00}%s{FFFFFF}.", amount, fullItemName, targetName);
    SendClientMessage(playerid, COL_GREEN, sendMsg);

    format(sendMsg, sizeof(sendMsg), "  [Inventory] Anda menerima {00EEFF}%dx %s{FFFFFF} dari {FFFF00}%s{FFFFFF}.", amount, fullItemName, myName);
    SendClientMessage(targetid, COL_GREEN, sendMsg);

    PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
    PlayerPlaySound(targetid, 1058, 0.0, 0.0, 0.0);
    return 1;
}

CMD:giveitem(playerid, params[]) {
    if (!IsAdmin(playerid, 1)) return 1;

    new targetid, itemName[32], amount;
    if (sscanf(params, "us[32]I(1)", targetid, itemName, amount)) {
        SendClientMessage(playerid, COL_ORANGE, "  [Admin] Gunakan: /giveitem [Player ID / Nama] [Nama Barang / ID] [Jumlah]");
        SendClientMessage(playerid, COL_GREY,   "  * Contoh: /giveitem 0 Burger 5 atau /giveitem 0 FirstAid 2");
        return 1;
    }

    if (!IsPlayerConnected(targetid) || !gPlayerData[targetid][p_LoggedIn] || !gPlayerData[targetid][p_Spawned]) {
        SendClientMessage(playerid, COL_RED, "  [Error] Pemain target tidak ditemukan atau sedang offline.");
        return 1;
    }

    new itId = GetItemIDByName(itemName);
    if (itId <= 0) {
        itId = strval(itemName);
        if (GetItemRegistryIndex(itId) == -1) {
            SendClientMessage(playerid, COL_RED, "  [Error] Nama atau ID barang tidak valid!");
            return 1;
        }
    }

    if (amount <= 0) amount = 1;

    Inventory_AddItem(targetid, itId, amount);

    new itName[32], tName[48], aName[48];
    GetItemNameByID(itId, itName, sizeof(itName));
    GetCharName(targetid, tName);
    GetCharName(playerid, aName);

    new msg[144];
    format(msg, sizeof(msg), "  [Admin] Anda memberikan %dx %s kepada %s.", amount, itName, tName);
    SendClientMessage(playerid, COL_GREEN, msg);

    format(msg, sizeof(msg), "  [Admin] Admin %s memberikan %dx %s ke dalam tas Anda.", aName, amount, itName);
    SendClientMessage(targetid, COL_GREEN, msg);
    return 1;
}
