from scipy.stats import norm
from numpy import mean, std, linspace
from matplotlib.pyplot import show, hist, grid, legend, xticks, plot

def first_ex(nr_sim):
    # a)
    data = norm.rvs(loc = 165, scale = 10, size = nr_sim)

    hist(data, bins = 16,  density = True, range = (130, 200), label='relative frequencies')

    x = linspace(130, 200, nr_sim)
    plot(x, norm.pdf(x, loc = 165, scale = 10), 'r-', label='functia de desnitate')

    xticks(range(130, 200,5))
    legend(loc = 'upper right')
    grid()
    show()

    # b)
    print("Valoarea medie:", mean(data))
    print("Deviatia standard:", std(data))

    print("Proportia de valori in [160, 170]:", sum((160 <= data) & (data <= 170)) / nr_sim)
    print("Valorile exacte:", norm.cdf(170, loc=165, scale=10) - norm.cdf(160, loc=165, scale=10))


first_ex(2000)

