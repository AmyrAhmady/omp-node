#include <Server/Components/Checkpoints/checkpoints.hpp>
#include "player.hpp"
#include "../logger.hpp"

void setHealth(const v8::FunctionCallbackInfo<v8::Value> &info) {
	if (info.Length() > 0) {
		auto isolate = info.GetIsolate();
		v8::Locker locker(isolate);
		v8::Isolate::Scope isolateScope(isolate);
		v8::HandleScope scope(isolate);

		v8::Local<v8::Context> context = isolate->GetCurrentContext();
		v8::Context::Scope contextScope(context);

		v8::Handle<v8::External> pointer = v8::Handle<v8::External>::Cast( info.This()->GetInternalField(0) );

		auto player = static_cast<IPlayer*>( pointer->Value() );

		float health = static_cast<float>(info[0]->NumberValue(context).ToChecked());

		L_DEBUG << "player->getName(): " << player->getName() << " " << "player->getID(): " << player->getID() << " " << player;

		player->setHealth(health);
	}
}

v8::Local<v8::Object> IPlayerToObject(v8::Local<v8::Context> context, IPlayer *player) {
	auto isolate = context->GetIsolate();

	auto objectTemplate = v8::ObjectTemplate::New(isolate);

	objectTemplate->SetInternalFieldCount(1);

	objectTemplate->Set(v8::String::NewFromUtf8(isolate, "setHealth", v8::NewStringType::kNormal).ToLocalChecked(), v8::FunctionTemplate::New(isolate, setHealth));

	auto object = objectTemplate->NewInstance(context).ToLocalChecked();

	object->SetInternalField(0, v8::External::New(isolate, player));

	return object;
}