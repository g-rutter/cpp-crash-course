// 5-1. You didn’t implement an accounting system in your Bank. Design an interface
//      called AccountDatabase that can retrieve and set amounts in bank accounts
//      (identified by a long id).
// 5-2. Generate an InMemoryAccountDatabase that implements AccountDatabase.
// 5-3. Add an AccountDatabase reference member to Bank. Use constructor
//      injection to add an InMemoryAccountDatabase to the Bank.
// 5-4. Modify ConsoleLogger to accept a const char* at construction.
//      When ConsoleLogger logs, prepend this string to the logging output.
//      Notice that you can modify logging behavior without having to modify Bank.
#include <cstdio>
#include <unordered_map>

struct Logger {
    Logger() = default;
    virtual ~Logger() = default;
    virtual void log_transfer(long from, long to, double amount) = 0;
};

struct ConsoleLogger : Logger{
    // TODO dtor?
    ConsoleLogger(const char* name) : name{name} {}
    void log_transfer(long from, long to, double amount) override{
        printf("[%s] %ld -> %ld: %f\n", name, from, to, amount);
    }
    protected:
        const char* name;
};

struct AccountDatabase {
    virtual ~AccountDatabase() = default;
    virtual double get_balance(long account_id) = 0;
    virtual void set_balance(long account_id, double amount) = 0;
};

struct InMemoryAccountDatabase : AccountDatabase {
    std::unordered_map<long, double> balances;

    double get_balance(long account_id) override {
        return balances[account_id];
    }

    void set_balance(long account_id, double amount) override {
        balances[account_id] = amount;
    }
};

struct Bank {
    Bank(Logger* logger, AccountDatabase& account_db) : logger{ logger }, account_db{ account_db } {}
    void set_logger(Logger* new_logger) {
        logger = new_logger;
    }
    void make_transfer(long from, long to, double amount) {
        account_db.set_balance(from ,account_db.get_balance(from) - amount);
        account_db.set_balance(to, account_db.get_balance(to) + amount);
        if (logger) logger->log_transfer(from, to, amount);
    }
    private:
        Logger* logger;
        AccountDatabase& account_db;
};

int main() {
    auto logger{ConsoleLogger("hello")};

    auto account_db{InMemoryAccountDatabase()};
    auto& account_db_ref{account_db};

    auto bank{Bank(&logger, account_db_ref)};
    bank.make_transfer(21L, 55L, 66.6);
}
