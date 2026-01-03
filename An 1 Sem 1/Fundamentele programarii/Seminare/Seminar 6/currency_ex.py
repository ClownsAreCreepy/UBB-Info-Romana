class Currency:
    # Read more about instance vs. class attributes
    # (and about some tricky behavior)
    # https://builtin.com/software-engineering-perspectives/python-attributes

    rata_conversie = {"RON": 0.2, "USD": 0.92, "EUR": 1.0}  # Class attribute

    def __init__(self, amount=0.0, currency_unit="EUR"):
        self.amount = float(amount)  # Instance attributes
        self.currency_unit = currency_unit  # Instance attributes

    @staticmethod
    def convert_to_EURO(amount, currency_unit):
        return amount * Currency.rata_conversie[currency_unit]

    def __add__(self, other):
        if type(other) == str:
            raise ValueError("Nu se poate face adunarea")

        if type(other) == int or type(other) == float:
            other = Currency(other)

        return Currency(Currency.convert_to_EURO(self.amount, self.currency_unit) +
                        other.convert_to_EURO(other.amount, other.currency_unit))

    def __radd__(self, other):
        return self.__add__(other)

    def __eq__(self, other):
        # usually, daca doua obiecte care se compara sunt de tipuri diferite,
        # nu pot fi egale, in consecinta returnam False
        # if type(other)!=type(self):
        #     return False

        #putems sa facem si ceva de genul acesta:
        if type(other) == int:
            other = Currency(other)

        return Currency.convert_to_EURO(self.amount, self.currency_unit) == Currency.convert_to_EURO(other.amount,
                                                                                                     other.currency_unit)

    @classmethod
    def from_string(cls, currency_str):
        # assume currency_str is of the form: 20EUR
        # numar de 2 cifre si valuta cunoscuta
        amount = float(currency_str[:2])
        currency_type = currency_str[2:]
        return cls(amount, currency_type)

    def __str__(self):
        return f"Suma de bani este {self.amount:.2f} iar valuta este {self.currency_unit}"


# Creare obiecte(instante) de tipul Currency

v1 = Currency(15, "EUR")
v2 = Currency(5, "RON")
v3 = v1 + v2

# ar trebui sa afiseze Money: 16.0 EUR
print(v3)

v4 = Currency(20)
v5 = v3 + v4

# ar trebui sa afiseze Money: 36.0 EUR
print(v5)

v6 = Currency()
v7 = v6 + v5

# ar trebui sa afiseze Money: 36.0 EUR
print(v7)

# ar trebui sa afiseze Money: 18 EUR (int sau float simplu sunt considerate ca amount, iar pentru ele currency_unit = EUR)
print(v1 + 3)

# se afiseaza "Nu se poate efectua adaugarea."
try:
    v8 = v1 + "20RON"
except ValueError as e:
    print(e)

# ar trebui sa afiseze Money: 25 EUR (int sau float simplu sunt considerate ca amount, iar pentru ele currency_unit = EUR)
print(10 + v1)

v9 = Currency(50, "RON")
v10 = Currency(10, "EUR")

# ar trebui sa se afiseze True
print (v9 == v10)
