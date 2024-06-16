#include "../Impl.hpp"
#include "../MacroMagic.hpp"

DECLARE_API(Actor, Create, int model, float x, float y, float z, float rot, IntRef id)
{
    objectPtr ret = Runtime::Instance().GetOMPAPI()->Actor.Create(model, x, y, z, rot, id);
    API_RETURN(objectPtr ret, IntRef id);
}

DECLARE_API(Actor, Destroy, objectPtr actor)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Actor.Destroy(actor);
    API_RETURN(bool ret);
}

DECLARE_API(Actor, IsStreamedInFor, objectPtr actor, objectPtr player)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Actor.IsStreamedInFor(actor, player);
    API_RETURN(bool ret);
}

DECLARE_API(Actor, SetVirtualWorld, objectPtr actor, int vw)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Actor.SetVirtualWorld(actor, vw);
    API_RETURN(bool ret);
}

DECLARE_API(Actor, GetVirtualWorld, objectPtr actor)
{
    int ret = Runtime::Instance().GetOMPAPI()->Actor.GetVirtualWorld(actor);
    API_RETURN(int ret);
}

DECLARE_API(Actor, ApplyAnimation, objectPtr actor, StringCharPtr name, StringCharPtr library, float delta, bool loop, bool lockX, bool lockY, bool freeze, int time)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Actor.ApplyAnimation(actor, name, library, delta, loop, lockX, lockY, freeze, time);
    API_RETURN(bool ret);
}

DECLARE_API(Actor, ClearAnimations, objectPtr actor)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Actor.ClearAnimations(actor);
    API_RETURN(bool ret);
}

DECLARE_API(Actor, SetPos, objectPtr actor, float x, float y, float z)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Actor.SetPos(actor, x, y, z);
    API_RETURN(bool ret);
}

DECLARE_API(Actor, GetPos, objectPtr actor, FloatRef x, FloatRef y, FloatRef z)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Actor.GetPos(actor, x, y, z);
    API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z);
}

DECLARE_API(Actor, SetFacingAngle, objectPtr actor, float angle)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Actor.SetFacingAngle(actor, angle);
    API_RETURN(bool ret);
}

DECLARE_API(Actor, GetFacingAngle, objectPtr actor)
{
    float ret = Runtime::Instance().GetOMPAPI()->Actor.GetFacingAngle(actor);
    API_RETURN(float ret);
}

DECLARE_API(Actor, SetHealth, objectPtr actor, float hp)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Actor.SetHealth(actor, hp);
    API_RETURN(bool ret);
}

DECLARE_API(Actor, GetHealth, objectPtr actor)
{
    float ret = Runtime::Instance().GetOMPAPI()->Actor.GetHealth(actor);
    API_RETURN(float ret);
}

DECLARE_API(Actor, SetInvulnerable, objectPtr actor, bool toggle)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Actor.SetInvulnerable(actor, toggle);
    API_RETURN(bool ret);
}

DECLARE_API(Actor, IsInvulnerable, objectPtr actor)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Actor.IsInvulnerable(actor);
    API_RETURN(bool ret);
}

DECLARE_API(Actor, IsValid, objectPtr actor)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Actor.IsValid(actor);
    API_RETURN(bool ret);
}

DECLARE_API(Actor, SetSkin, objectPtr actor, int skin)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Actor.SetSkin(actor, skin);
    API_RETURN(bool ret);
}

DECLARE_API(Actor, GetSkin, objectPtr actor)
{
    int ret = Runtime::Instance().GetOMPAPI()->Actor.GetSkin(actor);
    API_RETURN(int ret);
}

DECLARE_API(Actor, GetAnimation, objectPtr actor, OutputStringViewPtr library, OutputStringViewPtr name, FloatRef delta, BoolRef loop, BoolRef lockX, BoolRef lockY, BoolRef freeze, IntRef time)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Actor.GetAnimation(actor, library, name, delta, loop, lockX, lockY, freeze, time);
    API_RETURN(bool ret, OutputStringViewPtr library, OutputStringViewPtr name, FloatRef delta, BoolRef loop, BoolRef lockX, BoolRef lockY, BoolRef freeze, IntRef time);
}

DECLARE_API(Actor, GetSpawnInfo, objectPtr actor, FloatRef x, FloatRef y, FloatRef z, FloatRef angle, FloatRef skin)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Actor.GetSpawnInfo(actor, x, y, z, angle, skin);
    API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z, FloatRef angle, FloatRef skin);
}
