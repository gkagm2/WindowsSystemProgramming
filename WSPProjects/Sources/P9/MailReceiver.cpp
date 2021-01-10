// 메일슬롯 Receiver
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define SLOT_NAME _T(".\\mailslot\\mailbox")

int _tmain(int argc, TCHAR* argv[]) {
	HANDLE hMailSlot; // mailslot handle
	TCHAR messageBox[50];
	DWORD bytesRead; // number of bytes read

	// create mailslot
	hMailSlot = CreateMailslot(
		SLOT_NAME,
		0,
		MAILSLOT_WAIT_FOREVER,
		NULL
	);

	if (hMailSlot == INVALID_HANDLE_VALUE) {
		_fputts(_T("Unable to create mailslot!\n"), stdout);
		return 1;
	}

	// receive message
	_fputts(_T("***** Message ****\n"), stdout);
	while (1) {
		if (!ReadFile(hMailSlot, messageBox, sizeof(TCHAR) * 50, &bytesRead, NULL)) {
			_fputts(_T("Unable to read!"), stdout);
			CloseHandle(hMailSlot);
			return 1;
		}

		// _tcsncmp : 두 문자열의 문자를 지정한 수까지 비교.
		if (!_tcsncmp(messageBox, _T("exit"), 4)) {
			_fputts(_T("Unable to read!"), stdout);
			CloseHandle(hMailSlot);
			return 1;
		}
		
		messageBox[bytesRead / sizeof(TCHAR)] = 0; // NULL 문자 삽입
		_fputts(messageBox, stdout);
	}

	CloseHandle(hMailSlot);
	return 0;
}