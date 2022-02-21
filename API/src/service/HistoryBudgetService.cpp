
#include "HistoryBudgetService.hpp"

oatpp::Object<PageDto<oatpp::Object<HistoryBudgetDto>>>HistoryBudgetService::getHistoryBudgetsByUserId(const oatpp::Int32 &userId, const oatpp::UInt32 &offset, const oatpp::UInt32 &limit) {
    oatpp::UInt32 countToFetch = limit;

    auto dbResult = m_database->getHistoryBudgetsByUserId(userId, offset, countToFetch);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<HistoryBudgetDto>>>();

    auto page = PageDto<oatpp::Object<HistoryBudgetDto>>::createShared();
    page->offset = offset;
    page->limit = countToFetch;
    page->count = items->size();
    page->items = items;

    return page;
}

oatpp::Object<HistoryBudgetDto> HistoryBudgetService::getBudgetById(const oatpp::Int32 &id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection> &connection) {
    auto dbResult = m_database->getBudgetById(id, connection);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Budget not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<HistoryBudgetDto>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];

}

oatpp::Object<HistoryBudgetDto> HistoryBudgetService::createBudget(const oatpp::Object<HistoryBudgetDto> &dto) {
    auto dbResult = m_database->createBudget(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto budgetId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

    return getBudgetById((v_int32) budgetId);

}

oatpp::Object<StatusDto> HistoryBudgetService::deleteBudgetsByReceiptId(const oatpp::Int32 &receiptId) {
    auto dbResult = m_database->deleteBudgetsByReceiptId(receiptId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto status = StatusDto::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Budget was successfully deleted";
    return status;
}

oatpp::Object<StatusDto> HistoryBudgetService::deleteBudgetsByUserId(const oatpp::Int32 &userId) {
    auto dbResult = m_database->deleteBudgetsByUserId(userId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto status = StatusDto::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Budgets was successfully deleted";
    return status;
}
