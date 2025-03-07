#include "../Impl.hpp"
#include "../API.hpp"

DECLARE_API(Player, SetSpawnInfo, objectPtr player, uint8_t team, int skin, float x, float y, float z, float angle, uint8_t weapon1, uint32_t ammo1, uint8_t weapon2, uint32_t ammo2, uint8_t weapon3, uint32_t ammo3)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetSpawnInfo(player, team, skin, x, y, z, angle, weapon1, ammo1, weapon2, ammo2, weapon3, ammo3);
	API_RETURN(bool ret);
}

DECLARE_API_ARGNUM(Player, GetSpawnInfo, 1, objectPtr player, UInt8Ref team, IntRef skin, FloatRef x, FloatRef y, FloatRef z, FloatRef angle, UInt8Ref weapon1, UInt32Ref ammo1, UInt8Ref weapon2, UInt32Ref ammo2, UInt8Ref weapon3, UInt32Ref ammo3)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.GetSpawnInfo(player, team, skin, x, y, z, angle, weapon1, ammo1, weapon2, ammo2, weapon3, ammo3);
	API_RETURN(bool ret, UInt8Ref team, IntRef skin, FloatRef x, FloatRef y, FloatRef z, FloatRef angle, UInt8Ref weapon1, UInt32Ref ammo1, UInt8Ref weapon2, UInt32Ref ammo2, UInt8Ref weapon3, UInt32Ref ammo3);
}

DECLARE_API(Player, GetNetworkStats, objectPtr player)
{
	CREATE_CAPI_STRING_VIEW(output, 2048);
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetNetworkStats(player, output);
	COPY_AND_FREE_CAPI_STRING_VIEW(output);
	API_RETURN(int ret, OutputStringViewPtr output);
}

DECLARE_API(Player, NetStatsBytesReceived, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.NetStatsBytesReceived(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, NetStatsBytesSent, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.NetStatsBytesSent(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, NetStatsConnectionStatus, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.NetStatsConnectionStatus(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, NetStatsGetConnectedTime, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.NetStatsGetConnectedTime(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, NetStatsGetIpPort, objectPtr player)
{
	CREATE_CAPI_STRING_VIEW(output, 30);
	bool ret = Runtime::Instance().GetOMPAPI()->Player.NetStatsGetIpPort(player, output);
	COPY_AND_FREE_CAPI_STRING_VIEW(output);
	API_RETURN(bool ret, OutputStringViewPtr output);
}

DECLARE_API(Player, NetStatsMessagesReceived, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.NetStatsMessagesReceived(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, NetStatsMessagesRecvPerSecond, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.NetStatsMessagesRecvPerSecond(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, NetStatsMessagesSent, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.NetStatsMessagesSent(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, NetStatsPacketLossPercent, objectPtr player)
{
	float ret = Runtime::Instance().GetOMPAPI()->Player.NetStatsPacketLossPercent(player);
	API_RETURN(float ret);
}

DECLARE_API(Player, GetCustomSkin, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetCustomSkin(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, GetDialog, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetDialog(player);
	API_RETURN(int ret);
}

DECLARE_API_ARGNUM(Player, GetDialogData, 1, objectPtr player, IntRef dialogid, IntRef style, OutputStringViewPtr title, OutputStringViewPtr body, OutputStringViewPtr button1, OutputStringViewPtr button2)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.GetDialogData(player, dialogid, style, title, body, button1, button2);
	API_RETURN(bool ret, IntRef dialogid, IntRef style, OutputStringViewPtr title, OutputStringViewPtr body, OutputStringViewPtr button1, OutputStringViewPtr button2);
}

DECLARE_API(Player, GetMenu, objectPtr player)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Player.GetMenu(player);
	API_RETURN(objectPtr ret);
}

DECLARE_API(Player, GetSurfingPlayerObject, objectPtr player)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Player.GetSurfingPlayerObject(player);
	API_RETURN(objectPtr ret);
}

DECLARE_API(Player, GetCameraTargetPlayerObject, objectPtr player)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Player.GetCameraTargetPlayerObject(player);
	API_RETURN(objectPtr ret);
}

DECLARE_API(Player, FromID, int playerid)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Player.FromID(playerid);
	API_RETURN(objectPtr ret);
}

DECLARE_API(Player, GetID, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetID(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, SendClientMessage, objectPtr player, uint32_t color, StringCharPtr text)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SendClientMessage(player, color, text);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SetCameraPos, objectPtr player, float x, float y, float z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetCameraPos(player, x, y, z);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SetDrunkLevel, objectPtr player, int level)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetDrunkLevel(player, level);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SetInterior, objectPtr player, int interior)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetInterior(player, interior);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SetWantedLevel, objectPtr player, int level)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetWantedLevel(player, level);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SetWeather, objectPtr player, int weather)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetWeather(player, weather);
	API_RETURN(bool ret);
}

