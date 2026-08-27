#if defined _MODULE_DB_INIT_INC
    #endinput
#endif
#define _MODULE_DB_INIT_INC

// ============================================================
//  SantaraBaru Roleplay - Database Initialization & Migrations
// ============================================================

stock DB_InitDatabase() {
    // 1. Database Data Pemain (Dynamic User Data)
    gDB = DB_Open("santara_players.db");
    if (!gDB) {
        print("[FATAL] Gagal membuka database pemain 'santara_players.db'!");
        SendRconCommand("exit");
        return 0;
    }
    printf("[Database] Database Pemain 'santara_players.db' aktif.");

    // 2. Database Master Game (Development Data)
    gDB_Master = DB_Open("santara_master.db");
    if (!gDB_Master) {
        print("[FATAL] Gagal membuka database master 'santara_master.db'!");
        SendRconCommand("exit");
        return 0;
    }
    printf("[Database] Database Master Game 'santara_master.db' aktif.");

    // ─── Tabel di santara_players.db (Data Pemain) ───
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "CREATE TABLE IF NOT EXISTS `accounts` (`id` INTEGER PRIMARY KEY AUTOINCREMENT, `username` TEXT UNIQUE NOT NULL, `password` TEXT NOT NULL, `admin_level` INTEGER DEFAULT 0, `is_banned` INTEGER DEFAULT 0, `ban_reason` TEXT DEFAULT '', `created_at` DATETIME DEFAULT CURRENT_TIMESTAMP, `last_login` DATETIME);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "CREATE TABLE IF NOT EXISTS `characters` (`id` INTEGER PRIMARY KEY AUTOINCREMENT, `account_id` INTEGER NOT NULL, `char_name` TEXT UNIQUE NOT NULL, `birthplace` TEXT DEFAULT 'San Fierro', `birthdate` TEXT DEFAULT '01/01/2000', `gender` INTEGER DEFAULT 1, `skin_id` INTEGER DEFAULT 0, `job_id` INTEGER DEFAULT 0, `x` REAL DEFAULT 1958.33, `y` REAL DEFAULT 1343.12, `z` REAL DEFAULT 15.36, `angle` REAL DEFAULT 270.0, `score` INTEGER DEFAULT 1, `cash` INTEGER DEFAULT 500, `play_minutes` INTEGER DEFAULT 0, `has_ktp` INTEGER DEFAULT 0, `sim_a` INTEGER DEFAULT 0, `sim_b` INTEGER DEFAULT 0, `sim_c` INTEGER DEFAULT 0, `hunger` REAL DEFAULT 100.0, `thirst` REAL DEFAULT 100.0, `is_active` INTEGER DEFAULT 1, `created_at` DATETIME DEFAULT CURRENT_TIMESTAMP, `last_login` DATETIME);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "CREATE TABLE IF NOT EXISTS `player_vehicles` (`id` INTEGER PRIMARY KEY AUTOINCREMENT, `char_id` INTEGER NOT NULL, `model_id` INTEGER NOT NULL, `plate` TEXT DEFAULT 'SAN-001', `color1` INTEGER DEFAULT 1, `color2` INTEGER DEFAULT 1, `price` INTEGER DEFAULT 0, `x` REAL DEFAULT 539.5, `y` REAL DEFAULT -1273.0, `z` REAL DEFAULT 17.24, `angle` REAL DEFAULT 180.0, `health` REAL DEFAULT 1000.0, `locked` INTEGER DEFAULT 0, `status` INTEGER DEFAULT 0, `garage_id` INTEGER DEFAULT 1, `insurance_cost` INTEGER DEFAULT 1500000, `created_at` DATETIME DEFAULT CURRENT_TIMESTAMP);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "CREATE TABLE IF NOT EXISTS `inventory` (`id` INTEGER PRIMARY KEY AUTOINCREMENT, `char_id` INTEGER NOT NULL, `item_id` INTEGER NOT NULL, `amount` INTEGER NOT NULL DEFAULT 1, `created_at` DATETIME DEFAULT CURRENT_TIMESTAMP);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "CREATE TABLE IF NOT EXISTS `vehicle_trunk` (`id` INTEGER PRIMARY KEY AUTOINCREMENT, `veh_dbid` INTEGER NOT NULL, `item_id` INTEGER NOT NULL, `amount` INTEGER NOT NULL DEFAULT 1, `created_at` DATETIME DEFAULT CURRENT_TIMESTAMP);"));

    // ALTER TABLE jika ada kolom baru pada santara_players.db
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `accounts` ADD COLUMN `admin_level` INTEGER DEFAULT 0;"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `characters` ADD COLUMN `birthplace` TEXT DEFAULT 'San Fierro';"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `characters` ADD COLUMN `birthdate` TEXT DEFAULT '01/01/2000';"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `characters` ADD COLUMN `gender` INTEGER DEFAULT 1;"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `characters` ADD COLUMN `has_ktp` INTEGER DEFAULT 0;"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `characters` ADD COLUMN `sim_a` INTEGER DEFAULT 0;"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `characters` ADD COLUMN `sim_b` INTEGER DEFAULT 0;"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `characters` ADD COLUMN `sim_c` INTEGER DEFAULT 0;"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `characters` ADD COLUMN `hunger` REAL DEFAULT 100.0;"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `characters` ADD COLUMN `thirst` REAL DEFAULT 100.0;"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `characters` ADD COLUMN `is_active` INTEGER DEFAULT 1;"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `characters` ADD COLUMN `job_id` INTEGER DEFAULT 0;"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `player_vehicles` ADD COLUMN `status` INTEGER DEFAULT 0;"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `player_vehicles` ADD COLUMN `garage_id` INTEGER DEFAULT 1;"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `player_vehicles` ADD COLUMN `insurance_cost` INTEGER DEFAULT 1500000;"));

    // Migrasi otomatis data dari tabel lama santara_rp.db / players jika ada
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "INSERT OR IGNORE INTO `accounts` (`id`, `username`, `password`, `is_banned`, `ban_reason`, `created_at`, `last_login`) SELECT `id`, `username`, `password`, `is_banned`, `ban_reason`, `created_at`, `last_login` FROM `players` WHERE EXISTS (SELECT 1 FROM sqlite_master WHERE type='table' AND name='players');"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "INSERT OR IGNORE INTO `characters` (`account_id`, `char_name`, `skin_id`, `x`, `y`, `z`, `angle`, `score`, `cash`, `play_minutes`, `created_at`, `last_login`) SELECT `id`, `char_name`, `skin_id`, `x`, `y`, `z`, `angle`, `score`, `cash`, `play_minutes`, `created_at`, `last_login` FROM `players` WHERE `char_name` != '' AND EXISTS (SELECT 1 FROM sqlite_master WHERE type='table' AND name='players');"));

    // ─── Tabel di santara_master.db (Data Master Game) ───
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "CREATE TABLE IF NOT EXISTS `jobs` (`id` INTEGER PRIMARY KEY, `name` TEXT NOT NULL, `salary` INTEGER DEFAULT 0, `created_at` DATETIME DEFAULT CURRENT_TIMESTAMP);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "CREATE TABLE IF NOT EXISTS `items` (`id` INTEGER PRIMARY KEY, `name` TEXT NOT NULL, `category` TEXT NOT NULL, `hunger` REAL DEFAULT 0.0, `thirst` REAL DEFAULT 0.0, `health` REAL DEFAULT 0.0, `is_full_heal` INTEGER DEFAULT 0, `anim_lib` TEXT DEFAULT '', `anim_name` TEXT DEFAULT '', `price` INTEGER DEFAULT 0, `created_at` DATETIME DEFAULT CURRENT_TIMESTAMP);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "CREATE TABLE IF NOT EXISTS `dealership_vehicles` (`id` INTEGER PRIMARY KEY AUTOINCREMENT, `model_id` INTEGER NOT NULL, `name` TEXT NOT NULL, `description` TEXT NOT NULL, `category` INTEGER NOT NULL, `price` INTEGER NOT NULL, `top_speed` INTEGER NOT NULL, `seats` INTEGER NOT NULL, `created_at` DATETIME DEFAULT CURRENT_TIMESTAMP);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "CREATE TABLE IF NOT EXISTS `dealership_colors` (`id` INTEGER PRIMARY KEY AUTOINCREMENT, `color_id` INTEGER NOT NULL, `name` TEXT NOT NULL, `created_at` DATETIME DEFAULT CURRENT_TIMESTAMP);"));

    // Seed Data Master Pekerjaan di santara_master.db
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `jobs` (`id`, `name`, `salary`) VALUES (0, 'Pengangguran', 0);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `jobs` (`id`, `name`, `salary`) VALUES (1, 'Supir Taksi', 150000);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `jobs` (`id`, `name`, `salary`) VALUES (2, 'Mekanik', 200000);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `jobs` (`id`, `name`, `salary`) VALUES (3, 'Kurir Paket', 175000);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `jobs` (`id`, `name`, `salary`) VALUES (4, 'Supir Truk', 250000);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `jobs` (`id`, `name`, `salary`) VALUES (5, 'Petani', 160000);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `jobs` (`id`, `name`, `salary`) VALUES (6, 'Dokter / Medis', 300000);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `jobs` (`id`, `name`, `salary`) VALUES (7, 'Polisi', 350000);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `jobs` (`id`, `name`, `salary`) VALUES (8, 'Pedagang / Kasir', 140000);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `jobs` (`id`, `name`, `salary`) VALUES (9, 'Pemadam Kebakaran', 280000);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `jobs` (`id`, `name`, `salary`) VALUES (10, 'Pengacara / Advokat', 400000);"));

    // Seed Data Master Barang (Items) di santara_master.db (12 Item)
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `items` VALUES (1, 'Burger', 'Makanan', 40.0, 0.0, 0.0, 0, 'FOOD', 'eat_burger', 25000, CURRENT_TIMESTAMP);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `items` VALUES (2, 'Hotdog', 'Makanan', 35.0, 0.0, 0.0, 0, 'FOOD', 'eat_burger', 20000, CURRENT_TIMESTAMP);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `items` VALUES (3, 'Pizza', 'Makanan', 50.0, 0.0, 0.0, 0, 'FOOD', 'eat_pizza', 40000, CURRENT_TIMESTAMP);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `items` VALUES (4, 'Air Mineral', 'Minuman', 0.0, 35.0, 0.0, 0, 'DRINK_cw', 'drink_sprank', 5000, CURRENT_TIMESTAMP);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `items` VALUES (5, 'Cola', 'Minuman', 0.0, 40.0, 0.0, 0, 'DRINK_cw', 'drink_sprank', 10000, CURRENT_TIMESTAMP);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `items` VALUES (6, 'Milkshake', 'Minuman', 10.0, 45.0, 0.0, 0, 'DRINK_cw', 'drink_sprank', 20000, CURRENT_TIMESTAMP);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `items` VALUES (7, 'Bandage', 'Medis / Obat', 0.0, 0.0, 25.0, 0, 'MISC', 'bitchslap', 25000, CURRENT_TIMESTAMP);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `items` VALUES (8, 'Medkit', 'Medis / Obat', 0.0, 0.0, 60.0, 0, 'MISC', 'bitchslap', 60000, CURRENT_TIMESTAMP);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `items` VALUES (9, 'First Aid Kit', 'Medis / Obat', 0.0, 0.0, 100.0, 1, 'MISC', 'bitchslap', 120000, CURRENT_TIMESTAMP);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `items` VALUES (10, 'Ponsel', 'Elektronik', 0.0, 0.0, 0.0, 0, '', '', 150000, CURRENT_TIMESTAMP);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `items` VALUES (11, 'KTP (Kartu Identitas)', 'Dokumen', 0.0, 0.0, 0.0, 0, '', '', 50000, CURRENT_TIMESTAMP);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `items` VALUES (12, 'Surat Izin Mengemudi (SIM A)', 'Dokumen', 0.0, 0.0, 0.0, 0, '', '', 50000, CURRENT_TIMESTAMP);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `items` VALUES (13, 'Surat Izin Mengemudi (SIM B)', 'Dokumen', 0.0, 0.0, 0.0, 0, '', '', 100000, CURRENT_TIMESTAMP);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "INSERT OR IGNORE INTO `items` VALUES (14, 'Surat Izin Mengemudi (SIM C)', 'Dokumen', 0.0, 0.0, 0.0, 0, '', '', 25000, CURRENT_TIMESTAMP);"));
    // Update nama lama jika ada
    DB_FreeResultSet(DB_ExecuteQuery(gDB_Master, "UPDATE `items` SET `name`='Surat Izin Mengemudi (SIM A)' WHERE `id`=12;"));

    return 1;
}

stock DB_CloseDatabase() {
    if (gDB) {
        DB_Close(gDB);
        gDB = DB:0;
    }
    if (gDB_Master) {
        DB_Close(gDB_Master);
        gDB_Master = DB:0;
    }
}

