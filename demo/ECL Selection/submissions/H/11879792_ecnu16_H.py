with open('input.txt') as inf, open('output.txt', 'w') as ouf:
    n = int(inf.readline())
    if n <= 9:
        print(8 * 9 ** (n - 1), file=ouf)
    else:
        print(8 * 9 ** 8 * 10 ** (n - 9), file=ouf)