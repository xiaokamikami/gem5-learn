/*
 * Copyright (c) 2006 The Regents of The University of Michigan
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <string.h>  
#include <stdlib.h>  
#include <time.h>  
  
#define ARRAY_SIZE 30000  
#define ACCESS_TIMES 10  

int main(int argc, char* argv[])
{
    //creat arry  
    int *array = (int *)malloc(sizeof(int) * ARRAY_SIZE); 

    char temp[] = "Hello MEM world !";
    char copy[sizeof(temp)];
    memcpy(copy,temp,sizeof(temp));
    int i = memcmp(copy,temp,sizeof(temp));
    printf("%s == %s  reslut:%d \n",temp,copy , i);
 
  
    // srand init arry
    srand(time(NULL));  
    for (int i = 0; i < ARRAY_SIZE; i++) {  
        array[i] = rand();  
    }  
    printf("array init \n");

    clock_t start = clock();  
    for (int j = 0; j < ACCESS_TIMES; j++) {  
        for (int i = 0; i < ARRAY_SIZE; i++) {  
            array[i * 3 + j % 3];  //Increase access complexity
        }  
    }  
    clock_t end = clock();  
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;  
    printf("Array access time: %f seconds\n", elapsed_time);  
  
    // free
    free(array);
    
    return 0;
}
