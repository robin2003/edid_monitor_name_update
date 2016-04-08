#ifndef _WHALEY_EDID_UTIL_HEADER_
#define _WHALEY_EDID_UTIL_HEADER_

#include <stdio.h>



#define WHALEY_EDID_TYPE int


#define WHALEY_EDID_DESCRIPTOR_START_POS 54
#define WHALEY_EDID_DESCRIPTOR_END_POS 125
#define WHALEY_EDID_DESCRIPTOR_BLOCK_LEN 18
#define MONITOR_NAME_MAX_LEN 13
#define MONITOR_NAME_OFFSET(pos) ((pos) + 5)

class CWhaleyEdidUtil
{
	public:
		static CWhaleyEdidUtil&  getInstance()
		{
			static CWhaleyEdidUtil instance;
			return instance;
		};

		void setMonitorName(WHALEY_EDID_TYPE* edid, const char* name, int len = 256);
		void setMonitorName(WHALEY_EDID_TYPE * edid, int len = 256);

	protected:
		//monitor name assistent function
		int seekMonitorNamePos(WHALEY_EDID_TYPE* edid, int len = 256);
		void updateMonitorName(WHALEY_EDID_TYPE* edid, int pos, const char* name);

		void updateBlock1CheckSum(WHALEY_EDID_TYPE* edid);

	private:
		CWhaleyEdidUtil() {};
		CWhaleyEdidUtil(const CWhaleyEdidUtil &);
		CWhaleyEdidUtil& operator=(const CWhaleyEdidUtil &);
};

#endif
