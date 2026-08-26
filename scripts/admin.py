#!/usr/bin/env python3
"""
SantaraBaru Roleplay — Terminal Administrator CLI Tool
Kelola server, pemain, akun parent, uang, dan kendaraan langsung dari Terminal Laptop.
"""

import sys
import os
import sqlite3
import socket
import struct

DB_PATH = os.path.join(os.path.dirname(os.path.abspath(__file__)), "server", "scriptfiles", "santara_rp.db")
RCON_PASS = "SantaraRcon@2024"
RCON_PORT = 50034

def send_rcon_live(cmd, ip="127.0.0.1", port=RCON_PORT, password=RCON_PASS):
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.settimeout(0.6)
        ip_parts = [int(p) for p in ip.split('.')]
        packet = b'SAMP' + struct.pack('BBBB', *ip_parts) + struct.pack('<H', port) + b'x'
        pw_bytes = password.encode('latin1')
        packet += struct.pack('<H', len(pw_bytes)) + pw_bytes
        cmd_bytes = cmd.encode('latin1')
        packet += struct.pack('<H', len(cmd_bytes)) + cmd_bytes
        sock.sendto(packet, (ip, port))
        sock.close()
    except Exception:
        pass

# Terminal Color Codes
CYAN = "\033[96m"
GREEN = "\033[92m"
YELLOW = "\033[93m"
RED = "\033[91m"
BOLD = "\033[1m"
GREY = "\033[90m"
RESET = "\033[0m"

def get_db():
    if not os.path.exists(DB_PATH):
        print(f"{RED}[Error] Database tidak ditemukan di: {DB_PATH}{RESET}")
        sys.exit(1)
    conn = sqlite3.connect(DB_PATH)
    conn.row_factory = sqlite3.Row
    return conn

def format_rupiah(amount):
    try:
        val = int(amount)
        return f"Rp {val:,.0f}".replace(",", ".")
    except:
        return str(amount)

def show_help():
    print(f"""
{BOLD}{CYAN}================================================================={RESET}
{BOLD}{YELLOW}  SantaraBaru Roleplay — Terminal Administrator CLI Tool{RESET}
{BOLD}{CYAN}================================================================={RESET}

{BOLD}PENGGUNAAN:{RESET}
  ./admin.py <perintah> [argumen...]

{BOLD}PERINTAH YANG TERSEDIA:{RESET}
  {GREEN}setadmin{RESET} <username/id> <level 0-2>   {GREY}Ubah level admin akun parent (0=Player, 1=Admin, 2=Owner){RESET}
  {GREEN}givemoney{RESET} <char_name/id> <jumlah>    {GREY}Tambah/kurang saldo uang karakter pemain{RESET}
  {GREEN}setmoney{RESET} <char_name/id> <jumlah>     {GREY}Set saldo uang karakter pemain{RESET}
  {GREEN}delveh{RESET} <vehicle_db_id>               {GREY}Hapus kendaraan pribadi dari kepemilikan pemain & DB{RESET}
  {GREEN}vehlist{RESET} [char_name/id]               {GREY}Lihat daftar semua kendaraan & DB ID milik karakter{RESET}
  {GREEN}accounts{RESET}                             {GREY}Tampilkan semua akun parent & status admin{RESET}
  {GREEN}characters{RESET} [username/id]             {GREY}Tampilkan semua karakter RP yang terdaftar{RESET}
  {GREEN}unban{RESET} <username>                      {GREY}Buka ban akun pemain{RESET}
  {GREEN}ban{RESET} <username> [alasan]              {GREY}Ban akun pemain{RESET}
  {GREEN}stats{RESET}                                {GREY}Ringkasan statistik server (Akun, Karakter, Mobil, Ekonomi){RESET}

{BOLD}CONTOH:{RESET}
  ./admin.py setadmin Fathi_Akbar 2
  ./admin.py givemoney "Lucky Luck" 10000000
  ./admin.py delveh 1
  ./admin.py vehlist "Lucky Luck"
  ./admin.py stats
""")

def cmd_stats():
    conn = get_db()
    c = conn.cursor()
    acc_count = c.execute("SELECT COUNT(*) FROM accounts").fetchone()[0]
    admin_count = c.execute("SELECT COUNT(*) FROM accounts WHERE admin_level > 0").fetchone()[0]
    char_count = c.execute("SELECT COUNT(*) FROM characters WHERE is_active = 1").fetchone()[0]
    veh_count = c.execute("SELECT COUNT(*) FROM player_vehicles").fetchone()[0]
    total_cash = c.execute("SELECT SUM(cash) FROM characters WHERE is_active = 1").fetchone()[0] or 0

    print(f"\n{BOLD}{CYAN}=== STATISTIK SERVER SANTARABARU ==={RESET}")
    print(f" • Total Akun Parent      : {BOLD}{acc_count}{RESET} akun ({admin_count} Staff Admin)")
    print(f" • Total Karakter Aktif   : {BOLD}{char_count}{RESET} karakter")
    print(f" • Total Kendaraan Pemain : {BOLD}{veh_count}{RESET} unit")
    print(f" • Total Sirkulasi Uang   : {BOLD}{GREEN}{format_rupiah(total_cash)}{RESET}\n")
    conn.close()

