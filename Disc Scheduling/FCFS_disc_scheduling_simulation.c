#include<stdio.h>
#include<stdlib.h>
float system_time=0; //for storing the system time since the algorithm started
float serve=0; //global static variable serve for storing the service time of a data from a particular track (disc latency)
void elapsed_counter(float time,int head){
    printf("\nTime Elapsed (in ms) for last operation:%.2f",time);
    system_time+=time;
    printf("\nTotal time elapsed until the start of scheduling:%.2f",system_time);
    printf("\nCurrent read-write head position:%d track\n",head);
    printf("\n*************\n");
}

void handle_fault(int req,int head,float lat){
    int diff;
    if(head<req)  diff=req-head;
    else diff=head-req;
    printf("\nRead write head moved back by %d tracks!",diff);
    float seek=diff*lat;
    
    printf("\nService was given to %d !",req);
    elapsed_counter(seek+serve,req);
}

int service(int req,int head,float lat){
    if(head==req){
        printf("\nService was given to %d !",req);
        elapsed_counter(0+serve,req);
    }
    else{
        handle_fault(req,head,lat);
    }
    return req;
}

int main(){
    system("clear");
    printf("Welcome to FCFS disc scheduling simulation!\n");
    int head,req=0;
    printf("\nEnter the initial position of the read write head:");
    scanf("%d",&head);

    float lat;
    printf("Enter the seek latency(in ms):"); //time taken by the read-write head to move from one track to another
    scanf("%f",&lat);

    printf("\nEnter the disc latency(in ms):"); //time taken to access a data from a sector in a certain track
    scanf("%f",&serve);

    while (1){
        printf("Enter the requested track number(-1 to exit):");
        scanf("%d",&req);
        if(req==-1) break;
        head=service(req,head,lat);
    }
    printf("Thanks for using!");
}