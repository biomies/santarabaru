#!/bin/bash
set -e

# ============================================================
# SantaraBaru Roleplay — Entrypoint Script
# open.mp Native Engine + SAMPVOICE + sscanf2
# ============================================================

CYAN='\033[0;36m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "${CYAN}"
echo "  ███████╗ █████╗ ███╗   ██╗████████╗ █████╗ ██████╗  █████╗ "
echo "  ██╔════╝██╔══██╗████╗  ██║╚══██╔══╝██╔══██╗██╔══██╗██╔══██╗"
echo "  ███████╗███████║██╔██╗ ██║   ██║   ███████║██████╔╝███████║"
echo "  ╚════██║██╔══██║██║╚██╗██║   ██║   ██╔══██║██╔══██╗██╔══██║"
echo "  ███████║██║  ██║██║ ╚████║   ██║   ██║  ██║██║  ██║██║  ██║"
echo "  ╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝"
echo -e "${NC}"
echo -e "  ${GREEN}SantaraBaru Roleplay Server (open.mp Native)${NC} — Memulai..."
echo ""

# ── 1. Generate config.json ──────────────────────────────────
SERVER_NAME="${SERVER_NAME:-SantaraBaru Roleplay}"
RCON_PASSWORD="${RCON_PASSWORD:-SantaraRcon2024}"
SAMP_PORT="${SAMP_PORT:-50034}"
VOICE_PORT="${VOICE_PORT:-39966}"
ARTWORK_CDN="${ARTWORK_CDN:-https://raw.githubusercontent.com/biomies/santarabaru/main/server/models}"

cat > /server/config.json <<EOF
{
    "announce": true,
    "allow_queries": true,
    "query": true,
    "chat_input_filter": false,
    "language": "Indonesian",
    "max_players": 50,
    "name": "${SERVER_NAME}",
    "password": "",
    "port": ${SAMP_PORT},
    "rcon": {
        "enable": true,
        "allow_teleport": false,
        "password": "${RCON_PASSWORD}"
    },
    "sleep": 5,
    "use_player_ped_anims": true,
    "pawn": {
        "main_scripts": [
            "santara 0"
        ]
    },
    "logging": {
        "enable": true,
        "use_timestamp": true,
        "log_chat": false,
        "log_queries": false,
        "log_connections": true
    },
    "artwork": {
        "enable": true,
        "models_path": "models",
        "port": ${SAMP_PORT},
        "cdn": "${ARTWORK_CDN}",
        "web_server_bind": ""
    },
    "network": {
        "bind": "",
        "use_lan_mode": false,
        "port": ${SAMP_PORT}
    },
    "sampvoice": {
        "voice_port": ${VOICE_PORT},
        "check_for_streamed_in": true
    }
}
EOF
echo -e "${GREEN}[✓] config.json dibuat.${NC}"

# ── 2. Compile Gamemode ──────────────────────────────────────
PWN_FILE="/server/gamemodes/santara.pwn"
AMX_FILE="/server/gamemodes/santara.amx"
PAWNCC="/server/qawno/pawncc"

if [ ! -f "$PAWNCC" ]; then
    PAWNCC=$(find /server -name "pawncc" -type f 2>/dev/null | head -1)
fi

if [ -f "$PAWNCC" ] && [ -f "$PWN_FILE" ]; then
    # Copy custom includes if present
    if [ -d "/server/include" ]; then
        cp -f /server/include/*.inc /server/qawno/include/ 2>/dev/null || true
    fi

    NEEDS_COMPILE=0
    if [ ! -f "$AMX_FILE" ]; then
        NEEDS_COMPILE=1
    elif find /server/gamemodes /server/include -type f \( -name "*.pwn" -o -name "*.inc" \) -newer "$AMX_FILE" 2>/dev/null | grep -q .; then
        NEEDS_COMPILE=1
    fi

    if [ "$NEEDS_COMPILE" -eq 1 ]; then
        echo -e "${YELLOW}[*] Mengompilasi gamemode santara.pwn (termasuk modul)...${NC}"
        chmod +x "$PAWNCC"
        export LD_LIBRARY_PATH="/server/qawno:${LD_LIBRARY_PATH}"
        "$PAWNCC" "$PWN_FILE" \
            "-i/server/include" \
            "-i/server/qawno/include" \
            "-o${AMX_FILE}" \
            '-;+' \
            '-d0' \
            2>&1
        if [ -f "$AMX_FILE" ]; then
            echo -e "${GREEN}[✓] Kompilasi berhasil: santara.amx${NC}"
        else
            echo -e "${RED}[!] Kompilasi gagal! Periksa error di atas.${NC}"
            exit 1
        fi
    else
        echo -e "${GREEN}[✓] santara.amx sudah up-to-date. Skip kompilasi.${NC}"
    fi
fi

# ── 3. Start Server ──────────────────────────────────────────
echo ""
echo -e "${GREEN}[✓] Semua siap. Memulai open.mp server...${NC}"
echo -e "${CYAN}=================================================${NC}"
echo ""

cd /server
exec ./omp-server
