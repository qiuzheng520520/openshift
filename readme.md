[程序名]
openshift自动化交互脚本

[用到的脚本语言]
1.shell
2.expect

[功能]
1.自动登录openshift查询状态：查询目录结构、cpu信息、网络、磁盘使用量、磁盘挂载、进程、内存总量。
2.下载代码或目录的压缩文件。
3.运行二进制文件（可以后台）。

[目录]
1.etc	---存放各种配置文件:bashrc、vimrc等。
2.shell ---自动化交互脚本文件
3.src   ---源代码目录

[使用方法]
1.查看openshift状态信息:
命令:./status/status.exp
2.下载压缩文件
命令:./download/download.sh
3.运行二进制文件
命令:./run/run.exp
4.停止进程
命令:./run/stop.exp
5.查看进程运行状态
命令:./run/status.exp

[数据库查询方法]
1.下载sqlite3:http://www.sqlite.org/download.htmli,选择Pre-release Snapshots。
2.编译:./configure;make;make install。
3.打开sqlite数据库文件:sqlite3 test.db
4.查看表:.schema
5.查询表test_db的所有数据:select * from test_db。
6.查看表test_db的记录条目数量:select count(*) from test_db;

