#include "./Impl.hpp"

class OMP_NODE_Events
{
public:
	OMP_NODE_Events()
	{
		EventManager::Instance().Register("onPlayerGiveDamageActor", EventCallback_Common(&onPlayerGiveDamageActor));
		EventManager::Instance().Register("onActorStreamIn", EventCallback_Common(&onActorStreamIn));
		EventManager::Instance().Register("onActorStreamOut", EventCallback_Common(&onActorStreamOut));
		EventManager::Instance().Register("onPlayerEnterCheckpoint", EventCallback_Common(&onPlayerEnterCheckpoint));
		EventManager::Instance().Register("onPlayerLeaveCheckpoint", EventCallback_Common(&onPlayerLeaveCheckpoint));
		EventManager::Instance().Register("onPlayerEnterRaceCheckpoint", EventCallback_Common(&onPlayerEnterRaceCheckpoint));
		EventManager::Instance().Register("onPlayerLeaveRaceCheckpoint", EventCallback_Common(&onPlayerLeaveRaceCheckpoint));
		EventManager::Instance().Register("onPlayerRequestClass", EventCallback_Common(&onPlayerRequestClass));
		EventManager::Instance().Register("onConsoleText", EventCallback_Common(&onConsoleText));
		EventManager::Instance().Register("onRconLoginAttempt", EventCallback_Common(&onRconLoginAttempt));
		EventManager::Instance().Register("onPlayerFinishedDownloading", EventCallback_Common(&onPlayerFinishedDownloading));
		EventManager::Instance().Register("onPlayerRequestDownload", EventCallback_Common(&onPlayerRequestDownload));
		EventManager::Instance().Register("onDialogResponse", EventCallback_Common(&onDialogResponse));
		EventManager::Instance().Register("onPlayerEnterGangZone", EventCallback_Common(&onPlayerEnterGangZone));
		EventManager::Instance().Register("onPlayerLeaveGangZone", EventCallback_Common(&onPlayerLeaveGangZone));
		EventManager::Instance().Register("onPlayerClickGangZone", EventCallback_Common(&onPlayerClickGangZone));
		EventManager::Instance().Register("onPlayerSelectedMenuRow", EventCallback_Common(&onPlayerSelectedMenuRow));
		EventManager::Instance().Register("onPlayerExitedMenu", EventCallback_Common(&onPlayerExitedMenu));
		EventManager::Instance().Register("onObjectMove", EventCallback_Common(&onObjectMove));
		EventManager::Instance().Register("onPlayerObjectMove", EventCallback_Common(&onPlayerObjectMove));
		EventManager::Instance().Register("onPlayerEditObject", EventCallback_Common(&onPlayerEditObject));
		EventManager::Instance().Register("onPlayerEditPlayerObject", EventCallback_Common(&onPlayerEditPlayerObject));
		EventManager::Instance().Register("onPlayerEditAttachedObject", EventCallback_Common(&onPlayerEditAttachedObject));
		EventManager::Instance().Register("onPlayerSelectObject", EventCallback_Common(&onPlayerSelectObject));
		EventManager::Instance().Register("onPlayerSelectPlayerObject", EventCallback_Common(&onPlayerSelectPlayerObject));
		EventManager::Instance().Register("onPlayerPickUpPickup", EventCallback_Common(&onPlayerPickUpPickup));
		EventManager::Instance().Register("onPlayerCancelTextDrawSelection", EventCallback_Common(&onPlayerCancelTextDrawSelection));
		EventManager::Instance().Register("onPlayerCancelPlayerTextDrawSelection", EventCallback_Common(&onPlayerCancelPlayerTextDrawSelection));
		EventManager::Instance().Register("onPlayerClickTextDraw", EventCallback_Common(&onPlayerClickTextDraw));
		EventManager::Instance().Register("onPlayerClickPlayerTextDraw", EventCallback_Common(&onPlayerClickPlayerTextDraw));
		EventManager::Instance().Register("onPlayerConnect", EventCallback_Common(&onPlayerConnect));
		EventManager::Instance().Register("onPlayerSpawn", EventCallback_Common(&onPlayerSpawn));
		EventManager::Instance().Register("onPlayerCommandText", EventCallback_Common(&onPlayerCommandText));
		EventManager::Instance().Register("onPlayerKeyStateChange", EventCallback_Common(&onPlayerKeyStateChange));
		EventManager::Instance().Register("onIncomingConnection", EventCallback_Common(&onIncomingConnection));
		EventManager::Instance().Register("onPlayerDisconnect", EventCallback_Common(&onPlayerDisconnect));
		EventManager::Instance().Register("onPlayerRequestSpawn", EventCallback_Common(&onPlayerRequestSpawn));
		EventManager::Instance().Register("onPlayerStreamIn", EventCallback_Common(&onPlayerStreamIn));
		EventManager::Instance().Register("onPlayerStreamOut", EventCallback_Common(&onPlayerStreamOut));
		EventManager::Instance().Register("onPlayerText", EventCallback_Common(&onPlayerText));
		EventManager::Instance().Register("onPlayerShotMissed", EventCallback_Common(&onPlayerShotMissed));
		EventManager::Instance().Register("onPlayerShotPlayer", EventCallback_Common(&onPlayerShotPlayer));
		EventManager::Instance().Register("onPlayerShotVehicle", EventCallback_Common(&onPlayerShotVehicle));
		EventManager::Instance().Register("onPlayerShotObject", EventCallback_Common(&onPlayerShotObject));
		EventManager::Instance().Register("onPlayerShotPlayerObject", EventCallback_Common(&onPlayerShotPlayerObject));
		EventManager::Instance().Register("onPlayerDeath", EventCallback_Common(&onPlayerDeath));
		EventManager::Instance().Register("onPlayerTakeDamage", EventCallback_Common(&onPlayerTakeDamage));
		EventManager::Instance().Register("onPlayerGiveDamage", EventCallback_Common(&onPlayerGiveDamage));
		EventManager::Instance().Register("onPlayerInteriorChange", EventCallback_Common(&onPlayerInteriorChange));
		EventManager::Instance().Register("onPlayerStateChange", EventCallback_Common(&onPlayerStateChange));
		EventManager::Instance().Register("onPlayerClickMap", EventCallback_Common(&onPlayerClickMap));
		EventManager::Instance().Register("onPlayerClickPlayer", EventCallback_Common(&onPlayerClickPlayer));
		EventManager::Instance().Register("onClientCheckResponse", EventCallback_Common(&onClientCheckResponse));
		EventManager::Instance().Register("onPlayerUpdate", EventCallback_Common(&onPlayerUpdate));
		EventManager::Instance().Register("onVehicleStreamIn", EventCallback_Common(&onVehicleStreamIn));
		EventManager::Instance().Register("onVehicleStreamOut", EventCallback_Common(&onVehicleStreamOut));
		EventManager::Instance().Register("onVehicleDeath", EventCallback_Common(&onVehicleDeath));
		EventManager::Instance().Register("onPlayerEnterVehicle", EventCallback_Common(&onPlayerEnterVehicle));
		EventManager::Instance().Register("onPlayerExitVehicle", EventCallback_Common(&onPlayerExitVehicle));
		EventManager::Instance().Register("onVehicleDamageStatusUpdate", EventCallback_Common(&onVehicleDamageStatusUpdate));
		EventManager::Instance().Register("onVehiclePaintJob", EventCallback_Common(&onVehiclePaintJob));
		EventManager::Instance().Register("onVehicleMod", EventCallback_Common(&onVehicleMod));
		EventManager::Instance().Register("onVehicleRespray", EventCallback_Common(&onVehicleRespray));
		EventManager::Instance().Register("onEnterExitModShop", EventCallback_Common(&onEnterExitModShop));
		EventManager::Instance().Register("onVehicleSpawn", EventCallback_Common(&onVehicleSpawn));
		EventManager::Instance().Register("onUnoccupiedVehicleUpdate", EventCallback_Common(&onUnoccupiedVehicleUpdate));
		EventManager::Instance().Register("onTrailerUpdate", EventCallback_Common(&onTrailerUpdate));
		EventManager::Instance().Register("onVehicleSirenStateChange", EventCallback_Common(&onVehicleSirenStateChange));
	}

