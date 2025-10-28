#include "../Impl.hpp"
#include "../API.hpp"

DECLARE_API(NPC, Connect, StringCharPtr name, StringCharPtr script)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.Connect(name, script);
	API_RETURN(bool ret);
}

DECLARE_API_ARGNUM(NPC, Create, 1, StringCharPtr name, IntRef id)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->NPC.Create(name, id);
	API_RETURN(objectPtr ret);
}

DECLARE_API(NPC, Destroy, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.Destroy(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, FromID, int npcid)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->NPC.FromID(npcid);
	API_RETURN(objectPtr ret);
}

DECLARE_API(NPC, GetID, objectPtr npc)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetID(npc);
	API_RETURN(int ret);
}

DECLARE_API(NPC, IsValid, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.IsValid(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetPlayer, objectPtr npc)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->NPC.GetPlayer(npc);
	API_RETURN(objectPtr ret);
}

DECLARE_API(NPC, Spawn, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.Spawn(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, Respawn, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.Respawn(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, SetPos, objectPtr npc, float x, float y, float z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetPos(npc, x, y, z);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetPos, objectPtr npc, FloatRef x, FloatRef y, FloatRef z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.GetPos(npc, x, y, z);
	API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z);
}

DECLARE_API(NPC, SetRot, objectPtr npc, float rx, float ry, float rz)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetRot(npc, rx, ry, rz);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetRot, objectPtr npc, FloatRef rx, FloatRef ry, FloatRef rz)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.GetRot(npc, rx, ry, rz);
	API_RETURN(bool ret, FloatRef rx, FloatRef ry, FloatRef rz);
}

DECLARE_API(NPC, SetFacingAngle, objectPtr npc, float angle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetFacingAngle(npc, angle);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetFacingAngle, objectPtr npc, FloatRef angle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.GetFacingAngle(npc, angle);
	API_RETURN(bool ret, FloatRef angle);
}

DECLARE_API(NPC, SetVirtualWorld, objectPtr npc, int virtualWorld)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetVirtualWorld(npc, virtualWorld);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetVirtualWorld, objectPtr npc)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetVirtualWorld(npc);
	API_RETURN(int ret);
}

DECLARE_API(NPC, SetInterior, objectPtr npc, int interior)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetInterior(npc, interior);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetInterior, objectPtr npc)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetInterior(npc);
	API_RETURN(int ret);
}

DECLARE_API(NPC, Move, objectPtr npc, float x, float y, float z, int moveType, float moveSpeed, float stopRange)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.Move(npc, x, y, z, moveType, moveSpeed, stopRange);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, MoveToPlayer, objectPtr npc, objectPtr player, int moveType, float moveSpeed, float stopRange, int posCheckUpdateDelay, bool autoRestart)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.MoveToPlayer(npc, player, moveType, moveSpeed, stopRange, posCheckUpdateDelay, autoRestart);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, StopMove, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.StopMove(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, IsMoving, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.IsMoving(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, SetSkin, objectPtr npc, int model)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetSkin(npc, model);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, IsStreamedIn, objectPtr npc, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.IsStreamedIn(npc, player);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, IsAnyStreamedIn, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.IsAnyStreamedIn(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetAll, IntRef npcsArr, int maxNPCs)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetAll(npcsArr, maxNPCs);
	API_RETURN(int ret, IntRef npcsArr);
}

DECLARE_API(NPC, SetHealth, objectPtr npc, float health)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetHealth(npc, health);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetHealth, objectPtr npc)
{
	float ret = Runtime::Instance().GetOMPAPI()->NPC.GetHealth(npc);
	API_RETURN(float ret);
}

DECLARE_API(NPC, SetArmour, objectPtr npc, float armour)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetArmour(npc, armour);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetArmour, objectPtr npc)
{
	float ret = Runtime::Instance().GetOMPAPI()->NPC.GetArmour(npc);
	API_RETURN(float ret);
}

