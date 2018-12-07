
x = 4

def fib():
    global x
    if x == 0:
        return 1
    if x == 1:
        return 1
    x -= 1
    return fib() + fib() 

x = fib()
print x
