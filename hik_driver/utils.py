# -- coding: utf-8 --

import sys
from ctypes import *
import logging
from .SDK.MvCameraControl_class import *


# 配置日志记录器
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')
logger = logging.getLogger(__name__)

def save_non_raw_image(save_type, frame_info, cam_instance):
    logger.info("Saving non-raw image...")
    
    if save_type == 1:
        mv_image_type = MV_Image_Jpeg
        file_path = "Image_w%d_h%d_fn%d.jpg" % (
            frame_info.stFrameInfo.nWidth, frame_info.stFrameInfo.nHeight, frame_info.stFrameInfo.nFrameNum)

    elif save_type == 2:
        mv_image_type = MV_Image_Bmp
        file_path = "Image_w%d_h%d_fn%d.bmp" % (
            frame_info.stFrameInfo.nWidth, frame_info.stFrameInfo.nHeight, frame_info.stFrameInfo.nFrameNum)
    elif save_type == 3:
        mv_image_type = MV_Image_Tif
        file_path = "Image_w%d_h%d_fn%d.tif" % (
            frame_info.stFrameInfo.nWidth, frame_info.stFrameInfo.nHeight, frame_info.stFrameInfo.nFrameNum)
    else:
        file_path = "Image_w%d_h%d_fn%d.png" % (
            frame_info.stFrameInfo.nWidth, frame_info.stFrameInfo.nHeight, frame_info.stFrameInfo.nFrameNum)
        mv_image_type = MV_Image_Png

    c_file_path = file_path.encode('ascii')
    stSaveParam = MV_SAVE_IMAGE_TO_FILE_PARAM_EX()
    stSaveParam.enPixelType = frame_info.stFrameInfo.enPixelType  # ch:相机对应的像素格式 | en:Camera pixel type
    stSaveParam.nWidth = frame_info.stFrameInfo.nWidth  # ch:相机对应的宽 | en:Width
    stSaveParam.nHeight = frame_info.stFrameInfo.nHeight  # ch:相机对应的高 | en:Height
    stSaveParam.nDataLen = frame_info.stFrameInfo.nFrameLen
    stSaveParam.pData = frame_info.pBufAddr
    stSaveParam.enImageType = mv_image_type  # ch:需要保存的图像类型 | en:Image format to save
    stSaveParam.pcImagePath = create_string_buffer(c_file_path)
    stSaveParam.iMethodValue = 1
    stSaveParam.nQuality = 80  # ch: JPG: (50,99], invalid in other format
    mv_ret = cam_instance.MV_CC_SaveImageToFileEx(stSaveParam)
    return mv_ret

def print_device_info(mvcc_dev_info):
    logger.info("Printing device info...")
    
    if mvcc_dev_info.nTLayerType == MV_GIGE_DEVICE or mvcc_dev_info.nTLayerType == MV_GENTL_GIGE_DEVICE:
        logger.info("gige device: ")
        print_gige_device_info(mvcc_dev_info)
    elif mvcc_dev_info.nTLayerType == MV_USB_DEVICE:
        logger.info("u3v device: ")
        print_u3v_device_info(mvcc_dev_info)
    elif mvcc_dev_info.nTLayerType == MV_GENTL_CAMERALINK_DEVICE:
        logger.info("CML device: ")
        print_cml_device_info(mvcc_dev_info)
    elif mvcc_dev_info.nTLayerType == MV_GENTL_CXP_DEVICE:
        logger.info("CXP device: ")
        print_cxp_device_info(mvcc_dev_info)
    elif mvcc_dev_info.nTLayerType == MV_GENTL_XOF_DEVICE:
        logger.info("XoF device: ")
        print_xof_device_info(mvcc_dev_info)

