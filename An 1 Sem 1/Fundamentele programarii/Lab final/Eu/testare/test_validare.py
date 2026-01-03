from Domain.Inchirieri import Inchirieri
from Validare.validare import *
import unittest

class TestValidare(unittest.TestCase):

    def test_validare_film(self):
        film_valid = Film(1, "Se7en", "Thriller", "Film fain")
        valid = validare_film()

        valid.validare_film(film_valid)

        film_invalid =Film(-1, "", "", "")

        with self.assertRaises(ValueError) as context:
            valid.validare_film(film_invalid)

        self.assertEqual(
            str(context.exception),
            "id-ul introdus nu poate fi negativ \nnumele filmului nu poate sa fie vid \ngenul filmului nu poate sa fie vid \ndescrierea filmului nu poate sa fie vida \n")

    def test_validare_client(self):
        client_valid = Client(1, "Popescu", "5041118082209")
        client_invalid= Client(-1, "", "504111808220")
        valid = validare_client()

        valid.validare_client(client_valid)

        with self.assertRaises(ValueError) as context:
            valid.validare_client(client_invalid)

        self.assertEqual(
            str(context.exception),
            "id-ul introdus nu poate fi negativ \nnumele clientului nu poate fi negativ \ncnp-ul clientului a fost introdus gresit \n")

    def test_validare_inchiriere(self):
        inchiriere_valida = Inchirieri(1,5)
        inchiriere_invalida = Inchirieri(-1,-5)
        valid = validare_inchiriere()

        valid.validare_inchiriere(inchiriere_valida)

        with self.assertRaises(ValidationError) as context:
            valid.validare_inchiriere(inchiriere_invalida)

        self.assertEqual(
            str(context.exception),
            "id-ul clientului nu poate fi negativ \nid-ul filmului nu poate fi negativ \n")

    def test_validare_id(self):
        valid=validare_film()

        id_valid=1
        id_invalid=-3

        valid.validare_id(id_valid)

        with self.assertRaises(ValueError) as context:
            valid.validare_id(id_invalid)

        self.assertEqual(
            str(context.exception),
            "id-ul introdus nu poate fi negativ \n")

    def test_validare_nume(self):
        valid=validare_film()

        nume_valid="Zaza"
        nume_invalid=""

        valid.validare_nume(nume_valid)

        with self.assertRaises(ValueError) as context:
            valid.validare_nume(nume_invalid)

        self.assertEqual(
            str(context.exception),
            "numele filmului nu poate sa fie vid \n")

        valid = validare_client()

        nume_valid = "Zaza"
        nume_invalid = ""

        valid.validare_nume(nume_valid)

        with self.assertRaises(ValueError) as context:
            valid.validare_nume(nume_invalid)

        self.assertEqual(
            str(context.exception),
            "numele clientului nu poate sa fie vid \n")


if __name__ == '__main__':
    unittest.main()