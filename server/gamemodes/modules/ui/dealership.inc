#if defined _MODULE_DEALERSHIP_INC
    #endinput
#endif
#define _MODULE_DEALERSHIP_INC

// ============================================================
//  SantaraBaru Roleplay - Rodeo Luxury Dealership & Live 3D UI (/dealer)
//  Dark Indigo (#1E1E2E) & Electric Purple (#5814EE) Theme
// ============================================================

enum E_DEALER_VEHICLE {
    d_ModelID,
    d_Name[28],
    d_Type[28],
    d_Price,
    d_TopSpeed,
    d_Seats
};

#define MAX_DEALER_VEHICLES_PER_CAT 64
#define MAX_DEALER_COLORS           32

new gSportVehicles[MAX_DEALER_VEHICLES_PER_CAT][E_DEALER_VEHICLE];
new gSedanVehicles[MAX_DEALER_VEHICLES_PER_CAT][E_DEALER_VEHICLE];
new gSuvVehicles[MAX_DEALER_VEHICLES_PER_CAT][E_DEALER_VEHICLE];
new gBikeVehicles[MAX_DEALER_VEHICLES_PER_CAT][E_DEALER_VEHICLE];

new gSportVehicleCount = 0;
new gSedanVehicleCount = 0;
new gSuvVehicleCount   = 0;
new gBikeVehicleCount  = 0;

new gDealerColors[MAX_DEALER_COLORS];
new gDealerColorNames[MAX_DEALER_COLORS][24];
new gDealerColorCount = 0;

#define DEALER_COLOR_COUNT (gDealerColorCount > 0 ? gDealerColorCount : 20)

