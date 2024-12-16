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
#include "frame.h"

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
 * @param camera_idx Index of the camera to select
 * @return Pointer to the initialized SDK context, or nullptr on failure.
 */
void *init_SDK(unsigned int camera_idx);

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
uint64_t print_frame_info(MV_FRAME_OUT *frame, bool only_timestamp = false);



/**
 * @brief Combine high and low 32-bit values into a 64-bit integer.
 *
 * @param high High 32 bits.
 * @param low Low 32 bits.
 * @return Combined unsigned 64-bit integer.
 */
uint64_t combine_high_low(unsigned int high, unsigned int low);

/**
 * @brief Convert nanoseconds to a human-readable date format.
 * 
 * @param nanoseconds Timestamp in nanoseconds.
 * @return Formatted date string.
 */
std::string nanosec2date(uint64_t nanoseconds);

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




/**
 * @brief Get the enumeration value for a specified key.
 * 
 * This function retrieves the enumeration value associated with the given key.
 * 
 * @param handle Device handle.
 * @param strKey The key for which to retrieve the enumeration value.
 * @param pEnumValue Pointer to the structure that will receive the enumeration value.
 * @return int Status code indicating success or failure.
 */
int GetEnumValue(void *handle, 
                 IN const char *strKey, 
                 OUT MVCC_ENUMVALUE *pEnumValue);

/**
 * @brief Set the enumeration value for a specified key.
 * 
 * This function sets the enumeration value for the specified key.
 * 
 * @param handle Device handle.
 * @param strKey The key for which to set the enumeration value.
 * @param nValue The enumeration value to set.
 * @return int Status code indicating success or failure.
 */
int SetEnumValue(void *handle, 
                 IN const char *strKey, 
                 IN unsigned int nValue);

/**
 * @brief Set the enumeration value using a string.
 * 
 * This function sets the enumeration value for the specified key using a string representation.
 * 
 * @param handle Device handle.
 * @param strKey The key for which to set the enumeration value.
 * @param sValue The string representation of the enumeration value to set.
 * @return int Status code indicating success or failure.
 */
int SetEnumValueByString(void *handle, 
                         IN const char *strKey, 
                         IN const char *sValue);

/**
 * @brief Get the current pixel format of the camera.
 * 
 * This function retrieves the pixel format currently set for the camera.
 * 
 * @param handle Device handle.
 * @return unsigned int The current pixel format.
 */
unsigned int get_pixel_format(void *handle);

/**
 * @brief Set the pixel format for the camera.
 * 
 * This function sets the pixel format for the camera.
 * 
 * @param handle Device handle.
 * @param value The pixel format to set.
 * @return bool True if the operation was successful, false otherwise.
 */
bool set_pixel_format(void *handle, unsigned int value);

/**
 * @brief Get frame information from the camera.
 * 
 * This function retrieves frame information for the specified frame.
 * 
 * @param frame Pointer to the frame information structure.
 * @return FrameInfo* Pointer to the frame information structure.
 */
FrameInfo *get_frame_info(MV_FRAME_OUT_INFO_EX *frame);

/**
 * @brief Print the current time in a specific format.
 * 
 * This function retrieves the current time and prints it in a specified format.
 * 
 * @return uint64_t The current time in milliseconds since epoch.
 */
uint64_t print_current_time();

/**
 * @brief Register an image callback function.
 * 
 * This function registers a callback function that will be called when an image is available.
 * 
 * @param handle Device handle.
 * @param image_cb Pointer to the callback function that processes the image data.
 */
void register_img_callback(void *handle, 
                           void(__stdcall *image_cb)(unsigned char *pData, 
                                                     MV_FRAME_OUT_INFO_EX *pFrameInfo, 
                                                     void *pUser));

/**
 * @brief Watch for specific events from the camera.
 * 
 * This function registers a callback function to be called when a specified event occurs.
 * 
 * @param handle Device handle.
 * @param event_name The name of the event to watch for.
 * @param event_cb Pointer to the callback function that processes the event information.
 */
void watch_event(void *handle, 
                 const char *event_name, 
                 void (*event_cb)(MV_EVENT_OUT_INFO *pEventInfo, void *pUser));

/**
 * @brief Disable the trigger mode of the device.
 * 
 * This function disables the trigger mode of the connected device, ensuring that the device operates in free-run mode.
 * 
 * @param handle Device handle.
 * @return `true` if the trigger mode was successfully disabled, `false` otherwise.
 */
bool set_trigger_mode_off(void *handle);

/**
 * @brief Disable IEEE 1588 Precision Time Protocol (PTP).
 * 
 * This function disables the IEEE 1588 protocol on the device, stopping time synchronization with other devices.
 * 
 * @param handle Device handle.
 * @return `true` if IEEE 1588 was successfully disabled, `false` otherwise.
 */
bool turn_off_IEEE1588(void *handle);

/**
 * @brief Enable automatic exposure mode.
 * 
 * This function enables the automatic exposure mode on the device, allowing it to adjust exposure settings dynamically based on the environment.
 * 
 * @param handle Device handle.
 */
void set_exposure_auto_on(void *handle);

#endif


