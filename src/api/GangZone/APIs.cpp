#include "../Impl.hpp"
#include "../MacroMagic.hpp"

DECLARE_API(GangZone, Create, float minx, float miny, float maxx, float maxy, IntRef id)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->GangZone.Create(minx, miny, maxx, maxy, id);
	API_RETURN(objectPtr ret, IntRef id);
}

DECLARE_API(GangZone, Destroy, objectPtr gangzone)
{
	bool ret = Runtime::Instance().GetOMPAPI()->GangZone.Destroy(gangzone);
	API_RETURN(bool ret);
}

DECLARE_API(GangZone, FromID, int gangzoneid)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->GangZone.FromID(gangzoneid);
	API_RETURN(objectPtr ret);
}

DECLARE_API(GangZone, GetID, objectPtr gangzone)
{
	int ret = Runtime::Instance().GetOMPAPI()->GangZone.GetID(gangzone);
	API_RETURN(int ret);
}

DECLARE_API(GangZone, ShowForPlayer, objectPtr player, objectPtr gangzone, uint32_t color)
{
	bool ret = Runtime::Instance().GetOMPAPI()->GangZone.ShowForPlayer(player, gangzone, color);
	API_RETURN(bool ret);
}

DECLARE_API(GangZone, ShowForAll, objectPtr gangzone, uint32_t color)
{
	bool ret = Runtime::Instance().GetOMPAPI()->GangZone.ShowForAll(gangzone, color);
	API_RETURN(bool ret);
}

DECLARE_API(GangZone, HideForPlayer, objectPtr player, objectPtr gangzone)
{
	bool ret = Runtime::Instance().GetOMPAPI()->GangZone.HideForPlayer(player, gangzone);
	API_RETURN(bool ret);
}

DECLARE_API(GangZone, HideForAll, objectPtr gangzone)
{
	bool ret = Runtime::Instance().GetOMPAPI()->GangZone.HideForAll(gangzone);
	API_RETURN(bool ret);
}

DECLARE_API(GangZone, FlashForPlayer, objectPtr player, objectPtr gangzone, uint32_t color)
{
	bool ret = Runtime::Instance().GetOMPAPI()->GangZone.FlashForPlayer(player, gangzone, color);
	API_RETURN(bool ret);
}

DECLARE_API(GangZone, FlashForAll, objectPtr gangzone, uint32_t color)
{
	bool ret = Runtime::Instance().GetOMPAPI()->GangZone.FlashForAll(gangzone, color);
	API_RETURN(bool ret);
}

DECLARE_API(GangZone, StopFlashForPlayer, objectPtr player, objectPtr gangzone)
{
	bool ret = Runtime::Instance().GetOMPAPI()->GangZone.StopFlashForPlayer(player, gangzone);
	API_RETURN(bool ret);
}

DECLARE_API(GangZone, StopFlashForAll, objectPtr gangzone)
{
	bool ret = Runtime::Instance().GetOMPAPI()->GangZone.StopFlashForAll(gangzone);
	API_RETURN(bool ret);
}

DECLARE_API(GangZone, IsValid, objectPtr gangzone)
{
	bool ret = Runtime::Instance().GetOMPAPI()->GangZone.IsValid(gangzone);
	API_RETURN(bool ret);
}

DECLARE_API(GangZone, IsPlayerIn, objectPtr player, objectPtr gangzone)
{
	bool ret = Runtime::Instance().GetOMPAPI()->GangZone.IsPlayerIn(player, gangzone);
	API_RETURN(bool ret);
}

DECLARE_API(GangZone, IsVisibleForPlayer, objectPtr player, objectPtr gangzone)
{
	bool ret = Runtime::Instance().GetOMPAPI()->GangZone.IsVisibleForPlayer(player, gangzone);
	API_RETURN(bool ret);
}

DECLARE_API(GangZone, GetColorForPlayer, objectPtr player, objectPtr gangzone)
{
	int ret = Runtime::Instance().GetOMPAPI()->GangZone.GetColorForPlayer(player, gangzone);
	API_RETURN(int ret);
}

DECLARE_API(GangZone, GetFlashColorForPlayer, objectPtr player, objectPtr gangzone)
{
	int ret = Runtime::Instance().GetOMPAPI()->GangZone.GetFlashColorForPlayer(player, gangzone);
	API_RETURN(int ret);
}

DECLARE_API(GangZone, IsFlashingForPlayer, objectPtr player, objectPtr gangzone)
{
	bool ret = Runtime::Instance().GetOMPAPI()->GangZone.IsFlashingForPlayer(player, gangzone);
	API_RETURN(bool ret);
}

DECLARE_API(GangZone, GetPos, objectPtr gangzone, FloatRef minx, FloatRef miny, FloatRef maxx, FloatRef maxy)
{
	bool ret = Runtime::Instance().GetOMPAPI()->GangZone.GetPos(gangzone, minx, miny, maxx, maxy);
	API_RETURN(bool ret, FloatRef minx, FloatRef miny, FloatRef maxx, FloatRef maxy);
}

DECLARE_API(GangZone, UseCheck, objectPtr gangzone, bool enable)
{
	bool ret = Runtime::Instance().GetOMPAPI()->GangZone.UseCheck(gangzone, enable);
	API_RETURN(bool ret);
}
