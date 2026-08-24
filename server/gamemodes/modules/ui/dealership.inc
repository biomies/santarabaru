#if defined _MODULE_DEALERSHIP_INC
    #endinput
#endif
#define _MODULE_DEALERSHIP_INC

// ============================================================
//  SantaraBaru Roleplay — Rodeo Luxury Dealership & Live 3D UI
// ============================================================

enum E_DEALER_VEHICLE {
    d_ModelID,
    d_Name[28],
    d_Type[28],
    d_Price,
    d_TopSpeed,
    d_Seats
};

// ── 1. Mobil Sport, Tuners & Supercar (24 Kendaraan) ────────
new const gSportVehicles[][E_DEALER_VEHICLE] = {
    {411, "Infernus",       "Supercar V12 Top",     750000000, 240, 2},
    {451, "Turismo",        "Supercar Italia",      680000000, 235, 2},
    {541, "Bullet",         "Supercar Balap",       580000000, 230, 2},
    {415, "Cheetah",        "Supercar Klasik",      520000000, 225, 2},
    {429, "Banshee",        "Roadster Sport V10",   450000000, 220, 2},
    {506, "Super GT",       "Grand Tourer V8",      480000000, 225, 2},
    {477, "ZR-350",         "Rotary Sport Coupe",   260000000, 210, 2},
    {480, "Comet",          "Convertible Sport",    380000000, 215, 2},
    {402, "Buffalo",        "Modern Muscle V8",     240000000, 205, 2},
    {602, "Alpha",          "Luxury Sport Coupe",   290000000, 210, 2},
    {603, "Phoenix",        "Classic Muscle V8",    230000000, 200, 2},
    {587, "Euros",          "Touring Sport Coupe",  220000000, 200, 2},
    {560, "Sultan",         "Sedan Sport 4-Pintu",  320000000, 210, 4},
    {562, "Elegy",          "Drift King Tuner",     290000000, 205, 2},
    {559, "Jester",         "Tuner Sport Coupe",    275000000, 200, 2},
    {565, "Flash",          "Hatchback Sport",      210000000, 195, 2},
    {558, "Uranus",         "Street Tuner Coupe",   200000000, 190, 2},
    {561, "Stratum",        "Sport Station Wagon",  185000000, 185, 4},
    {494, "Hotring Racer",  "NASCAR Track Racer",   600000000, 245, 2},
    {502, "Hotring Racer A","NASCAR Track Racer A", 600000000, 245, 2},
    {503, "Hotring Racer B","NASCAR Track Racer B", 600000000, 245, 2},
    {555, "Windsor",        "Luxury Convertible",   310000000, 190, 2},
    {589, "Club",           "Compact Sport",        160000000, 185, 2},
    {434, "Hotknife",       "Custom Hot Rod",       420000000, 200, 2}
};

