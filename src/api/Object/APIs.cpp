#include "../Impl.hpp"
#include "../MacroMagic.hpp"

DECLARE_API(Object, Create, int modelid, float x, float y, float z, float rotationX, float rotationY, float rotationZ, float drawDistance, IntRef id)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Object.Create(modelid, x, y, z, rotationX, rotationY, rotationZ, drawDistance, id);
	API_RETURN(objectPtr ret, IntRef id);
}

DECLARE_API(Object, Destroy, objectPtr object)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.Destroy(object);
	API_RETURN(bool ret);
}

DECLARE_API(Object, FromID, int objectid)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Object.FromID(objectid);
	API_RETURN(objectPtr ret);
}

DECLARE_API(Object, GetID, objectPtr object)
{
	int ret = Runtime::Instance().GetOMPAPI()->Object.GetID(object);
	API_RETURN(int ret);
}

DECLARE_API(Object, AttachToVehicle, objectPtr object, objectPtr vehicle, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.AttachToVehicle(object, vehicle, offsetX, offsetY, offsetZ, rotationX, rotationY, rotationZ);
	API_RETURN(bool ret);
}

DECLARE_API(Object, AttachToObject, objectPtr object, objectPtr objAttachedTo, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ, bool syncRotation)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.AttachToObject(object, objAttachedTo, offsetX, offsetY, offsetZ, rotationX, rotationY, rotationZ, syncRotation);
	API_RETURN(bool ret);
}

DECLARE_API(Object, AttachToPlayer, objectPtr object, objectPtr player, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.AttachToPlayer(object, player, offsetX, offsetY, offsetZ, rotationX, rotationY, rotationZ);
	API_RETURN(bool ret);
}

DECLARE_API(Object, SetPos, objectPtr object, float x, float y, float z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.SetPos(object, x, y, z);
	API_RETURN(bool ret);
}

DECLARE_API(Object, GetPos, objectPtr object, FloatRef x, FloatRef y, FloatRef z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.GetPos(object, x, y, z);
	API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z);
}

DECLARE_API(Object, SetRot, objectPtr object, float rotationX, float rotationY, float rotationZ)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.SetRot(object, rotationX, rotationY, rotationZ);
	API_RETURN(bool ret);
}

DECLARE_API(Object, GetRot, objectPtr object, FloatRef rotationX, FloatRef rotationY, FloatRef rotationZ)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.GetRot(object, rotationX, rotationY, rotationZ);
	API_RETURN(bool ret, FloatRef rotationX, FloatRef rotationY, FloatRef rotationZ);
}

DECLARE_API(Object, GetModel, objectPtr object)
{
	int ret = Runtime::Instance().GetOMPAPI()->Object.GetModel(object);
	API_RETURN(int ret);
}

DECLARE_API(Object, SetNoCameraCollision, objectPtr object)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.SetNoCameraCollision(object);
	API_RETURN(bool ret);
}

DECLARE_API(Object, IsValid, objectPtr object)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.IsValid(object);
	API_RETURN(bool ret);
}

DECLARE_API(Object, Move, objectPtr object, float x, float y, float z, float speed, float rotationX, float rotationY, float rotationZ)
{
	int ret = Runtime::Instance().GetOMPAPI()->Object.Move(object, x, y, z, speed, rotationX, rotationY, rotationZ);
	API_RETURN(int ret);
}

DECLARE_API(Object, Stop, objectPtr object)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.Stop(object);
	API_RETURN(bool ret);
}

DECLARE_API(Object, IsMoving, objectPtr object)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.IsMoving(object);
	API_RETURN(bool ret);
}

DECLARE_API(Object, BeginEditing, objectPtr player, objectPtr object)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.BeginEditing(player, object);
	API_RETURN(bool ret);
}

DECLARE_API(Object, BeginSelecting, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.BeginSelecting(player);
	API_RETURN(bool ret);
}

DECLARE_API(Object, EndEditing, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.EndEditing(player);
	API_RETURN(bool ret);
}

DECLARE_API(Object, SetMaterial, objectPtr object, int materialIndex, int modelId, StringCharPtr textureLibrary, StringCharPtr textureName, uint32_t materialColor)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.SetMaterial(object, materialIndex, modelId, textureLibrary, textureName, materialColor);
	API_RETURN(bool ret);
}

