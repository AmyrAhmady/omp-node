#include <Windows.h>
#include <iostream>
#include <napi.h>
#include <nng/nng.h>
#include <nng/protocol/reqrep0/rep.h>
#include <nng/protocol/reqrep0/req.h>
#include <nng/supplemental/util/platform.h>
#include <string>

nng_socket nngSocketClient;
nng_socket nngSocketServer;

void fatal(const char* func, int rv)
{
	std::cout << func << ": " << nng_strerror(rv) << std::endl;
}

void log(const char* func, char* msg)
{
	std::cout << func << ": " << msg << std::endl;
}

Napi::Function eventListener;

bool SendRequest(const std::string& message)
{
	int rv;

	rv = nng_send(nngSocketClient, static_cast<void*>(const_cast<char*>(message.data())), message.size(), 0);
	if (rv != 0)
	{
		fatal("nng_send", rv);
		return false;
	}
	return true;
}

bool ReceiveResponse(std::string& message)
{
	int rv;
	size_t sz;
	char* buf = NULL;
	// Send data to IPC component
	rv = nng_recv(nngSocketClient, &buf, &sz, NNG_FLAG_ALLOC);
	if (rv != 0)
	{
		fatal("nng_recv", rv);
		return false;
	}

	message = std::string(buf, sz);
	nng_free(buf, sz);
	return true;
}

bool SendResponse(const std::string& message)
{
	int rv;

	rv = nng_send(nngSocketServer, static_cast<void*>(const_cast<char*>(message.data())), message.size(), 0);
	if (rv != 0)
	{
		fatal("nng_send", rv);
		return false;
	}
	return true;
}

bool ReceiveRequest(std::string& message)
{
	int rv;
	size_t sz;
	char* buf = NULL;
	// Send data to IPC component
	rv = nng_recv(nngSocketServer, &buf, &sz, NNG_FLAG_ALLOC);
	if (rv != 0)
	{
		fatal("nng_recv", rv);
		return false;
	}

	message = std::string(buf, sz);
	nng_free(buf, sz);
	return true;
}

Napi::Boolean InitializeIPC(const Napi::CallbackInfo& info)
{
	int rv;
	Napi::Env env = info.Env();

	rv = nng_req0_open(&nngSocketClient);

	if (rv != 0)
	{
		fatal("nng_socket", rv);
		return Napi::Boolean::New(env, false);
	}

	if ((rv = nng_dial(nngSocketClient, "ipc:///tmp/omp_node_server.ipc", NULL, 0)) != 0)
	{
		fatal("nng_dial", rv);
		return Napi::Boolean::New(env, false);
	}

	return Napi::Boolean::New(env, true);
}

Napi::Boolean Close(const Napi::CallbackInfo& info)
{
	Napi::Env env = info.Env();
	nng_close(nngSocketServer);
	nng_close(nngSocketClient);
	return Napi::Boolean::New(env, true);
}

Napi::Value AddonSendMessage(const Napi::CallbackInfo& info)
{
	Napi::Env env = info.Env();

	std::string message = info[0].ToString().Utf8Value();
	//auto start = std::chrono::high_resolution_clock::now();

	bool result = SendRequest(message);
	if (!result)
	{
		return Napi::String::From(env, "{\"ret_value\":\"fail_to_send_to_ipc_server\"}");
	}

	std::string recieveMessage;
	result = ReceiveResponse(recieveMessage);

	if (!result)
	{
		return Napi::String::From(env, "{\"ret_value\":\"fail_to_receive_from_ipc_server\"}");
	}

	//auto elapsed = std::chrono::high_resolution_clock::now() - start;
	//long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	//printf("Receive time %lli microseconds\n", microseconds);

	return Napi::String::From(env, recieveMessage);
}

Napi::Value JSReceiveRequest(const Napi::CallbackInfo& info)
{
	bool rv;
	Napi::Env env = info.Env();

	std::string result;
	rv = ReceiveRequest(result);
	if (!rv)
	{
		return Napi::Value(Napi::Boolean::New(env, false));
	}

	return Napi::Value(Napi::String::From(env, result));
}

Napi::Boolean JSSendResponse(const Napi::CallbackInfo& info)
{
	bool rv;
	Napi::Env env = info.Env();

	std::string message = info[0].ToString().Utf8Value();
	rv = SendResponse(message);
	if (!rv)
	{
		return Napi::Boolean::New(env, false);
	}

	return Napi::Boolean::New(env, true);
}

Napi::Value InitializeClient(const Napi::CallbackInfo& info)
{
	Napi::Env env = info.Env();
	int ret_value = 0;

	ret_value = nng_rep0_open(&nngSocketServer);
	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_rep0_open: " << nng_strerror(ret_value) << std::endl;
		std::exit(1);
	}

	ret_value = nng_listen(nngSocketServer, (std::string("ipc:///tmp/omp_node_client") + ".ipc").c_str(), NULL, 0);
	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_listen: " << nng_strerror(ret_value);
		std::exit(1);
	}

	bool result = SendRequest("{\"name\":\"create_omp_ipc_client\"}");
	if (!result)
	{
		return Napi::String::From(env, "{\"ret_value\":\"fail_to_send_to_ipc_server\"}");
	}

	std::string recieveMessage;
	result = ReceiveResponse(recieveMessage);

	if (!result)
	{
		return Napi::String::From(env, "{\"ret_value\":\"fail_to_receive_from_ipc_server\"}");
	}

	return Napi::String::From(env, recieveMessage);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
	exports.Set(Napi::String::New(env, "initializeIPC"), Napi::Function::New(env, InitializeIPC));
	exports.Set(Napi::String::New(env, "initializeClient"), Napi::Function::New(env, InitializeClient));
	exports.Set(Napi::String::New(env, "close"), Napi::Function::New(env, Close));
	exports.Set(Napi::String::New(env, "sendMessage"), Napi::Function::New(env, AddonSendMessage));
	exports.Set(Napi::String::New(env, "receiveRequest"), Napi::Function::New(env, JSReceiveRequest));
	exports.Set(Napi::String::New(env, "sendResponse"), Napi::Function::New(env, JSSendResponse));
	return exports;
}

NODE_API_MODULE(addon, Init)
