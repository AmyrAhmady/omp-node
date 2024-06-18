#include "../Impl.hpp"
#include "../MacroMagic.hpp"

DECLARE_API(Dialog, Show, objectPtr player, int dialog, int style, StringCharPtr title, StringCharPtr body, StringCharPtr button1, StringCharPtr button2)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Dialog.Show(player, dialog, style, title, body, button1, button2);
	API_RETURN(bool ret);
}

DECLARE_API(Dialog, Hide, objectPtr player)
{
	bool ret = Runtime::Instance().GetOMPAPI()->Dialog.Hide(player);
	API_RETURN(bool ret);
}
