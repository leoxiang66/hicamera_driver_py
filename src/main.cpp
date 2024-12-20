#include "timer.h"
#include "utils.h"

double count = 0;

void pop_thread(void *cam)
{
    while (true)
    {
        auto frame = pop_image_buffer(cam, 1, false);
        if (frame != NULL)
        {
            std::cout << "Time comparision:" << std::endl;
            printf("Time1: ");
            auto time1 = print_frame_info(frame, true);
            printf("Time2: ");
            auto time2 = print_current_time();
            std::cout << "Time2 - Time1 出图时间: " << (time2 - time1) / 1000000 << "ms" << std::endl;
            printf("\n");
            count += 1;
        }
    }
}

uint64_t last_time = -1;
int printed = 0;

void __stdcall ImageCallBackEx(unsigned char *pData, MV_FRAME_OUT_INFO_EX *pFrameInfo, void *pUser)
{
    if (pFrameInfo && printed < 2)
    {
        // printf("GetOneFrame, Width[%d], Height[%d], nFrameNum[%d]\n",
        //     pFrameInfo->nExtendWidth, pFrameInfo->nExtendHeight, pFrameInfo->nFrameNum);

        auto timestamp_nano = combine_high_low(pFrameInfo->nDevTimeStampHigh, pFrameInfo->nDevTimeStampLow);

        std::cout << "Time comparision:" << std::endl;
        printf("Time1: ");
        std::cout << nanosec2date(timestamp_nano) << std::endl;
        printf("Time2: ");

        auto time2 = pFrameInfo->nHostTimeStamp * 1000000;
        std::cout << nanosec2date(time2) << std::endl;
        std::cout << "Time2 - Time1 出图时间: " << (time2 - timestamp_nano) / 1000000 << "ms" << std::endl;
        // std::cout << "Time2 - Time1 出图时间: " << (last_time - timestamp_nano) / 1000000 << "ms" << std::endl;

        printf("Time3: ");
        auto time3 = print_current_time();
        printf("\n");
        count += 1;
        last_time = time2;
        printed++;
    }
}

void print_thread()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::cout << "FPS: " << count << std::endl;
        std::cout << "平均出图时间(ms): " << 1000 / count << std::endl;
        count = 0;
    }
}

void __stdcall EventCallBack(MV_EVENT_OUT_INFO *pEventInfo, void *pUser)
{
    if (pEventInfo && printed <2)
    {
        int64_t nBlockId = pEventInfo->nBlockIdHigh;
        nBlockId = (nBlockId << 32) + pEventInfo->nBlockIdLow;

        int64_t nTimestamp = pEventInfo->nTimestampHigh;
        nTimestamp = (nTimestamp << 32) + pEventInfo->nTimestampLow;

        std::cout << "Frame end:" <<nanosec2date(nTimestamp) << std::endl;
    }
}

int main()
{

    // uint64_t sync_point = 10000000;
    // Timer timer(sync_point, 30.0);

    void *cam = init_SDK(0);

    // 启动线程并运行 pop_thread 函数
    // std::thread thread1(pop_thread, cam);
    // thread1.detach(); // 让线程独立运行

    // std::thread thread2(print_thread);
    // thread2.detach();

    if (cam == NULL)
    {
        printf("Failed to initialize SDK.\n");
        return 1;
    }

    // set_exposure_auto_on(cam);

    set_exposure_auto_off(cam);

    set_exposure_time(cam, 15);

    // set_pixel_format(cam, PixelType_Gvsp_RGB8_Packed); // 50ms

    set_pixel_format(cam, PixelType_Gvsp_BayerRG8);
    // set_pixel_format(cam, PixelType_Gvsp_Mono8);

    std::cout << "Pixel format: " << get_pixel_format(cam) << std::endl;

    get_exposure_time(cam);

    set_gamma_correction(cam, 0.3);

    turn_on_IEEE1588(cam);
    wait_until_slave(cam);
    // turn_off_IEEE1588(cam);

    set_trigger_mode_off(cam);

    auto nRet = MV_CC_RegisterImageCallBackEx(cam, ImageCallBackEx, cam);
    if (MV_OK != nRet)
    {
        printf("MV_CC_RegisterImageCallBackEx fail! nRet [%x]\n", nRet);
    }

    // ch:开启Event | en:Set Event of ExposureEnd On
    nRet = MV_CC_EventNotificationOn(cam, "FrameEnd");
    if (MV_OK != nRet)
    {
        printf("Set Event Notification On fail! nRet [0x%x]\n", nRet);
    }

    nRet = MV_CC_RegisterEventCallBackEx(cam, "FrameEnd", EventCallBack, cam);
    if (MV_OK != nRet)
    {
        printf("Register Event CallBack fail! nRet [0x%x]\n", nRet);
    }

    // set_trigger_mode_on(cam);

    // set_trigger_source_to_action(cam);

    // set_action_keys(cam);

    // PressEnterToExit();

    std::cout << "开始的时间:";

    print_current_time();

    start_grabbing(cam);

    std::this_thread::sleep_for(std::chrono::seconds(10));

    // set_exposure_time(cam, 20000.0);

    // timer.syncToFirstInterval();

    // for (size_t i = 0; i < 1000; i++)
    // {
    //     // std::thread thread2(issue_action_command,1,1,1,"255.255.255.255",100,0);
    //     // thread2.detach(); // 让线程独立运行
    //     issue_action_command();
    //     timer.syncToNextInterval();
    // }

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