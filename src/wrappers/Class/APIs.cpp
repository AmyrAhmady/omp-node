#include "../Impl.hpp"
#include "../MacroMagic.hpp"

DECLARE_API(Class, Add, uint8_t team, int skin, float x, float y, float z, float angle, uint8_t weapon1, uint32_t ammo1, uint8_t weapon2, uint32_t ammo2, uint8_t weapon3, uint32_t ammo3, IntRef id)
{
    objectPtr ret = Runtime::Instance().GetOMPAPI()->Class.Add(team, skin, x, y, z, angle, weapon1, ammo1, weapon2, ammo2, weapon3, ammo3, id);
    API_RETURN(objectPtr ret, IntRef id);
}

DECLARE_API(Class, Count)
{
    int ret = Runtime::Instance().GetOMPAPI()->Class.Count();
    API_RETURN(int ret);
}

DECLARE_API(Class, GetData, objectPtr classptr, UInt8Ref teamid, IntRef skin, FloatRef x, FloatRef y, FloatRef z, FloatRef angle, UInt8Ref weapon1, UInt32Ref weapon1_ammo, UInt8Ref weapon2, UInt32Ref weapon2_ammo, UInt8Ref weapon3, UInt32Ref weapon3_ammo)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Class.GetData(classptr, teamid, skin, x, y, z, angle, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo);
    API_RETURN(bool ret, UInt8Ref teamid, IntRef skin, FloatRef x, FloatRef y, FloatRef z, FloatRef angle, UInt8Ref weapon1, UInt32Ref weapon1_ammo, UInt8Ref weapon2, UInt32Ref weapon2_ammo, UInt8Ref weapon3, UInt32Ref weapon3_ammo);
}

DECLARE_API(Class, Edit, objectPtr classptr, uint8_t teamid, int skin, float x, float y, float z, float angle, uint8_t weapon1, uint32_t ammo1, uint8_t weapon2, uint32_t ammo2, uint8_t weapon3, uint32_t ammo3)
{
    bool ret = Runtime::Instance().GetOMPAPI()->Class.Edit(classptr, teamid, skin, x, y, z, angle, weapon1, ammo1, weapon2, ammo2, weapon3, ammo3);
    API_RETURN(bool ret);
}
