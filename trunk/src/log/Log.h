/*
 * Log.h
 *
 *  Created on: 29/lug/2010
 *      Author: RaimondoS
 */

#include "../common/types.h"

#ifndef LOG_H_
#define LOG_H_

namespace std {

#define TRACE(msg) std::Log::trace(msg, __FILE__, __LINE__)
#define DEBUG(msg) std::Log::debug(msg, __FILE__, __LINE__)
#define INFO(msg) std::Log::info(msg, __FILE__, __LINE__)
#define WARN(msg) std::Log::warn(msg, __FILE__, __LINE__)
#define ERROR(msg) std::Log::ERROR(msg, __FILE__, __LINE__)

class Log {
public:
	virtual ~Log() {
	}
	;
	static void video(const char*);
	static void trace(const char*);
	static void trace(const char*, const char*, uint32_t);
	static void debug(const char*);
	static void debug(const char*, const char*, uint32_t);
	static void info(const char*);
	static void info(const char*, const char*, uint32_t);
	static void warn(const char*);
	static void warn(const char*, const char*, uint32_t);
	static void error(const char*);
	static void error(const char*, const char*, uint32_t);

private:
	Log() {
	}
	;
};

}

#endif /* LOG_H_ */
