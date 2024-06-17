#include "./Impl.hpp"

class OMP_NODE_Events
{
public:
    OMP_NODE_Events()
    {
        EventManager::Instance().Register("playerGiveDamageActor", EventCallback_Common(&onPlayerGiveDamageActor));
        EventManager::Instance().Register("actorStreamIn", EventCallback_Common(&onActorStreamIn));
        EventManager::Instance().Register("actorStreamOut", EventCallback_Common(&onActorStreamOut));
        EventManager::Instance().Register("playerEnterCheckpoint", EventCallback_Common(&onPlayerEnterCheckpoint));
        EventManager::Instance().Register("playerLeaveCheckpoint", EventCallback_Common(&onPlayerLeaveCheckpoint));
        EventManager::Instance().Register("playerEnterRaceCheckpoint", EventCallback_Common(&onPlayerEnterRaceCheckpoint));
        EventManager::Instance().Register("playerLeaveRaceCheckpoint", EventCallback_Common(&onPlayerLeaveRaceCheckpoint));
        EventManager::Instance().Register("playerRequestClass", EventCallback_Common(&onPlayerRequestClass));
        EventManager::Instance().Register("consoleText", EventCallback_Common(&onConsoleText));
        EventManager::Instance().Register("rconLoginAttempt", EventCallback_Common(&onRconLoginAttempt));
        EventManager::Instance().Register("tick", EventCallback_Common(&onTick));
        EventManager::Instance().Register("playerFinishedDownloading", EventCallback_Common(&onPlayerFinishedDownloading));
        EventManager::Instance().Register("playerRequestDownload", EventCallback_Common(&onPlayerRequestDownload));
        EventManager::Instance().Register("dialogResponse", EventCallback_Common(&onDialogResponse));
        EventManager::Instance().Register("playerEnterGangZone", EventCallback_Common(&onPlayerEnterGangZone));
        EventManager::Instance().Register("playerLeaveGangZone", EventCallback_Common(&onPlayerLeaveGangZone));
        EventManager::Instance().Register("playerClickGangZone", EventCallback_Common(&onPlayerClickGangZone));
        EventManager::Instance().Register("playerSelectedMenuRow", EventCallback_Common(&onPlayerSelectedMenuRow));
        EventManager::Instance().Register("playerExitedMenu", EventCallback_Common(&onPlayerExitedMenu));
        EventManager::Instance().Register("objectMove", EventCallback_Common(&onObjectMove));
        EventManager::Instance().Register("playerObjectMove", EventCallback_Common(&onPlayerObjectMove));
        EventManager::Instance().Register("playerEditObject", EventCallback_Common(&onPlayerEditObject));
        EventManager::Instance().Register("playerEditPlayerObject", EventCallback_Common(&onPlayerEditPlayerObject));
        EventManager::Instance().Register("playerEditAttachedObject", EventCallback_Common(&onPlayerEditAttachedObject));
        EventManager::Instance().Register("playerSelectObject", EventCallback_Common(&onPlayerSelectObject));
        EventManager::Instance().Register("playerSelectPlayerObject", EventCallback_Common(&onPlayerSelectPlayerObject));
        EventManager::Instance().Register("playerPickUpPickup", EventCallback_Common(&onPlayerPickUpPickup));
        EventManager::Instance().Register("playerCancelTextDrawSelection", EventCallback_Common(&onPlayerCancelTextDrawSelection));
        EventManager::Instance().Register("playerCancelPlayerTextDrawSelection", EventCallback_Common(&onPlayerCancelPlayerTextDrawSelection));
        EventManager::Instance().Register("playerClickTextDraw", EventCallback_Common(&onPlayerClickTextDraw));
        EventManager::Instance().Register("playerClickPlayerTextDraw", EventCallback_Common(&onPlayerClickPlayerTextDraw));
        EventManager::Instance().Register("playerConnect", EventCallback_Common(&onPlayerConnect));
        EventManager::Instance().Register("playerSpawn", EventCallback_Common(&onPlayerSpawn));
        EventManager::Instance().Register("playerCommandText", EventCallback_Common(&onPlayerCommandText));
        EventManager::Instance().Register("playerKeyStateChange", EventCallback_Common(&onPlayerKeyStateChange));
        EventManager::Instance().Register("incomingConnection", EventCallback_Common(&onIncomingConnection));
        EventManager::Instance().Register("playerDisconnect", EventCallback_Common(&onPlayerDisconnect));
        EventManager::Instance().Register("playerRequestSpawn", EventCallback_Common(&onPlayerRequestSpawn));
        EventManager::Instance().Register("playerStreamIn", EventCallback_Common(&onPlayerStreamIn));
        EventManager::Instance().Register("playerStreamOut", EventCallback_Common(&onPlayerStreamOut));
        EventManager::Instance().Register("playerText", EventCallback_Common(&onPlayerText));
        EventManager::Instance().Register("playerShotMissed", EventCallback_Common(&onPlayerShotMissed));
        EventManager::Instance().Register("playerShotPlayer", EventCallback_Common(&onPlayerShotPlayer));
        EventManager::Instance().Register("playerShotVehicle", EventCallback_Common(&onPlayerShotVehicle));
        EventManager::Instance().Register("playerShotObject", EventCallback_Common(&onPlayerShotObject));
        EventManager::Instance().Register("playerShotPlayerObject", EventCallback_Common(&onPlayerShotPlayerObject));
        EventManager::Instance().Register("playerDeath", EventCallback_Common(&onPlayerDeath));
        EventManager::Instance().Register("playerTakeDamage", EventCallback_Common(&onPlayerTakeDamage));
        EventManager::Instance().Register("playerGiveDamage", EventCallback_Common(&onPlayerGiveDamage));
        EventManager::Instance().Register("playerInteriorChange", EventCallback_Common(&onPlayerInteriorChange));
        EventManager::Instance().Register("playerStateChange", EventCallback_Common(&onPlayerStateChange));
        EventManager::Instance().Register("playerClickMap", EventCallback_Common(&onPlayerClickMap));
        EventManager::Instance().Register("playerClickPlayer", EventCallback_Common(&onPlayerClickPlayer));
        EventManager::Instance().Register("clientCheckResponse", EventCallback_Common(&onClientCheckResponse));
        EventManager::Instance().Register("playerUpdate", EventCallback_Common(&onPlayerUpdate));
        EventManager::Instance().Register("vehicleStreamIn", EventCallback_Common(&onVehicleStreamIn));
        EventManager::Instance().Register("vehicleStreamOut", EventCallback_Common(&onVehicleStreamOut));
        EventManager::Instance().Register("vehicleDeath", EventCallback_Common(&onVehicleDeath));
        EventManager::Instance().Register("playerEnterVehicle", EventCallback_Common(&onPlayerEnterVehicle));
        EventManager::Instance().Register("playerExitVehicle", EventCallback_Common(&onPlayerExitVehicle));
        EventManager::Instance().Register("vehicleDamageStatusUpdate", EventCallback_Common(&onVehicleDamageStatusUpdate));
        EventManager::Instance().Register("vehiclePaintJob", EventCallback_Common(&onVehiclePaintJob));
        EventManager::Instance().Register("vehicleMod", EventCallback_Common(&onVehicleMod));
        EventManager::Instance().Register("vehicleRespray", EventCallback_Common(&onVehicleRespray));
        EventManager::Instance().Register("enterExitModShop", EventCallback_Common(&onEnterExitModShop));
        EventManager::Instance().Register("vehicleSpawn", EventCallback_Common(&onVehicleSpawn));
        EventManager::Instance().Register("unoccupiedVehicleUpdate", EventCallback_Common(&onUnoccupiedVehicleUpdate));
        EventManager::Instance().Register("trailerUpdate", EventCallback_Common(&onTrailerUpdate));
        EventManager::Instance().Register("vehicleSirenStateChange", EventCallback_Common(&onVehicleSirenStateChange));
    }

