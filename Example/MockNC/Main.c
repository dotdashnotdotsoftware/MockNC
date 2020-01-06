#include <stdio.h>
#include "Foo.h"

//Release application main
int main()
{
	//Call Double_Foo as per normal & get the expected behaviour
    printf("Hello World!\n");
    printf("Double_Foo returns: %d\n", Double_Foo());
	printf("Done!\n");
}