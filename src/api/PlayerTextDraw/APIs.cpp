#include "../Impl.hpp"
#include "../MacroMagic.hpp"

DECLARE_API_ARGNUM(PlayerTextDraw, Create, 4, objectPtr player, float x, float y, StringCharPtr text, IntRef id)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.Create(player, x, y, text, id);
	API_RETURN(objectPtr ret, IntRef id);
}

DECLARE_API(PlayerTextDraw, Destroy, objectPtr player, objectPtr textdraw)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.Destroy(player, textdraw);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, FromID, objectPtr player, int textdrawid)
{
	objectPtr ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.FromID(player, textdrawid);
	API_RETURN(objectPtr ret);
}

DECLARE_API(PlayerTextDraw, GetID, objectPtr player, objectPtr textdraw)
{
	int ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.GetID(player, textdraw);
	API_RETURN(int ret);
}

DECLARE_API(PlayerTextDraw, IsValid, objectPtr player, objectPtr textdraw)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.IsValid(player, textdraw);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, IsVisible, objectPtr player, objectPtr textdraw)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.IsVisible(player, textdraw);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, SetLetterSize, objectPtr player, objectPtr textdraw, float x, float y)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.SetLetterSize(player, textdraw, x, y);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, SetTextSize, objectPtr player, objectPtr textdraw, float x, float y)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.SetTextSize(player, textdraw, x, y);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, SetAlignment, objectPtr player, objectPtr textdraw, int alignment)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.SetAlignment(player, textdraw, alignment);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, SetColor, objectPtr player, objectPtr textdraw, uint32_t color)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.SetColor(player, textdraw, color);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, UseBox, objectPtr player, objectPtr textdraw, bool use)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.UseBox(player, textdraw, use);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, SetBoxColor, objectPtr player, objectPtr textdraw, uint32_t color)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.SetBoxColor(player, textdraw, color);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, SetShadow, objectPtr player, objectPtr textdraw, int size)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.SetShadow(player, textdraw, size);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, SetOutline, objectPtr player, objectPtr textdraw, int size)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.SetOutline(player, textdraw, size);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, SetBackgroundColor, objectPtr player, objectPtr textdraw, uint32_t color)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.SetBackgroundColor(player, textdraw, color);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, SetFont, objectPtr player, objectPtr textdraw, int font)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.SetFont(player, textdraw, font);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, SetProportional, objectPtr player, objectPtr textdraw, bool set)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.SetProportional(player, textdraw, set);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, SetSelectable, objectPtr player, objectPtr textdraw, bool set)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.SetSelectable(player, textdraw, set);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, Show, objectPtr player, objectPtr textdraw)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.Show(player, textdraw);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, Hide, objectPtr player, objectPtr textdraw)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.Hide(player, textdraw);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, SetString, objectPtr player, objectPtr textdraw, StringCharPtr text)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.SetString(player, textdraw, text);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, SetPreviewModel, objectPtr player, objectPtr textdraw, int model)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.SetPreviewModel(player, textdraw, model);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, SetPreviewRot, objectPtr player, objectPtr textdraw, float rx, float ry, float rz, float zoom)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.SetPreviewRot(player, textdraw, rx, ry, rz, zoom);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, SetPreviewVehCol, objectPtr player, objectPtr textdraw, int color1, int color2)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.SetPreviewVehCol(player, textdraw, color1, color2);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, SetPos, objectPtr player, objectPtr textdraw, float x, float y)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.SetPos(player, textdraw, x, y);
	API_RETURN(bool ret);
}

DECLARE_API_ARGNUM(PlayerTextDraw, GetString, 2, objectPtr player, objectPtr textdraw, OutputStringViewPtr text)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.GetString(player, textdraw, text);
	API_RETURN(bool ret, OutputStringViewPtr text);
}

DECLARE_API_ARGNUM(PlayerTextDraw, GetLetterSize, 2, objectPtr player, objectPtr textdraw, FloatRef x, FloatRef y)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.GetLetterSize(player, textdraw, x, y);
	API_RETURN(bool ret, FloatRef x, FloatRef y);
}

DECLARE_API_ARGNUM(PlayerTextDraw, GetTextSize, 2, objectPtr player, objectPtr textdraw, FloatRef x, FloatRef y)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.GetTextSize(player, textdraw, x, y);
	API_RETURN(bool ret, FloatRef x, FloatRef y);
}

DECLARE_API_ARGNUM(PlayerTextDraw, GetPos, 2, objectPtr player, objectPtr textdraw, FloatRef x, FloatRef y)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.GetPos(player, textdraw, x, y);
	API_RETURN(bool ret, FloatRef x, FloatRef y);
}

DECLARE_API(PlayerTextDraw, GetColor, objectPtr player, objectPtr textdraw)
{
	int ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.GetColor(player, textdraw);
	API_RETURN(int ret);
}

DECLARE_API(PlayerTextDraw, GetBoxColor, objectPtr player, objectPtr textdraw)
{
	int ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.GetBoxColor(player, textdraw);
	API_RETURN(int ret);
}

DECLARE_API(PlayerTextDraw, GetBackgroundColor, objectPtr player, objectPtr textdraw)
{
	int ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.GetBackgroundColor(player, textdraw);
	API_RETURN(int ret);
}

DECLARE_API(PlayerTextDraw, GetShadow, objectPtr player, objectPtr textdraw)
{
	int ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.GetShadow(player, textdraw);
	API_RETURN(int ret);
}

DECLARE_API(PlayerTextDraw, GetOutline, objectPtr player, objectPtr textdraw)
{
	int ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.GetOutline(player, textdraw);
	API_RETURN(int ret);
}

DECLARE_API(PlayerTextDraw, GetFont, objectPtr player, objectPtr textdraw)
{
	int ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.GetFont(player, textdraw);
	API_RETURN(int ret);
}

DECLARE_API(PlayerTextDraw, IsBox, objectPtr player, objectPtr textdraw)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.IsBox(player, textdraw);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, IsProportional, objectPtr player, objectPtr textdraw)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.IsProportional(player, textdraw);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, IsSelectable, objectPtr player, objectPtr textdraw)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.IsSelectable(player, textdraw);
	API_RETURN(bool ret);
}

DECLARE_API(PlayerTextDraw, GetAlignment, objectPtr player, objectPtr textdraw)
{
	int ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.GetAlignment(player, textdraw);
	API_RETURN(int ret);
}

DECLARE_API(PlayerTextDraw, GetPreviewModel, objectPtr player, objectPtr textdraw)
{
	int ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.GetPreviewModel(player, textdraw);
	API_RETURN(int ret);
}

DECLARE_API_ARGNUM(PlayerTextDraw, GetPreviewRot, 2, objectPtr player, objectPtr textdraw, FloatRef rx, FloatRef ry, FloatRef rz, FloatRef zoom)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.GetPreviewRot(player, textdraw, rx, ry, rz, zoom);
	API_RETURN(bool ret, FloatRef rx, FloatRef ry, FloatRef rz, FloatRef zoom);
}

DECLARE_API_ARGNUM(PlayerTextDraw, GetPreviewVehColor, 2, objectPtr player, objectPtr textdraw, IntRef color1, IntRef color2)
{
	bool ret = Runtime::Instance().GetOMPAPI()->PlayerTextDraw.GetPreviewVehColor(player, textdraw, color1, color2);
	API_RETURN(bool ret, IntRef color1, IntRef color2);
}
