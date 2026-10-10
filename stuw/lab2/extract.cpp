#include "interaction.h"

void ExtractText(HWND hWindow1, wchar_t *out)
{
	if (!GetWindowText(hWindow1, out, MAX_PATH))
	{
		MessageBoxA(hWindow1, "Failed to extract path to the file", "Extraction Error", MB_OK);
	}//else MessageBoxA(hWindow, "Extracted path to the file", "Extraction Success", MB_OK);

}

ACCESS_MASK CheckCheckbox(HWND hCheckbox)
{
	//CheckDlgButton(hCheckbox, WRITE, BST_CHECKED);
	if (IsDlgButtonChecked(hCheckbox, WRITE))
	{
		MessageBoxW(hCheckbox, L"Write is Checked", L"asd", MB_OK);
		//return STANDARD_RIGHTS_WRITE;
	}
	if (CheckDlgButton(hCheckbox, READ, BST_CHECKED))
	{
		MessageBoxW(hCheckbox, L"REad is Checked", L"asd", MB_OK);
		return STANDARD_RIGHTS_READ;
	}
	if (CheckDlgButton(hCheckbox, CREATE, BST_CHECKED))
	{
		MessageBoxW(hCheckbox, L"Checked", L"asd", MB_OK);
		return STANDARD_RIGHTS_EXECUTE;
	}
	else
	{
		MessageBoxW(hCheckbox, L"Unhecked or INDETERMINATE", L"asd", MB_OK);
	}
}
