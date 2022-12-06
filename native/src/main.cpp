#include <Windows.h>
#include <iostream>
#include <napi.h>
#include "Socket.hpp"
#include <nng/nng.h>
#include <nng/protocol/reqrep0/rep.h>
#include <nng/protocol/reqrep0/req.h>
#include <nng/supplemental/util/platform.h>
#include <string>

Napi::Boolean InitializeIPC(const Napi::CallbackInfo& info)
{
	Napi::Env env = info.Env();

	bool ret = MessageSocket::Init("omp_node");
	if (!ret)
	{
		return Napi::Boolean::New(env, false);
	}

	return Napi::Boolean::New(env, true);
}

Napi::Value InitializeClient(const Napi::CallbackInfo& info)
{
	Napi::Env env = info.Env();
	bool result = MessageSocket::CreateClient();
	if (!result)
	{
		return Napi::String::From(env, "{\"ret_value\":\"failed_to_create_client\"}");
	}

	return Napi::String::From(env, "{\"ret_value\":true}");
}

Napi::Boolean Close(const Napi::CallbackInfo& info)
{
	Napi::Env env = info.Env();
	MessageSocket::Destroy();
	return Napi::Boolean::New(env, true);
}

Napi::Value SendMessageSync(const Napi::CallbackInfo& info)
{
	Napi::Env env = info.Env();

	std::string message = info[0].ToString().Utf8Value();
	bool result = MessageSocket::SendRequest(message);
	if (!result)
	{
		return Napi::String::From(env, "{\"ret_value\":\"fail_to_send_to_ipc_server\"}");
	}

	std::string recieveMessage;
	result = MessageSocket::ReceiveResponseBlocking(recieveMessage);
	if (!result)
	{
		return Napi::String::From(env, "{\"ret_value\":\"fail_to_receive_from_ipc_server\"}");
	}

	return Napi::String::From(env, recieveMessage);
}

Napi::Value ReceiveRequestBlocking(const Napi::CallbackInfo& info)
{
	bool rv;
	Napi::Env env = info.Env();

	std::string result;
	rv = MessageSocket::ReceiveRequestBlocking(result);
	if (!rv)
	{
		return Napi::Value(Napi::Boolean::New(env, false));
	}

	return Napi::Value(Napi::String::From(env, result));
}

Napi::Value ReceiveRequest(const Napi::CallbackInfo& info)
{
	bool rv;
	Napi::Env env = info.Env();

	std::string result;
	rv = MessageSocket::ReceiveRequest(result);
	if (!rv)
	{
		return Napi::Value(Napi::Boolean::New(env, false));
	}

	return Napi::Value(Napi::String::From(env, result));
}

Napi::Boolean SendResponse(const Napi::CallbackInfo& info)
{
	bool rv;
	Napi::Env env = info.Env();

	std::string message = info[0].ToString().Utf8Value();
	rv = MessageSocket::SendResponse(message);
	if (!rv)
	{
		return Napi::Boolean::New(env, false);
	}

	return Napi::Boolean::New(env, true);
}

Napi::Value ReceiveResponseBlocking(const Napi::CallbackInfo& info)
{
	bool rv;
	Napi::Env env = info.Env();

	std::string result;
	rv = MessageSocket::ReceiveResponseBlocking(result);
	if (!rv)
	{
		return Napi::Value(Napi::Boolean::New(env, false));
	}

	return Napi::Value(Napi::String::From(env, result));
}

Napi::Value ReceiveResponse(const Napi::CallbackInfo& info)
{
	bool rv;
	Napi::Env env = info.Env();

	std::string result;
	rv = MessageSocket::ReceiveResponse(result);
	if (!rv)
	{
		return Napi::Value(Napi::Boolean::New(env, false));
	}

	return Napi::Value(Napi::String::From(env, result));
}

Napi::Boolean SendRequest(const Napi::CallbackInfo& info)
{
	bool rv;
	Napi::Env env = info.Env();

	std::string message = info[0].ToString().Utf8Value();
	rv = MessageSocket::SendRequest(message);
	if (!rv)
	{
		return Napi::Boolean::New(env, false);
	}

	return Napi::Boolean::New(env, true);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
	exports.Set(Napi::String::New(env, "initializeIPC"), Napi::Function::New(env, InitializeIPC));
	exports.Set(Napi::String::New(env, "initializeClient"), Napi::Function::New(env, InitializeClient));
	exports.Set(Napi::String::New(env, "close"), Napi::Function::New(env, Close));
	exports.Set(Napi::String::New(env, "sendMessageSync"), Napi::Function::New(env, SendMessageSync));
	exports.Set(Napi::String::New(env, "receiveRequestBlocking"), Napi::Function::New(env, ReceiveRequestBlocking));
	exports.Set(Napi::String::New(env, "receiveRequest"), Napi::Function::New(env, ReceiveRequest));
	exports.Set(Napi::String::New(env, "sendResponse"), Napi::Function::New(env, SendResponse));
	exports.Set(Napi::String::New(env, "receiveResponseBlocking"), Napi::Function::New(env, ReceiveResponseBlocking));
	exports.Set(Napi::String::New(env, "receiveResponse"), Napi::Function::New(env, ReceiveResponse));
	exports.Set(Napi::String::New(env, "sendRequest"), Napi::Function::New(env, SendRequest));
	return exports;
}

NODE_API_MODULE(addon, Init)
