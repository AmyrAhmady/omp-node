#include "../common.hpp"
#include "Server/Components/Pickups/pickups.hpp"
#include "Server/Components/Objects/objects.hpp"
#include "Server/Components/TextLabels/textlabels.hpp"
#include "Server/Components/Vehicles/vehicles.hpp"
#include "Server/Components/Actors/actors.hpp"
#include "Server/Components/Menus/menus.hpp"
#include "Server/Components/TextDraws/textdraws.hpp"
#include "Server/Components/TextDraws/textdraws.hpp"
#include "Server/Components/TextLabels/textlabels.hpp"
#include "Server/Components/GangZones/gangzones.hpp"
#include "../runtime.hpp"

#define ADD_POOL_EVENT(pool)                                                                   \
	if (pool)                                                                                  \
	{                                                                                          \
		pool->getPoolEventDispatcher().addEventHandler(&InternalPoolEntityEvents::Instance()); \
	}

#define REMOVE_POOL_EVENT(pool)                                                                   \
	if (pool)                                                                                     \
	{                                                                                             \
		pool->getPoolEventDispatcher().removeEventHandler(&InternalPoolEntityEvents::Instance()); \
	}

enum class POOL_TYPE
{
	PLAYER,
	OBJECT,
	TEXTDRAW,
	PICKUP,
	GANGZONE,
	TEXTLABEL,
	ACTOR,
	MENU,
	PLAYEROBJECT,
	PLAYERTEXTLABEL,
	PLAYERTEXTDRAW
};

class InternalPoolEntityEvents : public PoolEventHandler<IPlayer>, public PoolEventHandler<IVehicle>, public PoolEventHandler<IObject>, public PoolEventHandler<ITextDraw>, public PoolEventHandler<IPickup>, public PoolEventHandler<IGangZone>, public PoolEventHandler<ITextLabel>, public PoolEventHandler<IActor>, public PoolEventHandler<IMenu>
{
public:
	void onPoolEntryDestroyed(IPlayer& player) override
	{
		Runtime::Instance().DispatchEvents("playerPoolEntryDestroy", false, EventBadRet::None, player.getID());
	}

	void onPoolEntryCreated(IPlayer& player) override
	{
		Runtime::Instance().DispatchEvents("playerPoolEntryCreate", false, EventBadRet::None, player.getID());
	}

	void onPoolEntryDestroyed(IVehicle& vehicle) override
	{
		Runtime::Instance().DispatchEvents("vehiclePoolEntryDestroy", false, EventBadRet::None, vehicle.getID());
	}

	void onPoolEntryCreated(IVehicle& vehicle) override
	{
		Runtime::Instance().DispatchEvents("vehiclePoolEntryCreate", false, EventBadRet::None, vehicle.getID());
	}

	void onPoolEntryDestroyed(IObject& object) override
	{
		Runtime::Instance().DispatchEvents("objectPoolEntryDestroy", false, EventBadRet::None, object.getID());
	}

	void onPoolEntryCreated(IObject& object) override
	{
		Runtime::Instance().DispatchEvents("objectPoolEntryCreate", false, EventBadRet::None, object.getID());
	}

	void onPoolEntryDestroyed(ITextDraw& textdraw) override
	{
		Runtime::Instance().DispatchEvents("textdrawPoolEntryDestroy", false, EventBadRet::None, textdraw.getID());
	}

	void onPoolEntryCreated(ITextDraw& textdraw) override
	{
		Runtime::Instance().DispatchEvents("textdrawPoolEntryCreate", false, EventBadRet::None, textdraw.getID());
	}

	void onPoolEntryDestroyed(IPickup& pickup) override
	{
		Runtime::Instance().DispatchEvents("pickupPoolEntryDestroy", false, EventBadRet::None, pickup.getID());
	}

