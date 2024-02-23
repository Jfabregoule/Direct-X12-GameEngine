#pragma once
#include <string>

namespace Time {

	/* - Get current Time in string format - */

	std::wstring ENGINE_API GetTime(BOOL stripped = FALSE);

	/* - Get current Date in string format - */

	std::wstring ENGINE_API GetDate(BOOL stripped = FALSE);

	/* - Get current Date and Time in string format - */

	std::wstring ENGINE_API GetDateTimeString(BOOL stripped = FALSE);
}