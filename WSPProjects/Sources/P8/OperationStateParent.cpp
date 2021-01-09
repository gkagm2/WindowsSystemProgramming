#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[]) {
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	DWORD state;

	si.cb = sizeof(si);
	si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
	si.dwX = 100;
	si.dwY = 200;
	si.dwXSize = 300;
	si.dwYSize = 200;
	// si.lpTitle = _T("return & exit");

	TCHAR command[] = _T("OperationStateChild.exe");
	CreateProcess(NULL, command, NULL, NULL, TRUE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	
	// Child Process의 우선종료 위해
	for (DWORD i = 0; i < 10000; ++i)
		for (DWORD j = 0; j < 10000; ++j);

	// 첫 번째 인자로 전달된 핸들이 가리키는 프로세스가 반환하는 종료코드를 얻기 위해 사용되는 함수.
	// 전달된 핸들에 해당하는 프로세스가 종료되지 않고 실행 중이라면 STILL_ACTIVE를 대신해서 반환
	GetExitCodeProcess(pi.hProcess, &state);
	if (state == STILL_ACTIVE)
		_tprintf(_T("STILL_ACTIVE \n\n"));
	else
		_tprintf(_T("state : %d\n\n", state));

	// CloseHandle(pi.hProcess);

	return 0;
}