# HyperLogLog

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