// ── 2. Mobil Sedan, Klasik & Lowrider (46 Kendaraan) ────────
new const gSedanVehicles[][E_DEALER_VEHICLE] = {
    {426, "Premier",        "Sedan Harian Tangguh",  95000000, 190, 4},
    {405, "Sentinel",       "Sedan Eksekutif Mewah",140000000, 190, 4},
    {421, "Washington",     "Sedan Pejabat Berkelas",165000000, 185, 4},
    {445, "Admiral",        "Sedan Klasik Eropa",   110000000, 180, 4},
    {507, "Elegant",        "Sedan Nyaman Elegan",  135000000, 185, 4},
    {551, "Merit",          "Sedan Menengah Modern",105000000, 180, 4},
    {550, "Sunrise",        "Sedan Keluarga Irit",   98000000, 175, 4},
    {580, "Stafford",       "Vintage Royal Luxury", 340000000, 175, 4},
    {585, "Emperor",        "Sedan Klasik Nyaman",   88000000, 170, 4},
    {540, "Vincent",        "Sedan Kompak Harian",   78000000, 165, 4},
    {546, "Intruder",       "Sedan 4-Pintu Sporty",  82000000, 170, 4},
    {547, "Primo",          "Sedan Standar Murah",   65000000, 160, 4},
    {516, "Nebula",         "Sedan Keluarga Santai", 72000000, 165, 4},
    {529, "Willard",        "Sedan Komuter Kota",    68000000, 160, 4},
    {492, "Greenwood",      "Sedan Retro Klasik",    75000000, 165, 4},
    {466, "Glendale",       "Sedan Vintage 1960s",   55000000, 155, 4},
    {467, "Oceanic",        "Sedan Klasik Elegan",   62000000, 160, 4},
    {474, "Hermes",         "Lead Sled Custom",     120000000, 160, 2},
    {567, "Savanna",        "Lowrider 4-Pintu",     175000000, 185, 4},
    {566, "Tahoma",         "Lowrider Sedan Mewah",  85000000, 175, 4},
    {536, "Blade",          "Lowrider Coupe V8",    160000000, 190, 2},
    {534, "Remington",      "Luxury Lowrider Coupe",195000000, 185, 2},
    {535, "Slamvan",        "Custom Lowrider Truck",180000000, 180, 2},
    {412, "Voodoo",         "Lowrider Klasik V8",   130000000, 180, 2},
    {575, "Broadway",       "Vintage Convertible",  150000000, 170, 2},
    {576, "Tornado",        "Classic Lowrider 50s", 115000000, 170, 2},
    {545, "Hustler",        "1930s Gangster Coupe", 210000000, 165, 2},
    {527, "Cadrona",        "Coupe 2-Pintu Murah",   58000000, 165, 2},
    {526, "Fortune",        "Coupe Nyaman 2-Pintu",  64000000, 170, 2},
    {517, "Majestic",       "Sedan Coupe Klasik",    69000000, 170, 2},
    {518, "Buccaneer",      "Muscle Coupe Klasik",   85000000, 175, 2},
    {419, "Esperanto",      "Sedan Retro Mewah",     76000000, 165, 2},
    {533, "Feltzer",        "Roadster Klasik Elegan",145000000, 180, 2},
    {542, "Clover",         "Muscle Car Murah",      52000000, 175, 2},
    {549, "Tampa",          "Classic Muscle Coupe",  70000000, 170, 2},
    {491, "Virgo",          "Coupe Retro Nyaman",    66000000, 165, 2},
    {475, "Sabre",          "Street Muscle V8",     110000000, 185, 2},
    {439, "Stallion",       "Convertible Muscle",   125000000, 185, 2},
    {436, "Previon",        "Coupe Irit Praktis",    48000000, 160, 2},
    {401, "Bravura",        "Coupe Pemula Murah",    42000000, 155, 2},
    {410, "Manana",         "Hatchback Klasik",      38000000, 145, 2},
    {496, "Blista Compact", "Hatchback Lincah Irit", 70000000, 175, 2},
    {404, "Perennial",      "Station Wagon Murah",   45000000, 145, 4},
    {479, "Regina",         "Station Wagon Klasik",  56000000, 155, 4},
    {458, "Solair",         "Station Wagon Nyaman",  74000000, 165, 4},
    {418, "Moonbeam",       "Minivan Keluarga Luas", 60000000, 145, 4}
};

// ── 3. SUV, Pick-up & Off-Road (23 Kendaraan) ───────────────
new const gSuvVehicles[][E_DEALER_VEHICLE] = {
    {579, "Huntley",        "Luxury Premium SUV",   350000000, 180, 4},
    {400, "Landstalker",    "SUV Keluarga Tangguh", 180000000, 170, 4},
    {489, "Rancher",        "SUV Off-road 2-Pintu", 150000000, 165, 2},
    {500, "Mesa",           "Jeep Terbuka 4x4",     160000000, 160, 2},
    {495, "Sandking",       "Truk Reli Padang Pasir",490000000, 195, 2},
    {444, "Monster",        "Monster Truck V8",     650000000, 140, 2},
    {556, "Monster A",      "Monster Truck A",      650000000, 140, 2},
    {557, "Monster B",      "Monster Truck B",      650000000, 140, 2},
    {554, "Yosemite",       "Pick-up Modern Perkasa",125000000, 165, 2},
    {422, "Bobcat",         "Pick-up Utility Murah", 75000000, 155, 2},
    {600, "Picador",        "Coupe Pick-up Klasik",  80000000, 165, 2},
    {478, "Walton",         "Vintage Farm Truck",    35000000, 130, 2},
    {543, "Sadler",         "Pick-up Pekerja Keras", 40000000, 145, 2},
    {568, "Bandito",        "Baja Sand Buggy",      180000000, 175, 1},
    {424, "BF Injection",   "Custom Beach Buggy",   110000000, 165, 2},
    {573, "Dune",           "Dakar Heavy Truck",    450000000, 140, 2},
    {482, "Burrito",        "Van Kargo Tertutup",   115000000, 165, 4},
    {413, "Pony",           "Van Komersial Serbaguna",85000000, 145, 2},
    {440, "Rumpo",          "Van Pengangkut Barang", 90000000, 150, 4},
    {483, "Camper",         "Hippie Camper Van",    140000000, 135, 3},
    {508, "Journey",        "Motorhome Karavan Luas",220000000, 130, 2},
    {571, "Kart",           "Go-Kart Sirkuit Mini",  50000000, 110, 1},
    {471, "Quad",           "ATV Roda 4 Petualang",  45000000, 130, 2}
};

