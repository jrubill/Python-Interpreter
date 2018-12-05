
x = 4

def f():
    if x > 0:
        x = x - 1
        print "woo!"
        f()
f()
