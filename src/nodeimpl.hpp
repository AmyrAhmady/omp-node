#pragma once
#include <unordered_map>
#include "node.h"
#include "node_api.h"
#include "env.h"
#include "env-inl.h"
#include "v8.h"
#include "uv.h"
#include "libplatform/libplatform.h"
#include "resource.hpp"
#include "uvloop.hpp"
#include "wrapper/core/core_wrapper.hpp"

namespace ompnode
{
	class NodeImpl
	{
	public:
		static std::unordered_map<node::Environment*, std::shared_ptr<Resource>> resourcesPool;

		static void LoadAllResources(const std::vector<std::string>& resources, bool enable_resources = true);

		NodeImpl();
		~NodeImpl();

		void Initialize(ICore *core);
		bool LoadResource(const std::string& name);
		bool LoadResource(const std::string& name, const std::string& entryFile);
		bool UnloadResource(const std::string& name);
		bool ReloadResource(const std::string& name);

		inline v8::Platform* GetPlatform()
		{
			return v8Platform.get();
		}

		inline v8::Isolate* GetIsolate()
		{
			return v8Isolate;
		}

		inline node::IsolateData* GetNodeIsolate()
		{
			return nodeData.get();
		}

		inline UvLoop* GetUVLoop()
		{
			return nodeLoop.get();
		}

		inline ICore* GetCore() {
			return core;
		}

		void Tick();

		void Stop();

	private:
		v8::Isolate* v8Isolate;
		std::unique_ptr<node::IsolateData, decltype(&node::FreeIsolateData)> nodeData;
		std::unique_ptr<node::MultiIsolatePlatform> v8Platform;
		std::unique_ptr<node::ArrayBufferAllocator> arrayBufferAllocator;
		std::unique_ptr<UvLoop> nodeLoop;
		std::unordered_map<std::string, node::Environment*> resourceNamesPool;
		ICore *core;
	};

	extern NodeImpl nodeImpl;
}