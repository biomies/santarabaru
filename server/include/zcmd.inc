#if defined _zcmd_included
	#endinput
#endif
#define _zcmd_included

#define CMD:%1(%2) \
	forward cmd_%1(%2); \
	public cmd_%1(%2)

#define COMMAND:%1(%2) \
	CMD:%1(%2)

public OnPlayerCommandText(playerid, cmdtext[])
{
	static funcname[32];
	new pos = 0;
	while (cmdtext[pos] > ' ') pos++;
	if (!pos) return 0;
	if (cmdtext[0] != '/') return 0;

	funcname[0] = 'c';
	funcname[1] = 'm';
	funcname[2] = 'd';
	funcname[3] = '_';
	
	new i = 1;
	while (i < pos && i < 28)
	{
		funcname[i + 3] = (cmdtext[i] >= 'A' && cmdtext[i] <= 'Z') ? (cmdtext[i] + 32) : cmdtext[i];
		i++;
	}
	funcname[i + 3] = '\0';

	while (cmdtext[pos] == ' ') pos++;

	if (funcidx(funcname) != -1)
	{
		return CallLocalFunction(funcname, "is", playerid, cmdtext[pos]);
	}
	return 0;
}
