#!/bin/bash

#SBATCH --job-name=MpiBinarySearch
#SBATCH --output=%A/mpi-bin.out
#SBATCH --error=%A/mpi-bin.err
#SBATCH --ntasks=10
#SBATCH --time=00:05:00

module load openmpi4/gcc
module load gcc

srun mpicc mpi-binary-search.c -o mpi-binary-search

srun --mpi=pmix --export=ALL,OMPI_MCA_btl_openib_allow_ib=true,OMPI_MCA_btl=openib,self,sm ./mpi-binary-search
