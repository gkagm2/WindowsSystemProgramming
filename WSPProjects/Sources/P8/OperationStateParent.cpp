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
	
	// Child Process�� �켱���� ����
	for (DWORD i = 0; i < 10000; ++i)
		for (DWORD j = 0; j < 10000; ++j);

	// ù ��° ���ڷ� ���޵� �ڵ��� ����Ű�� ���μ����� ��ȯ�ϴ� �����ڵ带 ��� ���� ���Ǵ� �Լ�.
	// ���޵� �ڵ鿡 �ش��ϴ� ���μ����� ������� �ʰ� ���� ���̶�� STILL_ACTIVE�� ����ؼ� ��ȯ
	GetExitCodeProcess(pi.hProcess, &state);
	if (state == STILL_ACTIVE)
		_tprintf(_T("STILL_ACTIVE \n\n"));
	else
		_tprintf(_T("state : %d\n\n", state));

	// CloseHandle(pi.hProcess);

	return 0;
}