DECLARE_API(Player, GetWeather, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetWeather(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, SetSkin, objectPtr player, int skin)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetSkin(player, skin);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SetShopName, objectPtr player, StringCharPtr name)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetShopName(player, name);
	API_RETURN(bool ret);
}

DECLARE_API(Player, GiveMoney, objectPtr player, int amount)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.GiveMoney(player, amount);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SetCameraLookAt, objectPtr player, float x, float y, float z, int cutType)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetCameraLookAt(player, x, y, z, cutType);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SetCameraBehind, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetCameraBehind(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, CreateExplosion, objectPtr player, float x, float y, float z, int type, float radius)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.CreateExplosion(player, x, y, z, type, radius);
	API_RETURN(bool ret);
}

DECLARE_API(Player, PlayAudioStream, objectPtr player, StringCharPtr url, float x, float y, float z, float distance, bool usePos)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.PlayAudioStream(player, url, x, y, z, distance, usePos);
	API_RETURN(bool ret);
}

DECLARE_API(Player, StopAudioStream, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.StopAudioStream(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, ToggleWidescreen, objectPtr player, bool enable)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.ToggleWidescreen(player, enable);
	API_RETURN(bool ret);
}

DECLARE_API(Player, IsWidescreenToggled, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.IsWidescreenToggled(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SetHealth, objectPtr player, float health)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetHealth(player, health);
	API_RETURN(bool ret);
}

DECLARE_API(Player, GetHealth, objectPtr player)
{
	float ret = Runtime::Instance().GetOMPAPI()->Player.GetHealth(player);
	API_RETURN(float ret);
}

DECLARE_API(Player, SetArmor, objectPtr player, float armor)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetArmor(player, armor);
	API_RETURN(bool ret);
}

DECLARE_API(Player, GetArmor, objectPtr player)
{
	float ret = Runtime::Instance().GetOMPAPI()->Player.GetArmor(player);
	API_RETURN(float ret);
}

DECLARE_API(Player, SetTeam, objectPtr player, int team)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetTeam(player, team);
	API_RETURN(bool ret);
}

DECLARE_API(Player, GetTeam, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetTeam(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, SetScore, objectPtr player, int score)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetScore(player, score);
	API_RETURN(bool ret);
}

DECLARE_API(Player, GetScore, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetScore(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, GetSkin, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetSkin(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, SetColor, objectPtr player, uint32_t color)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetColor(player, color);
	API_RETURN(bool ret);
}

DECLARE_API(Player, GetColor, objectPtr player)
{
	uint32_t ret = Runtime::Instance().GetOMPAPI()->Player.GetColor(player);
	API_RETURN(uint32_t ret);
}

DECLARE_API(Player, GetDefaultColor, objectPtr player)
{
	uint32_t ret = Runtime::Instance().GetOMPAPI()->Player.GetDefaultColor(player);
	API_RETURN(uint32_t ret);
}

DECLARE_API(Player, GetDrunkLevel, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetDrunkLevel(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, GiveWeapon, objectPtr player, int weapon, int ammo)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.GiveWeapon(player, weapon, ammo);
	API_RETURN(bool ret);
}

DECLARE_API(Player, RemoveWeapon, objectPtr player, int weapon)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.RemoveWeapon(player, weapon);
	API_RETURN(bool ret);
}

DECLARE_API(Player, GetMoney, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetMoney(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, ResetMoney, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.ResetMoney(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SetName, objectPtr player, StringCharPtr name)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.SetName(player, name);
	API_RETURN(int ret);
}

DECLARE_API_ARGNUM(Player, GetName, 1, objectPtr player, OutputStringViewPtr name)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetName(player, name);
	API_RETURN(int ret, OutputStringViewPtr name);
}

