#!/usr/bin/env python3
"""
SantaraBaru Roleplay — Database Master Seeder & Manager Tool
Kelola dan import data master Pekerjaan (Jobs), Barang (Items), Mobil Showroom (Dealership), dan Warna ke santara_master.db.
"""

import sys
import os
import sqlite3

def get_db_path():
    possible_paths = [
        os.path.join(os.path.dirname(os.path.abspath(__file__)), "server", "scriptfiles", "santara_master.db"),
        os.path.join(os.path.dirname(os.path.abspath(__file__)), "scriptfiles", "santara_master.db"),
        os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "server", "scriptfiles", "santara_master.db"),
        "/root/SantaraBaru/server/scriptfiles/santara_master.db"
    ]
    for p in possible_paths:
        if os.path.exists(p):
            return p
    return possible_paths[0]

DB_PATH = get_db_path()

# Format Warna Terminal
CYAN = "\033[96m"
GREEN = "\033[92m"
YELLOW = "\033[93m"
RED = "\033[91m"
BOLD = "\033[1m"
RESET = "\033[0m"
GREY = "\033[90m"

# 1. Default 12 Master Items (Burger, Hotdog, Pizza, Air Mineral, Cola, Milkshake, Medis, HP, KTP, SIM)
DEFAULT_ITEMS = [
    (1, "Burger", "Makanan", 40.0, 0.0, 0.0, 0, "FOOD", "eat_burger", 25000),
    (2, "Hotdog", "Makanan", 35.0, 0.0, 0.0, 0, "FOOD", "eat_burger", 20000),
    (3, "Pizza", "Makanan", 50.0, 0.0, 0.0, 0, "FOOD", "eat_pizza", 40000),
    (4, "Air Mineral", "Minuman", 0.0, 35.0, 0.0, 0, "DRINK_cw", "drink_sprank", 5000),
    (5, "Cola", "Minuman", 0.0, 40.0, 0.0, 0, "DRINK_cw", "drink_sprank", 10000),
    (6, "Milkshake", "Minuman", 10.0, 45.0, 0.0, 0, "DRINK_cw", "drink_sprank", 20000),
    (7, "Bandage", "Medis / Obat", 0.0, 0.0, 25.0, 0, "MISC", "bitchslap", 25000),
    (8, "Medkit", "Medis / Obat", 0.0, 0.0, 60.0, 0, "MISC", "bitchslap", 60000),
    (9, "First Aid Kit", "Medis / Obat", 0.0, 0.0, 100.0, 1, "MISC", "bitchslap", 120000),
    (10, "Ponsel", "Elektronik", 0.0, 0.0, 0.0, 0, "", "", 150000),
    (11, "KTP (Kartu Identitas)", "Dokumen", 0.0, 0.0, 0.0, 0, "", "", 50000),
    (12, "Surat Izin Mengemudi (SIM A)", "Dokumen", 0.0, 0.0, 0.0, 0, "", "", 50000),
    (13, "Surat Izin Mengemudi (SIM B)", "Dokumen", 0.0, 0.0, 0.0, 0, "", "", 100000),
    (14, "Surat Izin Mengemudi (SIM C)", "Dokumen", 0.0, 0.0, 0.0, 0, "", "", 25000),
    (15, "Bijih Besi (Iron Ore)", "Bahan Mentah", 0.0, 0.0, 0.0, 0, "", "", 15000),
    (16, "Besi Bekas (Scrap Metal)", "Bahan Mentah", 0.0, 0.0, 0.0, 0, "", "", 10000),
    (17, "Belerang (Sulfur)", "Bahan Mentah", 0.0, 0.0, 0.0, 0, "", "", 20000),
    (18, "Bubuk Arang (Charcoal)", "Bahan Mentah", 0.0, 0.0, 0.0, 0, "", "", 8000),
    (19, "Bijih Tembaga (Copper Ore)", "Bahan Mentah", 0.0, 0.0, 0.0, 0, "", "", 18000),
    (20, "Batang Baja (Steel Bar)", "Bahan Olahan", 0.0, 0.0, 0.0, 0, "", "", 55000),
    (21, "Lempeng Kuningan (Brass Plate)", "Bahan Olahan", 0.0, 0.0, 0.0, 0, "", "", 65000),
    (22, "Bubuk Mesiu (Gunpowder)", "Bahan Olahan", 0.0, 0.0, 0.0, 0, "", "", 50000),
    (23, "Laras & Slide Senjata", "Komponen", 0.0, 0.0, 0.0, 0, "", "", 180000),
    (24, "Pelatuk & Mekanikal Senjata", "Komponen", 0.0, 0.0, 0.0, 0, "", "", 140000),
    (25, "Magasin Kosong", "Komponen", 0.0, 0.0, 0.0, 0, "", "", 80000),
    (26, "Peluru 9mm", "Amunisi", 0.0, 0.0, 0.0, 0, "", "", 2500),
    (27, "Peluru .50 AE", "Amunisi", 0.0, 0.0, 0.0, 0, "", "", 5700),
    (28, "Peluru 12 Gauge", "Amunisi", 0.0, 0.0, 0.0, 0, "", "", 7000),
    (29, "Peluru 7.62mm", "Amunisi", 0.0, 0.0, 0.0, 0, "", "", 4200),
    (30, "Rompi Kevlar (Body Armor)", "Perlengkapan", 0.0, 0.0, 0.0, 0, "", "", 450000),
    (31, "Beliung Tambang (Pickaxe)", "Peralatan", 0.0, 0.0, 0.0, 0, "", "", 75000),
    (32, "Kotak Perkakas (Toolbox)", "Peralatan", 0.0, 0.0, 0.0, 0, "", "", 120000),
    (33, "Pistol 9mm (Colt 45)", "Senjata", 0.0, 0.0, 0.0, 0, "", "", 500000),
    (34, "Desert Eagle (.50 AE)", "Senjata", 0.0, 0.0, 0.0, 0, "", "", 850000),
    (35, "Shotgun (Pump-Action)", "Senjata", 0.0, 0.0, 0.0, 0, "", "", 1200000),
    (36, "AK-47 Assault Rifle", "Senjata", 0.0, 0.0, 0.0, 0, "", "", 2000000)
]

