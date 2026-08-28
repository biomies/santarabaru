#if defined _MODULE_PLAYER_DATA_INC
    #endinput
#endif
#define _MODULE_PLAYER_DATA_INC

// ============================================================
//  SantaraBaru Roleplay - Player Data & Global Variables
// ============================================================

enum E_PLAYER_DATA {
    p_AccountID,                // ID akun di tabel accounts
    p_CharID,                   // ID karakter aktif di tabel characters
    p_Username[MAX_PLAYER_NAME + 1],
    p_CharName[48],             // Nama karakter RP aktif
    p_BirthPlace[32],           // Tempat lahir
    p_BirthDate[16],            // Tanggal lahir (DD/MM/YYYY)
    p_Gender,                   // 1 = Pria, 2 = Wanita
    p_Skin,                     // Skin ID GTA SA
    Float:p_X,
    Float:p_Y,
    Float:p_Z,
    Float:p_A,                  // Angle / arah hadap
    p_Score,
    p_Cash,
    bool:p_Registered,
    bool:p_LoggedIn,
    p_LoginTries,               // Counter gagal login
    bool:p_Spawned,
    p_PlayTime,                 // Menit bermain sesi ini (timer)
    SV_GSTREAM:p_VoiceStream,   // SAMPVOICE local stream
    //    Multi-Character Temp Cache   
    p_CharListIDs[MAX_CHARS_PER_ACCOUNT],
    p_CharListCount,
    p_TempSelectedCharID,
    p_TempSelectedCharName[48],
    //    Live Eagle-Eye Spawn Selector State   
    bool:p_SelectingSpawn,
    p_SpawnIndex,
    //    Live 3D Skin Selector State   
    bool:p_SelectingSkin,
    p_SkinIndex,
    bool:p_SelectingChar3D,
    p_OriginalSkin,
    bool:p_IsNewCharacter,
    bool:p_InCharForm,          // Status membuka form UI Buat Karakter TextDraw
    //    Status Kepemilikan Dokumen   
    bool:p_HasKTP,
    //    Status Download Custom Asset   
    bool:p_FinishedDownload,
    bool:p_AuthLoaded,
    //    Status Dealership & Kendaraan Pribadi   
    bool:p_InDealership,
    p_DealerCat,
    p_DealerIndex,
    p_DealerColorIdx,
    p_DealerPreviewVeh,
    #define MAX_PLAYER_SPAWNED_VEHICLES 5
    p_ActiveVehID[MAX_PLAYER_SPAWNED_VEHICLES],
    p_ActiveVehDBID[MAX_PLAYER_SPAWNED_VEHICLES],
    //    Status Live 3D Garasi Kota & Manajemen Kendaraan   
    bool:p_InGarageUI,
    p_GarageCurrentID,
    p_GarageVehIndex,
    p_GarageVehCount,
    p_GarageVehDBIDs[32],
    p_GaragePreviewVeh,
    p_SelectedVehDBID,
    p_VehListDBIDs[32],
    p_VehListCount,
    bool:p_HasActiveCheckpoint,
    //    Status Kebutuhan Hidup & Vitalitas   
    Float:p_Hunger,             // 0.0 - 100.0%
    Float:p_Thirst,             // 0.0 - 100.0%
    //    Status Sesi Inventory Pemain   
    bool:p_InInventoryUI,
    p_InvCurrentPage,
    p_InvSlotItemID[64],
    p_InvSlotAmount[64],
    p_InvItemCount,
    p_SelectedInvSlot,
    p_SelectedInvItemID,
    p_TargetGivePlayerID,
    //    Status Sesi Bagasi Mobil (Vehicle Trunk)   
    bool:p_InTrunkUI,
    p_TrunkVehID,
    p_TrunkVehDBID,
    p_TrunkActiveTab,           // 0 = Isi Bagasi Mobil, 1 = Barang di Tas Karakter
    p_TrunkCurrentPage,
    p_TrunkSlotItemID[64],
    p_TrunkSlotAmount[64],
    p_TrunkItemCount,
    p_SelectedTrunkSlot,
    p_SelectedTrunkItemID,
    //    Status Pekerjaan Karakter
    p_Job,                      // 0 = Pengangguran
    //    Status Administrator Akun   
    p_AdminLevel,               // 0 = Player, 1 = Admin, 2 = Owner
    bool:p_AdminDuty,           // Status On-Duty Admin
    //    Status Interior & Eksterior Gedung   
    Float:p_LastExtX,
    Float:p_LastExtY,
    Float:p_LastExtZ,
    Float:p_LastExtA,
    p_LastExtVW,
    p_SelectedBuyItem,
    //    Status Surat Izin Mengemudi (SIM)
    bool:p_HasSIM_A,
    bool:p_HasSIM_B,
    bool:p_HasSIM_C,
    //    Status Ujian Praktik Mengemudi (Driving Test)
    bool:p_InDrivingTest,
    p_DrivingTestVehID,
    p_DrivingTestStep,
    p_DrivingTestErrors,
    p_DrivingTestType,          // 1: SIM A, 2: SIM B, 3: SIM C
    Float:p_DrivingVehLastHealth,
    //    Status Panel UI SIM (Right Sidebar)
    bool:p_InDokumenUI,
    p_SelectedDokumenIndex,         // 0: SIM A, 1: SIM B, 2: SIM C
    p_ViewingSimTarget
}

