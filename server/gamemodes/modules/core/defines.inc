#if defined _MODULE_DEFINES_INC
    #endinput
#endif
#define _MODULE_DEFINES_INC

// ============================================================
//  SantaraBaru Roleplay - Core Defines & Constants
// ============================================================

#define GAMEMODE_VERSION    "1.3.0"
#define SERVER_NAME         "SantaraBaru Roleplay v" GAMEMODE_VERSION
#define MAX_PLAYER_NAME     24

// Salt untuk password hashing (SHA256)
#define PASSWORD_SALT       "SantaraRP_Salt#2024!"

// Dialog IDs
#define DLG_LOGIN               1
#define DLG_REGISTER            2
#define DLG_CHAR_SELECT         3
#define DLG_CHAR_DASHBOARD      4
#define DLG_FORM_NAME           5
#define DLG_FORM_BIRTHPLACE     6
#define DLG_FORM_BIRTHDATE      7
#define DLG_FORM_GENDER         8
#define DLG_SPAWN_SELECT        9
#define DLG_CHAR_ACTION         10
#define DLG_CHAR_CONFIRM_DELETE 11
#define DLG_CHAR_DELETE_LIST    12
#define DLG_DEALER_CAT          20
#define DLG_VEH_MAIN            30
#define DLG_VEH_ACTION          31
#define DLG_INSURANCE_MAIN      32
#define DLG_INSURANCE_CONFIRM   33
// GPS Dialogs
#define DLG_GPS_MENU            40
#define DLG_GPS_GARAGE          41
#define DLG_GPS_INSURANCE       42
#define DLG_GPS_BURGER_SHOT     43
#define DLG_GPS_247             44
#define DLG_GPS_GAS_STATION     45
#define DLG_ADMIN_TELEPORT      50
#define DLG_ADMIN_TP_INSURANCE  51
#define DLG_ADMIN_TP_GARAGE     52
#define DLG_ADMIN_TP_BURGER_SHOT 53
#define DLG_ADMIN_TP_247        54
#define DLG_ADMIN_TP_GAS_STATION 55

// Inventory & Item Dialogs
#define DLG_INV_MAIN            60
#define DLG_INV_ACTION          61
#define DLG_INV_GIVE_PLAYER     62
#define DLG_INV_GIVE_QTY        63
#define DLG_INV_DROP_QTY        64
#define DLG_TRUNK_TAKE_QTY      65
#define DLG_TRUNK_STORE_QTY     66
#define DLG_TRUNK_DROP_QTY      67

// Restoran & Bisnis Dialogs
#define DLG_BURGER_SHOT         70
#define DLG_BURGER_SHOT_QTY     71
#define DLG_247_STORE           75
#define DLG_247_STORE_QTY       76

// DMV & SIM Dialogs
#define DLG_DMV_MAIN            80
#define DLG_DMV_CONFIRM         81
#define DLG_SIM_SHOW_TARGET     82
#define DLG_DOKUMEN_SHOW_TARGET 82
#define DLG_SHOW_SIM            83

// Smelter & Crafting Dialogs
#define DLG_SMELTER_MAIN        90
#define DLG_CRAFT_MAIN          91
#define DLG_CRAFT_CATEGORY      92
#define DLG_JOBCENTER_MAIN      95

// UI Color Palette untuk Panel SIM TextDraw
#define COLOR_SIM_BG            0x1E1E28F0
#define COLOR_SIM_PURPLE        0x5814EEFF
#define COLOR_SIM_SLATE         0x333333FF
#define COLOR_SIM_RED           0xE74C3CFF
#define COLOR_SIM_EMPTY         0x2A2A38FF

// ============================================================
//  Koordinat Satpas DMV Driving School (Garcia / Doherty SF)
// ============================================================
#define DMV_DESK_X              -2026.4281
#define DMV_DESK_Y              -100.8486
#define DMV_DESK_Z              35.1640
#define DMV_DESK_A              0.0000

#define DMV_SPAWN_X             -2047.0263
#define DMV_SPAWN_Y             -88.3369
#define DMV_SPAWN_Z             35.1640
#define DMV_SPAWN_A             0.0000

