cmake_minimum_required(VERSION 3.1)
project(crud)

set(CMAKE_CXX_STANDARD 11)

add_library(crud-lib
        src/controller/StaticController.hpp
        src/controller/UserController.hpp
        src/controller/ReceiptController.hpp
        src/controller/HistoryBudgetController.hpp
        src/db/UserDb.hpp
        src/db/ReceiptDb.hpp
        src/db/HistoryBudgetDb.hpp
        src/dto/PageDto.hpp
        src/dto/StatusDto.hpp
        src/dto/UserDto.hpp
        src/dto/ReceiptDto.hpp
        src/dto/HistoryBudgetDto.hpp
        src/service/UserService.cpp
        src/service/UserService.hpp
        src/service/ReceiptService.cpp
        src/service/ReceiptService.hpp
        src/service/HistoryBudgetService.cpp
        src/service/HistoryBudgetService.hpp
        src/AppComponent.hpp
        src/DatabaseComponent.hpp
        src/SwaggerComponent.hpp
        src/ErrorHandler.cpp
        src/ErrorHandler.hpp)

## include directories

target_include_directories(crud-lib PUBLIC src)


## link libs

find_package(oatpp          1.3.0 REQUIRED)
find_package(oatpp-swagger  1.3.0 REQUIRED)
find_package(oatpp-sqlite   1.3.0 REQUIRED)

target_link_libraries(crud-lib
        # Oat++
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
        PUBLIC oatpp::oatpp-sqlite
)

# If CMake can't find SQLite3:
#
# 1. Make sure that you've built oatpp-sqlite with -DOATPP_SQLITE_AMALGAMATION=ON flag
# 2. If you are not willing to use SQLite amalgamation then uncomment the following lines:
#
#find_package(SQLite3 REQUIRED)

#target_link_libraries(crud-lib
#   PUBLIC SQLite::SQLite3
#)

add_definitions(
        ## define path to swagger-ui static resources folder
        -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"

        ## SQLite database file
        -DDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/db.sqlite"
        ## SQLite database test file
        -DTESTDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/test-db.sqlite"

        ## Path to database migration scripts
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"
)

if(CMAKE_SYSTEM_NAME MATCHES Linux)
    find_package(Threads REQUIRED)
    target_link_libraries(crud-lib INTERFACE Threads::Threads ${CMAKE_DL_LIBS})
endif()

## add executables

add_executable(crud-exe src/App.cpp)
target_link_libraries(crud-exe crud-lib)

#add_executable(crud-test
#        test/tests.cpp
#        test/app/TestClient.hpp
#        test/app/TestDatabaseComponent.hpp
#        test/app/TestComponent.hpp
#        test/UserControllerTest.hpp
#        test/UserControllerTest.cpp)
#target_link_libraries(crud-test crud-lib)
#
#enable_testing()
#add_test(project-tests crud-test)