	void onPoolEntryCreated(IPickup& pickup) override
	{
		Runtime::Instance().DispatchEvents("pickupPoolEntryCreate", false, EventBadRet::None, pickup.getID());
	}

	void onPoolEntryDestroyed(IGangZone& gangzone) override
	{
		Runtime::Instance().DispatchEvents("gangzonePoolEntryDestroy", false, EventBadRet::None, gangzone.getID());
	}

	void onPoolEntryCreated(IGangZone& gangzone) override
	{
		Runtime::Instance().DispatchEvents("gangzonePoolEntryCreate", false, EventBadRet::None, gangzone.getID());
	}

	void onPoolEntryDestroyed(ITextLabel& textlabel) override
	{
		Runtime::Instance().DispatchEvents("textlabelPoolEntryDestroy", false, EventBadRet::None, textlabel.getID());
	}

	void onPoolEntryCreated(ITextLabel& textlabel) override
	{
		Runtime::Instance().DispatchEvents("textlabelPoolEntryCreate", false, EventBadRet::None, textlabel.getID());
	}

	void onPoolEntryDestroyed(IActor& actor) override
	{
		Runtime::Instance().DispatchEvents("actorPoolEntryDestroy", false, EventBadRet::None, actor.getID());
	}

	void onPoolEntryCreated(IActor& actor) override
	{
		Runtime::Instance().DispatchEvents("actorPoolEntryCreate", false, EventBadRet::None, actor.getID());
	}

	void onPoolEntryDestroyed(IMenu& menu) override
	{
		Runtime::Instance().DispatchEvents("menuPoolEntryDestroy", false, EventBadRet::None, menu.getID());
	}

	void onPoolEntryCreated(IMenu& menu) override
	{
		Runtime::Instance().DispatchEvents("menuPoolEntryCreate", false, EventBadRet::None, menu.getID());
	}

	static InternalPoolEntityEvents& Instance()
	{
		static InternalPoolEntityEvents _Instance;
		return _Instance;
	}
};

class InternalPoolPlayerEntityEvents_PlayerObjects : public PlayerConnectEventHandler, public PoolEventHandler<IPlayerObject>
{
public:
	void onPlayerConnect(IPlayer& player) override
	{
		auto data = queryExtension<IPlayerObjectData>(player);
		if (data)
		{
			auto handlers = new InternalPoolPlayerEntityEvents_PlayerObjects();
			handlers->player_ = &player;
			pools[player.getID()] = handlers;
			data->getPoolEventDispatcher().addEventHandler(handlers);
		}
	}

	void onPlayerDisconnect(IPlayer& player, PeerDisconnectReason reason) override
	{
		auto data = queryExtension<IPlayerObjectData>(player);
		if (data)
		{
			auto handlers = pools[player.getID()];
			if (handlers)
			{
				data->getPoolEventDispatcher().removeEventHandler(handlers);
				delete handlers;
				pools[player.getID()] = nullptr;
			}
		}
	}

	void onPoolEntryDestroyed(IPlayerObject& playerObject) override
	{
		Runtime::Instance().DispatchEvents("playerObjectPoolEntryDestroy", false, EventBadRet::None, player_->getID(), playerObject.getID());
	}

	void onPoolEntryCreated(IPlayerObject& playerObject) override
	{
		Runtime::Instance().DispatchEvents("playerObjectPoolEntryCreate", false, EventBadRet::None, player_->getID(), playerObject.getID());
	}

	void RemovePlayerEvents()
	{
		for (auto handlers : pools)
		{
			if (handlers)
			{
				auto data = queryExtension<IPlayerObjectData>(handlers->player_);
				if (data)
				{
					int playerId = handlers->player_->getID();
					data->getPoolEventDispatcher().removeEventHandler(handlers);
					delete handlers;
					pools[playerId] = nullptr;
				}
			}
		}
	}

