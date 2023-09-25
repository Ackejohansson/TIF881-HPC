#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/stat.h> // For mkdir function
#include <unistd.h>   // For access function

#define NUM_INTS 1048576
#define NUM_BENCHMARKS 10

int directoryExists(const char *path) {
  return access(path, F_OK) != -1;
}

void createDirectory(const char *path) {
  if (!directoryExists(path)) {
    int status = mkdir(path, 0777); // Create the directory with full permissions
    if (status == -1) {
      perror("Failed to create directory");
      exit(EXIT_FAILURE);
    }
  }
}

void writeToFile(const char *filename, int *data) {
  FILE *file = fopen(filename, "wb");
  if (file == NULL) {
    perror("Failed to open file for writing");
    exit(EXIT_FAILURE);
  }

  fwrite(data, sizeof(int), NUM_INTS, file);
  fflush(file);
  fclose(file);
}

void readFromFile(const char *filename, int *data) {
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    perror("Failed to open file for reading");
    exit(EXIT_FAILURE);
  }

  fread(data, sizeof(int), NUM_INTS, file);
  fclose(file);
}

int main() {
  int data[NUM_INTS];
  clock_t start, end;
  double total_hdd_write_time = 0.0;
  double total_hdd_read_time = 0.0;
  double total_ssd_write_time = 0.0;
  double total_ssd_read_time = 0.0;

  for (int i = 0; i < NUM_INTS; i++) {
    data[i] = i;
  }
  
  const char *hddDirectory = "./exe";
  const char *ssdDirectory = "../../../../run/mount/scratch/hpcuser074";
  
  createDirectory(hddDirectory);
  createDirectory(ssdDirectory);

  for (int benchmark = 1; benchmark <= NUM_BENCHMARKS; benchmark++) {
    printf("Benchmark %d of %d on HDD...\n", benchmark, NUM_BENCHMARKS);
  
    start = clock();
    writeToFile("./exe/hdd_test.txt", data);
    end = clock();
    total_hdd_write_time += ((double)(end - start)) / CLOCKS_PER_SEC;
  
    start = clock();
    readFromFile("./exe/hdd_test.txt", data);
    end = clock();
    total_hdd_read_time += ((double)(end - start)) / CLOCKS_PER_SEC;
  
    printf("Benchmark %d of %d on SSD...\n", benchmark, NUM_BENCHMARKS);
  
    start = clock();
    writeToFile("../../../../run/mount/scratch/hpcuser074/ssd_test.txt", data); 
    end = clock();
    total_ssd_write_time += ((double)(end - start)) / CLOCKS_PER_SEC;
  
    start = clock();
    readFromFile("../../../../run/mount/scratch/hpcuser074/ssd_test.txt", data);
    end = clock();
    total_ssd_read_time += ((double)(end - start)) / CLOCKS_PER_SEC;
  
    printf("------------------------------\n");
  }
  
  double avg_hdd_write_time = total_hdd_write_time / NUM_BENCHMARKS;
  double avg_hdd_read_time = total_hdd_read_time / NUM_BENCHMARKS;
  double avg_ssd_write_time = total_ssd_write_time / NUM_BENCHMARKS;
  double avg_ssd_read_time = total_ssd_read_time / NUM_BENCHMARKS;
  
  printf("Average HDD Write Time: %f seconds\n", avg_hdd_write_time);
  printf("Average HDD Read Time: %f seconds\n", avg_hdd_read_time);
  printf("Average SSD Write Time: %f seconds\n", avg_ssd_write_time);
  printf("Average SSD Read Time: %f seconds\n", avg_ssd_read_time);

  return 0;
}
