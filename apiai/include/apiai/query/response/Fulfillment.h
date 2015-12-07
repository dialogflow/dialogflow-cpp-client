#ifndef FULFILLMENT_H
#define FULFILLMENT_H

#include <string>

namespace ai {
    namespace query {
        namespace request {
            class QueryRequest;
        }

        namespace response {
            class Fulfillment {
            public:
                std::string getSpeech() const;

                virtual ~Fulfillment();
            private:
                Fulfillment(std::string speech);

                const std::string speech;

                friend class ai::query::request::QueryRequest;
                friend std::ostream& operator << (std::ostream& os, const Fulfillment& fulfillment);
            };

            std::ostream& operator << (std::ostream& os, const Fulfillment& fulfillment);
        }
    }
}

#endif // FULFILLMENT_H
