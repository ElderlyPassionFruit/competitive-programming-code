import requests
import sys
from bs4 import BeautifulSoup as BS

DATA = "some.txt"
CNT_PROBLEMS = 8
TEMPLATE = "\tThe table of results parallel A autumn qualification\n №  | name |   Q  |   R  |   S  |   T  |   U  |   V  |   W  |   X  | Total |  Dirt"
LINE = "-" * 83

def get_page():
    res = open(DATA, "r").read()
    return res

def get_tables(markup):
    soup = BS(markup, "html.parser")
    soup = soup.select("body tbody tr")
    return soup[4 + 324:]

def get_person(table_with_name):
    return table_with_name.select("td")

def get_name(person):
    return person[2].string.split(">")[0].split("-")[3]

def check(result):
    if ("+" in result):
        return "+"
    else:
        return "-"

def get_ok(problem):
    ans = ""
    try:
        ans = problem.string.split()[0]
    except AttributeError:
        ans = "-"
    return ans

def get_score(person):
    s = []
    #for i in person:
     #   print(i)
    #return
    for i in range(5, 29):
        s.append(get_ok(person[i]))
    return s[-CNT_PROBLEMS:]

def get_result(score):
    ans = 0
    for i in score:
        if check(i) == "+":
            ans += 1
    return ans

def check_interesting(score):
    return get_result(score) > 0 or len("".join(score)) > CNT_PROBLEMS

def get_problem_dirt(problem):
    if (problem.string == None):
        return 0
    if (check(problem.string) == "-"):
        return 0
    result = problem.string.split()[0]
    if (result != "+∞"):
        return int("0" + result[1:])
    else:
        return int(str(problem).split()[6].split("\"")[1])

def get_problem_submits(problem):
    if (problem.string == None):
        return 0
    if (problem.string == "-"):
        return 0
    result = problem.string.split()[0]
    if (not "∞" in result):
        return abs(int("0" + result[1:]))
    else:
        return abs(int(str(problem).split()[6].split("\"")[1]))

def get_dirt(person):
    ans = 0
    for i in range(21, 29):
        ans += get_problem_dirt(person[i])
    return ans

def get_info(person):
    name = get_name(person)
    score = get_score(person)
    result = -get_result(score)
    dirt = get_dirt(person)
    return [result, dirt, name, score]

def get_fout_point(point):
    return " " * (4 - len(point)) + point

def get_fout_score(score):
    for i in range(len(score)):
        score[i] = get_fout_point(score[i])
    return " | ".join(score)

def get_fout_inf(name):
    return " " * (3 - len(name)) + name

def get_fout_name(name):
    return " " * (3 - len(name)) + name

def get_fout(person, ind):
    person[3] = get_fout_score(person[3])
    person[0] = str(person[0])
    person[2] = get_fout_name(person[2])
    person[1] = get_fout_inf(str(person[1]))
    return get_fout_inf(str(ind)) + " |  " + person[2] + " | " + person[3] + " |   " + person[0] + "   |  " + person[1]

def get_cnt(data, problem):
    ans = 0
    for i in data:
        if (check(i[3][problem]) == "+"):
            ans += 1
    return ans

def get_res_for_problems(data):
    ans = []
    x = 0
    for i in range(CNT_PROBLEMS):
        x += get_cnt(data, i)
        ans.append(get_fout_point(str(get_cnt(data, i))))
    ans.append(" " + get_fout_point(str(x)))
    return " Accepted  | " + " | ".join(ans) + " |"


def get_dirt_for_problems(ans, person):
    for i in range(CNT_PROBLEMS):
        ans[i] += get_problem_dirt(person[i + 21])
    return ans

def get_submits_for_problems(ans, person):
    for i in range(CNT_PROBLEMS):
        ans[i] += get_problem_submits(person[i + 21])
    return ans

def get_data():
    result = open("result.txt", "w")
    page = get_page()
    table = get_tables(page)
   # for i in get_person(table[0]):
   #     print(i)
    #return
   # get_score(get_person(table[0]))
    data = []
    dirt = [0] * CNT_PROBLEMS
    submits = [0] * CNT_PROBLEMS
    for i in table:
        person = get_person(i)
        if (check_interesting(get_score(person))):
            dirt = get_dirt_for_problems(dirt, person)
            submits = get_submits_for_problems(submits, person)
            data.append(get_info(person))
    data.sort()
    for i in range(len(data)):
        data[i][0] = -data[i][0]
    problem_results = get_res_for_problems(data)
    print(TEMPLATE)
    print(TEMPLATE, file = result)

    print(LINE)
    print(LINE, file = result)
    cnt = 1
    for i in data:
        i = get_fout(i, cnt)
        print(i)
        print(i, file = result)
        cnt += 1
    x = sum(dirt)
    for i in range(CNT_PROBLEMS):
        dirt[i] = get_fout_point(str(dirt[i]))
    dirt.append(" " + get_fout_point(str(x)))
    
    dirt = " Dirt      | " + " | ".join(dirt) + " |"
    x = sum(submits)
    for i in range(CNT_PROBLEMS):
        submits[i] = get_fout_point(str(submits[i]))
    submits.append(" " + get_fout_point(str(x)))
    submits = " Submits   | " + " | ".join(submits) + " |"

    print(LINE)
    print(LINE, file = result)
    print(submits)
    print(submits, file = result)
    print(problem_results) 
    print(problem_results, file = result) 
    print(dirt)
    print(dirt, file = result)
   
get_data()
