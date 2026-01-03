def lgSublistaCresc(l,poz):
    if poz==len(l)-1:
        return 1
    maxLg = 1
    for i in range(poz+1,len(l)):
        if l[poz]<=l[i]:
            lg = 1+lgSublistaCresc(l,i)
        if lg>maxLg: maxLg = lg
    return maxLg

def lgSublistaCrescMem(l,poz,mem):
    if poz==len(l)-1:
        return 1
    if poz in mem: return mem[poz]
    maxLg = 1
    for i in range(poz+1,len(l)):
        if l[poz]<=l[i]:
            lg = 1+lgSublistaCrescMem(l,i,mem)
            if lg>maxLg: maxLg = lg
    mem[poz] = maxLg
    return maxLg

def lgSublistaCrescDP(l):
    lgs = [0]*len(l)
    lgs[-1] = 1
    for i in range(len(l)-2,-1,-1):
        lgs[i] = 1
        for j in range(i+1,len(l)):
            if l[i]<=l[j] and lgs[i]<lgs[j]+1:
                lgs[i] = lgs[j]+1
    return max(lgs)