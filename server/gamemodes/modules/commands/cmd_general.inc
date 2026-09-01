#if defined _MODULE_CMD_GENERAL_INC
    #endinput
#endif
#define _MODULE_CMD_GENERAL_INC

// ============================================================
//  SantaraBaru Roleplay - General Commands & Utilities
// ============================================================

CMD:help(playerid, params[]) {
    #pragma unused params
    if (!gPlayerData[playerid][p_LoggedIn]) return 1;
    SendClientMessage(playerid, COL_CYAN,  "================== [ PANDUAN PERINTAH ROLEPLAY ] ==================");
    SendClientMessage(playerid, COL_WHITE, "  > {E69958}Tombol Pintas Aksi Utama:");
    SendClientMessage(playerid, COL_WHITE, "     {FFFF00}[ H ]         {A0AEC0}- Interaksi universal (Gedung, Loket KTP, Job, DMV, Kasir, Pom Bensin, dll)");
    SendClientMessage(playerid, COL_WHITE, "     {FFFF00}[ C ] /cursor {A0AEC0}- Masuk ke mode kursor mouse untuk klik tombol HUD / UI");
    SendClientMessage(playerid, COL_WHITE, "  > {E69958}Tutorial Mengisi Bensin di Pom Bensin:");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}1. {FFFFFF}Parkirkan kendaraan dekat dispenser & matikan mesin ({FFFF00}/engine{FFFFFF} atau tombol HUD).");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}2. {FFFFFF}Turun dari mobil, dekati dispenser bensin lalu tekan {FFFF00}[ H ]{FFFFFF} atau {FFFF00}/isibensin{FFFFFF}.");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}3. {FFFFFF}Gunakan tombol {00EEFF}[ + ] / [ - ]{FFFFFF} atau {00EEFF}[ Full ]{FFFFFF} untuk memilih liter, lalu klik {5814EE}[ Isi ]{FFFFFF}.");
    SendClientMessage(playerid, COL_WHITE, "  > {E69958}Komunikasi Suara & Teks RP:");
    SendClientMessage(playerid, COL_WHITE, "     {F1C40F}/s {FFFFFF}[pesan]   {A0AEC0}- Bicara lokal biasa (Radius 20m)");
    SendClientMessage(playerid, COL_WHITE, "     {F1C40F}/sh {FFFFFF}[pesan]  {A0AEC0}- Berteriak kencang (Radius 40m)");
    SendClientMessage(playerid, COL_WHITE, "     {F1C40F}/w {FFFFFF}[pesan]   {A0AEC0}- Berbisik pelan (Radius 5m)");
    SendClientMessage(playerid, COL_WHITE, "     {F1C40F}/b {FFFFFF}[pesan]   {A0AEC0}- Chat OOC lokal (/ooc untuk global)");
    SendClientMessage(playerid, COL_WHITE, "     {C56CF0}/me {FFFFFF}[aksi]   {A0AEC0}- Deskripsi tindakan karakter");
    SendClientMessage(playerid, COL_WHITE, "     {00D2FF}/do {FFFFFF}[kondisi]{A0AEC0}- Deskripsi situasi lingkungan sekitar");
    SendClientMessage(playerid, COL_WHITE, "  > {E69958}Identitas, Dokumen & Tas:");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/dokumen       {A0AEC0}- Buka dompet dokumen (e-KTP, SIM A/B/C) & perlihatkan");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/buatktp       {A0AEC0}- Buat / cetak e-KTP di Loket Balai Kota");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/whoami        {A0AEC0}- Ringkasan biodata karakter & status");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/trunk /bagasi {A0AEC0}- Buka bagasi mobil untuk simpan/ambil barang");
    SendClientMessage(playerid, COL_WHITE, "  > {E69958}Kendaraan & Fasilitas:");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/v             {A0AEC0}- Menu manajemen kendaraan & GPS tracker");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/garasi        {A0AEC0}- Buka Live 3D Garasi Kota (simpan / ambil mobil)");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/asuransi      {A0AEC0}- Klaim kendaraan rusak/hancur di Kantor Asuransi");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/dealer        {A0AEC0}- Buka Showroom Coutt & Schutz");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/seatbelt /sb  {A0AEC0}- Pasang / lepas sabuk pengaman");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/isibensin     {A0AEC0}- Buka menu pengisian bensin di Pom Bensin");
    SendClientMessage(playerid, COL_WHITE, "  > {E69958}Navigasi & Umum:");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/gps           {A0AEC0}- Buka Legenda Peta & Navigasi Rute Fasilitas");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/cp            {A0AEC0}- Matikan tanda waypoint GPS aktif");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/job /jobcenter{A0AEC0}- Buka lowongan kerja di Balai Kota");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/craft         {A0AEC0}- Buka meja perakitan senjata di hideout");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/cursor        {A0AEC0}- Aktifkan kursor mouse untuk klik TextDraw UI");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/q             {A0AEC0}- Keluar dari server");
    SendClientMessage(playerid, COL_CYAN,  "====================================================================");
    return 1;
}

