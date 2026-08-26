#if defined _MODULE_SKIN_SELECTOR_INC
    #endinput
#endif
#define _MODULE_SKIN_SELECTOR_INC

// ============================================================
//  SantaraBaru Roleplay - Live 3D Skin Selector UI & Skin Catalog
// ============================================================

// Daftar semua 310 skin GTA SA / MTA Wiki (Model name sesuai https://wiki.multitheftauto.com/wiki/All_Skins_Page)
new const gSkins[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
    40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
    50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
    60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
    70, 71, 72, 73, 75, 76, 77, 78, 79, 80,
    81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
    91, 92, 93, 94, 95, 96, 97, 98, 99, 100,
    101, 102, 103, 104, 105, 106, 107, 108, 109, 110,
    111, 112, 113, 114, 115, 116, 117, 118, 119, 120,
    121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
    131, 132, 133, 134, 135, 136, 137, 138, 139, 140,
    141, 142, 143, 144, 145, 146, 147, 148, 150, 151,
    152, 153, 154, 155, 156, 157, 158, 159, 160, 161,
    162, 163, 164, 165, 166, 167, 168, 169, 170, 171,
    172, 173, 174, 175, 176, 177, 178, 179, 180, 181,
    182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
    192, 193, 194, 195, 196, 197, 198, 199, 200, 201,
    202, 203, 204, 205, 206, 207, 209, 210, 211, 212,
    213, 214, 215, 216, 217, 218, 219, 220, 221, 222,
    223, 224, 225, 226, 227, 228, 229, 230, 231, 232,
    233, 234, 235, 236, 237, 238, 239, 240, 241, 242,
    243, 244, 245, 246, 247, 248, 249, 250, 251, 252,
    253, 254, 255, 256, 257, 258, 259, 260, 261, 262,
    263, 264, 265, 266, 267, 268, 269, 270, 271, 272,
    273, 274, 275, 276, 277, 278, 279, 280, 281, 282,
    283, 284, 285, 286, 287, 288, 289, 290, 291, 292,
    293, 294, 295, 296, 297, 298, 299, 300, 301, 302,
    303, 304, 305, 306, 307, 308, 309, 310, 311, 312
};
#define SKIN_COUNT (sizeof(gSkins))

