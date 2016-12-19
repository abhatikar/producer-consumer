# include <stdio.h>
# include <pthread.h>

void *t1(void *);

int main()
{
    pthread_t tid;
    int iCount,iNumber=2;
    int PrimeFlag=1;
    pthread_create(&tid,NULL,t1,NULL);
    for(;;)
    {
        for(iCount=2;iCount<iNumber;iCount++)
        {        
            if(iNumber % iCount==0)
            {
                PrimeFlag=0;
                break;
            }
        }        
        if(PrimeFlag==1)
        {
            printf("%d \t",iNumber);
        }
        PrimeFlag=1;
        iNumber++;
        if(iNumber % 10 ==0)
        {
            usleep(1);
        }

    }    
    return 0;
}

void *t1(void *p)
{
    char ch;
    while(1)
    {
        ch=getchar();
        if(ch=='q' || ch=='Q')
        {
            exit(0);

        }
    }
}
