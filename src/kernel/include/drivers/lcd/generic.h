#ifndef DRIVER_LCD_GENERIC
#define DRIVER_LCD_GENERIC

// for multi compitable drivers
#define CONFIG_CYD28

#ifdef CONFIG_CYD28
// use this to write your driver to be
// compitable with generic LCD rules
#include "drivers/lcd/cyd28.h"
#endif //

#endif // !
