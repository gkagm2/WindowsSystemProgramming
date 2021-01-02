#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR *argv[]) {
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);

	while (true) {
		for (DWORD i = 0; i < 10000; ++i)
			for (DWORD j = 0; j < 10000; ++j); // busy waiting (책에선 i로)

		_fputts(_T("Operation2.exe\n"), stdout);
	}
	return 0;
}