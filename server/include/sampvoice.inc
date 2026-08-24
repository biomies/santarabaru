#if defined _sampvoice_included
	#endinput
#endif
#define _sampvoice_included

#define SV_NULL                 (SV_GSTREAM:0)
#define SV_INFINITY             (-1)

native bool:SvInit(bitrate = 24000);
native SV_GSTREAM:SvCreateDLStreamAtPlayer(Float:distance, max_players, playerid, color = -1, const name[] = "");
native bool:SvAttachSpeakerToStream(SV_GSTREAM:stream, playerid);
native bool:SvDetachSpeakerFromStream(SV_GSTREAM:stream, playerid);
native bool:SvDeleteStream(SV_GSTREAM:stream);
native bool:SvGetPlayerVoiceStatus(playerid);
