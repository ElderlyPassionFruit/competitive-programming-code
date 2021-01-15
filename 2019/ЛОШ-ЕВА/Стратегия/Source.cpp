#include<map>
#include<utility>
#include<vector>
#include<iostream>
#include<assert.h>
#include<algorithm>
using namespace std;

enum MoveEnum
{
	MOVE_1_N,
	MOVE_2_N,
	MOVE_1_E,
	MOVE_2_E,
	MOVE_1_W,
	MOVE_2_W,
	MOVE_1_S,
	MOVE_2_S,
	TURN_N,
	TURN_E,
	TURN_W,
	TURN_S,
	ATTACK,
	ATTACK_MOVE,
	SHOT,
	EAT,
	IDLE
};

template<typename T>
istream& operator >> (istream& in, vector<T>& v)
{
	for (auto& i : v) in >> i;
	return in;
}

struct pt
{
	int x = 0, y = 0;
};

pt vec_1_e = { 1, 0 }, vec_2_e = { 2, 0 };
pt vec_1_n = { 0, 1 }, vec_2_n = { 0, 2 };
pt vec_1_w = { -1, 0 }, vec_2_w = { -2, 0 };
pt vec_1_s = { 0, -1 }, vec_2_s = { 0, -2 };


pt operator - (pt& a, pt& b)
{
	return { a.x - b.x, a.y - b.y };
}

pt operator + (pt& a, pt& b)
{
	return { a.x + b.x, a.y + b.y };
}

