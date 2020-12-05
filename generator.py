import random
import time

def generrateStrings(n):
    X = "ATGC"
    s1 = ''.join(random.choice(X) for i in range(n))
    return s1

def generrateStrings2(n):
    s = generrateStrings(n)
    s1 = s
    q = n//100
    X = "ATGC"
    s = list(s)
    for i in range(q):
        a = random.randint(0,n)
        b = random.choice(X)
        # print(a,b)
        s[a] = b
    sx = ''.join(s)
    return sx,s1

def generrateStrings3(n,empty = 1000):
    s = generrateStrings(n)
    s1 = s
    q = n//100
    X = "ATGC"
    s = list(s)
    toss = random.randint(0,1)
    #print(toss)
    if(toss == 0):
        s = s[empty:]
    else:
        s = s[:len(s)-empty]

    for i in range(q):
        a = random.randint(0,n-empty)
        b = random.choice(X)
        # print(a,b)
        s[a] = b
        # print(a,b)
    # print(s)
    # print(len(s),len(s1))
    s = ''.join(s)
    return s,s1

if __name__ == "__main__":
    s = time.time()
    s1,s2 = generrateStrings3(100000000,1)
    # print(len(s1))
    # print(len(s2))
    # print(type(s1))
    # print(type(s2))
    e = time.time()
    print(s1)
    print()
    print(s2)
