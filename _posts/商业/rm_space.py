import os
def rm_space():
    for root, dirs, files in os.walk(".", topdown=False):
        for fn in files:
            if fn.find(" ") > 0:
                n  =  fn.replace(" ", "")
                fn = os.path.join(root, fn)
                n = os.path.join(root, n)
                os.rename(fn, n)

rm_space()