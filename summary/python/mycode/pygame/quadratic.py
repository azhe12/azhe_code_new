#!/usr/bin/python
#coding=utf-8
import math
def quadratic_equation(a, b, c):
    '''
    return a result of equation like bellow:
    a*x^2 + b*x + c = 0
    >>> quadratic_equation(0.5, 1, -1.5)
    1.0
    >>> quadratic_equation(1, 2, -8)
    2.0
    '''
    x1 = 0
    x2 = 0
    d = b**2 - 4.0*a*c
    if d < 0:
        print '方程没有实数解'
    elif d == 0:
        x1 = - (b / 2.0*a)
    else:
        x1 = (-b + math.sqrt(d)) / (2.0*a)
        x2 = (-b - math.sqrt(d)) / (2.0*a)
    #只需要正解
    if x1 > 0:
        return x1
    elif x2 > 0:
        return x2
    else:
        return 0

#print quadratic_equation(0.5, 1, -1.5)
if __name__ == '__main__':
    import doctest, quadratic
    doctest.testmod(quadratic)

