#include "../Impl.hpp"
#include "../MacroMagic.hpp"

DECLARE_API(Vehicle, Create, int modelid, float x, float y, float z, float rotation, int color1, int color2, int respawnDelay, bool addSiren, IntRef id)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Vehicle.Create(modelid, x, y, z, rotation, color1, color2, respawnDelay, addSiren, id);
	API_RETURN(objectPtr ret, IntRef id);
}

DECLARE_API(Vehicle, GetMaxPassengerSeats, int modelid)
{
	int ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetMaxPassengerSeats(modelid);
	API_RETURN(int ret);
}

DECLARE_API(Vehicle, Destroy, objectPtr vehicle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.Destroy(vehicle);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, IsStreamedIn, objectPtr vehicle, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.IsStreamedIn(vehicle, player);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, GetPos, objectPtr vehicle, FloatRef x, FloatRef y, FloatRef z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetPos(vehicle, x, y, z);
	API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z);
}

DECLARE_API(Vehicle, SetPos, objectPtr vehicle, float x, float y, float z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.SetPos(vehicle, x, y, z);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, GetZAngle, objectPtr vehicle)
{
	float ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetZAngle(vehicle);
	API_RETURN(float ret);
}

DECLARE_API(Vehicle, GetRotationQuat, objectPtr vehicle, FloatRef w, FloatRef x, FloatRef y, FloatRef z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetRotationQuat(vehicle, w, x, y, z);
	API_RETURN(bool ret, FloatRef w, FloatRef x, FloatRef y, FloatRef z);
}

DECLARE_API(Vehicle, GetDistanceFromPoint, objectPtr vehicle, float x, float y, float z)
{
	float ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetDistanceFromPoint(vehicle, x, y, z);
	API_RETURN(float ret);
}

DECLARE_API(Vehicle, SetZAngle, objectPtr vehicle, float angle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.SetZAngle(vehicle, angle);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, SetParamsForPlayer, objectPtr vehicle, objectPtr player, int objective, int doors)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.SetParamsForPlayer(vehicle, player, objective, doors);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, UseManualEngineAndLights)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.UseManualEngineAndLights();
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, SetParamsEx, objectPtr vehicle, int engine, int lights, int alarm, int doors, int bonnet, int boot, int objective)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.SetParamsEx(vehicle, engine, lights, alarm, doors, bonnet, boot, objective);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, GetParamsEx, objectPtr vehicle, IntRef engine, IntRef lights, IntRef alarm, IntRef doors, IntRef bonnet, IntRef boot, IntRef objective)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetParamsEx(vehicle, engine, lights, alarm, doors, bonnet, boot, objective);
	API_RETURN(bool ret, IntRef engine, IntRef lights, IntRef alarm, IntRef doors, IntRef bonnet, IntRef boot, IntRef objective);
}

DECLARE_API(Vehicle, GetParamsSirenState, objectPtr vehicle)
{
	int ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetParamsSirenState(vehicle);
	API_RETURN(int ret);
}

DECLARE_API(Vehicle, SetParamsCarDoors, objectPtr vehicle, int frontLeft, int frontRight, int rearLeft, int rearRight)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.SetParamsCarDoors(vehicle, frontLeft, frontRight, rearLeft, rearRight);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, GetParamsCarDoors, objectPtr vehicle, IntRef frontLeft, IntRef frontRight, IntRef rearLeft, IntRef rearRight)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetParamsCarDoors(vehicle, frontLeft, frontRight, rearLeft, rearRight);
	API_RETURN(bool ret, IntRef frontLeft, IntRef frontRight, IntRef rearLeft, IntRef rearRight);
}

DECLARE_API(Vehicle, SetParamsCarWindows, objectPtr vehicle, int frontLeft, int frontRight, int rearLeft, int rearRight)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.SetParamsCarWindows(vehicle, frontLeft, frontRight, rearLeft, rearRight);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, GetParamsCarWindows, objectPtr vehicle, IntRef frontLeft, IntRef frontRight, IntRef rearLeft, IntRef rearRight)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetParamsCarWindows(vehicle, frontLeft, frontRight, rearLeft, rearRight);
	API_RETURN(bool ret, IntRef frontLeft, IntRef frontRight, IntRef rearLeft, IntRef rearRight);
}

DECLARE_API(Vehicle, SetToRespawn, objectPtr vehicle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.SetToRespawn(vehicle);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, LinkToInterior, objectPtr vehicle, int interiorid)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.LinkToInterior(vehicle, interiorid);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, AddComponent, objectPtr vehicle, int componentid)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.AddComponent(vehicle, componentid);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, RemoveComponent, objectPtr vehicle, int componentid)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.RemoveComponent(vehicle, componentid);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, ChangeColor, objectPtr vehicle, int color1, int color2)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.ChangeColor(vehicle, color1, color2);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, ChangePaintjob, objectPtr vehicle, int paintjobid)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.ChangePaintjob(vehicle, paintjobid);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, SetHealth, objectPtr vehicle, float health)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.SetHealth(vehicle, health);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, GetHealth, objectPtr vehicle)
{
	float ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetHealth(vehicle);
	API_RETURN(float ret);
}

