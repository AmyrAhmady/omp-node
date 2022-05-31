#include "player_wrapper.hpp"
#include "../../converter/types.hpp"
#include "../../converter/player.hpp"
#include "../../converter/anim.hpp"
#include "../../converter/entity.hpp"
#include "../entity/entity_wrapper.hpp"
#include "../checkpoint/player_checkpoint_data_wrapper.hpp"
#include "../dialog/player_dialog_data_wrapper.hpp"
#include "../menu/player_menu_data_wrapper.hpp"
#include "../class/player_class_data_wrapper.hpp"
#include "../vehicle/player_vehicle_data_wrapper.hpp"
#include "../textlabel/player_textlabel_data_wrapper.hpp"
#include "../object/player_object_data_wrapper.hpp"
#include "../textdraw/player_textdraw_data_wrapper.hpp"
#include "../variable/player_variable_data_wrapper.hpp"

WRAP_BASIC(IPlayer)
WRAP_BASIC_CALL(IPlayer, kick)
WRAP_BASIC_CALL(IPlayer, ban, (Impl::String, JSToString, reason, Impl::String()))
WRAP_BASIC_CALL_RETURN(IPlayer, isBot, (bool, BoolToJS))
//WRAP_BASIC_CALL_RETURN(IPlayer, getNetworkData, (const PeerNetworkData&, TO_JS_FN(PeerNetworkData)))
WRAP_BASIC_CALL_RETURN(IPlayer, getPing, (unsigned, UIntToJS))
//WRAP_BASIC_CALL_RETURN(IPlayer, sendPacket, (bool, BoolToJS), (Span<uint8_t>, FROM_JS_FN(Span<uint8_t>), data), (int, JSToInt, channel))
//WRAP_BASIC_CALL_RETURN(IPlayer, sendRPC, (bool, BoolToJS), (int, JSToInt, id), (Span<uint8_t>, FROM_JS_FN(Span<uint8_t>), data), (int, JSToInt, channel))
//WRAP_BASIC_CALL(IPlayer, broadcastRPCToStreamed, (int, JSToInt, id), (Span<uint8_t>, FROM_JS_FN(Span<uint8_t>), data), (int, JSToInt, channel), (bool, JSToBool, skipFrom, false))
//WRAP_BASIC_CALL(IPlayer, broadcastPacketToStreamed, (Span<uint8_t>, FROM_JS_FN(Span<uint8_t>), data), (int, JSToInt, channel), (bool, JSToBool, skipFrom, true))
//WRAP_BASIC_CALL(IPlayer, broadcastSyncPacket, (Span<uint8_t>, FROM_JS_FN(Span<uint8_t>), data), (int, JSToInt, channel))
WRAP_BASIC_CALL(IPlayer, spawn)
WRAP_BASIC_CALL_RETURN(IPlayer, getClientVersion, (uint32_t, UIntToJS))
WRAP_BASIC_CALL_RETURN(IPlayer, getClientVersionName, (StringView, TO_JS_FN(StringView)))
WRAP_BASIC_CALL(IPlayer, setPositionFindZ, (Vector3, JSToVector<Vector3>, pos))
WRAP_BASIC_CALL(IPlayer, setCameraPosition, (Vector3, JSToVector<Vector3>, pos))
WRAP_BASIC_CALL_RETURN(IPlayer, getCameraPosition, (Vector3, VectorToJS<Vector3>))
WRAP_BASIC_CALL(IPlayer, setCameraLookAt, (Vector3, JSToVector<Vector3>, pos), (int, JSToInt, cutType))
WRAP_BASIC_CALL_RETURN(IPlayer, getCameraLookAt, (Vector3, VectorToJS<Vector3>))
WRAP_BASIC_CALL(IPlayer, setCameraBehind)
WRAP_BASIC_CALL(IPlayer,
                interpolateCameraPosition,
                (Vector3, JSToVector<Vector3>, from),
                (Vector3, JSToVector<Vector3>, to),
                (int, JSToInt, time),
                (PlayerCameraCutType, JSToEnum<PlayerCameraCutType>, cutType))