def cmd_accounts():
    conn = get_db()
    c = conn.cursor()
    rows = c.execute("SELECT id, username, admin_level, is_banned, created_at, last_login FROM accounts ORDER BY id ASC").fetchall()
    
    print(f"\n{BOLD}{CYAN}=== DAFTAR AKUN PARENT (ACCOUNTS) ==={RESET}")
    print(f"{BOLD}{'ID':<4} {'Username':<20} {'Admin Level':<15} {'Status':<10} {'Terdaftar':<20}{RESET}")
    print("-" * 75)
    for r in rows:
        lvl = r["admin_level"]
        if lvl == 2:
            lvl_str = f"{YELLOW}Level 2 (Owner){RESET}"
        elif lvl == 1:
            lvl_str = f"{GREEN}Level 1 (Admin){RESET}"
        else:
            lvl_str = f"{GREY}Player{RESET}"
        
        status = f"{RED}BANNED{RESET}" if r["is_banned"] else f"{GREEN}Active{RESET}"
        print(f"{r['id']:<4} {r['username']:<20} {lvl_str:<24} {status:<18} {str(r['created_at'])[:19]:<20}")
    print("-" * 75 + "\n")
    conn.close()

def cmd_characters(account_identifier=None):
    conn = get_db()
    c = conn.cursor()
    
    if account_identifier:
        # Check if ID or Username
        if account_identifier.isdigit():
            rows = c.execute("SELECT c.*, a.username FROM characters c JOIN accounts a ON c.account_id = a.id WHERE a.id = ? ORDER BY c.id ASC", (int(account_identifier),)).fetchall()
        else:
            rows = c.execute("SELECT c.*, a.username FROM characters c JOIN accounts a ON c.account_id = a.id WHERE a.username LIKE ? ORDER BY c.id ASC", (f"%{account_identifier}%",)).fetchall()
    else:
        rows = c.execute("SELECT c.*, a.username FROM characters c JOIN accounts a ON c.account_id = a.id ORDER BY c.id ASC").fetchall()

    print(f"\n{BOLD}{CYAN}=== DAFTAR KARAKTER (CHARACTERS) ==={RESET}")
    print(f"{BOLD}{'CID':<4} {'Nama Karakter':<20} {'Parent Account':<18} {'e-KTP':<8} {'Uang Tunai':<18} {'Status':<10}{RESET}")
    print("-" * 85)
    for r in rows:
        ktp = f"{GREEN}Ada{RESET}" if r["has_ktp"] else f"{GREY}Belum{RESET}"
        status = f"{GREEN}Aktif{RESET}" if r["is_active"] else f"{RED}Nonaktif{RESET}"
        print(f"{r['id']:<4} {r['char_name']:<20} {r['username']:<18} {ktp:<15} {format_rupiah(r['cash']):<18} {status:<18}")
    print("-" * 85 + "\n")
    conn.close()

def cmd_setadmin(account_identifier, level_str):
    try:
        level = int(level_str)
        if level < 0 or level > 2:
            raise ValueError()
    except:
        print(f"{RED}[Error] Level admin harus berupa angka 0, 1, atau 2!{RESET}")
        return

    conn = get_db()
    c = conn.cursor()
    
    if account_identifier.isdigit():
        row = c.execute("SELECT id, username FROM accounts WHERE id = ?", (int(account_identifier),)).fetchone()
    else:
        row = c.execute("SELECT id, username FROM accounts WHERE username = ?", (account_identifier,)).fetchone()

    if not row:
        print(f"{RED}[Error] Akun '{account_identifier}' tidak ditemukan di database!{RESET}")
        conn.close()
        return

    c.execute("UPDATE accounts SET admin_level = ? WHERE id = ?", (level, row["id"]))
    conn.commit()

    # Trigger live update ke open.mp server jika sedang berjalan
    send_rcon_live(f"setadmin {row['username']} {level}")

    lvl_title = "Owner / SuperAdmin" if level == 2 else ("Administrator" if level == 1 else "Regular Player")
    print(f"{GREEN}[✓] Sukses mengupdate akun '{row['username']}' (Account ID: {row['id']}) menjadi: {BOLD}{lvl_title} (Level {level}){RESET}")
    conn.close()

