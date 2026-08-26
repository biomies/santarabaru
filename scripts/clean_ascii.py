#!/usr/bin/env python3
import os

replacements = {
    "🚗": "",
    "🛒": "",
    "✖": "X",
    "✓": "[OK]",
    "🗑️": "[Hapus]",
    "🏛️": "[Gedung]",
    "🏎️": "[Mobil]",
    "🏢": "[Kantor]",
    "•": "*",
    "»": ">",
    "«": "<",
    "—": "-",
    "–": "-",
    "“": "\"",
    "”": "\"",
    "‘": "\'",
    "’": "\'",
    "…": "...",
    "™": "",
    "®": "",
    "©": "(c)",
    "★": "*",
    "☆": "*",
    "†": "+",
    "‡": "+",
    "§": "",
    "°": " deg"
}

def clean_file(filepath):
    with open(filepath, "rb") as f:
        raw = f.read()
    
    text = raw.decode("utf-8", errors="replace")
    original = text
    
    for k, v in replacements.items():
        text = text.replace(k, v)
        
    cleaned_chars = []
    for c in text:
        if ord(c) < 128:
            cleaned_chars.append(c)
        else:
            cleaned_chars.append(" ")
            
    final_text = "".join(cleaned_chars)
    if final_text != original:
        with open(filepath, "w", encoding="utf-8") as f:
            f.write(final_text)
        print(f"Cleaned non-ascii in: {filepath}")

count = 0
for root, dirs, files in os.walk("server/gamemodes"):
    for file in files:
        if file.endswith(".inc") or file.endswith(".pwn"):
            clean_file(os.path.join(root, file))
            count += 1

print(f"Scanned {count} files for non-ascii.")
