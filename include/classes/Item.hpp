#include "Entity.hpp"

enum itemType {
	BUFF,
	DEBUG,
	DEBUFF,
	WEAPON,
	ARTIFACT,
};

struct itemProperties {
	int ID;
	itemType type;
	const char* name;
	entityInfo stats;
	const char* description;

	friend std::ostream& operator<<(std::ostream& out, const itemProperties& p) {
		out << "ID: " << p.ID << std::endl;
		out << "type: " << p.type << std::endl;
		out << "name: " << p.name << std::endl;
		out << "stats: " << p.stats << std::endl;
		out << "description: " << p.description << std::endl;
		return out;
	}
};

class Item : Entity {
	protected:
		itemProperties properties;

	public:
};