#include "Socket.hpp"
#include <nng/protocol/reqrep0/rep.h>
#include <nng/protocol/reqrep0/req.h>

nng_socket MessageSocket::socketClient_;
nng_socket MessageSocket::socketServer_;
std::string MessageSocket::socketName_;
bool MessageSocket::clientInitialized_ = false;
bool MessageSocket::serverInitialized_ = false;

bool MessageSocket::Init(const std::string& name)
{
	socketName_ = name;
	int ret_value;

	ret_value = nng_req0_open(&socketServer_);
	if (ret_value != 0)
	{
		std::cout << "nng_socket" << ": " << nng_strerror(ret_value) << std::endl;
		serverInitialized_ = false;
		return false;
	}

	ret_value = nng_dial(socketServer_, (std::string("ipc:///tmp/") + name + "_server.ipc").c_str(), NULL, 0);
	if (ret_value != 0)
	{
		std::cout << "nng_dial" << ": " << nng_strerror(ret_value) << std::endl;
		serverInitialized_ = false;
		return false;
	}

	serverInitialized_ = true;
	return true;
}

bool MessageSocket::CreateClient()
{
	int ret_value = 0;

	ret_value = nng_rep0_open(&socketClient_);
	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_rep0_open: " << nng_strerror(ret_value) << std::endl;
		clientInitialized_ = false;
		return false;
	}

	ret_value = nng_listen(socketClient_, (std::string("ipc:///tmp/omp_node_client") + ".ipc").c_str(), NULL, 0);
	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_listen: " << nng_strerror(ret_value);
		clientInitialized_ = false;
		return false;
	}

	bool result = MessageSocket::SendRequest("{\"name\":\"create_omp_ipc_client\"}");
	if (!result)
	{
		clientInitialized_ = false;
		return false;
	}

	std::string recieveMessage;
	result = ReceiveResponseBlocking(recieveMessage);
	if (!result)
	{
		clientInitialized_ = false;
		return false;
	}

	clientInitialized_ = true;
	return true;
}

void MessageSocket::Destroy()
{
	nng_close(socketClient_);
	nng_close(socketServer_);
	serverInitialized_ = false;
	clientInitialized_ = false;
}

bool MessageSocket::SendResponse(const std::string& message)
{
	if (!clientInitialized_)
	{
		return false;
	}

	int ret_value = 0;

	ret_value = nng_send(socketClient_, static_cast<void*>(const_cast<char*>(message.data())), message.size(), 0);
	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_send: " << nng_strerror(ret_value);
		return false;
	}

	return true;
}

bool MessageSocket::ReceiveRequestBlocking(std::string& message)
{
	if (!clientInitialized_)
	{
		return false;
	}

	char* buf = NULL;
	size_t sz = 0;
	int ret_value = 0;

	ret_value = nng_recv(socketClient_, &buf, &sz, NNG_FLAG_ALLOC);
	if (ret_value == NNG_EAGAIN)
	{
		return false;
	}

	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_recv: " << nng_strerror(ret_value);
		return false;
	}

	message = std::string(buf, sz);
	nng_free(buf, sz);
	return true;
}

bool MessageSocket::ReceiveRequest(std::string& message)
{
	if (!clientInitialized_)
	{
		return false;
	}

	char* buf = NULL;
	size_t sz = 0;
	int ret_value = 0;

	ret_value = nng_recv(socketClient_, &buf, &sz, NNG_FLAG_ALLOC | NNG_FLAG_NONBLOCK);
	if (ret_value == NNG_EAGAIN)
	{
		return false;
	}

	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_recv: " << nng_strerror(ret_value);
		return false;
	}

	message = std::string(buf, sz);
	nng_free(buf, sz);
	return true;
}

bool MessageSocket::SendRequest(const std::string& message)
{
	if (!serverInitialized_)
	{
		return false;
	}

	int ret_value = 0;

	ret_value = nng_send(socketServer_, static_cast<void*>(const_cast<char*>(message.data())), message.size(), 0);
	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_send: " << nng_strerror(ret_value);
		return false;
	}

	return true;
}

bool MessageSocket::ReceiveResponseBlocking(std::string& message)
{
	if (!serverInitialized_)
	{
		return false;
	}

	char* buf = NULL;
	size_t sz = 0;
	int ret_value = 0;

	ret_value = nng_recv(socketServer_, &buf, &sz, NNG_FLAG_ALLOC);
	if (ret_value == NNG_EAGAIN)
	{
		return false;
	}

	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_recv: " << nng_strerror(ret_value);
		return false;
	}

	message = std::string(buf, sz);
	return true;
}

bool MessageSocket::ReceiveResponse(std::string& message)
{
	if (!serverInitialized_)
	{
		return false;
	}

	char* buf = NULL;
	size_t sz = 0;
	int ret_value = 0;

	ret_value = nng_recv(socketServer_, &buf, &sz, NNG_FLAG_ALLOC | NNG_FLAG_NONBLOCK);
	if (ret_value == NNG_EAGAIN)
	{
		return false;
	}

	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_recv: " << nng_strerror(ret_value);
		return false;
	}

	message = std::string(buf, sz);
	return true;
}
