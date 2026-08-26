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
#define DLG_GPS_MENU            40
#define DLG_GPS_GARAGE          41
#define DLG_GPS_INSURANCE       42
#define DLG_ADMIN_TELEPORT      50
#define DLG_ADMIN_TP_INSURANCE  51
#define DLG_ADMIN_TP_GARAGE     52

// Inventory & Item Dialogs
#define DLG_INV_MAIN            60
#define DLG_INV_ACTION          61
#define DLG_INV_GIVE_PLAYER     62
#define DLG_INV_GIVE_QTY        63
#define DLG_INV_DROP_QTY        64
#define DLG_TRUNK_TAKE_QTY      65
#define DLG_TRUNK_STORE_QTY     66
#define DLG_TRUNK_DROP_QTY      67

// ============================================================
//  Item ID Constants (Legal, Makanan, Minuman, Medis, Dokumen)
// ============================================================
// 1. Makanan Utama (1 - 14)
#define ITEM_BURGER             1
#define ITEM_CHEESEBURGER       2
#define ITEM_HOTDOG             3
#define ITEM_PIZZA              4
#define ITEM_SANDWICH           5
#define ITEM_TACO               6
#define ITEM_BURRITO            7
#define ITEM_FRIED_CHICKEN      8
#define ITEM_FRENCH_FRIES       9
#define ITEM_DONUT              10
#define ITEM_INSTANT_NOODLE     11
#define ITEM_FRIED_RICE         12
#define ITEM_AYAM_GORENG        13
#define ITEM_SATE               14

// 2. Snack (15 - 22)
#define ITEM_POTATO_CHIPS       15
#define ITEM_CHOCOLATE          16
#define ITEM_CANDY              17
#define ITEM_BISCUIT            18
#define ITEM_BREAD              19
#define ITEM_POPCORN            20
#define ITEM_PEANUTS            21
#define ITEM_ICE_CREAM          22

// 3. Minuman (23 - 31)
#define ITEM_MINERAL_WATER      23
#define ITEM_SODA               24
#define ITEM_COLA               25
#define ITEM_ORANGE_JUICE       26
#define ITEM_COFFEE             27
#define ITEM_TEA                28
#define ITEM_ENERGY_DRINK       29
#define ITEM_MILK               30
#define ITEM_MILKSHAKE          31

// 4. Medical / Pemulihan HP (32 - 34)
#define ITEM_BANDAGE            32
#define ITEM_MEDKIT             33
#define ITEM_FIRST_AID          34

// 5. Dokumen & Perlengkapan (35 - 36)
#define ITEM_PHONE              35
#define ITEM_KTP                36

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
