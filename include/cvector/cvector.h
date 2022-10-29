/*
 * This file is a part of "cvector" dynamic container for C.
 */

/**
 * @file cvector.h
 * @brief Definice dynamickeho kontejneru pro ulozeni dat.
 *
 * @version 1b0
 * @date 29.10.2022
 *
 * @author Denis Colesnicov <eugustus@gmail.com>
 *
 * @copyright MIT License
 *
 * @details <i>Original: https://eddmann.com/posts/implementing-a-dynamic-vector-array-in-c/ and modified.</i>
 *
 */

#pragma once

#include "cvector/configs.h"
#include <stdbool.h>

/**
 * @fn void cvector_fn_dealloc(void* _item)
 * @brief Prototyp funkce pro uvolneni prostredku.
 *
 * @param _item Ukazatel na data k uvolneni
 *
 * @fn void (*cvector_fn_dealloc)(void*)
 * @brief Typ prototypu funkce pro uvolneni prostredku.
 */
typedef void (*cvector_fn_dealloc)(void*);

/**
 * @fn void cvector_fn_search(size_t _index, void *_data, const void *_needle)
 * @brief Prototyp funkce pro vyhledavani v kontejneru.
 *
 * @param _index Index prvku v kontejneru
 * @param _data	Ukazatel na data
 * @param _needle Ukazatel na hledana data
 *
 * @fn void (*cvector_fn_search)(size_t _index, void *_data, const void *_needle)
 * @brief Typ prototypu funkce pro vyhledavani v kontejneru.
 *
 */
typedef bool (*cvector_fn_search)(size_t _index, void *_data, const void *_needle);

/**
 * @struct cvector_
 * @brief Struktura pro praci s kontejnerem.
 *
 * @typedef cvector_ cvector_s
 * @brief Definice typu cvector.
 *
 */
typedef struct cvector_ {
	/**
	 * @var void **items
	 * @brief Pole ukazatelu na data.
	 */
	void **items;
	/**
	 * @var size_t capacity
	 * @brief Celkova 'jiz rezervovana' velikost kontejneru.
	 */
	size_t capacity;
	/**
	 * @var size_t total
	 * @brief Kolik prvku uz v kontejneru je ulozeno.
	 */
	size_t total;

} cvector_s;

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * @fn bool cvector_init(cvector_s*)
	 * @brief Inicializuje prostredky pro kontejner.
	 *
	 * @note Call only once.
	 *
	 * @see CONFIG_CVECTOR_INIT_CAPACITY
	 *
	 * @param v Ukazatel na kontejner.
	 *
	 * @return FALSE jestli neni dostatek volne pameti, jinak TRUE.
	 */
	bool cvector_init(cvector_s *v);

	/**
	 * @fn void cvector_deinit(cvector_s*)
	 * @brief Uvolni prostredky po kontejneru.
	 *
	 * @param v Ukazatel na kontejner
	 */
	void cvector_deinit(cvector_s *v);

	/**
	 * @fn void cvector_deinit_dealloc(cvector_s*, cvector_fn_dealloc)
	 * @brief Uvolni prostredky po kontejneru a zaroven zavola uzivatelskou
	 * 			funkci pro uvolneni prostredku. Tato funkce bude volana pro
	 * 			kazdou polozku zvlast. Takto: <code>fn_free(stored_item);</code>.
	 *
	 * @param v Ukazatel na kontejner.
	 * @param fn_free Funkce pro uvolneni prostredku po prvku, napr f-ce 'free()'.
	 */
	void cvector_deinit_dealloc(cvector_s *v, cvector_fn_dealloc fn_free);

	/**
	 * @fn int cvector_total(cvector_s*)
	 * @brief Vrati pocet ulozenych prvku.
	 *
	 * @param v Ukazatel na kontejner.
	 *
	 * @return Pocet ulozenych prvku.
	 */
	int cvector_total(cvector_s *v);

	/**
	 * @fn bool cvector_resize(cvector_s*, size_t)
	 * @brief Zvetsi velikost uloziste.
	 *
	 * @note Nove pozadovana velikost musi byt aspon o 1 vetsi nez soucasna!
	 *
	 * @see CONFIG_CVECTOR_INC_CAPACITY
	 *
	 * @param v Ukazatel na kontejner.
	 * @param capacity Nova velikost kontejneru.
	 *
	 * @return FALSE jestli neni dostatek volne pameti, jinak TRUE.
	 */
	bool cvector_resize(cvector_s *v, size_t capacity);

	/**
	 * @fn bool cvector_add(cvector_s*, const void*)
	 * @brief Prida prvek do kontejneru.
	 *
	 * @param v Ukazatel na kontejner.
	 * @param item Prvek ke vlozeni.
	 *
	 * @return FALSE jestli neni dostatek volne pameti, jinak TRUE.
	 */
	bool cvector_add(cvector_s *v, const void *item);

	/**
	 * @fn bool cvector_set(cvector_s*, int, void*)
	 * @brief Vlozi prvek do kontejneru na zadany index.
	 *
	 * @note Index prvku musi byt v mezich '0' <= index < 'cvector_total()'!
	 *
	 * @param v Ukazatel na kontejner.
	 * @param index Index, kam se ma vlozit prvek.
	 * @param item Prvek ke vlozeni.
	 *
	 * @return FALSE jestli index je mimo rozsah, jinak TRUE.
	 */
	bool cvector_set(cvector_s *v, int index, void *item);

	/**
	 * @fn void* cvector_get(cvector_s*, int)
	 * @brief Vrati prvek ze zadane pozice.
	 *
	 * @note Index prvku musi byt v mezich '0' <= index < 'cvector_total()'!
	 *
	 * @param v Ukazatel na kontejner.
	 * @param index index Index pozice na ktere se prvek nachazi.
	 *
	 * @return Prvek ze zadane pozice, jestli nalezen, jinak NULL.
	 */
	void* cvector_get(cvector_s *v, int index);

	/**
	 * @fn void* cvector_search(cvector_s*, const void*, cvector_fn_search)
	 * @brief
	 *
	 * @param v Ukazatel na kontejner.
	 * @param _needle Hledane neco.
	 * @param _combain Funkce ktera pomuze s porovnavanim.
	 * @details Param _combain musi byt definovana uzivatelem.
	 * @see cvector_fn_search
	 *
	 * @return Ukazatel na data nebo NULL jestli nenalezeno.
	 */
	void* cvector_search(cvector_s *v, const void *_needle, cvector_fn_search _combain);

	/**
	 * @fn bool cvector_delete(cvector_s*, int)
	 * @brief Odstrani prvek z kontejneru.
	 *
	 * @param v Ukazatel na kontejner.
	 * @param index Index pozice na ktere se prvek nachazi.
	 *
	 * @return FALSE jestli neni dostatek volne pameti, jinak TRUE.
	 */
	bool cvector_delete(cvector_s *v, int index);

	/**
	 * @fn bool cvector_delete_dealloc(cvector_s*, int, cvector_fn_dealloc)
	 * @brief Odstrani prvek z kontejneru a zaroven zavola uzivatelskou
	 * 			funkci pro uvolneni prostredku.
	 *
	 * @param v Ukazatel na kontejner.
	 * @param index Index pozice na ktere se prvek nachazi.
	 * @param fn_free Funkce pro uvolneni prostredku po prvku, napr f-ce 'free()'.
	 *
	 * @return FALSE jestli neni dostatek volne pameti, jinak TRUE.
	 */
	bool cvector_delete_dealloc(cvector_s *v, int index, cvector_fn_dealloc fn_free);

#ifdef __cplusplus
}
#endif

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
