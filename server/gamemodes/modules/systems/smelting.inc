#if defined _MODULE_SMELTING_INC
    #endinput
#endif
#define _MODULE_SMELTING_INC

// ============================================================
//  SantaraBaru Roleplay - Smelter & Metal Refining System
//  4 Meja Smelter di Pabrik Ocean Docks (Los Santos)
//  Animasi Tangan Bergerak & Durasi 20 Detik
// ============================================================

#define SMELTER_TABLE_COUNT     4

enum E_SMELTER_TABLE {
    Float:sm_X,
    Float:sm_Y,
    Float:sm_Z,
    Float:sm_A,
    sm_ObjectID,
    Text3D:sm_Label
};

new gSmelterTables[SMELTER_TABLE_COUNT][E_SMELTER_TABLE] = {
    {SMELTER_TABLE1_X, SMELTER_TABLE1_Y, SMELTER_TABLE1_Z, SMELTER_TABLE1_A, INVALID_OBJECT_ID, Text3D:INVALID_3DTEXT_ID}, // Smelter 1
    {SMELTER_TABLE2_X, SMELTER_TABLE2_Y, SMELTER_TABLE2_Z, SMELTER_TABLE2_A, INVALID_OBJECT_ID, Text3D:INVALID_3DTEXT_ID}, // Smelter 2
    {SMELTER_TABLE3_X, SMELTER_TABLE3_Y, SMELTER_TABLE3_Z, SMELTER_TABLE3_A, INVALID_OBJECT_ID, Text3D:INVALID_3DTEXT_ID}, // Smelter 3
    {SMELTER_TABLE4_X, SMELTER_TABLE4_Y, SMELTER_TABLE4_Z, SMELTER_TABLE4_A, INVALID_OBJECT_ID, Text3D:INVALID_3DTEXT_ID}  // Smelter 4
};

new bool:gIsSmelting[MAX_PLAYERS];
new gSmeltRecipe[MAX_PLAYERS];
new gSmeltTimer[MAX_PLAYERS];

forward OnPlayerFinishSmelting(playerid);

stock InitSmelterSystem() {
    for (new i = 0; i < SMELTER_TABLE_COUNT; i++) {
        // Spawn Objek Meja Kerja Fisik (Model 2008 Workbench)
        gSmelterTables[i][sm_ObjectID] = CreateObject(
            2008,
            gSmelterTables[i][sm_X],
            gSmelterTables[i][sm_Y],
            gSmelterTables[i][sm_Z] - 0.9,
            0.0, 0.0, gSmelterTables[i][sm_A]
        );

        CreatePickup(1239, 1, gSmelterTables[i][sm_X], gSmelterTables[i][sm_Y], gSmelterTables[i][sm_Z], 0);

        new labelText[160];
        format(labelText, sizeof(labelText),
            "{FF6600}[ MEJA PELEBURAN %d / SMELTER ]\n{FFFFFF}Tekan {FFFF00}[ F / ENTER ]{FFFFFF} atau ketik {00EEFF}/smelt{FFFFFF}\n{AAAAAA}Untuk mengolah bijih & bahan kimia",
            i + 1);

        gSmelterTables[i][sm_Label] = Create3DTextLabel(
            labelText,
            0xFFFFFFFF,
            gSmelterTables[i][sm_X], gSmelterTables[i][sm_Y], gSmelterTables[i][sm_Z] + 0.6,
            12.0, 0, 0
        );
    }
}

stock IsPlayerNearSmelter(playerid) {
    if (!CheckSpawned(playerid)) return 0;
    for (new i = 0; i < SMELTER_TABLE_COUNT; i++) {
        if (IsPlayerInRangeOfPoint(playerid, 2.5, gSmelterTables[i][sm_X], gSmelterTables[i][sm_Y], gSmelterTables[i][sm_Z])) {
            return 1;
        }
    }
    return 0;
}