stock Dealership_LoadDataFromDB() {
    gSportVehicleCount = 0;
    gSedanVehicleCount = 0;
    gSuvVehicleCount   = 0;
    gBikeVehicleCount  = 0;
    gDealerColorCount  = 0;

    // 1. Load Vehicles from santara_master.db
    new DBResult:resVeh = DB_ExecuteQuery(gDB_Master, "SELECT `model_id`, `name`, `description`, `category`, `price`, `top_speed`, `seats` FROM `dealership_vehicles` ORDER BY `id` ASC");
    if (resVeh) {
        new rowCount = DB_GetRowCount(resVeh);
        for (new i = 0; i < rowCount; i++) {
            new cat = DB_GetFieldIntByName(resVeh, "category");
            switch (cat) {
                case DEALER_CAT_SPORT: {
                    if (gSportVehicleCount < MAX_DEALER_VEHICLES_PER_CAT) {
                        new idx = gSportVehicleCount;
                        gSportVehicles[idx][d_ModelID]  = DB_GetFieldIntByName(resVeh, "model_id");
                        DB_GetFieldStringByName(resVeh, "name", gSportVehicles[idx][d_Name], 28);
                        DB_GetFieldStringByName(resVeh, "description", gSportVehicles[idx][d_Type], 28);
                        gSportVehicles[idx][d_Price]    = DB_GetFieldIntByName(resVeh, "price");
                        gSportVehicles[idx][d_TopSpeed] = DB_GetFieldIntByName(resVeh, "top_speed");
                        gSportVehicles[idx][d_Seats]    = DB_GetFieldIntByName(resVeh, "seats");
                        gSportVehicleCount++;
                    }
                }
                case DEALER_CAT_SEDAN: {
                    if (gSedanVehicleCount < MAX_DEALER_VEHICLES_PER_CAT) {
                        new idx = gSedanVehicleCount;
                        gSedanVehicles[idx][d_ModelID]  = DB_GetFieldIntByName(resVeh, "model_id");
                        DB_GetFieldStringByName(resVeh, "name", gSedanVehicles[idx][d_Name], 28);
                        DB_GetFieldStringByName(resVeh, "description", gSedanVehicles[idx][d_Type], 28);
                        gSedanVehicles[idx][d_Price]    = DB_GetFieldIntByName(resVeh, "price");
                        gSedanVehicles[idx][d_TopSpeed] = DB_GetFieldIntByName(resVeh, "top_speed");
                        gSedanVehicles[idx][d_Seats]    = DB_GetFieldIntByName(resVeh, "seats");
                        gSedanVehicleCount++;
                    }
                }
                case DEALER_CAT_SUV: {
                    if (gSuvVehicleCount < MAX_DEALER_VEHICLES_PER_CAT) {
                        new idx = gSuvVehicleCount;
                        gSuvVehicles[idx][d_ModelID]  = DB_GetFieldIntByName(resVeh, "model_id");
                        DB_GetFieldStringByName(resVeh, "name", gSuvVehicles[idx][d_Name], 28);
                        DB_GetFieldStringByName(resVeh, "description", gSuvVehicles[idx][d_Type], 28);
                        gSuvVehicles[idx][d_Price]    = DB_GetFieldIntByName(resVeh, "price");
                        gSuvVehicles[idx][d_TopSpeed] = DB_GetFieldIntByName(resVeh, "top_speed");
                        gSuvVehicles[idx][d_Seats]    = DB_GetFieldIntByName(resVeh, "seats");
                        gSuvVehicleCount++;
                    }
                }
                case DEALER_CAT_BIKE: {
                    if (gBikeVehicleCount < MAX_DEALER_VEHICLES_PER_CAT) {
                        new idx = gBikeVehicleCount;
                        gBikeVehicles[idx][d_ModelID]  = DB_GetFieldIntByName(resVeh, "model_id");
                        DB_GetFieldStringByName(resVeh, "name", gBikeVehicles[idx][d_Name], 28);
                        DB_GetFieldStringByName(resVeh, "description", gBikeVehicles[idx][d_Type], 28);
                        gBikeVehicles[idx][d_Price]    = DB_GetFieldIntByName(resVeh, "price");
                        gBikeVehicles[idx][d_TopSpeed] = DB_GetFieldIntByName(resVeh, "top_speed");
                        gBikeVehicles[idx][d_Seats]    = DB_GetFieldIntByName(resVeh, "seats");
                        gBikeVehicleCount++;
                    }
                }
            }
            DB_SelectNextRow(resVeh);
        }
        DB_FreeResultSet(resVeh);
    }

    // 2. Load Colors from santara_master.db
    new DBResult:resCol = DB_ExecuteQuery(gDB_Master, "SELECT `color_id`, `name` FROM `dealership_colors` ORDER BY `id` ASC");
    if (resCol) {
        new colCount = DB_GetRowCount(resCol);
        for (new i = 0; i < colCount && i < MAX_DEALER_COLORS; i++) {
            gDealerColors[i] = DB_GetFieldIntByName(resCol, "color_id");
            DB_GetFieldStringByName(resCol, "name", gDealerColorNames[i], 24);
            gDealerColorCount++;
            DB_SelectNextRow(resCol);
        }
        DB_FreeResultSet(resCol);
    }

    printf("[Dealership] Sukses memuat %d Sport, %d Sedan, %d SUV, %d Motor, dan %d Warna dari santara_master.db ke RAM.",
        gSportVehicleCount, gSedanVehicleCount, gSuvVehicleCount, gBikeVehicleCount, gDealerColorCount);
    return 1;
}

// Colors from Reference Design
#define COLOR_DEALER_BG       0x1E1E2EFF  // Dark Indigo Background
#define COLOR_DEALER_PURPLE   0x5814EEFF  // Electric Purple Accent & Action
#define COLOR_DEALER_RED      0xFA1E38FF  // Vibrant Red Cancel & [X] Close Button
#define COLOR_DEALER_SLATE    0x3E3E44EE  // Dark Slate Button

