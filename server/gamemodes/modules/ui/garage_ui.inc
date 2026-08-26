#if defined _MODULE_GARAGE_UI_INC
    #endinput
#endif
#define _MODULE_GARAGE_UI_INC

// ============================================================
//  SantaraBaru Roleplay - Live 3D Public City Garage UI (/garasi)
//  Dark Indigo (#1E1E2E) & Electric Purple (#5814EE) Theme
// ============================================================

// Colors from Reference Design
#define COLOR_GARAGE_BG       0x1E1E2EFF  // Dark Indigo Background
#define COLOR_GARAGE_PURPLE   0x5814EEFF  // Electric Purple Accent & Action
#define COLOR_GARAGE_RED      0xFA1E38FF  // Vibrant Red Cancel & [X] Close Button
#define COLOR_GARAGE_SLATE    0x3E3E44EE  // Dark Slate Button (< Sebelum / Selanjutnya >)

// TextDraw Handles Garasi (Sisi Kanan X: 430.0 .. 620.0)
new PlayerText:TD_GarageBox[MAX_PLAYERS]       = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_GarageTopBar[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_GarageCloseBtn[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_GarageTitle[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_GarageInfo[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_GaragePrev[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_GarageNext[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_GarageSpawnBtn[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_GarageCancelBtn[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};

// Forward declaration untuk fungsi kepemilikan kendaraan
forward SpawnPlayerVehicleFromGarage(playerid, dbVehId, garageId);

stock DestroyPlayerGarageTextDraws(playerid) {
    if (TD_GarageBox[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_GarageBox[playerid]);
        TD_GarageBox[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_GarageTopBar[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_GarageTopBar[playerid]);
        TD_GarageTopBar[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_GarageCloseBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_GarageCloseBtn[playerid]);
        TD_GarageCloseBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_GarageTitle[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_GarageTitle[playerid]);
        TD_GarageTitle[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_GarageInfo[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_GarageInfo[playerid]);
        TD_GarageInfo[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_GaragePrev[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_GaragePrev[playerid]);
        TD_GaragePrev[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_GarageNext[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_GarageNext[playerid]);
        TD_GarageNext[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_GarageSpawnBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_GarageSpawnBtn[playerid]);
        TD_GarageSpawnBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_GarageCancelBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_GarageCancelBtn[playerid]);
        TD_GarageCancelBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
}

stock CreatePlayerGarageTextDraws(playerid) {
    DestroyPlayerGarageTextDraws(playerid);

    // 1. Box Panel Belakang (Dark Indigo #1E1E2EFF di Kanan X: 430.0 .. 620.0, Y: 100.0 .. 255.0)
    TD_GarageBox[playerid] = CreatePlayerTextDraw(playerid, 430.0, 100.0, "_");
    PlayerTextDrawUseBox(playerid, TD_GarageBox[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_GarageBox[playerid], COLOR_GARAGE_BG);
    PlayerTextDrawTextSize(playerid, TD_GarageBox[playerid], 620.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_GarageBox[playerid], 0.0, 17.0);
    PlayerTextDrawSetSelectable(playerid, TD_GarageBox[playerid], false);

    // 2. Top Accent Line (Electric Purple #5814EEFF, X: 430.0 .. 602.0, Y: 100.0)
    TD_GarageTopBar[playerid] = CreatePlayerTextDraw(playerid, 430.0, 100.0, "_");
    PlayerTextDrawUseBox(playerid, TD_GarageTopBar[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_GarageTopBar[playerid], COLOR_GARAGE_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_GarageTopBar[playerid], 602.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_GarageTopBar[playerid], 0.0, 0.75);
    PlayerTextDrawSetSelectable(playerid, TD_GarageTopBar[playerid], false);

    // 3. Top-Right Red Close Button [X] (Center X: 611.0, Y: 99.0)
    TD_GarageCloseBtn[playerid] = CreatePlayerTextDraw(playerid, 611.0, 99.0, "X");
    PlayerTextDrawFont(playerid, TD_GarageCloseBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_GarageCloseBtn[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_GarageCloseBtn[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_GarageCloseBtn[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_GarageCloseBtn[playerid], COLOR_GARAGE_RED);
    PlayerTextDrawTextSize(playerid, TD_GarageCloseBtn[playerid], 10.0, 18.0);
    PlayerTextDrawAlignment(playerid, TD_GarageCloseBtn[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_GarageCloseBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_GarageCloseBtn[playerid], true);

    // 4. Header Title Tile [ Nama Parkiran ] (Center X: 525.0, Y: 112.0)
    TD_GarageTitle[playerid] = CreatePlayerTextDraw(playerid, 525.0, 112.0, "Parkiran Kota");
    PlayerTextDrawFont(playerid, TD_GarageTitle[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_GarageTitle[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_GarageTitle[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_GarageTitle[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_GarageTitle[playerid], COLOR_GARAGE_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_GarageTitle[playerid], 14.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_GarageTitle[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_GarageTitle[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_GarageTitle[playerid], false);

    // 5. Vehicle Info Section (Model, Plat Nomor, Kondisi) (X: 442.0, Y: 134.0)
    TD_GarageInfo[playerid] = CreatePlayerTextDraw(playerid, 442.0, 134.0, "Memuat info kendaraan...");
    PlayerTextDrawFont(playerid, TD_GarageInfo[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_GarageInfo[playerid], 0.18, 1.00);
    PlayerTextDrawColor(playerid, TD_GarageInfo[playerid], 0xFFFFFFFF);
    PlayerTextDrawSetOutline(playerid, TD_GarageInfo[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_GarageInfo[playerid], false);

    // 6. Navigation Button: < Sebelum (Center X: 481.0, Y: 172.0)
    TD_GaragePrev[playerid] = CreatePlayerTextDraw(playerid, 481.0, 172.0, "< Sebelum");
    PlayerTextDrawFont(playerid, TD_GaragePrev[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_GaragePrev[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_GaragePrev[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_GaragePrev[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_GaragePrev[playerid], COLOR_GARAGE_SLATE);
    PlayerTextDrawTextSize(playerid, TD_GaragePrev[playerid], 14.0, 82.0);
    PlayerTextDrawAlignment(playerid, TD_GaragePrev[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_GaragePrev[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_GaragePrev[playerid], true);

    // 7. Navigation Button: Selanjutnya > (Center X: 569.0, Y: 172.0)
    TD_GarageNext[playerid] = CreatePlayerTextDraw(playerid, 569.0, 172.0, "Selanjutnya >");
    PlayerTextDrawFont(playerid, TD_GarageNext[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_GarageNext[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_GarageNext[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_GarageNext[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_GarageNext[playerid], COLOR_GARAGE_SLATE);
    PlayerTextDrawTextSize(playerid, TD_GarageNext[playerid], 14.0, 82.0);
    PlayerTextDrawAlignment(playerid, TD_GarageNext[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_GarageNext[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_GarageNext[playerid], true);

    // 8. Primary Action Button: [ Gunakan ] (Center X: 525.0, Y: 196.0)
    TD_GarageSpawnBtn[playerid] = CreatePlayerTextDraw(playerid, 525.0, 196.0, "Gunakan");
    PlayerTextDrawFont(playerid, TD_GarageSpawnBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_GarageSpawnBtn[playerid], 0.17, 1.05);
    PlayerTextDrawColor(playerid, TD_GarageSpawnBtn[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_GarageSpawnBtn[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_GarageSpawnBtn[playerid], COLOR_GARAGE_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_GarageSpawnBtn[playerid], 15.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_GarageSpawnBtn[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_GarageSpawnBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_GarageSpawnBtn[playerid], true);

    // 9. Secondary Button: [ Batal ] (Center X: 525.0, Y: 218.0)
    TD_GarageCancelBtn[playerid] = CreatePlayerTextDraw(playerid, 525.0, 218.0, "Batal");
    PlayerTextDrawFont(playerid, TD_GarageCancelBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_GarageCancelBtn[playerid], 0.17, 1.05);
    PlayerTextDrawColor(playerid, TD_GarageCancelBtn[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_GarageCancelBtn[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_GarageCancelBtn[playerid], COLOR_GARAGE_RED);
    PlayerTextDrawTextSize(playerid, TD_GarageCancelBtn[playerid], 15.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_GarageCancelBtn[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_GarageCancelBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_GarageCancelBtn[playerid], true);
}

stock UpdateGaragePreview(playerid) {
    if (!gPlayerData[playerid][p_InGarageUI]) return;

    new idx = gPlayerData[playerid][p_GarageVehIndex];
    new dbId = gPlayerData[playerid][p_GarageVehDBIDs][idx];

    new query[128];
    format(query, sizeof(query), "SELECT * FROM `player_vehicles` WHERE `id`=%d LIMIT 1", dbId);
    new DBResult:res = DB_ExecuteQuery(gDB, query);
    if (!res || DB_GetRowCount(res) == 0) {
        if (res) DB_FreeResultSet(res);
        return;
    }

    new modelid = DB_GetFieldIntByName(res, "model_id");
    new color1  = DB_GetFieldIntByName(res, "color1");
    new color2  = DB_GetFieldIntByName(res, "color2");
    new Float:vhp = DB_GetFieldFloatByName(res, "health");
    new plate[16];
    DB_GetFieldStringByName(res, "plate", plate, sizeof(plate));
    DB_FreeResultSet(res);

    // Ambil data posisi garasi saat ini
    new gName[48], gCity[24];
    new Float:camX, Float:camY, Float:camZ, Float:lookX, Float:lookY, Float:lookZ;
    new Float:spX, Float:spY, Float:spZ, Float:spA;
    GetGarageInfo(gPlayerData[playerid][p_GarageCurrentID], gName, gCity, camX, camY, camZ, lookX, lookY, lookZ, spX, spY, spZ, spA);

    // Update TextDraw Title dengan nama garasi
    new titleStr[64];
    format(titleStr, sizeof(titleStr), "%s", gName);
    PlayerTextDrawSetString(playerid, TD_GarageTitle[playerid], titleStr);

    // Dapatkan nama model kendaraan
    new vehName[32];
    GetModelFullName(modelid, vehName, sizeof(vehName));

    // Hitung persentase darah mesin
    new hpPct = floatround((vhp / 1000.0) * 100.0);
    if (hpPct > 100) hpPct = 100;
    if (hpPct < 0) hpPct = 0;

    // Update Teks Info Kendaraan
    new infoStr[192];
    format(infoStr, sizeof(infoStr),
        "~w~Model : ~w~%s~n~" \
        "~w~Plat Nomor : ~w~%s~n~" \
        "~w~Kondisi : ~w~%d%%",
        vehName, plate, hpPct);
    PlayerTextDrawSetString(playerid, TD_GarageInfo[playerid], infoStr);

    // Refresh TextDraws ke player
    PlayerTextDrawShow(playerid, TD_GarageTitle[playerid]);
    PlayerTextDrawShow(playerid, TD_GarageInfo[playerid]);

    // Hapus kendaraan display sebelumnya jika ada
    if (gPlayerData[playerid][p_GaragePreviewVeh] != INVALID_VEHICLE_ID) {
        DestroyVehicle(gPlayerData[playerid][p_GaragePreviewVeh]);
        gPlayerData[playerid][p_GaragePreviewVeh] = INVALID_VEHICLE_ID;
    }

    // Spawn kendaraan preview 3D di titik display garasi
    new vehId = CreateVehicle(modelid, spX, spY, spZ, spA, color1, color2, -1);
    if (vehId != INVALID_VEHICLE_ID) {
        SetVehicleNumberPlate(vehId, plate);
        SetVehicleToRespawn(vehId);
        SetVehiclePos(vehId, spX, spY, spZ);
        SetVehicleZAngle(vehId, spA);
        SetVehicleParamsEx(vehId, 0, 0, 0, 0, 0, 0, 0);
        gPlayerData[playerid][p_GaragePreviewVeh] = vehId;
    }

    // Set Kamera Sinematik ke Display Garasi
    SetPlayerCameraPos(playerid, camX, camY, camZ);
    SetPlayerCameraLookAt(playerid, lookX, lookY, lookZ);
}

stock OpenGarageUI(playerid, garageId) {
    if (!gPlayerData[playerid][p_LoggedIn] || !gPlayerData[playerid][p_Spawned]) return 0;
    if (gPlayerData[playerid][p_CharID] <= 0) return 0;

    // Ambil semua kendaraan milik karakter yang HANYA berstatus tersimpan di garasi
    new query[256];
    format(query, sizeof(query),
        "SELECT `id` FROM `player_vehicles` WHERE `char_id`=%d AND `status`=%d ORDER BY `id` ASC",
        gPlayerData[playerid][p_CharID], VEH_STATUS_GARAGE);

    new DBResult:res = DB_ExecuteQuery(gDB, query);
    new count = 0;
    if (res) {
        count = DB_GetRowCount(res);
        if (count > 0) {
            for (new i = 0; i < count && i < 32; i++) {
                gPlayerData[playerid][p_GarageVehDBIDs][i] = DB_GetFieldIntByName(res, "id");
                DB_SelectNextRow(res);
            }
        }
        DB_FreeResultSet(res);
    }

    if (count <= 0) {
        SendClientMessage(playerid, COL_RED, "  [Garasi] Anda tidak memiliki kendaraan yang tersimpan di dalam garasi!");
        SendClientMessage(playerid, COL_YELLOW, "  > Jika kendaraan Anda tertinggal di luar saat restart atau hancur, tebus di Asuransi ({00EEFF}/asuransi{FFFF00}).");
        return 0;
    }

    gPlayerData[playerid][p_InGarageUI] = true;
    gPlayerData[playerid][p_GarageCurrentID] = garageId;
    gPlayerData[playerid][p_GarageVehCount] = count;
    gPlayerData[playerid][p_GarageVehIndex] = 0;

    TogglePlayerControllable(playerid, false);
    HidePlayerMoneyHUD(playerid);

    CreatePlayerGarageTextDraws(playerid);

    // Tampilkan semua TextDraw ke pemain
    PlayerTextDrawShow(playerid, TD_GarageBox[playerid]);
    PlayerTextDrawShow(playerid, TD_GarageTopBar[playerid]);
    PlayerTextDrawShow(playerid, TD_GarageCloseBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_GarageTitle[playerid]);
    PlayerTextDrawShow(playerid, TD_GarageInfo[playerid]);
    PlayerTextDrawShow(playerid, TD_GaragePrev[playerid]);
    PlayerTextDrawShow(playerid, TD_GarageNext[playerid]);
    PlayerTextDrawShow(playerid, TD_GarageSpawnBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_GarageCancelBtn[playerid]);

    SelectTextDraw(playerid, COLOR_GARAGE_PURPLE);
    UpdateGaragePreview(playerid);

    PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
    return 1;
}

stock CloseGarageUI(playerid) {
    if (!gPlayerData[playerid][p_InGarageUI]) return;

    gPlayerData[playerid][p_InGarageUI] = false;

    // Hapus kendaraan preview
    if (gPlayerData[playerid][p_GaragePreviewVeh] != INVALID_VEHICLE_ID) {
        DestroyVehicle(gPlayerData[playerid][p_GaragePreviewVeh]);
        gPlayerData[playerid][p_GaragePreviewVeh] = INVALID_VEHICLE_ID;
    }

    DestroyPlayerGarageTextDraws(playerid);
    CancelSelectTextDraw(playerid);

    TogglePlayerControllable(playerid, true);
    SetCameraBehindPlayer(playerid);
    ShowPlayerMoneyHUD(playerid);
}

stock HandleGarageClick(playerid, PlayerText:playertextid) {
    if (!gPlayerData[playerid][p_InGarageUI]) return 0;

    // 1. Tombol [X] Merah atau BATAL
    if (playertextid == TD_GarageCloseBtn[playerid] || playertextid == TD_GarageCancelBtn[playerid]) {
        CloseGarageUI(playerid);
        PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
        SendClientMessage(playerid, COL_GREY, "  * Pengambilan kendaraan di garasi dibatalkan.");
        return 1;
    }

    // 2. Tombol < SEBELUM
    if (playertextid == TD_GaragePrev[playerid]) {
        gPlayerData[playerid][p_GarageVehIndex]--;
        if (gPlayerData[playerid][p_GarageVehIndex] < 0) {
            gPlayerData[playerid][p_GarageVehIndex] = gPlayerData[playerid][p_GarageVehCount] - 1;
        }
        UpdateGaragePreview(playerid);
        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
        return 1;
    }

    // 3. Tombol SELANJUTNYA >
    if (playertextid == TD_GarageNext[playerid]) {
        gPlayerData[playerid][p_GarageVehIndex]++;
        if (gPlayerData[playerid][p_GarageVehIndex] >= gPlayerData[playerid][p_GarageVehCount]) {
            gPlayerData[playerid][p_GarageVehIndex] = 0;
        }
        UpdateGaragePreview(playerid);
        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
        return 1;
    }

    // 4. Tombol [ GUNAKAN ]
    if (playertextid == TD_GarageSpawnBtn[playerid]) {
        new idx = gPlayerData[playerid][p_GarageVehIndex];
        new dbId = gPlayerData[playerid][p_GarageVehDBIDs][idx];
        new gid = gPlayerData[playerid][p_GarageCurrentID];

        CloseGarageUI(playerid);
        SpawnPlayerVehicleFromGarage(playerid, dbId, gid);
        PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
        return 1;
    }

    return 0;
}
