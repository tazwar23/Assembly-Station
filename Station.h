
#ifndef SDDS_STATION_H_
#define SDDS_STATION_H_
#include "Utilities.h"
namespace sdds {
	class Station
	{
		int m_id{};
		std::string m_itemName{};
		std::string m_stationDescription{};
		size_t m_serialNumber{};
		size_t m_numItems{};
		static size_t m_widthField;
		static size_t id_generator;
	public:
		Station(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;

	};
}
#endif 

