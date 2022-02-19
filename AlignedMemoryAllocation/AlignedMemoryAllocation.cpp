#include <iostream>

using namespace std;

struct SA
{
    long long ll0;
    long long ll1;
};

struct alignas(32) SB
{
    long long ll0;
    long long ll1;
};

struct SC
{
    SB stB0;
    SB stB1;
};

int main()
{
    wcout << L"sizeof(SA) : \t" << sizeof(SA) << endl;
    wcout << L"sizeof(SB) : \t" << sizeof(SB) << endl;
    wcout << L"sizeof(SC) : \t" << sizeof(SC) << endl;

    wcout << L"alignof(SA) : \t" << alignof(SA) << endl;
    wcout << L"alignof(SB) : \t" << alignof(SB) << endl;
    wcout << L"alignof(SC) : \t" << alignof(SC) << endl;

    SA* pA = new SA[3]();
    SB* pB = new SB[3]();
    SC* pC = new SC[3]();

    SC* pAlignedC = static_cast<SC*>(_aligned_malloc(sizeof(SC) * 3ULL, 64ULL));

    unsigned long long ullQuotient = 0ULL;
    unsigned long long ullRemainder = 0ULL;

    for (unsigned long long i = 0ULL; i < 3ULL; ++i)
    {
        ullQuotient = reinterpret_cast<unsigned long long>(&pA[i]) / 64ULL;
        ullRemainder = reinterpret_cast<unsigned long long>(&pA[i]) % 64ULL;

        wcout << L"SA[" << i << L"]\t\tAddress : \t" << &pA[i] << L"\tAddress / 64 : \t" << ullQuotient << L"\tAddress % 64 : \t" << ullRemainder << endl;
    }

    for (unsigned long long i = 0ULL; i < 3ULL; ++i)
    {
        ullQuotient = reinterpret_cast<unsigned long long>(&pB[i]) / 64ULL;
        ullRemainder = reinterpret_cast<unsigned long long>(&pB[i]) % 64ULL;

        wcout << L"SB[" << i << L"]\t\tAddress : \t" << &pB[i] << L"\tAddress / 64 : \t" << ullQuotient << L"\tAddress % 64 : \t" << ullRemainder << endl;
    }

    for (unsigned long long i = 0ULL; i < 3ULL; ++i)
    {
        ullQuotient = reinterpret_cast<unsigned long long>(&pC[i]) / 64ULL;
        ullRemainder = reinterpret_cast<unsigned long long>(&pC[i]) % 64ULL;

        wcout << L"SC[" << i << L"]\t\tAddress : \t" << &pC[i] << L"\tAddress / 64 : \t" << ullQuotient << L"\tAddress % 64 : \t" << ullRemainder << endl;
    }

    for (unsigned long long i = 0ULL; i < 3ULL; ++i)
    {
        ullQuotient = reinterpret_cast<unsigned long long>(&pAlignedC[i]) / 64ULL;
        ullRemainder = reinterpret_cast<unsigned long long>(&pAlignedC[i]) % 64ULL;

        wcout << L"Aligned SC[" << i << L"]\tAddress : \t" << &pAlignedC[i] << L"\tAddress / 64 : \t" << ullQuotient << L"\tAddress % 64 : \t" << ullRemainder << endl;
    }

    _aligned_free(static_cast<void*>(pAlignedC));

    delete[] pC;
    delete[] pB;
    delete[] pA;

    pC = nullptr;
    pB = nullptr;
    pA = nullptr;

    return 0;
}