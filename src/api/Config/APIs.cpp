#include "../Impl.hpp"
#include "../API.hpp"

DECLARE_API(Config, GetAsBool, StringCharPtr cvar)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Config.GetAsBool(cvar);
	API_RETURN(bool ret);
}

DECLARE_API(Config, GetAsInt, StringCharPtr cvar)
{
	int ret = Runtime::Instance().GetOMPAPI()->Config.GetAsInt(cvar);
	API_RETURN(int ret);
}

DECLARE_API(Config, GetAsFloat, StringCharPtr cvar)
{
	float ret = Runtime::Instance().GetOMPAPI()->Config.GetAsFloat(cvar);
	API_RETURN(float ret);
}

DECLARE_API(Config, GetAsString, StringCharPtr cvar)
{
	CREATE_CAPI_STRING_VIEW(output, 256);
	int ret = Runtime::Instance().GetOMPAPI()->Config.GetAsString(cvar, output);
	COPY_AND_FREE_CAPI_STRING_VIEW(output);
	API_RETURN(int ret, OutputStringViewPtr output);
}
