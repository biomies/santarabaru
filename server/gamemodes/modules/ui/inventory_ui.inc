#if defined _MODULE_INVENTORY_UI_INC
    #endinput
#endif
#define _MODULE_INVENTORY_UI_INC

// ============================================================
//  SantaraBaru Roleplay - Right-Aligned Modern Inventory GUI (/inv)
//  Clean Minimalist Dark Theme with Electric Purple Accent & Top Red [X]
// ============================================================

#define INV_SLOTS_PER_PAGE 10

// Colors from Reference Design
#define COLOR_INV_BG       0x1E1E2EFF  // Dark Indigo Background
#define COLOR_INV_PURPLE   0x5814EEFF  // Electric Purple Accent
#define COLOR_INV_RED      0xFA1E38FF  // Vibrant Red Delete & [X] Close Button
#define COLOR_INV_SLATE    0x3E3E44EE  // Dark Slate Inactive/Button Tile
#define COLOR_INV_EMPTY    0x34343AEE  // Dark Slate Empty Slot

new PlayerText:TD_InvMainBox[MAX_PLAYERS]        = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_InvTopBar[MAX_PLAYERS]         = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_InvCloseBtn[MAX_PLAYERS]       = {PlayerText:INVALID_TEXT_DRAW, ...};

// Header Tile (Tas Saya)
new PlayerText:TD_InvTitleTile[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};

// 10x Item Slots
new PlayerText:TD_InvSlotBox[MAX_PLAYERS][INV_SLOTS_PER_PAGE];

// Page Indicator
new PlayerText:TD_InvPageText[MAX_PLAYERS]       = {PlayerText:INVALID_TEXT_DRAW, ...};

// Action Buttons (Gunakan & Buang Dari Tas)
new PlayerText:TD_InvBtnUse[MAX_PLAYERS]         = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_InvBtnDrop[MAX_PLAYERS]        = {PlayerText:INVALID_TEXT_DRAW, ...};

// Navigation Buttons (Naik, Turun, < Sebelum, Selanjutnya >)
new PlayerText:TD_InvUpBtn[MAX_PLAYERS]          = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_InvDownBtn[MAX_PLAYERS]        = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_InvPrevBtn[MAX_PLAYERS]        = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_InvNextBtn[MAX_PLAYERS]        = {PlayerText:INVALID_TEXT_DRAW, ...};

