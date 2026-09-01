// ============================================================
//  SantaraBaru Roleplay - Entry Point Gamemode
//  Engine: open.mp v1.2.0 (Linux x86_64)
// ============================================================

#define SAMP_COMPAT
#include <open.mp>
#include <sampvoice>
#include <zcmd>
#include <sscanf2>

//    Modul Core (Definisi, Player Data & Utilitas)             
#include "modules/core/defines.inc"
#include "modules/core/player_data.inc"
#include "modules/core/utils.inc"

//    Modul Database                                           
#include "modules/database/db_init.inc"

//    Modul Voice & Chat Roleplay                              
#include "modules/systems/voice.inc"
#include "modules/systems/chat_rp.inc"

//    Modul UI & TextDraws                                     
#include "modules/ui/hud_money.inc"
#include "modules/ui/ktp_card.inc"
#include "modules/ui/char_create_ui.inc"
#include "modules/ui/char_select_ui.inc"
#include "modules/ui/spawn_selector.inc"
#include "modules/ui/skin_selector.inc"
#include "modules/ui/dealership.inc"
#include "modules/ui/garage_ui.inc"

//    Modul Database Pemain & Sistem Roleplay                  
#include "modules/database/db_players.inc"
#include "modules/systems/character.inc"
#include "modules/systems/account.inc"
#include "modules/systems/buildings.inc"
#include "modules/systems/twentyfour_seven.inc"
#include "modules/systems/driving_school.inc"
#include "modules/systems/ownership.inc"
#include "modules/ui/speedometer.inc"
#include "modules/ui/refuel_ui.inc"
#include "modules/systems/inventory.inc"
#include "modules/ui/inventory_ui.inc"
#include "modules/ui/trunk_ui.inc"
#include "modules/ui/dokumen_ui.inc"
#include "modules/systems/armor_visual.inc"
#include "modules/systems/mining.inc"
#include "modules/systems/smelting.inc"
#include "modules/systems/crafting.inc"
#include "modules/systems/jobcenter.inc"

//    Modul Perintah (Commands)                                
#include "modules/commands/cmd_general.inc"
#include "modules/commands/cmd_rp.inc"
#include "modules/commands/cmd_identity.inc"
#include "modules/commands/cmd_admin.inc"

// ============================================================
//  ENTRY POINT & CALLBACKS
// ============================================================

main() {
    print("================================================");
    print("   SantaraBaru Roleplay Gamemode Loaded");
    print("   Engine: open.mp (Linux Docker)");
    print("================================================");
}

forward Timer_PlayTime();
public Timer_PlayTime() {
    for (new i = 0; i < MAX_PLAYERS; i++) {
        if (!IsPlayerConnected(i)) continue;
        if (!gPlayerData[i][p_LoggedIn] || !gPlayerData[i][p_Spawned]) continue;
        gPlayerData[i][p_PlayTime]++;

        // 1. Penurunan Kebutuhan Hidup (Lapar: ~0.8%/mnt, Haus: ~1.2%/mnt)
        if (gPlayerData[i][p_Hunger] > 0.0) {
            gPlayerData[i][p_Hunger] -= 0.8;
            if (gPlayerData[i][p_Hunger] < 0.0) gPlayerData[i][p_Hunger] = 0.0;
        }
        if (gPlayerData[i][p_Thirst] > 0.0) {
            gPlayerData[i][p_Thirst] -= 1.2;
            if (gPlayerData[i][p_Thirst] < 0.0) gPlayerData[i][p_Thirst] = 0.0;
        }

        // 2. Efek Kelaparan & Dehidrasi Akut (Drain Darah / HP)
        new Float:curHp;
        GetPlayerHealth(i, curHp);

        if (gPlayerData[i][p_Hunger] <= 0.0) {
            curHp -= 3.0;
            SendClientMessage(i, COL_RED, "  * [!] Perut Anda terasa sangat lapar dan perih! Anda mulai kehilangan darah.");
        }
        if (gPlayerData[i][p_Thirst] <= 0.0) {
            curHp -= 4.0;
            SendClientMessage(i, COL_RED, "  * [!] Anda dehidrasi parah dan tenggorokan sangat kering! Anda mulai kehilangan darah.");
        }

        if (curHp < 0.0) curHp = 0.0;
        SetPlayerHealth(i, curHp);

        // 3. Update HUD Status
        UpdatePlayerMoneyHUD(i);
    }
    return 1;
}