// ============================================================
//  Koordinat Gedung & Interior Restoran Burger Shot
// ============================================================
#define BURGER_SHOT_INT_ID      10
#define BURGER_SHOT_INT_X       363.3857
#define BURGER_SHOT_INT_Y       -74.7937
#define BURGER_SHOT_INT_Z       1001.5078
#define BURGER_SHOT_INT_A       315.0000

#define BURGER_SHOT_COUNTER_X   376.5000
#define BURGER_SHOT_COUNTER_Y   -67.5000
#define BURGER_SHOT_COUNTER_Z   1001.5000

// Virtual World terpisah untuk masing-masing cabang restoran (101 - 110)
#define BURGER_SHOT_VW_BASE     101

// ============================================================
//  Koordinat Gedung & Interior Supermarket (Interior ID 17)
// ============================================================
#define TWENTYFOUR_SEVEN_INT_ID   17
#define TWENTYFOUR_SEVEN_INT_X    -25.8845
#define TWENTYFOUR_SEVEN_INT_Y    -185.8680
#define TWENTYFOUR_SEVEN_INT_Z    1003.5469
#define TWENTYFOUR_SEVEN_INT_A    0.0000

#define TWENTYFOUR_SEVEN_CASH1_X  -21.3273
#define TWENTYFOUR_SEVEN_CASH1_Y  -185.1126
#define TWENTYFOUR_SEVEN_CASH1_Z  1003.5468
#define TWENTYFOUR_SEVEN_CASH1_A  175.7660

#define TWENTYFOUR_SEVEN_CASH2_X  -9.3219
#define TWENTYFOUR_SEVEN_CASH2_Y  -178.3290
#define TWENTYFOUR_SEVEN_CASH2_Z  1003.5468
#define TWENTYFOUR_SEVEN_CASH2_A  182.4088

#define TWENTYFOUR_SEVEN_CASH_X   -21.3273
#define TWENTYFOUR_SEVEN_CASH_Y   -185.1126
#define TWENTYFOUR_SEVEN_CASH_Z   1003.5468

// Virtual World terpisah untuk masing-masing cabang (201 - 205)
#define TWENTYFOUR_SEVEN_VW_BASE  201

// ============================================================
//  Koordinat Meja Kerja Rahasia / Gunsmith Workbench
// ============================================================
#define CRAFT_BENCH_X           -1116.1784
#define CRAFT_BENCH_Y           -1637.0214
#define CRAFT_BENCH_Z           76.3671
#define CRAFT_BENCH_A           107.1094

// ============================================================
//  Koordinat Pom Bensin (Gas Stations)
// ============================================================
enum E_GAS_STATION {
    gs_Name[64],
    Float:gs_X,
    Float:gs_Y,
    Float:gs_Z
};

new const gGasStations[][E_GAS_STATION] = {
    // Flint County
    {"Flint Intersection Gas Station", -90.2, -1169.4, 2.4},
    // San Fierro
    {"Juniper Hollow Gas Station, San Fierro", -2408.7, 976.2, 45.2},
    // Las Venturas
    {"Come-A-Lot Gas Station, Las Venturas", 2115.4, 920.1, 10.8},
    {"Julius Thruway North Gas Station, LV", 1596.2, 2199.8, 10.8}
};
#define MAX_GAS_STATIONS (sizeof(gGasStations))

// Titik Dispenser Pom / Tangki Pengisian Bensin
enum E_FUEL_PUMP {
    Float:fp_X,
    Float:fp_Y,
    Float:fp_Z
};

