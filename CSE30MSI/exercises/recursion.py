# Iteration
# Recursion

def fibonacci(n):
    if(n == 1): # f(1) = 1
        return 1
    if(n <= 0): # f(0) = 0
        return 0
    return fibonacci(n-1) + fibonacci(n-2)

def iterative_fib(n):
    if (n <= 0):
        return 0
    if (n <= 2):
        return 1
    a, b, c = 1, 1, 0
    for i in range(n - 2):
        c = a + b
        b = a
        a = c
    return a

def main():
    print(fibonacci(3))
    print(iterative_fib(3))

if __name__ == "__main__":
    main()