DECLARE_API(Player, GetState, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetState(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, GetPing, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetPing(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, GetWeapon, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetWeapon(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, SetTime, objectPtr player, int hour, int minute)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetTime(player, hour, minute);
	API_RETURN(bool ret);
}

DECLARE_API_ARGNUM(Player, GetTime, 1, objectPtr player, IntRef hour, IntRef minute)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.GetTime(player, hour, minute);
	API_RETURN(bool ret, IntRef hour, IntRef minute);
}

DECLARE_API(Player, ToggleClock, objectPtr player, bool enable)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.ToggleClock(player, enable);
	API_RETURN(bool ret);
}

DECLARE_API(Player, HasClock, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.HasClock(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, ForceClassSelection, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.ForceClassSelection(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, GetWantedLevel, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetWantedLevel(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, SetFightingStyle, objectPtr player, int style)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetFightingStyle(player, style);
	API_RETURN(bool ret);
}

DECLARE_API(Player, GetFightingStyle, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetFightingStyle(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, SetVelocity, objectPtr player, float x, float y, float z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetVelocity(player, x, y, z);
	API_RETURN(bool ret);
}

DECLARE_API_ARGNUM(Player, GetVelocity, 1, objectPtr player, FloatRef x, FloatRef y, FloatRef z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.GetVelocity(player, x, y, z);
	API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z);
}

DECLARE_API_ARGNUM(Player, GetCameraPos, 1, objectPtr player, FloatRef x, FloatRef y, FloatRef z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.GetCameraPos(player, x, y, z);
	API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z);
}

DECLARE_API(Player, GetDistanceFromPoint, objectPtr player, float x, float y, float z)
{
	float ret = Runtime::Instance().GetOMPAPI()->Player.GetDistanceFromPoint(player, x, y, z);
	API_RETURN(float ret);
}

DECLARE_API(Player, GetInterior, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetInterior(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, SetPos, objectPtr player, float x, float y, float z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetPos(player, x, y, z);
	API_RETURN(bool ret);
}

DECLARE_API_ARGNUM(Player, GetPos, 1, objectPtr player, FloatRef x, FloatRef y, FloatRef z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.GetPos(player, x, y, z);
	API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z);
}

DECLARE_API(Player, GetVirtualWorld, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetVirtualWorld(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, IsNPC, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.IsNPC(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, IsStreamedIn, objectPtr player, objectPtr other)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.IsStreamedIn(player, other);
	API_RETURN(bool ret);
}

DECLARE_API(Player, PlayGameSound, objectPtr player, int sound, float x, float y, float z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.PlayGameSound(player, sound, x, y, z);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SpectatePlayer, objectPtr player, objectPtr target, int mode)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SpectatePlayer(player, target, mode);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SpectateVehicle, objectPtr player, objectPtr target, int mode)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SpectateVehicle(player, target, mode);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SetVirtualWorld, objectPtr player, int vw)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetVirtualWorld(player, vw);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SetWorldBounds, objectPtr player, float xMax, float xMin, float yMax, float yMin)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetWorldBounds(player, xMax, xMin, yMax, yMin);
	API_RETURN(bool ret);
}

DECLARE_API(Player, ClearWorldBounds, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.ClearWorldBounds(player);
	API_RETURN(bool ret);
}

DECLARE_API_ARGNUM(Player, GetWorldBounds, 1, objectPtr player, FloatRef xmax, FloatRef xmin, FloatRef ymax, FloatRef ymin)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.GetWorldBounds(player, xmax, xmin, ymax, ymin);
	API_RETURN(bool ret, FloatRef xmax, FloatRef xmin, FloatRef ymax, FloatRef ymin);
}

DECLARE_API(Player, ClearAnimations, objectPtr player, int syncType)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.ClearAnimations(player, syncType);
	API_RETURN(bool ret);
}

DECLARE_API_ARGNUM(Player, GetLastShotVectors, 1, objectPtr player, FloatRef origin_x, FloatRef origin_y, FloatRef origin_z, FloatRef hit_x, FloatRef hit_y, FloatRef hit_z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.GetLastShotVectors(player, origin_x, origin_y, origin_z, hit_x, hit_y, hit_z);
	API_RETURN(bool ret, FloatRef origin_x, FloatRef origin_y, FloatRef origin_z, FloatRef hit_x, FloatRef hit_y, FloatRef hit_z);
}

