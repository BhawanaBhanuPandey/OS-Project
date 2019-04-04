#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#include<unistd.h>
#include<stdbool.h>
#define MIN_PID 500
#define MAX_PID 3000

int allocate_map();
int allocate_pid();
void release_pid(int pid);

int threadVar = 0;
int i,j;
pthread_mutex_t mutex;
struct pid_tab
{
  int pid;
  bool bitmap;
  
}pidArr[4700];

int allocate_map(void)
{
  for( i = MIN_PID, j=0; j<=MAX_PID;i++,j++)
  {
	pidArr[j].pid = i;
	pidArr[j].bitmap = 0;
  }

  if(i==MAX_PID && j==4700)     
  {
	return 1;
  }
  else
  {
  	return -1;
  }
}

int allocate_pid(void)
{
   for( i = MIN_PID, j=0; j<=MAX_PID;i++,j++)
   {
      if(pidArr[j].bitmap == 0)
      {
	  pidArr[j].pid = i;
	  pidArr[j].bitmap = 1;
	  return i;
	  break;
      }
      else
      {
	return -1;
      }
   }
  
}

void release_pid(int pid)
{
  for( i=0;i<=4700;i++)
  {
     if(pidArr[i].pid == pid)
     {
	pidArr[i].bitmap = 0;
     }
  }
}

 void *threadCall(void *voidA)
 {
  int ret = allocate_pid();
  while(threadVar < 100)
  {
	pthread_mutex_lock(&mutex);
	if(threadVar >= 100)
	{
	      pthread_mutex_unlock(&mutex);
	      break;
	} 
  threadVar++;
  sleep(10);
  printf("\nVALUE OF THREADVVAR : %d",threadVar);

  pthread_mutex_unlock(&mutex);
  }
  sleep(8);
  release_pid(ret);
}

int main()
{
  int z = 0;
  pthread_t thread[100];
  printf("100 threads will be created and threadVar will be incremented each time by 1 ");
  
  //sleep(3000);
  //printf("Time to read output on the screen");
   
  for(z=0;z<100;z++)
  {
     pthread_mutex_init(&mutex,NULL);
     pthread_create(&thread[i],NULL,&threadCall,NULL);
  }
  
   for(z=0;z<100;z++)
  {
     
     pthread_join(thread[i],NULL);
     pthread_mutex_unlock(&mutex);
  }
  
  return 0;

}




