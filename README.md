# HyperLogLog

## Descriere algoritm

O foarte buna explicatie a acestui algoritm se poate gasi [aici](https://ocw.cs.pub.ro/courses/sd-ca/teme/tema2-2020),
la sectiunea *3. HyperLogLog*. Pe scurt, scopul acestui algoritm este
ca avand un set foarte mare de numere intregi date ca input, sa determinam
intr-un timp scurt si cu o precizie suficient de buna, numarul elementelor
distincte.

## Continut repo

Fisierele sursa sunt reprezentate de *hll.c* si *hll.h*, iar folderul
*tests_hll* contine 5 fisiere de test.

## Executie program

Este suficient sa compilam codul folosind comanda **make**, iar ulterior
putem rula dupa modelul **./hll tests_hll/test*number*.text**, unde number
reprezinta numarul testului curent.

## Rezultate obtinute

In urma rularii aplicatiei, obtin urmatoarele rezultate:

* test0.txt - 9 627 raspuns obtinut, 10 000 fiind cel corect;
* test1.txt - 13 998 raspuns obtinut, 15 000 fiind cel corect;
* test2.txt - 18 772 raspuns obtinut, 20 000 fiind cel corect;
* test3.txt si test4.txt - 22 583 raspunsuri obtinute, 25 000 fiind cele corecte.

Se remarca o eroare relativa de sub **10%**, ceea ce se justifica datorita
timpului de executie semnificativ mai redus.

## Explicatii cod

Pentru fiecare numar citit din fisier, folosesc functia put, astfel.
Calculez hash-ul acestuia, folosind o functie de hash. Din acest numar
obtinut, iau primii 20 de biti (am ales acest numar intrucat ofera o
predictie extrem de buna) care vor corespunde indicelui bucket-ului unde
voi stoca informatii despre numarul citit.

Pentru fiecare indice, folosesc functia count_zeros, care imi calculeaza
numarul de 0-uri initiale (care se afla dupa bitii indicelui) in modul
urmator:

Construiesc numarul *padding_index*, care imi umple index-ul cu 0-uri,
astfel incat hash-ul si padding-ul sa aiba acelasi numar de biti. Caut
partea comuna dintre padding si hash, eliminand cate un bit de la sfarsit.
Aceasta parte comuna, este reprezentata de bitii index-ului la care se
adauga si primele 0-uri de dupa (0-urile initiale din hash), caci se afla
si in hash si in padding (padding avand doar 0-uri pe pozitiile finale).
Numarul de 0-uri va fi diferenta dintre numarul de biti ai partii comune
si numarul de biti din index, pe care o calculez cu functia count_bits.

Avand aceste date, construiesc dictionarul si folosesc informatiile din el,
pentru a calcula cu formula finala rezultatul.



