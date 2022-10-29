/*
 ============================================================================
 Name        : cvector.c
 Author      : Denis Colesnicov
 Version     : 1b0
 Copyright   : MIT
 Description : Ukazka pouziti cvector.
 ============================================================================
 */
/*
 * This file is a part of "cvector" dynamic container for C.
 */

/**
 * @file example
 * @brief Ukazka pouziti cvector.
 *
 * @version 1b0
 * @date 29.10.2022
 *
 * @author Denis Colesnicov <eugustus@gmail.com>
 *
 * @copyright MIT License
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "cvector/cvector.h"

/**
 * @var
 * @brief
 *
 */
cvector_s cvector;
/**
 * @struct struct_s
 * @brief Struktura k ulozeni v kontejneru.
 *
 */
struct struct_s {
	int a;
	int b;
};

/**
 * @fn bool checkEqualityInt(size_t, void*, const void*)
 * @brief Funkce pro hledani v kontejneru.
 * @details Porovna Data s necim hledanym.
 *
 * @param _index Index pozice prvku v kontaineru.
 * @param _data Ukazatel na ulozena data k porovnani
 * @param _needle Hledane neco.
 *
 * @return TRUE jestrli se shoduji, jinak FALSE
 */
bool checkEqualityInt(size_t _index, void *_data, const void *_needle) {
	struct struct_s *s = (struct struct_s*) _data;

	if (s->a == (int) _needle) {
		return true;
	}

	return false;
}

/**
 * @fn void freeInt(void*)
 * @brief Funkce pro uvolneni pameti po struktore 'struct_s'.
 *
 * @param _data Ukazatel na data k odstraneni.
 */
void freeInt(void *_data) {
	if (NULL != _data) {
		free(_data);
	}
}

int main(void) {

	cvector_init(&cvector);

	// naplnim kontejner
	for (int i = 0; i < 4; i++) {
		struct struct_s *s = malloc(sizeof(struct struct_s));
		s->a = i;
		s->b = i % 2;
		cvector_add(&cvector, s);
	}

	printf("Initialized vector. size(%d)\n", cvector_total(&cvector));
	for (int i = 0; i < cvector_total(&cvector); i++) {
		printf("value of index %d is %d:%d.\n", i,
				(int) ((struct struct_s*) cvector_get(&cvector, i))->a,
				(int) ((struct struct_s*) cvector_get(&cvector, i))->b);
	}

//	cvector_delete(&cvector, 2); // use only for non pointer values!
	cvector_delete_dealloc(&cvector, 2, freeInt); // use only for pointer values!

	printf("\nAfter delete 3rd element. size(%d)\n", cvector_total(&cvector));
	for (int i = 0; i < cvector_total(&cvector); i++) {
		printf("value of index %d is %d:%d.\n", i,
				(int) ((struct struct_s*) cvector_get(&cvector, i))->a,
				(int) ((struct struct_s*) cvector_get(&cvector, i))->b);
	}

	int my_key = 0;
	{
		int my_value = 0;
		printf("Enter key number:");
		scanf("%d", &my_key);
		printf("Enter value number:");
		scanf("%d", &my_value);

		struct struct_s *s = malloc(sizeof(struct struct_s));
		s->a = my_key;
		s->b = my_value;
		cvector_add(&cvector, s);
	}

	printf("\nAfter added 1 new element. size(%d)\n", cvector_total(&cvector));
	for (int i = 0; i < cvector_total(&cvector); i++) {
		printf("value of index %d is %d:%d.\n", i,
				(int) ((struct struct_s*) cvector_get(&cvector, i))->a,
				(int) ((struct struct_s*) cvector_get(&cvector, i))->b);
	}

	printf("\nSearch for last added element. size(%d)\n", cvector_total(&cvector));
	struct struct_s *s = cvector_search(&cvector, my_key, checkEqualityInt);
	printf("found item with key %d and value %d.\n", (int) s->a, (int) s->b);

	cvector_deinit_dealloc(&cvector, freeInt);

	return EXIT_SUCCESS;
}

///
///
///
///
///
///
///
///
///
///
///
///
///
///
///
///
///
///
///
///
///
///
///
///
///
///
///
///
///
///
///