public OnGameModeInit() {
    SetGameModeText(SERVER_NAME);
    ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);
    ShowNameTags(true);
    SetNameTagDrawDistance(DIST_RP);
    DisableInteriorEnterExits();
    EnableStuntBonusForAll(false);
    UsePlayerPedAnims();

    AddPlayerClass(0, SPAWN_BUS_X, SPAWN_BUS_Y, SPAWN_BUS_Z, SPAWN_BUS_A, 0, 0, 0, 0, 0, 0);

    DB_InitDatabase();
    Inventory_LoadItemsFromDB();
    Dealership_LoadDataFromDB();
    InitVoiceSystem();
    InitBuildings();
    InitTwentyFourSeven();

    //    Coutt and Schutz Auto Showroom (Los Santos)
    Create3DTextLabel("{00EEFF}[ COUTT AND SCHUTZ SHOWROOM ]\n{FFFFFF}Koleksi Mobil Sport, Sedan, SUV dan Motor\n{FFFF00}Tekan [ H ] untuk Beli Kendaraan",
        0xFFFFFFFF, DEALER_RODEO_X, DEALER_RODEO_Y, DEALER_RODEO_Z + 0.8, 20.0, 0, true);
    CreatePickup(1274, 1, DEALER_RODEO_X, DEALER_RODEO_Y, DEALER_RODEO_Z, 0);

    //    Inisialisasi 3D Text Label Pom Bensin
    for (new gs = 0; gs < MAX_GAS_STATIONS; gs++) {
        Create3DTextLabel("{F1C40F}[ POM BENSIN ]\n{FFFFFF}Harga: {2ECC71}Rp 15.950{FFFFFF} / Liter\n{FFFF00}Dekati dispenser & Tekan [ H ] untuk Isi Bensin",
            0xFFFFFFFF, gGasStations[gs][gs_X], gGasStations[gs][gs_Y], gGasStations[gs][gs_Z] + 0.8, 20.0, 0, true);
    }

    //    Inisialisasi Jaringan Garasi Publik & Kantor Asuransi
    InitPublicGarages();
    InitInsuranceCenter();
    SyncVehiclesOnServerStart();

    //    Inisialisasi Rantai Pasok (Tambang, Smelter, Crafting, Job Center)
    InitMiningSystem();
    InitSmelterSystem();
    InitCraftingSystem();
    InitJobCenterSystem();

    gPlayTimeTimer = SetTimer("Timer_PlayTime", 60000, true);
    SetTimer("Timer_VehicleFuel", 1000, true);
    print("[SantaraBaru] Gamemode siap dimainkan!");
    return 1;
}

public OnGameModeExit() {
    KillTimer(gPlayTimeTimer);
    for (new i = 0; i < MAX_PLAYERS; i++) {
        if (IsPlayerConnected(i)) {
            DoSavePlayer(i);
        }
    }
    DB_CloseDatabase();
    return 1;
}

forward Timer_AuthFallback(playerid);
public Timer_AuthFallback(playerid) {
    if (IsPlayerConnected(playerid) && !gPlayerData[playerid][p_AuthLoaded]) {
        ProceedPlayerAuth(playerid);
    }
    return 1;
}

forward Timer_VehicleFuel();
public Timer_VehicleFuel() {
    for (new i = 1; i < MAX_VEHICLES; i++) {
        if (GetVehicleModel(i) > 0) {
            new engine, lights, alarm, doors, bonnet, boot, objective;
            GetVehicleParamsEx(i, engine, lights, alarm, doors, bonnet, boot, objective);
            if (engine == 1) {
                // Consume 0.05 liter per second
                gVehicleFuel[i] -= 0.05;
                if (gVehicleFuel[i] <= 0.0) {
                    gVehicleFuel[i] = 0.0;
                    SetVehicleParamsEx(i, 0, lights, alarm, doors, bonnet, boot, objective);
                    
                    for (new p = 0; p < MAX_PLAYERS; p++) {
                        if (IsPlayerConnected(p) && GetPlayerState(p) == PLAYER_STATE_DRIVER && GetPlayerVehicleID(p) == i) {
                            SendClientMessage(p, 0xFF4040FF, "  [Kendaraan] Mesin mati mendadak karena kehabisan bensin!");
                            PlayerPlaySound(p, 1084, 0.0, 0.0, 0.0);
                        }
                    }
                }
            }
        }
    }
    return 1;
}


stock ProceedPlayerAuth(playerid) {
    if (!IsPlayerConnected(playerid)) return 0;
    if (gPlayerData[playerid][p_AuthLoaded]) return 1;
    gPlayerData[playerid][p_AuthLoaded] = true;
    gPlayerData[playerid][p_FinishedDownload] = true;

    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
    SendClientMessage(playerid, COL_GREEN, "  [Asset Server] [OK] Seluruh asset & model kustom siap digunakan.");

    new query[256];
    format(query, sizeof(query),
        "SELECT `id`, `admin_level` FROM `accounts` WHERE `username`='%s' LIMIT 1",
        gPlayerData[playerid][p_Username]);

    new DBResult:res = DB_ExecuteQuery(gDB, query);
    if (res && DB_GetRowCount(res) > 0) {
        gPlayerData[playerid][p_AccountID]  = DB_GetFieldIntByName(res, "id");
        gPlayerData[playerid][p_AdminLevel] = DB_GetFieldIntByName(res, "admin_level");
        gPlayerData[playerid][p_Registered] = true;
        DB_FreeResultSet(res);
        ShowLoginDialog(playerid, "");
    } else {
        if (res) DB_FreeResultSet(res);
        gPlayerData[playerid][p_Registered] = false;
        ShowRegisterDialog(playerid, "");
    }
    return 1;
}

