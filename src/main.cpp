#include "utils.h"

int main()
{
    // Call your functions or perform desired operations here
    void* cam = init_SDK();
    if (cam == NULL)
    {
        printf("Failed to initialize SDK.\n");
        return 1;
    }

    set_exposure_auto_off(cam);

    set_exposure_time(cam, 30000.0); // 30ms

    get_exposure_time(cam);

    

    // Clean up and close the SDK
    close_device(cam);

    return 0;
}