// ── 4. Sepeda Motor, Skuter & Sepeda (12 Kendaraan) ─────────
new const gBikeVehicles[][E_DEALER_VEHICLE] = {
    {522, "NRG-500",        "Superbike Balap 500cc",250000000, 210, 2},
    {521, "FCR-900",        "Naked Sport 900cc",    175000000, 190, 2},
    {461, "PCJ-600",        "Sport Bike 600cc",     120000000, 185, 2},
    {581, "BF-400",         "Streetfighter 400cc",   90000000, 175, 2},
    {468, "Sanchez",        "Motor Trail Cross 4x4", 65000000, 165, 2},
    {463, "Freeway",        "Cruiser Moge Klasik",  140000000, 160, 2},
    {586, "Wayfarer",       "Touring Cruiser Moge", 130000000, 160, 2},
    {462, "Faggio",         "Skuter Matic Praktis",  25000000, 110, 2},
    {448, "Pizzaboy",       "Skuter Delivery Lincah",30000000, 115, 1},
    {510, "Mountain Bike",  "Sepeda Gunung 21-Speed", 8500000,  60, 1},
    {481, "BMX",            "Sepeda Freestyle BMX",   6000000,  55, 1},
    {509, "Bike",           "Sepeda Santai Klasik",   4500000,  50, 1}
};

// ── Warna Display Dealer (18 Warna Populer GTA SA) ──────────
new const gDealerColors[] = {
    1,   // Putih
    0,   // Hitam
    3,   // Merah
    6,   // Biru Tua
    8,   // Biru Langit
    12,  // Hijau Tua
    16,  // Hijau Daun
    25,  // Kuning Cerah
    36,  // Emas / Bronze
    42,  // Cokelat
    53,  // Ungu
    65,  // Oranye
    79,  // Abu-Abu Gelap
    86,  // Abu-Abu Terang / Silver
    92,  // Cyan / Teal
    101, // Merah Marun
    114, // Biru Sapphire
    126  // Putih Mutiara
};
#define DEALER_COLOR_COUNT (sizeof(gDealerColors))

new const gDealerColorNames[][20] = {
    "Putih Salju", "Hitam Glossy", "Merah Sport", "Biru Tua", "Biru Langit",
    "Hijau Tua", "Hijau Daun", "Kuning Cerah", "Emas / Bronze", "Cokelat",
    "Ungu Metalik", "Oranye Balap", "Abu-Abu Gelap", "Silver Metalik",
    "Teal / Cyan", "Merah Marun", "Biru Sapphire", "Putih Mutiara"
};

