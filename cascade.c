#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]){
  MPI_Init(&argc,&argv);
  int rank,size,dest,N = atoi(argv[1]),tag=99;
  if (N <= 0) N = 1;

  MPI_Status status;
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  int min,mout,i;
  if (rank %2 == 0) {
    dest = rank + 1;
    //Multiple MPI_Send will stack.
    for (i = N-1;i>=0;i--){
      mout = i;
      MPI_Send(&mout,1,MPI_INT,dest,tag,MPI_COMM_WORLD);
    }
  } else {
    dest = rank - 1;
    //Each MPI_Recv pops the stack of MPI_Send.
    for (i = 0;i<N;i++) {
      MPI_Recv(&min,1,MPI_INT,dest,tag,MPI_COMM_WORLD,&status);
      printf("i: %d, message: %d\n",i,min);
    }
  }
  MPI_Finalize();
  return 0;
}
