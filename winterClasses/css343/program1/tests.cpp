#include "poly.h"
#include <sstream>

bool IsExpectedValue(Poly tmp, string expected)
{
    stringstream ss;
    ss << tmp;
    if (ss.str() != expected)
    {
        cout << "\tExpected:|" << expected << "| Result:|" << ss.str() << "|" << endl;
    }
    return ss.str() == expected;
    // cout << "|" << ss.str() << "|" << endl;
}

void PrintTestResult(string testName, bool result)
{
    int offset = 50 - testName.size();
    cout << testName;
    for (int i = 0; i < offset; i++)
    {
        cout << " ";
    }
    cout << ((result) ? "PASS" : "FAIL") << endl;
}

bool DefaultConstructorTest()
{
    Poly A;
    bool result = IsExpectedValue(A, " 0");
    PrintTestResult("DefaultConstructorTest", result);
}

bool CoeffConstructorTest()
{
    Poly A(5);
    bool result = IsExpectedValue(A, " +5");
    PrintTestResult("CoeffConstructorTest", result);
}

bool NegCoeffConstructorTest()
{
    Poly A(-5);
    bool result = IsExpectedValue(A, " -5");
    PrintTestResult("NegCoeffConstructorTest", result);
}

bool CoeffExpConstructorTest()
{
    Poly A(5, 2);
    bool result = IsExpectedValue(A, " +5x^2");
    PrintTestResult("CoeffExpConstructorTest", result);
}

bool NegCoeffExpConstructorTest()
{
    Poly A(-5, 2);
    bool result = IsExpectedValue(A, " -5x^2");
    PrintTestResult("NegCoeffExpConstructorTest", result);
}

bool CoefNegExpConstructorTest()
{
    Poly A(5, -2);
    bool result = IsExpectedValue(A, " 0");
    PrintTestResult("CoefNegExpConstructorTest", result);
}

bool NegCoeffNegExpConstructorTest()
{
    Poly A(-5, -2);
    bool result = IsExpectedValue(A, " 0");
    PrintTestResult("NegCoeffNegExpConstructorTest", result);
}

bool MassNegExpConstructorTest()
{
    for (int i = -50; i < 0; i++)
    {
        for (int j = -50; j < 50; j++)
        {
            Poly A(j, i);
            if (!IsExpectedValue(A, " 0"))
            {
                PrintTestResult("MassNegExpConstructorTest", false);
                return false;
            }
        }
    }
    PrintTestResult("MassNegExpConstructorTest", true);
}

bool SetCoeffTest()
{
    for (int i = 2; i < 100; i++)
    {
        Poly A;
        A.setCoeff(5, i);
        if (!IsExpectedValue(A, " +5x^" + to_string(i)))
        {
            PrintTestResult("SetCoeffTest", false);
            return false;
        }
    }
    for (int i = -100; i < 0; i++)
    {
        Poly A;
        A.setCoeff(i, 2);

        if (!IsExpectedValue(A, " " + to_string(i) + "x^2"))
        {
            PrintTestResult("SetCoeffTest", false);
            return false;
        }
    }
    for (int i = 1; i < 100; i++)
    {
        Poly A;
        A.setCoeff(i, 2);

        if (!IsExpectedValue(A, " +" + to_string(i) + "x^2"))
        {
            PrintTestResult("SetCoeffTest", false);
            return false;
        }
    }
    PrintTestResult("SetCoeffTest", true);
}

void GetCoeffTest()
{
    Poly B;
    for (int i = 2; i < 100; i++)
    {
        Poly A;
        A.setCoeff(i, i);
        B.setCoeff(i, i);
        if (!IsExpectedValue(A, " +" + to_string(i) + "x^" + to_string(i)))
        {
            PrintTestResult("GetCoeffTest", false);
            return;
        }
    }
    for (int i = 2; i < 100; i++)
    {
        if (!IsExpectedValue(B.getCoeff(i), " +" + to_string(i)))
        {
            PrintTestResult("GetCoeffTest", false);
            return;
        }
    }
    PrintTestResult("GetCoeffTest", true);
}

void DeepCloneTest()
{
    Poly A(2, 5);
    Poly B(A);

    if (!IsExpectedValue(A, " +2x^5") || !IsExpectedValue(B, " +2x^5"))
    {
        PrintTestResult("DeepCloneTest", false);
        return;
    }
    A.setCoeff(2, 4);
    if (!IsExpectedValue(A, " +2x^5 +2x^4") || !IsExpectedValue(B, " +2x^5"))
    {
        PrintTestResult("DeepCloneTest", false);
        return;
    }
    PrintTestResult("DeepCloneTest", true);
}