WRAP_BASIC_CALL(IPlayer,
                interpolateCameraLookAt,
                (Vector3, JSToVector<Vector3>, from),
                (Vector3, JSToVector<Vector3>, to),
                (int, JSToInt, time),
                (PlayerCameraCutType, JSToEnum<PlayerCameraCutType>, cutType))
//WRAP_BASIC_CALL(IPlayer, attachCameraToObject, (IObject&, JSToEntity<IObject>, object)) // todo
//WRAP_BASIC_CALL(IPlayer, attachCameraToObject, (IPlayerObject&, JSToEntity<IPlayerObject>, object)) // todo
WRAP_BASIC_CALL_RETURN(IPlayer,
                       setName,
                       (EPlayerNameStatus, EnumToJS<EPlayerNameStatus>),
                       (Impl::String, JSToString, name))
WRAP_BASIC_CALL_RETURN(IPlayer, getName, (StringView, TO_JS_FN(StringView)))
WRAP_BASIC_CALL_RETURN(IPlayer, getSerial, (StringView, TO_JS_FN(StringView)))
WRAP_BASIC_CALL(IPlayer, giveWeapon, (WeaponSlotData, FROM_JS_FN(WeaponSlotData), weapon))
WRAP_BASIC_CALL(IPlayer, setWeaponAmmo, (WeaponSlotData, FROM_JS_FN(WeaponSlotData), data))
WRAP_BASIC_CALL_RETURN(IPlayer, getWeapons, (WeaponSlots, TO_JS_FN(WeaponSlots)))
WRAP_BASIC_CALL(IPlayer, resetWeapons)
WRAP_BASIC_CALL(IPlayer, setArmedWeapon, (uint32_t, JSToUInt<uint32_t>, weapon))
WRAP_BASIC_CALL_RETURN(IPlayer, getArmedWeapon, (uint32_t, UIntToJS))
WRAP_BASIC_CALL_RETURN(IPlayer, getArmedWeaponAmmo, (uint32_t, UIntToJS))
WRAP_BASIC_CALL(IPlayer, setShopName, (Impl::String, JSToString, name))
WRAP_BASIC_CALL_RETURN(IPlayer, getShopName, (StringView, TO_JS_FN(StringView)))
WRAP_BASIC_CALL(IPlayer, setDrunkLevel, (int, JSToInt, level))
WRAP_BASIC_CALL_RETURN(IPlayer, getDrunkLevel, (int, IntToJS))
WRAP_BASIC_CALL(IPlayer, setColour, (Colour, FROM_JS_FN(Colour), colour))
WRAP_BASIC_CALL_RETURN(IPlayer, getColour, (const Colour&, TO_JS_FN(Colour)))
WRAP_BASIC_CALL(IPlayer,
                setOtherColour,
                (IPlayer & , JSToEntityRef<IPlayer>, other),
                (Colour, FROM_JS_FN(Colour), colour))
