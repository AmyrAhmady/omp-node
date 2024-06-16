#include "../Impl.hpp"
#include "../MacroMagic.hpp"

DECLARE_API(Pickup, Create, int model, int type, float x, float y, float z, int virtualWorld, IntRef id)
{
    objectPtr ret = Runtime::Instance().GetOMPAPI()->Pickup.Create(model, type, x, y, z, virtualWorld, id);
    API_RETURN(objectPtr ret, IntRef id);
}

DECLARE_API(Pickup, AddStatic, int model, int type, float x, float y, float z, int virtualWorld)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Pickup.AddStatic(model, type, x, y, z, virtualWorld);
    API_RETURN(bool ret);
}

DECLARE_API(Pickup, Destroy, objectPtr pickup)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Pickup.Destroy(pickup);
    API_RETURN(bool ret);
}

DECLARE_API(Pickup, IsValid, objectPtr pickup)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Pickup.IsValid(pickup);
    API_RETURN(bool ret);
}

DECLARE_API(Pickup, IsStreamedIn, objectPtr player, objectPtr pickup)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Pickup.IsStreamedIn(player, pickup);
    API_RETURN(bool ret);
}

DECLARE_API(Pickup, GetPos, objectPtr pickup, FloatRef x, FloatRef y, FloatRef z)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Pickup.GetPos(pickup, x, y, z);
    API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z);
}

DECLARE_API(Pickup, GetModel, objectPtr pickup)
{
    int ret = Runtime::Instance().GetOMPAPI()->Pickup.GetModel(pickup);
    API_RETURN(int ret);
}

DECLARE_API(Pickup, GetType, objectPtr pickup)
{
    int ret = Runtime::Instance().GetOMPAPI()->Pickup.GetType(pickup);
    API_RETURN(int ret);
}

DECLARE_API(Pickup, GetVirtualWorld, objectPtr pickup)
{
    int ret = Runtime::Instance().GetOMPAPI()->Pickup.GetVirtualWorld(pickup);
    API_RETURN(int ret);
}

DECLARE_API(Pickup, SetPos, objectPtr pickup, float x, float y, float z, bool update)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Pickup.SetPos(pickup, x, y, z, update);
    API_RETURN(bool ret);
}

DECLARE_API(Pickup, SetModel, objectPtr pickup, int model, bool update)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Pickup.SetModel(pickup, model, update);
    API_RETURN(bool ret);
}

DECLARE_API(Pickup, SetType, objectPtr pickup, int type, bool update)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Pickup.SetType(pickup, type, update);
    API_RETURN(bool ret);
}

DECLARE_API(Pickup, SetVirtualWorld, objectPtr pickup, int virtualworld)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Pickup.SetVirtualWorld(pickup, virtualworld);
    API_RETURN(bool ret);
}

DECLARE_API(Pickup, ShowForPlayer, objectPtr player, objectPtr pickup)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Pickup.ShowForPlayer(player, pickup);
    API_RETURN(bool ret);
}

DECLARE_API(Pickup, HideForPlayer, objectPtr player, objectPtr pickup)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Pickup.HideForPlayer(player, pickup);
    API_RETURN(bool ret);
}

DECLARE_API(Pickup, IsHiddenForPlayer, objectPtr player, objectPtr pickup)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Pickup.IsHiddenForPlayer(player, pickup);
    API_RETURN(bool ret);
}
