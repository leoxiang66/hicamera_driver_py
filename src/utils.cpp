#include "utils.h"


// ch:����ͼƬ | en:Save Image
int SaveImage(void* handle, MV_SAVE_IAMGE_TYPE enSaveImageType, MV_FRAME_OUT *stImageInfo)
{
    char chImageName[256] = {0};
    MV_CC_IMAGE stImg;
    MV_CC_SAVE_IMAGE_PARAM stSaveParams;
    memset(&stSaveParams, 0, sizeof(MV_CC_SAVE_IMAGE_PARAM));
    memset(&stImg, 0, sizeof(MV_CC_SAVE_IMAGE_PARAM));

    stImg.enPixelType = stImageInfo->stFrameInfo.enPixelType;
    stImg.nHeight = stImageInfo->stFrameInfo.nExtendHeight;
    stImg.nWidth = stImageInfo->stFrameInfo.nExtendWidth;
    stImg.nImageBufLen = stImageInfo->stFrameInfo.nFrameLenEx;
    stImg.pImageBuf = stImageInfo->pBufAddr;

    stSaveParams.enImageType = enSaveImageType;
    stSaveParams.iMethodValue = 1;
    stSaveParams.nQuality = 99;

    if (MV_Image_Bmp == stSaveParams.enImageType)
    {
        sprintf(chImageName, "Image_w%d_h%d_fn%03d.bmp", stImageInfo->stFrameInfo.nExtendWidth, stImageInfo->stFrameInfo.nExtendHeight, stImageInfo->stFrameInfo.nFrameNum);
    }
    else if (MV_Image_Jpeg == stSaveParams.enImageType)
    {
        sprintf(chImageName, "Image_w%d_h%d_fn%03d.jpg", stImageInfo->stFrameInfo.nExtendWidth, stImageInfo->stFrameInfo.nExtendHeight, stImageInfo->stFrameInfo.nFrameNum);
    }
    else if (MV_Image_Tif == stSaveParams.enImageType)
    {
        sprintf(chImageName, "Image_w%d_h%d_fn%03d.tif", stImageInfo->stFrameInfo.nExtendWidth, stImageInfo->stFrameInfo.nExtendHeight, stImageInfo->stFrameInfo.nFrameNum);
    }
    else if (MV_Image_Png == stSaveParams.enImageType)
    {
        sprintf(chImageName, "Image_w%d_h%d_fn%03d.png", stImageInfo->stFrameInfo.nExtendWidth, stImageInfo->stFrameInfo.nExtendHeight, stImageInfo->stFrameInfo.nFrameNum);
    }

    int nRet = MV_CC_SaveImageToFileEx2(handle, &stImg, &stSaveParams, (char *)chImageName);

    return nRet;
}

bool IsHBPixelFormat(MvGvspPixelType enType)
{
    switch (enType)
    {
    case PixelType_Gvsp_HB_Mono8:
    case PixelType_Gvsp_HB_Mono10:
    case PixelType_Gvsp_HB_Mono10_Packed:
    case PixelType_Gvsp_HB_Mono12:
    case PixelType_Gvsp_HB_Mono12_Packed:
    case PixelType_Gvsp_HB_Mono16:
    case PixelType_Gvsp_HB_RGB8_Packed:
    case PixelType_Gvsp_HB_BGR8_Packed:
    case PixelType_Gvsp_HB_RGBA8_Packed:
    case PixelType_Gvsp_HB_BGRA8_Packed:
    case PixelType_Gvsp_HB_RGB16_Packed:
    case PixelType_Gvsp_HB_BGR16_Packed:
    case PixelType_Gvsp_HB_RGBA16_Packed:
    case PixelType_Gvsp_HB_BGRA16_Packed:
    case PixelType_Gvsp_HB_YUV422_Packed:
    case PixelType_Gvsp_HB_YUV422_YUYV_Packed:
    case PixelType_Gvsp_HB_BayerGR8:
    case PixelType_Gvsp_HB_BayerRG8:
    case PixelType_Gvsp_HB_BayerGB8:
    case PixelType_Gvsp_HB_BayerBG8:
    case PixelType_Gvsp_HB_BayerRBGG8:
    case PixelType_Gvsp_HB_BayerGB10:
    case PixelType_Gvsp_HB_BayerGB10_Packed:
    case PixelType_Gvsp_HB_BayerBG10:
    case PixelType_Gvsp_HB_BayerBG10_Packed:
    case PixelType_Gvsp_HB_BayerRG10:
    case PixelType_Gvsp_HB_BayerRG10_Packed:
    case PixelType_Gvsp_HB_BayerGR10:
    case PixelType_Gvsp_HB_BayerGR10_Packed:
    case PixelType_Gvsp_HB_BayerGB12:
    case PixelType_Gvsp_HB_BayerGB12_Packed:
    case PixelType_Gvsp_HB_BayerBG12:
    case PixelType_Gvsp_HB_BayerBG12_Packed:
    case PixelType_Gvsp_HB_BayerRG12:
    case PixelType_Gvsp_HB_BayerRG12_Packed:
    case PixelType_Gvsp_HB_BayerGR12:
    case PixelType_Gvsp_HB_BayerGR12_Packed:
        return true;
    default:
        return false;
    }
}

