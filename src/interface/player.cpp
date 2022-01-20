#include <Server/Components/Checkpoints/checkpoints.hpp>
#include "player.hpp"
#include "utils.hpp"

void setHealth(const v8::FunctionCallbackInfo<v8::Value> &info) {
	ENTER_CONTEXT_SCOPE(info)

	auto player = GetContextExternalPointer<IPlayer>(info);

	float health = GetFloat(info[0], context);

	player->setHealth(health);
}

v8::Local<v8::Object> IPlayerToObject(IPlayer *player, v8::Local<v8::Context> context) {
	ObjectMethods methods = {
			{ "setHealth", setHealth }
	};

	return InterfaceToObject<IPlayer>(player, context, methods);
}