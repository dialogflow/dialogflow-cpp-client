#ifndef FULFILLMENT_H
#define FULFILLMENT_H

#include <string>

namespace ai {
    namespace query {
        class QueryRequest;

        namespace response {
            class Fulfillment {
            public:
                std::string getSpeech() const;

                virtual ~Fulfillment();
            private:
                Fulfillment(std::string speech);

                const std::string speech;

                friend class ai::query::QueryRequest;
            };
        }
    }
}

#endif // FULFILLMENT_H
