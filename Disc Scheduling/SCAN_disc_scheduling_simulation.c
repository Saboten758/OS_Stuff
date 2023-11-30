#include<stdio.h>
#include<stdlib.h>
int tracks=0;
float sys_time=0;
void service(int*,int,float,float,int);
void sort(int*,int);
void elapsed_counter(int,float);
int main(){
    system("clear||cls");
    printf("Welcome to SCAN disc scheduling simulation!\n");
    printf("Enter the number of tracks present:");
    scanf("%d",&tracks);
    int head=0,buff,ind=0;
    float seek_time=0,disc_lat=0;
    while(1){
        printf("Enter the start position of the read-write head:");
        scanf("%d",&head);
        if(head>tracks) printf("\nHead can't be ahead of the number of tracks!\nTry again!\n");
        else break;
    }
    printf("Read-write head is moving in left to right direction!\n");
    printf("Enter the seek time(in ms):");
    scanf("%f",&seek_time);
    printf("Enter the disc latency(in ms):");
    scanf("%f",&disc_lat);
    printf("Enter the requests(10 at max)\n");
    int * req=malloc(sizeof(int*)*10);
    while(1){
        printf("Enter the track requested:(-1 to exit):");
        scanf("%d",&buff);
        if(buff==-1 || ind==10) break;
        if(buff>tracks)printf("Error in taking the request!\n");
        else{
            req[ind++]=buff;
        }    
    }
    sort(req,ind);
    service(req,ind,disc_lat,seek_time,head);

}
void sort(int*ar,int len){
    int temp;
    for(int i=0;i<len;i++){
        for(int j=i+1;j<len;j++){
            if(ar[i]>ar[j]){
                temp=ar[i];
                ar[i]=ar[j];
                ar[j]=temp;
            }
        }
    }
}
void service(int* req,int len,float lat,float seek_lat,int head){
    int diff=0;
    for(int i=0;i<len;i++){ //forward scan
        if(req[i]==head) diff=0;
        else if(req[i]>head) diff=req[i]-head;
        if(req[i]>=head) {
            float time=(diff*seek_lat)+lat;
            printf("\n\nService given to the request for %d  track!",req[i]);
            head=req[i];
            req[i]=-1;
            printf("\nRead-write moved to %d track!",head);
            elapsed_counter(diff,time);
        }
    }
    diff=tracks-head;
    head=tracks; //moving head till the end

    for(int i=len-1;i>=0;i--){  //backward scan
        if(req[i]!=-1){ 
            if(req[i]==head) diff+=0;
            else if(req[i]<head)  diff=(head-req[i])+diff;
            if(req[i]<=head ) {
                float time=(diff*seek_lat)+lat;
                printf("\n\nService given to the request for %d  track!",req[i]);
                head=req[i];
                req[i]=-1;
                printf("\nRead-write moved to %d track!",head);
                elapsed_counter(diff,time);
                diff=0;
            }
        }
    }
    
}
void elapsed_counter(int seeks,float time){
    printf("\nTotal seeks made:%d\n",seeks);
    printf("Total time last operation took:%.2f ms\n",time);
    sys_time+=time;
    printf("Total time elapsed from scheduling started:%.2f ms\n",sys_time);
    printf("*********************\n");
}