//------------------------------------------------------------------------------
//
// kernel:  mean
//
// Purpose: Updates the mean with a new vector of data points
//
// input:  m:      Current mean a
//         a:      vector of doubles
//         count:  Current count
//         length: Length of a
//
// output: m1:     Updated mean
//
// TODO: Check for correctness of algorithm

__kernel void mean(
    __global double m1
    __global double* a,
    const unsigned int length,
    const unsigned int count,
    const double m)
{                                          
    //int id = get_global_id(0);

    // Could do this on CPU ?
    // Still need both count and length
    count = count + length;

    // Could do this on the CPU
    // and then pass only m1 ?
    m1 = m;

    // Update mean m1
    for (int i = 0; i < length; i++)
        delta = a[i] - m1;
        m1 = mean + delta / count;
    }
}