DECLARE_API(Player, GetCameraTargetPlayer, objectPtr player)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Player.GetCameraTargetPlayer(player);
	API_RETURN(objectPtr ret);
}

DECLARE_API(Player, GetCameraTargetActor, objectPtr player)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Player.GetCameraTargetActor(player);
	API_RETURN(objectPtr ret);
}

DECLARE_API(Player, GetCameraTargetObject, objectPtr player)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Player.GetCameraTargetObject(player);
	API_RETURN(objectPtr ret);
}

DECLARE_API(Player, GetCameraTargetVehicle, objectPtr player)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Player.GetCameraTargetVehicle(player);
	API_RETURN(objectPtr ret);
}

DECLARE_API(Player, PutInVehicle, objectPtr player, objectPtr vehicle, int seat)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.PutInVehicle(player, vehicle, seat);
	API_RETURN(bool ret);
}

DECLARE_API(Player, RemoveBuilding, objectPtr player, int model, float x, float y, float z, float radius)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.RemoveBuilding(player, model, x, y, z, radius);
	API_RETURN(bool ret);
}

DECLARE_API(Player, GetBuildingsRemoved, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetBuildingsRemoved(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, RemoveFromVehicle, objectPtr player, bool force)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.RemoveFromVehicle(player, force);
	API_RETURN(bool ret);
}

DECLARE_API(Player, RemoveMapIcon, objectPtr player, int icon)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.RemoveMapIcon(player, icon);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SetMapIcon, objectPtr player, int iconID, float x, float y, float z, int type, uint32_t color, int style)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetMapIcon(player, iconID, x, y, z, type, color, style);
	API_RETURN(bool ret);
}

DECLARE_API(Player, ResetWeapons, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.ResetWeapons(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SetAmmo, objectPtr player, uint8_t id, uint32_t ammo)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetAmmo(player, id, ammo);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SetArmedWeapon, objectPtr player, uint8_t weapon)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetArmedWeapon(player, weapon);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SetChatBubble, objectPtr player, StringCharPtr text, uint32_t color, float drawdistance, int expiretime)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetChatBubble(player, text, color, drawdistance, expiretime);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SetPosFindZ, objectPtr player, float x, float y, float z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetPosFindZ(player, x, y, z);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SetSkillLevel, objectPtr player, uint8_t weapon, int level)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetSkillLevel(player, weapon, level);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SetSpecialAction, objectPtr player, uint32_t action)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetSpecialAction(player, action);
	API_RETURN(bool ret);
}

DECLARE_API(Player, ShowNameTagForPlayer, objectPtr player, objectPtr other, bool enable)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.ShowNameTagForPlayer(player, other, enable);
	API_RETURN(bool ret);
}

DECLARE_API(Player, ToggleControllable, objectPtr player, bool enable)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.ToggleControllable(player, enable);
	API_RETURN(bool ret);
}

DECLARE_API(Player, ToggleSpectating, objectPtr player, bool enable)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.ToggleSpectating(player, enable);
	API_RETURN(bool ret);
}

DECLARE_API(Player, ApplyAnimation, objectPtr player, StringCharPtr animlib, StringCharPtr animname, float delta, bool loop, bool lockX, bool lockY, bool freeze, uint32_t time, int sync)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.ApplyAnimation(player, animlib, animname, delta, loop, lockX, lockY, freeze, time, sync);
	API_RETURN(bool ret);
}

DECLARE_API_ARGNUM(Player, GetAnimationName, 1, int index, OutputStringViewPtr lib, OutputStringViewPtr name)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.GetAnimationName(index, lib, name);
	API_RETURN(bool ret, OutputStringViewPtr lib, OutputStringViewPtr name);
}

DECLARE_API(Player, EditAttachedObject, objectPtr player, int index)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.EditAttachedObject(player, index);
	API_RETURN(bool ret);
}

DECLARE_API(Player, EnableCameraTarget, objectPtr player, bool enable)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.EnableCameraTarget(player, enable);
	API_RETURN(bool ret);
}

DECLARE_API(Player, EnableStuntBonus, objectPtr player, bool enable)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.EnableStuntBonus(player, enable);
	API_RETURN(bool ret);
}

