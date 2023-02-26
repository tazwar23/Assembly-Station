#include "Station.h"
#include <string>
#include <iomanip>
using namespace std;

namespace sdds {
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;

	Station::Station(const std::string& str) {
		
		Utilities u;
		bool more = true;
		size_t next_pos = 0;
		m_id = ++id_generator;
		m_itemName = u.extractToken(str, next_pos, more);
		m_serialNumber = stoi(u.extractToken(str, next_pos, more));
		m_numItems = stoi(u.extractToken(str, next_pos, more));
		m_widthField = (u.getFieldWidth() > m_widthField) ? u.getFieldWidth() : m_widthField;
		m_stationDescription = u.extractToken(str, next_pos, more);

	}
	const std::string& Station::getItemName() const {
		return m_itemName;
	}
	size_t Station::getNextSerialNumber() {
		return m_serialNumber++;
	}
	size_t Station::getQuantity() const {
		return m_numItems;
	}
	void Station::updateQuantity() {
		if (m_numItems != 0) {
			m_numItems--;
		}
	}
	void Station::display(std::ostream& os, bool full) const {	
		os << setw(3) << right << setfill('0') << m_id << " | " << setw(m_widthField) << left << setfill(' ') << m_itemName
			<< "  | " << setw(6) << right << setfill('0') << m_serialNumber << " | ";
			if (full) 
				os << setw(4) << right << setfill(' ') << m_numItems << " | " << m_stationDescription;
			os << endl;
		
	}
}