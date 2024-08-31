#include "../Impl.hpp"
#include "../API.hpp"

DECLARE_API(Recording, Start, objectPtr player, int type, StringCharPtr file)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Recording.Start(player, type, file);
	API_RETURN(bool ret);
}

DECLARE_API(Recording, Stop, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Recording.Stop(player);
	API_RETURN(bool ret);
}
