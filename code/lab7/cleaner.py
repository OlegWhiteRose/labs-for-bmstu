import os

alph = ["key.txt", "source.txt", "encoded.txt", "decoded.txt", "table.txt"]

for x in os.listdir():
    if x.endswith(".txt") or x.endswith(".converted"):
        if x not in alph:
            print(x)
            os.system(f'rm -rf {x}')