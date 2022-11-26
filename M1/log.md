# 这里是历次改动的记录
# 10/30
增加batch/Ui选择，测试了UI模式
调节vis.mac 记得别删除
修改了shape2形状，删除了shape1
# 10/31
计划把in文件和out文件联系起来，顺道run.mac //这个没干
但是今天看了PrimaryGeneratorAction.c&h，但是还没看完。
# 11/03
今天啥也没干捏
明天上午先把这五个hh/cc凑齐吧。
# 11/04
DetectorConstruction.cc里面的位置坐标应该是以几何中心为准
# 11/06
摆烂了两天，感觉目前直接看别的geant4文档也用处不大，
可以想想要拿着这玩意做啥了，内容放笔记本上吧
# 11/7
今天计划先把detector弄一下
注意：修改/tracking/verbose 1为2，数字越大，屏幕打印信息越丰富。
妈的文件被误删了阿
# 11/9
今天把detector小整了一下
形状可用
颜色可以改一下
detector材料还没设置
一定要保存
今天又错删了一次
# 11/11
今天整上了vscode Cmake 
还有git ，代码可以存在github上面了
记得备份
* 11/11/17：50 
现在开始弄PhysicsList
* 11/11/23:01
今天为项目附加了run0.mac脚本
注意：脚本修改后Cmake插件会直接修改，不需要rebuild，
但是修改cc文件后需要重新编译。

注意：今天在StepAction.cc的
void SteppingAction::UserSteppingAction(const G4Step* step)
函数后附加了数据输出部分，目的为在该文件夹生成一个“myData.txt”文件
但运行后该文件未出现，需要debug。不知道为啥就出现了。（22/11/18）

注意：今天在gui模式下运行存在内存占用过高情况，
初步判断是在RockSeam和CoalSeam内次级粒子运算占用所致，
需要下一步在StepAction.cc中控制Track，kill掉前两层生成的非需要粒子。
over，今天下班
# 11/25
Todo：
* 增加粒子轨迹，方向，始发点。
* 生成、读取、分析root文件。
* 定义灵敏探测器SD和Hit抽取数据
* 基于上一条：通过mac脚本控制读取数据来自SteppingAction还是灵敏探测器
# 11/26
今天添加rundata.cc&hh文件，还没测试效果，之后在runaction加root文件生成功能。下班。
* 23:20 已经可以生成root文件了，生成了啥还没看出来。

