#ifndef _FILE_ACCESS_H_
#define _FILE_ACCESS_H_
#include "error_codes.h"


#define MAX_FILE_SIZE 1024

ERROR_CODES read_coord_data_from_file (char *p_buf_txt, char *p_file);

#endif
