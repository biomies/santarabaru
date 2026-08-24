#if defined _MODULE_VEHICLE_INC
    #endinput
#endif
#define _MODULE_VEHICLE_INC

// ============================================================
//  SantaraBaru Roleplay — Vehicle System & Spawner Engine
// ============================================================

// Database Nama Semua Kendaraan GTA San Andreas (Model ID 400 - 611)
stock const gVehicleNames[][] = {
    "Landstalker", "Bravura", "Buffalo", "Linerunner", "Perennial", "Sentinel", "Dumper", "Firetruck",
    "Trashmaster", "Stretch", "Manana", "Infernus", "Voodoo", "Pony", "Mule", "Cheetah", "Ambulance",
    "Leviathan", "Moonbeam", "Esperanto", "Taxi", "Washington", "Bobcat", "Mr Whoopee", "BF Injection",
    "Hunter", "Premier", "Enforcer", "Securicar", "Banshee", "Predator", "Bus", "Rhino", "Barracks",
    "Hotknife", "Trailer 1", "Previon", "Coach", "Cabbie", "Stallion", "Rumpo", "RC Bandit", "Romero",
    "Packer", "Monster", "Admiral", "Squalo", "Seasparrow", "Pizzaboy", "Tram", "Trailer 2", "Turismo",
    "Speeder", "Reefer", "Tropic", "Flatbed", "Yankee", "Caddy", "Solair", "Berkley's RC Van", "Skimmer",
    "PCJ-600", "Faggio", "Freeway", "RC Baron", "RC Raider", "Glendale", "Oceanic", "Sanchez", "Sparrow",
    "Patriot", "Quad", "Coastguard", "Dinghy", "Hermes", "Sabre", "Rustler", "ZR-350", "Walton", "Regina",
    "Comet", "BMX", "Burrito", "Camper", "Marquis", "Baggage", "Dozer", "Maverick", "News Chopper", "Rancher",
    "FBI Rancher", "Virgo", "Greenwood", "Jetmax", "Hotring Racer", "Sandking", "Blista Compact", "Police Maverick",
    "Boxville", "Benson", "Mesa", "RC Goblin", "Hotring Racer A", "Hotring Racer B", "Bloodring Banger", "Rancher Lure",
    "Super GT", "Elegant", "Journey", "Bike", "Mountain Bike", "Beagle", "Cropduster", "Stuntplane", "Tanker",
    "Roadtrain", "Nebula", "Majestic", "Buccaneer", "FCR-900", "NRG-500", "HPV1000", "Cement Truck", "Towtruck",
    "Fortune", "Cadrona", "FBI Truck", "Willard", "Forklift", "Tractor", "Combine Harvester", "Feltzer",
    "Remington", "Slamvan", "Blade", "Freight", "Streak", "Vortex", "Vincent", "Bullet", "Clover", "Sadler",
    "Firetruck LA", "Hustler", "Intruder", "Primo", "Cargobob", "Tampa", "Sunrise", "Merit", "Utility Van",
    "Nevada", "Yosemite", "Windsor", "Monster A", "Monster B", "Uranus", "Jester", "Sultan", "Stratum",
    "Elegy", "Raindance", "RC Tiger", "Flash", "Tahoma", "Savanna", "Bandito", "Freight Flat", "Streak Carriage",
    "Kart", "Mower", "Dune", "Sweeper", "Broadway", "Tornado", "AT-400", "DFT-30", "Huntley", "Stafford",
    "BF-400", "Newsvan", "Tug", "Trailer 3", "Emperor", "Wayfarer", "Euros", "Hotdog", "Club", "Freight Box",
    "Trailer 4", "Andromada", "Dodo", "RC Cam", "Launch", "Police Car (LSPD)", "Police Car (SFPD)", "Police Car (LVPD)",
    "Police Ranger", "Picador", "S.W.A.T.", "Alpha", "Phoenix", "Glendale Damaged", "Sadler Damaged", "Luggage Trailer A",
    "Luggage Trailer B", "Stairs Trailer", "Boxville Mission", "Farm Trailer", "Utility Trailer"
};

// ── Mengambil Nama Kendaraan berdasarkan Model ID ───────────
stock GetVehicleModelName(modelid, name[], maxlen = sizeof(name)) {
    if (modelid >= 400 && modelid <= 611) {
        new idx = modelid - 400;
        if (idx >= 0 && idx < sizeof(gVehicleNames)) {
            format(name, maxlen, "%s", gVehicleNames[idx]);
            return;
        }
    }
    format(name, maxlen, "Unknown Vehicle");
}