# 2. Default Master Jobs
DEFAULT_JOBS = [
    (0, "Pengangguran", 0),
    (1, "Penambang", 0)
]

# 3. Default Dealership Vehicles (105 Vehicles)
DEFAULT_DEALER_VEHICLES = [
    # Sport (0)
    (411, "Infernus", "Supercar V12 Top", 0, 750000000, 240, 2),
    (451, "Turismo", "Supercar Italia", 0, 680000000, 235, 2),
    (541, "Bullet", "Supercar Balap", 0, 580000000, 230, 2),
    (415, "Cheetah", "Supercar Klasik", 0, 520000000, 225, 2),
    (429, "Banshee", "Roadster Sport V10", 0, 450000000, 220, 2),
    (506, "Super GT", "Grand Tourer V8", 0, 480000000, 225, 2),
    (477, "ZR-350", "Rotary Sport Coupe", 0, 260000000, 210, 2),
    (480, "Comet", "Convertible Sport", 0, 380000000, 215, 2),
    (402, "Buffalo", "Modern Muscle V8", 0, 240000000, 205, 2),
    (602, "Alpha", "Luxury Sport Coupe", 0, 290000000, 210, 2),
    (603, "Phoenix", "Classic Muscle V8", 0, 230000000, 200, 2),
    (587, "Euros", "Touring Sport Coupe", 0, 220000000, 200, 2),
    (560, "Sultan", "Sedan Sport 4-Pintu", 0, 320000000, 210, 4),
    (562, "Elegy", "Drift King Tuner", 0, 290000000, 205, 2),
    (559, "Jester", "Tuner Sport Coupe", 0, 275000000, 200, 2),
    (565, "Flash", "Hatchback Sport", 0, 210000000, 195, 2),
    (558, "Uranus", "Street Tuner Coupe", 0, 200000000, 190, 2),
    (561, "Stratum", "Sport Station Wagon", 0, 185000000, 185, 4),
    (494, "Hotring Racer", "NASCAR Track Racer", 0, 600000000, 245, 2),
    (502, "Hotring Racer A", "NASCAR Track Racer A", 0, 600000000, 245, 2),
    (503, "Hotring Racer B", "NASCAR Track Racer B", 0, 600000000, 245, 2),
    (555, "Windsor", "Luxury Convertible", 0, 310000000, 190, 2),
    (589, "Club", "Compact Sport", 0, 160000000, 185, 2),
    (434, "Hotknife", "Custom Hot Rod", 0, 420000000, 200, 2),

    # Sedan & Klasik (1)
    (426, "Premier", "Sedan Harian Tangguh", 1, 95000000, 190, 4),
    (405, "Sentinel", "Sedan Eksekutif Mewah", 1, 140000000, 190, 4),
    (421, "Washington", "Sedan Pejabat Berkelas", 1, 165000000, 185, 4),
    (445, "Admiral", "Sedan Klasik Eropa", 1, 110000000, 180, 4),
    (507, "Elegant", "Sedan Nyaman Elegan", 1, 135000000, 185, 4),
    (551, "Merit", "Sedan Menengah Modern", 1, 105000000, 180, 4),
    (550, "Sunrise", "Sedan Keluarga Irit", 1, 98000000, 175, 4),
    (580, "Stafford", "Vintage Royal Luxury", 1, 340000000, 175, 4),
    (585, "Emperor", "Sedan Klasik Nyaman", 1, 88000000, 170, 4),
    (540, "Vincent", "Sedan Kompak Harian", 1, 78000000, 165, 4),
    (546, "Intruder", "Sedan 4-Pintu Sporty", 1, 82000000, 170, 4),
    (547, "Primo", "Sedan Standar Murah", 1, 65000000, 160, 4),
    (516, "Nebula", "Sedan Keluarga Santai", 1, 72000000, 165, 4),
    (529, "Willard", "Sedan Komuter Kota", 1, 68000000, 160, 4),
    (492, "Greenwood", "Sedan Retro Klasik", 1, 75000000, 165, 4),
    (466, "Glendale", "Sedan Vintage 1960s", 1, 55000000, 155, 4),
    (467, "Oceanic", "Sedan Klasik Elegan", 1, 62000000, 160, 4),
    (474, "Hermes", "Lead Sled Custom", 1, 120000000, 160, 2),
    (567, "Savanna", "Lowrider 4-Pintu", 1, 175000000, 185, 4),
    (566, "Tahoma", "Lowrider Sedan Mewah", 1, 85000000, 175, 4),
    (536, "Blade", "Lowrider Coupe V8", 1, 160000000, 190, 2),
    (534, "Remington", "Luxury Lowrider Coupe", 1, 195000000, 185, 2),
    (535, "Slamvan", "Custom Lowrider Truck", 1, 180000000, 180, 2),
    (412, "Voodoo", "Lowrider Klasik V8", 1, 130000000, 180, 2),
    (575, "Broadway", "Vintage Convertible", 1, 150000000, 170, 2),
    (576, "Tornado", "Classic Lowrider 50s", 1, 115000000, 170, 2),
    (545, "Hustler", "1930s Gangster Coupe", 1, 210000000, 165, 2),
    (527, "Cadrona", "Coupe 2-Pintu Murah", 1, 58000000, 165, 2),
    (526, "Fortune", "Coupe Nyaman 2-Pintu", 1, 64000000, 170, 2),
    (517, "Majestic", "Sedan Coupe Klasik", 1, 69000000, 170, 2),
    (518, "Buccaneer", "Muscle Coupe Klasik", 1, 85000000, 175, 2),
    (419, "Esperanto", "Sedan Retro Mewah", 1, 76000000, 165, 2),
    (533, "Feltzer", "Roadster Klasik Elegan", 1, 145000000, 180, 2),
    (542, "Clover", "Muscle Car Murah", 1, 52000000, 175, 2),
    (549, "Tampa", "Classic Muscle Coupe", 1, 70000000, 170, 2),
    (491, "Virgo", "Coupe Retro Nyaman", 1, 66000000, 165, 2),
    (475, "Sabre", "Street Muscle V8", 1, 110000000, 185, 2),
    (439, "Stallion", "Convertible Muscle", 1, 125000000, 185, 2),
    (436, "Previon", "Coupe Irit Praktis", 1, 48000000, 160, 2),
    (401, "Bravura", "Coupe Pemula Murah", 1, 42000000, 155, 2),
    (410, "Manana", "Hatchback Klasik", 1, 38000000, 145, 2),
    (496, "Blista Compact", "Hatchback Lincah Irit", 1, 70000000, 175, 2),
    (404, "Perennial", "Station Wagon Murah", 1, 45000000, 145, 4),
    (479, "Regina", "Station Wagon Klasik", 1, 56000000, 155, 4),
    (458, "Solair", "Station Wagon Nyaman", 1, 74000000, 165, 4),
    (418, "Moonbeam", "Minivan Keluarga Luas", 1, 60000000, 145, 4),

    # SUV & Off-Road (2)
    (579, "Huntley", "Luxury Premium SUV", 2, 350000000, 180, 4),
    (400, "Landstalker", "SUV Keluarga Tangguh", 2, 180000000, 170, 4),
    (489, "Rancher", "SUV Off-Road 4x4", 2, 140000000, 160, 2),
    (505, "Rancher Lure", "Special Off-Road 4x4", 2, 160000000, 165, 2),
    (500, "Mesa", "Open-Top Jeep 4x4", 2, 125000000, 155, 2),
    (422, "Bobcat", "Pick-up Klasik", 2, 65000000, 155, 2),
    (478, "Walton", "Vintage Farm Pick-up", 2, 45000000, 140, 2),
    (543, "Sadler", "Pekerja Keras Tangguh", 2, 48000000, 145, 2),
    (554, "Yosemite", "Heavy-Duty Pick-up", 2, 110000000, 165, 2),
    (495, "Sandking", "Dakar Rally Raid 4x4", 2, 390000000, 185, 2),
    (568, "Bandito", "Desert Buggy Rail", 2, 135000000, 170, 1),
    (424, "BF Injection", "Beach Dune Buggy", 2, 90000000, 160, 2),
    (571, "Kart", "Mini Gokart Balap", 2, 35000000, 120, 1),
    (572, "Mower", "Traktor Rumput Lucu", 2, 18000000, 80, 1),
    (483, "Camper", "Hippie Camper Van", 2, 115000000, 140, 3),
    (508, "Journey", "Motorhome Keluarga", 2, 160000000, 130, 2),
    (482, "Burrito", "Van Kargo Modern", 2, 95000000, 165, 4),
    (413, "Pony", "Van Pekerja Serbaguna", 2, 70000000, 150, 4),
    (440, "Rumpo", "Van Komersil Luas", 2, 80000000, 155, 4),
    (459, "Berkleys RC Van", "Van Ekspedisi Kurir", 2, 85000000, 155, 4),
    (499, "Benson", "Truk Box Logistik", 2, 130000000, 135, 2),
    (609, "Boxville", "Truk Box Paket", 2, 120000000, 130, 2),
    (414, "Mule", "Truk Distribusi Usaha", 2, 105000000, 125, 2),

    # Sepeda Motor & Skuter (3)
    (522, "NRG-500", "Superbike Balap 500cc", 3, 380000000, 220, 2),
    (521, "FCR-900", "Naked Sport 900cc", 3, 195000000, 195, 2),
    (461, "PCJ-600", "Sport Street 600cc", 3, 130000000, 185, 2),
    (463, "Freeway", "Cruiser Touring V-Twin", 3, 110000000, 175, 2),
    (586, "Wayfarer", "Touring Klasik Amerika", 3, 95000000, 170, 2),
    (468, "Sanchez", "Dirt Trail Enduro", 3, 75000000, 165, 2),
    (471, "Quad", "All-Terrain Quad 4-Roda", 3, 55000000, 140, 2),
    (462, "Faggio", "Skuter Matic Irit", 3, 18000000, 110, 2),
    (448, "Pizzaboy", "Skuter Delivery Cepat", 3, 22000000, 115, 1),
    (510, "Mountain Bike", "Sepeda Gunung Suspensi", 3, 8500000, 65, 1),
    (481, "BMX", "Sepeda Freestyle BMX", 3, 6500000, 60, 1),
    (509, "Bike", "Sepeda Santai Kota", 3, 4500000, 50, 1)
]

