#pragma once

#include <atomic>
#include <thread>
#include <cstdint>

enum class outputOptions : uint8_t {

	None,
	Warning,
	Error

};

#ifdef _DEBUG

#define DEBUG_OUT(x, y, ...) logger::getLogger().out(x, y, ##__VA_ARGS__)
#define FLUSH_LOGGER() logger::getLogger().flush()

class logger {

public:

	static constexpr size_t LOG_BUFFER_SIZE = 1024;
	static constexpr size_t LOG_BUFFER_MASK = LOG_BUFFER_SIZE - 1;
	static constexpr size_t LOG_SIZE = 256;
	
	~logger();
	static logger& getLogger();
	
	void out(const char* Format, outputOptions option, ...);
	void flush();

private:

	struct Log {

		outputOptions option;
		size_t len;
		char log[LOG_SIZE];
		std::atomic<bool> IsReady = false;

	};

	Log logBuffer[LOG_BUFFER_SIZE] = {};
	alignas(64) std::atomic<size_t> tail;
	alignas(64) std::atomic<size_t> head;
	std::thread m_LoggerListener;

	logger();
	void listenLoop();
	void formattedOutput(Log* CurrentLog);

};

#else

#define DEBUG_OUT(x, y, ...)
#define FLUSH()

#endif // ifdef _DEBUG