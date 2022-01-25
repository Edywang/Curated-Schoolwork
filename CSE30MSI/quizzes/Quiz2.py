print(range(0, 10))

print("Question 1")

a,b,c = 1, 2.3, "hello"
d=e=f=1, 2.3, "hello"
# Will this print true or false?
print(a==d)

print("Moving onto question 2")

# What will this block of code print?
for i in range(10):     # i goes from 0..9
    print(i)
    if(i == 9):
        break
else:
    print(i+100)

print("Moving onto question 3")

# Let's review for loops and the range() function
for i in range(11, 16):
    print(i)

print("Moving onto question 4")

# Now let's review nested loops
for outer in range(16, 21):
    print("Reached outer loop")
    for inner in range(1, 6):
        print(outer + inner)