DECLARE_API(Vehicle, AttachTrailer, objectPtr trailer, objectPtr vehicle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.AttachTrailer(trailer, vehicle);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, DetachTrailer, objectPtr vehicle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.DetachTrailer(vehicle);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, IsTrailerAttached, objectPtr vehicle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.IsTrailerAttached(vehicle);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, GetTrailer, objectPtr vehicle)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetTrailer(vehicle);
	API_RETURN(objectPtr ret);
}

DECLARE_API(Vehicle, SetNumberPlate, objectPtr vehicle, StringCharPtr numberPlate)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.SetNumberPlate(vehicle, numberPlate);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, GetModel, objectPtr vehicle)
{
	int ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetModel(vehicle);
	API_RETURN(int ret);
}

DECLARE_API(Vehicle, GetComponentInSlot, objectPtr vehicle, int slot)
{
	int ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetComponentInSlot(vehicle, slot);
	API_RETURN(int ret);
}

DECLARE_API(Vehicle, GetComponentType, int componentid)
{
	int ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetComponentType(componentid);
	API_RETURN(int ret);
}

DECLARE_API(Vehicle, CanHaveComponent, int modelid, int componentid)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.CanHaveComponent(modelid, componentid);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, GetRandomColorPair, int modelid, IntRef color1, IntRef color2, IntRef color3, IntRef color4)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetRandomColorPair(modelid, color1, color2, color3, color4);
	API_RETURN(bool ret, IntRef color1, IntRef color2, IntRef color3, IntRef color4);
}

DECLARE_API(Vehicle, ColorIndexToColor, int colorIndex, int alpha)
{
	int ret = Runtime::Instance().GetOMPAPI()->Vehicle.ColorIndexToColor(colorIndex, alpha);
	API_RETURN(int ret);
}

DECLARE_API(Vehicle, Repair, objectPtr vehicle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.Repair(vehicle);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, GetVelocity, objectPtr vehicle, FloatRef x, FloatRef y, FloatRef z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetVelocity(vehicle, x, y, z);
	API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z);
}

DECLARE_API(Vehicle, SetVelocity, objectPtr vehicle, float x, float y, float z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.SetVelocity(vehicle, x, y, z);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, SetAngularVelocity, objectPtr vehicle, float x, float y, float z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.SetAngularVelocity(vehicle, x, y, z);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, GetDamageStatus, objectPtr vehicle, IntRef panels, IntRef doors, IntRef lights, IntRef tires)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetDamageStatus(vehicle, panels, doors, lights, tires);
	API_RETURN(bool ret, IntRef panels, IntRef doors, IntRef lights, IntRef tires);
}

DECLARE_API(Vehicle, UpdateDamageStatus, objectPtr vehicle, int panels, int doors, int lights, int tires)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.UpdateDamageStatus(vehicle, panels, doors, lights, tires);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, GetModelInfo, int vehiclemodel, int infotype, FloatRef x, FloatRef y, FloatRef z)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetModelInfo(vehiclemodel, infotype, x, y, z);
	API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z);
}

DECLARE_API(Vehicle, SetVirtualWorld, objectPtr vehicle, int virtualWorld)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.SetVirtualWorld(vehicle, virtualWorld);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, GetVirtualWorld, objectPtr vehicle)
{
	int ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetVirtualWorld(vehicle);
	API_RETURN(int ret);
}

DECLARE_API(Vehicle, GetLandingGearState, objectPtr vehicle)
{
	int ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetLandingGearState(vehicle);
	API_RETURN(int ret);
}

DECLARE_API(Vehicle, IsValid, objectPtr vehicle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.IsValid(vehicle);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, AddStatic, int modelid, float x, float y, float z, float angle, int color1, int color2, IntRef id)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Vehicle.AddStatic(modelid, x, y, z, angle, color1, color2, id);
	API_RETURN(objectPtr ret, IntRef id);
}

DECLARE_API(Vehicle, AddStaticEx, int modelid, float x, float y, float z, float angle, int color1, int color2, int respawnDelay, bool addSiren, IntRef id)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Vehicle.AddStaticEx(modelid, x, y, z, angle, color1, color2, respawnDelay, addSiren, id);
	API_RETURN(objectPtr ret, IntRef id);
}

DECLARE_API(Vehicle, EnableFriendlyFire)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.EnableFriendlyFire();
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, GetSpawnInfo, objectPtr vehicle, FloatRef x, FloatRef y, FloatRef z, FloatRef rotation, IntRef color1, IntRef color2)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetSpawnInfo(vehicle, x, y, z, rotation, color1, color2);
	API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z, FloatRef rotation, IntRef color1, IntRef color2);
}

