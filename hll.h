/* Copyright [2020] IGNAT Andrei-Horia 314CA */

#ifndef _HLL_H_
#define _HLL_H_

#define FIRST_BYTES 11
#define HMAX 1 << FIRST_BYTES

struct hashtable
{
	int *buckets;
	int hmax;
	int size;
	unsigned int (*hash_function)(void*);
};

/* functie de hash pentru int */
unsigned int hash_function_int(void *a);

/* intializez dictionarul */
void init_ht(struct hashtable *ht);

/* numar cati biti are un numar n */
int count_bits(int n);

/* pentru un numar n dat ca parametru calculez numarul
 * de biti 0 initiali din a doua parte a hash-ului */
int count_zeros(struct hashtable *ht, int n);

/* introduc date in dictionar folosind linear probing */
void put(struct hashtable *ht, int key);

/* construiesc dictionarul cu datele dintr-un fisier */
void make_hashtable(struct hashtable *ht, FILE *f);

/* calculez numarul de bucket-uri folosite */
void size(struct hashtable *ht);

/* calculez factorul de atenuare alfa_m */
float alfa(int m);

/* folosesc formula algoritmului pentru
 * a vedea cate numere diferite exista */
int count(struct hashtable *ht);

#endif  // _HLL_H_
