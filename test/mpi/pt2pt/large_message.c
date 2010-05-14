/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 *  (C) 2010 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "mpitest.h"

/* tests send/recv of a message > 2GB. count=270M, type=long long */

int main(int argc, char *argv[]) 
{
  int        ierr,i,size,rank;
  int        cnt = 270000000;
  MPI_Status status;
  long long  *cols;
  int errs = 0;


  MTest_Init(&argc,&argv); 
  ierr = MPI_Comm_size(MPI_COMM_WORLD,&size);
  ierr = MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  if (size != 2) {
    fprintf(stderr,"[%d] usage: mpiexec -n 2 %s\n",rank,argv[0]);
    MPI_Abort(MPI_COMM_WORLD,1);
  }

  cols = malloc(cnt*sizeof(long long));
  if (rank == 0) {
    for (i=0; i<cnt; i++) cols[i] = i;
    /* printf("[%d] sending...\n",rank);*/
    ierr = MPI_Send(cols,cnt,MPI_LONG_LONG_INT,1,0,MPI_COMM_WORLD);
  } else {
      /* printf("[%d] receiving...\n",rank); */
    for (i=0; i<cnt; i++) cols[i] = -1;
    ierr = MPI_Recv(cols,cnt,MPI_LONG_LONG_INT,0,0,MPI_COMM_WORLD,&status);
    /* ierr = MPI_Get_count(&status,MPI_LONG_LONG_INT,&cnt);
       Get_count still fails because status.count is not 64 bit */
    for (i=0; i<cnt; i++) {
        if (cols[i] != i) {
            printf("cols[i]=%lld, should be %d\n", cols[i], i);
            errs++;
        }
    }
  }
  MTest_Finalize(errs);
  MPI_Finalize();
  return 0;
}
