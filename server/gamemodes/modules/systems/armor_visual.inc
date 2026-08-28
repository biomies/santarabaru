#if defined _MODULE_ARMOR_VISUAL_INC
    #endinput
#endif
#define _MODULE_ARMOR_VISUAL_INC

// ============================================================
//  SantaraBaru Roleplay - 3D Kevlar Vest Visual Attachment
//  Menempelkan model rompi 3D (Object 19142) ke tubuh karakter
// ============================================================

#define ATTACH_SLOT_ARMOR        0
#define ATTACH_SLOT_PISTOL_R     1
#define ATTACH_SLOT_BACK_WEAPON  2

#define MODEL_KEVLAR_VEST        19142
#define MODEL_WEAPON_COLT45      346
#define MODEL_WEAPON_DEAGLE      348
#define MODEL_WEAPON_SHOTGUN     349
#define MODEL_WEAPON_AK47        355

stock UpdatePlayerArmorVisual(playerid) {
    if (!IsPlayerConnected(playerid)) return 0;
    if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_SLOT_ARMOR)) {
        RemovePlayerAttachedObject(playerid, ATTACH_SLOT_ARMOR);
    }
    return 1;
}

stock RemovePlayerArmorVisual(playerid) {
    if (!IsPlayerConnected(playerid)) return 0;
    if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_SLOT_ARMOR)) {
        RemovePlayerAttachedObject(playerid, ATTACH_SLOT_ARMOR);
    }
    return 1;
}

stock UpdatePlayerWeaponHolsterVisual(playerid) {
    if (!IsPlayerConnected(playerid) || !gPlayerData[playerid][p_Spawned]) return 0;

    new currentWeapon = GetPlayerWeapon(playerid);
    new bool:hasDeagle = bool:Inventory_HasItem(playerid, ITEM_WEAPON_DEAGLE);
    new bool:hasColt = bool:Inventory_HasItem(playerid, ITEM_WEAPON_COLT45);
    new bool:hasShotgun = bool:Inventory_HasItem(playerid, ITEM_WEAPON_SHOTGUN);
    new bool:hasAK = bool:Inventory_HasItem(playerid, ITEM_WEAPON_AK47);

    // 1. PISTOL DI PINGGANG KANAN (Slot 1, Bone 8 - Right Thigh / Hip Holster)
    if (hasDeagle) {
        if (currentWeapon == 24) { // Sedang digenggam di tangan kanan
            if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_SLOT_PISTOL_R)) {
                RemovePlayerAttachedObject(playerid, ATTACH_SLOT_PISTOL_R);
            }
        } else { // Tidak digenggam -> Pasang sarung Deagle di pinggang kanan
            SetPlayerAttachedObject(playerid, ATTACH_SLOT_PISTOL_R, MODEL_WEAPON_DEAGLE, 8, 0.08, 0.04, 0.10, -100.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0, 0);
        }
    } else if (hasColt) {
        if (currentWeapon == 22) { // Sedang digenggam di tangan kanan
            if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_SLOT_PISTOL_R)) {
                RemovePlayerAttachedObject(playerid, ATTACH_SLOT_PISTOL_R);
            }
        } else { // Tidak digenggam -> Pasang sarung Colt 45 di pinggang kanan
            SetPlayerAttachedObject(playerid, ATTACH_SLOT_PISTOL_R, MODEL_WEAPON_COLT45, 8, 0.08, 0.04, 0.10, -100.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0, 0);
        }
    } else {
        if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_SLOT_PISTOL_R)) {
            RemovePlayerAttachedObject(playerid, ATTACH_SLOT_PISTOL_R);
        }
    }

    // 2. SENJATA LARAS PANJANG DI PUNGGUNG (Slot 2, Bone 1 - Spine / Back)
    if (hasAK) {
        if (currentWeapon == 30) { // Sedang digenggam di tangan
            if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_SLOT_BACK_WEAPON)) {
                RemovePlayerAttachedObject(playerid, ATTACH_SLOT_BACK_WEAPON);
            }
        } else { // Gendong AK-47 di punggung (posisi pas di punggung tengah)
            SetPlayerAttachedObject(playerid, ATTACH_SLOT_BACK_WEAPON, MODEL_WEAPON_AK47, 1, -0.08, -0.15, 0.0, 0.0, 45.0, 10.0, 1.0, 1.0, 1.0, 0, 0);
        }
    } else if (hasShotgun) {
        if (currentWeapon == 25) { // Sedang digenggam di tangan
            if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_SLOT_BACK_WEAPON)) {
                RemovePlayerAttachedObject(playerid, ATTACH_SLOT_BACK_WEAPON);
            }
        } else { // Gendong Shotgun di punggung (posisi pas di punggung tengah)
            SetPlayerAttachedObject(playerid, ATTACH_SLOT_BACK_WEAPON, MODEL_WEAPON_SHOTGUN, 1, -0.08, -0.15, 0.0, 0.0, 45.0, 10.0, 1.0, 1.0, 1.0, 0, 0);
        }
    } else {
        if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_SLOT_BACK_WEAPON)) {
            RemovePlayerAttachedObject(playerid, ATTACH_SLOT_BACK_WEAPON);
        }
    }
    return 1;
}

stock RemovePlayerAllVisualAttachments(playerid) {
    if (!IsPlayerConnected(playerid)) return 0;
    if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_SLOT_ARMOR)) RemovePlayerAttachedObject(playerid, ATTACH_SLOT_ARMOR);
    if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_SLOT_PISTOL_R)) RemovePlayerAttachedObject(playerid, ATTACH_SLOT_PISTOL_R);
    if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_SLOT_BACK_WEAPON)) RemovePlayerAttachedObject(playerid, ATTACH_SLOT_BACK_WEAPON);
    return 1;
}
