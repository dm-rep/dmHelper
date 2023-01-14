#ifndef _fixedqueue_link_h
#define _fixedqueue_link_h

#include <queue>
#include <functional>

namespace dmHelper
{
	// Queue with specified maximum length - older records are dropped
	template <typename T, int limit, typename Container = std::deque<T>>
	class FixedQueue : public std::queue<T, Container>
	{
	public:
		// pushes into queue
		void push(const T &value)
		{
			if (this->size() == limit) this->c.pop_front();
			std::queue<T, Container>::push(value);
		};
		// clears queue
		void clear()
		{
			while (!this->c.empty()) this->c.pop_front();
		}
	};
}

#endif
