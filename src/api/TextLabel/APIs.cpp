#include "../Impl.hpp"
#include "../MacroMagic.hpp"

DECLARE_API(TextLabel, Create, StringCharPtr text, uint32_t color, float x, float y, float z, float drawDistance, int virtualWorld, bool los, IntRef id)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->TextLabel.Create(text, color, x, y, z, drawDistance, virtualWorld, los, id);
	API_RETURN(objectPtr ret, IntRef id);
}

DECLARE_API(TextLabel, Destroy, objectPtr textlabel)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextLabel.Destroy(textlabel);
	API_RETURN(bool ret);
}

DECLARE_API(TextLabel, FromID, int textlabelid)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->TextLabel.FromID(textlabelid);
	API_RETURN(objectPtr ret);
}

DECLARE_API(TextLabel, GetID, objectPtr textlabel)
{
	int ret = Runtime::Instance().GetOMPAPI()->TextLabel.GetID(textlabel);
	API_RETURN(int ret);
}

DECLARE_API(TextLabel, AttachToPlayer, objectPtr textlabel, objectPtr player, float offsetX, float offsetY, float offsetZ)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextLabel.AttachToPlayer(textlabel, player, offsetX, offsetY, offsetZ);
	API_RETURN(bool ret);
}

DECLARE_API(TextLabel, AttachToVehicle, objectPtr textlabel, objectPtr vehicle, float offsetX, float offsetY, float offsetZ)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextLabel.AttachToVehicle(textlabel, vehicle, offsetX, offsetY, offsetZ);
	API_RETURN(bool ret);
}

DECLARE_API(TextLabel, UpdateText, objectPtr textlabel, uint32_t color, StringCharPtr text)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextLabel.UpdateText(textlabel, color, text);
	API_RETURN(bool ret);
}

DECLARE_API(TextLabel, IsValid, objectPtr textlabel)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextLabel.IsValid(textlabel);
	API_RETURN(bool ret);
}

DECLARE_API(TextLabel, IsStreamedIn, objectPtr player, objectPtr textlabel)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextLabel.IsStreamedIn(player, textlabel);
	API_RETURN(bool ret);
}

DECLARE_API(TextLabel, GetText, objectPtr textlabel, OutputStringViewPtr output)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextLabel.GetText(textlabel, output);
	API_RETURN(bool ret, OutputStringViewPtr output);
}

DECLARE_API(TextLabel, GetColor, objectPtr textlabel)
{
	uint32_t ret = Runtime::Instance().GetOMPAPI()->TextLabel.GetColor(textlabel);
	API_RETURN(uint32_t ret);
}

DECLARE_API(TextLabel, GetPos, objectPtr textlabel, FloatRef x, FloatRef y, FloatRef z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextLabel.GetPos(textlabel, x, y, z);
	API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z);
}

DECLARE_API(TextLabel, SetDrawDistance, objectPtr textlabel, float distance)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextLabel.SetDrawDistance(textlabel, distance);
	API_RETURN(bool ret);
}

DECLARE_API(TextLabel, GetDrawDistance, objectPtr textlabel)
{
	float ret = Runtime::Instance().GetOMPAPI()->TextLabel.GetDrawDistance(textlabel);
	API_RETURN(float ret);
}

DECLARE_API(TextLabel, GetLOS, objectPtr textlabel)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextLabel.GetLOS(textlabel);
	API_RETURN(bool ret);
}

DECLARE_API(TextLabel, SetLOS, objectPtr textlabel, bool status)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextLabel.SetLOS(textlabel, status);
	API_RETURN(bool ret);
}

DECLARE_API(TextLabel, GetVirtualWorld, objectPtr textlabel)
{
	int ret = Runtime::Instance().GetOMPAPI()->TextLabel.GetVirtualWorld(textlabel);
	API_RETURN(int ret);
}

DECLARE_API(TextLabel, SetVirtualWorld, objectPtr textlabel, int world)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextLabel.SetVirtualWorld(textlabel, world);
	API_RETURN(bool ret);
}

DECLARE_API(TextLabel, GetAttachedData, objectPtr textlabel, IntRef attached_player, IntRef attached_vehicle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextLabel.GetAttachedData(textlabel, attached_player, attached_vehicle);
	API_RETURN(bool ret, IntRef attached_player, IntRef attached_vehicle);
}
