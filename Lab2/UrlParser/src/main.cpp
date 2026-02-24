#include "UrlParser.h"
#include <iostream>
#include <string>

void PrintUrlInfo(const std::string& url, const std::string& host, int port, const std::string& document)
{
	std::cout << url << "\n"
			  << "HOST: " << host << "\n"
			  << "PORT: " << port << "\n"
			  << "DOC: " << document << "\n";
}

int main()
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		Protocol protocol;
		int port;
		std::string host;
		std::string document;

		if (!ParseURL(line, protocol, port, host, document))
		{
			std::cout << "ERROR" << "\n";
			return 0;
		}

		PrintUrlInfo(line, host, port, document);
	}

	return 0;
}