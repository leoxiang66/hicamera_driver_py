#ifndef TIMER_H
#define TIMER_H
#include "utils.h"

class Timer {
public:
    static const int Ksec2micro = 1000000;

    // 构造函数
    Timer(uint64_t sync_point = 10*Ksec2micro, double freq = 1);

    // 获取当前时间的微秒时间戳
    uint64_t getCurrentTimeUs() const;

    // 同步到第一个时间间隔
    void syncToFirstInterval();

    // 同步到下一个时间间隔
    void syncToNextInterval();

    void syncToNextIntervalMinusExposureTime(uint64_t exposure_time);

private:
    uint64_t sync_point_;       // 同步点
    double freq_;               // 频率
    uint64_t interval_us_;      // 时间间隔（微秒）
    uint64_t next_interval_us_; // 下一个时间间隔
};

#endif // TIMER_H