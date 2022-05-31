#include "../../logger.hpp"
#include "textlabel_pool_wrapper.hpp"
#include "textlabel_wrapper.hpp"
#include "../../converter/primitive.hpp"
#include "../../converter/types.hpp"
#include "../../converter/entity.hpp"
#include "../entry_handler.hpp"
#include "Server/Components/Vehicles/vehicles.hpp"
#include "../pool/read_only_pool_wrapper.hpp"
#include "../pool/pool_wrapper.hpp"

WRAP_BASIC(ITextLabelsComponent)

WRAP_BASIC_CALL_RETURN_OVERLOAD(ITextLabelsComponent,
                                create,
                                (create, info[6]->IsUndefined(), (ITextLabel
                                    * , EntityToJS<ITextLabel>), (Impl::String, JSToString, text), (Colour, JSToColour, colour), (Vector3, JSToVector<
                                    Vector3>, pos), (float, JSToFloat, drawDist), (int, JSToInt, vw), (bool, JSToBool, los)),
                                (create, GetValueInterfaceType(info[6], context) == typeid(IPlayer).name(), (ITextLabel
                                    * , EntityToJS<ITextLabel>), (Impl::String, JSToString, text), (Colour, JSToColour, colour), (Vector3, JSToVector<
                                    Vector3>, pos), (float, JSToFloat, drawDist), (int, JSToInt, vw), (bool, JSToBool, los), (
                                    IPlayer & , JSToEntityRef<IPlayer>, attach)),
                                (create, GetValueInterfaceType(info[6], context) == typeid(IVehicle).name(), (ITextLabel
                                    * , EntityToJS<ITextLabel>), (Impl::String, JSToString, text), (Colour, JSToColour, colour), (Vector3, JSToVector<
                                    Vector3>, pos), (float, JSToFloat, drawDist), (int, JSToInt, vw), (bool, JSToBool, los), (
                                    IVehicle & , JSToEntityRef<IVehicle>, attach)))

WRAP_READ_ONLY_POOL_METHODS(ITextLabelsComponent, ITextLabel, EntityToJS<ITextLabel>)
WRAP_POOL_METHODS(ITextLabelsComponent, ITextLabel)

NodeJSEntryHandler<ITextLabel> *handler;

void WrapTextLabelPool(ITextLabelsComponent *textLabelPool, v8::Local<v8::Context> context) {
    handler = new NodeJSEntryHandler<ITextLabel>(context, WrapTextLabel);
    textLabelPool->getPoolEventDispatcher().addEventHandler(handler);
    textLabelPool->addExtension(handler, true);

    auto textLabelPoolHandle = InterfaceToObject(textLabelPool, context, WRAPPED_METHODS(ITextLabelsComponent));
    textLabelPool->addExtension(new IHandleStorage(context->GetIsolate(), textLabelPoolHandle), true);

    auto poolEventDispatcherHandleStorage =
        WRAPPED_POOL_EVENT_DISPATCHER(ITextLabel)(&textLabelPool->getPoolEventDispatcher(), context);
    textLabelPool->addExtension(poolEventDispatcherHandleStorage, true);
}