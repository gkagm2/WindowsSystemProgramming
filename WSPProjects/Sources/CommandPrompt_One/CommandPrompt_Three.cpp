#pragma warning(disable:4996)
#include <stdio.h>
#include <tchar.h>
#include <locale.h>
#include <Windows.h>

#define STR_LEN 256
#define CMD_TOKEN_NUM 10

TCHAR ERROR_CMD[] = _T("'%s'��(��) ������ �� �ִ� ���α׷��� �ƴմϴ�.\n");
TCHAR cmdString[STR_LEN];
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
TCHAR seps[] = _T(" ,\t\n");

int CmdReadTokenize(void);
int CmdProcessing(int);
TCHAR *StrLower(TCHAR*);

int _tmain(int argc, TCHAR* argv[]) {
	// �ѱ� �Է��� ������ �ϱ� ����
	_tsetlocale(LC_ALL, _T("Korean"));

	// �Ű����� �������ڰ� �ִ� ��� ó���� ���� ���̴�.
	// Start ��ɾ ���� ó���� �����ϸ� ���ڴ�.
	if (argc > 2) {
		for (int i = 1; i < argc; ++i)
			_tcscpy(cmdTokenList[i - 1], argv[i]);
		CmdProcessing(argc - 1);
	}

	DWORD isExit = NULL;
	while (1) {
		int tokenNum = CmdReadTokenize();

		if (tokenNum == 0) // Enter �Է� ó���� ���� �κ�
			continue;

		isExit = CmdProcessing(tokenNum);
		if (isExit == TRUE) {
			_fputts(_T("��ɾ� ó���� �����մϴ�. \n"), stdout);
			break;
		}
	}

	return 0;
}

int CmdReadTokenize(void) {
	TCHAR* token;
	_fputts(_T("Best command prompt>> "), stdout);
	_fgetts(cmdString, sizeof(cmdString), stdin);
	
	token = _tcstok(cmdString, seps);

	int tokenNum = 0;
	while (token != NULL) {
		_tcscpy(cmdTokenList[tokenNum++], StrLower(token));
		token = _tcstok(NULL, seps);
	}

	return tokenNum;
}

int CmdProcessing(int tokenNum) {
	BOOL isRun;
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;

	TCHAR cmdStringWithOptions[STR_LEN] = { 0, };
	TCHAR optString[STR_LEN] = { 0, };

	si.cb = sizeof(si);
	if (!_tcscmp(cmdTokenList[0], _T("exit"))) {
		return TRUE;
	}
	else if (!_tcscmp(cmdTokenList[0], _T("start"))) {
		// "start echo test good" �̶�� ���ڿ��� �ԷµǾ��ٰ� ����.
		// �� ���α׷��� �������� �̸��� CmdProject.exe��� ����
		if (tokenNum > 1) {
			for (int i = 1; i < tokenNum; ++i) {
				_stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);
			}
			_stprintf(cmdStringWithOptions, _T("%s %s"), _T("CmdProject.exe"), optString);
		}
		else
			_stprintf(cmdStringWithOptions, _T("%s"), _T("CmdProject.exe"));

		isRun = CreateProcess(
			NULL, cmdStringWithOptions, NULL, NULL,
			TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else if (!_tcscmp(cmdTokenList[0], _T("echo"))) {
		// �Էµ� ���ڿ��� �״�� ����ϴ� echo ��ɾ�
		for (int i = 1; i < tokenNum; ++i) {
			_stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);
		}
		_tprintf(_T("echo message:%s \n"), optString);
	}
	else if (!_tcscmp(cmdTokenList[0], _T("help"))) {
		_tprintf(_T("--Command--\n"));
		_tprintf(_T("exit : exit process\n"));
		_tprintf(_T("echo : example -> echo Hello\n"));
		_tprintf(_T("start : example -> start echo Hello\n"));
	}
	else {
		_tcscpy(cmdStringWithOptions, cmdTokenList[0]);

		// ���ڿ� ó���� ���� for��
		for (int i = 1; i < tokenNum; ++i) {
			_stprintf(cmdStringWithOptions, _T("%s %s"), cmdStringWithOptions, cmdTokenList[i]);
		}

		isRun = CreateProcess(
			NULL, cmdStringWithOptions, NULL, NULL,
			TRUE, 0, NULL, NULL, &si, &pi);

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		if (isRun == FALSE) {
			_tprintf(ERROR_CMD, cmdTokenList[0]);
		}
	}
	return 0;
}

TCHAR *StrLower(TCHAR* pStr) {
	TCHAR *ret = pStr;

	while (*pStr) {
		if (_istupper) // �빮���ΰ�?
			*pStr = _totlower(*pStr);

		++pStr;
	}
	return ret;
}