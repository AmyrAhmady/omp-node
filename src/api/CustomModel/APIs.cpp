#include "../Impl.hpp"
#include "../MacroMagic.hpp"

DECLARE_API(CustomModel, AddCharModel, int baseid, int newid, StringCharPtr dff, StringCharPtr textureLibrary)
{
	bool ret = Runtime::Instance().GetOMPAPI()->CustomModel.AddCharModel(baseid, newid, dff, textureLibrary);
	API_RETURN(bool ret);
}

DECLARE_API(CustomModel, AddSimpleModel, int virtualWorld, int baseid, int newid, StringCharPtr dff, StringCharPtr textureLibrary)
{
	bool ret = Runtime::Instance().GetOMPAPI()->CustomModel.AddSimpleModel(virtualWorld, baseid, newid, dff, textureLibrary);
	API_RETURN(bool ret);
}

DECLARE_API(CustomModel, AddSimpleModelTimed, int virtualWorld, int baseid, int newid, StringCharPtr dff, StringCharPtr textureLibrary, int timeOn, int timeOff)
{
	bool ret = Runtime::Instance().GetOMPAPI()->CustomModel.AddSimpleModelTimed(virtualWorld, baseid, newid, dff, textureLibrary, timeOn, timeOff);
	API_RETURN(bool ret);
}

DECLARE_API(CustomModel, RedirectDownload, objectPtr player, StringCharPtr url)
{
	bool ret = Runtime::Instance().GetOMPAPI()->CustomModel.RedirectDownload(player, url);
	API_RETURN(bool ret);
}

DECLARE_API(CustomModel, FindModelFileNameFromCRC, int crc, OutputStringViewPtr output)
{
	int ret = Runtime::Instance().GetOMPAPI()->CustomModel.FindModelFileNameFromCRC(crc, output);
	API_RETURN(int ret, OutputStringViewPtr output);
}

DECLARE_API(CustomModel, IsValid, int modelId)
{
	bool ret = Runtime::Instance().GetOMPAPI()->CustomModel.IsValid(modelId);
	API_RETURN(bool ret);
}

DECLARE_API(CustomModel, GetPath, int modelId, OutputStringViewPtr dffPath, OutputStringViewPtr txdPath)
{
	bool ret = Runtime::Instance().GetOMPAPI()->CustomModel.GetPath(modelId, dffPath, txdPath);
	API_RETURN(bool ret, OutputStringViewPtr dffPath, OutputStringViewPtr txdPath);
}