def cmd_givemoney(char_identifier, amount_str):
    try:
        amount = int(amount_str)
    except:
        print(f"{RED}[Error] Jumlah uang harus berupa angka!{RESET}")
        return

    conn = get_db()
    c = conn.cursor()

    if char_identifier.isdigit():
        row = c.execute("SELECT id, char_name, cash FROM characters WHERE id = ?", (int(char_identifier),)).fetchone()
    else:
        row = c.execute("SELECT id, char_name, cash FROM characters WHERE char_name = ?", (char_identifier,)).fetchone()

    if not row:
        print(f"{RED}[Error] Karakter '{char_identifier}' tidak ditemukan di database!{RESET}")
        conn.close()
        return

    new_cash = max(0, row["cash"] + amount)
    c.execute("UPDATE characters SET cash = ? WHERE id = ?", (new_cash, row["id"]))
    conn.commit()

    # Trigger live update ke open.mp server jika pemain sedang online
    send_rcon_live(f"givemoney {row['char_name']} {amount}")

    print(f"{GREEN}[✓] Sukses menambahkan {format_rupiah(amount)} ke '{row['char_name']}' (Char ID: {row['id']}).{RESET}")
    print(f"    Saldo lama: {format_rupiah(row['cash'])} » {BOLD}Saldo baru: {format_rupiah(new_cash)}{RESET}")
    conn.close()

def cmd_setmoney(char_identifier, amount_str):
    try:
        amount = max(0, int(amount_str))
    except:
        print(f"{RED}[Error] Jumlah uang harus berupa angka positif!{RESET}")
        return

    conn = get_db()
    c = conn.cursor()

    if char_identifier.isdigit():
        row = c.execute("SELECT id, char_name, cash FROM characters WHERE id = ?", (int(char_identifier),)).fetchone()
    else:
        row = c.execute("SELECT id, char_name, cash FROM characters WHERE char_name = ?", (char_identifier,)).fetchone()

    if not row:
        print(f"{RED}[Error] Karakter '{char_identifier}' tidak ditemukan di database!{RESET}")
        conn.close()
        return

    c.execute("UPDATE characters SET cash = ? WHERE id = ?", (amount, row["id"]))
    conn.commit()

    # Trigger live update ke open.mp server jika pemain sedang online
    send_rcon_live(f"setmoney {row['char_name']} {amount}")

    print(f"{GREEN}[✓] Sukses mengatur saldo '{row['char_name']}' (Char ID: {row['id']}) menjadi: {BOLD}{format_rupiah(amount)}{RESET}")
    conn.close()

def cmd_vehlist(char_identifier=None):
    conn = get_db()
    c = conn.cursor()

    if char_identifier:
        if char_identifier.isdigit():
            char_row = c.execute("SELECT id, char_name FROM characters WHERE id = ?", (int(char_identifier),)).fetchone()
        else:
            char_row = c.execute("SELECT id, char_name FROM characters WHERE char_name = ?", (char_identifier,)).fetchone()
        
        if not char_row:
            print(f"{RED}[Error] Karakter '{char_identifier}' tidak ditemukan!{RESET}")
            conn.close()
            return
        
        rows = c.execute("SELECT * FROM player_vehicles WHERE char_id = ? ORDER BY id ASC", (char_row["id"],)).fetchall()
        print(f"\n{BOLD}{CYAN}=== KENDARAAN MILIK: {char_row['char_name']} (Char ID: {char_row['id']}) ==={RESET}")
    else:
        rows = c.execute("SELECT v.*, c.char_name FROM player_vehicles v JOIN characters c ON v.char_id = c.id ORDER BY v.id ASC").fetchall()
        print(f"\n{BOLD}{CYAN}=== DAFTAR SEMUA KENDARAAN PEMAIN ==={RESET}")

    if not rows:
        print(f"{YELLOW}Tidak ada kendaraan terdaftar.{RESET}\n")
        conn.close()
        return

    print(f"{BOLD}{'DB ID':<6} {'Owner':<18} {'Model ID':<10} {'Plat':<12} {'Status':<18} {'Harga Beli':<15}{RESET}")
    print("-" * 85)
    for r in rows:
        owner = r["char_name"] if "char_name" in r.keys() else char_identifier
        v_status = r["status"]
        if v_status == 1:
            st = f"{GREEN}Garasi #{r['garage_id']}{RESET}"
        elif v_status == 0:
            st = f"{YELLOW}Di Luar / Aktif{RESET}"
        else:
            st = f"{RED}Asuransi{RESET}"

        print(f"{r['id']:<6} {owner:<18} {r['model_id']:<10} {r['plate']:<12} {st:<26} {format_rupiah(r['price']):<15}")
    print("-" * 85)
    print(f"{GREY}* Gunakan './admin.py delveh <DB_ID>' untuk menghapus kendaraan.{RESET}\n")
    conn.close()