DECLARE_API(Object, SetMaterialText, objectPtr object, StringCharPtr text, int materialIndex, int materialSize, StringCharPtr fontface, int fontsize, bool bold, uint32_t fontColor, uint32_t backgroundColor, int textalignment)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.SetMaterialText(object, text, materialIndex, materialSize, fontface, fontsize, bold, fontColor, backgroundColor, textalignment);
	API_RETURN(bool ret);
}

DECLARE_API(Object, SetDefaultCameraCollision, bool disable)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.SetDefaultCameraCollision(disable);
	API_RETURN(bool ret);
}

DECLARE_API(Object, GetDrawDistance, objectPtr object)
{
	float ret = Runtime::Instance().GetOMPAPI()->Object.GetDrawDistance(object);
	API_RETURN(float ret);
}

DECLARE_API(Object, GetMoveSpeed, objectPtr object)
{
	float ret = Runtime::Instance().GetOMPAPI()->Object.GetMoveSpeed(object);
	API_RETURN(float ret);
}

DECLARE_API(Object, GetMovingTargetPos, objectPtr object, FloatRef targetX, FloatRef targetY, FloatRef targetZ)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.GetMovingTargetPos(object, targetX, targetY, targetZ);
	API_RETURN(bool ret, FloatRef targetX, FloatRef targetY, FloatRef targetZ);
}

DECLARE_API(Object, GetMovingTargetRot, objectPtr object, FloatRef rotationX, FloatRef rotationY, FloatRef rotationZ)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.GetMovingTargetRot(object, rotationX, rotationY, rotationZ);
	API_RETURN(bool ret, FloatRef rotationX, FloatRef rotationY, FloatRef rotationZ);
}

DECLARE_API(Object, GetAttachedData, objectPtr object, IntRef parentVehicle, IntRef parentObject, IntRef parentPlayer)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.GetAttachedData(object, parentVehicle, parentObject, parentPlayer);
	API_RETURN(bool ret, IntRef parentVehicle, IntRef parentObject, IntRef parentPlayer);
}

DECLARE_API(Object, GetAttachedOffset, objectPtr object, FloatRef offsetX, FloatRef offsetY, FloatRef offsetZ, FloatRef rotationX, FloatRef rotationY, FloatRef rotationZ)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.GetAttachedOffset(object, offsetX, offsetY, offsetZ, rotationX, rotationY, rotationZ);
	API_RETURN(bool ret, FloatRef offsetX, FloatRef offsetY, FloatRef offsetZ, FloatRef rotationX, FloatRef rotationY, FloatRef rotationZ);
}

DECLARE_API(Object, GetSyncRotation, objectPtr object)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.GetSyncRotation(object);
	API_RETURN(bool ret);
}

DECLARE_API(Object, IsMaterialSlotUsed, objectPtr object, int materialIndex)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.IsMaterialSlotUsed(object, materialIndex);
	API_RETURN(bool ret);
}

DECLARE_API(Object, GetMaterial, objectPtr object, int materialIndex, IntRef modelid, OutputStringViewPtr textureLibrary, OutputStringViewPtr textureName, IntRef materialColor)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.GetMaterial(object, materialIndex, modelid, textureLibrary, textureName, materialColor);
	API_RETURN(bool ret, IntRef modelid, OutputStringViewPtr textureLibrary, OutputStringViewPtr textureName, IntRef materialColor);
}

DECLARE_API(Object, GetMaterialText, objectPtr object, int materialIndex, OutputStringViewPtr text, IntRef materialSize, OutputStringViewPtr fontFace, IntRef fontSize, BoolRef bold, IntRef fontColor, IntRef backgroundColor, IntRef textAlignment)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.GetMaterialText(object, materialIndex, text, materialSize, fontFace, fontSize, bold, fontColor, backgroundColor, textAlignment);
	API_RETURN(bool ret, OutputStringViewPtr text, IntRef materialSize, OutputStringViewPtr fontFace, IntRef fontSize, BoolRef bold, IntRef fontColor, IntRef backgroundColor, IntRef textAlignment);
}

DECLARE_API(Object, IsObjectNoCameraCollision, objectPtr object)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Object.IsObjectNoCameraCollision(object);
	API_RETURN(bool ret);
}

DECLARE_API(Object, GetType, objectPtr player, int objectid)
{
	uint8_t ret = Runtime::Instance().GetOMPAPI()->Object.GetType(player, objectid);
	API_RETURN(uint8_t ret);
}
