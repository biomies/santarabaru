#if defined _MODULE_SPEEDOMETER_INC
    #endinput
#endif
#define _MODULE_SPEEDOMETER_INC

// ============================================================
//  SantaraBaru Roleplay - Minimalist Center-Bottom Speedometer
//  Pure Digital Speed + Clickable [ENGINE] and [LOCK] Button Tiles
// ============================================================

new PlayerText:TD_SpeedNumber[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpeedBtnEngine[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpeedBtnLock[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};

new gPlayerSpeedoTimer[MAX_PLAYERS] = {-1, ...};
new bool:gPlayerInVehicleHUD[MAX_PLAYERS] = {false, ...};

forward Timer_UpdateSpeedometer(playerid);

stock DestroySpeedometerTextDraws(playerid) {
    if (TD_SpeedNumber[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SpeedNumber[playerid]);
        TD_SpeedNumber[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SpeedBtnEngine[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SpeedBtnEngine[playerid]);
        TD_SpeedBtnEngine[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SpeedBtnLock[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SpeedBtnLock[playerid]);
        TD_SpeedBtnLock[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
}

stock CreateSpeedometerTextDraws(playerid) {
    DestroySpeedometerTextDraws(playerid);

    // 1. Angka Kecepatan Digital di Tengah Bawah (Center: X: 320.0, Y: 388.0)
    TD_SpeedNumber[playerid] = CreatePlayerTextDraw(playerid, 320.0, 388.0, "000 ~w~~h~KM/H");
    PlayerTextDrawAlignment(playerid, TD_SpeedNumber[playerid], 2); // Center Aligned
    PlayerTextDrawFont(playerid, TD_SpeedNumber[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SpeedNumber[playerid], 0.35, 1.4);
    PlayerTextDrawColor(playerid, TD_SpeedNumber[playerid], 0x00EEFFFF);
    PlayerTextDrawSetOutline(playerid, TD_SpeedNumber[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SpeedNumber[playerid], 0);

    // 2. Tombol Button Tile ENGINE (Kiri dari Center: X: 246.0 s/d 314.0, Y: 412.0)
    TD_SpeedBtnEngine[playerid] = CreatePlayerTextDraw(playerid, 246.0, 412.0, "  ENGINE");
    PlayerTextDrawFont(playerid, TD_SpeedBtnEngine[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SpeedBtnEngine[playerid], 0.22, 1.15);
    PlayerTextDrawColor(playerid, TD_SpeedBtnEngine[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SpeedBtnEngine[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_SpeedBtnEngine[playerid], 0x2ECC71D0); // Hijau saat ON
    PlayerTextDrawTextSize(playerid, TD_SpeedBtnEngine[playerid], 314.0, 14.0);
    PlayerTextDrawSetOutline(playerid, TD_SpeedBtnEngine[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SpeedBtnEngine[playerid], 1);

    // 3. Tombol Button Tile LOCK (Kanan dari Center: X: 326.0 s/d 394.0, Y: 412.0)
    TD_SpeedBtnLock[playerid] = CreatePlayerTextDraw(playerid, 326.0, 412.0, "   LOCK");
    PlayerTextDrawFont(playerid, TD_SpeedBtnLock[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SpeedBtnLock[playerid], 0.22, 1.15);
    PlayerTextDrawColor(playerid, TD_SpeedBtnLock[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SpeedBtnLock[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_SpeedBtnLock[playerid], 0x2C3E50D0); // Gelap saat OFF
    PlayerTextDrawTextSize(playerid, TD_SpeedBtnLock[playerid], 394.0, 14.0);
    PlayerTextDrawSetOutline(playerid, TD_SpeedBtnLock[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SpeedBtnLock[playerid], 1);
}

stock ShowSpeedometer(playerid) {
    if (!IsPlayerConnected(playerid)) return 0;
    if (!CheckSpawned(playerid)) return 0;

    new vehId = GetPlayerVehicleID(playerid);
    if (vehId == 0) return 0;

    CreateSpeedometerTextDraws(playerid);

    PlayerTextDrawShow(playerid, TD_SpeedNumber[playerid]);
    PlayerTextDrawShow(playerid, TD_SpeedBtnEngine[playerid]);
    PlayerTextDrawShow(playerid, TD_SpeedBtnLock[playerid]);

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
    if (vehId == 0) {
        HideSpeedometer(playerid);
        return 0;
    }

    // 1. Hitung Kecepatan Real-time
    new Float:vx, Float:vy, Float:vz;
    GetVehicleVelocity(vehId, vx, vy, vz);
    new Float:speedVal = floatsqroot(vx * vx + vy * vy + vz * vz) * 180.0;
    new speedInt = floatround(speedVal);

    new speedStr[32];
    format(speedStr, sizeof(speedStr), "%03d ~w~~h~KM/H", speedInt);
    PlayerTextDrawSetString(playerid, TD_SpeedNumber[playerid], speedStr);

    // 2. Status Warna Box Tombol Mesin & Kunci
    new engine, lights, alarm, doors, bonnet, boot, objective;
    GetVehicleParamsEx(vehId, engine, lights, alarm, doors, bonnet, boot, objective);

    if (engine == 1) {
        PlayerTextDrawBoxColor(playerid, TD_SpeedBtnEngine[playerid], 0x2ECC71E0); // Hijau
    } else {
        PlayerTextDrawBoxColor(playerid, TD_SpeedBtnEngine[playerid], 0xE74C3CE0); // Merah
    }
    PlayerTextDrawShow(playerid, TD_SpeedBtnEngine[playerid]);

    if (doors == 1) {
        PlayerTextDrawBoxColor(playerid, TD_SpeedBtnLock[playerid], 0xF1C40FE0); // Kuning/Amber
    } else {
        PlayerTextDrawBoxColor(playerid, TD_SpeedBtnLock[playerid], 0x2C3E50D0); // Abu-abu gelap
    }
    PlayerTextDrawShow(playerid, TD_SpeedBtnLock[playerid]);

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
    if (vehId == 0) return 0;

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

stock TogglePlayerVehicleLock(playerid) {
    if (!CheckSpawned(playerid)) return 0;

    // Cek jika pemain di dalam kendaraan
    if (IsPlayerInAnyVehicle(playerid)) {
        new vehId = GetPlayerVehicleID(playerid);
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
