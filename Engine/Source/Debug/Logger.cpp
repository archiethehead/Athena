#include "Debug/Logger.h"
#include <cstdio>
#include <cstdarg>
#include <windows.h>

CLogger::CLogger() {

	m_LoggerListener = std::thread(&CLogger::ListenLoop, this);

}

CLogger::~CLogger() {

	if (m_LoggerListener.joinable())
		m_LoggerListener.join();

}

CLogger& CLogger::GetLogger() {

	static CLogger CLoggerSingleton;
	return CLoggerSingleton;

}

void CLogger::Out(const char* Format, OutputOptions Option, ...) {

	size_t CurrentHead = (m_STHead++) & LOG_BUFFER_MASK;
	m_LogBuffer_s[CurrentHead].Option = Option;
	
	va_list args;
	va_start(args, Option);
	m_LogBuffer_s[CurrentHead].Len = vsnprintf(m_LogBuffer_s[CurrentHead].Log, sizeof(m_LogBuffer_s[CurrentHead].Log), Format, args);
	va_end(args);

	m_LogBuffer_s[CurrentHead].IsReady = true;

}

void CLogger::Flush() {

	while (m_STTail < m_STHead) {
		
		Log* CurrentLog = &(m_LogBuffer_s[m_STTail & LOG_BUFFER_MASK]);
		
		if (!CurrentLog->IsReady)
			continue;

		FormattedOutput(CurrentLog);
		m_STTail++;

	}

}

void CLogger::ListenLoop() {

	while (1) {
	
		if (!m_LogBuffer_s[m_STTail & LOG_BUFFER_MASK].IsReady) {
		
			std::this_thread::yield();
			continue;

		}

		Log* CurrentLog = &(m_LogBuffer_s[m_STTail & LOG_BUFFER_MASK]);
		FormattedOutput(CurrentLog);
		m_STTail++;

	}

}

void CLogger::FormattedOutput(Log* CurrentLog) {

	char SOutputBuffer[LOG_SIZE] = {0};

	if (CurrentLog->Option != OutputOptions::None) {

		const char* SPrefix = (CurrentLog->Option == OutputOptions::Error) ? "ERROR: " : "WARNING: ";
		size_t STPrefixLen = strlen(SPrefix);
		memcpy_s(SOutputBuffer + STPrefixLen, LOG_SIZE, CurrentLog->Log, CurrentLog->Len);
		memcpy_s(SOutputBuffer, LOG_SIZE, SPrefix, STPrefixLen);

	}

	else
		memcpy_s(SOutputBuffer, LOG_SIZE, CurrentLog->Log, CurrentLog->Len);

#ifdef _WIN32

	if (IsDebuggerPresent())
		OutputDebugStringA(SOutputBuffer);

	else
		//	printf_s("%s", CurrentLog->Log);
		fputs(SOutputBuffer, stdout);

#else

	fputs(SOutputBuffer, stdout);

#endif // ifdef _WIN32

}