public OnPlayerConnect(playerid) {
    ResetPlayerData(playerid);
    GetPlayerName(playerid, gPlayerData[playerid][p_Username], MAX_PLAYER_NAME + 1);
    TogglePlayerSpectating(playerid, true);

    // Set tampilan kamera sinematik San Fierro saat proses download & loading
    SetPlayerCameraPos(playerid, -1771.5, 960.0, 75.0);
    SetPlayerCameraLookAt(playerid, -1982.0, 137.0, 27.68);

    GameTextForPlayer(playerid, "~y~Santara Roleplay~n~~w~Memeriksa Asset & Menghubungkan...", 4000, 3);
    SendClientMessage(playerid, COL_CYAN, "  [Santara RP] Selamat datang! Sedang memeriksa & memuat asset kustom server...");

    // Fallback timer (2.5 detik) jika client lama tidak mentrigger OnPlayerFinishedDownloading
    SetTimerEx("Timer_AuthFallback", 2500, false, "i", playerid);
    return 1;
}

public OnPlayerRequestDownload(playerid, type, crc) {
    #pragma unused crc
    if (type == DOWNLOAD_REQUEST_MODEL_FILE || type == DOWNLOAD_REQUEST_TEXTURE_FILE) {
        return 1;
    }
    return 1;
}

public OnPlayerFinishedDownloading(playerid, virtualworld) {
    #pragma unused virtualworld
    ProceedPlayerAuth(playerid);
    return 1;
}

public OnPlayerDisconnect(playerid, reason) {
    #pragma unused reason
    DoSavePlayer(playerid);
    DestroyPlayerActiveVehicle(playerid);
    if (gPlayerData[playerid][p_InDrivingTest]) {
        CancelDrivingTest(playerid, "Pemain terputus dari server");
    }
    CloseDokumenPanelUI(playerid);
    DestroyPlayerDokumenTextDraws(playerid);
    CloseDealership(playerid);
    CloseGarageUI(playerid);
    CloseRefuelUI(playerid);
    HideInventoryUI(playerid);
    HideTrunkUI(playerid);
    DestroyPlayerTrunkTextDraws(playerid);
    DestroyVoiceStream(playerid);
    DestroyPlayerMoneyHUD(playerid);
    HideSpeedometer(playerid);
    CloseCharCreationUI(playerid);
    DestroyPlayerCharFormTextDraws(playerid);
    DestroyPlayerSpawnTextDraws(playerid);
    DestroyPlayerSkinTextDraws(playerid);
    DestroyPlayerKTPTextDraws(playerid);
    RemovePlayerAllVisualAttachments(playerid);
    ResetPlayerData(playerid);
    return 1;
}

public OnPlayerRequestClass(playerid, classid) {
    #pragma unused classid
    // Jika karakter sudah login dan punya ID aktif, langsung spawn
    // Tapi JANGAN spawn jika spawn selector sedang terbuka (p_SelectingSpawn)
    if (gPlayerData[playerid][p_LoggedIn] && gPlayerData[playerid][p_CharID] > 0) {
        if (gPlayerData[playerid][p_SelectingSpawn]) return 1; // Tunggu — spawn selector sedang aktif
        SetSpawnInfo(playerid, 0, gPlayerData[playerid][p_Skin],
            gPlayerData[playerid][p_X], gPlayerData[playerid][p_Y], gPlayerData[playerid][p_Z],
            gPlayerData[playerid][p_A], 0, 0, 0, 0, 0, 0);
        SpawnPlayer(playerid);
        return 0;
    }
    return 1;
}

