# -*- coding: utf-8 -*-
"""
Created on Mon Jun  4 17:08:23 2018

@author: Tony Innamorato
"""


#question 1
def f(x):
    if (x >= 12):
        return x - 1
    else:
        return f(f(x+2))
print(f(4))
print(f(20))

#question 2
def P(x, y):
    if (y == 1 or y == x):
        return 1
    elif (y > x):
        return 0
    else:
        total = 0
        temp = 1
        while temp != y:
            total += P(x - y, temp)
            temp += 1
        total += P(x-y, y)
        return total
print(P(7,4))
print(P(35, 7))

#question 3
def fun(n):
    if (n == 1):
        return 0
    else:
        return n * n + fun(n-1)
print(fun(10))

#questin 4
def baseTwo(n):
    if (n == 1):
        return 2
    else:
        return (2*n) * baseTwo(n-1)
print(baseTwo(3))

def AST(n):
    if (n == 1):
        return 2 - 8
    else:
        return 2*n + ((-1)**n+1) * n + AST(n-1)
print(AST(2))


#question 5
def S(n, k):
    if (k == 1 or k == n):
        return 1
    return S(n - 1, k-1) + k * S(n - 1, k)
print(S(5,3))






































