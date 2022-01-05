#include <iostream>
using namespace std;

#include <boost/format.hpp>
#include <boost/test/minimal.hpp>

//最小化测试套件
/*
    BOOST_CHECK(e)	断言测试通过, 如不通过不影响程序执行
    BOOST_REQUIRE(e)	要求断言必须通过, 否则程序停止执行
    BOOST_ERROR(e1, e2)	给出错误信息, 程序继续执行
    BOOST_FAIL(e1, e2)	给出错误信息, 程序运行停止
*/
int test_main(int argc, char* argv[])
{
    using namespace boost;
    format fmt("%d-%d");

    BOOST_CHECK(fmt.size() != 0);//断言测试通过，如不通过不影响程序执行
    fmt % 12 % 34;
    BOOST_REQUIRE(fmt.str() == "12-34");//要求断言必须通过，否则程序停止执行
    BOOST_ERROR("演示一条错误信息");
    fmt.clear();
    fmt % 12;

    try{
        std::cout << fmt;
    }
    catch(...)
    {
        BOOST_FAIL("致命错误，测试终止");
    }
    return 0;
}
//
// int mainminimal_test内部实现了main(), 因此无需自己编写main()函数, 
//只要实现test_main()即可, 它是minimal_test的真正功能函数. 注意test_main()必须返回一个整数.