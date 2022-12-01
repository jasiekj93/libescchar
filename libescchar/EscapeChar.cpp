#include "EscapeChar.hpp"

using namespace escchar;

static bool isSpecialChar(uint8_t, const std::initializer_list<uint8_t> &);

size_t escchar::addEscapeChars(const Configuration& config)
{
    size_t index = 0;

    for(size_t i = 0; i < config.inputSize; i++)
    {
        if(index == config.limit)
            return 0;

        if( config.input[i] == config.escapeChar ||
            isSpecialChar(config.input[i], config.specialChars) == true)
        {
            config.output[index++] = config.escapeChar;

            if(index == config.limit)
            return 0;
        }

        config.output[index++] = config.input[i];
    }

    return index;
}

size_t escchar::removeEscapeChars(const Configuration& config)
{
    size_t index = 0;
    bool wasEscapeChar = false;

    for(size_t i = 0; i < config.inputSize; i++)
    {
        if(index == config.limit)
            return 0;

        if(isSpecialChar(config.input[i], config.specialChars) == true)
        {
            if(wasEscapeChar == false)
                return 0;
            
            config.output[index++] = config.input[i];
            wasEscapeChar = false;
        }
        else if(config.input[i] == config.escapeChar)
        {
            if(wasEscapeChar == false)
                wasEscapeChar = true;
            else
            {
                config.output[index++] = config.input[i];
                wasEscapeChar = false;
            }
        }
        else
            config.output[index++] = config.input[i];

    }

    if(wasEscapeChar == true)
        return 0;
    else
        return index;
}


static bool isSpecialChar(uint8_t element, const std::initializer_list<uint8_t> &specialChars)
{
    for(auto character : specialChars)
        if(character == element)
            return true;

    return false;
}