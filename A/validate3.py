#!/usr/bin/python3
"""Upotreba ./validate3.py test/*.in*"""

import string
import sys

from math import sqrt
from itertools import count, islice

MAXN = 10**5

sys.setrecursionlimit(10**6)

def check_tree(node, dad, graph, visited):
    visited[node] = 1
    ok = True
    for nxt in graph[node]:
        if nxt == dad: continue
        if visited[nxt] != 0: return False
        ok &= check_tree(nxt, node, graph, visited)
    return ok

def check(lines):
    nl = []   # ispravno formatirane linije
    E = "\n"  # line ending

    n = int(lines[0])

    assert 2 <= n <= MAXN, "n je izvan intervala"
    nl.append("{}{}".format(n, E))

    edges = set()
    graph = []
    for i in range(n): graph.append([])

    for i in range(n - 1):
        u, v, w = map(int, lines[1 + i].split())
        assert 1 <= u <= n, "cvor u edgeu izvan intervala"
        assert 1 <= v <= n, "cvor u edgeu izvan intervala"
        assert 0 <= w <= 10**9, "weight edgea izvan intervala"
        assert u != v, "dva ista cvora u edgeu"
        assert (u, v) not in edges, "ponovljen edge"
        edges.add((u, v))
        edges.add((v, u))
        graph[u - 1].append(v - 1)
        graph[v - 1].append(u - 1)
        nl.append("{} {} {}{}".format(u, v, w, E))

    visited = [0] * n
    assert check_tree(0, -1, graph, visited), "Graf nije stablo"

    assert lines == nl, "Krivi format (%s vs %s)" % (lines, nl)
    assert lines[-1][-1] == "\n", "Zadnji red ne zavrsava sa \\n"
    return {}


# Ocekivani clusteri! Ovo vjerojatno zelis promijeniti!
expected_clusters = {'normalni': 30}


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
