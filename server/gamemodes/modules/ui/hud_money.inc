#if defined _MODULE_HUD_MONEY_INC
    #endinput
#endif
#define _MODULE_HUD_MONEY_INC

// ============================================================
//  SantaraBaru Roleplay - Top-Right Identity HUD & Vitality Bars
//  Dark Indigo (#1E1E2E) & Electric Purple (#5814EE) Theme
// ============================================================

#define COLOR_HUD_BG       0x1E1E2EFF  // Dark Indigo Background
#define COLOR_HUD_PURPLE   0x5814EEFF  // Electric Purple Top Accent Bar
#define COLOR_HUD_LOGO     0x2D2748EE  // Dark Indigo/Violet Watermark S Logo

// --- Top-Right Identity HUD TextDraws ---
new PlayerText:TD_HudBox[MAX_PLAYERS]          = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_HudTopBar[MAX_PLAYERS]       = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_HudLogo[MAX_PLAYERS]         = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_HudID[MAX_PLAYERS]           = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_HudName[MAX_PLAYERS]         = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_HudMoney[MAX_PLAYERS]        = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_HudJob[MAX_PLAYERS]          = {PlayerText:INVALID_TEXT_DRAW, ...};

// --- Bottom-Left Minimalist Status Bars TextDraws (Thirsty & Hunger) ---
#define STATUS_BAR_START_X  26.0
#define STATUS_BAR_END_X    94.0

