#include <iostream>
#include <vector>
using namespace std;

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/assign.hpp>
using namespace boost;

struct global_fixture // 全局测试夹具类
{
    global_fixture(){cout << ("global setup\n");}
    ~global_fixture(){cout << ("global teardown\n");}
};

// 该宏定义的夹具类被应用于整个测试用例的所有测试套件, 包括主测试套件
BOOST_GLOBAL_FIXTURE(global_fixture);

struct assign_fixture // 测试套件夹具类
{
    assign_fixture()
    {cout << ("suit setup\n");}
    ~assign_fixture()
    {cout << ("suit teardown\n");}

    vector<int> v;    // 所有测试用例都可以用的成员变量
};

// 定义测试套件级别的夹具
BOOST_FIXTURE_TEST_SUITE(s_assign, assign_fixture)

BOOST_AUTO_TEST_CASE(t_assign1) // 测试用例1, 测试+=操作符
{
    using namespace boost::assign;

    v += 1,2,3,4;
    BOOST_CHECK_EQUAL(v.size(), 4);
    BOOST_CHECK_EQUAL(v[2], 3);
}

BOOST_AUTO_TEST_CASE(t_assign2) // 测试用例2, 测试push_back函数
{
    using namespace boost::assign;

    push_back(v)(10)(20)(30);

    BOOST_CHECK_EQUAL(v.empty(), false);
    BOOST_CHECK_LT(v[0], v[1]);
}

BOOST_AUTO_TEST_SUITE_END() // 测试套件结束