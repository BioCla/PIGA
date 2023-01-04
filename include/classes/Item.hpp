#include "Player.hpp"

struct itemProperties {
	itemType type;
	const char* name;
	const char* description;

	friend std::ostream& operator<<(std::ostream& out, const itemProperties& p) {
		out << std::endl <<  "name: " << p.name << std::endl;
		out << "description: " << p.description << std::endl;
		out << "type: " << itemTypeToString(p.type) << std::endl;
		return out;
	}
};

class Item : public Entity {
	protected:
		itemProperties properties;
		std::function<void(Player)> effect;

	public:
		Item(itemProperties properties, std::function<void(Player)> effect) {
			this->properties = properties;
			this->effect = effect;
		}
		
		void use(Player target) {
			effect(target);
		}

		friend std::ostream& operator<<(std::ostream& out, const Item& i) {
			out << i.properties << std::endl;
			out << i.stats;
			return out;
		}
};