new PlayerText:TD_StatusBgThirst[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_StatusBgHunger[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};

new PlayerText:TD_StatusFillThirst[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_StatusFillHunger[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};

new PlayerText:TD_StatusTxtThirst[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_StatusTxtHunger[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};

stock GetPlayerJobName(playerid, jobName[], len = 32) {
    new query[128];
    format(query, sizeof(query), "SELECT `name` FROM `jobs` WHERE `id` = %d LIMIT 1", gPlayerData[playerid][p_Job]);
    new DBResult:res = DB_ExecuteQuery(gDB, query);
    if (res && DB_GetRowCount(res) > 0) {
        DB_GetFieldStringByName(res, "name", jobName, len);
        DB_FreeResultSet(res);
        return 1;
    }
    if (res) DB_FreeResultSet(res);
    format(jobName, len, "Pengangguran");
    return 1;
}

stock DestroyPlayerMoneyHUD(playerid) {
    // 1. Destroy Top-Right HUD
    if (TD_HudBox[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_HudBox[playerid]);
        TD_HudBox[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_HudTopBar[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_HudTopBar[playerid]);
        TD_HudTopBar[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_HudLogo[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_HudLogo[playerid]);
        TD_HudLogo[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_HudID[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_HudID[playerid]);
        TD_HudID[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_HudName[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_HudName[playerid]);
        TD_HudName[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_HudMoney[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_HudMoney[playerid]);
        TD_HudMoney[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_HudJob[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_HudJob[playerid]);
        TD_HudJob[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    // 2. Destroy Bottom-Left Status Bars
    if (TD_StatusBgThirst[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_StatusBgThirst[playerid]);
        TD_StatusBgThirst[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_StatusBgHunger[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_StatusBgHunger[playerid]);
        TD_StatusBgHunger[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (TD_StatusFillThirst[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_StatusFillThirst[playerid]);
        TD_StatusFillThirst[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_StatusFillHunger[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_StatusFillHunger[playerid]);
        TD_StatusFillHunger[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (TD_StatusTxtThirst[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_StatusTxtThirst[playerid]);
        TD_StatusTxtThirst[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_StatusTxtHunger[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_StatusTxtHunger[playerid]);
        TD_StatusTxtHunger[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
}

stock CreatePlayerMoneyHUD(playerid) {
    DestroyPlayerMoneyHUD(playerid);

    // ============================================================
    //  A. Top-Right Identity HUD (X: 470.0 .. 630.0, Y: 12.0 .. 86.0)
    // ============================================================

    // 1. Background Box (Dark Indigo #1E1E2EFF)
    TD_HudBox[playerid] = CreatePlayerTextDraw(playerid, 470.0, 12.0, "_");
    PlayerTextDrawUseBox(playerid, TD_HudBox[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_HudBox[playerid], COLOR_HUD_BG);
    PlayerTextDrawTextSize(playerid, TD_HudBox[playerid], 630.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_HudBox[playerid], 0.0, 8.0);
    PlayerTextDrawSetSelectable(playerid, TD_HudBox[playerid], false);

    // 2. Top Accent Bar (Electric Purple #5814EEFF)
    TD_HudTopBar[playerid] = CreatePlayerTextDraw(playerid, 470.0, 12.0, "_");
    PlayerTextDrawUseBox(playerid, TD_HudTopBar[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_HudTopBar[playerid], COLOR_HUD_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_HudTopBar[playerid], 630.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_HudTopBar[playerid], 0.0, 0.8);
    PlayerTextDrawSetSelectable(playerid, TD_HudTopBar[playerid], false);

    // 3. Watermark S Logo (Left Side of HUD)
    TD_HudLogo[playerid] = CreatePlayerTextDraw(playerid, 492.0, 23.0, "S");
    PlayerTextDrawFont(playerid, TD_HudLogo[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_HudLogo[playerid], 1.25, 4.8);
    PlayerTextDrawColor(playerid, TD_HudLogo[playerid], COLOR_HUD_LOGO);
    PlayerTextDrawAlignment(playerid, TD_HudLogo[playerid], 2);
    PlayerTextDrawSetSelectable(playerid, TD_HudLogo[playerid], false);

    // 4. Line 1: ID : 0 (Right-Aligned)
    TD_HudID[playerid] = CreatePlayerTextDraw(playerid, 622.0, 24.0, "ID : 0");
    PlayerTextDrawFont(playerid, TD_HudID[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_HudID[playerid], 0.18, 0.95);
    PlayerTextDrawColor(playerid, TD_HudID[playerid], 0xFFFFFFFF);
    PlayerTextDrawAlignment(playerid, TD_HudID[playerid], 3); // Right-Aligned
    PlayerTextDrawSetOutline(playerid, TD_HudID[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_HudID[playerid], false);

    // 5. Line 2: [Nama Pemain] (Right-Aligned)
    TD_HudName[playerid] = CreatePlayerTextDraw(playerid, 622.0, 36.0, "Nama Pemain");
    PlayerTextDrawFont(playerid, TD_HudName[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_HudName[playerid], 0.20, 1.05);
    PlayerTextDrawColor(playerid, TD_HudName[playerid], 0xFFFFFFFF);
    PlayerTextDrawAlignment(playerid, TD_HudName[playerid], 3); // Right-Aligned
    PlayerTextDrawSetOutline(playerid, TD_HudName[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_HudName[playerid], false);

    // 6. Line 3: Rp. xxx.xxx.xxx (Right-Aligned)
    TD_HudMoney[playerid] = CreatePlayerTextDraw(playerid, 622.0, 49.0, "Rp. 0");
    PlayerTextDrawFont(playerid, TD_HudMoney[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_HudMoney[playerid], 0.20, 1.05);
    PlayerTextDrawColor(playerid, TD_HudMoney[playerid], 0xFFFFFFFF);
    PlayerTextDrawAlignment(playerid, TD_HudMoney[playerid], 3); // Right-Aligned
    PlayerTextDrawSetOutline(playerid, TD_HudMoney[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_HudMoney[playerid], false);

    // 7. Line 4: Job : Pengangguran (Right-Aligned)
    TD_HudJob[playerid] = CreatePlayerTextDraw(playerid, 622.0, 62.0, "Job : Pengangguran");
    PlayerTextDrawFont(playerid, TD_HudJob[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_HudJob[playerid], 0.17, 0.95);
    PlayerTextDrawColor(playerid, TD_HudJob[playerid], 0xFFFFFFFF);
    PlayerTextDrawAlignment(playerid, TD_HudJob[playerid], 3); // Right-Aligned
    PlayerTextDrawSetOutline(playerid, TD_HudJob[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_HudJob[playerid], false);

    // ============================================================
    //  B. Bottom-Left Minimalist Status Bars (Thirsty, Hunger)
    // ============================================================

    // 1. Thirsty Bar (Y: 404.0)
    TD_StatusBgThirst[playerid] = CreatePlayerTextDraw(playerid, STATUS_BAR_START_X, 404.0, "_");
    PlayerTextDrawUseBox(playerid, TD_StatusBgThirst[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_StatusBgThirst[playerid], 0x1B2A36EE);
    PlayerTextDrawTextSize(playerid, TD_StatusBgThirst[playerid], STATUS_BAR_END_X, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_StatusBgThirst[playerid], 0.0, 0.95);
    PlayerTextDrawSetSelectable(playerid, TD_StatusBgThirst[playerid], false);

    TD_StatusFillThirst[playerid] = CreatePlayerTextDraw(playerid, STATUS_BAR_START_X, 404.0, "_");
    PlayerTextDrawUseBox(playerid, TD_StatusFillThirst[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_StatusFillThirst[playerid], 0x6C77C4FF); // Soft Violet Blue
    PlayerTextDrawTextSize(playerid, TD_StatusFillThirst[playerid], STATUS_BAR_END_X, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_StatusFillThirst[playerid], 0.0, 0.95);
    PlayerTextDrawSetSelectable(playerid, TD_StatusFillThirst[playerid], false);

    TD_StatusTxtThirst[playerid] = CreatePlayerTextDraw(playerid, 60.0, 402.8, "Thirsty");
    PlayerTextDrawFont(playerid, TD_StatusTxtThirst[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_StatusTxtThirst[playerid], 0.15, 0.85);
    PlayerTextDrawColor(playerid, TD_StatusTxtThirst[playerid], 0xFFFFFFFF);
    PlayerTextDrawAlignment(playerid, TD_StatusTxtThirst[playerid], 2); // Center
    PlayerTextDrawSetOutline(playerid, TD_StatusTxtThirst[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_StatusTxtThirst[playerid], false);

    // 2. Hunger Bar (Y: 416.0)
    TD_StatusBgHunger[playerid] = CreatePlayerTextDraw(playerid, STATUS_BAR_START_X, 416.0, "_");
    PlayerTextDrawUseBox(playerid, TD_StatusBgHunger[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_StatusBgHunger[playerid], 0x1B2A36EE);
    PlayerTextDrawTextSize(playerid, TD_StatusBgHunger[playerid], STATUS_BAR_END_X, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_StatusBgHunger[playerid], 0.0, 0.95);
    PlayerTextDrawSetSelectable(playerid, TD_StatusBgHunger[playerid], false);

    TD_StatusFillHunger[playerid] = CreatePlayerTextDraw(playerid, STATUS_BAR_START_X, 416.0, "_");
    PlayerTextDrawUseBox(playerid, TD_StatusFillHunger[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_StatusFillHunger[playerid], 0x8C4933FF); // Warm Brown Chocolate
    PlayerTextDrawTextSize(playerid, TD_StatusFillHunger[playerid], STATUS_BAR_END_X, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_StatusFillHunger[playerid], 0.0, 0.95);
    PlayerTextDrawSetSelectable(playerid, TD_StatusFillHunger[playerid], false);

    TD_StatusTxtHunger[playerid] = CreatePlayerTextDraw(playerid, 60.0, 414.8, "Hunger");
    PlayerTextDrawFont(playerid, TD_StatusTxtHunger[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_StatusTxtHunger[playerid], 0.15, 0.85);
    PlayerTextDrawColor(playerid, TD_StatusTxtHunger[playerid], 0xFFFFFFFF);
    PlayerTextDrawAlignment(playerid, TD_StatusTxtHunger[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_StatusTxtHunger[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_StatusTxtHunger[playerid], false);
}

stock ShowPlayerMoneyHUD(playerid) {
    // 1. Top-Right HUD
    if (TD_HudBox[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_HudBox[playerid]);
    if (TD_HudTopBar[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_HudTopBar[playerid]);
    if (TD_HudLogo[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_HudLogo[playerid]);
    if (TD_HudID[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_HudID[playerid]);
    if (TD_HudName[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_HudName[playerid]);
    if (TD_HudMoney[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_HudMoney[playerid]);
    if (TD_HudJob[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_HudJob[playerid]);

    // 2. Bottom-Left Status Bars (Thirsty & Hunger)
    if (TD_StatusBgThirst[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_StatusBgThirst[playerid]);
    if (TD_StatusFillThirst[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_StatusFillThirst[playerid]);
    if (TD_StatusTxtThirst[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_StatusTxtThirst[playerid]);

    if (TD_StatusBgHunger[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_StatusBgHunger[playerid]);
    if (TD_StatusFillHunger[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_StatusFillHunger[playerid]);
    if (TD_StatusTxtHunger[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_StatusTxtHunger[playerid]);
}

stock HidePlayerMoneyHUD(playerid) {
    // 1. Top-Right HUD
    if (TD_HudBox[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawHide(playerid, TD_HudBox[playerid]);
    if (TD_HudTopBar[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawHide(playerid, TD_HudTopBar[playerid]);
    if (TD_HudLogo[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawHide(playerid, TD_HudLogo[playerid]);
    if (TD_HudID[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawHide(playerid, TD_HudID[playerid]);
    if (TD_HudName[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawHide(playerid, TD_HudName[playerid]);
    if (TD_HudMoney[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawHide(playerid, TD_HudMoney[playerid]);
    if (TD_HudJob[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawHide(playerid, TD_HudJob[playerid]);

    // 2. Bottom-Left Status Bars
    if (TD_StatusBgThirst[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawHide(playerid, TD_StatusBgThirst[playerid]);
    if (TD_StatusFillThirst[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawHide(playerid, TD_StatusFillThirst[playerid]);
    if (TD_StatusTxtThirst[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawHide(playerid, TD_StatusTxtThirst[playerid]);

    if (TD_StatusBgHunger[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawHide(playerid, TD_StatusBgHunger[playerid]);
    if (TD_StatusFillHunger[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawHide(playerid, TD_StatusFillHunger[playerid]);
    if (TD_StatusTxtHunger[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawHide(playerid, TD_StatusTxtHunger[playerid]);
}

stock UpdatePlayerMoneyHUD(playerid) {
    if (TD_HudMoney[playerid] == PlayerText:INVALID_TEXT_DRAW) return;

    // 1. Line 1: ID : %d
    new idStr[32];
    format(idStr, sizeof(idStr), "ID : %d", playerid);
    PlayerTextDrawSetString(playerid, TD_HudID[playerid], idStr);

    // 2. Line 2: [Nama Karakter]
    new charname[48];
    GetCharName(playerid, charname);
    PlayerTextDrawSetString(playerid, TD_HudName[playerid], charname);

    // 3. Line 3: Rp. xxx.xxx.xxx
    new rup[32], str[64];
    FormatRupiah(gPlayerData[playerid][p_Cash], rup, sizeof(rup));
    format(str, sizeof(str), "Rp. %s", rup);
    PlayerTextDrawSetString(playerid, TD_HudMoney[playerid], str);

    // 4. Line 4: Job : %s
    new jobName[32], jobStr[48];
    GetPlayerJobName(playerid, jobName, sizeof(jobName));
    format(jobStr, sizeof(jobStr), "Job : %s", jobName);
    PlayerTextDrawSetString(playerid, TD_HudJob[playerid], jobStr);

    // ============================================================
    //  Update Bottom-Left Dynamic Progress Status Bars (Thirsty, Hunger)
    // ============================================================

    // A. Thirsty (Tingkat Haus)
    new Float:thirst = gPlayerData[playerid][p_Thirst];
    if (thirst > 100.0) thirst = 100.0;
    if (thirst < 0.0) thirst = 0.0;
    new Float:thirstEndX = STATUS_BAR_START_X + (thirst / 100.0) * (STATUS_BAR_END_X - STATUS_BAR_START_X);
    if (thirst > 0.0) {
        PlayerTextDrawTextSize(playerid, TD_StatusFillThirst[playerid], thirstEndX, 0.0);
        PlayerTextDrawShow(playerid, TD_StatusFillThirst[playerid]);
    } else {
        PlayerTextDrawHide(playerid, TD_StatusFillThirst[playerid]);
    }

    // B. Hunger (Tingkat Lapar)
    new Float:hunger = gPlayerData[playerid][p_Hunger];
    if (hunger > 100.0) hunger = 100.0;
    if (hunger < 0.0) hunger = 0.0;
    new Float:hungerEndX = STATUS_BAR_START_X + (hunger / 100.0) * (STATUS_BAR_END_X - STATUS_BAR_START_X);
    if (hunger > 0.0) {
        PlayerTextDrawTextSize(playerid, TD_StatusFillHunger[playerid], hungerEndX, 0.0);
        PlayerTextDrawShow(playerid, TD_StatusFillHunger[playerid]);
    } else {
        PlayerTextDrawHide(playerid, TD_StatusFillHunger[playerid]);
    }

    // Pastikan Backgrounds & Labels tetap tampil
    if (TD_HudBox[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_HudBox[playerid]);
    if (TD_HudTopBar[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_HudTopBar[playerid]);
    if (TD_HudLogo[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_HudLogo[playerid]);
    if (TD_HudID[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_HudID[playerid]);
    if (TD_HudName[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_HudName[playerid]);
    if (TD_HudMoney[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_HudMoney[playerid]);
    if (TD_HudJob[playerid] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawShow(playerid, TD_HudJob[playerid]);
}

stock GivePlayerMoneyEx(playerid, amount) {
    gPlayerData[playerid][p_Cash] += amount;
    UpdatePlayerMoneyHUD(playerid);
}

stock GivePlayerHunger(playerid, Float:amount) {
    gPlayerData[playerid][p_Hunger] += amount;
    if (gPlayerData[playerid][p_Hunger] > 100.0) gPlayerData[playerid][p_Hunger] = 100.0;
    if (gPlayerData[playerid][p_Hunger] < 0.0)   gPlayerData[playerid][p_Hunger] = 0.0;
    UpdatePlayerMoneyHUD(playerid);
}

stock GivePlayerThirst(playerid, Float:amount) {
    gPlayerData[playerid][p_Thirst] += amount;
    if (gPlayerData[playerid][p_Thirst] > 100.0) gPlayerData[playerid][p_Thirst] = 100.0;
    if (gPlayerData[playerid][p_Thirst] < 0.0)   gPlayerData[playerid][p_Thirst] = 0.0;
    UpdatePlayerMoneyHUD(playerid);
}
