#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "MvCameraControl.h"
#include <iostream>
#include <cstdint> // For int64_t
#include <chrono>
#include <ctime> // For std::localtime
#include <sstream>
#include <iomanip> 
#include "constants.h"
#include <thread>


int SaveImage(void *handle, MV_SAVE_IAMGE_TYPE enSaveImageType, MV_FRAME_OUT *stImageInfo);

bool IsHBPixelFormat(MvGvspPixelType enType);

void *init_SDK();

bool PrintDeviceInfo(MV_CC_DEVICE_INFO *pstMVDevInfo);

bool start_grabbing(void *handle);

void save_non_raw_image(const char *format, void *handle, MV_FRAME_OUT* stImageInfo);

void stop_grabbing(void *handle);

void close_device(void *handle);

void destroy_handle(void *handle);

void PressEnterToExit(void);

void set_exposure_auto_off(void *handle);

int GetFloatValue(void *handle, IN const char *strKey, OUT MVCC_FLOATVALUE *pFloatValue);

int GetIntValue(void *handle, IN const char *strKey, OUT MVCC_INTVALUE *pIntValue);

float get_exposure_time(void *handle);

int SetIntValue(void *handle, IN const char *strKey, IN unsigned int Value);

bool set_exposure_time(void *handle, float value);

int GetBoolValue(void *handle, IN const char *strKey, OUT bool *pbValue);

int SetBoolValue(void *handle, IN const char *strKey, IN bool bValue);

int GetStringValue(void *handle, IN const char *strKey, MVCC_STRINGVALUE *pStringValue);

int SetStringValue(void *handle, IN const char *strKey, IN const char *strValue);

bool turn_on_IEEE1588(void *handle);

void wait_until_slave(void *handle);

void print_IEEE1588_status(void *handle);

bool set_trigger_mode_on(void *handle);

bool set_trigger_source(void *handle, const char *source);

bool set_trigger_source_to_action(void *handle);

bool set_action_keys(void *handle, unsigned int action_device_key = 1, unsigned int action_group_key = 1, unsigned int group_mask = 1);

MV_FRAME_OUT* pop_image_buffer(void *handle, unsigned int timeout = 1000, bool print_info = true);



void print_frame_info(MV_FRAME_OUT *frame, bool only_timestamp = false);

int64_t combine_high_low(unsigned int high, unsigned int low);

std::string nanosec2date(int64_t nanoseconds);



void issue_action_command(unsigned int action_device_key = 1, unsigned int action_group_key = 1, unsigned int group_mask = 1, const char *broadcast_address = "255.255.255.255", unsigned int time_out = 100,
                          unsigned int action_time_enable = 0);