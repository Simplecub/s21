#include "fcgi_stdio.h"
#include <stdlib.h>
#include <stdio.h>

int main () {
	while(FCGI_Accept() >=0) {
	printf("\nHello World!\n");
	}
return 0;
}
