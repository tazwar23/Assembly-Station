#include <iomanip>
#include "CustomerOrder.h"

using namespace std;

namespace sdds {
	size_t CustomerOrder::m_widthField = 0;
	CustomerOrder::CustomerOrder(const std::string& s) {
		Utilities utilities;
		bool more = true;
		size_t next_pos = 0;
		m_name = utilities.extractToken(s, next_pos, more);
		m_product = utilities.extractToken(s, next_pos, more);
		size_t recordFromPos = next_pos;
		while (more) 
		{
			utilities.extractToken(s, recordFromPos, more);
			m_cntItem++;
		}
		more = true;
		m_lstItem = new Item * [m_cntItem];
		for (size_t i = 0; i < m_cntItem && more; i++)
			m_lstItem[i] = new Item(utilities.extractToken(s, next_pos, more));
		m_widthField = (utilities.getFieldWidth() > m_widthField) ? utilities.getFieldWidth() : m_widthField;
	}
	CustomerOrder::CustomerOrder(const CustomerOrder& co) {
		throw "Error";
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& co) noexcept {
		*this = move(co);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& co) noexcept {
		for (size_t i = 0; i < m_cntItem; i++) delete m_lstItem[i];		
		delete[] m_lstItem;
		m_lstItem = co.m_lstItem;
		m_name = co.m_name;
		m_product = co.m_product;
		m_cntItem = co.m_cntItem;
		co.m_lstItem = nullptr;
		co.m_name = {};
		co.m_product = {};
		co.m_cntItem = {};
		return *this;
	}
	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; i++) delete m_lstItem[i];	
		delete[] m_lstItem;
	}
	bool CustomerOrder::isOrderFilled() const {
		bool val = true;
		for (size_t i = 0; i < m_cntItem && val; i++) val = m_lstItem[i]->m_isFilled;	
		return val;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool filled = true;

		for (size_t i = 0; i < m_cntItem && filled; i++) {
			if (m_lstItem[i]->m_itemName == itemName) filled = m_lstItem[i]->m_isFilled;			
		}
		return filled;
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		bool valid = false;
		for (size_t i = 0; i < m_cntItem && !valid; i++) {
			if (station.getItemName() == m_lstItem[i]->m_itemName && !m_lstItem[i]->m_isFilled) {
				if (station.getQuantity() > 0) {
					station.updateQuantity();
					m_lstItem[i]->m_isFilled = true;
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
					valid = true;
				}
				else
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				
			}
		}
	}
	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber
				<< "] " << std::left << std::setw(m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName
				<< "   - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
		}
	}
}