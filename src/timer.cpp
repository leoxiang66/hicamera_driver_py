#include "timer.h"

Timer::Timer(uint64_t sync_point, double freq)
    : sync_point_(sync_point), freq_(freq)
{
    interval_us_ = static_cast<uint64_t>(Ksec2micro / freq_);
    next_interval_us_ = 0;
}

// 获取当前时间的微秒时间戳
uint64_t Timer::getCurrentTimeUs() const
{
    auto now = std::chrono::high_resolution_clock::now();
    auto now_us = std::chrono::duration_cast<std::chrono::microseconds>(
                      now.time_since_epoch())
                      .count();
    return now_us;
}

// 同步到第一个时间间隔
void Timer::syncToFirstInterval()
{
    uint64_t current_time_us = getCurrentTimeUs();
    uint64_t sleep_time_us = sync_point_ - (current_time_us % sync_point_);
    next_interval_us_ = current_time_us + sleep_time_us;

    std::cout << "Wait until " << nanosec2date(next_interval_us_ * 1000) << std::endl;

    // 睡眠
    std::this_thread::sleep_for(std::chrono::microseconds(sleep_time_us) -
                                std::chrono::microseconds(21000));
}

// 同步到下一个时间间隔
void Timer::syncToNextInterval()
{
    next_interval_us_ += interval_us_;
    int64_t sleep_t_us = next_interval_us_ - getCurrentTimeUs();

    if (sleep_t_us > 0)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(sleep_t_us) -
                                    std::chrono::microseconds(2));
    }
    else
    {
        std::cout << "No sleep" << std::flush << std::endl;
    }
}