// Model name resmi sesuai MTA Wiki
new const gSkinNames[][24] = {
    "cj", "truth", "maccer", "cdeput", "sfpdm1", "bb", "wfycrp", "male01", "wmycd2", "bfori",
    "bfost", "vbfycrp", "bfyri", "bfyst", "bmori", "bmost", "bmyap", "bmybu", "bmybe", "bmydj",
    "bmyri", "bmycr", "bmyst", "wmybmx", "wbdyg1", "wbdyg2", "wmybp", "wmycon", "bmydrug", "wmydrug",
    "hmydrug", "dwfolc", "dwmolc1", "dwmolc2", "dwmylc1", "hmogar", "wmygol1", "wmygol2", "hfori", "hfost",
    "hfyri", "hfyst", "suzie", "hmori", "hmost", "hmybe", "hmyri", "hmycr", "hmyst", "omokung",
    "wmymech", "bmymoun", "wmymoun", "ofori", "ofost", "ofyri", "ofyst", "omori", "omost", "omyri",
    "omyst", "wmyplt", "wmopj", "bfypro", "hfypro", "vwmyap", "bmypol1", "bmypol2", "wmoprea", "sbfyst",
    "wmosci", "wmysgrd", "swmyhp1", "swmyhp2", "swfopro", "wfystew", "swmotr1", "wmotr1", "bmotr1", "vbmybox",
    "vwmybox", "vhmyelv", "vbmyelv", "vimyelv", "vwfypro", "vhfyst", "vwfyst1", "wfori", "wfost", "wfyjg",
    "wfyri", "wfyro", "wfyst", "wmori", "wmost", "wmyjg", "wmylg", "wmyri", "wmyro", "wmycr",
    "wmyst", "ballas1", "ballas2", "ballas3", "fam1", "fam2", "fam3", "lsv1", "lsv2", "lsv3",
    "maffa", "maffb", "mafboss", "vla1", "vla2", "vla3", "triada", "triadb", "lvpdm1", "triboss",
    "dnb1", "dnb2", "dnb3", "vmaff1", "vmaff2", "vmaff3", "vmaff4", "dnmylc", "dnfolc1", "dnfolc2",
    "dnfylc", "dnmolc1", "dnmolc2", "sbmotr2", "swmotr2", "sbmytr3", "swmotr3", "wfybe", "bfybe", "hfybe",
    "sofybu", "sbmyst", "sbmycr", "bmycg", "wfycrk", "hmycm", "wmybu", "bfybu", "wfybu", "dwfylc1",
    "wfypro", "wmyconb", "wmybe", "wmypizz", "bmobar", "cwfyhb", "cwmofr", "cwmohb1", "cwmohb2", "cwmyfr",
    "cwmyhb1", "bmyboun", "wmyboun", "wmomib", "bmymib", "wmybell", "bmochil", "sofyri", "somyst", "vwmybjd",
    "vwfycrp", "sfr1", "sfr2", "sfr3", "bmybar", "wmybar", "wfysex", "wmyammo", "bmytatt", "vwmycr",
    "vbmocd", "vbmycr", "vhmycr", "sbmyri", "somyri", "somybu", "swmyst", "wmyva", "copgrl3", "gungrl3",
    "mecgrl3", "nurgrl3", "crogrl3", "gangrl3", "cwfofr", "cwfohb", "cwfyfr1", "cwfyfr2", "cwmyhb2", "dwfylc2",
    "dwmylc2", "omykara", "wmykara", "wfyburg", "vwmycd", "vhfypro", "omonood", "omoboat", "wfyclot", "vwmotr1",
    "vwmotr2", "vwfywai", "sbfori", "swfyri", "wmyclot", "sbfost", "sbfyri", "sbmocd", "sbmori", "sbmost",
    "shmycr", "sofori", "sofost", "sofyst", "somobu", "somori", "somost", "swmotr5", "swfori", "swfost",
    "swfyst", "swmocd", "swmori", "swmost", "shfypro", "sbfypro", "swmotr4", "swmyri", "smyst", "smyst2",
    "sfypro", "vbfyst2", "vbfypro", "vhfyst3", "bikera", "bikerb", "bmypimp", "swmycr", "wfylg", "wmyva2",
    "bmosec", "bikdrug", "wmych", "sbfystr", "swfystr", "heck1", "heck2", "bmycon", "wmycd1", "bmocd",
    "vwfywa2", "wmoice", "tenpen", "pulaski", "hern", "dwayne", "smoke", "sweet", "ryder", "forelli",
    "mediatr", "laemt1", "lvemt1", "sfemt1", "lafd1", "lvfd1", "sffd1", "lapd1", "sfpd1", "lvpd1",
    "csher", "lapdm1", "swat", "fbi", "army", "dsher", "somyap", "rose", "paul", "cesar",
    "ogloc", "wuzimu", "torino", "jizzy", "maddogg", "cat", "claude", "ryder2", "ryder3", "emmet",
    "andre", "kendl", "jethro", "zero", "tbone", "sindaco", "janitor", "bbthin", "smokev", "psycho"
};

