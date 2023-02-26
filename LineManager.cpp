#include "LineManager.h"
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

namespace sdds {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		std::ifstream f(file);
		if (f.is_open()) {

			while (f) {
				string line = "";
				getline(f, line);
				if (line != "") {
					string first;
					string second = "";
					Utilities utility;
					bool more = true;
					size_t next_pos = 0;
					first = utility.extractToken(line, next_pos, more);
					auto ptr = find_if(stations.begin(), stations.end(), [&](Workstation* s) {
						return s->getItemName() == first;
						});
					m_activeLine.push_back(*ptr);
					if (more) {
						second = utility.extractToken(line, next_pos, more);
						auto next = find_if(stations.begin(), stations.end(), [&](Workstation* s) {
							return s->getItemName() == second;
							});
						(*ptr)->setNextStation(*next);
					}
				}
			}
			m_cntCustomerOrder = g_pending.size();
			    find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
				bool found = true;
				if (ws->getNextStation()) {
					for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* s) {
						if (s->getNextStation() && ws->getItemName() == s->getNextStation()->getItemName()) { found = false; }
						});
				}
				else { found = false; }
				if (found) { m_firstStation = ws; }
				return found;
				});
		}
	}
	void LineManager::reorderStations() {
		auto size = m_activeLine.size();
		m_activeLine.clear();
		m_activeLine.push_back(m_firstStation);
		for (unsigned i = 0; i < size; i++) {
			if (m_activeLine[i]->getNextStation()) 
				m_activeLine.push_back(m_activeLine[i]->getNextStation());
			
		}
	}
	bool LineManager::run(std::ostream& os) {
	
		bool val = false, done = false;
		static int crntIt = 0;
		os << "Line Manager Iteration : " << crntIt + 1 << std::endl;

		if (!done && g_pending.size() > 0) {
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();
			done = !done;
		}

		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* fillStn) {
			fillStn->fill(os);
		});

		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* atmpMove) {
			atmpMove->attemptToMoveOrder();
		});

		crntIt++;
		val = m_cntCustomerOrder - (g_completed.size() + g_incomplete.size()) == 0;
		return val;
	}
	void LineManager::display(std::ostream& os) const {
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* w) {w->display(os); });
	}
}