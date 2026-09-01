#if defined _MODULE_MINING_INC
    #endinput
#endif
#define _MODULE_MINING_INC

// ============================================================
//  SantaraBaru Roleplay - Mining System (Hunter Quarry LV)
//  20 Node Batu Tambang Hunter Quarry (LV) - Respawn Dinamis 10-20 Detik
// ============================================================

#define MAX_MINING_NODES        20
#define MINING_ROCK_MODEL       3931

enum E_MINING_NODE {
    Float:node_X,
    Float:node_Y,
    Float:node_Z,
    Float:node_A,
    bool:node_Spawned,
    node_ObjectID,
    node_RespawnTimer
};

new gMiningNodes[MAX_MINING_NODES][E_MINING_NODE] = {
    {644.4195, 847.4263, -42.9609, 261.5465, false, INVALID_OBJECT_ID, 0}, // [1]
    {635.2061, 884.3985, -42.9609,  51.4054, false, INVALID_OBJECT_ID, 0}, // [2]
    {622.8604, 879.7741, -42.9609, 195.2218, false, INVALID_OBJECT_ID, 0}, // [3]
    {607.4149, 892.3889, -43.9942, 119.8932, false, INVALID_OBJECT_ID, 0}, // [4]
    {595.2315, 882.6049, -43.9698, 126.2136, false, INVALID_OBJECT_ID, 0}, // [5]
    {593.7333, 847.9405, -42.8453, 154.3083, false, INVALID_OBJECT_ID, 0}, // [6]
    {626.5507, 854.8333, -42.9609,  30.2847, false, INVALID_OBJECT_ID, 0}, // [7]
    {619.2924, 870.1538, -42.9609,  69.5290, false, INVALID_OBJECT_ID, 0}, // [8]
    {608.7841, 868.5647, -40.3152, 112.6833, false, INVALID_OBJECT_ID, 0}, // [9]
    {608.1008, 863.7029, -41.9451, 154.9140, false, INVALID_OBJECT_ID, 0}, // [10]
    {605.1264, 873.2512, -42.6184,  30.4682, false, INVALID_OBJECT_ID, 0}, // [11]
    {619.9466, 873.4855, -42.9609, 231.7903, false, INVALID_OBJECT_ID, 0}, // [12]
    {634.4887, 860.5540, -42.5836, 254.5696, false, INVALID_OBJECT_ID, 0}, // [13]
    {639.4152, 855.8873, -40.1487, 238.7380, false, INVALID_OBJECT_ID, 0}, // [14]
    {642.7677, 859.0764, -41.9683, 336.0137, false, INVALID_OBJECT_ID, 0}, // [15]
    {643.8988, 883.0888, -42.6405,  29.6097, false, INVALID_OBJECT_ID, 0}, // [16]
    {614.0963, 861.0206, -42.9609,   5.9726, false, INVALID_OBJECT_ID, 0}, // [17]
    {596.5886, 868.0502, -43.1221, 194.8273, false, INVALID_OBJECT_ID, 0}, // [18]
    {598.6620, 884.6767, -43.6526,  15.0180, false, INVALID_OBJECT_ID, 0}, // [19]
    {630.7486, 877.9566, -42.9609, 299.7828, false, INVALID_OBJECT_ID, 0}  // [20]
};

new bool:gIsMining[MAX_PLAYERS];
new gMiningTimer[MAX_PLAYERS];

forward RespawnMiningRock(nodeid);
forward OnPlayerFinishMining(playerid, nodeid);

stock InitMiningSystem() {
    // 1. Spawn Awal 20 Objek Batu di Hunter Quarry (Tanpa 3D Text Label)
    for (new i = 0; i < MAX_MINING_NODES; i++) {
        gMiningNodes[i][node_Spawned] = true;
        gMiningNodes[i][node_ObjectID] = CreateObject(
            MINING_ROCK_MODEL,
            gMiningNodes[i][node_X],
            gMiningNodes[i][node_Y],
            gMiningNodes[i][node_Z] - 0.3,
            0.0, 0.0, gMiningNodes[i][node_A]
        );
    }
}

public RespawnMiningRock(nodeid) {
    if (nodeid < 0 || nodeid >= MAX_MINING_NODES) return 0;
    if (!gMiningNodes[nodeid][node_Spawned]) {
        gMiningNodes[nodeid][node_Spawned] = true;
        gMiningNodes[nodeid][node_ObjectID] = CreateObject(
            MINING_ROCK_MODEL,
            gMiningNodes[nodeid][node_X],
            gMiningNodes[nodeid][node_Y],
            gMiningNodes[nodeid][node_Z] - 0.3,
            0.0, 0.0, gMiningNodes[nodeid][node_A]
        );
    }
    return 1;
}

