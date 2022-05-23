#include "player_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/player.hpp"
#include "../../converter/anim.hpp"

WRAP_BASIC(IPlayer)

WRAP_BASIC_CALL(IPlayer, kick)
WRAP_BASIC_CALL(IPlayer, ban, JSToString(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, isBot, BoolToJS)
//virtual const PeerNetworkData& getNetworkData() const = 0;
WRAP_BASIC_CALL_RETURN(IPlayer, getPing, UIntToJS)
//bool sendPacket(Span<uint8_t> data, int channel)
//bool sendRPC(int id, Span<uint8_t> data, int channel)
//virtual void broadcastRPCToStreamed(int id, Span<uint8_t> data, int channel, bool skipFrom = false) const = 0;
//virtual void broadcastPacketToStreamed(Span<uint8_t> data, int channel, bool skipFrom = true) const = 0;
//virtual void broadcastSyncPacket(Span<uint8_t> data, int channel) const = 0;
WRAP_BASIC_CALL(IPlayer, spawn)
WRAP_BASIC_CALL_RETURN(IPlayer, getClientVersion, UIntToJS)
WRAP_BASIC_CALL_RETURN(IPlayer, getClientVersionName, StringViewToJS)
WRAP_BASIC_CALL(IPlayer, setPositionFindZ, JSToVector3(info[0], context))
WRAP_BASIC_CALL(IPlayer, setCameraPosition, JSToVector3(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getCameraPosition, Vector3ToJS)
WRAP_BASIC_CALL(IPlayer, setCameraLookAt, JSToVector3(info[0], context), JSToInt(info[1], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getCameraLookAt, Vector3ToJS)
WRAP_BASIC_CALL(IPlayer, setCameraBehind)
WRAP_BASIC_CALL(IPlayer,
                interpolateCameraPosition,
                JSToVector3(info[0], context),
                JSToVector3(info[1], context),
                JSToInt(info[2], context),
                (PlayerCameraCutType)JSToUInt(info[3], context))
WRAP_BASIC_CALL(IPlayer,
                interpolateCameraLookAt,
                JSToVector3(info[0], context),
                JSToVector3(info[1], context),
                JSToInt(info[2], context),
                (PlayerCameraCutType)JSToUInt(info[3], context))
//WRAP_BASIC_CALL(IPlayer, attachCameraToObject, IObject& object)
//WRAP_BASIC_CALL(IPlayer, attachCameraToObject, IPlayerObject& object)
WRAP_BASIC_CALL_RETURN(IPlayer, setName, UIntToJS, JSToString(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getName, StringViewToJS)
WRAP_BASIC_CALL_RETURN(IPlayer, getSerial, StringViewToJS)
WRAP_BASIC_CALL(IPlayer, giveWeapon, JSToWeaponSlotData(info[0], context))
WRAP_BASIC_CALL(IPlayer, setWeaponAmmo, JSToWeaponSlotData(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getWeapons, WeaponSlotsToJS)
WRAP_BASIC_CALL(IPlayer, resetWeapons)
WRAP_BASIC_CALL(IPlayer, setArmedWeapon, JSToUInt(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getArmedWeapon, UIntToJS)
WRAP_BASIC_CALL_RETURN(IPlayer, getArmedWeaponAmmo, UIntToJS)
WRAP_BASIC_CALL(IPlayer, setShopName, JSToString(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getShopName, StringViewToJS)
WRAP_BASIC_CALL(IPlayer, setDrunkLevel, JSToInt(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getDrunkLevel, IntToJS)
WRAP_BASIC_CALL(IPlayer, setColour, JSToColour(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getColour, ColourToJS)
WRAP_BASIC_CALL(IPlayer, setOtherColour, *JSToIPlayer(info[0], context), JSToColour(info[1], context))
WRAP_BASIC_CODE(IPlayer, getOtherColour, {
    ENTER_FUNCTION_CALLBACK(info);
    auto external = GetContextExternalPointer<IPlayer>(info);
    if (external == nullptr) {
        return;
    }

    auto player = JSToIPlayer(info[0], context);
    Colour colour;

    auto value = external->getOtherColour(*player, colour);

    if (value) {
        auto valueHandle = ColourToJS(colour, context);

        info.GetReturnValue().Set(valueHandle);
    } else {
        info.GetReturnValue().Set(v8::Null(isolate));
    }
})
WRAP_BASIC_CALL(IPlayer, setControllable, JSToBool(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getControllable, BoolToJS)
WRAP_BASIC_CALL(IPlayer, setSpectating, JSToBool(info[0], context))
WRAP_BASIC_CALL(IPlayer, setWantedLevel, JSToUInt(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getWantedLevel, UIntToJS)
WRAP_BASIC_CALL(IPlayer, playSound, JSToUInt(info[0], context), JSToVector3(info[1], context))
WRAP_BASIC_CALL_RETURN(IPlayer, lastPlayedSound, UIntToJS)
WRAP_BASIC_CALL(IPlayer,
                playAudio,
                JSToString(info[0], context),
                JSToBool(info[1], context, false),
                JSToVector3(info[2], context, Vector3(0.f)),
                JSToFloat(info[3], context, 0.f))
WRAP_BASIC_CALL_RETURN(IPlayer, playerCrimeReport, BoolToJS, *JSToIPlayer(info[0], context), JSToInt(info[1], context))
WRAP_BASIC_CALL(IPlayer, stopAudio)
WRAP_BASIC_CALL_RETURN(IPlayer, lastPlayedAudio, StringViewToJS)
WRAP_BASIC_CALL(IPlayer,
                createExplosion,
                JSToVector3(info[0], context),
                JSToInt(info[1], context),
                JSToFloat(info[2], context))
WRAP_BASIC_CALL(IPlayer,
                sendDeathMessage,
                *JSToIPlayer(info[0], context),
                JSToIPlayer(info[1], context),
                JSToInt(info[2], context))
WRAP_BASIC_CALL(IPlayer, sendEmptyDeathMessage)
WRAP_BASIC_CALL(IPlayer,
                removeDefaultObjects,
                JSToUInt(info[0], context),
                JSToVector3(info[1], context),
                JSToFloat(info[2], context))
WRAP_BASIC_CALL(IPlayer, forceClassSelection)
WRAP_BASIC_CALL(IPlayer, setMoney, JSToInt(info[0], context))
WRAP_BASIC_CALL(IPlayer, giveMoney, JSToInt(info[0], context))
WRAP_BASIC_CALL(IPlayer, resetMoney)
WRAP_BASIC_CALL_RETURN(IPlayer, getMoney, IntToJS)
WRAP_BASIC_CALL(IPlayer,
                setMapIcon,
                JSToInt(info[0], context),
                JSToVector3(info[1], context),
                JSToInt(info[2], context),
                JSToColour(info[3], context),
                (MapIconStyle)JSToUInt(info[4], context))
WRAP_BASIC_CALL(IPlayer, unsetMapIcon, JSToInt(info[0], context))
WRAP_BASIC_CALL(IPlayer, useStuntBonuses, JSToBool(info[0], context))
WRAP_BASIC_CALL(IPlayer, toggleOtherNameTag, *JSToIPlayer(info[0], context), JSToBool(info[1], context))
WRAP_BASIC_CALL(IPlayer, setTime, JSToHours(info[0], context), JSToMinutes(info[1], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getTime, HoursMinutesToJS)
WRAP_BASIC_CALL(IPlayer, useClock, JSToBool(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, hasClock, BoolToJS)
WRAP_BASIC_CALL(IPlayer, useWidescreen, JSToBool(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, hasWidescreen, BoolToJS)
WRAP_BASIC_CALL(IPlayer, setTransform, JSToGTAQuat(info[0], context))
WRAP_BASIC_CALL(IPlayer, setHealth, JSToFloat(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getHealth, FloatToJS)
WRAP_BASIC_CALL(IPlayer, setScore, JSToInt(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getScore, IntToJS)
WRAP_BASIC_CALL(IPlayer, setArmour, JSToFloat(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getArmour, FloatToJS)
WRAP_BASIC_CALL(IPlayer, setGravity, JSToFloat(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getGravity, FloatToJS)
WRAP_BASIC_CALL(IPlayer, setWorldTime, JSToHours(info[0], context))
WRAP_BASIC_CALL(IPlayer,
                applyAnimation,
                JSToAnimationData(info[0], context),
                (PlayerAnimationSyncType)JSToUInt(info[1], context))
WRAP_BASIC_CALL(IPlayer, clearAnimations, (PlayerAnimationSyncType)JSToUInt(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getAnimationData, PlayerAnimationDataToJS)
WRAP_BASIC_CALL_RETURN(IPlayer, getSurfingData, PlayerSurfingDataToJS)
WRAP_BASIC_CALL(IPlayer, streamInForPlayer, *JSToIPlayer(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, isStreamedInForPlayer, BoolToJS, *JSToIPlayer(info[0], context))
WRAP_BASIC_CALL(IPlayer, streamOutForPlayer, *JSToIPlayer(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, streamedForPlayers, FlatPtrHashSetIPlayerToJS)
WRAP_BASIC_CALL_RETURN(IPlayer, getState, UIntToJS)
WRAP_BASIC_CALL(IPlayer, setTeam, JSToInt(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getTeam, IntToJS)
WRAP_BASIC_CALL(IPlayer, setSkin, JSToInt(info[0], context), JSToBool(info[1], context, true))
WRAP_BASIC_CALL_RETURN(IPlayer, getSkin, IntToJS)
WRAP_BASIC_CALL(IPlayer,
                setChatBubble,
                JSToString(info[0], context),
                JSToColour(info[1], context),
                JSToFloat(info[2], context),
                JSToMilliseconds(info[3], context))
WRAP_BASIC_CALL(IPlayer, sendClientMessage, JSToColour(info[0], context), JSToString(info[1], context))
WRAP_BASIC_CALL(IPlayer, sendChatMessage, *JSToIPlayer(info[0], context), JSToString(info[1], context))
WRAP_BASIC_CALL(IPlayer, sendCommand, JSToString(info[0], context))
WRAP_BASIC_CALL(IPlayer,
                sendGameText,
                JSToString(info[0], context),
                JSToMilliseconds(info[1], context),
                JSToInt(info[2], context))
WRAP_BASIC_CALL(IPlayer, setWeather, JSToInt(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getWeather, IntToJS)
WRAP_BASIC_CALL(IPlayer, setWorldBounds, JSToVector4(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getWorldBounds, Vector4ToJS)
WRAP_BASIC_CALL(IPlayer, setFightingStyle, (PlayerFightingStyle)JSToUInt(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getFightingStyle, UIntToJS)
WRAP_BASIC_CALL(IPlayer, setSkillLevel, (PlayerWeaponSkill)JSToUInt(info[0], context), JSToInt(info[1], context))
WRAP_BASIC_CALL(IPlayer, setAction, (PlayerSpecialAction)JSToUInt(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getAction, UIntToJS)
WRAP_BASIC_CALL(IPlayer, setVelocity, JSToVector3(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getVelocity, Vector3ToJS)
WRAP_BASIC_CALL(IPlayer, setInterior, JSToUInt(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getInterior, UIntToJS)
WRAP_BASIC_CALL_RETURN(IPlayer, getKeyData, PlayerKeyDataToJS)
WRAP_BASIC_CALL_RETURN(IPlayer, getSkillLevels, SkillLevelsToJS)
WRAP_BASIC_CALL_RETURN(IPlayer, getAimData, PlayerAimDataToJS)
WRAP_BASIC_CALL_RETURN(IPlayer, getBulletData, PlayerBulletDataToJS)
WRAP_BASIC_CALL(IPlayer, useCameraTargeting, JSToBool(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, hasCameraTargeting, BoolToJS)
WRAP_BASIC_CALL(IPlayer, removeFromVehicle)
WRAP_BASIC_CALL_RETURN(IPlayer, getCameraTargetPlayer, IPlayerToJS)
//WRAP_BASIC_CALL_RETURN(IPlayer, getCameraTargetVehicle, IVehicle*)
//WRAP_BASIC_CALL_RETURN(IPlayer, getCameraTargetObject, IObject*)
//WRAP_BASIC_CALL_RETURN(IPlayer, getCameraTargetActor, IActor*)
//WRAP_BASIC_CALL_RETURN(IPlayer, getTargetPlayer, IPlayer*)
//WRAP_BASIC_CALL_RETURN(IPlayer, getTargetActor, IActor*)
WRAP_BASIC_CALL(IPlayer, setRemoteVehicleCollisions, JSToBool(info[0], context))
WRAP_BASIC_CALL(IPlayer, spectatePlayer, *JSToIPlayer(info[0], context), (PlayerSpectateMode)JSToUInt(info[1], context))
//WRAP_BASIC_CALL(IPlayer, spectateVehicle, IVehicle& target, PlayerSpectateMode mode)
WRAP_BASIC_CALL_RETURN(IPlayer, getSpectateData, PlayerSpectateDataToJS)
WRAP_BASIC_CALL(IPlayer,
                sendClientCheck,
                JSToInt(info[0], context),
                JSToInt(info[1], context),
                JSToInt(info[2], context),
                JSToInt(info[3], context))
WRAP_BASIC_CALL(IPlayer, toggleGhostMode, JSToBool(info[0], context))
WRAP_BASIC_CALL_RETURN(IPlayer, isGhostModeEnabled, BoolToJS)
WRAP_BASIC_CALL_RETURN(IPlayer, getDefaultObjectsRemoved, IntToJS)

void WrapPlayer(IPlayer *player, v8::Local<v8::Context> context) {
    auto playerHandle = InterfaceToObject(player, context, WRAPPED_METHODS(IPlayer));

    player->addExtension(new IHandleStorage(context->GetIsolate(), playerHandle), true);
}