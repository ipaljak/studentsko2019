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

PROBLEM = "E"
sys.setrecursionlimit(1000010)

MAXN = 30
chars = "0123456789+-*/="

class Test(object):
    def __init__(self, expr):
        self.expr = expr       # mathematical expression


    def validate(self):
        assert 1 <= len(self.expr) <= MAXN
        for c in self.expr:
            assert c in chars

    def write(self, fd=sys.stdout):
        print>>fd, self.expr


def remove_cases():
    cases = glob.glob('test/%s.dummy.in.*' % PROBLEM)
    cases += glob.glob('test/%s.dummy.out.*' % PROBLEM)
    cases += glob.glob('test/%s.in.*' % PROBLEM)
    cases += glob.glob('test/%s.out.*' % PROBLEM)
    for c in cases:
        print>>sys.stderr, 'Removing ' + c
        os.remove(c)


def rand_oper():
    return random.sample(['+', '-', '*', '/'], 1)[0]


def rand_char():
    return chars[random.randint(0, len(chars) - 1)]


def rand_dig():
    return chr(ord('0') + random.randint(0, 9))


def gen_random_expr(oper):
    if oper == '+':
        a = random.randint(100000, 9999999)
        b = random.randint(100000, 9999999)
        c = a + b
        return a, b, c

    if oper == '-':
        a = random.randint(100000, 9999999)
        b = a
        while b == a:
            b = random.randint(100000, 9999999)
        if a < b: a, b = b, a
        c = a - b
        return a, b, c

    if oper == '*':
        a = random.randint(10000, 99999)
        b = random.randint(1000, 9999)
        if random.randint(0, 1) == 0: a, b = b, a
        c = a * b
        return a, b, c

    if oper == '/':
        a = random.randint(10000, 99999)
        b = random.randint(1000, 9999)
        if random.randint(0, 1) == 0: a, b = b, a
        c = a * b
        return c, a, b

    assert False


def gen_random_one_change():
    oper = rand_oper()
    a, b, c = gen_random_expr(oper)
    expr = list(str(a)) + [oper] + list(str(b)) + ['='] + list(str(c))

    i = -1
    while True:
        i = random.randint(0, len(expr) - 1)
        if expr[i] != '=': break

    if random.randint(0, 1) == 0:
        i = len(str(a))

    if expr[i] in "+-*/":
        expr[i] = rand_oper()
    else:
        expr[i] = rand_dig()

    expr_str = "".join(expr)
    return Test(expr_str)


def gen_random_two_changes():
    oper = rand_oper()
    a, b, c = gen_random_expr(oper)
    expr = list(str(a)) + [oper] + list(str(b)) + ['='] + list(str(c))

    i = -1
    while True:
        i = random.randint(0, len(expr) - 1)
        if expr[i] != '=': break

    j = -1
    while True:
        j = random.randint(0, len(expr) - 1)
        if expr[i] != '=' and j != i: break

    if random.randint(0, 1) == 0 and j != len(str(a)):
        i = len(str(a))

    for k in [i, j]:
        if expr[k] in "+-*/":
            expr[k] = rand_oper()
        else:
            expr[k] = rand_dig()

    expr_str = "".join(expr)
    return Test(expr_str)


def gen_random_move_operand():
    oper = rand_oper()
    a, b, c = gen_random_expr(oper)
    expr = list(str(a)) + [oper] + list(str(b)) + ['='] + list(str(c))

    i = len(str(a))
    j = random.randint(2, len(str(a)) + 1 + len(str(b)) - 3)

    expr[j] = expr[i]
    expr[i] = rand_char()

    expr_str = "".join(expr)
    return Test(expr_str)


def gen_random_move_equals():
    oper = rand_oper()
    a, b, c = gen_random_expr(oper)
    expr = list(str(a)) + [oper] + list(str(b)) + ['='] + list(str(c))

    i = len(str(a)) + 1 + len(str(b))
    j = random.randint(len(str(a)) + 4, len(expr) - 4)

    expr[j] = expr[i]
    expr[i] = rand_char()

    expr_str = "".join(expr)
    return Test(expr_str)


def gen_cases():
    remove_cases()

    real = []
    dummy = []

    dummy.append(Test("1++1=2"))
    dummy.append(Test("2+3=6"))

    for i, test in enumerate(dummy):
        test.validate()
        print>>sys.stderr, 'Generating test/%s.dummy.in.%d' % (PROBLEM, i+1)
        test.write(file('test/%s.dummy.in.%d' % (PROBLEM, i+1), 'wt'))

    # handmade "correct"

    real.append(Test("12345678+98765432=111111110"))
    real.append(Test("222222222+777777778=1000000000"))
    real.append(Test("1000000000-777777778=222222222"))
    real.append(Test("4322351*43=185861093"))
    real.append(Test("4567234/652462=7"))

    # handmade "wrong format"
    real.append(Test("41244"))
    real.append(Test("0"))
    real.append(Test("5+0=5"))
    real.append(Test("0*10=0"))
    real.append(Test("42-0=42"))
    real.append(Test("17-17=0"))
    real.append(Test("2/0=0"))
    real.append(Test("/"))
    real.append(Test("+="))
    real.append(Test("-10+10=0"))
    real.append(Test("5-10=-5"))
    real.append(Test("2*2="))
    real.append(Test("2*=4"))
    real.append(Test("*2=4"))
    real.append(Test("2*2==4"))
    real.append(Test("20+30=50+"))
    real.append(Test("400=100+300"))
    real.append(Test("400=100+500"))

    # handmade navlakuse na correct
    real.append(Test("5/2=2"))
    real.append(Test("10/3=3"))
    real.append(Test("432413/542=797"))

    # random testovi s jednom promjenom
    for i in range(16):
        real.append(gen_random_one_change())

    # random testovi s dvije promjene
    for i in range(11):
        real.append(gen_random_two_changes())

    # random testovi s pomicanjem operanda
    for i in range(11):
        real.append(gen_random_move_operand())

    # random testovi s pomicanjem jednakosti
    for i in range(11):
        real.append(gen_random_move_equals())

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

