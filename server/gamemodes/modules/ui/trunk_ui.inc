#if defined _MODULE_TRUNK_UI_INC
    #endinput
#endif
#define _MODULE_TRUNK_UI_INC

// ============================================================
//  SantaraBaru Roleplay - Right-Aligned 2-Tab Vehicle Trunk GUI
//  Tab 1: Bagasi Mobil <---> Tab 2: Tas Saya
//  Clean Minimalist Dark Theme with Electric Purple Accent & Top Red [X]
// ============================================================

#define TRUNK_SLOTS_PER_PAGE 10

// Colors from Reference Design
#define COLOR_TRUNK_BG       0x1E1E2EFF  // Dark Indigo Background
#define COLOR_TRUNK_PURPLE   0x5814EEFF  // Electric Purple Accent
#define COLOR_TRUNK_RED      0xFA1E38FF  // Vibrant Red Delete & [X] Close Button
#define COLOR_TRUNK_SLATE    0x3E3E44EE  // Dark Slate Inactive/Button Tile
#define COLOR_TRUNK_EMPTY    0x34343AEE  // Dark Slate Empty Slot

new PlayerText:TD_TrunkMainBox[MAX_PLAYERS]        = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_TrunkTopBar[MAX_PLAYERS]         = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_TrunkCloseBtn[MAX_PLAYERS]       = {PlayerText:INVALID_TEXT_DRAW, ...};

// 2 Tab Headers
new PlayerText:TD_TrunkTab1[MAX_PLAYERS]           = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_TrunkTab2[MAX_PLAYERS]           = {PlayerText:INVALID_TEXT_DRAW, ...};

// 10x Item Slots
new PlayerText:TD_TrunkSlotBox[MAX_PLAYERS][TRUNK_SLOTS_PER_PAGE];

// Page Indicator
new PlayerText:TD_TrunkPageText[MAX_PLAYERS]       = {PlayerText:INVALID_TEXT_DRAW, ...};

