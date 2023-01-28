#pragma once
#include <Windows.h>
#include <cstdint>
#include <string>
#include <tuple>
#include <vector>

class ExecutableMeta
{
  public:
    ExecutableMeta();

    inline uintptr_t Begin() const
    {
        return m_Begin;
    }
    inline uintptr_t End() const
    {
        return m_End;
    }

  private:
    uintptr_t m_Begin;
    uintptr_t m_End;
    HANDLE m_Process;
};

class PatternMatch
{
  public:
    inline PatternMatch(void *Ptr) : m_Ptr(Ptr)
    {
    }

    template <typename T> T *Get(int Offset = 0)
    {
        if (m_Ptr == nullptr)
            return nullptr;

        uint8_t *Ptr = reinterpret_cast<uint8_t *>(m_Ptr);
        return reinterpret_cast<T *>(Ptr + Offset);
    }

  private:
    void *m_Ptr;
};

class Pattern
{
  public:
    Pattern(const std::string &Pattern) : Pattern(Pattern.c_str(), Pattern.size())
    {
    }

    template <size_t Len> Pattern(const char (&Pattern)[Len]) : Pattern(Pattern, Len)
    {
    }

    Pattern(const char *Pattern, size_t Len)
    {
        size_t j = 0;
        for (size_t i = 0; i < Len; ++i)
        {
            const char c = Pattern[i];

            if (c == ' ')
            {
                continue;
            }
            else if (c == '?')
            {
                m_Data[j] = '\x00';
                m_Mask[j] = '?';
                j++;
            }
            else if (c >= 'a' && c <= 'f' || c >= 'A' && c <= 'F' || c >= '0' && c <= '9')
            {
                m_Data[j] = (FromHex(c) << 4) | FromHex(Pattern[i + 1]);
                m_Mask[j] = 'x';
                i++;
                j++;
            }
        }
        m_Len = j;
    }

    inline PatternMatch &Get(int Index)
    {
        if (!m_Matched)
        {
            Find(INT_MAX);
        }

        if (m_Matches.size() == 0)
        {
            m_Matches.emplace_back(nullptr);
            return m_Matches[0];
        }

        return m_Matches[Index];
    }

    void Find(int MaxMatches);

  private:
    bool ConsiderMatch(const uint8_t *Start);

  private:
    static uint8_t FromHex(const char c)
    {
        if (c >= 'a' && c <= 'f')
            return c - 'a' + 10;
        if (c >= 'A' && c <= 'F')
            return c - 'A' + 10;
        if (c >= '0' && c <= '9')
            return c - '0';

        return 0;
    }

  private:
    size_t m_Len = 0;
    uint8_t m_Data[4096] = {0};
    uint8_t m_Mask[4096] = {0};

    bool m_Matched = false;
    std::vector<PatternMatch> m_Matches{};
};