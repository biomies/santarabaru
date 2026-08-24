# SantaraBaru Roleplay Server

> Server SA-MP Roleplay Indonesia berbasis **open.mp** — berjalan di Docker, bisa dimainkan dari PC maupun Android.

---

## 🚀 Quick Start

### Prasyarat
- [Docker](https://docs.docker.com/get-docker/) + [Docker Compose](https://docs.docker.com/compose/install/) terinstall
- Akun [playit.gg](https://playit.gg) (untuk akses publik)

### 1. Clone & Setup Environment

```bash
cd SantaraBaru
cp .env.example .env
nano .env   # Edit password dan konfigurasi sesuai kebutuhan
```

### 2. Dapatkan playit.gg Secret Key

1. Buka [https://playit.gg](https://playit.gg) → Login / Daftar
2. Klik **New Agent** → pilih **Docker**
3. Salin **Secret Key** yang diberikan
4. Paste ke `.env` → `PLAYIT_SECRET=key_anda_disini`

### 3. Jalankan Server

```bash
docker compose up -d --build
```

> Build pertama membutuhkan waktu lebih lama (download open.mp, plugins, dll.)

### 4. Cek Status

```bash
# Lihat semua container
docker compose ps

# Lihat log server SA-MP
docker compose logs -f omp-server

# Lihat log MySQL
docker compose logs mysql
```

### 5. Setup Tunnel playit.gg

Setelah container playit jalan:
1. Buka [https://playit.gg/manage](https://playit.gg/manage)
2. Klik agent yang muncul → **Add Tunnel**
3. Pilih **Custom UDP**
4. Local: `omp-server:7777`
5. Salin alamat publik (contoh: `abc.playit.gg:12345`)
6. Bagikan ke pemain!

---

## 📱 Cara Main

### PC (SA-MP / open.mp)

1. Download [SA-MP 0.3.7](https://www.sa-mp.mp/) atau [open.mp client](https://open.mp)
2. Buka → Add Server → masukkan IP dari playit.gg
3. Sambungkan!

### Android

1. Download **[Alyn SA-MP Mobile](https://play.google.com/store)** dari Play Store
   - Launcher ini sudah include dukungan **voice chat (Opus)** built-in
2. Buka app → Add Server → masukkan IP dari playit.gg
3. Grant izin **Microphone** saat diminta
4. Sambungkan!

---

## 🎮 Fitur Server

### Sistem Akun
- **Register** — Akun baru dibuat otomatis saat pertama join
- **Login** — Password di-hash dengan Whirlpool (aman)
- **Auto-save** — Data disimpan setiap 5 menit & saat disconnect

### Karakter RP
- **Nama Karakter** — Format: Nama Depan Nama Belakang (contoh: Budi Santoso)
- **Pilih Skin** — Lebih dari 40 skin tersedia dalam kategori
- **Posisi Tersimpan** — Karakter spawn di posisi terakhir logout

### 🎙️ Voice Chat (Proximity)
| Jenis | Radius | Keterangan |
|-------|--------|------------|
| Voice Chat | 20m | Bicara langsung via mikrofon |

Untuk Android: gunakan **Alyn SA-MP Mobile** launcher (sudah support voice).

### 💬 Text Chat RP (Fallback)
| Perintah | Radius | Warna |
|----------|--------|-------|
| Chat biasa | 20m | Putih |
| `/s [pesan]` | 20m | Putih |
| `/sh [pesan]` | 40m | Kuning (UPPERCASE) |
| `/w [pesan]` | 5m | Abu-abu |
| `/me [aksi]` | 20m | Ungu |
| `/do [deskripsi]` | 20m | Cyan |
| `/ooc [pesan]` | Global | Kuning gelap |

### Perintah Lainnya
| Perintah | Fungsi |
|----------|--------|
| `/help` | Lihat semua perintah |
| `/voice` | Status voice chat |
| `/skin` | Ganti skin karakter |
| `/whoami` | Info karakter Anda |
| `/q` | Keluar server |

---

## 🛠️ Management

### phpMyAdmin
Buka browser → `http://localhost:8080`
- Login: `root` / password dari `.env`
- Database: `santara_rp`

### Restart Server Tanpa Rebuild
```bash
# Edit santara.pwn → restart container (auto-compile)
docker compose restart omp-server
```

### Rebuild Image (setelah edit Dockerfile/plugins)
```bash
docker compose up -d --build omp-server
```

### Stop Semua
```bash
docker compose down

# Hapus juga data volume (HATI-HATI: data DB hilang!)
docker compose down -v
```

---

## 📁 Struktur File

```
SantaraBaru/
├── docker-compose.yml       ← Orkestrasi semua service
├── Dockerfile               ← Image open.mp server
├── .env                     ← Konfigurasi (jangan di-commit!)
├── .env.example             ← Template environment
├── scripts/
│   └── entrypoint.sh        ← Startup script container
├── server/
│   ├── gamemodes/
│   │   └── santara.pwn      ← Gamemode utama (edit di sini!)
│   └── scriptfiles/
│       └── db.ini           ← Konfigurasi koneksi MySQL
├── sql/
│   └── init.sql             ← Schema database
└── README.md
```

---

## 🔧 Troubleshooting

**Server tidak bisa start?**
```bash
docker compose logs omp-server
# Cek error kompilasi atau koneksi MySQL
```

**MySQL tidak bisa konek?**
```bash
docker compose logs mysql
# Pastikan MYSQL_PASSWORD di .env sama antara mysql dan omp-server
```

**playit.gg tidak konek?**
```bash
docker compose logs playit
# Pastikan PLAYIT_SECRET sudah diisi dengan benar
```

**Pemain Android tidak bisa voice?**
- Pastikan menggunakan **Alyn SA-MP Mobile** launcher
- Grant izin Microphone di Settings HP
- Pastikan server dalam kondisi online (cek `/voice` in-game)

---

## 📞 Support

Untuk bantuan lebih lanjut, hubungi admin di Discord server SantaraBaru Roleplay.
