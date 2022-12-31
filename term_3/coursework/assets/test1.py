def w(filename, data, n, opt):
    with open(f"{filename}.test", "w") as f:
        f.write(f"open {data}.ssa\n")
        for i in range(n):
            f.write(f"{opt} {i}\n")
        f.write("quit\n")


w("data1-1", "1", 5000, "add")
w("data1-2", "2", 7500, "add")
w("data1-3", "3", 10000, "add")

w("data2-1", "1", 5000, "find")
w("data2-2", "2", 7500, "find")
w("data2-3", "3", 10000, "find")
