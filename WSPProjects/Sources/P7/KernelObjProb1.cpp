// CloseHandle 함수

#pragma warning(disable:4996)
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, TCHAR* argv[]) {
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	TCHAR command[] = _T("KernelObjProb2.exe");
	CreateProcess(
		NULL, command, NULL, NULL, TRUE,
		0, NULL, NULL, &si, &pi);

	// 핸들을 닫는다. 프로세스 핸들뿐만 아니라 다른 종류의 핸들을 반환할 때에도 사용되는 함수.
	CloseHandle(pi.hProcess);
	

	return 0;
}