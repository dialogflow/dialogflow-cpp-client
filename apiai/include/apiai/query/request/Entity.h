#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>

namespace ai {
    namespace query {
        namespace request {
            class Entry {
            public:
                Entry(const std::string &value, const std::vector<std::string> &synonyms = {});

                Entry& addSynonym(const std::string &synonym);

                const std::string &getValue() const;
                const std::vector<std::string> &getSynonyms() const;

                virtual ~Entry();
            private:
                std::string value;
                std::vector<std::string> synonyms;
            };

            class Entity
            {
            public:
                Entity(/*const std::string &id,*/ const std::string &name, const std::vector<Entry> &entries = {});

                Entity& addEntry(const Entry &entry);

//                const std::string &getId() const;
                const std::string &getName() const;
                const std::vector<Entry> &getEntries() const;

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
