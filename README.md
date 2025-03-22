# A simple Logger

## How to use
```cpp
#include "Logger.h"
// Initialize passing the path and filename
Logger logger("C:\\YourPath\\YourFileName.csv");
// Add logentry
logger.log("Warning", "Hook failed", "Present hook failed. Access violation.");
// Print all entries
logger.print();
// Print grouped by type
logger.print(true);
// Print grouped by title
logger.print(true, "Title");
// Print filtered by type/title
logger.print(false, "", "Error");
// Delete all logs from memory and file
logger.deleteLogs();
```

## Video demonstration
https://youtu.be/eJShMeVyezU
