// notepad ¿­±â
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, TCHAR * argv[]) {
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	TCHAR command[] = _T("notepad.exe");
	SetCurrentDirectory(_T(".\\"));

	CreateProcess(
		NULL, command, NULL, NULL,
		TRUE, NULL, NULL, NULL,
		&si, &pi
	);

	return 0;
}