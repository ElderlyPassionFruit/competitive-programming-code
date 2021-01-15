//Если на максимум - наоборот
const ll INF = 1e18;

struct line{
	ll k, b;
	line() {
		k = 0, b = INF;
	}
	line(ll x, ll y) {
		k = x, b = y;
	}
};

ld cross(line l, line m) {
	return (ld)(l.b - m.b) / (m.k - l.k);
}

ll eval(line l, ll x) {
	return l.k * x + l.b;
}

struct cht{
	vector<line> l;
	vector<ld> p;
	cht() {}

	void add(line x) {
		while (!p.empty() && p.back() >= cross(l.back(), x))
			p.pop_back(), l.pop_back();
		l.push_back(x);
		if (l.size() >= 2) {
			p.push_back(cross(l[l.size() - 1], l[l.size() - 2]));
		}
	}

	ll get(ll x) {
		int pos = lower_bound(all(p), x) - p.begin();
		return eval(l[pos], x);
	}
};
