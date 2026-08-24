#if defined _MODULE_CMD_VEHICLE_INC
    #endinput
#endif
#define _MODULE_CMD_VEHICLE_INC

// ============================================================
//  SantaraBaru Roleplay — Vehicle Commands
// ============================================================

// ── Perintah Utama: Spawn Kendaraan (ID / Nama) ─────────────
CMD:veh(playerid, params[]) {
    if (!CheckSpawned(playerid)) return 1;

    if (!strlen(params) || params[0] == '\0') {
        ShowVehicleMainMenu(playerid);
        return 1;
    }

    new modelStr[32], color1 = -1, color2 = -1;
    if (sscanf(params, "s[32]I(-1)I(-1)", modelStr, color1, color2)) {
        SendClientMessage(playerid, COL_ORANGE, "  [Gunakan] /veh [ID/Nama Model] [Warna 1] [Warna 2]");
        SendClientMessage(playerid, COL_GREY,   "  Contoh: /veh copcarsf | /veh 597 | /veh infernus | /veh sultan 1 1");
        SendClientMessage(playerid, COL_GREY,   "  Ketik {00EEFF}/vehmenu{AAAAAA} untuk membuka menu katalog mobil lengkap.");
        return 1;
    }

    new modelid = GetVehicleModelByName(modelStr);
    if (modelid < 400 || modelid > 611) {
        SendClientMessage(playerid, COL_RED, "  [!] Kendaraan tidak ditemukan. Masukkan Model ID (400-611) atau nama yang valid.");
        SendClientMessage(playerid, COL_GREY, "  Contoh: {00EEFF}/veh copcarsf {AAAAAA}| {00EEFF}/veh infernus {AAAAAA}| {00EEFF}/veh sultan {AAAAAA}| {00EEFF}/vehmenu");
        return 1;
    }

    new bool:isCustomCop = (modelid == 597 || !strcmp(modelStr, "copcarsf", true) || !strcmp(modelStr, "copsf", true));
    SpawnPlayerVehicle(playerid, modelid, color1, color2, isCustomCop);
    return 1;
}

CMD:v(playerid, params[]) {
    return cmd_veh(playerid, params);
}

CMD:car(playerid, params[]) {
    return cmd_veh(playerid, params);
}

CMD:spawnveh(playerid, params[]) {
    return cmd_veh(playerid, params);
}

CMD:spawncar(playerid, params[]) {
    return cmd_veh(playerid, params);
}

// ── Shortcut Khusus: Mobil Polisi Kustom San Fierro (copcarsf) ──
CMD:copcarsf(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    SpawnPlayerVehicle(playerid, 597, 1, 1, true);
    return 1;
}

CMD:copsf(playerid, params[]) {
    return cmd_copcarsf(playerid, params);
}

CMD:copcar(playerid, params[]) {
    return cmd_copcarsf(playerid, params);
}

CMD:policecar(playerid, params[]) {
    return cmd_copcarsf(playerid, params);
}

// ── Menu Dialog Katalog Semua Kendaraan ─────────────────────
CMD:vehmenu(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    ShowVehicleMainMenu(playerid);
    return 1;
}

CMD:cars(playerid, params[]) {
    return cmd_vehmenu(playerid, params);
}

CMD:mobil(playerid, params[]) {
    return cmd_vehmenu(playerid, params);
}

CMD:vmenu(playerid, params[]) {
    return cmd_vehmenu(playerid, params);
}

// ── Hapus Kendaraan Spawn Pemain ─────────────────────────────
CMD:destroyveh(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    if (DestroyPlayerSpawnedVehicle(playerid)) {
        SendClientMessage(playerid, COL_GREEN, "  ✓ Kendaraan spawn Anda berhasil dihapus dari server.");
    } else {
        SendClientMessage(playerid, COL_RED, "  [!] Anda tidak memiliki kendaraan spawn aktif.");
    }
    return 1;
}

CMD:dv(playerid, params[]) {
    return cmd_destroyveh(playerid, params);
}

CMD:delveh(playerid, params[]) {
    return cmd_destroyveh(playerid, params);
}

// ── Perbaiki Kendaraan ──────────────────────────────────────
CMD:fixveh(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    RepairPlayerVehicle(playerid);
    return 1;
}

CMD:repair(playerid, params[]) {
    return cmd_fixveh(playerid, params);
}

CMD:fix(playerid, params[]) {
    return cmd_fixveh(playerid, params);
}

// ── Balikkan Kendaraan Terbalik ─────────────────────────────
CMD:flip(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    FlipPlayerVehicle(playerid);
    return 1;
}

CMD:flipveh(playerid, params[]) {
    return cmd_flip(playerid, params);
}

// ── Ganti Warna Kendaraan ───────────────────────────────────
CMD:vcolor(playerid, params[]) {
    if (!CheckSpawned(playerid)) return 1;
    if (!IsPlayerInAnyVehicle(playerid)) {
        SendClientMessage(playerid, COL_RED, "  [!] Anda harus berada di dalam kendaraan.");
        return 1;
    }
    new color1, color2;
    if (sscanf(params, "dd", color1, color2)) {
        SendClientMessage(playerid, COL_ORANGE, "  [Gunakan] /vcolor [ID Warna 1] [ID Warna 2] (0-255)");
        return 1;
    }
    new vehid = GetPlayerVehicleID(playerid);
    ChangeVehicleColor(vehid, color1, color2);
    SendClientMessage(playerid, COL_GREEN, "  ✓ Warna kendaraan berhasil diubah!");
    return 1;
}

CMD:vehcolor(playerid, params[]) {
    return cmd_vcolor(playerid, params);
}

// ── Mesin Kendaraan (Engine On/Off) ─────────────────────────
CMD:engine(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    TogglePlayerVehicleEngine(playerid);
    return 1;
}

CMD:mesin(playerid, params[]) {
    return cmd_engine(playerid, params);
}

// ── Lampu Kendaraan (Lights On/Off) ─────────────────────────
CMD:lights(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    TogglePlayerVehicleLights(playerid);
    return 1;
}

CMD:lampu(playerid, params[]) {
    return cmd_lights(playerid, params);
}

// ── Kunci Pintu Kendaraan (Lock/Unlock) ─────────────────────
CMD:lock(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    TogglePlayerVehicleLock(playerid);
    return 1;
}

CMD:kunci(playerid, params[]) {
    return cmd_lock(playerid, params);
}
