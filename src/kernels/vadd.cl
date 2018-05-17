//------------------------------------------------------------------------------
//
// kernel:  vadd  
//
// Purpose: Compute the elementwise sum c = a+b
// 
// input: a and b float vectors of length count
//
// output: c float vector of length count holding the sum a + b
//

__kernel void vadd(                             
   __global double* a,
   __global double* b,
   __global double* c,
   const unsigned int count)               
{                                          
   int i = get_global_id(0);               
   if(i < count)  {
       c[i] = a[i] + b[i];                 
   }
}
