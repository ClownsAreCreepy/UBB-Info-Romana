from scipy.stats import norm
from numpy import mean, var

# a)

print("P(X > 1) =", 1 - norm.cdf(1, loc = 1, scale = 1))
print("P(X < 1, Y > 2) =", norm.cdf(1, loc = 1, scale = 1) * (1 - norm.cdf(2, loc = 2, scale = 1)))

# P(1 < X < 2) = Fx(2) - Fx(1) = P(X<2) - P(X<1)
# P(X > 1 | X < 2) = P(1 < X < 2) / P(X < 2)
Fx2 = norm.cdf(2, loc = 1, scale = 1)
Fx1 = norm.cdf(1, loc = 1, scale = 1)
print("P(X > 1 | X < 2) =", (Fx2 - Fx1) / Fx2)

# b)
# Prep variables for b and c
nr_simulations = 100000
X = norm.rvs(loc = 1, scale = 1, size = nr_simulations)
Y = norm.rvs(loc = 2, scale = 1, size = nr_simulations)

print("P(3 < X^2 + Y^2 < 6", mean((3 < X**2 + Y**2) & (X**2 + Y**2 < 6)))

# c)
print("V(X + Y) =", var(X + Y))
print("E((X - Y) ^ 2) =", mean((X - Y)**2))