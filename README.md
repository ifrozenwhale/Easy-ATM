[TOC]

# 基于命令行的ATM模拟程序的设计与实现

> 初学C++时候实现的，较为有年代感了。

## 功能

1. 显示欢迎词及提示信息；
2. 用户插卡，ATM验证用户账号及密码有效性，输入错误3次即被锁卡；
3. 用户的帐户有两类,一类是存款帐户,一类是借款帐户,存款帐户里的钱是用户自己的钱, 借款帐户无余额只有信用额度和已借银行的钱.。
4. 存款帐户的可以查询余额：初始余额为10000元；
5. 借款帐户的可以查询当前欠银行的钱的数量和信用额度；
6. 存款帐户和借款帐户都可以取款，每次取款额为100的整数倍，有单笔和单日金额限制，存款帐户的余额不能为负，借款帐户欠的钱不能超过信用额度；
7. 存款帐户的可以转账，可将本账户中的存款转入其它账户，转入账户账号需两次输入确认；
8. 借款帐户的可以接受还款（转账），接收其它存款账户将钱转入本账户；
9. 修改密码：密码为6位数字，新密码需要两次输入确认；
10. 退卡。

## UML

![image-20210316225648251](https://frozenwhale.oss-cn-beijing.aliyuncs.com/img/image-20210316225648251.png)

1. 共设计了8个类，分别是ATM类，Account类，DepositAccount类，LoanAccount类，ServerSide类，KeyBoard类，ViewingScreen类，CardRead类。
2. ATM类内嵌KeyBoard类，ViewingScreen类和CardRead类，这三个类代表的组成ATM的硬件部分。内嵌DepositAccount类和LoanAccount类，这两个类的实际意义是虚拟的账户。
3. ATM类依赖于ServerSide类，这个类代表ATM后台即服务器端。
4. ATM类是controller。接受从KeyBoard类传入的数据，调用Account类实现在本机上的处理，然后调用ServerSide类，将处理的请求传至ServerSide。调用ViewingScreen类输出给用户。
5. KeyBoard类是接受输入类，在本实验中接受从键盘输入（命令行）。
6. CardRead类是接受输入类，在本实验中实现卡号的读取（命令行实现）。
7. ViewingScreen类是View类，在本实验中提示语句和反馈处理结果。
8. ServerSide类是model类，在本实验中以对文件操作的形式，模拟ATM后台银行系统的处理过程。
9. Account类是一个基类，表示基本的卡信息。DepositAccount类和LoanAccount类从Account类派生。
10. DepositAccount类是存款账户类，可以进行存款，取款，转账操作，修改密码，查看账户信息，查看交易记录等操作。
11. LoanAccount是借款账户类，可以进行借款，还款，可以接受来自存款账户的转账，可以查看账户信息，查看未读的转账消息，以及查看交易记录等操作。

## 流程

**概述：**用户首先输入卡号，在文件中检索此卡号，判断是否存在，存在则继续输入密码完成登录。输错三次即锁卡，此账户被冻结。在检索卡号的同时，可以判定此卡的账户类型，然后将账户的信息拷贝到相应的账户中，并将ATM当前的账户属性设置为相应的类型。之后用户进行各种操作。

## 部分设计

### 文件数据库模拟

1. `a.txt`。在这个文件，存储着账户（及所有者）信息。格式按照如下格式

   [编号|账户状态|名字|身份证号|卡号|密码|账户余额|账户信用额度|账户欠款|账户类型]

   ![image-20210316225915734](https://frozenwhale.oss-cn-beijing.aliyuncs.com/img/image-20210316225915734.png)

   > 说明：如借款账户无余额项，记为none。

2. `b.txt`。在这个文件中，存储着转账记录。信息按照如下格式

   [转账账户|收款人账户|转账金额]

   ![image-20210316230221125](https://frozenwhale.oss-cn-beijing.aliyuncs.com/img/image-20210316230221125.png)

   

3. `c.txt`。在这个文件中，存储着交易记录。

4. `d.txt`。在这个文件中，储存着账户id，取款金额，以及取款时间。

### ServerSide的读取算法

1. 以空格为分隔符进行读取，将每行的数据以string类型保存在vector<string>中，其中第一个元素表示是否查找到记录。返回vector。
2. 在外部枚举这些数据，对数据进行相应的操作。

### ServerSide的更新算法

1. 给定需要更新的数据的所在行数和更新内容，首先对文件内容进行备份。从第一行开始，将数据存储在string中，读完一行，添加换行符。直到读取到要更新的部分，将要更新的内容存进string，然后继续备份文本内容。读取完所有数据后，返回string。
2. 将返回的string再次写到文件中。
3. 为避免读取备份时出现差错导致返回空的字符串，使用try catch进行保护，如果返回了空串，抛出异常防止将文件写为空文件。

###  转账算法

1. 同步转账算法。申请转账后，若此操作合法有效，即进行转账。
2. 转账后会在transfer文件中追加一条转账记录，多次转账多次追加。

### 查看未读转账消息的算法

1. 读取transfer文件，以接收方的账户卡号进行检索，从第一行开始一次读取，读取到后即返回此条消息。

2. 将此条消息的位置标记，然后更新transfer文件，删除该条记录。继续开始检索，依次循环，直到所有消息全部已读，在文件中找不到此账号的记录。

### 查看交易记录的算法

1. 按照账户卡号进行检索，返回所有有关账号的交易记录。

### 判断账户是否达到当日最大金额

1. 将账户id，取款金额以及取款的时间（单位为秒）存储到文件中，每条记录一行。

2. 存取时，判断文件中的此账号第一条记录的时间，和本次要存取的时间差，该时间差未超过一天的秒数，则以追加的形式，向该文件中添加交易记录。若时间差超过了一天的秒数，则首先备份文件的内容。

3. 具体的，首先读取这个文件，记录此id信息所在的行数，以vector的形式保存下来，然后依次删除改行记录，做法是，读取文件中的内容，遇到改行则将改行内容置换为“”，其他的部分复制，返回这个字符串。将该字符串重写到文件中。下一次删除的时候，行数减一（由于已经删除了一行，将所有的行上移）。

## 总结

1. **实现了接口分离，例如输入、处理、输出分离。**

   设置接受输入类的原因在于，如果不是在命令行中实现，只需要在KeyBoard类中添加方法，然后再原位置调用新的方法即可。输出分离，想要输入到不同的位置，也只需要修改ViewingScreen类中的方法。而处理的操作并没有在ATM类直接进行，而是由服务器端类ServerSide类完成，这也符合实际情况，ATM只是一个负责中转的控制，真正处理的部分在银行系统（数据库中）。事实上，通过这样的设计，在为我后来补充完善或者修改的时候，提供了巨大的方便，不用测试什么代码，就能实现功能的增加。

2. **没有使用多态进行两个账户的操作。**原因是，使用多态时，子类的方法及参数被统一，而这为账户类型的拓展带来了麻烦。尽管使用多态，可以用父类的指针改变指向来进行不同账户的操作，避免了分情况讨论从而减小了代码量，但是相比功能性和拓展性，我仍放弃了多态的使用（有多态的版本）。

3. **遗憾是数据的存储不够完善。**将所有的账户信息存储在一个文件中，不方便操作。目前的想法是，一个文件中存储着基本的账户信息，包括卡号和卡的类型。然后一个卡号对应3个文件，一个是账户及其所有人的信息，一个是该账号的交易记录信息，一个是该账号的转账信息。