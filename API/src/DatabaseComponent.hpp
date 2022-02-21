
#ifndef CRUD_DATABASECOMPONENT_HPP
#define CRUD_DATABASECOMPONENT_HPP

#include "db/UserDb.hpp"
#include "db/ReceiptDb.hpp"
#include "db/HistoryBudgetDb.hpp"

class DatabaseComponent {
public:
    
  /**
   * Create database connection provider component
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, dbConnectionProvider)([] {

    /* Create database-specific ConnectionProvider */
    auto connectionProvider = std::make_shared<oatpp::sqlite::ConnectionProvider>(DATABASE_FILE);

    /* Create database-specific ConnectionPool */
    return oatpp::sqlite::ConnectionPool::createShared(connectionProvider,
                                                       10 /* max-connections */,
                                                       std::chrono::seconds(5) /* connection TTL */);

  }());

  /**
   * Create database client
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<UserDb>, userDb)([] {

    /* Get database ConnectionProvider component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, connectionProvider);

    /* Create database-specific Executor */
    auto executor = std::make_shared<oatpp::sqlite::Executor>(connectionProvider);

    /* Create MyClient database client */
    return std::make_shared<UserDb>(executor);

  }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<HistoryBudgetDb>, historyBudgetDb)([] {

        /* Get database ConnectionProvider component */
        OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, connectionProvider);

        /* Create database-specific Executor */
        auto executor = std::make_shared<oatpp::sqlite::Executor>(connectionProvider);

        /* Create MyClient database client */
        return std::make_shared<HistoryBudgetDb>(executor);

    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<ReceiptDb>, receiptDb)([] {

        /* Get database ConnectionProvider component */
        OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, connectionProvider);

        /* Create database-specific Executor */
        auto executor = std::make_shared<oatpp::sqlite::Executor>(connectionProvider);

        /* Create MyClient database client */
        return std::make_shared<ReceiptDb>(executor);

    }());

};

#endif //CRUD_DATABASECOMPONENT_HPP
