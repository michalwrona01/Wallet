#ifndef HistoryBudgetDto_hpp
#define HistoryBudgetDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)


class HistoryBudgetDto : public oatpp::DTO {

    DTO_INIT(HistoryBudgetDto, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD(Float32 , amount, "amount");
    DTO_FIELD(Int32 , receiptId, "receiptId");
    DTO_FIELD(String , dateCreated, "dateCreated");
    DTO_FIELD(String, topic, "topic");
    DTO_FIELD(Int32, userId,"userId");
};

#include OATPP_CODEGEN_END(DTO)

#endif /* HistoryBudgetDto_hpp */