    static bool onPlayerGiveDamageActor(EventArgs_onPlayerGiveDamageActor* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerGiveDamageActor", true, EventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->actor)), *(args->list->amount), *(args->list->weapon), *(args->list->part));
    }

    static bool onActorStreamIn(EventArgs_onActorStreamIn* args)
    {
        return Runtime::Instance().DispatchEvents("ActorStreamIn", true, EventBadRet::None, uintptr_t(*(args->list->actor)), uintptr_t(*(args->list->forPlayer)));
    }

    static bool onActorStreamOut(EventArgs_onActorStreamOut* args)
    {
        return Runtime::Instance().DispatchEvents("ActorStreamOut", true, EventBadRet::None, uintptr_t(*(args->list->actor)), uintptr_t(*(args->list->forPlayer)));
    }

    static bool onPlayerEnterCheckpoint(EventArgs_onPlayerEnterCheckpoint* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerEnterCheckpoint", true, EventBadRet::None, uintptr_t(*(args->list->player)));
    }

    static bool onPlayerLeaveCheckpoint(EventArgs_onPlayerLeaveCheckpoint* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerLeaveCheckpoint", true, EventBadRet::None, uintptr_t(*(args->list->player)));
    }

    static bool onPlayerEnterRaceCheckpoint(EventArgs_onPlayerEnterRaceCheckpoint* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerEnterRaceCheckpoint", true, EventBadRet::None, uintptr_t(*(args->list->player)));
    }