// ── Smart Search: Mencari Model ID berdasarkan Kata Kunci ───
stock GetVehicleModelByName(const search[]) {
    if (!strlen(search)) return -1;

    // Cek jika input berupa angka ID langsung
    if (search[0] >= '0' && search[0] <= '9') {
        new id = strval(search);
        if (id >= 400 && id <= 611) return id;
    }

    new lowerSearch[32];
    for (new i = 0; search[i] != '\0' && i < 31; i++) {
        lowerSearch[i] = tolower(search[i]);
    }

    // Alias Populer Khusus & Shortcut
    if (!strcmp(lowerSearch, "copcarsf") || !strcmp(lowerSearch, "copsf") || !strcmp(lowerSearch, "policesf") || !strcmp(lowerSearch, "sfpd")) return 597;
    if (!strcmp(lowerSearch, "copcarls") || !strcmp(lowerSearch, "copls") || !strcmp(lowerSearch, "policels") || !strcmp(lowerSearch, "lspd") || !strcmp(lowerSearch, "police")) return 596;
    if (!strcmp(lowerSearch, "copcarlv") || !strcmp(lowerSearch, "coplv") || !strcmp(lowerSearch, "policelv") || !strcmp(lowerSearch, "lvpd")) return 598;
    if (!strcmp(lowerSearch, "policeranger") || !strcmp(lowerSearch, "ranger")) return 599;
    if (!strcmp(lowerSearch, "nrg") || !strcmp(lowerSearch, "nrg500")) return 522;
    if (!strcmp(lowerSearch, "fcr") || !strcmp(lowerSearch, "fcr900")) return 521;
    if (!strcmp(lowerSearch, "pcj") || !strcmp(lowerSearch, "pcj600")) return 461;
    if (!strcmp(lowerSearch, "bf400") || !strcmp(lowerSearch, "bf")) return 581;
    if (!strcmp(lowerSearch, "sultan")) return 560;
    if (!strcmp(lowerSearch, "elegy")) return 562;
    if (!strcmp(lowerSearch, "infernus")) return 411;
    if (!strcmp(lowerSearch, "turismo")) return 451;
    if (!strcmp(lowerSearch, "bullet")) return 541;
    if (!strcmp(lowerSearch, "cheetah")) return 415;
    if (!strcmp(lowerSearch, "banshee")) return 429;
    if (!strcmp(lowerSearch, "jester")) return 559;
    if (!strcmp(lowerSearch, "flash")) return 565;
    if (!strcmp(lowerSearch, "zr350") || !strcmp(lowerSearch, "zr")) return 477;
    if (!strcmp(lowerSearch, "faggio")) return 462;
    if (!strcmp(lowerSearch, "bmx")) return 510;
    if (!strcmp(lowerSearch, "hydra")) return 520;
    if (!strcmp(lowerSearch, "hunter")) return 425;
    if (!strcmp(lowerSearch, "maverick")) return 487;
    if (!strcmp(lowerSearch, "ambulance") || !strcmp(lowerSearch, "ambulan")) return 416;
    if (!strcmp(lowerSearch, "firetruck") || !strcmp(lowerSearch, "damkar")) return 407;
    if (!strcmp(lowerSearch, "swat")) return 601;
    if (!strcmp(lowerSearch, "enforcer")) return 427;
    if (!strcmp(lowerSearch, "patriot")) return 470;
    if (!strcmp(lowerSearch, "sanchez")) return 468;
    if (!strcmp(lowerSearch, "kart")) return 571;

    // Substring search di database kendaraan
    for (new i = 0; i < sizeof(gVehicleNames); i++) {
        new lowerName[32];
        for (new j = 0; gVehicleNames[i][j] != '\0' && j < 31; j++) {
            lowerName[j] = tolower(gVehicleNames[i][j]);
        }
        if (strfind(lowerName, lowerSearch, true) != -1) {
            return (400 + i);
        }
    }
    return -1;
}

// ── Menghapus Kendaraan Spawn Pemain ─────────────────────────
stock DestroyPlayerSpawnedVehicle(playerid) {
    if (gPlayerSpawnedVehObj[playerid] != INVALID_OBJECT_ID) {
        DestroyObject(gPlayerSpawnedVehObj[playerid]);
        gPlayerSpawnedVehObj[playerid] = INVALID_OBJECT_ID;
    }
    if (gPlayerSpawnedVeh[playerid] != INVALID_VEHICLE_ID) {
        DestroyVehicle(gPlayerSpawnedVeh[playerid]);
        gPlayerSpawnedVeh[playerid] = INVALID_VEHICLE_ID;
        return 1;
    }
    return 0;
}