	static InternalPoolPlayerEntityEvents_PlayerObjects& Instance()
	{
		static InternalPoolPlayerEntityEvents_PlayerObjects _Instance;
		return _Instance;
	}

private:
	std::array<InternalPoolPlayerEntityEvents_PlayerObjects*, PLAYER_POOL_SIZE> pools;
	IPlayer* player_ = nullptr;
};

class InternalPoolPlayerEntityEvents_PlayerTextLabels : public PlayerConnectEventHandler, public PoolEventHandler<IPlayerTextLabel>
{
public:
	void onPlayerConnect(IPlayer& player) override
	{
		auto data = queryExtension<IPlayerTextLabelData>(player);
		if (data)
		{
			auto handlers = new InternalPoolPlayerEntityEvents_PlayerTextLabels();
			handlers->player_ = &player;
			pools[player.getID()] = handlers;
			data->getPoolEventDispatcher().addEventHandler(handlers);
		}
	}

	void onPlayerDisconnect(IPlayer& player, PeerDisconnectReason reason) override
	{
		auto data = queryExtension<IPlayerTextLabelData>(player);
		if (data)
		{
			auto handlers = pools[player.getID()];
			if (handlers)
			{
				data->getPoolEventDispatcher().removeEventHandler(handlers);
				delete handlers;
				pools[player.getID()] = nullptr;
			}
		}
	}

	void onPoolEntryDestroyed(IPlayerTextLabel& playerTextLabel) override
	{
		Runtime::Instance().DispatchEvents("playerTextLabelPoolEntryDestroy", false, EventBadRet::None, player_->getID(), playerTextLabel.getID());
	}

	void onPoolEntryCreated(IPlayerTextLabel& playerTextLabel) override
	{
		Runtime::Instance().DispatchEvents("playerTextLabelPoolEntryCreate", false, EventBadRet::None, player_->getID(), playerTextLabel.getID());
	}

	void RemovePlayerEvents()
	{
		for (auto handlers : pools)
		{
			if (handlers)
			{
				auto data = queryExtension<IPlayerTextLabelData>(handlers->player_);
				if (data)
				{
					int playerId = handlers->player_->getID();
					data->getPoolEventDispatcher().removeEventHandler(handlers);
					delete handlers;
					pools[playerId] = nullptr;
				}
			}
		}
	}

	static InternalPoolPlayerEntityEvents_PlayerTextLabels& Instance()
	{
		static InternalPoolPlayerEntityEvents_PlayerTextLabels _Instance;
		return _Instance;
	}

private:
	std::array<InternalPoolPlayerEntityEvents_PlayerTextLabels*, PLAYER_POOL_SIZE> pools;
	IPlayer* player_ = nullptr;
};

class InternalPoolPlayerEntityEvents_PlayerTextDraws : public PlayerConnectEventHandler, public PoolEventHandler<IPlayerTextDraw>
{
public:
	void onPlayerConnect(IPlayer& player) override
	{
		auto data = queryExtension<IPlayerTextDrawData>(player);
		if (data)
		{
			auto handlers = new InternalPoolPlayerEntityEvents_PlayerTextDraws();
			handlers->player_ = &player;
			pools[player.getID()] = handlers;
			data->getPoolEventDispatcher().addEventHandler(handlers);
		}
	}

	void onPlayerDisconnect(IPlayer& player, PeerDisconnectReason reason) override
	{
		auto data = queryExtension<IPlayerTextDrawData>(player);
		if (data)
		{
			auto handlers = pools[player.getID()];
			if (handlers)
			{
				data->getPoolEventDispatcher().removeEventHandler(handlers);
				delete handlers;
				pools[player.getID()] = nullptr;
			}
		}
	}

	void onPoolEntryDestroyed(IPlayerTextDraw& playerTextDraw) override
	{
		Runtime::Instance().DispatchEvents("playerTextDrawPoolEntryDestroy", false, EventBadRet::None, player_->getID(), playerTextDraw.getID());
	}