new const gFuelPumps[][E_FUEL_PUMP] = {
    // Idlewood Gas Station (tangki1 - tangki8)
    {1942.8265, -1767.1629, 13.3828},
    {1942.8984, -1771.3872, 13.3828},
    {1942.6756, -1774.1885, 13.3828},
    {1942.9613, -1778.5849, 13.3828},
    {1940.2662, -1778.4846, 13.3828},
    {1940.5788, -1774.2008, 13.3828},
    {1940.3822, -1771.0925, 13.3828},
    {1940.5921, -1767.3498, 13.3828},

    // Flint Intersection (tangki9 - tangki12)
    {-93.2643, -1161.5599, 2.2217},
    {-91.0316, -1162.3957, 2.2491},
    {-86.2047, -1164.5446, 2.2366},
    {-84.2428, -1165.6151, 2.2397},

    // Doherty Gas Station (tangki13 - tangki28)
    {-1678.3383, 402.0085, 7.1796},
    {-1674.2669, 405.7527, 7.1796},
    {-1668.6002, 411.6022, 7.1796},
    {-1664.5936, 415.8706, 7.1796},
    {-1666.4274, 418.1445, 7.1796},
    {-1671.0621, 413.3896, 7.1796},
    {-1676.1293, 408.2176, 7.1796},
    {-1680.5645, 404.1178, 7.1796},
    {-1684.8944, 408.5599, 7.1796},
    {-1680.8145, 412.9151, 7.1796},
    {-1675.6666, 417.8793, 7.1796},
    {-1671.2846, 422.5403, 7.1796},
    {-1673.1501, 424.7570, 7.1796},
    {-1677.7843, 420.0374, 7.1796},
    {-1683.0493, 414.3297, 7.1796},
    {-1686.8847, 410.1979, 7.1796},

    // Come-A-Lot Las Venturas (tangki29 - tangki40)
    {2108.6240, 924.2965, 10.8203},
    {2115.1711, 923.9681, 10.8203},
    {2120.7324, 923.7891, 10.8203},
    {2120.7958, 926.6746, 10.8203},
    {2114.9040, 926.7042, 10.8203},
    {2108.9116, 926.9218, 10.8203},
    {2120.8703, 916.1760, 10.8203},
    {2115.1413, 916.0952, 10.8203},
    {2109.3596, 915.9287, 10.8203},
    {2109.2504, 913.1273, 10.8203},
    {2115.1230, 913.1756, 10.8203},
    {2120.7846, 913.3820, 10.8203},

    // Julius Thruway North Las Venturas (tangki41 - tangki51)
    {1590.0989, 2203.4379, 10.8203},
    {1596.2375, 2203.3417, 10.8203},
    {1602.0463, 2203.2426, 10.8203},
    {1602.0588, 2205.5891, 10.8203},
    {1590.3211, 2205.6677, 10.8203},
    {1590.2838, 2194.9084, 10.8203},
    {1596.3613, 2194.9106, 10.8203},
    {1602.0925, 2195.0097, 10.8203},
    {1601.8291, 2192.4287, 10.8203},
    {1596.1467, 2192.4704, 10.8203},
    {1590.1176, 2192.1242, 10.8203},

    // Emerald Isle Las Venturas (tangki52 - tangki63)
    {2195.3395, 2470.1889, 10.8203},
    {2195.3718, 2474.8845, 10.8203},
    {2195.5593, 2480.5407, 10.8203},
    {2198.1713, 2480.3820, 10.8203},
    {2198.3735, 2474.5808, 10.8203},
    {2198.4990, 2470.2219, 10.8203},
    {2206.4426, 2470.1982, 10.8203},
    {2206.1567, 2474.9521, 10.8203},
    {2206.1765, 2480.4147, 10.8203},
    {2209.1484, 2480.3789, 10.8203},
    {2209.2490, 2474.7807, 10.8203},
    {2209.4062, 2470.3454, 10.8203},

    // Juniper Hollow San Fierro
    {-2408.7, 976.2, 45.2}
};
#define MAX_FUEL_PUMPS (sizeof(gFuelPumps))

stock bool:IsPlayerNearFuelPump(playerid) {
    for (new p = 0; p < MAX_FUEL_PUMPS; p++) {
        if (IsPlayerInRangeOfPoint(playerid, 3.5, gFuelPumps[p][fp_X], gFuelPumps[p][fp_Y], gFuelPumps[p][fp_Z])) {
            return true;
        }
    }
    for (new g = 0; g < MAX_GAS_STATIONS; g++) {
        if (IsPlayerInRangeOfPoint(playerid, 10.0, gGasStations[g][gs_X], gGasStations[g][gs_Y], gGasStations[g][gs_Z])) {
            return true;
        }
    }
    return false;
}

