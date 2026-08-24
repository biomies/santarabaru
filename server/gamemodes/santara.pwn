// ============================================================
//  SantaraBaru Roleplay — Entry Point Gamemode
//  Engine: open.mp v1.2.0 (Linux x86_64)
// ============================================================

#define SAMP_COMPAT
#include <open.mp>
#include <sampvoice>
#include <zcmd>
#include <sscanf2>

// ── Modul Core (Definisi, Player Data & Utilitas) ────────────
#include "modules/core/defines.inc"
#include "modules/core/player_data.inc"
#include "modules/core/utils.inc"

// ── Modul Database ──────────────────────────────────────────
#include "modules/database/db_init.inc"

// ── Modul Voice & Chat Roleplay ─────────────────────────────
#include "modules/systems/voice.inc"
#include "modules/systems/chat_rp.inc"

// ── Modul UI & TextDraws ────────────────────────────────────
#include "modules/ui/hud_money.inc"
#include "modules/ui/ktp_card.inc"
#include "modules/ui/spawn_selector.inc"
#include "modules/ui/skin_selector.inc"

// ── Modul Database Pemain & Sistem Roleplay ─────────────────
#include "modules/database/db_players.inc"
#include "modules/systems/character.inc"
#include "modules/systems/account.inc"
#include "modules/systems/buildings.inc"
#include "modules/systems/vehicle.inc"

// ── Modul Perintah (Commands) ───────────────────────────────
#include "modules/commands/cmd_general.inc"
#include "modules/commands/cmd_rp.inc"
#include "modules/commands/cmd_identity.inc"
#include "modules/commands/cmd_vehicle.inc"

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
    InitVoiceSystem();
    InitBuildings();

    gPlayTimeTimer = SetTimer("Timer_PlayTime", 60000, true);
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

