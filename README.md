# MPI-Demos
Contains some demos for MPI functions in C. It requires mpi.h to use and mpicc to compile.

cascade.c calls a series of MPI_Send, which are then picked up by MPI_Recv in a sort of stack structure.

chain.c calls an MPI_Send and MPI_Recv at the first step, which is then picked up at the next step (assuming the number of steps N > 1) by an MPI_Recv and MPI_Send, followed by an MPI_Send and MPI_Recv for the next step, repeating until the last step, where it picks up the previous MPI_Send with an MPI_Recv and completes the MPI_Recv of the previous step with an MPI_Send.

funnel.c calls an MPI_Send at each step, all of which are picked up at the last step by a series of MPI_Recv.
