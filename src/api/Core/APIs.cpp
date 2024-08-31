#include "../Impl.hpp"
#include "../API.hpp"

DECLARE_API(Core, TickCount)
{
	uint32_t ret = Runtime::Instance().GetOMPAPI()->Core.TickCount();
	API_RETURN(uint32_t ret);
}

DECLARE_API(Core, MaxPlayers)
{
	int ret = Runtime::Instance().GetOMPAPI()->Core.MaxPlayers();
	API_RETURN(int ret);
}

DECLARE_API(Core, Log, StringCharPtr text)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.Log(text);
	API_RETURN(bool ret);
}

DECLARE_API(Core, IsAdminTeleportAllowed)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.IsAdminTeleportAllowed();
	API_RETURN(bool ret);
}

DECLARE_API(Core, AllowAdminTeleport, bool allow)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.AllowAdminTeleport(allow);
	API_RETURN(bool ret);
}

DECLARE_API(Core, AreAllAnimationsEnabled)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.AreAllAnimationsEnabled();
	API_RETURN(bool ret);
}

DECLARE_API(Core, EnableAllAnimations, bool allow)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.EnableAllAnimations(allow);
	API_RETURN(bool ret);
}

DECLARE_API(Core, IsAnimationLibraryValid, StringCharPtr name)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.IsAnimationLibraryValid(name);
	API_RETURN(bool ret);
}

DECLARE_API(Core, AreInteriorWeaponsAllowed)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.AreInteriorWeaponsAllowed();
	API_RETURN(bool ret);
}

DECLARE_API(Core, AllowInteriorWeapons, bool allow)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.AllowInteriorWeapons(allow);
	API_RETURN(bool ret);
}

DECLARE_API(Core, BlockIpAddress, StringCharPtr ipAddress, int timeMS)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.BlockIpAddress(ipAddress, timeMS);
	API_RETURN(bool ret);
}

DECLARE_API(Core, UnBlockIpAddress, StringCharPtr ipAddress)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.UnBlockIpAddress(ipAddress);
	API_RETURN(bool ret);
}

DECLARE_API(Core, DisableEntryExitMarkers)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.DisableEntryExitMarkers();
	API_RETURN(bool ret);
}

DECLARE_API(Core, DisableNameTagsLOS)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.DisableNameTagsLOS();
	API_RETURN(bool ret);
}

DECLARE_API(Core, EnableZoneNames, bool enable)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.EnableZoneNames(enable);
	API_RETURN(bool ret);
}

DECLARE_API(Core, ShowGameTextForAll, StringCharPtr msg, int time, int style)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.ShowGameTextForAll(msg, time, style);
	API_RETURN(bool ret);
}

DECLARE_API(Core, HideGameTextForAll, int style)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.HideGameTextForAll(style);
	API_RETURN(bool ret);
}

DECLARE_API_ARGNUM(Core, NetworkStats, 0, OutputStringViewPtr output)
{
	int ret = Runtime::Instance().GetOMPAPI()->Core.NetworkStats(output);
	API_RETURN(int ret, OutputStringViewPtr output);
}

DECLARE_API(Core, ServerTickRate)
{
	int ret = Runtime::Instance().GetOMPAPI()->Core.ServerTickRate();
	API_RETURN(int ret);
}

DECLARE_API_ARGNUM(Core, GetWeaponName, 1, int weaponid, OutputStringViewPtr output)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.GetWeaponName(weaponid, output);
	API_RETURN(bool ret, OutputStringViewPtr output);
}

DECLARE_API(Core, SetChatRadius, float globalChatRadius)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.SetChatRadius(globalChatRadius);
	API_RETURN(bool ret);
}

DECLARE_API(Core, SetMarkerRadius, float playerMarkerRadius)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.SetMarkerRadius(playerMarkerRadius);
	API_RETURN(bool ret);
}

DECLARE_API(Core, SendRconCommand, StringCharPtr command)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.SendRconCommand(command);
	API_RETURN(bool ret);
}

DECLARE_API(Core, SetDeathDropAmount, int amount)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.SetDeathDropAmount(amount);
	API_RETURN(bool ret);
}

DECLARE_API(Core, GameMode, StringCharPtr string)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.GameMode(string);
	API_RETURN(bool ret);
}

DECLARE_API(Core, SetGravity, float gravity)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.SetGravity(gravity);
	API_RETURN(bool ret);
}

DECLARE_API(Core, GetGravity)
{
	float ret = Runtime::Instance().GetOMPAPI()->Core.GetGravity();
	API_RETURN(float ret);
}

DECLARE_API(Core, SetNameTagsDrawDistance, float distance)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.SetNameTagsDrawDistance(distance);
	API_RETURN(bool ret);
}

DECLARE_API(Core, SetWeather, int weatherid)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.SetWeather(weatherid);
	API_RETURN(bool ret);
}

DECLARE_API(Core, SetWorldTime, int hour)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.SetWorldTime(hour);
	API_RETURN(bool ret);
}

DECLARE_API(Core, ShowNameTags, bool show)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.ShowNameTags(show);
	API_RETURN(bool ret);
}

DECLARE_API(Core, ShowPlayerMarkers, int mode)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.ShowPlayerMarkers(mode);
	API_RETURN(bool ret);
}

DECLARE_API(Core, UsePedAnims)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.UsePedAnims();
	API_RETURN(bool ret);
}

DECLARE_API(Core, GetWeather)
{
	int ret = Runtime::Instance().GetOMPAPI()->Core.GetWeather();
	API_RETURN(int ret);
}

DECLARE_API(Core, GetWorldTime)
{
	int ret = Runtime::Instance().GetOMPAPI()->Core.GetWorldTime();
	API_RETURN(int ret);
}

DECLARE_API(Core, ToggleChatTextReplacement, bool enable)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.ToggleChatTextReplacement(enable);
	API_RETURN(bool ret);
}

DECLARE_API(Core, IsChatTextReplacementToggled)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.IsChatTextReplacementToggled();
	API_RETURN(bool ret);
}

DECLARE_API(Core, IsNickNameValid, StringCharPtr name)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.IsNickNameValid(name);
	API_RETURN(bool ret);
}

DECLARE_API(Core, AllowNickNameCharacter, int character, bool allow)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.AllowNickNameCharacter(character, allow);
	API_RETURN(bool ret);
}

DECLARE_API(Core, IsNickNameCharacterAllowed, int character)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.IsNickNameCharacterAllowed(character);
	API_RETURN(bool ret);
}

DECLARE_API(Core, ClearBanList)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.ClearBanList();
	API_RETURN(bool ret);
}

DECLARE_API(Core, IsIpAddressBanned, StringCharPtr ip)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.IsIpAddressBanned(ip);
	API_RETURN(bool ret);
}

DECLARE_API(Core, GetWeaponSlot, uint8_t weapon)
{
	int ret = Runtime::Instance().GetOMPAPI()->Core.GetWeaponSlot(weapon);
	API_RETURN(int ret);
}

DECLARE_API(Core, AddRule, StringCharPtr name, StringCharPtr value)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.AddRule(name, value);
	API_RETURN(bool ret);
}

DECLARE_API(Core, IsValidRule, StringCharPtr name)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.IsValidRule(name);
	API_RETURN(bool ret);
}

DECLARE_API(Core, RemoveRule, StringCharPtr name)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Core.RemoveRule(name);
	API_RETURN(bool ret);
}