new gPlayerData[MAX_PLAYERS][E_PLAYER_DATA];
new gCharListNames[MAX_PLAYERS][MAX_CHARS_PER_ACCOUNT][48];
new DB:gDB;                     // open.mp native DB handle (santara_players.db)
new DB:gDB_Master;              // open.mp native DB handle (santara_master.db)
new bool:gVoiceEnabled;         // SAMPVOICE terinisialisasi?
new gPlayTimeTimer;             // Timer untuk hitung waktu bermain

stock ResetPlayerData(playerid) {
    gPlayerData[playerid][p_AccountID]      = 0;
    gPlayerData[playerid][p_CharID]         = 0;
    gPlayerData[playerid][p_Username][0]    = '\0';
    gPlayerData[playerid][p_CharName][0]    = '\0';
    format(gPlayerData[playerid][p_BirthPlace], 32, "San Fierro");
    format(gPlayerData[playerid][p_BirthDate], 16, "01/01/2000");
    gPlayerData[playerid][p_Gender]         = 1;
    gPlayerData[playerid][p_Skin]           = 0;
    gPlayerData[playerid][p_Job]            = 0;
    gPlayerData[playerid][p_X]              = SPAWN_BUS_X;
    gPlayerData[playerid][p_Y]              = SPAWN_BUS_Y;
    gPlayerData[playerid][p_Z]              = SPAWN_BUS_Z;
    gPlayerData[playerid][p_A]              = SPAWN_BUS_A;
    gPlayerData[playerid][p_LastExtX]       = 0.0;
    gPlayerData[playerid][p_LastExtY]       = 0.0;
    gPlayerData[playerid][p_LastExtZ]       = 0.0;
    gPlayerData[playerid][p_LastExtA]       = 0.0;
    gPlayerData[playerid][p_LastExtVW]      = 0;
    gPlayerData[playerid][p_SelectedBuyItem]= 0;
    gPlayerData[playerid][p_HasSIM_A]       = false;
    gPlayerData[playerid][p_HasSIM_B]       = false;
    gPlayerData[playerid][p_HasSIM_C]       = false;
    gPlayerData[playerid][p_InDrivingTest]  = false;
    gPlayerData[playerid][p_DrivingTestVehID] = INVALID_VEHICLE_ID;
    gPlayerData[playerid][p_DrivingTestStep] = 0;
    gPlayerData[playerid][p_DrivingTestErrors] = 0;
    gPlayerData[playerid][p_DrivingTestType] = 0;
    gPlayerData[playerid][p_DrivingVehLastHealth] = 1000.0;
    gPlayerData[playerid][p_InDokumenUI]        = false;
    gPlayerData[playerid][p_SelectedDokumenIndex] = 0;
    gPlayerData[playerid][p_ViewingSimTarget] = INVALID_PLAYER_ID;
    gPlayerData[playerid][p_Score]          = 1;
    gPlayerData[playerid][p_Cash]           = 500;
    gPlayerData[playerid][p_Hunger]         = 100.0;
    gPlayerData[playerid][p_Thirst]         = 100.0;
    gPlayerData[playerid][p_Registered]     = false;
    gPlayerData[playerid][p_LoggedIn]       = false;
    gPlayerData[playerid][p_Spawned]        = false;
    gPlayerData[playerid][p_LoginTries]     = 0;
    gPlayerData[playerid][p_PlayTime]       = 0;
    gPlayerData[playerid][p_VoiceStream]    = SV_NULL;
    gPlayerData[playerid][p_CharListCount]  = 0;
    gPlayerData[playerid][p_TempSelectedCharID] = 0;
    gPlayerData[playerid][p_TempSelectedCharName][0] = '\0';
    for (new c = 0; c < MAX_CHARS_PER_ACCOUNT; c++) {
        gPlayerData[playerid][p_CharListIDs][c] = 0;
        gCharListNames[playerid][c][0] = '\0';
    }
    gPlayerData[playerid][p_SelectingSpawn] = false;
    gPlayerData[playerid][p_SpawnIndex]     = 0;
    gPlayerData[playerid][p_SelectingSkin]  = false;
    gPlayerData[playerid][p_SkinIndex]      = 0;
    gPlayerData[playerid][p_OriginalSkin]   = 0;
    gPlayerData[playerid][p_IsNewCharacter] = false;
    gPlayerData[playerid][p_InCharForm]     = false;
    gPlayerData[playerid][p_HasKTP]         = false;
    gPlayerData[playerid][p_FinishedDownload] = false;
    gPlayerData[playerid][p_AuthLoaded]     = false;
    gPlayerData[playerid][p_InDealership]   = false;
    gPlayerData[playerid][p_DealerCat]      = 0;
    gPlayerData[playerid][p_DealerIndex]    = 0;
    gPlayerData[playerid][p_DealerColorIdx] = 0;
    gPlayerData[playerid][p_DealerPreviewVeh] = INVALID_VEHICLE_ID;
    for (new v = 0; v < MAX_PLAYER_SPAWNED_VEHICLES; v++) {
        gPlayerData[playerid][p_ActiveVehID][v]    = INVALID_VEHICLE_ID;
        gPlayerData[playerid][p_ActiveVehDBID][v]  = 0;
    }
    gPlayerData[playerid][p_InGarageUI]     = false;
    gPlayerData[playerid][p_GarageCurrentID] = 0;
    gPlayerData[playerid][p_GarageVehIndex] = 0;
    gPlayerData[playerid][p_GarageVehCount] = 0;
    for (new v = 0; v < 32; v++) {
        gPlayerData[playerid][p_GarageVehDBIDs][v] = 0;
        gPlayerData[playerid][p_VehListDBIDs][v] = 0;
    }
    gPlayerData[playerid][p_GaragePreviewVeh] = INVALID_VEHICLE_ID;
    gPlayerData[playerid][p_SelectedVehDBID] = 0;
    gPlayerData[playerid][p_VehListCount]   = 0;
    gPlayerData[playerid][p_HasActiveCheckpoint] = false;
    gPlayerData[playerid][p_InInventoryUI]  = false;
    gPlayerData[playerid][p_InvCurrentPage] = 0;
    gPlayerData[playerid][p_InvItemCount]   = 0;
    gPlayerData[playerid][p_SelectedInvSlot] = -1;
    gPlayerData[playerid][p_SelectedInvItemID] = 0;
    gPlayerData[playerid][p_TargetGivePlayerID] = INVALID_PLAYER_ID;
    gPlayerData[playerid][p_InTrunkUI]      = false;
    gPlayerData[playerid][p_TrunkVehID]     = INVALID_VEHICLE_ID;
    gPlayerData[playerid][p_TrunkVehDBID]   = 0;
    gPlayerData[playerid][p_TrunkActiveTab] = 0;
    gPlayerData[playerid][p_TrunkCurrentPage] = 0;
    gPlayerData[playerid][p_TrunkItemCount] = 0;
    gPlayerData[playerid][p_SelectedTrunkSlot] = -1;
    gPlayerData[playerid][p_SelectedTrunkItemID] = 0;
    gPlayerData[playerid][p_AdminLevel]     = 0;
    gPlayerData[playerid][p_AdminDuty]      = false;
}
