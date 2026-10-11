#include "interaction.h"

int ExtractText(HWND hWindow1, wchar_t *out)
{
	if (!GetWindowText(hWindow1, out, MAX_PATH)) return 1;
	return 0;
}

ACCESS_MASK CheckFileMask(HWND hCheckbox)
{
	ACCESS_MASK result = 0;
	//CheckDlgButton(hCheckbox, WRITE, BST_CHECKED);
	if (IsDlgButtonChecked(hCheckbox, WRITE))
	{
		//MessageBoxW(hCheckbox, L"Write is Checked", L"asd", MB_OK);
		result |= FILE_WRITE_DATA;
	}
	if (IsDlgButtonChecked(hCheckbox, READ))
	{
		//MessageBoxW(hCheckbox, L"Read is Checked", L"asd", MB_OK);
		result |= FILE_READ_ATTRIBUTES;
	}
	if (IsDlgButtonChecked(hCheckbox, CREATE))
	{
		//MessageBoxW(hCheckbox, L"Checked", L"asd", MB_OK);
		result |= FILE_WRITE_ATTRIBUTES;
	}
	if(result == 0)
	{
		MessageBoxW(hCheckbox, L"No rights were checked", L"", MB_OK | MB_ICONEXCLAMATION);
	}
	return result;
}

ACCESS_MASK CheckDirMask(HWND hCheckbox)
{
	ACCESS_MASK result = 0;
	//CheckDlgButton(hCheckbox, WRITE, BST_CHECKED);
	if (IsDlgButtonChecked(hCheckbox, DIR_WRITE_ATTR) == BST_CHECKED)
	{
		//MessageBoxW(hCheckbox, L"Write is Checked", L"asd", MB_OK);
		result |= FILE_WRITE_ATTRIBUTES;
	}
	if (IsDlgButtonChecked(hCheckbox, DIR_CREATE) == BST_CHECKED)
	{
		//MessageBoxW(hCheckbox, L"Read is Checked", L"asd", MB_OK);
		result |= (FILE_APPEND_DATA | FILE_ADD_SUBDIRECTORY | FILE_ADD_FILE);
	}
	if (IsDlgButtonChecked(hCheckbox, DIR_READ_OWNER) == BST_CHECKED ||
		IsDlgButtonChecked(hCheckbox, DIR_READ_PERM) == BST_CHECKED)
	{
		//MessageBoxW(hCheckbox, L"Checked", L"asd", MB_OK);
		result |= (FILE_LIST_DIRECTORY | READ_CONTROL | FILE_READ_ATTRIBUTES);
	}
	if (result == 0)
	{
		MessageBoxW(hCheckbox, L"No rights were checked", L"", MB_OK | MB_ICONEXCLAMATION);
	}
	return result;
}
