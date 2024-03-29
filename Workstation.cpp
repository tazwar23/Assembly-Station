#include "Workstation.h"

using namespace std;

namespace sdds {
	std::deque<CustomerOrder> g_pending;
	std::deque<CustomerOrder> g_completed;
	std::deque<CustomerOrder> g_incomplete;
	Workstation::Workstation(const std::string& s) : Station(s) { }

	void Workstation::fill(std::ostream& os) {
		if (!(m_orders.empty())) {
			m_orders.front().fillItem(*this, os);
		}
	}
	bool Workstation::attemptToMoveOrder() {
		bool moved = false;
		if (!(m_orders.empty())) {
			if (m_orders.front().isItemFilled(Station::getItemName()) || Station::getQuantity() == 0)
			{
				if (m_pNextStation) {
					*m_pNextStation += move(m_orders.front());
					m_orders.pop_front();
				}
				else {
					if (m_orders.front().isOrderFilled()) {
						g_completed.push_back(move(m_orders.front()));
						m_orders.pop_front();
					}
					else {
						g_incomplete.push_back(move(m_orders.front()));
						m_orders.pop_front();
					}
				}
				moved = true;
			}
		}
		return moved;
	}
	void Workstation::setNextStation(Workstation* station) {
		m_pNextStation = station;
	}
	Workstation* Workstation::getNextStation() const {
		return m_pNextStation;
	}
	void Workstation::display(std::ostream& os) const {
		os << Station::getItemName() << " --> ";
		if (m_pNextStation)
			os << m_pNextStation->getItemName() << '\n';
		else
			os << "End of Line\n";
	}
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_orders.push_back(move(newOrder));
		return *this;
	}
}