public OnPlayerSpawn(playerid) {
    gPlayerData[playerid][p_Spawned] = true;
    gPlayerData[playerid][p_LastHoldingWeapon] = -1;

    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
    SetPlayerSkin(playerid, gPlayerData[playerid][p_Skin]);
    SetPlayerPos(playerid, gPlayerData[playerid][p_X], gPlayerData[playerid][p_Y], gPlayerData[playerid][p_Z]);
    SetPlayerFacingAngle(playerid, gPlayerData[playerid][p_A]);
    ResetPlayerMoney(playerid);
    SetPlayerScore(playerid, gPlayerData[playerid][p_Score]);

    if (gPlayerData[playerid][p_SelectingSkin]) {
        SetPlayerFrontCamera(playerid);
        SetTimerEx("Timer_FixSkinCamera", 150, false, "i", playerid);
    } else {
        CancelSelectTextDraw(playerid);
        TogglePlayerControllable(playerid, true);
        SetCameraBehindPlayer(playerid);
        SetPlayerHealth(playerid, gPlayerData[playerid][p_Health]);
        SetPlayerArmour(playerid, gPlayerData[playerid][p_Armour]);
        Inventory_LoadPlayerItems(playerid);
        SyncPlayerWeaponsFromInventory(playerid);
        CreatePlayerMoneyHUD(playerid);
        UpdatePlayerMoneyHUD(playerid);
        ShowPlayerMoneyHUD(playerid);
        UpdatePlayerArmorVisual(playerid);
        UpdatePlayerWeaponHolsterVisual(playerid);

        if (gVoiceEnabled) {
            SetupVoiceStream(playerid);
            SendClientMessage(playerid, COL_TEAL,
                "  [Voice] Voice Chat aktif (radius 20m). Bicara lewat mikrofon HP/PC.");
        }

        // Pasang Map Icons Legenda Peta (Balai Kota, Rodeo Dealer, Asuransi, & 10 Garasi Kota)
        SetupPlayerMapIcons(playerid);

        // Munculkan kendaraan pribadi pemain yang terparkir di luar
        LoadPlayerOutsideVehicles(playerid);

        SendClientMessage(playerid, COL_GREEN, "  Selamat datang! Ketik {00EEFF}/help{00CC66} untuk melihat perintah atau {00EEFF}/gps{00CC66} untuk peta.");
    }
    return 1;
}

public OnPlayerUpdate(playerid) {
    if (!gPlayerData[playerid][p_LoggedIn] || !gPlayerData[playerid][p_Spawned]) return 1;

    // 1. Deteksi perubahan nilai Armor untuk visual Rompi Kevlar 3D di badan
    new Float:curArm;
    GetPlayerArmour(playerid, curArm);
    if (curArm != gPlayerData[playerid][p_LastArmour]) {
        gPlayerData[playerid][p_LastArmour] = curArm;
        UpdatePlayerArmorVisual(playerid);
    }

    // 2. Deteksi pergantian senjata di tangan untuk visual sarung pistol & laras panjang di tubuh
    new curWep = GetPlayerWeapon(playerid);
    if (curWep != gPlayerData[playerid][p_LastHoldingWeapon]) {
        gPlayerData[playerid][p_LastHoldingWeapon] = curWep;
        UpdatePlayerWeaponHolsterVisual(playerid);
    }
    return 1;
}

public OnPlayerWeaponShot(playerid, WEAPON:weaponid, BULLET_HIT_TYPE:hittype, hitid, Float:fX, Float:fY, Float:fZ) {
    #pragma unused hittype, hitid, fX, fY, fZ
    if (!HandlePlayerWeaponShot(playerid, _:weaponid)) {
        return 0;
    }
    return 1;
}