WRAP_BASIC_CODE(IPlayer, getOtherColour, {
    ENTER_FUNCTION_CALLBACK(info);
    auto external = GetContextExternalPointer<IPlayer>(info);
    if (external == nullptr) {
        return;
    }
    auto player = JSToEntity<IPlayer>(info[0], context);
    Colour colour;
    auto value = external->getOtherColour(*player, colour);
    if (value) {
        auto valueHandle = ColourToJS(colour, context);
        info.GetReturnValue().Set(valueHandle);
    } else {
        info.GetReturnValue().Set(v8::Null(isolate));
    }
})
WRAP_BASIC_CALL(IPlayer, setControllable, (bool, JSToBool, controllable))
WRAP_BASIC_CALL_RETURN(IPlayer, getControllable, (bool, BoolToJS))
WRAP_BASIC_CALL(IPlayer, setSpectating, (bool, JSToBool, spectating))
WRAP_BASIC_CALL(IPlayer, setWantedLevel, (unsigned, JSToUInt<unsigned>, level))
WRAP_BASIC_CALL_RETURN(IPlayer, getWantedLevel, (unsigned, UIntToJS))
WRAP_BASIC_CALL(IPlayer, playSound, (uint32_t, JSToUInt<uint32_t>, sound), (Vector3, JSToVector<Vector3>, pos))
WRAP_BASIC_CALL_RETURN(IPlayer, lastPlayedSound, (uint32_t, UIntToJS))
WRAP_BASIC_CALL(IPlayer,
                playAudio,
                (Impl::String, JSToString, url),
                (bool, JSToBool, usePos, false),
                (Vector3, JSToVector<Vector3>, pos, Vector3(0.f)),
                (float, JSToFloat, distance, 0.f))
WRAP_BASIC_CALL_RETURN(IPlayer,
                       playerCrimeReport,
                       (bool, BoolToJS),
                       (IPlayer & , *JSToEntity<IPlayer>, suspect),
                       (int, JSToInt, crime))
WRAP_BASIC_CALL(IPlayer, stopAudio)
WRAP_BASIC_CALL_RETURN(IPlayer, lastPlayedAudio, (StringView, TO_JS_FN(StringView)))
WRAP_BASIC_CALL(IPlayer,
                createExplosion,
                (Vector3, JSToVector<Vector3>, vec),
                (int, JSToInt, type),
                (float, JSToFloat, radius))
WRAP_BASIC_CALL(IPlayer,
                sendDeathMessage,
                (IPlayer & , JSToEntityRef<IPlayer>, player),
                (IPlayer * , JSToEntity<IPlayer>, killer),
                (int, JSToInt, weapon))
WRAP_BASIC_CALL(IPlayer, sendEmptyDeathMessage)
WRAP_BASIC_CALL(IPlayer,
                removeDefaultObjects,
                (unsigned, JSToUInt<unsigned>, model),
                (Vector3, JSToVector<Vector3>, pos),
                (float, JSToFloat, radius))
WRAP_BASIC_CALL(IPlayer, forceClassSelection)
WRAP_BASIC_CALL(IPlayer, setMoney, (int, JSToInt, money))
WRAP_BASIC_CALL(IPlayer, giveMoney, (int, JSToInt, money))
WRAP_BASIC_CALL(IPlayer, resetMoney)
WRAP_BASIC_CALL_RETURN(IPlayer, getMoney, (int, IntToJS))
WRAP_BASIC_CALL(IPlayer,
                setMapIcon,
                (int, JSToInt, id),
                (Vector3, JSToVector<Vector3>, pos),
                (int, JSToInt, type),
                (Colour, FROM_JS_FN(Colour), colour),
                (MapIconStyle, JSToEnum<MapIconStyle>, style))
