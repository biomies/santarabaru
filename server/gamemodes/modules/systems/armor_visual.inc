#if defined _MODULE_ARMOR_VISUAL_INC
    #endinput
#endif
#define _MODULE_ARMOR_VISUAL_INC

// ============================================================
//  SantaraBaru Roleplay - 3D Kevlar Vest Visual Attachment
//  Menempelkan model rompi 3D (Object 19142) ke tubuh karakter
// ============================================================

#define ATTACH_SLOT_ARMOR       0
#define MODEL_KEVLAR_VEST       19142

stock UpdatePlayerArmorVisual(playerid) {
    if (!IsPlayerConnected(playerid) || !gPlayerData[playerid][p_Spawned]) return 0;

    new Float:armour;
    GetPlayerArmour(playerid, armour);

    if (armour > 0.0) {
        if (!IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_SLOT_ARMOR)) {
            // Model 19142 pada Bone 1 (Spine/Dada)
            SetPlayerAttachedObject(playerid, ATTACH_SLOT_ARMOR, MODEL_KEVLAR_VEST, 1, 0.08, 0.04, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0, 0);
        }
    } else {
        if (IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_SLOT_ARMOR)) {
            RemovePlayerAttachedObject(playerid, ATTACH_SLOT_ARMOR);
        }
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
