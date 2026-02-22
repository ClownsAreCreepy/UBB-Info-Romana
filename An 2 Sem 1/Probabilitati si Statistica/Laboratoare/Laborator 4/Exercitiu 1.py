from scipy.stats import bernoulli, binom
from matplotlib.pyplot import bar, show, hist, grid, legend

def movementSim(nr_steps, p):
    movement = bernoulli.rvs(p, size = nr_steps)
    position = 0
    step_list = [0]
    for step in movement:
        position += 2 * step - 1
        step_list.append(position)
        print(position)

def histogram_line(nr_steps, p):
    step_list = []

    for _ in range(1000):
        movement = bernoulli.rvs(p, size=nr_steps)
        position = 0
        for step in movement:
            position += 2 * step - 1

        step_list.append(position)

    data = [binom.pmf(k, nr_steps, p) for k in range(nr_steps + 1)]
    bin_edges = [k + 0.5 for k in range(nr_steps + 1)]
    hist(step_list, bin_edges, density=True, rwidth=0.9, color='green', edgecolor='black', alpha=0.5,
         label='relative frequencies')

    distribution = dict([(2 * i - nr_steps, data[i]) for i in range(0 ,nr_steps + 1)])
    bar(distribution.keys(), distribution.values(), width=0.85, color='red', edgecolor='black', alpha=0.6,
        label='probabilities')

    legend(loc='lower left')
    grid()
    show()


def histogram_circle(nr_steps, p, n):
    step_list = []

    for _ in range(1000):
        movement = bernoulli.rvs(p, size=nr_steps)
        position = 0
        for step in movement:
            position +=2 * step - 1
            position = position % n

        step_list.append(int (position))

    theoretical_prob = n * [0]
    for k in range(nr_steps + 1):
        theoretical_prob[(2*k - nr_steps) % n] += binom.pmf(k ,nr_steps, p)

    bin_edges = [k + 0.5 for k in range(-1,n)]
    hist(step_list, bin_edges, density=True, rwidth=0.9, color='green', edgecolor='black', alpha=0.5,
         label='relative frequencies')

    bar(range(0, n), theoretical_prob, width=0.85, color='red', edgecolor='black', alpha=0.6,
        label='probabilities')

    legend(loc='lower left')
    grid()
    show()

#a)
#movementSim(1000, 0.5)

#b)
#histogram_line(10, 0.5)

#c)
histogram_circle(40, 0.5, 5)