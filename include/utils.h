/**
 * @file utils.h
 * @brief Utility functions for camera control using MvCamera SDK.
 * 
 * This header provides various utility functions for interacting with a camera
 * using the MvCamera SDK, including device initialization, image processing, 
 * and camera parameter configuration.
 * 
 * Dependencies:
 * - MvCameraControl.h
 * - chrono, iostream, cstdint, ctime, thread, sstream
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "MvCameraControl.h"
#include <iostream>
#include <cstdint>  // For int64_t
#include <chrono>
#include <ctime>    // For std::localtime
#include <sstream>
#include <iomanip>
#include "constants.h"
#include <thread>

/**
 * @brief Save an image captured by the camera.
 * 
 * @param handle Camera handle.
 * @param enSaveImageType Image save format (e.g., JPEG, BMP).
 * @param stImageInfo Pointer to the image frame information.
 * @return 0 on success, non-zero on failure.
 */
int SaveImage(void *handle, MV_SAVE_IAMGE_TYPE enSaveImageType, MV_FRAME_OUT *stImageInfo);

/**
 * @brief Check if a pixel format is HB-compatible.
 * 
 * @param enType Pixel format type.
 * @return true if the pixel format is HB-compatible, false otherwise.
 */
bool IsHBPixelFormat(MvGvspPixelType enType);

/**
 * @brief Initialize the camera SDK.
 * 
 * @return Pointer to the initialized SDK context, or nullptr on failure.
 */
void *init_SDK();

/**
 * @brief Print device information.
 * 
 * @param pstMVDevInfo Pointer to the camera device information.
 * @return true on success, false on failure.
 */
bool PrintDeviceInfo(MV_CC_DEVICE_INFO *pstMVDevInfo);

/**
 * @brief Start grabbing images from the camera.
 * 
 * @param handle Camera handle.
 * @return true on success, false on failure.
 */
bool start_grabbing(void *handle);

/**
 * @brief Save a non-raw image to disk in the specified format.
 * 
 * @param format Image format (e.g., "jpg", "bmp").
 * @param handle Camera handle.
 * @param stImageInfo Pointer to the captured image frame.
 */
void save_non_raw_image(const char *format, void *handle, MV_FRAME_OUT *stImageInfo);

/**
 * @brief Stop grabbing images from the camera.
 * 
 * @param handle Camera handle.
 */
void stop_grabbing(void *handle);

/**
 * @brief Close the camera device.
 * 
 * @param handle Camera handle.
 */
void close_device(void *handle);

/**
 * @brief Destroy the camera handle.
 * 
 * @param handle Camera handle.
 */
void destroy_handle(void *handle);

/**
 * @brief Wait for the user to press Enter to exit.
 */
void PressEnterToExit(void);

/**
 * @brief Disable the camera's automatic exposure mode.
 * 
 * @param handle Camera handle.
 */
void set_exposure_auto_off(void *handle);

/**
 * @brief Get a float parameter value from the camera.
 * 
 * @param handle Camera handle.
 * @param strKey Parameter key (e.g., "ExposureTime").
 * @param pFloatValue Pointer to store the retrieved value.
 * @return 0 on success, non-zero on failure.
 */
int GetFloatValue(void *handle, IN const char *strKey, OUT MVCC_FLOATVALUE *pFloatValue);

/**
 * @brief Get an integer parameter value from the camera.
 * 
 * @param handle Camera handle.
 * @param strKey Parameter key.
 * @param pIntValue Pointer to store the retrieved value.
 * @return 0 on success, non-zero on failure.
 */
int GetIntValue(void *handle, IN const char *strKey, OUT MVCC_INTVALUE *pIntValue);

/**
 * @brief Get the camera's exposure time.
 * 
 * @param handle Camera handle.
 * @return Exposure time in microseconds.
 */
float get_exposure_time(void *handle);

/**
 * @brief Set an integer parameter value on the camera.
 * 
 * @param handle Camera handle.
 * @param strKey Parameter key.
 * @param Value The value to set.
 * @return 0 on success, non-zero on failure.
 */
int SetIntValue(void *handle, IN const char *strKey, IN unsigned int Value);

/**
 * @brief Set the camera's exposure time.
 * 
 * @param handle Camera handle.
 * @param value New exposure time in microseconds.
 * @return true on success, false on failure.
 */
bool set_exposure_time(void *handle, float value);

/**
 * @brief Get a boolean parameter value from the camera.
 * 
 * @param handle Camera handle.
 * @param strKey Parameter key.
 * @param pbValue Pointer to store the retrieved value.
 * @return 0 on success, non-zero on failure.
 */