// ── Spawn Kendaraan & Auto-Attach Object Kustom ─────────────
stock SpawnPlayerVehicle(playerid, modelid, color1 = -1, color2 = -1, bool:isCustomCop = false) {
    if (!gPlayerData[playerid][p_LoggedIn] || !gPlayerData[playerid][p_Spawned]) return 0;
    if (modelid < 400 || modelid > 611) return 0;

    // Hapus kendaraan spawn sebelumnya milik pemain ini jika ada
    DestroyPlayerSpawnedVehicle(playerid);

    // Ambil koordinat dan sudut hadap pemain
    new Float:x, Float:y, Float:z, Float:a;
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, a);

    if (color1 == -1) color1 = (isCustomCop || modelid == 596 || modelid == 597 || modelid == 598) ? 0 : random(128);
    if (color2 == -1) color2 = (isCustomCop || modelid == 596 || modelid == 597 || modelid == 598) ? 1 : random(128);

    // Buat kendaraan di posisi pemain
    new vehid = CreateVehicle(modelid, x, y, z + 0.5, a, color1, color2, 60000, false);
    if (vehid == INVALID_VEHICLE_ID) {
        SendClientMessage(playerid, COL_RED, "  [!] Gagal memunculkan kendaraan. Batas maksimal kendaraan server tercapai.");
        return 0;
    }

    LinkVehicleToInterior(vehid, GetPlayerInterior(playerid));
    SetVehicleVirtualWorld(vehid, GetPlayerVirtualWorld(playerid));

    // Masukkan pemain ke kursi pengemudi
    PutPlayerInVehicle(playerid, vehid, 0);

    // Nyalakan mesin kendaraan otomatis
    new engine, lights, alarm, doors, bonnet, boot, objective;
    GetVehicleParamsEx(vehid, engine, lights, alarm, doors, bonnet, boot, objective);
    SetVehicleParamsEx(vehid, VEHICLE_PARAMS_ON, VEHICLE_PARAMS_ON, alarm, doors, bonnet, boot, objective);

    // Tempelkan Custom 3D Object jika mobil polisi kustom (Solusi A: Tanpa replace)
    if (isCustomCop || modelid == 597) {
        new objId = CreateObject(CUSTOM_MODEL_COPCARSF, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
        if (objId != INVALID_OBJECT_ID) {
            AttachObjectToVehicle(objId, vehid, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
            gPlayerSpawnedVehObj[playerid] = objId;
        }
    }

    gPlayerSpawnedVeh[playerid] = vehid;

    new vehName[32], msg[144];
    GetVehicleModelName(modelid, vehName, sizeof(vehName));

    if (isCustomCop || modelid == 597) {
        SendClientMessage(playerid, COL_YELLOW, "==========================================================");
        SendClientMessage(playerid, COL_GREEN,  "  🚓 [KENDARAAN KUSTOM] Berhasil Memunculkan Mobil Polisi San Fierro!");
        SendClientMessage(playerid, COL_WHITE,  "  • Model Base : {00EEFF}Police Car SFPD {FFFFFF}(ID: {2ECC71}597{FFFFFF})");
        SendClientMessage(playerid, COL_WHITE,  "  • Custom Mesh: {00EEFF}copcarsf.dff & .txd {FFFFFF}(Custom Simple Model ID: {2ECC71}-1000{FFFFFF})");
        SendClientMessage(playerid, COL_WHITE,  "  • Status     : {2ECC71}Objek Kustom Terpasang (Bebas Replace){FFFFFF}");
        SendClientMessage(playerid, COL_YELLOW, "==========================================================");
    } else {
        format(msg, sizeof(msg), "  [Kendaraan] Berhasil memunculkan {00EEFF}%s {FFFFFF}(Model ID: {2ECC71}%d{FFFFFF}, Warna: %d, %d)", vehName, modelid, color1, color2);
        SendClientMessage(playerid, COL_GREEN, msg);
    }
    return vehid;
}

// ── Menu Dialog Kategori Utama ──────────────────────────────
stock ShowVehicleMainMenu(playerid) {
    new body[1024];
    format(body, sizeof(body),
        "Kategori Kendaraan\tJumlah\n\
        {00EEFF}1. 🚓 Kendaraan Polisi & Darurat (Termasuk Copcar SF Baru)\t{2ECC71}12 Kendaraan\n\
        {00EEFF}2. 🏎️ Mobil Sport & Balap Super (Infernus, Sultan, Bullet)\t{2ECC71}20 Kendaraan\n\
        {00EEFF}3. 🚗 Mobil Sedan & Kendaraan Sipil Harian\t{2ECC71}26 Kendaraan\n\
        {00EEFF}4. 🚙 SUV, Truk Pick-up & Off-Road (Patriot, Huntley)\t{2ECC71}16 Kendaraan\n\
        {00EEFF}5. 🚚 Truk Industri, Angkutan Berat & Bus\t{2ECC71}15 Kendaraan\n\
        {00EEFF}6. 🏍️ Sepeda Motor, Skuter & Sepeda (NRG-500, Sanchez)\t{2ECC71}12 Kendaraan\n\
        {00EEFF}7. ✈️ Pesawat Terbang & Helikopter (Hydra, Maverick)\t{2ECC71}12 Kendaraan\n\
        {00EEFF}8. 🚤 Kapal Cepat, Boat & Perahu Air\t{2ECC71}10 Kendaraan\n\
        {00EEFF}9. 🚜 Kendaraan Unik, Khusus & Kart\t{2ECC71}14 Kendaraan\n\
        {FF4040}0. 🗑️ Hapus Kendaraan Saya Saat Ini\t{E69958}[ /dv ]");

    ShowPlayerDialog(playerid, DLG_VEH_MAIN_MENU, DIALOG_STYLE_TABLIST_HEADERS,
        "Katalog Kendaraan Santara - Pilih Kategori", body, "Buka", "Tutup");
    return 1;
}

// ── Sub-Dialog: Kendaraan Darurat & Polisi ───────────────────
stock ShowEmergencyVehMenu(playerid) {
    new body[1024];
    format(body, sizeof(body),
        "Model ID\tNama Kendaraan\tKeterangan\n\
        {2ECC71}597\t{FFFF00}Police Car SFPD (copcarsf)\t{00EEFF}⭐ Mobil Kustom Baru\n\
        {2ECC71}596\t{FFFFFF}Police Car LSPD\t{AAAAAA}Mobil Patroli Los Santos\n\
        {2ECC71}598\t{FFFFFF}Police Car LVPD\t{AAAAAA}Mobil Patroli Las Venturas\n\
        {2ECC71}599\t{FFFFFF}Police Ranger\t{AAAAAA}SUV Patroli Pedesaan\n\
        {2ECC71}427\t{FFFFFF}Enforcer\t{AAAAAA}Truk Taktis Polisi\n\
        {2ECC71}601\t{FFFFFF}S.W.A.T. Van\t{AAAAAA}Kendaraan Lapis Baja\n\
        {2ECC71}490\t{FFFFFF}FBI Rancher\t{AAAAAA}SUV Hitam Agen Rahasia\n\
        {2ECC71}528\t{FFFFFF}FBI Truck\t{AAAAAA}Truk Taktis Agen Khusus\n\
        {2ECC71}416\t{FFFFFF}Ambulance\t{AAAAAA}Mobil Medis Gawat Darurat\n\
        {2ECC71}407\t{FFFFFF}Firetruck (Tangga)\t{AAAAAA}Mobil Pemadam Kebakaran\n\
        {2ECC71}544\t{FFFFFF}Firetruck LA (Semprot)\t{AAAAAA}Mobil Pemadam Kebakaran\n\
        {2ECC71}497\t{FFFFFF}Police Maverick\t{AAAAAA}Helikopter Patroli Udara\n\
        {2ECC71}430\t{FFFFFF}Predator\t{AAAAAA}Boat Patroli Pantai\n\
        {E69958}<<\t{E69958}Kembali ke Menu Utama\t{E69958}[ Back ]");

    ShowPlayerDialog(playerid, DLG_VEH_CAT_EMERGENCY, DIALOG_STYLE_TABLIST_HEADERS,
        "Kendaraan Darurat & Polisi", body, "Spawn", "Kembali");
    return 1;
}

// ── Sub-Dialog: Mobil Sport ─────────────────────────────────
stock ShowSportVehMenu(playerid) {
    new body[1024];
    format(body, sizeof(body),
        "Model ID\tNama Kendaraan\tTipe\n\
        {2ECC71}411\t{FFFFFF}Infernus\t{00EEFF}Supercar Legendaris\n\
        {2ECC71}451\t{FFFFFF}Turismo\t{00EEFF}Supercar Italia\n\
        {2ECC71}541\t{FFFFFF}Bullet\t{00EEFF}Supercar Balap Ford GT\n\
        {2ECC71}415\t{FFFFFF}Cheetah\t{00EEFF}Supercar Klasik\n\
        {2ECC71}429\t{FFFFFF}Banshee\t{00EEFF}Roadster Viper\n\
        {2ECC71}560\t{FFFFFF}Sultan\t{00EEFF}Sedan Sport 4-Pintu (Subaru)\n\
        {2ECC71}562\t{FFFFFF}Elegy\t{00EEFF}Drift Car Skyline R32\n\
        {2ECC71}559\t{FFFFFF}Jester\t{00EEFF}Tuner Sport Supra\n\
        {2ECC71}565\t{FFFFFF}Flash\t{00EEFF}Hatchback Sport Civic\n\
        {2ECC71}477\t{FFFFFF}ZR-350\t{00EEFF}Rotary Sport RX-7\n\
        {2ECC71}402\t{FFFFFF}Buffalo\t{00EEFF}Muscle Modern\n\
        {2ECC71}506\t{FFFFFF}Super GT\t{00EEFF}Grand Tourer Aston\n\
        {2ECC71}494\t{FFFFFF}Hotring Racer\t{00EEFF}NASCAR Balap\n\
        {2ECC71}603\t{FFFFFF}Phoenix\t{00EEFF}Muscle Trans Am\n\
        {2ECC71}480\t{FFFFFF}Comet\t{00EEFF}Porsche 911\n\
        {2ECC71}587\t{FFFFFF}Euros\t{00EEFF}Coupe Sport 300ZX\n\
        {2ECC71}558\t{FFFFFF}Uranus\t{00EEFF}Hatchback Tuner Eclipse\n\
        {2ECC71}535\t{FFFFFF}Slamvan\t{00EEFF}Custom Lowrider Truck\n\
        {2ECC71}567\t{FFFFFF}Savanna\t{00EEFF}Convertible Lowrider Impala\n\
        {2ECC71}434\t{FFFFFF}Hotknife\t{00EEFF}Hotrod Vintage\n\
        {E69958}<<\t{E69958}Kembali ke Menu Utama\t{E69958}[ Back ]");

    ShowPlayerDialog(playerid, DLG_VEH_CAT_SPORT, DIALOG_STYLE_TABLIST_HEADERS,
        "Mobil Sport & Balap Super", body, "Spawn", "Kembali");
    return 1;
}

// ── Sub-Dialog: Sedan & Sipil ────────────────────────────────
stock ShowSedanVehMenu(playerid) {
    new body[1024];
    format(body, sizeof(body),
        "Model ID\tNama Kendaraan\tKategori\n\
        {2ECC71}426\t{FFFFFF}Premier\t{AAAAAA}Sedan Sipil Cepat\n\
        {2ECC71}405\t{FFFFFF}Sentinel\t{AAAAAA}Sedan Eksekutif BMW\n\
        {2ECC71}421\t{FFFFFF}Washington\t{AAAAAA}Sedan Mewah Pejabat\n\
        {2ECC71}445\t{FFFFFF}Admiral\t{AAAAAA}Sedan Klasik Mercedes\n\
        {2ECC71}507\t{FFFFFF}Elegant\t{AAAAAA}Sedan Mewah Buick\n\
        {2ECC71}566\t{FFFFFF}Tahoma\t{AAAAAA}Sedan Lowrider 4-Pintu\n\
        {2ECC71}516\t{FFFFFF}Nebula\t{AAAAAA}Sedan Keluarga\n\
        {2ECC71}547\t{FFFFFF}Primo\t{AAAAAA}Sedan Kompak\n\
        {2ECC71}550\t{FFFFFF}Sunrise\t{AAAAAA}Sedan Modern\n\
        {2ECC71}551\t{FFFFFF}Merit\t{AAAAAA}Sedan Menengah\n\
        {2ECC71}420\t{FFFFFF}Taxi\t{AAAAAA}Taksi Kuning Publik\n\
        {2ECC71}438\t{FFFFFF}Cabbie\t{AAAAAA}Taksi Klasik\n\
        {2ECC71}409\t{FFFFFF}Stretch\t{AAAAAA}Limousine Panjang\n\
        {2ECC71}492\t{FFFFFF}Greenwood\t{AAAAAA}Sedan Retro CJ\n\
        {2ECC71}466\t{FFFFFF}Glendale\t{AAAAAA}Sedan Klasik 1950\n\
        {2ECC71}549\t{FFFFFF}Tampa\t{AAAAAA}Coupe Klasik\n\
        {2ECC71}496\t{FFFFFF}Blista Compact\t{AAAAAA}Hatchback Kompak CRX\n\
        {2ECC71}410\t{FFFFFF}Manana\t{AAAAAA}Mobil Kecil Mini\n\
        {2ECC71}404\t{FFFFFF}Perennial\t{AAAAAA}Station Wagon Keluarga\n\
        {2ECC71}458\t{FFFFFF}Solair\t{AAAAAA}Station Wagon Modern\n\
        {E69958}<<\t{E69958}Kembali ke Menu Utama\t{E69958}[ Back ]");

    ShowPlayerDialog(playerid, DLG_VEH_CAT_SEDAN, DIALOG_STYLE_TABLIST_HEADERS,
        "Mobil Sedan & Sipil", body, "Spawn", "Kembali");
    return 1;
}

// ── Sub-Dialog: SUV & Off-Road ──────────────────────────────
stock ShowSuvVehMenu(playerid) {
    new body[1024];
    format(body, sizeof(body),
        "Model ID\tNama Kendaraan\tTipe\n\
        {2ECC71}579\t{FFFFFF}Huntley\t{00EEFF}Luxury SUV Range Rover\n\
        {2ECC71}470\t{FFFFFF}Patriot\t{00EEFF}Humvee Militer 4x4\n\
        {2ECC71}400\t{FFFFFF}Landstalker\t{00EEFF}SUV Keluarga Tangguh\n\
        {2ECC71}489\t{FFFFFF}Rancher\t{00EEFF}SUV Off-road 2-Pintu\n\
        {2ECC71}500\t{FFFFFF}Mesa\t{00EEFF}Jeep Terbuka Off-road\n\
        {2ECC71}495\t{FFFFFF}Sandking\t{00EEFF}Truk Reli Padang Pasir\n\
        {2ECC71}444\t{FFFFFF}Monster Truck\t{00EEFF}Truk Monster Raksasa\n\
        {2ECC71}422\t{FFFFFF}Bobcat\t{00EEFF}Pick-up Utility\n\
        {2ECC71}478\t{FFFFFF}Walton\t{00EEFF}Pick-up Klasik Kayu\n\
        {2ECC71}543\t{FFFFFF}Sadler\t{00EEFF}Pick-up Pekerja Keras\n\
        {2ECC71}554\t{FFFFFF}Yosemite\t{00EEFF}Pick-up Modern Perkasa\n\
        {2ECC71}600\t{FFFFFF}Picador\t{00EEFF}Coupe Utility El Camino\n\
        {2ECC71}568\t{FFFFFF}Bandito\t{00EEFF}Buggy Pipa Padang Pasir\n\
        {2ECC71}424\t{FFFFFF}BF Injection\t{00EEFF}Baja Buggy VW Kodok\n\
        {2ECC71}573\t{FFFFFF}Dune\t{00EEFF}Truk Reli Dakar Raksasa\n\
        {E69958}<<\t{E69958}Kembali ke Menu Utama\t{E69958}[ Back ]");

    ShowPlayerDialog(playerid, DLG_VEH_CAT_SUV, DIALOG_STYLE_TABLIST_HEADERS,
        "SUV, Pick-up & Off-Road", body, "Spawn", "Kembali");
    return 1;
}

// ── Sub-Dialog: Truk Berat & Bus ────────────────────────────
stock ShowHeavyVehMenu(playerid) {
    new body[1024];
    format(body, sizeof(body),
        "Model ID\tNama Kendaraan\tKategori\n\
        {2ECC71}515\t{FFFFFF}Roadtrain\t{AAAAAA}Kepala Truk Tronton Kontainer\n\
        {2ECC71}403\t{FFFFFF}Linerunner\t{AAAAAA}Kepala Truk Gandeng Amerika\n\
        {2ECC71}514\t{FFFFFF}Tanker\t{AAAAAA}Truk Tangki BBM\n\
        {2ECC71}455\t{FFFFFF}Flatbed\t{AAAAAA}Truk Bak Datar Panjang\n\
        {2ECC71}473\t{FFFFFF}DFT-30\t{AAAAAA}Truk Derek Pengangkut Mobil\n\
        {2ECC71}443\t{FFFFFF}Packer\t{AAAAAA}Truk Pengangkut Mobil 2-Tingkat\n\
        {2ECC71}414\t{FFFFFF}Mule\t{AAAAAA}Truk Box Logistik Sedang\n\
        {2ECC71}456\t{FFFFFF}Yankee\t{AAAAAA}Truk Box Ekspedisi Besar\n\
        {2ECC71}498\t{FFFFFF}Boxville\t{AAAAAA}Mobil Box Kurir Paket\n\
        {2ECC71}431\t{FFFFFF}Bus\t{AAAAAA}Bus Angkutan Umum Kota\n\
        {2ECC71}437\t{FFFFFF}Coach\t{AAAAAA}Bus Pariwisata Antar Kota\n\
        {2ECC71}408\t{FFFFFF}Trashmaster\t{AAAAAA}Truk Pengangkut Sampah\n\
        {2ECC71}524\t{FFFFFF}Cement Truck\t{AAAAAA}Truk Molen Semen Proyek\n\
        {2ECC71}525\t{FFFFFF}Towtruck\t{AAAAAA}Mobil Derek Derek Derek\n\
        {2ECC71}428\t{FFFFFF}Securicar\t{AAAAAA}Mobil Baja Pengangkut Uang Bank\n\
        {E69958}<<\t{E69958}Kembali ke Menu Utama\t{E69958}[ Back ]");

    ShowPlayerDialog(playerid, DLG_VEH_CAT_HEAVY, DIALOG_STYLE_TABLIST_HEADERS,
        "Truk Industri & Bus", body, "Spawn", "Kembali");
    return 1;
}

// ── Sub-Dialog: Motor & Sepeda ──────────────────────────────
stock ShowBikesVehMenu(playerid) {
    new body[1024];
    format(body, sizeof(body),
        "Model ID\tNama Kendaraan\tKategori\n\
        {2ECC71}522\t{FFFFFF}NRG-500\t{00EEFF}Motor Balap Super 500cc\n\
        {2ECC71}521\t{FFFFFF}FCR-900\t{00EEFF}Motor Sport Streetfighter\n\
        {2ECC71}461\t{FFFFFF}PCJ-600\t{00EEFF}Motor Naked Sport 600cc\n\
        {2ECC71}581\t{FFFFFF}BF-400\t{00EEFF}Motor Sport Harian 400cc\n\
        {2ECC71}468\t{FFFFFF}Sanchez\t{00EEFF}Motor Trail Cross Off-road\n\
        {2ECC71}463\t{FFFFFF}Freeway\t{00EEFF}Motor Cruiser Harley-Davidson\n\
        {2ECC71}586\t{FFFFFF}Wayfarer\t{00EEFF}Motor Touring Lintas Kota\n\
        {2ECC71}462\t{FFFFFF}Faggio\t{00EEFF}Skuter Vespa Klasik Matic\n\
        {2ECC71}471\t{FFFFFF}Quad\t{00EEFF}ATV Motor Roda 4\n\
        {2ECC71}523\t{FFFFFF}HPV-1000\t{00EEFF}Motor Polisi Lalu Lintas\n\
        {2ECC71}510\t{FFFFFF}Mountain Bike\t{00EEFF}Sepeda Gunung Gowes\n\
        {2ECC71}481\t{FFFFFF}BMX\t{00EEFF}Sepeda Akrobatik Trik BMX\n\
        {E69958}<<\t{E69958}Kembali ke Menu Utama\t{E69958}[ Back ]");

    ShowPlayerDialog(playerid, DLG_VEH_CAT_BIKES, DIALOG_STYLE_TABLIST_HEADERS,
        "Sepeda Motor & Sepeda", body, "Spawn", "Kembali");
    return 1;
}

// ── Sub-Dialog: Pesawat & Helikopter ────────────────────────
stock ShowAircraftVehMenu(playerid) {
    new body[1024];
    format(body, sizeof(body),
        "Model ID\tNama Kendaraan\tTipe\n\
        {2ECC71}520\t{FFFFFF}Hydra\t{00EEFF}Jet Tempur VTOL Militer\n\
        {2ECC71}519\t{FFFFFF}Shamal\t{00EEFF}Jet Pribadi Eksekutif VIP\n\
        {2ECC71}577\t{FFFFFF}AT-400\t{00EEFF}Pesawat Penumpang Komersial Jumbo\n\
        {2ECC71}592\t{FFFFFF}Andromada\t{00EEFF}Pesawat Kargo Militer Raksasa\n\
        {2ECC71}487\t{FFFFFF}Maverick\t{00EEFF}Helikopter Sipil Mewah\n\
        {2ECC71}425\t{FFFFFF}Hunter\t{00EEFF}Helikopter Tempur Apache\n\
        {2ECC71}548\t{FFFFFF}Cargobob\t{00EEFF}Helikopter Pengangkut Kargo\n\
        {2ECC71}447\t{FFFFFF}Sea Sparrow\t{00EEFF}Helikopter Amfibi Laut\n\
        {2ECC71}469\t{FFFFFF}Sparrow\t{00EEFF}Helikopter Ringan Kecil\n\
        {2ECC71}511\t{FFFFFF}Beagle\t{00EEFF}Pesawat Baling-baling Kembar\n\
        {2ECC71}512\t{FFFFFF}Cropduster\t{00EEFF}Pesawat Penyemprot Ladang\n\
        {2ECC71}513\t{FFFFFF}Stuntplane\t{00EEFF}Pesawat Akrobat Udara\n\
        {E69958}<<\t{E69958}Kembali ke Menu Utama\t{E69958}[ Back ]");

    ShowPlayerDialog(playerid, DLG_VEH_CAT_AIRCRAFT, DIALOG_STYLE_TABLIST_HEADERS,
        "Pesawat & Helikopter", body, "Spawn", "Kembali");
    return 1;
}

// ── Sub-Dialog: Kapal & Perahu ──────────────────────────────
stock ShowBoatsVehMenu(playerid) {
    new body[1024];
    format(body, sizeof(body),
        "Model ID\tNama Kendaraan\tTipe\n\
        {2ECC71}452\t{FFFFFF}Speeder\t{00EEFF}Speedboat Cepat Modern\n\
        {2ECC71}446\t{FFFFFF}Squalo\t{00EEFF}Speedboat Balap Laut\n\
        {2ECC71}493\t{FFFFFF}Jetmax\t{00EEFF}Speedboat Mewah Performa Tinggi\n\
        {2ECC71}454\t{FFFFFF}Tropic\t{00EEFF}Kapal Pesiar Cabin Cruiser\n\
        {2ECC71}484\t{FFFFFF}Marquis\t{00EEFF}Kapal Layar Mewah Yacht\n\
        {2ECC71}453\t{FFFFFF}Reefer\t{00EEFF}Kapal Penangkap Ikan Nelayan\n\
        {2ECC71}472\t{FFFFFF}Coastguard\t{00EEFF}Boat Penjaga Pantai\n\
        {2ECC71}473\t{FFFFFF}Dinghy\t{00EEFF}Perahu Karet Motor Tempel\n\
        {2ECC71}595\t{FFFFFF}Launch\t{00EEFF}Boat Kayu Klasik\n\
        {2ECC71}539\t{FFFFFF}Vortex\t{00EEFF}Hovercraft Amfibi Darat & Air\n\
        {E69958}<<\t{E69958}Kembali ke Menu Utama\t{E69958}[ Back ]");

    ShowPlayerDialog(playerid, DLG_VEH_CAT_BOATS, DIALOG_STYLE_TABLIST_HEADERS,
        "Kapal & Perahu Air", body, "Spawn", "Kembali");
    return 1;
}

// ── Sub-Dialog: Kendaraan Unik & Khusus ──────────────────────
stock ShowUniqueVehMenu(playerid) {
    new body[1024];
    format(body, sizeof(body),
        "Model ID\tNama Kendaraan\tKategori\n\
        {2ECC71}571\t{FFFFFF}Kart\t{00EEFF}Go-Kart Sirkuit Kecil\n\
        {2ECC71}457\t{FFFFFF}Caddy\t{00EEFF}Mobil Golf Lapangan\n\
        {2ECC71}532\t{FFFFFF}Combine Harvester\t{00EEFF}Mesin Pemanen Padi Sawah\n\
        {2ECC71}531\t{FFFFFF}Tractor\t{00EEFF}Traktor Bajak Sawah\n\
        {2ECC71}486\t{FFFFFF}Dozer\t{00EEFF}Bulldozer Pengeruk Tanah Proyek\n\
        {2ECC71}406\t{FFFFFF}Dumper\t{00EEFF}Truk Tambang Raksasa Caterpillar\n\
        {2ECC71}530\t{FFFFFF}Forklift\t{00EEFF}Forklift Pengangkat Palet Gudang\n\
        {2ECC71}574\t{FFFFFF}Sweeper\t{00EEFF}Mobil Penyapu Sampah Jalanan\n\
        {2ECC71}572\t{FFFFFF}Mower\t{00EEFF}Mesin Pemotong Rumput\n\
        {2ECC71}485\t{FFFFFF}Baggage\t{00EEFF}Mobil Derek Koper Bandara\n\
        {2ECC71}583\t{FFFFFF}Tug\t{00EEFF}Mobil Pendorong Pesawat Bandara\n\
        {2ECC71}423\t{FFFFFF}Mr Whoopee\t{00EEFF}Mobil Penjual Es Krim Lagu\n\
        {2ECC71}588\t{FFFFFF}Hotdog\t{00EEFF}Mobil Van Penjual Makanan Hotdog\n\
        {2ECC71}432\t{FFFFFF}Rhino\t{00EEFF}Tank Tempur Lapis Baja Meriam\n\
        {E69958}<<\t{E69958}Kembali ke Menu Utama\t{E69958}[ Back ]");

    ShowPlayerDialog(playerid, DLG_VEH_CAT_UNIQUE, DIALOG_STYLE_TABLIST_HEADERS,
        "Kendaraan Unik & Khusus", body, "Spawn", "Kembali");
    return 1;
}

// ── Handler Dialog Kendaraan ────────────────────────────────
stock HandleVehicleDialog(playerid, dialogid, response, listitem, inputtext[]) {
    #pragma unused inputtext

    // ── 1. MAIN MENU ──
    if (dialogid == DLG_VEH_MAIN_MENU) {
        if (!response) return 1;
        switch (listitem) {
            case 0: ShowEmergencyVehMenu(playerid);
            case 1: ShowSportVehMenu(playerid);
            case 2: ShowSedanVehMenu(playerid);
            case 3: ShowSuvVehMenu(playerid);
            case 4: ShowHeavyVehMenu(playerid);
            case 5: ShowBikesVehMenu(playerid);
            case 6: ShowAircraftVehMenu(playerid);
            case 7: ShowBoatsVehMenu(playerid);
            case 8: ShowUniqueVehMenu(playerid);
            case 9: {
                if (DestroyPlayerSpawnedVehicle(playerid)) {
                    SendClientMessage(playerid, COL_GREEN, "  ✓ Kendaraan spawn Anda berhasil dihapus.");
                } else {
                    SendClientMessage(playerid, COL_RED, "  [!] Anda tidak memiliki kendaraan spawn yang aktif.");
                }
            }
        }
        return 1;
    }

    // ── 2. DARURAT & POLISI ──
    if (dialogid == DLG_VEH_CAT_EMERGENCY) {
        if (!response) return ShowVehicleMainMenu(playerid);
        new models[] = {597, 596, 598, 599, 427, 601, 490, 528, 416, 407, 544, 497, 430};
        if (listitem >= 0 && listitem < sizeof(models)) {
            new bool:isCop = (models[listitem] == 597);
            SpawnPlayerVehicle(playerid, models[listitem], 1, 1, isCop);
        } else {
            ShowVehicleMainMenu(playerid);
        }
        return 1;
    }

    // ── 3. SPORT & SUPERCAR ──
    if (dialogid == DLG_VEH_CAT_SPORT) {
        if (!response) return ShowVehicleMainMenu(playerid);
        new models[] = {411, 451, 541, 415, 429, 560, 562, 559, 565, 477, 402, 506, 494, 603, 480, 587, 558, 535, 567, 434};
        if (listitem >= 0 && listitem < sizeof(models)) {
            SpawnPlayerVehicle(playerid, models[listitem]);
        } else {
            ShowVehicleMainMenu(playerid);
        }
        return 1;
    }

    // ── 4. SEDAN & SIPIL ──
    if (dialogid == DLG_VEH_CAT_SEDAN) {
        if (!response) return ShowVehicleMainMenu(playerid);
        new models[] = {426, 405, 421, 445, 507, 566, 516, 547, 550, 551, 420, 438, 409, 492, 466, 549, 496, 410, 404, 458};
        if (listitem >= 0 && listitem < sizeof(models)) {
            SpawnPlayerVehicle(playerid, models[listitem]);
        } else {
            ShowVehicleMainMenu(playerid);
        }
        return 1;
    }

    // ── 5. SUV & OFF-ROAD ──
    if (dialogid == DLG_VEH_CAT_SUV) {
        if (!response) return ShowVehicleMainMenu(playerid);
        new models[] = {579, 470, 400, 489, 500, 495, 444, 422, 478, 543, 554, 600, 568, 424, 573};
        if (listitem >= 0 && listitem < sizeof(models)) {
            SpawnPlayerVehicle(playerid, models[listitem]);
        } else {
            ShowVehicleMainMenu(playerid);
        }
        return 1;
    }

    // ── 6. TRUK BERAT & BUS ──
    if (dialogid == DLG_VEH_CAT_HEAVY) {
        if (!response) return ShowVehicleMainMenu(playerid);
        new models[] = {515, 403, 514, 455, 473, 443, 414, 456, 498, 431, 437, 408, 524, 525, 428};
        if (listitem >= 0 && listitem < sizeof(models)) {
            SpawnPlayerVehicle(playerid, models[listitem]);
        } else {
            ShowVehicleMainMenu(playerid);
        }
        return 1;
    }

    // ── 7. MOTOR & SEPEDA ──
    if (dialogid == DLG_VEH_CAT_BIKES) {
        if (!response) return ShowVehicleMainMenu(playerid);
        new models[] = {522, 521, 461, 581, 468, 463, 586, 462, 471, 523, 510, 481};
        if (listitem >= 0 && listitem < sizeof(models)) {
            SpawnPlayerVehicle(playerid, models[listitem]);
        } else {
            ShowVehicleMainMenu(playerid);
        }
        return 1;
    }

    // ── 8. PESAWAT & HELIKOPTER ──
    if (dialogid == DLG_VEH_CAT_AIRCRAFT) {
        if (!response) return ShowVehicleMainMenu(playerid);
        new models[] = {520, 519, 577, 592, 487, 425, 548, 447, 469, 511, 512, 513};
        if (listitem >= 0 && listitem < sizeof(models)) {
            SpawnPlayerVehicle(playerid, models[listitem]);
        } else {
            ShowVehicleMainMenu(playerid);
        }
        return 1;
    }

    // ── 9. KAPAL & BOAT ──
    if (dialogid == DLG_VEH_CAT_BOATS) {
        if (!response) return ShowVehicleMainMenu(playerid);
        new models[] = {452, 446, 493, 454, 484, 453, 472, 473, 595, 539};
        if (listitem >= 0 && listitem < sizeof(models)) {
            SpawnPlayerVehicle(playerid, models[listitem]);
        } else {
            ShowVehicleMainMenu(playerid);
        }
        return 1;
    }

    // ── 10. UNIK & KHUSUS ──
    if (dialogid == DLG_VEH_CAT_UNIQUE) {
        if (!response) return ShowVehicleMainMenu(playerid);
        new models[] = {571, 457, 532, 531, 486, 406, 530, 574, 572, 485, 583, 423, 588, 432};
        if (listitem >= 0 && listitem < sizeof(models)) {
            SpawnPlayerVehicle(playerid, models[listitem]);
        } else {
            ShowVehicleMainMenu(playerid);
        }
        return 1;
    }

    return 0;
}

// ── Utilitas: Perbaiki Kendaraan ────────────────────────────
stock RepairPlayerVehicle(playerid) {
    if (!IsPlayerInAnyVehicle(playerid)) {
        SendClientMessage(playerid, COL_RED, "  [!] Anda harus berada di dalam kendaraan.");
        return 0;
    }
    new vehid = GetPlayerVehicleID(playerid);
    RepairVehicle(vehid);
    SetVehicleHealth(vehid, 1000.0);
    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
    SendClientMessage(playerid, COL_GREEN, "  ✓ Kendaraan berhasil diperbaiki mulus seperti baru!");
    return 1;
}

// ── Utilitas: Balikkan Kendaraan Terbalik ────────────────────
stock FlipPlayerVehicle(playerid) {
    if (!IsPlayerInAnyVehicle(playerid)) {
        SendClientMessage(playerid, COL_RED, "  [!] Anda harus berada di dalam kendaraan.");
        return 0;
    }
    new vehid = GetPlayerVehicleID(playerid);
    new Float:a, Float:x, Float:y, Float:z;
    GetVehicleZAngle(vehid, a);
    GetVehiclePos(vehid, x, y, z);
    SetVehiclePos(vehid, x, y, z + 1.2);
    SetVehicleZAngle(vehid, a);
    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
    SendClientMessage(playerid, COL_GREEN, "  ✓ Posisi kendaraan berhasil dibalikkan ke posisi normal.");
    return 1;
}

// ── Utilitas: Mesin Kendaraan (Engine On/Off) ────────────────
stock TogglePlayerVehicleEngine(playerid) {
    if (!IsPlayerInAnyVehicle(playerid)) {
        SendClientMessage(playerid, COL_RED, "  [!] Anda harus berada di dalam kendaraan.");
        return 0;
    }
    if (GetPlayerVehicleSeat(playerid) != 0) {
        SendClientMessage(playerid, COL_RED, "  [!] Hanya pengemudi yang dapat menyalakan/mematikan mesin.");
        return 0;
    }
    new vehid = GetPlayerVehicleID(playerid);
    new engine, lights, alarm, doors, bonnet, boot, objective;
    GetVehicleParamsEx(vehid, engine, lights, alarm, doors, bonnet, boot, objective);
    if (engine == VEHICLE_PARAMS_ON) {
        SetVehicleParamsEx(vehid, VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);
        SendClientMessage(playerid, COL_YELLOW, "  * Mesin kendaraan dimatikan.");
    } else {
        SetVehicleParamsEx(vehid, VEHICLE_PARAMS_ON, lights, alarm, doors, bonnet, boot, objective);
        SendClientMessage(playerid, COL_GREEN, "  * Mesin kendaraan dinyalakan.");
    }
    return 1;
}

// ── Utilitas: Lampu Kendaraan (Lights On/Off) ────────────────
stock TogglePlayerVehicleLights(playerid) {
    if (!IsPlayerInAnyVehicle(playerid)) {
        SendClientMessage(playerid, COL_RED, "  [!] Anda harus berada di dalam kendaraan.");
        return 0;
    }
    new vehid = GetPlayerVehicleID(playerid);
    new engine, lights, alarm, doors, bonnet, boot, objective;
    GetVehicleParamsEx(vehid, engine, lights, alarm, doors, bonnet, boot, objective);
    if (lights == VEHICLE_PARAMS_ON) {
        SetVehicleParamsEx(vehid, engine, VEHICLE_PARAMS_OFF, alarm, doors, bonnet, boot, objective);
        SendClientMessage(playerid, COL_YELLOW, "  * Lampu kendaraan dimatikan.");
    } else {
        SetVehicleParamsEx(vehid, engine, VEHICLE_PARAMS_ON, alarm, doors, bonnet, boot, objective);
        SendClientMessage(playerid, COL_GREEN, "  * Lampu kendaraan dinyalakan.");
    }
    return 1;
}

// ── Utilitas: Kunci Pintu Kendaraan (Lock/Unlock) ────────────
stock TogglePlayerVehicleLock(playerid) {
    if (!IsPlayerInAnyVehicle(playerid)) {
        SendClientMessage(playerid, COL_RED, "  [!] Anda harus berada di dalam kendaraan.");
        return 0;
    }
    new vehid = GetPlayerVehicleID(playerid);
    new engine, lights, alarm, doors, bonnet, boot, objective;
    GetVehicleParamsEx(vehid, engine, lights, alarm, doors, bonnet, boot, objective);
    if (doors == VEHICLE_PARAMS_ON) {
        SetVehicleParamsEx(vehid, engine, lights, alarm, VEHICLE_PARAMS_OFF, bonnet, boot, objective);
        SendClientMessage(playerid, COL_GREEN, "  * Pintu kendaraan dibuka (Unlocked).");
        PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
    } else {
        SetVehicleParamsEx(vehid, engine, lights, alarm, VEHICLE_PARAMS_ON, bonnet, boot, objective);
        SendClientMessage(playerid, COL_YELLOW, "  * Pintu kendaraan dikunci (Locked).");
        PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
    }
    return 1;
}
