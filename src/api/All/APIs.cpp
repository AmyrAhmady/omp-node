#include "../Impl.hpp"
#include "../API.hpp"

DECLARE_API(All, SendClientMessage, uint32_t color, StringCharPtr text)
{
	bool ret = Runtime::Instance().GetOMPAPI()->All.SendClientMessage(color, text);
	API_RETURN(bool ret);
}

DECLARE_API(All, CreateExplosion, float x, float y, float z, int type, float radius)
{
	bool ret = Runtime::Instance().GetOMPAPI()->All.CreateExplosion(x, y, z, type, radius);
	API_RETURN(bool ret);
}

DECLARE_API(All, SendDeathMessage, objectPtr killer, objectPtr killee, int weapon)
{
	bool ret = Runtime::Instance().GetOMPAPI()->All.SendDeathMessage(killer, killee, weapon);
	API_RETURN(bool ret);
}

DECLARE_API(All, EnableStuntBonus, bool enable)
{
	bool ret = Runtime::Instance().GetOMPAPI()->All.EnableStuntBonus(enable);
	API_RETURN(bool ret);
}
