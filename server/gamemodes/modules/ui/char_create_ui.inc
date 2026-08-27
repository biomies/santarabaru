#if defined _MODULE_CHAR_CREATE_UI_INC
    #endinput
#endif
#define _MODULE_CHAR_CREATE_UI_INC

// ============================================================
//  SantaraBaru Roleplay - Modern Character Creation Form UI
//  Dark Indigo (#1E1E2E) & Electric Purple (#5814EE)
//  Fully Optimized for Android SA-MP Touch & PC Cursor
// ============================================================

#define COLOR_CHARFORM_BG       0x1E1E28F5  // Dark Indigo Background
#define COLOR_CHARFORM_PURPLE   0x5814EEFF  // Electric Purple Accent & Action
#define COLOR_CHARFORM_RED      0xFA1E38FF  // Vibrant Red Cancel Button
#define COLOR_CHARFORM_FIELD    0x2D2B3DF0  // Dark Slate Input Field Box

// TextDraw Handles (Modal Form di Tengah Layar)
new PlayerText:TD_CharForm_Bg[MAX_PLAYERS]          = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_CharForm_TopBar[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_CharForm_Header[MAX_PLAYERS]      = {PlayerText:INVALID_TEXT_DRAW, ...};

new PlayerText:TD_CharForm_LblName[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_CharForm_BtnName[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};

new PlayerText:TD_CharForm_LblPlace[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_CharForm_BtnPlace[MAX_PLAYERS]    = {PlayerText:INVALID_TEXT_DRAW, ...};

new PlayerText:TD_CharForm_LblDate[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_CharForm_BtnDate[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};

new PlayerText:TD_CharForm_LblGender[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_CharForm_BtnGender[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};

new PlayerText:TD_CharForm_BtnNext[MAX_PLAYERS]     = {PlayerText:INVALID_TEXT_DRAW, ...};
new PlayerText:TD_CharForm_BtnCancel[MAX_PLAYERS]   = {PlayerText:INVALID_TEXT_DRAW, ...};

stock DestroyPlayerCharFormTextDraws(playerid) {
    if (TD_CharForm_Bg[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_CharForm_Bg[playerid]);
        TD_CharForm_Bg[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_CharForm_TopBar[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_CharForm_TopBar[playerid]);
        TD_CharForm_TopBar[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_CharForm_Header[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_CharForm_Header[playerid]);
        TD_CharForm_Header[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (TD_CharForm_LblName[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_CharForm_LblName[playerid]);
        TD_CharForm_LblName[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_CharForm_BtnName[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_CharForm_BtnName[playerid]);
        TD_CharForm_BtnName[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (TD_CharForm_LblPlace[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_CharForm_LblPlace[playerid]);
        TD_CharForm_LblPlace[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_CharForm_BtnPlace[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_CharForm_BtnPlace[playerid]);
        TD_CharForm_BtnPlace[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (TD_CharForm_LblDate[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_CharForm_LblDate[playerid]);
        TD_CharForm_LblDate[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_CharForm_BtnDate[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_CharForm_BtnDate[playerid]);
        TD_CharForm_BtnDate[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (TD_CharForm_LblGender[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_CharForm_LblGender[playerid]);
        TD_CharForm_LblGender[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_CharForm_BtnGender[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_CharForm_BtnGender[playerid]);
        TD_CharForm_BtnGender[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    if (TD_CharForm_BtnNext[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_CharForm_BtnNext[playerid]);
        TD_CharForm_BtnNext[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    if (TD_CharForm_BtnCancel[playerid] != PlayerText:INVALID_TEXT_DRAW) {
        PlayerTextDrawDestroy(playerid, TD_CharForm_BtnCancel[playerid]);
        TD_CharForm_BtnCancel[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
}

stock UpdateCharCreationUI(playerid) {
    if (!gPlayerData[playerid][p_InCharForm]) return;

    // 1. Text Button Nama
    new nameBuf[64];
    if (strlen(gPlayerData[playerid][p_CharName]) > 0) {
        format(nameBuf, sizeof(nameBuf), "%s", gPlayerData[playerid][p_CharName]);
    } else {
        format(nameBuf, sizeof(nameBuf), "~w~~h~~h~- Klik untuk mengisi nama -");
    }
    PlayerTextDrawHide(playerid, TD_CharForm_BtnName[playerid]);
    PlayerTextDrawSetString(playerid, TD_CharForm_BtnName[playerid], nameBuf);
    PlayerTextDrawShow(playerid, TD_CharForm_BtnName[playerid]);

    // 2. Text Button Tempat Lahir
    new placeBuf[48];
    if (strlen(gPlayerData[playerid][p_BirthPlace]) > 0) {
        format(placeBuf, sizeof(placeBuf), "%s", gPlayerData[playerid][p_BirthPlace]);
    } else {
        format(placeBuf, sizeof(placeBuf), "~w~~h~~h~- Isi Kota -");
    }
    PlayerTextDrawHide(playerid, TD_CharForm_BtnPlace[playerid]);
    PlayerTextDrawSetString(playerid, TD_CharForm_BtnPlace[playerid], placeBuf);
    PlayerTextDrawShow(playerid, TD_CharForm_BtnPlace[playerid]);

    // 3. Text Button Tanggal Lahir
    new dateBuf[32];
    if (strlen(gPlayerData[playerid][p_BirthDate]) > 0) {
        format(dateBuf, sizeof(dateBuf), "%s", gPlayerData[playerid][p_BirthDate]);
    } else {
        format(dateBuf, sizeof(dateBuf), "~w~~h~~h~- DD/MM/YYYY -");
    }
    PlayerTextDrawHide(playerid, TD_CharForm_BtnDate[playerid]);
    PlayerTextDrawSetString(playerid, TD_CharForm_BtnDate[playerid], dateBuf);
    PlayerTextDrawShow(playerid, TD_CharForm_BtnDate[playerid]);

    // 4. Text Button Jenis Kelamin
    new genderBuf[64];
    if (gPlayerData[playerid][p_Gender] == 1) {
        format(genderBuf, sizeof(genderBuf), "Laki-Laki (Pria)   ~y~v");
    } else if (gPlayerData[playerid][p_Gender] == 2) {
        format(genderBuf, sizeof(genderBuf), "Perempuan (Wanita)   ~y~v");
    } else {
        format(genderBuf, sizeof(genderBuf), "~w~~h~~h~-- Pilih Jenis Kelamin --   v");
    }
    PlayerTextDrawHide(playerid, TD_CharForm_BtnGender[playerid]);
    PlayerTextDrawSetString(playerid, TD_CharForm_BtnGender[playerid], genderBuf);
    PlayerTextDrawShow(playerid, TD_CharForm_BtnGender[playerid]);
}

stock OpenCharCreationUI(playerid) {
    gPlayerData[playerid][p_InCharForm] = true;
    gPlayerData[playerid][p_IsNewCharacter] = true;

    // Format strings berdasarkan data karakter saat ini
    new nameBuf[64], placeBuf[48], dateBuf[32], genderBuf[64];
    if (strlen(gPlayerData[playerid][p_CharName]) > 0) {
        format(nameBuf, sizeof(nameBuf), "%s", gPlayerData[playerid][p_CharName]);
    } else {
        format(nameBuf, sizeof(nameBuf), "~w~~h~~h~- Klik untuk mengisi nama -");
    }

    if (strlen(gPlayerData[playerid][p_BirthPlace]) > 0) {
        format(placeBuf, sizeof(placeBuf), "%s", gPlayerData[playerid][p_BirthPlace]);
    } else {
        format(placeBuf, sizeof(placeBuf), "~w~~h~~h~- Isi Kota -");
    }

    if (strlen(gPlayerData[playerid][p_BirthDate]) > 0) {
        format(dateBuf, sizeof(dateBuf), "%s", gPlayerData[playerid][p_BirthDate]);
    } else {
        format(dateBuf, sizeof(dateBuf), "~w~~h~~h~- DD/MM/YYYY -");
    }

    if (gPlayerData[playerid][p_Gender] == 1) {
        format(genderBuf, sizeof(genderBuf), "Laki-Laki (Pria)   ~y~v");
    } else if (gPlayerData[playerid][p_Gender] == 2) {
        format(genderBuf, sizeof(genderBuf), "Perempuan (Wanita)   ~y~v");
    } else {
        format(genderBuf, sizeof(genderBuf), "~w~~h~~h~-- Pilih Jenis Kelamin --   v");
    }

    // Freeze pemain & sembunyikan HUD uang
    TogglePlayerControllable(playerid, false);
    HidePlayerMoneyHUD(playerid);
    DestroyPlayerCharFormTextDraws(playerid);

    // ─── 1. Background Modal Box (Tengah Layar: X 205.0 .. 435.0, Y 90.0 .. 345.0) ───
    TD_CharForm_Bg[playerid] = CreatePlayerTextDraw(playerid, 205.0, 90.0, "_");
    PlayerTextDrawUseBox(playerid, TD_CharForm_Bg[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_CharForm_Bg[playerid], COLOR_CHARFORM_BG);
    PlayerTextDrawTextSize(playerid, TD_CharForm_Bg[playerid], 435.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_CharForm_Bg[playerid], 0.0, 27.5);
    PlayerTextDrawSetSelectable(playerid, TD_CharForm_Bg[playerid], false);

    // ─── 2. Top Accent Line (Electric Purple) ───
    TD_CharForm_TopBar[playerid] = CreatePlayerTextDraw(playerid, 205.0, 90.0, "_");
    PlayerTextDrawUseBox(playerid, TD_CharForm_TopBar[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_CharForm_TopBar[playerid], COLOR_CHARFORM_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_CharForm_TopBar[playerid], 435.0, 0.0);
    PlayerTextDrawLetterSize(playerid, TD_CharForm_TopBar[playerid], 0.0, 0.50);
    PlayerTextDrawSetSelectable(playerid, TD_CharForm_TopBar[playerid], false);

    // ─── 3. Header Banner Box & Title ───
    TD_CharForm_Header[playerid] = CreatePlayerTextDraw(playerid, 320.0, 104.0, "Buat Karakter");
    PlayerTextDrawAlignment(playerid, TD_CharForm_Header[playerid], 2);
    PlayerTextDrawFont(playerid, TD_CharForm_Header[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_CharForm_Header[playerid], 0.17, 1.05);
    PlayerTextDrawColor(playerid, TD_CharForm_Header[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_CharForm_Header[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_CharForm_Header[playerid], COLOR_CHARFORM_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_CharForm_Header[playerid], 15.0, 206.0);
    PlayerTextDrawSetOutline(playerid, TD_CharForm_Header[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_CharForm_Header[playerid], false);

    // ─── 4. Field Nama : ───
    TD_CharForm_LblName[playerid] = CreatePlayerTextDraw(playerid, 217.0, 130.0, "Nama :");
    PlayerTextDrawFont(playerid, TD_CharForm_LblName[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_CharForm_LblName[playerid], 0.16, 0.85);
    PlayerTextDrawColor(playerid, TD_CharForm_LblName[playerid], 0xFFFFFFFF);
    PlayerTextDrawSetSelectable(playerid, TD_CharForm_LblName[playerid], false);

    TD_CharForm_BtnName[playerid] = CreatePlayerTextDraw(playerid, 320.0, 142.0, nameBuf);
    PlayerTextDrawAlignment(playerid, TD_CharForm_BtnName[playerid], 2);
    PlayerTextDrawFont(playerid, TD_CharForm_BtnName[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_CharForm_BtnName[playerid], 0.16, 0.95);
    PlayerTextDrawColor(playerid, TD_CharForm_BtnName[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_CharForm_BtnName[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_CharForm_BtnName[playerid], COLOR_CHARFORM_FIELD);
    PlayerTextDrawTextSize(playerid, TD_CharForm_BtnName[playerid], 15.0, 206.0);
    PlayerTextDrawSetOutline(playerid, TD_CharForm_BtnName[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_CharForm_BtnName[playerid], true);

    // ─── 5. Field Tempat Lahir : (Kolom Kiri) ───
    TD_CharForm_LblPlace[playerid] = CreatePlayerTextDraw(playerid, 217.0, 168.0, "Tempat Lahir :");
    PlayerTextDrawFont(playerid, TD_CharForm_LblPlace[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_CharForm_LblPlace[playerid], 0.14, 0.80);
    PlayerTextDrawColor(playerid, TD_CharForm_LblPlace[playerid], 0xFFFFFFFF);
    PlayerTextDrawSetSelectable(playerid, TD_CharForm_LblPlace[playerid], false);

    TD_CharForm_BtnPlace[playerid] = CreatePlayerTextDraw(playerid, 265.0, 180.0, placeBuf);
    PlayerTextDrawAlignment(playerid, TD_CharForm_BtnPlace[playerid], 2);
    PlayerTextDrawFont(playerid, TD_CharForm_BtnPlace[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_CharForm_BtnPlace[playerid], 0.14, 0.90);
    PlayerTextDrawColor(playerid, TD_CharForm_BtnPlace[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_CharForm_BtnPlace[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_CharForm_BtnPlace[playerid], COLOR_CHARFORM_FIELD);
    PlayerTextDrawTextSize(playerid, TD_CharForm_BtnPlace[playerid], 15.0, 96.0);
    PlayerTextDrawSetOutline(playerid, TD_CharForm_BtnPlace[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_CharForm_BtnPlace[playerid], true);

    // ─── 6. Field Tanggal Lahir : (Kolom Kanan) ───
    TD_CharForm_LblDate[playerid] = CreatePlayerTextDraw(playerid, 327.0, 168.0, "Tanggal Lahir :");
    PlayerTextDrawFont(playerid, TD_CharForm_LblDate[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_CharForm_LblDate[playerid], 0.14, 0.80);
    PlayerTextDrawColor(playerid, TD_CharForm_LblDate[playerid], 0xFFFFFFFF);
    PlayerTextDrawSetSelectable(playerid, TD_CharForm_LblDate[playerid], false);

    TD_CharForm_BtnDate[playerid] = CreatePlayerTextDraw(playerid, 375.0, 180.0, dateBuf);
    PlayerTextDrawAlignment(playerid, TD_CharForm_BtnDate[playerid], 2);
    PlayerTextDrawFont(playerid, TD_CharForm_BtnDate[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_CharForm_BtnDate[playerid], 0.14, 0.90);
    PlayerTextDrawColor(playerid, TD_CharForm_BtnDate[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_CharForm_BtnDate[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_CharForm_BtnDate[playerid], COLOR_CHARFORM_FIELD);
    PlayerTextDrawTextSize(playerid, TD_CharForm_BtnDate[playerid], 15.0, 96.0);
    PlayerTextDrawSetOutline(playerid, TD_CharForm_BtnDate[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_CharForm_BtnDate[playerid], true);

    // ─── 7. Field Jenis Kelamin : ───
    TD_CharForm_LblGender[playerid] = CreatePlayerTextDraw(playerid, 217.0, 206.0, "Jenis Kelamin :");
    PlayerTextDrawFont(playerid, TD_CharForm_LblGender[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_CharForm_LblGender[playerid], 0.16, 0.85);
    PlayerTextDrawColor(playerid, TD_CharForm_LblGender[playerid], 0xFFFFFFFF);
    PlayerTextDrawSetSelectable(playerid, TD_CharForm_LblGender[playerid], false);

    TD_CharForm_BtnGender[playerid] = CreatePlayerTextDraw(playerid, 320.0, 218.0, genderBuf);
    PlayerTextDrawAlignment(playerid, TD_CharForm_BtnGender[playerid], 2);
    PlayerTextDrawFont(playerid, TD_CharForm_BtnGender[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TD_CharForm_BtnGender[playerid], 0.15, 0.95);
    PlayerTextDrawColor(playerid, TD_CharForm_BtnGender[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_CharForm_BtnGender[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_CharForm_BtnGender[playerid], COLOR_CHARFORM_FIELD);
    PlayerTextDrawTextSize(playerid, TD_CharForm_BtnGender[playerid], 15.0, 206.0);
    PlayerTextDrawSetOutline(playerid, TD_CharForm_BtnGender[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_CharForm_BtnGender[playerid], true);

    // ─── 8. Action Button: Selanjutnya ───
    TD_CharForm_BtnNext[playerid] = CreatePlayerTextDraw(playerid, 320.0, 254.0, "Selanjutnya");
    PlayerTextDrawAlignment(playerid, TD_CharForm_BtnNext[playerid], 2);
    PlayerTextDrawFont(playerid, TD_CharForm_BtnNext[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_CharForm_BtnNext[playerid], 0.17, 1.05);
    PlayerTextDrawColor(playerid, TD_CharForm_BtnNext[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_CharForm_BtnNext[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_CharForm_BtnNext[playerid], COLOR_CHARFORM_PURPLE);
    PlayerTextDrawTextSize(playerid, TD_CharForm_BtnNext[playerid], 15.0, 206.0);
    PlayerTextDrawSetOutline(playerid, TD_CharForm_BtnNext[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_CharForm_BtnNext[playerid], true);

    // ─── 9. Action Button: Batal ───
    TD_CharForm_BtnCancel[playerid] = CreatePlayerTextDraw(playerid, 320.0, 280.0, "Batal");
    PlayerTextDrawAlignment(playerid, TD_CharForm_BtnCancel[playerid], 2);
    PlayerTextDrawFont(playerid, TD_CharForm_BtnCancel[playerid], 2);
    PlayerTextDrawLetterSize(playerid, TD_CharForm_BtnCancel[playerid], 0.17, 1.05);
    PlayerTextDrawColor(playerid, TD_CharForm_BtnCancel[playerid], 0xFFFFFFFF);
    PlayerTextDrawUseBox(playerid, TD_CharForm_BtnCancel[playerid], true);
    PlayerTextDrawBoxColor(playerid, TD_CharForm_BtnCancel[playerid], COLOR_CHARFORM_RED);
    PlayerTextDrawTextSize(playerid, TD_CharForm_BtnCancel[playerid], 15.0, 206.0);
    PlayerTextDrawSetOutline(playerid, TD_CharForm_BtnCancel[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TD_CharForm_BtnCancel[playerid], true);

    // Tampilkan seluruh TextDraw ke layar pemain
    PlayerTextDrawShow(playerid, TD_CharForm_Bg[playerid]);
    PlayerTextDrawShow(playerid, TD_CharForm_TopBar[playerid]);
    PlayerTextDrawShow(playerid, TD_CharForm_Header[playerid]);
    PlayerTextDrawShow(playerid, TD_CharForm_LblName[playerid]);
    PlayerTextDrawShow(playerid, TD_CharForm_BtnName[playerid]);
    PlayerTextDrawShow(playerid, TD_CharForm_LblPlace[playerid]);
    PlayerTextDrawShow(playerid, TD_CharForm_BtnPlace[playerid]);
    PlayerTextDrawShow(playerid, TD_CharForm_LblDate[playerid]);
    PlayerTextDrawShow(playerid, TD_CharForm_BtnDate[playerid]);
    PlayerTextDrawShow(playerid, TD_CharForm_LblGender[playerid]);
    PlayerTextDrawShow(playerid, TD_CharForm_BtnGender[playerid]);
    PlayerTextDrawShow(playerid, TD_CharForm_BtnNext[playerid]);
    PlayerTextDrawShow(playerid, TD_CharForm_BtnCancel[playerid]);

    UpdateCharCreationUI(playerid);
    SelectTextDraw(playerid, COLOR_CHARFORM_PURPLE);
}

stock CloseCharCreationUI(playerid, bool:cancelSelect = true) {
    gPlayerData[playerid][p_InCharForm] = false;
    if (cancelSelect) {
        CancelSelectTextDraw(playerid);
    }
    DestroyPlayerCharFormTextDraws(playerid);
}

stock bool:HandleCharCreationClick(playerid, PlayerText:playertextid) {
    if (!gPlayerData[playerid][p_InCharForm]) return false;

    // 1. Klik Field Nama
    if (playertextid == TD_CharForm_BtnName[playerid]) {
        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
        new info[300];
        format(info, sizeof(info),
            "{FFFFFF}Masukkan Nama Karakter Roleplay Anda:\n\n\
            {AAAAAA}Format: Nama Depan Nama Belakang\n\
            Contoh: Budi Santoso, Alex Mercer");
        ShowPlayerDialog(playerid, DLG_FORM_NAME, DIALOG_STYLE_INPUT, "Field: Nama Karakter", info, "Simpan", "Batal");
        return true;
    }

    // 2. Klik Field Tempat Lahir
    if (playertextid == TD_CharForm_BtnPlace[playerid]) {
        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
        new info[300];
        format(info, sizeof(info),
            "{FFFFFF}Masukkan Tempat / Kota Asal Lahir Karakter:\n\n\
            {AAAAAA}Contoh: Jakarta, Surabaya, San Fierro, Los Santos");
        ShowPlayerDialog(playerid, DLG_FORM_BIRTHPLACE, DIALOG_STYLE_INPUT, "Field: Tempat Lahir", info, "Simpan", "Batal");
        return true;
    }

    // 3. Klik Field Tanggal Lahir
    if (playertextid == TD_CharForm_BtnDate[playerid]) {
        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
        new info[300];
        format(info, sizeof(info),
            "{FFFFFF}Masukkan Tanggal Lahir Karakter:\n\n\
            {AAAAAA}Format: DD/MM/YYYY (Contoh: 17/08/1998)");
        ShowPlayerDialog(playerid, DLG_FORM_BIRTHDATE, DIALOG_STYLE_INPUT, "Field: Tanggal Lahir", info, "Simpan", "Batal");
        return true;
    }

    // 4. Klik Field Jenis Kelamin
    if (playertextid == TD_CharForm_BtnGender[playerid]) {
        PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
        ShowPlayerDialog(playerid, DLG_FORM_GENDER, DIALOG_STYLE_LIST, "Field: Jenis Kelamin",
            "1. Laki-Laki (Pria)\n2. Perempuan (Wanita)", "Pilih", "Batal");
        return true;
    }

    // 5. Tombol Selanjutnya (Ungu)
    if (playertextid == TD_CharForm_BtnNext[playerid]) {
        if (strlen(gPlayerData[playerid][p_CharName]) == 0) {
            PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
            SendClientMessage(playerid, COL_RED, "  [!] Anda belum mengisi Nama Karakter!");
            return true;
        }
        if (strlen(gPlayerData[playerid][p_BirthPlace]) == 0) {
            PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
            SendClientMessage(playerid, COL_RED, "  [!] Anda belum mengisi Tempat Lahir!");
            return true;
        }
        if (strlen(gPlayerData[playerid][p_BirthDate]) == 0) {
            PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
            SendClientMessage(playerid, COL_RED, "  [!] Anda belum mengisi Tanggal Lahir!");
            return true;
        }
        if (gPlayerData[playerid][p_Gender] == 0) {
            PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
            SendClientMessage(playerid, COL_RED, "  [!] Anda belum memilih Jenis Kelamin!");
            return true;
        }

        // Data lengkap -> Lanjut ke Eagle-Eye Spawn Selector!
        PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
        CloseCharCreationUI(playerid, false);
        OpenSpawnSelection(playerid, true);
        return true;
    }

    // 6. Tombol Batal (Merah)
    if (playertextid == TD_CharForm_BtnCancel[playerid]) {
        PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
        CloseCharCreationUI(playerid, true);
        ShowCharacterSelection(playerid);
        return true;
    }

    return false;
}
