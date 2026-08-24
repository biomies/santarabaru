-- ============================================================
-- SantaraBaru Roleplay — Database Schema
-- Dijalankan otomatis saat MySQL container pertama kali dibuat
-- ============================================================

CREATE DATABASE IF NOT EXISTS `santara_rp`
    CHARACTER SET utf8mb4
    COLLATE utf8mb4_unicode_ci;

USE `santara_rp`;

-- ── Tabel Players ────────────────────────────────────────────
CREATE TABLE IF NOT EXISTS `players` (
    `id`            INT          UNSIGNED NOT NULL AUTO_INCREMENT,
    `username`      VARCHAR(24)  NOT NULL UNIQUE COMMENT 'Nama SA-MP player (login name)',
    `password`      VARCHAR(130) NOT NULL COMMENT 'Whirlpool hash dari password',
    `char_name`     VARCHAR(48)  NOT NULL DEFAULT '' COMMENT 'Nama karakter RP (Nama Depan Nama Belakang)',
    `skin_id`       SMALLINT     UNSIGNED NOT NULL DEFAULT 0 COMMENT 'ID skin GTA SA',

    -- Posisi terakhir
    `x`             FLOAT        NOT NULL DEFAULT 1958.33,
    `y`             FLOAT        NOT NULL DEFAULT 1343.12,
    `z`             FLOAT        NOT NULL DEFAULT 15.36,
    `angle`         FLOAT        NOT NULL DEFAULT 270.0,

    -- Statistik
    `score`         INT          NOT NULL DEFAULT 0,
    `cash`          INT          NOT NULL DEFAULT 500,
    `play_minutes`  INT          UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Total menit bermain',

    -- Status akun
    `registered`    TINYINT(1)   NOT NULL DEFAULT 1,
    `is_banned`     TINYINT(1)   NOT NULL DEFAULT 0,
    `ban_reason`    VARCHAR(128) DEFAULT NULL,

    -- Timestamps
    `created_at`    TIMESTAMP    NOT NULL DEFAULT CURRENT_TIMESTAMP,
    `last_login`    TIMESTAMP    NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,

    PRIMARY KEY (`id`),
    INDEX `idx_username` (`username`),
    INDEX `idx_char_name` (`char_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci
  COMMENT='Data akun dan karakter pemain';

-- ── Tabel Admin Logs ─────────────────────────────────────────
CREATE TABLE IF NOT EXISTS `admin_logs` (
    `id`         INT         UNSIGNED NOT NULL AUTO_INCREMENT,
    `admin_id`   INT         UNSIGNED NOT NULL,
    `target_id`  INT         UNSIGNED DEFAULT NULL,
    `action`     VARCHAR(64) NOT NULL,
    `detail`     TEXT        DEFAULT NULL,
    `logged_at`  TIMESTAMP   NOT NULL DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (`id`),
    INDEX `idx_admin` (`admin_id`),
    INDEX `idx_target` (`target_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='Log aksi admin';

-- ── Data default (untuk testing) ─────────────────────────────
-- Akun test: username=Admin, password=admin123
-- WP_Hash("admin123") = a2f6469e7bfe94e4e02de0b78c66503c94b53e0a...
-- Catatan: Hash ini hanya placeholder, ganti via in-game register
