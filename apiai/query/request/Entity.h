#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>

namespace ai {
    namespace query {
        namespace request {
            class Entry {
            public:
                Entry(std::string value, std::vector<std::string> synonyms = {});

                Entry& addSynonym(std::string synonym);

                std::string getValue() const;
                std::vector<std::string> getSynonyms() const;

                virtual ~Entry();
            private:
                std::string value;
                std::vector<std::string> synonyms;
            };

            class Entity
            {
            public:
                Entity(/*std::string id,*/ std::string name, std::vector<Entry> entries = {});

                Entity& addEntry(Entry entry);

//                std::string getId() const;
                std::string getName() const;
                std::vector<Entry> getEntries() const;

                virtual ~Entity();
            private:
//                std::string id;
                std::string name;
                std::vector<Entry> entries;
            };
        }
    }
}

#endif // ENTITY_H
