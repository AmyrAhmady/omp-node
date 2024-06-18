#include "../Impl.hpp"
#include "../MacroMagic.hpp"

DECLARE_API(RaceCheckpoint, Set, objectPtr player, int type, float x, float y, float z, float nextX, float nextY, float nextZ, float radius)
{
	bool ret = Runtime::Instance().GetOMPAPI()->RaceCheckpoint.Set(player, type, x, y, z, nextX, nextY, nextZ, radius);
	API_RETURN(bool ret);
}

DECLARE_API(RaceCheckpoint, Disable, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->RaceCheckpoint.Disable(player);
	API_RETURN(bool ret);
}

DECLARE_API(RaceCheckpoint, IsPlayerIn, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->RaceCheckpoint.IsPlayerIn(player);
	API_RETURN(bool ret);
}

DECLARE_API(RaceCheckpoint, IsActive, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->RaceCheckpoint.IsActive(player);
	API_RETURN(bool ret);
}

DECLARE_API(RaceCheckpoint, Get, objectPtr player, FloatRef x, FloatRef y, FloatRef z, FloatRef nextX, FloatRef nextY, FloatRef nextZ, FloatRef radius)
{
	bool ret = Runtime::Instance().GetOMPAPI()->RaceCheckpoint.Get(player, x, y, z, nextX, nextY, nextZ, radius);
	API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z, FloatRef nextX, FloatRef nextY, FloatRef nextZ, FloatRef radius);
}
