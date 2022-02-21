
#ifndef CRUD_HISTORYBUDGETSERVICE_HPP
#define CRUD_HISTORYBUDGETSERVICE_HPP

#include "db/HistoryBudgetDb.hpp"
#include "dto/PageDto.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class HistoryBudgetService {
private:
    typedef oatpp::web::protocol::http::Status Status;
private:
    OATPP_COMPONENT(std::shared_ptr<HistoryBudgetDb>, m_database); // Inject database component
public:
    oatpp::Object<PageDto<oatpp::Object<HistoryBudgetDto>>> getHistoryBudgetsByUserId(const oatpp::Int32 &userId,const oatpp::UInt32 &offset, const oatpp::UInt32 &limit);
    oatpp::Object<HistoryBudgetDto> getBudgetById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr);
    oatpp::Object<HistoryBudgetDto> createBudget(const oatpp::Object<HistoryBudgetDto>& dto);
    oatpp::Object<StatusDto> deleteBudgetsByReceiptId(const oatpp::Int32& receiptId);
    oatpp::Object<StatusDto> deleteBudgetsByUserId(const oatpp::Int32& userId);
};

#endif //CRUD_HISTORYBUDGETSERVICE_HPP