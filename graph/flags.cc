#include "graph/flags.h"

DEFINE_string(command_file, "../misc/batch_file",
              "all instruction to run graph algorithm");
DEFINE_bool(serialize, false, "enable serialize");
DEFINE_bool(deserialize, false, "enable deserialize");