public OnPlayerText(playerid, text[]) {
    if (!gPlayerData[playerid][p_LoggedIn] || !gPlayerData[playerid][p_Spawned] || gPlayerData[playerid][p_SelectingSkin]) {
        return 0;
    }
    DoProximitySay(playerid, text, DIST_VOICE, COL_WHITE, false);
    return 0;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
    if (HandleAccountDialog(playerid, dialogid, response, listitem, inputtext)) return 1;
    if (HandleCharacterDialog(playerid, dialogid, response, listitem, inputtext)) return 1;
    if (HandleInventoryDialog(playerid, dialogid, response, listitem, inputtext)) return 1;
    if (HandleTrunkDialog(playerid, dialogid, response, inputtext)) return 1;
    if (HandleDokumenUIDialog(playerid, dialogid, response, inputtext)) return 1;
    if (HandleDrivingSchoolDialog(playerid, dialogid, response, listitem)) return 1;
    if (HandleDealershipDialog(playerid, dialogid, response, listitem)) return 1;
    if (HandleVehicleMenuDialog(playerid, dialogid, response, listitem)) return 1;
    if (HandleInsuranceDialog(playerid, dialogid, response, listitem)) return 1;
    if (HandleGPSDialog(playerid, dialogid, response, listitem)) return 1;
    if (HandleBurgerShotDialog(playerid, dialogid, response, listitem, inputtext)) return 1;
    if (HandleTwentyFourSevenDialog(playerid, dialogid, response, listitem, inputtext)) return 1;
    if (HandleSmelterDialog(playerid, dialogid, response, listitem)) return 1;
    if (HandleCraftingDialog(playerid, dialogid, response, listitem)) return 1;
    if (HandleJobCenterDialog(playerid, dialogid, response, listitem)) return 1;
    if (HandleAdminTeleportDialog(playerid, dialogid, response, listitem)) return 1;
    return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid) {
    //    REFUEL / ISI BENSIN UI
    if (gPlayerInRefuelUI[playerid]) {
        if (HandleRefuelUIClick(playerid, playertextid)) return 1;
    }

    //    0. CUSTOM CHARACTER CREATION FORM MODAL
    if (gPlayerData[playerid][p_InCharForm]) {
        if (HandleCharCreationClick(playerid, playertextid)) return 1;
    }

    //    0.5 3D CHARACTER SELECTION UI
    if (gPlayerData[playerid][p_SelectingChar3D]) {
        if (HandleCharSelectClick(playerid, playertextid)) return 1;
    }

    //    1. LIVE EAGLE-EYE SPAWN SELECTOR   
    if (gPlayerData[playerid][p_SelectingSpawn]) {
        new total = gPlayerData[playerid][p_IsNewCharacter] ? PUBLIC_SPAWN_COUNT : (PUBLIC_SPAWN_COUNT + 1);

        // Panah Kiri (<<)
        if (playertextid == TD_SpawnPrev[playerid]) {
            gPlayerData[playerid][p_SpawnIndex]--;
            if (gPlayerData[playerid][p_SpawnIndex] < 0) {
                gPlayerData[playerid][p_SpawnIndex] = total - 1;
            }
            UpdateSpawnSelectorUI(playerid);
            UpdateSpawnSelectorCamera(playerid);
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
            return 1;
        }

        // Panah Kanan (>>)
        if (playertextid == TD_SpawnNext[playerid]) {
            gPlayerData[playerid][p_SpawnIndex]++;
            if (gPlayerData[playerid][p_SpawnIndex] >= total) {
                gPlayerData[playerid][p_SpawnIndex] = 0;
            }
            UpdateSpawnSelectorUI(playerid);
            UpdateSpawnSelectorCamera(playerid);
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
            return 1;
        }

        // Tombol SPAWN DI SINI (Hijau)
        if (playertextid == TD_SpawnConfirm[playerid]) {
            new idx = gPlayerData[playerid][p_SpawnIndex];

            if (gPlayerData[playerid][p_IsNewCharacter]) {
                gPlayerData[playerid][p_X] = gPublicSpawns[idx][s_SpawnX];
                gPlayerData[playerid][p_Y] = gPublicSpawns[idx][s_SpawnY];
                gPlayerData[playerid][p_Z] = gPublicSpawns[idx][s_SpawnZ];
                gPlayerData[playerid][p_A] = gPublicSpawns[idx][s_SpawnA];

                new defaultSkin = (gPlayerData[playerid][p_Gender] == 2) ? 12 : 0;

                new insertQuery[512];
                format(insertQuery, sizeof(insertQuery),
                    "INSERT INTO `characters` (`account_id`, `char_name`, `birthplace`, `birthdate`, `gender`, `skin_id`, `x`, `y`, `z`, `angle`, `score`, `cash`, `is_active`) VALUES (%d, '%s', '%s', '%s', %d, %d, %.4f, %.4f, %.4f, %.4f, 1, 500, 1)",
                    gPlayerData[playerid][p_AccountID], gPlayerData[playerid][p_CharName], gPlayerData[playerid][p_BirthPlace], gPlayerData[playerid][p_BirthDate], gPlayerData[playerid][p_Gender],
                    defaultSkin, gPlayerData[playerid][p_X], gPlayerData[playerid][p_Y], gPlayerData[playerid][p_Z], gPlayerData[playerid][p_A]);
                DB_FreeResultSet(DB_ExecuteQuery(gDB, insertQuery));

                format(insertQuery, sizeof(insertQuery), "SELECT `id` FROM `characters` WHERE `char_name`='%s' AND `is_active`=1 LIMIT 1", gPlayerData[playerid][p_CharName]);
                new DBResult:resNew = DB_ExecuteQuery(gDB, insertQuery);
                if (resNew && DB_GetRowCount(resNew) > 0) {
                    gPlayerData[playerid][p_CharID] = DB_GetFieldIntByName(resNew, "id");
                }
                if (resNew) DB_FreeResultSet(resNew);

                gPlayerData[playerid][p_Skin]   = defaultSkin;
                gPlayerData[playerid][p_Score]  = 1;
                gPlayerData[playerid][p_Cash]   = 500;

                PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
                CloseSpawnSelection(playerid, false);

                gPlayerData[playerid][p_SelectingSkin] = true;
                TogglePlayerSpectating(playerid, false);
                SetSpawnInfo(playerid, 0, defaultSkin,
                    gPlayerData[playerid][p_X], gPlayerData[playerid][p_Y], gPlayerData[playerid][p_Z],
                    gPlayerData[playerid][p_A], 0, 0, 0, 0, 0, 0);
                SpawnPlayer(playerid);
                OpenSkinSelection(playerid, true);
            } else {
                if (idx > 0) {
                    new pIdx = idx - 1;
                    gPlayerData[playerid][p_X] = gPublicSpawns[pIdx][s_SpawnX];
                    gPlayerData[playerid][p_Y] = gPublicSpawns[pIdx][s_SpawnY];
                    gPlayerData[playerid][p_Z] = gPublicSpawns[pIdx][s_SpawnZ];
                    gPlayerData[playerid][p_A] = gPublicSpawns[pIdx][s_SpawnA];
                }
                PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
                CloseSpawnSelection(playerid, false);
                TogglePlayerSpectating(playerid, false);
                SetSpawnInfo(playerid, 0, gPlayerData[playerid][p_Skin],
                    gPlayerData[playerid][p_X], gPlayerData[playerid][p_Y], gPlayerData[playerid][p_Z],
                    gPlayerData[playerid][p_A], 0, 0, 0, 0, 0, 0);
                SpawnPlayer(playerid);
            }
            return 1;
        }

        // Tombol KEMBALI (Merah)
        if (playertextid == TD_SpawnCancel[playerid]) {
            PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
            if (gPlayerData[playerid][p_IsNewCharacter]) {
                CloseSpawnSelection(playerid, false);
                OpenCharCreationUI(playerid);
            } else {
                CloseSpawnSelection(playerid, true);
                ShowCharacterSelection(playerid);
            }
            return 1;
        }
        return 1;
    }

    //    2. LIVE 3D SKIN SELECTOR   
    if (gPlayerData[playerid][p_SelectingSkin]) {
        // 1. Tombol [X] Merah atau BATAL
        if (playertextid == TD_SkinCloseBtn[playerid] || playertextid == TD_SkinCancel[playerid]) {
            if (gPlayerData[playerid][p_IsNewCharacter]) {
                SendClientMessage(playerid, COL_RED, "    Anda harus memilih skin untuk menyelesaikan pembuatan karakter.");
                return 1;
            }
            SetPlayerSkin(playerid, gPlayerData[playerid][p_OriginalSkin]);
            PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
            CloseSkinSelection(playerid, false);
            SendClientMessage(playerid, COL_GREY, "  * Pemilihan skin dibatalkan.");
            return 1;
        }

        // 2. Tombol < SEBELUM
        if (playertextid == TD_SkinPrev[playerid]) {
            gPlayerData[playerid][p_SkinIndex]--;
            if (gPlayerData[playerid][p_SkinIndex] < 0) {
                gPlayerData[playerid][p_SkinIndex] = SKIN_COUNT - 1;
            }
            SetPlayerSkin(playerid, gSkins[gPlayerData[playerid][p_SkinIndex]]);
            UpdateSkinSelectorUI(playerid);
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
            return 1;
        }

        // 3. Tombol SELANJUTNYA >
        if (playertextid == TD_SkinNext[playerid]) {
            gPlayerData[playerid][p_SkinIndex]++;
            if (gPlayerData[playerid][p_SkinIndex] >= SKIN_COUNT) {
                gPlayerData[playerid][p_SkinIndex] = 0;
            }
            SetPlayerSkin(playerid, gSkins[gPlayerData[playerid][p_SkinIndex]]);
            UpdateSkinSelectorUI(playerid);
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
            return 1;
        }

        // 4. Tombol [ GUNAKAN ]
        if (playertextid == TD_SkinSave[playerid]) {
            gPlayerData[playerid][p_Skin] = gSkins[gPlayerData[playerid][p_SkinIndex]];
            
            new query[128];
            format(query, sizeof(query), "UPDATE `characters` SET `skin_id`=%d WHERE `id`=%d",
                gPlayerData[playerid][p_Skin], gPlayerData[playerid][p_CharID]);
            DB_FreeResultSet(DB_ExecuteQuery(gDB, query));

            PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
            CloseSkinSelection(playerid, true);

            new msg[128];
            format(msg, sizeof(msg), "  [OK] Penampilan karakter {FFFF00}%s {00CC66}berhasil disimpan! (Skin ID: %d)",
                gSkinNames[gPlayerData[playerid][p_SkinIndex]], gPlayerData[playerid][p_Skin]);
            SendClientMessage(playerid, COL_GREEN, msg);
            return 1;
        }

        return 1;
    }

    //    3. SISTEM e-KTP CARD UI   
    if (gShowingKTP[playerid]) {
        if (playertextid == TD_KTP_Close[playerid]) {
            HidePlayerKTPCard(playerid);
            return 1;
        }
        return 1;
    }

    //    4. LIVE 3D RODEO DEALERSHIP   
    if (gPlayerData[playerid][p_InDealership]) {
        if (HandleDealershipClick(playerid, playertextid)) return 1;
    }

    //    5. LIVE 3D GARASI PUBLIK KOTA   
    if (gPlayerData[playerid][p_InGarageUI]) {
        if (HandleGarageClick(playerid, playertextid)) return 1;
    }

    //    6. INTERACTIVE TEXTDRAW INVENTORY UI
    if (gPlayerData[playerid][p_InInventoryUI]) {
        if (HandleInventoryClick(playerid, playertextid)) return 1;
    }

    //    7. 2-TAB INTERACTIVE VEHICLE TRUNK UI
    if (gPlayerData[playerid][p_InTrunkUI]) {
        if (HandleTrunkClick(playerid, playertextid)) return 1;
    }

    //    8. INTERACTIVE TEXTDRAW SIM PANEL & CARD UI
    if (gShowingSIMCard[playerid] || gPlayerData[playerid][p_InDokumenUI]) {
        if (HandleDokumenUIClick(playerid, playertextid)) return 1;
    }

    //    9. TOUCHPAD KONTROL KENDARAAN (Clickable TextDraw)
    if (gPlayerInVehicleHUD[playerid]) {
        if (playertextid == TD_SpeedBtnEngine[playerid]) {
            TogglePlayerVehicleEngine(playerid);
            CancelSelectTextDraw(playerid);
            return 1;
        }
        if (playertextid == TD_SpeedBtnLock[playerid]) {
            TogglePlayerVehicleLock(playerid);
            CancelSelectTextDraw(playerid);
            return 1;
        }
        if (playertextid == TD_SpeedBtnLight[playerid]) {
            TogglePlayerVehicleLight(playerid);
            CancelSelectTextDraw(playerid);
            return 1;
        }
        if (playertextid == TD_SpeedBtnSeatbelt[playerid]) {
            TogglePlayerVehicleSeatbelt(playerid);
            CancelSelectTextDraw(playerid);
            return 1;
        }
    }

    return 0;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid) {
    if (clickedid == Text:INVALID_TEXT_DRAW) {
        if (gPlayerInRefuelUI[playerid]) {
            CloseRefuelUI(playerid);
            return 1;
        }
        if (gShowingKTP[playerid]) {
            HidePlayerKTPCard(playerid);
            return 1;
        }
        if (gShowingSIMCard[playerid]) {
            HidePlayerSIMCard(playerid);
            return 1;
        }
        if (gPlayerData[playerid][p_SelectingChar3D]) {
            SelectTextDraw(playerid, 0x5814EEFF);
            return 1;
        }
        if (gPlayerData[playerid][p_InCharForm]) {
            CloseCharCreationUI(playerid);
            ShowCharacterSelection(playerid);
            return 1;
        }
        if (gPlayerData[playerid][p_SelectingSpawn]) {
            if (gPlayerData[playerid][p_IsNewCharacter]) {
                CloseSpawnSelection(playerid, false);
                OpenCharCreationUI(playerid);
            } else {
                CloseSpawnSelection(playerid, true);
                ShowCharacterSelection(playerid);
            }
            return 1;
        }
        if (gPlayerData[playerid][p_SelectingSkin]) {
            if (gPlayerData[playerid][p_IsNewCharacter]) {
                SelectTextDraw(playerid, COLOR_SKIN_PURPLE);
                SendClientMessage(playerid, COL_YELLOW, "  * Tekan tombol [ Gunakan ] untuk mengonfirmasi penampilan karakter Anda.");
                return 1;
            }
            SetPlayerSkin(playerid, gPlayerData[playerid][p_OriginalSkin]);
            CloseSkinSelection(playerid, false);
            SendClientMessage(playerid, COL_GREY, "  * Pemilihan skin dibatalkan.");
            return 1;
        }
        if (gPlayerData[playerid][p_InDealership]) {
            CloseDealership(playerid);
            return 1;
        }
        if (gPlayerData[playerid][p_InGarageUI]) {
            CloseGarageUI(playerid);
            return 1;
        }
        if (gPlayerData[playerid][p_InInventoryUI]) {
            HideInventoryUI(playerid);
            return 1;
        }
        if (gPlayerData[playerid][p_InTrunkUI]) {
            HideTrunkUI(playerid);
            return 1;
        }
        if (gPlayerData[playerid][p_InDokumenUI]) {
            CloseDokumenPanelUI(playerid);
            return 1;
        }
    }
    return 0;
}

