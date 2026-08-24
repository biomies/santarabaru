# ============================================================
# SantaraBaru Roleplay — Dockerfile
# Base : Ubuntu 22.04 (i386 support untuk open.mp & components)
# open.mp   : v1.5.8.3079
# sscanf    : v2.13.8 (open.mp component)
# sampvoice : v3.2.0-omp (open.mp component)
# ============================================================

FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# ── Install dependencies ─────────────────────────────────────
RUN dpkg --add-architecture i386 && \
    apt-get update && apt-get install -y \
        wget \
        curl \
        unzip \
        tar \
        netcat-openbsd \
        lib32stdc++6 \
        lib32gcc-s1 \
        lib32z1 \
        libatomic1:i386 \
        libc6:i386 \
        libssl-dev:i386 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /server

# ── Download open.mp server v1.5.8.3079 (Linux x86) ─────────
RUN wget -q \
    "https://github.com/openmultiplayer/open.mp/releases/download/v1.5.8.3079/open.mp-linux-x86.tar.gz" \
    -O /tmp/omp.tar.gz && \
    tar -xzf /tmp/omp.tar.gz -C /tmp && \
    cp -r /tmp/Server/. /server/ && \
    rm -rf /tmp/omp.tar.gz /tmp/Server

# ── Download sscanf v2.13.8 — open.mp component .so ──────────
RUN wget -q \
    "https://github.com/Y-Less/sscanf/releases/download/v2.13.8/sscanf-2.13.8-linux.tar.gz" \
    -O /tmp/sscanf.tar.gz && \
    mkdir -p /tmp/sscanf && \
    tar -xzf /tmp/sscanf.tar.gz -C /tmp/sscanf && \
    find /tmp/sscanf -name "sscanf.so" -exec cp {} /server/components/ \; && \
    rm -rf /tmp/sscanf.tar.gz /tmp/sscanf

# ── Download SAMPVOICE v3.2.0-omp — component .so ─────────────
RUN wget -q \
    "https://github.com/AmyrAhmady/sampvoice/releases/download/v3.2.0-omp/sampvoice-linux.zip" \
    -O /tmp/sampvoice.zip && \
    unzip -q /tmp/sampvoice.zip -d /tmp/sampvoice && \
    find /tmp/sampvoice -name "*.so" -exec cp {} /server/components/ \; || true && \
    rm -rf /tmp/sampvoice.zip /tmp/sampvoice

# ── Pastikan direktori yang diperlukan ada ────────────────────
RUN mkdir -p \
    /server/gamemodes \
    /server/include \
    /server/plugins \
    /server/components \
    /server/scriptfiles \
    /server/logs

# ── Copy server files (gamemodes, include, scriptfiles) ───────
COPY server/gamemodes/ /server/gamemodes/
COPY server/scriptfiles/ /server/scriptfiles/
COPY server/include/ /server/include/
RUN cp -rf /server/include/*.inc /server/qawno/include/ 2>/dev/null || true

# ── Copy & setup entrypoint ───────────────────────────────────
COPY scripts/entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh /server/omp-server

EXPOSE 7777/udp

ENTRYPOINT ["/entrypoint.sh"]
