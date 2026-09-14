#include "Debug/Logger.h"
#include <cstdio>
#include <cstdarg>

CLogger::CLogger() {

	m_LoggerListener = std::thread(&CLogger::ListenLoop, this);

}

CLogger::~CLogger() {

	if (m_LoggerListener.joinable()) {
	
		m_LoggerListener.join();
	
	}

}

CLogger& CLogger::GetLogger() {

	static CLogger CLoggerSingleton;
	return CLoggerSingleton;

}

void CLogger::Out(const char* Format, OutputOptions Option, ...) {

	m_STHead++;

	va_list args;
	va_start(args, Option);
	size_t Len = vsnprintf(m_LogBuffer_s[m_STHead & LOG_BUFFER_MASK].Log, sizeof(m_LogBuffer_s[m_STHead & LOG_BUFFER_MASK].Log), Format, args);
	va_end(args);

}

void CLogger::ListenLoop() {

	while (1) {
	
		if (m_STTail == m_STHead) {
		
			std::this_thread::yield();
			continue;

		}

		m_STTail++;
		Log* CurrentLog = &(m_LogBuffer_s[m_STTail & LOG_BUFFER_MASK]);
		printf("%s (Tail = %zu, Head = %zu)\n", CurrentLog->Log, m_STTail.load(), m_STHead.load());
	
	}

}