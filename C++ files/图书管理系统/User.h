#include<vector>
#include"LibMat.h"
#include<string>
#include<map>
typedef std::vector<std::vector<std::string> >::iterator vv_iterator;
typedef std::vector<std::vector<std::string>::iterator> viterator_v;

class User{
public:
	User(){}
	~User(){}
	virtual bool check_in(const::std::string &) = 0;//登入
	virtual std::string user_name()const = 0;
	virtual void display_borrow(LibMat &libmat) = 0;//打印借书信息
	virtual void display_data() = 0;                //打印用户信息
	virtual bool is_borrow(std::string book_name) = 0;
	virtual void change_password() = 0;
	virtual void borrow_book(std::string &) = 0;    //借书
	virtual void return_book(std::string &) = 0;    //还书
	virtual bool kill_me() = 0;
	virtual void check_out(bool save_me,bool book) = 0;       //保存数据       
protected:
	std::vector<std::string> _file1;//用于保存读入的文本
	std::vector<std::string> _file2;//回写时提高效率
	std::vector<std::string> _file3;//file_1+要操作的数据+file_2=要保存的文本
	std::vector<std::string> _file4;//
};

class Student:public User {
public:
	Student(){
	}
	Student(const std::string &);
	virtual bool check_in(const std::string &);
	virtual std::string user_name()const { return _user_name; }
	virtual bool is_borrow(std::string book_name);   //判断书籍是否在借阅行列
	virtual void change_password();                       //修改密码
	virtual void display_borrow(LibMat &libmat);
	virtual void display_data();
	virtual void borrow_book(std::string &book_name)
	{
		_borrow_book.push_back(book_name);
	}
	virtual void return_book(std::string &);
	virtual bool kill_me();
	virtual void check_out(bool save_me,bool book);
private:
	std::string _user_name;               //用户名
	std::string _password;				  //登入密码
	std::string _id;			          //学号
	std::string _academe;			      //学院
	std::vector<std::string> _borrow_book;//借书信息	
};

class Teacher :public User {
public:
	Teacher(){}
	Teacher(const std::string &);
	virtual bool check_in(const std::string &);
	virtual std::string user_name()const { return _user_name; }
	virtual void display_borrow(LibMat &libmat);
	virtual void display_data();
	virtual bool is_borrow(std::string book_name);
	virtual void change_password();
	virtual void borrow_book(std::string &book_name)
	{
		_borrow_book.push_back(book_name);
	}
	virtual void return_book(std::string &);
	virtual bool kill_me();
	virtual void check_out(bool save_me,bool book);
private:
	std::string _user_name;			//用户名
	std::string _password;		    //登入密码
	std::string _job_num;			//工号
	std::vector<std::string>_borrow_book;//借书信息	
};

class Admin {
public:
	Admin();
	bool check_in(const::std::string &);
	void add_book(LibMat &libmat);
	void change_book(LibMat &libmat);
	void remove_book(LibMat &libmat);
	std::string find_book(LibMat &libmat,bool dispaly = false);
	void add_student();
	bool check_student(std::string &id);
	void remove_student();
	viterator_v &find_student(vv_iterator &beg_book);
	bool check_teacher(std::string &id);
	void add_teacher();
	void remove_teacher();
	viterator_v &find_teacher(vv_iterator &beg_book);
	void display_book(LibMat &libmat) { libmat.display(); }
	void display_student();
	void display_teacher();
	void change_password();
	bool delete_all_data(LibMat &libmat);
	void check_out(bool student, bool teacher,bool password);
private://为避免频繁的文件读写
	std::string _password;//登入密码
	//book_source数据与class LibMat共享
	std::vector<std::string> _student_id;//student_data文件数据
	std::vector<std::string> _student_name;
	std::vector<std::string> _student_academe;
	std::vector<std::vector<std::string> > _student_book;

	std::map<std::string,std::string> _student_password;//student_password
	                                                   // 文件数据
	std::vector<std::string> _teacher_id;//teacher_data文件数据
	std::vector<std::string> _teacher_name;
	std::vector<std::vector<std::string> > _teacher_book;

	std::map<std::string, std::string> _teacher_password;//teacher_password
	                                                    //文件数据
};