# 4. Default Dealership Colors (20 Colors)
DEFAULT_DEALER_COLORS = [
    (1, "Pure White"),
    (0, "Jet Black"),
    (3, "Crimson Red"),
    (6, "Sunburst Yellow"),
    (79, "Sapphire Blue"),
    (86, "Racing Green"),
    (64, "Tangerine Orange"),
    (148, "Royal Purple"),
    (25, "Silver Chrome"),
    (134, "Gunmetal Grey"),
    (151, "Arctic Aqua"),
    (139, "Rose Gold"),
    (130, "Platinum Silver"),
    (75, "Navy Blue"),
    (141, "Bordeaux Maroon"),
    (144, "Dark Olive"),
    (138, "Champagne Gold"),
    (129, "Steel Charcoal"),
    (158, "Neon Fuchsia"),
    (135, "Mocha Bronze")
]

def format_rupiah(amount):
    try:
        return f"Rp {int(amount):,}".replace(",", ".")
    except:
        return str(amount)

def init_tables(conn):
    c = conn.cursor()
    c.execute("""
    CREATE TABLE IF NOT EXISTS jobs (
        id INTEGER PRIMARY KEY,
        name TEXT NOT NULL,
        salary INTEGER DEFAULT 0,
        created_at DATETIME DEFAULT CURRENT_TIMESTAMP
    );
    """)
    c.execute("""
    CREATE TABLE IF NOT EXISTS items (
        id INTEGER PRIMARY KEY,
        name TEXT NOT NULL,
        category TEXT NOT NULL,
        hunger REAL DEFAULT 0.0,
        thirst REAL DEFAULT 0.0,
        health REAL DEFAULT 0.0,
        is_full_heal INTEGER DEFAULT 0,
        anim_lib TEXT DEFAULT '',
        anim_name TEXT DEFAULT '',
        price INTEGER DEFAULT 0,
        created_at DATETIME DEFAULT CURRENT_TIMESTAMP
    );
    """)
    c.execute("""
    CREATE TABLE IF NOT EXISTS dealership_vehicles (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        model_id INTEGER NOT NULL,
        name TEXT NOT NULL,
        description TEXT NOT NULL,
        category INTEGER NOT NULL,
        price INTEGER NOT NULL,
        top_speed INTEGER NOT NULL,
        seats INTEGER NOT NULL,
        created_at DATETIME DEFAULT CURRENT_TIMESTAMP
    );
    """)
    c.execute("""
    CREATE TABLE IF NOT EXISTS dealership_colors (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        color_id INTEGER NOT NULL,
        name TEXT NOT NULL,
        created_at DATETIME DEFAULT CURRENT_TIMESTAMP
    );
    """)
    conn.commit()

