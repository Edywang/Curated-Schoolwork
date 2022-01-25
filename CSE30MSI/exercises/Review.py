# List and tuple comprehension is awesome!
myTup = {i for i in range(10) if i % 2 == 0}
print(myTup)

myList = [i for i in range(10) if i % 3 == 0]
print(myList)
# What is this commented out line going to do?
# myList.remove(1)

print("Onto more comprehensive usages, pun intended")

myListTup = ([(i+j)+(i*j) for i in range(5)] for j in range(5))
for obj in myListTup:
    print(obj)

d1 = {"name":"alex", "age":20}
d2 = dict(name="alex", age=20)
print(d1 == d2)
print(d1)
d1["name"] = "ben"
# We could also add keys in the same way as modifying
d1["mane"] = "Not a typo"
# We could even add a dictionary as a value to make nested dictionaries
d1["myDict"] = dict(first="Isn't", second="this", third="cool?")
print(d1)