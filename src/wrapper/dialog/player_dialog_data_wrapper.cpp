#include "../../logger.hpp"
#include "player_dialog_data_wrapper.hpp"
#include "../../converter/entity.hpp"

WRAP_BASIC(IPlayerDialogData)

WRAP_BASIC_CALL(IPlayerDialogData, hide, (IPlayer & , JSToEntityRef<IPlayer>, player))
WRAP_BASIC_CALL(IPlayerDialogData,
                    show,
                    (IPlayer & , JSToEntityRef<IPlayer>, player),
                    (int, JSToInt<int>, id),
                    (DialogStyle, JSToEnum<DialogStyle>, style),
                    (Impl::String, JSToString, title),
                    (Impl::String, JSToString, body),
                    (Impl::String, JSToString, button1),
                    (Impl::String, JSToString, button2))
WRAP_BASIC_CODE(IPlayerDialogData, get, {
    ENTER_FUNCTION_CALLBACK(info)
    auto external = GetContextExternalPointer<IPlayerDialogData>(info);
    if (external == nullptr) {
        return;
    }
    v8::TryCatch tryCatch(isolate);

    int id;
    DialogStyle style;
    StringView title;
    StringView body;
    StringView button1;
    StringView button2;

    external->get(id, style, title, body, button1, button2);

    v8::Local<v8::Array> array = v8::Array::New(context->GetIsolate(), 6);

    if (array.IsEmpty())
        return;

    // Fill out the values
    array->Set(context, 0, IntToJS(id, context)).Check();
    array->Set(context, 1, EnumToJS(style, context)).Check();
    array->Set(context, 2, StringViewToJS(title, context)).Check();
    array->Set(context, 3, StringViewToJS(body, context)).Check();
    array->Set(context, 4, StringViewToJS(button1, context)).Check();
    array->Set(context, 5, StringViewToJS(button2, context)).Check();

    info.GetReturnValue().Set(array);
})
WRAP_BASIC_CALL_RETURN(IPlayerDialogData, getActiveID, (int, IntToJS))

std::vector<IExtension *> WrapPlayerDialogData(IPlayer *player,
                                                  IPlayerDialogData *playerDialogData,
                                                  v8::Local<v8::Context> context) {

    std::vector<IExtension *> handleStorages;

    auto objectPoolHandle = InterfaceToObject(playerDialogData, context, WRAPPED_METHODS(IPlayerDialogData), player);
    handleStorages.push_back(new PlayerDialogDataHandleStorage(context->GetIsolate(), objectPoolHandle));

    return handleStorages;
}
