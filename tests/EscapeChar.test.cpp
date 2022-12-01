/**
 * @file EscapeChar.test.cpp
 * @author Adrian Szczepanski
 * @date 11-08-2021
 * @brief 
 * @details
 */

#include <libescchar/EscapeChar.hpp>

#include <CppUTest/CommandLineTestRunner.h>

using namespace escchar;

TEST_GROUP(EscapeCharTest)
{
};

TEST(EscapeCharTest, AddEscapes_NoSpecialChars)
{  
    uint8_t expected[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09 };
    uint8_t text[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09 };
    uint8_t output[256];

    auto result = addEscapeChars({ output, 
        256, 
        text,
        sizeof(text), 
        0x1b, 
        { 0x7e } });

    CHECK_EQUAL(sizeof(expected), result);
    MEMCMP_EQUAL(expected, output, result);
}

TEST(EscapeCharTest, AddEscapes_EscapeChar)
{  
    uint8_t expected[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x1b, 0x1b, 0x06, 0x07, 0x08, 0x09 };
    uint8_t text[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x1b, 0x06, 0x07, 0x08, 0x09 };
    uint8_t output[256];

    auto result = addEscapeChars({ output, 
        256, 
        text, 
        sizeof(text), 
        0x1b, 
        { 0x7e } });

    CHECK_EQUAL(sizeof(expected), result);
    MEMCMP_EQUAL(expected, output, result);
}

TEST(EscapeCharTest, AddEscapes_EscapeCharSpecialChars)
{  
    uint8_t expected[] = { 0x1b, 0x00, 0x01, 0x02, 0x03, 0x04, 0x1b, 0x1b, 0x1b, 0x06, 0x07, 0x08, 0x09 };
    uint8_t text[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x1b, 0x06, 0x07, 0x08, 0x09 };
    uint8_t output[256];

    auto result = addEscapeChars({ output, 
        256, 
        text, 
        sizeof(text), 
        0x1b, 
        { 0x00, 0x06 } });

    CHECK_EQUAL(sizeof(expected), result);
    MEMCMP_EQUAL(expected, output, result);
}

TEST(EscapeCharTest, AddEscapes_MoreThanLimit)
{  
    uint8_t text[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x1b, 0x06, 0x07, 0x08, 0x09 };
    uint8_t output[256];

    auto result = addEscapeChars({ output, 
        sizeof(text), 
        text, 
        sizeof(text), 
        0x1b, 
        { 0x00, 0x06 } });

    CHECK_EQUAL(0, result);
}

TEST(EscapeCharTest, AddEscapes_LimitZero)
{  
    uint8_t expected[] = { 0x1b, 0x00, 0x01, 0x02, 0x03, 0x04, 0x1b, 0x1b, 0x1b, 0x06, 0x07, 0x08, 0x09 };
    uint8_t text[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x1b, 0x06, 0x07, 0x08, 0x09 };
    uint8_t output[256];

    auto result = addEscapeChars({ output, 
        0, 
        text, 
        sizeof(text), 
        0x1b, 
        { 0x00, 0x06 } });

    CHECK_EQUAL(0, result);
}

TEST(EscapeCharTest, AddEscapes_EscapeCharIsSpecial)
{  
    uint8_t expected[] = { 0x1b, 0x00, 0x01, 0x02, 0x03, 0x04, 0x1b, 0x1b, 0x1b, 0x06, 0x07, 0x08, 0x09 };
    uint8_t text[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x1b, 0x06, 0x07, 0x08, 0x09 };
    uint8_t output[256];

    auto result = addEscapeChars({ output, 
        256, 
        text, 
        sizeof(text), 
        0x1b, 
        { 0x00, 0x06, 0x1b } });

    CHECK_EQUAL(sizeof(expected), result);
    MEMCMP_EQUAL(expected, output, result);
}

TEST(EscapeCharTest, RemoveEscapes_NoSpecialChars)
{  
    uint8_t expected[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09 };
    uint8_t text[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09 };
    uint8_t output[256];

    auto result = removeEscapeChars({ output, 
        256, 
        text, 
        sizeof(text), 
        0x1b, 
        { 0x7e } });

    CHECK_EQUAL(sizeof(expected), result);
    MEMCMP_EQUAL(expected, output, result);
}

TEST(EscapeCharTest, RemoveEscapes_EscapeChar)
{  
    uint8_t expected[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x1b, 0x06, 0x07, 0x08, 0x09 };
    uint8_t text[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x1b, 0x1b, 0x06, 0x07, 0x08, 0x09 };
    uint8_t output[256];

    auto result = removeEscapeChars({ output, 
        256, 
        text, 
        sizeof(text), 
        0x1b, 
        { 0x7e } });

    CHECK_EQUAL(sizeof(expected), result);
    MEMCMP_EQUAL(expected, output, result);
}

TEST(EscapeCharTest, RemoveEscapes_EscapeChar_NoPadded)
{  
    uint8_t text[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x1b, 0x1b, 0x06, 0x07, 0x08, 0x09, 0x1b };
    uint8_t output[256];

    auto result = removeEscapeChars({ output, 
        256, 
        text, 
        sizeof(text), 
        0x1b, 
        { 0x7e } });

    CHECK_EQUAL(0, result);
}

TEST(EscapeCharTest, RemoveEscapes_SpecialChar_NoPadded)
{  
    uint8_t text[] = { 0x00, 0x01, 0x02, 0x7e, 0x04, 0x1b, 0x1b, 0x06, 0x07, 0x08, 0x09 };
    uint8_t output[256];

    auto result = removeEscapeChars({ output, 
        256, 
        text, 
        sizeof(text), 
        0x1b, 
        { 0x7e } });

    CHECK_EQUAL(0, result);
}

TEST(EscapeCharTest, RemoveEscapes_EscapeCharSpecialChars)
{  
    uint8_t expected[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x1b, 0x06, 0x07, 0x08, 0x09 };
    uint8_t text[] = { 0x1b, 0x00, 0x01, 0x02, 0x03, 0x04, 0x1b, 0x1b, 0x1b, 0x06, 0x07, 0x08, 0x09 };
    uint8_t output[256];

    auto result = removeEscapeChars({ output, 
        256, 
        text, 
        sizeof(text), 
        0x1b, 
        { 0x00, 0x06 } });

    CHECK_EQUAL(sizeof(expected), result);
    MEMCMP_EQUAL(expected, output, result);
}

TEST(EscapeCharTest, RemoveEscapes_MoreThanLimit)
{  
    uint8_t text[] = { 0x1b, 0x00, 0x01, 0x02, 0x03, 0x04, 0x1b, 0x06, 0x07, 0x08, 0x09 };
    uint8_t output[256];

    auto result = removeEscapeChars({ output, 
        8, 
        text, 
        sizeof(text), 
        0x1b, 
        { 0x00, 0x06 } });

    CHECK_EQUAL(0, result);
}

TEST(EscapeCharTest, RemoveEscapes_LimitZero)
{  
    uint8_t text[] = { 0x1b, 0x00, 0x01, 0x02, 0x03, 0x04, 0x1b, 0x1b, 0x1b, 0x06, 0x07, 0x08, 0x09 };
    uint8_t output[256];

    auto result = removeEscapeChars({ output, 
        0, 
        text, 
        sizeof(text), 
        0x1b, 
        { 0x00, 0x06 } });

    CHECK_EQUAL(0, result);
}