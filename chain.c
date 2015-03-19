/* Communication chain:
 * Exchange between messages between mpirank
 * 0 <-> 1 <-> 2 <-> 3 <-> ....
 */
#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

int main( int argc, char *argv[])
{
  int rank, size, tag, origin, destination;
  MPI_Status status;

  char hostname[1024];
  gethostname(hostname, 1024);

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int message_out = rank;
  int message_in = -1;
  tag = 99;

  if(rank == 0)
  {
    destination = size == 1 ? 0:1;
    origin = size == 1 ? 0:1;
    MPI_Send(&message_out, 1, MPI_INT, destination, tag, MPI_COMM_WORLD);
    MPI_Recv(&message_in,  1, MPI_INT, origin, tag, MPI_COMM_WORLD, &status);
    printf("rank %d hosted on %s received from %d the message %d\n", rank, hostname, origin, message_in);
  }
  else if (rank == size - 1)
  {
    destination = size - 2;
    origin = size - 2;
    MPI_Recv(&message_in,  1, MPI_INT, origin, tag, MPI_COMM_WORLD, &status);
  printf("rank %d hosted on %s received from %d the message %d\n", rank, hostname, origin, message_in);
    MPI_Send(&message_out, 1, MPI_INT, destination, tag, MPI_COMM_WORLD);
  }
  else
  {
    destination = rank - 1;
    origin = rank - 1;
    MPI_Recv(&message_in,  1, MPI_INT, origin,      tag, MPI_COMM_WORLD, &status);
    MPI_Send(&message_out, 1, MPI_INT, destination, tag, MPI_COMM_WORLD);

  printf("rank %d hosted on %s received from %d the message %d\n", rank, hostname, origin, message_in);
    destination = rank + 1;
    origin = rank + 1;
    MPI_Send(&message_out, 1, MPI_INT, destination, tag, MPI_COMM_WORLD);
    MPI_Recv(&message_in,  1, MPI_INT, origin,      tag, MPI_COMM_WORLD, &status);
  }


  MPI_Finalize();
  return 0;
}
