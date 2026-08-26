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
    SendClientMessage(playerid, COL_WHITE, "  [ {E69958}PANDUAN PERINTAH ROLEPLAY {FFFFFF}]");
    SendClientMessage(playerid, COL_WHITE, "  > {E69958}Komunikasi Suara & Teks RP:");
    SendClientMessage(playerid, COL_WHITE, "     {F1C40F}/s {FFFFFF}[pesan]   {A0AEC0}- Bicara lokal biasa (Radius 20m)");
    SendClientMessage(playerid, COL_WHITE, "     {F1C40F}/sh {FFFFFF}[pesan]  {A0AEC0}- Berteriak kencang (Radius 40m)");
    SendClientMessage(playerid, COL_WHITE, "     {F1C40F}/w {FFFFFF}[pesan]   {A0AEC0}- Berbisik pelan (Radius 5m)");
    SendClientMessage(playerid, COL_WHITE, "     {F1C40F}/ooc {FFFFFF}[pesan] {A0AEC0}- Chat Out-of-Character global");
    SendClientMessage(playerid, COL_WHITE, "  > {E69958}Aksi & Situasi Roleplay:");
    SendClientMessage(playerid, COL_WHITE, "     {C56CF0}/me {FFFFFF}[aksi]   {A0AEC0}- Deskripsi tindakan karakter");
    SendClientMessage(playerid, COL_WHITE, "     {00D2FF}/do {FFFFFF}[kondisi]{A0AEC0}- Deskripsi situasi sekitar");
    SendClientMessage(playerid, COL_WHITE, "  > {E69958}Kependudukan & Identitas:");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/ktp           {A0AEC0}- Buka KTP sendiri / buat di Balai Kota");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/ktp {FFFFFF}[id]      {A0AEC0}- Perlihatkan KTP ke pemain terdekat");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/whoami        {A0AEC0}- Ringkasan identitas & status karakter");
    SendClientMessage(playerid, COL_WHITE, "  > {E69958}Kendaraan & Garasi Kota:");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/v             {A0AEC0}- Menu manajemen kendaraan & GPS tracker");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/garasi        {A0AEC0}- Buka Live 3D Garasi Kota (simpan / ambil mobil)");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/asuransi      {A0AEC0}- Klaim kendaraan hancur di Kantor Asuransi");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/dealer        {A0AEC0}- Buka Coutt & Schutz Auto Showroom");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/engine        {A0AEC0}- Nyalakan / matikan mesin kendaraan");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/lock          {A0AEC0}- Kunci / buka pintu kendaraan");
    SendClientMessage(playerid, COL_WHITE, "  > {E69958}Karakter & Gedung:");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}[ F / ENTER ]  {A0AEC0}- Masuk / keluar gedung & interaksi loket");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/char          {A0AEC0}- Pilih / ganti karakter aktif");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/skin          {A0AEC0}- Buka Live 3D ganti pakaian");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/gps           {A0AEC0}- Buka Legenda Peta & Navigasi Rute Fasilitas");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/cp            {A0AEC0}- Matikan tanda checkpoint GPS aktif");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/getpos        {A0AEC0}- Ambil data koordinat posisi");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/voice         {A0AEC0}- Cek status Voice Chat 3D");
    SendClientMessage(playerid, COL_WHITE, "     {2ECC71}/q             {A0AEC0}- Keluar dari server");
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

CMD:q(playerid, params[]) {
    #pragma unused params
    Kick(playerid);
    return 1;
}
