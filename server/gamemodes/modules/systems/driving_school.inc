#if defined _MODULE_DRIVING_SCHOOL_INC
    #endinput
#endif
#define _MODULE_DRIVING_SCHOOL_INC

// ============================================================
//  SantaraBaru Roleplay - Satpas DMV & Practical Driving Test
//  Official Driving School San Fierro (Garcia / Doherty)
// ============================================================

enum E_DMV_ROUTE {
    Float:dmv_X,
    Float:dmv_Y,
    Float:dmv_Z,
    dmv_Instruction[128]
};

// 11 Race Checkpoint Rute Ujian Praktik Mengemudi Keliling San Fierro
new const gDMVRoute[][E_DMV_ROUTE] = {
    {-2153.0012,  -66.8554, 34.8989, "Mulai ujian mengemudi. Melaju lurus di jalan Garcia dan patuhi rambu lalu lintas."},
    {-2418.3259,  -56.4013, 34.8989, "Melewati persimpangan Garcia. Tetap di jalur kanan dan perhatikan kendaraan lain."},
    {-2413.7006,  259.2149, 34.7427, "Memasuki wilayah Queens. Jaga kecepatan dan kendalikan laju kendaraan."},
    {-2324.7561,  439.4621, 34.2702, "Melewati area pemukiman Queens. Waspada pejalan kaki dan bersiap belok."},
    {-2381.4731,  550.4691, 24.8843, "Menuju kawasan Balai Kota San Fierro. Pertahankan posisi kemudi."},
    {-2020.6586,  560.6036, 34.7426, "Memasuki jalan utama Downtown. Perhatikan lampu lalu lintas dan persimpangan."},
    {-2016.2816,  110.6112, 27.2929, "Melewati jalan turunan Cranberry Station. Kurangi kecepatan secara halus."},
    {-2163.7229,   93.0082, 34.8989, "Menuju kembali ke arah Garcia. Bersiap mengambil jalur kiri."},
    {-2151.3303,  -73.8353, 34.8990, "Mendekati area Satpas DMV Driving School. Nyalakan lampu sein."},
    {-2047.9995,  -86.1869, 34.8911, "Masuk ke area parkir Satpas DMV. Perlambat laju kendaraan."},
    {-2089.0615,  -84.4886, 34.8911, "Garis Finish! Hentikan kendaraan dengan rapi di slot parkir."}
};
#define DMV_ROUTE_COUNT (sizeof(gDMVRoute))

stock InitDrivingSchool() {
    // Marker Loket Pendaftaran Satpas DMV di Doherty / Garcia SF
    CreatePickup(1239, 1, DMV_DESK_X, DMV_DESK_Y, DMV_DESK_Z, 0);
    Create3DTextLabel(
        "{00EEFF}[ SATPAS DMV - SEKOLAH MENGEMUDI ]\n{FFFFFF}Tekan {FFFF00}[ H ]{FFFFFF} atau ketik {FFFF00}/buatsim{FFFFFF}\n{AAAAAA}Pendaftaran & Ujian Praktik SIM (A, B, C)",
        0xFFFFFFFF,
        DMV_DESK_X, DMV_DESK_Y, DMV_DESK_Z + 0.5,
        15.0, 0, false
    );
}

stock ShowDMVDialog(playerid) {
    if (!CheckSpawned(playerid)) return 0;

    new statusA[48], statusB[48], statusC[48];

    // Cek Status SIM A
    if (gPlayerData[playerid][p_HasSIM_A]) {
        if (Inventory_HasItem(playerid, ITEM_SIM_A)) {
            format(statusA, sizeof(statusA), "{00FF00}Aktif (Fisik Ada)");
        } else {
            format(statusA, sizeof(statusA), "{F1C40F}Cetak Ulang (Rp 10.000)");
        }
    } else {
        format(statusA, sizeof(statusA), "{FFFFFF}Rp 50.000 (Ujian Praktik)");
    }

    // Cek Status SIM B
    if (gPlayerData[playerid][p_HasSIM_B]) {
        if (Inventory_HasItem(playerid, ITEM_SIM_B)) {
            format(statusB, sizeof(statusB), "{00FF00}Aktif (Fisik Ada)");
        } else {
            format(statusB, sizeof(statusB), "{F1C40F}Cetak Ulang (Rp 10.000)");
        }
    } else {
        format(statusB, sizeof(statusB), "{FFFFFF}Rp 100.000 (Ujian Praktik)");
    }

    // Cek Status SIM C
    if (gPlayerData[playerid][p_HasSIM_C]) {
        if (Inventory_HasItem(playerid, ITEM_SIM_C)) {
            format(statusC, sizeof(statusC), "{00FF00}Aktif (Fisik Ada)");
        } else {
            format(statusC, sizeof(statusC), "{F1C40F}Cetak Ulang (Rp 10.000)");
        }
    } else {
        format(statusC, sizeof(statusC), "{FFFFFF}Rp 25.000 (Ujian Praktik)");
    }

    new dialogStr[600];
    format(dialogStr, sizeof(dialogStr),
        "Golongan SIM\tKlasifikasi Kendaraan\tBiaya / Status\n" \
        "{33CCFF}SIM A\t{FFFFFF}Mobil Pribadi & Angkutan\t%s\n" \
        "{33CCFF}SIM B\t{FFFFFF}Truk & Kendaraan Berat\t%s\n" \
        "{33CCFF}SIM C\t{FFFFFF}Sepeda Motor (Roda 2)\t%s",
        statusA, statusB, statusC);

    ShowPlayerDialog(playerid, DLG_DMV_MAIN, DIALOG_STYLE_TABLIST_HEADERS,
        "{5814EE}Satpas DMV - Pendaftaran & Cetak SIM", dialogStr, "Pilih", "Tutup");
    return 1;
}

