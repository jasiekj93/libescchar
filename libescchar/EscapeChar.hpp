#pragma once

/**
 * @file EscapeChar.hpp
 * @author Adrian Szczepanski
 * @date 17-08-2021
 * @brief 
 * @details
 */

#include <utility>
#include <cstddef>
#include <cstdint>

namespace escchar
{
    /**
     * @brief Struktura konfiguracyjna do funkcji. 
     * 
     */
    struct Configuration
    {
        uint8_t* output; /**< bufor wyjściowy dla danych */
        size_t limit; /**< maksymalny rozmiar bufora wyjściowego */
        const uint8_t* input; /**< dane wejściowe */
        size_t inputSize; /**< rozmiar danych wejściowych */
        uint8_t escapeChar; /**< znak escape */
        std::initializer_list<uint8_t> specialChars; /**< zbiór znaków specjalnych, przed którymi należy umieścić znak ucieczki */
    };

    /**
     * @brief Dodaje znaki ecape do danych wejściowych.
     * 
     * @return rozmiar bufora wyjściowego po dodaniu znaków esape.
     */
    size_t addEscapeChars(const Configuration&);

    /**
     * @brief Usuwa znaki escape z danych wejściowych. 
     * 
     * @return rozmiar bufora wyjściowego po usunięciu znaków escape. 
     */
    size_t removeEscapeChars(const Configuration&);
}