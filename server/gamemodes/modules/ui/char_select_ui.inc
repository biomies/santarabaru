#if defined _MODULE_CHAR_SELECT_UI_INC
    #endinput
#endif
#define _MODULE_CHAR_SELECT_UI_INC

// ============================================================
//  SantaraBaru Roleplay - 3D Character Selection UI
// ============================================================

#define COLOR_CHARSEL_BG        0x1E1E2EFF  // Dark Indigo Background
#define COLOR_CHARSEL_PURPLE    0x5814EEFF  // Electric Purple Accent & Action
#define COLOR_CHARSEL_SLATE     0x3E3E44EE  // Dark Slate Button

// Variables per player
new PlayerText:TD_CharSel_Bg[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_CharSel_TopBar[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_CharSel_Title[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_CharSel_Name[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_CharSel_Gender[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_CharSel_Prev[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_CharSel_Next[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_CharSel_Play[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_CharSel_Create[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};

new gCharActors[MAX_PLAYERS][MAX_CHARS_PER_ACCOUNT] = { {-1, -1, -1}, ... };
new gCharSelectIndex[MAX_PLAYERS] = 0;
new gCharSelectCount[MAX_PLAYERS] = 0;
new gCharSelectSkins[MAX_PLAYERS][MAX_CHARS_PER_ACCOUNT];
new gCharSelectIDs[MAX_PLAYERS][MAX_CHARS_PER_ACCOUNT];
new gCharSelectNames[MAX_PLAYERS][MAX_CHARS_PER_ACCOUNT][48];
new gCharSelectGenders[MAX_PLAYERS][MAX_CHARS_PER_ACCOUNT];

forward Timer_ApplyCharSelectAnim(playerid);
public Timer_ApplyCharSelectAnim(playerid) {
    if (!IsPlayerConnected(playerid) || !gPlayerData[playerid][p_SelectingChar3D]) return 1;

    for (new i = 0; i < gCharSelectCount[playerid]; i++) {
        if (gCharActors[playerid][i] != -1 && IsValidActor(gCharActors[playerid][i])) {
            if (i == 0) {
                ApplyActorAnimation(gCharActors[playerid][i], "DEALER", "DEALER_IDLE", 4.1, 1, 0, 0, 0, 0);
            } else if (i == 1) {
                ApplyActorAnimation(gCharActors[playerid][i], "COP_AMBIENT", "Coplook_loop", 4.1, 1, 0, 0, 0, 0);
            } else {
                ApplyActorAnimation(gCharActors[playerid][i], "SMOKING", "M_smk_loop", 4.1, 1, 0, 0, 0, 0);
            }
        }
    }
    return 1;
}

stock DestroyPlayerCharSelectUI(playerid) {
    if (TD_CharSel_Bg[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_CharSel_Bg[playerid]); TD_CharSel_Bg[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_CharSel_TopBar[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_CharSel_TopBar[playerid]); TD_CharSel_TopBar[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_CharSel_Title[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_CharSel_Title[playerid]); TD_CharSel_Title[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_CharSel_Name[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_CharSel_Name[playerid]); TD_CharSel_Name[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_CharSel_Gender[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_CharSel_Gender[playerid]); TD_CharSel_Gender[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_CharSel_Prev[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_CharSel_Prev[playerid]); TD_CharSel_Prev[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_CharSel_Next[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_CharSel_Next[playerid]); TD_CharSel_Next[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_CharSel_Play[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_CharSel_Play[playerid]); TD_CharSel_Play[playerid] = PlayerText:INVALID_TEXT_DRAW; }
    if (TD_CharSel_Create[playerid] != PlayerText:INVALID_TEXT_DRAW) { PlayerTextDrawDestroy(playerid, TD_CharSel_Create[playerid]); TD_CharSel_Create[playerid] = PlayerText:INVALID_TEXT_DRAW; }

    for (new i = 0; i < MAX_CHARS_PER_ACCOUNT; i++) {
        if (gCharActors[playerid][i] != -1 && IsValidActor(gCharActors[playerid][i])) {
            DestroyActor(gCharActors[playerid][i]);
        }
        gCharActors[playerid][i] = -1;
    }
}

stock UpdateCharSelectCamera(playerid, prevIdx = -1) {
    if (gCharSelectCount[playerid] == 0) return;

    new idx = gCharSelectIndex[playerid];
    new Float:aX = 1476.0 + (idx * 2.2);
    new Float:aY = -1742.6;
    new Float:aZ = 13.54;

    // Aktor menghadap Selatan (Angle 180.0, arah -Y).
    // Kamera berada 2.7 meter di depan aktor (-Y / Selatan), digeser 0.65m ke KANAN kamera
    // sehingga karakter terlihat jelas dari DEPAN dan posisinya berada di KIRI layar (karena UI ada di KANAN).
    new Float:camX = aX + 0.65;
    new Float:camY = aY - 2.7;
    new Float:camZ = aZ + 0.40;

    new Float:lookX = aX;
    new Float:lookY = aY;
    new Float:lookZ = aZ + 0.15;

    if (prevIdx != -1 && prevIdx != idx) {
        new Float:fromAX = 1476.0 + (prevIdx * 2.2);
        new Float:fromCamX = fromAX + 0.65;
        new Float:fromCamY = aY - 2.7;
        new Float:fromCamZ = aZ + 0.40;

        new Float:fromLookX = fromAX;
        new Float:fromLookY = aY;
        new Float:fromLookZ = aZ + 0.15;

        InterpolateCameraPos(playerid, fromCamX, fromCamY, fromCamZ, camX, camY, camZ, 700, CAMERA_MOVE);
        InterpolateCameraLookAt(playerid, fromLookX, fromLookY, fromLookZ, lookX, lookY, lookZ, 700, CAMERA_MOVE);
    } else {
        SetPlayerCameraPos(playerid, camX, camY, camZ);
        SetPlayerCameraLookAt(playerid, lookX, lookY, lookZ, CAMERA_CUT);
    }

    // Update TextDraw Strings
    new strName[128], strGender[64];
    format(strName, sizeof(strName), "Nama : ~y~%s", gCharSelectNames[playerid][idx]);
    format(strGender, sizeof(strGender), "Gender : ~w~%s", (gCharSelectGenders[playerid][idx] == 1) ? ("Pria") : ("Wanita"));

    PlayerTextDrawSetString(playerid, TD_CharSel_Name[playerid], strName);
    PlayerTextDrawSetString(playerid, TD_CharSel_Gender[playerid], strGender);
}

stock OpenCharSelectUI(playerid) {
    // 1. Query Database untuk mendapatkan karakter
    new query[256];
    format(query, sizeof(query),
        "SELECT `id`, `char_name`, `gender`, `skin_id` FROM `characters` WHERE `account_id` = %d AND `is_active` = 1 ORDER BY `id` ASC LIMIT %d",
        gPlayerData[playerid][p_AccountID], MAX_CHARS_PER_ACCOUNT);

    new DBResult:res = DB_ExecuteQuery(gDB, query);
    new count = 0;
    if (res) {
        count = DB_GetRowCount(res);
    }

    gCharSelectCount[playerid] = count;
    gCharSelectIndex[playerid] = 0;

    if (count == 0) {
        if (res) DB_FreeResultSet(res);
        StartNewCharacterCreation(playerid);
        return 1;
    }

    DestroyPlayerCharSelectUI(playerid);

    // Preload Animation Libraries ke player client agar animasi actor langsung berjalan
    ApplyAnimation(playerid, "DEALER", "null", 0.0, 0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "COP_AMBIENT", "null", 0.0, 0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "SMOKING", "null", 0.0, 0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "PED", "null", 0.0, 0, 0, 0, 0, 0, 0);

    // Siapkan Lingkungan (Waktu Siang, VW Terisolasi, Bekukan Pemain)
    SetPlayerTime(playerid, 12, 0);
    SetPlayerVirtualWorld(playerid, playerid + 1000);
    SetPlayerInterior(playerid, 0);
    TogglePlayerControllable(playerid, false);
    SetPlayerPos(playerid, 1476.0, -1755.0, 13.54); // Jauhkan ped pemain dari pandangan

    // Spawn Aktor
    for (new i = 0; i < count; i++) {
        gCharSelectIDs[playerid][i] = DB_GetFieldIntByName(res, "id");
        gCharSelectSkins[playerid][i] = DB_GetFieldIntByName(res, "skin_id");
        gCharSelectGenders[playerid][i] = DB_GetFieldIntByName(res, "gender");
        DB_GetFieldStringByName(res, "char_name", gCharSelectNames[playerid][i], 48);

        new Float:aX = 1476.0 + (i * 2.2);
        new Float:aY = -1742.6;
        new Float:aZ = 13.54;
        new Float:aA = 180.0; // Menghadap SELATAN (tepat ke arah kamera di depan)

        gCharActors[playerid][i] = CreateActor(gCharSelectSkins[playerid][i], aX, aY, aZ, aA);
        SetActorVirtualWorld(gCharActors[playerid][i], playerid + 1000);
        
        DB_SelectNextRow(res);
    }
    if (res) DB_FreeResultSet(res);

    // Jalankan timer 150ms untuk memasang animasi pose agar tidak tertimpa engine stream
    SetTimerEx("Timer_ApplyCharSelectAnim", 150, false, "i", playerid);

    // 2. Buat TextDraw UI di sebelah kanan (Tanpa Bayangan / Shadow: 0, Outline: 0)
    // Background Box (X: 430.0 .. 620.0, Y: 140.0 .. 340.0)
    TD_CharSel_Bg[playerid] = CreatePlayerTextDraw(playerid, 430.0, 140.0, "_");
    PlayerTextDrawUseBox(playerid, TD_CharSel_Bg[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_CharSel_Bg[playerid], COLOR_CHARSEL_BG);
    PlayerTextDrawTextSize(playerid, TD_CharSel_Bg[playerid], 620.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_CharSel_Bg[playerid], 0.0, 20.0);

    // Top Bar Purple
    TD_CharSel_TopBar[playerid] = CreatePlayerTextDraw(playerid, 430.0, 140.0, "_");
    PlayerTextDrawUseBox(playerid, TD_CharSel_TopBar[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_CharSel_TopBar[playerid], COLOR_CHARSEL_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_CharSel_TopBar[playerid], 620.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_CharSel_TopBar[playerid], 0.0, 0.75);

    // Title [ Pilih Karakter ]
    TD_CharSel_Title[playerid] = CreatePlayerTextDraw(playerid, 525.0, 155.0, "Pilih Karakter");
    PlayerTextDrawFont(playerid, TD_CharSel_Title[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_CharSel_Title[playerid], 0.20, 1.1);
    PlayerTextDrawColor(playerid, TD_CharSel_Title[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_CharSel_Title[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_CharSel_Title[playerid], COLOR_CHARSEL_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_CharSel_Title[playerid], 15.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_CharSel_Title[playerid], 2); // Center X=525
    PlayerTextDrawSetShadow(playerid, TD_CharSel_Title[playerid], 0);
    PlayerTextDrawSetOutline(playerid, TD_CharSel_Title[playerid], 0);
    
    // Teks Info Nama
    TD_CharSel_Name[playerid] = CreatePlayerTextDraw(playerid, 440.0, 180.0, "Nama : ~y~Memuat...");
    PlayerTextDrawFont(playerid, TD_CharSel_Name[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_CharSel_Name[playerid], 0.20, 1.0);
    PlayerTextDrawColor(playerid, TD_CharSel_Name[playerid], 0xFFFFFFFF);
    PlayerTextDrawSetShadow(playerid, TD_CharSel_Name[playerid], 0);
    PlayerTextDrawSetOutline(playerid, TD_CharSel_Name[playerid], 0);

    // Teks Info Gender
    TD_CharSel_Gender[playerid] = CreatePlayerTextDraw(playerid, 440.0, 195.0, "Gender : ~w~Memuat...");
    PlayerTextDrawFont(playerid, TD_CharSel_Gender[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_CharSel_Gender[playerid], 0.20, 1.0);
    PlayerTextDrawColor(playerid, TD_CharSel_Gender[playerid], 0xFFFFFFFF);
    PlayerTextDrawSetShadow(playerid, TD_CharSel_Gender[playerid], 0);
    PlayerTextDrawSetOutline(playerid, TD_CharSel_Gender[playerid], 0);

    // Navigasi: < Sebelum
    TD_CharSel_Prev[playerid] = CreatePlayerTextDraw(playerid, 477.5, 230.0, "< Sebelum");
    PlayerTextDrawFont(playerid, TD_CharSel_Prev[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_CharSel_Prev[playerid], 0.18, 1.0);
    PlayerTextDrawColor(playerid, TD_CharSel_Prev[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_CharSel_Prev[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_CharSel_Prev[playerid], COLOR_CHARSEL_SLATE);
    PlayerTextDrawTextSize(playerid, TD_CharSel_Prev[playerid], 15.0, 75.0);
    PlayerTextDrawAlignment(playerid, TD_CharSel_Prev[playerid], 2);
    PlayerTextDrawSetShadow(playerid, TD_CharSel_Prev[playerid], 0);
    PlayerTextDrawSetOutline(playerid, TD_CharSel_Prev[playerid], 0);
    PlayerTextDrawSetSelectable(playerid, TD_CharSel_Prev[playerid], true);

    // Navigasi: Selanjutnya >
    TD_CharSel_Next[playerid] = CreatePlayerTextDraw(playerid, 572.5, 230.0, "Selanjutnya >");
    PlayerTextDrawFont(playerid, TD_CharSel_Next[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_CharSel_Next[playerid], 0.18, 1.0);
    PlayerTextDrawColor(playerid, TD_CharSel_Next[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_CharSel_Next[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_CharSel_Next[playerid], COLOR_CHARSEL_SLATE);
    PlayerTextDrawTextSize(playerid, TD_CharSel_Next[playerid], 15.0, 75.0);
    PlayerTextDrawAlignment(playerid, TD_CharSel_Next[playerid], 2);
    PlayerTextDrawSetShadow(playerid, TD_CharSel_Next[playerid], 0);
    PlayerTextDrawSetOutline(playerid, TD_CharSel_Next[playerid], 0);
    PlayerTextDrawSetSelectable(playerid, TD_CharSel_Next[playerid], true);

    // Tombol Main
    TD_CharSel_Play[playerid] = CreatePlayerTextDraw(playerid, 525.0, 260.0, "Main");
    PlayerTextDrawFont(playerid, TD_CharSel_Play[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_CharSel_Play[playerid], 0.18, 1.05);
    PlayerTextDrawColor(playerid, TD_CharSel_Play[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_CharSel_Play[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_CharSel_Play[playerid], COLOR_CHARSEL_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_CharSel_Play[playerid], 15.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_CharSel_Play[playerid], 2);
    PlayerTextDrawSetShadow(playerid, TD_CharSel_Play[playerid], 0);
    PlayerTextDrawSetOutline(playerid, TD_CharSel_Play[playerid], 0);
    PlayerTextDrawSetSelectable(playerid, TD_CharSel_Play[playerid], true);

    // Tombol Buat Karakter
    TD_CharSel_Create[playerid] = CreatePlayerTextDraw(playerid, 525.0, 282.0, "Buat Karakter");
    PlayerTextDrawFont(playerid, TD_CharSel_Create[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_CharSel_Create[playerid], 0.18, 1.05);
    PlayerTextDrawColor(playerid, TD_CharSel_Create[playerid], (count < MAX_CHARS_PER_ACCOUNT) ? 0xFFFFFFFF : 0xAAAAAAFF);
    PlayerTextDrawUseBox(playerid, TD_CharSel_Create[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_CharSel_Create[playerid], COLOR_CHARSEL_SLATE);
    PlayerTextDrawTextSize(playerid, TD_CharSel_Create[playerid], 15.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_CharSel_Create[playerid], 2);
    PlayerTextDrawSetShadow(playerid, TD_CharSel_Create[playerid], 0);
    PlayerTextDrawSetOutline(playerid, TD_CharSel_Create[playerid], 0);
    PlayerTextDrawSetSelectable(playerid, TD_CharSel_Create[playerid], (count < MAX_CHARS_PER_ACCOUNT));

    PlayerTextDrawShow(playerid, TD_CharSel_Bg[playerid]);
    PlayerTextDrawShow(playerid, TD_CharSel_TopBar[playerid]);
    PlayerTextDrawShow(playerid, TD_CharSel_Title[playerid]);
    PlayerTextDrawShow(playerid, TD_CharSel_Name[playerid]);
    PlayerTextDrawShow(playerid, TD_CharSel_Gender[playerid]);
    PlayerTextDrawShow(playerid, TD_CharSel_Prev[playerid]);
    PlayerTextDrawShow(playerid, TD_CharSel_Next[playerid]);
    PlayerTextDrawShow(playerid, TD_CharSel_Play[playerid]);
    PlayerTextDrawShow(playerid, TD_CharSel_Create[playerid]);

    UpdateCharSelectCamera(playerid, false);
    SelectTextDraw(playerid, COLOR_CHARSEL_PURPLE);
    
    // Status flag
    gPlayerData[playerid][p_SelectingChar3D] = true;

    return 1;
}

stock CloseCharSelectUI(playerid, bool:cancelSelect = true) {
    if (!gPlayerData[playerid][p_SelectingChar3D]) return;
    gPlayerData[playerid][p_SelectingChar3D] = false;
    
    if (cancelSelect) {
        CancelSelectTextDraw(playerid);
    }
    DestroyPlayerCharSelectUI(playerid);
}

stock HandleCharSelectClick(playerid, PlayerText:playertextid) {
    if (!gPlayerData[playerid][p_SelectingChar3D]) return 0;

    if (playertextid == TD_CharSel_Prev[playerid]) {
        if (gCharSelectCount[playerid] > 1) {
            new oldIdx = gCharSelectIndex[playerid];
            gCharSelectIndex[playerid]--;
            if (gCharSelectIndex[playerid] < 0) gCharSelectIndex[playerid] = gCharSelectCount[playerid] - 1;
            UpdateCharSelectCamera(playerid, oldIdx);
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
        }
        return 1;
    }
    
    if (playertextid == TD_CharSel_Next[playerid]) {
        if (gCharSelectCount[playerid] > 1) {
            new oldIdx = gCharSelectIndex[playerid];
            gCharSelectIndex[playerid]++;
            if (gCharSelectIndex[playerid] >= gCharSelectCount[playerid]) gCharSelectIndex[playerid] = 0;
            UpdateCharSelectCamera(playerid, oldIdx);
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
        }
        return 1;
    }

    if (playertextid == TD_CharSel_Play[playerid]) {
        PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
        new selectedCharID = gCharSelectIDs[playerid][gCharSelectIndex[playerid]];
        CloseCharSelectUI(playerid, false);
        LoadCharacter(playerid, selectedCharID);
        return 1;
    }

    if (playertextid == TD_CharSel_Create[playerid]) {
        if (gCharSelectCount[playerid] < MAX_CHARS_PER_ACCOUNT) {
            PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
            CloseCharSelectUI(playerid, false); // smooth transition ke form char
            StartNewCharacterCreation(playerid);
        } else {
            PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
        }
        return 1;
    }

    return 0;
}
