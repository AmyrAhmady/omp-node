#include "menu_wrapper.hpp"
#include "../entity/entity_wrapper.hpp"
#include "../../converter/types.hpp"
#include "../../converter/vehicle.hpp"
#include "../../converter/entity.hpp"

WRAP_BASIC(IMenu)

WRAP_BASIC_CALL(IMenu,
                setColumnHeader,
                (Impl::String, FROM_JS_FN(String), header),
                (MenuColumn, JSToUInt<MenuColumn>, column))
WRAP_BASIC_CALL_RETURN(IMenu,
                       addCell,
                       (int, IntToJS<int>),
                       (Impl::String, FROM_JS_FN(String), itemText),
                       (MenuColumn, JSToUInt<MenuColumn>, column))
WRAP_BASIC_CALL(IMenu, disableRow, (MenuRow, JSToUInt<MenuRow>, row))
WRAP_BASIC_CALL_RETURN(IMenu, isRowEnabled, (bool, BoolToJS), (MenuRow, JSToUInt<MenuRow>, row))
WRAP_BASIC_CALL(IMenu, disable)
WRAP_BASIC_CALL_RETURN(IMenu, isEnabled, (bool, BoolToJS))
WRAP_BASIC_CALL_RETURN(IMenu, getPosition, (const Vector2&, VectorToJS<Vector2>))
WRAP_BASIC_CALL_RETURN(IMenu, getRowCount, (int, IntToJS<int>), (MenuColumn, JSToUInt<MenuColumn>, column))
WRAP_BASIC_CALL_RETURN(IMenu, getColumnCount, (int, IntToJS<int>))
WRAP_BASIC_CALL_RETURN(IMenu, getColumnWidths, (Vector2, VectorToJS<Vector2>))
WRAP_BASIC_CALL_RETURN(IMenu,
                       getColumnHeader,
                       (const StringView, TO_JS_FN(StringView)),
                       (MenuColumn, JSToUInt<MenuColumn>, column))
WRAP_BASIC_CALL_RETURN(IMenu,
                       getCell,
                       (const StringView, TO_JS_FN(StringView)),
                       (MenuColumn, JSToUInt<MenuColumn>, column),
                       (MenuRow, JSToUInt<MenuRow>, row))
WRAP_BASIC_CALL(IMenu, initForPlayer, (IPlayer & , JSToEntityRef<IPlayer>, player))
WRAP_BASIC_CALL(IMenu, showForPlayer, (IPlayer & , JSToEntityRef<IPlayer>, player))
WRAP_BASIC_CALL(IMenu, hideForPlayer, (IPlayer & , JSToEntityRef<IPlayer>, player))

WRAP_IID_PROVIDER_METHODS(IMenu)

void WrapMenu(IMenu *menu, v8::Local<v8::Context> context) {
    auto menuHandle = InterfaceToObject(menu, context, WRAPPED_METHODS(IMenu));

    menu->addExtension(new IHandleStorage(context->GetIsolate(), menuHandle), true);
}