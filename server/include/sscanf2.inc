#if defined _sscanf2_included
	#endinput
#endif
#define _sscanf2_included

native sscanf(const data[], const format[], {Float,_}:...);
native unformat(const data[], const format[], {Float,_}:...) = sscanf;
