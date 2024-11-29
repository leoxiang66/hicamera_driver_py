#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "MvCameraControl.h"

void *init_SDK();

bool PrintDeviceInfo(MV_CC_DEVICE_INFO *pstMVDevInfo);

bool start_grabbing(auto handle);