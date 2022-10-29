/*
 * This file is a part of "cvector" dynamic container for C.
 */

/**
 * @file cvector.c
 * @brief Implementace dynamickeho kontejneru pro ulozeni dat
 *
 * @version 1b0
 * @date 29.10.2022
 *
 * @author Denis Colesnicov <eugustus@gmail.com>
 *
 * @copyright MIT License
 *
 * @details Original: https://eddmann.com/posts/implementing-a-dynamic-vector-array-in-c/ and modified
 */

#include "cvector/configs.h"
#include "cvector/cvector.h"

#include <stdlib.h>
#include <stdbool.h>

#if 1

#define S(x) #x
#define SS(x) S(x)
#define CC_LOG_TAG __FILE__ " : " SS(__LINE__)

#else

#define	CC_LOG_TAG	__FUNCTION__

#endif

bool cvector_init(cvector_s *v) {
	CVECTOR_ASSERT(v->items == NULL && "VECTOR ALREADY INITIALIZED!");

	v->items = CVECTOR_MALLOC(sizeof(void*) * CVECTOR_INIT_CAPACITY);
	if (!v->items) {
#if CVECTOR_DEBUG
#if CVECTOR_DEBUG
		CVECTOR_PRINT("Can't init cvector. No memmory.");
#endif
#endif
		return false;
	}
	v->capacity = CVECTOR_INIT_CAPACITY;
	v->total = 0;

	return true;
}

int cvector_total(cvector_s *v) {
	CVECTOR_ASSERT(v->items != NULL && "VECTOR NOT INITIALIZED!");

	return v->total;
}

bool cvector_resize(cvector_s *v, size_t capacity) {
	CVECTOR_ASSERT(v->items != NULL && "VECTOR NOT INITIALIZED!");

#if CONFIG_CVECTOR_DEBUG_ON & 1
	printf("cvector_resize: %d to %d\n", v->capacity, capacity);
#endif

	void **items = CVECTOR_REALLOC(v->items, sizeof(void*) * capacity);
	if (!items) {
#if CVECTOR_DEBUG
#if CVECTOR_DEBUG
		CVECTOR_PRINT("Can't resize cvector. No memmory.");
#endif
#endif
		return false;
	}

	v->items = items;
	v->capacity = capacity;

	return true;
}

bool cvector_add(cvector_s *v, const void *item) {
	CVECTOR_ASSERT(v->items != NULL && "VECTOR NOT INITIALIZED!");

	if (v->capacity == v->total) {
		if (!cvector_resize(v, v->capacity + CVECTOR_INC_CAPACITY)) {
			return false;
		}
	}
	v->items[v->total++] = (void*) item;

	return true;
}

bool cvector_set(cvector_s *v, int index, void *item) {
	CVECTOR_ASSERT(v->items != NULL && "VECTOR NOT INITIALIZED!");

	if (index >= 0 && index < v->total) {
		v->items[index] = item;
		return true;
	}

	return false;
}

void* cvector_get(cvector_s *v, int index) {
	CVECTOR_ASSERT(v->items != NULL && "VECTOR NOT INITIALIZED!");

	if (index >= 0 && index < v->total) {
		return v->items[index];
	}

	return NULL;
}

void* cvector_search(cvector_s *_v, const void *_needle, cvector_fn_search _combain) {
	CVECTOR_ASSERT(_v->items != NULL && "VECTOR NOT INITIALIZED!");

	for (size_t i = 0; i < _v->total; i++) {
		if (true == _combain(i, _v->items[i], _needle)) {
			return _v->items[i];
		}
	}

	return NULL;
}

bool cvector_delete(cvector_s *v, int index) {
	CVECTOR_ASSERT(v->items != NULL && "VECTOR NOT INITIALIZED!");

	if (index < 0 || index >= v->total) {
		return false;
	}

	v->items[index] = NULL;

	for (int i = index; i < v->total - 1; i++) {
		v->items[i] = v->items[i + 1];
		v->items[i + 1] = NULL;
	}

	v->total--;

	if (v->total > 0 && v->total == v->capacity - (CVECTOR_INC_CAPACITY * 2)) {
		return cvector_resize(v, v->capacity - CVECTOR_INC_CAPACITY);
	}

	return true;
}

bool cvector_delete_dealloc(cvector_s *v, int index, cvector_fn_dealloc fn_free) {
	CVECTOR_ASSERT(v->items != NULL && "VECTOR NOT INITIALIZED!");

	if (index < 0 || index >= v->total) {
#if CVECTOR_DEBUG
#if CVECTOR_DEBUG
		CVECTOR_PRINT("Can't dealloc cvector item. Out of range.");
#endif
#endif
		return false;
	}

	fn_free(v->items[index]);
	v->items[index] = NULL;

	for (int i = index; i < v->total - 1; i++) {
		v->items[i] = v->items[i + 1];
		v->items[i + 1] = NULL;
	}

	v->total--;

	if (v->total > 0 && v->total == v->capacity - (CVECTOR_INC_CAPACITY * 2)) {
		return cvector_resize(v, v->capacity - CVECTOR_INC_CAPACITY);
	}

	return true;
}

void cvector_deinit(cvector_s *v) {
	CVECTOR_ASSERT(v->items != NULL && "VECTOR NOT INITIALIZED!");

	CVECTOR_FREE(v->items);
	v->items = NULL;
}

void cvector_deinit_dealloc(cvector_s *v, cvector_fn_dealloc fn_free) {
	CVECTOR_ASSERT(v->items != NULL && "VECTOR NOT INITIALIZED!");

	for (int index = 0; index < v->total; index++) {
		fn_free(v->items[index]);
		v->items[index] = NULL;
	}

	CVECTOR_FREE(v->items);
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