	static bool onPlayerGiveDamageActor(EventArgs_onPlayerGiveDamageActor* args)
	{
		return Runtime::Instance().DispatchEvents("playerGiveDamageActor", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->actor)), *(args->list->amount), *(args->list->weapon), *(args->list->part));
	}

	static bool onActorStreamIn(EventArgs_onActorStreamIn* args)
	{
		return Runtime::Instance().DispatchEvents("actorStreamIn", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->actor)), uintptr_t(*(args->list->forPlayer)));
	}

	static bool onActorStreamOut(EventArgs_onActorStreamOut* args)
	{
		return Runtime::Instance().DispatchEvents("actorStreamOut", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->actor)), uintptr_t(*(args->list->forPlayer)));
	}

	static bool onPlayerEnterCheckpoint(EventArgs_onPlayerEnterCheckpoint* args)
	{
		return Runtime::Instance().DispatchEvents("playerEnterCheckpoint", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)));
	}

	static bool onPlayerLeaveCheckpoint(EventArgs_onPlayerLeaveCheckpoint* args)
	{
		return Runtime::Instance().DispatchEvents("playerLeaveCheckpoint", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)));
	}

	static bool onPlayerEnterRaceCheckpoint(EventArgs_onPlayerEnterRaceCheckpoint* args)
	{
		return Runtime::Instance().DispatchEvents("playerEnterRaceCheckpoint", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)));
	}

	static bool onPlayerLeaveRaceCheckpoint(EventArgs_onPlayerLeaveRaceCheckpoint* args)
	{
		return Runtime::Instance().DispatchEvents("playerLeaveRaceCheckpoint", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)));
	}

	static bool onPlayerRequestClass(EventArgs_onPlayerRequestClass* args)
	{
		return Runtime::Instance().DispatchEvents("playerRequestClass", true, OmpNodeEventBadRet::False, uintptr_t(*(args->list->player)), *(args->list->classId));
	}

	static bool onConsoleText(EventArgs_onConsoleText* args)
	{
		return Runtime::Instance().DispatchEvents("consoleText", true, OmpNodeEventBadRet::True, *(args->list->command), *(args->list->parameters));
	}

	static bool onRconLoginAttempt(EventArgs_onRconLoginAttempt* args)
	{
		return Runtime::Instance().DispatchEvents("rconLoginAttempt", true, OmpNodeEventBadRet::True, *(args->list->address), *(args->list->password), *(args->list->success));
	}

	static bool onPlayerFinishedDownloading(EventArgs_onPlayerFinishedDownloading* args)
	{
		return Runtime::Instance().DispatchEvents("playerFinishedDownloading", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->vw));
	}

	static bool onPlayerRequestDownload(EventArgs_onPlayerRequestDownload* args)
	{
		return Runtime::Instance().DispatchEvents("playerRequestDownload", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->type), *(args->list->checksum));
	}

	static bool onDialogResponse(EventArgs_onDialogResponse* args)
	{
		return Runtime::Instance().DispatchEvents("dialogResponse", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->dialogId), *(args->list->response), *(args->list->listItem), *(args->list->inputText));
	}

	static bool onPlayerEnterGangZone(EventArgs_onPlayerEnterGangZone* args)
	{
		return Runtime::Instance().DispatchEvents("playerEnterGangZone", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->zone)));
	}

	static bool onPlayerLeaveGangZone(EventArgs_onPlayerLeaveGangZone* args)
	{
		return Runtime::Instance().DispatchEvents("playerLeaveGangZone", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->zone)));
	}

	static bool onPlayerClickGangZone(EventArgs_onPlayerClickGangZone* args)
	{
		return Runtime::Instance().DispatchEvents("playerClickGangZone", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->zone)));
	}

	static bool onPlayerSelectedMenuRow(EventArgs_onPlayerSelectedMenuRow* args)
	{
		return Runtime::Instance().DispatchEvents("playerSelectedMenuRow", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->row));
	}

	static bool onPlayerExitedMenu(EventArgs_onPlayerExitedMenu* args)
	{
		return Runtime::Instance().DispatchEvents("playerExitedMenu", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)));
	}

	static bool onObjectMove(EventArgs_onObjectMove* args)
	{
		return Runtime::Instance().DispatchEvents("objectMove", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->object)));
	}

	static bool onPlayerObjectMove(EventArgs_onPlayerObjectMove* args)
	{
		return Runtime::Instance().DispatchEvents("playerObjectMove", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->object)));
	}

	static bool onPlayerEditObject(EventArgs_onPlayerEditObject* args)
	{
		return Runtime::Instance().DispatchEvents("playerEditObject", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->object)), *(args->list->response), *(args->list->offsetX), *(args->list->offsetY), *(args->list->offsetZ), *(args->list->rotationX), *(args->list->rotationY), *(args->list->rotationZ));
	}

	static bool onPlayerEditPlayerObject(EventArgs_onPlayerEditPlayerObject* args)
	{
		return Runtime::Instance().DispatchEvents("playerEditPlayerObject", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->object)), *(args->list->response), *(args->list->offsetX), *(args->list->offsetY), *(args->list->offsetZ), *(args->list->rotationX), *(args->list->rotationY), *(args->list->rotationZ));
	}

	static bool onPlayerEditAttachedObject(EventArgs_onPlayerEditAttachedObject* args)
	{
		return Runtime::Instance().DispatchEvents("playerEditAttachedObject", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->saved), *(args->list->index), *(args->list->model), *(args->list->bone), *(args->list->offsetX), *(args->list->offsetY), *(args->list->offsetZ), *(args->list->rotationX), *(args->list->rotationY), *(args->list->rotationZ), *(args->list->scaleX), *(args->list->scaleY), *(args->list->scaleZ));
	}

	static bool onPlayerSelectObject(EventArgs_onPlayerSelectObject* args)
	{
		return Runtime::Instance().DispatchEvents("playerSelectObject", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->object)), *(args->list->model), *(args->list->x), *(args->list->y), *(args->list->z));
	}

	static bool onPlayerSelectPlayerObject(EventArgs_onPlayerSelectPlayerObject* args)
	{
		return Runtime::Instance().DispatchEvents("playerSelectPlayerObject", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->object)), *(args->list->model), *(args->list->x), *(args->list->y), *(args->list->z));
	}

	static bool onPlayerPickUpPickup(EventArgs_onPlayerPickUpPickup* args)
	{
		return Runtime::Instance().DispatchEvents("playerPickUpPickup", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->pickup)));
	}

	static bool onPlayerCancelTextDrawSelection(EventArgs_onPlayerCancelTextDrawSelection* args)
	{
		return Runtime::Instance().DispatchEvents("playerCancelTextDrawSelection", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)));
	}

	static bool onPlayerCancelPlayerTextDrawSelection(EventArgs_onPlayerCancelPlayerTextDrawSelection* args)
	{
		return Runtime::Instance().DispatchEvents("playerCancelPlayerTextDrawSelection", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)));
	}

	static bool onPlayerClickTextDraw(EventArgs_onPlayerClickTextDraw* args)
	{
		return Runtime::Instance().DispatchEvents("playerClickTextDraw", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->textdraw)));
	}

	static bool onPlayerClickPlayerTextDraw(EventArgs_onPlayerClickPlayerTextDraw* args)
	{
		return Runtime::Instance().DispatchEvents("playerClickPlayerTextDraw", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->textdraw)));
	}

	static bool onPlayerConnect(EventArgs_onPlayerConnect* args)
	{
		return Runtime::Instance().DispatchEvents("playerConnect", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)));
	}

	static bool onPlayerSpawn(EventArgs_onPlayerSpawn* args)
	{
		return Runtime::Instance().DispatchEvents("playerSpawn", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)));
	}

	static bool onPlayerCommandText(EventArgs_onPlayerCommandText* args)
	{
		return Runtime::Instance().DispatchEvents("playerCommandText", true, OmpNodeEventBadRet::True, uintptr_t(*(args->list->player)), *(args->list->command));
	}

	static bool onPlayerKeyStateChange(EventArgs_onPlayerKeyStateChange* args)
	{
		return Runtime::Instance().DispatchEvents("playerKeyStateChange", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->newKeys), *(args->list->oldKeys));
	}

	static bool onIncomingConnection(EventArgs_onIncomingConnection* args)
	{
		return Runtime::Instance().DispatchEvents("incomingConnection", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->ipAddress), *(args->list->port));
	}

	static bool onPlayerDisconnect(EventArgs_onPlayerDisconnect* args)
	{
		return Runtime::Instance().DispatchEvents("playerDisconnect", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->reason));
	}

	static bool onPlayerRequestSpawn(EventArgs_onPlayerRequestSpawn* args)
	{
		return Runtime::Instance().DispatchEvents("playerRequestSpawn", true, OmpNodeEventBadRet::False, uintptr_t(*(args->list->player)));
	}

	static bool onPlayerStreamIn(EventArgs_onPlayerStreamIn* args)
	{
		return Runtime::Instance().DispatchEvents("playerStreamIn", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->forPlayer)));
	}

	static bool onPlayerStreamOut(EventArgs_onPlayerStreamOut* args)
	{
		return Runtime::Instance().DispatchEvents("playerStreamOut", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->forPlayer)));
	}

	static bool onPlayerText(EventArgs_onPlayerText* args)
	{
		return Runtime::Instance().DispatchEvents("playerText", true, OmpNodeEventBadRet::False, uintptr_t(*(args->list->player)), *(args->list->text));
	}

	static bool onPlayerShotMissed(EventArgs_onPlayerShotMissed* args)
	{
		return Runtime::Instance().DispatchEvents("playerShotMissed", true, OmpNodeEventBadRet::False, uintptr_t(*(args->list->player)), *(args->list->weapon), *(args->list->x), *(args->list->y), *(args->list->z));
	}

	static bool onPlayerShotPlayer(EventArgs_onPlayerShotPlayer* args)
	{
		return Runtime::Instance().DispatchEvents("playerShotPlayer", true, OmpNodeEventBadRet::False, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->target)), *(args->list->weapon), *(args->list->x), *(args->list->y), *(args->list->z));
	}

	static bool onPlayerShotVehicle(EventArgs_onPlayerShotVehicle* args)
	{
		return Runtime::Instance().DispatchEvents("playerShotVehicle", true, OmpNodeEventBadRet::False, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->target)), *(args->list->weapon), *(args->list->x), *(args->list->y), *(args->list->z));
	}

	static bool onPlayerShotObject(EventArgs_onPlayerShotObject* args)
	{
		return Runtime::Instance().DispatchEvents("playerShotObject", true, OmpNodeEventBadRet::False, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->target)), *(args->list->weapon), *(args->list->x), *(args->list->y), *(args->list->z));
	}

	static bool onPlayerShotPlayerObject(EventArgs_onPlayerShotPlayerObject* args)
	{
		return Runtime::Instance().DispatchEvents("playerShotPlayerObject", true, OmpNodeEventBadRet::False, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->target)), *(args->list->weapon), *(args->list->x), *(args->list->y), *(args->list->z));
	}

	static bool onPlayerDeath(EventArgs_onPlayerDeath* args)
	{
		return Runtime::Instance().DispatchEvents("playerDeath", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->killer)), *(args->list->reason));
	}

	static bool onPlayerTakeDamage(EventArgs_onPlayerTakeDamage* args)
	{
		return Runtime::Instance().DispatchEvents("playerTakeDamage", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->from)), *(args->list->amount), *(args->list->weapon), *(args->list->bodypart));
	}

	static bool onPlayerGiveDamage(EventArgs_onPlayerGiveDamage* args)
	{
		return Runtime::Instance().DispatchEvents("playerGiveDamage", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->to)), *(args->list->amount), *(args->list->weapon), *(args->list->bodypart));
	}

	static bool onPlayerInteriorChange(EventArgs_onPlayerInteriorChange* args)
	{
		return Runtime::Instance().DispatchEvents("playerInteriorChange", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->newInterior), *(args->list->oldInterior));
	}

	static bool onPlayerStateChange(EventArgs_onPlayerStateChange* args)
	{
		return Runtime::Instance().DispatchEvents("playerStateChange", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->newState), *(args->list->oldState));
	}

	static bool onPlayerClickMap(EventArgs_onPlayerClickMap* args)
	{
		return Runtime::Instance().DispatchEvents("playerClickMap", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->x), *(args->list->y), *(args->list->z));
	}

	static bool onPlayerClickPlayer(EventArgs_onPlayerClickPlayer* args)
	{
		return Runtime::Instance().DispatchEvents("playerClickPlayer", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->clicked)), *(args->list->source));
	}

	static bool onClientCheckResponse(EventArgs_onClientCheckResponse* args)
	{
		return Runtime::Instance().DispatchEvents("clientCheckResponse", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->actionType), *(args->list->address), *(args->list->result));
	}

	static bool onPlayerUpdate(EventArgs_onPlayerUpdate* args)
	{
		return Runtime::Instance().DispatchEvents("playerUpdate", true, OmpNodeEventBadRet::False, uintptr_t(*(args->list->player)));
	}

	static bool onVehicleStreamIn(EventArgs_onVehicleStreamIn* args)
	{
		return Runtime::Instance().DispatchEvents("vehicleStreamIn", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->vehicle)), uintptr_t(*(args->list->player)));
	}

	static bool onVehicleStreamOut(EventArgs_onVehicleStreamOut* args)
	{
		return Runtime::Instance().DispatchEvents("vehicleStreamOut", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->vehicle)), uintptr_t(*(args->list->player)));
	}

	static bool onVehicleDeath(EventArgs_onVehicleDeath* args)
	{
		return Runtime::Instance().DispatchEvents("vehicleDeath", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->vehicle)), uintptr_t(*(args->list->player)));
	}

	static bool onPlayerEnterVehicle(EventArgs_onPlayerEnterVehicle* args)
	{
		return Runtime::Instance().DispatchEvents("playerEnterVehicle", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->vehicle)), *(args->list->passenger));
	}

	static bool onPlayerExitVehicle(EventArgs_onPlayerExitVehicle* args)
	{
		return Runtime::Instance().DispatchEvents("playerExitVehicle", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->vehicle)));
	}

	static bool onVehicleDamageStatusUpdate(EventArgs_onVehicleDamageStatusUpdate* args)
	{
		return Runtime::Instance().DispatchEvents("vehicleDamageStatusUpdate", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->vehicle)), uintptr_t(*(args->list->player)));
	}

	static bool onVehiclePaintJob(EventArgs_onVehiclePaintJob* args)
	{
		return Runtime::Instance().DispatchEvents("vehiclePaintJob", true, OmpNodeEventBadRet::False, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->vehicle)), *(args->list->paintJob));
	}

	static bool onVehicleMod(EventArgs_onVehicleMod* args)
	{
		return Runtime::Instance().DispatchEvents("vehicleMod", true, OmpNodeEventBadRet::False, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->vehicle)), *(args->list->component));
	}

	static bool onVehicleRespray(EventArgs_onVehicleRespray* args)
	{
		return Runtime::Instance().DispatchEvents("vehicleRespray", true, OmpNodeEventBadRet::False, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->vehicle)), *(args->list->color1), *(args->list->color2));
	}

	static bool onEnterExitModShop(EventArgs_onEnterExitModShop* args)
	{
		return Runtime::Instance().DispatchEvents("enterExitModShop", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->enterexit), *(args->list->interiorId));
	}

	static bool onVehicleSpawn(EventArgs_onVehicleSpawn* args)
	{
		return Runtime::Instance().DispatchEvents("vehicleSpawn", true, OmpNodeEventBadRet::None, uintptr_t(*(args->list->vehicle)));
	}

	static bool onUnoccupiedVehicleUpdate(EventArgs_onUnoccupiedVehicleUpdate* args)
	{
		return Runtime::Instance().DispatchEvents("unoccupiedVehicleUpdate", true, OmpNodeEventBadRet::False, uintptr_t(*(args->list->vehicle)), uintptr_t(*(args->list->player)), *(args->list->seat), *(args->list->posX), *(args->list->posY), *(args->list->posZ), *(args->list->velocityX), *(args->list->velocityY), *(args->list->velocityZ));
	}

	static bool onTrailerUpdate(EventArgs_onTrailerUpdate* args)
	{
		return Runtime::Instance().DispatchEvents("trailerUpdate", true, OmpNodeEventBadRet::False, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->trailer)));
	}

	static bool onVehicleSirenStateChange(EventArgs_onVehicleSirenStateChange* args)
	{
		return Runtime::Instance().DispatchEvents("vehicleSirenStateChange", true, OmpNodeEventBadRet::False, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->vehicle)), *(args->list->sirenState));
	}
};

OMP_NODE_Events OMP_NODE_Events_instance;
