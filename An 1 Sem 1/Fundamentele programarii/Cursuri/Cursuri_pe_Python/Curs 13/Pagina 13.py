def fibo(n):
    if n<=2: return 1
    return fibo(n-1)+fibo(n-2)


def fiboMem(n, mem):
    if n in mem: return mem[n]
    if n <= 2:
        rez = 1
    else:
        rez = fiboMem(n - 1, mem) + fiboMem(n - 2, mem)
    mem[n] = rez
    return rez


def fiboMemoization(n):
    return fiboMem(n, {})


def fiboDP(n):
    """
      Dynamic programming
      bottom up (backward) variant
      DP(1) = DP(2) = 1
      DP(i) = DP(i-1) + DP(i-2)
    """
    if n<=2: return 1
    mem = [None]*(n)
    mem[0] = 1
    mem[1] = 1
    for i in range(2,n):
        mem[i] = mem[i-1]+mem[i-2]
    return mem[n-1] 