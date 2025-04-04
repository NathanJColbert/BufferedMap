#ifndef BUFFERED_MAP_H
#define BUFFERED_MAP_H
#include <unordered_map>
#include <deque>
#include <cstddef>

template<typename Key, typename Item>
class BufferedMap : public std::unordered_map<Key, Item> {
public:
	BufferedMap(size_t maxBuffer) : MAX_BUFFER_SIZE(maxBuffer) { }
	bool exists(Key key) { return find(key) != end(); }
	bool insert(Key key, Item item) {
		if (exists(key)) return false;
		auto i = std::unordered_map<Key, Item>::insert({key, item});
		addToBuffer(i.first);
		return true;
	}
	bool remove(Key key) {
		auto iterator = this->find(key);
		if (iterator == this->end()) return false;
		this->erase(iterator);
		return true;
	}
	typename std::unordered_map<Key, Item>::iterator find(Key key) { return std::unordered_map<Key, Item>::find(key); }
	typename std::unordered_map<Key, Item>::iterator end() { return std::unordered_map<Key, Item>::end(); }
private:
	const size_t MAX_BUFFER_SIZE;
	std::deque<typename std::unordered_map<Key, Item>::iterator> buffer;
	
	void addToBuffer(typename std::unordered_map<Key, Item>::iterator i) {
		if (buffer.size() > 0 && buffer.size() >= MAX_BUFFER_SIZE) {
			auto toDel = buffer.front();
			buffer.pop_front();
			if (toDel != this->end()) { this->erase(toDel); }
		}
        buffer.push_back(i);
	}
};

#endif
