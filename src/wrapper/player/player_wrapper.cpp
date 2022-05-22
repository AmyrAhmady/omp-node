#include "player_wrapper.hpp"
#include "../../logger.hpp"
#include "../primitive.hpp"
#include "../types.hpp"
#include "../player.hpp"

IPlayer *GetPlayerFromContext(const v8::FunctionCallbackInfo<v8::Value> &info) {
    auto player = GetContextExternalPointer<IPlayer>(info);

    if (player == nullptr) {
        info.GetIsolate()->ThrowException(v8::Exception::ReferenceError(v8::String::NewFromUtf8(info.GetIsolate(),
                                                                                                "The player is not connected").ToLocalChecked()));
    }

    return player;
}

WRAP_BASIC(IPlayer)

WRAP_BASIC_CALL(IPlayer, kick)
WRAP_BASIC_CALL(IPlayer, ban, JSToString(info[argn++], context))
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
WRAP_BASIC_CALL(IPlayer, setPositionFindZ, JSToVector3(info[argn++], context))
WRAP_BASIC_CALL(IPlayer, setCameraPosition, JSToVector3(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getCameraPosition, Vector3ToJS)
WRAP_BASIC_CALL(IPlayer, setCameraLookAt, JSToVector3(info[argn++], context), JSToInt(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getCameraLookAt, Vector3ToJS)
WRAP_BASIC_CALL(IPlayer, setCameraBehind)
WRAP_BASIC_CALL(IPlayer,
                interpolateCameraPosition,
                JSToVector3(info[argn++], context),
                JSToVector3(info[argn++], context),
                JSToInt(info[argn++], context),
                (PlayerCameraCutType)JSToUInt(info[argn++], context))
WRAP_BASIC_CALL(IPlayer,
                interpolateCameraLookAt,
                JSToVector3(info[argn++], context),
                JSToVector3(info[argn++], context),
                JSToInt(info[argn++], context),
                (PlayerCameraCutType)JSToUInt(info[argn++], context))
//WRAP_BASIC_CALL(IPlayer, attachCameraToObject, IObject& object)
//WRAP_BASIC_CALL(IPlayer, attachCameraToObject, IPlayerObject& object)
WRAP_BASIC_CALL_RETURN(IPlayer, setName, UIntToJS, JSToString(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getName, StringViewToJS)
WRAP_BASIC_CALL_RETURN(IPlayer, getSerial, StringViewToJS)
//WRAP_BASIC_CALL(IPlayer, giveWeapon, WeaponSlotData weapon)
//WRAP_BASIC_CALL(IPlayer, setWeaponAmmo, WeaponSlotData data)
//WRAP_BASIC_CALL_RETURN(IPlayer, getWeapons, WeaponSlots)
WRAP_BASIC_CALL(IPlayer, resetWeapons)
WRAP_BASIC_CALL(IPlayer, setArmedWeapon, JSToUInt(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getArmedWeapon, UIntToJS)
WRAP_BASIC_CALL_RETURN(IPlayer, getArmedWeaponAmmo, UIntToJS)
WRAP_BASIC_CALL(IPlayer, setShopName, JSToString(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getShopName, StringViewToJS)
WRAP_BASIC_CALL(IPlayer, setDrunkLevel, JSToInt(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getDrunkLevel, IntToJS)
//WRAP_BASIC_CALL(IPlayer, setColour, Colour colour)
//WRAP_BASIC_CALL_RETURN(IPlayer, getColour, const Colour&)
//WRAP_BASIC_CALL(IPlayer, setOtherColour, *JSToIPlayer(info[argn++], context), Colour colour)
//WRAP_BASIC_CALL_RETURN(IPlayer, getOtherColour, BoolToJS, *JSToIPlayer(info[argn++], context), Colour& colour)
WRAP_BASIC_CALL(IPlayer, setControllable, JSToBool(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getControllable, BoolToJS)
WRAP_BASIC_CALL(IPlayer, setSpectating, JSToBool(info[argn++], context))
WRAP_BASIC_CALL(IPlayer, setWantedLevel, JSToUInt(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getWantedLevel, UIntToJS)
WRAP_BASIC_CALL(IPlayer, playSound, JSToUInt(info[argn++], context), JSToVector3(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, lastPlayedSound, UIntToJS)
WRAP_BASIC_CALL(IPlayer,
                playAudio,
                JSToString(info[argn++], context),
                JSToBool(info[argn++], context, false),
                JSToVector3(info[argn++], context, Vector3(0.f)),
                JSToFloat(info[argn++], context, 0.f))
WRAP_BASIC_CALL_RETURN(IPlayer,
                       playerCrimeReport,
                       BoolToJS,
                       *JSToIPlayer(info[argn++], context),
                       JSToInt(info[argn++], context))
WRAP_BASIC_CALL(IPlayer, stopAudio)
WRAP_BASIC_CALL_RETURN(IPlayer, lastPlayedAudio, StringViewToJS)
WRAP_BASIC_CALL(IPlayer,
                createExplosion,
                JSToVector3(info[argn++], context),
                JSToInt(info[argn++], context),
                JSToFloat(info[argn++], context))
//WRAP_BASIC_CALL(IPlayer, sendDeathMessage, IPlayer& player, *JSToIPlayer(info[argn++], context), JSToInt(info[argn++], context))
WRAP_BASIC_CALL(IPlayer, sendEmptyDeathMessage)
WRAP_BASIC_CALL(IPlayer,
                removeDefaultObjects,
                JSToUInt(info[argn++], context),
                JSToVector3(info[argn++], context),
                JSToFloat(info[argn++], context))
WRAP_BASIC_CALL(IPlayer, forceClassSelection)
WRAP_BASIC_CALL(IPlayer, setMoney, JSToInt(info[argn++], context))
WRAP_BASIC_CALL(IPlayer, giveMoney, JSToInt(info[argn++], context))
WRAP_BASIC_CALL(IPlayer, resetMoney)
WRAP_BASIC_CALL_RETURN(IPlayer, getMoney, IntToJS)
//WRAP_BASIC_CALL(IPlayer, setMapIcon, JSToInt(info[argn++], context), JSToVector3(info[argn++], context), JSToInt(info[argn++], context), Colour colour, MapIconStyle style)
WRAP_BASIC_CALL(IPlayer, unsetMapIcon, JSToInt(info[argn++], context))
WRAP_BASIC_CALL(IPlayer, useStuntBonuses, JSToBool(info[argn++], context))
WRAP_BASIC_CALL(IPlayer, toggleOtherNameTag, *JSToIPlayer(info[argn++], context), JSToBool(info[argn++], context))
//WRAP_BASIC_CALL(IPlayer, setTime, Hours hr, Minutes min)
//WRAP_BASIC_CALL_RETURN(IPlayer, getTime, Pair<Hours, Minutes>)
WRAP_BASIC_CALL(IPlayer, useClock, JSToBool(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, hasClock, BoolToJS)
WRAP_BASIC_CALL(IPlayer, useWidescreen, JSToBool(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, hasWidescreen, BoolToJS)
//WRAP_BASIC_CALL(IPlayer, setTransform, GTAQuat tm)
WRAP_BASIC_CALL(IPlayer, setHealth, JSToFloat(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getHealth, FloatToJS)
WRAP_BASIC_CALL(IPlayer, setScore, JSToInt(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getScore, IntToJS)
WRAP_BASIC_CALL(IPlayer, setArmour, JSToFloat(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getArmour, FloatToJS)
WRAP_BASIC_CALL(IPlayer, setGravity, JSToFloat(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getGravity, FloatToJS)
//WRAP_BASIC_CALL(IPlayer, setWorldTime, Hours time)
//WRAP_BASIC_CALL(IPlayer, applyAnimation, const AnimationData& animation, PlayerAnimationSyncType syncType)
//WRAP_BASIC_CALL(IPlayer, clearAnimations, PlayerAnimationSyncType syncType)
//WRAP_BASIC_CALL_RETURN(IPlayer, getAnimationData, PlayerAnimationData)
//WRAP_BASIC_CALL_RETURN(IPlayer, getSurfingData, PlayerSurfingData)
WRAP_BASIC_CALL(IPlayer, streamInForPlayer, *JSToIPlayer(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, isStreamedInForPlayer, BoolToJS, *JSToIPlayer(info[argn++], context))
//WRAP_BASIC_CALL(IPlayer, streamOutForPlayer, IPlayer& other)
//WRAP_BASIC_CALL_RETURN(IPlayer, streamedForPlayers, const FlatPtrHashSet<IPlayer>&)
//WRAP_BASIC_CALL_RETURN(IPlayer, getState, PlayerState)
WRAP_BASIC_CALL(IPlayer, setTeam, JSToInt(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getTeam, IntToJS)
WRAP_BASIC_CALL(IPlayer, setSkin, JSToInt(info[argn++], context), JSToBool(info[argn++], context, true))
WRAP_BASIC_CALL_RETURN(IPlayer, getSkin, IntToJS)
//WRAP_BASIC_CALL(IPlayer, setChatBubble, JSToString(info[argn++], context), const Colour& colour, JSToFloat(info[argn++], context), Milliseconds expire)
//WRAP_BASIC_CALL(IPlayer, sendClientMessage, const Colour& colour, JSToString(info[argn++], context))
WRAP_BASIC_CALL(IPlayer, sendChatMessage, *JSToIPlayer(info[argn++], context), JSToString(info[argn++], context))
WRAP_BASIC_CALL(IPlayer, sendCommand, JSToString(info[argn++], context))
//WRAP_BASIC_CALL(IPlayer, sendGameText, JSToString(info[argn++], context), Milliseconds time, JSToInt(info[argn++], context))
WRAP_BASIC_CALL(IPlayer, setWeather, JSToInt(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getWeather, IntToJS)
WRAP_BASIC_CALL(IPlayer, setWorldBounds, JSToVector4(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getWorldBounds, Vector4ToJS)
WRAP_BASIC_CALL(IPlayer, setFightingStyle, (PlayerFightingStyle)JSToUInt(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getFightingStyle, UIntToJS)
WRAP_BASIC_CALL(IPlayer,
                setSkillLevel,
                (PlayerWeaponSkill)JSToUInt(info[argn++], context),
                JSToInt(info[argn++], context))
WRAP_BASIC_CALL(IPlayer, setAction, (PlayerSpecialAction)JSToUInt(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getAction, UIntToJS)
WRAP_BASIC_CALL(IPlayer, setVelocity, JSToVector3(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getVelocity, Vector3ToJS)
WRAP_BASIC_CALL(IPlayer, setInterior, JSToUInt(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, getInterior, UIntToJS)
WRAP_BASIC_CALL_RETURN(IPlayer, getKeyData, PlayerKeyDataToJS)
//WRAP_BASIC_CALL_RETURN(IPlayer, getSkillLevels, const StaticArray<uint16_t, NUM_SKILL_LEVELS>&)
//WRAP_BASIC_CALL_RETURN(IPlayer, getAimData, const PlayerAimData&)
WRAP_BASIC_CALL_RETURN(IPlayer, getBulletData, PlayerBulletDataToJS)
WRAP_BASIC_CALL(IPlayer, useCameraTargeting, JSToBool(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, hasCameraTargeting, BoolToJS)
WRAP_BASIC_CALL(IPlayer, removeFromVehicle)
//WRAP_BASIC_CALL_RETURN(IPlayer, getCameraTargetPlayer, IPlayer*)
//WRAP_BASIC_CALL_RETURN(IPlayer, getCameraTargetVehicle, IVehicle*)
//WRAP_BASIC_CALL_RETURN(IPlayer, getCameraTargetObject, IObject*)
//WRAP_BASIC_CALL_RETURN(IPlayer, getCameraTargetActor, IActor*)
//WRAP_BASIC_CALL_RETURN(IPlayer, getTargetPlayer, IPlayer*)
//WRAP_BASIC_CALL_RETURN(IPlayer, getTargetActor, IActor*)
WRAP_BASIC_CALL(IPlayer, setRemoteVehicleCollisions, JSToBool(info[argn++], context))
WRAP_BASIC_CALL(IPlayer,
                spectatePlayer,
                *JSToIPlayer(info[argn++], context),
                (PlayerSpectateMode)JSToUInt(info[argn++], context))
//WRAP_BASIC_CALL(IPlayer, spectateVehicle, IVehicle& target, PlayerSpectateMode mode)
//WRAP_BASIC_CALL_RETURN(IPlayer, getSpectateData, const PlayerSpectateData&)
WRAP_BASIC_CALL(IPlayer,
                sendClientCheck,
                JSToInt(info[argn++], context),
                JSToInt(info[argn++], context),
                JSToInt(info[argn++], context),
                JSToInt(info[argn++], context))
WRAP_BASIC_CALL(IPlayer, toggleGhostMode, JSToBool(info[argn++], context))
WRAP_BASIC_CALL_RETURN(IPlayer, isGhostModeEnabled, BoolToJS)
WRAP_BASIC_CALL_RETURN(IPlayer, getDefaultObjectsRemoved, IntToJS)

void WrapPlayer(IPlayer *player, v8::Local<v8::Context> context) {
    auto playerHandle = InterfaceToObject(player, context, WRAPPED_METHODS(IPlayer));

    player->addExtension(new IHandleStorage(context->GetIsolate(), playerHandle), true);
}