stock TryStartMining(playerid) {
    if (!CheckSpawned(playerid)) return 0;
    if (gIsMining[playerid]) {
        SendClientMessage(playerid, COL_RED, "  [!] Anda sedang melakukan aktivitas lain!");
        return 1;
    }

    new nearNode = -1;
    for (new i = 0; i < MAX_MINING_NODES; i++) {
        if (gMiningNodes[i][node_Spawned] && IsPlayerInRangeOfPoint(playerid, 2.8, gMiningNodes[i][node_X], gMiningNodes[i][node_Y], gMiningNodes[i][node_Z])) {
            nearNode = i;
            break;
        }
    }

    if (nearNode == -1) {
        return 0;
    }

    if (!Inventory_HasItem(playerid, ITEM_PICKAXE)) {
        SendClientMessage(playerid, COL_RED, "  [!] Anda membutuhkan Beliung Tambang (Pickaxe) di inventory untuk menambang batu!");
        return 1;
    }

    gIsMining[playerid] = true;
    ApplyAnimation(playerid, "BASEBALL", "Bat_4", 4.1, 1, 0, 0, 0, 0, 1);
    GameTextForPlayer(playerid, "~y~Sedang Menambang...", 4000, 3);
    SendClientMessage(playerid, COL_YELLOW, "  [*] Sedang menggali dan memecahkan batu tambang...");

    new charname[48], rpMsg[144];
    GetCharName(playerid, charname);
    format(rpMsg, sizeof(rpMsg), "* %s mengayunkan beliung sekuat tenaga memecah batuan tambang.", charname);
    DoProximitySay(playerid, rpMsg, DIST_RP, COL_PURPLE, false);

    gMiningTimer[playerid] = SetTimerEx("OnPlayerFinishMining", 4000, false, "ii", playerid, nearNode);
    return 1;
}

public OnPlayerFinishMining(playerid, nodeid) {
    if (!gIsMining[playerid]) return 1;
    gIsMining[playerid] = false;
    ClearAnimations(playerid, 1);

    // Hancurkan / hilangkan batu di posisi nodeid
    if (nodeid >= 0 && nodeid < MAX_MINING_NODES) {
        if (gMiningNodes[nodeid][node_Spawned]) {
            gMiningNodes[nodeid][node_Spawned] = false;
            if (gMiningNodes[nodeid][node_ObjectID] != INVALID_OBJECT_ID) {
                DestroyObject(gMiningNodes[nodeid][node_ObjectID]);
                gMiningNodes[nodeid][node_ObjectID] = INVALID_OBJECT_ID;
            }

            // Muncul kembali secara acak paling cepat 10 detik s/d paling lama 20 detik (10.000ms - 20.000ms)
            new respawnTimeMs = (10 + random(11)) * 1000;
            gMiningNodes[nodeid][node_RespawnTimer] = SetTimerEx("RespawnMiningRock", respawnTimeMs, false, "i", nodeid);
        }
    }

    new roll = random(100);
    new itemName[48], amount = 0, itemID = 0;

    if (roll < 50) {
        itemID = ITEM_IRON_ORE;
        amount = 2 + random(3);
        format(itemName, sizeof(itemName), "%d bijih Besi (Iron Ore)", amount);
    } else if (roll < 78) {
        itemID = ITEM_SULFUR;
        amount = 1 + random(3);
        format(itemName, sizeof(itemName), "%d bongkahan Belerang (Sulfur)", amount);
    } else {
        itemID = ITEM_COPPER_ORE;
        amount = 1 + random(3);
        format(itemName, sizeof(itemName), "%d bijih Tembaga (Copper Ore)", amount);
    }

    Inventory_AddItem(playerid, itemID, amount);

    new msg[144];
    format(msg, sizeof(msg), "  [TAMBANG] Sukses menambang dan mendapatkan {00EEFF}%s{FFFFFF}!", itemName);
    SendClientMessage(playerid, COL_GREEN, msg);
    GameTextForPlayer(playerid, "~g~Tambang Selesai!", 2500, 3);
    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);

    new charname[48], rpMsg[144];
    GetCharName(playerid, charname);
    format(rpMsg, sizeof(rpMsg), "* %s menyeka keringat setelah memecahkan batu dan mengantongi mineral tambang.", charname);
    DoProximitySay(playerid, rpMsg, DIST_RP, COL_PURPLE, false);
    return 1;
}

// ─── Command: /tambang & /mine ──────────────────────────────
CMD:tambang(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    if (!TryStartMining(playerid)) {
        SendClientMessage(playerid, COL_RED, "  [!] Dekati bongkahan batu tambang di Hunter Quarry dan tekan [ F ] atau /tambang!");
    }
    return 1;
}

CMD:mine(playerid, params[]) {
    return cmd_tambang(playerid, params);
}