DECLARE_API(Player, GetPlayerAmmo, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetPlayerAmmo(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, GetAnimationIndex, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetAnimationIndex(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, GetFacingAngle, objectPtr player)
{
	float ret = Runtime::Instance().GetOMPAPI()->Player.GetFacingAngle(player);
	API_RETURN(float ret);
}

DECLARE_API(Player, GetIp, objectPtr player)
{
	CREATE_CAPI_STRING_VIEW(output, 30);
	bool ret = Runtime::Instance().GetOMPAPI()->Player.GetIp(player, output);
	COPY_AND_FREE_CAPI_STRING_VIEW(output);
	API_RETURN(int ret, OutputStringViewPtr output);
}

DECLARE_API(Player, GetSpecialAction, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetSpecialAction(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, GetVehicleID, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetVehicleID(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, GetVehicleSeat, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetVehicleSeat(player);
	API_RETURN(int ret);
}

DECLARE_API_ARGNUM(Player, GetWeaponData, 2, objectPtr player, int slot, IntRef weaponid, IntRef ammo)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.GetWeaponData(player, slot, weaponid, ammo);
	API_RETURN(bool ret, IntRef weaponid, IntRef ammo);
}

DECLARE_API(Player, GetWeaponState, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetWeaponState(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, InterpolateCameraPos, objectPtr player, float from_x, float from_y, float from_z, float to_x, float to_y, float to_z, int time, int cut)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.InterpolateCameraPos(player, from_x, from_y, from_z, to_x, to_y, to_z, time, cut);
	API_RETURN(bool ret);
}

DECLARE_API(Player, InterpolateCameraLookAt, objectPtr player, float from_x, float from_y, float from_z, float to_x, float to_y, float to_z, int time, int cut)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.InterpolateCameraLookAt(player, from_x, from_y, from_z, to_x, to_y, to_z, time, cut);
	API_RETURN(bool ret);
}

DECLARE_API(Player, IsPlayerAttachedObjectSlotUsed, objectPtr player, int index)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.IsPlayerAttachedObjectSlotUsed(player, index);
	API_RETURN(bool ret);
}

DECLARE_API(Player, AttachCameraToObject, objectPtr player, objectPtr object)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.AttachCameraToObject(player, object);
	API_RETURN(bool ret);
}

DECLARE_API(Player, AttachCameraToPlayerObject, objectPtr player, objectPtr object)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.AttachCameraToPlayerObject(player, object);
	API_RETURN(bool ret);
}

DECLARE_API(Player, GetCameraAspectRatio, objectPtr player)
{
	float ret = Runtime::Instance().GetOMPAPI()->Player.GetCameraAspectRatio(player);
	API_RETURN(float ret);
}

DECLARE_API_ARGNUM(Player, GetCameraFrontVector, 1, objectPtr player, FloatRef x, FloatRef y, FloatRef z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.GetCameraFrontVector(player, x, y, z);
	API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z);
}

DECLARE_API(Player, GetCameraMode, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetCameraMode(player);
	API_RETURN(int ret);
}

DECLARE_API_ARGNUM(Player, GetKeys, 1, objectPtr player, IntRef keys, IntRef updown, IntRef leftright)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.GetKeys(player, keys, updown, leftright);
	API_RETURN(bool ret, IntRef keys, IntRef updown, IntRef leftright);
}

DECLARE_API(Player, GetSurfingVehicle, objectPtr player)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Player.GetSurfingVehicle(player);
	API_RETURN(objectPtr ret);
}

DECLARE_API(Player, GetSurfingObject, objectPtr player)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Player.GetSurfingObject(player);
	API_RETURN(objectPtr ret);
}

DECLARE_API(Player, GetTargetPlayer, objectPtr player)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Player.GetTargetPlayer(player);
	API_RETURN(objectPtr ret);
}

DECLARE_API(Player, GetTargetActor, objectPtr player)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Player.GetTargetActor(player);
	API_RETURN(objectPtr ret);
}

DECLARE_API(Player, IsInVehicle, objectPtr player, objectPtr targetVehicle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.IsInVehicle(player, targetVehicle);
	API_RETURN(bool ret);
}

DECLARE_API(Player, IsInAnyVehicle, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.IsInAnyVehicle(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, IsInRangeOfPoint, objectPtr player, float range, float x, float y, float z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.IsInRangeOfPoint(player, range, x, y, z);
	API_RETURN(bool ret);
}

DECLARE_API(Player, PlayCrimeReport, objectPtr player, objectPtr suspect, int crime)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.PlayCrimeReport(player, suspect, crime);
	API_RETURN(bool ret);
}

