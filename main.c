
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <time.h>
int main(int argc , char** argv)
{
    int rank , size , i , n , ps , mx=0 , Pmx=0;
    int *arr , *subarr ;
    MPI_Status status ;

    time_t t1 = time(NULL);

    MPI_Init(&argc , &argv);
    MPI_Comm_rank(MPI_COMM_WORLD , &rank);
    MPI_Comm_size(MPI_COMM_WORLD , &size);

   if(rank==0)
   {
       printf("Enter Array Size:");
       scanf("%d" , &n);
       arr=malloc(n*sizeof(int));

       for(i=0 ;i<n ;i++)
        arr[i]=i+1;

        mx=arr[0];
   }

   MPI_Bcast(&n , 1 , MPI_INT , 0 , MPI_COMM_WORLD);
   MPI_Bcast(arr , n , MPI_INT , 0 , MPI_COMM_WORLD);

   ps=n/size;

   int low = rank*ps ;
   int high= low+ ps;

   for(i=low ; i<high ;i++)
    {
        if(arr[i]>Pmx)
            Pmx=arr[i];
    }


  // MPI_Reduce(&Pmx , &mx , 1  , MPI_INT , MPI_MAX , 0 , MPI_COMM_WORLD);
   MPI_Allreduce(&Pmx , &mx , 1  , MPI_INT , MPI_MAX  , MPI_COMM_WORLD);
   if(rank==1)
   {
       if(n%size!=0)
       {
           for(i=size*ps ;i<n ;i++)
           {
               if(arr[i]>mx)
                mx=arr[i];
           }
       }

       time_t t2 = time(NULL);

       printf("Max number = %d \n" , mx);
       printf("Time = %d \n" , t2-t1);
   }



    MPI_Finalize();

    return 0;
}
