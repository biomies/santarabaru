#if defined _MODULE_HUD_MONEY_INC
    #endinput
#endif
#define _MODULE_HUD_MONEY_INC

// ============================================================
//  SantaraBaru Roleplay — Custom Top-Right Luxury HUD (#1D1D1D & #E69958)
// ============================================================

new PlayerText:TD_HudBox[MAX_PLAYERS]       = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_HudBorder[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_HudBrand[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_HudName[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_HudMoney[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_HudStats[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};

stock DestroyPlayerMoneyHUD(playerid) {
    if (TD_HudBox[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_HudBox[playerid]);
        TD_HudBox[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_HudBorder[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_HudBorder[playerid]);
        TD_HudBorder[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_HudBrand[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_HudBrand[playerid]);
        TD_HudBrand[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_HudName[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_HudName[playerid]);
        TD_HudName[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_HudMoney[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_HudMoney[playerid]);
        TD_HudMoney[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_HudStats[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_HudStats[playerid]);
        TD_HudStats[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
}

stock CreatePlayerMoneyHUD(playerid) {
    DestroyPlayerMoneyHUD(playerid);

    // 1. Background Cover Box Solid (#1D1D1D Matte - Menutupi seluruh icon senjata & uang bawaan)
    TD_HudBox[playerid] = CreatePlayerTextDraw(playerid, 470.0, 10.0, "_");
    PlayerTextDrawUseBox(playerid, TD_HudBox[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_HudBox[playerid], 0x1D1D1DFF);
    PlayerTextDrawTextSize(playerid, TD_HudBox[playerid], 640.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_HudBox[playerid], 0.0, 10.0); // Tinggi 95px (Y: 10 s/d 105)
    PlayerTextDrawSetSelectable(playerid, TD_HudBox[playerid], 0);

    // 2. Left Border Accent Bar (#E69958 Warm Amber)
    TD_HudBorder[playerid] = CreatePlayerTextDraw(playerid, 470.0, 10.0, "_");
    PlayerTextDrawUseBox(playerid, TD_HudBorder[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_HudBorder[playerid], 0xE69958FF);
    PlayerTextDrawTextSize(playerid, TD_HudBorder[playerid], 473.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_HudBorder[playerid], 0.0, 10.0);
    PlayerTextDrawSetSelectable(playerid, TD_HudBorder[playerid], 0);

    // 3. Baris 1: ID Karakter (Paling Atas)
    TD_HudStats[playerid] = CreatePlayerTextDraw(playerid, 625.0, 15.0, "ID: 0");
    PlayerTextDrawFont(playerid, TD_HudStats[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_HudStats[playerid], 0.18, 1.0);
    PlayerTextDrawColor(playerid, TD_HudStats[playerid], 0xFFFFFFFF);
    PlayerTextDrawAlignment(playerid, TD_HudStats[playerid], 3); // Rata Kanan
    PlayerTextDrawSetOutline(playerid, TD_HudStats[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_HudStats[playerid], 0);

    // 4. Baris 2: Nama Karakter (Font 2, Bersih)
    TD_HudName[playerid] = CreatePlayerTextDraw(playerid, 625.0, 31.0, "Karakter");
    PlayerTextDrawFont(playerid, TD_HudName[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_HudName[playerid], 0.20, 1.15);
    PlayerTextDrawColor(playerid, TD_HudName[playerid], 0xFFFFFFFF);
    PlayerTextDrawAlignment(playerid, TD_HudName[playerid], 3); // Rata Kanan
    PlayerTextDrawSetOutline(playerid, TD_HudName[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_HudName[playerid], 0);

    // 5. Baris 3: Uang Rupiah (Tebal, Bersih)
    TD_HudMoney[playerid] = CreatePlayerTextDraw(playerid, 625.0, 50.0, "Rp 0");
    PlayerTextDrawFont(playerid, TD_HudMoney[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_HudMoney[playerid], 0.26, 1.4);
    PlayerTextDrawColor(playerid, TD_HudMoney[playerid], 0xFFFFFFFF);
    PlayerTextDrawAlignment(playerid, TD_HudMoney[playerid], 3); // Rata Kanan
    PlayerTextDrawSetOutline(playerid, TD_HudMoney[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_HudMoney[playerid], 0);

    // 6. Baris 4: Server Brand & Jumlah Pemain Online (Paling Bawah)
    TD_HudBrand[playerid] = CreatePlayerTextDraw(playerid, 625.0, 71.0, "SANTARA ROLEPLAY  1/100");
    PlayerTextDrawFont(playerid, TD_HudBrand[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_HudBrand[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_HudBrand[playerid], 0xCCCCCCFF);
    PlayerTextDrawAlignment(playerid, TD_HudBrand[playerid], 3); // Rata Kanan
    PlayerTextDrawSetOutline(playerid, TD_HudBrand[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_HudBrand[playerid], 0);
}

stock ShowPlayerMoneyHUD(playerid) {
    if (TD_HudBox[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_HudBox[playerid]);
    if (TD_HudBorder[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_HudBorder[playerid]);
    if (TD_HudStats[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_HudStats[playerid]);
    if (TD_HudName[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_HudName[playerid]);
    if (TD_HudMoney[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_HudMoney[playerid]);
    if (TD_HudBrand[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_HudBrand[playerid]);
}

stock HidePlayerMoneyHUD(playerid) {
    if (TD_HudBox[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawHide(playerid, TD_HudBox[playerid]);
    if (TD_HudBorder[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawHide(playerid, TD_HudBorder[playerid]);
    if (TD_HudStats[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawHide(playerid, TD_HudStats[playerid]);
    if (TD_HudName[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawHide(playerid, TD_HudName[playerid]);
    if (TD_HudMoney[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawHide(playerid, TD_HudMoney[playerid]);
    if (TD_HudBrand[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawHide(playerid, TD_HudBrand[playerid]);
}

stock UpdatePlayerMoneyHUD(playerid) {
    if (TD_HudMoney[playerid] == PlayerText:INVALID_TEXT_DRAW) return;

    // 1. Baris 1: ID Karakter
    new idStr[32];
    format(idStr, sizeof(idStr), "~y~ID:~w~ %d", playerid);
    PlayerTextDrawSetString(playerid, TD_HudStats[playerid], idStr);

    // 2. Baris 2: Nama Karakter
    new charname[48];
    GetCharName(playerid, charname);
    PlayerTextDrawSetString(playerid, TD_HudName[playerid], charname);

    // 3. Baris 3: Uang Rupiah (Contoh: "Rp 500.000")
    new rup[32], str[64];
    FormatRupiah(gPlayerData[playerid][p_Cash], rup, sizeof(rup));
    format(str, sizeof(str), "~y~Rp ~w~%s", rup);
    PlayerTextDrawSetString(playerid, TD_HudMoney[playerid], str);

    // 4. Baris 4: Brand & Jumlah Pemain Online (Contoh: "SANTARA ROLEPLAY  1/100")
    new onlineCount = 0;
    for (new i = 0; i < MAX_PLAYERS; i++) {
        if (IsPlayerConnected(i)) onlineCount++;
    }
    new brandStr[64];
    format(brandStr, sizeof(brandStr), "~w~SANTARA ~y~RP  ~w~%d/%d", onlineCount, GetMaxPlayers());
    PlayerTextDrawSetString(playerid, TD_HudBrand[playerid], brandStr);
}

stock GivePlayerMoneyEx(playerid, amount) {
    gPlayerData[playerid][p_Cash] += amount;
    UpdatePlayerMoneyHUD(playerid);
}

stock SetPlayerMoneyEx(playerid, amount) {
    gPlayerData[playerid][p_Cash] = amount;
    UpdatePlayerMoneyHUD(playerid);
}
