#include "stdio.h" 
int main() 
{    
    /*int a[6]={3,4,-2,-9,10,8}; */
    int a[6]={-3,-4,-2,-9,-10,-8}; 
    int i,sum=0; 
    for(i=0;i<6;++i) 
    { 
        sum+=a[i]; 
        if(sum<0) 
            sum=0; 
    } 
     
    printf("max=%d",sum); 
    return 0; 
} 
