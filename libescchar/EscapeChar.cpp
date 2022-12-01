#include "EscapeChar.hpp"

using namespace Ekms308;
using namespace Ekms308::Frame;

static bool isSpecialChar(byte, const std::initializer_list<byte> &);

size_t Format::AddEscapeChars(byte *output,
                              size_t limit,
                              const ByteSpan &input,
                              byte escapeChar,
                              std::initializer_list<byte> specialChars)
{
    size_t index = 0;

    for(size_t i = 0; i < input.size; i++)
    {
        if(index == limit)
            return 0;

        if( input.data[i] == escapeChar ||
            isSpecialChar(input.data[i], specialChars) == true)
        {
            output[index++] = escapeChar;

            if(index == limit)
            return 0;
        }

        output[index++] = input.data[i];
    }

    return index;
}

size_t Format::RemoveEscapeChars(byte *output,
                                 size_t limit,
                                 const ByteSpan &input,
                                 byte escapeChar,
                                 std::initializer_list<byte> specialChars)
{
    size_t index = 0;
    bool wasEscapeChar = false;

    for(size_t i = 0; i < input.size; i++)
    {
        if(index == limit)
            return 0;

        if(isSpecialChar(input.data[i], specialChars) == true)
        {
            if(wasEscapeChar == false)
                return 0;
            
            output[index++] = input.data[i];
            wasEscapeChar = false;
        }
        else if(input.data[i] == escapeChar)
        {
            if(wasEscapeChar == false)
                wasEscapeChar = true;
            else
            {
                output[index++] = input.data[i];
                wasEscapeChar = false;
            }
        }
        else
            output[index++] = input.data[i];

    }

    if(wasEscapeChar == true)
        return 0;
    else
        return index;
}


static bool isSpecialChar(byte element, const std::initializer_list<byte> &specialChars)
{
    for(auto character : specialChars)
        if(character == element)
            return true;

    return false;
}