    static bool onPlayerLeaveRaceCheckpoint(EventArgs_onPlayerLeaveRaceCheckpoint* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerLeaveRaceCheckpoint", true, EventBadRet::None, uintptr_t(*(args->list->player)));
    }

    static bool onPlayerRequestClass(EventArgs_onPlayerRequestClass* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerRequestClass", true, EventBadRet::False, uintptr_t(*(args->list->player)), *(args->list->classId));
    }

    static bool onConsoleText(EventArgs_onConsoleText* args)
    {
        return Runtime::Instance().DispatchEvents("ConsoleText", true, EventBadRet::True, *(args->list->command), *(args->list->parameters));
    }

    static bool onRconLoginAttempt(EventArgs_onRconLoginAttempt* args)
    {
        return Runtime::Instance().DispatchEvents("RconLoginAttempt", true, EventBadRet::True, *(args->list->address), *(args->list->password), *(args->list->success));
    }

    static bool onTick(EventArgs_onTick* args)
    {
        return Runtime::Instance().DispatchEvents("Tick", true, EventBadRet::None, *(args->list->elapsed));
    }

    static bool onPlayerFinishedDownloading(EventArgs_onPlayerFinishedDownloading* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerFinishedDownloading", true, EventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->vw));
    }

    static bool onPlayerRequestDownload(EventArgs_onPlayerRequestDownload* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerRequestDownload", true, EventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->type), *(args->list->checksum));
    }

