
#ifndef HistoryBudgetController_hpp
#define HistoryBudgetController_hpp

#include "service/HistoryBudgetService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * HistoryBudget REST controller.
 */
class HistoryBudgetController : public oatpp::web::server::api::ApiController {
public:
    HistoryBudgetController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
            : oatpp::web::server::api::ApiController(objectMapper)
    {}
private:
    HistoryBudgetService m_historyBudgetService; // Create history budget.
public:

    static std::shared_ptr<HistoryBudgetController> createShared(
            OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
    ){
        return std::make_shared<HistoryBudgetController>(objectMapper);
    }

    ENDPOINT_INFO(getHistoryBudgetsByUserId){
        info->summary = "get all budgets by user id";

        info->addResponse<oatpp::Object<HistoryBudgetsDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("GET", "budgets/user/{userId}/offset/{offset}/limit/{limit}", getHistoryBudgetsByUserId,
             PATH(Int32, userId),
             PATH(UInt32, offset),
             PATH(UInt32, limit)){
        return createDtoResponse(Status::CODE_200, m_historyBudgetService.getHistoryBudgetsByUserId(userId, offset, limit));
    }

    ENDPOINT_INFO(getBudgetById) {
        info->summary = "Get one Budget by budgetId";

        info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["budgetId"].description = "Budget Identifier";
    }
    ENDPOINT("GET", "budgets/{budgetId}", getBudgetById,
             PATH(Int32, budgetId))
    {
        return createDtoResponse(Status::CODE_200, m_historyBudgetService.getBudgetById(budgetId));
    }

    ENDPOINT_INFO(createBudget) {
        info->summary = "Create new Budget";

        info->addConsumes<Object<HistoryBudgetDto>>("application/json");

        info->addResponse<Object<HistoryBudgetDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("POST", "budgets", createBudget,
             BODY_DTO(Object<HistoryBudgetDto>, budgetDto))
    {
        return createDtoResponse(Status::CODE_200, m_historyBudgetService.createBudget(budgetDto));
    }

    ENDPOINT_INFO(deleteBudgetsByReceiptId) {
        info->summary = "Delete Budgets by receiptId";

        info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["receiptId"].description = "Receipt Identifier";
    }
    ENDPOINT("DELETE", "budgets/receipt/{receiptId}", deleteBudgetsByReceiptId,
             PATH(Int32, receiptId))
    {
        return createDtoResponse(Status::CODE_200, m_historyBudgetService.deleteBudgetsByReceiptId(receiptId));
    }

    ENDPOINT_INFO(deleteBudgetsByUserId) {
        info->summary = "Delete Budgets by userId";

        info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["receiptId"].description = "Receipt Identifier";
    }
    ENDPOINT("DELETE", "budgets/user/{userId}", deleteBudgetsByUserId,
             PATH(Int32, userId))
    {
        return createDtoResponse(Status::CODE_200, m_historyBudgetService.deleteBudgetsByUserId(userId));
    }


};

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif /* HistoryBudgetController_hpp */