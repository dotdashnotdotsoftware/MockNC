#include "MockNC.h"


MNC_DEF(void, Log_Access, ()) {
	printf("Pretend to log to logging system...\n");
}
MNC_DEF(int, Get_Foo, ()) {
	Log_Access();
	return 3;
}
MNC_DEF(void, Print_Foo, ()) {
	printf("Foo was: %d\n", Get_Foo());
}
MNC_DEF(int, Double_Foo, ()) {
	return Get_Foo() * 2;
}