#include <string.h>
/*#include <string>*/

#include "WhaleyEdidUtil.h"
#define LOG_TAG "WhaleyEdidUtil"

#define LOGI(format, ...)        \
                         do {    \
                            printf("%s %s:%d: ", LOG_TAG, __FUNCTION__, __LINE__);\
                            printf(format, ##__VA_ARGS__);\
                            printf("\n");                \
                         }while(0);


using namespace std;

void CWhaleyEdidUtil::setMonitorName(WHALEY_EDID_TYPE* edid, int len)
{
    /*string monitorName = HiCfgFact::get()->parseString("edidcontent:monitorname");
    LOGI("[%s] monitorName=%s", __FUNCTION__, monitorName.data());
    if( "" == monitorName )
    {
        LOGI("[%s] do not find monitor name config, use default monitor name!!!", __FUNCTION__);
        return;
    }
    setMonitorName(edid, monitorName.data());*/
}

void CWhaleyEdidUtil::setMonitorName(WHALEY_EDID_TYPE* edid, const char* name, int len)
{
    if( NULL == edid )
    {
        LOGI("%s edid is null, return!!!\n",  __FUNCTION__);
        return ;
    }

    if( NULL == name || strlen(name) >= MONITOR_NAME_MAX_LEN )
    {
        LOGI("%s name is null or too long, return!!!\n", __FUNCTION__);
        return;
    }

    if(len != 256)
    {
        LOGI("%s len(%d) is invalid, return!!!\n", __FUNCTION__, len);
        return;
    }

    int pos = seekMonitorNamePos(edid, len);
    if( pos < 0 || pos >= 256)
    {
        LOGI("%s can't find monitor name position!!!\n", __FUNCTION__);
        return;
    }

    LOGI("%s monitor name pos in edid is %d !", __FUNCTION__, pos);
    updateMonitorName(edid, pos, name);
    updateBlock1CheckSum(edid);
}

int CWhaleyEdidUtil::seekMonitorNamePos(WHALEY_EDID_TYPE* edid, int len)
{

    int desc_end_pos = WHALEY_EDID_DESCRIPTOR_END_POS;
    int desc_start_pos = WHALEY_EDID_DESCRIPTOR_START_POS;
    int offset = desc_start_pos;
    int pos = desc_start_pos;


    if( NULL == edid )
    {
        LOGI("%s edid is null, return!!!\n", __FUNCTION__);
        return -1;
    }

    while( offset < desc_end_pos )
    {
        if( edid[offset] == 0x00
            && edid[offset + 1] == 0x00
            && edid[offset + 2] == 0x00
            && edid[offset + 3] == 0xFC
            && edid[offset + 4] == 0x00 )
            {
                pos = offset;
                break;
            }

        //check next block
        offset += WHALEY_EDID_DESCRIPTOR_BLOCK_LEN;
    }

    if( offset >= desc_end_pos )
    {
        pos = -1;
    }

    return pos;
}


void CWhaleyEdidUtil::updateMonitorName(WHALEY_EDID_TYPE* edid, int pos, const char* name)
{
    if( NULL == edid )
    {
        LOGI("%s edid is null, return!!!\n", __FUNCTION__);
        return ;
    }

    int len = strlen(name);
    int offset = MONITOR_NAME_OFFSET(pos);
    int end_pos = offset + MONITOR_NAME_MAX_LEN;
    for(int i = 0; i < len; i++, offset++)
    {
        edid[offset] = name[i]&0xFF;
    }

    //reset other bytes to empty
    while(offset < end_pos)
    {
        edid[offset] = 0x20;
        offset++;
    }
}

void CWhaleyEdidUtil::updateBlock1CheckSum(WHALEY_EDID_TYPE* edid)
{
    if( NULL == edid )
    {
        LOGI("%s edid is null, return!!!\n", __FUNCTION__);
        return ;
    }

    int sum = 0;
    for(int i = 0; i < 127; i++)
    {
        sum += edid[i];
    }

    edid[127] = 256-(sum % 256);
    LOGI("%s checksum is %d !", __FUNCTION__, edid[127]);
}