CMD:cursor(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    SelectTextDraw(playerid, 0x00EEFFFF);
    PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
    SendClientMessage(playerid, COL_GREEN, "  [Kursor] Mode kursor mouse aktif. Tekan ESC untuk menutup kursor.");
    return 1;
}

CMD:cp(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    ClearGPSWaypoint(playerid);
    PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
    SendClientMessage(playerid, COL_GREEN, "  [GPS] Tanda penunjuk arah waypoint GPS telah dimatikan.");
    return 1;
}

CMD:getpos(playerid, params[]) {
    if (!CheckSpawned(playerid)) return 1;

    new Float:x, Float:y, Float:z, Float:a;
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, a);
    new intID = GetPlayerInterior(playerid);
    new vwID  = GetPlayerVirtualWorld(playerid);

    new msg[144];
    SendClientMessage(playerid, COL_YELLOW, "================= [ INFORMASI KOORDINAT ] =================");
    format(msg, sizeof(msg), "  {FFFFFF}* Posisi (X, Y, Z)   : {33CCFF}%.4f, %.4f, %.4f", x, y, z);
    SendClientMessage(playerid, COL_WHITE, msg);

    format(msg, sizeof(msg), "  {FFFFFF}* Facing Angle (A)   : {33CCFF}%.4f", a);
    SendClientMessage(playerid, COL_WHITE, msg);

    format(msg, sizeof(msg), "  {FFFFFF}* Interior / VW      : {33CCFF}Interior ID: %d {FFFFFF}| {33CCFF}Virtual World: %d", intID, vwID);
    SendClientMessage(playerid, COL_WHITE, msg);

    format(msg, sizeof(msg), "  {FFFFFF}* Format Siap Copy   : {00FF00}%.4f, %.4f, %.4f, %.4f", x, y, z, a);
    SendClientMessage(playerid, COL_WHITE, msg);

    if (strlen(params) > 0) {
        format(msg, sizeof(msg), "  {FFFFFF}* Keterangan Catatan : {FFFF00}%s", params);
        SendClientMessage(playerid, COL_WHITE, msg);
        printf("[GETPOS] [%s] X: %.4f, Y: %.4f, Z: %.4f, Angle: %.4f | Int: %d, VW: %d (Player: %s)",
            params, x, y, z, a, intID, vwID, gPlayerData[playerid][p_CharName]);
    } else {
        printf("[GETPOS] X: %.4f, Y: %.4f, Z: %.4f, Angle: %.4f | Int: %d, VW: %d (Player: %s)",
            x, y, z, a, intID, vwID, gPlayerData[playerid][p_CharName]);
    }

    // Simpan otomatis ke file scriptfiles/coordinates.txt
    new File:logFile = fopen("coordinates.txt", io_append);
    if (logFile) {
        new logBuffer[256];
        if (strlen(params) > 0) {
            format(logBuffer, sizeof(logBuffer), "[%s] %.4f, %.4f, %.4f, %.4f // Int: %d, VW: %d (Char: %s)\r\n",
                params, x, y, z, a, intID, vwID, gPlayerData[playerid][p_CharName]);
        } else {
            format(logBuffer, sizeof(logBuffer), "%.4f, %.4f, %.4f, %.4f // Int: %d, VW: %d (Char: %s)\r\n",
                x, y, z, a, intID, vwID, gPlayerData[playerid][p_CharName]);
        }
        fwrite(logFile, logBuffer);
        fclose(logFile);
    }

    SendClientMessage(playerid, COL_YELLOW, "==========================================================");
    return 1;
}

CMD:char(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    if (gPlayerData[playerid][p_SelectingSkin]) return 1;

    // Simpan data karakter saat ini
    DoSavePlayer(playerid);
    DestroyVoiceStream(playerid);
    DestroyPlayerSkinTextDraws(playerid);
    HidePlayerMoneyHUD(playerid);

    gPlayerData[playerid][p_Spawned] = false;
    gPlayerData[playerid][p_CharID] = 0;
    gPlayerData[playerid][p_CharName][0] = '\0';
    TogglePlayerSpectating(playerid, true);

    ShowCharacterSelection(playerid);
    return 1;
}

