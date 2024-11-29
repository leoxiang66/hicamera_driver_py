from .utils import nanosec2date
import time

class Timer:
    Ksec2micro = 1000000

    def __init__(self, sync_point=10000000, freq=1):
        self.sync_point = sync_point
        self.freq = freq
        self.next_interval_us = None
        self.interval_us = int(Timer.Ksec2micro / freq)

    def get_current_time_us(self):
        # 获取当前时间的微秒时间戳
        current_time_us = int(time.time() * Timer.Ksec2micro)
        return current_time_us

    def sync_to_first_interval(self):
        current_time_us = self.get_current_time_us()
        sleep_time_us = self.sync_point - current_time_us % self.sync_point
        self.next_interval_us = current_time_us + sleep_time_us
        print(f"Wait until {nanosec2date(self.next_interval_us*1000)}")
        time.sleep(sleep_time_us / Timer.Ksec2micro - 0.021)

    def sync_to_next_interval(self):
        self.next_interval_us += self.interval_us
        sleep_t_us = self.next_interval_us - self.get_current_time_us()

        if sleep_t_us > 0:
            time.sleep(sleep_t_us / Timer.Ksec2micro - 0.000002)
        else:
            print("No sleep",flush=True)