#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>

#define size 100
int main(int argc, char const *argv[])
{
    float arr[2],sum;
    pid_t id;
    int pid1[2],pid2[20];
    pipe(pid1);
    pipe(pid2);

    id=fork();

    if(id==0)
    {
        close(pid1[1]);

        read(pid1[0],arr,size);
        printf("Child process\n");
        printf("%f %f\n",arr[0],arr[1]);
        close(pid1[1]);

        close(pid2[0]);
        sum=arr[0]+arr[1];
        write(pid2[1],&sum,sizeof(sum));
        close(pid2[1]);

    }   
    else
    {
        printf("Parent process\n");
        close(pid1[0]);

        printf("enter two values: ");
        scanf("%f %f",&arr[0],&arr[1]);
        write(pid1[1],arr,sizeof(arr));

        printf("data sent\n");
        close(pid1[1]);

        close(pid2[1]);
        read(pid2[0],&sum,sizeof(sum));
        printf("Result:%f\n",sum);
     } 
    return 0;
}