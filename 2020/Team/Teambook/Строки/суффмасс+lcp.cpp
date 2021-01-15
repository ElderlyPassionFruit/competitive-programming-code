const int INF = 1e9;

vector<int> build_suff(vector<int> & s) {
	s.push_back(-INF);
	int n = s.size();
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		a[i] = i;
	stable_sort(a.begin(), a.end(), [&] (int i, int j) {return s[i] < s[j];});

	vector<int> c(n);
	int cc = 0;
	for (int i = 0; i < n; i++) {
		if (i == 0 || s[a[i]] != s[a[i - 1]])
			c[a[i]] = cc++;
		else
			c[a[i]] = c[a[i - 1]];
	}

	for (int l = 1; l < n; l *= 2) {
		vector<int> cnt(n);
		for (auto i : c)
			cnt[i]++;
		vector<int> pref(n);
		for (int i = 1; i < n; i++)
			pref[i] = pref[i - 1] + cnt[i - 1];
		vector<int> na(n);
		for (int i = 0; i < n; i++) {
			int pos = (a[i] - l + n) % n;
			na[pref[c[pos]]++] = pos;
		}
		a = na;
		cc = 0;
		vector<int> nc(n);
		for (int i = 0; i < n; i++) {
			if (i == 0 || c[a[i]] != c[a[i - 1]] || c[(a[i] + l) % n] != c[(a[i - 1] + l) % n])
				nc[a[i]] = cc++;
			else
				nc[a[i]] = nc[a[i - 1]];
		}
		c = nc;
	}
	return a;
}

vector<int> build_lcp(vector<int> & s, vector<int> & a) {
	int n = a.size();
	vector<int> ra(n);
	for (int i = 0; i < n; i++)
		ra[a[i]] = i;
	vector<int> lcp(n - 1);
	int cur = 0;
	for (int i = 0; i < n; i++) {
		cur = max(cur - 1, 0);
		if (ra[i] == n - 1) {
			cur = 0;
			continue;
		}
		int j = a[ra[i] + 1];
		while (s[(i + cur) % n] == s[(j + cur) % n]) {
			cur++;
			if (cur == n)
				break;
		}
		lcp[ra[i]] = cur;
	}
	lcp.erase(lcp.begin());
	a.erase(a.begin());
	s.pop_back();
	return lcp;
}