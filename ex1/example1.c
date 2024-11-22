#include <stdio.h>
#include <setjmp.h>
#include <string.h>

jmp_buf buf;
int exception_code;
char error_code[100];

#define TRY if ((exception_code = setjmp(buf)) == 0) 
#define CATCH(x) else if (exception_code == (x))
#define THROW(x, y) \
strcpy(error_code, #y); \
longjmp(buf, (x)); 


double divide(int a, int b) {
    if (b == 0) {
        THROW(1, Devided by 0!); // Mã lỗi 1 cho lỗi chia cho 0
    }
    return (double)a / b;
}

int main() {
    int a = 10;
    int b = 0;
    double result = 0.0;


    TRY {
        result = divide(a, b);
        printf("Result: %f\n", result);
    } CATCH(1) {
        printf("%s\n", error_code);
    }


    // Các xử lý khác của chương trình
    return 0;
    }
