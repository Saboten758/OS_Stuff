#include<stdio.h>
#include<stdlib.h>
void fifo_management(int*,int);
void lfu_management(int*,int,int*);
void wm_with_freq(int*,int*);
void wm_print(int* wm);
int pointer=0; //for FIFO
int frames=0;
int main(){
    system("clear||cls");
    printf("Welcome to page replacement algorithms simulation\n");
    printf("Enter the number of frames allocated to the process:");
    scanf("%d",&frames);
    int * working_cache=malloc(sizeof(int*)*frames);
    int * page_freq=calloc(sizeof(int*),frames);
    printf("Frames allocated to the process successfully!\n");
    int req,ch;
    while(1){
        printf("Enter 1 to use FIFO management\n");
        printf("Enter 2 to use LFU management\n");
        printf("Enter your choice:");
        scanf("%d",&ch);
        if(ch==1 || ch==2) break;
        else printf("\nWrong choice!\n");
    }
    while(1){
        printf("Enter the page requested by the process(-1 to exit):");
        scanf("%d",&req);
        if(req==-1) break;
        if (ch==1) fifo_management(working_cache,req);
        else lru_management(working_cache,req,page_freq);
    }
    printf("thanks!\n");
}

void fifo_management(int* work,int req){
    for (int i=0;i<frames;i++){
        if(req==work[i]){
            printf("\nHit!\n");
            return; 
        }
    }
    printf("\nMiss!\n");
    work[pointer]=req;
    pointer=(pointer+1)%frames;
    wm_print(work);
    
}

void lfu_management(int*work,int req,int* page_freq){
    for (int i=0;i<frames;i++){
        if(req==work[i]){
            printf("\nHit!\n");
            page_freq[i]+=1;
            wm_with_freq(work,page_freq);
            return; 
        }
    }
    printf("\nMiss!\n");
    int ind=0;
    int min=page_freq[0];
    for(int i=0;i<frames;i++){
        if(min>page_freq[i]) {
            min=page_freq[i];
            ind=i;
        }
    }
    work[ind]=req;
    page_freq[ind]=1;
    wm_with_freq(work,page_freq);
}
void wm_with_freq(int*wm,int* page){
    printf("\nCurrent frames with frequency:\n");
    for(int i=0;i<frames;i++){
        printf("%d  :  %d\n",wm[i],page[i]);
    }
    printf("************************\n\n");
}
void wm_print(int* wm){
    printf("\nCurrent frames:\n");
    for(int i=0;i<frames;i++){
        printf("%d\n",wm[i]);
    }
    printf("************************\n\n");
}