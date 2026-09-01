#if defined _MODULE_CRAFTING_INC
    #endinput
#endif
#define _MODULE_CRAFTING_INC

// ============================================================
//  SantaraBaru Roleplay - Gunsmith & Weapon Crafting System
//  Lokasi: Meja Rakit Gudang Rahasia (Flint County Hideout)
// ============================================================

new Text3D:gCraftingLabel;
new gCraftingTableObject = INVALID_OBJECT_ID;

stock InitCraftingSystem() {
    // Spawn Objek Meja Kerja Fisik (Model 2008 Workbench)
    gCraftingTableObject = CreateObject(2008, CRAFT_BENCH_X, CRAFT_BENCH_Y, CRAFT_BENCH_Z - 0.9, 0.0, 0.0, CRAFT_BENCH_A);
    CreatePickup(1239, 1, CRAFT_BENCH_X, CRAFT_BENCH_Y, CRAFT_BENCH_Z, 0);

    gCraftingLabel = Create3DTextLabel(
        "{FF0055}[ MEJA KERJA RAHASIA / GUNSMITH WORKBENCH ]\n{FFFFFF}Tekan {FFFF00}[ H ]{FFFFFF} atau gunakan {00EEFF}/craft{FFFFFF}\n{AAAAAA}(Wajib membawa Kotak Perkakas / Toolbox di tas)",
        0xFFFFFFFF,
        CRAFT_BENCH_X, CRAFT_BENCH_Y, CRAFT_BENCH_Z + 0.6,
        15.0, 0, 0
    );
}

stock ShowCraftingMainMenu(playerid) {
    if (!Inventory_HasItem(playerid, ITEM_TOOLBOX)) {
        SendClientMessage(playerid, COL_RED, "  [!] Anda membutuhkan Kotak Perkakas (Toolbox) di tas untuk menggunakan Meja Kerja!");
        return 0;
    }

    new menuStr[256];
    format(menuStr, sizeof(menuStr),
        "1. Komponen & Part Senjata\n" \
        "2. Senjata Api (Pistol, Shotgun, AK-47)\n" \
        "3. Kotak Amunisi Peluru\n" \
        "4. Perlengkapan Tempur (Rompi Kevlar)"
    );

    ShowPlayerDialog(playerid, DLG_CRAFT_CATEGORY, DIALOG_STYLE_LIST,
        "{FF0055}Meja Perakitan Senjata & Amunisi", menuStr, "Pilih", "Tutup");
    return 1;
}