DECLARE_API(NPC, IsDead, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.IsDead(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, SetInvulnerable, objectPtr npc, bool toggle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetInvulnerable(npc, toggle);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, IsInvulnerable, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.IsInvulnerable(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, SetWeapon, objectPtr npc, uint8_t weapon)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetWeapon(npc, weapon);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetWeapon, objectPtr npc)
{
	uint8_t ret = Runtime::Instance().GetOMPAPI()->NPC.GetWeapon(npc);
	API_RETURN(uint8_t ret);
}

DECLARE_API(NPC, SetAmmo, objectPtr npc, int ammo)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetAmmo(npc, ammo);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetAmmo, objectPtr npc)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetAmmo(npc);
	API_RETURN(int ret);
}

DECLARE_API(NPC, SetAmmoInClip, objectPtr npc, int ammo)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetAmmoInClip(npc, ammo);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetAmmoInClip, objectPtr npc)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetAmmoInClip(npc);
	API_RETURN(int ret);
}

DECLARE_API(NPC, EnableReloading, objectPtr npc, bool enable)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.EnableReloading(npc, enable);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, IsReloadEnabled, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.IsReloadEnabled(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, IsReloading, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.IsReloading(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, EnableInfiniteAmmo, objectPtr npc, bool enable)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.EnableInfiniteAmmo(npc, enable);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, IsInfiniteAmmoEnabled, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.IsInfiniteAmmoEnabled(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetWeaponState, objectPtr npc)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetWeaponState(npc);
	API_RETURN(int ret);
}

DECLARE_API(NPC, SetKeys, objectPtr npc, uint16_t upAndDown, uint16_t leftAndRight, uint16_t keys)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetKeys(npc, upAndDown, leftAndRight, keys);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetKeys, objectPtr npc, UInt16Ref upAndDown, UInt16Ref leftAndRight, UInt16Ref keys)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.GetKeys(npc, upAndDown, leftAndRight, keys);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, SetWeaponSkillLevel, objectPtr npc, uint8_t skill, int level)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetWeaponSkillLevel(npc, skill, level);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetWeaponSkillLevel, objectPtr npc, int skill)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetWeaponSkillLevel(npc, skill);
	API_RETURN(int ret);
}

DECLARE_API(NPC, MeleeAttack, objectPtr npc, int time, bool secondaryAttack)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.MeleeAttack(npc, time, secondaryAttack);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, StopMeleeAttack, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.StopMeleeAttack(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, IsMeleeAttacking, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.IsMeleeAttacking(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, SetFightingStyle, objectPtr npc, int style)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetFightingStyle(npc, style);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetFightingStyle, objectPtr npc)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetFightingStyle(npc);
	API_RETURN(int ret);
}

DECLARE_API(NPC, Shoot, objectPtr npc, uint8_t weapon, int hitId, int hitType, float endX, float endY, float endZ, float offsetX, float offsetY, float offsetZ, bool isHit, uint8_t checkInBetweenFlags)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.Shoot(npc, weapon, hitId, hitType, endX, endY, endZ, offsetX, offsetY, offsetZ, isHit, checkInBetweenFlags);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, IsShooting, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.IsShooting(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, AimAt, objectPtr npc, float x, float y, float z, bool shoot, int shootDelay, bool updateAngle, float offsetFromX, float offsetFromY, float offsetFromZ, uint8_t checkInBetweenFlags)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.AimAt(npc, x, y, z, shoot, shootDelay, updateAngle, offsetFromX, offsetFromY, offsetFromZ, checkInBetweenFlags);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, AimAtPlayer, objectPtr npc, objectPtr atPlayer, bool shoot, int shootDelay, bool updateAngle, float offsetX, float offsetY, float offsetZ, float offsetFromX, float offsetFromY, float offsetFromZ, uint8_t checkInBetweenFlags)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.AimAtPlayer(npc, atPlayer, shoot, shootDelay, updateAngle, offsetX, offsetY, offsetZ, offsetFromX, offsetFromY, offsetFromZ, checkInBetweenFlags);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, StopAim, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.StopAim(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, IsAiming, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.IsAiming(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, IsAimingAtPlayer, objectPtr npc, objectPtr atPlayer)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.IsAimingAtPlayer(npc, atPlayer);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, SetWeaponAccuracy, objectPtr npc, int weapon, float accuracy)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetWeaponAccuracy(npc, weapon, accuracy);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetWeaponAccuracy, objectPtr npc, int weapon)
{
	float ret = Runtime::Instance().GetOMPAPI()->NPC.GetWeaponAccuracy(npc, weapon);
	API_RETURN(float ret);
}