DECLARE_API(Vehicle, SetSpawnInfo, objectPtr vehicle, int modelid, float x, float y, float z, float rotation, int color1, int color2, int respawn_time, int interior)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.SetSpawnInfo(vehicle, modelid, x, y, z, rotation, color1, color2, respawn_time, interior);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, GetModelCount, int modelid)
{
	int ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetModelCount(modelid);
	API_RETURN(int ret);
}

DECLARE_API(Vehicle, GetModelsUsed)
{
	int ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetModelsUsed();
	API_RETURN(int ret);
}

DECLARE_API(Vehicle, GetPaintjob, objectPtr vehicle)
{
	int ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetPaintjob(vehicle);
	API_RETURN(int ret);
}

DECLARE_API(Vehicle, GetColor, objectPtr vehicle, IntRef color1, IntRef color2)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetColor(vehicle, color1, color2);
	API_RETURN(bool ret, IntRef color1, IntRef color2);
}

DECLARE_API(Vehicle, GetInterior, objectPtr vehicle)
{
	int ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetInterior(vehicle);
	API_RETURN(int ret);
}

DECLARE_API(Vehicle, GetNumberPlate, objectPtr vehicle, OutputStringViewPtr numberPlate)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetNumberPlate(vehicle, numberPlate);
	API_RETURN(bool ret, OutputStringViewPtr numberPlate);
}

DECLARE_API(Vehicle, SetRespawnDelay, objectPtr vehicle, int respawn_delay)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.SetRespawnDelay(vehicle, respawn_delay);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, GetRespawnDelay, objectPtr vehicle)
{
	int ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetRespawnDelay(vehicle);
	API_RETURN(int ret);
}

DECLARE_API(Vehicle, GetCab, objectPtr vehicle)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetCab(vehicle);
	API_RETURN(objectPtr ret);
}

DECLARE_API(Vehicle, GetTower, objectPtr vehicle)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetTower(vehicle);
	API_RETURN(objectPtr ret);
}

DECLARE_API(Vehicle, GetOccupiedTick, objectPtr vehicle)
{
	int ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetOccupiedTick(vehicle);
	API_RETURN(int ret);
}

DECLARE_API(Vehicle, GetRespawnTick, objectPtr vehicle)
{
	int ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetRespawnTick(vehicle);
	API_RETURN(int ret);
}

DECLARE_API(Vehicle, HasBeenOccupied, objectPtr vehicle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.HasBeenOccupied(vehicle);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, IsOccupied, objectPtr vehicle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.IsOccupied(vehicle);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, IsDead, objectPtr vehicle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.IsDead(vehicle);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, SetParamsSirenState, objectPtr vehicle, bool siren_state)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.SetParamsSirenState(vehicle, siren_state);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, ToggleSirenEnabled, objectPtr vehicle, bool status)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.ToggleSirenEnabled(vehicle, status);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, IsSirenEnabled, objectPtr vehicle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.IsSirenEnabled(vehicle);
	API_RETURN(bool ret);
}

DECLARE_API(Vehicle, GetLastDriver, objectPtr vehicle)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetLastDriver(vehicle);
	API_RETURN(objectPtr ret);
}

DECLARE_API(Vehicle, GetDriver, objectPtr vehicle)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetDriver(vehicle);
	API_RETURN(objectPtr ret);
}

DECLARE_API(Vehicle, GetSirenState, objectPtr vehicle)
{
	int ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetSirenState(vehicle);
	API_RETURN(int ret);
}

DECLARE_API(Vehicle, GetHydraReactorAngle, objectPtr vehicle)
{
	uint32_t ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetHydraReactorAngle(vehicle);
	API_RETURN(uint32_t ret);
}

DECLARE_API(Vehicle, GetTrainSpeed, objectPtr vehicle)
{
	float ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetTrainSpeed(vehicle);
	API_RETURN(float ret);
}

DECLARE_API(Vehicle, GetMatrix, objectPtr vehicle, FloatRef rightX, FloatRef rightY, FloatRef rightZ, FloatRef upX, FloatRef upY, FloatRef upZ, FloatRef atX, FloatRef atY, FloatRef atZ)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetMatrix(vehicle, rightX, rightY, rightZ, upX, upY, upZ, atX, atY, atZ);
	API_RETURN(bool ret, FloatRef rightX, FloatRef rightY, FloatRef rightZ, FloatRef upX, FloatRef upY, FloatRef upZ, FloatRef atX, FloatRef atY, FloatRef atZ);
}

DECLARE_API(Vehicle, GetOccupant, objectPtr vehicle, int seat)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Vehicle.GetOccupant(vehicle, seat);
	API_RETURN(objectPtr ret);
}

DECLARE_API(Vehicle, CountOccupants, objectPtr vehicle)
{
	int ret = Runtime::Instance().GetOMPAPI()->Vehicle.CountOccupants(vehicle);
	API_RETURN(int ret);
}
