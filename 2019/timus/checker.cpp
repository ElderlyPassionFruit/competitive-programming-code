#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

const long long maxx = 1000000;

int main(int argc, char* argv[]) {
	registerTestlibCmd(argc, argv);
	// inf - ����
	// ouf - ������� ���������
	// ans - ������� ����
	int a1 = ouf.readLong(0, maxx, "too big number");
	int a2 = ans.readLong(0, maxx, "too big number");
	if (a1 != a2) {
		quitf(_wa, "not correct");
	}
	quitf(_ok, "Correct");
}