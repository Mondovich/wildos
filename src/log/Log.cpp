/*
 * Log.cpp
 *
 *  Created on: 29/lug/2010
 *      Author: RaimondoS
 */

#include "Log.h"
#include "../std/iostream.h"

namespace std {

void Log::video(const char* s) {
	clog << s;
}
;
void Log::trace(const char* s) {
	clog << "TRACE  " << s << endl;
}
;
void Log::trace(const char* s, const char *file, uint32_t line) {
	clog << "TRACE  " << file << ":" << line << " - " << s << endl;
}
;
void Log::debug(const char* s) {
	clog << "DEBUG  " << s << endl;
}
;
void Log::debug(const char* s, const char *file, uint32_t line) {
	clog << "DEBUG  " << file << ":" << line << " - " << s << endl;
}
;
void Log::info(const char* s) {
	clog << "INFO  " << s << endl;
}
;
void Log::info(const char* s, const char *file, uint32_t line) {
	clog << "INFO  " << file << ":" << line << " - " << s << endl;
}
;
void Log::warn(const char* s) {
	clog << "WARN  " << s << endl;
}
;
void Log::warn(const char* s, const char *file, uint32_t line) {
	clog << "WARN  " << file << ":" << line << " - " << s << endl;
}
;
void Log::error(const char* s) {
	cerr << "ERROR  " << s << endl;
}
;
void Log::error(const char* s, const char *file, uint32_t line) {
	cerr << "ERROR  " << file << ":" << line << " - " << s << endl;
}
;
}