stock ShowCraftCategoryMenu(playerid, category) {
    new dialogStr[1024];

    switch (category) {
        case 0: { // Komponen (Baja & Kuningan)
            new steel = Inventory_GetItemCount(playerid, ITEM_STEEL_BAR);
            new brass = Inventory_GetItemCount(playerid, ITEM_BRASS_PLATE);

            format(dialogStr, sizeof(dialogStr),
                "Komponen\tBahan Diperlukan\tStok Anda\n" \
                "{00EEFF}Laras & Slide Senjata{FFFFFF}\t8x Batang Baja\t%s%d/8 Baja{FFFFFF}\n" \
                "{00EEFF}Pelatuk & Mekanikal{FFFFFF}\t6x Batang Baja, 4x Lempeng Kuningan\t%s%d/6 Baja, %s%d/4 Kuningan{FFFFFF}\n" \
                "{00EEFF}Magasin Kosong{FFFFFF}\t5x Lempeng Kuningan, 2x Batang Baja\t%s%d/5 Kuningan, %s%d/2 Baja{FFFFFF}",
                (steel >= 8) ? "{00FF00}" : "{FF0000}", steel,
                (steel >= 6) ? "{00FF00}" : "{FF0000}", steel,
                (brass >= 4) ? "{00FF00}" : "{FF0000}", brass,
                (brass >= 5) ? "{00FF00}" : "{FF0000}", brass,
                (steel >= 2) ? "{00FF00}" : "{FF0000}", steel
            );
            SetPVarInt(playerid, "CraftCat", 1);
            ShowPlayerDialog(playerid, DLG_CRAFT_MAIN, DIALOG_STYLE_TABLIST_HEADERS,
                "{FF0055}Rakit Komponen Senjata", dialogStr, "Rakit", "Kembali");
        }
        case 1: { // Senjata Api (Tier Eksklusif)
            new barrel = Inventory_GetItemCount(playerid, ITEM_BARREL_SLIDE);
            new trigger = Inventory_GetItemCount(playerid, ITEM_TRIGGER_MECH);
            new mag = Inventory_GetItemCount(playerid, ITEM_EMPTY_MAG);
            new steel = Inventory_GetItemCount(playerid, ITEM_STEEL_BAR);
            new brass = Inventory_GetItemCount(playerid, ITEM_BRASS_PLATE);

            format(dialogStr, sizeof(dialogStr),
                "Senjata Api\tResep Bahan Diperlukan\tKetersediaan Anda\n" \
                "{00EEFF}Pistol 9mm (Colt 45){FFFFFF}\t2 Laras, 2 Pelatuk, 1 Mag, 12 Baja, 8 Kuningan\t%s%d/2 Laras, %s%d/2 Pelatuk, %s%d/1 Mag, %s%d/12 Baja, %s%d/8 Kuningan{FFFFFF}\n" \
                "{00EEFF}Pump-Action Shotgun{FFFFFF}\t3 Laras, 3 Pelatuk, 24 Baja, 14 Kuningan\t%s%d/3 Laras, %s%d/3 Pelatuk, %s%d/24 Baja, %s%d/14 Kuningan{FFFFFF}\n" \
                "{00EEFF}AK-47 Assault Rifle{FFFFFF}\t4 Laras, 3 Pelatuk, 2 Mag, 26 Baja, 18 Kuningan\t%s%d/4 Laras, %s%d/3 Pelatuk, %s%d/2 Mag, %s%d/26 Baja, %s%d/18 Kuningan{FFFFFF}\n" \
                "{00EEFF}Desert Eagle (.50 AE){FFFFFF}\t4 Laras, 4 Pelatuk, 2 Mag, 32 Baja, 22 Kuningan\t%s%d/4 Laras, %s%d/4 Pelatuk, %s%d/2 Mag, %s%d/32 Baja, %s%d/22 Kuningan{FFFFFF}",
                (barrel >= 2) ? "{00FF00}" : "{FF0000}", barrel,
                (trigger >= 2) ? "{00FF00}" : "{FF0000}", trigger,
                (mag >= 1) ? "{00FF00}" : "{FF0000}", mag,
                (steel >= 12) ? "{00FF00}" : "{FF0000}", steel,
                (brass >= 8) ? "{00FF00}" : "{FF0000}", brass,
                (barrel >= 3) ? "{00FF00}" : "{FF0000}", barrel,
                (trigger >= 3) ? "{00FF00}" : "{FF0000}", trigger,
                (steel >= 24) ? "{00FF00}" : "{FF0000}", steel,
                (brass >= 14) ? "{00FF00}" : "{FF0000}", brass,
                (barrel >= 4) ? "{00FF00}" : "{FF0000}", barrel,
                (trigger >= 3) ? "{00FF00}" : "{FF0000}", trigger,
                (mag >= 2) ? "{00FF00}" : "{FF0000}", mag,
                (steel >= 26) ? "{00FF00}" : "{FF0000}", steel,
                (brass >= 18) ? "{00FF00}" : "{FF0000}", brass,
                (barrel >= 4) ? "{00FF00}" : "{FF0000}", barrel,
                (trigger >= 4) ? "{00FF00}" : "{FF0000}", trigger,
                (mag >= 2) ? "{00FF00}" : "{FF0000}", mag,
                (steel >= 32) ? "{00FF00}" : "{FF0000}", steel,
                (brass >= 22) ? "{00FF00}" : "{FF0000}", brass
            );
            SetPVarInt(playerid, "CraftCat", 2);
            ShowPlayerDialog(playerid, DLG_CRAFT_MAIN, DIALOG_STYLE_TABLIST_HEADERS,
                "{FF0055}Rakit Senjata Api Eksklusif", dialogStr, "Rakit", "Kembali");
        }
        case 2: { // Amunisi
            new brass = Inventory_GetItemCount(playerid, ITEM_BRASS_PLATE);
            new powder = Inventory_GetItemCount(playerid, ITEM_GUNPOWDER);

            format(dialogStr, sizeof(dialogStr),
                "Amunisi\tBahan Diperlukan\tKetersediaan Anda\n" \
                "{00EEFF}50x Peluru 9mm (Pistol){FFFFFF}\t2x Kuningan, 2x Mesiu\t%s%d/2 Kuningan, %s%d/2 Mesiu{FFFFFF}\n" \
                "{00EEFF}35x Peluru .50 AE (Deagle){FFFFFF}\t3x Kuningan, 3x Mesiu\t%s%d/3 Kuningan, %s%d/3 Mesiu{FFFFFF}\n" \
                "{00EEFF}25x Peluru 12 Gauge (Shotgun){FFFFFF}\t2x Kuningan, 3x Mesiu\t%s%d/2 Kuningan, %s%d/3 Mesiu{FFFFFF}\n" \
                "{00EEFF}60x Peluru 7.62mm (AK-47){FFFFFF}\t4x Kuningan, 4x Mesiu\t%s%d/4 Kuningan, %s%d/4 Mesiu{FFFFFF}",
                (brass >= 2) ? "{00FF00}" : "{FF0000}", brass,
                (powder >= 2) ? "{00FF00}" : "{FF0000}", powder,
                (brass >= 3) ? "{00FF00}" : "{FF0000}", brass,
                (powder >= 3) ? "{00FF00}" : "{FF0000}", powder,
                (brass >= 2) ? "{00FF00}" : "{FF0000}", brass,
                (powder >= 3) ? "{00FF00}" : "{FF0000}", powder,
                (brass >= 4) ? "{00FF00}" : "{FF0000}", brass,
                (powder >= 4) ? "{00FF00}" : "{FF0000}", powder
            );
            SetPVarInt(playerid, "CraftCat", 3);
            ShowPlayerDialog(playerid, DLG_CRAFT_MAIN, DIALOG_STYLE_TABLIST_HEADERS,
                "{FF0055}Cetak Amunisi Peluru", dialogStr, "Cetak", "Kembali");
        }
        case 3: { // Perlengkapan: Rompi Kevlar (10 Batang Baja)
            new steel = Inventory_GetItemCount(playerid, ITEM_STEEL_BAR);

            format(dialogStr, sizeof(dialogStr),
                "Perlengkapan\tResep Bahan\tKetersediaan Anda\n" \
                "{00EEFF}Rompi Kevlar (Body Armor){FFFFFF}\t10x Batang Baja\t%s%d/10 Batang Baja{FFFFFF}",
                (steel >= 10) ? "{00FF00}" : "{FF0000}", steel
            );
            SetPVarInt(playerid, "CraftCat", 4);
            ShowPlayerDialog(playerid, DLG_CRAFT_MAIN, DIALOG_STYLE_TABLIST_HEADERS,
                "{FF0055}Rakit Perlengkapan Tempur", dialogStr, "Rakit", "Kembali");
        }
    }
}

