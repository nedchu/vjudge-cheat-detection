with open('input.txt') as inf, open('output.txt', 'w') as ouf:
    n = int(inf.readline())
    m = n // 3
    a = [0, 2]
    t = [0, -1]
    for i in range(500):
        t.append(4 * t[-1] + 21)
    for i in range(2, 500):
        if i % 2 == 0:
            a.append(4 * a[-1] - t[i // 2])
        else:
            a.append(4 * a[-1] + 2)
    print(a[m], file=ouf)

