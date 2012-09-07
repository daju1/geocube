#pragma once

const char * GetNameFromCommandLine(const char *in, char *out);
#define FILE_NAME_LEN 4096

class CommandLineParser
{
public:
	char module[FILE_NAME_LEN];
	char path[FILE_NAME_LEN];
	char open_file[FILE_NAME_LEN];

	CommandLineParser(void);
	virtual ~CommandLineParser(void);
	void DoParsing();
};
