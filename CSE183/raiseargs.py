### raiseargs

def raiseargs(n):
    """Decorator that raises to the n-th power all arguments
    (positional, or keyword arguments) of a given function."""
    # 7 lines
    # YOUR CODE HERE
    def innerfunc(func):
      def f(*args, **kwargs):
        return func(*[pow(i, n) for i in args], **{x: pow(y, n) for x, y in kwargs.items()})
      return f
    return innerfunc
    # YOUR CODE ENDS HERE

### Tests for raiseargs (10 points)

@raiseargs(2)
def f(x, y):
    return x + y

assert f(2, 3) == 13 # 4 + 9

@raiseargs(3)
def g(x, y=1):
    return x + y + 1

assert g(2, y=2) == 17 # 8 + 8 + 1