// ============================================================
//  Koordinat 4 Meja Peleburan / Smelter (Ocean Docks LS)
// ============================================================
#define SMELTER_TABLE1_X        2475.1838
#define SMELTER_TABLE1_Y        -2080.1926
#define SMELTER_TABLE1_Z        13.5468
#define SMELTER_TABLE1_A        352.5955

#define SMELTER_TABLE2_X        2481.9882
#define SMELTER_TABLE2_Y        -2080.0844
#define SMELTER_TABLE2_Z        13.5468
#define SMELTER_TABLE2_A        355.2447

#define SMELTER_TABLE3_X        2489.0581
#define SMELTER_TABLE3_Y        -2080.0927
#define SMELTER_TABLE3_Z        13.5468
#define SMELTER_TABLE3_A        2.9976

#define SMELTER_TABLE4_X        2496.2946
#define SMELTER_TABLE4_Y        -2079.8083
#define SMELTER_TABLE4_Z        13.5468
#define SMELTER_TABLE4_A        17.7647

// ============================================================
//  Item ID Constants (Legal, Makanan, Minuman, Medis, Dokumen, Crafting)
// ============================================================
// 1. Makanan (1 - 3)
#define ITEM_BURGER             1
#define ITEM_HOTDOG             2
#define ITEM_PIZZA              3

// 2. Minuman (4 - 6)
#define ITEM_MINERAL_WATER      4
#define ITEM_COLA               5
#define ITEM_MILKSHAKE          6

// 3. Medical / Pemulihan HP (7 - 9)
#define ITEM_BANDAGE            7
#define ITEM_MEDKIT             8
#define ITEM_FIRST_AID          9

// 4. Dokumen & Perlengkapan (10 - 14)
#define ITEM_PHONE              10
#define ITEM_KTP                11
#define ITEM_SIM_A              12
#define ITEM_SIM_B              13
#define ITEM_SIM_C              14

// 5. Bahan Mentah Tambang & Alam (15 - 19)
#define ITEM_IRON_ORE           15
#define ITEM_SCRAP_METAL        16
#define ITEM_SULFUR             17
#define ITEM_CHARCOAL           18
#define ITEM_COPPER_ORE         19

// 6. Bahan Olahan Peleburan (20 - 22)
#define ITEM_STEEL_BAR          20
#define ITEM_BRASS_PLATE        21
#define ITEM_GUNPOWDER          22

// 7. Komponen Senjata (23 - 25)
#define ITEM_BARREL_SLIDE       23
#define ITEM_TRIGGER_MECH       24
#define ITEM_EMPTY_MAG          25

// 8. Amunisi & Rompi (26 - 30)
#define ITEM_AMMO_9MM           26
#define ITEM_AMMO_DEAGLE        27
#define ITEM_AMMO_SHOTGUN       28
#define ITEM_AMMO_RIFLE         29
#define ITEM_KEVLAR_VEST        30

// 9. Alat Kerja / Tools (31 - 32)
#define ITEM_PICKAXE            31
#define ITEM_TOOLBOX            32

// 10. Senjata Api Jadi / Crafted Weapons (33 - 36)
#define ITEM_WEAPON_COLT45      33
#define ITEM_WEAPON_DEAGLE      34
#define ITEM_WEAPON_SHOTGUN     35
#define ITEM_WEAPON_AK47        36

#define TOTAL_ITEM_COUNT        36

// Status Kendaraan Pribadi
#define VEH_STATUS_OUTSIDE      0   // Terparkir di Luar (Dunia Game)
#define VEH_STATUS_GARAGE       1   // Disimpan di Garasi Publik
#define VEH_STATUS_INSURANCE    2   // Hancur / Dalam Asuransi

//    Kantor Asuransi Los Santos (Commerce)                    
#define INSURANCE_X             1766.4250
#define INSURANCE_Y             -1700.5420
#define INSURANCE_Z             13.5469


//    Coutt and Schutz Auto Showroom (Los Santos)
#define DEALER_RODEO_X          2131.7839
#define DEALER_RODEO_Y          -1148.1304
#define DEALER_RODEO_Z          24.4051