// TextDraw Handles Dealership (Sisi Kanan X: 430.0 .. 610.0)
new PlayerText:TD_DealerBox[MAX_PLAYERS]       = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_DealerHeader[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_DealerTitle[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_DealerCatBadge[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_DealerInfo[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_DealerPrev[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_DealerNext[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_DealerCatBtn[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_DealerColorBtn[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_DealerBuyBtn[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_DealerCancelBtn[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_DealerHint[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};

stock GetDealerCategoryCount(cat) {
    switch (cat) {
        case DEALER_CAT_SPORT: return sizeof(gSportVehicles);
        case DEALER_CAT_SEDAN: return sizeof(gSedanVehicles);
        case DEALER_CAT_SUV:   return sizeof(gSuvVehicles);
        case DEALER_CAT_BIKE:  return sizeof(gBikeVehicles);
    }
    return 0;
}

stock GetDealerVehicleData(cat, idx, &modelid, name[], type[], &price, &topspeed, &seats) {
    switch (cat) {
        case DEALER_CAT_SPORT: {
            if (idx < 0 || idx >= sizeof(gSportVehicles)) idx = 0;
            modelid = gSportVehicles[idx][d_ModelID];
            format(name, 28, "%s", gSportVehicles[idx][d_Name]);
            format(type, 28, "%s", gSportVehicles[idx][d_Type]);
            price = gSportVehicles[idx][d_Price];
            topspeed = gSportVehicles[idx][d_TopSpeed];
            seats = gSportVehicles[idx][d_Seats];
        }
        case DEALER_CAT_SEDAN: {
            if (idx < 0 || idx >= sizeof(gSedanVehicles)) idx = 0;
            modelid = gSedanVehicles[idx][d_ModelID];
            format(name, 28, "%s", gSedanVehicles[idx][d_Name]);
            format(type, 28, "%s", gSedanVehicles[idx][d_Type]);
            price = gSedanVehicles[idx][d_Price];
            topspeed = gSedanVehicles[idx][d_TopSpeed];
            seats = gSedanVehicles[idx][d_Seats];
        }
        case DEALER_CAT_SUV: {
            if (idx < 0 || idx >= sizeof(gSuvVehicles)) idx = 0;
            modelid = gSuvVehicles[idx][d_ModelID];
            format(name, 28, "%s", gSuvVehicles[idx][d_Name]);
            format(type, 28, "%s", gSuvVehicles[idx][d_Type]);
            price = gSuvVehicles[idx][d_Price];
            topspeed = gSuvVehicles[idx][d_TopSpeed];
            seats = gSuvVehicles[idx][d_Seats];
        }
        case DEALER_CAT_BIKE: {
            if (idx < 0 || idx >= sizeof(gBikeVehicles)) idx = 0;
            modelid = gBikeVehicles[idx][d_ModelID];
            format(name, 28, "%s", gBikeVehicles[idx][d_Name]);
            format(type, 28, "%s", gBikeVehicles[idx][d_Type]);
            price = gBikeVehicles[idx][d_Price];
            topspeed = gBikeVehicles[idx][d_TopSpeed];
            seats = gBikeVehicles[idx][d_Seats];
        }
    }
}

stock DestroyPlayerDealerTextDraws(playerid) {
    if (TD_DealerBox[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_DealerBox[playerid]);
        TD_DealerBox[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_DealerHeader[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_DealerHeader[playerid]);
        TD_DealerHeader[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_DealerTitle[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_DealerTitle[playerid]);
        TD_DealerTitle[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_DealerCatBadge[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_DealerCatBadge[playerid]);
        TD_DealerCatBadge[playerid] = PlayerText:INVALID_TEXT_DRAW;
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
    if (TD_DealerCatBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_DealerCatBtn[playerid]);
        TD_DealerCatBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_DealerColorBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_DealerColorBtn[playerid]);
        TD_DealerColorBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_DealerBuyBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_DealerBuyBtn[playerid]);
        TD_DealerBuyBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_DealerCancelBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_DealerCancelBtn[playerid]);
        TD_DealerCancelBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_DealerHint[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_DealerHint[playerid]);
        TD_DealerHint[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
}

stock UpdateDealershipUI(playerid) {
    if (!gPlayerData[playerid][p_InDealership]) return;

    new cat = gPlayerData[playerid][p_DealerCat];
    new idx = gPlayerData[playerid][p_DealerIndex];
    new colorIdx = gPlayerData[playerid][p_DealerColorIdx];
    new count = GetDealerCategoryCount(cat);

    new modelid, name[28], type[28], price, topspeed, seats;
    GetDealerVehicleData(cat, idx, modelid, name, type, price, topspeed, seats);

    // Update Badge Kategori
    new badgeStr[48];
    switch (cat) {
        case DEALER_CAT_SPORT: format(badgeStr, sizeof(badgeStr), "Kategori: MOBIL SPORT");
        case DEALER_CAT_SEDAN: format(badgeStr, sizeof(badgeStr), "Kategori: SEDAN & KLASIK");
        case DEALER_CAT_SUV:   format(badgeStr, sizeof(badgeStr), "Kategori: SUV & OFF-ROAD");
        case DEALER_CAT_BIKE:  format(badgeStr, sizeof(badgeStr), "Kategori: MOTOR & SKUTER");
    }
    PlayerTextDrawSetString(playerid, TD_DealerCatBadge[playerid], badgeStr);

    // Format Harga & Uang Pemain (dengan pemisah ribuan)
    new priceStr[32], cashStr[32];
    FormatRupiah(price, priceStr, sizeof(priceStr));
    FormatRupiah(gPlayerData[playerid][p_Cash], cashStr, sizeof(cashStr));

    new moneyColor[8];
    if (gPlayerData[playerid][p_Cash] >= price) {
        format(moneyColor, sizeof(moneyColor), "~g~");
    } else {
        format(moneyColor, sizeof(moneyColor), "~r~");
    }

    new str[384];
    format(str, sizeof(str),
        "~w~Kendaraan : ~y~%s~n~" \
        "~w~Model GTA : ~y~#%d~n~" \
        "~w~Tipe : ~w~%s~n~" \
        "~w~Top Speed : ~g~%d km/h~n~" \
        "~w~Kapasitas : ~w~%d Kursi~n~" \
        "~w~Warna : ~y~%s~n~" \
        "~w~Harga : ~g~%s~n~" \
        "~w~Uang Anda : %s%s~n~" \
        "~w~Pilihan : ~y~%d / %d",
        name, modelid, type, topspeed, seats,
        gDealerColorNames[colorIdx], priceStr, moneyColor, cashStr,
        idx + 1, count);

    PlayerTextDrawSetString(playerid, TD_DealerInfo[playerid], str);
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
        // Link to player's virtual world if needed (VW 0)
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

    // ── Buat UI TextDraw Dealership di KANAN (X: 430 .. 610) ───

    // 1. Background Box (#1D1D1D Dark Matte di Kanan)
    TD_DealerBox[playerid] = CreatePlayerTextDraw(playerid, 430.0, 95.0, "_");
    PlayerTextDrawUseBox(playerid, TD_DealerBox[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_DealerBox[playerid], 0x1D1D1DF5);
    PlayerTextDrawTextSize(playerid, TD_DealerBox[playerid], 610.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_DealerBox[playerid], 0.0, 31.0);
    PlayerTextDrawSetSelectable(playerid, TD_DealerBox[playerid], 0);

    // 2. Header Bar Box (#00BCD4 Teal Cyan Header)
    TD_DealerHeader[playerid] = CreatePlayerTextDraw(playerid, 430.0, 95.0, "_");
    PlayerTextDrawUseBox(playerid, TD_DealerHeader[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_DealerHeader[playerid], 0x00BCD4FF);
    PlayerTextDrawTextSize(playerid, TD_DealerHeader[playerid], 610.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_DealerHeader[playerid], 0.0, 2.7);
    PlayerTextDrawSetSelectable(playerid, TD_DealerHeader[playerid], 0);

    // 3. Header Title Text
    TD_DealerTitle[playerid] = CreatePlayerTextDraw(playerid, 520.0, 100.0, "RODEO DEALERSHIP");
    PlayerTextDrawFont(playerid, TD_DealerTitle[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_DealerTitle[playerid], 0.25, 1.2);
    PlayerTextDrawColor(playerid, TD_DealerTitle[playerid], 0xFFFFFFFF);
    PlayerTextDrawAlignment(playerid, TD_DealerTitle[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_DealerTitle[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_DealerTitle[playerid], 0);

    // 4. Badge Kategori Bar
    TD_DealerCatBadge[playerid] = CreatePlayerTextDraw(playerid, 520.0, 126.0, "Kategori: MOBIL SPORT");
    PlayerTextDrawFont(playerid, TD_DealerCatBadge[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_DealerCatBadge[playerid], 0.19, 1.05);
    PlayerTextDrawColor(playerid, TD_DealerCatBadge[playerid], 0x00EEFFFF);
    PlayerTextDrawAlignment(playerid, TD_DealerCatBadge[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_DealerCatBadge[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_DealerCatBadge[playerid], 0);

    // 5. Vehicle Info Text Box
    TD_DealerInfo[playerid] = CreatePlayerTextDraw(playerid, 438.0, 142.0, "Memuat info kendaraan...");
    PlayerTextDrawFont(playerid, TD_DealerInfo[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_DealerInfo[playerid], 0.21, 1.05);
    PlayerTextDrawColor(playerid, TD_DealerInfo[playerid], 0xFFFFFFFF);
    PlayerTextDrawSetOutline(playerid, TD_DealerInfo[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_DealerInfo[playerid], 0);

    // 6. Button: << PREV (Clickable)
    TD_DealerPrev[playerid] = CreatePlayerTextDraw(playerid, 438.0, 246.0, "< SEBELUM");
    PlayerTextDrawFont(playerid, TD_DealerPrev[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_DealerPrev[playerid], 0.20, 1.25);
    PlayerTextDrawColor(playerid, TD_DealerPrev[playerid], 0x00BCD4FF);
    PlayerTextDrawUseBox(playerid, TD_DealerPrev[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_DealerPrev[playerid], 0x2A2A2AFF);
    PlayerTextDrawTextSize(playerid, TD_DealerPrev[playerid], 517.0, 15.0);
    PlayerTextDrawSetOutline(playerid, TD_DealerPrev[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_DealerPrev[playerid], 1);

    // 7. Button: NEXT >> (Clickable)
    TD_DealerNext[playerid] = CreatePlayerTextDraw(playerid, 524.0, 246.0, "LANJUT >");
    PlayerTextDrawFont(playerid, TD_DealerNext[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_DealerNext[playerid], 0.20, 1.25);
    PlayerTextDrawColor(playerid, TD_DealerNext[playerid], 0x00BCD4FF);
    PlayerTextDrawUseBox(playerid, TD_DealerNext[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_DealerNext[playerid], 0x2A2A2AFF);
    PlayerTextDrawTextSize(playerid, TD_DealerNext[playerid], 602.0, 15.0);
    PlayerTextDrawSetOutline(playerid, TD_DealerNext[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_DealerNext[playerid], 1);

    // 8. Button: [ GANTI KATEGORI ] (Clickable)
    TD_DealerCatBtn[playerid] = CreatePlayerTextDraw(playerid, 438.0, 269.0, "  [ GANTI KATEGORI ]");
    PlayerTextDrawFont(playerid, TD_DealerCatBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_DealerCatBtn[playerid], 0.20, 1.25);
    PlayerTextDrawColor(playerid, TD_DealerCatBtn[playerid], 0xE69958FF);
    PlayerTextDrawUseBox(playerid, TD_DealerCatBtn[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_DealerCatBtn[playerid], 0x33261CFF);
    PlayerTextDrawTextSize(playerid, TD_DealerCatBtn[playerid], 602.0, 15.0);
    PlayerTextDrawSetOutline(playerid, TD_DealerCatBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_DealerCatBtn[playerid], 1);

    // 9. Button: [ GANTI WARNA ] (Clickable)
    TD_DealerColorBtn[playerid] = CreatePlayerTextDraw(playerid, 438.0, 292.0, "    [ PILIH WARNA ]");
    PlayerTextDrawFont(playerid, TD_DealerColorBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_DealerColorBtn[playerid], 0.20, 1.25);
    PlayerTextDrawColor(playerid, TD_DealerColorBtn[playerid], 0xFFD700FF);
    PlayerTextDrawUseBox(playerid, TD_DealerColorBtn[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_DealerColorBtn[playerid], 0x332B1AFF);
    PlayerTextDrawTextSize(playerid, TD_DealerColorBtn[playerid], 602.0, 15.0);
    PlayerTextDrawSetOutline(playerid, TD_DealerColorBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_DealerColorBtn[playerid], 1);

    // 10. Button: [ 🛒 BELI KENDARAAN ] (Clickable)
    TD_DealerBuyBtn[playerid] = CreatePlayerTextDraw(playerid, 438.0, 315.0, "  [ 🛒 BELI KENDARAAN ]");
    PlayerTextDrawFont(playerid, TD_DealerBuyBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_DealerBuyBtn[playerid], 0.20, 1.35);
    PlayerTextDrawColor(playerid, TD_DealerBuyBtn[playerid], 0x2ECC71FF);
    PlayerTextDrawUseBox(playerid, TD_DealerBuyBtn[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_DealerBuyBtn[playerid], 0x1A3828FF);
    PlayerTextDrawTextSize(playerid, TD_DealerBuyBtn[playerid], 602.0, 16.0);
    PlayerTextDrawSetOutline(playerid, TD_DealerBuyBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_DealerBuyBtn[playerid], 1);

    // 11. Button: [ ✖ BATAL / KELUAR ] (Clickable)
    TD_DealerCancelBtn[playerid] = CreatePlayerTextDraw(playerid, 438.0, 340.0, "   [ ✖ BATAL / KELUAR ]");
    PlayerTextDrawFont(playerid, TD_DealerCancelBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_DealerCancelBtn[playerid], 0.20, 1.25);
    PlayerTextDrawColor(playerid, TD_DealerCancelBtn[playerid], 0xE74C3CFF);
    PlayerTextDrawUseBox(playerid, TD_DealerCancelBtn[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_DealerCancelBtn[playerid], 0x3D1F1DFF);
    PlayerTextDrawTextSize(playerid, TD_DealerCancelBtn[playerid], 602.0, 15.0);
    PlayerTextDrawSetOutline(playerid, TD_DealerCancelBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_DealerCancelBtn[playerid], 1);

    // 12. Hint Footer
    TD_DealerHint[playerid] = CreatePlayerTextDraw(playerid, 520.0, 363.0, "Klik menu di atas atau tekan ESC untuk keluar");
    PlayerTextDrawFont(playerid, TD_DealerHint[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_DealerHint[playerid], 0.17, 0.85);
    PlayerTextDrawColor(playerid, TD_DealerHint[playerid], 0xAAAAAAFF);
    PlayerTextDrawAlignment(playerid, TD_DealerHint[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_DealerHint[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_DealerHint[playerid], 0);

    // Tampilkan semua TextDraw ke pemain
    PlayerTextDrawShow(playerid, TD_DealerBox[playerid]);
    PlayerTextDrawShow(playerid, TD_DealerHeader[playerid]);
    PlayerTextDrawShow(playerid, TD_DealerTitle[playerid]);
    PlayerTextDrawShow(playerid, TD_DealerCatBadge[playerid]);
    PlayerTextDrawShow(playerid, TD_DealerInfo[playerid]);
    PlayerTextDrawShow(playerid, TD_DealerPrev[playerid]);
    PlayerTextDrawShow(playerid, TD_DealerNext[playerid]);
    PlayerTextDrawShow(playerid, TD_DealerCatBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_DealerColorBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_DealerBuyBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_DealerCancelBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_DealerHint[playerid]);

    // Aktifkan mode kursor mouse
    SelectTextDraw(playerid, 0x00BCD4FF);

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
        "🏎️ Mobil Sport & Supercar\t(%d Unit)\n" \
        "🚗 Mobil Sedan & Klasik\t(%d Unit)\n" \
        "🚙 SUV, Pick-up & Off-Road\t(%d Unit)\n" \
        "🏍️ Sepeda Motor & Skuter\t(%d Unit)",
        sizeof(gSportVehicles),
        sizeof(gSedanVehicles),
        sizeof(gSuvVehicles),
        sizeof(gBikeVehicles));

    ShowPlayerDialog(playerid, DLG_DEALER_CAT, DIALOG_STYLE_LIST,
        "{00EEFF}PILIH KATEGORI KENDARAAN DEALERSHIP",
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
    SelectTextDraw(playerid, 0x00BCD4FF);
    return 1;
}

// Forward deklarasi fungsi pembelian dari ownership.inc
forward BuyCurrentDealerVehicle(playerid);

stock HandleDealershipClick(playerid, PlayerText:playertextid) {
    if (!gPlayerData[playerid][p_InDealership]) return 0;

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

    if (playertextid == TD_DealerCatBtn[playerid]) {
        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
        ShowDealerCatDialog(playerid);
        return 1;
    }

    if (playertextid == TD_DealerColorBtn[playerid]) {
        gPlayerData[playerid][p_DealerColorIdx]++;
        if (gPlayerData[playerid][p_DealerColorIdx] >= DEALER_COLOR_COUNT) {
            gPlayerData[playerid][p_DealerColorIdx] = 0;
        }
        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
        UpdateDealershipPreview(playerid);
        return 1;
    }

    if (playertextid == TD_DealerBuyBtn[playerid]) {
        BuyCurrentDealerVehicle(playerid);
        return 1;
    }

    if (playertextid == TD_DealerCancelBtn[playerid]) {
        PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
        CloseDealership(playerid);
        return 1;
    }
    return 0;
}