	void onPoolEntryCreated(IPlayerTextDraw& playerTextDraw) override
	{
		Runtime::Instance().DispatchEvents("playerTextDrawPoolEntryCreate", false, EventBadRet::None, player_->getID(), playerTextDraw.getID());
	}

	void RemovePlayerEvents()
	{
		for (auto handlers : pools)
		{
			if (handlers)
			{
				auto data = queryExtension<IPlayerTextDrawData>(handlers->player_);
				if (data)
				{
					int playerId = handlers->player_->getID();
					data->getPoolEventDispatcher().removeEventHandler(handlers);
					delete handlers;
					pools[playerId] = nullptr;
				}
			}
		}
	}

	static InternalPoolPlayerEntityEvents_PlayerTextDraws& Instance()
	{
		static InternalPoolPlayerEntityEvents_PlayerTextDraws _Instance;
		return _Instance;
	}

private:
	std::array<InternalPoolPlayerEntityEvents_PlayerTextDraws*, PLAYER_POOL_SIZE> pools;
	IPlayer* player_ = nullptr;
};

class NodeOmpPool
{
public:
	void Init(ICore* c, IComponentList* componentList)
	{
		players = &c->getPlayers();

		actors = componentList->queryComponent<IActorsComponent>();
		objects = componentList->queryComponent<IObjectsComponent>();
		pickups = componentList->queryComponent<IPickupsComponent>();
		textlabels = componentList->queryComponent<ITextLabelsComponent>();
		vehicles = componentList->queryComponent<IVehiclesComponent>();
		menus = componentList->queryComponent<IMenusComponent>();
		textdraws = componentList->queryComponent<ITextDrawsComponent>();
		gangzones = componentList->queryComponent<IGangZonesComponent>();
	}

	void AddPoolEvents()
	{
		if (players)
		{
			players->getPoolEventDispatcher().addEventHandler(&InternalPoolEntityEvents::Instance());
			players->getPlayerConnectDispatcher().addEventHandler(&InternalPoolPlayerEntityEvents_PlayerObjects::Instance(), EventPriority_Lowest);
			players->getPlayerConnectDispatcher().addEventHandler(&InternalPoolPlayerEntityEvents_PlayerTextLabels::Instance(), EventPriority_Lowest);
			players->getPlayerConnectDispatcher().addEventHandler(&InternalPoolPlayerEntityEvents_PlayerTextDraws::Instance(), EventPriority_Lowest);
		}

		ADD_POOL_EVENT(actors);
		ADD_POOL_EVENT(objects);
		ADD_POOL_EVENT(pickups);
		ADD_POOL_EVENT(textlabels);
		ADD_POOL_EVENT(vehicles);
		ADD_POOL_EVENT(menus);
		ADD_POOL_EVENT(textdraws);
		ADD_POOL_EVENT(gangzones);
	}

	void RemovePoolEvents()
	{
		if (players)
		{
			InternalPoolPlayerEntityEvents_PlayerObjects::Instance().RemovePlayerEvents();
			InternalPoolPlayerEntityEvents_PlayerTextLabels::Instance().RemovePlayerEvents();
			InternalPoolPlayerEntityEvents_PlayerTextDraws::Instance().RemovePlayerEvents();

			players->getPoolEventDispatcher().removeEventHandler(&InternalPoolEntityEvents::Instance());
			players->getPlayerConnectDispatcher().removeEventHandler(&InternalPoolPlayerEntityEvents_PlayerObjects::Instance());
			players->getPlayerConnectDispatcher().removeEventHandler(&InternalPoolPlayerEntityEvents_PlayerTextLabels::Instance());
			players->getPlayerConnectDispatcher().removeEventHandler(&InternalPoolPlayerEntityEvents_PlayerTextDraws::Instance());
		}

		// REMOVE_POOL_EVENT(actors);
		// REMOVE_POOL_EVENT(objects);
		// REMOVE_POOL_EVENT(pickups);
		// REMOVE_POOL_EVENT(textlabels);
		// REMOVE_POOL_EVENT(vehicles);
		// REMOVE_POOL_EVENT(menus);
		// REMOVE_POOL_EVENT(textdraws);
		// REMOVE_POOL_EVENT(gangzones);
	}

