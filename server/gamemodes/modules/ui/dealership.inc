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

//    1. Mobil Sport, Tuners & Supercar (24 Kendaraan)         
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

//    2. Mobil Sedan, Klasik & Lowrider (46 Kendaraan)         
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

//    3. SUV, Pick-up & Off-Road (23 Kendaraan)                
new const gSuvVehicles[][E_DEALER_VEHICLE] = {
    {579, "Huntley",        "Luxury Premium SUV",   350000000, 180, 4},
    {400, "Landstalker",    "SUV Keluarga Tangguh", 180000000, 170, 4},
    {489, "Rancher",        "SUV Off-Road 4x4",     140000000, 160, 2},
    {505, "Rancher Lure",   "Special Off-Road 4x4", 160000000, 165, 2},
    {500, "Mesa",           "Open-Top Jeep 4x4",    125000000, 155, 2},
    {422, "Bobcat",         "Pick-up Klasik",        65000000, 155, 2},
    {478, "Walton",         "Vintage Farm Pick-up",  45000000, 140, 2},
    {543, "Sadler",         "Pekerja Keras Tangguh", 48000000, 145, 2},
    {554, "Yosemite",       "Heavy-Duty Pick-up",   110000000, 165, 2},
    {495, "Sandking",       "Dakar Rally Raid 4x4", 390000000, 185, 2},
    {568, "Bandito",        "Desert Buggy Rail",    135000000, 170, 1},
    {424, "BF Injection",   "Beach Dune Buggy",      90000000, 160, 2},
    {571, "Kart",           "Mini Gokart Balap",     35000000, 120, 1},
    {572, "Mower",          "Traktor Rumput Lucu",   18000000,  80, 1},
    {483, "Camper",         "Hippie Camper Van",    115000000, 140, 3},
    {508, "Journey",        "Motorhome Keluarga",   160000000, 130, 2},
    {482, "Burrito",        "Van Kargo Modern",      95000000, 165, 4},
    {413, "Pony",           "Van Pekerja Serbaguna", 70000000, 150, 4},
    {440, "Rumpo",          "Van Komersil Luas",     80000000, 155, 4},
    {459, "Berkleys RC Van","Van Ekspedisi Kurir",   85000000, 155, 4},
    {499, "Benson",         "Truk Box Logistik",    130000000, 135, 2},
    {609, "Boxville",       "Truk Box Paket",       120000000, 130, 2},
    {414, "Mule",           "Truk Distribusi Usaha",105000000, 125, 2}
};

//    4. Sepeda Motor, Skuter & Sepeda (12 Kendaraan)          
new const gBikeVehicles[][E_DEALER_VEHICLE] = {
    {522, "NRG-500",        "Superbike Balap 500cc",380000000, 220, 2},
    {521, "FCR-900",        "Naked Sport 900cc",    195000000, 195, 2},
    {461, "PCJ-600",        "Sport Street 600cc",   130000000, 185, 2},
    {463, "Freeway",        "Cruiser Touring V-Twin",110000000, 175, 2},
    {586, "Wayfarer",       "Touring Klasik Amerika", 95000000, 170, 2},
    {468, "Sanchez",        "Dirt Trail Enduro",     75000000, 165, 2},
    {471, "Quad",           "All-Terrain Quad 4-Roda",55000000, 140, 2},
    {462, "Faggio",         "Skuter Matic Irit",     18000000, 110, 2},
    {448, "Pizzaboy",       "Skuter Delivery Cepat", 22000000, 115, 1},
    {510, "Mountain Bike",  "Sepeda Gunung Suspensi", 8500000,  65, 1},
    {481, "BMX",            "Sepeda Freestyle BMX",   6500000,  60, 1},
    {509, "Bike",           "Sepeda Santai Kota",     4500000,  50, 1}
};

//    5. Pilihan Warna Cat Showroom (20 Warna Premium)        
new const gDealerColors[] = {
    1,   // Solid Pure White
    0,   // Midnight Jet Black
    3,   // Torchfire Crimson Red
    6,   // Racing Sunburst Yellow
    79,  // Electric Sapphire Blue
    86,  // Emerald British Racing Green
    64,  // Sunset Tangerine Orange
    148, // Velvet Royal Purple
    25,  // Silver Chrome Metallic
    134, // Liquid Gunmetal Grey
    151, // Arctic Ice Aqua Blue
    139, // Rose Gold Blush Pink
    130, // Platinum Titanium Silver
    75,  // Deep Indigo Navy Blue
    141, // Midnight Bordeaux Maroon
    144, // Forest Camo Dark Olive
    138, // Warm Champagne Gold
    129, // Slate Steel Charcoal
    158, // Hot Neon Fuchsia Pink
    135  // Mocha Bronze Metallic
};
#define DEALER_COLOR_COUNT (sizeof(gDealerColors))

new const gDealerColorNames[][24] = {
    "Pure White", "Jet Black", "Crimson Red", "Sunburst Yellow",
    "Sapphire Blue", "Racing Green", "Tangerine Orange", "Royal Purple",
    "Silver Chrome", "Gunmetal Grey", "Arctic Aqua", "Rose Gold",
    "Platinum Silver", "Navy Blue", "Bordeaux Maroon", "Dark Olive",
    "Champagne Gold", "Steel Charcoal", "Neon Fuchsia", "Mocha Bronze"
};

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
        case DEALER_CAT_SPORT: return sizeof(gSportVehicles);
        case DEALER_CAT_SEDAN: return sizeof(gSedanVehicles);
        case DEALER_CAT_SUV:   return sizeof(gSuvVehicles);
        case DEALER_CAT_BIKE:  return sizeof(gBikeVehicles);
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
            if (idx < 0 || idx >= sizeof(gSportVehicles)) idx = 0;
            modelid  = gSportVehicles[idx][d_ModelID];
            format(name, 28, "%s", gSportVehicles[idx][d_Name]);
            format(type, 28, "%s", gSportVehicles[idx][d_Type]);
            price    = gSportVehicles[idx][d_Price];
            topspeed = gSportVehicles[idx][d_TopSpeed];
            seats    = gSportVehicles[idx][d_Seats];
        }
        case DEALER_CAT_SEDAN: {
            if (idx < 0 || idx >= sizeof(gSedanVehicles)) idx = 0;
            modelid  = gSedanVehicles[idx][d_ModelID];
            format(name, 28, "%s", gSedanVehicles[idx][d_Name]);
            format(type, 28, "%s", gSedanVehicles[idx][d_Type]);
            price    = gSedanVehicles[idx][d_Price];
            topspeed = gSedanVehicles[idx][d_TopSpeed];
            seats    = gSedanVehicles[idx][d_Seats];
        }
        case DEALER_CAT_SUV: {
            if (idx < 0 || idx >= sizeof(gSuvVehicles)) idx = 0;
            modelid  = gSuvVehicles[idx][d_ModelID];
            format(name, 28, "%s", gSuvVehicles[idx][d_Name]);
            format(type, 28, "%s", gSuvVehicles[idx][d_Type]);
            price    = gSuvVehicles[idx][d_Price];
            topspeed = gSuvVehicles[idx][d_TopSpeed];
            seats    = gSuvVehicles[idx][d_Seats];
        }
        case DEALER_CAT_BIKE: {
            if (idx < 0 || idx >= sizeof(gBikeVehicles)) idx = 0;
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
        sizeof(gSportVehicles),
        sizeof(gSedanVehicles),
        sizeof(gSuvVehicles),
        sizeof(gBikeVehicles));

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