int GetBoolValue(void *handle, IN const char *strKey, OUT bool *pbValue);

/**
 * @brief Set a boolean parameter value on the camera.
 * 
 * @param handle Camera handle.
 * @param strKey Parameter key.
 * @param bValue The value to set.
 * @return 0 on success, non-zero on failure.
 */
int SetBoolValue(void *handle, IN const char *strKey, IN bool bValue);

/**
 * @brief Get a string parameter value from the camera.
 * 
 * @param handle Camera handle.
 * @param strKey Parameter key.
 * @param pStringValue Pointer to store the retrieved value.
 * @return 0 on success, non-zero on failure.
 */
int GetStringValue(void *handle, IN const char *strKey, MVCC_STRINGVALUE *pStringValue);

/**
 * @brief Set a string parameter value on the camera.
 * 
 * @param handle Camera handle.
 * @param strKey Parameter key.
 * @param strValue The string value to set.
 * @return 0 on success, non-zero on failure.
 */
int SetStringValue(void *handle, IN const char *strKey, IN const char *strValue);

/**
 * @brief Enable IEEE1588 precision time protocol on the camera.
 * 
 * @param handle Camera handle.
 * @return true on success, false on failure.
 */
bool turn_on_IEEE1588(void *handle);

/**
 * @brief Wait until the camera is in slave mode.
 * 
 * @param handle Camera handle.
 */
void wait_until_slave(void *handle);

/**
 * @brief Print the status of IEEE1588 on the camera.
 * 
 * @param handle Camera handle.
 */
void print_IEEE1588_status(void *handle);

/**
 * @brief Enable trigger mode on the camera.
 * 
 * @param handle Camera handle.
 * @return true on success, false on failure.
 */
bool set_trigger_mode_on(void *handle);

/**
 * @brief Set the trigger source for the camera.
 * 
 * @param handle Camera handle.
 * @param source Trigger source (e.g., "Line0").
 * @return true on success, false on failure.
 */
bool set_trigger_source(void *handle, const char *source);

/**
 * @brief Set the trigger source to "Action" mode.
 * 
 * @param handle Camera handle.
 * @return true on success, false on failure.
 */
bool set_trigger_source_to_action(void *handle);

/**
 * @brief Configure action command keys on the camera.
 * 
 * @param handle Camera handle.
 * @param action_device_key Action device key (default: 1).
 * @param action_group_key Action group key (default: 1).
 * @param group_mask Group mask (default: 1).
 * @return true on success, false on failure.
 */
bool set_action_keys(void *handle, unsigned int action_device_key = 1, unsigned int action_group_key = 1, unsigned int group_mask = 1);

/**
 * @brief Retrieve an image buffer from the camera.
 * 
 * @param handle Camera handle.
 * @param timeout Timeout in milliseconds (default: 1000).
 * @param print_info Whether to print image information (default: true).
 * @return Pointer to the retrieved image frame, or nullptr on failure.
 */
MV_FRAME_OUT *pop_image_buffer(void *handle, unsigned int timeout = 1000, bool print_info = true);

/**
 * @brief Print information about an image frame.
 * 
 * @param frame Pointer to the image frame.
 * @param only_timestamp Whether to only print the timestamp (default: false).
 */
void print_frame_info(MV_FRAME_OUT *frame, bool only_timestamp = false);

/**
 * @brief Combine high and low 32-bit values into a 64-bit integer.
 * 
 * @param high High 32 bits.
 * @param low Low 32 bits.
 * @return Combined 64-bit integer.
 */
int64_t combine_high_low(unsigned int high, unsigned int low);

/**
 * @brief Convert nanoseconds to a human-readable date format.
 * 
 * @param nanoseconds Timestamp in nanoseconds.
 * @return Formatted date string.
 */
std::string nanosec2date(int64_t nanoseconds);

/**
 * @brief Issue an action command to the camera.
 * 
 * @param action_device_key Action device key (default: 1).
 * @param action_group_key Action group key (default: 1).
 * @param group_mask Group mask (default: 1).
 * @param broadcast_address Broadcast address (default: "255.255.255.255").
 * @param time_out Timeout in seconds (default: 1).
 * @param action_time_enable Whether to enable action time (default: 0).
 */
void issue_action_command(unsigned int action_device_key = 1, unsigned int action_group_key = 1, unsigned int group_mask = 1, const char *broadcast_address = "255.255.255.255", unsigned int time_out = 1, unsigned int action_time_enable = 0);

#endif