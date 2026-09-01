#if defined _MODULE_ACCOUNT_INC
    #endinput
#endif
#define _MODULE_ACCOUNT_INC

// ============================================================
//  SantaraBaru Roleplay - Account Authentication & Security
// ============================================================

stock ShowLoginDialog(playerid, const errMsg[]) {
    new info[400];
    if (strlen(errMsg)) {
        format(info, sizeof(info), "{FF4040}%s\n\n{FFFFFF}Selamat datang kembali, {00EEFF}%s{FFFFFF}!\n\nMasukkan password Anda:", errMsg, gPlayerData[playerid][p_Username]);
    } else {
        format(info, sizeof(info), "Selamat datang kembali, {00EEFF}%s{FFFFFF}!\n\nAkun Anda ditemukan. Masukkan password untuk login:", gPlayerData[playerid][p_Username]);
    }
    ShowPlayerDialog(playerid, DLG_LOGIN, DIALOG_STYLE_PASSWORD, "Login - SantaraBaru Roleplay", info, "Login", "Keluar");
}

stock ShowRegisterDialog(playerid, const errMsg[]) {
    new info[400];
    if (strlen(errMsg)) {
        format(info, sizeof(info), "{FF4040}%s\n\n{FFFFFF}Akun {00EEFF}%s{FFFFFF} belum terdaftar.\nBuat password baru (minimal 6 karakter):", errMsg, gPlayerData[playerid][p_Username]);
    } else {
        format(info, sizeof(info), "Selamat datang di {FFFF00}SantaraBaru Roleplay{FFFFFF}!\n\nAkun {00EEFF}%s{FFFFFF} belum terdaftar.\nBuat password baru untuk bergabung (minimal 6 karakter):", gPlayerData[playerid][p_Username]);
    }
    ShowPlayerDialog(playerid, DLG_REGISTER, DIALOG_STYLE_PASSWORD, "Daftar - SantaraBaru Roleplay", info, "Daftar", "Keluar");
}

stock HandleAccountDialog(playerid, dialogid, response, listitem, const inputtext[]) {
    #pragma unused listitem
    switch (dialogid) {
        //    Dialog Login                                       
        case DLG_LOGIN: {
            if (!response) { Kick(playerid); return 1; }
            if (!strlen(inputtext)) {
                ShowLoginDialog(playerid, "Password tidak boleh kosong!");
                return 1;
            }

            new hash[65];
            SHA256_PassHash(inputtext, PASSWORD_SALT, hash, sizeof(hash));

            new query[256];
            format(query, sizeof(query),
                "SELECT `id`, `admin_level` FROM `accounts` WHERE `username`='%s' AND `password`='%s' LIMIT 1",
                gPlayerData[playerid][p_Username], hash);

            new DBResult:res = DB_ExecuteQuery(gDB, query);
            if (DB_GetRowCount(res) == 0) {
                DB_FreeResultSet(res);
                gPlayerData[playerid][p_LoginTries]++;
                if (gPlayerData[playerid][p_LoginTries] >= MAX_LOGIN_TRIES) {
                    SendClientMessage(playerid, COL_RED,
                        "  Terlalu banyak percobaan login yang gagal. Anda di-kick.");
                    SetTimerEx("KickPlayer", 1500, false, "i", playerid);
                    return 1;
                }
                new err[80];
                format(err, sizeof(err), "Password salah! ({FF4040}%d/%d{FFFFFF} percobaan)",
                    gPlayerData[playerid][p_LoginTries], MAX_LOGIN_TRIES);
                ShowLoginDialog(playerid, err);
                return 1;
            }
            gPlayerData[playerid][p_AdminLevel] = DB_GetFieldIntByName(res, "admin_level");
            DB_FreeResultSet(res);

            gPlayerData[playerid][p_LoggedIn] = true;
            format(query, sizeof(query), "UPDATE `accounts` SET `last_login`=CURRENT_TIMESTAMP WHERE `id`=%d", gPlayerData[playerid][p_AccountID]);
            DB_FreeResultSet(DB_ExecuteQuery(gDB, query));

            SendClientMessage(playerid, COL_GREEN, "  Login berhasil! Membuka daftar karakter...");
            if (gPlayerData[playerid][p_AdminLevel] >= 2) {
                SendClientMessage(playerid, COL_CYAN, "  [Staff] Selamat datang, {E69958}Owner / SuperAdmin{00EEFF}! Ketik {FFFF00}/ahelp{00EEFF} untuk perintah.");
            } else if (gPlayerData[playerid][p_AdminLevel] == 1) {
                SendClientMessage(playerid, COL_CYAN, "  [Staff] Selamat datang, {2ECC71}Administrator Server{00EEFF}! Ketik {FFFF00}/ahelp{00EEFF} untuk perintah.");
            }
            ShowCharacterSelection(playerid);
            return 1;
        }

        //    Dialog Register                                    
        case DLG_REGISTER: {
            if (!response) { Kick(playerid); return 1; }
            if (strlen(inputtext) < 6) {
                ShowRegisterDialog(playerid, "Password minimal 6 karakter!");
                return 1;
            }
            if (strlen(inputtext) > 32) {
                ShowRegisterDialog(playerid, "Password maksimal 32 karakter!");
                return 1;
            }

            new hash[65];
            SHA256_PassHash(inputtext, PASSWORD_SALT, hash, sizeof(hash));

            new query[512];
            format(query, sizeof(query),
                "INSERT INTO `accounts` (`username`, `password`) VALUES ('%s', '%s')",
                gPlayerData[playerid][p_Username], hash);

            DB_FreeResultSet(DB_ExecuteQuery(gDB, query));

            format(query, sizeof(query),
                "SELECT `id` FROM `accounts` WHERE `username`='%s' LIMIT 1",
                gPlayerData[playerid][p_Username]);

            new DBResult:res = DB_ExecuteQuery(gDB, query);
            if (res && DB_GetRowCount(res) > 0) {
                gPlayerData[playerid][p_AccountID] = DB_GetFieldIntByName(res, "id");
                DB_FreeResultSet(res);
            }

            gPlayerData[playerid][p_Registered] = true;
            gPlayerData[playerid][p_LoggedIn]   = true;

            SendClientMessage(playerid, COL_GREEN,
                "  Pendaftaran akun berhasil! Silakan buat karakter pertama Anda.");
            StartNewCharacterCreation(playerid);
            return 1;
        }
    }
    return 0;
}
