#!/bin/bash
#SBATCH --job-name=array-example
##SBATCH --array=1-5 # Submits a job array with index values between 1 and 5
#SBATCH --array=1,3,5,7 # Submits a job array with index values of 1,3,5,7
##SBATCH --array=1-7:2 # Submits a job array with index values between 1 and 7 with steps of 2 (1,3,5,7)
##SBATCH --array=1-5%2 # Submis a job array with index values between 1 and 5 but limits the number of simultaneously running tasks for this job array to 4
#SBATCH --partition=short-cpu
#SBATCH --output=%A/out_%a.out # The output file will be in a folder with the name jobId and will have the form out_arrayIndex
#SBATCH --error=%A/error_%a.err # The error file will be in a folder with the name jobId and will have the form error_arrayIndex
#SBATCH --ntasks=1
#SBATCH --time=00:05:00

module load python39

srun python3 ~/examples/array-example/array-example.py $SLURM_ARRAY_JOB_ID $SLURM_ARRAY_TASK_ID # Calls a python script with the arguments jobId and arrayIndex
