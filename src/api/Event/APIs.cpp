#include "../Impl.hpp"
#include "../MacroMagic.hpp"

DECLARE_API(Event, AddHandler, StringCharPtr name, int priority, objectPtr callback)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Event.AddHandler(name, priority, callback);
	API_RETURN(bool ret);
}

DECLARE_API(Event, RemoveHandler, StringCharPtr name, int priority, objectPtr callback)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Event.RemoveHandler(name, priority, callback);
	API_RETURN(bool ret);
}

DECLARE_API(Event, RemoveAllHandlers, StringCharPtr name, int priority)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Event.RemoveAllHandlers(name, priority);
	API_RETURN(bool ret);
}
