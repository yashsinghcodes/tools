import time


# Normal Speed
def NormalMeth():
    v = []
    for i in range(100):
        if i % 3 == 0:
            v.append("Fizz")
        if i % 5 == 0:
            v.append("Buzz")
        if i % 3 == 0 and i % 5 == 0:
            v.append("FizzBuzz")
        else:
            v.append(i)


# Currently The Fastest
def VarMeth():
    v = []
    for i in range(1, 100):
        output = ""
        if i % 3 == 0:
            output += "Fizz"
        if i % 5 == 0:
            output += "Buzz"
        v.append(output or i)


# Slowest
def MapMeth():
    value = { 3: "Fizz", 5: "Buzz" }
    v = []
    for i in range(1, 100):
        output = ""
        for j in value.keys():
            if i % j == 0:
                output += value[j]
        v.append(output or i)


if __name__ == "__main__":
    methods = {
            "Normal method": NormalMeth,
            "Using HashMap": MapMeth,
            "Using Just A Variable": VarMeth
    }
    for i, j in methods.items():
        start = time.time()
        j()
        end = time.time()
        print("Time taken by the following function", i, "is ", str(end-start))