stock StartDrivingTest(playerid, type) {
    new fee = 0, modelid = 426, simTypeName[16];
    switch (type) {
        case 0: { // SIM A (Mobil Pribadi - Premier)
            fee = 50000;
            modelid = 426;
            format(simTypeName, sizeof(simTypeName), "SIM A (Mobil)");
        }
        case 1: { // SIM B (Truk - Yankee)
            fee = 100000;
            modelid = 456;
            format(simTypeName, sizeof(simTypeName), "SIM B (Truk)");
        }
        case 2: { // SIM C (Motor - Wayfarer)
            fee = 25000;
            modelid = 586;
            format(simTypeName, sizeof(simTypeName), "SIM C (Motor)");
        }
    }

    // Cek uang pendaftaran
    if (gPlayerData[playerid][p_Cash] < fee) {
        new feeFmt[32], cashFmt[32], errMsg[144];
        FormatRupiah(fee, feeFmt, sizeof(feeFmt));
        FormatRupiah(gPlayerData[playerid][p_Cash], cashFmt, sizeof(cashFmt));
        format(errMsg, sizeof(errMsg), "  [DMV] Uang tunai Anda tidak mencukupi! Biaya ujian: {FF3333}%s{FFFFFF} (Uang Anda: {2ECC71}%s{FFFFFF}).", feeFmt, cashFmt);
        SendClientMessage(playerid, COL_RED, errMsg);
        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        return 0;
    }

    // Potong uang pendaftaran
    gPlayerData[playerid][p_Cash] -= fee;
    new qCash[128];
    format(qCash, sizeof(qCash), "UPDATE `characters` SET `cash`=%d WHERE `id`=%d", gPlayerData[playerid][p_Cash], gPlayerData[playerid][p_CharID]);
    DB_FreeResultSet(DB_ExecuteQuery(gDB, qCash));
    UpdatePlayerMoneyHUD(playerid);

    // Hapus kendaraan ujian lama jika ada
    if (gPlayerData[playerid][p_DrivingTestVehID] != INVALID_VEHICLE_ID) {
        DestroyVehicle(gPlayerData[playerid][p_DrivingTestVehID]);
        gPlayerData[playerid][p_DrivingTestVehID] = INVALID_VEHICLE_ID;
    }

    // Spawn Mobil Ujian di Area Parkir Satpas DMV
    new vehid = CreateVehicle(modelid, DMV_SPAWN_X, DMV_SPAWN_Y, DMV_SPAWN_Z, DMV_SPAWN_A, 1, 1, -1);
    gPlayerData[playerid][p_DrivingTestVehID] = vehid;
    gPlayerData[playerid][p_InDrivingTest]    = true;
    gPlayerData[playerid][p_DrivingTestStep]  = 0;
    gPlayerData[playerid][p_DrivingTestErrors]= 0;
    gPlayerData[playerid][p_DrivingTestType]  = type;
    gPlayerData[playerid][p_DrivingVehLastHealth] = 1000.0;

    // Masukkan pemain ke kursi driver
    PutPlayerInVehicle(playerid, vehid, 0);

    // Nyalakan mesin kendaraan otomatis
    new engine, lights, alarm, doors, bonnet, boot, objective;
    GetVehicleParamsEx(vehid, engine, lights, alarm, doors, bonnet, boot, objective);
    SetVehicleParamsEx(vehid, 1, 1, alarm, doors, bonnet, boot, objective);

    // Pasang Race Checkpoint pertama
    SetPlayerRaceCheckpoint(playerid, 0,
        gDMVRoute[0][dmv_X], gDMVRoute[0][dmv_Y], gDMVRoute[0][dmv_Z],
        gDMVRoute[1][dmv_X], gDMVRoute[1][dmv_Y], gDMVRoute[1][dmv_Z],
        5.0
    );

    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
    GameTextForPlayer(playerid, "~w~Ujian Praktik ~g~DIMULAI!", 4000, 3);

    SendClientMessage(playerid, COL_GREEN,  "================== [ UJIAN PRAKTIK SATPAS DMV ] ==================");
    SendClientMessage(playerid, COL_WHITE,  "  * Anda telah memulai sesi ujian mengemudi resmi keliling San Fierro.");
    SendClientMessage(playerid, COL_YELLOW, "  * Ikuti tanda [ RACE CHECKPOINT ] bertanda panah merah di jalan.");
    SendClientMessage(playerid, COL_CYAN,   "  * Peringatan: Jangan menabrak keras (Maksimal 3x pelanggaran) dan jangan keluar dari mobil.");
    SendClientMessage(playerid, COL_GREEN,  "==================================================================");

    new msg[144];
    format(msg, sizeof(msg), "  [Instruktur] %s", gDMVRoute[0][dmv_Instruction]);
    SendClientMessage(playerid, COL_WHITE, msg);
    return 1;
}

