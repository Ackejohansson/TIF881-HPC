#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SOURCE_SIZE (0x100000)

void checkError(cl_int status, const char* message) {
    if (status != CL_SUCCESS) {
        fprintf(stderr, "Error %s: %d\n", message, status);
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Usage: ./diffusion -n [iterations] -d [diffusion constant]\n");
        return 1;
    }
    printf("HEREYO");
    int n_iterations = atoi(argv[2]);
    float diffusion_constant = atof(argv[4]);

    // Read input from the "init" file
    FILE* init_file = fopen("init", "r");
    int n_x, n_y;
    fscanf(init_file, "%d %d", &n_x, &n_y);

    float* temperature_grid = (float*)malloc(n_x * n_y * sizeof(float));

    for (int i = 0; i < n_x * n_y; i++) {
        fscanf(init_file, "%f", &temperature_grid[i]);
    }
    fclose(init_file);

    // Set up OpenCL environment
    cl_platform_id platform_id;
    clGetPlatformIDs(1, &platform_id, NULL);

    cl_device_id device_id;
    clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL);

    cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, NULL);
    cl_queue_properties properties[] = {CL_QUEUE_PROPERTIES, CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE, 0};
    cl_command_queue command_queue = clCreateCommandQueueWithProperties(context, device_id, properties, NULL);

    // Create buffers for input and output data
    cl_mem temperature_grid_buffer = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float) * n_x * n_y, NULL, NULL);
    cl_mem n_x_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int), NULL, NULL);
    cl_mem n_y_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int), NULL, NULL);
    cl_mem diffusion_constant_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(float), NULL, NULL);

    // Load OpenCL kernel source code
    FILE* kernel_file = fopen("diffusion_kernel.cl", "r");
    char* kernel_source = (char*)malloc(MAX_SOURCE_SIZE);
    size_t kernel_size = fread(kernel_source, 1, MAX_SOURCE_SIZE, kernel_file);
    fclose(kernel_file);

    // Create and build the OpenCL program
    cl_program program = clCreateProgramWithSource(context, 1, (const char**)&kernel_source, &kernel_size, NULL);
    clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "heatDiffusion", NULL);

    // Set kernel arguments
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &temperature_grid_buffer);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &n_x_buffer);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), &n_y_buffer);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), &diffusion_constant_buffer);

    // Copy data to OpenCL buffers
    clEnqueueWriteBuffer(command_queue, temperature_grid_buffer, CL_TRUE, 0, sizeof(float) * n_x * n_y, temperature_grid, 0, NULL, NULL);
    clEnqueueWriteBuffer(command_queue, n_x_buffer, CL_TRUE, 0, sizeof(int), &n_x, 0, NULL, NULL);
    clEnqueueWriteBuffer(command_queue, n_y_buffer, CL_TRUE, 0, sizeof(int), &n_y, 0, NULL, NULL);
    clEnqueueWriteBuffer(command_queue, diffusion_constant_buffer, CL_TRUE, 0, sizeof(float), &diffusion_constant, 0, NULL, NULL);

    // Execute the OpenCL kernel
    size_t global_work_size[2] = {n_x, n_y};
    for (int iteration = 0; iteration < n_iterations; iteration++) {
        clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, global_work_size, NULL, 0, NULL, NULL);
    }

    // Read the result from the OpenCL buffer
    clEnqueueReadBuffer(command_queue, temperature_grid_buffer, CL_TRUE, 0, sizeof(float) * n_x * n_y, temperature_grid, 0, NULL, NULL);

    // Calculate the average temperature and average absolute difference
    float sum_temperature = 0.0;
    float sum_abs_difference = 0.0;
    float average_temperature, average_abs_difference;

    for (int i = 0; i < n_x * n_y; i++) {
        sum_temperature += temperature_grid[i];
    }

    average_temperature = sum_temperature / (n_x * n_y);

    for (int i = 0; i < n_x * n_y; i++) {
        sum_abs_difference += fabs(temperature_grid[i] - average_temperature);
    }

    average_abs_difference = sum_abs_difference / (n_x * n_y);

    printf("average: %f\n", average_temperature);
    printf("average absolute difference: %f\n", average_abs_difference);

    // Clean up OpenCL resources
    clReleaseMemObject(temperature_grid_buffer);
    clReleaseMemObject(n_x_buffer);
    clReleaseMemObject(n_y_buffer);
    clReleaseMemObject(diffusion_constant_buffer);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(command_queue);
    clReleaseContext(context);

    free(temperature_grid);
    free(kernel_source);

    return 0;
}

