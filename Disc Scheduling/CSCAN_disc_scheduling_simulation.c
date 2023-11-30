#include<stdio.h>
#include<stdlib.h>
float system_time=0; //for storing the system time since the algorithm started
float serve=0; //global static variable serve for storing the service time of a data from a particular track (disc latency)
int tracks=0;

void elapsed_counter(float time,int head){
    printf("\nTime Elapsed (in ms) for last operation:%.2f ms",time);
    system_time+=time;
    printf("\nTotal time elapsed until the start of scheduling:%.2f ms",system_time);
    printf("\nCurrent read-write head position:%d track\n",head);
    printf("\n*************\n");
}

void service(int* req,int len,int head,float seek_lat){
    int diff=0;
    for(int i=0;i<len;i++){
        if(req[i]==head){
            diff=0;
        }
        else if(req[i]>head){
            diff=req[i]-head;
        }
        if(req[i]>=head){
            printf("\nService was given for the request made to %d track!",req[i]);
            printf("\nread-write head made a seek of %d seeks!",diff);
            head=req[i];
            req[i]=-1;
            float time=(diff*seek_lat)+serve;
            elapsed_counter(time,head);
        }
    }
    diff=tracks-head;
    head=0;  //bring read-write head to first track (simulates the cylindrical arrangement of tracks needed for cscan)
    for(int i=0;i<len;i++){
        if(req[i]==head){
            diff+=0;
        }
        else if(req[i]>head){
            diff+=(req[i]-head);
        }
        if(req[i]>=head){
            printf("\nService was given for the request made to %d track!",req[i]);
            printf("\nread-write head made a seek of %d seeks!",diff);
            head=req[i];
            req[i]=-1;
            float time=(diff*seek_lat)+serve;
            elapsed_counter(time,head);
            diff=0;
        }
    }
}
void sort(int*arr,int len){ //SIMPLE ASCENDING ORDER (TODO: OPTIMIZE!)
    for(int i=0;i<len;i++){
        for(int j=i+1;j<len;j++){
            if(arr[j]<arr[i]){
                int temp=arr[j];
                arr[j]=arr[i];
                arr[i]=temp;
            }
        }
    }
}
int main(){
    system("clear");
    printf("Welcome to CSCAN disc scheduling simulation!\n"); //the readwrite head moves in circular manner while the tracks are considered to be arraged in the form of a cylinder
    int head;
    
    printf("The read-write head is moving in right\n");
    printf("Enter the max number of tracks:");
    scanf("%d",&tracks);
    while(1){
        printf("\nEnter the initial position of the read-write head:");
        scanf("%d",&head);
        if(head<=tracks) break;
        else printf("\nThe initial head pos can't be ahead of the number of tracks!\n");
    }
    
    float lat;

    printf("Enter the seek latency(in ms):"); //time taken by the read-write head to move from one track to another
    scanf("%f",&lat);

    printf("\nEnter the disc latency(in ms):"); //time taken to access a data from a sector in a certain track
    scanf("%f",&serve);
    int * req=malloc(10*sizeof(int*));

    int ind=0,buff;
    while (1){
        printf("Enter the requested track number(-1 to exit):");
        scanf("%d",&buff);
        if(buff==-1 || ind==9) break;
        if(buff<=tracks){
            req[ind]=buff;
            ind+=1;
        }
        else printf("Error taking request!");
    } 
    sort(req,ind);
    service(req,ind,head,lat);
    // for (int i=0;i<ind;i++){
    //     printf("%d\n",req[i]);
    // }
    
    printf("Thanks for using!");
}