stock CancelDrivingTest(playerid, const reason[]) {
    if (!gPlayerData[playerid][p_InDrivingTest]) return;

    DisablePlayerRaceCheckpoint(playerid);

    if (gPlayerData[playerid][p_DrivingTestVehID] != INVALID_VEHICLE_ID) {
        DestroyVehicle(gPlayerData[playerid][p_DrivingTestVehID]);
        gPlayerData[playerid][p_DrivingTestVehID] = INVALID_VEHICLE_ID;
    }

    gPlayerData[playerid][p_InDrivingTest]   = false;
    gPlayerData[playerid][p_DrivingTestStep] = 0;
    gPlayerData[playerid][p_DrivingTestErrors] = 0;

    SetPlayerPos(playerid, DMV_DESK_X, DMV_DESK_Y, DMV_DESK_Z);
    SetPlayerFacingAngle(playerid, DMV_DESK_A);
    SetCameraBehindPlayer(playerid);

    new errMsg[144];
    format(errMsg, sizeof(errMsg), "  [DMV] Ujian mengemudi GAGAL! Alasan: {FF3333}%s{FFFFFF}.", reason);
    SendClientMessage(playerid, COL_RED, errMsg);
    PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
    GameTextForPlayer(playerid, "~r~UJIAN GAGAL", 4000, 3);
}

