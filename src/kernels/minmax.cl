// Kernel to find the sum of a vector.
typedef struct rawStats {
    double min;
    double max;
    //cl_int m1;
} __attribute__ ((aligned (128))) rawStats;

__kernel void minmax(__global const double* input,
                     __global struct rawStats* output_stats,
                     __local double* local_min,
                     __local double* local_max
) {
    const int global_id = get_global_id(0); // Get the ID of the item in global memory
    //const int global_size = get_global_size(0); // Get the size of the global dimension
    const int local_id = get_local_id(0); // Get the ID of the item in local memory
    const int local_size = get_local_size(0); // Get the size of the workgroups
    const int group_id = global_id / local_size;

    local_min[local_id] = input[global_id]; // Write from the input vector to a local array
    local_max[local_id] = input[global_id];
    barrier(CLK_LOCAL_MEM_FENCE); // Wait for all operations to reach this point

    //
    for (int i = 1; i < local_size; i *= 2) {
        if (!(local_id % (i * 2)) && ((local_id + i) < local_size)) {
            // Compare the current value to the other values.
            local_min[local_id] = (local_min[local_id]>local_min[local_id+i]) ? local_min[local_id+i] : local_min[local_id];
            local_max[local_id] = (local_max[local_id]<local_max[local_id+i]) ? local_max[local_id+i] : local_max[local_id];
        }

        barrier(CLK_LOCAL_MEM_FENCE);
    }

    if(local_id == 0) {	// the root of the reduction subtree
        (output_stats+group_id)->min = local_min[local_id];
        (output_stats+group_id)->max = local_max[local_id];
    }
}
