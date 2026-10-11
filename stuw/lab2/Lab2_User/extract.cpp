#include "interaction.h"

int ExtractText(HWND hWindow1, wchar_t *out)
{
	if (!GetWindowText(hWindow1, out, MAX_PATH)) return 1;
	return 0;
}


DWORD ParseAttribute(wchar_t *attr)
{
	DWORD dwAttr = 0;

	if (_wcsicmp(attr, L"normal") == 0)
	{
		return FILE_ATTRIBUTE_NORMAL;
	}
	if (_wcsicmp(attr, L"hidden") == 0)
	{
		dwAttr |= FILE_ATTRIBUTE_HIDDEN;
	}
	if (_wcsicmp(attr, L"readonly") == 0)
	{
		dwAttr |= FILE_ATTRIBUTE_READONLY;
	}
	return dwAttr;
}