public OnPlayerConnect(playerid) {
    ResetPlayerData(playerid);
    GetPlayerName(playerid, gPlayerData[playerid][p_Username], MAX_PLAYER_NAME + 1);
    TogglePlayerSpectating(playerid, true);

    new query[256];
    format(query, sizeof(query),
        "SELECT `id` FROM `accounts` WHERE `username`='%s' LIMIT 1",
        gPlayerData[playerid][p_Username]);

    new DBResult:res = DB_ExecuteQuery(gDB, query);
    if (res && DB_GetRowCount(res) > 0) {
        gPlayerData[playerid][p_AccountID]  = DB_GetFieldIntByName(res, "id");
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

public OnPlayerDisconnect(playerid, reason) {
    #pragma unused reason
    DoSavePlayer(playerid);
    DestroyVoiceStream(playerid);
    DestroyPlayerMoneyHUD(playerid);
    DestroyPlayerSpawnTextDraws(playerid);
    DestroyPlayerSkinTextDraws(playerid);
    DestroyPlayerKTPTextDraws(playerid);
    DestroyPlayerSpawnedVehicle(playerid);
    ResetPlayerData(playerid);
    return 1;
}

public OnPlayerRequestClass(playerid, classid) {
    #pragma unused classid
    // Jika karakter sudah login dan punya ID aktif, langsung spawn
    if (gPlayerData[playerid][p_LoggedIn] && gPlayerData[playerid][p_CharID] > 0) {
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
        TogglePlayerControllable(playerid, true);
        SetCameraBehindPlayer(playerid);
        CreatePlayerMoneyHUD(playerid);
        UpdatePlayerMoneyHUD(playerid);
        ShowPlayerMoneyHUD(playerid);

        if (gVoiceEnabled) {
            SetupVoiceStream(playerid);
            SendClientMessage(playerid, COL_TEAL,
                "  [Voice] Voice Chat aktif (radius 20m). Bicara lewat mikrofon HP/PC.");
        }

        // Map Icon Balai Kota Los Santos di radar (Icon 56: Mayor's Office / City Hall)
        SetPlayerMapIcon(playerid, 1, CITYHALL_EXT_X, CITYHALL_EXT_Y, CITYHALL_EXT_Z, 56, 0, MAPICON_GLOBAL);

        SendClientMessage(playerid, COL_GREEN, "  Selamat datang! Ketik {00EEFF}/help{00CC66} untuk melihat perintah.");
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
    if (HandleVehicleDialog(playerid, dialogid, response, listitem, inputtext)) return 1;
    return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid) {
    // ── 1. LIVE EAGLE-EYE SPAWN SELECTOR ──
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
                CloseSpawnSelection(playerid);

                gPlayerData[playerid][p_SelectingSkin] = true;
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
                CloseSpawnSelection(playerid);
                SpawnPlayer(playerid);
            }
            return 1;
        }

        // Tombol KEMBALI (Merah)
        if (playertextid == TD_SpawnCancel[playerid]) {
            PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
            if (gPlayerData[playerid][p_IsNewCharacter]) {
                CloseSpawnSelection(playerid);
                ShowCharFormDashboard(playerid);
            } else {
                CloseSpawnSelection(playerid);
                ShowCharacterSelection(playerid);
            }
            return 1;
        }
        return 1;
    }

    // ── 2. LIVE 3D SKIN SELECTOR ──
    if (gPlayerData[playerid][p_SelectingSkin]) {
        // 1. Tombol PREVIOUS (<<)
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

        // 2. Tombol NEXT (>>)
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

        // 3. Tombol ACAK / RANDOM
        if (playertextid == TD_SkinRand[playerid]) {
            gPlayerData[playerid][p_SkinIndex] = random(SKIN_COUNT);
            SetPlayerSkin(playerid, gSkins[gPlayerData[playerid][p_SkinIndex]]);
            UpdateSkinSelectorUI(playerid);
            PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
            return 1;
        }

        // 4. Tombol KONFIRMASI / SIMPAN
        if (playertextid == TD_SkinSave[playerid]) {
            gPlayerData[playerid][p_Skin] = gSkins[gPlayerData[playerid][p_SkinIndex]];
            
            new query[128];
            format(query, sizeof(query), "UPDATE `characters` SET `skin_id`=%d WHERE `id`=%d",
                gPlayerData[playerid][p_Skin], gPlayerData[playerid][p_CharID]);
            DB_FreeResultSet(DB_ExecuteQuery(gDB, query));

            PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
            CloseSkinSelection(playerid, true);

            new msg[128];
            format(msg, sizeof(msg), "  ✓ Penampilan karakter {FFFF00}%s {00CC66}berhasil disimpan! (Skin ID: %d)",
                gSkinNames[gPlayerData[playerid][p_SkinIndex]], gPlayerData[playerid][p_Skin]);
            SendClientMessage(playerid, COL_GREEN, msg);
            return 1;
        }

        // 5. Tombol BATAL
        if (playertextid == TD_SkinCancel[playerid]) {
            if (gPlayerData[playerid][p_IsNewCharacter]) {
                SendClientMessage(playerid, COL_RED, "  ✗ Anda harus memilih skin untuk menyelesaikan pembuatan karakter.");
                return 1;
            }
            SetPlayerSkin(playerid, gPlayerData[playerid][p_OriginalSkin]);
            PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
            CloseSkinSelection(playerid, false);
            SendClientMessage(playerid, COL_GREY, "  * Pemilihan skin dibatalkan.");
            return 1;
        }
        return 1;
    }

    // ── 3. SISTEM e-KTP CARD UI ──
    if (gShowingKTP[playerid]) {
        if (playertextid == TD_KTP_Close[playerid]) {
            HidePlayerKTPCard(playerid);
            return 1;
        }
        return 1;
    }

    return 0;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid) {
    if (clickedid == Text:INVALID_TEXT_DRAW) {
        if (gShowingKTP[playerid]) {
            HidePlayerKTPCard(playerid);
            return 1;
        }
        if (gPlayerData[playerid][p_SelectingSpawn]) {
            if (gPlayerData[playerid][p_IsNewCharacter]) {
                CloseSpawnSelection(playerid);
                ShowCharFormDashboard(playerid);
            } else {
                CloseSpawnSelection(playerid);
                ShowCharacterSelection(playerid);
            }
            return 1;
        }
        if (gPlayerData[playerid][p_SelectingSkin]) {
            if (gPlayerData[playerid][p_IsNewCharacter]) {
                SelectTextDraw(playerid, 0xE69958FF);
                SendClientMessage(playerid, COL_YELLOW, "  * Tekan [ ✓ SIMPAN ] untuk mengonfirmasi penampilan karakter Anda.");
                return 1;
            }
            SetPlayerSkin(playerid, gPlayerData[playerid][p_OriginalSkin]);
            CloseSkinSelection(playerid, false);
            SendClientMessage(playerid, COL_GREY, "  * Pemilihan skin dibatalkan.");
            return 1;
        }
    }
    return 0;
}

public OnPlayerKeyStateChange(playerid, KEY:newkeys, KEY:oldkeys) {
    return HandleBuildingKeys(playerid, newkeys, oldkeys);
}
