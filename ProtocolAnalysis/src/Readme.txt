注意事项

(1)
每一个符号之间必须使用至少一个空格、换行、水平制表符分割，否则解析错误
变量声明后面一定要跟一个等号"=" ，然后写上赋值，赋值后面一定要有一个分号
uint32 time_1 = 1; 		// 成员属性测试-1

(2)
枚举定义最后一定要加一个分号";"
enum eTest
{
	eValue_1 = 0;		// 测试枚举值
};

(3)
多行注释只支持在 Proto 顶层元素注释，不支持在成员中注释
/**
 * @brief 多行测试
 */
message stTestMulti : stBase
{
	base aaa = eTest.eValue_1;	// 定义基类成员的数值，基类成员前面添加 base ，不用写类型
	uint32 time = 1; 		// 成员属性测试
};

(4)
不支持嵌套定义类型，所有类型定义都要卸载 proto 顶级中

(5)
名字空间定义
package Game.Msg;

(6)
C++ 包含的头文件
header "aaa/bbb.h","dddd/gggg.h";	// 包含头文件

(7)
CS 需要导入的名字空间
import SDK.Lib,Game.UI;		// 命名空间解释

(8)
仅仅支持 enum message 两个类型定义，不支持 proto 顶层宏定义和常亮定义