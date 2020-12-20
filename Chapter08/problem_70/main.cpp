// #70 承認システム
// Chain of Responsibility パターン
#include <iostream>
#include <string>
#include <string_view>
#include <memory>
#include <limits>

// 役職を表す抽象基底クラス
class role
{
public:
   // 決裁できる限度額
   virtual double approval_limit() const noexcept = 0;
   virtual ~role() {}
};

class employee_role : public role
{
public:
   virtual double approval_limit() const noexcept override
   {
      return 1000;
   }
};

class team_manager_role : public role
{
public:
   virtual double approval_limit() const noexcept override
   {
      return 10000;
   }
};

class department_manager_role : public role
{
public:
   virtual double approval_limit() const noexcept override
   {
      return 100000;
   }
};

class president_role : public role
{
public:
   virtual double approval_limit() const noexcept override
   {
      return std::numeric_limits<double>::max();
   }
};

struct expense
{
   double      amount;
   std::string description;

   expense(double const amount, std::string_view desc):
      amount(amount), description(desc)
   {
   }
};

// 事業所内の従業員を表すクラス
class employee
{
public:
   explicit employee(std::string_view name, std::unique_ptr<role> ownrole) :
      name(name), own_role(std::move(ownrole))
   {
   }

   // std::shared_ptr は値渡し
   void set_direct_manager(std::shared_ptr<employee> manager)
   {
      direct_manager = manager;
   }

   // 決裁を仰ぐ
   void approve(expense const & e)
   {
      // 自分で決済できる金額ならば経費を処理する。
      if(e.amount <= own_role->approval_limit())
         std::cout << name << " approved expense '" << e.description << "', cost=" << e.amount << std::endl;
      // そうでなければ自分の上司に決済を仰ぐ。
      // この本では nullptr を初めて見た？
      else if(direct_manager != nullptr)
         direct_manager->approve(e);
   }

private:
   std::string                name; // 自分の名前
   std::unique_ptr<role>      own_role; // 自分の役職
   std::shared_ptr<employee>  direct_manager; // 自分の上司
};

int main()
{
   // make_shared() と make_unique() が入り乱れる面倒なコードだ
   auto john = std::make_shared<employee>("john smith", std::make_unique<employee_role>());
   auto robert = std::make_shared<employee>("robert booth", std::make_unique<team_manager_role>());
   auto david = std::make_shared<employee>("david jones", std::make_unique<department_manager_role>());
   auto cecil = std::make_shared<employee>("cecil williamson", std::make_unique<president_role>());

   john->set_direct_manager(robert);
   robert->set_direct_manager(david);
   david->set_direct_manager(cecil);

   john->approve(expense{500, "magazines"});
   john->approve(expense{5000, "hotel accomodation"});
   john->approve(expense{50000, "conference costs"});
   john->approve(expense{200000, "new lorry"});
}

// john smith approved expense 'magazins', cost=500
// robert booth approved expense 'hotel accomodation', cost=5000
// david jones approved expense 'conference costs', cost=50000
// cecil williamson approved expense 'new lorry', cost=200000
