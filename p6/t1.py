
x = 4

def f():
    if x >= 0:
        print x
        x -= 1
        f()

f()
