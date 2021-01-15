import os
from random import randint as rnd

INF = 10 ** 10

MIN_START = 0
MAX_START = 3

MIN_ENERGY = -1
MAX_ENERGY = 1
MIN_FOOD = 0
MAX_FOOD = 10

CNT_SWEET = 10

def get(l, r):
	return rnd(0, INF) % (r - l + 1) + l

def gen(index):
	FILE_NAME = "tests/" + str(index) + ".txt"
	print(FILE_NAME)
	f = open(FILE_NAME, "w")
	energy = get(MIN_START, MAX_START)
	
	print(energy, file = f)
	print(CNT_SWEET, file = f)
	
	for i in range(CNT_SWEET):
		energy = get(MIN_ENERGY, MAX_ENERGY)
		food = get(MIN_FOOD, MAX_FOOD)
		print(energy, food, file = f)
	f.close()

def main():
	print("Введите отрезок индексов тестов")
	a = input().split()
	l = int(a[0])
	r = int(a[1])
	for i in range(l, r + 1):
		gen(i);

main()