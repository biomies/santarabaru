#if defined _streamer_included
	#endinput
#endif
#define _streamer_included

#define INVALID_STREAMER_ID (0)

native CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 300.0, Float:drawdistance = 0.0, areaid = -1, priority = 0);
native DestroyDynamicObject(objectid);
native CreateDynamic3DTextLabel(const text[], color, Float:x, Float:y, Float:z, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 100.0, areaid = -1, priority = 0);
native DestroyDynamic3DTextLabel(Text3D:id);
native UpdateDynamic3DTextLabelText(Text3D:id, color, const text[]);