stock ShowSmelterDialog(playerid) {
    new ironOre = Inventory_GetItemCount(playerid, ITEM_IRON_ORE);
    new copperOre = Inventory_GetItemCount(playerid, ITEM_COPPER_ORE);
    new sulfur = Inventory_GetItemCount(playerid, ITEM_SULFUR);

    new dialogStr[512];
    format(dialogStr, sizeof(dialogStr),
        "Hasil Olahan\tBahan Yang Dibutuhkan\tKetersediaan Anda\n" \
        "{00EEFF}Batang Baja (Steel Bar){FFFFFF}\t3x Bijih Besi\t%s%d/3 Bijih Besi{FFFFFF}\n" \
        "{00EEFF}Lempeng Kuningan (Brass Plate){FFFFFF}\t3x Bijih Tembaga\t%s%d/3 Bijih Tembaga{FFFFFF}\n" \
        "{00EEFF}Bubuk Mesiu (Gunpowder){FFFFFF}\t2x Belerang\t%s%d/2 Belerang{FFFFFF}",
        (ironOre >= 3) ? "{00FF00}" : "{FF0000}", ironOre,
        (copperOre >= 3) ? "{00FF00}" : "{FF0000}", copperOre,
        (sulfur >= 2) ? "{00FF00}" : "{FF0000}", sulfur
    );

    ShowPlayerDialog(playerid, DLG_SMELTER_MAIN, DIALOG_STYLE_TABLIST_HEADERS,
        "{FF6600}Meja Peleburan & Pengolahan Material", dialogStr, "Lebur", "Tutup");
}

stock HandleSmelterDialog(playerid, dialogid, response, listitem) {
    if (dialogid != DLG_SMELTER_MAIN) return 0;
    if (!response) return 1;

    if (gIsSmelting[playerid]) {
        SendClientMessage(playerid, COL_RED, "  [!] Anda sedang dalam proses peleburan!");
        return 1;
    }

    if (!IsPlayerNearSmelter(playerid)) {
        SendClientMessage(playerid, COL_RED, "  [!] Anda harus berada di dekat Meja Peleburan Pabrik (Ocean Docks LS)!");
        return 1;
    }

    switch (listitem) {
        case 0: { // Batang Baja (3x Bijih Besi)
            if (Inventory_GetItemCount(playerid, ITEM_IRON_ORE) < 3) {
                SendClientMessage(playerid, COL_RED, "  [SMELTER] Anda membutuhkan minimal 3x Bijih Besi (Iron Ore) untuk dilebur!");
                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
                return 1;
            }
        }
        case 1: { // Lempeng Kuningan (3x Bijih Tembaga)
            if (Inventory_GetItemCount(playerid, ITEM_COPPER_ORE) < 3) {
                SendClientMessage(playerid, COL_RED, "  [SMELTER] Anda membutuhkan minimal 3x Bijih Tembaga (Copper Ore) untuk dilebur!");
                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
                return 1;
            }
        }
        case 2: { // Bubuk Mesiu (2x Belerang - Tanpa Arang)
            if (Inventory_GetItemCount(playerid, ITEM_SULFUR) < 2) {
                SendClientMessage(playerid, COL_RED, "  [SMELTER] Anda membutuhkan 2x Belerang (Sulfur) untuk meracik bubuk mesiu!");
                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
                return 1;
            }
        }
        default: return 1;
    }

    // Mulai proses peleburan selama 20 detik dengan animasi tangan bergerak-gerak
    gIsSmelting[playerid] = true;
    gSmeltRecipe[playerid] = listitem;

    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
    GameTextForPlayer(playerid, "~y~Sedang Melebur...~n~~w~20 Detik", 5000, 3);
    SendClientMessage(playerid, COL_YELLOW, "  [*] Sedang mengolah dan melebur material di meja smelter... (20 detik)");

    new charname[48], rpMsg[144];
    GetCharName(playerid, charname);
    format(rpMsg, sizeof(rpMsg), "* %s menggerakkan tangan mengolah bahan dan memanaskan material di atas meja peleburan.", charname);
    DoProximitySay(playerid, rpMsg, DIST_RP, COL_PURPLE, false);

    gSmeltTimer[playerid] = SetTimerEx("OnPlayerFinishSmelting", 20000, false, "i", playerid);
    return 1;
}

