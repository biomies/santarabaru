#if defined _MODULE_CHARACTER_INC
    #endinput
#endif
#define _MODULE_CHARACTER_INC

// ============================================================
//  SantaraBaru Roleplay - Multi-Character System & Creation Wizard
// ============================================================

stock StartNewCharacterCreation(playerid) {
    gPlayerData[playerid][p_CharName][0]    = '\0';
    gPlayerData[playerid][p_BirthPlace][0]  = '\0';
    gPlayerData[playerid][p_BirthDate][0]   = '\0';
    gPlayerData[playerid][p_Gender]         = 0;
    gPlayerData[playerid][p_IsNewCharacter] = true;
    OpenCharCreationUI(playerid);
}

stock ShowCharFormDashboard(playerid) {
    if (!gPlayerData[playerid][p_InCharForm]) {
        OpenCharCreationUI(playerid);
    } else {
        UpdateCharCreationUI(playerid);
        SelectTextDraw(playerid, COLOR_CHARFORM_PURPLE);
    }
    return 1;
}

stock ShowCharacterSelection(playerid) {
    new query[256];
    format(query, sizeof(query),
        "SELECT `id`, `char_name`, `skin_id`, `score`, `cash` FROM `characters` WHERE `account_id` = %d AND `is_active` = 1 ORDER BY `id` ASC LIMIT %d",
        gPlayerData[playerid][p_AccountID], MAX_CHARS_PER_ACCOUNT);

    new DBResult:res = DB_ExecuteQuery(gDB, query);
    new count = 0;
    if (res) {
        count = DB_GetRowCount(res);
    }

    gPlayerData[playerid][p_CharListCount] = count;

    if (count == 0) {
        if (res) DB_FreeResultSet(res);
        // Akun belum punya karakter aktif sama sekali -> buat karakter
        StartNewCharacterCreation(playerid);
        return 1;
    }

    new dialogBody[1024], line[128], rup[32];
    format(dialogBody, sizeof(dialogBody), "Nama Karakter\tLevel\tUang Tunai\n");

    for (new i = 0; i < count; i++) {
        new cid = DB_GetFieldIntByName(res, "id");
        new cname[48];
        DB_GetFieldStringByName(res, "char_name", cname, sizeof(cname));
        new cscore = DB_GetFieldIntByName(res, "score");
        new ccash = DB_GetFieldIntByName(res, "cash");

        gPlayerData[playerid][p_CharListIDs][i] = cid;
        format(gCharListNames[playerid][i], 48, "%s", cname);
        FormatRupiah(ccash, rup, sizeof(rup));

        format(line, sizeof(line), "{FFFFFF}%s\t{F1C40F}Level %d\t{2ECC71}Rp %s\n", cname, cscore, rup);
        strcat(dialogBody, line);

        DB_SelectNextRow(res);
    }
    if (res) DB_FreeResultSet(res);

    // Opsi Buat Karakter Baru jika belum penuh
    if (count < MAX_CHARS_PER_ACCOUNT) {
        strcat(dialogBody, "{00D2FF}+ Buat Karakter Baru\t\t\n");
    }

    // Opsi Hapus Karakter di baris list
    strcat(dialogBody, "{FF4040}- Hapus Karakter (Soft Delete)\t\t\n");

    ShowPlayerDialog(playerid, DLG_CHAR_SELECT, DIALOG_STYLE_TABLIST_HEADERS,
        "Pilih Karakter - Santara Roleplay", dialogBody, "Mainkan", "Hapus Karakter");
    return 1;
}

stock ShowCharDeleteList(playerid) {
    if (gPlayerData[playerid][p_CharListCount] == 0) {
        ShowCharacterSelection(playerid);
        return 1;
    }

    new listBody[512];
    for (new i = 0; i < gPlayerData[playerid][p_CharListCount]; i++) {
        new row[128];
        format(row, sizeof(row), "{FF4040}[Hapus] Karakter: {FFFFFF}%s\n", gCharListNames[playerid][i]);
        strcat(listBody, row);
    }

    ShowPlayerDialog(playerid, DLG_CHAR_DELETE_LIST, DIALOG_STYLE_LIST,
        "Pilih Karakter yang Ingin Dihapus (Soft Delete)", listBody, "Pilih Hapus", "Kembali");
    return 1;
}

