#include <Windows.h>
#include <iostream>
#include <napi.h>
#include <nng/nng.h>
#include <nng/protocol/reqrep0/rep.h>
#include <nng/protocol/reqrep0/req.h>
#include <nng/supplemental/util/platform.h>
#include <string>

nng_socket nngSocket;

void fatal(const char* func, int rv)
{
	std::cout << func << ": " << nng_strerror(rv) << std::endl;
	exit(1);
}

void log(const char* func, char* msg)
{
	std::cout << func << ": " << msg << std::endl;
}

Napi::Value Add(const Napi::CallbackInfo& info)
{
	Napi::Env env = info.Env();

	if (info.Length() < 2) {
		Napi::TypeError::New(env, "Wrong number of arguments")
			.ThrowAsJavaScriptException();
		return env.Null();
	}

	if (!info[0].IsNumber() || !info[1].IsNumber()) {
		Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
		return env.Null();
	}

	double arg0 = info[0].As<Napi::Number>().DoubleValue();
	double arg1 = info[1].As<Napi::Number>().DoubleValue();
	Napi::Number num = Napi::Number::New(env, arg0 + arg1);

	return num;
}

Napi::Boolean InitializeIPC(const Napi::CallbackInfo& info)
{
	int rv;
	Napi::Env env = info.Env();

	rv = nng_req0_open(&nngSocket);

	if (rv != 0)
	{
		fatal("nng_socket", rv);
		return Napi::Boolean::New(env, false);
	}

	if ((rv = nng_dial(nngSocket, "ipc:///tmp/omp_node.ipc", NULL, 0)) != 0)
	{
		fatal("nng_dial", rv);
		return Napi::Boolean::New(env, false);
	}

	return Napi::Boolean::New(env, true);
}

Napi::Boolean Close(const Napi::CallbackInfo& info)
{
	Napi::Env env = info.Env();
	nng_close(nngSocket);
	return Napi::Boolean::New(env, true);
}

Napi::Value AddonSendMessage(const Napi::CallbackInfo& info)
{
	int rv;
	Napi::Env env = info.Env();
	size_t sz;
	char* buf = NULL;

	std::string message = info[0].ToString().Utf8Value();
	//auto start = std::chrono::high_resolution_clock::now();

	// Send data to IPC component
	rv = nng_send(nngSocket, static_cast<void*>(message.data()), message.size(), 0);
	if (rv != 0)
	{
		fatal("nng_send", rv);
		return Napi::String::From(env, "{\"ret_value\":\"fail_to_send_to_ipc_server\"}");
	}

	// Wait for return value from IPC component
	rv = nng_recv(nngSocket, &buf, &sz, NNG_FLAG_ALLOC);
	if (rv != 0)
	{
		fatal("nng_recv", rv);
		return Napi::String::From(env, "{\"ret_value\":\"fail_to_receive_from_ipc_server\"}");
	}

	std::string result(buf, sz);
	//auto elapsed = std::chrono::high_resolution_clock::now() - start;
	//long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	//printf("Receive time %lli\n", microseconds);

	nng_free(buf, sz);
	return Napi::String::From(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
	exports.Set(Napi::String::New(env, "add"), Napi::Function::New(env, Add));
	exports.Set(Napi::String::New(env, "initializeIPC"), Napi::Function::New(env, InitializeIPC));
	exports.Set(Napi::String::New(env, "close"), Napi::Function::New(env, Close));
	exports.Set(Napi::String::New(env, "sendMessage"), Napi::Function::New(env, AddonSendMessage));
	return exports;
}

NODE_API_MODULE(addon, Init)
