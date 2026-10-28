#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <cstdlib>

// Підключаємо ітераційну програму, перейменувавши main.
// Шлях змініть на свій.
#define main lab_main
#include "C:\Users\aizen\Documents\lab c++\Lab_6\Lab_it_6.1\Lab_it_6.1\Lab_it_6.1.cpp"
#undef main

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestIterative
{
    // Еталон: критерій «всі, крім додатних кратних 5»
    static bool RefOk(int x) { return x <= 0 || x % 5 != 0; }

    static int RefCount(const std::vector<int>& v)
    {
        int c = 0;
        for (size_t i = 0; i < v.size(); i++)
            if (RefOk(v[i])) c++;
        return c;
    }

    static int RefSum(const std::vector<int>& v)
    {
        int s = 0;
        for (size_t i = 0; i < v.size(); i++)
            if (RefOk(v[i])) s += v[i];
        return s;
    }

    static std::vector<int> RefZero(std::vector<int> v)
    {
        for (size_t i = 0; i < v.size(); i++)
            if (RefOk(v[i])) v[i] = 0;
        return v;
    }

    // Випадковий масив із діапазону [-40; 50] (не залежить від fillArray)
    static std::vector<int> RandomVector(int n)
    {
        std::vector<int> v;
        for (int i = 0; i < n; i++) v.push_back(rand() % 91 - 40);
        return v;
    }

    TEST_CLASS(UnitTestIterative)
    {
    public:

        // ---------- isSatisfying ----------

        TEST_METHOD(IsSatisfying_PositiveMultiplesOf5_False)
        {
            for (int x = 5; x <= 50; x += 5)
                Assert::IsFalse(isSatisfying(x));
        }

        TEST_METHOD(IsSatisfying_ZeroAndNegatives_True)
        {
            Assert::IsTrue(isSatisfying(0));
            Assert::IsTrue(isSatisfying(-1));
            Assert::IsTrue(isSatisfying(-5));
            Assert::IsTrue(isSatisfying(-40));
        }

        TEST_METHOD(IsSatisfying_NotMultiplesOf5_True)
        {
            Assert::IsTrue(isSatisfying(1));
            Assert::IsTrue(isSatisfying(7));
            Assert::IsTrue(isSatisfying(49));
        }

        TEST_METHOD(IsSatisfying_MatchesReference)
        {
            for (int x = -40; x <= 50; x++)
                Assert::AreEqual(RefOk(x), isSatisfying(x));
        }

        // ---------- fillArray ----------

        TEST_METHOD(FillArray_ValuesInRange)
        {
            int a[22];
            srand(12345);
            for (int run = 0; run < 100; run++)
            {
                fillArray(a, 22, -40, 50);
                for (int i = 0; i < 22; i++)
                {
                    Assert::IsTrue(a[i] >= -40);
                    Assert::IsTrue(a[i] <= 50);
                }
            }
        }

        TEST_METHOD(FillArray_ReachesBothBounds)
        {
            int a[22];
            bool sawLow = false, sawHigh = false;
            srand(12345);
            for (int run = 0; run < 1000; run++)
            {
                fillArray(a, 22, -40, 50);
                for (int i = 0; i < 22; i++)
                {
                    if (a[i] == -40) sawLow = true;
                    if (a[i] == 50) sawHigh = true;
                }
            }
            Assert::IsTrue(sawLow);
            Assert::IsTrue(sawHigh);
        }

        // ---------- countSatisfying ----------

        TEST_METHOD(Count_KnownValues)
        {
            int mixed[8] = { -40, 5, 0, 7, 10, -5, 50, 3 };
            int allOk[4] = { -1, -2, 0, 3 };
            int noneOk[4] = { 5, 10, 50, 45 };

            Assert::AreEqual(5, countSatisfying(mixed, 8));
            Assert::AreEqual(4, countSatisfying(allOk, 4));
            Assert::AreEqual(0, countSatisfying(noneOk, 4));
        }

        TEST_METHOD(Count_MatchesReference)
        {
            srand(777);
            for (int run = 0; run < 200; run++)
            {
                std::vector<int> v = RandomVector(22);
                Assert::AreEqual(RefCount(v), countSatisfying(v.data(), 22));
            }
        }

        // ---------- sumSatisfying ----------

        TEST_METHOD(Sum_KnownValues)
        {
            int mixed[8] = { -40, 5, 0, 7, 10, -5, 50, 3 };
            int allOk[4] = { -1, -2, 0, 3 };
            int noneOk[4] = { 5, 10, 50, 45 };

            Assert::AreEqual(-35, sumSatisfying(mixed, 8));
            Assert::AreEqual(0, sumSatisfying(allOk, 4));
            Assert::AreEqual(0, sumSatisfying(noneOk, 4));
        }

        TEST_METHOD(Sum_MatchesReference)
        {
            srand(888);
            for (int run = 0; run < 200; run++)
            {
                std::vector<int> v = RandomVector(22);
                Assert::AreEqual(RefSum(v), sumSatisfying(v.data(), 22));
            }
        }

        // ---------- zeroSatisfying ----------

        TEST_METHOD(Zero_KnownValues)
        {
            int a[8] = { -40, 5, 0, 7, 10, -5, 50, 3 };
            int expected[8] = { 0, 5, 0, 0, 10, 0, 50, 0 };

            zeroSatisfying(a, 8);
            for (int i = 0; i < 8; i++)
                Assert::AreEqual(expected[i], a[i]);
        }

        TEST_METHOD(Zero_NoneSatisfy_ArrayUnchanged)
        {
            int a[4] = { 5, 10, 50, 45 };
            zeroSatisfying(a, 4);
            Assert::AreEqual(5, a[0]);
            Assert::AreEqual(10, a[1]);
            Assert::AreEqual(50, a[2]);
            Assert::AreEqual(45, a[3]);
        }

        TEST_METHOD(Zero_MatchesReference)
        {
            srand(999);
            for (int run = 0; run < 200; run++)
            {
                std::vector<int> v = RandomVector(22);
                std::vector<int> expected = RefZero(v);
                zeroSatisfying(v.data(), 22);
                for (int i = 0; i < 22; i++)
                    Assert::AreEqual(expected[i], v[i]);
            }
        }

        // ---------- повний сценарій з main ----------

        TEST_METHOD(Scenario_CountSumThenZero)
        {
            srand(2024);
            int b[22];
            fillArray(b, 22, -40, 50);

            int countBefore = countSatisfying(b, 22);
            zeroSatisfying(b, 22);

            // після заміни нулі також задовольняють критерію, тож кількість та сама,
            // а сума цих елементів дорівнює нулю
            Assert::AreEqual(countBefore, countSatisfying(b, 22));
            Assert::AreEqual(0, sumSatisfying(b, 22));
        }
    };
}