#if defined _MODULE_GARAGE_UI_INC
    #endinput
#endif
#define _MODULE_GARAGE_UI_INC

// ============================================================
//  SantaraBaru Roleplay - Live 3D Public City Garage UI
// ============================================================

// TextDraw Handles Garasi (Sisi Kanan X: 430.0 .. 610.0, Match Dealership Style)
new PlayerText:TD_GarageBox[MAX_PLAYERS]       = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_GarageHeader[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_GarageTitle[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_GarageBadge[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_GarageInfo[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_GaragePrev[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_GarageNext[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_GarageSpawnBtn[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_GarageCancelBtn[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_GarageHint[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};

// Forward declaration untuk fungsi kepemilikan kendaraan
forward SpawnPlayerVehicleFromGarage(playerid, dbVehId, garageId);

stock DestroyPlayerGarageTextDraws(playerid) {
    if (TD_GarageBox[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_GarageBox[playerid]);
        TD_GarageBox[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_GarageHeader[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_GarageHeader[playerid]);
        TD_GarageHeader[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_GarageTitle[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_GarageTitle[playerid]);
        TD_GarageTitle[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_GarageBadge[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_GarageBadge[playerid]);
        TD_GarageBadge[playerid] = PlayerText:INVALID_TEXT_DRAW;
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
    if (TD_GarageHint[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_GarageHint[playerid]);
        TD_GarageHint[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
}

stock CreatePlayerGarageTextDraws(playerid) {
    DestroyPlayerGarageTextDraws(playerid);

    // 1. Box Panel Belakang (Transparan Gelap Mewah)
    TD_GarageBox[playerid] = CreatePlayerTextDraw(playerid, 430.0, 95.0, "_");
    PlayerTextDrawUseBox(playerid, TD_GarageBox[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_GarageBox[playerid], 0x111119E8);
    PlayerTextDrawTextSize(playerid, TD_GarageBox[playerid], 610.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_GarageBox[playerid], 0.0, 27.5);
    PlayerTextDrawSetSelectable(playerid, TD_GarageBox[playerid], false);

    // 2. Header Strip (Cyan / Teal Glow)
    TD_GarageHeader[playerid] = CreatePlayerTextDraw(playerid, 430.0, 95.0, "_");
    PlayerTextDrawUseBox(playerid, TD_GarageHeader[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_GarageHeader[playerid], 0x00BCD4FF);
    PlayerTextDrawTextSize(playerid, TD_GarageHeader[playerid], 610.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_GarageHeader[playerid], 0.0, 2.7);
    PlayerTextDrawSetSelectable(playerid, TD_GarageHeader[playerid], false);

    // 3. Header Title Text
    TD_GarageTitle[playerid] = CreatePlayerTextDraw(playerid, 520.0, 100.0, "GEDUNG PARKIR KOTA");
    PlayerTextDrawFont(playerid, TD_GarageTitle[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_GarageTitle[playerid], 0.23, 1.2);
    PlayerTextDrawColor(playerid, TD_GarageTitle[playerid], 0xFFFFFFFF);
    PlayerTextDrawAlignment(playerid, TD_GarageTitle[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_GarageTitle[playerid], true);
    PlayerTextDrawSetSelectable(playerid, TD_GarageTitle[playerid], false);

    // 4. Badge Indikator Unit
    TD_GarageBadge[playerid] = CreatePlayerTextDraw(playerid, 520.0, 126.0, "Unit: [ 1 / 1 ]");
    PlayerTextDrawFont(playerid, TD_GarageBadge[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_GarageBadge[playerid], 0.19, 1.05);
    PlayerTextDrawColor(playerid, TD_GarageBadge[playerid], 0x00EEFFFF);
    PlayerTextDrawAlignment(playerid, TD_GarageBadge[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_GarageBadge[playerid], true);
    PlayerTextDrawSetSelectable(playerid, TD_GarageBadge[playerid], false);

    // 5. Vehicle Info Text Box
    TD_GarageInfo[playerid] = CreatePlayerTextDraw(playerid, 438.0, 142.0, "Memuat info kendaraan...");
    PlayerTextDrawFont(playerid, TD_GarageInfo[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_GarageInfo[playerid], 0.20, 1.05);
    PlayerTextDrawColor(playerid, TD_GarageInfo[playerid], 0xFFFFFFFF);
    PlayerTextDrawSetOutline(playerid, TD_GarageInfo[playerid], true);
    PlayerTextDrawSetSelectable(playerid, TD_GarageInfo[playerid], false);

    // 6. Button: << PREV (Clickable)
    TD_GaragePrev[playerid] = CreatePlayerTextDraw(playerid, 438.0, 246.0, "< SEBELUM");
    PlayerTextDrawFont(playerid, TD_GaragePrev[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_GaragePrev[playerid], 0.20, 1.25);
    PlayerTextDrawColor(playerid, TD_GaragePrev[playerid], 0x00BCD4FF);
    PlayerTextDrawUseBox(playerid, TD_GaragePrev[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_GaragePrev[playerid], 0x2A2A2AFF);
    PlayerTextDrawTextSize(playerid, TD_GaragePrev[playerid], 517.0, 15.0);
    PlayerTextDrawSetOutline(playerid, TD_GaragePrev[playerid], true);
    PlayerTextDrawSetSelectable(playerid, TD_GaragePrev[playerid], true);

    // 7. Button: NEXT >> (Clickable)
    TD_GarageNext[playerid] = CreatePlayerTextDraw(playerid, 524.0, 246.0, "LANJUT >");
    PlayerTextDrawFont(playerid, TD_GarageNext[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_GarageNext[playerid], 0.20, 1.25);
    PlayerTextDrawColor(playerid, TD_GarageNext[playerid], 0x00BCD4FF);
    PlayerTextDrawUseBox(playerid, TD_GarageNext[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_GarageNext[playerid], 0x2A2A2AFF);
    PlayerTextDrawTextSize(playerid, TD_GarageNext[playerid], 602.0, 15.0);
    PlayerTextDrawSetOutline(playerid, TD_GarageNext[playerid], true);
    PlayerTextDrawSetSelectable(playerid, TD_GarageNext[playerid], true);

    // 8. Button: [ KELUARKAN MOBIL ] (Clickable)
    TD_GarageSpawnBtn[playerid] = CreatePlayerTextDraw(playerid, 438.0, 275.0, "  [ KELUARKAN MOBIL ]");
    PlayerTextDrawFont(playerid, TD_GarageSpawnBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_GarageSpawnBtn[playerid], 0.20, 1.35);
    PlayerTextDrawColor(playerid, TD_GarageSpawnBtn[playerid], 0x2ECC71FF);
    PlayerTextDrawUseBox(playerid, TD_GarageSpawnBtn[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_GarageSpawnBtn[playerid], 0x1A3828FF);
    PlayerTextDrawTextSize(playerid, TD_GarageSpawnBtn[playerid], 602.0, 16.0);
    PlayerTextDrawSetOutline(playerid, TD_GarageSpawnBtn[playerid], true);
    PlayerTextDrawSetSelectable(playerid, TD_GarageSpawnBtn[playerid], true);

    // 9. Button: [ BATAL / KELUAR ] (Clickable)
    TD_GarageCancelBtn[playerid] = CreatePlayerTextDraw(playerid, 438.0, 305.0, "   [ BATAL / KELUAR ]");
    PlayerTextDrawFont(playerid, TD_GarageCancelBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_GarageCancelBtn[playerid], 0.20, 1.25);
    PlayerTextDrawColor(playerid, TD_GarageCancelBtn[playerid], 0xE74C3CFF);
    PlayerTextDrawUseBox(playerid, TD_GarageCancelBtn[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_GarageCancelBtn[playerid], 0x3D1F1DFF);
    PlayerTextDrawTextSize(playerid, TD_GarageCancelBtn[playerid], 602.0, 15.0);
    PlayerTextDrawSetOutline(playerid, TD_GarageCancelBtn[playerid], true);
    PlayerTextDrawSetSelectable(playerid, TD_GarageCancelBtn[playerid], true);

    // 10. Hint Footer
    TD_GarageHint[playerid] = CreatePlayerTextDraw(playerid, 520.0, 335.0, "Klik menu di atas atau tekan ESC untuk keluar");
    PlayerTextDrawFont(playerid, TD_GarageHint[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_GarageHint[playerid], 0.17, 0.85);
    PlayerTextDrawColor(playerid, TD_GarageHint[playerid], 0xAAAAAAFF);
    PlayerTextDrawAlignment(playerid, TD_GarageHint[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_GarageHint[playerid], true);
    PlayerTextDrawSetSelectable(playerid, TD_GarageHint[playerid], false);

    // Tampilkan semua TextDraw ke pemain
    PlayerTextDrawShow(playerid, TD_GarageBox[playerid]);
    PlayerTextDrawShow(playerid, TD_GarageHeader[playerid]);
    PlayerTextDrawShow(playerid, TD_GarageTitle[playerid]);
    PlayerTextDrawShow(playerid, TD_GarageBadge[playerid]);
    PlayerTextDrawShow(playerid, TD_GarageInfo[playerid]);
    PlayerTextDrawShow(playerid, TD_GaragePrev[playerid]);
    PlayerTextDrawShow(playerid, TD_GarageNext[playerid]);
    PlayerTextDrawShow(playerid, TD_GarageSpawnBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_GarageCancelBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_GarageHint[playerid]);
    return 1;
}

// Forward declarations untuk data garasi di ownership.inc
forward GetGarageInfo(garageId, name[], city[], &Float:camX, &Float:camY, &Float:camZ, &Float:lookX, &Float:lookY, &Float:lookZ, &Float:spX, &Float:spY, &Float:spZ, &Float:spA);
forward GetModelFullName(modelid, name[], maxlen);

stock UpdateGaragePreview(playerid) {
    if (!gPlayerData[playerid][p_InGarageUI]) return;
    if (gPlayerData[playerid][p_GarageVehCount] <= 0) return;

    new idx = gPlayerData[playerid][p_GarageVehIndex];
    if (idx < 0 || idx >= gPlayerData[playerid][p_GarageVehCount]) {
        idx = 0;
        gPlayerData[playerid][p_GarageVehIndex] = 0;
    }

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
    new vStatus = DB_GetFieldIntByName(res, "status");
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

    // Update Badge Indikator Unit
    new badgeStr[48];
    format(badgeStr, sizeof(badgeStr), "Koleksi Kendaraan [ %d / %d ]", idx + 1, gPlayerData[playerid][p_GarageVehCount]);
    PlayerTextDrawSetString(playerid, TD_GarageBadge[playerid], badgeStr);

    // Dapatkan nama kendaraan
    new vehName[32];
    GetModelFullName(modelid, vehName, sizeof(vehName));

    // Status teks
    new statusStr[32];
    if (vStatus == VEH_STATUS_GARAGE) {
        format(statusStr, sizeof(statusStr), "~g~Tersimpan di Garasi");
    } else if (vStatus == VEH_STATUS_OUTSIDE) {
        format(statusStr, sizeof(statusStr), "~y~Terparkir di Luar");
    } else {
        format(statusStr, sizeof(statusStr), "~r~Dalam Asuransi");
    }

    // Hitung persentase darah mesin
    new hpPct = floatround((vhp / 1000.0) * 100.0);
    if (hpPct > 100) hpPct = 100;
    if (hpPct < 0) hpPct = 0;

    // Update Teks Info Kendaraan
    new infoStr[256];
    format(infoStr, sizeof(infoStr),
        "~w~Model:~n~  ~y~%s~n~~n~" \
        "~w~Plat Nomor:~n~  ~c~%s~n~~n~" \
        "~w~Kondisi Mesin:~n~  ~g~%d%% ~w~(%.0f HP)~n~~n~" \
        "~w~Status:~n~  %s",
        vehName, plate, hpPct, vhp, statusStr);
    PlayerTextDrawSetString(playerid, TD_GarageInfo[playerid], infoStr);

    // Refresh TextDraws ke player
    PlayerTextDrawShow(playerid, TD_GarageTitle[playerid]);
    PlayerTextDrawShow(playerid, TD_GarageBadge[playerid]);
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
    SelectTextDraw(playerid, 0x00BCD4FF);
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

    // 1. Tombol << PREVIOUS
    if (playertextid == TD_GaragePrev[playerid]) {
        gPlayerData[playerid][p_GarageVehIndex]--;
        if (gPlayerData[playerid][p_GarageVehIndex] < 0) {
            gPlayerData[playerid][p_GarageVehIndex] = gPlayerData[playerid][p_GarageVehCount] - 1;
        }
        UpdateGaragePreview(playerid);
        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
        return 1;
    }

    // 2. Tombol NEXT >>
    if (playertextid == TD_GarageNext[playerid]) {
        gPlayerData[playerid][p_GarageVehIndex]++;
        if (gPlayerData[playerid][p_GarageVehIndex] >= gPlayerData[playerid][p_GarageVehCount]) {
            gPlayerData[playerid][p_GarageVehIndex] = 0;
        }
        UpdateGaragePreview(playerid);
        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
        return 1;
    }

    // 3. Tombol [  KELUARKAN KENDARAAN ]
    if (playertextid == TD_GarageSpawnBtn[playerid]) {
        new idx = gPlayerData[playerid][p_GarageVehIndex];
        new dbId = gPlayerData[playerid][p_GarageVehDBIDs][idx];
        new gid = gPlayerData[playerid][p_GarageCurrentID];

        CloseGarageUI(playerid);
        SpawnPlayerVehicleFromGarage(playerid, dbId, gid);
        PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
        return 1;
    }

    // 4. Tombol [ X BATAL / KELUAR ]
    if (playertextid == TD_GarageCancelBtn[playerid]) {
        CloseGarageUI(playerid);
        PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
        SendClientMessage(playerid, COL_GREY, "  * Pengambilan kendaraan di garasi dibatalkan.");
        return 1;
    }

    return 0;
}
