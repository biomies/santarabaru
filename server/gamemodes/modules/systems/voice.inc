#if defined _MODULE_VOICE_INC
    #endinput
#endif
#define _MODULE_VOICE_INC

// ============================================================
//  SantaraBaru Roleplay - Voice Chat System (SAMPVOICE 3D)
// ============================================================

stock InitVoiceSystem() {
    gVoiceEnabled = SvInit(24000);
    if (!gVoiceEnabled) {
        // Fallback jika component open.mp aktif tanpa return value
        gVoiceEnabled = true;
        print("[Voice] SAMPVOICE component aktif (fallback mode).");
    } else {
        printf("[Voice] SAMPVOICE aktif (bitrate 24000) - proximity 3D 20m.");
    }
    return 1;
}

stock SetupVoiceStream(playerid) {
    DestroyVoiceStream(playerid);
    if (!gVoiceEnabled) return 0;

    // Buat dynamic local stream 3D di sekitar pemain (radius 20 meter)
    gPlayerData[playerid][p_VoiceStream] = SvCreateDLStreamAtPlayer(
        DIST_VOICE,
        SV_INFINITY,
        playerid,
        0x00FF00FF,
        "Local"
    );

    // Daftarkan tombol Push-To-Talk:
    // 0x42 = Huruf 'B' (Default SA-MP Voice)
    // 0x5A = Huruf 'Z' (Alternatif)
    // 0x56 = Huruf 'V' (Alternatif)
    SvAddKey(playerid, 0x42);
    SvAddKey(playerid, 0x5A);
    SvAddKey(playerid, 0x56);

    return 1;
}

stock DestroyVoiceStream(playerid) {
    if (gPlayerData[playerid][p_VoiceStream] != SV_NULL) {
        SvDetachSpeakerFromStream(gPlayerData[playerid][p_VoiceStream], playerid);
        SvDeleteStream(gPlayerData[playerid][p_VoiceStream]);
        gPlayerData[playerid][p_VoiceStream] = SV_NULL;
    }
    return 1;
}

// Callback saat pemain menekan tombol Push-To-Talk
public OnPlayerActivationKeyPress(playerid, keyid) {
    if ((keyid == 0x42 || keyid == 0x5A || keyid == 0x56) && gPlayerData[playerid][p_VoiceStream] != SV_NULL) {
        SvAttachSpeakerToStream(gPlayerData[playerid][p_VoiceStream], playerid);
    }
    return 1;
}

// Callback saat pemain melepas tombol Push-To-Talk
public OnPlayerActivationKeyRelease(playerid, keyid) {
    if ((keyid == 0x42 || keyid == 0x5A || keyid == 0x56) && gPlayerData[playerid][p_VoiceStream] != SV_NULL) {
        SvDetachSpeakerFromStream(gPlayerData[playerid][p_VoiceStream], playerid);
    }
    return 1;
}