WRAP_BASIC_CALL(IPlayer, unsetMapIcon, (int, JSToInt, id))
WRAP_BASIC_CALL(IPlayer, useStuntBonuses, (bool, JSToBool, enable))
WRAP_BASIC_CALL(IPlayer, toggleOtherNameTag, (IPlayer & , JSToEntityRef<IPlayer>, other), (bool, JSToBool, toggle))
WRAP_BASIC_CALL(IPlayer, setTime, (Hours, FROM_JS_FN(Hours), hr), (Minutes, FROM_JS_FN(Minutes), min))
WRAP_BASIC_CALL_RETURN(IPlayer, getTime, (HoursMinutes, HoursMinutesToJS))
WRAP_BASIC_CALL(IPlayer, useClock, (bool, JSToBool, enable))
WRAP_BASIC_CALL_RETURN(IPlayer, hasClock, (bool, BoolToJS))
WRAP_BASIC_CALL(IPlayer, useWidescreen, (bool, JSToBool, enable))
WRAP_BASIC_CALL_RETURN(IPlayer, hasWidescreen, (bool, BoolToJS))
WRAP_BASIC_CALL(IPlayer, setTransform, (GTAQuat, FROM_JS_FN(GTAQuat), tm))
WRAP_BASIC_CALL(IPlayer, setHealth, (float, JSToFloat, health))
WRAP_BASIC_CALL_RETURN(IPlayer, getHealth, (float, FloatToJS))
WRAP_BASIC_CALL(IPlayer, setScore, (int, JSToInt, score))
WRAP_BASIC_CALL_RETURN(IPlayer, getScore, (int, IntToJS))
WRAP_BASIC_CALL(IPlayer, setArmour, (float, JSToFloat, armour))
WRAP_BASIC_CALL_RETURN(IPlayer, getArmour, (float, FloatToJS))
WRAP_BASIC_CALL(IPlayer, setGravity, (float, JSToFloat, gravity))
WRAP_BASIC_CALL_RETURN(IPlayer, getGravity, (float, FloatToJS))
WRAP_BASIC_CALL(IPlayer, setWorldTime, (Hours, FROM_JS_FN(Hours), time))
WRAP_BASIC_CALL(IPlayer,
                applyAnimation,
                (const AnimationData&, FROM_JS_FN(AnimationData), animation),
                (PlayerAnimationSyncType, JSToEnum<PlayerAnimationSyncType>, syncType))
WRAP_BASIC_CALL(IPlayer, clearAnimations, (PlayerAnimationSyncType, JSToEnum<PlayerAnimationSyncType>, syncType))
WRAP_BASIC_CALL_RETURN(IPlayer, getAnimationData, (PlayerAnimationData, TO_JS_FN(PlayerAnimationData)))
WRAP_BASIC_CALL_RETURN(IPlayer, getSurfingData, (PlayerSurfingData, TO_JS_FN(PlayerSurfingData)))
WRAP_BASIC_CALL(IPlayer, streamInForPlayer, (IPlayer & , JSToEntityRef<IPlayer>, other))
WRAP_BASIC_CALL_RETURN(IPlayer,
                       isStreamedInForPlayer,
                       (bool, BoolToJS),
                       (const IPlayer&, JSToEntityRef<IPlayer>, other))
WRAP_BASIC_CALL(IPlayer, streamOutForPlayer, (IPlayer & , JSToEntityRef<IPlayer>, other))
WRAP_BASIC_CALL_RETURN(IPlayer, streamedForPlayers, (const FlatPtrHashSetIPlayer&, TO_JS_FN(FlatPtrHashSetIPlayer)))
WRAP_BASIC_CALL_RETURN(IPlayer, getState, (PlayerState, EnumToJS))
WRAP_BASIC_CALL(IPlayer, setTeam, (int, JSToInt, team))
WRAP_BASIC_CALL_RETURN(IPlayer, getTeam, (int, IntToJS))
WRAP_BASIC_CALL(IPlayer, setSkin, (int, JSToInt, skin), (bool, JSToBool, send, true))
WRAP_BASIC_CALL_RETURN(IPlayer, getSkin, (int, IntToJS))
WRAP_BASIC_CALL(IPlayer,
                setChatBubble,
                (Impl::String, JSToString, text),
                (const Colour&, FROM_JS_FN(Colour), colour),
                (float, JSToFloat, drawDist),
                (Milliseconds, FROM_JS_FN(Milliseconds), expire))
WRAP_BASIC_CALL(IPlayer,
                sendClientMessage,
                (const Colour&, FROM_JS_FN(Colour), colour),
                (Impl::String, JSToString, message))
WRAP_BASIC_CALL(IPlayer,
                sendChatMessage,
                (IPlayer & , JSToEntityRef<IPlayer>, sender),
                (Impl::String, JSToString, message))