DECLARE_API(NPC, SetWeaponReloadTime, objectPtr npc, int weapon, int time)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetWeaponReloadTime(npc, weapon, time);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetWeaponReloadTime, objectPtr npc, int weapon)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetWeaponReloadTime(npc, weapon);
	API_RETURN(int ret);
}

DECLARE_API(NPC, GetWeaponActualReloadTime, objectPtr npc, int weapon)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetWeaponActualReloadTime(npc, weapon);
	API_RETURN(int ret);
}

DECLARE_API(NPC, SetWeaponShootTime, objectPtr npc, int weapon, int time)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetWeaponShootTime(npc, weapon, time);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetWeaponShootTime, objectPtr npc, int weapon)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetWeaponShootTime(npc, weapon);
	API_RETURN(int ret);
}

DECLARE_API(NPC, SetWeaponClipSize, objectPtr npc, int weapon, int size)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetWeaponClipSize(npc, weapon, size);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetWeaponClipSize, objectPtr npc, int weapon)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetWeaponClipSize(npc, weapon);
	API_RETURN(int ret);
}

DECLARE_API(NPC, GetWeaponActualClipSize, objectPtr npc, int weapon)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetWeaponActualClipSize(npc, weapon);
	API_RETURN(int ret);
}

DECLARE_API(NPC, EnterVehicle, objectPtr npc, objectPtr vehicle, int seatId, int moveType)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.EnterVehicle(npc, vehicle, seatId, moveType);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, ExitVehicle, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.ExitVehicle(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, PutInVehicle, objectPtr npc, objectPtr vehicle, int seatId)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.PutInVehicle(npc, vehicle, seatId);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, RemoveFromVehicle, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.RemoveFromVehicle(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetVehicle, objectPtr npc)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->NPC.GetVehicle(npc);
	API_RETURN(objectPtr ret);
}

DECLARE_API(NPC, GetVehicleID, objectPtr npc)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetVehicleID(npc);
	API_RETURN(int ret);
}

DECLARE_API(NPC, GetEnteringVehicle, objectPtr npc)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->NPC.GetEnteringVehicle(npc);
	API_RETURN(objectPtr ret);
}

DECLARE_API(NPC, GetEnteringVehicleID, objectPtr npc)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetEnteringVehicleID(npc);
	API_RETURN(int ret);
}

DECLARE_API(NPC, GetVehicleSeat, objectPtr npc)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetVehicleSeat(npc);
	API_RETURN(int ret);
}

DECLARE_API(NPC, GetEnteringVehicleSeat, objectPtr npc)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetEnteringVehicleSeat(npc);
	API_RETURN(int ret);
}

DECLARE_API(NPC, IsEnteringVehicle, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.IsEnteringVehicle(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, UseVehicleSiren, objectPtr npc, bool use)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.UseVehicleSiren(npc, use);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, IsVehicleSirenUsed, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.IsVehicleSirenUsed(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, SetVehicleHealth, objectPtr npc, float health)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetVehicleHealth(npc, health);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetVehicleHealth, objectPtr npc)
{
	float ret = Runtime::Instance().GetOMPAPI()->NPC.GetVehicleHealth(npc);
	API_RETURN(float ret);
}

DECLARE_API(NPC, SetVehicleHydraThrusters, objectPtr npc, int direction)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetVehicleHydraThrusters(npc, direction);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetVehicleHydraThrusters, objectPtr npc)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetVehicleHydraThrusters(npc);
	API_RETURN(int ret);
}

DECLARE_API(NPC, SetVehicleGearState, objectPtr npc, int gearState)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetVehicleGearState(npc, gearState);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetVehicleGearState, objectPtr npc)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetVehicleGearState(npc);
	API_RETURN(int ret);
}