void *init_SDK()
{
    // logging

    int nRet = MV_OK;

    nRet = MV_CC_Initialize();
    if (MV_OK != nRet)
    {
        printf("Initialize SDK fail! nRet [0x%x]\n", nRet);
        return NULL;
    }

    // ch:ö���豸 | en:Enum device
    MV_CC_DEVICE_INFO_LIST stDeviceList;
    memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
    nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE | MV_GENTL_CAMERALINK_DEVICE | MV_GENTL_CXP_DEVICE | MV_GENTL_XOF_DEVICE, &stDeviceList);
    if (MV_OK != nRet)
    {
        printf("Enum Devices fail! nRet [0x%x]\n", nRet);
        return NULL;
    }

    if (stDeviceList.nDeviceNum > 0)
    {
        printf("Find %d Devices!\n", stDeviceList.nDeviceNum);
        for (unsigned int i = 0; i < stDeviceList.nDeviceNum; i++)
        {
            printf("[device %d]:\n", i);
            MV_CC_DEVICE_INFO *pDeviceInfo = stDeviceList.pDeviceInfo[i];
            if (NULL == pDeviceInfo)
            {
                return NULL;
            }
            printf("Print device info ...\n");
            PrintDeviceInfo(pDeviceInfo);
        }
    }
    else
    {
        printf("Find No Devices!\n");
        return NULL;
    }

    printf("Please Intput camera index: ");
    unsigned int nIndex = 0;
    scanf("%d", &nIndex);

    if (nIndex >= stDeviceList.nDeviceNum)
    {
        printf("Input error!\n");
        return NULL;
    }

    // ch:ѡ���豸��������� | en:Select device and create handle
    void *handle = NULL;
    nRet = MV_CC_CreateHandle(&handle, stDeviceList.pDeviceInfo[nIndex]);
    if (MV_OK != nRet)
    {
        printf("Create Handle fail! nRet [0x%x]\n", nRet);
        return NULL;
    }

    // ch:���豸 | en:Open device
    nRet = MV_CC_OpenDevice(handle);
    if (MV_OK != nRet)
    {
        printf("Open Device fail! nRet [0x%x]\n", nRet);
        return NULL;
    }

    // ch:̽��������Ѱ���С(ֻ��GigE�����Ч) | en:Detection network optimal package size(It only works for the GigE camera)
    if (stDeviceList.pDeviceInfo[nIndex]->nTLayerType == MV_GIGE_DEVICE)
    {
        int nPacketSize = MV_CC_GetOptimalPacketSize(handle);
        if (nPacketSize > 0)
        {
            nRet = MV_CC_SetIntValue(handle, "GevSCPSPacketSize", nPacketSize);
            if (nRet != MV_OK)
            {
                printf("Warning: Set Packet Size fail nRet [0x%x]!", nRet);
            }
        }
        else
        {
            printf("Warning: Get Packet Size fail nRet [0x%x]!", nPacketSize);
        }
    }

    return handle;
}