// TextDraw Handles Dealership (Sisi Kanan X: 430.0 .. 620.0)
new PlayerText:TD_DealerBox[MAX_PLAYERS]       = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_DealerTopBar[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_DealerCloseBtn[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_DealerCatTile[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_DealerInfo[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_DealerPrev[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_DealerNext[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_DealerColorBtn[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_DealerCatBtn[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_DealerBuyBtn[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_DealerCancelBtn[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};

stock GetDealerCategoryCount(cat) {
    switch (cat) {
        case DEALER_CAT_SPORT: return gSportVehicleCount;
        case DEALER_CAT_SEDAN: return gSedanVehicleCount;
        case DEALER_CAT_SUV:   return gSuvVehicleCount;
        case DEALER_CAT_BIKE:  return gBikeVehicleCount;
    }
    return 0;
}

stock GetDealerCategoryName(cat, name[], len = 32) {
    switch (cat) {
        case DEALER_CAT_SPORT: format(name, len, "Mobil Sport");
        case DEALER_CAT_SEDAN: format(name, len, "Sedan & Klasik");
        case DEALER_CAT_SUV:   format(name, len, "SUV & Off-Road");
        case DEALER_CAT_BIKE:  format(name, len, "Motor & Skuter");
        default:               format(name, len, "Kendaraan");
    }
}

stock GetDealerVehicleData(cat, idx, &modelid, name[], type[], &price, &topspeed, &seats) {
    switch (cat) {
        case DEALER_CAT_SPORT: {
            if (idx < 0 || idx >= gSportVehicleCount) idx = 0;
            modelid  = gSportVehicles[idx][d_ModelID];
            format(name, 28, "%s", gSportVehicles[idx][d_Name]);
            format(type, 28, "%s", gSportVehicles[idx][d_Type]);
            price    = gSportVehicles[idx][d_Price];
            topspeed = gSportVehicles[idx][d_TopSpeed];
            seats    = gSportVehicles[idx][d_Seats];
        }
        case DEALER_CAT_SEDAN: {
            if (idx < 0 || idx >= gSedanVehicleCount) idx = 0;
            modelid  = gSedanVehicles[idx][d_ModelID];
            format(name, 28, "%s", gSedanVehicles[idx][d_Name]);
            format(type, 28, "%s", gSedanVehicles[idx][d_Type]);
            price    = gSedanVehicles[idx][d_Price];
            topspeed = gSedanVehicles[idx][d_TopSpeed];
            seats    = gSedanVehicles[idx][d_Seats];
        }
        case DEALER_CAT_SUV: {
            if (idx < 0 || idx >= gSuvVehicleCount) idx = 0;
            modelid  = gSuvVehicles[idx][d_ModelID];
            format(name, 28, "%s", gSuvVehicles[idx][d_Name]);
            format(type, 28, "%s", gSuvVehicles[idx][d_Type]);
            price    = gSuvVehicles[idx][d_Price];
            topspeed = gSuvVehicles[idx][d_TopSpeed];
            seats    = gSuvVehicles[idx][d_Seats];
        }
        case DEALER_CAT_BIKE: {
            if (idx < 0 || idx >= gBikeVehicleCount) idx = 0;
            modelid  = gBikeVehicles[idx][d_ModelID];
            format(name, 28, "%s", gBikeVehicles[idx][d_Name]);
            format(type, 28, "%s", gBikeVehicles[idx][d_Type]);
            price    = gBikeVehicles[idx][d_Price];
            topspeed = gBikeVehicles[idx][d_TopSpeed];
            seats    = gBikeVehicles[idx][d_Seats];
        }
    }
}

stock DestroyPlayerDealerTextDraws(playerid) {
    if (TD_DealerBox[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_DealerBox[playerid]);
        TD_DealerBox[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_DealerTopBar[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_DealerTopBar[playerid]);
        TD_DealerTopBar[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_DealerCloseBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_DealerCloseBtn[playerid]);
        TD_DealerCloseBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_DealerCatTile[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_DealerCatTile[playerid]);
        TD_DealerCatTile[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_DealerInfo[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_DealerInfo[playerid]);
        TD_DealerInfo[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_DealerPrev[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_DealerPrev[playerid]);
        TD_DealerPrev[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_DealerNext[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_DealerNext[playerid]);
        TD_DealerNext[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_DealerColorBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_DealerColorBtn[playerid]);
        TD_DealerColorBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_DealerCatBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_DealerCatBtn[playerid]);
        TD_DealerCatBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_DealerBuyBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_DealerBuyBtn[playerid]);
        TD_DealerBuyBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_DealerCancelBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_DealerCancelBtn[playerid]);
        TD_DealerCancelBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
}

stock CreatePlayerDealerTextDraws(playerid) {
    DestroyPlayerDealerTextDraws(playerid);

    // 1. Background Box (Dark Indigo #1E1E2EFF di Kanan X: 430.0 .. 620.0, Y: 85.0 .. 298.0)
    TD_DealerBox[playerid] = CreatePlayerTextDraw(playerid, 430.0, 85.0, "_");
    PlayerTextDrawUseBox(playerid, TD_DealerBox[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_DealerBox[playerid], COLOR_DEALER_BG);
    PlayerTextDrawTextSize(playerid, TD_DealerBox[playerid], 620.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_DealerBox[playerid], 0.0, 23.5);
    PlayerTextDrawSetSelectable(playerid, TD_DealerBox[playerid], false);

    // 2. Top Accent Line (Electric Purple #5814EEFF, X: 430.0 .. 602.0, Y: 85.0)
    TD_DealerTopBar[playerid] = CreatePlayerTextDraw(playerid, 430.0, 85.0, "_");
    PlayerTextDrawUseBox(playerid, TD_DealerTopBar[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_DealerTopBar[playerid], COLOR_DEALER_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_DealerTopBar[playerid], 602.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_DealerTopBar[playerid], 0.0, 0.75);
    PlayerTextDrawSetSelectable(playerid, TD_DealerTopBar[playerid], false);

    // 3. Top-Right Red Close Button [X] (Center X: 611.0, Y: 84.0)
    TD_DealerCloseBtn[playerid] = CreatePlayerTextDraw(playerid, 611.0, 84.0, "X");
    PlayerTextDrawFont(playerid, TD_DealerCloseBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_DealerCloseBtn[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_DealerCloseBtn[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_DealerCloseBtn[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_DealerCloseBtn[playerid], COLOR_DEALER_RED);
    PlayerTextDrawTextSize(playerid, TD_DealerCloseBtn[playerid], 10.0, 18.0);
    PlayerTextDrawAlignment(playerid, TD_DealerCloseBtn[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_DealerCloseBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_DealerCloseBtn[playerid], true);

    // 4. Header Title Tile [ Kategori : Mobil Sport ] (Center X: 525.0, Y: 97.0)
    TD_DealerCatTile[playerid] = CreatePlayerTextDraw(playerid, 525.0, 97.0, "Kategori : Mobil Sport");
    PlayerTextDrawFont(playerid, TD_DealerCatTile[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_DealerCatTile[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_DealerCatTile[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_DealerCatTile[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_DealerCatTile[playerid], COLOR_DEALER_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_DealerCatTile[playerid], 14.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_DealerCatTile[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_DealerCatTile[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_DealerCatTile[playerid], false);

    // 5. Vehicle Info Text Box (Kendaraan, Harga, Uang Anda, Jumlah Kursi, Pilihan) (X: 442.0, Y: 118.0)
    TD_DealerInfo[playerid] = CreatePlayerTextDraw(playerid, 442.0, 118.0, "Memuat info kendaraan...");
    PlayerTextDrawFont(playerid, TD_DealerInfo[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_DealerInfo[playerid], 0.18, 0.95);
    PlayerTextDrawColor(playerid, TD_DealerInfo[playerid], 0xFFFFFFFF);
    PlayerTextDrawSetOutline(playerid, TD_DealerInfo[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_DealerInfo[playerid], false);

    // 6. Navigation Button: < Sebelum (Center X: 481.0, Y: 178.0)
    TD_DealerPrev[playerid] = CreatePlayerTextDraw(playerid, 481.0, 178.0, "< Sebelum");
    PlayerTextDrawFont(playerid, TD_DealerPrev[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_DealerPrev[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_DealerPrev[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_DealerPrev[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_DealerPrev[playerid], COLOR_DEALER_SLATE);
    PlayerTextDrawTextSize(playerid, TD_DealerPrev[playerid], 14.0, 82.0);
    PlayerTextDrawAlignment(playerid, TD_DealerPrev[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_DealerPrev[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_DealerPrev[playerid], true);

    // 7. Navigation Button: Selanjutnya > (Center X: 569.0, Y: 178.0)
    TD_DealerNext[playerid] = CreatePlayerTextDraw(playerid, 569.0, 178.0, "Selanjutnya >");
    PlayerTextDrawFont(playerid, TD_DealerNext[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_DealerNext[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_DealerNext[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_DealerNext[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_DealerNext[playerid], COLOR_DEALER_SLATE);
    PlayerTextDrawTextSize(playerid, TD_DealerNext[playerid], 14.0, 82.0);
    PlayerTextDrawAlignment(playerid, TD_DealerNext[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_DealerNext[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_DealerNext[playerid], true);

    // 8. Action Button: [ Ganti Warna ] (Center X: 525.0, Y: 200.0)
    TD_DealerColorBtn[playerid] = CreatePlayerTextDraw(playerid, 525.0, 200.0, "Ganti Warna");
    PlayerTextDrawFont(playerid, TD_DealerColorBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_DealerColorBtn[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_DealerColorBtn[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_DealerColorBtn[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_DealerColorBtn[playerid], COLOR_DEALER_SLATE);
    PlayerTextDrawTextSize(playerid, TD_DealerColorBtn[playerid], 14.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_DealerColorBtn[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_DealerColorBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_DealerColorBtn[playerid], true);

    // 9. Action Button: [ Ganti Kategori ] (Center X: 525.0, Y: 222.0)
    TD_DealerCatBtn[playerid] = CreatePlayerTextDraw(playerid, 525.0, 222.0, "Ganti Kategori");
    PlayerTextDrawFont(playerid, TD_DealerCatBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_DealerCatBtn[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_DealerCatBtn[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_DealerCatBtn[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_DealerCatBtn[playerid], COLOR_DEALER_SLATE);
    PlayerTextDrawTextSize(playerid, TD_DealerCatBtn[playerid], 14.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_DealerCatBtn[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_DealerCatBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_DealerCatBtn[playerid], true);

    // 10. Primary Action Button: [ Beli ] (Center X: 525.0, Y: 246.0)
    TD_DealerBuyBtn[playerid] = CreatePlayerTextDraw(playerid, 525.0, 246.0, "Beli");
    PlayerTextDrawFont(playerid, TD_DealerBuyBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_DealerBuyBtn[playerid], 0.17, 1.05);
    PlayerTextDrawColor(playerid, TD_DealerBuyBtn[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_DealerBuyBtn[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_DealerBuyBtn[playerid], COLOR_DEALER_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_DealerBuyBtn[playerid], 15.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_DealerBuyBtn[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_DealerBuyBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_DealerBuyBtn[playerid], true);

    // 11. Secondary Button: [ Batal ] (Center X: 525.0, Y: 268.0)
    TD_DealerCancelBtn[playerid] = CreatePlayerTextDraw(playerid, 525.0, 268.0, "Batal");
    PlayerTextDrawFont(playerid, TD_DealerCancelBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_DealerCancelBtn[playerid], 0.17, 1.05);
    PlayerTextDrawColor(playerid, TD_DealerCancelBtn[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_DealerCancelBtn[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_DealerCancelBtn[playerid], COLOR_DEALER_RED);
    PlayerTextDrawTextSize(playerid, TD_DealerCancelBtn[playerid], 15.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_DealerCancelBtn[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_DealerCancelBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_DealerCancelBtn[playerid], true);
}

stock UpdateDealershipUI(playerid) {
    if (!gPlayerData[playerid][p_InDealership]) return;

    new cat = gPlayerData[playerid][p_DealerCat];
    new idx = gPlayerData[playerid][p_DealerIndex];

    new modelid, name[28], type[28], price, topspeed, seats;
    GetDealerVehicleData(cat, idx, modelid, name, type, price, topspeed, seats);

    new catName[32];
    GetDealerCategoryName(cat, catName, sizeof(catName));

    new catTileStr[64];
    format(catTileStr, sizeof(catTileStr), "Kategori : %s", catName);
    PlayerTextDrawSetString(playerid, TD_DealerCatTile[playerid], catTileStr);

    new priceFmt[32], cashFmt[32];
    FormatRupiah(price, priceFmt, sizeof(priceFmt));
    FormatRupiah(gPlayerData[playerid][p_Cash], cashFmt, sizeof(cashFmt));
    new count = GetDealerCategoryCount(cat);

    new infoStr[256];
    format(infoStr, sizeof(infoStr),
        "~w~Kendaraan : ~w~%s~n~" \
        "~w~Harga : ~w~%s~n~" \
        "~w~Uang Anda : ~w~%s~n~" \
        "~w~Jumlah Kursi : ~w~%d Kursi~n~" \
        "~w~Pilihan : ~w~%d/%d",
        name, priceFmt, cashFmt, seats, idx + 1, count);

    PlayerTextDrawSetString(playerid, TD_DealerInfo[playerid], infoStr);

    PlayerTextDrawShow(playerid, TD_DealerCatTile[playerid]);
    PlayerTextDrawShow(playerid, TD_DealerInfo[playerid]);
}

stock UpdateDealershipPreview(playerid) {
    if (!gPlayerData[playerid][p_InDealership]) return;

    new cat = gPlayerData[playerid][p_DealerCat];
    new idx = gPlayerData[playerid][p_DealerIndex];
    new colorIdx = gPlayerData[playerid][p_DealerColorIdx];

    new modelid, name[28], type[28], price, topspeed, seats;
    GetDealerVehicleData(cat, idx, modelid, name, type, price, topspeed, seats);

    // Hapus kendaraan display sebelumnya jika ada
    if (gPlayerData[playerid][p_DealerPreviewVeh] != INVALID_VEHICLE_ID) {
        DestroyVehicle(gPlayerData[playerid][p_DealerPreviewVeh]);
        gPlayerData[playerid][p_DealerPreviewVeh] = INVALID_VEHICLE_ID;
    }

    // Spawn kendaraan preview di atas panggung showcase
    new color = gDealerColors[colorIdx];
    gPlayerData[playerid][p_DealerPreviewVeh] = CreateVehicle(
        modelid,
        DEALER_PREVIEW_X, DEALER_PREVIEW_Y, DEALER_PREVIEW_Z, DEALER_PREVIEW_A,
        color, color, -1
    );

    // Matikan mesin & kunci pintu kendaraan preview
    if (gPlayerData[playerid][p_DealerPreviewVeh] != INVALID_VEHICLE_ID) {
        SetVehicleParamsEx(gPlayerData[playerid][p_DealerPreviewVeh], 0, 0, 0, 1, 0, 0, 0);
        SetVehicleVirtualWorld(gPlayerData[playerid][p_DealerPreviewVeh], 0);
    }

    UpdateDealershipUI(playerid);
}

stock OpenDealership(playerid) {
    if (!IsPlayerConnected(playerid) || !gPlayerData[playerid][p_LoggedIn]) return 0;
    if (gPlayerData[playerid][p_InDealership]) return 0;

    gPlayerData[playerid][p_InDealership]   = true;
    gPlayerData[playerid][p_DealerCat]      = DEALER_CAT_SPORT;
    gPlayerData[playerid][p_DealerIndex]    = 0;
    gPlayerData[playerid][p_DealerColorIdx] = 0;

    // Freeze pemain & posisikan kamera sinematik dealer
    TogglePlayerControllable(playerid, false);
    SetPlayerCameraPos(playerid, DEALER_CAM_X, DEALER_CAM_Y, DEALER_CAM_Z);
    SetPlayerCameraLookAt(playerid, DEALER_LOOK_X, DEALER_LOOK_Y, DEALER_LOOK_Z, CAMERA_CUT);

    // Hapus TextDraws lama & sembunyikan HUD uang
    DestroyPlayerDealerTextDraws(playerid);
    HidePlayerMoneyHUD(playerid);

    CreatePlayerDealerTextDraws(playerid);

    // Tampilkan semua TextDraw ke pemain
    PlayerTextDrawShow(playerid, TD_DealerBox[playerid]);
    PlayerTextDrawShow(playerid, TD_DealerTopBar[playerid]);
    PlayerTextDrawShow(playerid, TD_DealerCloseBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_DealerCatTile[playerid]);
    PlayerTextDrawShow(playerid, TD_DealerInfo[playerid]);
    PlayerTextDrawShow(playerid, TD_DealerPrev[playerid]);
    PlayerTextDrawShow(playerid, TD_DealerNext[playerid]);
    PlayerTextDrawShow(playerid, TD_DealerColorBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_DealerCatBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_DealerBuyBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_DealerCancelBtn[playerid]);

    // Aktifkan mode kursor mouse (Electric Purple)
    SelectTextDraw(playerid, COLOR_DEALER_PURPLE);

    // Tampilkan kendaraan preview pertama
    UpdateDealershipPreview(playerid);
    return 1;
}

stock CloseDealership(playerid) {
    if (!gPlayerData[playerid][p_InDealership]) return;

    gPlayerData[playerid][p_InDealership] = false;

    // Hapus kendaraan display
    if (gPlayerData[playerid][p_DealerPreviewVeh] != INVALID_VEHICLE_ID) {
        DestroyVehicle(gPlayerData[playerid][p_DealerPreviewVeh]);
        gPlayerData[playerid][p_DealerPreviewVeh] = INVALID_VEHICLE_ID;
    }

    // Hapus TextDraws & batalkan kursor mouse
    DestroyPlayerDealerTextDraws(playerid);
    CancelSelectTextDraw(playerid);

    // Kembalikan kamera dan kontrol pemain
    TogglePlayerControllable(playerid, true);
    SetCameraBehindPlayer(playerid);
    ShowPlayerMoneyHUD(playerid);
}

stock ShowDealerCatDialog(playerid) {
    new dialogText[256];
    format(dialogText, sizeof(dialogText),
        "[Mobil] Mobil Sport & Supercar\t(%d Unit)\n" \
        " Mobil Sedan & Klasik\t(%d Unit)\n" \
        "  SUV, Pick-up & Off-Road\t(%d Unit)\n" \
        "   Sepeda Motor & Skuter\t(%d Unit)",
        gSportVehicleCount,
        gSedanVehicleCount,
        gSuvVehicleCount,
        gBikeVehicleCount);

    ShowPlayerDialog(playerid, DLG_DEALER_CAT, DIALOG_STYLE_LIST,
        "{5814EE}Pilih Kategori Kendaraan Dealership",
        dialogText, "Pilih", "Batal");
}

stock HandleDealershipDialog(playerid, dialogid, response, listitem) {
    if (dialogid != DLG_DEALER_CAT) return 0;
    if (!gPlayerData[playerid][p_InDealership]) return 1;

    if (response) {
        gPlayerData[playerid][p_DealerCat] = listitem;
        gPlayerData[playerid][p_DealerIndex] = 0;
        UpdateDealershipPreview(playerid);
        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
    }
    // Re-enable select textdraw in case dialog closed
    SelectTextDraw(playerid, COLOR_DEALER_PURPLE);
    return 1;
}

// Forward deklarasi fungsi pembelian dari ownership.inc
forward BuyCurrentDealerVehicle(playerid);

stock HandleDealershipClick(playerid, PlayerText:playertextid) {
    if (!gPlayerData[playerid][p_InDealership]) return 0;

    // 1. Tombol [X] Merah atau BATAL
    if (playertextid == TD_DealerCloseBtn[playerid] || playertextid == TD_DealerCancelBtn[playerid]) {
        PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
        CloseDealership(playerid);
        return 1;
    }

    // 2. Tombol < SEBELUM
    if (playertextid == TD_DealerPrev[playerid]) {
        new cat = gPlayerData[playerid][p_DealerCat];
        new count = GetDealerCategoryCount(cat);
        gPlayerData[playerid][p_DealerIndex]--;
        if (gPlayerData[playerid][p_DealerIndex] < 0) {
            gPlayerData[playerid][p_DealerIndex] = count - 1;
        }
        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
        UpdateDealershipPreview(playerid);
        return 1;
    }

    // 3. Tombol SELANJUTNYA >
    if (playertextid == TD_DealerNext[playerid]) {
        new cat = gPlayerData[playerid][p_DealerCat];
        new count = GetDealerCategoryCount(cat);
        gPlayerData[playerid][p_DealerIndex]++;
        if (gPlayerData[playerid][p_DealerIndex] >= count) {
            gPlayerData[playerid][p_DealerIndex] = 0;
        }
        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
        UpdateDealershipPreview(playerid);
        return 1;
    }

    // 4. Tombol GANTI WARNA
    if (playertextid == TD_DealerColorBtn[playerid]) {
        gPlayerData[playerid][p_DealerColorIdx]++;
        if (gPlayerData[playerid][p_DealerColorIdx] >= DEALER_COLOR_COUNT) {
            gPlayerData[playerid][p_DealerColorIdx] = 0;
        }
        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
        UpdateDealershipPreview(playerid);
        return 1;
    }

    // 5. Tombol GANTI KATEGORI
    if (playertextid == TD_DealerCatBtn[playerid]) {
        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
        ShowDealerCatDialog(playerid);
        return 1;
    }

    // 6. Tombol BELI
    if (playertextid == TD_DealerBuyBtn[playerid]) {
        BuyCurrentDealerVehicle(playerid);
        return 1;
    }

    return 0;
}
