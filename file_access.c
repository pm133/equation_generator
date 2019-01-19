#include "stdio.h"
#include "file_access.h"



ERROR_CODES read_coord_data_from_file (char *p_buf_txt, char *p_file)
{
	ERROR_CODES ret = ERR_OK;
	FILE *fp;

	
	fp = fopen(p_file, "r");
	if (fp == NULL)
	{
		printf("File access error %s\n", p_file);
		ret = ERR_FILE;
	}
	else
	{
		//File is now open. Read the contents until new line, EOF up to
		//MAX_FILE_SIZE-1. Null char is then appended.
		(void)fgets(p_buf_txt, MAX_FILE_SIZE, fp);

		(void) fclose (fp);
	}
	
	return ret;
}

