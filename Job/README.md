# Job samples

Shows how to use the job module.

The job module lets you utilize multi-threaded CPUs in an easy way. 
You submit jobs to the job service, and it automatically distributes them among the threads.
Jobs may have dependencies on other jobs. In this case, the job execution won't start till all its dependent jobs are finished.

## Samples

| Sample     | Description      |
|:-----------|:-----------------|
| [Job](Job) | Main job sample. |
