#include <cstdlib>
#include <iostream>
#include <nng/nng.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <thread>
#include <chrono>

class MessageSocket
{
public:
	static bool Init(const std::string& name);
	static void Destroy();
	static bool CreateClient();

	static bool SendResponse(const std::string& message);
	static bool ReceiveRequestBlocking(std::string& message);
	static bool ReceiveRequest(std::string& message);

	static bool SendRequest(const std::string& message);
	static bool ReceiveResponseBlocking(std::string& message);
	static bool ReceiveResponse(std::string& message);

	bool processingEvents_ = false;
private:
	static nng_socket socketClient_;
	static nng_socket socketServer_;
	static std::string socketName_;
	static bool clientInitialized_;
	static bool serverInitialized_;
};
