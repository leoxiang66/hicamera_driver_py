#ifndef FRAME_H
#define FRAME_H

#include <cstdint>
// #include <string>

class FrameInfo
{
public:
    // 构造函数
    FrameInfo(
        const uint64_t timestamp_nano,
        const unsigned int &frame_id,
        // const std::string &encoding,
        const unsigned short width,
        const unsigned short height)
        : timestamp_nano(timestamp_nano),
          frame_id(frame_id),
          //   encoding(encoding),
          width(width),
          height(height)
    {
    }

    // 获取时间戳（纳秒）
    uint64_t getTimestampNano() const { return timestamp_nano; }

    // 获取帧ID
    unsigned int getFrameID() const { return frame_id; }

    // 获取图像编码
    // std::string getEncoding() const { return encoding; }

    // 获取图像宽度
    unsigned short getWidth() const { return width; }

    // 获取图像高度
    unsigned short getHeight() const { return height; }

private:
    const uint64_t timestamp_nano; // 时间戳（纳秒）
    unsigned int frame_id;          // 帧ID，用于标识帧的来源
    // std::string encoding;          // 图像编码，例如"mono8", "bgr8", "rgb8"等
    unsigned short width;  // 图像宽度
    unsigned short height; // 图像高度
};

#endif // FRAME_H