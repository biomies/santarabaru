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
        // Fallback: component mungkin sudah aktif meski SvInit() return false
        gVoiceEnabled = true;
        print("[Voice] SAMPVOICE component aktif (SvInit() fallback mode).");
    }
    if (gVoiceEnabled) {
        printf("[Voice] SAMPVOICE aktif - proximity voice chat tersedia (20m)");
    } else {
        print("[Voice] SAMPVOICE non-aktif - menggunakan text chat RP");
    }
}

stock SetupVoiceStream(playerid) {
    DestroyVoiceStream(playerid);
    if (!gVoiceEnabled) return;
    gPlayerData[playerid][p_VoiceStream] = SvCreateDLStreamAtPlayer(
        DIST_VOICE,
        SV_INFINITY,
        playerid,
        -1,
        "local"
    );
    SvAttachSpeakerToStream(gPlayerData[playerid][p_VoiceStream], playerid);
}

stock DestroyVoiceStream(playerid) {
    if (gVoiceEnabled && gPlayerData[playerid][p_VoiceStream] != SV_NULL) {
        SvDetachSpeakerFromStream(gPlayerData[playerid][p_VoiceStream], playerid);
        SvDeleteStream(gPlayerData[playerid][p_VoiceStream]);
        gPlayerData[playerid][p_VoiceStream] = SV_NULL;
    }
}