DECLARE_API(NPC, SetVehicleTrainSpeed, objectPtr npc, float speed)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetVehicleTrainSpeed(npc, speed);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetVehicleTrainSpeed, objectPtr npc)
{
	float ret = Runtime::Instance().GetOMPAPI()->NPC.GetVehicleTrainSpeed(npc);
	API_RETURN(float ret);
}

DECLARE_API(NPC, CreatePath)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.CreatePath();
	API_RETURN(int ret);
}

DECLARE_API(NPC, DestroyPath, int pathId)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.DestroyPath(pathId);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, DestroyAllPath)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.DestroyAllPath();
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetPathCount)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetPathCount();
	API_RETURN(int ret);
}

DECLARE_API(NPC, AddPointToPath, int pathId, float x, float y, float z, float stopRange)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.AddPointToPath(pathId, x, y, z, stopRange);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, RemovePointFromPath, int pathId, int pointIndex)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.RemovePointFromPath(pathId, pointIndex);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, ClearPath, int pathId)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.ClearPath(pathId);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetPathPointCount, int pathId)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetPathPointCount(pathId);
	API_RETURN(int ret);
}

DECLARE_API(NPC, GetPathPoint, int pathId, int pointIndex, FloatRef x, FloatRef y, FloatRef z, FloatRef stopRange)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.GetPathPoint(pathId, pointIndex, x, y, z, stopRange);
	API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z, FloatRef stopRange);
}

DECLARE_API(NPC, GetCurrentPathPointIndex, objectPtr npc)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetCurrentPathPointIndex(npc);
	API_RETURN(int ret);
}

DECLARE_API(NPC, IsValidPath, int pathId)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.IsValidPath(pathId);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, HasPathPointInRange, int pathId, float x, float y, float z, float radius)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.HasPathPointInRange(pathId, x, y, z, radius);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, MoveByPath, objectPtr npc, int pathId, int moveType, float moveSpeed, bool reverse)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.MoveByPath(npc, pathId, moveType, moveSpeed, reverse);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, ResetAnimation, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.ResetAnimation(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, SetAnimation, objectPtr npc, int animationId, float delta, bool loop, bool lockX, bool lockY, bool freeze, int time)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetAnimation(npc, animationId, delta, loop, lockX, lockY, freeze, time);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetAnimation, objectPtr npc, IntRef animationId, FloatRef delta, BoolRef loop, BoolRef lockX, BoolRef lockY, BoolRef freeze, IntRef time)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.GetAnimation(npc, animationId, delta, loop, lockX, lockY, freeze, time);
	API_RETURN(bool ret, IntRef animationId, FloatRef delta, BoolRef loop, BoolRef lockX, BoolRef lockY, BoolRef freeze, IntRef time);
}

DECLARE_API(NPC, ApplyAnimation, objectPtr npc, StringCharPtr animlib, StringCharPtr animname, float delta, bool loop, bool lockX, bool lockY, bool freeze, int time)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.ApplyAnimation(npc, animlib, animname, delta, loop, lockX, lockY, freeze, time);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, ClearAnimations, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.ClearAnimations(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, SetSpecialAction, objectPtr npc, int action)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetSpecialAction(npc, action);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetSpecialAction, objectPtr npc)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetSpecialAction(npc);
	API_RETURN(int ret);
}

DECLARE_API(NPC, StartPlayback, objectPtr npc, StringCharPtr recordName, bool autoUnload, float startPosX, float startPosY, float startPosZ, float startRotX, float startRotY, float startRotZ)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.StartPlayback(npc, recordName, autoUnload, startPosX, startPosY, startPosZ, startRotX, startRotY, startRotZ);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, StartPlaybackEx, objectPtr npc, int recordId, bool autoUnload, float startPosX, float startPosY, float startPosZ, float startRotX, float startRotY, float startRotZ)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.StartPlaybackEx(npc, recordId, autoUnload, startPosX, startPosY, startPosZ, startRotX, startRotY, startRotZ);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, StopPlayback, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.StopPlayback(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, PausePlayback, objectPtr npc, bool paused)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.PausePlayback(npc, paused);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, IsPlayingPlayback, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.IsPlayingPlayback(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, IsPlaybackPaused, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.IsPlaybackPaused(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, LoadRecord, StringCharPtr recordName)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.LoadRecord(recordName);
	API_RETURN(int ret);
}

