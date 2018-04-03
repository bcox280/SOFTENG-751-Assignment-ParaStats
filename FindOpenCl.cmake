#If the system is windows, check the 32 and 64 bit paths
IF (WIN32)
    FIND_PATH(OPENCL_DIR CL/cl.h C:/Intel/OpenCL/sdk/include)

    #Check if its in a 64bit system, or else a 32 bit system
    FIND_LIBRARY(OPENCL_LIBRARIES ./OpenCl.lib C:/Intel/OpenCL/sdk/lib/x64)
    IF( OPENCL_LIBRARIES )
        FIND_LIBRARY(OPENCL_LIBRARIES  ./OpenCl.lib C:/Intel/OpenCL/sdk/lib/x86)
    ENDIF( OPENCL_LIBRARIES )
ELSE (WIN32)

    # Unix style platforms
    FIND_PATH(OPENCL_DIR CL/cl.h /opt/AMDAPPSDK-2.9-1/include/ )
    FIND_LIBRARY(OPENCL_LIBRARIES OpenCL
            ENV LD_LIBRARY_PATH
            )
ENDIF (WIN32)

#To tell CmakeLists if the library was correctly found
SET( OPENCL_FOUND "NO" )
IF(OPENCL_LIBRARIES )
    SET( OPENCL_FOUND "YES" )
ENDIF(OPENCL_LIBRARIES)
