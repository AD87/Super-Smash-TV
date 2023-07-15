#include <SDL_messagebox.h>
#include "ReportError.h"

void ReportError(const std::string& errorMsg){
	SDL_ShowSimpleMessageBox(0, "error", errorMsg.c_str(), 0);
}