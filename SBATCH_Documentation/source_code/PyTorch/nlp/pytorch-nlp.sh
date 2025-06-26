#!/bin/bash
#SBATCH --job-name=pytorch-nlp
#SBATCH --partition=short-gpu
#SBATCH --output=%A/out.out
#SBATCH --error=%A/err.err
#SBATCH --ntasks=1
#SBATCH --time=00:10:00

module load python39

source pytorch/bin/activate

srun python3 nlp.py

deactivate