public OnPlayerFinishSmelting(playerid) {
    if (!gIsSmelting[playerid]) return 1;
    gIsSmelting[playerid] = false;
    ClearAnimations(playerid, 1);

    new charname[48], rpMsg[144];
    GetCharName(playerid, charname);

    switch (gSmeltRecipe[playerid]) {
        case 0: { // Batang Baja
            if (Inventory_GetItemCount(playerid, ITEM_IRON_ORE) < 3) {
                SendClientMessage(playerid, COL_RED, "  [SMELTER] Bijih Besi Anda tidak cukup!");
                return 1;
            }
            Inventory_RemoveItem(playerid, ITEM_IRON_ORE, 3);
            Inventory_AddItem(playerid, ITEM_STEEL_BAR, 1);

            SendClientMessage(playerid, COL_GREEN, "  [SMELTER] Sukses melebur 3x Bijih Besi menjadi {00EEFF}1x Batang Baja (Steel Bar){FFFFFF}!");
            format(rpMsg, sizeof(rpMsg), "* %s mendinginkan cetakan logam dan mengantongi 1x Batang Baja padat.", charname);
        }
        case 1: { // Lempeng Kuningan
            if (Inventory_GetItemCount(playerid, ITEM_COPPER_ORE) < 3) {
                SendClientMessage(playerid, COL_RED, "  [SMELTER] Bijih Tembaga Anda tidak cukup!");
                return 1;
            }
            Inventory_RemoveItem(playerid, ITEM_COPPER_ORE, 3);
            Inventory_AddItem(playerid, ITEM_BRASS_PLATE, 1);

            SendClientMessage(playerid, COL_GREEN, "  [SMELTER] Sukses melebur 3x Bijih Tembaga menjadi {00EEFF}1x Lempeng Kuningan (Brass Plate){FFFFFF}!");
            format(rpMsg, sizeof(rpMsg), "* %s mencetak lempengan logam kuningan panas dari bijih tembaga.", charname);
        }
        case 2: { // Bubuk Mesiu (2x Belerang)
            if (Inventory_GetItemCount(playerid, ITEM_SULFUR) < 2) {
                SendClientMessage(playerid, COL_RED, "  [SMELTER] Belerang Anda tidak cukup!");
                return 1;
            }
            Inventory_RemoveItem(playerid, ITEM_SULFUR, 2);
            Inventory_AddItem(playerid, ITEM_GUNPOWDER, 2);

            SendClientMessage(playerid, COL_GREEN, "  [SMELTER] Sukses meracik material kimia menjadi {00EEFF}2x Bubuk Mesiu (Gunpowder){FFFFFF}!");
            format(rpMsg, sizeof(rpMsg), "* %s menumbuk dan memurnikan belerang menjadi bubuk mesiu peledak berkualitas.", charname);
        }
    }

    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
    GameTextForPlayer(playerid, "~g~Peleburan Selesai!", 2500, 3);
    DoProximitySay(playerid, rpMsg, DIST_RP, COL_PURPLE, false);
    return 1;
}

CMD:smelt(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    if (!IsPlayerNearSmelter(playerid)) {
        return SendClientMessage(playerid, COL_RED, "  [!] Anda harus berada di dekat Meja Peleburan Pabrik (Ocean Docks LS)!");
    }
    ShowSmelterDialog(playerid);
    return 1;
}

CMD:lebur(playerid, params[]) {
    return cmd_smelt(playerid, params);
}
