#include "timer.h"
#include "utils.h"

void pop_thread(void *handle)
{
    while (true)
    {
        auto frame = pop_image_buffer(handle, 1, false);
        if (frame != NULL)
        {
            print_frame_info(frame, true);
            // save_non_raw_image("png", handle, frame);
        }
    }
}

int main()
{

    uint64_t sync_point = 10000000;
    Timer timer(sync_point, 20.0);

    void *cam = init_SDK(0);

    // 启动线程并运行 pop_thread 函数
    std::thread thread1(pop_thread, cam);
    thread1.detach(); // 让线程独立运行

    if (cam == NULL)
    {
        printf("Failed to initialize SDK.\n");
        return 1;
    }

    set_exposure_auto_off(cam);

    set_exposure_time(cam, 15000.0);

    set_pixel_format(cam, PixelType_Gvsp_RGB8_Packed);

    std::cout << "Pixel format: " <<get_pixel_format(cam) << std::endl;

    get_exposure_time(cam);

    turn_on_IEEE1588(cam);

    // wait_until_slave(cam);

    print_IEEE1588_status(cam);

    set_trigger_mode_on(cam);

    set_trigger_source_to_action(cam);

    set_action_keys(cam);

    start_grabbing(cam);

    timer.syncToFirstInterval();

    for (size_t i = 0; i < 10; i++)
    {
        // std::thread thread2(issue_action_command,1,1,1,"255.255.255.255",100,0);
        // thread2.detach(); // 让线程独立运行
        issue_action_command();
        timer.syncToNextInterval();
    }

    // if (frame != NULL)
    // {
    //     save_non_raw_image("png", cam, frame);
    // }

    PressEnterToExit();

    // Clean up and close the SDK
    stop_grabbing(cam);
    close_device(cam);

    return 0;
}