WRAP_BASIC_CALL(IPlayer, sendCommand, (Impl::String, JSToString, message))
WRAP_BASIC_CALL(IPlayer,
                sendGameText,
                (Impl::String, JSToString, message),
                (Milliseconds, FROM_JS_FN(Milliseconds), time),
                (int, JSToInt, style))
WRAP_BASIC_CALL(IPlayer, setWeather, (int, JSToInt, weatherID))
WRAP_BASIC_CALL_RETURN(IPlayer, getWeather, (int, IntToJS))
WRAP_BASIC_CALL(IPlayer, setWorldBounds, (Vector4, JSToVector<Vector4>, coords))
WRAP_BASIC_CALL_RETURN(IPlayer, getWorldBounds, (Vector4, VectorToJS<Vector4>))
WRAP_BASIC_CALL(IPlayer, setFightingStyle, (PlayerFightingStyle, JSToEnum<PlayerFightingStyle>, style))
WRAP_BASIC_CALL_RETURN(IPlayer, getFightingStyle, (PlayerFightingStyle, EnumToJS))
WRAP_BASIC_CALL(IPlayer, setSkillLevel, (PlayerWeaponSkill, JSToEnum<PlayerWeaponSkill>, skill), (int, JSToInt, level))
WRAP_BASIC_CALL(IPlayer, setAction, (PlayerSpecialAction, JSToEnum<PlayerSpecialAction>, action))
WRAP_BASIC_CALL_RETURN(IPlayer, getAction, (PlayerSpecialAction, EnumToJS))
WRAP_BASIC_CALL(IPlayer, setVelocity, (Vector3, JSToVector<Vector3>, velocity))
WRAP_BASIC_CALL_RETURN(IPlayer, getVelocity, (Vector3, VectorToJS<Vector3>))
WRAP_BASIC_CALL(IPlayer, setInterior, (unsigned, JSToUInt<unsigned>, interior))
WRAP_BASIC_CALL_RETURN(IPlayer, getInterior, (unsigned, UIntToJS))
WRAP_BASIC_CALL_RETURN(IPlayer, getKeyData, (const PlayerKeyData&, TO_JS_FN(PlayerKeyData)))
WRAP_BASIC_CALL_RETURN(IPlayer, getSkillLevels, (const SkillLevels&, TO_JS_FN(SkillLevels)))
WRAP_BASIC_CALL_RETURN(IPlayer, getAimData, (const PlayerAimData&, TO_JS_FN(PlayerAimData)))
WRAP_BASIC_CALL_RETURN(IPlayer, getBulletData, (const PlayerBulletData&, TO_JS_FN(PlayerBulletData)))
WRAP_BASIC_CALL(IPlayer, useCameraTargeting, (bool, JSToBool, enable))
WRAP_BASIC_CALL_RETURN(IPlayer, hasCameraTargeting, (bool, BoolToJS))
WRAP_BASIC_CALL(IPlayer, removeFromVehicle)
WRAP_BASIC_CALL_RETURN(IPlayer, getCameraTargetPlayer, (IPlayer * , EntityToJS<IPlayer>))
WRAP_BASIC_CALL_RETURN(IPlayer, getCameraTargetVehicle, (IVehicle * , EntityToJS<IVehicle>))
//WRAP_BASIC_CALL_RETURN(IPlayer, getCameraTargetObject, (IObject*, EntityToJS<IObject>)) // todo
WRAP_BASIC_CALL_RETURN(IPlayer, getCameraTargetActor, (IActor * , EntityToJS<IActor>))
WRAP_BASIC_CALL_RETURN(IPlayer, getTargetPlayer, (IPlayer * , EntityToJS<IPlayer>))
WRAP_BASIC_CALL_RETURN(IPlayer, getTargetActor, (IActor * , EntityToJS<IActor>))
WRAP_BASIC_CALL(IPlayer, setRemoteVehicleCollisions, (bool, JSToBool, collide))
WRAP_BASIC_CALL(IPlayer,
                spectatePlayer,
                (IPlayer & , JSToEntityRef<IPlayer>, target),
                (PlayerSpectateMode, JSToEnum<PlayerSpectateMode>, mode))
