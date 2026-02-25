#include "StringUtils.h"

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	if (searchString.empty())
	{
		return subject;
	}

	size_t pos = 0;
	std::string result;

	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);

		if (foundPos == std::string::npos)
		{
			break;
		}

		result.append(replacementString);
		pos = foundPos + searchString.length();
	}

	return result;
}