def seed_all():
    conn = sqlite3.connect(DB_PATH)
    init_tables(conn)
    c = conn.cursor()

    # Seed Jobs
    for j in DEFAULT_JOBS:
        c.execute("INSERT OR REPLACE INTO jobs (id, name, salary) VALUES (?, ?, ?)", j)
    
    # Seed Items
    for it in DEFAULT_ITEMS:
        c.execute("""
        INSERT OR REPLACE INTO items (id, name, category, hunger, thirst, health, is_full_heal, anim_lib, anim_name, price)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
        """, it)

    # Seed Dealership Vehicles
    c.execute("DELETE FROM dealership_vehicles;")
    for v in DEFAULT_DEALER_VEHICLES:
        c.execute("""
        INSERT INTO dealership_vehicles (model_id, name, description, category, price, top_speed, seats)
        VALUES (?, ?, ?, ?, ?, ?, ?)
        """, v)

    # Seed Dealership Colors
    c.execute("DELETE FROM dealership_colors;")
    for col in DEFAULT_DEALER_COLORS:
        c.execute("INSERT INTO dealership_colors (color_id, name) VALUES (?, ?)", col)

    conn.commit()
    conn.close()
    print(f"\n{BOLD}{GREEN}[✓] Sukses mengimpor seluruh Master Data ke santara_master.db!{RESET}")
    print(f"  • {len(DEFAULT_JOBS)} Pekerjaan (Jobs)")
    print(f"  • {len(DEFAULT_ITEMS)} Barang (Items)")
    print(f"  • {len(DEFAULT_DEALER_VEHICLES)} Mobil/Motor Showroom (Dealership)")
    print(f"  • {len(DEFAULT_DEALER_COLORS)} Pilihan Warna Cat (Colors)")
    print(f"{GREY}Lokasi DB: {DB_PATH}{RESET}\n")

