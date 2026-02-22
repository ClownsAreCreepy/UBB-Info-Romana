from scipy.stats import expon, randint
from matplotlib.pyplot import hist, plot, show
from numpy import linspace, floor

nr_simulations = 10000

# a)
# Histogram
latency = expon.rvs(scale = 2, size=nr_simulations)
hist(latency, bins=10, range = (0, 10), density=True, color="red", edgecolor="black")

# Line
x = linspace(0, 10, nr_simulations)
plot(x, expon.pdf(x, scale = 2))

# Compute
show()


# b)
# 1. Empiric:
# Array de note
grades = [randint.rvs(1, 11) for _ in range(nr_simulations)]

# Calculate how many grades would be over 5, then we divide them by total grades
favorable_case = 0

for i in range(nr_simulations):
    late = latency[i]
    grade = grades[i]

    final_grade = int(grade - floor(late))

    if final_grade >= 5:
        favorable_case += 1

print ("P(N>=5) =", favorable_case / nr_simulations, "empirically")

# 2. Theoretic
print ("P(N>=5) =", sum([randint.pmf(k, 1, 11)*expon.cdf(k - 4, scale = 2) for k in range(5, 11)]), "theoretically")