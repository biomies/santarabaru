# 🎨 Panduan Menambahkan Skin, Objek & Kendaraan Kustom di SantaraBaru RP

Server **SantaraBaru Roleplay (open.mp)** mendukung fitur **Auto-Download Custom Assets**. Pemain yang masuk ke server akan otomatis mengunduh skin, kendaraan kustom, dan bangunan kustom tanpa perlu menginstal mod secara manual di perangkat mereka!

---

## 📁 1. Lokasi Menaruh File Mod
Semua file model 3D (`.dff`) dan tekstur (`.txd`) ditaruh di dalam folder:
```
server/models/
 ├── artconfig.txt          <-- File daftar registrasi model
 ├── copcarsf.dff           <-- File model 3D (Mobil Polisi Kustom)
 ├── copcarsf.txd           <-- File tekstur (Mobil Polisi Kustom)
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
* **`newid`**: ID unik skin baru yang akan dipakai di server (gunakan angka mulai dari `20000` ke atas).
* **Contoh:**
  ```
  AddCharModel(265, 20001, "polisi_indo.dff", "polisi_indo.txd");
  AddCharModel(0, 20002, "ojol_grab.dff", "ojol_grab.txd");
  ```

### B. Untuk Objek, Bangunan & Kendaraan Kustom (`AddSimpleModel`):
```
AddSimpleModel(virtualworld, baseid, newid, "dffname.dff", "txdname.txd");
```
* **`virtualworld`**: Gunakan `-1` agar bisa dilihat di semua virtual world.
* **`baseid`**: ID objek GTA SA asli sebagai referensi collision (contoh: `19377`).
* **`newid`**: ID objek baru di server (contoh: `20100`).
* **Contoh (Kendaraan / Objek):**
  ```
  AddSimpleModel(-1, 19377, 20100, "copcarsf.dff", "copcarsf.txd");
  AddSimpleModel(-1, 19377, 20003, "indomaret.dff", "indomaret.txd");
  ```

---

## 🚗 3. Menghadirkan Kendaraan Kustom Tanpa Replace Mobil Asli
Untuk menghadirkan mobil kustom tanpa mereplace mobil bawaan GTA SA:
1. Daftarkan model sebagai `AddSimpleModel` di `artconfig.txt` (contoh ID `20100`).
2. Di dalam server, gunakan command:
   * **`/copcarsf`** atau **`/veh copcarsf`** : Langsung memunculkan mobil kustom baru ini dengan auto-attach object ID 20100.
   * **`/vehmenu`** : Membuka katalog lengkap semua kendaraan.
   * **`/dv`** : Menghapus kendaraan spawn Anda.

---

## 🔄 4. Terapkan Perubahan
Setelah memasukkan file `.dff`, `.txd`, dan mengedit `artconfig.txt`, restart server dengan:
```bash
docker compose restart omp-server
```
Pemain yang login berikutnya akan langsung otomatis mendownload asset tersebut! 🚀