def list_items():
    conn = sqlite3.connect(DB_PATH)
    init_tables(conn)
    c = conn.cursor()
    rows = c.execute("SELECT id, name, category, hunger, thirst, health, price FROM items ORDER BY id ASC").fetchall()
    conn.close()

    print(f"\n{BOLD}{CYAN}=== DAFTAR MASTER BARANG (ITEMS) DI DATABASE ==={RESET}")
    print(f"{BOLD}{'ID':<4} {'Nama Barang':<24} {'Kategori':<16} {'Lapar':<8} {'Haus':<8} {'HP':<8} {'Harga Jual':<15}{RESET}")
    print("-" * 88)
    for r in rows:
        hunger_str = f"+{r[3]:.0f}%" if r[3] > 0 else "-"
        thirst_str = f"+{r[4]:.0f}%" if r[4] > 0 else "-"
        health_str = f"+{r[5]:.0f} HP" if r[5] > 0 else "-"
        price_str = format_rupiah(r[6])
        print(f"{r[0]:<4} {r[1]:<24} {r[2]:<16} {hunger_str:<8} {thirst_str:<8} {health_str:<8} {price_str:<15}")
    print("-" * 88)
    print(f"Total: {len(rows)} barang terdaftar di database.\n")

def list_jobs():
    conn = sqlite3.connect(DB_PATH)
    init_tables(conn)
    c = conn.cursor()
    rows = c.execute("SELECT id, name, salary FROM jobs ORDER BY id ASC").fetchall()
    conn.close()

    print(f"\n{BOLD}{CYAN}=== DAFTAR MASTER PEKERJAAN (JOBS) DI DATABASE ==={RESET}")
    print(f"{BOLD}{'ID':<4} {'Nama Pekerjaan':<28} {'Gaji / Paycheck':<18}{RESET}")
    print("-" * 52)
    for r in rows:
        print(f"{r[0]:<4} {r[1]:<28} {format_rupiah(r[2]):<18}")
    print("-" * 52)
    print(f"Total: {len(rows)} pekerjaan terdaftar di database.\n")

