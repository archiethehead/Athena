#pragma once

#include <atomic>
#include <thread>
#include <cstdint>

enum class OutputOptions : uint8_t {

	None,
	Wanring,
	Error,
	Underline,
	Header

};

#ifdef _DEBUG

#define DEBUG_OUT(x, y, ...) CLogger::GetLogger().Out(x, y, ##__VA_ARGS__)
#define FLUSH_LOGGER() CLogger::GetLogger().Flush()

class CLogger {

public:

	static constexpr size_t LOG_BUFFER_SIZE = 1024;
	static constexpr size_t LOG_BUFFER_MASK = LOG_BUFFER_SIZE - 1;
	static constexpr size_t LOG_SIZE = 256;
	
	~CLogger();
	static CLogger& GetLogger();
	
	void Out(const char* Format, OutputOptions Option, ...);
	void Flush();

private:

	struct Log {

		OutputOptions Option;
		int Len;
		char Log[LOG_SIZE];

	};

	Log m_LogBuffer_s[LOG_BUFFER_SIZE] = {};
	alignas(64) std::atomic<size_t> m_STTail;
	alignas(64) std::atomic<size_t> m_STHead;
	std::thread m_LoggerListener;

	CLogger();
	void ListenLoop();

};

#else

#define DEBUG_OUT(x, y, ...)
#define FLUSH()

#endif // ifdef _DEBUG