stock HandleCharacterDialog(playerid, dialogid, response, listitem, const inputtext[]) {
    switch (dialogid) {
        //    Dialog Pemilihan Karakter (Multi-Character List)   
        case DLG_CHAR_SELECT: {
            if (!response) {
                // Klik tombol kanan "Hapus Karakter" -> Buka menu list hapus karakter
                ShowCharDeleteList(playerid);
                return 1;
            }

            if (listitem < gPlayerData[playerid][p_CharListCount]) {
                // Memilih karakter yang ada -> Langsung mainkan!
                new selectedCharID = gPlayerData[playerid][p_CharListIDs][listitem];
                LoadCharacter(playerid, selectedCharID);
            } else if (listitem == gPlayerData[playerid][p_CharListCount] && gPlayerData[playerid][p_CharListCount] < MAX_CHARS_PER_ACCOUNT) {
                // Memilih "+ Buat Karakter Baru"
                StartNewCharacterCreation(playerid);
            } else {
                // Memilih "- Hapus Karakter (Soft Delete)"
                ShowCharDeleteList(playerid);
            }
            return 1;
        }

        //    Dialog Daftar Karakter yang Ingin Dihapus          
        case DLG_CHAR_DELETE_LIST: {
            if (!response) {
                ShowCharacterSelection(playerid);
                return 1;
            }

            if (listitem >= 0 && listitem < gPlayerData[playerid][p_CharListCount]) {
                gPlayerData[playerid][p_TempSelectedCharID] = gPlayerData[playerid][p_CharListIDs][listitem];
                format(gPlayerData[playerid][p_TempSelectedCharName], 48, "%s", gCharListNames[playerid][listitem]);

                new confirmTitle[64], confirmMsg[512];
                format(confirmTitle, sizeof(confirmTitle), "Konfirmasi Hapus Karakter");
                format(confirmMsg, sizeof(confirmMsg),
                    "{FFFFFF}Apakah Anda yakin ingin menghapus karakter {FFFF00}%s{FFFFFF}?\n\n\
                    {AAAAAA}* Status karakter akan dinonaktifkan (is_active = 0).\n\
                    * Karakter ini tidak akan muncul lagi di daftar pemilihan.\n\
                    * Data karakter tetap aman tersimpan di database server.\n\n\
                    {FF4040}Tekan 'Hapus' untuk mengonfirmasi soft delete.",
                    gPlayerData[playerid][p_TempSelectedCharName]);
                ShowPlayerDialog(playerid, DLG_CHAR_CONFIRM_DELETE, DIALOG_STYLE_MSGBOX, confirmTitle, confirmMsg, "Hapus", "Batal");
            } else {
                ShowCharacterSelection(playerid);
            }
            return 1;
        }

        //    Dialog Konfirmasi Hapus Karakter (Soft Delete)      
        case DLG_CHAR_CONFIRM_DELETE: {
            if (!response) {
                // Batal -> kembali ke pemilihan karakter
                ShowCharacterSelection(playerid);
                return 1;
            }

            // Soft Delete: Set is_active = 0
            new query[256];
            format(query, sizeof(query), "UPDATE `characters` SET `is_active` = 0 WHERE `id` = %d AND `account_id` = %d",
                gPlayerData[playerid][p_TempSelectedCharID], gPlayerData[playerid][p_AccountID]);
            DB_FreeResultSet(DB_ExecuteQuery(gDB, query));

            new msg[128];
            format(msg, sizeof(msg), "  [OK] Karakter {FFFF00}%s {00CC66}berhasil dihapus / dinonaktifkan.", gPlayerData[playerid][p_TempSelectedCharName]);
            SendClientMessage(playerid, COL_GREEN, msg);

            // Buka kembali menu karakter yang sudah ter-update
            ShowCharacterSelection(playerid);
            return 1;
        }

        //    Form Dashboard Karakter (1 UI Utama dengan Field Terpisah)   
        case DLG_CHAR_DASHBOARD: {
            if (!response) {
                if (gPlayerData[playerid][p_CharListCount] > 0) {
                    ShowCharacterSelection(playerid);
                } else {
                    Kick(playerid);
                }
                return 1;
            }

            switch (listitem) {
                case 0: {
                    // Field 1: Nama Karakter
                    new info[300];
                    format(info, sizeof(info),
                        "{FFFFFF}Masukkan Nama Karakter Roleplay Anda:\n\n\
                        {AAAAAA}Format: Nama Depan Nama Belakang\n\
                        Contoh: Budi Santoso");
                    ShowPlayerDialog(playerid, DLG_FORM_NAME, DIALOG_STYLE_INPUT, "Field 1: Nama Karakter", info, "Simpan", "Kembali");
                }
                case 1: {
                    // Field 2: Tempat Lahir
                    new info[300];
                    format(info, sizeof(info),
                        "{FFFFFF}Masukkan Tempat / Kota Asal Lahir Karakter:\n\n\
                        {AAAAAA}Contoh: Jakarta, Surabaya, San Fierro, Los Santos");
                    ShowPlayerDialog(playerid, DLG_FORM_BIRTHPLACE, DIALOG_STYLE_INPUT, "Field 2: Tempat Lahir", info, "Simpan", "Kembali");
                }
                case 2: {
                    // Field 3: Tanggal Lahir
                    new info[300];
                    format(info, sizeof(info),
                        "{FFFFFF}Masukkan Tanggal Lahir Karakter:\n\n\
                        {AAAAAA}Format: DD/MM/YYYY (Contoh: 17/08/1998)");
                    ShowPlayerDialog(playerid, DLG_FORM_BIRTHDATE, DIALOG_STYLE_INPUT, "Field 3: Tanggal Lahir", info, "Simpan", "Kembali");
                }
                case 3: {
                    // Field 4: Jenis Kelamin
                    ShowPlayerDialog(playerid, DLG_FORM_GENDER, DIALOG_STYLE_LIST, "Field 4: Jenis Kelamin",
                        "1. Laki-Laki (Pria)\n2. Perempuan (Wanita)", "Pilih", "Kembali");
                }
                case 4: {
                    // Tombol Lanjut ke Pemilihan Spawn
                    if (strlen(gPlayerData[playerid][p_CharName]) == 0) {
                        SendClientMessage(playerid, COL_RED, "  [!] Anda belum mengisi Nama Karakter (Baris 1)!");
                        ShowCharFormDashboard(playerid);
                        return 1;
                    }
                    if (strlen(gPlayerData[playerid][p_BirthPlace]) == 0) {
                        SendClientMessage(playerid, COL_RED, "  [!] Anda belum mengisi Tempat Lahir (Baris 2)!");
                        ShowCharFormDashboard(playerid);
                        return 1;
                    }
                    if (strlen(gPlayerData[playerid][p_BirthDate]) == 0) {
                        SendClientMessage(playerid, COL_RED, "  [!] Anda belum mengisi Tanggal Lahir (Baris 3)!");
                        ShowCharFormDashboard(playerid);
                        return 1;
                    }
                    if (gPlayerData[playerid][p_Gender] == 0) {
                        SendClientMessage(playerid, COL_RED, "  [!] Anda belum memilih Jenis Kelamin (Baris 4)!");
                        ShowCharFormDashboard(playerid);
                        return 1;
                    }

                    // Data sudah lengkap -> Lanjut ke Eagle-Eye Spawn Selector!
                    OpenSpawnSelection(playerid, true);
                }
            }
            return 1;
        }

        //    Input Field 1: Nama Karakter                       
        case DLG_FORM_NAME: {
            if (!response) {
                ShowCharFormDashboard(playerid);
                return 1;
            }
            new text[64];
            format(text, sizeof(text), "%s", inputtext);
            TrimSpaces(text);
            if (strlen(text) < 3 || strlen(text) > 24) {
                SendClientMessage(playerid, COL_RED, "  [!] Nama karakter minimal 3 dan maksimal 24 karakter.");
                ShowCharFormDashboard(playerid);
                return 1;
            }

            // Validasi karakter yang diizinkan (Huruf, spasi, dan underscore)
            new bool:valid = true;
            for (new i = 0; text[i]; i++) {
                if (!((text[i] >= 'a' && text[i] <= 'z') ||
                      (text[i] >= 'A' && text[i] <= 'Z') ||
                      text[i] == ' ' || text[i] == '_')) {
                    valid = false;
                    break;
                }
            }
            if (!valid) {
                SendClientMessage(playerid, COL_RED, "  [!] Nama hanya boleh mengandung huruf, spasi, atau underscore.");
                ShowCharFormDashboard(playerid);
                return 1;
            }

            // Cek apakah nama karakter sudah dipakai oleh akun lain di database
            new checkQuery[256];
            format(checkQuery, sizeof(checkQuery), "SELECT `id` FROM `characters` WHERE `char_name` = '%s' LIMIT 1", text);
            new DBResult:res = DB_ExecuteQuery(gDB, checkQuery);
            if (res && DB_GetRowCount(res) > 0) {
                DB_FreeResultSet(res);
                SendClientMessage(playerid, COL_RED, "  [!] Nama karakter tersebut sudah dipakai! Gunakan nama lain.");
                ShowCharFormDashboard(playerid);
                return 1;
            }
            if (res) DB_FreeResultSet(res);

            format(gPlayerData[playerid][p_CharName], 48, "%s", text);
            ShowCharFormDashboard(playerid);
            return 1;
        }

        //    Input Field 2: Tempat Lahir                        
        case DLG_FORM_BIRTHPLACE: {
            if (!response) {
                ShowCharFormDashboard(playerid);
                return 1;
            }
            new text[64];
            format(text, sizeof(text), "%s", inputtext);
            TrimSpaces(text);
            if (strlen(text) < 2 || strlen(text) > 30) {
                SendClientMessage(playerid, COL_RED, "  [!] Tempat lahir minimal 2 dan maksimal 30 karakter.");
                ShowCharFormDashboard(playerid);
                return 1;
            }

            format(gPlayerData[playerid][p_BirthPlace], 32, "%s", text);
            ShowCharFormDashboard(playerid);
            return 1;
        }

        //    Input Field 3: Tanggal Lahir                       
        case DLG_FORM_BIRTHDATE: {
            if (!response) {
                ShowCharFormDashboard(playerid);
                return 1;
            }
            new text[64];
            format(text, sizeof(text), "%s", inputtext);
            TrimSpaces(text);
            if (strlen(text) < 6 || (strfind(text, "/") == -1 && strfind(text, "-") == -1)) {
                SendClientMessage(playerid, COL_RED, "  [!] Format tanggal lahir salah! Contoh: 17/08/1998 atau 1998-08-17");
                ShowCharFormDashboard(playerid);
                return 1;
            }

            format(gPlayerData[playerid][p_BirthDate], 16, "%s", text);
            ShowCharFormDashboard(playerid);
            return 1;
        }

        //    Input Field 4: Jenis Kelamin                       
        case DLG_FORM_GENDER: {
            if (!response) {
                ShowCharFormDashboard(playerid);
                return 1;
            }
            gPlayerData[playerid][p_Gender] = (listitem == 0) ? 1 : 2;
            ShowCharFormDashboard(playerid);
            return 1;
        }
    }
    return 0;
}