def cmd_delveh(veh_db_id):
    try:
        vid = int(veh_db_id)
    except:
        print(f"{RED}[Error] Database ID kendaraan harus berupa angka!{RESET}")
        return

    conn = get_db()
    c = conn.cursor()
    row = c.execute("SELECT v.*, c.char_name FROM player_vehicles v JOIN characters c ON v.char_id = c.id WHERE v.id = ?", (vid,)).fetchone()

    if not row:
        print(f"{RED}[Error] Kendaraan dengan Database ID {vid} tidak ditemukan!{RESET}")
        conn.close()
        return

    c.execute("DELETE FROM player_vehicles WHERE id = ?", (vid,))
    conn.commit()

    print(f"{GREEN}[✓] Sukses menghapus permanen kendaraan (DB ID: {vid}, Model: {row['model_id']}, Plat: {row['plate']}) milik '{row['char_name']}'!{RESET}")
    conn.close()

def cmd_unban(username):
    conn = get_db()
    c = conn.cursor()
    row = c.execute("SELECT id, username FROM accounts WHERE username = ?", (username,)).fetchone()
    if not row:
        print(f"{RED}[Error] Akun '{username}' tidak ditemukan!{RESET}")
        conn.close()
        return
    c.execute("UPDATE accounts SET is_banned = 0, ban_reason = '' WHERE id = ?", (row["id"],))
    conn.commit()
    print(f"{GREEN}[✓] Sukses membuka ban akun '{row['username']}'!{RESET}")
    conn.close()

def cmd_ban(username, reason="Admin ban via Terminal CLI"):
    conn = get_db()
    c = conn.cursor()
    row = c.execute("SELECT id, username FROM accounts WHERE username = ?", (username,)).fetchone()
    if not row:
        print(f"{RED}[Error] Akun '{username}' tidak ditemukan!{RESET}")
        conn.close()
        return
    c.execute("UPDATE accounts SET is_banned = 1, ban_reason = ? WHERE id = ?", (reason, row["id"]))
    conn.commit()
    print(f"{RED}[✓] Sukses membanned akun '{row['username']}' (Alasan: {reason})!{RESET}")
    conn.close()

def main():
    if len(sys.argv) < 2:
        show_help()
        return

    cmd = sys.argv[1].lower()

    if cmd in ["help", "--help", "-h", "?"]:
        show_help()
    elif cmd == "stats":
        cmd_stats()
    elif cmd == "accounts":
        cmd_accounts()
    elif cmd == "characters":
        target = sys.argv[2] if len(sys.argv) > 2 else None
        cmd_characters(target)
    elif cmd == "setadmin":
        if len(sys.argv) < 4:
            print(f"{RED}Gunakan: ./admin.py setadmin <username/account_id> <0/1/2>{RESET}")
            return
        cmd_setadmin(sys.argv[2], sys.argv[3])
    elif cmd == "givemoney":
        if len(sys.argv) < 4:
            print(f"{RED}Gunakan: ./admin.py givemoney <char_name/char_id> <jumlah>{RESET}")
            return
        cmd_givemoney(sys.argv[2], sys.argv[3])
    elif cmd == "setmoney":
        if len(sys.argv) < 4:
            print(f"{RED}Gunakan: ./admin.py setmoney <char_name/char_id> <jumlah>{RESET}")
            return
        cmd_setmoney(sys.argv[2], sys.argv[3])
    elif cmd == "vehlist":
        target = sys.argv[2] if len(sys.argv) > 2 else None
        cmd_vehlist(target)
    elif cmd == "delveh":
        if len(sys.argv) < 3:
            print(f"{RED}Gunakan: ./admin.py delveh <vehicle_db_id>{RESET}")
            return
        cmd_delveh(sys.argv[2])
    elif cmd == "unban":
        if len(sys.argv) < 3:
            print(f"{RED}Gunakan: ./admin.py unban <username>{RESET}")
            return
        cmd_unban(sys.argv[2])
    elif cmd == "ban":
        if len(sys.argv) < 3:
            print(f"{RED}Gunakan: ./admin.py ban <username> [alasan]{RESET}")
            return
        reason = " ".join(sys.argv[3:]) if len(sys.argv) > 3 else "Banned via Terminal CLI"
        cmd_ban(sys.argv[2], reason)
    else:
        print(f"{RED}Perintah '{cmd}' tidak dikenali.{RESET}")
        show_help()

if __name__ == "__main__":
    main()