bool PrintDeviceInfo(MV_CC_DEVICE_INFO *pstMVDevInfo)
{
    if (NULL == pstMVDevInfo)
    {
        printf("The Pointer of pstMVDevInfo is NULL!\n");
        return false;
    }
    if (pstMVDevInfo->nTLayerType == MV_GIGE_DEVICE)
    {
        int nIp1 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
        int nIp2 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
        int nIp3 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
        int nIp4 = (pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);

        // ch:��ӡ��ǰ���ip���û��Զ������� | en:print current ip and user defined name
        printf("CurrentIp: %d.%d.%d.%d\n", nIp1, nIp2, nIp3, nIp4);
        printf("Device Type: %d\n", pstMVDevInfo->nTLayerType);
        printf("UserDefinedName: %s\n\n", pstMVDevInfo->SpecialInfo.stGigEInfo.chUserDefinedName);
    }
    else if (pstMVDevInfo->nTLayerType == MV_USB_DEVICE)
    {
        printf("UserDefinedName: %s\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName);
        printf("Serial Number: %s\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.chSerialNumber);
        printf("Device Type: %d\n", pstMVDevInfo->nTLayerType);
        printf("Device Number: %d\n\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.nDeviceNumber);
    }
    else if (pstMVDevInfo->nTLayerType == MV_GENTL_GIGE_DEVICE)
    {
        printf("UserDefinedName: %s\n", pstMVDevInfo->SpecialInfo.stGigEInfo.chUserDefinedName);
        printf("Serial Number: %s\n", pstMVDevInfo->SpecialInfo.stGigEInfo.chSerialNumber);
        printf("Device Type: %d\n", pstMVDevInfo->nTLayerType);
        printf("Model Name: %s\n\n", pstMVDevInfo->SpecialInfo.stGigEInfo.chModelName);
    }
    else if (pstMVDevInfo->nTLayerType == MV_GENTL_CAMERALINK_DEVICE)
    {
        printf("UserDefinedName: %s\n", pstMVDevInfo->SpecialInfo.stCMLInfo.chUserDefinedName);
        printf("Serial Number: %s\n", pstMVDevInfo->SpecialInfo.stCMLInfo.chSerialNumber);
        printf("Device Type: %d\n", pstMVDevInfo->nTLayerType);
        printf("Model Name: %s\n\n", pstMVDevInfo->SpecialInfo.stCMLInfo.chModelName);
    }
    else if (pstMVDevInfo->nTLayerType == MV_GENTL_CXP_DEVICE)
    {
        printf("UserDefinedName: %s\n", pstMVDevInfo->SpecialInfo.stCXPInfo.chUserDefinedName);
        printf("Serial Number: %s\n", pstMVDevInfo->SpecialInfo.stCXPInfo.chSerialNumber);
        printf("Device Type: %d\n", pstMVDevInfo->nTLayerType);
        printf("Model Name: %s\n\n", pstMVDevInfo->SpecialInfo.stCXPInfo.chModelName);
    }
    else if (pstMVDevInfo->nTLayerType == MV_GENTL_XOF_DEVICE)
    {
        printf("UserDefinedName: %s\n", pstMVDevInfo->SpecialInfo.stXoFInfo.chUserDefinedName);
        printf("Serial Number: %s\n", pstMVDevInfo->SpecialInfo.stXoFInfo.chSerialNumber);
        printf("Device Type: %d\n", pstMVDevInfo->nTLayerType);
        printf("Model Name: %s\n\n", pstMVDevInfo->SpecialInfo.stXoFInfo.chModelName);
    }
    else
    {
        printf("Not support.\n");
    }

    return true;
}

bool start_grabbing(void* handle)
{
    auto nRet = MV_CC_StartGrabbing(handle);
    if (MV_OK != nRet)
    {
        printf("Start Grabbing fail! nRet [0x%x]\n", nRet);
        return false;
    }

    return true;
}

void save_non_raw_image(char chSaveImageType[], void* handle)
{
    // ch:��ȡ���ݰ���С | en:Get payload size
    MVCC_INTVALUE stParam;
    memset(&stParam, 0, sizeof(MVCC_INTVALUE));
    auto nRet = MV_CC_GetIntValue(handle, "PayloadSize", &stParam);
    if (MV_OK != nRet)
    {
        printf("Get PayloadSize fail! nRet [0x%x]\n", nRet);
        return;
    }
    unsigned int nPayloadSize = stParam.nCurValue;

    unsigned char *pDstBuf = NULL;
    MV_FRAME_OUT stImageInfo = {0};
    MV_CC_HB_DECODE_PARAM stDecodeParam = {0};
    nRet = MV_CC_GetImageBuffer(handle, &stImageInfo, 20000); // ���������Ҫ�����ͼ���ȡ���
    if (nRet == MV_OK)
    {
        printf("Get Image Buffer: Width[%d], Height[%d], FrameNum[%d]\n",
               stImageInfo.stFrameInfo.nExtendWidth, stImageInfo.stFrameInfo.nExtendHeight, stImageInfo.stFrameInfo.nFrameNum);

        printf("Please Input Save Image Type(raw/Jpeg/bmp/tiff/png):");
        while (true)
        {
            char chSaveImageType[128] = {0};
            scanf("%s", chSaveImageType);
            if (0 == strcmp(chSaveImageType, "raw"))
            {
                // �ж��Ƿ�ΪHBģʽ,���ǽ��н���
                bool bflag = IsHBPixelFormat(stImageInfo.stFrameInfo.enPixelType);
                if (bflag)
                {
                    stDecodeParam.pSrcBuf = stImageInfo.pBufAddr;
                    stDecodeParam.nSrcLen = stImageInfo.stFrameInfo.nFrameLenEx;

                    if (pDstBuf == NULL)
                    {
                        pDstBuf = (unsigned char *)malloc(sizeof(unsigned char) * (nPayloadSize * 3));
                        if (NULL == pDstBuf)
                        {
                            printf("malloc pDstData fail !\n");
                            nRet = MV_E_RESOURCE;
                        }
                    }
                    stDecodeParam.pDstBuf = pDstBuf;
                    stDecodeParam.nDstBufSize = nPayloadSize;
                    nRet = MV_CC_HB_Decode(handle, &stDecodeParam);
                    if (nRet != MV_OK)
                    {
                        printf("Decode fail![0x%x]\n", nRet);
                    }
                    else
                    {
                        printf("HB Decode success!\n");
                    }

                    // ������ͼ
                    char chRawPath[256] = {0};
                    sprintf(chRawPath, "Image_w%d_h%d_fn%03d.raw", stDecodeParam.nWidth, stDecodeParam.nHeight, stImageInfo.stFrameInfo.nFrameNum);
                    FILE *file = fopen(chRawPath, "wb+");
                    if (NULL != file)
                    {
                        // д�����ݵ��ļ�
                        size_t bytesWritten = fwrite(stDecodeParam.pDstBuf, 1, stDecodeParam.nDstBufLen, file);
                        if (stDecodeParam.nDstBufLen == bytesWritten)
                        {
                            printf("Save image raw success.\n");
                        }
                        else
                        {
                            printf("Save image raw failed.\n");
                        }

                        // �ر��ļ�
                        fclose(file);
                    }
                }
                else
                {
                    // ������ͼ
                    char chRawPath[256] = {0};
                    sprintf(chRawPath, "Image_w%d_h%d_fn%03d.raw", stImageInfo.stFrameInfo.nExtendWidth, stImageInfo.stFrameInfo.nExtendHeight, stImageInfo.stFrameInfo.nFrameNum);
                    FILE *file = fopen(chRawPath, "wb+");
                    if (NULL != file)
                    {
                        // д�����ݵ��ļ�
                        size_t bytesWritten = fwrite(stImageInfo.pBufAddr, 1, stImageInfo.stFrameInfo.nFrameLenEx, file);

                        if (stImageInfo.stFrameInfo.nFrameLenEx == bytesWritten)
                        {
                            printf("Save image raw success.\n");
                        }
                        else
                        {
                            printf("Save image raw failed.\n");
                        }
                        // �ر��ļ�
                        fclose(file);
                    }
                }
            }
            else if (0 == strcmp(chSaveImageType, "Jpeg"))
            {
                nRet = SaveImage(handle,MV_Image_Jpeg, &stImageInfo);
                if (MV_OK == nRet)
                {
                    printf("Save Image Jpeg success.\n");
                }
                else
                {
                    printf("Save image Jpeg failed.\n");
                }
            }
            else if (0 == strcmp(chSaveImageType, "bmp"))
            {
                nRet = SaveImage(handle,MV_Image_Bmp, &stImageInfo);
                if (MV_OK == nRet)
                {
                    printf("Save Image bmp success.\n");
                }
                else
                {
                    printf("Save image bmp failed.\n");
                }
            }
            else if (0 == strcmp(chSaveImageType, "tiff"))
            {
                nRet = SaveImage(handle,MV_Image_Tif, &stImageInfo);
                if (MV_OK == nRet)
                {
                    printf("Save Image tif success.\n");
                }
                else
                {
                    printf("Save image tif failed.\n");
                }
            }
            else if (0 == strcmp(chSaveImageType, "png"))
            {
                nRet = SaveImage(handle,MV_Image_Png, &stImageInfo);
                if (MV_OK == nRet)
                {
                    printf("Save Image png success.\n");
                }
                else
                {
                    printf("Save image png failed.\n");
                }
            }
            else
            {
                printf("Input not supoort,Please Input Save Image Type(raw/Jpeg/bmp/tiff/png):");
                continue;
            }
        }

        if (MV_OK != nRet)
        {
            if (NULL != pDstBuf)
            {
                free(pDstBuf);
                pDstBuf = NULL;
            }
        }

        nRet = MV_CC_FreeImageBuffer(handle, &stImageInfo);
        if (nRet != MV_OK)
        {
            printf("Free Image Buffer fail! nRet [0x%x]\n", nRet);
        }
    }
    else
    {
        printf("Get Image fail! nRet [0x%x]\n", nRet);
    }
}

void stop_grabbing(void* handle)
{
    // ch:ֹͣȡ�� | en:Stop grab image
    auto nRet = MV_CC_StopGrabbing(handle);
    if (MV_OK != nRet)
    {
        printf("Stop Grabbing fail! nRet [0x%x]\n", nRet);
    }
}

void close_device(void* handle)
{ // ch:�ر��豸 | Close device
    auto nRet = MV_CC_CloseDevice(handle);
    if (MV_OK != nRet)
    {
        printf("ClosDevice fail! nRet [0x%x]\n", nRet);
    }

    destroy_handle(handle);

    // ch:����ʼ��SDK | en:Finalize SDK
    MV_CC_Finalize();
}

void destroy_handle(void* handle)
{ // ch:���پ�� | Destroy handle
    auto nRet = MV_CC_DestroyHandle(handle);
    if (MV_OK != nRet)
    {
        printf("Destroy Handle fail! nRet [0x%x]\n", nRet);
    }
    handle = NULL;
}

// ch:�ȴ��������� | en:Wait for key press
void PressEnterToExit(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    fprintf(stderr, "\nPress enter to exit.\n");
    while (getchar() != '\n')
        ;
}

void set_exposure_auto_off(void* handle)
{

    auto nRet = MV_CC_SetEnumValue(handle, "ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF);
    if (MV_OK != nRet)
    {
        printf("Set auto exposure off fail! nRet [0x%x]\n", nRet);
    }
}

// ch:获取和设置Float型参数，如 ExposureTime和Gain
// en:Get Float type parameters, such as ExposureTime and Gain
int GetFloatValue(void* handle, IN const char *strKey, OUT MVCC_FLOATVALUE *pFloatValue)
{
    return MV_CC_GetFloatValue(handle, strKey, pFloatValue);
}

int GetIntValue(void* handle, IN const char *strKey, OUT MVCC_INTVALUE *pIntValue)
{
    return MV_CC_GetIntValue(handle, strKey, pIntValue);
}

float get_exposure_time(void* handle)
{

    MVCC_FLOATVALUE *result = new MVCC_FLOATVALUE;

    auto ret = GetFloatValue(handle, "ExposureTime", result);

    if (ret != MV_OK)
    {
        printf("Get exposure time fail\n");
        return -1;
    }
    else
    {
        // 获取曝光时间的当前值、最大值和最小值
        auto exposure_time_cur = result->fCurValue;
        auto exposure_time_max = result->fMax;
        auto exposure_time_min = result->fMin;

        // 输出结构体的值
        std::cout << "Current Value: " << exposure_time_cur << std::endl;
        std::cout << "Max Value: " << exposure_time_max << std::endl;
        std::cout << "Min Value: " << exposure_time_min << std::endl;

        return exposure_time_cur;
    }
}

int SetFloatValue(void* handle, IN const char *strKey, IN float fValue)
{
    return MV_CC_SetFloatValue(handle, strKey, fValue);
}

int SetIntValue(void* handle, IN const char *strKey, IN unsigned int Value)
{
    return MV_CC_SetIntValue(handle, strKey, Value);
}

bool set_exposure_time(void* handle, float value)
{
    if (SetFloatValue(handle, "ExposureTime", value) != MV_OK)
    {
        std::cout << "Set exposure time failed" << std::endl;
        return false;
    }

    return true;
}

// ch:获取和设置Bool型参数，如 ReverseX
// en:Get Bool type parameters, such as ReverseX
int GetBoolValue(void* handle, IN const char *strKey, OUT bool *pbValue)
{
    return MV_CC_GetBoolValue(handle, strKey, pbValue);
}

int SetBoolValue(void* handle, IN const char *strKey, IN bool bValue)
{
    return MV_CC_SetBoolValue(handle, strKey, bValue);
}

// ch:获取和设置String型参数，如 DeviceUserID
// en:Get String type parameters, such as DeviceUserID
int GetStringValue(void* handle, IN const char *strKey, MVCC_STRINGVALUE *pStringValue)
{
    return MV_CC_GetStringValue(handle, strKey, pStringValue);
}

int SetStringValue(void* handle, IN const char *strKey, IN const char *strValue)
{
    return MV_CC_SetStringValue(handle, strKey, strValue);
}

// ch:获取和设置Enum型参数，如 PixelFormat
// en:Get Enum type parameters, such as PixelFormat
int GetEnumValue(void* handle, IN const char *strKey, OUT MVCC_ENUMVALUE *pEnumValue)
{
    return MV_CC_GetEnumValue(handle, strKey, pEnumValue);
}

int SetEnumValue(void* handle, IN const char *strKey, IN unsigned int nValue)
{
    return MV_CC_SetEnumValue(handle, strKey, nValue);
}

int SetEnumValueByString(void* handle, IN const char *strKey, IN const char *sValue)
{
    return MV_CC_SetEnumValueByString(handle, strKey, sValue);
}

bool turn_on_IEEE1588(void* handle)
{
    if (SetBoolValue(handle, "GevIEEE1588", true) != MV_OK)
    {
        std::cout << "Failed to turn on IEEE 1588" << std::endl;
        return false;
    }
    return true;
}

bool set_trigger_mode_on(void* handle)
{
    if (SetEnumValue(handle, "TriggerMode", MV_TRIGGER_MODE_ON) != MV_OK)
    {
        std::cout << "Turn on trigger mode fail..." << std::endl;
        return false;
    }
    return true;
}

bool set_trigger_source(void* handle, const char *source)
{
    if (SetEnumValueByString(handle, "TriggerSource", source) != MV_OK)
    {
        std::cout << "Set trigger source fail..." << std::endl;
        return false;
    }
    return true;
}

bool set_trigger_source_to_action(void* handle)
{
    if (SetEnumValueByString(handle, "TriggerSource", "Action1") != MV_OK)
    {
        std::cout << "Set trigger source to action fail..." << std::endl;
        return false;
    }
    return true;
}

bool set_action_keys(void* handle, unsigned int action_device_key, unsigned int action_group_key, unsigned int group_mask)
{

    if (SetIntValue(handle, "ActionDeviceKey", action_device_key) != MV_OK)
    {
        std::cout << "Set action device key fail..." << std::endl;
        return false;
    }
    if (SetIntValue(handle, "ActionGroupKey", action_group_key) != MV_OK)
    {
        std::cout << "Set action group key fail..." << std::endl;
        return false;
    }
    if (SetIntValue(handle, "ActionGroupMask", group_mask) != MV_OK)
    {
        std::cout << "Set group mask fail..." << std::endl;
        return false;
    }

    return true;
}
