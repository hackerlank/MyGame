#include "TCPRequest.h"
#include "NetworkPackage.h"
#include <string>
using namespace std;

CTCPRequest::CTCPRequest() :m_nDataLen(0), m_pCallback(nullptr)
{
	m_dataMutex.lock();
	memset(m_dataBuf, 0, g_nMaxRequsetDataSize);
	m_dataMutex.unlock();
}


CTCPRequest::~CTCPRequest()
{
}

void CTCPRequest::setRequestData(char* requestData, int size)
{
	m_dataMutex.lock();
	memset(m_dataBuf, 0, g_nMaxRequsetDataSize);
	if (size > g_nMaxRequsetDataSize)
	{
		m_nDataLen = 0;
		m_dataMutex.unlock();
		return;
	}
	memcpy(m_dataBuf, requestData, size);
	m_nDataLen = size;
	m_dataMutex.unlock();
}