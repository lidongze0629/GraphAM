#include "graph/flags.h"

DEFINE_string(command_file, "../misc/batch_file",
              "all instruction to run graph algorithm");
DEFINE_bool(serialize, true, "enable serialize");