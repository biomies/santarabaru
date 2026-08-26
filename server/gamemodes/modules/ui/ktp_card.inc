#if defined _MODULE_KTP_CARD_INC
    #endinput
#endif
#define _MODULE_KTP_CARD_INC

// ============================================================
//  SantaraBaru Roleplay - Indonesian e-KTP Ultra-Clean Right-Side UI
//  100% Native TextDraws, Sharp Typography (No Shadow/Blur), Non-Obstructive
// ============================================================

new bool:gShowingKTP[MAX_PLAYERS]             = {false, ...};

// Container Box & Borders (Kanan Layar: X 365.0 s/d 625.0)
new PlayerText:TD_KTP_Border[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_KTP_CardBg[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_KTP_HeaderBar[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_KTP_GoldLine[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_KTP_FootLine[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};

// Header
new PlayerText:TD_KTP_Header1[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_KTP_Header2[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_KTP_Header3[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_KTP_Close[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};

// NIK
new PlayerText:TD_KTP_NIK[MAX_PLAYERS]        = {PlayerText:INVALID_TEXT_DRAW, ...};

// Label & Value Rows (Terpisah agar tajam & tidak berbayang)
new PlayerText:TD_KTP_LblNama[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_KTP_ValNama[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};

new PlayerText:TD_KTP_LblTTL[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_KTP_ValTTL[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};

new PlayerText:TD_KTP_LblGender[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_KTP_ValGender[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};

new PlayerText:TD_KTP_LblAlamat[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_KTP_ValAlamat[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};

new PlayerText:TD_KTP_LblWarga[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_KTP_ValWarga[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};

new PlayerText:TD_KTP_LblStatus[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_KTP_ValStatus[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};

new PlayerText:TD_KTP_LblBerlaku[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_KTP_ValBerlaku[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};

// Pas Foto 3D & Cap Tanda Tangan
new PlayerText:TD_KTP_PhotoBorder[MAX_PLAYERS]= {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_KTP_PhotoBg[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_KTP_Photo[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_KTP_SignCity[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_KTP_SignDate[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_KTP_SignStamp[MAX_PLAYERS]  = {PlayerText:INVALID_TEXT_DRAW, ...};

// Petunjuk Tutup
new PlayerText:TD_KTP_Hint[MAX_PLAYERS]       = {PlayerText:INVALID_TEXT_DRAW, ...};

stock DestroyPlayerKTPTextDraws(playerid) {
    if (TD_KTP_Border[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_Border[playerid]);
        TD_KTP_Border[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_CardBg[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_CardBg[playerid]);
        TD_KTP_CardBg[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_HeaderBar[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_HeaderBar[playerid]);
        TD_KTP_HeaderBar[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_GoldLine[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_GoldLine[playerid]);
        TD_KTP_GoldLine[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_FootLine[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_FootLine[playerid]);
        TD_KTP_FootLine[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_Header1[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_Header1[playerid]);
        TD_KTP_Header1[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_Header2[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_Header2[playerid]);
        TD_KTP_Header2[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_Header3[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_Header3[playerid]);
        TD_KTP_Header3[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_Close[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_Close[playerid]);
        TD_KTP_Close[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_NIK[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_NIK[playerid]);
        TD_KTP_NIK[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_LblNama[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_LblNama[playerid]);
        TD_KTP_LblNama[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_ValNama[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_ValNama[playerid]);
        TD_KTP_ValNama[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_LblTTL[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_LblTTL[playerid]);
        TD_KTP_LblTTL[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_ValTTL[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_ValTTL[playerid]);
        TD_KTP_ValTTL[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_LblGender[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_LblGender[playerid]);
        TD_KTP_LblGender[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_ValGender[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_ValGender[playerid]);
        TD_KTP_ValGender[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_LblAlamat[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_LblAlamat[playerid]);
        TD_KTP_LblAlamat[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_ValAlamat[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_ValAlamat[playerid]);
        TD_KTP_ValAlamat[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_LblWarga[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_LblWarga[playerid]);
        TD_KTP_LblWarga[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_ValWarga[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_ValWarga[playerid]);
        TD_KTP_ValWarga[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_LblStatus[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_LblStatus[playerid]);
        TD_KTP_LblStatus[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_ValStatus[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_ValStatus[playerid]);
        TD_KTP_ValStatus[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_LblBerlaku[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_LblBerlaku[playerid]);
        TD_KTP_LblBerlaku[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_ValBerlaku[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_ValBerlaku[playerid]);
        TD_KTP_ValBerlaku[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_PhotoBorder[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_PhotoBorder[playerid]);
        TD_KTP_PhotoBorder[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_PhotoBg[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_PhotoBg[playerid]);
        TD_KTP_PhotoBg[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_Photo[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_Photo[playerid]);
        TD_KTP_Photo[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_SignCity[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_SignCity[playerid]);
        TD_KTP_SignCity[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_SignDate[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_SignDate[playerid]);
        TD_KTP_SignDate[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_SignStamp[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_SignStamp[playerid]);
        TD_KTP_SignStamp[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_KTP_Hint[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_KTP_Hint[playerid]);
        TD_KTP_Hint[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
}

stock ShowPlayerKTPCard(viewerid, ownerid) {
    if (!IsPlayerConnected(viewerid) || !IsPlayerConnected(ownerid)) return 0;

    // Bersihkan TextDraw KTP lama jika sedang terbuka
    DestroyPlayerKTPTextDraws(viewerid);
    gShowingKTP[viewerid] = true;

    //    1. Outer Dark Navy Border (Kanan Layar: 364.0 s/d 626.0)   
    TD_KTP_Border[viewerid] = CreatePlayerTextDraw(viewerid, 364.0, 124.0, "_");
    PlayerTextDrawUseBox(viewerid, TD_KTP_Border[viewerid], 1);
    PlayerTextDrawBoxColor(viewerid, TD_KTP_Border[viewerid], 0x143452FF);
    PlayerTextDrawTextSize(viewerid, TD_KTP_Border[viewerid], 626.0, 0.0);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_Border[viewerid], 0.0, 22.8);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_Border[viewerid], 0);

    //    2. Main Cyan Surface Box (Sky Cyan e-KTP)   
    TD_KTP_CardBg[viewerid] = CreatePlayerTextDraw(viewerid, 365.0, 125.0, "_");
    PlayerTextDrawUseBox(viewerid, TD_KTP_CardBg[viewerid], 1);
    PlayerTextDrawBoxColor(viewerid, TD_KTP_CardBg[viewerid], 0x8CD6EEFF);
    PlayerTextDrawTextSize(viewerid, TD_KTP_CardBg[viewerid], 625.0, 0.0);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_CardBg[viewerid], 0.0, 22.6);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_CardBg[viewerid], 0);

    //    3. Header Navy Bar   
    TD_KTP_HeaderBar[viewerid] = CreatePlayerTextDraw(viewerid, 365.0, 125.0, "_");
    PlayerTextDrawUseBox(viewerid, TD_KTP_HeaderBar[viewerid], 1);
    PlayerTextDrawBoxColor(viewerid, TD_KTP_HeaderBar[viewerid], 0x143452FF);
    PlayerTextDrawTextSize(viewerid, TD_KTP_HeaderBar[viewerid], 625.0, 0.0);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_HeaderBar[viewerid], 0.0, 3.5);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_HeaderBar[viewerid], 0);

    //    4. Gold Divider Line   
    TD_KTP_GoldLine[viewerid] = CreatePlayerTextDraw(viewerid, 365.0, 156.0, "_");
    PlayerTextDrawUseBox(viewerid, TD_KTP_GoldLine[viewerid], 1);
    PlayerTextDrawBoxColor(viewerid, TD_KTP_GoldLine[viewerid], 0xF1C40FFF);
    PlayerTextDrawTextSize(viewerid, TD_KTP_GoldLine[viewerid], 625.0, 0.0);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_GoldLine[viewerid], 0.0, 0.20);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_GoldLine[viewerid], 0);

    //    5. Header Texts (Tengah Header: X 495.0, Bebas Shadow/Outline)   
    TD_KTP_Header1[viewerid] = CreatePlayerTextDraw(viewerid, 495.0, 127.0, "PROVINSI SAN ANDREAS");
    PlayerTextDrawFont(viewerid, TD_KTP_Header1[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_Header1[viewerid], 0.16, 0.95);
    PlayerTextDrawColor(viewerid, TD_KTP_Header1[viewerid], 0xFFFFFFFF);
    PlayerTextDrawAlignment(viewerid, TD_KTP_Header1[viewerid], 2);
    PlayerTextDrawSetProportional(viewerid, TD_KTP_Header1[viewerid], 1);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_Header1[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_Header1[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_Header1[viewerid], 0);

    TD_KTP_Header2[viewerid] = CreatePlayerTextDraw(viewerid, 495.0, 137.0, "KOTA SANTARA");
    PlayerTextDrawFont(viewerid, TD_KTP_Header2[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_Header2[viewerid], 0.18, 1.05);
    PlayerTextDrawColor(viewerid, TD_KTP_Header2[viewerid], 0xF1C40FFF);
    PlayerTextDrawAlignment(viewerid, TD_KTP_Header2[viewerid], 2);
    PlayerTextDrawSetProportional(viewerid, TD_KTP_Header2[viewerid], 1);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_Header2[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_Header2[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_Header2[viewerid], 0);

    TD_KTP_Header3[viewerid] = CreatePlayerTextDraw(viewerid, 495.0, 147.0, "KARTU TANDA PENDUDUK ELEKTRONIK");
    PlayerTextDrawFont(viewerid, TD_KTP_Header3[viewerid], 1);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_Header3[viewerid], 0.13, 0.75);
    PlayerTextDrawColor(viewerid, TD_KTP_Header3[viewerid], 0xDCE8F2FF);
    PlayerTextDrawAlignment(viewerid, TD_KTP_Header3[viewerid], 2);
    PlayerTextDrawSetProportional(viewerid, TD_KTP_Header3[viewerid], 1);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_Header3[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_Header3[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_Header3[viewerid], 0);

    //    6. Tombol Tutup [ X ] di Kanan Header   
    TD_KTP_Close[viewerid] = CreatePlayerTextDraw(viewerid, 614.0, 127.0, "X");
    PlayerTextDrawFont(viewerid, TD_KTP_Close[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_Close[viewerid], 0.18, 0.95);
    PlayerTextDrawColor(viewerid, TD_KTP_Close[viewerid], 0xFF4D4DFF);
    PlayerTextDrawUseBox(viewerid, TD_KTP_Close[viewerid], 1);
    PlayerTextDrawBoxColor(viewerid, TD_KTP_Close[viewerid], 0x3B1818EE);
    PlayerTextDrawTextSize(viewerid, TD_KTP_Close[viewerid], 622.0, 10.0);
    PlayerTextDrawAlignment(viewerid, TD_KTP_Close[viewerid], 2);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_Close[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_Close[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_Close[viewerid], 1);

    //    7. NIK (Nomor Induk Kependudukan)   
    new nikStr[64];
    format(nikStr, sizeof(nikStr), "NIK  :  317104%02d%02d%02d%04d", 24, 8, 26, gPlayerData[ownerid][p_CharID]);
    TD_KTP_NIK[viewerid] = CreatePlayerTextDraw(viewerid, 372.0, 161.0, nikStr);
    PlayerTextDrawFont(viewerid, TD_KTP_NIK[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_NIK[viewerid], 0.20, 1.15);
    PlayerTextDrawColor(viewerid, TD_KTP_NIK[viewerid], 0x0C2236FF);
    PlayerTextDrawSetProportional(viewerid, TD_KTP_NIK[viewerid], 1);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_NIK[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_NIK[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_NIK[viewerid], 0);

    //    8. Form Baris Data (Independen, Tajam & Presisi)   
    new valBuf[128];

    // Baris 1: Nama
    TD_KTP_LblNama[viewerid] = CreatePlayerTextDraw(viewerid, 372.0, 177.0, "Nama");
    PlayerTextDrawFont(viewerid, TD_KTP_LblNama[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_LblNama[viewerid], 0.14, 0.85);
    PlayerTextDrawColor(viewerid, TD_KTP_LblNama[viewerid], 0x143452FF);
    PlayerTextDrawSetProportional(viewerid, TD_KTP_LblNama[viewerid], 1);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_LblNama[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_LblNama[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_LblNama[viewerid], 0);

    format(valBuf, sizeof(valBuf), ": %s", gPlayerData[ownerid][p_CharName]);
    TD_KTP_ValNama[viewerid] = CreatePlayerTextDraw(viewerid, 430.0, 177.0, valBuf);
    PlayerTextDrawFont(viewerid, TD_KTP_ValNama[viewerid], 1);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_ValNama[viewerid], 0.15, 0.90);
    PlayerTextDrawColor(viewerid, TD_KTP_ValNama[viewerid], 0x081C2DFF);
    PlayerTextDrawSetProportional(viewerid, TD_KTP_ValNama[viewerid], 1);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_ValNama[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_ValNama[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_ValNama[viewerid], 0);

    // Baris 2: TTL
    TD_KTP_LblTTL[viewerid] = CreatePlayerTextDraw(viewerid, 372.0, 191.0, "TTL");
    PlayerTextDrawFont(viewerid, TD_KTP_LblTTL[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_LblTTL[viewerid], 0.14, 0.85);
    PlayerTextDrawColor(viewerid, TD_KTP_LblTTL[viewerid], 0x143452FF);
    PlayerTextDrawSetProportional(viewerid, TD_KTP_LblTTL[viewerid], 1);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_LblTTL[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_LblTTL[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_LblTTL[viewerid], 0);

    format(valBuf, sizeof(valBuf), ": %s, %s", gPlayerData[ownerid][p_BirthPlace], gPlayerData[ownerid][p_BirthDate]);
    TD_KTP_ValTTL[viewerid] = CreatePlayerTextDraw(viewerid, 430.0, 191.0, valBuf);
    PlayerTextDrawFont(viewerid, TD_KTP_ValTTL[viewerid], 1);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_ValTTL[viewerid], 0.14, 0.85);
    PlayerTextDrawColor(viewerid, TD_KTP_ValTTL[viewerid], 0x081C2DFF);
    PlayerTextDrawSetProportional(viewerid, TD_KTP_ValTTL[viewerid], 1);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_ValTTL[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_ValTTL[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_ValTTL[viewerid], 0);

    // Baris 3: Jenis Kelamin
    TD_KTP_LblGender[viewerid] = CreatePlayerTextDraw(viewerid, 372.0, 205.0, "Kelamin");
    PlayerTextDrawFont(viewerid, TD_KTP_LblGender[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_LblGender[viewerid], 0.14, 0.85);
    PlayerTextDrawColor(viewerid, TD_KTP_LblGender[viewerid], 0x143452FF);
    PlayerTextDrawSetProportional(viewerid, TD_KTP_LblGender[viewerid], 1);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_LblGender[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_LblGender[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_LblGender[viewerid], 0);

    format(valBuf, sizeof(valBuf), ": %s (Gol: O)", (gPlayerData[ownerid][p_Gender] == 2) ? "PEREMPUAN" : "LAKI-LAKI");
    TD_KTP_ValGender[viewerid] = CreatePlayerTextDraw(viewerid, 430.0, 205.0, valBuf);
    PlayerTextDrawFont(viewerid, TD_KTP_ValGender[viewerid], 1);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_ValGender[viewerid], 0.14, 0.85);
    PlayerTextDrawColor(viewerid, TD_KTP_ValGender[viewerid], 0x081C2DFF);
    PlayerTextDrawSetProportional(viewerid, TD_KTP_ValGender[viewerid], 1);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_ValGender[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_ValGender[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_ValGender[viewerid], 0);

    // Baris 4: Domisili
    TD_KTP_LblAlamat[viewerid] = CreatePlayerTextDraw(viewerid, 372.0, 219.0, "Alamat");
    PlayerTextDrawFont(viewerid, TD_KTP_LblAlamat[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_LblAlamat[viewerid], 0.14, 0.85);
    PlayerTextDrawColor(viewerid, TD_KTP_LblAlamat[viewerid], 0x143452FF);
    PlayerTextDrawSetProportional(viewerid, TD_KTP_LblAlamat[viewerid], 1);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_LblAlamat[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_LblAlamat[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_LblAlamat[viewerid], 0);

    format(valBuf, sizeof(valBuf), ": Kota %s", gPlayerData[ownerid][p_BirthPlace]);
    TD_KTP_ValAlamat[viewerid] = CreatePlayerTextDraw(viewerid, 430.0, 219.0, valBuf);
    PlayerTextDrawFont(viewerid, TD_KTP_ValNama[viewerid], 1);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_ValAlamat[viewerid], 0.14, 0.85);
    PlayerTextDrawColor(viewerid, TD_KTP_ValAlamat[viewerid], 0x081C2DFF);
    PlayerTextDrawSetProportional(viewerid, TD_KTP_ValAlamat[viewerid], 1);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_ValAlamat[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_ValAlamat[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_ValAlamat[viewerid], 0);

    // Baris 5: Warga
    TD_KTP_LblWarga[viewerid] = CreatePlayerTextDraw(viewerid, 372.0, 233.0, "Warga");
    PlayerTextDrawFont(viewerid, TD_KTP_LblWarga[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_LblWarga[viewerid], 0.14, 0.85);
    PlayerTextDrawColor(viewerid, TD_KTP_LblWarga[viewerid], 0x143452FF);
    PlayerTextDrawSetProportional(viewerid, TD_KTP_LblWarga[viewerid], 1);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_LblWarga[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_LblWarga[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_LblWarga[viewerid], 0);

    TD_KTP_ValWarga[viewerid] = CreatePlayerTextDraw(viewerid, 430.0, 233.0, ": WNI (Santara)");
    PlayerTextDrawFont(viewerid, TD_KTP_ValWarga[viewerid], 1);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_ValWarga[viewerid], 0.14, 0.85);
    PlayerTextDrawColor(viewerid, TD_KTP_ValWarga[viewerid], 0x081C2DFF);
    PlayerTextDrawSetProportional(viewerid, TD_KTP_ValWarga[viewerid], 1);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_ValWarga[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_ValWarga[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_ValWarga[viewerid], 0);

    // Baris 6: Status
    TD_KTP_LblStatus[viewerid] = CreatePlayerTextDraw(viewerid, 372.0, 247.0, "Status");
    PlayerTextDrawFont(viewerid, TD_KTP_LblStatus[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_LblStatus[viewerid], 0.14, 0.85);
    PlayerTextDrawColor(viewerid, TD_KTP_LblStatus[viewerid], 0x143452FF);
    PlayerTextDrawSetProportional(viewerid, TD_KTP_LblStatus[viewerid], 1);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_LblStatus[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_LblStatus[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_LblStatus[viewerid], 0);

    TD_KTP_ValStatus[viewerid] = CreatePlayerTextDraw(viewerid, 430.0, 247.0, ": TERDAFTAR");
    PlayerTextDrawFont(viewerid, TD_KTP_ValStatus[viewerid], 1);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_ValStatus[viewerid], 0.14, 0.85);
    PlayerTextDrawColor(viewerid, TD_KTP_ValStatus[viewerid], 0x081C2DFF);
    PlayerTextDrawSetProportional(viewerid, TD_KTP_ValStatus[viewerid], 1);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_ValStatus[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_ValStatus[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_ValStatus[viewerid], 0);

    // Baris 7: Berlaku
    TD_KTP_LblBerlaku[viewerid] = CreatePlayerTextDraw(viewerid, 372.0, 261.0, "Berlaku");
    PlayerTextDrawFont(viewerid, TD_KTP_LblBerlaku[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_LblBerlaku[viewerid], 0.14, 0.85);
    PlayerTextDrawColor(viewerid, TD_KTP_LblBerlaku[viewerid], 0x143452FF);
    PlayerTextDrawSetProportional(viewerid, TD_KTP_LblBerlaku[viewerid], 1);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_LblBerlaku[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_LblBerlaku[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_LblBerlaku[viewerid], 0);

    TD_KTP_ValBerlaku[viewerid] = CreatePlayerTextDraw(viewerid, 430.0, 261.0, ": SEUMUR HIDUP");
    PlayerTextDrawFont(viewerid, TD_KTP_ValBerlaku[viewerid], 1);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_ValBerlaku[viewerid], 0.14, 0.85);
    PlayerTextDrawColor(viewerid, TD_KTP_ValBerlaku[viewerid], 0x081C2DFF);
    PlayerTextDrawSetProportional(viewerid, TD_KTP_ValBerlaku[viewerid], 1);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_ValBerlaku[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_ValBerlaku[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_ValBerlaku[viewerid], 0);

    //    9. Pas Foto 3D Avatar (Sisi Kanan Kartu: X 554.0 s/d 616.0)   
    TD_KTP_PhotoBorder[viewerid] = CreatePlayerTextDraw(viewerid, 553.0, 175.0, "_");
    PlayerTextDrawUseBox(viewerid, TD_KTP_PhotoBorder[viewerid], 1);
    PlayerTextDrawBoxColor(viewerid, TD_KTP_PhotoBorder[viewerid], 0x143452FF);
    PlayerTextDrawTextSize(viewerid, TD_KTP_PhotoBorder[viewerid], 617.0, 0.0);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_PhotoBorder[viewerid], 0.0, 7.2);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_PhotoBorder[viewerid], 0);

    TD_KTP_PhotoBg[viewerid] = CreatePlayerTextDraw(viewerid, 554.0, 176.0, "_");
    PlayerTextDrawUseBox(viewerid, TD_KTP_PhotoBg[viewerid], 1);
    PlayerTextDrawBoxColor(viewerid, TD_KTP_PhotoBg[viewerid], 0xB32424FF);
    PlayerTextDrawTextSize(viewerid, TD_KTP_PhotoBg[viewerid], 616.0, 0.0);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_PhotoBg[viewerid], 0.0, 7.0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_PhotoBg[viewerid], 0);

    TD_KTP_Photo[viewerid] = CreatePlayerTextDraw(viewerid, 554.0, 176.0, "_");
    PlayerTextDrawFont(viewerid, TD_KTP_Photo[viewerid], TEXT_DRAW_FONT_MODEL_PREVIEW);
    PlayerTextDrawTextSize(viewerid, TD_KTP_Photo[viewerid], 62.0, 63.0);
    PlayerTextDrawSetPreviewModel(viewerid, TD_KTP_Photo[viewerid], gPlayerData[ownerid][p_Skin]);
    PlayerTextDrawSetPreviewRot(viewerid, TD_KTP_Photo[viewerid], -10.0, 0.0, -12.0, 0.85);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_Photo[viewerid], 0);

    //    10. Cap Digital & Tanda Tangan   
    TD_KTP_SignCity[viewerid] = CreatePlayerTextDraw(viewerid, 585.0, 244.0, "KOTA SANTARA");
    PlayerTextDrawFont(viewerid, TD_KTP_SignCity[viewerid], 2);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_SignCity[viewerid], 0.13, 0.75);
    PlayerTextDrawColor(viewerid, TD_KTP_SignCity[viewerid], 0x0E273FFF);
    PlayerTextDrawAlignment(viewerid, TD_KTP_SignCity[viewerid], 2);
    PlayerTextDrawSetProportional(viewerid, TD_KTP_SignCity[viewerid], 1);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_SignCity[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_SignCity[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_SignCity[viewerid], 0);

    TD_KTP_SignDate[viewerid] = CreatePlayerTextDraw(viewerid, 585.0, 253.0, "24-08-2026");
    PlayerTextDrawFont(viewerid, TD_KTP_SignDate[viewerid], 1);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_SignDate[viewerid], 0.12, 0.70);
    PlayerTextDrawColor(viewerid, TD_KTP_SignDate[viewerid], 0x1A3C5EFF);
    PlayerTextDrawAlignment(viewerid, TD_KTP_SignDate[viewerid], 2);
    PlayerTextDrawSetProportional(viewerid, TD_KTP_SignDate[viewerid], 1);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_SignDate[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_SignDate[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_SignDate[viewerid], 0);

    TD_KTP_SignStamp[viewerid] = CreatePlayerTextDraw(viewerid, 585.0, 263.0, "[ TTD DIGITAL ]");
    PlayerTextDrawFont(viewerid, TD_KTP_SignStamp[viewerid], 1);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_SignStamp[viewerid], 0.12, 0.65);
    PlayerTextDrawColor(viewerid, TD_KTP_SignStamp[viewerid], 0x1B6B3EFF);
    PlayerTextDrawAlignment(viewerid, TD_KTP_SignStamp[viewerid], 2);
    PlayerTextDrawSetProportional(viewerid, TD_KTP_SignStamp[viewerid], 1);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_SignStamp[viewerid], 0);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_SignStamp[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_SignStamp[viewerid], 0);

    //    11. Bottom Security Bar   
    TD_KTP_FootLine[viewerid] = CreatePlayerTextDraw(viewerid, 365.0, 324.0, "_");
    PlayerTextDrawUseBox(viewerid, TD_KTP_FootLine[viewerid], 1);
    PlayerTextDrawBoxColor(viewerid, TD_KTP_FootLine[viewerid], 0x143452FF);
    PlayerTextDrawTextSize(viewerid, TD_KTP_FootLine[viewerid], 625.0, 0.0);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_FootLine[viewerid], 0.0, 0.35);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_FootLine[viewerid], 0);

    //    12. Screen Hint di Bawah Kartu (Kanan Layar)   
    TD_KTP_Hint[viewerid] = CreatePlayerTextDraw(viewerid, 495.0, 332.0, "~w~Tekan ~y~ESC ~w~atau klik ~r~[ X ] ~w~untuk menutup");
    PlayerTextDrawFont(viewerid, TD_KTP_Hint[viewerid], 1);
    PlayerTextDrawLetterSize(viewerid, TD_KTP_Hint[viewerid], 0.14, 0.80);
    PlayerTextDrawColor(viewerid, TD_KTP_Hint[viewerid], 0xFFFFFFFF);
    PlayerTextDrawAlignment(viewerid, TD_KTP_Hint[viewerid], 2);
    PlayerTextDrawSetProportional(viewerid, TD_KTP_Hint[viewerid], 1);
    PlayerTextDrawSetOutline(viewerid, TD_KTP_Hint[viewerid], 1);
    PlayerTextDrawSetShadow(viewerid, TD_KTP_Hint[viewerid], 0);
    PlayerTextDrawSetSelectable(viewerid, TD_KTP_Hint[viewerid], 0);

    // Tampilkan semua elemen kartu KTP
    PlayerTextDrawShow(viewerid, TD_KTP_Border[viewerid]);
    PlayerTextDrawShow(viewerid, TD_KTP_CardBg[viewerid]);
    PlayerTextDrawShow(viewerid, TD_KTP_HeaderBar[viewerid]);
    PlayerTextDrawShow(viewerid, TD_KTP_GoldLine[viewerid]);
    PlayerTextDrawShow(viewerid, TD_KTP_Header1[viewerid]);
    PlayerTextDrawShow(viewerid, TD_KTP_Header2[viewerid]);
    PlayerTextDrawShow(viewerid, TD_KTP_Header3[viewerid]);
    PlayerTextDrawShow(viewerid, TD_KTP_Close[viewerid]);
    PlayerTextDrawShow(viewerid, TD_KTP_NIK[viewerid]);

    PlayerTextDrawShow(viewerid, TD_KTP_LblNama[viewerid]);
    PlayerTextDrawShow(viewerid, TD_KTP_ValNama[viewerid]);

    PlayerTextDrawShow(viewerid, TD_KTP_LblTTL[viewerid]);
    PlayerTextDrawShow(viewerid, TD_KTP_ValTTL[viewerid]);

    PlayerTextDrawShow(viewerid, TD_KTP_LblGender[viewerid]);
    PlayerTextDrawShow(viewerid, TD_KTP_ValGender[viewerid]);

    PlayerTextDrawShow(viewerid, TD_KTP_LblAlamat[viewerid]);
    PlayerTextDrawShow(viewerid, TD_KTP_ValAlamat[viewerid]);

    PlayerTextDrawShow(viewerid, TD_KTP_LblWarga[viewerid]);
    PlayerTextDrawShow(viewerid, TD_KTP_ValWarga[viewerid]);

    PlayerTextDrawShow(viewerid, TD_KTP_LblStatus[viewerid]);
    PlayerTextDrawShow(viewerid, TD_KTP_ValStatus[viewerid]);

    PlayerTextDrawShow(viewerid, TD_KTP_LblBerlaku[viewerid]);
    PlayerTextDrawShow(viewerid, TD_KTP_ValBerlaku[viewerid]);

    PlayerTextDrawShow(viewerid, TD_KTP_PhotoBorder[viewerid]);
    PlayerTextDrawShow(viewerid, TD_KTP_PhotoBg[viewerid]);
    PlayerTextDrawShow(viewerid, TD_KTP_Photo[viewerid]);
    PlayerTextDrawShow(viewerid, TD_KTP_SignCity[viewerid]);
    PlayerTextDrawShow(viewerid, TD_KTP_SignDate[viewerid]);
    PlayerTextDrawShow(viewerid, TD_KTP_SignStamp[viewerid]);
    PlayerTextDrawShow(viewerid, TD_KTP_FootLine[viewerid]);
    PlayerTextDrawShow(viewerid, TD_KTP_Hint[viewerid]);

    SelectTextDraw(viewerid, 0xE69958FF);
    PlayerPlaySound(viewerid, 1083, 0.0, 0.0, 0.0);
    return 1;
}

stock HidePlayerKTPCard(playerid) {
    if (!gShowingKTP[playerid]) return;
    gShowingKTP[playerid] = false;
    CancelSelectTextDraw(playerid);
    DestroyPlayerKTPTextDraws(playerid);
    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
}