// Primary & Secondary Action Buttons
new PlayerText:TD_TrunkBtnPrimary[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_TrunkBtnSecondary[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};

// Navigation Buttons
new PlayerText:TD_TrunkUpBtn[MAX_PLAYERS]          = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_TrunkDownBtn[MAX_PLAYERS]        = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_TrunkPrevBtn[MAX_PLAYERS]        = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_TrunkNextBtn[MAX_PLAYERS]        = {PlayerText:INVALID_TEXT_DRAW, ...};

forward Trunk_LoadItems(veh_dbid, playerid);
forward Trunk_AddItem(veh_dbid, item_id, amount);
forward Trunk_RemoveItem(veh_dbid, item_id, amount);
forward Trunk_GetItemCount(veh_dbid, item_id);
forward SetVehicleBootOpen(vehicleid, bool:open);

stock DestroyPlayerTrunkTextDraws(playerid) {
    if (TD_TrunkMainBox[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_TrunkMainBox[playerid]);
        TD_TrunkMainBox[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_TrunkTopBar[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_TrunkTopBar[playerid]);
        TD_TrunkTopBar[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_TrunkCloseBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_TrunkCloseBtn[playerid]);
        TD_TrunkCloseBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (TD_TrunkTab1[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_TrunkTab1[playerid]);
        TD_TrunkTab1[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_TrunkTab2[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_TrunkTab2[playerid]);
        TD_TrunkTab2[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    for (new s = 0; s < TRUNK_SLOTS_PER_PAGE; s++) {
        if (TD_TrunkSlotBox[playerid][s] != PlayerText:INVALID_TEXT_DRAW) {
            PlayerTextDrawDestroy(playerid, TD_TrunkSlotBox[playerid][s]);
            TD_TrunkSlotBox[playerid][s] = PlayerText:INVALID_TEXT_DRAW;
        }
    }

    if (TD_TrunkPageText[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_TrunkPageText[playerid]);
        TD_TrunkPageText[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (TD_TrunkBtnPrimary[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_TrunkBtnPrimary[playerid]);
        TD_TrunkBtnPrimary[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_TrunkBtnSecondary[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_TrunkBtnSecondary[playerid]);
        TD_TrunkBtnSecondary[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (TD_TrunkUpBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_TrunkUpBtn[playerid]);
        TD_TrunkUpBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_TrunkDownBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_TrunkDownBtn[playerid]);
        TD_TrunkDownBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_TrunkPrevBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_TrunkPrevBtn[playerid]);
        TD_TrunkPrevBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_TrunkNextBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_TrunkNextBtn[playerid]);
        TD_TrunkNextBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
}

stock CreatePlayerTrunkTextDraws(playerid) {
    DestroyPlayerTrunkTextDraws(playerid);

    // 1. Background Frame (Right side: X: 430.0 .. 620.0, Y: 78.0 .. 360.0)
    TD_TrunkMainBox[playerid] = CreatePlayerTextDraw(playerid, 430.0, 78.0, "_");
    PlayerTextDrawUseBox(playerid, TD_TrunkMainBox[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_TrunkMainBox[playerid], COLOR_TRUNK_BG);
    PlayerTextDrawTextSize(playerid, TD_TrunkMainBox[playerid], 620.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_TrunkMainBox[playerid], 0.0, 31.0);
    PlayerTextDrawSetSelectable(playerid, TD_TrunkMainBox[playerid], false);

    // 2. Top Accent Line (Electric Purple #5814EEFF, X: 430.0 .. 602.0, Y: 78.0)
    TD_TrunkTopBar[playerid] = CreatePlayerTextDraw(playerid, 430.0, 78.0, "_");
    PlayerTextDrawUseBox(playerid, TD_TrunkTopBar[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_TrunkTopBar[playerid], COLOR_TRUNK_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_TrunkTopBar[playerid], 602.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_TrunkTopBar[playerid], 0.0, 0.75);
    PlayerTextDrawSetSelectable(playerid, TD_TrunkTopBar[playerid], false);

    // 3. Top-Right Red Close Button [X] (Center X: 611.0, Y: 77.0)
    TD_TrunkCloseBtn[playerid] = CreatePlayerTextDraw(playerid, 611.0, 77.0, "X");
    PlayerTextDrawFont(playerid, TD_TrunkCloseBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_TrunkCloseBtn[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_TrunkCloseBtn[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_TrunkCloseBtn[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_TrunkCloseBtn[playerid], COLOR_TRUNK_RED);
    PlayerTextDrawTextSize(playerid, TD_TrunkCloseBtn[playerid], 10.0, 18.0);
    PlayerTextDrawAlignment(playerid, TD_TrunkCloseBtn[playerid], 2); // Center
    PlayerTextDrawSetOutline(playerid, TD_TrunkCloseBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_TrunkCloseBtn[playerid], true);

    // 4. 2 Tab Selectors (Y: 90.0)
    // Tab 1: Bagasi Mobil (Center X: 481.0, Width: 82.0)
    TD_TrunkTab1[playerid] = CreatePlayerTextDraw(playerid, 481.0, 90.0, "Bagasi Mobil");
    PlayerTextDrawFont(playerid, TD_TrunkTab1[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_TrunkTab1[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_TrunkTab1[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_TrunkTab1[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_TrunkTab1[playerid], COLOR_TRUNK_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_TrunkTab1[playerid], 14.0, 82.0);
    PlayerTextDrawAlignment(playerid, TD_TrunkTab1[playerid], 2); // Center
    PlayerTextDrawSetOutline(playerid, TD_TrunkTab1[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_TrunkTab1[playerid], true);

    // Tab 2: Tas Saya (Center X: 569.0, Width: 82.0)
    TD_TrunkTab2[playerid] = CreatePlayerTextDraw(playerid, 569.0, 90.0, "Tas Saya");
    PlayerTextDrawFont(playerid, TD_TrunkTab2[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_TrunkTab2[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_TrunkTab2[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_TrunkTab2[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_TrunkTab2[playerid], COLOR_TRUNK_SLATE);
    PlayerTextDrawTextSize(playerid, TD_TrunkTab2[playerid], 14.0, 82.0);
    PlayerTextDrawAlignment(playerid, TD_TrunkTab2[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_TrunkTab2[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_TrunkTab2[playerid], true);

    // 5. 10x Item Slot Tiles (Y: 110.0 .. 250.0, Left Edge: 440.0, Right: 610.0)
    for (new s = 0; s < TRUNK_SLOTS_PER_PAGE; s++) {
        new Float:slotY = 110.0 + (s * 14.5);
        TD_TrunkSlotBox[playerid][s] = CreatePlayerTextDraw(playerid, 440.0, slotY, "Kosong");
        PlayerTextDrawFont(playerid, TD_TrunkSlotBox[playerid][s], 1);
        PlayerTextDrawLetterSize(playerid, TD_TrunkSlotBox[playerid][s], 0.16, 0.90);
        PlayerTextDrawColor(playerid, TD_TrunkSlotBox[playerid][s], 0xFFFFFFFF);
        PlayerTextDrawUseBox(playerid, TD_TrunkSlotBox[playerid][s], true);
        PlayerTextDrawBoxColor(playerid, TD_TrunkSlotBox[playerid][s], COLOR_TRUNK_EMPTY);
        PlayerTextDrawTextSize(playerid, TD_TrunkSlotBox[playerid][s], 610.0, 12.0);
        PlayerTextDrawSetOutline(playerid, TD_TrunkSlotBox[playerid][s], 1);
        PlayerTextDrawSetSelectable(playerid, TD_TrunkSlotBox[playerid][s], true);
    }

    // 6. Page Indicator (Center X: 525.0, Y: 259.0)
    TD_TrunkPageText[playerid] = CreatePlayerTextDraw(playerid, 525.0, 259.0, "Hal 1/1");
    PlayerTextDrawFont(playerid, TD_TrunkPageText[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_TrunkPageText[playerid], 0.15, 0.85);
    PlayerTextDrawColor(playerid, TD_TrunkPageText[playerid], 0xCCCCCCFF);
    PlayerTextDrawAlignment(playerid, TD_TrunkPageText[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_TrunkPageText[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_TrunkPageText[playerid], false);

    // 7. Primary Action Button (Ambil Ke Tas Saya / Masukan ke Bagasi) (Center X: 525.0, Y: 275.0)
    TD_TrunkBtnPrimary[playerid] = CreatePlayerTextDraw(playerid, 525.0, 275.0, "Ambil Ke Tas Saya");
    PlayerTextDrawFont(playerid, TD_TrunkBtnPrimary[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_TrunkBtnPrimary[playerid], 0.17, 1.05);
    PlayerTextDrawColor(playerid, TD_TrunkBtnPrimary[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_TrunkBtnPrimary[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_TrunkBtnPrimary[playerid], COLOR_TRUNK_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_TrunkBtnPrimary[playerid], 15.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_TrunkBtnPrimary[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_TrunkBtnPrimary[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_TrunkBtnPrimary[playerid], true);

    // 8. Secondary Action Button (Buang Dari Bagasi / Buang Dari Tas) (Center X: 525.0, Y: 295.0)
    TD_TrunkBtnSecondary[playerid] = CreatePlayerTextDraw(playerid, 525.0, 295.0, "Buang Dari Bagasi");
    PlayerTextDrawFont(playerid, TD_TrunkBtnSecondary[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_TrunkBtnSecondary[playerid], 0.17, 1.05);
    PlayerTextDrawColor(playerid, TD_TrunkBtnSecondary[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_TrunkBtnSecondary[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_TrunkBtnSecondary[playerid], COLOR_TRUNK_RED);
    PlayerTextDrawTextSize(playerid, TD_TrunkBtnSecondary[playerid], 15.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_TrunkBtnSecondary[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_TrunkBtnSecondary[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_TrunkBtnSecondary[playerid], true);

    // 9. Navigation Row 1: Naik / Turun (Y: 316.0)
    TD_TrunkUpBtn[playerid] = CreatePlayerTextDraw(playerid, 481.0, 316.0, "Naik");
    PlayerTextDrawFont(playerid, TD_TrunkUpBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_TrunkUpBtn[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_TrunkUpBtn[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_TrunkUpBtn[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_TrunkUpBtn[playerid], COLOR_TRUNK_SLATE);
    PlayerTextDrawTextSize(playerid, TD_TrunkUpBtn[playerid], 14.0, 82.0);
    PlayerTextDrawAlignment(playerid, TD_TrunkUpBtn[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_TrunkUpBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_TrunkUpBtn[playerid], true);

    TD_TrunkDownBtn[playerid] = CreatePlayerTextDraw(playerid, 569.0, 316.0, "Turun");
    PlayerTextDrawFont(playerid, TD_TrunkDownBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_TrunkDownBtn[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_TrunkDownBtn[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_TrunkDownBtn[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_TrunkDownBtn[playerid], COLOR_TRUNK_SLATE);
    PlayerTextDrawTextSize(playerid, TD_TrunkDownBtn[playerid], 14.0, 82.0);
    PlayerTextDrawAlignment(playerid, TD_TrunkDownBtn[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_TrunkDownBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_TrunkDownBtn[playerid], true);

    // 10. Navigation Row 2: < Sebelum / Selanjutnya > (Y: 334.0)
    TD_TrunkPrevBtn[playerid] = CreatePlayerTextDraw(playerid, 481.0, 334.0, "< Sebelum");
    PlayerTextDrawFont(playerid, TD_TrunkPrevBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_TrunkPrevBtn[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_TrunkPrevBtn[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_TrunkPrevBtn[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_TrunkPrevBtn[playerid], COLOR_TRUNK_SLATE);
    PlayerTextDrawTextSize(playerid, TD_TrunkPrevBtn[playerid], 14.0, 82.0);
    PlayerTextDrawAlignment(playerid, TD_TrunkPrevBtn[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_TrunkPrevBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_TrunkPrevBtn[playerid], true);

    TD_TrunkNextBtn[playerid] = CreatePlayerTextDraw(playerid, 569.0, 334.0, "Selanjutnya >");
    PlayerTextDrawFont(playerid, TD_TrunkNextBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_TrunkNextBtn[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_TrunkNextBtn[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_TrunkNextBtn[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_TrunkNextBtn[playerid], COLOR_TRUNK_SLATE);
    PlayerTextDrawTextSize(playerid, TD_TrunkNextBtn[playerid], 14.0, 82.0);
    PlayerTextDrawAlignment(playerid, TD_TrunkNextBtn[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_TrunkNextBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_TrunkNextBtn[playerid], true);
}

stock UpdateTrunkUI(playerid) {
    if (!gPlayerData[playerid][p_InTrunkUI]) return;

    new vehDbId = gPlayerData[playerid][p_TrunkVehDBID];

    // Update Tab Colors & Button Labels based on active state
    if (gPlayerData[playerid][p_TrunkActiveTab] == 0) { // TAB 1: BAGASI MOBIL
        PlayerTextDrawBoxColor(playerid, TD_TrunkTab1[playerid], COLOR_TRUNK_PURPLE);
        PlayerTextDrawBoxColor(playerid, TD_TrunkTab2[playerid], COLOR_TRUNK_SLATE);

        PlayerTextDrawSetString(playerid, TD_TrunkBtnPrimary[playerid], "Ambil Ke Tas Saya");
        PlayerTextDrawSetString(playerid, TD_TrunkBtnSecondary[playerid], "Buang Dari Bagasi");

        Trunk_LoadItems(vehDbId, playerid);
    } else { // TAB 2: TAS SAYA
        PlayerTextDrawBoxColor(playerid, TD_TrunkTab1[playerid], COLOR_TRUNK_SLATE);
        PlayerTextDrawBoxColor(playerid, TD_TrunkTab2[playerid], COLOR_TRUNK_PURPLE);

        PlayerTextDrawSetString(playerid, TD_TrunkBtnPrimary[playerid], "Masukan ke Bagasi");
        PlayerTextDrawSetString(playerid, TD_TrunkBtnSecondary[playerid], "Buang Dari Tas");

        Inventory_LoadPlayerItems(playerid);
    }

    new totalItems = (gPlayerData[playerid][p_TrunkActiveTab] == 0) ? (gPlayerData[playerid][p_TrunkItemCount]) : (gPlayerData[playerid][p_InvItemCount]);
    new totalPages = (totalItems + TRUNK_SLOTS_PER_PAGE - 1) / TRUNK_SLOTS_PER_PAGE;
    if (totalPages <= 0) totalPages = 1;

    if (gPlayerData[playerid][p_TrunkCurrentPage] >= totalPages) {
        gPlayerData[playerid][p_TrunkCurrentPage] = totalPages - 1;
    }
    if (gPlayerData[playerid][p_TrunkCurrentPage] < 0) {
        gPlayerData[playerid][p_TrunkCurrentPage] = 0;
    }

    new page = gPlayerData[playerid][p_TrunkCurrentPage];

    // Update Page Indicator
    new pageStr[32];
    format(pageStr, sizeof(pageStr), "Hal %d/%d", page + 1, totalPages);
    PlayerTextDrawSetString(playerid, TD_TrunkPageText[playerid], pageStr);

    // Update 10 Item Slots
    for (new s = 0; s < TRUNK_SLOTS_PER_PAGE; s++) {
        new itemIdxInList = (page * TRUNK_SLOTS_PER_PAGE) + s;
        if (itemIdxInList < totalItems) {
            new itId = (gPlayerData[playerid][p_TrunkActiveTab] == 0) ? (gPlayerData[playerid][p_TrunkSlotItemID][itemIdxInList]) : (gPlayerData[playerid][p_InvSlotItemID][itemIdxInList]);
            new itAmt = (gPlayerData[playerid][p_TrunkActiveTab] == 0) ? (gPlayerData[playerid][p_TrunkSlotAmount][itemIdxInList]) : (gPlayerData[playerid][p_InvSlotAmount][itemIdxInList]);
            new itName[32];
            GetItemNameByID(itId, itName, sizeof(itName));

            new slotStr[64];
            if (itemIdxInList == gPlayerData[playerid][p_SelectedTrunkSlot]) {
                format(slotStr, sizeof(slotStr), " > %s (%dx)", itName, itAmt);
                PlayerTextDrawBoxColor(playerid, TD_TrunkSlotBox[playerid][s], COLOR_TRUNK_PURPLE); // Active Electric Purple
            } else {
                format(slotStr, sizeof(slotStr), " %s (%dx)", itName, itAmt);
                PlayerTextDrawBoxColor(playerid, TD_TrunkSlotBox[playerid][s], COLOR_TRUNK_SLATE);
            }
            PlayerTextDrawSetString(playerid, TD_TrunkSlotBox[playerid][s], slotStr);
            PlayerTextDrawShow(playerid, TD_TrunkSlotBox[playerid][s]);
        } else {
            PlayerTextDrawSetString(playerid, TD_TrunkSlotBox[playerid][s], " Kosong");
            PlayerTextDrawBoxColor(playerid, TD_TrunkSlotBox[playerid][s], COLOR_TRUNK_EMPTY);
            PlayerTextDrawShow(playerid, TD_TrunkSlotBox[playerid][s]);
        }
    }

    // Refresh selected item ID
    new selSlot = gPlayerData[playerid][p_SelectedTrunkSlot];
    if (selSlot >= 0 && selSlot < totalItems) {
        new itId = (gPlayerData[playerid][p_TrunkActiveTab] == 0) ? (gPlayerData[playerid][p_TrunkSlotItemID][selSlot]) : (gPlayerData[playerid][p_InvSlotItemID][selSlot]);
        gPlayerData[playerid][p_SelectedTrunkItemID] = itId;
    } else {
        gPlayerData[playerid][p_SelectedTrunkSlot] = -1;
        gPlayerData[playerid][p_SelectedTrunkItemID] = 0;
    }

    // Pastikan tabs & buttons tetap aktif
    PlayerTextDrawShow(playerid, TD_TrunkCloseBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_TrunkTab1[playerid]);
    PlayerTextDrawShow(playerid, TD_TrunkTab2[playerid]);
    PlayerTextDrawShow(playerid, TD_TrunkBtnPrimary[playerid]);
    PlayerTextDrawShow(playerid, TD_TrunkBtnSecondary[playerid]);
}

stock ShowTrunkUI(playerid, vehicleid) {
    if (!CheckSpawned(playerid)) return 0;
    if (vehicleid == INVALID_VEHICLE_ID) return 0;

    new vehDbId = GetVehicleDBID(vehicleid);
    if (vehDbId <= 0) {
        SendClientMessage(playerid, COL_RED, "  [Bagasi] Kendaraan ini tidak memiliki sistem penyimpanan bagasi!");
        return 0;
    }

    // Sembunyikan HUD pojok kanan atas sementara waktu
    DestroyPlayerMoneyHUD(playerid);

    CreatePlayerTrunkTextDraws(playerid);
    gPlayerData[playerid][p_InTrunkUI] = true;
    gPlayerData[playerid][p_TrunkVehID] = vehicleid;
    gPlayerData[playerid][p_TrunkVehDBID] = vehDbId;
    gPlayerData[playerid][p_TrunkActiveTab] = 0; // Default: Tab 1 (Bagasi Mobil)
    gPlayerData[playerid][p_TrunkCurrentPage] = 0;

    // Buka kap bagasi kendaraan secara visual di dunia game
    SetVehicleBootOpen(vehicleid, true);

    Trunk_LoadItems(vehDbId, playerid);
    if (gPlayerData[playerid][p_TrunkItemCount] > 0) {
        gPlayerData[playerid][p_SelectedTrunkSlot] = 0;
        gPlayerData[playerid][p_SelectedTrunkItemID] = gPlayerData[playerid][p_TrunkSlotItemID][0];
    } else {
        gPlayerData[playerid][p_SelectedTrunkSlot] = -1;
        gPlayerData[playerid][p_SelectedTrunkItemID] = 0;
    }

    // Tampilkan TextDraws
    PlayerTextDrawShow(playerid, TD_TrunkMainBox[playerid]);
    PlayerTextDrawShow(playerid, TD_TrunkTopBar[playerid]);
    PlayerTextDrawShow(playerid, TD_TrunkCloseBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_TrunkTab1[playerid]);
    PlayerTextDrawShow(playerid, TD_TrunkTab2[playerid]);

    for (new s = 0; s < TRUNK_SLOTS_PER_PAGE; s++) {
        PlayerTextDrawShow(playerid, TD_TrunkSlotBox[playerid][s]);
    }

    PlayerTextDrawShow(playerid, TD_TrunkPageText[playerid]);
    PlayerTextDrawShow(playerid, TD_TrunkBtnPrimary[playerid]);
    PlayerTextDrawShow(playerid, TD_TrunkBtnSecondary[playerid]);
    PlayerTextDrawShow(playerid, TD_TrunkUpBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_TrunkDownBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_TrunkPrevBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_TrunkNextBtn[playerid]);

    UpdateTrunkUI(playerid);

    // Aktifkan mode kursor mouse dengan highlight Electric Purple
    SelectTextDraw(playerid, COLOR_TRUNK_PURPLE);
    PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
    return 1;
}

stock HideTrunkUI(playerid) {
    if (!gPlayerData[playerid][p_InTrunkUI]) return;

    new vehId = gPlayerData[playerid][p_TrunkVehID];
    if (vehId != INVALID_VEHICLE_ID) {
        // Tutup kembali kap bagasi kendaraan secara visual di dunia game
        SetVehicleBootOpen(vehId, false);
    }

    gPlayerData[playerid][p_InTrunkUI] = false;
    gPlayerData[playerid][p_TrunkVehID] = INVALID_VEHICLE_ID;
    gPlayerData[playerid][p_TrunkVehDBID] = 0;
    CancelSelectTextDraw(playerid);

    DestroyPlayerTrunkTextDraws(playerid);
    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);

    // Kembalikan & segarkan HUD
    CreatePlayerMoneyHUD(playerid);
    UpdatePlayerMoneyHUD(playerid);
    ShowPlayerMoneyHUD(playerid);
}

stock HandleTrunkClick(playerid, PlayerText:playertextid) {
    if (!gPlayerData[playerid][p_InTrunkUI]) return 0;

    // 1. TOMBOL [X] MERAH TUTUP
    if (playertextid == TD_TrunkCloseBtn[playerid]) {
        HideTrunkUI(playerid);
        return 1;
    }

    // 2. TAB 1: BAGASI MOBIL
    if (playertextid == TD_TrunkTab1[playerid]) {
        if (gPlayerData[playerid][p_TrunkActiveTab] != 0) {
            gPlayerData[playerid][p_TrunkActiveTab] = 0;
            gPlayerData[playerid][p_TrunkCurrentPage] = 0;
            gPlayerData[playerid][p_SelectedTrunkSlot] = 0;
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
            UpdateTrunkUI(playerid);
        }
        return 1;
    }

    // 3. TAB 2: TAS SAYA
    if (playertextid == TD_TrunkTab2[playerid]) {
        if (gPlayerData[playerid][p_TrunkActiveTab] != 1) {
            gPlayerData[playerid][p_TrunkActiveTab] = 1;
            gPlayerData[playerid][p_TrunkCurrentPage] = 0;
            gPlayerData[playerid][p_SelectedTrunkSlot] = 0;
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
            UpdateTrunkUI(playerid);
        }
        return 1;
    }

    new totalItems = (gPlayerData[playerid][p_TrunkActiveTab] == 0) ? (gPlayerData[playerid][p_TrunkItemCount]) : (gPlayerData[playerid][p_InvItemCount]);

    // 4. Tombol NAIK (UP)
    if (playertextid == TD_TrunkUpBtn[playerid]) {
        if (totalItems > 0 && gPlayerData[playerid][p_SelectedTrunkSlot] > 0) {
            gPlayerData[playerid][p_SelectedTrunkSlot]--;
            if (gPlayerData[playerid][p_SelectedTrunkSlot] < gPlayerData[playerid][p_TrunkCurrentPage] * TRUNK_SLOTS_PER_PAGE) {
                if (gPlayerData[playerid][p_TrunkCurrentPage] > 0) {
                    gPlayerData[playerid][p_TrunkCurrentPage]--;
                }
            }
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
            UpdateTrunkUI(playerid);
        }
        return 1;
    }

    // 5. Tombol TURUN (DOWN)
    if (playertextid == TD_TrunkDownBtn[playerid]) {
        if (totalItems > 0 && gPlayerData[playerid][p_SelectedTrunkSlot] < totalItems - 1) {
            gPlayerData[playerid][p_SelectedTrunkSlot]++;
            if (gPlayerData[playerid][p_SelectedTrunkSlot] >= (gPlayerData[playerid][p_TrunkCurrentPage] + 1) * TRUNK_SLOTS_PER_PAGE) {
                gPlayerData[playerid][p_TrunkCurrentPage]++;
            }
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
            UpdateTrunkUI(playerid);
        }
        return 1;
    }

    // 6. Tombol < SEBELUM (PREV)
    if (playertextid == TD_TrunkPrevBtn[playerid]) {
        if (gPlayerData[playerid][p_TrunkCurrentPage] > 0) {
            gPlayerData[playerid][p_TrunkCurrentPage]--;
            gPlayerData[playerid][p_SelectedTrunkSlot] = gPlayerData[playerid][p_TrunkCurrentPage] * TRUNK_SLOTS_PER_PAGE;
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
            UpdateTrunkUI(playerid);
        }
        return 1;
    }

    // 7. Tombol SELANJUTNYA > (NEXT)
    if (playertextid == TD_TrunkNextBtn[playerid]) {
        new totalPages = (totalItems + TRUNK_SLOTS_PER_PAGE - 1) / TRUNK_SLOTS_PER_PAGE;
        if (gPlayerData[playerid][p_TrunkCurrentPage] < totalPages - 1) {
            gPlayerData[playerid][p_TrunkCurrentPage]++;
            gPlayerData[playerid][p_SelectedTrunkSlot] = gPlayerData[playerid][p_TrunkCurrentPage] * TRUNK_SLOTS_PER_PAGE;
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
            UpdateTrunkUI(playerid);
        }
        return 1;
    }

    // 8. Klik Slot Barang Langsung (0 - 9)
    for (new s = 0; s < TRUNK_SLOTS_PER_PAGE; s++) {
        if (playertextid == TD_TrunkSlotBox[playerid][s]) {
            new itemIdxInList = (gPlayerData[playerid][p_TrunkCurrentPage] * TRUNK_SLOTS_PER_PAGE) + s;
            if (itemIdxInList < totalItems) {
                gPlayerData[playerid][p_SelectedTrunkSlot] = itemIdxInList;
                PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
                UpdateTrunkUI(playerid);
            }
            return 1;
        }
    }

    // 9. Tombol Aksi Utama [ Ambil Ke Tas Saya / Masukan ke Bagasi ]
    if (playertextid == TD_TrunkBtnPrimary[playerid]) {
        new itId = gPlayerData[playerid][p_SelectedTrunkItemID];
        if (itId <= 0) {
            SendClientMessage(playerid, COL_RED, "  [Bagasi] Silakan pilih barang di daftar terlebih dahulu!");
            return 1;
        }

        new itName[32];
        GetItemNameByID(itId, itName, sizeof(itName));

        if (gPlayerData[playerid][p_TrunkActiveTab] == 0) { // AMBIL DARI BAGASI KE TAS
            new curAmt = Trunk_GetItemCount(gPlayerData[playerid][p_TrunkVehDBID], itId);
            if (curAmt <= 0) {
                SendClientMessage(playerid, COL_RED, "  [Bagasi] Barang ini sudah tidak tersedia di bagasi!");
                UpdateTrunkUI(playerid);
                return 1;
            }

            new takePrompt[256];
            format(takePrompt, sizeof(takePrompt),
                "{FFFFFF}Berapa banyak {5814EE}%s{FFFFFF} yang ingin Anda ambil ke dalam tas?\n\n{A0AEC0}(Jumlah di bagasi mobil: %d unit)",
                itName, curAmt);

            ShowPlayerDialog(playerid, DLG_TRUNK_TAKE_QTY, DIALOG_STYLE_INPUT,
                "{5814EE}Ambil Barang dari Bagasi", takePrompt, "Ambil", "Batal");
        } else { // SIMPAN DARI TAS KE BAGASI
            if (itId == ITEM_KTP) {
                SendClientMessage(playerid, COL_RED, "  [Bagasi] Dokumen e-KTP tidak dapat disimpan ke dalam bagasi mobil!");
                return 1;
            }

            new curAmt = Inventory_GetItemCount(playerid, itId);
            if (curAmt <= 0) {
                SendClientMessage(playerid, COL_RED, "  [Bagasi] Anda tidak memiliki barang tersebut di dalam tas!");
                UpdateTrunkUI(playerid);
                return 1;
            }

            new storePrompt[256];
            format(storePrompt, sizeof(storePrompt),
                "{FFFFFF}Berapa banyak {5814EE}%s{FFFFFF} yang ingin Anda simpan ke dalam bagasi mobil?\n\n{A0AEC0}(Jumlah di tas Anda: %d unit)",
                itName, curAmt);

            ShowPlayerDialog(playerid, DLG_TRUNK_STORE_QTY, DIALOG_STYLE_INPUT,
                "{5814EE}Simpan Barang ke Bagasi", storePrompt, "Simpan", "Batal");
        }
        return 1;
    }

    // 10. Tombol Aksi Kedua [ Buang Dari Bagasi / Buang Dari Tas ]
    if (playertextid == TD_TrunkBtnSecondary[playerid]) {
        new itId = gPlayerData[playerid][p_SelectedTrunkItemID];
        if (itId <= 0) {
            SendClientMessage(playerid, COL_RED, "  [Bagasi] Silakan pilih barang di daftar terlebih dahulu!");
            return 1;
        }

        if (itId == ITEM_KTP) {
            SendClientMessage(playerid, COL_RED, "  [Bagasi] Dokumen e-KTP tidak dapat dibuang!");
            return 1;
        }

        new itName[32];
        GetItemNameByID(itId, itName, sizeof(itName));

        new curAmt = (gPlayerData[playerid][p_TrunkActiveTab] == 0) ? (Trunk_GetItemCount(gPlayerData[playerid][p_TrunkVehDBID], itId)) : (Inventory_GetItemCount(playerid, itId));
        if (curAmt <= 0) {
            SendClientMessage(playerid, COL_RED, "  [Bagasi] Barang tidak ditemukan!");
            UpdateTrunkUI(playerid);
            return 1;
        }

        new dropPrompt[256];
        format(dropPrompt, sizeof(dropPrompt),
            "{FFFFFF}Berapa banyak {FA1E38}%s{FFFFFF} yang ingin Anda buang?\n\n{A0AEC0}(Jumlah saat ini: %d unit)",
            itName, curAmt);

        ShowPlayerDialog(playerid, DLG_TRUNK_DROP_QTY, DIALOG_STYLE_INPUT,
            "{FA1E38}Buang Barang", dropPrompt, "Buang", "Batal");
        return 1;
    }

    return 0;
}

stock HandleTrunkGlobalClick(playerid, Text:clickedid) {
    if (!gPlayerData[playerid][p_InTrunkUI]) return 0;

    if (clickedid == Text:INVALID_TEXT_DRAW) {
        HideTrunkUI(playerid);
        return 1;
    }
    return 0;
}

stock HandleTrunkDialog(playerid, dialogid, response, inputtext[]) {
    // 1. Ambil dari Bagasi ke Tas (DLG_TRUNK_TAKE_QTY)
    if (dialogid == DLG_TRUNK_TAKE_QTY) {
        if (!response) {
            if (gPlayerData[playerid][p_InTrunkUI]) UpdateTrunkUI(playerid);
            return 1;
        }

        new qty = strval(inputtext);
        new itId = gPlayerData[playerid][p_SelectedTrunkItemID];
        new vehDbId = gPlayerData[playerid][p_TrunkVehDBID];
        new curAmt = Trunk_GetItemCount(vehDbId, itId);

        if (qty <= 0 || qty > curAmt) {
            SendClientMessage(playerid, COL_RED, "  [Error] Jumlah barang yang diambil tidak valid!");
            if (gPlayerData[playerid][p_InTrunkUI]) UpdateTrunkUI(playerid);
            return 1;
        }

        if (itId >= ITEM_WEAPON_COLT45 && itId <= ITEM_WEAPON_AK47) {
            if (!Inventory_CanAddWeapon(playerid, itId)) {
                if (itId == ITEM_WEAPON_COLT45 || itId == ITEM_WEAPON_DEAGLE) {
                    SendClientMessage(playerid, COL_RED, "  [Bagasi] Anda sudah membawa 1 senjata jenis pistol di tas (Maksimal 1 Pistol)!");
                } else {
                    SendClientMessage(playerid, COL_RED, "  [Bagasi] Anda sudah membawa 1 senjata laras panjang di tas (Maksimal 1 Laras Panjang)!");
                }
                if (gPlayerData[playerid][p_InTrunkUI]) UpdateTrunkUI(playerid);
                return 1;
            }
        }

        Trunk_RemoveItem(vehDbId, itId, qty);
        Inventory_AddItem(playerid, itId, qty);

        new itName[32], charname[48], rpMsg[160];
        GetItemNameByID(itId, itName, sizeof(itName));
        GetCharName(playerid, charname);

        format(rpMsg, sizeof(rpMsg), "%s mengambil %dx %s dari bagasi mobil.", charname, qty, itName);
        DoProximityRaw(playerid, rpMsg, DIST_RP, COL_PURPLE);

        new msg[144];
        format(msg, sizeof(msg), "  [Bagasi] Anda mengambil {5814EE}%dx %s{FFFFFF} dari bagasi mobil.", qty, itName);
        SendClientMessage(playerid, COL_GREEN, msg);
        PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);

        if (gPlayerData[playerid][p_InTrunkUI]) UpdateTrunkUI(playerid);
        return 1;
    }

    // 2. Simpan dari Tas ke Bagasi (DLG_TRUNK_STORE_QTY)
    if (dialogid == DLG_TRUNK_STORE_QTY) {
        if (!response) {
            if (gPlayerData[playerid][p_InTrunkUI]) UpdateTrunkUI(playerid);
            return 1;
        }

        new qty = strval(inputtext);
        new itId = gPlayerData[playerid][p_SelectedTrunkItemID];
        new vehDbId = gPlayerData[playerid][p_TrunkVehDBID];
        new curAmt = Inventory_GetItemCount(playerid, itId);

        if (qty <= 0 || qty > curAmt) {
            SendClientMessage(playerid, COL_RED, "  [Error] Jumlah barang yang disimpan tidak valid!");
            if (gPlayerData[playerid][p_InTrunkUI]) UpdateTrunkUI(playerid);
            return 1;
        }

        Inventory_RemoveItem(playerid, itId, qty);
        Trunk_AddItem(vehDbId, itId, qty);

        new itName[32], charname[48], rpMsg[160];
        GetItemNameByID(itId, itName, sizeof(itName));
        GetCharName(playerid, charname);

        format(rpMsg, sizeof(rpMsg), "%s memasukkan %dx %s ke dalam bagasi mobil.", charname, qty, itName);
        DoProximityRaw(playerid, rpMsg, DIST_RP, COL_PURPLE);

        new msg[144];
        format(msg, sizeof(msg), "  [Bagasi] Anda menyimpan {5814EE}%dx %s{FFFFFF} ke dalam bagasi mobil.", qty, itName);
        SendClientMessage(playerid, COL_GREEN, msg);
        PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);

        if (gPlayerData[playerid][p_InTrunkUI]) UpdateTrunkUI(playerid);
        return 1;
    }

    // 3. Buang Barang (DLG_TRUNK_DROP_QTY)
    if (dialogid == DLG_TRUNK_DROP_QTY) {
        if (!response) {
            if (gPlayerData[playerid][p_InTrunkUI]) UpdateTrunkUI(playerid);
            return 1;
        }

        new qty = strval(inputtext);
        new itId = gPlayerData[playerid][p_SelectedTrunkItemID];
        new vehDbId = gPlayerData[playerid][p_TrunkVehDBID];
        new curAmt = (gPlayerData[playerid][p_TrunkActiveTab] == 0) ? (Trunk_GetItemCount(vehDbId, itId)) : (Inventory_GetItemCount(playerid, itId));

        if (qty <= 0 || qty > curAmt) {
            SendClientMessage(playerid, COL_RED, "  [Error] Jumlah barang yang dibuang tidak valid!");
            if (gPlayerData[playerid][p_InTrunkUI]) UpdateTrunkUI(playerid);
            return 1;
        }

        if (gPlayerData[playerid][p_TrunkActiveTab] == 0) {
            Trunk_RemoveItem(vehDbId, itId, qty);
        } else {
            Inventory_RemoveItem(playerid, itId, qty);
        }

        new itName[32], charname[48], rpMsg[160];
        GetItemNameByID(itId, itName, sizeof(itName));
        GetCharName(playerid, charname);

        format(rpMsg, sizeof(rpMsg), "%s membuang %dx %s.", charname, qty, itName);
        DoProximityRaw(playerid, rpMsg, DIST_RP, COL_PURPLE);

        new msg[144];
        format(msg, sizeof(msg), "  [Bagasi] Anda membuang {FA1E38}%dx %s{FFFFFF}.", qty, itName);
        SendClientMessage(playerid, COL_YELLOW, msg);
        PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);

        if (gPlayerData[playerid][p_InTrunkUI]) UpdateTrunkUI(playerid);
        return 1;
    }

    return 0;
}
