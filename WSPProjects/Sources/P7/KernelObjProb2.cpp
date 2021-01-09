// 100회에 걸쳐서 문자열을 출력하는 프로그램
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR *argv[]) {
	DWORD n = 0;
	while (n < 100) {
		// Busy waiting
		for (DWORD i = 0; i < 10000; ++i)
			for (DWORD j = 0; j < 10000; ++j);


		_fputts(_T("KernelObjProb2.exe\n"), stdout);
		++n;
	}
	return 0;
}