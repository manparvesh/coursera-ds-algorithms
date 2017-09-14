# python3
from sys import stdin
import math


class LinearEquationResolver(object):
    """docstring for LinearEquationResolver"""

    def __init__(self, A, b, c):
        self.A = A  # coefficient matrix
        self.b = b  # output matrix for coefficient
        self.c = c  # objective function matrix

        self.n = len(A)  # number of input equations
        self.m = len(c)  # number of variables

        self.max_value = -math.inf
        self.result = []

        self.INFINITY = 10**9
        self.bounded = True

        total = n + m + 1
        self.compute(total)

    def compute(total):
        arr = [] * total
        for i in range(0, len(arr)):
            arr[i] = i
        self.generateProcessCombinations(arr, total, 0)

    def generateProcessCombinations(arr, n, r):
        data = [] * r
        self.combinationUtil(arr, n, r, 0, data, 0)

    def combinationUtil(arr, n, r, index, data, i):
        if index == r:
            st = set()
            for d in data:
                st.add(d)
            self.processSubset(st)
            return

        # when no more elements are there to put in data
        if i >= n:
            return

        # current is included, put next at next location
        data[index] = arr[i]


def solve_diet_problem(n, m, A, b, c):
    # Write your code here
    return [0, [0] * m]

n, m = list(map(int, stdin.readline().split()))
A = []
for i in range(n):
    A += [list(map(int, stdin.readline().split()))]
b = list(map(int, stdin.readline().split()))
c = list(map(int, stdin.readline().split()))

anst, ansx = solve_diet_problem(n, m, A, b, c)

if anst == -1:
    print("No solution")
if anst == 0:
    print("Bounded solution")
    print(' '.join(list(map(lambda x: '%.18f' % x, ansx))))
if anst == 1:
    print("Infinity")
