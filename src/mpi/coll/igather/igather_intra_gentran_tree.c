/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil ; -*- */
/*
 *  (C) 2017 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 *
 *  Portions of this code were written by Intel Corporation.
 *  Copyright (C) 2011-2018 Intel Corporation.  Intel provides this material
 *  to Argonne National Laboratory subject to Software Grant and Corporate
 *  Contributor License Agreement dated February 8, 2012.
 */

#include "mpiimpl.h"

/* generate gentran algo prototypes */
#include "tsp_gentran.h"
#include "igather_tsp_tree_algos_prototypes.h"
#include "tsp_undef.h"

int MPIR_Igather_intra_gentran_tree(const void *sendbuf, int sendcount,
                                    MPI_Datatype sendtype, void *recvbuf, int recvcount,
                                    MPI_Datatype recvtype, int root, MPIR_Comm * comm_ptr,
                                    MPIR_Request ** request)
{
    int mpi_errno = MPI_SUCCESS;

    mpi_errno = MPII_Gentran_Igather_intra_tree(sendbuf, sendcount, sendtype,
                                                recvbuf, recvcount, recvtype,
                                                root, comm_ptr, request,
                                                MPIR_CVAR_IGATHER_TREE_KVAL);

    return mpi_errno;
}
