import subprocess
import os

testinput = 'tests\\big_tests\\'
print('print size test')
size = int(input())
subprocess.call(['binaryToTxt.exe', testinput+str(size)+'.in', testinput+str(size)+'.txt', testinput+str(size)+'.ans', testinput+str(size)+'.ans.txt', testinput+str(size)+'.user.ans', testinput+str(size)+'.user.ans.txt'], stdout=subprocess.PIPE, shell = True)
print('matrix A, B, res bin to txt '+str(size))
