# MockNC
MockNC (Mock-n-see) is a basic Mocking Framework for C to simplify unit testing. By leveraging function pointers, any function written through MockNC can be easily swapped out for another, redirecting all calls to your substituted function instead of the original. 
# How it works
Whereas normally code might look like:

**Header**
```
int MyFunc();
```
**Source**
```
int MyFunc()
{
    return 10*10;
}
```
Code written using MockNC would look like:

**Header**
```
MNC_DECLARATION(int, MyFunc, ())
```
**Source**
```
MNC_DEFINITION(int, MyFunc, ())
{
    return 10*10;
}
```
Which in the default configuration will just expand to output your code as normal!

**Header**
```
int MyFunc();
```
**Source**
```
int MyFunc()
{
    return 10*10;
}
```
Define a preprocessor variable called "MNC" however and then the magic happens:

**Header**
```
extern int(*MyFunc)();
```
**Source**
```
int MyFunc_Imp();
int (*MyFunc)() = MyFunc_Imp;
int MyFunc_Imp()
{
    return 10*10;
}
```
Which lets you
1. Call your function as you normally would
2. Swap out the implementation of your function at runtime

```
MyFunc(); //Returns 100
MyFunc = AlwaysReturn20;
MyFunc(); //Now returns 20
```

# Extra Bits
Now, simply helping you swap the implementation behind a function is great and everything but it helps to have some extra tools!

## MNC_SWAP and MNC_RESET
Using ```MNC_SWAP(identifier, new_target)``` and ```MNC_RESET()``` is a great combination when writing tests. Instead of manually tracking which functions are pointing where, one can simply reset the state of play at the start of each test:
```
    //Arrange
    MNC_RESET();
    MNC_SWAP(Get_Foo, Bar);

    //Act - Prove that Double_Foo() doubles the result from Bar()
    int result = Double_Foo();

    //Assert
    printf("%s\n", 18 == result ? "PASS" : "FAIL");
```

## MNC_MOCK and MNC_VOID_MOCK
I get it, sometimes you just want to check that a function behaves correctly when it receives a certain return value when it calls another function or you just want to prove it's calling a function - this is what ```MNC_MOCK``` and ```MNC_VOID_MOCK``` can provide by helping take away the drudgery of writing your own code to handle this common task:
```
MNC_MOCK(int, Mock_Foo, ())

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
```

```
MNC_VOID_MOCK(Mock_Log_Foo, ())

//Typical testing example, using a MockNC MOCK
void TestFour()
{
	//Arrange
	MNC_RESET();
	MNC_SWAP(Log_Access, Mock_Log_Foo.MockFunc);

	//Act - Prove Get_Foo() uses Log_Access()
	Get_Foo();

	//Assert
	printf("%s\n", 1 == Mock_Log_Foo.CallCount ? "PASS" : "FAIL");
}
```
