// Structs for kernel
typedef struct moments {
    double m1;
    double m2;
    double m3;
    double m4;
} __attribute__ ((packed)) moments;

typedef struct rawStats {
    double min;
    double max;
    moments rawMoments;
} __attribute__ ((packed)) rawStats;

// Kernel to find the sum of a vector.
__kernel void stats(__global const double* input,
                     __global struct rawStats* output_stats,
                     __local double* local_minmax,
                     __local struct moments* local_moments) {

    const int global_id = get_global_id(0); // Get the ID of the item in global memory
    //const int global_size = get_global_size(0); // Get the size of the global dimension
    const int local_id = get_local_id(0); // Get the ID of the item in local memory
    const int local_size = get_local_size(0); // Get the size of the workgroups

    local_minmax[local_id] = input[global_id]; // Write from the input vector to a local array
    barrier(CLK_LOCAL_MEM_FENCE); // Wait for copying of segment to local memory

    if (!(local_id % 2) && ((local_id + 1) < local_size)) { // First pass to reduce every 2nd element
        // Moments of each pair
        double delta = local_minmax[local_id + 1] - local_minmax[local_id];
        (local_moments+(local_id>>1))->m1 = local_minmax[local_id] + (delta*0.5);
        (local_moments+(local_id>>1))->m2 = 0.5*delta*delta;
        (local_moments+(local_id>>1))->m3 = 0.0;
        (local_moments+(local_id>>1))->m4 = 0.125*delta*delta*delta*delta; // Assume data range is < 4th root of DBL_MAX

        // Min/Max of each pair
        if (local_minmax[local_id] > local_minmax[local_id + 1]) {
            delta = local_minmax[local_id + 1];
            local_minmax[local_id + 1] = local_minmax[local_id];
            local_minmax[local_id] = delta;
        }
    }
    barrier(CLK_LOCAL_MEM_FENCE); // Wait for 1st pass to complete

    // TODO: Optimise i*=2 with bit shifting
    for (int i = 2; i < local_size; i*=2) { // Remaining passes to reduce every 2nd element to final element
        if (!(local_id % (i * 2)) && ((local_id + i) < local_size)) {
            // Moments
            double delta = (local_moments+((local_id+i)>>1))->m1 - (local_moments+(local_id>>1))->m1;
            (local_moments+(local_id>>1))->m4 = (local_moments+((local_id+i)>>1))->m4 +
                                                (local_moments+(local_id>>1))->m4 + 0.125*i*delta*delta*delta*delta
                                                + 1.5*delta*delta*((local_moments+((local_id+i)>>1))->m2
                                                                   + (local_moments+(local_id>>1))->m2)
                                                + 2.0*delta*((local_moments+((local_id+i)>>1))->m3
                                                             - (local_moments+(local_id>>1))->m3);
            (local_moments+(local_id>>1))->m3 = (local_moments+((local_id+i)>>1))->m3
                                                + (local_moments+(local_id>>1))->m3
                                                + 1.5*delta*((local_moments+((local_id+i)>>1))->m2
                                                             - (local_moments+(local_id>>1))->m2);
            (local_moments+(local_id>>1))->m2 = (local_moments+((local_id+i)>>1))->m2
                                                + (local_moments+(local_id>>1))->m2 + 0.5*i*delta*delta;
            (local_moments+(local_id>>1))->m1 = (local_moments+(local_id>>1))->m1 + (delta*0.5);

            // Min/Max
            // Compare the min values to the other values.
            local_minmax[local_id] = (local_minmax[local_id] > local_minmax[local_id+i]) ? local_minmax[local_id+i] : local_minmax[local_id];

        } else if (!((local_id - 1) % (i * 2)) && ((local_id - 1 + i) < local_size)) {
            // Compare the max values to the other values.
            local_minmax[local_id] = (local_minmax[local_id] < local_minmax[local_id+i]) ? local_minmax[local_id+i] : local_minmax[local_id];
        }
        barrier(CLK_LOCAL_MEM_FENCE); // Wait for each pass to complete before moving to next pass
    }

    if (local_id == 0) { // Place reduced workgroup solution on output buffer
        const int group_id = global_id / local_size;
        (output_stats+group_id)->min = local_minmax[0];
        (output_stats+group_id)->rawMoments = local_moments[0];
    } else if(local_id == 1) {
        const int group_id = global_id / local_size;
        (output_stats+group_id)->max = local_minmax[local_id];
    }
}
