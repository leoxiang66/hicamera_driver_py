#include "utils.h"

int main()
{
    // Call your functions or perform desired operations here
    void* handle = init_SDK();
    if (handle == NULL)
    {
        printf("Failed to initialize SDK.\n");
        return 1;
    }


    // Clean up and close the SDK
    MV_CC_CloseDevice(handle);
    MV_CC_DestroyHandle(handle);

    return 0;
}