def list_vehicles(cat_filter=None):
    conn = sqlite3.connect(DB_PATH)
    init_tables(conn)
    c = conn.cursor()
    cat_names = {0: "Mobil Sport", 1: "Sedan & Klasik", 2: "SUV & Off-Road", 3: "Sepeda Motor & Skuter"}
    
    if cat_filter is not None and str(cat_filter).isdigit():
        rows = c.execute("SELECT id, model_id, name, description, category, price, top_speed, seats FROM dealership_vehicles WHERE category = ? ORDER BY category, price DESC", (int(cat_filter),)).fetchall()
    else:
        rows = c.execute("SELECT id, model_id, name, description, category, price, top_speed, seats FROM dealership_vehicles ORDER BY category, price DESC").fetchall()
    conn.close()

    print(f"\n{BOLD}{CYAN}=== DAFTAR KENDARAAN DEALERSHIP (SHOWROOM) DI DATABASE ==={RESET}")
    print(f"{BOLD}{'ID':<4} {'Model':<6} {'Nama Kendaraan':<20} {'Kategori':<16} {'Top Speed':<10} {'Kursi':<6} {'Harga OTR':<18}{RESET}")
    print("-" * 86)
    for r in rows:
        c_name = cat_names.get(r[4], "Lainnya")
        spd = f"{r[6]} km/h"
        seat = f"{r[7]} P"
        print(f"{r[0]:<4} {r[1]:<6} {r[2]:<20} {c_name:<16} {spd:<10} {seat:<6} {format_rupiah(r[5]):<18}")
    print("-" * 86)
    print(f"Total: {len(rows)} kendaraan showroom terdaftar di database.\n")

def list_colors():
    conn = sqlite3.connect(DB_PATH)
    init_tables(conn)
    c = conn.cursor()
    rows = c.execute("SELECT id, color_id, name FROM dealership_colors ORDER BY id ASC").fetchall()
    conn.close()

    print(f"\n{BOLD}{CYAN}=== DAFTAR PILIHAN WARNA SHOWROOM (DEALERSHIP COLORS) ==={RESET}")
    print(f"{BOLD}{'ID':<4} {'SA-MP Color ID':<16} {'Nama Warna Cat':<24}{RESET}")
    print("-" * 46)
    for r in rows:
        print(f"{r[0]:<4} {r[1]:<16} {r[2]:<24}")
    print("-" * 46)
    print(f"Total: {len(rows)} warna showroom terdaftar di database.\n")

