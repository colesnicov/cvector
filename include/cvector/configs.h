/*
 * This file is a part of "cvector" dynamic container for C.
 */

/**
 * @file configs.h
 * @brief Uzivatelske nastaveni.
 *
 * @version 1b0
 * @date 29.10.2022
 *
 * @author Denis Colesnicov <eugustus@gmail.com>
 *
 * @copyright MIT License
 *
 */

#pragma once

#include <assert.h>

/**
 * @def CVECTOR_ASSERT
 * @brief Assert funkce pro kontrolu stavu parseru.
 *
 * @note Kdyz neni treba, CC_ASSERT(expr) nahradit za (0)..
 *
 */
#define CVECTOR_ASSERT(expr)	assert(expr)
/**
 * @def CVECTOR_DEBUG
 * @brief Vypisovat dodatecne informace?
 *
 */
#ifdef CONFIG_CVECTOR_DEBUG

#define CVECTOR_DEBUG		CONFIG_CVECTOR_DEBUG

#else

#define CVECTOR_DEBUG		1

#endif

/**
 * @def CVECTOR_INC_CAPACITY
 * @brief O kolik navysovat kapacitu kontejneru?
 *
 * @see CVECTOR_INC_OPERATOR
 *
 */
#ifdef CONFIG_CVECTOR_INC_CAPACITY

#define CVECTOR_INC_CAPACITY	CONFIG_CVECTOR_INC_CAPACITY

#else

#define CVECTOR_INC_CAPACITY	2

#endif

/**
 * @def CVECTOR_INIT_CAPACITY
 * @brief Vychozi velikost kontejneru.
 *
 */
#ifdef CONFIG_CVECTOR_INIT_CAPACITY

#define CVECTOR_INIT_CAPACITY	CONFIG_CVECTOR_INIT_CAPACITY

#else

#define CVECTOR_INIT_CAPACITY	2

#endif

#ifdef CONFIG_IDF_TARGET_ESP8266

#include <freertos/FreeRTOS.h>
#include <freertos/private/portable.h>

/**
 * @def CVECTOR_MALLOC
 * @brief Makro pro alokaci nove pameti.
 *
 */
#define CVECTOR_MALLOC(s)		pvPortMalloc((s))

/**
 * @def CVECTOR_REALLOC
 * @brief  Makro pro alokaci dodatecne pameti.
 *
 */
#define CVECTOR_REALLOC(p, s)	pvPortRealloc((p),(s))

/**
 * @def CVECTOR_FREE
 * @brief Makro pro uvolneni pameti.
 *
 */
#define CVECTOR_FREE(p)		vPortFree((p))

#else

#include <malloc.h>

/**
 * @def CVECTOR_MALLOC
 * @brief Makro pro alokaci nove pameti.
 *
 */
#define CVECTOR_MALLOC(s)		malloc((s))

/**
 * @def CVECTOR_REALLOC
 * @brief  Makro pro alokaci dodatecne pameti.
 *
 */
#define CVECTOR_REALLOC(p, s)	realloc((p),(s))

/**
 * @def CVECTOR_FREE
 * @brief Makro pro uvolneni pameti.
 *
 */
#define CVECTOR_FREE(p)		free((p))

#endif

#ifdef CONFIG_IDF_TARGET_ESP8266

#include <esp_log.h>

/**
 * @def CVECTOR_PRINT
 * @brief Funkce pro vypis do konzole.
 *
 */
#define CVECTOR_PRINT(...)	ESP_LOGI(CC_LOG_TAG, __VA_ARGS__)

#else

#include <stdio.h>

/**
 * @def CVECTOR_PRINT
 * @brief Funkce pro vypis do konzole.
 *
 */
#define CVECTOR_PRINT(...)	printf(__VA_ARGS__)

#endif

