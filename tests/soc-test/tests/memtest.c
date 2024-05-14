#include "trap.h"


extern char _heap_start;

#define HEAP_SIZE (128 * 1024 * 1024)
#define HEAP_END  ((uintptr_t)&_heap_start + 1024)

#define Assert(cond)   \
	do                 \
	{                  \
		if (!(cond))     \
		{              \
			panic(#cond); \
		}              \
	} while (0)


uint32_t _test_num = -1;

static inline void test_start(void* st, void* ed, const char* test){
	for(int i = 0;i < 32;i++){
		putch('-');
	}
	putch('\n');
	putstr(test);
	putstr(" start from ");
	print_int((uintptr_t)st);
	putstr(" to ");
	print_int((uintptr_t)ed);
	putstr("\n");
	_test_num = -1;
}

static inline void test_end(void* st, void* ed, const char* test){
	putstr(test);
	putstr(" success\n");
	_test_num = -1;
}

static inline void test_info(void* st, void* ed, const char* test, void* p){
	if(_test_num++ < 0x100000) return;
	_test_num = 0;
	putstr("INFO: ");
	putstr(test);
	putstr(" Running at ");
	print_int((uintptr_t)p); 
	putstr(" from ");
	print_int((uintptr_t)st);
	putstr(" to ");
	print_int((uintptr_t)ed);
	putstr("\n");
}

void u8_test(void* st,void* ed){
	test_start(st,ed,"u8_test");
	for(uint8_t* p = (uint8_t*)ed -1;p > (uint8_t*)st;p--){
		uint8_t data = (uintptr_t)p & 0xff;
		*p = data;
		test_info(st,ed,"u8_test write",p);
	}
	for(uint8_t* p = (uint8_t*)st;p < (uint8_t*)ed;p++){
		uint8_t data = (uintptr_t)p & 0xff;
		if(*p != data){
			print_int((uintptr_t)p);
			putch('\n');
			print_int(*p);
			putch('\n');
			print_int(data);
			putch('\n');
			putstr({*p == data ? "same" : "diff"});
			putstr("\n------------------\n");
			panic("");
		}
		test_info(st,ed,"u8_test read",p);
	}
	test_end(st,ed,"u8_test");
}


void u16_test(void* st,void* ed){
	test_start(st,ed,"u16_test");
	for(uint16_t* p = (uint16_t*)st;p < (uint16_t*)ed;p++){
		uint16_t data = (uintptr_t)p & 0xffff;
		*p = data;
		test_info(st,ed,"u16_test write",p);
	}
	for(uint16_t* p = (uint16_t*)st;p < (uint16_t*)ed;p++){
		uint16_t data = (uintptr_t)p & 0xffff;
		if(!(*p == data)){
			char val_str[9] = {0};
			uint32_to_str((uint32_t)p,val_str);
			putstr(val_str);
			putch('\n');
			uint32_to_str(data,val_str);
			putstr(val_str);
			putch('\n');
			uint32_to_str(*p,val_str);
			putstr(val_str);
			panic("");
		}
		test_info(st,ed,"u16_test read",p);
	}
	test_end(st,ed,"u16_test");
}

// static inline void uint32_to_str(uint32_t n, char* hex) {
//     char* hex_str = "0123456789ABCDEF";
//     int i = 0;
//     for (i = 7; i >= 0; --i) {
//         hex[i] = hex_str[n & 0xF];
//         n >>= 4;
//     }
//     hex[8] = 0; // 确保字符串以 NULL 结束
// }

void u32_test(void* st,void* ed){
	test_start(st,ed,"u32_test");
	for(uint32_t* p = (uint32_t*)ed - 1;p >= (uint32_t*)st;p--){
		uint32_t data = (uintptr_t)p & 0xffffffff;
		*p = data;
		test_info(st,ed,"u32_test write",p);
	}
	for(uint32_t* p = (uint32_t*)st;p < (uint32_t*)ed;p++){
		uint32_t data = (uintptr_t)p & 0xffffffff;
		if(!(*p == data)){
			char val_str[9] = {0};
			uint32_to_str((uint32_t)p,val_str);
			putstr(val_str);
			putch('\n');
			uint32_to_str(data,val_str);
			putstr(val_str);
			putch('\n');
			uint32_to_str(*p,val_str);
			putstr(val_str);
			panic("");
		}
		test_info(st,ed,"u32_test read",p);
	}
	test_end(st,ed,"u32_test");
}


#define TEST_BASE 0xA0000000
#define TEST_SIZE 128*1024*1024
int a[] = {0x12345678,1,2,3,4,5,0x12345678};
typedef uint32_t* test_t ;
int main(){
	uintptr_t st = TEST_BASE;
	// int test_num = 64;
	// uintptr_t mem_size = TEST_SIZE / test_num;
	// for(int i = 0;i < test_num;i++){
	// u32_test((void*)st,(void*)(st + TEST_SIZE));
	// u16_test((void*)st,(void*)(st + TEST_SIZE));
	 u8_test((void*)st,(void*)(st + TEST_SIZE));
	// }
}
