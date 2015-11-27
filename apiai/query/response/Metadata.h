#ifndef METADATA_H
#define METADATA_H

#include <memory>

namespace ai {
    namespace query {
        class QueryRequest;

        namespace response {
            class Metadata {
            public:
                std::shared_ptr<std::string> getIntentId() const;
                std::shared_ptr<std::string> getIntentName() const;

                virtual ~Metadata();
            private:

                Metadata();
                Metadata(std::shared_ptr<std::string> intentId, std::shared_ptr<std::string> intentName);

                const std::shared_ptr<std::string> intentId;
                const std::shared_ptr<std::string> intentName;

                friend class ai::query::QueryRequest;
                friend std::ostream& operator << (std::ostream& os, const Metadata& metadata);
            };

            std::ostream& operator << (std::ostream& os, const Metadata& metadata);
        }
    }
}

#endif // METADATA_H
