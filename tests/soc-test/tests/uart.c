#include "trap.h"

int main(){
	int i = 0;
	char str[] = "1234567890zxcvbnmasdfghjklqwertyuiop,./;'[]\\-=`\n";
	while(true){
		putstr(str);
		extern char uart_getch();
		putch(uart_getch());
		i %= 10;
	}
}
