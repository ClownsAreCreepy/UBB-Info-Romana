from random import sample
from random import randint


def MontyHall_sim(change_door=False, nr_sim=1, show=False):
    count = 0
    for _ in range(nr_sim):
        arrangement = ['g', 'g', 'g']
        car, goat_1, goat_2 = sample([0, 1, 2], 3)
        arrangement[car] = 'c'

        init_choice = randint(0, 2)
        if init_choice == car:
            monty_choice = sample([goat_1, goat_2], 1).pop()
        elif init_choice == goat_1:
            monty_choice = goat_2
        else:
            monty_choice = goat_1

        if change_door:
            final_choice = ({0, 1, 2} - {init_choice, monty_choice}).pop()
        else:
            final_choice = init_choice

        if show:
            print("Initial arrangement: " + arrangement.__str__())

            previous = arrangement[init_choice]
            arrangement[init_choice] = "P"
            print("First choice: " + arrangement.__str__())

            arrangement[monty_choice] = "R"
            print("Revealed goat: " + arrangement.__str__())

            arrangement[init_choice] = previous
            arrangement[final_choice] = "P"
            print("Second choice: " + arrangement.__str__())

            print("Result: ", end='')
            if final_choice == car:
                print("SUCCESS!")
            else:
                print("FAIL!")

        result = final_choice == car
        count += result
    return count / nr_sim


prob = MontyHall_sim(change_door=True, nr_sim=1000, show=False)
print("Probability of winning  the car: ", prob)