stock HandleCraftingDialog(playerid, dialogid, response, listitem) {
    if (dialogid == DLG_CRAFT_CATEGORY) {
        if (!response) return 1;
        ShowCraftCategoryMenu(playerid, listitem);
        return 1;
    }

    if (dialogid == DLG_CRAFT_MAIN) {
        if (!response) {
            ShowCraftingMainMenu(playerid);
            return 1;
        }

        new cat = GetPVarInt(playerid, "CraftCat");
        new charname[48], rpMsg[144];
        GetCharName(playerid, charname);

        if (cat == 1) { // Komponen (Baja & Kuningan)
            if (listitem == 0) { // Laras & Slide (8 Baja)
                if (Inventory_GetItemCount(playerid, ITEM_STEEL_BAR) < 8) {
                    SendClientMessage(playerid, COL_RED, "  [CRAFT] Anda butuh 8x Batang Baja!");
                    return 1;
                }
                Inventory_RemoveItem(playerid, ITEM_STEEL_BAR, 8);
                Inventory_AddItem(playerid, ITEM_BARREL_SLIDE, 1);
                SendClientMessage(playerid, COL_GREEN, "  [CRAFT] Sukses merakit {00EEFF}1x Laras & Slide Senjata{FFFFFF}!");
                format(rpMsg, sizeof(rpMsg), "* %s membubut dan menghaluskan batang baja murni menjadi laras senjata presisi.", charname);
            } else if (listitem == 1) { // Pelatuk & Mekanikal (6 Baja + 4 Kuningan)
                if (Inventory_GetItemCount(playerid, ITEM_STEEL_BAR) < 6 || Inventory_GetItemCount(playerid, ITEM_BRASS_PLATE) < 4) {
                    SendClientMessage(playerid, COL_RED, "  [CRAFT] Anda butuh 6x Batang Baja dan 4x Lempeng Kuningan!");
                    return 1;
                }
                Inventory_RemoveItem(playerid, ITEM_STEEL_BAR, 6);
                Inventory_RemoveItem(playerid, ITEM_BRASS_PLATE, 4);
                Inventory_AddItem(playerid, ITEM_TRIGGER_MECH, 1);
                SendClientMessage(playerid, COL_GREEN, "  [CRAFT] Sukses merakit {00EEFF}1x Pelatuk & Mekanikal Senjata{FFFFFF}!");
                format(rpMsg, sizeof(rpMsg), "* %s merakit pegas baja dan pelatuk mekanik kuningan presisi.", charname);
            } else if (listitem == 2) { // Magasin Kosong (5 Kuningan + 2 Baja)
                if (Inventory_GetItemCount(playerid, ITEM_BRASS_PLATE) < 5 || Inventory_GetItemCount(playerid, ITEM_STEEL_BAR) < 2) {
                    SendClientMessage(playerid, COL_RED, "  [CRAFT] Anda butuh 5x Lempeng Kuningan dan 2x Batang Baja!");
                    return 1;
                }
                Inventory_RemoveItem(playerid, ITEM_BRASS_PLATE, 5);
                Inventory_RemoveItem(playerid, ITEM_STEEL_BAR, 2);
                Inventory_AddItem(playerid, ITEM_EMPTY_MAG, 1);
                SendClientMessage(playerid, COL_GREEN, "  [CRAFT] Sukses merakit {00EEFF}1x Magasin Kosong{FFFFFF}!");
                format(rpMsg, sizeof(rpMsg), "* %s menekuk pelat kuningan dan memasang per pegas baja magasin amunisi.", charname);
            }
        }
        else if (cat == 2) { // Senjata Api (Tier Eksklusif - Maksimal 1 Pistol & 1 Laras Panjang)
            if (listitem == 0) { // Colt 45 (2 Laras, 2 Pelatuk, 1 Mag, 12 Baja, 8 Kuningan)
                if (Inventory_HasPistol(playerid)) {
                    SendClientMessage(playerid, COL_RED, "  [CRAFT] Anda sudah membawa 1 senjata jenis pistol (Maksimal 1 Pistol)!");
                    return 1;
                }
                if (Inventory_GetItemCount(playerid, ITEM_BARREL_SLIDE) < 2 || Inventory_GetItemCount(playerid, ITEM_TRIGGER_MECH) < 2 || Inventory_GetItemCount(playerid, ITEM_EMPTY_MAG) < 1 || Inventory_GetItemCount(playerid, ITEM_STEEL_BAR) < 12 || Inventory_GetItemCount(playerid, ITEM_BRASS_PLATE) < 8) {
                    SendClientMessage(playerid, COL_RED, "  [CRAFT] Bahan tidak cukup (2 Laras, 2 Pelatuk, 1 Mag, 12 Baja, 8 Kuningan)!");
                    return 1;
                }
                Inventory_RemoveItem(playerid, ITEM_BARREL_SLIDE, 2);
                Inventory_RemoveItem(playerid, ITEM_TRIGGER_MECH, 2);
                Inventory_RemoveItem(playerid, ITEM_EMPTY_MAG, 1);
                Inventory_RemoveItem(playerid, ITEM_STEEL_BAR, 12);
                Inventory_RemoveItem(playerid, ITEM_BRASS_PLATE, 8);
                Inventory_AddItem(playerid, ITEM_WEAPON_COLT45, 1);
                SyncPlayerWeaponsFromInventory(playerid);
                SendClientMessage(playerid, COL_GREEN, "  [CRAFT] Sukses merakit {00EEFF}1x Pistol 9mm (Colt 45){FFFFFF} (tersimpan di tas)!");
                format(rpMsg, sizeof(rpMsg), "* %s menyatukan seluruh komponen laras presisi, pelatuk, dan bodi pistol 9mm.", charname);
            } else if (listitem == 1) { // Shotgun (3 Laras, 3 Pelatuk, 24 Baja, 14 Kuningan)
                if (Inventory_HasLongWeapon(playerid)) {
                    SendClientMessage(playerid, COL_RED, "  [CRAFT] Anda sudah membawa 1 senjata laras panjang (Maksimal 1 Laras Panjang)!");
                    return 1;
                }
                if (Inventory_GetItemCount(playerid, ITEM_BARREL_SLIDE) < 3 || Inventory_GetItemCount(playerid, ITEM_TRIGGER_MECH) < 3 || Inventory_GetItemCount(playerid, ITEM_STEEL_BAR) < 24 || Inventory_GetItemCount(playerid, ITEM_BRASS_PLATE) < 14) {
                    SendClientMessage(playerid, COL_RED, "  [CRAFT] Bahan tidak cukup (3 Laras, 3 Pelatuk, 24 Baja, 14 Kuningan)!");
                    return 1;
                }
                Inventory_RemoveItem(playerid, ITEM_BARREL_SLIDE, 3);
                Inventory_RemoveItem(playerid, ITEM_TRIGGER_MECH, 3);
                Inventory_RemoveItem(playerid, ITEM_STEEL_BAR, 24);
                Inventory_RemoveItem(playerid, ITEM_BRASS_PLATE, 14);
                Inventory_AddItem(playerid, ITEM_WEAPON_SHOTGUN, 1);
                SyncPlayerWeaponsFromInventory(playerid);
                SendClientMessage(playerid, COL_GREEN, "  [CRAFT] Sukses merakit {00EEFF}1x Pump-Action Shotgun{FFFFFF} (tersimpan di tas)!");
                format(rpMsg, sizeof(rpMsg), "* %s merakit tabung pompa, breech baja, dan laras panjang senapan shotgun.", charname);
            } else if (listitem == 2) { // AK-47 (4 Laras, 3 Pelatuk, 2 Mag, 26 Baja, 18 Kuningan)
                if (Inventory_HasLongWeapon(playerid)) {
                    SendClientMessage(playerid, COL_RED, "  [CRAFT] Anda sudah membawa 1 senjata laras panjang (Maksimal 1 Laras Panjang)!");
                    return 1;
                }
                if (Inventory_GetItemCount(playerid, ITEM_BARREL_SLIDE) < 4 || Inventory_GetItemCount(playerid, ITEM_TRIGGER_MECH) < 3 || Inventory_GetItemCount(playerid, ITEM_EMPTY_MAG) < 2 || Inventory_GetItemCount(playerid, ITEM_STEEL_BAR) < 26 || Inventory_GetItemCount(playerid, ITEM_BRASS_PLATE) < 18) {
                    SendClientMessage(playerid, COL_RED, "  [CRAFT] Bahan tidak cukup (4 Laras, 3 Pelatuk, 2 Mag, 26 Baja, 18 Kuningan)!");
                    return 1;
                }
                Inventory_RemoveItem(playerid, ITEM_BARREL_SLIDE, 4);
                Inventory_RemoveItem(playerid, ITEM_TRIGGER_MECH, 3);
                Inventory_RemoveItem(playerid, ITEM_EMPTY_MAG, 2);
                Inventory_RemoveItem(playerid, ITEM_STEEL_BAR, 26);
                Inventory_RemoveItem(playerid, ITEM_BRASS_PLATE, 18);
                Inventory_AddItem(playerid, ITEM_WEAPON_AK47, 1);
                SyncPlayerWeaponsFromInventory(playerid);
                SendClientMessage(playerid, COL_GREEN, "  [CRAFT] Sukses merakit {00EEFF}1x AK-47 Assault Rifle{FFFFFF} (tersimpan di tas)!");
                format(rpMsg, sizeof(rpMsg), "* %s merakit receiver baja berat dan mekanisme otomatis senapan serbu AK-47.", charname);
            } else if (listitem == 3) { // Desert Eagle (4 Laras, 4 Pelatuk, 2 Mag, 32 Baja, 22 Kuningan)
                if (Inventory_HasPistol(playerid)) {
                    SendClientMessage(playerid, COL_RED, "  [CRAFT] Anda sudah membawa 1 senjata jenis pistol (Maksimal 1 Pistol)!");
                    return 1;
                }
                if (Inventory_GetItemCount(playerid, ITEM_BARREL_SLIDE) < 4 || Inventory_GetItemCount(playerid, ITEM_TRIGGER_MECH) < 4 || Inventory_GetItemCount(playerid, ITEM_EMPTY_MAG) < 2 || Inventory_GetItemCount(playerid, ITEM_STEEL_BAR) < 32 || Inventory_GetItemCount(playerid, ITEM_BRASS_PLATE) < 22) {
                    SendClientMessage(playerid, COL_RED, "  [CRAFT] Bahan tidak cukup (4 Laras, 4 Pelatuk, 2 Mag, 32 Baja, 22 Kuningan)!");
                    return 1;
                }
                Inventory_RemoveItem(playerid, ITEM_BARREL_SLIDE, 4);
                Inventory_RemoveItem(playerid, ITEM_TRIGGER_MECH, 4);
                Inventory_RemoveItem(playerid, ITEM_EMPTY_MAG, 2);
                Inventory_RemoveItem(playerid, ITEM_STEEL_BAR, 32);
                Inventory_RemoveItem(playerid, ITEM_BRASS_PLATE, 22);
                Inventory_AddItem(playerid, ITEM_WEAPON_DEAGLE, 1);
                SyncPlayerWeaponsFromInventory(playerid);
                SendClientMessage(playerid, COL_GREEN, "  [CRAFT] Sukses merakit {00EEFF}1x Desert Eagle (.50 AE){FFFFFF} (tersimpan di tas)!");
                format(rpMsg, sizeof(rpMsg), "* %s mengunci slide dan laras baja murni Desert Eagle berkekuatan dahsyat.", charname);
            }
        }
        else if (cat == 3) { // Amunisi (Dapat Butiran Peluru Langsung)
            if (listitem == 0) { // 9mm (2 Kuningan, 2 Mesiu -> 50 Peluru)
                if (Inventory_GetItemCount(playerid, ITEM_BRASS_PLATE) < 2 || Inventory_GetItemCount(playerid, ITEM_GUNPOWDER) < 2) {
                    SendClientMessage(playerid, COL_RED, "  [CRAFT] Anda butuh 2x Lempeng Kuningan dan 2x Bubuk Mesiu!");
                    return 1;
                }
                Inventory_RemoveItem(playerid, ITEM_BRASS_PLATE, 2);
                Inventory_RemoveItem(playerid, ITEM_GUNPOWDER, 2);
                Inventory_AddItem(playerid, ITEM_AMMO_9MM, 50);
                SyncPlayerWeaponsFromInventory(playerid);
                SendClientMessage(playerid, COL_GREEN, "  [CRAFT] Sukses mencetak {00EEFF}50 butir Peluru 9mm{FFFFFF} (masuk ke tas & senjata)!");
                format(rpMsg, sizeof(rpMsg), "* %s mengisi mesiu dan menekan selongsong peluru 9mm siap pakai.", charname);
            } else if (listitem == 1) { // .50 AE (3 Kuningan, 3 Mesiu -> 35 Peluru)
                if (Inventory_GetItemCount(playerid, ITEM_BRASS_PLATE) < 3 || Inventory_GetItemCount(playerid, ITEM_GUNPOWDER) < 3) {
                    SendClientMessage(playerid, COL_RED, "  [CRAFT] Anda butuh 3x Lempeng Kuningan dan 3x Bubuk Mesiu!");
                    return 1;
                }
                Inventory_RemoveItem(playerid, ITEM_BRASS_PLATE, 3);
                Inventory_RemoveItem(playerid, ITEM_GUNPOWDER, 3);
                Inventory_AddItem(playerid, ITEM_AMMO_DEAGLE, 35);
                SyncPlayerWeaponsFromInventory(playerid);
                SendClientMessage(playerid, COL_GREEN, "  [CRAFT] Sukses mencetak {00EEFF}35 butir Peluru .50 AE{FFFFFF} (masuk ke tas & senjata)!");
                format(rpMsg, sizeof(rpMsg), "* %s mencetak peluru kaliber berat .50 Desert Eagle.", charname);
            } else if (listitem == 2) { // 12 Gauge (2 Kuningan, 3 Mesiu -> 25 Peluru)
                if (Inventory_GetItemCount(playerid, ITEM_BRASS_PLATE) < 2 || Inventory_GetItemCount(playerid, ITEM_GUNPOWDER) < 3) {
                    SendClientMessage(playerid, COL_RED, "  [CRAFT] Anda butuh 2x Lempeng Kuningan dan 3x Bubuk Mesiu!");
                    return 1;
                }
                Inventory_RemoveItem(playerid, ITEM_BRASS_PLATE, 2);
                Inventory_RemoveItem(playerid, ITEM_GUNPOWDER, 3);
                Inventory_AddItem(playerid, ITEM_AMMO_SHOTGUN, 25);
                SyncPlayerWeaponsFromInventory(playerid);
                SendClientMessage(playerid, COL_GREEN, "  [CRAFT] Sukses mencetak {00EEFF}25 butir Peluru 12 Gauge{FFFFFF} (masuk ke tas & senjata)!");
                format(rpMsg, sizeof(rpMsg), "* %s mengisi bubuk mesiu dan proyektil timah ke selongsong shotgun.", charname);
            } else if (listitem == 3) { // 7.62mm (4 Kuningan, 4 Mesiu -> 60 Peluru)
                if (Inventory_GetItemCount(playerid, ITEM_BRASS_PLATE) < 4 || Inventory_GetItemCount(playerid, ITEM_GUNPOWDER) < 4) {
                    SendClientMessage(playerid, COL_RED, "  [CRAFT] Anda butuh 4x Lempeng Kuningan dan 4x Bubuk Mesiu!");
                    return 1;
                }
                Inventory_RemoveItem(playerid, ITEM_BRASS_PLATE, 4);
                Inventory_RemoveItem(playerid, ITEM_GUNPOWDER, 4);
                Inventory_AddItem(playerid, ITEM_AMMO_RIFLE, 60);
                SyncPlayerWeaponsFromInventory(playerid);
                SendClientMessage(playerid, COL_GREEN, "  [CRAFT] Sukses mencetak {00EEFF}60 butir Peluru 7.62mm{FFFFFF} (masuk ke tas & senjata)!");
                format(rpMsg, sizeof(rpMsg), "* %s merakit amunisi peluru kaliber 7.62mm AK-47.", charname);
            }
        }
        else if (cat == 4) { // Perlengkapan: Rompi Kevlar (10 Batang Baja)
            if (Inventory_GetItemCount(playerid, ITEM_STEEL_BAR) < 10) {
                SendClientMessage(playerid, COL_RED, "  [CRAFT] Anda membutuhkan minimal 10x Batang Baja untuk merakit Rompi Kevlar!");
                return 1;
            }
            Inventory_RemoveItem(playerid, ITEM_STEEL_BAR, 10);
            Inventory_AddItem(playerid, ITEM_KEVLAR_VEST, 1);
            SendClientMessage(playerid, COL_GREEN, "  [CRAFT] Sukses merakit {00EEFF}1x Rompi Kevlar (Body Armor){FFFFFF}!");
            format(rpMsg, sizeof(rpMsg), "* %s menempa pelat baja anti-peluru dan menyatukannya menjadi rompi pelindung tubuh.", charname);
        }

        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
        GameTextForPlayer(playerid, "~g~Rakit Selesai!", 2500, 3);
        DoProximitySay(playerid, rpMsg, DIST_RP, COL_PURPLE, false);
        return 1;
    }
    return 0;
}

CMD:craft(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    if (!IsPlayerInRangeOfPoint(playerid, 3.5, CRAFT_BENCH_X, CRAFT_BENCH_Y, CRAFT_BENCH_Z)) {
        return SendClientMessage(playerid, COL_RED, "  [!] Anda harus berada di dekat Meja Kerja Rahasia (Flint County Hideout)!");
    }
    ShowCraftingMainMenu(playerid);
    return 1;
}

CMD:rakit(playerid, params[]) {
    return cmd_craft(playerid, params);
}
