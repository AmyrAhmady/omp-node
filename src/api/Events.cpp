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
        EventManager::Instance().Register("onTick", EventCallback_Common(&onTick));
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
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->actor))));
        argv.push_back(helpers::JSValue(*(args->list->amount)));
        argv.push_back(helpers::JSValue(*(args->list->weapon)));
        argv.push_back(helpers::JSValue(*(args->list->part)));
    }

    static bool onActorStreamIn(EventArgs_onActorStreamIn* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->actor))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->forPlayer))));
    }

    static bool onActorStreamOut(EventArgs_onActorStreamOut* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->actor))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->forPlayer))));
    }

    static bool onPlayerEnterCheckpoint(EventArgs_onPlayerEnterCheckpoint* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
    }

    static bool onPlayerLeaveCheckpoint(EventArgs_onPlayerLeaveCheckpoint* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
    }

    static bool onPlayerEnterRaceCheckpoint(EventArgs_onPlayerEnterRaceCheckpoint* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
    }

    static bool onPlayerLeaveRaceCheckpoint(EventArgs_onPlayerLeaveRaceCheckpoint* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
    }

    static bool onPlayerRequestClass(EventArgs_onPlayerRequestClass* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(*(args->list->classId)));
    }

    static bool onConsoleText(EventArgs_onConsoleText* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(*(args->list->command)));
        argv.push_back(helpers::JSValue(*(args->list->parameters)));
    }

    static bool onRconLoginAttempt(EventArgs_onRconLoginAttempt* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(*(args->list->address)));
        argv.push_back(helpers::JSValue(*(args->list->password)));
        argv.push_back(helpers::JSValue(*(args->list->success)));
    }

    static bool onTick(EventArgs_onTick* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(*(args->list->elapsed)));
    }

    static bool onPlayerFinishedDownloading(EventArgs_onPlayerFinishedDownloading* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(*(args->list->vw)));
    }

    static bool onPlayerRequestDownload(EventArgs_onPlayerRequestDownload* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(*(args->list->type)));
        argv.push_back(helpers::JSValue(*(args->list->checksum)));
    }

    static bool onDialogResponse(EventArgs_onDialogResponse* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(*(args->list->dialogId)));
        argv.push_back(helpers::JSValue(*(args->list->response)));
        argv.push_back(helpers::JSValue(*(args->list->listItem)));
        argv.push_back(helpers::JSValue(*(args->list->inputText)));
    }

    static bool onPlayerEnterGangZone(EventArgs_onPlayerEnterGangZone* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->zone))));
    }

    static bool onPlayerLeaveGangZone(EventArgs_onPlayerLeaveGangZone* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->zone))));
    }

    static bool onPlayerClickGangZone(EventArgs_onPlayerClickGangZone* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->zone))));
    }

    static bool onPlayerSelectedMenuRow(EventArgs_onPlayerSelectedMenuRow* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(*(args->list->row)));
    }

    static bool onPlayerExitedMenu(EventArgs_onPlayerExitedMenu* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
    }

    static bool onObjectMove(EventArgs_onObjectMove* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->object))));
    }

    static bool onPlayerObjectMove(EventArgs_onPlayerObjectMove* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->object))));
    }

    static bool onPlayerEditObject(EventArgs_onPlayerEditObject* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->object))));
        argv.push_back(helpers::JSValue(*(args->list->response)));
        argv.push_back(helpers::JSValue(*(args->list->offsetX)));
        argv.push_back(helpers::JSValue(*(args->list->offsetY)));
        argv.push_back(helpers::JSValue(*(args->list->offsetZ)));
        argv.push_back(helpers::JSValue(*(args->list->rotationX)));
        argv.push_back(helpers::JSValue(*(args->list->rotationY)));
        argv.push_back(helpers::JSValue(*(args->list->rotationZ)));
    }

    static bool onPlayerEditPlayerObject(EventArgs_onPlayerEditPlayerObject* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->object))));
        argv.push_back(helpers::JSValue(*(args->list->response)));
        argv.push_back(helpers::JSValue(*(args->list->offsetX)));
        argv.push_back(helpers::JSValue(*(args->list->offsetY)));
        argv.push_back(helpers::JSValue(*(args->list->offsetZ)));
        argv.push_back(helpers::JSValue(*(args->list->rotationX)));
        argv.push_back(helpers::JSValue(*(args->list->rotationY)));
        argv.push_back(helpers::JSValue(*(args->list->rotationZ)));
    }

    static bool onPlayerEditAttachedObject(EventArgs_onPlayerEditAttachedObject* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(*(args->list->saved)));
        argv.push_back(helpers::JSValue(*(args->list->index)));
        argv.push_back(helpers::JSValue(*(args->list->model)));
        argv.push_back(helpers::JSValue(*(args->list->bone)));
        argv.push_back(helpers::JSValue(*(args->list->offsetX)));
        argv.push_back(helpers::JSValue(*(args->list->offsetY)));
        argv.push_back(helpers::JSValue(*(args->list->offsetZ)));
        argv.push_back(helpers::JSValue(*(args->list->rotationX)));
        argv.push_back(helpers::JSValue(*(args->list->rotationY)));
        argv.push_back(helpers::JSValue(*(args->list->rotationZ)));
        argv.push_back(helpers::JSValue(*(args->list->scaleX)));
        argv.push_back(helpers::JSValue(*(args->list->scaleY)));
        argv.push_back(helpers::JSValue(*(args->list->scaleZ)));
    }

    static bool onPlayerSelectObject(EventArgs_onPlayerSelectObject* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->object))));
        argv.push_back(helpers::JSValue(*(args->list->model)));
        argv.push_back(helpers::JSValue(*(args->list->x)));
        argv.push_back(helpers::JSValue(*(args->list->y)));
        argv.push_back(helpers::JSValue(*(args->list->z)));
    }

    static bool onPlayerSelectPlayerObject(EventArgs_onPlayerSelectPlayerObject* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->object))));
        argv.push_back(helpers::JSValue(*(args->list->model)));
        argv.push_back(helpers::JSValue(*(args->list->x)));
        argv.push_back(helpers::JSValue(*(args->list->y)));
        argv.push_back(helpers::JSValue(*(args->list->z)));
    }

    static bool onPlayerPickUpPickup(EventArgs_onPlayerPickUpPickup* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->pickup))));
    }

    static bool onPlayerCancelTextDrawSelection(EventArgs_onPlayerCancelTextDrawSelection* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
    }

    static bool onPlayerCancelPlayerTextDrawSelection(EventArgs_onPlayerCancelPlayerTextDrawSelection* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
    }

    static bool onPlayerClickTextDraw(EventArgs_onPlayerClickTextDraw* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->textdraw))));
    }

    static bool onPlayerClickPlayerTextDraw(EventArgs_onPlayerClickPlayerTextDraw* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->textdraw))));
    }

    static bool onPlayerConnect(EventArgs_onPlayerConnect* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
    }

    static bool onPlayerSpawn(EventArgs_onPlayerSpawn* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
    }

    static bool onPlayerCommandText(EventArgs_onPlayerCommandText* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(*(args->list->command)));
    }

    static bool onPlayerKeyStateChange(EventArgs_onPlayerKeyStateChange* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(*(args->list->newKeys)));
        argv.push_back(helpers::JSValue(*(args->list->oldKeys)));
    }

    static bool onIncomingConnection(EventArgs_onIncomingConnection* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(*(args->list->ipAddress)));
        argv.push_back(helpers::JSValue(*(args->list->port)));
    }

    static bool onPlayerDisconnect(EventArgs_onPlayerDisconnect* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(*(args->list->reason)));
    }

    static bool onPlayerRequestSpawn(EventArgs_onPlayerRequestSpawn* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
    }

    static bool onPlayerStreamIn(EventArgs_onPlayerStreamIn* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->forPlayer))));
    }

    static bool onPlayerStreamOut(EventArgs_onPlayerStreamOut* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->forPlayer))));
    }

    static bool onPlayerText(EventArgs_onPlayerText* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(*(args->list->text)));
    }

    static bool onPlayerShotMissed(EventArgs_onPlayerShotMissed* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(*(args->list->weapon)));
        argv.push_back(helpers::JSValue(*(args->list->x)));
        argv.push_back(helpers::JSValue(*(args->list->y)));
        argv.push_back(helpers::JSValue(*(args->list->z)));
    }

    static bool onPlayerShotPlayer(EventArgs_onPlayerShotPlayer* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->target))));
        argv.push_back(helpers::JSValue(*(args->list->weapon)));
        argv.push_back(helpers::JSValue(*(args->list->x)));
        argv.push_back(helpers::JSValue(*(args->list->y)));
        argv.push_back(helpers::JSValue(*(args->list->z)));
    }

    static bool onPlayerShotVehicle(EventArgs_onPlayerShotVehicle* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->target))));
        argv.push_back(helpers::JSValue(*(args->list->weapon)));
        argv.push_back(helpers::JSValue(*(args->list->x)));
        argv.push_back(helpers::JSValue(*(args->list->y)));
        argv.push_back(helpers::JSValue(*(args->list->z)));
    }

    static bool onPlayerShotObject(EventArgs_onPlayerShotObject* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->target))));
        argv.push_back(helpers::JSValue(*(args->list->weapon)));
        argv.push_back(helpers::JSValue(*(args->list->x)));
        argv.push_back(helpers::JSValue(*(args->list->y)));
        argv.push_back(helpers::JSValue(*(args->list->z)));
    }

    static bool onPlayerShotPlayerObject(EventArgs_onPlayerShotPlayerObject* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->target))));
        argv.push_back(helpers::JSValue(*(args->list->weapon)));
        argv.push_back(helpers::JSValue(*(args->list->x)));
        argv.push_back(helpers::JSValue(*(args->list->y)));
        argv.push_back(helpers::JSValue(*(args->list->z)));
    }

    static bool onPlayerDeath(EventArgs_onPlayerDeath* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->killer))));
        argv.push_back(helpers::JSValue(*(args->list->reason)));
    }

    static bool onPlayerTakeDamage(EventArgs_onPlayerTakeDamage* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->from))));
        argv.push_back(helpers::JSValue(*(args->list->amount)));
        argv.push_back(helpers::JSValue(*(args->list->weapon)));
        argv.push_back(helpers::JSValue(*(args->list->bodypart)));
    }

    static bool onPlayerGiveDamage(EventArgs_onPlayerGiveDamage* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->to))));
        argv.push_back(helpers::JSValue(*(args->list->amount)));
        argv.push_back(helpers::JSValue(*(args->list->weapon)));
        argv.push_back(helpers::JSValue(*(args->list->bodypart)));
    }

    static bool onPlayerInteriorChange(EventArgs_onPlayerInteriorChange* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(*(args->list->newInterior)));
        argv.push_back(helpers::JSValue(*(args->list->oldInterior)));
    }

    static bool onPlayerStateChange(EventArgs_onPlayerStateChange* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(*(args->list->newState)));
        argv.push_back(helpers::JSValue(*(args->list->oldState)));
    }

    static bool onPlayerClickMap(EventArgs_onPlayerClickMap* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(*(args->list->x)));
        argv.push_back(helpers::JSValue(*(args->list->y)));
        argv.push_back(helpers::JSValue(*(args->list->z)));
    }

    static bool onPlayerClickPlayer(EventArgs_onPlayerClickPlayer* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->clicked))));
        argv.push_back(helpers::JSValue(*(args->list->source)));
    }

    static bool onClientCheckResponse(EventArgs_onClientCheckResponse* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(*(args->list->actionType)));
        argv.push_back(helpers::JSValue(*(args->list->address)));
        argv.push_back(helpers::JSValue(*(args->list->result)));
    }

    static bool onPlayerUpdate(EventArgs_onPlayerUpdate* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
    }

    static bool onVehicleStreamIn(EventArgs_onVehicleStreamIn* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->vehicle))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
    }

    static bool onVehicleStreamOut(EventArgs_onVehicleStreamOut* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->vehicle))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
    }

    static bool onVehicleDeath(EventArgs_onVehicleDeath* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->vehicle))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
    }

    static bool onPlayerEnterVehicle(EventArgs_onPlayerEnterVehicle* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->vehicle))));
        argv.push_back(helpers::JSValue(*(args->list->passenger)));
    }

    static bool onPlayerExitVehicle(EventArgs_onPlayerExitVehicle* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->vehicle))));
    }

    static bool onVehicleDamageStatusUpdate(EventArgs_onVehicleDamageStatusUpdate* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->vehicle))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
    }

    static bool onVehiclePaintJob(EventArgs_onVehiclePaintJob* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->vehicle))));
        argv.push_back(helpers::JSValue(*(args->list->paintJob)));
    }

    static bool onVehicleMod(EventArgs_onVehicleMod* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->vehicle))));
        argv.push_back(helpers::JSValue(*(args->list->component)));
    }

    static bool onVehicleRespray(EventArgs_onVehicleRespray* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->vehicle))));
        argv.push_back(helpers::JSValue(*(args->list->color1)));
        argv.push_back(helpers::JSValue(*(args->list->color2)));
    }

    static bool onEnterExitModShop(EventArgs_onEnterExitModShop* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(*(args->list->enterexit)));
        argv.push_back(helpers::JSValue(*(args->list->interiorId)));
    }

    static bool onVehicleSpawn(EventArgs_onVehicleSpawn* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->vehicle))));
    }

    static bool onUnoccupiedVehicleUpdate(EventArgs_onUnoccupiedVehicleUpdate* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->vehicle))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(*(args->list->seat)));
        argv.push_back(helpers::JSValue(*(args->list->posX)));
        argv.push_back(helpers::JSValue(*(args->list->posY)));
        argv.push_back(helpers::JSValue(*(args->list->posZ)));
        argv.push_back(helpers::JSValue(*(args->list->velocityX)));
        argv.push_back(helpers::JSValue(*(args->list->velocityY)));
        argv.push_back(helpers::JSValue(*(args->list->velocityZ)));
    }

    static bool onTrailerUpdate(EventArgs_onTrailerUpdate* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->trailer))));
    }

    static bool onVehicleSirenStateChange(EventArgs_onVehicleSirenStateChange* args)
    {
        std::vector<v8::Local<v8::Value>> argv;

        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->player))));
        argv.push_back(helpers::JSValue(uintptr_t(*(args->list->vehicle))));
        argv.push_back(helpers::JSValue(*(args->list->sirenState)));
    }
};

OMP_NODE_Events OMP_NODE_Events_instance;
