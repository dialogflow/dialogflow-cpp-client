#ifndef QUERYTEXTVISITOR_H
#define QUERYTEXTVISITOR_H

namespace ai {
    namespace query {
        namespace request {
            class QueryOne;
            class QueryMultipleStrings;
            class QueryMultipleVariants;

            class QueryTextVisitor {
            public:
                virtual void visit(const QueryOne& ref) = 0;
                virtual void visit(const QueryMultipleStrings& ref) = 0;
                virtual void visit(const QueryMultipleVariants& ref) = 0;
            };
        }
    }
}

#endif // QUERYTEXTVISITOR_H
