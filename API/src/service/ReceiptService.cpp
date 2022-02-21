
#include "ReceiptService.hpp"


oatpp::Object<ReceiptDto> ReceiptService::getReceiptById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection) {

    auto dbResult = m_database->getReceiptById(id, connection);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Receipt not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<ReceiptDto>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];
}

oatpp::Object<ReceiptDto> ReceiptService::createReceipt(const oatpp::Object<ReceiptDto> &dto) {
    auto dbResult = m_database->createReceipt(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto receiptId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

    return getReceiptById((v_int32) receiptId);
}

oatpp::Object<PageDto<oatpp::Object<ReceiptDto>>>ReceiptService::getAllReceiptsByUserId(const oatpp::Int32 &userId, const oatpp::UInt32 &offset, const oatpp::UInt32 &limit) {
    oatpp::UInt32 countToFetch = limit;

    auto dbResult = m_database->getReceiptsByUserId(userId, offset, countToFetch);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<ReceiptDto>>>();

    auto page = PageDto<oatpp::Object<ReceiptDto>>::createShared();
    page->offset = offset;
    page->limit = countToFetch;
    page->count = items->size();
    page->items = items;

    return page;
}

oatpp::Object<StatusDto> ReceiptService::deleteReceiptsByUserId(const oatpp::Int32 &userId) {
    auto dbResult = m_database->deleteReceiptsByUserId(userId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto status = StatusDto::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Receipts was successfully deleted";
    return status;
}

