import random
import time

def generrateStrings(n):
    X = "ATGC"
    s1 = ''.join(random.choice(X) for i in range(n))
    return s1

if __name__ == "__main__":
    s = time.time()
    s1 = generrateStrings(100000000)
    e = time.time()
    print(s1)
    print()
    print(s1)