def print_gige_device_info(mvcc_dev_info):
    logger.info("Printing GigE device info...")
    
    strModeName = ""
    for per in mvcc_dev_info.SpecialInfo.stGigEInfo.chModelName:
        if per == 0:
            break
        strModeName = strModeName + chr(per)
    logger.info("device model name: %s" % strModeName)

    nip1 = ((mvcc_dev_info.SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24)
    nip2 = ((mvcc_dev_info.SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16)
    nip3 = ((mvcc_dev_info.SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8)
    nip4 = (mvcc_dev_info.SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff)
    logger.info("current ip: %d.%d.%d.%d" % (nip1, nip2, nip3, nip4))

def print_u3v_device_info(mvcc_dev_info):
    logger.info("Printing U3V device info...")
    
    strModeName = ""
    for per in mvcc_dev_info.SpecialInfo.stUsb3VInfo.chModelName:
        if per == 0:
            break
        strModeName = strModeName + chr(per)
    logger.info("device model name: %s" % strModeName)

    strSerialNumber = ""
    for per in mvcc_dev_info.SpecialInfo.stUsb3VInfo.chSerialNumber:
        if per == 0:
            break
        strSerialNumber = strSerialNumber + chr(per)
    logger.info("user serial number: %s" % strSerialNumber)

def print_cml_device_info(mvcc_dev_info):
    logger.info("Printing CML device info...")
    
    strModeName = ""
    for per in mvcc_dev_info.SpecialInfo.stCMLInfo.chModelName:
        if per == 0:
            break
        strModeName = strModeName + chr(per)
    logger.info("device model name: %s" % strModeName)

    strSerialNumber = ""
    for per in mvcc_dev_info.SpecialInfo.stCMLInfo.chSerialNumber:
        if per == 0:
            break
        strSerialNumber = strSerialNumber + chr(per)
    logger.info("user serial number: %s" % strSerialNumber)

def print_cxp_device_info(mvcc_dev_info):
    logger.info("Printing CXP device info...")
    
    strModeName = ""
    for per in mvcc_dev_info.SpecialInfo.stCXPInfo.chModelName:
        if per == 0:
            break
        strModeName = strModeName + chr(per)
    logger.info("device model name: %s" % strModeName)

    strSerialNumber = ""
    for per in mvcc_dev_info.SpecialInfo.stCXPInfo.chSerialNumber:
        if per == 0:
            break
        strSerialNumber = strSerialNumber + chr(per)
    logger.info("user serial number: %s" % strSerialNumber)

def print_xof_device_info(mvcc_dev_info):
    logger.info("Printing XoF device info...")
    
    strModeName = ""
    for per in mvcc_dev_info.SpecialInfo.stXoFInfo.chModelName:
        if per == 0:
            break
        strModeName = strModeName + chr(per)
    logger.info("device model name: %s" % strModeName)

    strSerialNumber = ""
    for per in mvcc_dev_info.SpecialInfo.stXoFInfo.chSerialNumber:
        if per == 0:
            break
        strSerialNumber = strSerialNumber + chr(per)
    logger.info("user serial number: %s" % strSerialNumber)

def enum_devices(tlayerType):
    logger.info("Enumerating devices...")
    
    deviceList = MV_CC_DEVICE_INFO_LIST()
    ret = MvCamera.MV_CC_EnumDevices(tlayerType, deviceList)
    if ret != 0:
        logger.info("enum devices fail! ret[0x%x]" % ret)
        sys.exit()

    if deviceList.nDeviceNum == 0:
        logger.info("find no device!")
        sys.exit()

    logger.info("Find %d devices!" % deviceList.nDeviceNum)

    for i in range(0, deviceList.nDeviceNum):
        mvcc_dev_info = cast(deviceList.pDeviceInfo[i], POINTER(MV_CC_DEVICE_INFO)).contents
        print_device_info(mvcc_dev_info)
    
    return deviceList

def open_device(cam, stDeviceList):
    logger.info("Opening device...")
    
    ret = cam.MV_CC_CreateHandle(stDeviceList)
    if ret != 0:
        raise Exception("create handle fail! ret[0x%x]" % ret)

    ret = cam.MV_CC_OpenDevice(MV_ACCESS_Exclusive, 0)
    if ret != 0:
        raise Exception("open device fail! ret[0x%x]" % ret)

    if stDeviceList.nTLayerType == MV_GIGE_DEVICE or stDeviceList.nTLayerType == MV_GENTL_GIGE_DEVICE:
        nPacketSize = cam.MV_CC_GetOptimalPacketSize()
        if int(nPacketSize) > 0:
            ret = cam.MV_CC_SetIntValue("GevSCPSPacketSize", nPacketSize)
            if ret != 0:
                logger.info("Warning: Set Packet Size fail! ret[0x%x]" % ret)
        else:
            logger.info("Warning: Get Packet Size fail! ret[0x%x]" % nPacketSize)

def close_device(cam):
    logger.info("Closing device...")
    input("Press Enter to close the device and exit...")
    cam.MV_CC_CloseDevice()
    cam.MV_CC_DestroyHandle()
    MvCamera.MV_CC_Finalize()
    logger.info("Device closed and SDK finalized")
    

def init_SDK():
    logger.info("Initializing SDK...")
    
    MvCamera.MV_CC_Initialize()

    tlayerType = (MV_GIGE_DEVICE | MV_USB_DEVICE | MV_GENTL_CAMERALINK_DEVICE
                | MV_GENTL_CXP_DEVICE | MV_GENTL_XOF_DEVICE)
    
    deviceList = enum_devices(tlayerType)

    nConnectionNum = input("please input the number of the device to connect:")

    if int(nConnectionNum) >= deviceList.nDeviceNum:
        logger.info("input error!")
        sys.exit()
        
        
    stDeviceList = cast(deviceList.pDeviceInfo[int(nConnectionNum)], POINTER(MV_CC_DEVICE_INFO)).contents

    cam = MvCamera()
    
    open_device(cam, stDeviceList)
    
    return cam

def start_grabbing(cam):
    logger.info("start grabbing...")
    ret = cam.MV_CC_StartGrabbing()
    if ret != 0:
        raise Exception("start grabbing fail! ret[0x%x]" % ret)
    
def capture_and_save_image(cam, save_type):
    logger.info("Capturing and saving image...")
    
    try:
        # ch:开始取流 | en:Start grab image
        start_grabbing(cam)

        # ch:获取的帧信息 | en: frame from device
        stOutFrame = MV_FRAME_OUT()
        memset(byref(stOutFrame), 0, sizeof(stOutFrame))

        ret = cam.MV_CC_GetImageBuffer(stOutFrame, 20000)
        if None != stOutFrame.pBufAddr and 0 == ret:
            logger.info("get one frame: Width[%d], Height[%d], nFrameNum[%d]" % (
            stOutFrame.stFrameInfo.nWidth, stOutFrame.stFrameInfo.nHeight, stOutFrame.stFrameInfo.nFrameNum))

            # ch:根据save_type选择保存格式 | en:Choose save format according to save_type
            if save_type.lower() == "raw":
                ret = save_raw(stOutFrame, cam)
            elif save_type.lower() == "jpg" or save_type.lower() == "jpeg":
                ret = save_non_raw_image(1, stOutFrame, cam)
            elif save_type.lower() == "bmp":
                ret = save_non_raw_image(2, stOutFrame, cam)
            elif save_type.lower() == "tif" or save_type.lower() == "tiff":
                ret = save_non_raw_image(3, stOutFrame, cam)
            elif save_type.lower() == "png":
                ret = save_non_raw_image(4, stOutFrame, cam)
            else:
                raise ValueError("Invalid save type: %s" % save_type)

            if ret != 0:
                cam.MV_CC_FreeImageBuffer(stOutFrame)
                raise Exception("save image fail! ret[0x%x]" % ret)
            else:
                logger.info("Save image success!")

            cam.MV_CC_FreeImageBuffer(stOutFrame)
        else:
            raise Exception("no data[0x%x]" % ret)

        # ch:停止取流 | en:Stop grab image
        ret = cam.MV_CC_StopGrabbing()
        if ret != 0:
            raise Exception("stop grabbing fail! ret[0x%x]" % ret)

    except Exception as e:
        logger.info(e)
        raise
    

def set_trigger_mode_Off(cam):
    logger.info("Setting trigger mode to Off...")
    
    ret = cam.MV_CC_SetEnumValue("TriggerMode", MV_TRIGGER_MODE_OFF)
    if ret != 0:
        raise Exception("set trigger mode fail! ret[0x%x]" % ret)
    
def set_trigger_mode_On(cam):
    logger.info("Setting trigger mode to On...")
    ret = cam.MV_CC_SetEnumValue("TriggerMode", MV_TRIGGER_MODE_ON)
    if ret != 0:
        raise Exception("set trigger mode fail! ret[0x%x]" % ret)

def set_trigger_source(cam,source:str):
    logger.info(f"Setting trigger source to {source}...")
    ret = cam.MV_CC_SetEnumValueByString("TriggerSource", source)
    if ret != 0:
        raise Exception("set trigger source fail! ret[0x%x]" % ret)
    

def set_action_keys(cam,action_device_key=1,action_group_key=1,group_mask=1):
    logger.info(f"Setting action keys...")
    
    ret = cam.MV_CC_SetIntValue('ActionDeviceKey',action_device_key)
    if ret != 0:
        raise Exception("set action device key fail! ret[0x%x]" % ret)
    
    ret = cam.MV_CC_SetIntValue('ActionGroupKey',action_group_key)
    if ret != 0:
        raise Exception("set action group key fail! ret[0x%x]" % ret)
    
    ret = cam.MV_CC_SetIntValue('ActionGroupMask',group_mask)
    if ret != 0:
        raise Exception("set action group mask fail! ret[0x%x]" % ret)
    
    
def issue_action_command(
    cam,
    action_device_key=1,
    action_group_key=1,
    group_mask=1,
    broadcast_address = "255.255.255.255",
    time_out = 100,
    action_time_enable = 0
    ):
    
    stActionCmdInfo = MV_ACTION_CMD_INFO()
    
    stActionCmdInfo.nDeviceKey = action_device_key
    stActionCmdInfo.nGroupKey = action_group_key
    stActionCmdInfo.nGroupMask = group_mask
    stActionCmdInfo.pBroadcastAddress = c_char_p(broadcast_address.encode("ASCII"))
    stActionCmdInfo.nTimeOut = time_out
    stActionCmdInfo.bActionTimeEnable = action_time_enable
    
    actionCmdResults = MV_ACTION_CMD_RESULT_LIST()
    
    ret = cam.MV_GIGE_IssueActionCommand(stActionCmdInfo,actionCmdResults)
    if ret != 0:
        raise Exception("Issue action command failed! ret[0x%x]" % ret)
    
    # 打印 Action 命令结果
    logger.info("Action Command Results:")
    for i in range(actionCmdResults.nNumResults):
        result = actionCmdResults.pResults[i]
        logger.info(f"Result {i+1}:")
        logger.info(f"Status: {result.nStatus==0}")
        
        
def pop_image_buffer(cam, timeout=1000):
    stOutFrame = MV_FRAME_OUT()
    memset(byref(stOutFrame), 0, sizeof(stOutFrame))

    ret = cam.MV_CC_GetImageBuffer(stOutFrame, timeout)
    if None != stOutFrame.pBufAddr and 0 == ret:
        logger.info("get one frame: Width[%d], Height[%d], nFrameNum[%d]" % (
        stOutFrame.stFrameInfo.nWidth, stOutFrame.stFrameInfo.nHeight, stOutFrame.stFrameInfo.nFrameNum))

        return stOutFrame


        
    
    
    
    


    