CMD:voice(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    if (!gVoiceEnabled) {
        SendClientMessage(playerid, COL_RED, "  Voice chat tidak aktif di server ini.");
        return 1;
    }
    SendClientMessage(playerid, COL_TEAL, "  [Voice] Voice chat {00CC66}AKTIF{FFFFFF}.");
    SendClientMessage(playerid, COL_WHITE, "  Radius bicara: {00BCD4}20 meter{FFFFFF}.");
    SendClientMessage(playerid, COL_WHITE, "  Pemain Android: gunakan {FFFF00}Alyn SA-MP Mobile{FFFFFF} launcher.");
    return 1;
}

CMD:skin(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    if (gPlayerData[playerid][p_SelectingSkin]) return 1;
    OpenSkinSelection(playerid, false);
    return 1;
}

CMD:whoami(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    new charname[48], msg[144], rup[32], genderStr[16];
    GetCharName(playerid, charname);
    FormatRupiah(gPlayerData[playerid][p_Cash], rup, sizeof(rup));
    format(genderStr, sizeof(genderStr), (gPlayerData[playerid][p_Gender] == 2) ? ("Perempuan") : ("Laki-Laki"));

    SendClientMessage(playerid, COL_WHITE, "  [ {E69958}PROFIL IDENTITAS KARAKTER {FFFFFF}]");
    format(msg, sizeof(msg), "  > {A0AEC0}Nama Karakter  : {FFFFFF}%s {708090}(ID: %d)", charname, playerid);
    SendClientMessage(playerid, COL_WHITE, msg);
    format(msg, sizeof(msg), "  > {A0AEC0}Nama Akun      : {E69958}%s", gPlayerData[playerid][p_Username]);
    SendClientMessage(playerid, COL_WHITE, msg);
    format(msg, sizeof(msg), "  > {A0AEC0}Tempat/Tgl Lahir: {FFFFFF}%s, %s", gPlayerData[playerid][p_BirthPlace], gPlayerData[playerid][p_BirthDate]);
    SendClientMessage(playerid, COL_WHITE, msg);
    format(msg, sizeof(msg), "  > {A0AEC0}Jenis Kelamin  : {FFFFFF}%s", genderStr);
    SendClientMessage(playerid, COL_WHITE, msg);
    format(msg, sizeof(msg), "  > {A0AEC0}Skin Model ID  : {FFFFFF}%d", gPlayerData[playerid][p_Skin]);
    SendClientMessage(playerid, COL_WHITE, msg);
    format(msg, sizeof(msg), "  > {A0AEC0}Tingkat Level  : {F1C40F}%d Score", GetPlayerScore(playerid));
    SendClientMessage(playerid, COL_WHITE, msg);
    format(msg, sizeof(msg), "  > {A0AEC0}Uang Tunai     : {2ECC71}%s", rup);
    SendClientMessage(playerid, COL_WHITE, msg);
    return 1;
}

CMD:job(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;
    if (IsPlayerAtJobCenter(playerid)) {
        ShowJobCenterMenu(playerid);
    } else {
        SendClientMessage(playerid, COL_RED, "  [Job Center] Anda harus berada di loket Job Center (Balai Kota Los Santos)!");
        SendClientMessage(playerid, COL_YELLOW, "  > Gunakan {FFFFFF}/gps{FFFF00} -> Balai Kota & Job Center untuk navigasi.");
    }
    return 1;
}

CMD:jobcenter(playerid, params[]) {
    return cmd_job(playerid, params);
}

CMD:joinjob(playerid, params[]) {
    return cmd_job(playerid, params);
}

CMD:q(playerid, params[]) {
    #pragma unused params
    Kick(playerid);
    return 1;
}

stock DoPlayerRefuel(playerid) {
    return OpenRefuelUI(playerid);
}

CMD:fillfuel(playerid, params[]) {
    #pragma unused params
    DoPlayerRefuel(playerid);
    return 1;
}

CMD:isibensin(playerid, params[]) {
    #pragma unused params
    DoPlayerRefuel(playerid);
    return 1;
}

CMD:seatbelt(playerid, params[]) {
    #pragma unused params
    TogglePlayerVehicleSeatbelt(playerid);
    return 1;
}

CMD:sb(playerid, params[]) {
    return cmd_seatbelt(playerid, params);
}
