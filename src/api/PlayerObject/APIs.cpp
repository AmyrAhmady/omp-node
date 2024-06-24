#include "../Impl.hpp"
#include "../MacroMagic.hpp"

DECLARE_API(PlayerObject, Create, objectPtr player, int modelid, float x, float y, float z, float rotationX, float rotationY, float rotationZ, float drawDistance, IntRef id)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->PlayerObject.Create(player, modelid, x, y, z, rotationX, rotationY, rotationZ, drawDistance, id);
	API_RETURN(objectPtr ret, IntRef id);
}

DECLARE_API(PlayerObject, Destroy, objectPtr player, objectPtr object)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.Destroy(player, object);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerObject, AttachToVehicle, objectPtr player, objectPtr object, objectPtr vehicle, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.AttachToVehicle(player, object, vehicle, offsetX, offsetY, offsetZ, rotationX, rotationY, rotationZ);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerObject, AttachToPlayer, objectPtr player, objectPtr object, objectPtr playerAttachedTo, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.AttachToPlayer(player, object, playerAttachedTo, offsetX, offsetY, offsetZ, rotationX, rotationY, rotationZ);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerObject, AttachToObject, objectPtr player, objectPtr object, objectPtr attachedTo, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.AttachToObject(player, object, attachedTo, offsetX, offsetY, offsetZ, rotationX, rotationY, rotationZ);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerObject, SetPos, objectPtr player, objectPtr object, float x, float y, float z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.SetPos(player, object, x, y, z);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerObject, GetPos, objectPtr player, objectPtr object, FloatRef x, FloatRef y, FloatRef z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.GetPos(player, object, x, y, z);
	API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z);
}

DECLARE_API(PlayerObject, SetRot, objectPtr player, objectPtr object, float rotationX, float rotationY, float rotationZ)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.SetRot(player, object, rotationX, rotationY, rotationZ);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerObject, GetRot, objectPtr player, objectPtr object, FloatRef rotationX, FloatRef rotationY, FloatRef rotationZ)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.GetRot(player, object, rotationX, rotationY, rotationZ);
	API_RETURN(bool ret, FloatRef rotationX, FloatRef rotationY, FloatRef rotationZ);
}

DECLARE_API(PlayerObject, GetModel, objectPtr player, objectPtr object)
{
	int ret = Runtime::Instance().GetOMPAPI()->PlayerObject.GetModel(player, object);
	API_RETURN(int ret);
}

DECLARE_API(PlayerObject, SetNoCameraCollision, objectPtr player, objectPtr object)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.SetNoCameraCollision(player, object);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerObject, IsValid, objectPtr player, objectPtr object)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.IsValid(player, object);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerObject, Move, objectPtr player, objectPtr object, float x, float y, float z, float speed, float rotationX, float rotationY, float rotationZ)
{
	int ret = Runtime::Instance().GetOMPAPI()->PlayerObject.Move(player, object, x, y, z, speed, rotationX, rotationY, rotationZ);
	API_RETURN(int ret);
}

DECLARE_API(PlayerObject, Stop, objectPtr player, objectPtr object)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.Stop(player, object);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerObject, IsMoving, objectPtr player, objectPtr object)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.IsMoving(player, object);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerObject, BeginEditing, objectPtr player, objectPtr object)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.BeginEditing(player, object);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerObject, SetMaterial, objectPtr player, objectPtr object, int materialIndex, int modelId, StringCharPtr textureLibrary, StringCharPtr textureName, uint32_t materialColor)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.SetMaterial(player, object, materialIndex, modelId, textureLibrary, textureName, materialColor);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerObject, SetMaterialText, objectPtr player, objectPtr object, StringCharPtr text, int materialIndex, int materialSize, StringCharPtr fontface, int fontsize, bool bold, uint32_t fontColor, uint32_t backgroundColor, int textalignment)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.SetMaterialText(player, object, text, materialIndex, materialSize, fontface, fontsize, bold, fontColor, backgroundColor, textalignment);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerObject, GetDrawDistance, objectPtr player, objectPtr object)
{
	float ret = Runtime::Instance().GetOMPAPI()->PlayerObject.GetDrawDistance(player, object);
	API_RETURN(float ret);
}

