#if defined _MODULE_SPAWN_SELECTOR_INC
    #endinput
#endif
#define _MODULE_SPAWN_SELECTOR_INC

// ============================================================
//  SantaraBaru Roleplay - Eagle-Eye Spawn Selector UI (Right Card)
// ============================================================

enum E_SPAWN_PRESET {
    s_City[32],
    s_Name[32],
    s_Region[32],
    s_Facilities[64],
    Float:s_SpawnX,
    Float:s_SpawnY,
    Float:s_SpawnZ,
    Float:s_SpawnA,
    Float:s_CamX,
    Float:s_CamY,
    Float:s_CamZ,
    Float:s_LookX,
    Float:s_LookY,
    Float:s_LookZ
};

new const gPublicSpawns[][E_SPAWN_PRESET] = {
    //                                                           
    //  KOTA 1: LOS SANTOS (LS)
    //                                                           
    // 0: Stasiun Unity (Los Santos)
    {
        "Kota 1: Los Santos", "Stasiun Unity", "Unity Station, Los Santos", "Taksi ~w~| ~g~ATM ~w~| ~g~Kereta Api",
        1757.5, -1894.0, 13.56, 270.0,
        1815.0, -1945.0, 48.0,
        1757.5, -1894.0, 13.56
    },
    // 1: Bandara Internasional Los Santos (LSX)
    {
        "Kota 1: Los Santos", "Bandara Los Santos", "LS International Airport", "Penerbangan ~w~| ~g~Taksi ~w~| ~g~ATM",
        1685.5, -2238.5, 13.55, 180.0,
        1750.0, -2180.0, 55.0,
        1685.5, -2238.5, 13.55
    },
    // 2: Balai Kota / Pershing Square (Los Santos)
    {
        "Kota 1: Los Santos", "Balai Kota LS", "Pershing Square, LS", "Pemerintahan ~w~| ~g~Polisi ~w~| ~g~ATM",
        1481.0, -1742.0, 13.55, 0.0,
        1530.0, -1800.0, 52.0,
        1481.0, -1742.0, 13.55
    },
    // 3: Pantai Santa Maria (Los Santos)
    {
        "Kota 1: Los Santos", "Pantai Santa Maria", "Santa Maria Promenade, LS", "Dermaga ~w~| ~g~Resto ~w~| ~g~Wisata",
        362.5, -2032.0, 7.84, 180.0,
        420.0, -1975.0, 45.0,
        362.5, -2032.0, 7.84
    },
    // 4: Stasiun Market (Los Santos)
    {
        "Kota 1: Los Santos", "Stasiun Market", "Market District, LS", "Pusat Bisnis ~w~| ~g~ATM ~w~| ~g~Resto",
        825.5, -1346.0, 13.53, 90.0,
        890.0, -1400.0, 50.0,
        825.5, -1346.0, 13.53
    },

    //                                                           
    //  KOTA 2: SAN FIERRO (SF)
    //                                                           
    // 5: Stasiun Cranberry (San Fierro)
    {
        "Kota 2: San Fierro", "Stasiun Cranberry", "Cranberry Station, SF", "Taksi ~w~| ~g~ATM ~w~| ~g~Kereta Api",
        -1982.0, 137.0, 27.68, 89.0,
        -1915.0, 80.0, 65.0,
        -1982.0, 137.0, 27.68
    },
    // 6: Bandara Easter Bay (San Fierro)
    {
        "Kota 2: San Fierro", "Bandara Easter Bay", "Easter Bay Airport, SF", "Penerbangan ~w~| ~g~Taksi ~w~| ~g~ATM",
        -1423.5, -287.2, 14.14, 135.0,
        -1340.0, -215.0, 58.0,
        -1423.5, -287.2, 14.14
    },
    // 7: Balai Kota / Civic Center (San Fierro)
    {
        "Kota 2: San Fierro", "Balai Kota SF", "Civic Center Plaza, SF", "Pusat Kota ~w~| ~g~ATM ~w~| ~g~Plaza",
        -2763.5, 375.5, 6.33, 90.0,
        -2695.0, 310.0, 48.0,
        -2763.5, 375.5, 6.33
    },
    // 8: Dermaga Wisata Pier 69 (San Fierro)
    {
        "Kota 2: San Fierro", "Dermaga Pier 69", "Esplanade North, SF", "Dermaga Kapal ~w~| ~g~Resto ~w~| ~g~Wisata",
        -2270.0, 1040.0, 50.40, 270.0,
        -2210.0, 980.0, 88.0,
        -2270.0, 1040.0, 50.40
    },
    // 9: Terminal Bus SF (San Fierro)
    {
        "Kota 2: San Fierro", "Terminal Bus SF", "Central Bus Terminal, SF", "Bus Kota ~w~| ~g~Taksi ~w~| ~g~Rest Area",
        -1988.5, -215.0, 15.36, 180.0,
        -1930.0, -270.0, 52.0,
        -1988.5, -215.0, 15.36
    },

    //                                                           
    //  KOTA 3: LAS VENTURAS (LV)
    //                                                           
    // 10: The Strip / Casino District (Las Venturas)
    {
        "Kota 3: Las Venturas", "The Strip Kasino", "The Strip District, LV", "Kasino ~w~| ~g~Hotel ~w~| ~g~ATM ~w~| ~g~Taksi",
        2028.5, 1007.5, 10.82, 270.0,
        2090.0, 940.0, 56.0,
        2028.5, 1007.5, 10.82
    },
    // 11: Bandara Las Venturas (LVA)
    {
        "Kota 3: Las Venturas", "Bandara Las Venturas", "Las Venturas Airport", "Penerbangan ~w~| ~g~Taksi ~w~| ~g~ATM",
        1682.0, 1450.0, 10.76, 270.0,
        1750.0, 1390.0, 55.0,
        1682.0, 1450.0, 10.76
    },
    // 12: Stasiun Kereta Sobell (Las Venturas)
    {
        "Kota 3: Las Venturas", "Stasiun Sobell", "Sobell Rail Station, LV", "Kereta Api ~w~| ~g~ATM ~w~| ~g~Taksi",
        2862.0, 1250.0, 10.82, 90.0,
        2800.0, 1190.0, 52.0,
        2862.0, 1250.0, 10.82
    },
    // 13: Old Venturas Strip / The Visage (Las Venturas)
    {
        "Kota 3: Las Venturas", "Old Venturas Strip", "The Visage & Pirates, LV", "Kasino Klasik ~w~| ~g~ATM ~w~| ~g~Resto",
        2420.0, 1125.0, 10.82, 0.0,
        2480.0, 1060.0, 55.0,
        2420.0, 1125.0, 10.82
    },
    // 14: Redsands Plaza (Las Venturas)
    {
        "Kota 3: Las Venturas", "Redsands Plaza", "Redsands East, LV", "Mall ~w~| ~g~Resto ~w~| ~g~ATM ~w~| ~g~Taksi",
        2000.0, 2300.0, 10.82, 90.0,
        1940.0, 2240.0, 54.0,
        2000.0, 2300.0, 10.82
    }
};
#define PUBLIC_SPAWN_COUNT (sizeof(gPublicSpawns))

