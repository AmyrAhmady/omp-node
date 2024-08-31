#include "../Impl.hpp"
#include "../API.hpp"

DECLARE_API_ARGNUM(TextDraw, Create, 3, float x, float y, StringCharPtr text, IntRef id)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->TextDraw.Create(x, y, text, id);
	API_RETURN(objectPtr ret, IntRef id);
}

DECLARE_API(TextDraw, Destroy, objectPtr textdraw)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.Destroy(textdraw);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, FromID, int textdrawid)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->TextDraw.FromID(textdrawid);
	API_RETURN(objectPtr ret);
}

DECLARE_API(TextDraw, GetID, objectPtr textdraw)
{
	int ret = Runtime::Instance().GetOMPAPI()->TextDraw.GetID(textdraw);
	API_RETURN(int ret);
}

DECLARE_API(TextDraw, IsValid, objectPtr textdraw)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.IsValid(textdraw);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, IsVisibleForPlayer, objectPtr player, objectPtr textdraw)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.IsVisibleForPlayer(player, textdraw);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, SetLetterSize, objectPtr textdraw, float sizeX, float sizeY)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.SetLetterSize(textdraw, sizeX, sizeY);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, SetTextSize, objectPtr textdraw, float sizeX, float sizeY)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.SetTextSize(textdraw, sizeX, sizeY);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, SetAlignment, objectPtr textdraw, int alignment)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.SetAlignment(textdraw, alignment);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, SetColor, objectPtr textdraw, uint32_t color)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.SetColor(textdraw, color);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, SetUseBox, objectPtr textdraw, bool use)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.SetUseBox(textdraw, use);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, SetBoxColor, objectPtr textdraw, uint32_t color)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.SetBoxColor(textdraw, color);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, SetShadow, objectPtr textdraw, int size)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.SetShadow(textdraw, size);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, SetOutline, objectPtr textdraw, int size)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.SetOutline(textdraw, size);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, SetBackgroundColor, objectPtr textdraw, uint32_t color)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.SetBackgroundColor(textdraw, color);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, SetFont, objectPtr textdraw, int font)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.SetFont(textdraw, font);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, SetSetProportional, objectPtr textdraw, bool set)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.SetSetProportional(textdraw, set);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, SetSelectable, objectPtr textdraw, bool set)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.SetSelectable(textdraw, set);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, ShowForPlayer, objectPtr player, objectPtr textdraw)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.ShowForPlayer(player, textdraw);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, HideForPlayer, objectPtr player, objectPtr textdraw)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.HideForPlayer(player, textdraw);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, ShowForAll, objectPtr textdraw)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.ShowForAll(textdraw);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, HideForAll, objectPtr textdraw)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.HideForAll(textdraw);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, SetString, objectPtr textdraw, StringCharPtr text)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.SetString(textdraw, text);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, SetPreviewModel, objectPtr textdraw, int model)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.SetPreviewModel(textdraw, model);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, SetPreviewRot, objectPtr textdraw, float rotationX, float rotationY, float rotationZ, float zoom)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.SetPreviewRot(textdraw, rotationX, rotationY, rotationZ, zoom);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, SetPreviewVehCol, objectPtr textdraw, int color1, int color2)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.SetPreviewVehCol(textdraw, color1, color2);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, SetPos, objectPtr textdraw, float x, float y)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.SetPos(textdraw, x, y);
	API_RETURN(bool ret);
}

DECLARE_API_ARGNUM(TextDraw, GetString, 1, objectPtr textdraw, OutputStringViewPtr text)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.GetString(textdraw, text);
	API_RETURN(bool ret, OutputStringViewPtr text);
}

DECLARE_API_ARGNUM(TextDraw, GetLetterSize, 1, objectPtr textdraw, FloatRef sizeX, FloatRef sizeY)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.GetLetterSize(textdraw, sizeX, sizeY);
	API_RETURN(bool ret, FloatRef sizeX, FloatRef sizeY);
}

DECLARE_API_ARGNUM(TextDraw, GetTextSize, 1, objectPtr textdraw, FloatRef sizeX, FloatRef sizeY)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.GetTextSize(textdraw, sizeX, sizeY);
	API_RETURN(bool ret, FloatRef sizeX, FloatRef sizeY);
}

DECLARE_API_ARGNUM(TextDraw, GetPos, 1, objectPtr textdraw, FloatRef x, FloatRef y)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.GetPos(textdraw, x, y);
	API_RETURN(bool ret, FloatRef x, FloatRef y);
}

DECLARE_API(TextDraw, GetColor, objectPtr textdraw)
{
	int ret = Runtime::Instance().GetOMPAPI()->TextDraw.GetColor(textdraw);
	API_RETURN(int ret);
}

DECLARE_API(TextDraw, GetBoxColor, objectPtr textdraw)
{
	int ret = Runtime::Instance().GetOMPAPI()->TextDraw.GetBoxColor(textdraw);
	API_RETURN(int ret);
}

DECLARE_API(TextDraw, GetBackgroundColor, objectPtr textdraw)
{
	int ret = Runtime::Instance().GetOMPAPI()->TextDraw.GetBackgroundColor(textdraw);
	API_RETURN(int ret);
}

DECLARE_API(TextDraw, GetShadow, objectPtr textdraw)
{
	int ret = Runtime::Instance().GetOMPAPI()->TextDraw.GetShadow(textdraw);
	API_RETURN(int ret);
}

DECLARE_API(TextDraw, GetOutline, objectPtr textdraw)
{
	int ret = Runtime::Instance().GetOMPAPI()->TextDraw.GetOutline(textdraw);
	API_RETURN(int ret);
}

DECLARE_API(TextDraw, GetFont, objectPtr textdraw)
{
	int ret = Runtime::Instance().GetOMPAPI()->TextDraw.GetFont(textdraw);
	API_RETURN(int ret);
}

DECLARE_API(TextDraw, IsBox, objectPtr textdraw)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.IsBox(textdraw);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, IsProportional, objectPtr textdraw)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.IsProportional(textdraw);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, IsSelectable, objectPtr textdraw)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.IsSelectable(textdraw);
	API_RETURN(bool ret);
}

DECLARE_API(TextDraw, GetAlignment, objectPtr textdraw)
{
	int ret = Runtime::Instance().GetOMPAPI()->TextDraw.GetAlignment(textdraw);
	API_RETURN(int ret);
}

DECLARE_API(TextDraw, GetPreviewModel, objectPtr textdraw)
{
	int ret = Runtime::Instance().GetOMPAPI()->TextDraw.GetPreviewModel(textdraw);
	API_RETURN(int ret);
}

DECLARE_API_ARGNUM(TextDraw, GetPreviewRot, 1, objectPtr textdraw, FloatRef x, FloatRef y, FloatRef z, FloatRef zoom)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.GetPreviewRot(textdraw, x, y, z, zoom);
	API_RETURN(bool ret, FloatRef x, FloatRef y, FloatRef z, FloatRef zoom);
}

DECLARE_API_ARGNUM(TextDraw, GetPreviewVehColor, 1, objectPtr textdraw, IntRef color1, IntRef color2)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.GetPreviewVehColor(textdraw, color1, color2);
	API_RETURN(bool ret, IntRef color1, IntRef color2);
}

DECLARE_API(TextDraw, SetStringForPlayer, objectPtr textdraw, objectPtr player, StringCharPtr text)
{
	bool ret = Runtime::Instance().GetOMPAPI()->TextDraw.SetStringForPlayer(textdraw, player, text);
	API_RETURN(bool ret);
}
