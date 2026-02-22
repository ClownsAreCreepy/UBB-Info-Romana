from scipy.stats import hypergeom, geom

def lotto(nr_sims):
    prob = 0
    for k in range(3, 6):
        prob_winning_ticket = hypergeom.pmf(k, 49, 6, 6)
        prob += prob_winning_ticket

    # sau putem direct: prob = 1 - hypergeom.cdf(2, 49, 6, 6)

    extractions = geom.rvs(prob, size = nr_sims)
    print("Lista nr bilete: ", extractions)

    nr_wins = 0
    for ex in extractions:
        if ex >= 10:
            nr_wins += 1

    print("Approximate")
    print(nr_wins / nr_sims)

    prob_b = 0
    for k in range(0, 10):
        prob_b += geom.pmf(k, prob)

    # sau putem direct prob_b = geom.cdf(10, prob)

    print("Theoretical")
    print(1 - prob_b)


lotto(100)