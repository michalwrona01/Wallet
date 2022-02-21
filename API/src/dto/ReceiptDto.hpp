#ifndef ReceiptDto_hpp
#define ReceiptDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)


class ReceiptDto : public oatpp::DTO {

    DTO_INIT(ReceiptDto, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD(String, shopName, "shopName");
    DTO_FIELD(String, companyName, "companyName");
    DTO_FIELD(Int32, numberReceipt, "numberReceipt");
    DTO_FIELD(Int32, nipNumber,"nipNumber");
    DTO_FIELD(Float32, price, "price");
    DTO_FIELD(String, dateCreated, "dateCreated");
    DTO_FIELD(Int32, userId, "userId");
};

#include OATPP_CODEGEN_END(DTO)

#endif /* ReceiptDto_hpp */