DECLARE_API(Player, RemoveAttachedObject, objectPtr player, int index)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.RemoveAttachedObject(player, index);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SetAttachedObject, objectPtr player, int index, int modelid, int bone, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ, float scaleX, float scaleY, float scaleZ, uint32_t materialcolor1, uint32_t materialcolor2)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetAttachedObject(player, index, modelid, bone, offsetX, offsetY, offsetZ, rotationX, rotationY, rotationZ, scaleX, scaleY, scaleZ, materialcolor1, materialcolor2);
	API_RETURN(bool ret);
}

DECLARE_API_ARGNUM(Player, GetAttachedObject, 2, objectPtr player, int index, IntRef modelid, IntRef bone, FloatRef offsetX, FloatRef offsetY, FloatRef offsetZ, FloatRef rotationX, FloatRef rotationY, FloatRef rotationZ, FloatRef scaleX, FloatRef scaleY, FloatRef scaleZ, IntRef materialcolor1, IntRef materialcolor2)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.GetAttachedObject(player, index, modelid, bone, offsetX, offsetY, offsetZ, rotationX, rotationY, rotationZ, scaleX, scaleY, scaleZ, materialcolor1, materialcolor2);
	API_RETURN(bool ret, IntRef modelid, IntRef bone, FloatRef offsetX, FloatRef offsetY, FloatRef offsetZ, FloatRef rotationX, FloatRef rotationY, FloatRef rotationZ, FloatRef scaleX, FloatRef scaleY, FloatRef scaleZ, IntRef materialcolor1, IntRef materialcolor2);
}

DECLARE_API(Player, SetFacingAngle, objectPtr player, float angle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetFacingAngle(player, angle);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SetMarkerForPlayer, objectPtr player, objectPtr other, uint32_t color)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetMarkerForPlayer(player, other, color);
	API_RETURN(bool ret);
}

DECLARE_API(Player, GetMarkerForPlayer, objectPtr player, objectPtr other)
{
	uint32_t ret = Runtime::Instance().GetOMPAPI()->Player.GetMarkerForPlayer(player, other);
	API_RETURN(uint32_t ret);
}

DECLARE_API(Player, AllowTeleport, objectPtr player, bool allow)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.AllowTeleport(player, allow);
	API_RETURN(bool ret);
}

DECLARE_API(Player, IsTeleportAllowed, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.IsTeleportAllowed(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, DisableRemoteVehicleCollisions, objectPtr player, bool disable)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.DisableRemoteVehicleCollisions(player, disable);
	API_RETURN(bool ret);
}

DECLARE_API(Player, GetCameraZoom, objectPtr player)
{
	float ret = Runtime::Instance().GetOMPAPI()->Player.GetCameraZoom(player);
	API_RETURN(float ret);
}

DECLARE_API(Player, SelectTextDraw, objectPtr player, uint32_t hoverColour)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SelectTextDraw(player, hoverColour);
	API_RETURN(bool ret);
}

DECLARE_API(Player, CancelSelectTextDraw, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.CancelSelectTextDraw(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SendClientCheck, objectPtr player, int actionType, int address, int offset, int count)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SendClientCheck(player, actionType, address, offset, count);
	API_RETURN(bool ret);
}

DECLARE_API(Player, Spawn, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.Spawn(player);
	API_RETURN(bool ret);
}

DECLARE_API_ARGNUM(Player, GPCI, 1, objectPtr player, OutputStringViewPtr gpci)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.GPCI(player, gpci);
	API_RETURN(bool ret, OutputStringViewPtr gpci);
}

DECLARE_API(Player, IsAdmin, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.IsAdmin(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, Kick, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.Kick(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, ShowGameText, objectPtr player, StringCharPtr text, int time, int style)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.ShowGameText(player, text, time, style);
	API_RETURN(bool ret);
}

DECLARE_API(Player, HideGameText, objectPtr player, int style)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.HideGameText(player, style);
	API_RETURN(bool ret);
}

DECLARE_API(Player, HasGameText, objectPtr player, int style)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.HasGameText(player, style);
	API_RETURN(bool ret);
}

DECLARE_API_ARGNUM(Player, GetGameText, 2, objectPtr player, int style, OutputStringViewPtr message, IntRef time, IntRef remaining)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.GetGameText(player, style, message, time, remaining);
	API_RETURN(bool ret, OutputStringViewPtr message, IntRef time, IntRef remaining);
}