def set_veh_price(model_or_name, new_price):
    conn = sqlite3.connect(DB_PATH)
    init_tables(conn)
    c = conn.cursor()
    if str(model_or_name).isdigit():
        c.execute("UPDATE dealership_vehicles SET price = ? WHERE model_id = ? OR id = ?", (int(new_price), int(model_or_name), int(model_or_name)))
    else:
        c.execute("UPDATE dealership_vehicles SET price = ? WHERE name LIKE ?", (int(new_price), f"%{model_or_name}%"))
    conn.commit()
    conn.close()
    print(f"{GREEN}[✓] Berhasil mengubah harga kendaraan '{model_or_name}' menjadi: {BOLD}{format_rupiah(new_price)}{RESET}")

def get_players_db_path():
    possible_paths = [
        os.path.join(os.path.dirname(os.path.abspath(__file__)), "server", "scriptfiles", "santara_players.db"),
        os.path.join(os.path.dirname(os.path.abspath(__file__)), "scriptfiles", "santara_players.db"),
        os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "server", "scriptfiles", "santara_players.db"),
        "/root/SantaraBaru/server/scriptfiles/santara_players.db"
    ]
    for p in possible_paths:
        if os.path.exists(p):
            return p
    return possible_paths[0]

def wipe_inventory():
    p_path = get_players_db_path()
    if not os.path.exists(p_path):
        print(f"{RED}[Error] Database santara_players.db tidak ditemukan di: {p_path}{RESET}")
        return
    conn = sqlite3.connect(p_path)
    cur = conn.cursor()
    cur.execute("DELETE FROM inventory;")
    cur.execute("DELETE FROM vehicle_trunk;")
    conn.commit()
    conn.close()
    print(f"{GREEN}[✓] Sukses mengosongkan seluruh isi inventory pemain dan vehicle_trunk di {p_path}.{RESET}")

def show_help():
    print(f"""
{BOLD}{CYAN}SantaraBaru — Database Master Seeder & Manager Tool{RESET}
{GREY}Kelola data master Pekerjaan, Barang, Mobil Showroom, dan Warna di santara_master.db.{RESET}

{BOLD}PENGGUNAAN:{RESET}
  {GREEN}python3 seeder.py seed{RESET}                             Import seluruh master data (Jobs, Items, Mobil, Warna)
  {GREEN}python3 seeder.py vehicles [optional: kategori 0-3]{RESET} Lihat daftar mobil & harga OTR
  {GREEN}python3 seeder.py colors{RESET}                           Lihat pilihan warna cat showroom
  {GREEN}python3 seeder.py items{RESET}                            Lihat daftar barang & harga
  {GREEN}python3 seeder.py jobs{RESET}                             Lihat daftar pekerjaan & gaji
  {GREEN}python3 seeder.py set-price [model/nama] [harga_baru]{RESET} Ubah harga mobil di Showroom
  {GREEN}python3 seeder.py clear-inv{RESET}                        Bersihkan seluruh inventory pemain & bagasi mobil

{BOLD}CONTOH:{RESET}
  python3 seeder.py vehicles 0              (Lihat hanya mobil sport)
  python3 seeder.py set-price Infernus 800000000
  python3 seeder.py clear-inv               (Wipe semua inventory & bagasi)
    """)

def main():
    if len(sys.argv) < 2:
        show_help()
        return

    cmd = sys.argv[1].lower()

    if cmd in ["seed", "import", "init"]:
        seed_all()
    elif cmd in ["vehicles", "veh", "cars", "list-vehicles"]:
        cat = sys.argv[2] if len(sys.argv) > 2 else None
        list_vehicles(cat)
    elif cmd in ["colors", "color", "list-colors"]:
        list_colors()
    elif cmd in ["items", "item", "list-items"]:
        list_items()
    elif cmd in ["jobs", "job", "list-jobs"]:
        list_jobs()
    elif cmd in ["clear-inv", "clear-trunks", "wipe-items", "wipe-inventory", "clear-inventory"]:
        wipe_inventory()
    elif cmd in ["set-price", "setprice", "setvehprice"]:
        if len(sys.argv) < 4:
            print(f"{RED}[Error] Format: python3 seeder.py set-price [model/nama] [harga_baru]{RESET}")
            return
        set_veh_price(sys.argv[2], sys.argv[3])
    else:
        show_help()

if __name__ == "__main__":
    main()
