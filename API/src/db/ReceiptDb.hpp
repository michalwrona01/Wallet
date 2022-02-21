
#ifndef CRUD_RECEIPTDB_HPP
#define CRUD_RECEIPTDB_HPP

#include "dto/ReceiptDto.hpp"
#include "oatpp-sqlite/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * ReceiptDb client definitions.
 */
class ReceiptDb : public oatpp::orm::DbClient {
public:

    ReceiptDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
            : oatpp::orm::DbClient(executor)
    {

        oatpp::orm::SchemaMigration migration(executor);
        migration.addFile(2 /* start from version 1 */, DATABASE_MIGRATIONS "/002_init_receipt.sql");
        // TODO - Add more migrations here.
        migration.migrate(); // <-- run migrations. This guy will throw on error.

        auto version = executor->getSchemaVersion();
        OATPP_LOGD("ReceiptDb", "Migration - OK. Version=%lld.", version);

    }

    QUERY(getReceiptById,
          "SELECT * FROM AppReceipt WHERE id=:id;",
          PARAM(oatpp::Int32, id))

    QUERY(getReceiptsByUserId,
          "SELECT * FROM AppReceipt WHERE userId=:userId LIMIT :limit OFFSET :offset ",
          PARAM(oatpp::Int32, userId),
          PARAM(oatpp::UInt32, offset),
          PARAM(oatpp::UInt32, limit))

    QUERY(createReceipt,
          "INSERT INTO AppReceipt"
          "(shopName, companyName, numberReceipt, nipNumber, price, dateCreated, userId) VALUES "
          "(:receipt.shopName, :receipt.companyName, :receipt.numberReceipt, :receipt.nipNumber, :receipt.price, :receipt.dateCreated, :receipt.userId);",
          PARAM(oatpp::Object<ReceiptDto>, receipt))

    QUERY(updateReceipt,
          "UPDATE AppReceipt "
          "SET "
          " shopName=:receipt.shopName, "
          " companyName=:receipt.companyName, "
          " numberReceipt=:receipt.numberReceipt, "
          " nipNumber=:receipt.nipNumber, "
          " price=:receipt.price, "
          " userId=:receipt.userId, "
          "WHERE "
          " id=:receipt.id;",
          PARAM(oatpp::Object<ReceiptDto>, receipt))

    QUERY(deleteReceiptsByUserId,
          "DELETE FROM AppReceipt WHERE userId=:userId;",
          PARAM(oatpp::Int32, userId))
};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //CRUD_RECEIPTDB_HPP