public OnPlayerStateChange(playerid, PLAYER_STATE:newstate, PLAYER_STATE:oldstate) {
    if (newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER) {
        gPlayerData[playerid][p_Seatbelt] = false;
        gPlayerData[playerid][p_LastSpeed] = 0.0;
        ShowSpeedometer(playerid);
    } else if (oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER) {
        gPlayerData[playerid][p_Seatbelt] = false;
        HideSpeedometer(playerid);
    }

    if (oldstate == PLAYER_STATE_DRIVER && gPlayerData[playerid][p_InDrivingTest]) {
        CancelDrivingTest(playerid, "Keluar dari kursi pengemudi saat ujian");
    }
    return 1;
}

public OnPlayerDeath(playerid, killerid, reason) {
    #pragma unused killerid, reason
    HideSpeedometer(playerid);
    RemovePlayerAllVisualAttachments(playerid);
    gPlayerData[playerid][p_Health] = 100.0;
    gPlayerData[playerid][p_Armour] = 0.0;
    if (gPlayerData[playerid][p_InDrivingTest]) {
        CancelDrivingTest(playerid, "Pemain pingsan / mati saat ujian");
    }
    return 1;
}

public OnPlayerKeyStateChange(playerid, KEY:newkeys, KEY:oldkeys) {
    // 1. Interaksi Garasi Kota (Simpan & Ambil Mobil Murni Tombol H / KEY_CTRL_BACK)
    if (newkeys & KEY_CTRL_BACK) {
        for (new g = 0; g < PUBLIC_GARAGE_COUNT; g++) {
            if (IsPlayerInRangeOfPoint(playerid, 7.5, gPublicGarages[g][g_MarkerX], gPublicGarages[g][g_MarkerY], gPublicGarages[g][g_MarkerZ])) {
                if (IsPlayerInAnyVehicle(playerid)) {
                    if (IsPlayerActiveVeh(playerid, GetPlayerVehicleID(playerid))) {
                        StoreVehicleInGarage(playerid, g);
                        return 1;
                    }
                } else {
                    OpenGarageUI(playerid, g);
                    return 1;
                }
            }
        }
    }

    // 2. Interaksi Showroom, Asuransi & Pom Bensin (Tombol H atau F / ENTER saat berjalan kaki)
    if ((newkeys & KEY_CTRL_BACK) || (newkeys & KEY_SECONDARY_ATTACK)) {
        // Cek Pom Bensin / Tangki Dispenser Bensin
        if (!IsPlayerInAnyVehicle(playerid) && IsPlayerNearFuelPump(playerid)) {
            DoPlayerRefuel(playerid);
            return 1;
        }

        // Cek Rodeo Luxury Dealership
        if (IsPlayerInRangeOfPoint(playerid, 3.5, DEALER_RODEO_X, DEALER_RODEO_Y, DEALER_RODEO_Z)) {
            OpenDealership(playerid);
            return 1;
        }

        // Cek Kantor Asuransi Cabang 3 Kota (LS, SF, LV)
        if (IsPlayerNearInsurance(playerid)) {
            ShowInsuranceMenu(playerid);
            return 1;
        }
    }

    // 2. Tombol C di Kendaraan (KEY_CROUCH) - Masuk ke Mode Kursor
    if (newkeys & KEY_CROUCH) {
        if (gPlayerInVehicleHUD[playerid] || IsPlayerInAnyVehicle(playerid)) {
            SelectTextDraw(playerid, 0x00EEFFFF);
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
            return 1;
        }
    }

    // 4. Interaksi Supermarket 24-7 & Gedung Masuk / Keluar / Loket KTP
    if (HandleTwentyFourSevenKeys(playerid, newkeys)) return 1;
    return HandleBuildingKeys(playerid, newkeys, oldkeys);
}

