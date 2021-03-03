/* Copyright [2020] IGNAT Andrei-Horia 314CA */

#include <stdio.h>
#include <stdlib.h>

#include "hll.h"

unsigned int hash_function_int(void *a)
{
	unsigned int uint_a = *((unsigned int *)a);

	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = (uint_a >> 16u) ^ uint_a;
	
	return uint_a;
}

void init_ht(struct hashtable *ht)
{
	ht->hmax = HMAX;
	ht->size = 0;
	ht->hash_function = hash_function_int;
	ht->buckets = calloc(ht->hmax, sizeof(int));
}

int count_bits(int n)
{
	int count = 0;

	while(n > 0)
	{
		count++;
		n >>= 1;
	}

	return count;
}

int count_zeros(struct hashtable *ht, int n)
{
	unsigned int hash, index, padding_index;

	/* hash-ul lui n */
	hash = ht->hash_function(&n);
	/* indicele bucket-ului corespunzator lui n */
	index = hash >> (count_bits(hash) - FIRST_BYTES);
	/* pun biti de 0 la final indicelui index */
	padding_index = index << (count_bits(hash) - FIRST_BYTES);

	/* gasesc partea comuna din hash si padding_index;
	 * aceasta parte comuna va contine primii 11 biti care
	 * formeaza indicele si primii biti de 0 de dupa el */
	while(hash != padding_index)
	{
		hash >>= 1;
		padding_index >>= 1;
	}

	/* numarul de biti 0 initiali din hash, va fi diferenta dintre
	 * numarul de biti din padding si numarul de biti din index */
	return count_bits(padding_index) - count_bits(index);
}

void put(struct hashtable *ht, int key)
{
	int count;
	unsigned int hash, index;

	hash = ht->hash_function(&key);
	index = hash >> (count_bits(hash) - FIRST_BYTES);
	count = count_zeros(ht, key);

	/* daca numarul maxim de biti 0 initiali este mai mic decat
	 * noul numar de biti 0 initial, actualizez dictionarul */
	if(ht->buckets[index] < count)
		ht->buckets[index] = count;
}

void make_hashtable(struct hashtable *ht, FILE *f)
{
	int n;

	while(!feof(f))
	{
		fscanf(f, "%d ", &n);
		put(ht, n);
	}
}

void size(struct hashtable *ht)
{
	int i;
	
	for(i = 0; i < ht->hmax; i++)
		if(ht->buckets[i] != 0)
			ht->size++;
}

float alfa(int m)
{
	return 0.7413 / (1 + 1.079 / m);
}

int count_distinct(struct hashtable *ht)
{
	float sum;
	int i, count_numbers;

	/* calculez media datelor din dictionar */
	sum = 0;
	for(i = 0; i < ht->hmax; i++)
		if(ht->buckets[i] != 0)
			sum += (float) 1 / (1 << (ht->buckets[i] + 1));
	sum = 1 / sum;

	/* rezultatul final */
	count_numbers = (int) (alfa(ht->size) * ht->size * ht->size * sum);

	return count_numbers;
}

int main(int argc, char *argv[])
{
	struct hashtable *ht;
	FILE *f;

	/* aloc memorie si initializez dictionarul */
	ht = malloc(sizeof(struct hashtable));
	init_ht(ht);

	if(argc != 2)
	{
		fprintf(stderr, "Error: wrong number of parametres in command line\n");
		return -1;
	}

	if((f = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "Error: can't open input file: %s\n", argv[1]);
		return -1;
	}

	/* construiesc dictionarul si afisez numarul elementelor diferite */
	make_hashtable(ht, f);
	size(ht);
	printf("%d\n", count_distinct(ht));

	/* eliberez memoria */
	fclose(f);
	free(ht->buckets);
	free(ht);

	return 0;
}
