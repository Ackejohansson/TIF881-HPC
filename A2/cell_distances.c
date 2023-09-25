#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <omp.h>

//#define SIZE 10 // Matrix size
#define MAX_POINTS 1000000

typedef struct {
  double x, y, z;
} Point;


// Function prototypes
int setMPThreadNumber(int argc, char *argv[], int *MP_threads);
double distance(Point p1, Point p2);


int main(int argc, char *argv[]) {
  // Set the number of threads to use
  int MP_threads = -1;
  setMPThreadNumber(argc, argv, &MP_threads);
  printf("The value after -t is: %d\n", MP_threads);


  // Read points from file
  int fd = open("cells.txt", O_RDONLY);
  if (fd == -1) {
    perror("Error opening file");
    return 1;
  }

  struct stat sb;
  if (fstat(fd, &sb) == -1) {
    perror("Error getting file size");
    return 1;
  }

  size_t file_size = (size_t)sb.st_size;

  char* file_data = (char*)mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (file_data == MAP_FAILED) {
    perror("Error mapping file to memory");
    return 1;
  }

  Point points[MAX_POINTS];
  int num_points = 0;
  char* line = file_data;

  // Parallel processing using OpenMP
  #pragma omp parallel
  {
    #pragma omp for
    for (size_t i = 0; i < file_size; ++i) {
      if (file_data[i] == '\n') {
        if (sscanf(line, "%lf %lf %lf", &points[num_points].x, &points[num_points].y, &points[num_points].z) == 3) {
          #pragma omp atomic
          num_points++;
        }
        line = file_data + i + 1;
      }
    }
  }

  // Compute distances between points
  printf("Distances between points:\n");
  #pragma omp parallel for
  for (int i = 0; i < num_points; i++) {
    for (int j = i + 1; j < num_points; j++) {
      double dist = distance(points[i], points[j]);
      printf("Distance between point %d and point %d: %lf\n", i + 1, j + 1, dist);
    }
  }

  // Clean up
  munmap(file_data, file_size);
  close(fd);

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////

int setMPThreadNumber(int argc, char *argv[], int *MP_threads) {
  int option;
  while ((option = getopt(argc, argv, "t:")) != -1)
    if (option == 't') 
      *MP_threads = atoi(optarg);

  if (*MP_threads == -1) {
    fprintf(stderr, "You must provide a value for -t\n");
    exit(EXIT_FAILURE);
  }
  return 0;
}

double distance(Point p1, Point p2) {
  double dx = p1.x - p2.x;
  double dy = p1.y - p2.y;
  double dz = p1.z - p2.z;
  return sqrt(dx * dx + dy * dy + dz * dz);
}