int pt_sq_dst(pt& a, pt& b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

istream& operator >> (istream& in, pt& p)
{
	in >> p.x >> p.y;
	return in;
}

ostream& operator << (ostream& out, pt p)
{
	out << p.x << ' ' << p.y;
	return out;
}

struct Player
{
	int id, h, s, f, b, last_shot, move_cnt;
	pt pos;
	char d;

	bool can_shot()
	{
		return b > 0 && move_cnt - last_shot >= 10 && s >= 5;
	}
};

istream& operator >> (istream& in, Player& p)
{
	in >> p.id >> p.h >> p.s >> p.f >> p.b >> p.pos >> p.d;
	return in;
}

struct Enemy
{
	pt pos = { 0, 0 };
	int id = -1, h_s = 0, r = 0, move_num = -1;
	char d = '*';
	bool agressive = false;
};


istream& operator >> (istream& in, Enemy& e)
{
	in >> e.pos >> e.d >> e.id >> e.h_s >> e.r;
	return in;
}

map<int, Enemy> enemy_info;

pt initial_pos;
const int N = 3e3 + 5, INF = 1e9 + 7;
char field[N][N];
int f_id = -1;

void field_reset()
{
	for (int i = 0; i < N; i++) fill(field[i], field[i] + N, '.');
}

void set_cell_state(pt pos, char c)
{
	pt n_pos = pos - initial_pos;
	field[n_pos.x][n_pos.y] = c;
}

char get_cell_state(pt pos)
{
	pt n_pos = pos - initial_pos;
	return field[n_pos.x][n_pos.y];
}

char get_pos(pt x) {
	pt n_pos = x - initial_pos;
	return field[n_pos.x][n_pos.y];
}

bool check_turn(char a, char b) {
	return a != b;
}

int next_turn(char a) {
	if (a == 'N')
		return TURN_N;
	if (a == 'E')
		return TURN_E;
	if (a == 'S')
		return TURN_S;
	if (a == 'W')
		return TURN_W;
	return IDLE;
}

int double_move(Player a) {
	if (a.d == 'N')
		return MOVE_2_N;
	if (a.d == 'S')
		return MOVE_2_S;
	if (a.d == 'E')
		return MOVE_2_E;
	if (a.d == 'W')
		return MOVE_2_W;
	return IDLE;
}

int move(Player a) 
{
	if (a.d == 'N')
		return MOVE_1_N;
	if (a.d == 'S')
		return MOVE_1_S;
	if (a.d == 'E')
		return MOVE_1_E;
	if (a.d == 'W')
		return MOVE_1_W;
	return IDLE;
}

int move(Player a, pt b) {
	if (a.pos.y != b.y) {
		char need = ' ';
		if (a.pos.y > b.y)
			need = 'S';
		else
			need = 'N';
		if (check_turn(a.d, need))
			return next_turn(need);
		//else if (abs(a.pos.y - b.y) >= 10)
		//	return double_move(a);
		else
			return move(a);
	}
	else if (a.pos.x != b.x) {
		char need = ' ';
		if (a.pos.x > b.x)
			need = 'W';
		else
			need = 'E';
		if (check_turn(a.d, need))
			return next_turn(need);
		//else if (abs(a.pos.x - b.x) >= 10)
		//	return double_move(a);
		else
			return move(a);
	}
	return IDLE;
}

int get_time(Player a, pt b) {
	int ans = 0;
	ans += (abs(a.pos.x - b.x) + 1) / 2;
	ans += (abs(a.pos.y - b.y) + 1) / 2;
	return ans;
}

bool check(Player a, Enemy b) {
	if (abs(b.pos.x - a.pos.x) <= 2 && abs(a.pos.y - b.pos.y) == 3)
		return true;
	return false;
}

bool check_ray_attack(Player a, Enemy b) {
	return pt_sq_dst(a.pos, b.pos) <= 100 && a.can_shot();
}

Player help_move(Player a) {
	if (a.d == 'N')
		a.pos.y++;
	if (a.d == 'E')
		a.pos.x++;
	if (a.d == 'S')
		a.pos.y--;
	if (a.d == 'W')
		a.pos.x--;
	return a;
}

bool check_attack_move(Player a, Enemy b) {
	a = help_move(a);
	return check(a, b);
}

int get_fight(Player a, Enemy b) {
	if (check_ray_attack(a, b)) return SHOT;
	if (check(a, b)) return ATTACK;
	if (check_attack_move(a, b)) return ATTACK_MOVE;
	return move(a, b.pos);
}

//t, move
pair<int, int> get_optimum_food(vector<pt> food, Player& player) {
	pair <int, int> ans = { INF, INF };
	for (auto i : food) {
		ans = min(ans, { get_time(player, i), move(player, i) });
	}
	return ans;
}

pair <pair<int, int>, int> get_optimum_enemy(vector<Enemy> enemy, Player& player) {
	pair<pair <int, int>, int> ans = { {INF, INF}, INF };
	for (auto i : enemy) {
		ans = min(ans, make_pair(make_pair(get_time(player, i.pos), get_fight(player, i)), i.id));
	}
	return ans;
}

pair<int, int> get_optimum_ammo(vector<pt> ammo, Player& player) {
	pair <int, int> ans = { INF, INF };
	for (auto i : ammo) {
		ans = min(ans, { get_time(player, i), move(player, i) });
	}
	return ans;
}

int get_next_fight(Enemy& e, Player& p) {
	return get_fight(p, e);
}

bool need_food(Player& p) {
	return p.s < 200 && p.f >= 10;
}

class Interactor
{
public:
	int move_cnt = 0;
	Player player;
	vector<pt> food, baterry, ray;
	vector<Enemy> v_enemy;

	bool get_state()
	{
		bool flag = true;
		for (pt pos : ray) set_cell_state(pos, '.');
		ray.clear();
		++move_cnt;
		cin >> player;
		player.move_cnt = move_cnt;
		int e, o;
		cin >> e >> o;

		string s;

		for (int i = 0; i < e; i++)
		{
			cin >> s;
			if (s == "finish") flag = false;
			if (s == "pickup_battery")
			{
				int b_p;
				cin >> b_p;
			}
			if (s == "pickup_food")
			{
				int f_s;
				cin >> f_s;
			}
			if (s == "attack")
			{
				int p_id;
				cin >> p_id;
				enemy_info[p_id].agressive = true;
			}
			if (s == "attack_ray")
			{
				int p_id;
				cin >> p_id;
				enemy_info[p_id].agressive = true;
			}
			if (s == "death")
			{
				move_cnt = 1;
				//CLEAR
			}
		}

		if (move_cnt == 1)
		{
			pt vec = { 1500, 1500 };
			initial_pos = player.pos - vec;
			field_reset();
			player.last_shot = move_cnt - 10;
			enemy_info.clear();
			f_id = -1;
		}

		v_enemy.clear();
		for (int i = 0; i < o; i++)
		{
			cin >> s;

			if (s == "player")
			{
				Enemy enemy;
				cin >> enemy;
				if (enemy_info.find(enemy.id) == enemy_info.end()) enemy_info[enemy.id].move_num = move_cnt;
				else set_cell_state(enemy.pos, '.');
				enemy_info[enemy.id].pos = enemy.pos;
				field[enemy_info[enemy.id].pos.x][enemy_info[enemy.id].pos.y] = 'E';
				enemy_info[enemy.id].h_s = enemy.h_s;
				enemy_info[enemy.id].id = enemy.id;
				enemy_info[enemy.id].d = enemy.d;
				enemy_info[enemy.id].r = enemy.r;
				v_enemy.push_back(enemy);

			}
			if (s == "food")
			{
				int n;
				cin >> n;
				food.resize(n);
				cin >> food;
			}
			if (s == "battery")
			{
				int n;
				cin >> n;
				baterry.resize(n);
				cin >> baterry;
			}
			if (s == "obstacles")
			{
				int n;
				cin >> n;
				for (int i = 0; i < n; i++)
				{
					pt pos;
					cin >> pos;
					set_cell_state(pos, '#');
				}
			}
			if (s == "damaged_platform")
			{
				int n;
				cin >> n;
				for (int i = 0; i < n; i++)
				{
					pt pos;
					cin >> pos;
					set_cell_state(pos, 'd');
				}
			}
			if (s == "destroyed_platform")
			{
				int n;
				cin >> n;
				for (int i = 0; i < n; i++)
				{
					pt pos;
					cin >> pos;
					set_cell_state(pos, 'D');
				}
			}
			if (s == "ray")
			{
				pt pos;
				int id, n;
				cin >> id >> n;
				enemy_info[id].agressive = true;
				for (int i = 0; i < n; i++)
				{
					pt pos;
					cin >> pos;
					set_cell_state(pos, 'R');
					ray.push_back(pos);
				}
			}
		}

		return flag;
	}

	void act_move(int action)
	{
		switch (action)
		{
		case MOVE_1_N:
			cout << "move " << player.pos + vec_1_n << endl;
			cerr << "move " << player.pos + vec_1_n << endl;
			break;
		case MOVE_2_N:
			cout << "move " << player.pos + vec_2_n << endl;
			cerr << "move " << player.pos + vec_2_n << endl;
			break;
		case MOVE_1_E:
			cout << "move " << player.pos + vec_1_e << endl;
			cerr << "move " << player.pos + vec_1_e << endl;
			break;
		case MOVE_2_E:
			cout << "move " << player.pos + vec_2_e << endl;
			cerr << "move " << player.pos + vec_2_e << endl;
			break;
		case MOVE_1_S:
			cout << "move " << player.pos + vec_1_s << endl;
			cerr << "move " << player.pos + vec_1_s << endl;
			break;
		case MOVE_2_S:
			cout << "move " << player.pos + vec_2_s << endl;
			cerr << "move " << player.pos + vec_2_s << endl;
			break;
		case MOVE_1_W:
			cout << "move " << player.pos + vec_1_w << endl;
			cerr << "move " << player.pos + vec_1_w << endl;
			break;
		case MOVE_2_W:
			cout << "move " << player.pos + vec_2_w << endl;
			cerr << "move " << player.pos + vec_2_w << endl;
			break;
		case TURN_N:
			cout << "turn N" << endl;
			cerr << "turn N" << endl;
			break;
		case TURN_E:
			cout << "turn E" << endl;
			cerr << "turn E" << endl;
			break;
		case TURN_W:
			cout << "turn W" << endl;
			cerr << "turn W" << endl;
			break;
		case TURN_S:
			cout << "turn S" << endl;
			cerr << "turn S" << endl;
			break;
		case EAT:
			cout << "eat " << min(300 - player.s, player.f) << endl;
			cerr << "eat " << min(300 - player.s, player.f) << endl;
			break;
		case ATTACK:
			assert(f_id != -1);
			cout << "attack " << f_id << endl;
			cerr << "attack " << f_id << endl;
			break;
		case ATTACK_MOVE:
			assert(f_id != -1);
			cout << "both ";
			switch (move(player))
			{
			case MOVE_1_N:
				cout << "move " << player.pos + vec_1_n << ' ';
				cerr << "move " << player.pos + vec_1_n << ' ';
				break;
			case MOVE_1_W:
				cout << "move " << player.pos + vec_1_w << ' ';
				cerr << "move " << player.pos + vec_1_w << ' ';
				break;
			case MOVE_1_E:
				cout << "move " << player.pos + vec_1_e << ' ';
				cerr << "move " << player.pos + vec_1_e << ' ';
				break;
			case MOVE_1_S:
				cout << "move " << player.pos + vec_1_s << ' ';
				cerr << "move " << player.pos + vec_1_s << ' ';
				break;

			}
			cout << "and ";
			cout << "attack " << f_id << endl;
			cerr << "attack " << f_id << endl;
			break;
		case SHOT:
			assert(player.can_shot() && f_id != -1);
			cout << "shot " << enemy_info[f_id].pos << endl;
			cerr << "shot " << enemy_info[f_id].pos << endl;
			break;
		case IDLE:
			cout << "idle" << endl;
			cerr << "idle" << endl;
			break;
		default:
			assert(false);
		}
		cout.flush();
	}
};

int main()
{
	Interactor interactor;

	while (interactor.get_state())
	{
		auto food = get_optimum_food(interactor.food, interactor.player);
		auto ammo = get_optimum_food(interactor.baterry, interactor.player);
		auto enemy = get_optimum_enemy(interactor.v_enemy, interactor.player);

		if (food.first == INF && ammo.first == INF && enemy.first.first == INF)
		{
			interactor.act_move(next_turn(interactor.player.d));
			continue;
		}

		if (f_id != -1)
		{
			bool flag = false;
			for (auto i : interactor.v_enemy) flag |= (i.id == f_id);
			if (flag)
			{
				interactor.act_move(get_next_fight(enemy_info[f_id], interactor.player));
				continue;
			}
			f_id = -1;
		}

		if (enemy.first.second == ATTACK || enemy.first.second == SHOT || enemy.first.second == ATTACK_MOVE) {
			f_id = enemy.second;
			interactor.act_move(enemy.first.second);
			continue;
		}

		if (interactor.player.f > 0){
			interactor.act_move(EAT);
			continue;
		}

		if (enemy.second != INF)
		{
			f_id = enemy.second;
			interactor.act_move(enemy.first.second);
			continue;
		}
		else if (food.second != INF)
		{
			interactor.act_move(food.second);
			continue;
		}
		else if (ammo.second != INF)
		{
			interactor.act_move(ammo.second);
			continue;
		}
		else
		{
			interactor.act_move(move(interactor.player));
		}
	}
}