#define DEALER_PREVIEW_X        2126.1943
#define DEALER_PREVIEW_Y        -1129.0712
#define DEALER_PREVIEW_Z        25.5196
#define DEALER_PREVIEW_A        340.9118

#define DEALER_CAM_X            2129.5000
#define DEALER_CAM_Y            -1136.0000
#define DEALER_CAM_Z            27.0000
#define DEALER_LOOK_X           2126.1943
#define DEALER_LOOK_Y           -1129.0712
#define DEALER_LOOK_Z           25.8000

#define DEALER_DELIVER_X        2126.1943
#define DEALER_DELIVER_Y        -1129.0712
#define DEALER_DELIVER_Z        25.5196
#define DEALER_DELIVER_A        340.9118

#define DEALER_CAT_SPORT        0
#define DEALER_CAT_SEDAN        1
#define DEALER_CAT_SUV          2
#define DEALER_CAT_BIKE         3
#define DEALER_CAT_COUNT        4

// Batas maksimal karakter per akun
#define MAX_CHARS_PER_ACCOUNT 3

// Proximity radius (unit = ~1 meter di GTA SA)
#define DIST_VOICE          20.0    // Voice chat & normal speak
#define DIST_SHOUT          40.0    // /sh teriak
#define DIST_WHISPER        5.0     // /w bisik
#define DIST_RP             20.0    // /me /do

// Brute-force protection
#define MAX_LOGIN_TRIES     3

// Pilihan Lokasi Spawn Publik Default (San Fierro)
#define SPAWN_TRAIN_X       -1982.0
#define SPAWN_TRAIN_Y       137.0
#define SPAWN_TRAIN_Z       27.68
#define SPAWN_TRAIN_A       89.0

#define SPAWN_AIRPORT_X     -1423.5
#define SPAWN_AIRPORT_Y     -287.2
#define SPAWN_AIRPORT_Z     14.14
#define SPAWN_AIRPORT_A     135.0

#define SPAWN_CITYHALL_X    -2763.5
#define SPAWN_CITYHALL_Y    375.5
#define SPAWN_CITYHALL_Z    6.33
#define SPAWN_CITYHALL_A    90.0

#define SPAWN_BUS_X         1958.33
#define SPAWN_BUS_Y         1343.12
#define SPAWN_BUS_Z         15.36
#define SPAWN_BUS_A         270.0

//    Lokasi Balai Kota (City Hall Los Santos & Interior Planning Department)   
#define CITYHALL_EXT_X      1481.1611
#define CITYHALL_EXT_Y      -1771.6991
#define CITYHALL_EXT_Z      18.7958
#define CITYHALL_EXT_A      180.0

#define CITYHALL_INT_ID     3
#define CITYHALL_INT_X      386.5259
#define CITYHALL_INT_Y      173.6381
#define CITYHALL_INT_Z      1008.3828
#define CITYHALL_INT_A      90.0

//    Lokasi Loket Catatan Sipil & Pembuatan e-KTP (Balai Kota LV Interior)   
#define KTP_DESK_INT_ID     3
#define KTP_DESK_VW_ID      0
#define KTP_DESK_X          361.8269
#define KTP_DESK_Y          173.5707
#define KTP_DESK_Z          1008.3828
#define KTP_DESK_A          81.5142

//    Lokasi Pusat Tenaga Kerja / Job Center (Balai Kota Interior)
#define JOBCENTER_INT_ID    3
#define JOBCENTER_VW_ID     0
#define JOBCENTER_X         361.1137
#define JOBCENTER_Y         171.3065
#define JOBCENTER_Z         1008.3828
#define JOBCENTER_A         60.2671

// Warna chat
#define COL_WHITE           0xFFFFFFFF
#define COL_YELLOW          0xFFFF00FF
#define COL_ORANGE          0xFF8C00FF
#define COL_GREEN           0x00CC66FF
#define COL_RED             0xFF4040FF
#define COL_PURPLE          0xC2A2DAFF
#define COL_CYAN            0x00EEFFFF
#define COL_GREY            0xAAAAAAFF
#define COL_PINK            0xFF69B4FF
#define COL_TEAL            0x00BCD4FF
