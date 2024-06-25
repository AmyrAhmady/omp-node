#include "../Impl.hpp"
#include "../MacroMagic.hpp"

DECLARE_API_ARGNUM(Menu, Create, 6, StringCharPtr title, uint32_t columns, float x, float y, float column1Width, float column2Width, IntRef id)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Menu.Create(title, columns, x, y, column1Width, column2Width, id);
	API_RETURN(objectPtr ret, IntRef id);
}

DECLARE_API(Menu, Destroy, objectPtr menu)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Menu.Destroy(menu);
	API_RETURN(bool ret);
}

DECLARE_API(Menu, FromID, int menuid)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->Menu.FromID(menuid);
	API_RETURN(objectPtr ret);
}

DECLARE_API(Menu, GetID, objectPtr menu)
{
	int ret = Runtime::Instance().GetOMPAPI()->Menu.GetID(menu);
	API_RETURN(int ret);
}

DECLARE_API(Menu, AddItem, objectPtr menu, uint8_t column, StringCharPtr text)
{
	int ret = Runtime::Instance().GetOMPAPI()->Menu.AddItem(menu, column, text);
	API_RETURN(int ret);
}

DECLARE_API(Menu, SetColumnHeader, objectPtr menu, uint8_t column, StringCharPtr headerTitle)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Menu.SetColumnHeader(menu, column, headerTitle);
	API_RETURN(bool ret);
}

DECLARE_API(Menu, ShowForPlayer, objectPtr menu, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Menu.ShowForPlayer(menu, player);
	API_RETURN(bool ret);
}

DECLARE_API(Menu, HideForPlayer, objectPtr menu, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Menu.HideForPlayer(menu, player);
	API_RETURN(bool ret);
}

DECLARE_API(Menu, Disable, objectPtr menu)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Menu.Disable(menu);
	API_RETURN(bool ret);
}

DECLARE_API(Menu, DisableRow, objectPtr menu, uint8_t row)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Menu.DisableRow(menu, row);
	API_RETURN(bool ret);
}

DECLARE_API(Menu, IsValid, objectPtr menu)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Menu.IsValid(menu);
	API_RETURN(bool ret);
}

DECLARE_API(Menu, IsDisabled, objectPtr menu)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Menu.IsDisabled(menu);
	API_RETURN(bool ret);
}

DECLARE_API(Menu, IsRowDisabled, objectPtr menu, int row)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Menu.IsRowDisabled(menu, row);
	API_RETURN(bool ret);
}

DECLARE_API(Menu, GetColumns, objectPtr menu)
{
	int ret = Runtime::Instance().GetOMPAPI()->Menu.GetColumns(menu);
	API_RETURN(int ret);
}

DECLARE_API(Menu, GetItems, objectPtr menu, int column)
{
	int ret = Runtime::Instance().GetOMPAPI()->Menu.GetItems(menu, column);
	API_RETURN(int ret);
}

DECLARE_API_ARGNUM(Menu, GetPos, 1, objectPtr menu, FloatRef x, FloatRef y)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Menu.GetPos(menu, x, y);
	API_RETURN(bool ret, FloatRef x, FloatRef y);
}

DECLARE_API_ARGNUM(Menu, GetColumnWidth, 1, objectPtr menu, FloatRef column1Width, FloatRef column2Width)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Menu.GetColumnWidth(menu, column1Width, column2Width);
	API_RETURN(bool ret, FloatRef column1Width, FloatRef column2Width);
}

DECLARE_API_ARGNUM(Menu, GetColumnHeader, 2, objectPtr menu, int column, OutputStringViewPtr header)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Menu.GetColumnHeader(menu, column, header);
	API_RETURN(bool ret, OutputStringViewPtr header);
}

DECLARE_API_ARGNUM(Menu, GetItem, 3, objectPtr menu, int column, int row, OutputStringViewPtr item)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Menu.GetItem(menu, column, row, item);
	API_RETURN(bool ret, OutputStringViewPtr item);
}
