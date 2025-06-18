#!/bin/bash
#SBATCH --job-name=omp-bin-search
#SBATCH --output=%A/omp-bin.out
#SBATCH --error=%A/omp-bin.err
#SBATCH --time=00:05:00
#SBATCH --cpus-per-task=4

module load openmpi/gcc/64

srun gcc -fopenmp openmp-binary-search.c -o openmp-binary-search

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

srun --mpi=pmi2 ./openmp-binary-search
