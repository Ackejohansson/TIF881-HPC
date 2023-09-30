# TIF881-HPC
Repo for High Performance Computing

## GANTENBEIN

### Logging In
To log on Gantenbein, use the following SSH command:

```bash
ssh hpcuser074@gantenbein.math.chalmers.se
```
Copy from local file to remote
```bash
scp -r c:/Users/axelg/Documents/Chalmers/CAS2/TMA881-HPC/A1 hpcuser074@gantenbein.math.chalmers.se:./dev
```

## A2
Create tar file:
```bash
tar -czvf cell_distances.tar.gz Makefile cell_distances.c
```
Test script :
```bash
/home/hpc2023/cell_distances/check_submission.jl /home/hpcuser074/dev/a2/cell_distances.tar.gz
```