#if defined _MODULE_UTILS_INC
    #endinput
#endif
#define _MODULE_UTILS_INC

// ============================================================
//  SantaraBaru Roleplay - Core Utilities & Helper Functions
// ============================================================

forward KickPlayer(playerid);
public KickPlayer(playerid) {
    if (IsPlayerConnected(playerid)) Kick(playerid);
}

stock bool:CheckSpawned(playerid) {
    if (!gPlayerData[playerid][p_LoggedIn] || !gPlayerData[playerid][p_Spawned]) {
        SendClientMessage(playerid, COL_RED, "  Anda harus login dan spawn terlebih dahulu.");
        return false;
    }
    return true;
}

stock GetCharName(playerid, name[], len = 48) {
    if (strlen(gPlayerData[playerid][p_CharName]) > 0) {
        format(name, len, "%s", gPlayerData[playerid][p_CharName]);
    } else {
        format(name, len, "%s", gPlayerData[playerid][p_Username]);
    }
}

stock StrToUpper(str[]) {
    for (new i = 0; str[i]; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 32;
        }
    }
}

stock TrimSpaces(str[]) {
    new start = 0;
    while (str[start] == ' ' || str[start] == '\t') start++;
    if (start > 0) {
        new i = 0;
        while (str[start + i]) {
            str[i] = str[start + i];
            i++;
        }
        str[i] = '\0';
    }
    new len = strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len - 1] == '\r' || str[len - 1] == '\n')) {
        str[len - 1] = '\0';
        len--;
    }
}

stock FormatRupiah(amount, output[], len = 32) {
    new str[32];
    format(str, sizeof(str), "%d", amount);
    new strLen = strlen(str);
    new isNegative = (amount < 0);
    new startDigits = isNegative ? 1 : 0;

    new outIdx = 0;
    if (isNegative) {
        output[outIdx++] = '-';
    }

    for (new i = startDigits; i < strLen; i++) {
        output[outIdx++] = str[i];
        new remaining = strLen - i - 1;
        if (remaining > 0 && remaining % 3 == 0) {
            output[outIdx++] = '.';
        }
    }
    output[outIdx] = '\0';
}
