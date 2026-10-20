#include "Debug/Logger.h"
#include <cstdio>
#include <cstdarg>
#include <windows.h>

logger::logger() {

	m_LoggerListener = std::thread(&logger::listenLoop, this);

}

logger::~logger() {

	if (m_LoggerListener.joinable())
		m_LoggerListener.join();

}

logger& logger::getLogger() {

	static logger loggerSingleton;
	return loggerSingleton;

}

void logger::out(const char* format, outputOptions option, ...) {

	size_t currentHead = (head++) & LOG_BUFFER_MASK;
	logBuffer[currentHead].option = option;
	
	va_list args;
	va_start(args, option);
	logBuffer[currentHead].len = vsnprintf(logBuffer[currentHead].log, sizeof(logBuffer[currentHead].log), format, args);
	va_end(args);

	logBuffer[currentHead].IsReady = true;

}

void logger::flush() {

	while (tail < head) {
		
		Log* currentLog = &(logBuffer[tail & LOG_BUFFER_MASK]);
		
		if (!currentLog->IsReady)
			continue;

		formattedOutput(currentLog);
		tail++;

	}

}

void logger::listenLoop() {

	while (1) {
	
		if (!logBuffer[tail & LOG_BUFFER_MASK].IsReady) {
		
			std::this_thread::yield();
			continue;

		}

		Log* currentLog = &(logBuffer[tail & LOG_BUFFER_MASK]);
		formattedOutput(currentLog);
		tail++;

	}

}

void logger::formattedOutput(Log* currentLog) {

	char outputBuffer[LOG_SIZE] = {0};

	if (currentLog->option != outputOptions::None) {

		const char* prefix = (currentLog->option == outputOptions::Error) ? "ERROR: " : "WARNING: ";
		size_t prefixLen = strlen(prefix);
		memcpy_s(outputBuffer + prefixLen, LOG_SIZE, currentLog->log, currentLog->len);
		memcpy_s(outputBuffer, LOG_SIZE, prefix, prefixLen);

	}

	else
		memcpy_s(outputBuffer, LOG_SIZE, currentLog->log, currentLog->len);

#ifdef _WIN32

	if (IsDebuggerPresent())
		OutputDebugStringA(outputBuffer);

	else
		//	printf_s("%s", CurrentLog->Log);
		fputs(outputBuffer, stdout);

#else

	fputs(outputBuffer, stdout);

#endif // ifdef _WIN32

}