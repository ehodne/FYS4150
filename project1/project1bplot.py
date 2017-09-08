from __future__ import division
from pylab import *

A = genfromtxt('pls10.txt')
B = genfromtxt('pls100.txt')
C = genfromtxt('pls1000.txt')
D = genfromtxt('pls10000.txt')


x_A = A[:,0]; u_A = A[:,1]; cfs_A = A[:,2]
x_B = B[:,0]; u_B = B[:,1]; cfs_B = B[:,2]
x_C = C[:,0]; u_C = C[:,1]; cfs_C = C[:,2]
x_D = D[:,0]; u_D = D[:,1]; cfs_D = D[:,2]


'''
plot(x_A, u_A, label='Calculated Values, n = 10')
plot(x_A, cfs_A, label='Close-Form Solution, n = 10')

plot(x_B, u_B, label='Calculated Values, n = 100')
plot(x_B, cfs_B, label='Close-Form Solution, n = 100')

plot(x_C, u_C, label='Calculated Values, n = 1000')
plot(x_C, cfs_C, label='Close-Form Solution, n = 1000')
'''

plot(x_D, u_D, label='Calculated Values, n = 10000')
plot(x_D, cfs_D, label='Close-Form Solution, n = 10000')


legend()
xlabel('x')
ylabel('f(x)')
show()

