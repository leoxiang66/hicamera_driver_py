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

    set_exposure_time(cam, 40000.0); // 40ms

    get_exposure_time(cam);

    turn_on_IEEE1588(cam);

    // wait_until_slave(cam);

    print_IEEE1588_status(cam);

    set_trigger_mode_on(cam);

    set_trigger_source_to_action(cam);

    set_action_keys(cam);

    start_grabbing(cam);

    issue_action_command();

    auto frame = pop_image_buffer(cam);

    if (frame != NULL)
    {
        save_non_raw_image("png", cam, frame);
    }

    // Clean up and close the SDK
    stop_grabbing(cam);
    close_device(cam);

    return 0;
}