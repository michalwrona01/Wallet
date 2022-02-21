
#ifndef ReceiptController_hpp
#define ReceiptController_hpp

#include "service/ReceiptService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * User REST controller.
 */
class ReceiptController : public oatpp::web::server::api::ApiController {
public:
    ReceiptController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
            : oatpp::web::server::api::ApiController(objectMapper)
    {}
private:
    ReceiptService m_receiptService; // Create user service.
public:

    static std::shared_ptr<ReceiptController> createShared(
            OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
    ){
        return std::make_shared<ReceiptController>(objectMapper);
    }

    ENDPOINT_INFO(getReceiptById) {
        info->summary = "Get one Receipt by receiptId";

        info->addResponse<Object<ReceiptDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["receiptId"].description = "Receipt Identifier";
    }
    ENDPOINT("GET", "receipts/{receiptId}", getReceiptById,
             PATH(Int32, receiptId))
    {
        return createDtoResponse(Status::CODE_200, m_receiptService.getReceiptById(receiptId));
    }

    ENDPOINT_INFO(createReceipt){
        info->summary = "Create new receipt";

        info->addConsumes<Object<ReceiptDto>>("application/json");

        info->addResponse<Object<ReceiptDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }

    ENDPOINT("POST", "receipts", createReceipt,
             BODY_DTO(Object<ReceiptDto>, receiptDto))
    {
        return createDtoResponse(Status::CODE_200, m_receiptService.createReceipt(receiptDto));
    }

    ENDPOINT_INFO(getReceiptsByUserId){
        info->summary = "get all receipts by user id";

        info->addResponse<oatpp::Object<ReceiptsDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("GET", "receipts/user/{userId}/offset/{offset}/limit/{limit}", getReceiptsByUserId,
             PATH(Int32, userId),
             PATH(UInt32, offset),
             PATH(UInt32, limit)){
        return createDtoResponse(Status::CODE_200, m_receiptService.getAllReceiptsByUserId(userId, offset, limit));
    }

    ENDPOINT_INFO(deleteReceiptsByUserId) {
        info->summary = "Delete Receipt by UserId";

        info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["userId"].description = "User Identifier";
    }
    ENDPOINT("DELETE", "receipts/user/{userId}", deleteReceiptsByUserId,
             PATH(Int32, userId))
    {
        return createDtoResponse(Status::CODE_200, m_receiptService.deleteReceiptsByUserId(userId));
    }
};



#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif /* ReceiptController_hpp */
