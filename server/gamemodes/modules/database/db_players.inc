#if defined _MODULE_DB_PLAYERS_INC
    #endinput
#endif
#define _MODULE_DB_PLAYERS_INC

// ============================================================
//  SantaraBaru Roleplay - Player Database Operations (Save / Load)
// ============================================================

stock DoSavePlayer(playerid) {
    if (!gPlayerData[playerid][p_LoggedIn] || gPlayerData[playerid][p_CharID] == 0) return;
    new Float:x, Float:y, Float:z, Float:a;
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, a);
    new query[512];
    format(query, sizeof(query),
        "UPDATE `characters` SET `skin_id`=%d, `x`=%.4f, `y`=%.4f, `z`=%.4f, `angle`=%.4f, `score`=%d, `cash`=%d, `play_minutes`=`play_minutes`+%d WHERE `id`=%d",
        gPlayerData[playerid][p_Skin],
        x, y, z, a,
        GetPlayerScore(playerid), gPlayerData[playerid][p_Cash],
        gPlayerData[playerid][p_PlayTime],
        gPlayerData[playerid][p_CharID]);
    DB_FreeResultSet(DB_ExecuteQuery(gDB, query));
    gPlayerData[playerid][p_PlayTime] = 0;
}

stock LoadCharacter(playerid, charid) {
    new query[256];
    format(query, sizeof(query),
        "SELECT `id`, `char_name`, `birthplace`, `birthdate`, `gender`, `skin_id`, `x`, `y`, `z`, `angle`, `score`, `cash`, `has_ktp` FROM `characters` WHERE `id` = %d AND `account_id` = %d AND `is_active` = 1 LIMIT 1",
        charid, gPlayerData[playerid][p_AccountID]);

    new DBResult:res = DB_ExecuteQuery(gDB, query);
    if (!res || DB_GetRowCount(res) == 0) {
        if (res) DB_FreeResultSet(res);
        ShowCharacterSelection(playerid);
        return 0;
    }

    gPlayerData[playerid][p_CharID] = DB_GetFieldIntByName(res, "id");
    gPlayerData[playerid][p_Skin]   = DB_GetFieldIntByName(res, "skin_id");
    gPlayerData[playerid][p_X]      = DB_GetFieldFloatByName(res, "x");
    gPlayerData[playerid][p_Y]      = DB_GetFieldFloatByName(res, "y");
    gPlayerData[playerid][p_Z]      = DB_GetFieldFloatByName(res, "z");
    gPlayerData[playerid][p_A]      = DB_GetFieldFloatByName(res, "angle");
    gPlayerData[playerid][p_Score]  = DB_GetFieldIntByName(res, "score");
    gPlayerData[playerid][p_Cash]   = DB_GetFieldIntByName(res, "cash");
    gPlayerData[playerid][p_Gender] = DB_GetFieldIntByName(res, "gender");
    gPlayerData[playerid][p_HasKTP] = (DB_GetFieldIntByName(res, "has_ktp") == 1);
    DB_GetFieldStringByName(res, "char_name", gPlayerData[playerid][p_CharName], 48);
    DB_GetFieldStringByName(res, "birthplace", gPlayerData[playerid][p_BirthPlace], 32);
    DB_GetFieldStringByName(res, "birthdate", gPlayerData[playerid][p_BirthDate], 16);
    DB_FreeResultSet(res);

    // Update last_login karakter
    format(query, sizeof(query), "UPDATE `characters` SET `last_login`=CURRENT_TIMESTAMP WHERE `id`=%d", gPlayerData[playerid][p_CharID]);
    DB_FreeResultSet(DB_ExecuteQuery(gDB, query));

    gPlayerData[playerid][p_IsNewCharacter] = false;
    OpenSpawnSelection(playerid, false);
    return 1;
}
