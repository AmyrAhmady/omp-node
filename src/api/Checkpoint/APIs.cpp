#include "../Impl.hpp"
#include "../MacroMagic.hpp"

DECLARE_API(Checkpoint, Set, objectPtr player, float x, float y, float z, float radius)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Checkpoint.Set(player, x, y, z, radius);
	API_RETURN(bool ret);
}

DECLARE_API(Checkpoint, Disable, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Checkpoint.Disable(player);
	API_RETURN(bool ret);
}

DECLARE_API(Checkpoint, IsPlayerIn, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Checkpoint.IsPlayerIn(player);
	API_RETURN(bool ret);
}

DECLARE_API(Checkpoint, IsActive, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Checkpoint.IsActive(player);
	API_RETURN(bool ret);
}

DECLARE_API_ARGNUM(Checkpoint, Get, 1, objectPtr player, FloatRef x, FloatRef y, FloatRef z, FloatRef radius)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Checkpoint.Get(player, x, y, z, radius);
	API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z, FloatRef radius);
}
