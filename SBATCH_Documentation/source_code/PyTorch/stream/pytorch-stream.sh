#!/bin/bash
#SBATCH --job-name=pytorch-stream
#SBATCH --partition=short-gpu
#SBATCH --output=%A/out.out
#SBATCH --error=%A/err.err
#SBATCH --ntasks=1
#SBATCH --time=00:05:00

module load python39

source pytorch/bin/activate

srun python3 pytorch-stream.py

deactivate
