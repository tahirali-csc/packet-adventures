#include <stdio.h>

#define MAX_PORTS	1024
const volatile int target_sports[MAX_PORTS] = {};

int main(){
    // printf("Hello\n");
    for (int i = 0; i < MAX_PORTS; i++) {
        if (!target_sports[i]){
            printf("Exiting... %d",i);
            return 0;
        }
    }
    return 0;
}