void SubtractionTest()
{
    Poly A;
    Poly B;
    A.setCoeff(5, 7);
    A.setCoeff(-100, 6);
    A.setCoeff(500, 5);
    A.setCoeff(124, 4);
    A.setCoeff(3, 2);
    A.setCoeff(1, 0);

    string AExpected = " +5x^7 -100x^6 +500x^5 +124x^4 +3x^2 +1";
    if (!IsExpectedValue(A, AExpected))
    {
        PrintTestResult("SubtractionTestA", false);
        return;
    }

    B.setCoeff(10, 14);
    B.setCoeff(5, 7);
    B.setCoeff(-12, 6);
    B.setCoeff(652, 4);
    B.setCoeff(15, 1);

    string BExpected = " +10x^14 +5x^7 -12x^6 +652x^4 +15x";
    if (!IsExpectedValue(B, BExpected))
    {
        PrintTestResult("SubtractionTestB", false);
        return;
    }

    Poly C = A - B;

    string CExpected = " -10x^14 -88x^6 +500x^5 -528x^4 +3x^2 -15x +1";
    if (!IsExpectedValue(C, CExpected))
    {
        PrintTestResult("SubtractionTestC", false);
        return;
    }
    PrintTestResult("SubtractionTest", true);
}

void MultiplicationTest()
{
    Poly A;
    Poly B;
    A.setCoeff(5, 7);
    A.setCoeff(-100, 6);
    A.setCoeff(500, 5);
    A.setCoeff(124, 4);
    A.setCoeff(3, 2);
    A.setCoeff(1, 0);

    string AExpected = " +5x^7 -100x^6 +500x^5 +124x^4 +3x^2 +1";
    if (!IsExpectedValue(A, AExpected))
    {
        PrintTestResult("MultiplicationTestA", false);
        return;
    }

    B.setCoeff(10, 14);
    B.setCoeff(5, 7);
    B.setCoeff(-12, 6);
    B.setCoeff(652, 4);
    B.setCoeff(15, 1);

    string BExpected = " +10x^14 +5x^7 -12x^6 +652x^4 +15x";
    if (!IsExpectedValue(B, BExpected))
    {
        PrintTestResult("MultiplicationTestB", false);
        return;
    }

    Poly C = A * B;

    string CExpected = " +50x^21 -1000x^20 +5000x^19 +1240x^18 +30x^16 +35x^14 -560x^13 +3700x^12 -2120x^11 -66688x^10 +326015x^9 +80887x^8 -1495x^7 +9444x^6 +1860x^5 +652x^4 +45x^3 +15x";
    if (!IsExpectedValue(C, CExpected))
    {
        PrintTestResult("MultiplicationTestC", false);
        return;
    }
    PrintTestResult("MultiplicationTest", true);
}

void AdditionTest()
{
    Poly A;
    Poly B;
    A.setCoeff(5, 7);
    A.setCoeff(-100, 6);
    A.setCoeff(500, 5);
    A.setCoeff(124, 4);
    A.setCoeff(3, 2);
    A.setCoeff(1, 0);

    string AExpected = " +5x^7 -100x^6 +500x^5 +124x^4 +3x^2 +1";
    if (!IsExpectedValue(A, AExpected))
    {
        PrintTestResult("AdditionTestA", false);
        return;
    }

    B.setCoeff(10, 14);
    B.setCoeff(5, 7);
    B.setCoeff(-12, 6);
    B.setCoeff(652, 4);
    B.setCoeff(15, 1);

    string BExpected = " +10x^14 +5x^7 -12x^6 +652x^4 +15x";
    if (!IsExpectedValue(B, BExpected))
    {
        PrintTestResult("AdditionTestB", false);
        return;
    }

    Poly C = A + B;

    string CExpected = " +10x^14 +10x^7 -112x^6 +500x^5 +776x^4 +3x^2 +15x +1";
    if (!IsExpectedValue(C, CExpected))
    {
        PrintTestResult("AdditionTestC", false);
        return;
    }
    PrintTestResult("AdditionTest", true);
}