stock DestroyPlayerInventoryTextDraws(playerid) {
    if (TD_InvMainBox[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_InvMainBox[playerid]);
        TD_InvMainBox[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_InvTopBar[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_InvTopBar[playerid]);
        TD_InvTopBar[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_InvCloseBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_InvCloseBtn[playerid]);
        TD_InvCloseBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (TD_InvTitleTile[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_InvTitleTile[playerid]);
        TD_InvTitleTile[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    for (new s = 0; s < INV_SLOTS_PER_PAGE; s++) {
        if (TD_InvSlotBox[playerid][s] != PlayerText:INVALID_TEXT_DRAW) {
            PlayerTextDrawDestroy(playerid, TD_InvSlotBox[playerid][s]);
            TD_InvSlotBox[playerid][s] = PlayerText:INVALID_TEXT_DRAW;
        }
    }

    if (TD_InvPageText[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_InvPageText[playerid]);
        TD_InvPageText[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (TD_InvBtnUse[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_InvBtnUse[playerid]);
        TD_InvBtnUse[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_InvBtnDrop[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_InvBtnDrop[playerid]);
        TD_InvBtnDrop[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (TD_InvUpBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_InvUpBtn[playerid]);
        TD_InvUpBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_InvDownBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_InvDownBtn[playerid]);
        TD_InvDownBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_InvPrevBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_InvPrevBtn[playerid]);
        TD_InvPrevBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_InvNextBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_InvNextBtn[playerid]);
        TD_InvNextBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
}

stock CreatePlayerInventoryTextDraws(playerid) {
    DestroyPlayerInventoryTextDraws(playerid);

    // 1. Background Frame (Right side: X: 430.0 .. 620.0, Y: 78.0 .. 360.0)
    TD_InvMainBox[playerid] = CreatePlayerTextDraw(playerid, 430.0, 78.0, "_");
    PlayerTextDrawUseBox(playerid, TD_InvMainBox[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_InvMainBox[playerid], COLOR_INV_BG);
    PlayerTextDrawTextSize(playerid, TD_InvMainBox[playerid], 620.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_InvMainBox[playerid], 0.0, 31.0);
    PlayerTextDrawSetSelectable(playerid, TD_InvMainBox[playerid], false);

    // 2. Top Accent Line (Electric Purple #5814EEFF, X: 430.0 .. 602.0, Y: 78.0)
    TD_InvTopBar[playerid] = CreatePlayerTextDraw(playerid, 430.0, 78.0, "_");
    PlayerTextDrawUseBox(playerid, TD_InvTopBar[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_InvTopBar[playerid], COLOR_INV_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_InvTopBar[playerid], 602.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_InvTopBar[playerid], 0.0, 0.75);
    PlayerTextDrawSetSelectable(playerid, TD_InvTopBar[playerid], false);

    // 3. Top-Right Red Close Button [X] (Center X: 611.0, Y: 77.0)
    TD_InvCloseBtn[playerid] = CreatePlayerTextDraw(playerid, 611.0, 77.0, "X");
    PlayerTextDrawFont(playerid, TD_InvCloseBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_InvCloseBtn[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_InvCloseBtn[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_InvCloseBtn[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_InvCloseBtn[playerid], COLOR_INV_RED);
    PlayerTextDrawTextSize(playerid, TD_InvCloseBtn[playerid], 10.0, 18.0);
    PlayerTextDrawAlignment(playerid, TD_InvCloseBtn[playerid], 2); // Center
    PlayerTextDrawSetOutline(playerid, TD_InvCloseBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_InvCloseBtn[playerid], true);

    // 4. Header Title Tile [ Tas Saya ] (Center X: 525.0, Y: 90.0, Width: 170.0)
    TD_InvTitleTile[playerid] = CreatePlayerTextDraw(playerid, 525.0, 90.0, "Tas Saya");
    PlayerTextDrawFont(playerid, TD_InvTitleTile[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_InvTitleTile[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_InvTitleTile[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_InvTitleTile[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_InvTitleTile[playerid], COLOR_INV_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_InvTitleTile[playerid], 14.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_InvTitleTile[playerid], 2); // Center
    PlayerTextDrawSetOutline(playerid, TD_InvTitleTile[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_InvTitleTile[playerid], false);

    // 5. 10x Item Slot Tiles (Y: 110.0 .. 250.0, Left Edge: 440.0, Right: 610.0)
    for (new s = 0; s < INV_SLOTS_PER_PAGE; s++) {
        new Float:slotY = 110.0 + (s * 14.5);
        TD_InvSlotBox[playerid][s] = CreatePlayerTextDraw(playerid, 440.0, slotY, "Kosong");
        PlayerTextDrawFont(playerid, TD_InvSlotBox[playerid][s], 1);
        PlayerTextDrawLetterSize(playerid, TD_InvSlotBox[playerid][s], 0.16, 0.90);
        PlayerTextDrawColor(playerid, TD_InvSlotBox[playerid][s], 0xFFFFFFFF);
        PlayerTextDrawUseBox(playerid, TD_InvSlotBox[playerid][s], true);
        PlayerTextDrawBoxColor(playerid, TD_InvSlotBox[playerid][s], COLOR_INV_EMPTY);
        PlayerTextDrawTextSize(playerid, TD_InvSlotBox[playerid][s], 610.0, 12.0);
        PlayerTextDrawSetOutline(playerid, TD_InvSlotBox[playerid][s], 1);
        PlayerTextDrawSetSelectable(playerid, TD_InvSlotBox[playerid][s], true);
    }

    // 6. Page Indicator (Center X: 525.0, Y: 259.0)
    TD_InvPageText[playerid] = CreatePlayerTextDraw(playerid, 525.0, 259.0, "Hal 1/1");
    PlayerTextDrawFont(playerid, TD_InvPageText[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_InvPageText[playerid], 0.15, 0.85);
    PlayerTextDrawColor(playerid, TD_InvPageText[playerid], 0xCCCCCCFF);
    PlayerTextDrawAlignment(playerid, TD_InvPageText[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_InvPageText[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_InvPageText[playerid], false);

    // 7. Primary Action Button (Gunakan) (Center X: 525.0, Y: 275.0)
    TD_InvBtnUse[playerid] = CreatePlayerTextDraw(playerid, 525.0, 275.0, "Gunakan");
    PlayerTextDrawFont(playerid, TD_InvBtnUse[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_InvBtnUse[playerid], 0.17, 1.05);
    PlayerTextDrawColor(playerid, TD_InvBtnUse[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_InvBtnUse[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_InvBtnUse[playerid], COLOR_INV_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_InvBtnUse[playerid], 15.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_InvBtnUse[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_InvBtnUse[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_InvBtnUse[playerid], true);

    // 8. Secondary Action Button (Buang Dari Tas) (Center X: 525.0, Y: 295.0)
    TD_InvBtnDrop[playerid] = CreatePlayerTextDraw(playerid, 525.0, 295.0, "Buang Dari Tas");
    PlayerTextDrawFont(playerid, TD_InvBtnDrop[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_InvBtnDrop[playerid], 0.17, 1.05);
    PlayerTextDrawColor(playerid, TD_InvBtnDrop[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_InvBtnDrop[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_InvBtnDrop[playerid], COLOR_INV_RED);
    PlayerTextDrawTextSize(playerid, TD_InvBtnDrop[playerid], 15.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_InvBtnDrop[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_InvBtnDrop[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_InvBtnDrop[playerid], true);

    // 9. Navigation Row 1: Naik / Turun (Y: 316.0)
    TD_InvUpBtn[playerid] = CreatePlayerTextDraw(playerid, 481.0, 316.0, "Naik");
    PlayerTextDrawFont(playerid, TD_InvUpBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_InvUpBtn[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_InvUpBtn[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_InvUpBtn[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_InvUpBtn[playerid], COLOR_INV_SLATE);
    PlayerTextDrawTextSize(playerid, TD_InvUpBtn[playerid], 14.0, 82.0);
    PlayerTextDrawAlignment(playerid, TD_InvUpBtn[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_InvUpBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_InvUpBtn[playerid], true);

    TD_InvDownBtn[playerid] = CreatePlayerTextDraw(playerid, 569.0, 316.0, "Turun");
    PlayerTextDrawFont(playerid, TD_InvDownBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_InvDownBtn[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_InvDownBtn[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_InvDownBtn[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_InvDownBtn[playerid], COLOR_INV_SLATE);
    PlayerTextDrawTextSize(playerid, TD_InvDownBtn[playerid], 14.0, 82.0);
    PlayerTextDrawAlignment(playerid, TD_InvDownBtn[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_InvDownBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_InvDownBtn[playerid], true);

    // 10. Navigation Row 2: < Sebelum / Selanjutnya > (Y: 334.0)
    TD_InvPrevBtn[playerid] = CreatePlayerTextDraw(playerid, 481.0, 334.0, "< Sebelum");
    PlayerTextDrawFont(playerid, TD_InvPrevBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_InvPrevBtn[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_InvPrevBtn[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_InvPrevBtn[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_InvPrevBtn[playerid], COLOR_INV_SLATE);
    PlayerTextDrawTextSize(playerid, TD_InvPrevBtn[playerid], 14.0, 82.0);
    PlayerTextDrawAlignment(playerid, TD_InvPrevBtn[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_InvPrevBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_InvPrevBtn[playerid], true);

    TD_InvNextBtn[playerid] = CreatePlayerTextDraw(playerid, 569.0, 334.0, "Selanjutnya >");
    PlayerTextDrawFont(playerid, TD_InvNextBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_InvNextBtn[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_InvNextBtn[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_InvNextBtn[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_InvNextBtn[playerid], COLOR_INV_SLATE);
    PlayerTextDrawTextSize(playerid, TD_InvNextBtn[playerid], 14.0, 82.0);
    PlayerTextDrawAlignment(playerid, TD_InvNextBtn[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_InvNextBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_InvNextBtn[playerid], true);
}

stock UpdateInventoryUI(playerid) {
    if (!gPlayerData[playerid][p_InInventoryUI]) return;

    Inventory_LoadPlayerItems(playerid);

    new totalItems = gPlayerData[playerid][p_InvItemCount];
    new totalPages = (totalItems + INV_SLOTS_PER_PAGE - 1) / INV_SLOTS_PER_PAGE;
    if (totalPages <= 0) totalPages = 1;

    if (gPlayerData[playerid][p_InvCurrentPage] >= totalPages) {
        gPlayerData[playerid][p_InvCurrentPage] = totalPages - 1;
    }
    if (gPlayerData[playerid][p_InvCurrentPage] < 0) {
        gPlayerData[playerid][p_InvCurrentPage] = 0;
    }

    new page = gPlayerData[playerid][p_InvCurrentPage];

    // Update Page Indicator
    new pageStr[32];
    format(pageStr, sizeof(pageStr), "Hal %d/%d", page + 1, totalPages);
    PlayerTextDrawSetString(playerid, TD_InvPageText[playerid], pageStr);

    // Update 10 Item Slots
    for (new s = 0; s < INV_SLOTS_PER_PAGE; s++) {
        new itemIdxInList = (page * INV_SLOTS_PER_PAGE) + s;
        if (itemIdxInList < totalItems) {
            new itId = gPlayerData[playerid][p_InvSlotItemID][itemIdxInList];
            new itAmt = gPlayerData[playerid][p_InvSlotAmount][itemIdxInList];
            new itName[32];
            GetItemNameByID(itId, itName, sizeof(itName));

            new slotStr[64];
            if (itemIdxInList == gPlayerData[playerid][p_SelectedInvSlot]) {
                format(slotStr, sizeof(slotStr), " > %s (%dx)", itName, itAmt);
                PlayerTextDrawBoxColor(playerid, TD_InvSlotBox[playerid][s], COLOR_INV_PURPLE); // Active Electric Purple
            } else {
                format(slotStr, sizeof(slotStr), " %s (%dx)", itName, itAmt);
                PlayerTextDrawBoxColor(playerid, TD_InvSlotBox[playerid][s], COLOR_INV_SLATE);
            }
            PlayerTextDrawSetString(playerid, TD_InvSlotBox[playerid][s], slotStr);
            PlayerTextDrawShow(playerid, TD_InvSlotBox[playerid][s]);
        } else {
            PlayerTextDrawSetString(playerid, TD_InvSlotBox[playerid][s], " Kosong");
            PlayerTextDrawBoxColor(playerid, TD_InvSlotBox[playerid][s], COLOR_INV_EMPTY);
            PlayerTextDrawShow(playerid, TD_InvSlotBox[playerid][s]);
        }
    }

    // Refresh selected item ID
    new selSlot = gPlayerData[playerid][p_SelectedInvSlot];
    if (selSlot >= 0 && selSlot < totalItems) {
        gPlayerData[playerid][p_SelectedInvItemID] = gPlayerData[playerid][p_InvSlotItemID][selSlot];
    } else {
        gPlayerData[playerid][p_SelectedInvSlot] = -1;
        gPlayerData[playerid][p_SelectedInvItemID] = 0;
    }

    // Pastikan elements tetap aktif
    PlayerTextDrawShow(playerid, TD_InvCloseBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_InvTitleTile[playerid]);
    PlayerTextDrawShow(playerid, TD_InvBtnUse[playerid]);
    PlayerTextDrawShow(playerid, TD_InvBtnDrop[playerid]);
}

stock ShowInventoryUI(playerid) {
    if (!CheckSpawned(playerid)) return 0;

    // Sembunyikan HUD pojok kanan atas sementara waktu
    DestroyPlayerMoneyHUD(playerid);

    CreatePlayerInventoryTextDraws(playerid);
    gPlayerData[playerid][p_InInventoryUI] = true;
    gPlayerData[playerid][p_InvCurrentPage] = 0;

    Inventory_LoadPlayerItems(playerid);
    if (gPlayerData[playerid][p_InvItemCount] > 0) {
        gPlayerData[playerid][p_SelectedInvSlot] = 0;
        gPlayerData[playerid][p_SelectedInvItemID] = gPlayerData[playerid][p_InvSlotItemID][0];
    } else {
        gPlayerData[playerid][p_SelectedInvSlot] = -1;
        gPlayerData[playerid][p_SelectedInvItemID] = 0;
    }

    // Tampilkan TextDraws
    PlayerTextDrawShow(playerid, TD_InvMainBox[playerid]);
    PlayerTextDrawShow(playerid, TD_InvTopBar[playerid]);
    PlayerTextDrawShow(playerid, TD_InvCloseBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_InvTitleTile[playerid]);

    for (new s = 0; s < INV_SLOTS_PER_PAGE; s++) {
        PlayerTextDrawShow(playerid, TD_InvSlotBox[playerid][s]);
    }

    PlayerTextDrawShow(playerid, TD_InvPageText[playerid]);
    PlayerTextDrawShow(playerid, TD_InvBtnUse[playerid]);
    PlayerTextDrawShow(playerid, TD_InvBtnDrop[playerid]);
    PlayerTextDrawShow(playerid, TD_InvUpBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_InvDownBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_InvPrevBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_InvNextBtn[playerid]);

    UpdateInventoryUI(playerid);

    // Aktifkan mode kursor mouse dengan highlight Electric Purple
    SelectTextDraw(playerid, COLOR_INV_PURPLE);
    PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
    return 1;
}

stock HideInventoryUI(playerid) {
    if (!gPlayerData[playerid][p_InInventoryUI]) return;

    gPlayerData[playerid][p_InInventoryUI] = false;
    CancelSelectTextDraw(playerid);

    DestroyPlayerInventoryTextDraws(playerid);
    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);

    // Kembalikan & segarkan HUD
    CreatePlayerMoneyHUD(playerid);
    UpdatePlayerMoneyHUD(playerid);
    ShowPlayerMoneyHUD(playerid);
}

stock HandleInventoryClick(playerid, PlayerText:playertextid) {
    if (!gPlayerData[playerid][p_InInventoryUI]) return 0;

    // 1. TOMBOL [X] MERAH TUTUP
    if (playertextid == TD_InvCloseBtn[playerid]) {
        HideInventoryUI(playerid);
        return 1;
    }

    new totalItems = gPlayerData[playerid][p_InvItemCount];

    // 2. Tombol NAIK (UP)
    if (playertextid == TD_InvUpBtn[playerid]) {
        if (totalItems > 0 && gPlayerData[playerid][p_SelectedInvSlot] > 0) {
            gPlayerData[playerid][p_SelectedInvSlot]--;
            if (gPlayerData[playerid][p_SelectedInvSlot] < gPlayerData[playerid][p_InvCurrentPage] * INV_SLOTS_PER_PAGE) {
                if (gPlayerData[playerid][p_InvCurrentPage] > 0) {
                    gPlayerData[playerid][p_InvCurrentPage]--;
                }
            }
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
            UpdateInventoryUI(playerid);
        }
        return 1;
    }

    // 3. Tombol TURUN (DOWN)
    if (playertextid == TD_InvDownBtn[playerid]) {
        if (totalItems > 0 && gPlayerData[playerid][p_SelectedInvSlot] < totalItems - 1) {
            gPlayerData[playerid][p_SelectedInvSlot]++;
            if (gPlayerData[playerid][p_SelectedInvSlot] >= (gPlayerData[playerid][p_InvCurrentPage] + 1) * INV_SLOTS_PER_PAGE) {
                gPlayerData[playerid][p_InvCurrentPage]++;
            }
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
            UpdateInventoryUI(playerid);
        }
        return 1;
    }

    // 4. Tombol < SEBELUM (PREV)
    if (playertextid == TD_InvPrevBtn[playerid]) {
        if (gPlayerData[playerid][p_InvCurrentPage] > 0) {
            gPlayerData[playerid][p_InvCurrentPage]--;
            gPlayerData[playerid][p_SelectedInvSlot] = gPlayerData[playerid][p_InvCurrentPage] * INV_SLOTS_PER_PAGE;
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
            UpdateInventoryUI(playerid);
        }
        return 1;
    }

    // 5. Tombol SELANJUTNYA > (NEXT)
    if (playertextid == TD_InvNextBtn[playerid]) {
        new totalPages = (totalItems + INV_SLOTS_PER_PAGE - 1) / INV_SLOTS_PER_PAGE;
        if (gPlayerData[playerid][p_InvCurrentPage] < totalPages - 1) {
            gPlayerData[playerid][p_InvCurrentPage]++;
            gPlayerData[playerid][p_SelectedInvSlot] = gPlayerData[playerid][p_InvCurrentPage] * INV_SLOTS_PER_PAGE;
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
            UpdateInventoryUI(playerid);
        }
        return 1;
    }

    // 6. Klik Slot Barang Langsung (0 - 9)
    for (new s = 0; s < INV_SLOTS_PER_PAGE; s++) {
        if (playertextid == TD_InvSlotBox[playerid][s]) {
            new itemIdxInList = (gPlayerData[playerid][p_InvCurrentPage] * INV_SLOTS_PER_PAGE) + s;
            if (itemIdxInList < totalItems) {
                gPlayerData[playerid][p_SelectedInvSlot] = itemIdxInList;
                PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
                UpdateInventoryUI(playerid);
            }
            return 1;
        }
    }

    // 7. Tombol Aksi Utama [ Gunakan ]
    if (playertextid == TD_InvBtnUse[playerid]) {
        new itId = gPlayerData[playerid][p_SelectedInvItemID];
        if (itId <= 0 || !Inventory_HasItem(playerid, itId)) {
            SendClientMessage(playerid, COL_RED, "  [Inventory] Silakan pilih barang di daftar terlebih dahulu!");
            return 1;
        }

        UseInventoryItem(playerid, itId);
        UpdateInventoryUI(playerid);
        return 1;
    }

    // 8. Tombol Aksi Kedua [ Buang Dari Tas ]
    if (playertextid == TD_InvBtnDrop[playerid]) {
        new itId = gPlayerData[playerid][p_SelectedInvItemID];
        if (itId <= 0 || !Inventory_HasItem(playerid, itId)) {
            SendClientMessage(playerid, COL_RED, "  [Inventory] Silakan pilih barang di daftar terlebih dahulu!");
            return 1;
        }

        if (itId == ITEM_KTP || itId == ITEM_SIM_A || itId == ITEM_SIM_B || itId == ITEM_SIM_C) {
            SendClientMessage(playerid, COL_RED, "  [Inventory] Dokumen resmi (e-KTP / SIM) tidak dapat dibuang!");
            return 1;
        }

        new itName[32];
        GetItemNameByID(itId, itName, sizeof(itName));
        new curAmt = Inventory_GetItemCount(playerid, itId);

        new dropPrompt[256];
        format(dropPrompt, sizeof(dropPrompt),
            "{FFFFFF}Berapa banyak {FA1E38}%s{FFFFFF} yang ingin Anda buang?\n\n{A0AEC0}(Jumlah saat ini: %d unit)",
            itName, curAmt);

        ShowPlayerDialog(playerid, DLG_INV_DROP_QTY, DIALOG_STYLE_INPUT,
            "{FA1E38}Buang Barang dari Tas", dropPrompt, "Buang", "Batal");
        return 1;
    }

    return 0;
}

stock HandleInventoryGlobalClick(playerid, Text:clickedid) {
    if (!gPlayerData[playerid][p_InInventoryUI]) return 0;

    // Menekan ESC / Klik di luar
    if (clickedid == Text:INVALID_TEXT_DRAW) {
        HideInventoryUI(playerid);
        return 1;
    }
    return 0;
}
