#include "../Impl.hpp"
#include "../MacroMagic.hpp"

DECLARE_API(PlayerTextLabel, Create, objectPtr player, StringCharPtr text, uint32_t color, float x, float y, float z, float drawDistance, objectPtr attachedPlayer, objectPtr attachedVehicle, bool los, IntRef id)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->PlayerTextLabel.Create(player, text, color, x, y, z, drawDistance, attachedPlayer, attachedVehicle, los, id);
	API_RETURN(objectPtr ret, IntRef id);
}

DECLARE_API(PlayerTextLabel, Destroy, objectPtr player, objectPtr textlabel)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextLabel.Destroy(player, textlabel);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextLabel, FromID, objectPtr player, int textlabelid)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->PlayerTextLabel.FromID(player, textlabelid);
	API_RETURN(objectPtr ret);
}

DECLARE_API(PlayerTextLabel, GetID, objectPtr player, objectPtr textlabel)
{
	int ret = Runtime::Instance().GetOMPAPI()->PlayerTextLabel.GetID(player, textlabel);
	API_RETURN(int ret);
}

DECLARE_API(PlayerTextLabel, UpdateText, objectPtr player, objectPtr textlabel, uint32_t color, StringCharPtr text)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextLabel.UpdateText(player, textlabel, color, text);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextLabel, IsValid, objectPtr player, objectPtr textlabel, BoolRef valid)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextLabel.IsValid(player, textlabel, valid);
	API_RETURN(bool ret, BoolRef valid);
}

DECLARE_API(PlayerTextLabel, GetText, objectPtr player, objectPtr textlabel, OutputStringViewPtr output)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextLabel.GetText(player, textlabel, output);
	API_RETURN(bool ret, OutputStringViewPtr output);
}

DECLARE_API(PlayerTextLabel, GetColor, objectPtr player, objectPtr textlabel, UInt32Ref color)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextLabel.GetColor(player, textlabel, color);
	API_RETURN(bool ret, UInt32Ref color);
}

DECLARE_API(PlayerTextLabel, GetPos, objectPtr player, objectPtr textlabel, FloatRef x, FloatRef y, FloatRef z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextLabel.GetPos(player, textlabel, x, y, z);
	API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z);
}

DECLARE_API(PlayerTextLabel, SetDrawDistance, objectPtr player, objectPtr textlabel, float distance)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextLabel.SetDrawDistance(player, textlabel, distance);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextLabel, GetDrawDistance, objectPtr player, objectPtr textlabel)
{
	float ret = Runtime::Instance().GetOMPAPI()->PlayerTextLabel.GetDrawDistance(player, textlabel);
	API_RETURN(float ret);
}

DECLARE_API(PlayerTextLabel, GetLOS, objectPtr player, objectPtr textlabel)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextLabel.GetLOS(player, textlabel);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextLabel, SetLOS, objectPtr player, objectPtr textlabel, bool status)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextLabel.SetLOS(player, textlabel, status);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextLabel, GetVirtualWorld, objectPtr player)
{
	int ret = Runtime::Instance().GetOMPAPI()->PlayerTextLabel.GetVirtualWorld(player);
	API_RETURN(int ret);
}

DECLARE_API(PlayerTextLabel, GetAttachedData, objectPtr player, objectPtr textlabel, IntRef attached_player, IntRef attached_vehicle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextLabel.GetAttachedData(player, textlabel, attached_player, attached_vehicle);
	API_RETURN(bool ret, IntRef attached_player, IntRef attached_vehicle);
}
