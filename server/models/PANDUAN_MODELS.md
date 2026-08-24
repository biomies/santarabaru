# 🎨 Panduan Menambahkan Skin & Objek Kustom di SantaraBaru RP

Server **SantaraBaru Roleplay (open.mp)** mendukung fitur **Auto-Download Custom Assets**. Pemain yang masuk ke server akan otomatis mengunduh skin dan bangunan/objek kustom tanpa perlu menginstal mod secara manual di perangkat mereka!

---

## 📁 1. Lokasi Menaruh File Mod
Semua file model 3D (`.dff`) dan tekstur (`.txd`) ditaruh di dalam folder:
```
server/models/
 ├── artconfig.txt          <-- File daftar registrasi model
 ├── polisi_indo.dff        <-- File model 3D
 ├── polisi_indo.txd        <-- File tekstur
 └── ...
```

---

## 📝 2. Mendaftarkan Model di `artconfig.txt`

Buka file `server/models/artconfig.txt`, lalu tambahkan baris model kustom:

### A. Untuk Skin / Karakter Kustom (`AddCharModel`):
```
AddCharModel(baseid, newid, "dffname.dff", "txdname.txd");
```
* **`baseid`**: ID skin GTA SA bawaan untuk kerangka animasi (contoh: `265` untuk polisi, `0` untuk CJ/sipil).
* **`newid`**: ID unik skin baru yang akan dipakai di server (rentang `20000` s/d `30000`).
* **Contoh:**
  ```
  AddCharModel(265, 20001, "polisi_indo.dff", "polisi_indo.txd");
  AddCharModel(0, 20002, "ojol_grab.dff", "ojol_grab.txd");
  ```

### B. Untuk Objek, Aksesoris & Bangunan Kustom (`AddSimpleModel`):
```
AddSimpleModel(virtualworld, baseid, newid, "dffname.dff", "txdname.txd");
```
* **`virtualworld`**: Gunakan `-1` agar bisa dilihat di semua virtual world.
* **`baseid`**: ID objek GTA SA asli sebagai referensi collision (contoh: `19377`).
* **`newid`**: ID objek baru di server (rentang negatif `-1000` s/d `-30000`).
* **Contoh:**
  ```
  AddSimpleModel(-1, 19377, -1000, "indomaret.dff", "indomaret.txd");
  AddSimpleModel(-1, 19377, -1001, "gapura_bali.dff", "gapura_bali.txd");
  ```

---

## 🎮 3. Cara Menggunakannya di Gamemode (`santara.pwn`)
Setelah didaftarkan di `artconfig.txt`:
* **Memberikan Skin ke Pemain:**
  ```pawn
  SetPlayerSkin(playerid, 20001); // Skin Polisi Indo
  ```
* **Membuat Objek di Peta:**
  ```pawn
  CreateObject(-1000, 1481.0, -1771.0, 18.79, 0.0, 0.0, 0.0); // Gedung Indomaret
  ```

---

## 🔄 4. Terapkan Perubahan
Setelah memasukkan file `.dff`, `.txd`, dan mengedit `artconfig.txt`, restart server dengan:
```bash
docker compose restart omp-server
```
Pemain yang login berikutnya akan langsung otomatis mendownload asset tersebut! 🚀
