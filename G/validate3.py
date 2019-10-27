#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string

from math import sqrt
from itertools import count, islice

MAXN = 5 * (10**5)

def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n = int(lines[0])

    assert 2 <= n <= MAXN, "n je izvan intervala"
    nl.append("{}{}".format(n, E))

    cnt = [0] * (2*n)

    for i in range(n):
        x, y = map(int, lines[1 + i].split())
        assert 1 <= x <= 2*n, "x je izvan intervala"
        assert 1 <= y <= 2*n, "y je izvan intervala"
        assert x != y, "x je jednak y"
        cnt[x - 1] += 1
        cnt[y - 1] += 1
        nl.append("{} {}{}".format(x, y, E))

    for i in range(2*n):
        assert cnt[x - 1] == 1, "student se u parovima ne pojavljuje tocno jednom"

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'normalni': 26}


def what_cluster(data):
    return "normalni"


################### Zadatak-specifican kod iznad ove linije #########################

import sys
import glob
import hashlib


def group_in_batches(files):
    # mnozenje.in.1a, mnozenje.in.1b sprema u isti batch

    files.sort()
    B = []
    for f in files:
        if f[-1].islower() and len(B) > 0 and f[:-1] == B[-1][-1][:-1]:
            B[-1].append(f)
        else:
            B.append([f])
    return B


if __name__ == "__main__":
    f = []
    for pattern in sys.argv[1:]:
        for filename in glob.glob(pattern):
            f.append(filename)

    bc = []
    for batch in group_in_batches(f):
        if 'dummy' not in batch[0]:
            bc.append([])
        for filename in batch:
            print("{}: ".format(filename), end="")
            try:
                lines = open(filename).readlines()
                summary = check(lines)
                c = what_cluster(summary)
                if 'dummy' not in batch[0]:
                    bc[-1].append(c)
            except Exception as e:
                print("Greska!", e)
                raise
            else:
                print("Sve ok! (cluster {}, summary = {})".format(c, summary))

    clusters = {}
    for b in bc:
        for c in b:
            assert c == b[0], "Ima razlicitih cluster-a unutar batcha"
        if not b[0] in clusters:
            clusters[b[0]] = 0
        clusters[b[0]] += 1

    assert clusters == expected_clusters, "Kriva raspodjela clustera ({} vs {})".format(clusters, expected_clusters)

    # Buda test - provjeri duplikate
    hashes = set(hashlib.sha1(open(x, 'rb').read()).hexdigest() for x in f)
    assert len(hashes) == len(f), "Ima duplikata!"
