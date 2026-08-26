#if defined _sampvoice_included
	#endinput
#endif
#define _sampvoice_included

#define SV_NULL                 (SV_GSTREAM:0)
#define SV_INFINITY             (-1)
#define SV_FALSE                (false)
#define SV_TRUE                 (true)

native bool:SvInit(bitrate = 24000);
native SvGetVersion(playerid);
native bool:SvHasMicro(playerid);
native SV_GSTREAM:SvCreateDLStreamAtPlayer(Float:distance, max_players, playerid, color = -1, const name[] = "");
native bool:SvAttachSpeakerToStream(SV_GSTREAM:stream, playerid);
native bool:SvDetachSpeakerFromStream(SV_GSTREAM:stream, playerid);
native bool:SvAttachListenerToStream(SV_GSTREAM:stream, playerid);
native bool:SvDetachListenerFromStream(SV_GSTREAM:stream, playerid);
native bool:SvDeleteStream(SV_GSTREAM:stream);
native bool:SvAddKey(playerid, keyid);
native bool:SvRemoveKey(playerid, keyid);
native bool:SvGetPlayerVoiceStatus(playerid);

forward OnPlayerActivationKeyPress(playerid, keyid);
forward OnPlayerActivationKeyRelease(playerid, keyid);