// TextDraw Handles
new PlayerText:TD_SkinBox[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SkinHeader[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SkinTitle[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SkinInfo[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SkinPrev[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SkinNext[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SkinRand[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SkinSave[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SkinCancel[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SkinHint[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};

forward Timer_FixSkinCamera(playerid);
public Timer_FixSkinCamera(playerid) {
    if (IsPlayerConnected(playerid) && gPlayerData[playerid][p_SelectingSkin]) {
        SetPlayerFrontCamera(playerid);
    }
    return 1;
}

stock DestroyPlayerSkinTextDraws(playerid) {
    if (TD_SkinBox[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SkinBox[playerid]);
        TD_SkinBox[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SkinHeader[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SkinHeader[playerid]);
        TD_SkinHeader[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SkinTitle[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SkinTitle[playerid]);
        TD_SkinTitle[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SkinInfo[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SkinInfo[playerid]);
        TD_SkinInfo[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SkinPrev[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SkinPrev[playerid]);
        TD_SkinPrev[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SkinNext[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SkinNext[playerid]);
        TD_SkinNext[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SkinRand[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SkinRand[playerid]);
        TD_SkinRand[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SkinSave[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SkinSave[playerid]);
        TD_SkinSave[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SkinCancel[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SkinCancel[playerid]);
        TD_SkinCancel[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SkinHint[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SkinHint[playerid]);
        TD_SkinHint[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
}

stock GetSkinCategory(skinid, cat[], len = 32) {
    switch (skinid) {
        case 6, 9..13, 31, 38..41, 53..56, 63, 64, 69, 75..77, 85..93,
             129..131, 138..141, 145, 148, 150..152, 157, 169, 172, 178,
             190..199, 201, 205, 207, 211, 214..216, 218, 219, 224..226,
             231..233, 237, 238, 243..246, 251, 256, 257, 263, 298, 304: {
            format(cat, len, "Wanita");
        }
        default: {
            format(cat, len, "Pria");
        }
    }
}

stock SetPlayerFrontCamera(playerid) {
    new Float:px = gPlayerData[playerid][p_X];
    new Float:py = gPlayerData[playerid][p_Y];
    new Float:pz = gPlayerData[playerid][p_Z];
    new Float:pa = gPlayerData[playerid][p_A];

    SetPlayerPos(playerid, px, py, pz);
    SetPlayerFacingAngle(playerid, pa);
    TogglePlayerControllable(playerid, false);
    ClearAnimations(playerid, 1);

    // Vektor arah depan karakter (tempat muka/dada karakter menghadap)
    new Float:fwdX = -floatsin(pa, degrees);
    new Float:fwdY = floatcos(pa, degrees);

    // Vektor ke arah kanan karakter
    new Float:rightX = floatcos(pa, degrees);
    new Float:rightY = floatsin(pa, degrees);

    // Kamera ditempatkan 2.8 meter di DEPAN karakter, digeser 0.85 meter ke KANAN karakter
    // Sehingga karakter terlihat jelas dari DEPAN dan posisinya berada di KIRI layar (karena UI ada di KANAN)
    new Float:camDist = 2.8;
    new Float:camRight = 0.85;
    new Float:camX = px + (fwdX * camDist) + (rightX * camRight);
    new Float:camY = py + (fwdY * camDist) + (rightY * camRight);
    new Float:camZ = pz + 0.45;

    new Float:lookX = px;
    new Float:lookY = py;
    new Float:lookZ = pz + 0.15;

    SetPlayerCameraPos(playerid, camX, camY, camZ);
    SetPlayerCameraLookAt(playerid, lookX, lookY, lookZ, CAMERA_CUT);
}

stock UpdateSkinSelectorUI(playerid) {
    if (!gPlayerData[playerid][p_SelectingSkin]) return;

    new idx = gPlayerData[playerid][p_SkinIndex];
    new skinid = gSkins[idx];
    new cat[32];
    GetSkinCategory(skinid, cat, sizeof(cat));

    new str[256];
    format(str, sizeof(str),
        "~w~Model : ~y~%s~n~" \
        "~w~Skin ID : ~y~%d~n~" \
        "~w~Gender : ~w~%s~n~" \
        "~w~Pilihan : ~y~%d / %d",
        gSkinNames[idx], skinid, cat, idx + 1, SKIN_COUNT);

    PlayerTextDrawSetString(playerid, TD_SkinInfo[playerid], str);
}

stock OpenSkinSelection(playerid, bool:isNewChar = false) {
    gPlayerData[playerid][p_SelectingSkin] = true;
    gPlayerData[playerid][p_OriginalSkin]  = gPlayerData[playerid][p_Skin];
    gPlayerData[playerid][p_IsNewCharacter] = isNewChar;

    // Cari index skin saat ini di daftar gSkins
    gPlayerData[playerid][p_SkinIndex] = 0;
    for (new i = 0; i < SKIN_COUNT; i++) {
        if (gSkins[i] == gPlayerData[playerid][p_Skin]) {
            gPlayerData[playerid][p_SkinIndex] = i;
            break;
        }
    }

    // Freeze pemain & posisikan kamera hadap depan karakter
    SetPlayerFrontCamera(playerid);
    SetTimerEx("Timer_FixSkinCamera", 150, false, "i", playerid);

    // Pastikan skin langsung terlihat di karakter
    SetPlayerSkin(playerid, gSkins[gPlayerData[playerid][p_SkinIndex]]);

    // Hapus TextDraws lama jika ada & sembunyikan HUD uang selama menu skin terbuka
    DestroyPlayerSkinTextDraws(playerid);
    HidePlayerMoneyHUD(playerid);

    //    Buat UI TextDraw di sebelah KANAN (X: 430 .. 610)       

    // 1. Background Box (#1D1D1D Dark Matte di Kanan)
    TD_SkinBox[playerid] = CreatePlayerTextDraw(playerid, 430.0, 105.0, "_");
    PlayerTextDrawUseBox(playerid, TD_SkinBox[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_SkinBox[playerid], 0x1D1D1DF2);
    PlayerTextDrawTextSize(playerid, TD_SkinBox[playerid], 610.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_SkinBox[playerid], 0.0, 26.0);
    PlayerTextDrawSetSelectable(playerid, TD_SkinBox[playerid], 0);

    // 2. Header Bar Box (#E69958 Warm Amber Header)
    TD_SkinHeader[playerid] = CreatePlayerTextDraw(playerid, 430.0, 105.0, "_");
    PlayerTextDrawUseBox(playerid, TD_SkinHeader[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_SkinHeader[playerid], 0xE69958FF);
    PlayerTextDrawTextSize(playerid, TD_SkinHeader[playerid], 610.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_SkinHeader[playerid], 0.0, 2.7);
    PlayerTextDrawSetSelectable(playerid, TD_SkinHeader[playerid], 0);

    // 3. Header Title Text
    TD_SkinTitle[playerid] = CreatePlayerTextDraw(playerid, 520.0, 110.0, "PILIH PENAMPILAN");
    PlayerTextDrawFont(playerid, TD_SkinTitle[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SkinTitle[playerid], 0.25, 1.2);
    PlayerTextDrawColor(playerid, TD_SkinTitle[playerid], 0xFFFFFFFF);
    PlayerTextDrawAlignment(playerid, TD_SkinTitle[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SkinTitle[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SkinTitle[playerid], 0);

    // 4. Skin Info Text Box
    TD_SkinInfo[playerid] = CreatePlayerTextDraw(playerid, 438.0, 142.0, "Memuat info skin...");
    PlayerTextDrawFont(playerid, TD_SkinInfo[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_SkinInfo[playerid], 0.22, 1.15);
    PlayerTextDrawColor(playerid, TD_SkinInfo[playerid], 0xFFFFFFFF);
    PlayerTextDrawSetOutline(playerid, TD_SkinInfo[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SkinInfo[playerid], 0);

    // 5. Button: << PREV (Clickable)
    TD_SkinPrev[playerid] = CreatePlayerTextDraw(playerid, 438.0, 212.0, "< SEBELUM");
    PlayerTextDrawFont(playerid, TD_SkinPrev[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SkinPrev[playerid], 0.21, 1.3);
    PlayerTextDrawColor(playerid, TD_SkinPrev[playerid], 0xE69958FF);
    PlayerTextDrawUseBox(playerid, TD_SkinPrev[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_SkinPrev[playerid], 0x2A2A2AFF);
    PlayerTextDrawTextSize(playerid, TD_SkinPrev[playerid], 517.0, 16.0);
    PlayerTextDrawSetOutline(playerid, TD_SkinPrev[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SkinPrev[playerid], 1);

    // 6. Button: NEXT >> (Clickable)
    TD_SkinNext[playerid] = CreatePlayerTextDraw(playerid, 524.0, 212.0, "LANJUT >");
    PlayerTextDrawFont(playerid, TD_SkinNext[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SkinNext[playerid], 0.21, 1.3);
    PlayerTextDrawColor(playerid, TD_SkinNext[playerid], 0xE69958FF);
    PlayerTextDrawUseBox(playerid, TD_SkinNext[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_SkinNext[playerid], 0x2A2A2AFF);
    PlayerTextDrawTextSize(playerid, TD_SkinNext[playerid], 602.0, 16.0);
    PlayerTextDrawSetOutline(playerid, TD_SkinNext[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SkinNext[playerid], 1);

    // 7. Button: [ PILIH ACAK ] (Clickable)
    TD_SkinRand[playerid] = CreatePlayerTextDraw(playerid, 438.0, 238.0, "   [ PILIH ACAK ]");
    PlayerTextDrawFont(playerid, TD_SkinRand[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SkinRand[playerid], 0.21, 1.3);
    PlayerTextDrawColor(playerid, TD_SkinRand[playerid], 0xE69958FF);
    PlayerTextDrawUseBox(playerid, TD_SkinRand[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_SkinRand[playerid], 0x33261CFF);
    PlayerTextDrawTextSize(playerid, TD_SkinRand[playerid], 602.0, 16.0);
    PlayerTextDrawSetOutline(playerid, TD_SkinRand[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SkinRand[playerid], 1);

    // 8. Button: [ PILIH SKIN INI ] (Clickable - #E69958 Accent)
    TD_SkinSave[playerid] = CreatePlayerTextDraw(playerid, 438.0, 265.0, "  ~w~[ PILIH SKIN INI ]");
    PlayerTextDrawFont(playerid, TD_SkinSave[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SkinSave[playerid], 0.21, 1.35);
    PlayerTextDrawColor(playerid, TD_SkinSave[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SkinSave[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_SkinSave[playerid], 0xE69958FF);
    PlayerTextDrawTextSize(playerid, TD_SkinSave[playerid], 602.0, 18.0);
    PlayerTextDrawSetOutline(playerid, TD_SkinSave[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SkinSave[playerid], 1);

    // 9. Button: [ BATAL ] (Clickable - Dark Crimson)
    TD_SkinCancel[playerid] = CreatePlayerTextDraw(playerid, 438.0, 293.0, "      ~w~[ ~r~BATAL ~w~]");
    PlayerTextDrawFont(playerid, TD_SkinCancel[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SkinCancel[playerid], 0.21, 1.3);
    PlayerTextDrawColor(playerid, TD_SkinCancel[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SkinCancel[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TD_SkinCancel[playerid], 0x481E1EFF);
    PlayerTextDrawTextSize(playerid, TD_SkinCancel[playerid], 602.0, 16.0);
    PlayerTextDrawSetOutline(playerid, TD_SkinCancel[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SkinCancel[playerid], 1);

    // 10. Hint text di bawah
    TD_SkinHint[playerid] = CreatePlayerTextDraw(playerid, 520.0, 318.0, "~w~Klik tombol di atas untuk memilih");
    PlayerTextDrawFont(playerid, TD_SkinHint[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_SkinHint[playerid], 0.16, 0.9);
    PlayerTextDrawColor(playerid, TD_SkinHint[playerid], 0xCCCCCCFF);
    PlayerTextDrawAlignment(playerid, TD_SkinHint[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SkinHint[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SkinHint[playerid], 0);

    // Tampilkan semua TextDraw ke pemain
    PlayerTextDrawShow(playerid, TD_SkinBox[playerid]);
    PlayerTextDrawShow(playerid, TD_SkinHeader[playerid]);
    PlayerTextDrawShow(playerid, TD_SkinTitle[playerid]);
    PlayerTextDrawShow(playerid, TD_SkinInfo[playerid]);
    PlayerTextDrawShow(playerid, TD_SkinPrev[playerid]);
    PlayerTextDrawShow(playerid, TD_SkinNext[playerid]);
    PlayerTextDrawShow(playerid, TD_SkinRand[playerid]);
    PlayerTextDrawShow(playerid, TD_SkinSave[playerid]);
    PlayerTextDrawShow(playerid, TD_SkinCancel[playerid]);
    PlayerTextDrawShow(playerid, TD_SkinHint[playerid]);

    // Update info text
    UpdateSkinSelectorUI(playerid);

    // Aktifkan mode kursor klik TextDraw (Highlight warna #E69958 Warm Amber)
    SelectTextDraw(playerid, 0xE69958FF);

    SendClientMessage(playerid, COL_CYAN, "  [Live 3D] Pilih penampilan karakter Anda di menu sebelah kiri.");
    SendClientMessage(playerid, COL_WHITE, "  Karakter di sebelah kanan akan berubah secara langsung saat Anda memilih!");
}

stock CloseSkinSelection(playerid, bool:saved = true) {
    if (!gPlayerData[playerid][p_SelectingSkin]) return;

    gPlayerData[playerid][p_SelectingSkin] = false;

    // Matikan kursor klik TextDraw
    CancelSelectTextDraw(playerid);

    // Hapus TextDraws
    DestroyPlayerSkinTextDraws(playerid);

    // Unfreeze pemain
    TogglePlayerControllable(playerid, true);

    // Kembalikan kamera ke belakang pemain & tampilkan kembali HUD uang
    SetCameraBehindPlayer(playerid);
    ShowPlayerMoneyHUD(playerid);
    UpdatePlayerMoneyHUD(playerid);

    if (gPlayerData[playerid][p_IsNewCharacter] && saved) {
        gPlayerData[playerid][p_IsNewCharacter] = false;
        new welcome[128];
        format(welcome, sizeof(welcome),
            "  Selamat datang di SantaraBaru RP, {FFFF00}%s{00CC66}! Karakter Anda siap dimainkan.",
            gPlayerData[playerid][p_CharName]);
        SendClientMessage(playerid, COL_GREEN, welcome);
    }
}
