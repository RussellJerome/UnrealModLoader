#include "Pattern.h"
#include <Windows.h>
#include <intrin.h>

ExecutableMeta::ExecutableMeta()
{
    HANDLE Module = GetModuleHandle(NULL);

    const IMAGE_DOS_HEADER *DosHeader = reinterpret_cast<const IMAGE_DOS_HEADER *>(Module);
    const IMAGE_NT_HEADERS *NtHeader = reinterpret_cast<const IMAGE_NT_HEADERS64 *>(
        reinterpret_cast<const uint8_t *>(DosHeader) + DosHeader->e_lfanew);

    m_Begin = reinterpret_cast<uintptr_t>(Module);
    m_End = m_Begin + NtHeader->OptionalHeader.SizeOfCode;
}

bool Pattern::ConsiderMatch(const uint8_t *Start)
{
    for (size_t i = 0; i < m_Len; ++i)
    {
        if (m_Mask[i] == '?')
            continue;

        if (m_Data[i] != Start[i])
            return false;
    }

    return true;
}

void Pattern::Find(int MaxMatches)
{
    int CpuId[4];
    __cpuid(CpuId, 0);

    bool Sse42 = false;

    if (m_Len <= 16 && CpuId[0] >= 1)
    {
        __cpuidex(CpuId, 1, 0);
        Sse42 = (CpuId[2] & (1 << 20)) == 1;
    }

    ExecutableMeta Meta;

    if (!Sse42)
    {
        for (uintptr_t i = Meta.Begin(); i <= Meta.End(); ++i)
        {
            if (ConsiderMatch(reinterpret_cast<const uint8_t *>(i)))
            {
                m_Matches.emplace_back(reinterpret_cast<void *>(i));
            }
        }
    }
    else
    {
        __declspec(align(16)) uint8_t DesiredMask[16] = {0};

        for (size_t i = 0; i < m_Len; i++)
        {
            DesiredMask[i / 8] |= ((m_Mask[i] == '?') ? 0 : 1) << (i % 8);
        }

        __m128i Mask = _mm_load_si128(reinterpret_cast<const __m128i *>(DesiredMask));
        __m128i Comparand = _mm_loadu_si128(reinterpret_cast<const __m128i *>(m_Data));

        for (uintptr_t i = Meta.Begin(); i <= Meta.End(); ++i)
        {
            __m128i Value = _mm_loadu_si128(reinterpret_cast<const __m128i *>(i));
            __m128i Result = _mm_cmpestrm(Value, 16, Comparand, m_Len, _SIDD_CMP_EQUAL_EACH);

            // As the result can match more bits than the mask contains
            __m128i Matches = _mm_and_si128(Mask, Result);
            __m128i Equivalence = _mm_xor_si128(Mask, Matches);

            if (_mm_test_all_zeros(Equivalence, Equivalence))
            {
                m_Matches.emplace_back(reinterpret_cast<void *>(i));
            }
        }
    }

    m_Matched = true;
}