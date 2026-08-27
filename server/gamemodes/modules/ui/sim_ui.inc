#if defined _MODULE_SIM_UI_INC
    #endinput
#endif
#define _MODULE_SIM_UI_INC

// ============================================================
//  SantaraBaru Roleplay - Driving License (SIM) UI
//  1. Right-Side Interactive Sidebar Menu (/sim)
//  2. High-Fidelity Custom "SANTARA Driving License" Card Viewer
// ============================================================

// ─── 1. Sesi Panel Sidebar Kanan Layar (/sim) ───────────────
new PlayerText:TD_SimMainBox[MAX_PLAYERS]        = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SimTopBar[MAX_PLAYERS]         = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SimCloseBtn[MAX_PLAYERS]       = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SimHeader[MAX_PLAYERS]         = {PlayerText:INVALID_TEXT_DRAW, ...};

// 3x Option Slots (SIM A, SIM B, SIM C)
new PlayerText:TD_SimSlot[MAX_PLAYERS][3];

// Action Buttons
new PlayerText:TD_SimBtnLihat[MAX_PLAYERS]       = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SimBtnTunjukkan[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SimBtnBatal[MAX_PLAYERS]       = {PlayerText:INVALID_TEXT_DRAW, ...};

// Navigation Buttons
new PlayerText:TD_SimBtnNaik[MAX_PLAYERS]        = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SimBtnTurun[MAX_PLAYERS]       = {PlayerText:INVALID_TEXT_DRAW, ...};

// ─── 2. Kartu Fisik Digital "SANTARA Driving License" ────────
new bool:gShowingSIMCard[MAX_PLAYERS]            = {false, ...};

new PlayerText:TD_SIMCard_Border[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SIMCard_Bg[MAX_PLAYERS]        = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SIMCard_RedHeader[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SIMCard_Close[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};

new PlayerText:TD_SIMCard_Title[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SIMCard_SubHeader[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SIMCard_Subtitle[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SIMCard_Badge[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};

// Label & Value Rows (Terpisah & Bebas Shadow/Outline agar tajam & tidak berbayang)
new PlayerText:TD_SIMCard_LblNama[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SIMCard_ValNama[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};

new PlayerText:TD_SIMCard_LblTTL[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SIMCard_ValTTL[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};

new PlayerText:TD_SIMCard_LblGender[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SIMCard_ValGender[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};

new PlayerText:TD_SIMCard_LblAlamat[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SIMCard_ValAlamat[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};

new PlayerText:TD_SIMCard_LblJob[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SIMCard_ValJob[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};

new PlayerText:TD_SIMCard_LblNoSIM[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SIMCard_ValNoSIM[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};

new PlayerText:TD_SIMCard_LblBerlaku[MAX_PLAYERS]= {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SIMCard_ValBerlaku[MAX_PLAYERS]= {PlayerText:INVALID_TEXT_DRAW, ...};

// 3D Photo & Cap Kepolisian
new PlayerText:TD_SIMCard_PhotoBorder[MAX_PLAYERS]= {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SIMCard_PhotoBg[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SIMCard_Photo[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SIMCard_SignCity[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_SIMCard_SignStamp[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};

// Petunjuk Tutup
new PlayerText:TD_SIMCard_Hint[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};

// ============================================================
//  Fungsi Destroy & Pembersihan TextDraw
// ============================================================

stock DestroyPlayerSimMenuTextDraws(playerid) {
    if (TD_SimMainBox[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SimMainBox[playerid]);
        TD_SimMainBox[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SimTopBar[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SimTopBar[playerid]);
        TD_SimTopBar[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SimCloseBtn[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SimCloseBtn[playerid]);
        TD_SimCloseBtn[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SimHeader[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SimHeader[playerid]);
        TD_SimHeader[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    for (new i = 0; i < 3; i++) {
        if (TD_SimSlot[playerid][i] != PlayerText:INVALID_TEXT_DRAW) {
            PlayerTextDrawDestroy(playerid, TD_SimSlot[playerid][i]);
            TD_SimSlot[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
        }
    }

    if (TD_SimBtnLihat[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SimBtnLihat[playerid]);
        TD_SimBtnLihat[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SimBtnTunjukkan[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SimBtnTunjukkan[playerid]);
        TD_SimBtnTunjukkan[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SimBtnBatal[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SimBtnBatal[playerid]);
        TD_SimBtnBatal[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SimBtnNaik[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SimBtnNaik[playerid]);
        TD_SimBtnNaik[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SimBtnTurun[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SimBtnTurun[playerid]);
        TD_SimBtnTurun[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
}

stock DestroyPlayerSIMCardTextDraws(playerid) {
    if (TD_SIMCard_Border[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_Border[playerid]);
        TD_SIMCard_Border[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_Bg[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_Bg[playerid]);
        TD_SIMCard_Bg[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_RedHeader[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_RedHeader[playerid]);
        TD_SIMCard_RedHeader[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_Close[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_Close[playerid]);
        TD_SIMCard_Close[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_Title[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_Title[playerid]);
        TD_SIMCard_Title[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_SubHeader[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_SubHeader[playerid]);
        TD_SIMCard_SubHeader[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_Subtitle[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_Subtitle[playerid]);
        TD_SIMCard_Subtitle[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_Badge[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_Badge[playerid]);
        TD_SIMCard_Badge[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_LblNama[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_LblNama[playerid]);
        TD_SIMCard_LblNama[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_ValNama[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_ValNama[playerid]);
        TD_SIMCard_ValNama[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_LblTTL[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_LblTTL[playerid]);
        TD_SIMCard_LblTTL[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_ValTTL[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_ValTTL[playerid]);
        TD_SIMCard_ValTTL[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_LblGender[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_LblGender[playerid]);
        TD_SIMCard_LblGender[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_ValGender[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_ValGender[playerid]);
        TD_SIMCard_ValGender[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_LblAlamat[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_LblAlamat[playerid]);
        TD_SIMCard_LblAlamat[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_ValAlamat[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_ValAlamat[playerid]);
        TD_SIMCard_ValAlamat[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_LblJob[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_LblJob[playerid]);
        TD_SIMCard_LblJob[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_ValJob[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_ValJob[playerid]);
        TD_SIMCard_ValJob[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_LblNoSIM[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_LblNoSIM[playerid]);
        TD_SIMCard_LblNoSIM[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_ValNoSIM[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_ValNoSIM[playerid]);
        TD_SIMCard_ValNoSIM[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_LblBerlaku[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_LblBerlaku[playerid]);
        TD_SIMCard_LblBerlaku[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_ValBerlaku[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_ValBerlaku[playerid]);
        TD_SIMCard_ValBerlaku[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_PhotoBorder[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_PhotoBorder[playerid]);
        TD_SIMCard_PhotoBorder[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_PhotoBg[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_PhotoBg[playerid]);
        TD_SIMCard_PhotoBg[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_Photo[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_Photo[playerid]);
        TD_SIMCard_Photo[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_SignCity[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_SignCity[playerid]);
        TD_SIMCard_SignCity[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_SignStamp[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_SignStamp[playerid]);
        TD_SIMCard_SignStamp[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_SIMCard_Hint[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_SIMCard_Hint[playerid]);
        TD_SIMCard_Hint[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
}

stock DestroyPlayerSimTextDraws(playerid) {
    DestroyPlayerSimMenuTextDraws(playerid);
    DestroyPlayerSIMCardTextDraws(playerid);
}

// ============================================================
//  1. UI Menu Sisi Kanan Layar (/sim)
// ============================================================

stock CreatePlayerSimMenuTextDraws(playerid) {
    DestroyPlayerSimMenuTextDraws(playerid);

    // 1. Background Container Box (Right side: X: 430.0 .. 620.0, Y: 78.0 .. 275.0)
    TD_SimMainBox[playerid] = CreatePlayerTextDraw(playerid, 430.0, 78.0, "_");
    PlayerTextDrawUseBox(playerid, TD_SimMainBox[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_SimMainBox[playerid], COLOR_SIM_BG);
    PlayerTextDrawTextSize(playerid, TD_SimMainBox[playerid], 620.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_SimMainBox[playerid], 0.0, 24.5);
    PlayerTextDrawSetSelectable(playerid, TD_SimMainBox[playerid], false);

    // 2. Top Accent Line (Electric Purple, X: 430.0 .. 602.0, Y: 78.0)
    TD_SimTopBar[playerid] = CreatePlayerTextDraw(playerid, 430.0, 78.0, "_");
    PlayerTextDrawUseBox(playerid, TD_SimTopBar[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_SimTopBar[playerid], COLOR_SIM_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_SimTopBar[playerid], 602.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_SimTopBar[playerid], 0.0, 0.75);
    PlayerTextDrawSetSelectable(playerid, TD_SimTopBar[playerid], false);

    // 3. Top-Right Red Close Button [X] (Center X: 611.0, Y: 77.0)
    TD_SimCloseBtn[playerid] = CreatePlayerTextDraw(playerid, 611.0, 77.0, "X");
    PlayerTextDrawFont(playerid, TD_SimCloseBtn[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SimCloseBtn[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_SimCloseBtn[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SimCloseBtn[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_SimCloseBtn[playerid], COLOR_SIM_RED);
    PlayerTextDrawTextSize(playerid, TD_SimCloseBtn[playerid], 10.0, 18.0);
    PlayerTextDrawAlignment(playerid, TD_SimCloseBtn[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SimCloseBtn[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SimCloseBtn[playerid], true);

    // 4. Header Bar Box (SIM) (Center X: 525.0, Y: 92.0)
    TD_SimHeader[playerid] = CreatePlayerTextDraw(playerid, 525.0, 92.0, "SIM");
    PlayerTextDrawFont(playerid, TD_SimHeader[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SimHeader[playerid], 0.18, 1.05);
    PlayerTextDrawColor(playerid, TD_SimHeader[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SimHeader[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_SimHeader[playerid], COLOR_SIM_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_SimHeader[playerid], 15.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_SimHeader[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SimHeader[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SimHeader[playerid], false);

    // 5. 3x Option Slots (SIM A, SIM B, SIM C) (Y: 114.0, 131.0, 148.0)
    for (new i = 0; i < 3; i++) {
        new Float:slotY = 114.0 + (i * 17.0);
        TD_SimSlot[playerid][i] = CreatePlayerTextDraw(playerid, 440.0, slotY, "SIM");
        PlayerTextDrawFont(playerid, TD_SimSlot[playerid][i], 1);
        PlayerTextDrawLetterSize(playerid, TD_SimSlot[playerid][i], 0.17, 1.00);
        PlayerTextDrawColor(playerid, TD_SimSlot[playerid][i], 0xFFFFFFFF);
        PlayerTextDrawUseBox(playerid, TD_SimSlot[playerid][i], true);
        PlayerTextDrawBoxColor(playerid, TD_SimSlot[playerid][i], COLOR_SIM_EMPTY);
        PlayerTextDrawTextSize(playerid, TD_SimSlot[playerid][i], 610.0, 14.0);
        PlayerTextDrawSetOutline(playerid, TD_SimSlot[playerid][i], 1);
        PlayerTextDrawSetSelectable(playerid, TD_SimSlot[playerid][i], true);
    }

    // 6. Action Button: Lihat (Center X: 525.0, Y: 172.0)
    TD_SimBtnLihat[playerid] = CreatePlayerTextDraw(playerid, 525.0, 172.0, "Lihat");
    PlayerTextDrawFont(playerid, TD_SimBtnLihat[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SimBtnLihat[playerid], 0.17, 1.05);
    PlayerTextDrawColor(playerid, TD_SimBtnLihat[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SimBtnLihat[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_SimBtnLihat[playerid], COLOR_SIM_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_SimBtnLihat[playerid], 15.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_SimBtnLihat[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SimBtnLihat[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SimBtnLihat[playerid], true);

    // 7. Action Button: Tunjukkan (Center X: 525.0, Y: 195.0)
    TD_SimBtnTunjukkan[playerid] = CreatePlayerTextDraw(playerid, 525.0, 195.0, "Tunjukkan");
    PlayerTextDrawFont(playerid, TD_SimBtnTunjukkan[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SimBtnTunjukkan[playerid], 0.17, 1.05);
    PlayerTextDrawColor(playerid, TD_SimBtnTunjukkan[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SimBtnTunjukkan[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_SimBtnTunjukkan[playerid], COLOR_SIM_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_SimBtnTunjukkan[playerid], 15.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_SimBtnTunjukkan[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SimBtnTunjukkan[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SimBtnTunjukkan[playerid], true);

    // 8. Action Button: Batal (Center X: 525.0, Y: 218.0)
    TD_SimBtnBatal[playerid] = CreatePlayerTextDraw(playerid, 525.0, 218.0, "Batal");
    PlayerTextDrawFont(playerid, TD_SimBtnBatal[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SimBtnBatal[playerid], 0.17, 1.05);
    PlayerTextDrawColor(playerid, TD_SimBtnBatal[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SimBtnBatal[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_SimBtnBatal[playerid], COLOR_SIM_RED);
    PlayerTextDrawTextSize(playerid, TD_SimBtnBatal[playerid], 15.0, 170.0);
    PlayerTextDrawAlignment(playerid, TD_SimBtnBatal[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SimBtnBatal[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SimBtnBatal[playerid], true);

    // 9. Navigation Row: Naik (Center X: 481.0, Y: 242.0) & Turun (Center X: 569.0, Y: 242.0)
    TD_SimBtnNaik[playerid] = CreatePlayerTextDraw(playerid, 481.0, 242.0, "Naik");
    PlayerTextDrawFont(playerid, TD_SimBtnNaik[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SimBtnNaik[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_SimBtnNaik[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SimBtnNaik[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_SimBtnNaik[playerid], COLOR_SIM_SLATE);
    PlayerTextDrawTextSize(playerid, TD_SimBtnNaik[playerid], 14.0, 82.0);
    PlayerTextDrawAlignment(playerid, TD_SimBtnNaik[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SimBtnNaik[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SimBtnNaik[playerid], true);

    TD_SimBtnTurun[playerid] = CreatePlayerTextDraw(playerid, 569.0, 242.0, "Turun");
    PlayerTextDrawFont(playerid, TD_SimBtnTurun[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_SimBtnTurun[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_SimBtnTurun[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_SimBtnTurun[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_SimBtnTurun[playerid], COLOR_SIM_SLATE);
    PlayerTextDrawTextSize(playerid, TD_SimBtnTurun[playerid], 14.0, 82.0);
    PlayerTextDrawAlignment(playerid, TD_SimBtnTurun[playerid], 2);
    PlayerTextDrawSetOutline(playerid, TD_SimBtnTurun[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_SimBtnTurun[playerid], true);
}

stock UpdateSimUI(playerid) {
    if (!gPlayerData[playerid][p_InSimUI]) return;

    new const simNames[3][] = {
        "SIM A",
        "SIM B",
        "SIM C"
    };

    for (new i = 0; i < 3; i++) {
        new label[32];
        if (gPlayerData[playerid][p_SelectedSimIndex] == i) {
            format(label, sizeof(label), "> %s", simNames[i]);
            PlayerTextDrawSetString(playerid, TD_SimSlot[playerid][i], label);
            PlayerTextDrawBoxColor(playerid, TD_SimSlot[playerid][i], COLOR_SIM_PURPLE);
        } else {
            format(label, sizeof(label), "%s", simNames[i]);
            PlayerTextDrawSetString(playerid, TD_SimSlot[playerid][i], label);
            PlayerTextDrawBoxColor(playerid, TD_SimSlot[playerid][i], COLOR_SIM_EMPTY);
        }
        PlayerTextDrawShow(playerid, TD_SimSlot[playerid][i]);
    }
}

stock ShowSimPanelUI(playerid) {
    if (!CheckSpawned(playerid)) return 0;

    // Sembunyikan HUD pojok kanan atas sementara waktu (seperti /inv)
    DestroyPlayerMoneyHUD(playerid);

    // Tutup kartu SIM jika sebelumnya sedang terbuka
    if (gShowingSIMCard[playerid]) {
        gShowingSIMCard[playerid] = false;
        DestroyPlayerSIMCardTextDraws(playerid);
    }

    CreatePlayerSimMenuTextDraws(playerid);

    gPlayerData[playerid][p_InSimUI] = true;
    if (gPlayerData[playerid][p_SelectedSimIndex] < 0 || gPlayerData[playerid][p_SelectedSimIndex] > 2) {
        gPlayerData[playerid][p_SelectedSimIndex] = 0;
    }

    // Show Elements
    PlayerTextDrawShow(playerid, TD_SimMainBox[playerid]);
    PlayerTextDrawShow(playerid, TD_SimTopBar[playerid]);
    PlayerTextDrawShow(playerid, TD_SimCloseBtn[playerid]);
    PlayerTextDrawShow(playerid, TD_SimHeader[playerid]);

    UpdateSimUI(playerid);

    PlayerTextDrawShow(playerid, TD_SimBtnLihat[playerid]);
    PlayerTextDrawShow(playerid, TD_SimBtnTunjukkan[playerid]);
    PlayerTextDrawShow(playerid, TD_SimBtnBatal[playerid]);
    PlayerTextDrawShow(playerid, TD_SimBtnNaik[playerid]);
    PlayerTextDrawShow(playerid, TD_SimBtnTurun[playerid]);

    SelectTextDraw(playerid, COLOR_SIM_PURPLE);
    PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
    return 1;
}

stock CloseSimPanelUI(playerid, bool:cancelSelect = true) {
    if (!gPlayerData[playerid][p_InSimUI]) return;

    gPlayerData[playerid][p_InSimUI] = false;
    if (cancelSelect) {
        CancelSelectTextDraw(playerid);
    }
    DestroyPlayerSimMenuTextDraws(playerid);
    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);

    // Kembalikan & segarkan HUD jika tidak ada UI layar kanan lain yang aktif
    if (!gShowingSIMCard[playerid] && !gPlayerData[playerid][p_InInventoryUI] && !gShowingKTP[playerid]) {
        CreatePlayerMoneyHUD(playerid);
        UpdatePlayerMoneyHUD(playerid);
        ShowPlayerMoneyHUD(playerid);
    }
}

// ============================================================
//  2. UI Kartu Resmi "SANTARA Driving License" (Desain Merah-Putih)
// ============================================================

stock HidePlayerSIMCard(viewerid) {
    if (!gShowingSIMCard[viewerid]) return;
    gShowingSIMCard[viewerid] = false;
    DestroyPlayerSIMCardTextDraws(viewerid);
    CancelSelectTextDraw(viewerid);
    PlayerPlaySound(viewerid, 1084, 0.0, 0.0, 0.0);

    // Kembalikan & segarkan HUD jika tidak ada UI layar kanan lain yang aktif
    if (!gPlayerData[viewerid][p_InSimUI] && !gPlayerData[viewerid][p_InInventoryUI] && !gShowingKTP[viewerid]) {
        CreatePlayerMoneyHUD(viewerid);
        UpdatePlayerMoneyHUD(viewerid);
        ShowPlayerMoneyHUD(viewerid);
    }
}

stock ShowPlayerSIMCard(viewerid, ownerid, simType) {
    if (!IsPlayerConnected(viewerid) || !IsPlayerConnected(ownerid)) return 0;

    // Sembunyikan HUD pojok kanan atas sementara waktu
    DestroyPlayerMoneyHUD(viewerid);

    DestroyPlayerSIMCardTextDraws(viewerid);
    gShowingSIMCard[viewerid] = true;

    new const simLetter[3][] = {"A", "B", "C"};

    // 1. Dark Outer Border (X: 364.0 s/d 626.0, Y: 124.0 s/d 300.0)
    TD_SIMCard_Border[viewerid] = CreatePlayerTextDraw(viewerid, 364.0, 124.0, "_");
    PlayerTextDrawUseBox(viewerid, TD_SIMCard_Border[viewerid], true);
    PlayerTextDrawBoxColor(viewerid, TD_SIMCard_Border[viewerid], 0x1A1A24FF);
    PlayerTextDrawTextSize(viewerid, TD_SIMCard_Border[viewerid], 626.0, 0.0);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_Border[viewerid], 0.0, 20.0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_Border[viewerid], false);

    // 2. Pure White Card Background Body (X: 365.0 s/d 625.0, Y: 125.0)
    TD_SIMCard_Bg[viewerid] = CreatePlayerTextDraw(viewerid, 365.0, 125.0, "_");
    PlayerTextDrawUseBox(viewerid, TD_SIMCard_Bg[viewerid], true);
    PlayerTextDrawBoxColor(viewerid, TD_SIMCard_Bg[viewerid], 0xFFFFFFFF);
    PlayerTextDrawTextSize(viewerid, TD_SIMCard_Bg[viewerid], 625.0, 0.0);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_Bg[viewerid], 0.0, 19.8);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_Bg[viewerid], false);

    // 3. Bright Red Header Bar (X: 365.0 s/d 625.0, Y: 125.0 .. 158.0)
    TD_SIMCard_RedHeader[viewerid] = CreatePlayerTextDraw(viewerid, 365.0, 125.0, "_");
    PlayerTextDrawUseBox(viewerid, TD_SIMCard_RedHeader[viewerid], true);
    PlayerTextDrawBoxColor(viewerid, TD_SIMCard_RedHeader[viewerid], 0xDE222AFF);
    PlayerTextDrawTextSize(viewerid, TD_SIMCard_RedHeader[viewerid], 625.0, 0.0);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_RedHeader[viewerid], 0.0, 3.8);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_RedHeader[viewerid], false);

    // 4. Header Text "SANTARA" (Large Bold White, X: 372.0, Y: 128.0)
    TD_SIMCard_Title[viewerid] = CreatePlayerTextDraw(viewerid, 372.0, 128.0, "SANTARA");
    PlayerTextDrawFont(viewerid, TD_SIMCard_Title[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_Title[viewerid], 0.32, 1.70);
    PlayerTextDrawColor(viewerid, TD_SIMCard_Title[viewerid], 0xFFFFFFFF);
    PlayerTextDrawSetProportional(viewerid, TD_SIMCard_Title[viewerid], true);
    PlayerTextDrawSetOutline(viewerid, TD_SIMCard_Title[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_SIMCard_Title[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_Title[viewerid], false);

    // 5. Header Right Text "Driving License" (Medium White, Center X: 560.0, Y: 137.0)
    TD_SIMCard_SubHeader[viewerid] = CreatePlayerTextDraw(viewerid, 560.0, 137.0, "Driving License");
    PlayerTextDrawFont(viewerid, TD_SIMCard_SubHeader[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_SubHeader[viewerid], 0.16, 1.00);
    PlayerTextDrawColor(viewerid, TD_SIMCard_SubHeader[viewerid], 0xFFFFFFFF);
    PlayerTextDrawAlignment(viewerid, TD_SIMCard_SubHeader[viewerid], 2);
    PlayerTextDrawSetProportional(viewerid, TD_SIMCard_SubHeader[viewerid], true);
    PlayerTextDrawSetOutline(viewerid, TD_SIMCard_SubHeader[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_SIMCard_SubHeader[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_SubHeader[viewerid], false);

    // 6. Tombol Tutup [ X ] di Kanan Atas Header
    TD_SIMCard_Close[viewerid] = CreatePlayerTextDraw(viewerid, 614.0, 127.0, "X");
    PlayerTextDrawFont(viewerid, TD_SIMCard_Close[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_Close[viewerid], 0.18, 0.95);
    PlayerTextDrawColor(viewerid, TD_SIMCard_Close[viewerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(viewerid, TD_SIMCard_Close[viewerid], true);
    PlayerTextDrawBoxColor(viewerid, TD_SIMCard_Close[viewerid], 0x8A1010FF);
    PlayerTextDrawTextSize(viewerid, TD_SIMCard_Close[viewerid], 622.0, 10.0);
    PlayerTextDrawAlignment(viewerid, TD_SIMCard_Close[viewerid], 2);
    PlayerTextDrawSetOutline(viewerid, TD_SIMCard_Close[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_SIMCard_Close[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_Close[viewerid], true);

    // 7. Subheader Merah "Surat Izin Mengemudi" (X: 372.0, Y: 161.0)
    TD_SIMCard_Subtitle[viewerid] = CreatePlayerTextDraw(viewerid, 372.0, 161.0, "Surat Izin Mengemudi");
    PlayerTextDrawFont(viewerid, TD_SIMCard_Subtitle[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_Subtitle[viewerid], 0.16, 0.95);
    PlayerTextDrawColor(viewerid, TD_SIMCard_Subtitle[viewerid], 0xDE222AFF);
    PlayerTextDrawSetProportional(viewerid, TD_SIMCard_Subtitle[viewerid], true);
    PlayerTextDrawSetOutline(viewerid, TD_SIMCard_Subtitle[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_SIMCard_Subtitle[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_Subtitle[viewerid], false);

    // 8. Badge Golongan SIM (X: 585.0, Y: 161.0)
    new badgeStr[32];
    format(badgeStr, sizeof(badgeStr), "GOLONGAN: %s", simLetter[simType]);
    TD_SIMCard_Badge[viewerid] = CreatePlayerTextDraw(viewerid, 585.0, 161.0, badgeStr);
    PlayerTextDrawFont(viewerid, TD_SIMCard_Badge[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_Badge[viewerid], 0.16, 0.95);
    PlayerTextDrawColor(viewerid, TD_SIMCard_Badge[viewerid], 0xDE222AFF);
    PlayerTextDrawAlignment(viewerid, TD_SIMCard_Badge[viewerid], 2);
    PlayerTextDrawSetProportional(viewerid, TD_SIMCard_Badge[viewerid], true);
    PlayerTextDrawSetOutline(viewerid, TD_SIMCard_Badge[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_SIMCard_Badge[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_Badge[viewerid], false);

    // 9. Baris Data (Field Label & Values)
    new valBuf[128], jobName[32];
    GetPlayerJobName(ownerid, jobName, sizeof(jobName));

    // Baris 1: Nama
    TD_SIMCard_LblNama[viewerid] = CreatePlayerTextDraw(viewerid, 372.0, 176.0, "Nama");
    PlayerTextDrawFont(viewerid, TD_SIMCard_LblNama[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_LblNama[viewerid], 0.13, 0.80);
    PlayerTextDrawColor(viewerid, TD_SIMCard_LblNama[viewerid], 0x222222FF);
    PlayerTextDrawSetProportional(viewerid, TD_SIMCard_LblNama[viewerid], true);
    PlayerTextDrawSetOutline(viewerid, TD_SIMCard_LblNama[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_SIMCard_LblNama[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_LblNama[viewerid], false);

    format(valBuf, sizeof(valBuf), ": %s", gPlayerData[ownerid][p_CharName]);
    TD_SIMCard_ValNama[viewerid] = CreatePlayerTextDraw(viewerid, 425.0, 176.0, valBuf);
    PlayerTextDrawFont(viewerid, TD_SIMCard_ValNama[viewerid], 1);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_ValNama[viewerid], 0.14, 0.85);
    PlayerTextDrawColor(viewerid, TD_SIMCard_ValNama[viewerid], 0x111111FF);
    PlayerTextDrawSetProportional(viewerid, TD_SIMCard_ValNama[viewerid], true);
    PlayerTextDrawSetOutline(viewerid, TD_SIMCard_ValNama[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_SIMCard_ValNama[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_ValNama[viewerid], false);

    // Baris 2: TTL
    TD_SIMCard_LblTTL[viewerid] = CreatePlayerTextDraw(viewerid, 372.0, 189.0, "TTL");
    PlayerTextDrawFont(viewerid, TD_SIMCard_LblTTL[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_LblTTL[viewerid], 0.13, 0.80);
    PlayerTextDrawColor(viewerid, TD_SIMCard_LblTTL[viewerid], 0x222222FF);
    PlayerTextDrawSetProportional(viewerid, TD_SIMCard_LblTTL[viewerid], true);
    PlayerTextDrawSetOutline(viewerid, TD_SIMCard_LblTTL[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_SIMCard_LblTTL[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_LblTTL[viewerid], false);

    format(valBuf, sizeof(valBuf), ": %s, %s", gPlayerData[ownerid][p_BirthPlace], gPlayerData[ownerid][p_BirthDate]);
    TD_SIMCard_ValTTL[viewerid] = CreatePlayerTextDraw(viewerid, 425.0, 189.0, valBuf);
    PlayerTextDrawFont(viewerid, TD_SIMCard_ValTTL[viewerid], 1);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_ValTTL[viewerid], 0.13, 0.80);
    PlayerTextDrawColor(viewerid, TD_SIMCard_ValTTL[viewerid], 0x111111FF);
    PlayerTextDrawSetProportional(viewerid, TD_SIMCard_ValTTL[viewerid], true);
    PlayerTextDrawSetOutline(viewerid, TD_SIMCard_ValTTL[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_SIMCard_ValTTL[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_ValTTL[viewerid], false);

    // Baris 3: Kelamin
    TD_SIMCard_LblGender[viewerid] = CreatePlayerTextDraw(viewerid, 372.0, 202.0, "Kelamin");
    PlayerTextDrawFont(viewerid, TD_SIMCard_LblGender[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_LblGender[viewerid], 0.13, 0.80);
    PlayerTextDrawColor(viewerid, TD_SIMCard_LblGender[viewerid], 0x222222FF);
    PlayerTextDrawSetProportional(viewerid, TD_SIMCard_LblGender[viewerid], true);
    PlayerTextDrawSetOutline(viewerid, TD_SIMCard_LblGender[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_SIMCard_LblGender[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_LblGender[viewerid], false);

    format(valBuf, sizeof(valBuf), ": %s (Gol: O)", (gPlayerData[ownerid][p_Gender] == 2) ? "PEREMPUAN" : "LAKI-LAKI");
    TD_SIMCard_ValGender[viewerid] = CreatePlayerTextDraw(viewerid, 425.0, 202.0, valBuf);
    PlayerTextDrawFont(viewerid, TD_SIMCard_ValGender[viewerid], 1);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_ValGender[viewerid], 0.13, 0.80);
    PlayerTextDrawColor(viewerid, TD_SIMCard_ValGender[viewerid], 0x111111FF);
    PlayerTextDrawSetProportional(viewerid, TD_SIMCard_ValGender[viewerid], true);
    PlayerTextDrawSetOutline(viewerid, TD_SIMCard_ValGender[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_SIMCard_ValGender[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_ValGender[viewerid], false);

    // Baris 4: Alamat
    TD_SIMCard_LblAlamat[viewerid] = CreatePlayerTextDraw(viewerid, 372.0, 215.0, "Alamat");
    PlayerTextDrawFont(viewerid, TD_SIMCard_LblAlamat[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_LblAlamat[viewerid], 0.13, 0.80);
    PlayerTextDrawColor(viewerid, TD_SIMCard_LblAlamat[viewerid], 0x222222FF);
    PlayerTextDrawSetProportional(viewerid, TD_SIMCard_LblAlamat[viewerid], true);
    PlayerTextDrawSetOutline(viewerid, TD_SIMCard_LblAlamat[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_SIMCard_LblAlamat[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_LblAlamat[viewerid], false);

    format(valBuf, sizeof(valBuf), ": Kota %s, Santara", gPlayerData[ownerid][p_BirthPlace]);
    TD_SIMCard_ValAlamat[viewerid] = CreatePlayerTextDraw(viewerid, 425.0, 215.0, valBuf);
    PlayerTextDrawFont(viewerid, TD_SIMCard_ValAlamat[viewerid], 1);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_ValAlamat[viewerid], 0.13, 0.80);
    PlayerTextDrawColor(viewerid, TD_SIMCard_ValAlamat[viewerid], 0x111111FF);
    PlayerTextDrawSetProportional(viewerid, TD_SIMCard_ValAlamat[viewerid], true);
    PlayerTextDrawSetOutline(viewerid, TD_SIMCard_ValAlamat[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_SIMCard_ValAlamat[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_ValAlamat[viewerid], false);

    // Baris 5: Pekerjaan
    TD_SIMCard_LblJob[viewerid] = CreatePlayerTextDraw(viewerid, 372.0, 228.0, "Profesi");
    PlayerTextDrawFont(viewerid, TD_SIMCard_LblJob[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_LblJob[viewerid], 0.13, 0.80);
    PlayerTextDrawColor(viewerid, TD_SIMCard_LblJob[viewerid], 0x222222FF);
    PlayerTextDrawSetProportional(viewerid, TD_SIMCard_LblJob[viewerid], true);
    PlayerTextDrawSetOutline(viewerid, TD_SIMCard_LblJob[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_SIMCard_LblJob[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_LblJob[viewerid], false);

    format(valBuf, sizeof(valBuf), ": %s", jobName);
    TD_SIMCard_ValJob[viewerid] = CreatePlayerTextDraw(viewerid, 425.0, 228.0, valBuf);
    PlayerTextDrawFont(viewerid, TD_SIMCard_ValJob[viewerid], 1);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_ValJob[viewerid], 0.13, 0.80);
    PlayerTextDrawColor(viewerid, TD_SIMCard_ValJob[viewerid], 0x111111FF);
    PlayerTextDrawSetProportional(viewerid, TD_SIMCard_ValJob[viewerid], true);
    PlayerTextDrawSetOutline(viewerid, TD_SIMCard_ValJob[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_SIMCard_ValJob[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_ValJob[viewerid], false);

    // Baris 6: No. SIM
    TD_SIMCard_LblNoSIM[viewerid] = CreatePlayerTextDraw(viewerid, 372.0, 241.0, "No. SIM");
    PlayerTextDrawFont(viewerid, TD_SIMCard_LblNoSIM[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_LblNoSIM[viewerid], 0.13, 0.80);
    PlayerTextDrawColor(viewerid, TD_SIMCard_LblNoSIM[viewerid], 0x222222FF);
    PlayerTextDrawSetProportional(viewerid, TD_SIMCard_LblNoSIM[viewerid], true);
    PlayerTextDrawSetOutline(viewerid, TD_SIMCard_LblNoSIM[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_SIMCard_LblNoSIM[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_LblNoSIM[viewerid], false);

    format(valBuf, sizeof(valBuf), ": SIM-%s-%04d-%04d", simLetter[simType], gPlayerData[ownerid][p_AccountID], gPlayerData[ownerid][p_CharID]);
    TD_SIMCard_ValNoSIM[viewerid] = CreatePlayerTextDraw(viewerid, 425.0, 241.0, valBuf);
    PlayerTextDrawFont(viewerid, TD_SIMCard_ValNoSIM[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_ValNoSIM[viewerid], 0.14, 0.85);
    PlayerTextDrawColor(viewerid, TD_SIMCard_ValNoSIM[viewerid], 0xDE222AFF);
    PlayerTextDrawSetProportional(viewerid, TD_SIMCard_ValNoSIM[viewerid], true);
    PlayerTextDrawSetOutline(viewerid, TD_SIMCard_ValNoSIM[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_SIMCard_ValNoSIM[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_ValNoSIM[viewerid], false);

    // Baris 7: Berlaku
    TD_SIMCard_LblBerlaku[viewerid] = CreatePlayerTextDraw(viewerid, 372.0, 254.0, "Berlaku");
    PlayerTextDrawFont(viewerid, TD_SIMCard_LblBerlaku[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_LblBerlaku[viewerid], 0.13, 0.80);
    PlayerTextDrawColor(viewerid, TD_SIMCard_LblBerlaku[viewerid], 0x222222FF);
    PlayerTextDrawSetProportional(viewerid, TD_SIMCard_LblBerlaku[viewerid], true);
    PlayerTextDrawSetOutline(viewerid, TD_SIMCard_LblBerlaku[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_SIMCard_LblBerlaku[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_LblBerlaku[viewerid], false);

    TD_SIMCard_ValBerlaku[viewerid] = CreatePlayerTextDraw(viewerid, 425.0, 254.0, ": SEUMUR HIDUP");
    PlayerTextDrawFont(viewerid, TD_SIMCard_ValBerlaku[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_ValBerlaku[viewerid], 0.13, 0.80);
    PlayerTextDrawColor(viewerid, TD_SIMCard_ValBerlaku[viewerid], 0x27AE60FF);
    PlayerTextDrawSetProportional(viewerid, TD_SIMCard_ValBerlaku[viewerid], true);
    PlayerTextDrawSetOutline(viewerid, TD_SIMCard_ValBerlaku[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_SIMCard_ValBerlaku[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_ValBerlaku[viewerid], false);

    // 10. Pas Foto 3D Avatar (Sisi Kanan Kartu: X 554.0 s/d 616.0, Y: 175.0)
    TD_SIMCard_PhotoBorder[viewerid] = CreatePlayerTextDraw(viewerid, 553.0, 175.0, "_");
    PlayerTextDrawUseBox(viewerid, TD_SIMCard_PhotoBorder[viewerid], true);
    PlayerTextDrawBoxColor(viewerid, TD_SIMCard_PhotoBorder[viewerid], 0xCCCCCCFF);
    PlayerTextDrawTextSize(viewerid, TD_SIMCard_PhotoBorder[viewerid], 617.0, 0.0);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_PhotoBorder[viewerid], 0.0, 6.2);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_PhotoBorder[viewerid], false);

    TD_SIMCard_PhotoBg[viewerid] = CreatePlayerTextDraw(viewerid, 554.0, 176.0, "_");
    PlayerTextDrawUseBox(viewerid, TD_SIMCard_PhotoBg[viewerid], true);
    PlayerTextDrawBoxColor(viewerid, TD_SIMCard_PhotoBg[viewerid], 0x2980B9FF);
    PlayerTextDrawTextSize(viewerid, TD_SIMCard_PhotoBg[viewerid], 616.0, 0.0);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_PhotoBg[viewerid], 0.0, 6.0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_PhotoBg[viewerid], false);

    TD_SIMCard_Photo[viewerid] = CreatePlayerTextDraw(viewerid, 554.0, 176.0, "_");
    PlayerTextDrawFont(viewerid, TD_SIMCard_Photo[viewerid], TEXT_DRAW_FONT_MODEL_PREVIEW);
    PlayerTextDrawTextSize(viewerid, TD_SIMCard_Photo[viewerid], 62.0, 55.0);
    PlayerTextDrawSetPreviewModel(viewerid, TD_SIMCard_Photo[viewerid], gPlayerData[ownerid][p_Skin]);
    PlayerTextDrawSetPreviewRot(viewerid, TD_SIMCard_Photo[viewerid], -10.0, 0.0, -12.0, 0.85);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_Photo[viewerid], false);

    // 11. Cap Digital & Tanda Tangan
    TD_SIMCard_SignCity[viewerid] = CreatePlayerTextDraw(viewerid, 585.0, 236.0, "KORLANTAS POLRI");
    PlayerTextDrawFont(viewerid, TD_SIMCard_SignCity[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_SignCity[viewerid], 0.12, 0.70);
    PlayerTextDrawColor(viewerid, TD_SIMCard_SignCity[viewerid], 0x333333FF);
    PlayerTextDrawAlignment(viewerid, TD_SIMCard_SignCity[viewerid], 2);
    PlayerTextDrawSetProportional(viewerid, TD_SIMCard_SignCity[viewerid], true);
    PlayerTextDrawSetOutline(viewerid, TD_SIMCard_SignCity[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_SIMCard_SignCity[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_SignCity[viewerid], false);

    TD_SIMCard_SignStamp[viewerid] = CreatePlayerTextDraw(viewerid, 585.0, 245.0, "[ TTD DIGITAL ]");
    PlayerTextDrawFont(viewerid, TD_SIMCard_SignStamp[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_SignStamp[viewerid], 0.11, 0.65);
    PlayerTextDrawColor(viewerid, TD_SIMCard_SignStamp[viewerid], 0xDE222AFF);
    PlayerTextDrawAlignment(viewerid, TD_SIMCard_SignStamp[viewerid], 2);
    PlayerTextDrawSetProportional(viewerid, TD_SIMCard_SignStamp[viewerid], true);
    PlayerTextDrawSetOutline(viewerid, TD_SIMCard_SignStamp[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_SIMCard_SignStamp[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_SignStamp[viewerid], false);

    // 12. Hint Penutup
    TD_SIMCard_Hint[viewerid] = CreatePlayerTextDraw(viewerid, 495.0, 282.0, "~w~Tekan ~y~ESC ~w~atau klik ~r~[ X ] ~w~untuk menutup");
    PlayerTextDrawFont(viewerid, TD_SIMCard_Hint[viewerid], 1);
    PlayerTextDrawLetterSize(viewerid, TD_SIMCard_Hint[viewerid], 0.15, 0.85);
    PlayerTextDrawColor(viewerid, TD_SIMCard_Hint[viewerid], 0xFFFFFFFF);
    PlayerTextDrawAlignment(viewerid, TD_SIMCard_Hint[viewerid], 2);
    PlayerTextDrawSetProportional(viewerid, TD_SIMCard_Hint[viewerid], true);
    PlayerTextDrawSetOutline(viewerid, TD_SIMCard_Hint[viewerid], 1);
    PlayerTextDrawSetShadow(viewerid, TD_SIMCard_Hint[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_SIMCard_Hint[viewerid], false);

    // Tampilkan Seluruh TextDraw
    PlayerTextDrawShow(viewerid, TD_SIMCard_Border[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_Bg[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_RedHeader[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_Close[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_Title[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_SubHeader[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_Subtitle[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_Badge[viewerid]);

    PlayerTextDrawShow(viewerid, TD_SIMCard_LblNama[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_ValNama[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_LblTTL[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_ValTTL[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_LblGender[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_ValGender[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_LblAlamat[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_ValAlamat[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_LblJob[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_ValJob[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_LblNoSIM[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_ValNoSIM[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_LblBerlaku[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_ValBerlaku[viewerid]);

    PlayerTextDrawShow(viewerid, TD_SIMCard_PhotoBorder[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_PhotoBg[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_Photo[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_SignCity[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_SignStamp[viewerid]);
    PlayerTextDrawShow(viewerid, TD_SIMCard_Hint[viewerid]);

    SelectTextDraw(viewerid, 0xDE222AFF);
    PlayerPlaySound(viewerid, 1058, 0.0, 0.0, 0.0);
    return 1;
}

stock bool:PlayerHasSpecificSIM(playerid, simIndex) {
    switch (simIndex) {
        case 0: return gPlayerData[playerid][p_HasSIM_A];
        case 1: return gPlayerData[playerid][p_HasSIM_B];
        case 2: return gPlayerData[playerid][p_HasSIM_C];
    }
    return false;
}

stock HandleSimUIClick(playerid, PlayerText:playertextid) {
    // 1. Cek Interaksi Kartu SIM Fisik Terbuka
    if (gShowingSIMCard[playerid]) {
        if (playertextid == TD_SIMCard_Close[playerid]) {
            HidePlayerSIMCard(playerid);
            return 1;
        }
        return 1;
    }

    if (!gPlayerData[playerid][p_InSimUI]) return 0;

    // 2. Tombol Close [X] atau Batal Menu
    if (playertextid == TD_SimCloseBtn[playerid] || playertextid == TD_SimBtnBatal[playerid]) {
        CloseSimPanelUI(playerid, true);
        return 1;
    }

    // 3. Tombol Navigasi Naik
    if (playertextid == TD_SimBtnNaik[playerid]) {
        gPlayerData[playerid][p_SelectedSimIndex]--;
        if (gPlayerData[playerid][p_SelectedSimIndex] < 0) {
            gPlayerData[playerid][p_SelectedSimIndex] = 2;
        }
        UpdateSimUI(playerid);
        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
        return 1;
    }

    // 4. Tombol Navigasi Turun
    if (playertextid == TD_SimBtnTurun[playerid]) {
        gPlayerData[playerid][p_SelectedSimIndex]++;
        if (gPlayerData[playerid][p_SelectedSimIndex] > 2) {
            gPlayerData[playerid][p_SelectedSimIndex] = 0;
        }
        UpdateSimUI(playerid);
        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
        return 1;
    }

    // 5. Klik Langsung ke Slot SIM A, B, atau C
    for (new s = 0; s < 3; s++) {
        if (playertextid == TD_SimSlot[playerid][s]) {
            gPlayerData[playerid][p_SelectedSimIndex] = s;
            UpdateSimUI(playerid);
            PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
            return 1;
        }
    }

    // 6. Tombol [ Lihat ] (Tampilkan Kartu SIM Fisik Digital tanpa menutup SelectTextDraw)
    if (playertextid == TD_SimBtnLihat[playerid]) {
        new idx = gPlayerData[playerid][p_SelectedSimIndex];
        new const simNames[3][] = {"SIM A", "SIM B", "SIM C"};

        if (!PlayerHasSpecificSIM(playerid, idx)) {
            new errMsg[128];
            format(errMsg, sizeof(errMsg), "  [SIM] Anda belum memiliki lisensi %s! Silakan buat di Kantor Satpas DMV San Fierro.", simNames[idx]);
            SendClientMessage(playerid, COL_RED, errMsg);
            PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
            return 1;
        }

        CloseSimPanelUI(playerid, false);
        ShowPlayerSIMCard(playerid, playerid, idx);
        return 1;
    }

    // 7. Tombol [ Tunjukkan ] (Membuka dialog input target ID)
    if (playertextid == TD_SimBtnTunjukkan[playerid]) {
        new idx = gPlayerData[playerid][p_SelectedSimIndex];
        new const simNames[3][] = {"SIM A", "SIM B", "SIM C"};

        if (!PlayerHasSpecificSIM(playerid, idx)) {
            new errMsg[128];
            format(errMsg, sizeof(errMsg), "  [SIM] Anda belum memiliki lisensi %s untuk diperlihatkan!", simNames[idx]);
            SendClientMessage(playerid, COL_RED, errMsg);
            PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
            return 1;
        }

        new prompt[256];
        format(prompt, sizeof(prompt),
            "{FFFFFF}Anda akan memperlihatkan {00EEFF}%s{FFFFFF} Anda.\n\n" \
            "{FFFFFF}Masukkan {FFFF00}Player ID{FFFFFF} pemain terdekat yang ingin Anda perlihatkan SIM:",
            simNames[idx]);

        ShowPlayerDialog(playerid, DLG_SIM_SHOW_TARGET, DIALOG_STYLE_INPUT,
            "{5814EE}Tunjukkan Surat Izin Mengemudi", prompt, "Tunjukkan", "Batal");
        return 1;
    }

    return 0;
}

stock HandleSimUIDialog(playerid, dialogid, response, const inputtext[]) {
    if (dialogid == DLG_SIM_SHOW_TARGET) {
        if (!response) return 1;

        new targetid = strval(inputtext);
        if (strlen(inputtext) == 0 || !IsPlayerConnected(targetid) || !gPlayerData[targetid][p_LoggedIn] || !gPlayerData[targetid][p_Spawned]) {
            SendClientMessage(playerid, COL_RED, "  [SIM] ID pemain target tidak valid atau sedang offline!");
            PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
            return 1;
        }

        if (targetid == playerid) {
            new idx = gPlayerData[playerid][p_SelectedSimIndex];
            CloseSimPanelUI(playerid, false);
            ShowPlayerSIMCard(playerid, playerid, idx);
            return 1;
        }

        new Float:tx, Float:ty, Float:tz;
        GetPlayerPos(targetid, tx, ty, tz);
        if (!IsPlayerInRangeOfPoint(playerid, 5.0, tx, ty, tz)) {
            SendClientMessage(playerid, COL_RED, "  [SIM] Pemain target berada terlalu jauh dari Anda (maks 5 meter)!");
            PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
            return 1;
        }

        new idx = gPlayerData[playerid][p_SelectedSimIndex];
        new const simNames[3][] = {"SIM A", "SIM B", "SIM C"};

        // Tampilkan kartu SIM ke targetid dan pengirim
        CloseSimPanelUI(playerid, false);
        ShowPlayerSIMCard(targetid, playerid, idx);
        ShowPlayerSIMCard(playerid, playerid, idx);

        new myName[48], targetName[48], rpMsg[160], notifMsg[144];
        GetCharName(playerid, myName);
        GetCharName(targetid, targetName);

        format(rpMsg, sizeof(rpMsg), "%s memperlihatkan kartu fisik %s miliknya kepada %s.", myName, simNames[idx], targetName);
        DoProximityRaw(playerid, rpMsg, DIST_RP, COL_PURPLE);

        format(notifMsg, sizeof(notifMsg), "  [SIM] Anda telah memperlihatkan {00EEFF}%s{FFFFFF} Anda kepada {FFFF00}%s{FFFFFF}.", simNames[idx], targetName);
        SendClientMessage(playerid, COL_GREEN, notifMsg);

        format(notifMsg, sizeof(notifMsg), "  [SIM] {FFFF00}%s{FFFFFF} memperlihatkan kartu {00EEFF}%s{FFFFFF} miliknya kepada Anda.", myName, simNames[idx]);
        SendClientMessage(targetid, COL_GREEN, notifMsg);

        PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
        PlayerPlaySound(targetid, 1058, 0.0, 0.0, 0.0);
        return 1;
    }
    return 0;
}

// Perintah /sim untuk membuka Panel UI SIM di sisi kanan layar
CMD:sim(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    if (gShowingSIMCard[playerid]) {
        HidePlayerSIMCard(playerid);
    }
    if (gShowingKTP[playerid]) {
        HidePlayerKTPCard(playerid);
    }
    ShowSimPanelUI(playerid);
    return 1;
}
