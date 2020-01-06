#ifdef MNC
#include <stdio.h>
#include "MockNC.h"
#include "Foo.h"
#include "Bar.h"

MNC_MOCK(int, Mock_Foo, ())
MNC_VOID_MOCK(Mock_Log_Foo, ())

//Typical testing example, using a MockNC MOCK
void TestOne()
{
	//Arrange
	MNC_RESET();
	Mock_Foo.ReturnValue = 99;
	MNC_SWAP(Get_Foo, Mock_Foo.MockFunc);

	//Act - Prove Print_Foo() uses Get_Foo()
	Print_Foo();
	Print_Foo();
	Print_Foo();

	//Assert
	printf("%s\n", 3 == Mock_Foo.CallCount ? "PASS" : "FAIL");
}

//Typical testing example, using another MockNC function from Bar.c
void TestTwo()
{
	//Arrange
	MNC_RESET();
	MNC_SWAP(Get_Foo, Bar);

	//Act - Prove that Double_Foo() doubles the result from Bar()
	int result = Double_Foo();

	//Assert
	printf("%s\n", 18 == result ? "PASS" : "FAIL");
}

//Typical testing example, using a regular C style function from Bar.c
void TestThree()
{
	//Arrange
	MNC_RESET();
	MNC_SWAP(Get_Foo, NormalFunction);

	//Act - Prove that Double_Foo() doubles the result from NormalFunction()
	int result = Double_Foo();

	//Assert
	printf("%s\n", 50 == result ? "PASS" : "FAIL");
}

//Typical testing example, using a MockNC MOCK
void TestFour()
{
	//Arrange
	MNC_RESET();
	MNC_SWAP(Log_Access, Mock_Log_Foo.MockFunc);

	//Act - Prove Get_Foo() uses Log_Access()
	Get_Foo();
	Get_Foo();
	Get_Foo();

	//Assert
	printf("%s\n", 3 == Mock_Foo.CallCount ? "PASS" : "FAIL");
}

//Test Application Main
int main()
{
	//Run Tests
	TestOne();
	TestTwo();
	TestThree();
	TestFour();
	printf("Done!\n");
}
#endif