DECLARE_API(Player, Ban, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.Ban(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, BanEx, objectPtr player, StringCharPtr reason)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.BanEx(player, reason);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SendDeathMessage, objectPtr player, objectPtr killer, objectPtr killee, int weapon)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SendDeathMessage(player, killer, killee, weapon);
	API_RETURN(bool ret);
}

DECLARE_API(Player, SendMessageToPlayer, objectPtr player, objectPtr sender, StringCharPtr message)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SendMessageToPlayer(player, sender, message);
	API_RETURN(bool ret);
}

DECLARE_API_ARGNUM(Player, GetVersion, 1, objectPtr player, OutputStringViewPtr version)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetVersion(player, version);
	API_RETURN(int ret, OutputStringViewPtr version);
}

DECLARE_API(Player, GetSkillLevel, objectPtr player, int skill)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetSkillLevel(player, skill);
	API_RETURN(int ret);
}

DECLARE_API(Player, GetZAim, objectPtr player)
{
	float ret = Runtime::Instance().GetOMPAPI()->Player.GetZAim(player);
	API_RETURN(float ret);
}

DECLARE_API_ARGNUM(Player, GetSurfingOffsets, 1, objectPtr player, FloatRef offsetX, FloatRef offsetY, FloatRef offsetZ)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.GetSurfingOffsets(player, offsetX, offsetY, offsetZ);
	API_RETURN(bool ret, FloatRef offsetX, FloatRef offsetY, FloatRef offsetZ);
}

DECLARE_API_ARGNUM(Player, GetRotationQuat, 1, objectPtr player, FloatRef x, FloatRef y, FloatRef z, FloatRef w)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.GetRotationQuat(player, x, y, z, w);
	API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z, FloatRef w);
}

DECLARE_API(Player, GetPlayerSpectateID, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetPlayerSpectateID(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, GetSpectateType, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetSpectateType(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, GetRawIp, objectPtr player)
{
	uint32_t ret = Runtime::Instance().GetOMPAPI()->Player.GetRawIp(player);
	API_RETURN(uint32_t ret);
}

DECLARE_API(Player, SetGravity, objectPtr player, float gravity)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetGravity(player, gravity);
	API_RETURN(bool ret);
}

DECLARE_API(Player, GetGravity, objectPtr player)
{
	float ret = Runtime::Instance().GetOMPAPI()->Player.GetGravity(player);
	API_RETURN(float ret);
}

DECLARE_API(Player, SetAdmin, objectPtr player, bool set)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.SetAdmin(player, set);
	API_RETURN(bool ret);
}

DECLARE_API(Player, IsSpawned, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.IsSpawned(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, IsControllable, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.IsControllable(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, IsCameraTargetEnabled, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.IsCameraTargetEnabled(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, ToggleGhostMode, objectPtr player, bool toggle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.ToggleGhostMode(player, toggle);
	API_RETURN(bool ret);
}

DECLARE_API(Player, GetGhostMode, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.GetGhostMode(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, AllowWeapons, objectPtr player, bool allow)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.AllowWeapons(player, allow);
	API_RETURN(bool ret);
}

DECLARE_API(Player, AreWeaponsAllowed, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.AreWeaponsAllowed(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, IsPlayerUsingOfficialClient, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.IsPlayerUsingOfficialClient(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, GetAnimationFlags, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetAnimationFlags(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, IsInDriveByMode, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.IsInDriveByMode(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, IsCuffed, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.IsCuffed(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, IsInModShop, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Player.IsInModShop(player);
	API_RETURN(bool ret);
}

DECLARE_API(Player, GetSirenState, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetSirenState(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, GetLandingGearState, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->Player.GetLandingGearState(player);
	API_RETURN(int ret);
}

DECLARE_API(Player, GetHydraReactorAngle, objectPtr player)
{
	uint32_t ret = Runtime::Instance().GetOMPAPI()->Player.GetHydraReactorAngle(player);
	API_RETURN(uint32_t ret);
}

DECLARE_API(Player, GetTrainSpeed, objectPtr player)
{
	float ret = Runtime::Instance().GetOMPAPI()->Player.GetTrainSpeed(player);
	API_RETURN(float ret);
}
