#include "Entity.hpp"

struct itemProperties {
	itemType type;
	const char* name;
	const char* description;

	friend std::ostream& operator<<(std::ostream& out, const itemProperties& p) {
		out << "type: " << itemTypeToString(p.type) << std::endl;
		out << "name: " << p.name << std::endl;
		out << "description: " << p.description << std::endl;
		return out;
	}
};

class Item : Entity {
	protected:
		itemProperties properties;

	public:
		Item();
		Item(itemProperties properties);
};