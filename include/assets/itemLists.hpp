
#ifndef ITEMS_LIST
#define ITEMS_LIST

enum ItemType {
	BUFF, // Colore verde
	DEBUFF, // colore rosso
	ARTIFACT, // colore giallo
	WEAPON, // colore blu
	DEBUG, // nessun colore
};

struct itemProperties {
	const char* name;
	const char* description;
	const char* icon;
	int ID;
	ItemType type;
};

#endif