    static bool onDialogResponse(EventArgs_onDialogResponse* args)
    {
        return Runtime::Instance().DispatchEvents("DialogResponse", true, EventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->dialogId), *(args->list->response), *(args->list->listItem), *(args->list->inputText));
    }

    static bool onPlayerEnterGangZone(EventArgs_onPlayerEnterGangZone* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerEnterGangZone", true, EventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->zone)));
    }

    static bool onPlayerLeaveGangZone(EventArgs_onPlayerLeaveGangZone* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerLeaveGangZone", true, EventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->zone)));
    }

    static bool onPlayerClickGangZone(EventArgs_onPlayerClickGangZone* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerClickGangZone", true, EventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->zone)));
    }

    static bool onPlayerSelectedMenuRow(EventArgs_onPlayerSelectedMenuRow* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerSelectedMenuRow", true, EventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->row));
    }

    static bool onPlayerExitedMenu(EventArgs_onPlayerExitedMenu* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerExitedMenu", true, EventBadRet::None, uintptr_t(*(args->list->player)));
    }

    static bool onObjectMove(EventArgs_onObjectMove* args)
    {
        return Runtime::Instance().DispatchEvents("ObjectMove", true, EventBadRet::None, uintptr_t(*(args->list->object)));
    }

    static bool onPlayerObjectMove(EventArgs_onPlayerObjectMove* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerObjectMove", true, EventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->object)));
    }

    static bool onPlayerEditObject(EventArgs_onPlayerEditObject* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerEditObject", true, EventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->object)), *(args->list->response), *(args->list->offsetX), *(args->list->offsetY), *(args->list->offsetZ), *(args->list->rotationX), *(args->list->rotationY), *(args->list->rotationZ));
    }

    static bool onPlayerEditPlayerObject(EventArgs_onPlayerEditPlayerObject* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerEditPlayerObject", true, EventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->object)), *(args->list->response), *(args->list->offsetX), *(args->list->offsetY), *(args->list->offsetZ), *(args->list->rotationX), *(args->list->rotationY), *(args->list->rotationZ));
    }

    static bool onPlayerEditAttachedObject(EventArgs_onPlayerEditAttachedObject* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerEditAttachedObject", true, EventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->saved), *(args->list->index), *(args->list->model), *(args->list->bone), *(args->list->offsetX), *(args->list->offsetY), *(args->list->offsetZ), *(args->list->rotationX), *(args->list->rotationY), *(args->list->rotationZ), *(args->list->scaleX), *(args->list->scaleY), *(args->list->scaleZ));
    }

    static bool onPlayerSelectObject(EventArgs_onPlayerSelectObject* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerSelectObject", true, EventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->object)), *(args->list->model), *(args->list->x), *(args->list->y), *(args->list->z));
    }

    static bool onPlayerSelectPlayerObject(EventArgs_onPlayerSelectPlayerObject* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerSelectPlayerObject", true, EventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->object)), *(args->list->model), *(args->list->x), *(args->list->y), *(args->list->z));
    }

    static bool onPlayerPickUpPickup(EventArgs_onPlayerPickUpPickup* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerPickUpPickup", true, EventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->pickup)));
    }

    static bool onPlayerCancelTextDrawSelection(EventArgs_onPlayerCancelTextDrawSelection* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerCancelTextDrawSelection", true, EventBadRet::None, uintptr_t(*(args->list->player)));
    }

    static bool onPlayerCancelPlayerTextDrawSelection(EventArgs_onPlayerCancelPlayerTextDrawSelection* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerCancelPlayerTextDrawSelection", true, EventBadRet::None, uintptr_t(*(args->list->player)));
    }

    static bool onPlayerClickTextDraw(EventArgs_onPlayerClickTextDraw* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerClickTextDraw", true, EventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->textdraw)));
    }

    static bool onPlayerClickPlayerTextDraw(EventArgs_onPlayerClickPlayerTextDraw* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerClickPlayerTextDraw", true, EventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->textdraw)));
    }

    static bool onPlayerConnect(EventArgs_onPlayerConnect* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerConnect", true, EventBadRet::None, uintptr_t(*(args->list->player)));
    }

    static bool onPlayerSpawn(EventArgs_onPlayerSpawn* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerSpawn", true, EventBadRet::None, uintptr_t(*(args->list->player)));
    }

    static bool onPlayerCommandText(EventArgs_onPlayerCommandText* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerCommandText", true, EventBadRet::True, uintptr_t(*(args->list->player)), *(args->list->command));
    }

    static bool onPlayerKeyStateChange(EventArgs_onPlayerKeyStateChange* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerKeyStateChange", true, EventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->newKeys), *(args->list->oldKeys));
    }

    static bool onIncomingConnection(EventArgs_onIncomingConnection* args)
    {
        return Runtime::Instance().DispatchEvents("IncomingConnection", true, EventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->ipAddress), *(args->list->port));
    }

    static bool onPlayerDisconnect(EventArgs_onPlayerDisconnect* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerDisconnect", true, EventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->reason));
    }

    static bool onPlayerRequestSpawn(EventArgs_onPlayerRequestSpawn* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerRequestSpawn", true, EventBadRet::False, uintptr_t(*(args->list->player)));
    }

    static bool onPlayerStreamIn(EventArgs_onPlayerStreamIn* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerStreamIn", true, EventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->forPlayer)));
    }

    static bool onPlayerStreamOut(EventArgs_onPlayerStreamOut* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerStreamOut", true, EventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->forPlayer)));
    }

    static bool onPlayerText(EventArgs_onPlayerText* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerText", true, EventBadRet::False, uintptr_t(*(args->list->player)), *(args->list->text));
    }

    static bool onPlayerShotMissed(EventArgs_onPlayerShotMissed* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerShotMissed", true, EventBadRet::False, uintptr_t(*(args->list->player)), *(args->list->weapon), *(args->list->x), *(args->list->y), *(args->list->z));
    }

    static bool onPlayerShotPlayer(EventArgs_onPlayerShotPlayer* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerShotPlayer", true, EventBadRet::False, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->target)), *(args->list->weapon), *(args->list->x), *(args->list->y), *(args->list->z));
    }

    static bool onPlayerShotVehicle(EventArgs_onPlayerShotVehicle* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerShotVehicle", true, EventBadRet::False, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->target)), *(args->list->weapon), *(args->list->x), *(args->list->y), *(args->list->z));
    }

    static bool onPlayerShotObject(EventArgs_onPlayerShotObject* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerShotObject", true, EventBadRet::False, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->target)), *(args->list->weapon), *(args->list->x), *(args->list->y), *(args->list->z));
    }

    static bool onPlayerShotPlayerObject(EventArgs_onPlayerShotPlayerObject* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerShotPlayerObject", true, EventBadRet::False, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->target)), *(args->list->weapon), *(args->list->x), *(args->list->y), *(args->list->z));
    }

    static bool onPlayerDeath(EventArgs_onPlayerDeath* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerDeath", true, EventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->killer)), *(args->list->reason));
    }

    static bool onPlayerTakeDamage(EventArgs_onPlayerTakeDamage* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerTakeDamage", true, EventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->from)), *(args->list->amount), *(args->list->weapon), *(args->list->bodypart));
    }

    static bool onPlayerGiveDamage(EventArgs_onPlayerGiveDamage* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerGiveDamage", true, EventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->to)), *(args->list->amount), *(args->list->weapon), *(args->list->bodypart));
    }

    static bool onPlayerInteriorChange(EventArgs_onPlayerInteriorChange* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerInteriorChange", true, EventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->newInterior), *(args->list->oldInterior));
    }

    static bool onPlayerStateChange(EventArgs_onPlayerStateChange* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerStateChange", true, EventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->newState), *(args->list->oldState));
    }

    static bool onPlayerClickMap(EventArgs_onPlayerClickMap* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerClickMap", true, EventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->x), *(args->list->y), *(args->list->z));
    }

    static bool onPlayerClickPlayer(EventArgs_onPlayerClickPlayer* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerClickPlayer", true, EventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->clicked)), *(args->list->source));
    }

    static bool onClientCheckResponse(EventArgs_onClientCheckResponse* args)
    {
        return Runtime::Instance().DispatchEvents("ClientCheckResponse", true, EventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->actionType), *(args->list->address), *(args->list->result));
    }

    static bool onPlayerUpdate(EventArgs_onPlayerUpdate* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerUpdate", true, EventBadRet::False, uintptr_t(*(args->list->player)));
    }

    static bool onVehicleStreamIn(EventArgs_onVehicleStreamIn* args)
    {
        return Runtime::Instance().DispatchEvents("VehicleStreamIn", true, EventBadRet::None, uintptr_t(*(args->list->vehicle)), uintptr_t(*(args->list->player)));
    }

    static bool onVehicleStreamOut(EventArgs_onVehicleStreamOut* args)
    {
        return Runtime::Instance().DispatchEvents("VehicleStreamOut", true, EventBadRet::None, uintptr_t(*(args->list->vehicle)), uintptr_t(*(args->list->player)));
    }

    static bool onVehicleDeath(EventArgs_onVehicleDeath* args)
    {
        return Runtime::Instance().DispatchEvents("VehicleDeath", true, EventBadRet::None, uintptr_t(*(args->list->vehicle)), uintptr_t(*(args->list->player)));
    }

    static bool onPlayerEnterVehicle(EventArgs_onPlayerEnterVehicle* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerEnterVehicle", true, EventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->vehicle)), *(args->list->passenger));
    }

    static bool onPlayerExitVehicle(EventArgs_onPlayerExitVehicle* args)
    {
        return Runtime::Instance().DispatchEvents("PlayerExitVehicle", true, EventBadRet::None, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->vehicle)));
    }

    static bool onVehicleDamageStatusUpdate(EventArgs_onVehicleDamageStatusUpdate* args)
    {
        return Runtime::Instance().DispatchEvents("VehicleDamageStatusUpdate", true, EventBadRet::None, uintptr_t(*(args->list->vehicle)), uintptr_t(*(args->list->player)));
    }

    static bool onVehiclePaintJob(EventArgs_onVehiclePaintJob* args)
    {
        return Runtime::Instance().DispatchEvents("VehiclePaintJob", true, EventBadRet::False, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->vehicle)), *(args->list->paintJob));
    }

    static bool onVehicleMod(EventArgs_onVehicleMod* args)
    {
        return Runtime::Instance().DispatchEvents("VehicleMod", true, EventBadRet::False, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->vehicle)), *(args->list->component));
    }

    static bool onVehicleRespray(EventArgs_onVehicleRespray* args)
    {
        return Runtime::Instance().DispatchEvents("VehicleRespray", true, EventBadRet::False, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->vehicle)), *(args->list->color1), *(args->list->color2));
    }

    static bool onEnterExitModShop(EventArgs_onEnterExitModShop* args)
    {
        return Runtime::Instance().DispatchEvents("EnterExitModShop", true, EventBadRet::None, uintptr_t(*(args->list->player)), *(args->list->enterexit), *(args->list->interiorId));
    }

    static bool onVehicleSpawn(EventArgs_onVehicleSpawn* args)
    {
        return Runtime::Instance().DispatchEvents("VehicleSpawn", true, EventBadRet::None, uintptr_t(*(args->list->vehicle)));
    }

    static bool onUnoccupiedVehicleUpdate(EventArgs_onUnoccupiedVehicleUpdate* args)
    {
        return Runtime::Instance().DispatchEvents("UnoccupiedVehicleUpdate", true, EventBadRet::False, uintptr_t(*(args->list->vehicle)), uintptr_t(*(args->list->player)), *(args->list->seat), *(args->list->posX), *(args->list->posY), *(args->list->posZ), *(args->list->velocityX), *(args->list->velocityY), *(args->list->velocityZ));
    }

    static bool onTrailerUpdate(EventArgs_onTrailerUpdate* args)
    {
        return Runtime::Instance().DispatchEvents("TrailerUpdate", true, EventBadRet::False, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->trailer)));
    }

    static bool onVehicleSirenStateChange(EventArgs_onVehicleSirenStateChange* args)
    {
        return Runtime::Instance().DispatchEvents("VehicleSirenStateChange", true, EventBadRet::False, uintptr_t(*(args->list->player)), uintptr_t(*(args->list->vehicle)), *(args->list->sirenState));
    }
};

OMP_NODE_Events OMP_NODE_Events_instance;
