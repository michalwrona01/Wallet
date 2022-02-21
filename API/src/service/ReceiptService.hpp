
#ifndef CRUD_RECEIPTSERVICE_HPP
#define CRUD_RECEIPTSERVICE_HPP

#include "db/ReceiptDb.hpp"
#include "dto/PageDto.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class ReceiptService {
private:
    typedef oatpp::web::protocol::http::Status Status;
private:
    OATPP_COMPONENT(std::shared_ptr<ReceiptDb>, m_database); // Inject database component
public:
    oatpp::Object<ReceiptDto> getReceiptById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr);
    oatpp::Object<ReceiptDto> createReceipt(const oatpp::Object<ReceiptDto>& dto);
    oatpp::Object<PageDto<oatpp::Object<ReceiptDto>>> getAllReceiptsByUserId(const oatpp::Int32 &userId, const oatpp::UInt32& offset, const oatpp::UInt32& limit);
    oatpp::Object<StatusDto> deleteReceiptsByUserId(const oatpp::Int32& userId);
};

#endif //CRUD_RECEIPTSERVICE_HPP