public OnVehicleDeath(vehicleid, killerid) {
    for (new i = 0; i < MAX_PLAYERS; i++) {
        if (IsPlayerConnected(i) && gPlayerData[i][p_InDrivingTest] && gPlayerData[i][p_DrivingTestVehID] == vehicleid) {
            CancelDrivingTest(i, "Kendaraan ujian hancur / meledak");
        }
    }
    OnPlayerVehicleDeath(vehicleid, killerid);
    return 1;
}

public OnRconCommand(cmd[]) {
    if (HandleRconAdminCommand(cmd)) return 1;
    return 0;
}

public OnPlayerEnterCheckpoint(playerid) {
    if (gPlayerData[playerid][p_HasActiveCheckpoint]) {
        ClearGPSWaypoint(playerid);
        PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
        SendClientMessage(playerid, COL_GREEN, "  [GPS] Anda telah sampai di lokasi tujuan navigasi.");
    }
    return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid) {
    if (gPlayerData[playerid][p_InDrivingTest]) {
        HandleDrivingTestRaceCheckpoint(playerid);
        return 1;
    }
    if (gPlayerData[playerid][p_HasActiveCheckpoint]) {
        ClearGPSWaypoint(playerid);
        PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
        SendClientMessage(playerid, COL_GREEN, "  [GPS] Anda telah sampai di lokasi tujuan navigasi.");
    }
    return 1;
}

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart) {
    #pragma unused issuerid, amount, weaponid, bodypart
    UpdatePlayerArmorVisual(playerid);
    return 1;
}

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart) {
    #pragma unused playerid, amount, weaponid, bodypart
    UpdatePlayerArmorVisual(damagedid);
    return 1;
}