stock CompleteDrivingTest(playerid) {
    if (!gPlayerData[playerid][p_InDrivingTest]) return;

    new type = gPlayerData[playerid][p_DrivingTestType];
    new const simCode[3][] = {"sim_a", "sim_b", "sim_c"};
    new const simName[3][] = {"SIM A (Mobil Pribadi)", "SIM B (Truk & Kendaraan Berat)", "SIM C (Sepeda Motor)"};

    new itemToGive = ITEM_SIM_A;
    switch (type) {
        case 0: { gPlayerData[playerid][p_HasSIM_A] = true; itemToGive = ITEM_SIM_A; }
        case 1: { gPlayerData[playerid][p_HasSIM_B] = true; itemToGive = ITEM_SIM_B; }
        case 2: { gPlayerData[playerid][p_HasSIM_C] = true; itemToGive = ITEM_SIM_C; }
    }

    // Update Lisensi Permanen di Database
    new query[256];
    format(query, sizeof(query), "UPDATE `characters` SET `%s` = 1 WHERE `id` = %d", simCode[type], gPlayerData[playerid][p_CharID]);
    DB_FreeResultSet(DB_ExecuteQuery(gDB, query));

    // Berikan fisik kartu SIM ke inventory jika belum ada
    if (!Inventory_HasItem(playerid, itemToGive)) {
        Inventory_AddItem(playerid, itemToGive, 1);
    }

    // Bersihkan sesi ujian
    DisablePlayerRaceCheckpoint(playerid);
    if (gPlayerData[playerid][p_DrivingTestVehID] != INVALID_VEHICLE_ID) {
        DestroyVehicle(gPlayerData[playerid][p_DrivingTestVehID]);
        gPlayerData[playerid][p_DrivingTestVehID] = INVALID_VEHICLE_ID;
    }
    gPlayerData[playerid][p_InDrivingTest]   = false;
    gPlayerData[playerid][p_DrivingTestStep] = 0;
    gPlayerData[playerid][p_DrivingTestErrors] = 0;

    SetPlayerPos(playerid, DMV_DESK_X, DMV_DESK_Y, DMV_DESK_Z);
    SetPlayerFacingAngle(playerid, DMV_DESK_A);
    SetCameraBehindPlayer(playerid);

    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
    GameTextForPlayer(playerid, "~g~SELAMAT! ANDA LULUS UJIAN SIM", 5000, 3);

    SendClientMessage(playerid, COL_GREEN,  "================== [ KELULUSAN UJIAN SATPAS DMV ] ==================");
    SendClientMessage(playerid, COL_WHITE,  "  * Selamat! Anda dinyatakan LULUS ujian praktik mengemudi resmi.");
    new notif[144];
    format(notif, sizeof(notif), "  * Lisensi resmi {00EEFF}%s{FFFFFF} telah diterbitkan dan aktif di database kepolisian.", simName[type]);
    SendClientMessage(playerid, COL_GREEN, notif);
    SendClientMessage(playerid, COL_CYAN,   "  * Fisik {00EEFF}Kartu SIM{FFFFFF} telah dimasukkan ke dalam tas inventory Anda (/inv).");
    SendClientMessage(playerid, COL_YELLOW, "  * Gunakan perintah {FFFFFF}/sim{FFFF00} kapan saja untuk membuka panel lisensi mengemudi Anda.");
    SendClientMessage(playerid, COL_GREEN,  "===================================================================");

    new charname[48], rpMsg[160];
    GetCharName(playerid, charname);
    format(rpMsg, sizeof(rpMsg), "%s menerima kartu Surat Izin Mengemudi resmi (%s) dari instruktur penguji Satpas DMV.", charname, simName[type]);
    DoProximityRaw(playerid, rpMsg, DIST_RP, COL_PURPLE);
}

stock HandleDrivingTestRaceCheckpoint(playerid) {
    if (!gPlayerData[playerid][p_InDrivingTest]) return 0;

    new curStep = gPlayerData[playerid][p_DrivingTestStep];
    curStep++;
    gPlayerData[playerid][p_DrivingTestStep] = curStep;

    // Jika telah sampai di Checkpoint terakhir (Finish Line)
    if (curStep >= DMV_ROUTE_COUNT - 1) {
        CompleteDrivingTest(playerid);
        return 1;
    }

    // Jika Checkpoint berikutnya adalah Finish Line (Tipe 1 = Finish Flag)
    if (curStep == DMV_ROUTE_COUNT - 2) {
        SetPlayerRaceCheckpoint(playerid, 1,
            gDMVRoute[curStep][dmv_X], gDMVRoute[curStep][dmv_Y], gDMVRoute[curStep][dmv_Z],
            0.0, 0.0, 0.0,
            5.0
        );
    } else {
        SetPlayerRaceCheckpoint(playerid, 0,
            gDMVRoute[curStep][dmv_X], gDMVRoute[curStep][dmv_Y], gDMVRoute[curStep][dmv_Z],
            gDMVRoute[curStep + 1][dmv_X], gDMVRoute[curStep + 1][dmv_Y], gDMVRoute[curStep + 1][dmv_Z],
            5.0
        );
    }

    PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);

    new msg[160];
    format(msg, sizeof(msg), "  [Instruktur] %s {A0AEC0}(Rute %d/%d)", gDMVRoute[curStep][dmv_Instruction], curStep + 1, DMV_ROUTE_COUNT);
    SendClientMessage(playerid, COL_WHITE, msg);
    return 1;
}

