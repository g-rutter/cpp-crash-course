// 6-5. Using the example from Chapter 5, make Bank a template class that accepts a template parameter.
//      Use this type parameter as the type of an account rather than long.
//      Verify that your code still works using a Bank<long> class.
// 6-6. Implement an Account class and instantiate a Bank<Account>. Implement functions in Account to keep track of balances.
// 6-7. Make Account an interface. Implement a CheckingAccount and SavingsAccount.
//      Create a program with several checking and savings accounts.
//      Use a Bank<Account> to make several transactions between the accounts.
#include <cstdio>


struct Account {
    Account() : balance{0} {};
    Account(const double balance) : balance{balance} {};
    virtual ~Account() = default;
    virtual void withdraw(const double amount) {
        balance -= amount;
    }
    virtual void deposit(const double amount) {
        balance += amount;
    }
    virtual void report() {
        printf("%g\n", balance);
    }
    protected:
        double balance;
};

struct CheckingAccount : Account {};

struct SavingsAccount : Account {};

struct Bank {
    template<typename AccountType1, typename AccountType2>
    void make_transfer(AccountType1& from, AccountType2& to, double const amount) const {
        from.withdraw(amount);
        to.deposit(amount);
    }
};

int main() {
    CheckingAccount acc1{};
    SavingsAccount acc2{};

    Bank bank{};
    bank.make_transfer(acc1, acc2, 100.0);

    acc1.report();
    acc2.report();
}