#if defined _MODULE_DEFINES_INC
    #endinput
#endif
#define _MODULE_DEFINES_INC

// ============================================================
//  SantaraBaru Roleplay — Core Defines & Constants
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

// Vehicle Dialog IDs (Menu Spawner)
#define DLG_VEH_MAIN_MENU       20
#define DLG_VEH_CAT_EMERGENCY   21
#define DLG_VEH_CAT_SPORT       22
#define DLG_VEH_CAT_SEDAN       23
#define DLG_VEH_CAT_SUV         24
#define DLG_VEH_CAT_HEAVY       25
#define DLG_VEH_CAT_BIKES       26
#define DLG_VEH_CAT_AIRCRAFT    27
#define DLG_VEH_CAT_BOATS       28
#define DLG_VEH_CAT_UNIQUE      29

// Custom Models IDs (open.mp Native Artwork)
#define CUSTOM_MODEL_COPCARSF   -1000

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

// ── Lokasi Balai Kota (City Hall Los Santos & Interior Planning Department) ──
#define CITYHALL_EXT_X      1481.1611
#define CITYHALL_EXT_Y      -1771.6991
#define CITYHALL_EXT_Z      18.7958
#define CITYHALL_EXT_A      180.0

#define CITYHALL_INT_ID     3
#define CITYHALL_INT_X      386.5259
#define CITYHALL_INT_Y      173.6381
#define CITYHALL_INT_Z      1008.3828
#define CITYHALL_INT_A      90.0

// ── Lokasi Loket Catatan Sipil & Pembuatan e-KTP (Balai Kota LV Interior) ──
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
