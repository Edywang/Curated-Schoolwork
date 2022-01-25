
# a function that returns a list
# provided `n`, will produce a list of n evens starting at 2
def first_n_evens_l(n):
    num = 2
    to_return = []
    while num <= (n*2):
        to_return.append(num)
        num += 2
    return to_return

# a function that returns a generator
# provided `n`, will generate n evens starting at 2.
def first_n_evens_g(n):
    num = 2
    while num <= (n*2):
        yield num
        # at this line of code, the function will stop. 
        # it returns `num`, for now, and when iterated forward, will continue executing the function
        num += 2

lst = first_n_evens_l(4)
gen = first_n_evens_g(4)

print(type(lst))
print(type(gen))

print()
print('List')
for i in lst:
    print(i, end=' ')
    
print()
print('Generator')
for i in gen:
    print(i, end=' ')
    
print()

