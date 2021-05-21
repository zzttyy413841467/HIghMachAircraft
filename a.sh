### new.sh

# 输入一个文件名 $projectname
read projectname

# 添加前缀
filename=$projectname

# 源文件目录
Src="$filename/Sources"

# 头文件目录
Inc="$filename/Headers"

# 创建项目树
mkdir -p $Src $Inc $filename/Output/bin

# 创建makefile文件
touch $filename/makefile

# 创建 main.cpp文件
touch $Src/main.cpp

# 文件名小写转换
#declare -l lfilename=$projectname
lfilename="${projectname,,}"

# 源文件
cpp_file=$Src"/"${lfilename}".cpp"
# 头文件
hpp_file=$Inc"/"${lfilename}".hpp"

# 创建一对项目文件
touch $cpp_file $hpp_file

# 向main.cpp中写入内容
echo "#include <iostream> " >> $Src/main.cpp
echo "#include \"$lfilename.hpp\"" >> $Src/main.cpp
echo "" >> $Src/main.cpp
echo "using namespace std;" >> $Src/main.cpp
echo "" >> $Src/main.cpp
echo "int main()" >> $Src/main.cpp
echo "{" >> $Src/main.cpp
echo "    cout << \"Hello VSC\" << endl;" >> $Src/main.cpp
echo "    return 0;" >> $Src/main.cpp
echo "}" >> $Src/main.cpp

# 向*.hpp中写入内容
echo "#pragma once" >> $Inc/$lfilename.hpp
echo "#include <iostream>" >> $Inc/$lfilename.hpp
echo "using namespace std;" >> $Inc/$lfilename.hpp
echo "" >> $Inc/$lfilename.hpp
echo "class $projectname" >> $Inc/$lfilename.hpp
echo "{" >> $Inc/$lfilename.hpp
echo "public:" >> $Inc/$lfilename.hpp
echo "    $projectname();" >> $Inc/$lfilename.hpp
echo "    $projectname($projectname &&) = default;" >> $Inc/$lfilename.hpp
echo "    $projectname(const $projectname &) = default;" >> $Inc/$lfilename.hpp
echo "    $projectname &operator=($projectname &&) = default;" >> $Inc/$lfilename.hpp
echo "    $projectname &operator=(const $projectname &) = default;" >> $Inc/$lfilename.hpp
echo "    ~$projectname();" >> $Inc/$lfilename.hpp
echo "" >> $Inc/$lfilename.hpp
echo "protected:" >> $Inc/$lfilename.hpp
echo "" >> $Inc/$lfilename.hpp
echo "private:" >> $Inc/$lfilename.hpp
echo "" >> $Inc/$lfilename.hpp
echo "};" >> $Inc/$lfilename.hpp

# 向*.cpp中写入内容
echo "#include \"$lfilename.hpp\"" >> $Src/$lfilename.cpp
echo "" >> $Src/$lfilename.cpp
echo "$projectname::$projectname()" >> $Src/$lfilename.cpp
echo "{" >> $Src/$lfilename.cpp
echo "}" >> $Src/$lfilename.cpp
echo "" >> $Src/$lfilename.cpp
echo "$projectname::~$projectname()" >> $Src/$lfilename.cpp
echo "{" >> $Src/$lfilename.cpp
echo "}" >> $Src/$lfilename.cpp

# 导入makefile
# cat "./makefile" >> $filename/makefile
echo "# 描述： C++ 项目 makefile文件" >> $filename/makefile
echo "# 版本： v3.0" >> $filename/makefile
echo "# 修改记录:  1.先测试普通的cpp文件的编译运行" >> $filename/makefile
echo "#		    2.使用变量来改进我们的makefile文件" >> $filename/makefile
echo "#			3.新加了一个源文件" >> $filename/makefile
echo "#			4.使用伪目标，加上clean规则" >> $filename/makefile
echo "#			5.使用wildcard函数，自动扫描当前目录下的源文件" >> $filename/makefile
echo "#			6.加入了自动规则依赖" >> $filename/makefile
echo "#			7.改变依赖关系的生成模式" >> $filename/makefile
echo "#			8.提供多目录文件编译" >> $filename/makefile
echo "" >> $filename/makefile
echo "# 头文件存放目录" >> $filename/makefile
echo "INC_DIR=./Headers" >> $filename/makefile
echo "" >> $filename/makefile
echo "# 可执行文件存放目录" >> $filename/makefile
echo "BIN_DIR=./Output/bin" >> $filename/makefile
echo "" >> $filename/makefile
echo "# 源文件存放目录" >> $filename/makefile
echo "SRC_DIR=./Sources" >> $filename/makefile
echo "" >> $filename/makefile
echo "# 其它中间文件存放目录" >> $filename/makefile
echo "OBJ_DIR=./Output" >> $filename/makefile
echo "" >> $filename/makefile
echo "# 源文件列表" >> $filename/makefile
echo "SRC	:= \${wildcard \${SRC_DIR}/*.cpp}" >> $filename/makefile
echo "" >> $filename/makefile
echo "# obj文件列表" >> $filename/makefile
echo "OBJ	:= \${patsubst %.cpp, \$(OBJ_DIR)/%.o, \${notdir \${SRC}}}" >> $filename/makefile
echo "" >> $filename/makefile
echo "# 定义编译命令变量" >> $filename/makefile
echo "CC	:= g++" >> $filename/makefile
echo "rm	:= rm -rf" >> $filename/makefile
echo "" >> $filename/makefile
echo "# 定义可执行文件变量" >> $filename/makefile
echo "executable	:= main" >> $filename/makefile
echo "BIN_TARGET=\${BIN_DIR}/\${executable}" >> $filename/makefile
echo "" >> $filename/makefile
echo "# 终极目标规则：生成可执行文件" >> $filename/makefile
echo "\${BIN_TARGET}:\${OBJ}" >> $filename/makefile
echo "	\${CC} \${OBJ} -o \$@" >> $filename/makefile
echo "" >> $filename/makefile
echo "# 子目标规则：生成链接文件" >> $filename/makefile
echo "\${OBJ_DIR}/%.o:\${SRC_DIR}/%.cpp" >> $filename/makefile
echo "	\${CC} -o \$@ -c -g $< -I\${INC_DIR}" >> $filename/makefile
echo "" >> $filename/makefile
echo "#clean规则" >> $filename/makefile
echo "#.PHONY: clean" >> $filename/makefile
echo "#clean:" >> $filename/makefile
echo "#清除编译生成的所有文件" >> $filename/makefile
echo "##	\$(RM) \$(BIN_TARGET) \$(OBJ_DIR)/*.o" >> $filename/makefile
echo "#清除编译生成的所有文件,不包括可执行文件" >> $filename/makefile
echo "#	\$(RM) \$(OBJ_DIR)/*.o" >> $filename/makefile