stock HandleDrivingSchoolDialog(playerid, dialogid, response, listitem) {
    if (dialogid == DLG_DMV_MAIN) {
        if (!response) return 1;

        switch (listitem) {
            case 0: { // SIM A
                if (gPlayerData[playerid][p_HasSIM_A]) {
                    // Cetak Ulang jika belum ada di tas
                    if (!Inventory_HasItem(playerid, ITEM_SIM_A)) {
                        if (gPlayerData[playerid][p_Cash] < 10000) {
                            SendClientMessage(playerid, COL_RED, "  [DMV] Uang Anda tidak cukup untuk biaya cetak ulang kartu SIM A (Rp 10.000)!");
                            return 1;
                        }
                        gPlayerData[playerid][p_Cash] -= 10000;
                        new qCash[128];
                        format(qCash, sizeof(qCash), "UPDATE `characters` SET `cash`=%d WHERE `id`=%d", gPlayerData[playerid][p_Cash], gPlayerData[playerid][p_CharID]);
                        DB_FreeResultSet(DB_ExecuteQuery(gDB, qCash));
                        UpdatePlayerMoneyHUD(playerid);

                        Inventory_AddItem(playerid, ITEM_SIM_A, 1);
                        PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
                        SendClientMessage(playerid, COL_GREEN, "  [DMV] Berhasil mencetak ulang fisik Kartu SIM A Anda seharga {2ECC71}Rp 10.000{FFFFFF}.");
                        return 1;
                    } else {
                        SendClientMessage(playerid, COL_GREEN, "  [DMV] Anda sudah memiliki SIM A aktif dan membawa fisik kartunya di tas (/inv).");
                        return 1;
                    }
                } else {
                    StartDrivingTest(playerid, 0);
                    return 1;
                }
            }
            case 1: { // SIM B
                if (gPlayerData[playerid][p_HasSIM_B]) {
                    if (!Inventory_HasItem(playerid, ITEM_SIM_B)) {
                        if (gPlayerData[playerid][p_Cash] < 10000) {
                            SendClientMessage(playerid, COL_RED, "  [DMV] Uang Anda tidak cukup untuk biaya cetak ulang kartu SIM B (Rp 10.000)!");
                            return 1;
                        }
                        gPlayerData[playerid][p_Cash] -= 10000;
                        new qCash[128];
                        format(qCash, sizeof(qCash), "UPDATE `characters` SET `cash`=%d WHERE `id`=%d", gPlayerData[playerid][p_Cash], gPlayerData[playerid][p_CharID]);
                        DB_FreeResultSet(DB_ExecuteQuery(gDB, qCash));
                        UpdatePlayerMoneyHUD(playerid);

                        Inventory_AddItem(playerid, ITEM_SIM_B, 1);
                        PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
                        SendClientMessage(playerid, COL_GREEN, "  [DMV] Berhasil mencetak ulang fisik Kartu SIM B Anda seharga {2ECC71}Rp 10.000{FFFFFF}.");
                        return 1;
                    } else {
                        SendClientMessage(playerid, COL_GREEN, "  [DMV] Anda sudah memiliki SIM B aktif dan membawa fisik kartunya di tas (/inv).");
                        return 1;
                    }
                } else {
                    StartDrivingTest(playerid, 1);
                    return 1;
                }
            }
            case 2: { // SIM C
                if (gPlayerData[playerid][p_HasSIM_C]) {
                    if (!Inventory_HasItem(playerid, ITEM_SIM_C)) {
                        if (gPlayerData[playerid][p_Cash] < 10000) {
                            SendClientMessage(playerid, COL_RED, "  [DMV] Uang Anda tidak cukup untuk biaya cetak ulang kartu SIM C (Rp 10.000)!");
                            return 1;
                        }
                        gPlayerData[playerid][p_Cash] -= 10000;
                        new qCash[128];
                        format(qCash, sizeof(qCash), "UPDATE `characters` SET `cash`=%d WHERE `id`=%d", gPlayerData[playerid][p_Cash], gPlayerData[playerid][p_CharID]);
                        DB_FreeResultSet(DB_ExecuteQuery(gDB, qCash));
                        UpdatePlayerMoneyHUD(playerid);

                        Inventory_AddItem(playerid, ITEM_SIM_C, 1);
                        PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
                        SendClientMessage(playerid, COL_GREEN, "  [DMV] Berhasil mencetak ulang fisik Kartu SIM C Anda seharga {2ECC71}Rp 10.000{FFFFFF}.");
                        return 1;
                    } else {
                        SendClientMessage(playerid, COL_GREEN, "  [DMV] Anda sudah memiliki SIM C aktif dan membawa fisik kartunya di tas (/inv).");
                        return 1;
                    }
                } else {
                    StartDrivingTest(playerid, 2);
                    return 1;
                }
            }
        }
        return 1;
    }
    return 0;
}

CMD:buatsim(playerid, params[]) {
    #pragma unused params
    if (!CheckSpawned(playerid)) return 1;

    if (!IsPlayerInRangeOfPoint(playerid, 3.5, DMV_DESK_X, DMV_DESK_Y, DMV_DESK_Z)) {
        SendClientMessage(playerid, COL_RED, "  [Error] Anda harus berada di depan Loket Satpas DMV Driving School (San Fierro)!");
        return 1;
    }

    ShowDMVDialog(playerid);
    PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
    return 1;
}

CMD:dmv(playerid, params[]) {
    return cmd_buatsim(playerid, params);
}
