
#ifndef CRUD_PAGEDTO_HPP
#define CRUD_PAGEDTO_HPP

#include "UserDto.hpp"
#include "HistoryBudgetDto.hpp"
#include "ReceiptDto.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

template<class T>
class PageDto : public oatpp::DTO {

  DTO_INIT(PageDto, DTO)

  DTO_FIELD(UInt32, offset);
  DTO_FIELD(UInt32, limit);
  DTO_FIELD(UInt32, count);
  DTO_FIELD(Vector<T>, items);

};

class UsersPageDto : public PageDto<oatpp::Object<UserDto>> {

  DTO_INIT(UsersPageDto, PageDto<oatpp::Object<UserDto>>)

};

class HistoryBudgetsDto : public PageDto<oatpp::Object<HistoryBudgetDto>>{
    DTO_INIT(HistoryBudgetsDto, PageDto<oatpp::Object<HistoryBudgetDto>>)
};

class ReceiptsDto : public PageDto<oatpp::Object<ReceiptDto>>{
    DTO_INIT(ReceiptsDto, PageDto<oatpp::Object<ReceiptDto>>)
};

#include OATPP_CODEGEN_END(DTO)

#endif //CRUD_PAGEDTO_HPP
