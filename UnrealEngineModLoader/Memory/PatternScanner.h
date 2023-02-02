#pragma once
#include "Pattern.h"
#include <Log/Log.h>
#include <functional>
#include <span>

namespace PatternScanner
{

static Pattern Scan(const std::string &PatternString, int MaxAttempts = 30)
{
    for (int i = 0; i < MaxAttempts; ++i)
    {
        Pattern Found(PatternString);
        Found.Find();
        if (Found.HasMatches())
        {
            return Found;
        }

        if (i != 0)
        {
            LOG_INFO("Scan attempt {}/{}", i, MaxAttempts);
        }
    }

    return Pattern(PatternString);
}

template <typename T, size_t N>
static T Scan(const std::span<std::string, N> &PatternList, std::function<T(size_t, Pattern &)> OnFound,
              int MaxAttempts = 30)
{
    for (int i = 0; i < MaxAttempts; ++i)
    {
        for (size_t PatternIndex = 0; PatternIndex < PatternList.size(); PatternIndex++)
        {
            const auto &PatternString = PatternList[PatternIndex];

            Pattern Found(PatternString);
            Found.Find();

            if (Found.HasMatches())
            {
                return OnFound(PatternIndex, Found);
            }
        }

        if (i != 0)
        {
            LOG_INFO("Scan Attempt {}/{}", i, MaxAttempts);
        }
    }

    return T{};
}

} // namespace PatternScanner