DECLARE_API(NPC, UnloadRecord, int recordId)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.UnloadRecord(recordId);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, IsValidRecord, int recordId)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.IsValidRecord(recordId);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetRecordCount)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetRecordCount();
	API_RETURN(int ret);
}

DECLARE_API(NPC, UnloadAllRecords)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.UnloadAllRecords();
	API_RETURN(bool ret);
}

DECLARE_API(NPC, OpenNode, int nodeId)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.OpenNode(nodeId);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, CloseNode, int nodeId)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.CloseNode(nodeId);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, IsNodeOpen, int nodeId)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.IsNodeOpen(nodeId);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetNodeType, int nodeId)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetNodeType(nodeId);
	API_RETURN(int ret);
}

DECLARE_API(NPC, SetNodePoint, int nodeId, int pointId)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetNodePoint(nodeId, pointId);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetNodePointPosition, int nodeId, FloatRef x, FloatRef y, FloatRef z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.GetNodePointPosition(nodeId, x, y, z);
	API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z);
}

DECLARE_API(NPC, GetNodePointCount, int nodeId)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetNodePointCount(nodeId);
	API_RETURN(int ret);
}

DECLARE_API(NPC, GetNodeInfo, int nodeId, UInt32Ref vehicleNodes, UInt32Ref pedNodes, UInt32Ref naviNodes)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.GetNodeInfo(nodeId, vehicleNodes, pedNodes, naviNodes);
	API_RETURN(bool ret, UInt32Ref vehicleNodes, UInt32Ref pedNodes, UInt32Ref naviNodes);
}

DECLARE_API(NPC, PlayNode, objectPtr npc, int nodeId, int moveType, float moveSpeed, float radius, bool setAngle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.PlayNode(npc, nodeId, moveType, moveSpeed, radius, setAngle);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, StopPlayingNode, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.StopPlayingNode(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, PausePlayingNode, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.PausePlayingNode(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, ResumePlayingNode, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.ResumePlayingNode(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, IsPlayingNodePaused, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.IsPlayingNodePaused(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, IsPlayingNode, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.IsPlayingNode(npc);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, ChangeNode, objectPtr npc, int nodeId, int linkId)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.ChangeNode(npc, nodeId, linkId);
	API_RETURN(int ret);
}

DECLARE_API(NPC, UpdateNodePoint, objectPtr npc, int pointId)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.UpdateNodePoint(npc, pointId);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, SetSurfingOffset, objectPtr npc, float x, float y, float z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetSurfingOffset(npc, x, y, z);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetSurfingOffset, objectPtr npc, FloatRef x, FloatRef y, FloatRef z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.GetSurfingOffset(npc, x, y, z);
	API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z);
}

DECLARE_API(NPC, SetSurfingVehicle, objectPtr npc, objectPtr vehicle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetSurfingVehicle(npc, vehicle);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetSurfingVehicle, objectPtr npc)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetSurfingVehicle(npc);
	API_RETURN(int ret);
}

DECLARE_API(NPC, SetSurfingObject, objectPtr npc, objectPtr object)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetSurfingObject(npc, object);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetSurfingObject, objectPtr npc)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetSurfingObject(npc);
	API_RETURN(int ret);
}

DECLARE_API(NPC, SetSurfingPlayerObject, objectPtr npc, objectPtr player, int objectId)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.SetSurfingPlayerObject(npc, player, objectId);
	API_RETURN(bool ret);
}

DECLARE_API(NPC, GetSurfingPlayerObject, objectPtr npc)
{
	int ret = Runtime::Instance().GetOMPAPI()->NPC.GetSurfingPlayerObject(npc);
	API_RETURN(int ret);
}

DECLARE_API(NPC, ResetSurfingData, objectPtr npc)
{
	bool ret = Runtime::Instance().GetOMPAPI()->NPC.ResetSurfingData(npc);
	API_RETURN(bool ret);
}
