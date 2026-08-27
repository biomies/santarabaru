#if defined _MODULE_SPAWN_SELECTOR_INC
    #endinput
#endif
#define _MODULE_SPAWN_SELECTOR_INC

// ============================================================
//  SantaraBaru Roleplay - Eagle-Eye Spawn Selector UI (Lokasi Awal Spawn)
//  Dark Indigo (#1E1E2E) & Electric Purple (#5814EE) Theme
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
        -1985.0, 280.0, 35.17, 180.0,
        -1910.0, 220.0, 68.0,
        -1985.0, 280.0, 35.17
    },

    //                                                           
    //  KOTA 3: LAS VENTURAS (LV)
    //                                                           
    // 10: Stasiun Yellow Bell (Las Venturas)
    {
        "Kota 3: Las Venturas", "Stasiun Yellow Bell", "Yellow Bell Station, LV", "Taksi ~w~| ~g~ATM ~w~| ~g~Kereta Api",
        1463.0, 2635.0, 10.82, 0.0,
        1520.0, 2570.0, 45.0,
        1463.0, 2635.0, 10.82
    },
    // 11: Bandara Las Venturas (LVX)
    {
        "Kota 3: Las Venturas", "Bandara Las Venturas", "LV International Airport", "Penerbangan ~w~| ~g~Taksi ~w~| ~g~ATM",
        1602.0, 1618.0, 10.82, 270.0,
        1670.0, 1550.0, 55.0,
        1602.0, 1618.0, 10.82
    },
    // 12: Las Venturas Strip / The Emerald
    {
        "Kota 3: Las Venturas", "The Strip Casino", "Las Venturas Boulevard", "Pusat Hiburan ~w~| ~g~Kasino ~w~| ~g~ATM",
        2024.0, 1008.0, 10.82, 90.0,
        2090.0, 940.0, 52.0,
        2024.0, 1008.0, 10.82
    },
    // 13: Terminal Bus Las Venturas
    {
        "Kota 3: Las Venturas", "Terminal Bus LV", "Redsands East Terminal, LV", "Bus Antarkota ~w~| ~g~Taksi ~w~| ~g~ATM",
        2185.0, 2045.0, 10.82, 180.0,
        2250.0, 1980.0, 48.0,
        2185.0, 2045.0, 10.82
    },

    //                                                           
    //  PEDESAAN & WILAYAH KHUSUS
    //                                                           
    // 14: Fort Carson (Tierra Robada)
    {
        "Pedesaan: Tierra Robada", "Fort Carson", "Fort Carson Town Square", "Klinik ~w~| ~g~ATM ~w~| ~g~Rest Area",
        -216.5, 979.0, 19.55, 90.0,
        -150.0, 920.0, 55.0,
        -216.5, 979.0, 19.55
    },
    // 15: Angel Pine (Whetstone / Mt Chiliad)
    {
        "Pedesaan: Whetstone", "Angel Pine", "Angel Pine Town Center", "Wisata Gunung ~w~| ~g~Klinik ~w~| ~g~Motel",
        -2160.0, -2390.0, 30.62, 225.0,
        -2090.0, -2450.0, 65.0,
        -2160.0, -2390.0, 30.62
    },
    // 16: Blueberry (Red County)
    {
        "Pedesaan: Red County", "Blueberry", "Blueberry Commercial Area", "Pusat Logistik ~w~| ~g~ATM ~w~| ~g~Resto",
        230.0, -58.0, 1.57, 180.0,
        290.0, -120.0, 42.0,
        230.0, -58.0, 1.57
    },
    // 17: Montgomery (Red County)
    {
        "Pedesaan: Red County", "Montgomery", "Montgomery Hospital Square", "Rumah Sakit ~w~| ~g~Apotek ~w~| ~g~ATM",
        1380.0, 260.0, 19.56, 90.0,
        1440.0, 200.0, 50.0,
        1380.0, 260.0, 19.56
    },
    // 18: Dillimore (Red County)
    {
        "Pedesaan: Red County", "Dillimore", "Dillimore Sheriff Station", "Kantor Polisi ~w~| ~g~ATM ~w~| ~g~Bengkel",
        655.0, -565.0, 16.33, 90.0,
        715.0, -620.0, 48.0,
        655.0, -565.0, 16.33
    },
    // 19: Palomino Creek (Red County)
    {
        "Pedesaan: Red County", "Palomino Creek", "Palomino Creek Center", "Bank Cabang ~w~| ~g~ATM ~w~| ~g~Resto",
        2255.0, -85.0, 26.50, 180.0,
        2315.0, -145.0, 55.0,
        2255.0, -85.0, 26.50
    }
};

