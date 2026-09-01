#if defined _MODULE_REFUEL_UI_INC
    #endinput
#endif
#define _MODULE_REFUEL_UI_INC

// ============================================================
//  SantaraBaru Roleplay - Interactive Refuel / Isi Bensin UI
// ============================================================

#define COLOR_REFUEL_CARD_BG    0x14141EF6
#define COLOR_REFUEL_PURPLE     0x5814EEFF
#define COLOR_REFUEL_BAR_BG     0x22222CEE
#define COLOR_REFUEL_BTN_DARK   0x32323DEE
#define COLOR_REFUEL_RED        0xFF1133FF
#define FUEL_PRICE_PER_LITER    15950

new bool:gPlayerInRefuelUI[MAX_PLAYERS]             = {false, ...};
new gRefuelTargetVeh[MAX_PLAYERS]                  = {INVALID_VEHICLE_ID, ...};
new Float:gRefuelSelectedLiters[MAX_PLAYERS]       = {0.0, ...};
new Float:gRefuelMaxNeeded[MAX_PLAYERS]            = {0.0, ...};
new Float:gRefuelCurrentFuel[MAX_PLAYERS]          = {0.0, ...};

// TextDraws
new PlayerText:TD_RefuelCardBG[MAX_PLAYERS]        = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_RefuelHeaderPurple[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_RefuelTitleText[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_RefuelBtnClose[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_RefuelPriceBox[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_RefuelPriceText[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_RefuelBtnPlus[MAX_PLAYERS]       = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_RefuelBarBG[MAX_PLAYERS]         = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_RefuelBarFill[MAX_PLAYERS]       = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_RefuelBarInfo[MAX_PLAYERS]       = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_RefuelBtnMinus[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_RefuelBtnFull[MAX_PLAYERS]       = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_RefuelBtnConfirm[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_RefuelBtnCancel[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};

forward DestroyRefuelTextDraws(playerid);
forward UpdateRefuelUI(playerid);

stock DestroyRefuelTextDraws(playerid) {
    if (TD_RefuelCardBG[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_RefuelCardBG[playerid]); TD_RefuelCardBG[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_RefuelHeaderPurple[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_RefuelHeaderPurple[playerid]); TD_RefuelHeaderPurple[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_RefuelTitleText[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_RefuelTitleText[playerid]); TD_RefuelTitleText[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_RefuelBtnClose[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_RefuelBtnClose[playerid]); TD_RefuelBtnClose[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_RefuelPriceBox[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_RefuelPriceBox[playerid]); TD_RefuelPriceBox[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_RefuelPriceText[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_RefuelPriceText[playerid]); TD_RefuelPriceText[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_RefuelBtnPlus[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_RefuelBtnPlus[playerid]); TD_RefuelBtnPlus[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_RefuelBarBG[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_RefuelBarBG[playerid]); TD_RefuelBarBG[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_RefuelBarFill[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_RefuelBarFill[playerid]); TD_RefuelBarFill[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_RefuelBarInfo[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_RefuelBarInfo[playerid]); TD_RefuelBarInfo[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_RefuelBtnMinus[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_RefuelBtnMinus[playerid]); TD_RefuelBtnMinus[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_RefuelBtnFull[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_RefuelBtnFull[playerid]); TD_RefuelBtnFull[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_RefuelBtnConfirm[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_RefuelBtnConfirm[playerid]); TD_RefuelBtnConfirm[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_RefuelBtnCancel[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_RefuelBtnCancel[playerid]); TD_RefuelBtnCancel[playerid] = PlayerText:INVALID_TEXT_DRAW; }
}

stock CloseRefuelUI(playerid) {
    if (!gPlayerInRefuelUI[playerid]) return 0;
    gPlayerInRefuelUI[playerid] = false;
    gRefuelTargetVeh[playerid] = INVALID_VEHICLE_ID;
    CancelSelectTextDraw(playerid);
    DestroyRefuelTextDraws(playerid);
    return 1;
}

stock OpenRefuelUI(playerid) {
    if (!CheckSpawned(playerid)) return 0;

    if (IsPlayerInAnyVehicle(playerid)) {
        SendClientMessage(playerid, COL_RED, "  [Pom Bensin] Anda harus turun dari kendaraan untuk mengisi bensin!");
        return 0;
    }

    if (!IsPlayerNearFuelPump(playerid)) {
        SendClientMessage(playerid, COL_RED, "  [Pom Bensin] Anda harus berdiri di dekat titik dispenser / tangki Pom Bensin!");
        return 0;
    }

    // Cari kendaraan terdekat dari pemain (maks 5.5 meter)
    new nearestVeh = INVALID_VEHICLE_ID;
    new Float:minDist = 5.5;
    new Float:px, Float:py, Float:pz;
    GetPlayerPos(playerid, px, py, pz);

    for (new v = 1; v < MAX_VEHICLES; v++) {
        if (GetVehicleModel(v) > 0) {
            new Float:vx, Float:vy, Float:vz;
            GetVehiclePos(v, vx, vy, vz);
            new Float:dx = px - vx; new Float:dy = py - vy; new Float:dz = pz - vz;
            new Float:dist = floatsqroot((dx * dx) + (dy * dy) + (dz * dz));
            if (dist <= minDist) {
                minDist = dist;
                nearestVeh = v;
            }
        }
    }

    if (nearestVeh == INVALID_VEHICLE_ID) {
        SendClientMessage(playerid, COL_RED, "  [Pom Bensin] Tidak ada kendaraan di dekat Anda (parkirkan mobil dekat tangki bensin)!");
        return 0;
    }

    new engine, lights, alarm, doors, bonnet, boot, objective;
    GetVehicleParamsEx(nearestVeh, engine, lights, alarm, doors, bonnet, boot, objective);
    if (engine == 1) {
        SendClientMessage(playerid, COL_RED, "  [Pom Bensin] Matikan mesin kendaraan terlebih dahulu sebelum mengisi bensin!");
        return 0;
    }

    new Float:maxFuel = 50.0;
    new Float:currentFuel = gVehicleFuel[nearestVeh];

    if (currentFuel >= maxFuel - 0.5) {
        SendClientMessage(playerid, COL_RED, "  [Pom Bensin] Tangki bensin kendaraan tersebut sudah penuh (50 L)!");
        return 0;
    }

    gRefuelTargetVeh[playerid] = nearestVeh;
    gRefuelCurrentFuel[playerid] = currentFuel;
    gRefuelMaxNeeded[playerid] = maxFuel - currentFuel;

    // Default pilihan awal: 10 Liter atau sisa jika kurang dari 10L
    gRefuelSelectedLiters[playerid] = (gRefuelMaxNeeded[playerid] >= 10.0) ? 10.0 : gRefuelMaxNeeded[playerid];

    // Buat TextDraw UI
    DestroyRefuelTextDraws(playerid);

    // 1. Container Card Background (Center X: 255.0 .. 385.0, Y: 100.0 .. 365.0)
    TD_RefuelCardBG[playerid] = CreatePlayerTextDraw(playerid, 255.0, 100.0, "_");
    PlayerTextDrawUseBox(playerid, TD_RefuelCardBG[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_RefuelCardBG[playerid], COLOR_REFUEL_CARD_BG);
    PlayerTextDrawTextSize(playerid, TD_RefuelCardBG[playerid], 385.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_RefuelCardBG[playerid], 0.0, 29.5);
    PlayerTextDrawSetSelectable(playerid, TD_RefuelCardBG[playerid], false);

    // 2. Top Purple Header Bar (Width: 105.0)
    TD_RefuelHeaderPurple[playerid] = CreatePlayerTextDraw(playerid, 255.0, 100.0, "_");
    PlayerTextDrawUseBox(playerid, TD_RefuelHeaderPurple[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_RefuelHeaderPurple[playerid], COLOR_REFUEL_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_RefuelHeaderPurple[playerid], 360.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_RefuelHeaderPurple[playerid], 0.0, 1.8);
    PlayerTextDrawSetSelectable(playerid, TD_RefuelHeaderPurple[playerid], false);

    // 3. Header Title Text
    TD_RefuelTitleText[playerid] = CreatePlayerTextDraw(playerid, 260.0, 103.0, "isibensin");
    PlayerTextDrawFont(playerid, TD_RefuelTitleText[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_RefuelTitleText[playerid], 0.16, 1.0);
    PlayerTextDrawColor(playerid, TD_RefuelTitleText[playerid], 0xFFFFFFFF);
    PlayerTextDrawSetOutline(playerid, TD_RefuelTitleText[playerid], 0);
    PlayerTextDrawSetSelectable(playerid, TD_RefuelTitleText[playerid], false);

    // 4. Red [ X ] Close Button (Center X: 372.5)
    TD_RefuelBtnClose[playerid] = CreatePlayerTextDraw(playerid, 372.5, 102.5, "X");
    PlayerTextDrawFont(playerid, TD_RefuelBtnClose[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_RefuelBtnClose[playerid], 0.18, 1.05);
    PlayerTextDrawColor(playerid, TD_RefuelBtnClose[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_RefuelBtnClose[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_RefuelBtnClose[playerid], COLOR_REFUEL_RED);
    PlayerTextDrawTextSize(playerid, TD_RefuelBtnClose[playerid], 15.0, 25.0);
    PlayerTextDrawAlignment(playerid, TD_RefuelBtnClose[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_RefuelBtnClose[playerid], 0);
    PlayerTextDrawSetSelectable(playerid, TD_RefuelBtnClose[playerid], true);

    // 5. Price Display Purple Box (X: 265.0 .. 375.0, Y: 125.0 .. 150.0)
    TD_RefuelPriceBox[playerid] = CreatePlayerTextDraw(playerid, 265.0, 125.0, "_");
    PlayerTextDrawUseBox(playerid, TD_RefuelPriceBox[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_RefuelPriceBox[playerid], COLOR_REFUEL_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_RefuelPriceBox[playerid], 375.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_RefuelPriceBox[playerid], 0.0, 2.7);
    PlayerTextDrawSetSelectable(playerid, TD_RefuelPriceBox[playerid], false);

    // 6. Dynamic Price Text
    TD_RefuelPriceText[playerid] = CreatePlayerTextDraw(playerid, 320.0, 128.5, "Rp. 0");
    PlayerTextDrawFont(playerid, TD_RefuelPriceText[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_RefuelPriceText[playerid], 0.19, 1.15);
    PlayerTextDrawColor(playerid, TD_RefuelPriceText[playerid], 0xFFFFFFFF);
    PlayerTextDrawAlignment(playerid, TD_RefuelPriceText[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_RefuelPriceText[playerid], 0);
    PlayerTextDrawSetSelectable(playerid, TD_RefuelPriceText[playerid], false);

    // 7. [ + ] Stepper Plus Button (Center X: 320.0, Y: 158.0)
    TD_RefuelBtnPlus[playerid] = CreatePlayerTextDraw(playerid, 320.0, 158.0, "+");
    PlayerTextDrawFont(playerid, TD_RefuelBtnPlus[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_RefuelBtnPlus[playerid], 0.25, 1.35);
    PlayerTextDrawColor(playerid, TD_RefuelBtnPlus[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_RefuelBtnPlus[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_RefuelBtnPlus[playerid], COLOR_REFUEL_BTN_DARK);
    PlayerTextDrawTextSize(playerid, TD_RefuelBtnPlus[playerid], 16.0, 28.0);
    PlayerTextDrawAlignment(playerid, TD_RefuelBtnPlus[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_RefuelBtnPlus[playerid], 0);
    PlayerTextDrawSetSelectable(playerid, TD_RefuelBtnPlus[playerid], true);

    // 8. Vertical Fuel Bar BG (Grey, X: 306.0 .. 334.0, Y: 180.0 .. 252.0, Height = 72px)
    TD_RefuelBarBG[playerid] = CreatePlayerTextDraw(playerid, 306.0, 180.0, "_");
    PlayerTextDrawUseBox(playerid, TD_RefuelBarBG[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_RefuelBarBG[playerid], COLOR_REFUEL_BAR_BG);
    PlayerTextDrawTextSize(playerid, TD_RefuelBarBG[playerid], 334.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_RefuelBarBG[playerid], 0.0, 7.8);
    PlayerTextDrawSetSelectable(playerid, TD_RefuelBarBG[playerid], false);

    // 9. Vertical Fuel Bar Info (Liters Text inside bar)
    TD_RefuelBarInfo[playerid] = CreatePlayerTextDraw(playerid, 320.0, 211.0, "0 L");
    PlayerTextDrawFont(playerid, TD_RefuelBarInfo[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_RefuelBarInfo[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_RefuelBarInfo[playerid], 0xFFFFFFFF);
    PlayerTextDrawAlignment(playerid, TD_RefuelBarInfo[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_RefuelBarInfo[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_RefuelBarInfo[playerid], false);

    // 10. [ - ] Stepper Minus Button (Center X: 320.0, Y: 258.0)
    TD_RefuelBtnMinus[playerid] = CreatePlayerTextDraw(playerid, 320.0, 258.0, "-");
    PlayerTextDrawFont(playerid, TD_RefuelBtnMinus[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_RefuelBtnMinus[playerid], 0.25, 1.35);
    PlayerTextDrawColor(playerid, TD_RefuelBtnMinus[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_RefuelBtnMinus[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_RefuelBtnMinus[playerid], COLOR_REFUEL_BTN_DARK);
    PlayerTextDrawTextSize(playerid, TD_RefuelBtnMinus[playerid], 16.0, 28.0);
    PlayerTextDrawAlignment(playerid, TD_RefuelBtnMinus[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_RefuelBtnMinus[playerid], 0);
    PlayerTextDrawSetSelectable(playerid, TD_RefuelBtnMinus[playerid], true);

    // 11. [ Full ] Button (Center X: 320.0, Y: 282.0)
    TD_RefuelBtnFull[playerid] = CreatePlayerTextDraw(playerid, 320.0, 282.0, "Full");
    PlayerTextDrawFont(playerid, TD_RefuelBtnFull[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_RefuelBtnFull[playerid], 0.17, 1.1);
    PlayerTextDrawColor(playerid, TD_RefuelBtnFull[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_RefuelBtnFull[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_RefuelBtnFull[playerid], COLOR_REFUEL_BTN_DARK);
    PlayerTextDrawTextSize(playerid, TD_RefuelBtnFull[playerid], 16.0, 95.0);
    PlayerTextDrawAlignment(playerid, TD_RefuelBtnFull[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_RefuelBtnFull[playerid], 0);
    PlayerTextDrawSetSelectable(playerid, TD_RefuelBtnFull[playerid], true);

    // 12. [ Isi ] Button (Center X: 320.0, Y: 306.0)
    TD_RefuelBtnConfirm[playerid] = CreatePlayerTextDraw(playerid, 320.0, 306.0, "Isi");
    PlayerTextDrawFont(playerid, TD_RefuelBtnConfirm[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_RefuelBtnConfirm[playerid], 0.19, 1.15);
    PlayerTextDrawColor(playerid, TD_RefuelBtnConfirm[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_RefuelBtnConfirm[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_RefuelBtnConfirm[playerid], COLOR_REFUEL_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_RefuelBtnConfirm[playerid], 18.0, 95.0);
    PlayerTextDrawAlignment(playerid, TD_RefuelBtnConfirm[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_RefuelBtnConfirm[playerid], 0);
    PlayerTextDrawSetSelectable(playerid, TD_RefuelBtnConfirm[playerid], true);

    // 13. [ Batal ] Button (Center X: 320.0, Y: 332.0)
    TD_RefuelBtnCancel[playerid] = CreatePlayerTextDraw(playerid, 320.0, 332.0, "Batal");
    PlayerTextDrawFont(playerid, TD_RefuelBtnCancel[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_RefuelBtnCancel[playerid], 0.17, 1.1);
    PlayerTextDrawColor(playerid, TD_RefuelBtnCancel[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_RefuelBtnCancel[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_RefuelBtnCancel[playerid], COLOR_REFUEL_RED);
    PlayerTextDrawTextSize(playerid, TD_RefuelBtnCancel[playerid], 16.0, 95.0);
    PlayerTextDrawAlignment(playerid, TD_RefuelBtnCancel[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_RefuelBtnCancel[playerid], 0);
    PlayerTextDrawSetSelectable(playerid, TD_RefuelBtnCancel[playerid], true);

    // Tampilkan semua static textdraws
    PlayerTextDrawShow(playerid, TD_RefuelCardBG[playerid]);
    PlayerTextDrawShow(playerid, TD_RefuelHeaderPurple[playerid]);
    PlayerTextDrawShow(playerid, TD_RefuelTitleText[playerid]);
    PlayerTextDrawShow(playerid, TD_RefuelBtnClose[playerid]);
    PlayerTextDrawShow(playerid, TD_RefuelPriceBox[playerid]);
    PlayerTextDrawShow(playerid, TD_RefuelBtnPlus[playerid]);
    PlayerTextDrawShow(playerid, TD_RefuelBarBG[playerid]);
    PlayerTextDrawShow(playerid, TD_RefuelBtnMinus[playerid]);
    PlayerTextDrawShow(playerid, TD_RefuelBtnFull[playerid]);
    PlayerTextDrawShow(playerid, TD_RefuelBtnConfirm[playerid]);
    PlayerTextDrawShow(playerid, TD_RefuelBtnCancel[playerid]);

    gPlayerInRefuelUI[playerid] = true;
    UpdateRefuelUI(playerid);

    SelectTextDraw(playerid, 0x00EEFFFF);
    PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
    return 1;
}

stock UpdateRefuelUI(playerid) {
    if (!gPlayerInRefuelUI[playerid]) return 0;

    new totalCost = floatround(gRefuelSelectedLiters[playerid]) * FUEL_PRICE_PER_LITER;
    new costStr[32];
    FormatRupiah(totalCost, costStr, sizeof(costStr));

    new priceTextStr[64];
    format(priceTextStr, sizeof(priceTextStr), "Rp. %s", costStr);
    PlayerTextDrawSetString(playerid, TD_RefuelPriceText[playerid], priceTextStr);
    PlayerTextDrawShow(playerid, TD_RefuelPriceText[playerid]);

    // Update Info Text inside Bar
    new barInfoStr[32];
    format(barInfoStr, sizeof(barInfoStr), "%.1f L", gRefuelSelectedLiters[playerid]);
    PlayerTextDrawSetString(playerid, TD_RefuelBarInfo[playerid], barInfoStr);

    // Update Vertical Fuel Bar Fill
    if (TD_RefuelBarFill[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_RefuelBarFill[playerid]);
        TD_RefuelBarFill[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    new Float:totalLevel = gRefuelCurrentFuel[playerid] + gRefuelSelectedLiters[playerid];
    if (totalLevel > 50.0) totalLevel = 50.0;
    if (totalLevel < 0.0) totalLevel = 0.0;

    new Float:ratio = totalLevel / 50.0;
    new Float:maxBarH = 72.0; // Bar range Y: 180.0 to 252.0
    new Float:fillH = maxBarH * ratio;
    if (fillH < 1.0) fillH = 1.0;

    new Float:topY = 252.0 - fillH;
    new Float:lineHeight = fillH / 9.0;

    TD_RefuelBarFill[playerid] = CreatePlayerTextDraw(playerid, 306.0, topY, "_");
    PlayerTextDrawUseBox(playerid, TD_RefuelBarFill[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_RefuelBarFill[playerid], COLOR_REFUEL_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_RefuelBarFill[playerid], 334.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_RefuelBarFill[playerid], 0.0, lineHeight);
    PlayerTextDrawSetSelectable(playerid, TD_RefuelBarFill[playerid], false);

    PlayerTextDrawShow(playerid, TD_RefuelBarFill[playerid]);
    PlayerTextDrawShow(playerid, TD_RefuelBarInfo[playerid]);
    return 1;
}

stock HandleRefuelUIClick(playerid, PlayerText:playertextid) {
    if (!gPlayerInRefuelUI[playerid]) return 0;

    // 1. Close Button [ X ]
    if (playertextid == TD_RefuelBtnClose[playerid] || playertextid == TD_RefuelBtnCancel[playerid]) {
        CloseRefuelUI(playerid);
        PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
        return 1;
    }

    // 2. Stepper Plus [ + ]
    if (playertextid == TD_RefuelBtnPlus[playerid]) {
        gRefuelSelectedLiters[playerid] += 5.0;
        if (gRefuelSelectedLiters[playerid] > gRefuelMaxNeeded[playerid]) {
            gRefuelSelectedLiters[playerid] = gRefuelMaxNeeded[playerid];
        }
        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
        UpdateRefuelUI(playerid);
        return 1;
    }

    // 3. Stepper Minus [ - ]
    if (playertextid == TD_RefuelBtnMinus[playerid]) {
        gRefuelSelectedLiters[playerid] -= 5.0;
        if (gRefuelSelectedLiters[playerid] < 1.0) {
            gRefuelSelectedLiters[playerid] = 1.0;
        }
        PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
        UpdateRefuelUI(playerid);
        return 1;
    }

    // 4. [ Full ] Button
    if (playertextid == TD_RefuelBtnFull[playerid]) {
        gRefuelSelectedLiters[playerid] = gRefuelMaxNeeded[playerid];
        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
        UpdateRefuelUI(playerid);
        return 1;
    }

    // 5. [ Isi ] Confirm Button
    if (playertextid == TD_RefuelBtnConfirm[playerid]) {
        new targetVeh = gRefuelTargetVeh[playerid];
        if (targetVeh == INVALID_VEHICLE_ID || GetVehicleModel(targetVeh) <= 0) {
            SendClientMessage(playerid, COL_RED, "  [Pom Bensin] Kendaraan tidak ditemukan lagi di dekat Anda!");
            CloseRefuelUI(playerid);
            return 1;
        }

        new totalCost = floatround(gRefuelSelectedLiters[playerid]) * FUEL_PRICE_PER_LITER;
        new Float:litersToFill = gRefuelSelectedLiters[playerid];

        if (gPlayerData[playerid][p_Cash] < totalCost) {
            new canAffordLiters = gPlayerData[playerid][p_Cash] / FUEL_PRICE_PER_LITER;
            if (canAffordLiters <= 0) {
                SendClientMessage(playerid, COL_RED, "  [Pom Bensin] Uang tunai Anda tidak cukup untuk mengisi bensin!");
                PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
                return 1;
            }
            totalCost = canAffordLiters * FUEL_PRICE_PER_LITER;
            litersToFill = float(canAffordLiters);
        }

        gPlayerData[playerid][p_Cash] -= totalCost;
        UpdatePlayerMoneyHUD(playerid);

        new qMoney[128];
        format(qMoney, sizeof(qMoney), "UPDATE `characters` SET `cash`=%d WHERE `id`=%d", gPlayerData[playerid][p_Cash], gPlayerData[playerid][p_CharID]);
        DB_FreeResultSet(DB_ExecuteQuery(gDB, qMoney));

        gVehicleFuel[targetVeh] += litersToFill;
        if (gVehicleFuel[targetVeh] > 50.0) gVehicleFuel[targetVeh] = 50.0;

        ApplyAnimation(playerid, "INT_HOUSE", "wash_up", 4.1, false, false, false, false, 2000, true);
        PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);

        new costStr[32];
        FormatRupiah(totalCost, costStr, sizeof(costStr));
        new msg[144];
        format(msg, sizeof(msg), "  [Pom Bensin] Berhasil mengisi {FFFF00}%.1f liter{FFFFFF} bensin ke kendaraan seharga {2ECC71}%s{FFFFFF}.", litersToFill, costStr);
        SendClientMessage(playerid, COL_GREEN, msg);

        CloseRefuelUI(playerid);
        return 1;
    }

    return 0;
}
