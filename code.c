#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#define MIN_PID 300
#define MAX_PID 5000

int share = 0;
pthread_mutex_t l;
void *function1();
void *function2();
struct pidmanager   
{

  int pid;
  int bitmap;

}Array[4700];

int allocate_map(void)                   
{
  int i=MIN_PID,j=0;

  while(i<MAX_PID)        		//Complexity - O(n)
  {
	Array[j].pid = i;
	Array[j].bitmap = 0;
	i++;
	j++;
  }
  if(i==MAX_PID && j==4700)
    return 1;

  else 
    return -1;

}


int allocate_pid(void)                //Complexity - O(1)
{
	int p;
	X:printf("Enter the process id you need to allocate to process -");
	scanf("%d",&p);
	if(p<300 || p>5000)
	{
		printf("\nEntered wrong(300-5000)\n");
		goto X;
	}
		

	if(Array[p-300].bitmap == 0)
	{
	  Array[p-300].bitmap = 1;
	  return p;
	}

  return -1;

}

void release_pid(int p)                   //Complexity - O(1)
{

	if(Array[p-300].bitmap == 1)
	{
	  Array[p-300].bitmap = 0;
	  printf("\nPid _ %d released successfully\n",p);
	}
	else
	{
		printf("pid no released\n");
	}

}

int main()
{
	int status;
	pthread_t thread1;
	pthread_t thread2;
	status = allocate_map();
	if(status==1)			//Complexity - O(1)
	printf("\nAllocation of bit map to all the process is successfull\n");
	else
	{
		printf("\nAllocation of bit map is unsuccessfull please try it again\n");
		return 0;
	}
   	
	pthread_mutex_init(&l,NULL);
	pthread_create(&thread1,NULL,&function1,NULL); // thread1 created
	pthread_create(&thread2,NULL,&function2,NULL); // thread2 created
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	
    return 0;
 }



void *function1()                
{
        int ret,n,ar[4700];   
	pthread_mutex_lock(&l);
	printf("Enter the no. of processes -");
	scanf("%d",&n);   
	for(int i=1;i<=n;i++)				//Complexity- O(n)
	{            
		X:printf("\nProcess -%d\n",i);
		 ret = allocate_pid();
		 if(ret==-1)
		{
	
    		printf("pid not allocated\n");
			goto X;
		}
		ar[i]=ret;
		printf("pid -%d allocated successfully\n",ret);
   	}
    
    share++;     
	for(int i=1;i<=n;i++)
	{            
		release_pid(ar[i]);	
   	}
    printf("\nprocess slept for a while\n");
    sleep(1);
    printf("\nShare Variable-%d\n",share);
    pthread_mutex_unlock(&l);           
    
}
void *function2()                
{
        int ret,n,ar[4700];
	pthread_mutex_lock(&l);
	printf("Enter the no. of processes -");
	scanf("%d",&n);   
	for(int i=1;i<=n;i++)				//Complexity- O(n)
	{            
		X:printf("\nProcess -%d\n",i);
		 ret = allocate_pid();
		 if(ret==-1)
		{
	
    		printf("pid not allocated\n");
			goto X;
		}
		ar[i]=ret;
		printf("pid -%d allocated successfully\n",ret);
   	}
    
    share++;     
	for(int i=1;i<=n;i++)
	{            
		release_pid(ar[i]);	
   	}
                        
    
    printf("\nprocess slept for a while\n");
    sleep(1);
    printf("\nShare Variable-%d\n",share);
    pthread_mutex_unlock(&l);           
    
}
