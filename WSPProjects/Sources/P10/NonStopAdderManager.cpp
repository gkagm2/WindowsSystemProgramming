// 1~10까지 덧셈하여 출력
// 문제점을 지니고 있는 코드임
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[]) {
	STARTUPINFO si1 = { 0, };
	STARTUPINFO si2 = { 0, };

	PROCESS_INFORMATION pi1;
	PROCESS_INFORMATION pi2;

	DWORD return_val1;
	DWORD  return_val2;

	TCHAR command1[] = _T("PartAdder.exe 1 5");
	TCHAR command2[] = _T("PartAdder.exe 6 10");

	DWORD sum = 0;

	si1.cb = sizeof(si1);
	si2.cb = sizeof(si2);

	CreateProcess(NULL, command1,
		NULL, NULL, TRUE,
		0, NULL, NULL,
		&si1, &pi1);

	CreateProcess(NULL, command2,
		NULL, NULL, TRUE,
		0, NULL, NULL,
		&si2, &pi2);

	CloseHandle(pi1.hThread);
	CloseHandle(pi2.hThread);

	// 자식 프로세스가 signaled(종료)상태가 될때까지 기다림
	WaitForSingleObject(pi1.hProcess, INFINITE); 
	WaitForSingleObject(pi2.hProcess, INFINITE);

	GetExitCodeProcess(pi1.hProcess, &return_val1);
	GetExitCodeProcess(pi2.hProcess, &return_val2);

	if (return_val1 == -1 || return_val2 == -1)
		return -1; // 비정상적 종료

	sum += return_val1;
	sum += return_val2;

	_tprintf(_T("total : %d \n"), sum);

	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);

	return 0;
}