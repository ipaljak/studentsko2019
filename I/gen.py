#!/usr/bin/python2

doc = """
  Cenerate all test cases in test/:  gen.py
"""

import collections
import sys
import glob
import os
import random
import subprocess
import math

PROBLEM = "I"
sys.setrecursionlimit(1000010)

MAXN = 10**5

class Test(object):
    def __init__(self, n, pics):
        self.n = n       # number of pics
        self.pics = pics # Kx3 matrix of pics


    def validate(self):
        assert 1 <= self.n <= MAXN

        picrow = ""
        for (i, row) in enumerate(self.pics):
            if i < self.n / 3 or self.n % 3 == 0:
                assert len(row) == 3
            else:
                assert len(row) == self.n % 3
            for c in row: picrow += c

        assert len(picrow) == self.n

        groups = []
        for i in range(self.n):
            c = picrow[i]
            assert c >= 'A' and c <= 'Z'
            if i == 0 or picrow[i] != picrow[i - 1]:
                groups.append(c)

        for i in range(len(groups)):
            for j in range(i + 1, len(groups)):
                assert groups[i] != groups[j]


    def write(self, fd=sys.stdout):
        print>>fd, self.n
        for row in self.pics:
            print>>fd, row


def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)


def random_sum_to(n, k):
    a = random.sample(range(1, n), k - 1) + [0, n]
    list.sort(a)
    return [a[i+1] - a[i] for i in range(len(a) - 1)]


def gen_random(n):
    l = random_sum_to(n, 26)
    picrow = ""
    grid = []
    for i, cnt in enumerate(l):
        for j in range(cnt):
            picrow += chr(ord('A') + i)

    for i in range(0, n, 3):
        row = ""
        for j in range(3):
            if i + j < n: row += picrow[i + j]
        grid.append(row)

    return Test(n, grid)


def gen_random_suffix_one(n):
    suff_len = random.randint(1, 26)
    l = random_sum_to(n - suff_len, 26 - suff_len)
    for i in range(suff_len): l.append(1)

    picrow = ""
    grid = []
    for i, cnt in enumerate(l):
        for j in range(cnt):
            picrow += chr(ord('A') + i)

    for i in range(0, n, 3):
        row = ""
        for j in range(3):
            if i + j < n: row += picrow[i + j]
        grid.append(row)

    return Test(n, grid)


def gen_cases():
    remove_cases()

    real = []
    dummy = []

    dummy.append(Test(
        6,
        ["AAA",
         "AAA"]
    ))

    dummy.append(Test(
        13,
        ["AAA",
         "ABB",
         "BBB",
         "BCC",
         "C"]
    ))

    dummy.append(Test(
        19,
        ["VCC",
         "CRR",
         "RRR",
         "RRR",
         "RUI",
         "TLL",
         "L"]
    ))

    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

    # 5 handmade cases
    real.append(Test(
        1,
        ["G"]
    ))

    real.append(Test(
        5,
        ["GHI",
         "ZY"]
    ))

    real.append(Test(
        16,
        ["AAA",
         "BBB",
         "BBC",
         "DEF",
         "GHI",
         "J"]
    ))

    real.append(Test(
        12,
        ["BBB",
         "DDD",
         "DDD",
         "ZZZ"]
    ))

    real.append(Test(
        14,
        ["BBB",
         "DDD",
         "DDD",
         "ZZZ",
         "ZZ"]
    ))

    # 10 random cases
    for i in range(1, 11):
        real.append(gen_random(random.randint(90000, MAXN)))

    # 10 large cases with suffix of ones
    for i in range(1, 11):
        real.append(gen_random_suffix_one(random.randint(90000, MAXN)))

    for i, test in enumerate(real):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.in.%d' \
                % (PROBLEM, i+1)
        input = 'test/%s.in.%d' % (PROBLEM, i+1)
        test.write(file(input, 'wt'))


def main():
    random.seed(293487)
    gen_cases()


if __name__ == "__main__":
    main()

