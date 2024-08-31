#include "../Impl.hpp"
#include "../API.hpp"

DECLARE_API(NPC, Connect, StringCharPtr name, StringCharPtr script)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.Connect(name, script);
	API_RETURN(bool ret);
}
