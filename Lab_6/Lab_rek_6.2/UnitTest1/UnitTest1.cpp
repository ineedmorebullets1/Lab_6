#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <cstdlib>

#define main lab_main
#include "C:\Users\aizen\Documents\lab c++\Lab_6\Lab_rek_6.2\Lab_rek_6.2\Lab_rek_6.2.cpp"
#undef main

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestRecursive
{
    // Еталон (ітераційний, не залежить від перевірюваного коду)
    static int RefMinEvenIndex(const std::vector<int>& v)
    {
        int idx = -1;
        for (size_t i = 0; i < v.size(); i++)
            if (v[i] % 2 == 0 && (idx == -1 || v[i] < v[idx]))
                idx = (int)i;
        return idx;
    }

    static std::vector<int> RefSwap(std::vector<int> v)
    {
        int idx = RefMinEvenIndex(v);
        if (idx != -1)
        {
            int t = v[0];
            v[0] = v[idx];
            v[idx] = t;
        }
        return v;
    }

    static std::vector<int> RandomVector(int n)
    {
        std::vector<int> v;
        for (int i = 0; i < n; i++) v.push_back(rand() % 101 - 50);
        return v;
    }

    TEST_CLASS(UnitTestRecursive)
    {
    public:

        // ---------- isEven ----------

        TEST_METHOD(IsEven_EvenNumbers_True)
        {
            Assert::IsTrue(isEven(0));
            Assert::IsTrue(isEven(2));
            Assert::IsTrue(isEven(-4));
            Assert::IsTrue(isEven(50));
        }

        TEST_METHOD(IsEven_OddNumbers_False)
        {
            Assert::IsFalse(isEven(1));
            Assert::IsFalse(isEven(-3));    // -3 % 2 == -1, а не 1
            Assert::IsFalse(isEven(49));
        }

        // ---------- fillArray (рекурсивна) ----------

        TEST_METHOD(FillArray_ValuesInRange)
        {
            int a[15];
            srand(12345);
            for (int run = 0; run < 100; run++)
            {
                fillArray(a, 15, -50, 50);
                for (int i = 0; i < 15; i++)
                {
                    Assert::IsTrue(a[i] >= -50);
                    Assert::IsTrue(a[i] <= 50);
                }
            }
        }

        // ---------- базовий випадок рекурсії (n = 0) ----------

        TEST_METHOD(BaseCase_EmptyArray)
        {
            int a[1] = { 7 };

            Assert::AreEqual(-1, findMinEvenIndex(a, 0));
            Assert::IsFalse(swapFirstWithMinEven(a, 0));
            Assert::AreEqual(7, a[0]);          // масив не змінився
        }

        // ---------- findMinEvenIndex ----------

        TEST_METHOD(FindMinEven_KnownValues)
        {
            int a1[6] = { 5, 8, 3, 2, 9, 4 };
            Assert::AreEqual(3, findMinEvenIndex(a1, 6));      // 2

            int a2[4] = { 3, -6, 4, -2 };
            Assert::AreEqual(1, findMinEvenIndex(a2, 4));      // -6

            int a3[3] = { 5, 0, 2 };
            Assert::AreEqual(1, findMinEvenIndex(a3, 3));      // нуль парний
        }

        TEST_METHOD(FindMinEven_NoEven_ReturnsMinusOne)
        {
            int a[3] = { 1, 3, -5 };
            Assert::AreEqual(-1, findMinEvenIndex(a, 3));
        }

        TEST_METHOD(FindMinEven_Duplicates_ReturnsFirst)
        {
            int a[5] = { 7, 4, 2, 2, 6 };
            Assert::AreEqual(2, findMinEvenIndex(a, 5));
        }

        TEST_METHOD(FindMinEven_SingleElement)
        {
            int even[1] = { 4 };
            int odd[1] = { 3 };
            Assert::AreEqual(0, findMinEvenIndex(even, 1));
            Assert::AreEqual(-1, findMinEvenIndex(odd, 1));
        }

        TEST_METHOD(FindMinEven_MinEvenIsLast)
        {
            int a[4] = { 8, 6, 3, 2 };
            Assert::AreEqual(3, findMinEvenIndex(a, 4));
        }

        TEST_METHOD(FindMinEven_MatchesReference)
        {
            srand(777);
            for (int run = 0; run < 300; run++)
            {
                std::vector<int> v = RandomVector(15);
                Assert::AreEqual(RefMinEvenIndex(v), findMinEvenIndex(v.data(), 15));
            }
        }

        // ---------- swapElements ----------

        TEST_METHOD(SwapElements_SwapsValues)
        {
            int x = 3, y = -7;
            swapElements(x, y);
            Assert::AreEqual(-7, x);
            Assert::AreEqual(3, y);
        }

        // ---------- swapFirstWithMinEven ----------

        TEST_METHOD(SwapFirst_KnownValues)
        {
            int a[6] = { 5, 8, 3, 2, 9, 4 };
            int expected[6] = { 2, 8, 3, 5, 9, 4 };

            Assert::IsTrue(swapFirstWithMinEven(a, 6));
            for (int i = 0; i < 6; i++)
                Assert::AreEqual(expected[i], a[i]);
        }

        TEST_METHOD(SwapFirst_FirstIsAlreadyMinEven_Unchanged)
        {
            int a[3] = { 2, 5, 4 };
            Assert::IsTrue(swapFirstWithMinEven(a, 3));
            Assert::AreEqual(2, a[0]);
            Assert::AreEqual(5, a[1]);
            Assert::AreEqual(4, a[2]);
        }

        TEST_METHOD(SwapFirst_NoEven_ReturnsFalse_ArrayUnchanged)
        {
            int a[3] = { 1, 3, 5 };
            Assert::IsFalse(swapFirstWithMinEven(a, 3));
            Assert::AreEqual(1, a[0]);
            Assert::AreEqual(3, a[1]);
            Assert::AreEqual(5, a[2]);
        }

        TEST_METHOD(SwapFirst_SingleEvenElement)
        {
            int a[1] = { 4 };
            Assert::IsTrue(swapFirstWithMinEven(a, 1));
            Assert::AreEqual(4, a[0]);
        }

        TEST_METHOD(SwapFirst_MatchesReference)
        {
            srand(999);
            for (int run = 0; run < 300; run++)
            {
                std::vector<int> v = RandomVector(15);
                std::vector<int> expected = RefSwap(v);
                bool hadEven = RefMinEvenIndex(v) != -1;

                Assert::AreEqual(hadEven, swapFirstWithMinEven(v.data(), 15));
                for (int i = 0; i < 15; i++)
                    Assert::AreEqual(expected[i], v[i]);
            }
        }

        // ---------- глибока рекурсія ----------

        TEST_METHOD(LargeArray_DeepRecursion)
        {
            const int n = 2000;
            std::vector<int> v(n);
            for (int i = 0; i < n; i++)
                v[i] = 2 * i + 1;          // усі елементи непарні
            v[1500] = 4;
            v[1900] = 2;                   // найменший парний

            Assert::AreEqual(1900, findMinEvenIndex(v.data(), n));

            Assert::IsTrue(swapFirstWithMinEven(v.data(), n));
            Assert::AreEqual(2, v[0]);
            Assert::AreEqual(1, v[1900]);  // колишній перший елемент
        }
    };
}