DECLARE_API(PlayerObject, GetMoveSpeed, objectPtr player, objectPtr object)
{
	float ret = Runtime::Instance().GetOMPAPI()->PlayerObject.GetMoveSpeed(player, object);
	API_RETURN(float ret);
}

DECLARE_API(PlayerObject, GetMovingTargetPos, objectPtr player, objectPtr object, FloatRef targetX, FloatRef targetY, FloatRef targetZ)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.GetMovingTargetPos(player, object, targetX, targetY, targetZ);
	API_RETURN(bool ret, FloatRef targetX, FloatRef targetY, FloatRef targetZ);
}

DECLARE_API(PlayerObject, GetMovingTargetRot, objectPtr player, objectPtr object, FloatRef rotationX, FloatRef rotationY, FloatRef rotationZ)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.GetMovingTargetRot(player, object, rotationX, rotationY, rotationZ);
	API_RETURN(bool ret, FloatRef rotationX, FloatRef rotationY, FloatRef rotationZ);
}

DECLARE_API(PlayerObject, GetAttachedData, objectPtr player, objectPtr object, IntRef parentVehicle, IntRef parentObject, IntRef parentPlayer)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.GetAttachedData(player, object, parentVehicle, parentObject, parentPlayer);
	API_RETURN(bool ret, IntRef parentVehicle, IntRef parentObject, IntRef parentPlayer);
}

DECLARE_API(PlayerObject, GetAttachedOffset, objectPtr player, objectPtr object, FloatRef offsetX, FloatRef offsetY, FloatRef offsetZ, FloatRef rotationX, FloatRef rotationY, FloatRef rotationZ)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.GetAttachedOffset(player, object, offsetX, offsetY, offsetZ, rotationX, rotationY, rotationZ);
	API_RETURN(bool ret, FloatRef offsetX, FloatRef offsetY, FloatRef offsetZ, FloatRef rotationX, FloatRef rotationY, FloatRef rotationZ);
}

DECLARE_API(PlayerObject, GetSyncRotation, objectPtr player, objectPtr object)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.GetSyncRotation(player, object);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerObject, IsMaterialSlotUsed, objectPtr player, objectPtr object, int materialIndex)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.IsMaterialSlotUsed(player, object, materialIndex);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerObject, GetMaterial, objectPtr player, objectPtr object, int materialIndex, IntRef modelid, OutputStringViewPtr textureLibrary, OutputStringViewPtr textureName, IntRef materialColor)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.GetMaterial(player, object, materialIndex, modelid, textureLibrary, textureName, materialColor);
	API_RETURN(bool ret, IntRef modelid, OutputStringViewPtr textureLibrary, OutputStringViewPtr textureName, IntRef materialColor);
}

DECLARE_API(PlayerObject, GetMaterialText, objectPtr player, objectPtr object, int materialIndex, OutputStringViewPtr text, IntRef materialSize, OutputStringViewPtr fontFace, IntRef fontSize, BoolRef bold, IntRef fontColor, IntRef backgroundColor, IntRef textAlignment)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.GetMaterialText(player, object, materialIndex, text, materialSize, fontFace, fontSize, bold, fontColor, backgroundColor, textAlignment);
	API_RETURN(bool ret, OutputStringViewPtr text, IntRef materialSize, OutputStringViewPtr fontFace, IntRef fontSize, BoolRef bold, IntRef fontColor, IntRef backgroundColor, IntRef textAlignment);
}

DECLARE_API(PlayerObject, IsNoCameraCollision, objectPtr player, objectPtr object)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerObject.IsNoCameraCollision(player, object);
	API_RETURN(bool ret);
}
