# include <stdio.h>
# include <pthread.h>
# define QUEUE_SIZE 10

int In=0,Out=0;
void *Producer(void *);
void *Consumer(void *);

pthread_mutex_t read_mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t write_mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t Queue_Not_Full=PTHREAD_COND_INITIALIZER;
pthread_cond_t Queue_Not_Empty=PTHREAD_COND_INITIALIZER
;
int Queue_Is_Empty()
{
    if(In==Out)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Queue_Is_Full()
{
    if(Out==((In+1)%QUEUE_SIZE))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{    
    pthread_t tid[4];
    int p_array[2];
    int c_array[2];
    int iCount;
    
    p_array[0]=1;
    p_array[1]=2;
    
    c_array[0]=1;
    c_array[1]=2;
        
    pthread_create(&tid[0],NULL,Consumer,(void *)c_array[0]);
    pthread_create(&tid[1],NULL,Consumer,(void *)c_array[1]);
    pthread_create(&tid[2],NULL,Producer,(void *)p_array[0]);
    pthread_create(&tid[3],NULL,Producer,(void *)p_array[1]);
    
    for(iCount=0;iCount<4;iCount++)
    {
        pthread_join(tid[iCount],NULL);
    }
    return 0;
}

void *Producer(void *arg)
{    
    int *Pno;
    Pno=(int *) arg;
    for(;;)
    {
        pthread_mutex_lock(&write_mutex);
        if(Queue_Is_Full())
        {                                    
            pthread_cond_wait(&Queue_Not_Full,&write_mutex);            
        }                
        printf("Produce [%d] :%d \n",Pno,In);
        In=(In + 1) % QUEUE_SIZE;
        pthread_mutex_unlock(&write_mutex);
        pthread_cond_signal(&Queue_Not_Empty);        
    }    
    
}

void *Consumer(void * arg)
{
    int *Cno;
    Cno=(int *) arg;
    for(;;)
    {
        pthread_mutex_lock(&read_mutex);
        if(Queue_Is_Empty())
        {                        
            pthread_cond_wait(&Queue_Not_Empty,&read_mutex);            
        }
        printf("Consume [%d] :%d \n",Cno,Out);
        Out=(Out + 1) % QUEUE_SIZE;
        pthread_mutex_unlock(&read_mutex);        
        pthread_cond_signal(&Queue_Not_Full);                
    }    
}
