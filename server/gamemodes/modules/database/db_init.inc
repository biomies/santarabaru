#if defined _MODULE_DB_INIT_INC
    #endinput
#endif
#define _MODULE_DB_INIT_INC

// ============================================================
//  SantaraBaru Roleplay - Database Initialization & Migrations
// ============================================================

stock DB_InitDatabase() {
    gDB = DB_Open("santara_rp.db");
    if (!gDB) {
        print("[FATAL] Gagal membuka database open.mp native!");
        SendRconCommand("exit");
        return 0;
    }
    printf("[Database] Database 'santara_rp.db' aktif.");

    // Buat tabel accounts, characters, dan player_vehicles jika belum ada
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "CREATE TABLE IF NOT EXISTS `accounts` (`id` INTEGER PRIMARY KEY AUTOINCREMENT, `username` TEXT UNIQUE NOT NULL, `password` TEXT NOT NULL, `admin_level` INTEGER DEFAULT 0, `is_banned` INTEGER DEFAULT 0, `ban_reason` TEXT DEFAULT '', `created_at` DATETIME DEFAULT CURRENT_TIMESTAMP, `last_login` DATETIME);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "CREATE TABLE IF NOT EXISTS `characters` (`id` INTEGER PRIMARY KEY AUTOINCREMENT, `account_id` INTEGER NOT NULL, `char_name` TEXT UNIQUE NOT NULL, `birthplace` TEXT DEFAULT 'San Fierro', `birthdate` TEXT DEFAULT '01/01/2000', `gender` INTEGER DEFAULT 1, `skin_id` INTEGER DEFAULT 0, `x` REAL DEFAULT 1958.33, `y` REAL DEFAULT 1343.12, `z` REAL DEFAULT 15.36, `angle` REAL DEFAULT 270.0, `score` INTEGER DEFAULT 1, `cash` INTEGER DEFAULT 500, `play_minutes` INTEGER DEFAULT 0, `has_ktp` INTEGER DEFAULT 0, `hunger` REAL DEFAULT 100.0, `thirst` REAL DEFAULT 100.0, `is_active` INTEGER DEFAULT 1, `created_at` DATETIME DEFAULT CURRENT_TIMESTAMP, `last_login` DATETIME);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "CREATE TABLE IF NOT EXISTS `player_vehicles` (`id` INTEGER PRIMARY KEY AUTOINCREMENT, `char_id` INTEGER NOT NULL, `model_id` INTEGER NOT NULL, `plate` TEXT DEFAULT 'SAN-001', `color1` INTEGER DEFAULT 1, `color2` INTEGER DEFAULT 1, `price` INTEGER DEFAULT 0, `x` REAL DEFAULT 539.5, `y` REAL DEFAULT -1273.0, `z` REAL DEFAULT 17.24, `angle` REAL DEFAULT 180.0, `health` REAL DEFAULT 1000.0, `locked` INTEGER DEFAULT 0, `status` INTEGER DEFAULT 0, `garage_id` INTEGER DEFAULT 1, `insurance_cost` INTEGER DEFAULT 1500000, `created_at` DATETIME DEFAULT CURRENT_TIMESTAMP);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "CREATE TABLE IF NOT EXISTS `inventory` (`id` INTEGER PRIMARY KEY AUTOINCREMENT, `char_id` INTEGER NOT NULL, `item_id` INTEGER NOT NULL, `amount` INTEGER NOT NULL DEFAULT 1, `created_at` DATETIME DEFAULT CURRENT_TIMESTAMP);"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "CREATE TABLE IF NOT EXISTS `vehicle_trunk` (`id` INTEGER PRIMARY KEY AUTOINCREMENT, `veh_dbid` INTEGER NOT NULL, `item_id` INTEGER NOT NULL, `amount` INTEGER NOT NULL DEFAULT 1, `created_at` DATETIME DEFAULT CURRENT_TIMESTAMP);"));

    // Tambah kolom baru jika database sudah ada sebelumnya (ALTER TABLE)
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `accounts` ADD COLUMN `admin_level` INTEGER DEFAULT 0;"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `characters` ADD COLUMN `birthplace` TEXT DEFAULT 'San Fierro';"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `characters` ADD COLUMN `birthdate` TEXT DEFAULT '01/01/2000';"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `characters` ADD COLUMN `gender` INTEGER DEFAULT 1;"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `characters` ADD COLUMN `has_ktp` INTEGER DEFAULT 0;"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `characters` ADD COLUMN `hunger` REAL DEFAULT 100.0;"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `characters` ADD COLUMN `thirst` REAL DEFAULT 100.0;"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `characters` ADD COLUMN `is_active` INTEGER DEFAULT 1;"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `player_vehicles` ADD COLUMN `status` INTEGER DEFAULT 0;"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `player_vehicles` ADD COLUMN `garage_id` INTEGER DEFAULT 1;"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "ALTER TABLE `player_vehicles` ADD COLUMN `insurance_cost` INTEGER DEFAULT 1500000;"));

    // Migrasi otomatis data dari tabel lama jika ada
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "INSERT OR IGNORE INTO `accounts` (`id`, `username`, `password`, `is_banned`, `ban_reason`, `created_at`, `last_login`) SELECT `id`, `username`, `password`, `is_banned`, `ban_reason`, `created_at`, `last_login` FROM `players` WHERE EXISTS (SELECT 1 FROM sqlite_master WHERE type='table' AND name='players');"));
    DB_FreeResultSet(DB_ExecuteQuery(gDB, "INSERT OR IGNORE INTO `characters` (`account_id`, `char_name`, `skin_id`, `x`, `y`, `z`, `angle`, `score`, `cash`, `play_minutes`, `created_at`, `last_login`) SELECT `id`, `char_name`, `skin_id`, `x`, `y`, `z`, `angle`, `score`, `cash`, `play_minutes`, `created_at`, `last_login` FROM `players` WHERE `char_name` != '' AND EXISTS (SELECT 1 FROM sqlite_master WHERE type='table' AND name='players');"));
    return 1;
}

stock DB_CloseDatabase() {
    if (gDB) {
        DB_Close(gDB);
        gDB = DB:0;
    }
}
