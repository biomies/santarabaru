#if defined _MODULE_SPEEDOMETER_INC
    #endinput
#endif
#define _MODULE_SPEEDOMETER_INC

// ============================================================
//  SantaraBaru Roleplay - Compact Center-Bottom Purple HUD
// ============================================================

#define COLOR_HUD_PURPLE_ON   0x5814EEFF
#define COLOR_HUD_BTN_OFF     0x262626EE
#define COLOR_HUD_MAIN_BG     0x181818EE
#define COLOR_HUD_FUEL_BAR_BG 0x2E2E2EFF

new PlayerText:TD_SpeedMainBG[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpeedFuelTitle[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_FuelBarBG[MAX_PLAYERS]       = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_FuelBar[MAX_PLAYERS]         = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpeedBtnEngine[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpeedBtnLight[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpeedBtnLock[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpeedBtnSeatbelt[MAX_PLAYERS]= {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpeedBoxBG[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpeedNumber[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpeedUnit[MAX_PLAYERS]       = {PlayerText:INVALID_TEXT_DRAW, ...};

new gPlayerSpeedoTimer[MAX_PLAYERS] = {-1, ...};
new bool:gPlayerInVehicleHUD[MAX_PLAYERS] = {false, ...};

forward Timer_UpdateSpeedometer(playerid);

stock DestroySpeedometerTextDraws(playerid) {
    if (TD_SpeedMainBG[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_SpeedMainBG[playerid]); TD_SpeedMainBG[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_SpeedFuelTitle[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_SpeedFuelTitle[playerid]); TD_SpeedFuelTitle[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_FuelBarBG[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_FuelBarBG[playerid]); TD_FuelBarBG[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_FuelBar[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_FuelBar[playerid]); TD_FuelBar[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_SpeedBtnEngine[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_SpeedBtnEngine[playerid]); TD_SpeedBtnEngine[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_SpeedBtnLight[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_SpeedBtnLight[playerid]); TD_SpeedBtnLight[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_SpeedBtnLock[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_SpeedBtnLock[playerid]); TD_SpeedBtnLock[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_SpeedBtnSeatbelt[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_SpeedBtnSeatbelt[playerid]); TD_SpeedBtnSeatbelt[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_SpeedBoxBG[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_SpeedBoxBG[playerid]); TD_SpeedBoxBG[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_SpeedNumber[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_SpeedNumber[playerid]); TD_SpeedNumber[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_SpeedUnit[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_SpeedUnit[playerid]); TD_SpeedUnit[playerid] = PlayerText:INVALID_TEXT_DRAW; }
}

stock CreateSpeedometerTextDraws(playerid) {
    DestroySpeedometerTextDraws(playerid);

    // 1. Container Card Background (Compact Center X: 220.0 .. 420.0, Y: 366.0 .. 428.0)
    TD_SpeedMainBG[playerid] = CreatePlayerTextDraw(playerid, 220.0, 366.0, "_");
    PlayerTextDrawUseBox(playerid, TD_SpeedMainBG[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_SpeedMainBG[playerid], COLOR_HUD_MAIN_BG);
    PlayerTextDrawTextSize(playerid, TD_SpeedMainBG[playerid], 420.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_SpeedMainBG[playerid], 0.0, 6.8);
    PlayerTextDrawSetSelectable(playerid, TD_SpeedMainBG[playerid], false);

    // 2. "Fuel" Title Text
    TD_SpeedFuelTitle[playerid] = CreatePlayerTextDraw(playerid, 228.0, 372.0, "Fuel");
    PlayerTextDrawFont(playerid, TD_SpeedFuelTitle[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SpeedFuelTitle[playerid], 0.18, 0.95);
    PlayerTextDrawColor(playerid, TD_SpeedFuelTitle[playerid], 0xFFFFFFFF);
    PlayerTextDrawSetOutline(playerid, TD_SpeedFuelTitle[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SpeedFuelTitle[playerid], false);

    // 3. Fuel Bar BG (Grey Bar, Width = 138.0)
    TD_FuelBarBG[playerid] = CreatePlayerTextDraw(playerid, 228.0, 386.0, "_");
    PlayerTextDrawUseBox(playerid, TD_FuelBarBG[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_FuelBarBG[playerid], COLOR_HUD_FUEL_BAR_BG);
    PlayerTextDrawTextSize(playerid, TD_FuelBarBG[playerid], 366.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_FuelBarBG[playerid], 0.0, 0.6);
    PlayerTextDrawSetSelectable(playerid, TD_FuelBarBG[playerid], false);

    // 4. Fuel Bar Fill (Purple Bar)
    TD_FuelBar[playerid] = CreatePlayerTextDraw(playerid, 228.0, 386.0, "_");
    PlayerTextDrawUseBox(playerid, TD_FuelBar[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_FuelBar[playerid], COLOR_HUD_PURPLE_ON);
    PlayerTextDrawTextSize(playerid, TD_FuelBar[playerid], 366.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_FuelBar[playerid], 0.0, 0.6);
    PlayerTextDrawSetSelectable(playerid, TD_FuelBar[playerid], false);

    // 5. Buttons (Engine, Light, Lock, Seatbelt)
    // ENGINE (Center X: 244.0)
    TD_SpeedBtnEngine[playerid] = CreatePlayerTextDraw(playerid, 244.0, 401.0, "Engine");
    PlayerTextDrawFont(playerid, TD_SpeedBtnEngine[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SpeedBtnEngine[playerid], 0.13, 0.95);
    PlayerTextDrawColor(playerid, TD_SpeedBtnEngine[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SpeedBtnEngine[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_SpeedBtnEngine[playerid], COLOR_HUD_BTN_OFF);
    PlayerTextDrawTextSize(playerid, TD_SpeedBtnEngine[playerid], 14.0, 32.5);
    PlayerTextDrawAlignment(playerid, TD_SpeedBtnEngine[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SpeedBtnEngine[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SpeedBtnEngine[playerid], true);

    // LIGHT (Center X: 279.0)
    TD_SpeedBtnLight[playerid] = CreatePlayerTextDraw(playerid, 279.0, 401.0, "Light");
    PlayerTextDrawFont(playerid, TD_SpeedBtnLight[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SpeedBtnLight[playerid], 0.13, 0.95);
    PlayerTextDrawColor(playerid, TD_SpeedBtnLight[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SpeedBtnLight[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_SpeedBtnLight[playerid], COLOR_HUD_BTN_OFF);
    PlayerTextDrawTextSize(playerid, TD_SpeedBtnLight[playerid], 14.0, 32.5);
    PlayerTextDrawAlignment(playerid, TD_SpeedBtnLight[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SpeedBtnLight[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SpeedBtnLight[playerid], true);

    // LOCK (Center X: 314.0)
    TD_SpeedBtnLock[playerid] = CreatePlayerTextDraw(playerid, 314.0, 401.0, "Lock");
    PlayerTextDrawFont(playerid, TD_SpeedBtnLock[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SpeedBtnLock[playerid], 0.13, 0.95);
    PlayerTextDrawColor(playerid, TD_SpeedBtnLock[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SpeedBtnLock[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_SpeedBtnLock[playerid], COLOR_HUD_BTN_OFF);
    PlayerTextDrawTextSize(playerid, TD_SpeedBtnLock[playerid], 14.0, 32.5);
    PlayerTextDrawAlignment(playerid, TD_SpeedBtnLock[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SpeedBtnLock[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SpeedBtnLock[playerid], true);

    // SEATBELT (Center X: 349.0)
    TD_SpeedBtnSeatbelt[playerid] = CreatePlayerTextDraw(playerid, 349.0, 401.0, "Seatbelt");
    PlayerTextDrawFont(playerid, TD_SpeedBtnSeatbelt[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SpeedBtnSeatbelt[playerid], 0.11, 0.95);
    PlayerTextDrawColor(playerid, TD_SpeedBtnSeatbelt[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SpeedBtnSeatbelt[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_SpeedBtnSeatbelt[playerid], COLOR_HUD_BTN_OFF);
    PlayerTextDrawTextSize(playerid, TD_SpeedBtnSeatbelt[playerid], 14.0, 33.0);
    PlayerTextDrawAlignment(playerid, TD_SpeedBtnSeatbelt[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SpeedBtnSeatbelt[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SpeedBtnSeatbelt[playerid], true);

    // 6. Right Speed Purple Box (Compact X: 372.0 .. 412.0, Y: 372.0 .. 422.0)
    TD_SpeedBoxBG[playerid] = CreatePlayerTextDraw(playerid, 372.0, 372.0, "_");
    PlayerTextDrawUseBox(playerid, TD_SpeedBoxBG[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_SpeedBoxBG[playerid], COLOR_HUD_PURPLE_ON);
    PlayerTextDrawTextSize(playerid, TD_SpeedBoxBG[playerid], 412.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_SpeedBoxBG[playerid], 0.0, 5.3);
    PlayerTextDrawSetSelectable(playerid, TD_SpeedBoxBG[playerid], false);

    // 7. Speed Value Number (Bold White)
    TD_SpeedNumber[playerid] = CreatePlayerTextDraw(playerid, 392.0, 375.0, "000");
    PlayerTextDrawFont(playerid, TD_SpeedNumber[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SpeedNumber[playerid], 0.36, 1.7);
    PlayerTextDrawColor(playerid, TD_SpeedNumber[playerid], 0xFFFFFFFF);
    PlayerTextDrawAlignment(playerid, TD_SpeedNumber[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SpeedNumber[playerid], 0);
    PlayerTextDrawSetSelectable(playerid, TD_SpeedNumber[playerid], false);

    // 8. Speed Unit "Km/h"
    TD_SpeedUnit[playerid] = CreatePlayerTextDraw(playerid, 392.0, 400.0, "Km/h");
    PlayerTextDrawFont(playerid, TD_SpeedUnit[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SpeedUnit[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_SpeedUnit[playerid], 0xFFFFFFFF);
    PlayerTextDrawAlignment(playerid, TD_SpeedUnit[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SpeedUnit[playerid], 0);
    PlayerTextDrawSetSelectable(playerid, TD_SpeedUnit[playerid], false);
}

stock ShowSpeedometer(playerid) {
    if (!IsPlayerConnected(playerid)) return 0;
    if (!CheckSpawned(playerid)) return 0;

    new vehId = GetPlayerVehicleID(playerid);
    if (vehId <= 0 || vehId >= MAX_VEHICLES || vehId == INVALID_VEHICLE_ID) return 0;

    CreateSpeedometerTextDraws(playerid);

    PlayerTextDrawShow(playerid, TD_SpeedMainBG[playerid]);
    PlayerTextDrawShow(playerid, TD_SpeedFuelTitle[playerid]);
    PlayerTextDrawShow(playerid, TD_FuelBarBG[playerid]);
    PlayerTextDrawShow(playerid, TD_FuelBar[playerid]);
    PlayerTextDrawShow(playerid, TD_SpeedBtnEngine[playerid]);
    PlayerTextDrawShow(playerid, TD_SpeedBtnLight[playerid]);
    PlayerTextDrawShow(playerid, TD_SpeedBtnLock[playerid]);
    PlayerTextDrawShow(playerid, TD_SpeedBtnSeatbelt[playerid]);
    PlayerTextDrawShow(playerid, TD_SpeedBoxBG[playerid]);
    PlayerTextDrawShow(playerid, TD_SpeedNumber[playerid]);
    PlayerTextDrawShow(playerid, TD_SpeedUnit[playerid]);

    gPlayerInVehicleHUD[playerid] = true;

    if (gPlayerSpeedoTimer[playerid] != -1) {
        KillTimer(gPlayerSpeedoTimer[playerid]);
    }
    gPlayerSpeedoTimer[playerid] = SetTimerEx("Timer_UpdateSpeedometer", 150, true, "i", playerid);

    UpdateSpeedometer(playerid);
    return 1;
}

stock HideSpeedometer(playerid) {
    if (gPlayerSpeedoTimer[playerid] != -1) {
        KillTimer(gPlayerSpeedoTimer[playerid]);
        gPlayerSpeedoTimer[playerid] = -1;
    }
    gPlayerInVehicleHUD[playerid] = false;
    CancelSelectTextDraw(playerid);
    DestroySpeedometerTextDraws(playerid);
    return 1;
}

stock UpdateSpeedometer(playerid) {
    if (!IsPlayerConnected(playerid) || !gPlayerInVehicleHUD[playerid]) {
        HideSpeedometer(playerid);
        return 0;
    }

    new pState = GetPlayerState(playerid);
    if (pState != PLAYER_STATE_DRIVER && pState != PLAYER_STATE_PASSENGER) {
        HideSpeedometer(playerid);
        return 0;
    }

    new vehId = GetPlayerVehicleID(playerid);
    if (vehId <= 0 || vehId >= MAX_VEHICLES || vehId == INVALID_VEHICLE_ID) {
        HideSpeedometer(playerid);
        return 0;
    }

    // 1. Hitung Kecepatan Real-time
    new Float:vx, Float:vy, Float:vz;
    GetVehicleVelocity(vehId, vx, vy, vz);
    new Float:speedVal = floatsqroot(vx * vx + vy * vy + vz * vz) * 180.0;
    new speedInt = floatround(speedVal);

    new speedStr[16];
    format(speedStr, sizeof(speedStr), "%03d", speedInt);
    PlayerTextDrawSetString(playerid, TD_SpeedNumber[playerid], speedStr);

    // Deteksi Tabrakan
    new Float:lastSpeed = gPlayerData[playerid][p_LastSpeed];
    if (lastSpeed > 80.0 && lastSpeed - speedVal > 80.0) { // Turun tajam 80km/h dalam 150ms (tabrakan ekstrem)
        new Float:hp;
        GetPlayerHealth(playerid, hp);
        if (gPlayerData[playerid][p_Seatbelt]) {
            // Sabuk pengaman terpasang, kurang damage sedikit
            SetPlayerHealth(playerid, hp - 10.0);
            SendClientMessage(playerid, COL_YELLOW, "  [Tabrakan] Sabuk pengaman menahan benturan. Anda terluka ringan!");
            PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
        } else {
            // Tanpa sabuk pengaman, damage besar
            SetPlayerHealth(playerid, hp - 50.0);
            SendClientMessage(playerid, 0xFF4040FF, "  [Tabrakan] Anda menabrak keras tanpa sabuk pengaman!");
            PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
        }
    }
    gPlayerData[playerid][p_LastSpeed] = speedVal;

    // 2. Status Warna Box Tombol Mesin, Lampu, Kunci, Seatbelt
    new engine, lights, alarm, doors, bonnet, boot, objective;
    GetVehicleParamsEx(vehId, engine, lights, alarm, doors, bonnet, boot, objective);

    if (engine == 1) {
        PlayerTextDrawBoxColor(playerid, TD_SpeedBtnEngine[playerid], COLOR_HUD_PURPLE_ON);
    } else {
        PlayerTextDrawBoxColor(playerid, TD_SpeedBtnEngine[playerid], COLOR_HUD_BTN_OFF);
    }
    PlayerTextDrawShow(playerid, TD_SpeedBtnEngine[playerid]);

    if (lights == 1) {
        PlayerTextDrawBoxColor(playerid, TD_SpeedBtnLight[playerid], COLOR_HUD_PURPLE_ON);
    } else {
        PlayerTextDrawBoxColor(playerid, TD_SpeedBtnLight[playerid], COLOR_HUD_BTN_OFF);
    }
    PlayerTextDrawShow(playerid, TD_SpeedBtnLight[playerid]);

    if (doors == 1) {
        PlayerTextDrawBoxColor(playerid, TD_SpeedBtnLock[playerid], COLOR_HUD_PURPLE_ON);
    } else {
        PlayerTextDrawBoxColor(playerid, TD_SpeedBtnLock[playerid], COLOR_HUD_BTN_OFF);
    }
    PlayerTextDrawShow(playerid, TD_SpeedBtnLock[playerid]);

    if (gPlayerData[playerid][p_Seatbelt]) {
        PlayerTextDrawBoxColor(playerid, TD_SpeedBtnSeatbelt[playerid], COLOR_HUD_PURPLE_ON);
    } else {
        PlayerTextDrawBoxColor(playerid, TD_SpeedBtnSeatbelt[playerid], COLOR_HUD_BTN_OFF);
    }
    PlayerTextDrawShow(playerid, TD_SpeedBtnSeatbelt[playerid]);

    // 3. Fuel Bar Update (Lebar bar 138.0)
    new Float:fuel = gVehicleFuel[vehId];
    if (fuel < 0.0) fuel = 0.0;
    if (fuel > 50.0) fuel = 50.0;
    new Float:fuelPercent = fuel / 50.0;
    new Float:barWidth = 138.0 * fuelPercent;
    PlayerTextDrawTextSize(playerid, TD_FuelBar[playerid], 228.0 + barWidth, 0.0);
    PlayerTextDrawShow(playerid, TD_FuelBar[playerid]);

    return 1;
}

public Timer_UpdateSpeedometer(playerid) {
    UpdateSpeedometer(playerid);
    return 1;
}

// ------------------------------------------------------------
//  Fungsi Toggle Cepat (Tombol Layar / Keypress Y & N / Command)
// ------------------------------------------------------------

stock TogglePlayerVehicleEngine(playerid) {
    if (!CheckSpawned(playerid)) return 0;
    if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
        SendClientMessage(playerid, COL_RED, "  [Kendaraan] Anda harus berada di kursi pengemudi untuk menyalakan mesin!");
        return 0;
    }

    new vehId = GetPlayerVehicleID(playerid);
    if (vehId <= 0 || vehId >= MAX_VEHICLES || vehId == INVALID_VEHICLE_ID) return 0;

    new engine, lights, alarm, doors, bonnet, boot, objective;
    GetVehicleParamsEx(vehId, engine, lights, alarm, doors, bonnet, boot, objective);

    if (engine == 1) {
        SetVehicleParamsEx(vehId, 0, lights, alarm, doors, bonnet, boot, objective);
        PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
        SendClientMessage(playerid, COL_YELLOW, "  [Kendaraan] Mesin dimatikan.");
        GameTextForPlayer(playerid, "~r~MESIN DIMATIKAN", 1500, 4);
    } else {
        SetVehicleParamsEx(vehId, 1, lights, alarm, doors, bonnet, boot, objective);
        PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
        SendClientMessage(playerid, COL_GREEN, "  [Kendaraan] Mesin dinyalakan. Silakan berkendara dengan aman!");
        GameTextForPlayer(playerid, "~g~MESIN MENYALA", 1500, 4);
    }
    UpdateSpeedometer(playerid);
    return 1;
}

stock TogglePlayerVehicleLight(playerid) {
    if (!CheckSpawned(playerid)) return 0;
    if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) {
        SendClientMessage(playerid, COL_RED, "  [Kendaraan] Anda harus berada di kursi pengemudi untuk menyalakan lampu!");
        return 0;
    }

    new vehId = GetPlayerVehicleID(playerid);
    if (vehId <= 0 || vehId >= MAX_VEHICLES || vehId == INVALID_VEHICLE_ID) return 0;

    new engine, lights, alarm, doors, bonnet, boot, objective;
    GetVehicleParamsEx(vehId, engine, lights, alarm, doors, bonnet, boot, objective);

    if (lights == 1) {
        SetVehicleParamsEx(vehId, engine, 0, alarm, doors, bonnet, boot, objective);
        PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
        GameTextForPlayer(playerid, "~r~LAMPU MATI", 1500, 4);
    } else {
        SetVehicleParamsEx(vehId, engine, 1, alarm, doors, bonnet, boot, objective);
        PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
        GameTextForPlayer(playerid, "~g~LAMPU NYALA", 1500, 4);
    }
    UpdateSpeedometer(playerid);
    return 1;
}

stock TogglePlayerVehicleSeatbelt(playerid) {
    if (!CheckSpawned(playerid)) return 0;
    new pState = GetPlayerState(playerid);
    if (pState != PLAYER_STATE_DRIVER && pState != PLAYER_STATE_PASSENGER) {
        SendClientMessage(playerid, COL_RED, "  [Kendaraan] Anda harus berada di dalam kendaraan!");
        return 0;
    }

    gPlayerData[playerid][p_Seatbelt] = !gPlayerData[playerid][p_Seatbelt];

    if (gPlayerData[playerid][p_Seatbelt]) {
        SendClientMessage(playerid, COL_GREEN, "  [Kendaraan] Sabuk pengaman {00FF00}terpasang{FFFFFF}.");
        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
    } else {
        SendClientMessage(playerid, COL_YELLOW, "  [Kendaraan] Sabuk pengaman {FF4040}dilepas{FFFFFF}.");
        PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
    }
    UpdateSpeedometer(playerid);
    return 1;
}

stock TogglePlayerVehicleLock(playerid) {
    if (!CheckSpawned(playerid)) return 0;

    // Cek jika pemain di dalam kendaraan
    if (IsPlayerInAnyVehicle(playerid)) {
        new vehId = GetPlayerVehicleID(playerid);
        if (vehId > 0 && vehId < MAX_VEHICLES && vehId != INVALID_VEHICLE_ID) {
            new engine, lights, alarm, doors, bonnet, boot, objective;
            GetVehicleParamsEx(vehId, engine, lights, alarm, doors, bonnet, boot, objective);

            if (doors == 1) {
                SetVehicleParamsEx(vehId, engine, lights, alarm, 0, bonnet, boot, objective);
                PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
                SendClientMessage(playerid, COL_GREEN, "  [Kendaraan] Kunci pintu: {FFFFFF}TERBUKA (Unlocked).");
                GameTextForPlayer(playerid, "~g~PINTU TERBUKA", 1500, 4);
            } else {
                SetVehicleParamsEx(vehId, engine, lights, alarm, 1, bonnet, boot, objective);
                PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
                SendClientMessage(playerid, COL_YELLOW, "  [Kendaraan] Kunci pintu: {E74C3C}TERKUNCI (Locked).");
                GameTextForPlayer(playerid, "~r~PINTU TERKUNCI", 1500, 4);
            }
            UpdateSpeedometer(playerid);
            return 1;
        }
    }

    // Jika pemain di luar mobil -> Cari mobil aktif terdekat milik pemain (dalam radius 8.0 meter)
    new nearestVeh = INVALID_VEHICLE_ID;
    new Float:minDist = 999.0;
    new Float:px, Float:py, Float:pz;
    GetPlayerPos(playerid, px, py, pz);

    for (new v = 0; v < MAX_PLAYER_SPAWNED_VEHICLES; v++) {
        new veh = gPlayerData[playerid][p_ActiveVehID][v];
        if (veh != INVALID_VEHICLE_ID && gPlayerData[playerid][p_ActiveVehDBID][v] > 0) {
            new Float:vx, Float:vy, Float:vz;
            GetVehiclePos(veh, vx, vy, vz);
            new Float:dx = px - vx; new Float:dy = py - vy; new Float:dz = pz - vz;
            new Float:dist = floatsqroot((dx * dx) + (dy * dy) + (dz * dz));
            if (dist <= 8.0 && dist < minDist) {
                minDist = dist;
                nearestVeh = veh;
            }
        }
    }

    if (nearestVeh != INVALID_VEHICLE_ID) {
        new engine, lights, alarm, doors, bonnet, boot, objective;
        GetVehicleParamsEx(nearestVeh, engine, lights, alarm, doors, bonnet, boot, objective);

        if (doors == 1) {
            SetVehicleParamsEx(nearestVeh, engine, lights, alarm, 0, bonnet, boot, objective);
            PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
            SendClientMessage(playerid, COL_GREEN, "  [Kendaraan] Kunci pintu mobil pribadi Anda: {FFFFFF}TERBUKA (Unlocked).");
            GameTextForPlayer(playerid, "~g~PINTU MOBIL TERBUKA", 1500, 4);
        } else {
            SetVehicleParamsEx(nearestVeh, engine, lights, alarm, 1, bonnet, boot, objective);
            PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
            SendClientMessage(playerid, COL_YELLOW, "  [Kendaraan] Kunci pintu mobil pribadi Anda: {E74C3C}TERKUNCI (Locked).");
            GameTextForPlayer(playerid, "~r~PINTU MOBIL TERKUNCI", 1500, 4);
        }
        return 1;
    }

    SendClientMessage(playerid, COL_RED, "  [Kendaraan] Anda harus berada di dalam kendaraan atau dekat (maks 8m) mobil pribadi Anda!");
    return 0;
}
