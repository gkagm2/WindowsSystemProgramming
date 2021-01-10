// 전달된 인자 사이의 수 덧셈
#include <iostream>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[]) {
	if (argc != 3)
		return -1;

	DWORD start = _ttoi(argv[1]);
	DWORD end = _ttoi(argv[2]);
	DWORD total = 0;

	start = 3;
	end = 6;

	DWORD num;
	if (start < end)
		num = end - start + 1;
	else
		num = start - end + 1;

	total = num * (start + end) / 2;
	return total;
}