#if defined _MODULE_BUILDINGS_INC
    #endinput
#endif
#define _MODULE_BUILDINGS_INC

// ============================================================
//  SantaraBaru Roleplay - Buildings, Interiors & Teleports
// ============================================================

stock InitBuildings() {
    //    Marker & 3D Text Label Balai Kota Los Santos           
    // Pintu Masuk (Eksterior - Pershing Square LS)
    CreatePickup(1239, 1, CITYHALL_EXT_X, CITYHALL_EXT_Y, CITYHALL_EXT_Z, 0);
    Create3DTextLabel(
        "{33CCFF}[ BALAI KOTA LOS SANTOS ]\n{FFFFFF}Tekan {FFFF00}[ F / ENTER ]{FFFFFF} untuk masuk",
        0xFFFFFFFF,
        CITYHALL_EXT_X, CITYHALL_EXT_Y, CITYHALL_EXT_Z + 0.5,
        15.0, 0, false
    );

    // Pintu Keluar (Interior - Planning Department LV)
    CreatePickup(1318, 1, CITYHALL_INT_X, CITYHALL_INT_Y, CITYHALL_INT_Z, 0);
    Create3DTextLabel(
        "{33CCFF}[ PINTU KELUAR ]\n{FFFFFF}Tekan {FFFF00}[ F / ENTER ]{FFFFFF} untuk keluar",
        0xFFFFFFFF,
        CITYHALL_INT_X, CITYHALL_INT_Y, CITYHALL_INT_Z + 0.5,
        12.0, 0, false
    );

    //    Loket Catatan Sipil & Pembuatan e-KTP Balai Kota           
    CreatePickup(1239, 1, KTP_DESK_X, KTP_DESK_Y, KTP_DESK_Z, 0);
    Create3DTextLabel(
        "{33CCFF}[ LOKET CATATAN SIPIL & E-KTP ]\n{FFFFFF}Tekan {FFFF00}[ F / ENTER ]{FFFFFF} atau ketik {FFFF00}/ktp{FFFFFF}\n{AAAAAA}Untuk membuat / menerbitkan e-KTP Anda",
        0xFFFFFFFF,
        KTP_DESK_X, KTP_DESK_Y, KTP_DESK_Z + 0.5,
        10.0, 0, false
    );
}

stock HandleBuildingKeys(playerid, KEY:newkeys, KEY:oldkeys) {
    #pragma unused oldkeys
    if (!gPlayerData[playerid][p_LoggedIn] || !gPlayerData[playerid][p_Spawned]) return 1;
    if (IsPlayerInAnyVehicle(playerid)) return 1;

    // Deteksi jika pemain menekan tombol F / ENTER (KEY_SECONDARY_ATTACK)
    if (newkeys & KEY_SECONDARY_ATTACK) {
        // 1. Masuk ke Balai Kota (Dari Luar ke Dalam Interior Planning Dept)
        if (IsPlayerInRangeOfPoint(playerid, 2.5, CITYHALL_EXT_X, CITYHALL_EXT_Y, CITYHALL_EXT_Z) && GetPlayerInterior(playerid) == 0) {
            SetPlayerInterior(playerid, CITYHALL_INT_ID);
            SetPlayerPos(playerid, CITYHALL_INT_X, CITYHALL_INT_Y, CITYHALL_INT_Z);
            SetPlayerFacingAngle(playerid, CITYHALL_INT_A);
            SetCameraBehindPlayer(playerid);
            GameTextForPlayer(playerid, "~w~Selamat Datang di ~g~Balai Kota", 3000, 3);
            PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
            return 1;
        }

        // 2. Keluar dari Balai Kota (Dari Dalam Interior kembali ke Luar)
        if (IsPlayerInRangeOfPoint(playerid, 2.5, CITYHALL_INT_X, CITYHALL_INT_Y, CITYHALL_INT_Z) && GetPlayerInterior(playerid) == CITYHALL_INT_ID) {
            SetPlayerInterior(playerid, 0);
            SetPlayerPos(playerid, CITYHALL_EXT_X, CITYHALL_EXT_Y, CITYHALL_EXT_Z);
            SetPlayerFacingAngle(playerid, CITYHALL_EXT_A);
            SetCameraBehindPlayer(playerid);
            GameTextForPlayer(playerid, "~w~Keluar dari ~g~Balai Kota", 3000, 3);
            PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
            return 1;
        }

        // 3. Interaksi Loket Pembuatan e-KTP di Balai Kota
        if (IsPlayerInRangeOfPoint(playerid, 2.5, KTP_DESK_X, KTP_DESK_Y, KTP_DESK_Z) && GetPlayerInterior(playerid) == KTP_DESK_INT_ID) {
            new emptyParam[1];
            cmd_ktp(playerid, emptyParam);
            return 1;
        }
    }
    return 1;
}
