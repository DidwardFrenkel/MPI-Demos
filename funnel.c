#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]){
  MPI_Init(&argc,&argv);
  int rank,size,tag=99;

  MPI_Status status;
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  int min,mout,i;

  //Also serves to confirm stack structure for message passing
  if (rank == 0) {
    //Multiple MPI_Send will stack.
      mout = 0;
      MPI_Send(&mout,1,MPI_INT,size - 1,tag,MPI_COMM_WORLD);
  } else if (rank == size -1 ) {
    //Each MPI_Recv pops the stack of MPI_Send.
    for (i = size - 2;i>=0;i--) {
      MPI_Recv(&min,1,MPI_INT,i,tag,MPI_COMM_WORLD,&status);
      printf("Source rank: %d, message: %d\n",i,min);
    }
  } else {
    mout = rank;
    MPI_Send(&mout,1,MPI_INT,size - 1,tag,MPI_COMM_WORLD);
  }
  MPI_Finalize();
  return 0;
}
