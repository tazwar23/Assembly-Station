#include "Utilities.h"

using namespace std;

namespace sdds {
	char Utilities::m_delimiter = ' ';

	Utilities::Utilities() : m_widthField(1) {}
	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		string sub_str = "";
		int end = str.find(m_delimiter, next_pos);
		if ((int)next_pos != end) {
			sub_str = str.substr(next_pos, end - next_pos);

			if (sub_str == "")
				more = false;
			else
			{
				more = true;
				while (sub_str[0] == ' ')
					sub_str.erase(0, 1);
				for (int i = sub_str.length() - 1; sub_str[i] == ' '; i--)
					sub_str.erase(i);
				
				if (end == -1)
					more = false;
				else 
					next_pos = ++end;
			}
			if (m_widthField < sub_str.length()) m_widthField = sub_str.length();
		}
		else
		{
			more = false;
			throw string("");
		}
		return sub_str;
	}
	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter() {
		return m_delimiter;
	}
}