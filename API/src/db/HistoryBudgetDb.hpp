
#ifndef CRUD_HISTORYBUDGETDB_HPP
#define CRUD_HISTORYBUDGETDB_HPP

#include "dto/HistoryBudgetDto.hpp"
#include "oatpp-sqlite/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * HistoryBudgetDb client definitions.
 */
class HistoryBudgetDb : public oatpp::orm::DbClient {
public:

    HistoryBudgetDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
            : oatpp::orm::DbClient(executor)
    {

        oatpp::orm::SchemaMigration migration(executor);
//        migration.addFile(3 /* start from version 1 */, DATABASE_MIGRATIONS "/003_init_HistoryBudget.sql");
//        // TODO - Add more migrations here.
//        migration.migrate(); // <-- run migrations. This guy will throw on error.

        auto version = executor->getSchemaVersion();
        OATPP_LOGD("HistoryBudgetDb", "Migration - OK. Version=%lld.", version);

    }

    QUERY(getHistoryBudgetsByUserId,
          "SELECT * FROM AppHistoryBudget WHERE userId=:userId LIMIT :limit OFFSET :offset ",
          PARAM(oatpp::Int32, userId),
          PARAM(oatpp::UInt32, offset),
          PARAM(oatpp::UInt32, limit))

    QUERY(getBudgetById,
          "SELECT * FROM AppHistoryBudget WHERE id=:id",
          PARAM(oatpp::Int32, id))

    QUERY(createBudget,
          "INSERT INTO AppHistoryBudget"
          "(amount, receiptId, dateCreated, topic, userId) VALUES "
          "(:budget.amount, :budget.receiptId, :budget.dateCreated, :budget.topic, :budget.userId);",
          PARAM(oatpp::Object<HistoryBudgetDto>, budget))

    QUERY(deleteBudgetsByReceiptId,
          "DELETE FROM AppHistoryBudget WHERE receiptId=:receiptId;",
          PARAM(oatpp::Int32, receiptId))

    QUERY(deleteBudgetsByUserId,
          "DELETE FROM AppHistoryBudget WHERE userId=:userId;",
          PARAM(oatpp::Int32, userId))
};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //CRUD_HISTORYBUDGETDB_HPP