void SubtractionAssignmentTest()
{
    Poly A;
    Poly B;
    A.setCoeff(5, 7);
    A.setCoeff(-100, 6);
    A.setCoeff(500, 5);
    A.setCoeff(124, 4);
    A.setCoeff(3, 2);
    A.setCoeff(1, 0);

    string AExpected = " +5x^7 -100x^6 +500x^5 +124x^4 +3x^2 +1";
    if (!IsExpectedValue(A, AExpected))
    {
        PrintTestResult("SubtractionAssignmentTestA", false);
        return;
    }

    B.setCoeff(10, 14);
    B.setCoeff(5, 7);
    B.setCoeff(-12, 6);
    B.setCoeff(652, 4);
    B.setCoeff(15, 1);

    string BExpected = " +10x^14 +5x^7 -12x^6 +652x^4 +15x";
    if (!IsExpectedValue(B, BExpected))
    {
        PrintTestResult("SubtractionAssignmentTestB", false);
        return;
    }

    A -= B;

    string CExpected = " -10x^14 -88x^6 +500x^5 -528x^4 +3x^2 -15x +1";
    if (!IsExpectedValue(A, CExpected))
    {
        PrintTestResult("SubtractionAssignmentTestC", false);
        return;
    }
    PrintTestResult("SubtractionAssignmentTest", true);
}

void MultiplicationAssignmentTest()
{
    Poly A;
    Poly B;
    A.setCoeff(5, 7);
    A.setCoeff(-100, 6);
    A.setCoeff(500, 5);
    A.setCoeff(124, 4);
    A.setCoeff(3, 2);
    A.setCoeff(1, 0);

    string AExpected = " +5x^7 -100x^6 +500x^5 +124x^4 +3x^2 +1";
    if (!IsExpectedValue(A, AExpected))
    {
        PrintTestResult("MultiplicationAssignmentTestA", false);
        return;
    }

    B.setCoeff(10, 14);
    B.setCoeff(5, 7);
    B.setCoeff(-12, 6);
    B.setCoeff(652, 4);
    B.setCoeff(15, 1);

    string BExpected = " +10x^14 +5x^7 -12x^6 +652x^4 +15x";
    if (!IsExpectedValue(B, BExpected))
    {
        PrintTestResult("MultiplicationAssignmentTestB", false);
        return;
    }

    A *= B;

    string CExpected = " +50x^21 -1000x^20 +5000x^19 +1240x^18 +30x^16 +35x^14 -560x^13 +3700x^12 -2120x^11 -66688x^10 +326015x^9 +80887x^8 -1495x^7 +9444x^6 +1860x^5 +652x^4 +45x^3 +15x";
    if (!IsExpectedValue(A, CExpected))
    {
        PrintTestResult("MultiplicationAssignmentTestC", false);
        return;
    }
    PrintTestResult("MultiplicationAssignmentTest", true);
}

void AdditionAssignmentTest()
{
    Poly A;
    Poly B;
    A.setCoeff(5, 7);
    A.setCoeff(-100, 6);
    A.setCoeff(500, 5);
    A.setCoeff(124, 4);
    A.setCoeff(3, 2);
    A.setCoeff(1, 0);

    string AExpected = " +5x^7 -100x^6 +500x^5 +124x^4 +3x^2 +1";
    if (!IsExpectedValue(A, AExpected))
    {
        PrintTestResult("AdditionAssignmentTestA", false);
        return;
    }

    B.setCoeff(10, 14);
    B.setCoeff(5, 7);
    B.setCoeff(-12, 6);
    B.setCoeff(652, 4);
    B.setCoeff(15, 1);

    string BExpected = " +10x^14 +5x^7 -12x^6 +652x^4 +15x";
    if (!IsExpectedValue(B, BExpected))
    {
        PrintTestResult("AdditionAssignmentTestB", false);
        return;
    }

    A += B;

    string CExpected = " +10x^14 +10x^7 -112x^6 +500x^5 +776x^4 +3x^2 +15x +1";
    if (!IsExpectedValue(A, CExpected))
    {
        PrintTestResult("AdditionAssignmentTestC", false);
        return;
    }
    PrintTestResult("AdditionAssignmentTest", true);
}

int main()
{
    DefaultConstructorTest();
    CoeffConstructorTest();
    NegCoeffConstructorTest();
    CoeffExpConstructorTest();
    NegCoeffExpConstructorTest();
    CoefNegExpConstructorTest();
    NegCoeffNegExpConstructorTest();
    MassNegExpConstructorTest();
    SetCoeffTest();
    GetCoeffTest();
    DeepCloneTest();
    AdditionTest();
    SubtractionTest();
    MultiplicationTest();
    AdditionAssignmentTest();
    SubtractionAssignmentTest();
    MultiplicationAssignmentTest();
    return 0;
}