// TextDraw Handles
new PlayerText:TD_SpawnBox[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpawnHeader[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpawnTitle[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpawnInfo[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpawnPrev[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpawnNext[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpawnCount[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpawnConfirm[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpawnCancel[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpawnHint[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};

stock DestroyPlayerSpawnTextDraws(playerid) {
    if (TD_SpawnBox[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SpawnBox[playerid]);
        TD_SpawnBox[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SpawnHeader[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SpawnHeader[playerid]);
        TD_SpawnHeader[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SpawnTitle[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SpawnTitle[playerid]);
        TD_SpawnTitle[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SpawnInfo[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SpawnInfo[playerid]);
        TD_SpawnInfo[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SpawnPrev[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SpawnPrev[playerid]);
        TD_SpawnPrev[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SpawnNext[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SpawnNext[playerid]);
        TD_SpawnNext[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SpawnCount[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SpawnCount[playerid]);
        TD_SpawnCount[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SpawnConfirm[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SpawnConfirm[playerid]);
        TD_SpawnConfirm[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SpawnCancel[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SpawnCancel[playerid]);
        TD_SpawnCancel[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SpawnHint[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SpawnHint[playerid]);
        TD_SpawnHint[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
}

stock UpdateSpawnSelectorCamera(playerid) {
    if (!gPlayerData[playerid][p_SelectingSpawn]) return;

    new Float:targetCamX, Float:targetCamY, Float:targetCamZ;
    new Float:targetLookX, Float:targetLookY, Float:targetLookZ;

    if (!gPlayerData[playerid][p_IsNewCharacter] && gPlayerData[playerid][p_SpawnIndex] == 0) {
        // Lokasi Terakhir
        targetLookX = gPlayerData[playerid][p_X];
        targetLookY = gPlayerData[playerid][p_Y];
        targetLookZ = gPlayerData[playerid][p_Z];
        targetCamX  = targetLookX + 45.0;
        targetCamY  = targetLookY - 45.0;
        targetCamZ  = targetLookZ + 40.0;
    } else {
        new idx = gPlayerData[playerid][p_SpawnIndex];
        if (!gPlayerData[playerid][p_IsNewCharacter]) idx--; // Offset by 1

        targetCamX  = gPublicSpawns[idx][s_CamX];
        targetCamY  = gPublicSpawns[idx][s_CamY];
        targetCamZ  = gPublicSpawns[idx][s_CamZ];
        targetLookX = gPublicSpawns[idx][s_LookX];
        targetLookY = gPublicSpawns[idx][s_LookY];
        targetLookZ = gPublicSpawns[idx][s_LookZ];
    }

    SetPlayerCameraPos(playerid, targetCamX, targetCamY, targetCamZ);
    SetPlayerCameraLookAt(playerid, targetLookX, targetLookY, targetLookZ, CAMERA_CUT);
}

stock UpdateSpawnSelectorUI(playerid) {
    if (!gPlayerData[playerid][p_SelectingSpawn]) return;

    new total = gPlayerData[playerid][p_IsNewCharacter] ? PUBLIC_SPAWN_COUNT : (PUBLIC_SPAWN_COUNT + 1);
    new idx = gPlayerData[playerid][p_SpawnIndex];

    new title[64], info[256], countStr[32];

    if (!gPlayerData[playerid][p_IsNewCharacter] && idx == 0) {
        format(title, sizeof(title), "~g~* Lokasi Terakhir");
        format(info, sizeof(info),
            "~y~[ SESI TERAKHIR ]~n~\
            ~w~Wilayah: ~g~Posisi Saat Logout~n~\
            ~w~Status: ~w~Karakter Siap Bermain");
    } else {
        new pIdx = gPlayerData[playerid][p_IsNewCharacter] ? idx : (idx - 1);
        format(title, sizeof(title), "~y~%s", gPublicSpawns[pIdx][s_Name]);
        format(info, sizeof(info),
            "~y~[ %s ]~n~\
            ~w~Wilayah: ~w~%s~n~\
            ~w~Fasilitas: ~g~%s",
            gPublicSpawns[pIdx][s_City],
            gPublicSpawns[pIdx][s_Region],
            gPublicSpawns[pIdx][s_Facilities]);
    }

    format(countStr, sizeof(countStr), "%d / %d", idx + 1, total);

    PlayerTextDrawSetString(playerid, TD_SpawnTitle[playerid], title);
    PlayerTextDrawSetString(playerid, TD_SpawnInfo[playerid], info);
    PlayerTextDrawSetString(playerid, TD_SpawnCount[playerid], countStr);
}

stock OpenSpawnSelection(playerid, bool:isNewChar = false) {
    gPlayerData[playerid][p_SelectingSpawn] = true;
    gPlayerData[playerid][p_IsNewCharacter] = isNewChar;
    gPlayerData[playerid][p_SpawnIndex]     = 0;

    // Freeze pemain & sembunyikan HUD uang
    TogglePlayerControllable(playerid, false);
    HidePlayerMoneyHUD(playerid);
    DestroyPlayerSpawnTextDraws(playerid);

    //    Buat UI TextDraw di sebelah KANAN (X: 430 .. 610)       

    // 1. Background Box (#1D1D1D Dark Matte di Kanan)
    TD_SpawnBox[playerid] = CreatePlayerTextDraw(playerid, 430.0, 105.0, "_");
    PlayerTextDrawUseBox(playerid, TD_SpawnBox[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_SpawnBox[playerid], 0x1D1D1DF2);
    PlayerTextDrawTextSize(playerid, TD_SpawnBox[playerid], 610.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_SpawnBox[playerid], 0.0, 24.5);
    PlayerTextDrawSetSelectable(playerid, TD_SpawnBox[playerid], 0);

    // 2. Header Bar Box (#E69958 Warm Amber Header)
    TD_SpawnHeader[playerid] = CreatePlayerTextDraw(playerid, 430.0, 105.0, "   LOKASI AWAL SPAWN");
    PlayerTextDrawFont(playerid, TD_SpawnHeader[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SpawnHeader[playerid], 0.22, 1.4);
    PlayerTextDrawColor(playerid, TD_SpawnHeader[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SpawnHeader[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_SpawnHeader[playerid], 0xE69958FF);
    PlayerTextDrawTextSize(playerid, TD_SpawnHeader[playerid], 610.0, 14.0);
    PlayerTextDrawSetSelectable(playerid, TD_SpawnHeader[playerid], 0);

    // 3. Location Title
    TD_SpawnTitle[playerid] = CreatePlayerTextDraw(playerid, 520.0, 126.0, "Stasiun Cranberry");
    PlayerTextDrawFont(playerid, TD_SpawnTitle[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SpawnTitle[playerid], 0.23, 1.3);
    PlayerTextDrawColor(playerid, TD_SpawnTitle[playerid], 0xFFFF00FF);
    PlayerTextDrawAlignment(playerid, TD_SpawnTitle[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SpawnTitle[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SpawnTitle[playerid], 0);

    // 4. Location Subtitle & Facilities Info
    TD_SpawnInfo[playerid] = CreatePlayerTextDraw(playerid, 440.0, 148.0, "Wilayah: Cranberry Station~n~Fasilitas: Taksi | ATM | Kereta");
    PlayerTextDrawFont(playerid, TD_SpawnInfo[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_SpawnInfo[playerid], 0.17, 1.05);
    PlayerTextDrawColor(playerid, TD_SpawnInfo[playerid], 0xFFFFFFFF);
    PlayerTextDrawSetOutline(playerid, TD_SpawnInfo[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SpawnInfo[playerid], 0);

    // 5. Tombol PREVIOUS (<<)
    TD_SpawnPrev[playerid] = CreatePlayerTextDraw(playerid, 440.0, 218.0, "<<");
    PlayerTextDrawFont(playerid, TD_SpawnPrev[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SpawnPrev[playerid], 0.32, 1.5);
    PlayerTextDrawColor(playerid, TD_SpawnPrev[playerid], 0xE69958FF);
    PlayerTextDrawAlignment(playerid, TD_SpawnPrev[playerid], 2);
    PlayerTextDrawUseBox(playerid, TD_SpawnPrev[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_SpawnPrev[playerid], 0x2D2D2DFF);
    PlayerTextDrawTextSize(playerid, TD_SpawnPrev[playerid], 20.0, 36.0);
    PlayerTextDrawSetOutline(playerid, TD_SpawnPrev[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SpawnPrev[playerid], 1);

    // 6. Indicator (Lokasi 1 / 4)
    TD_SpawnCount[playerid] = CreatePlayerTextDraw(playerid, 520.0, 222.0, "1 / 4");
    PlayerTextDrawFont(playerid, TD_SpawnCount[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SpawnCount[playerid], 0.22, 1.2);
    PlayerTextDrawColor(playerid, TD_SpawnCount[playerid], 0xFFFFFFFF);
    PlayerTextDrawAlignment(playerid, TD_SpawnCount[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SpawnCount[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SpawnCount[playerid], 0);

    // 7. Tombol NEXT (>>)
    TD_SpawnNext[playerid] = CreatePlayerTextDraw(playerid, 600.0, 218.0, ">>");
    PlayerTextDrawFont(playerid, TD_SpawnNext[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SpawnNext[playerid], 0.32, 1.5);
    PlayerTextDrawColor(playerid, TD_SpawnNext[playerid], 0xE69958FF);
    PlayerTextDrawAlignment(playerid, TD_SpawnNext[playerid], 2);
    PlayerTextDrawUseBox(playerid, TD_SpawnNext[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_SpawnNext[playerid], 0x2D2D2DFF);
    PlayerTextDrawTextSize(playerid, TD_SpawnNext[playerid], 20.0, 36.0);
    PlayerTextDrawSetOutline(playerid, TD_SpawnNext[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SpawnNext[playerid], 1);

    // 8. Tombol SPAWN DI SINI (Hijau)
    TD_SpawnConfirm[playerid] = CreatePlayerTextDraw(playerid, 438.0, 252.0, "   [ ~w~SPAWN DI SINI ~y~~h~]~n~ ");
    PlayerTextDrawFont(playerid, TD_SpawnConfirm[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SpawnConfirm[playerid], 0.21, 1.3);
    PlayerTextDrawColor(playerid, TD_SpawnConfirm[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SpawnConfirm[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_SpawnConfirm[playerid], 0x1D6F42FF);
    PlayerTextDrawTextSize(playerid, TD_SpawnConfirm[playerid], 602.0, 16.0);
    PlayerTextDrawSetOutline(playerid, TD_SpawnConfirm[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SpawnConfirm[playerid], 1);

    // 9. Tombol KEMBALI (Merah)
    TD_SpawnCancel[playerid] = CreatePlayerTextDraw(playerid, 438.0, 278.0, "   [ ~w~KEMBALI ~y~~h~]~n~ ");
    PlayerTextDrawFont(playerid, TD_SpawnCancel[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SpawnCancel[playerid], 0.21, 1.3);
    PlayerTextDrawColor(playerid, TD_SpawnCancel[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SpawnCancel[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_SpawnCancel[playerid], 0x481E1EFF);
    PlayerTextDrawTextSize(playerid, TD_SpawnCancel[playerid], 602.0, 16.0);
    PlayerTextDrawSetOutline(playerid, TD_SpawnCancel[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SpawnCancel[playerid], 1);

    // 10. Hint text
    TD_SpawnHint[playerid] = CreatePlayerTextDraw(playerid, 520.0, 305.0, "~w~Klik ~y~<< >> ~w~untuk memilih lokasi");
    PlayerTextDrawFont(playerid, TD_SpawnHint[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_SpawnHint[playerid], 0.16, 0.9);
    PlayerTextDrawColor(playerid, TD_SpawnHint[playerid], 0xCCCCCCFF);
    PlayerTextDrawAlignment(playerid, TD_SpawnHint[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SpawnHint[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SpawnHint[playerid], 0);

    // Tampilkan semua TextDraw
    PlayerTextDrawShow(playerid, TD_SpawnBox[playerid]);
    PlayerTextDrawShow(playerid, TD_SpawnHeader[playerid]);
    PlayerTextDrawShow(playerid, TD_SpawnTitle[playerid]);
    PlayerTextDrawShow(playerid, TD_SpawnInfo[playerid]);
    PlayerTextDrawShow(playerid, TD_SpawnPrev[playerid]);
    PlayerTextDrawShow(playerid, TD_SpawnNext[playerid]);
    PlayerTextDrawShow(playerid, TD_SpawnCount[playerid]);
    PlayerTextDrawShow(playerid, TD_SpawnConfirm[playerid]);
    PlayerTextDrawShow(playerid, TD_SpawnCancel[playerid]);
    PlayerTextDrawShow(playerid, TD_SpawnHint[playerid]);

    UpdateSpawnSelectorUI(playerid);
    UpdateSpawnSelectorCamera(playerid);

    SelectTextDraw(playerid, 0xE69958FF);
}

stock CloseSpawnSelection(playerid) {
    gPlayerData[playerid][p_SelectingSpawn] = false;
    CancelSelectTextDraw(playerid);
    DestroyPlayerSpawnTextDraws(playerid);
    TogglePlayerSpectating(playerid, false);
}
