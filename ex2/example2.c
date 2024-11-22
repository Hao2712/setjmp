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

enum ErrorCodes {
   NO_ERROR, 
   FILE_ERROR, 
   NETWORK_ERROR, 
   CALCULATE_ERROR
};

void readFile() {
   printf("File reading...\n");
   THROW(FILE_ERROR, Read_file error!);
}

void networkOperation() {
   printf("Network status...\n");
   THROW(NETWORK_ERROR, Connect_file error!);
}

void calculateData() {
   printf("Calculate...\n");
   THROW(CALCULATE_ERROR, Calculate error!);
}

int main() {
   TRY {
      readFile();
      networkOperation();
   } CATCH(FILE_ERROR) {
      printf("%s", error_code);
   } CATCH(NETWORK_ERROR) {
      printf("%s", error_code);
   } CATCH(CALCULATE_ERROR) {
      printf("%s", error_code);
   }
}
