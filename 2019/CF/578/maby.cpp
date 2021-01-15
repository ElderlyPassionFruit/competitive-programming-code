#include <bits/stdc++.h>

using namespace std;

template<typename T, typename U, bool debug_message=false>
pair<string, string> BirthdatAttack(const function<T()> gen_str_func, const function<U(T)> hash_func) {
	map<U, T> hash_to_str;
	while (true) {
		string str = gen_str_func();
		long long hash = hash_func(str);
		auto iter = hash_to_str.insert({hash, str}).first;
		if (iter->second != str)
			return {iter->second, str};
		if (debug_message && hash_to_str.size() % 10000 == 0)
			fprintf(stderr, "map.size()=%d\n", (int)hash_to_str.size());
	}
}

constexpr long long MOD = 1000000007;
constexpr int length = 10;

int main() {
	vector<string> v;
	const function<string()> gen_str_func = []() {
		string str;
		for (int i = 0; i < length; i++) {
			int tmp = rand() % 62;
			if (tmp < 10)
				str.push_back('0' + tmp);
			else if (tmp < 36)
				str.push_back('A' + (tmp - 10));
			else
				str.push_back('a' + (tmp - 36));
		}
		return str;
	};
	vector<long long> to(256);
    long long cnt = 1;
	for (char i = 'a'; i <= 'z'; i++, cnt++)
		to[i] = cnt;
    for (char i = 'A'; i <= 'Z'; i++, cnt++)
		to[i] = cnt;
    for (char i = '0'; i <= '9'; i++, cnt++)
		to[i] = cnt;
	unsigned now = time(NULL) / 100 * 100;
	for (int i = 0; i < 200; i++) {
		srand(now + i);
		long long base = 0;
		while (base < 70)
			base = rand() % (int)1e5;
		fprintf(stderr, "base=%lld\n", base);
		const function<long long(string)> hash_func = [to, base](string str) {
			long long hash = 0;
			for (char j : str)
				hash = (hash * base + to[j]) % MOD;
			return hash;
		};
		pair<string, string> re = BirthdatAttack<string, long long>(gen_str_func, hash_func);
		fprintf(stderr, "%s %s\n", re.first.c_str(), re.second.c_str());
		v.push_back(re.first);
		v.push_back(re.second);
	}
	printf("%d\n", (int)v.size());
	for (int i = 0; i < v.size(); i++)
		printf("%s%c", v[i].c_str(), " \n"[i == v.size() - 1]);
}