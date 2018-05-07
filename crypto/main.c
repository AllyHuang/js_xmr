#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash-ops.h"


const char num2ch[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','E','F'};
inline static uint64_t t32_to_t64(uint32_t t) { return 0xFFFFFFFFFFFFFFFFULL / (0xFFFFFFFFULL / ((uint64_t)t)); }
void hexdump(uint8_t *data, size_t len) {
   int i;
   for (i = 0; i < len; i++) {
      printf("%x", data[i]);
   }
   printf("\n");
   return;
}

inline static uint32_t hex2bin(char *data, size_t len) {
   size_t i;
   uint32_t res = 0;
   for (i = 0; i < len; i+=2) {
     if (data[i+1] >= '0' && data[i+1] <= '9') {
        res += ((size_t)(data[i+1]) - 48) << (i << 2);
     } else
     if (data[i+1] >= 'A' && data[i+1] <= 'F') {
        res += ((size_t)(data[i+1]) - 55) << (i << 2);
     } else 
     if (data[i+1] >= 'a' && data[i+1] <= 'f') {
        res += ((size_t)(data[i+1]) - 87) << (i << 2);
     }
     if (data[i] >= '0' && data[i] <= '9') {
        res += ((size_t)(data[i]) - 48) << ((i+1) << 2);
     } else
     if (data[i] >= 'A' && data[i] <= 'F') {
        res += ((size_t)(data[i]) - 55) << ((i+1) << 2);
     } else
     if (data[i] >= 'a' && data[i] <= 'f') {
        res += ((size_t)(data[i]) - 87) << ((i+1) << 2);
     }
   }
   return res;
}


int crack(char *work, char *target_s, char *output) {
   uint8_t hash[256];
   char data[] = {"This is a test\0"};
   uint8_t blob[76];
   uint32_t *nounce = (uint32_t*)(blob + 39);
   uint64_t *hash_val = (uint64_t*)(hash + 24);
   char a[3];
   a[2] = '\0';
   uint32_t i;
   uint64_t target = t32_to_t64(hex2bin(target_s,8));
   
   for (i = 0; i < 76; i++) {
       memcpy(a, work + (i<<1), 2);
       blob[i] = strtoul(a, NULL, 16);
   }
   cn_slow_hash((void*)blob, 76, hash, 0, 0);
   for (i = 0; i < UINT_MAX; i++) {
       (*nounce) ++;
       cn_slow_hash((void*)blob, 76, hash, 0, 0);
       if (i % 100 == 0) {
           printf("hash calculated %u\n", i);
       }
       if (target > *hash_val) {
           memcpy(output, hash, 32);
           break;
       }
   }
   return *nounce;
}

int main(int argc, char *argv[]) {
   char output[32];
   crack(argv[1], argv[2], output);
   hexdump(output, 32);
   return 1;
}