WRAP_BASIC_CALL(IPlayer,
                spectateVehicle,
                (IVehicle & , JSToEntityRef<IVehicle>, target),
                (PlayerSpectateMode, JSToEnum<PlayerSpectateMode>, mode))
WRAP_BASIC_CALL_RETURN(IPlayer, getSpectateData, (const PlayerSpectateData&, TO_JS_FN(PlayerSpectateData)))
WRAP_BASIC_CALL(IPlayer,
                sendClientCheck,
                (int, JSToInt, actionType),
                (int, JSToInt, address),
                (int, JSToInt, offset),
                (int, JSToInt, count))
WRAP_BASIC_CALL(IPlayer, toggleGhostMode, (bool, JSToBool, toggle))
WRAP_BASIC_CALL_RETURN(IPlayer, isGhostModeEnabled, (bool, BoolToJS))
WRAP_BASIC_CALL_RETURN(IPlayer, getDefaultObjectsRemoved, (int, IntToJS))

WRAP_LAZILY_GET_EXTENSION_HANDLE(IPlayer,
                                 getPlayerVariableData,
                                 PlayerVariableDataHandleStorage,
                                 IPlayerVariableData,
                                 WrapPlayerVariableData)

WRAP_LAZILY_GET_EXTENSION_HANDLE(IPlayer,
                                 getPlayerVehicleData,
                                 PlayerVehicleDataHandleStorage,
                                 IPlayerVehicleData,
                                 WrapPlayerVehicleData)

WRAP_LAZILY_GET_EXTENSION_HANDLE(IPlayer,
                                 getPlayerCheckpointData,
                                 PlayerCheckpointDataHandleStorage,
                                 IPlayerCheckpointData,
                                 WrapPlayerCheckpointData)

WRAP_LAZILY_GET_EXTENSION_HANDLE(IPlayer,
                                 getPlayerDialogData,
                                 PlayerDialogDataHandleStorage,
                                 IPlayerDialogData,
                                 WrapPlayerDialogData)

WRAP_LAZILY_GET_EXTENSION_HANDLE(IPlayer,
                                 getPlayerMenuData,
                                 PlayerMenuDataHandleStorage,
                                 IPlayerMenuData,
                                 WrapPlayerMenuData)

WRAP_LAZILY_GET_EXTENSION_HANDLE(IPlayer,
                                 getPlayerClassData,
                                 PlayerClassDataHandleStorage,
                                 IPlayerClassData,
                                 WrapPlayerClassData)

WRAP_LAZILY_GET_EXTENSION_HANDLE(IPlayer,
                                 getPlayerTextLabelData,
                                 PlayerTextLabelPoolHandleStorage,
                                 IPlayerTextLabelData,
                                 WrapPlayerTextLabelData)

WRAP_LAZILY_GET_EXTENSION_HANDLE(IPlayer,
                                 getPlayerObjectData,
                                 PlayerObjectPoolHandleStorage,
                                 IPlayerObjectData,
                                 WrapPlayerObjectData)

WRAP_LAZILY_GET_EXTENSION_HANDLE(IPlayer,
                                 getPlayerTextDrawData,
                                 PlayerTextDrawPoolHandleStorage,
                                 IPlayerTextDrawData,
                                 WrapPlayerTextDrawData)

WRAP_ENTITY_METHODS(IPlayer)

void WrapPlayer(IPlayer *player, v8::Local<v8::Context> context) {
    auto playerHandle = InterfaceToObject(player, context, WRAPPED_METHODS(IPlayer));
    player->addExtension(new IHandleStorage(context->GetIsolate(), playerHandle), true);
}