#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>

#define STEKLOPAKET 2
#define LEFT -1
#define STAY 0
#define RIGHT 1

#define OK 0
#define HALT -1111
#define ERROR -2222
#define TOOMANY -3333

const int MAX_K = 20;
const int MAX_ITER = 3e7;
const int MAX_MF = MAX_ITER * 2 + 1;
int k;
int pos, command, money, iter;
int mfs[MAX_MF];

struct Instruction {
    bool work{false};
    int company{0};
    int mov{STAY};
    int command{0};

    bool halt{false};

    std::string cmd;
} instr[3][MAX_K];

template<typename T>
T getByChar(const std::vector<T>& vars, const char* str, char c) {
    return vars[strchr(str, c) - str];
}

int load() {
    std::cin >> k;
    std::string allCmd;
    getline(std::cin, allCmd);
    if (k <= 0 || k > MAX_K) return ERROR;
    for (const int& s : {STEKLOPAKET, 0, 1}) {
        for (int num = 0; num < k; ++num) {
            getline(std::cin, allCmd);
            std::stringstream allIn(allCmd);
            std::string mv;
            allIn >> mv;
            if (mv.size() != 1 && (mv.size() != 2 || mv[1] != 'C')) return ERROR;
            if (mv[0] == 'H') {
                instr[s][num].halt = true;
            } else if (mv[0] == 'L' || mv[0] == 'S' || mv[0] == 'R') {
                instr[s][num].mov = getByChar<int>({LEFT, STAY, RIGHT}, "LSR", mv[0]);
            } else {
                return ERROR;
            }
            if (mv.size() == 2 && mv[1] == 'C') instr[s][num].work = true;

            instr[s][num].cmd = mv;
            if (!instr[s][num].halt) {
                std::string comp;
                allIn >> comp;
                if (comp != "S" && comp != "0" && comp != "1") return ERROR;
                if (comp == "S" && s != STEKLOPAKET) return ERROR;
                instr[s][num].company = getByChar<int>({STEKLOPAKET, 0, 1}, "S01", comp[0]);

                int newNum;
                allIn >> newNum;
                if (newNum < 0 || newNum >= k) return ERROR;
                instr[s][num].command = newNum;
                instr[s][num].cmd += " " + comp + " " + std::to_string(newNum);
            }
            if (allIn.rdbuf()->in_avail() != 0) return ERROR;
        }
    }
    return OK;
}

void init() {
    pos = MAX_MF / 2;
    mfs[pos] = STEKLOPAKET;
    command = 0;
    money = 0;
    iter = 0;
}

int doIteration() {
    if (iter == MAX_ITER) {
        return TOOMANY;
    }

    std::cerr << "Company: ";
    if (mfs[pos] == STEKLOPAKET) std::cerr << "S";
    else std::cerr << mfs[pos];
    std::cerr << " Command: " << command << std::endl;

    const Instruction& toDo = instr[mfs[pos]][command];
    if (toDo.mov == ERROR || toDo.company == ERROR || toDo.command == ERROR) {
        std::cerr << "ERROR: You tried executing an invalid instruction: " << toDo.cmd << std::endl;
        return ERROR;
    }
    std::cerr << "You executed instruction: " << toDo.cmd << std::endl;

    if (toDo.work) ++money;
    if (toDo.halt) return HALT;

    mfs[pos] = toDo.company;
    pos += toDo.mov;
    command = toDo.command;
    ++iter;
    return OK;
}

int simulate() {
    int res;
    do {
        res = doIteration();
    } while (res == OK);
    return res;
}

int main() {
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    if (load() != OK) {
        if (k <= 0 || k > MAX_K) {
            std::cout << "Your program required and invalid number of companies." << std::endl;
        } else {
            std::cout << "Error while reading instructions." << std::endl;
        }
    } else {
        init();
        int res = simulate();
        if (res == HALT) std::cout << "Your program halted successfully with " << money << " bubles after " << iter << " iterations." << std::endl;
        else if (res == ERROR) std::cout << "Your program tried executing an invalid instruction." << std::endl;
        else if (res == TOOMANY) std::cout << "Your program exceeded the number of allowed iterations." << std::endl;
        else std::cout << "Unknown error." << std::endl;
    }
    return 0;
}