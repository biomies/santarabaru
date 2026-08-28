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
#define DLG_ADMIN_TELEPORT      50
#define DLG_ADMIN_TP_INSURANCE  51
#define DLG_ADMIN_TP_GARAGE     52
#define DLG_ADMIN_TP_BURGER_SHOT 53
#define DLG_ADMIN_TP_247        54

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
