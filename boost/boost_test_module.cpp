/*
单元测试框架UTF
    Boost test库提供了一个用于单元测试的基于命令行界面的测试套件UTF: Unit Test Framework，
    具有单元测试、检测内存泄露、监控程序运行的功能。


测试用例与测试套件
    test库将测试程序定义为一个测试模块，由测试安装，测试主体，测试清理和测试运行器四个部分组成。
    
    测试主体是测试模块的实际运行部分，由测试用例和测试套件组织成测试树的形式。
    
    测试用例是一个包含多个测试断言的函数, 是可以被独立执行测试的最小单元, 各个测试用例之间是无关的, 发生的错误不会影响其他测试用例.
    
    测试套件是测试用例的容器，可以嵌套，包含一个或多个测试用例，将多个测试用例分组管理，共享安装/清理代码, 更好的组织测试用例。
    
    主测试套件, 任何UTF单元测试程序必须存在唯一一个主测试套件, 它是整个测试树的根节点, 其他测试套件都是它的子节点. 
    主测试套件的定义可以使用宏BOOST_TEST_MAIN或者BOOST_TEST_MODULE, 它们必须出现在<boost/test/unit_test.hpp>之前.
*/

#define BOOST_TEST_MODULE // 主测试套件
#include <boost/test/unit_test.hpp> // test库头文件

#include <boost/smart_ptr.hpp>
using namespace boost;


BOOST_AUTO_TEST_SUITE(s_smart_ptr) // 测试套件开始

BOOST_AUTO_TEST_CASE(t_scoped_ptr) // 测试用例1
{
    scoped_ptr<int> p(new int(874));
    BOOST_CHECK(p);
    BOOST_CHECK_EQUAL(*p , 874);

    p.reset();
    BOOST_CHECK(p == 0);
}

BOOST_AUTO_TEST_CASE(t_shared_ptr) // 测试用例2
{
    shared_ptr<int> p(new int(100));

    BOOST_CHECK(p);
    BOOST_CHECK_EQUAL(*p , 100);
    BOOST_CHECK_EQUAL(p.use_count(), 1);

    shared_ptr<int> p2 = p;
    BOOST_CHECK_EQUAL(p, p2);
    BOOST_CHECK_EQUAL(p2.use_count(), 2);

    *p2 = 255;
    BOOST_CHECK_EQUAL(*p, 255);
    BOOST_CHECK_GT(*p, 200);
}

BOOST_AUTO_TEST_SUITE_END() // 测试套件结束