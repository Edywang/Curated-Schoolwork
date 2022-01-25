import matplotlib.pyplot as plt
import numpy as np
N_points = 100
n_bins = 5

# Generate a normal distribution, center at x=0 and y=5
x = np.random.randn(N_points) # Array with 100 values

# Creating our histogram for scenario 1
UNEXPOSED = 10
INFECTED = 20
SICK = 30
DEAD = 35
RECOVERED = 5
x = []
for i in range(UNEXPOSED):
    x.append(0)
for i in range(INFECTED):
    x.append(1)
for i in range(SICK):
    x.append(2)
for i in range(DEAD):
    x.append(3)
for i in range(RECOVERED):
    x.append(4)

# Creating our histogram for scenario 2
y = []
#for i in range(UNEXPOSED):
#x = []
#for i in 
#x = [UNEXPOSED, INFECTED, SICK, DEAD, RECOVERED]
# y = .4 * x + np.random.randn(100000) + 5

fig, axs = plt.subplots(1, 3, sharey=True, tight_layout=True)

# We can set the number of bins with the `bins` kwarg
axs[0].hist(x, label=["unexposed", "infected", "sick", "dead", "recovered"], histtype="barstacked", stacked=True, bins=n_bins)
axs[1].hist(x, bins=n_bins)
axs[2].hist(x, bins=n_bins)
# stacked=True, label, color, bins, data, histtype

plt.show()