#define PUBLIC_SPAWN_COUNT (sizeof(gPublicSpawns))

// Colors from Reference Design
#define COLOR_SPAWN_BG       0x1E1E2EFF  // Dark Indigo Background
#define COLOR_SPAWN_PURPLE   0x5814EEFF  // Electric Purple Accent & Action
#define COLOR_SPAWN_RED      0xFA1E38FF  // Vibrant Red Cancel Button
#define COLOR_SPAWN_SLATE    0x3E3E44EE  // Dark Slate Button

// TextDraw Handles Spawn Selector (Sisi Kanan X: 430.0 .. 620.0)
new PlayerText:TD_SpawnBox[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpawnTopBar[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpawnTitle[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpawnInfo[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpawnPrev[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpawnNext[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpawnConfirm[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SpawnCancel[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};

stock DestroyPlayerSpawnTextDraws(playerid) {
    if (TD_SpawnBox[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SpawnBox[playerid]);
        TD_SpawnBox[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SpawnTopBar[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SpawnTopBar[playerid]);
        TD_SpawnTopBar[playerid] = PlayerText:INVALID_TEXT_DRAW;
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
    if (TD_SpawnConfirm[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SpawnConfirm[playerid]);
        TD_SpawnConfirm[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SpawnCancel[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SpawnCancel[playerid]);
        TD_SpawnCancel[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
}

stock UpdateSpawnSelectorCamera(playerid) {
    if (!gPlayerData[playerid][p_SelectingSpawn]) return;

    new idx = gPlayerData[playerid][p_SpawnIndex];

    if (gPlayerData[playerid][p_IsNewCharacter]) {
        // Karakter baru: langsung pilih dari preset
        SetPlayerCameraPos(playerid,
            gPublicSpawns[idx][s_CamX],
            gPublicSpawns[idx][s_CamY],
            gPublicSpawns[idx][s_CamZ]);
        SetPlayerCameraLookAt(playerid,
            gPublicSpawns[idx][s_LookX],
            gPublicSpawns[idx][s_LookY],
            gPublicSpawns[idx][s_LookZ], CAMERA_CUT);
    } else {
        if (idx == 0) {
            // Posisi Terakhir Karakter
            new Float:px = gPlayerData[playerid][p_X];
            new Float:py = gPlayerData[playerid][p_Y];
            new Float:pz = gPlayerData[playerid][p_Z];

            SetPlayerCameraPos(playerid, px + 55.0, py - 55.0, pz + 45.0);
            SetPlayerCameraLookAt(playerid, px, py, pz + 1.0, CAMERA_CUT);
        } else {
            new pIdx = idx - 1;
            SetPlayerCameraPos(playerid,
                gPublicSpawns[pIdx][s_CamX],
                gPublicSpawns[pIdx][s_CamY],
                gPublicSpawns[pIdx][s_CamZ]);
            SetPlayerCameraLookAt(playerid,
                gPublicSpawns[pIdx][s_LookX],
                gPublicSpawns[pIdx][s_LookY],
                gPublicSpawns[pIdx][s_LookZ], CAMERA_CUT);
        }
    }
}

stock UpdateSpawnSelectorUI(playerid) {
    if (!gPlayerData[playerid][p_SelectingSpawn]) return;

    new idx = gPlayerData[playerid][p_SpawnIndex];
    new info[128];

    if (gPlayerData[playerid][p_IsNewCharacter]) {
        format(info, sizeof(info), "~w~Wilayah : ~w~%s", gPublicSpawns[idx][s_Name]);
    } else {
        if (idx == 0) {
            format(info, sizeof(info), "~w~Wilayah : ~w~Sesi terakhir");
        } else {
            new pIdx = idx - 1;
            format(info, sizeof(info), "~w~Wilayah : ~w~%s", gPublicSpawns[pIdx][s_Name]);
        }
    }

    PlayerTextDrawSetString(playerid, TD_SpawnInfo[playerid], info);
    PlayerTextDrawShow(playerid, TD_SpawnInfo[playerid]);
}

stock OpenSpawnSelection(playerid, bool:isNewChar = false) {
    gPlayerData[playerid][p_SelectingSpawn] = true;
    gPlayerData[playerid][p_IsNewCharacter] = isNewChar;
    gPlayerData[playerid][p_SpawnIndex]     = 0;

    // Freeze pemain & sembunyikan HUD uang
    TogglePlayerControllable(playerid, false);
    HidePlayerMoneyHUD(playerid);
    DestroyPlayerSpawnTextDraws(playerid);

    //    Buat UI TextDraw di sebelah KANAN (X: 430.0 .. 620.0, Y: 100.0 .. 255.0)

    // 1. Background Box (Dark Indigo #1E1E2EFF di Kanan)
    TD_SpawnBox[playerid] = CreatePlayerTextDraw(playerid, 430.0, 100.0, "_");
    PlayerTextDrawUseBox(playerid, TD_SpawnBox[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_SpawnBox[playerid], COLOR_SPAWN_BG);
    PlayerTextDrawTextSize(playerid, TD_SpawnBox[playerid], 620.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_SpawnBox[playerid], 0.0, 17.0);
    PlayerTextDrawSetSelectable(playerid, TD_SpawnBox[playerid], false);

    // 2. Top Accent Line (Electric Purple #5814EEFF, X: 430.0 .. 620.0, Y: 100.0)
    TD_SpawnTopBar[playerid] = CreatePlayerTextDraw(playerid, 430.0, 100.0, "_");
    PlayerTextDrawUseBox(playerid, TD_SpawnTopBar[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_SpawnTopBar[playerid], COLOR_SPAWN_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_SpawnTopBar[playerid], 620.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_SpawnTopBar[playerid], 0.0, 0.75);
    PlayerTextDrawSetSelectable(playerid, TD_SpawnTopBar[playerid], false);

    // 3. Header Title Tile [ Lokasi Awal Spawn ] (Center X: 525.0, Y: 112.0)
    TD_SpawnTitle[playerid] = CreatePlayerTextDraw(playerid, 525.0, 112.0, "Lokasi Awal Spawn");
    PlayerTextDrawFont(playerid, TD_SpawnTitle[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SpawnTitle[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_SpawnTitle[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SpawnTitle[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_SpawnTitle[playerid], COLOR_SPAWN_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_SpawnTitle[playerid], 14.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_SpawnTitle[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SpawnTitle[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SpawnTitle[playerid], false);

    // 4. Spawn Info Text Box (Wilayah) (X: 442.0, Y: 138.0)
    TD_SpawnInfo[playerid] = CreatePlayerTextDraw(playerid, 442.0, 138.0, "Memuat info wilayah...");
    PlayerTextDrawFont(playerid, TD_SpawnInfo[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_SpawnInfo[playerid], 0.18, 1.00);
    PlayerTextDrawColor(playerid, TD_SpawnInfo[playerid], 0xFFFFFFFF);
    PlayerTextDrawSetOutline(playerid, TD_SpawnInfo[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SpawnInfo[playerid], false);

    // 5. Navigation Button: < Sebelum (Center X: 481.0, Y: 172.0)
    TD_SpawnPrev[playerid] = CreatePlayerTextDraw(playerid, 481.0, 172.0, "< Sebelum");
    PlayerTextDrawFont(playerid, TD_SpawnPrev[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SpawnPrev[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_SpawnPrev[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SpawnPrev[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_SpawnPrev[playerid], COLOR_SPAWN_SLATE);
    PlayerTextDrawTextSize(playerid, TD_SpawnPrev[playerid], 14.0, 82.0);
    PlayerTextDrawAlignment(playerid, TD_SpawnPrev[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SpawnPrev[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SpawnPrev[playerid], true);

    // 6. Navigation Button: Selanjutnya > (Center X: 569.0, Y: 172.0)
    TD_SpawnNext[playerid] = CreatePlayerTextDraw(playerid, 569.0, 172.0, "Selanjutnya >");
    PlayerTextDrawFont(playerid, TD_SpawnNext[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SpawnNext[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_SpawnNext[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SpawnNext[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_SpawnNext[playerid], COLOR_SPAWN_SLATE);
    PlayerTextDrawTextSize(playerid, TD_SpawnNext[playerid], 14.0, 82.0);
    PlayerTextDrawAlignment(playerid, TD_SpawnNext[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SpawnNext[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SpawnNext[playerid], true);

    // 7. Primary Action Button: [ Gunakan ] (Center X: 525.0, Y: 196.0)
    TD_SpawnConfirm[playerid] = CreatePlayerTextDraw(playerid, 525.0, 196.0, "Gunakan");
    PlayerTextDrawFont(playerid, TD_SpawnConfirm[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SpawnConfirm[playerid], 0.17, 1.05);
    PlayerTextDrawColor(playerid, TD_SpawnConfirm[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SpawnConfirm[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_SpawnConfirm[playerid], COLOR_SPAWN_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_SpawnConfirm[playerid], 15.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_SpawnConfirm[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SpawnConfirm[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SpawnConfirm[playerid], true);

    // 8. Secondary Button: [ Batal ] (Center X: 525.0, Y: 218.0)
    TD_SpawnCancel[playerid] = CreatePlayerTextDraw(playerid, 525.0, 218.0, "Batal");
    PlayerTextDrawFont(playerid, TD_SpawnCancel[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SpawnCancel[playerid], 0.17, 1.05);
    PlayerTextDrawColor(playerid, TD_SpawnCancel[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SpawnCancel[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_SpawnCancel[playerid], COLOR_SPAWN_RED);
    PlayerTextDrawTextSize(playerid, TD_SpawnCancel[playerid], 15.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_SpawnCancel[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SpawnCancel[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SpawnCancel[playerid], true);

    // Tampilkan semua TextDraw ke pemain
    PlayerTextDrawShow(playerid, TD_SpawnBox[playerid]);
    PlayerTextDrawShow(playerid, TD_SpawnTopBar[playerid]);
    PlayerTextDrawShow(playerid, TD_SpawnTitle[playerid]);
    PlayerTextDrawShow(playerid, TD_SpawnInfo[playerid]);
    PlayerTextDrawShow(playerid, TD_SpawnPrev[playerid]);
    PlayerTextDrawShow(playerid, TD_SpawnNext[playerid]);
    PlayerTextDrawShow(playerid, TD_SpawnConfirm[playerid]);
    PlayerTextDrawShow(playerid, TD_SpawnCancel[playerid]);

    UpdateSpawnSelectorUI(playerid);
    UpdateSpawnSelectorCamera(playerid);

    SelectTextDraw(playerid, COLOR_SPAWN_PURPLE);
}

stock CloseSpawnSelection(playerid, bool:cancelSelect = true) {
    gPlayerData[playerid][p_SelectingSpawn] = false;
    if (cancelSelect) {
        CancelSelectTextDraw(playerid);
    }
    DestroyPlayerSpawnTextDraws(playerid);
}