	static NodeOmpPool& Instance()
	{
		static NodeOmpPool _Instance;
		return _Instance;
	}

	static void at(const v8::FunctionCallbackInfo<v8::Value>& info)
	{
		v8::Isolate* isolate = info.GetIsolate();
		v8::Local<v8::Context> ctx = isolate->GetEnteredOrMicrotaskContext();

		V8_TO_INT32(info[0], pooltype_);
		auto pooltype = POOL_TYPE(pooltype_);

		V8_TO_INT32(info[1], id);

		auto pools = NodeOmpPool::Instance();

		void* ret = nullptr;
		switch (pooltype)
		{
		case POOL_TYPE::PLAYER:
			ret = reinterpret_cast<void*>(pools.players->get(id));
			break;
		case POOL_TYPE::OBJECT:
			ret = reinterpret_cast<void*>(pools.objects->get(id));
			break;
		case POOL_TYPE::TEXTDRAW:
			ret = reinterpret_cast<void*>(pools.textdraws->get(id));
			break;
		case POOL_TYPE::PICKUP:
			ret = reinterpret_cast<void*>(pools.pickups->get(id));
			break;
		case POOL_TYPE::GANGZONE:
			ret = reinterpret_cast<void*>(pools.gangzones->get(id));
			break;
		case POOL_TYPE::TEXTLABEL:
			ret = reinterpret_cast<void*>(pools.textlabels->get(id));
			break;
		case POOL_TYPE::ACTOR:
			ret = reinterpret_cast<void*>(pools.actors->get(id));
			break;
		case POOL_TYPE::MENU:
			ret = reinterpret_cast<void*>(pools.menus->get(id));
			break;
		case POOL_TYPE::PLAYERTEXTDRAW:
		case POOL_TYPE::PLAYEROBJECT:
		case POOL_TYPE::PLAYERTEXTLABEL:
		{
			V8_TO_UINTPTR(info[2], player_);
			auto player = reinterpret_cast<IPlayer*>(player_);

			if (player)
			{
				if (pooltype == POOL_TYPE::PLAYERTEXTDRAW)
				{
					auto data = queryExtension<IPlayerTextDrawData>(*player);
					if (data)
					{
						ret = data->get(id);
					}
				}
				else if (pooltype == POOL_TYPE::PLAYEROBJECT)
				{
					auto data = queryExtension<IPlayerObjectData>(*player);
					if (data)
					{
						ret = data->get(id);
					}
				}
				else if (pooltype == POOL_TYPE::PLAYERTEXTLABEL)
				{
					auto data = queryExtension<IPlayerTextLabelData>(*player);
					if (data)
					{
						ret = data->get(id);
					}
				}
			}
			break;
		}
		default:
			break;
		}

		if (sizeof(uintptr_t) == 8)
		{
			info.GetReturnValue().Set(v8::BigInt::NewFromUnsigned(isolate, uintptr_t(ret)));
		}
		else
		{
			info.GetReturnValue().Set(v8::Integer::NewFromUnsigned(isolate, uintptr_t(ret)));
		}
	}

private:
	IPlayerPool* players = nullptr;
	IPickupsComponent* pickups = nullptr;
	IObjectsComponent* objects = nullptr;
	ITextLabelsComponent* textlabels = nullptr;
	IVehiclesComponent* vehicles = nullptr;
	IActorsComponent* actors = nullptr;
	IMenusComponent* menus = nullptr;
	ITextDrawsComponent* textdraws = nullptr;
	IGangZonesComponent* gangzones = nullptr;
};
