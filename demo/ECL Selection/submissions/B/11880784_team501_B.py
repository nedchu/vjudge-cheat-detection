fin = open('input.txt')
n = int(fin.readline())
m = int(n/3)
fout = open('output.txt', 'w+')
if m%2==1:
    fout.write(str(int( 2**(m*2-1)+(2**m)-2 )))
else:
    fout.write(str(int( 2**(m*2-1)+(2**(m-1)-1 ))))