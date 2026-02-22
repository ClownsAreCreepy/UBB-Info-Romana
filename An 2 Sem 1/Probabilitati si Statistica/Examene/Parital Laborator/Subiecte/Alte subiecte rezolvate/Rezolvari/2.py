from scipy.stats import geom, norm
from matplotlib.pyplot import hist, show, xticks
from numpy import mean

# a)
# Get success probability
# We take the probability of getting a person over 1.90m
prob_success = 1 - norm.cdf(1.90, loc = 1.65, scale = 0.2)

# Generate simulations
nr_simulations = 10000
x = geom.rvs(prob_success, size = nr_simulations)

# Histogram from 1 to 10
bin_edges = [k + 0.5 for k in range(0, 11)]
hist(x, bin_edges, density = True, color = "red", edgecolor = "black")
xticks(range(1,11))

show()

# b)
# Empirical

print("P(X > 10) =", mean([i > 10 for i in x]), "empirically")

# Theoretic
print("P(X > 10) =", 1 - geom.cdf(10, prob_success), "theoretically")