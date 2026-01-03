#!/bin/bash

# Verificam sa fi primit un argument
if [[ $# -ne 1 ]];then
	echo "Usage: $0 <arg>"
	exit 1
fi

# Verificam ca argumentul sa fie un fisier valid
if ! [[ -f $1 ]]; then
	echo "Argument must be a valid file!"
	exit 2
fi

# Salvam fisierul intr-o variabila
file="$1"

# 1. Sa se afiseze continutul unui fisier de tip text in ordinea inversa a liniilor
# Metoda 1: folosim tac
echo "Fisierul invers:"
tac "$file"

# Metoda 2: folosim awk
# NR este nr liniei din text
# Deci practic salvam liniile intr-un array, apoi trecem prin el invers la final
#awk '{ lines[NR] = $0 } END { 
#			for (i = NR; i > 0; i--) 
#				print lines[i] 
#			}' "$file"

echo ""
echo "-----------------------------------------------------------------------------------------------"
# 2. Sa se determine si sa afiseze linia dintr-un fisier care contine cele mai multe caractere
# Pregatim maximul si linia cea mai lunga (ne ajuta doar la metoda 1)
max=0
longest=""
echo "Linia cea mai lunga:"

# Metida 1: While loop
# While loop-ul astfel merge prin fiecare linie din fisier, unde for mere prin fiecare cuvant
while read -r line; do
	
	# Putem folosi ori ${#line}, care determina lungimea, ori echo | wc -c, care face la fel
	len=${#line}
	#len=$(echo "$line" | wc -c)
	
	# Daca gasim o lungime mai mare, o modificam
	if (( len > max )); then
		max=$len
		longest="$line"
	fi
done < "$file"

echo "$longest"

# Metoda 2: awk
# Ok deci awk are un length built in care arata lungimea liniei
# Pe parcursul awk-ului aflam lungimea maxima
# La final tiparim linia cea mai lunga
#awk 'length > max { max = length; longest = $0} END {print longest }' "$file"

# Metoda 3: awk + sort
# Deci aratam lungimea unei linii urmata de linia intreaga cu awk
# sort -r si head pentru a lua linia cu cele mai multe cuvinte
# cut pentru a lua tot in afara de primul field (lungimea)
#awk '{print length, $0}' "$file" | sort -rn | head -n 1 | cut -d ' ' -f2-

echo ""
echo "-----------------------------------------------------------------------------------------------"
# 3. Sa se calculeze si sa afiseze numarul de vocale si numarul de consoane dintr-un fisier
# Metoda 1: grep -o
# Folosim -i pentru a ignora case-ul si dupaia un wc -l, deoarece grep -o returneaza o linie/match
vowels=$(grep -o -i '[aeiou]' "$file" | wc -l)
consonants=$(grep -o -i '[b-df-hj-np-tv-z]' "$file" |wc -l)

echo "Vocale: $vowels"
echo "Consoane: $consonants"

# Metoda 2: awk
# Merem cu un for pentru fiecare linie
# Verificam fiecare caracter din linie sa fie consoana sau vocala, si incrementam ce trebuie
#awk '
#{
#	for (i = 1; i <= length; i++){
#		c = tolower(substr($0, i, 1))
#		if (c ~ /[aeiou]/) vowels++
#		else if (c ~ /[a-z]/) consonants++
#	}
#}
#END {
#	print "Vocale:", vowels
#	print "Consoane:", consonants
#}' "$file"
#
# Metoda 3: sed + wc
# Stergem fiecare caracter care nu e consoane/vocale, apoi le numaram cu wc -c
# tr -d '\n' taie caracterul de newline, care nu este eliminat de sed, astfel avem contoare corecte
#echo "Vocale: $(sed 's/[^aeiouAEIOU]//g' "$file" | tr -d '\n' | wc -c)"
#echo "Consoane: $(sed 's/[^b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z]//g' "$file" | tr -d '\n' | wc -c)"

echo ""
echo "-----------------------------------------------------------------------------------------------"

# 4. Sa se afiseze liniile dintr-un fisier in care un cuvant se repeta de cel putin 2 ori
echo "Linii cu cuvinte care se repeta:"

# Metoda 1: awk cu array
# awk merge prin fiecare linie si coloana (NF)
# Tine minte de cate ori a aparut fiecare coloana (cuvant) intr-un contor
# Can acel contor ajunge la doi, printeaza linia
# if (seen[w]++) <=> if (seen[w] > 0) { .. } seen[w]++
# Folosim gsub pentru a elimina caracterele \r si \n din cuvinte din w (pentru ultima coloana) 
awk '
{
	delete seen
	for (i = 1; i <= NF; ++i){
		w = $i
		gsub(/\r|\n/, "", w)
		if (seen[w]++){
			print
			next
		}
	}
}' "$file"
#
# Metoda 2: awk cu 2 for-uri
# Facem un fel de selection sort pentru cuvinte
# Eliminam \n si \r si verificam daca sunt egale. Daca da, printam
#awk '
#{
#	for (i = 1; i < NF; ++i)
#		for (j = i+1; j <= NF; ++j)
#			{
#				gsub(/\r|\n/, "", $j);
#				gsub(/\r|\n/, "", $i);
#				if ($i == $j)
#					print
#			}
#}' "$file"
#
# Metoda 3: while + sort + grep
# Verificam pentru fiecare linie, cu while ( || [..] pentru ca while nu ia ultima linie (fara \n)
# tr inlocuieste fiecare spatiu cu un \n => un cuvant -> o line
# Le sortam si afisam alea care au duplicate (uniq -d)
# command1 && command2 <=> executa command2 DOAR DACA command1 reuseste (returneaza 1)
#while read -r line || [ -n "$line" ]; do
#	echo "$line" | tr '[:space:]' '\n' | sort | uniq -d | grep -q . && echo "$line"
#done < "$file"

echo ""
echo "-----------------------------------------------------------------------------------------------"

# 5. Sa se determine si sa afiseze numarul de numere valide si suma lor dintr-un fisier
# Metoda 1: awk
# Merem prin fiecare linie cu NF (fiecare cuvant)
# Verificam daca forma trunchiata (gsub) e numar valid (N*)
# Daca da, crestem contorul si adunam la suma
awk '
{
	for (i = 1; i <= NF; ++i){
		gsub(/\r|\n/, "", $i)
		if ($i ~ /^[1-9][0-9]*$/) {
			count++
			sum += $i
		}
	}
}
END {
	print "Numere:", count
	print "Suma:", sum
}' "$file"

# Nu am mai gasit o alta metoda care sa mearga 100%
