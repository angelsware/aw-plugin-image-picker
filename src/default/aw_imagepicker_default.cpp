#include <statusbar/aw_statusbarfactory.h>
#include "aw_statusbar_default.h"

namespace StatusBar {
	IStatusBar* CStatusBarFactory::create() {
		return new CStatusBar_Default();
	}

	void CStatusBarFactory::destroy(IStatusBar* statusBar) {
		delete statusBar;
	}
}
