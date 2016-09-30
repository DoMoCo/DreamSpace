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
	virtual bool check_in(const::std::string &) = 0;//����
	virtual std::string user_name()const = 0;
	virtual void display_borrow(LibMat &libmat) = 0;//��ӡ������Ϣ
	virtual void display_data() = 0;                //��ӡ�û���Ϣ
	virtual bool is_borrow(std::string book_name) = 0;
	virtual void change_password() = 0;
	virtual void borrow_book(std::string &) = 0;    //����
	virtual void return_book(std::string &) = 0;    //����
	virtual bool kill_me() = 0;
	virtual void check_out(bool save_me,bool book) = 0;       //��������       
protected:
	std::vector<std::string> _file1;//���ڱ��������ı�
	std::vector<std::string> _file2;//��дʱ���Ч��
	std::vector<std::string> _file3;//file_1+Ҫ����������+file_2=Ҫ������ı�
	std::vector<std::string> _file4;//
};

class Student:public User {
public:
	Student(){
	}
	Student(const std::string &);
	virtual bool check_in(const std::string &);
	virtual std::string user_name()const { return _user_name; }
	virtual bool is_borrow(std::string book_name);   //�ж��鼮�Ƿ��ڽ�������
	virtual void change_password();                       //�޸�����
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
	std::string _user_name;               //�û���
	std::string _password;				  //��������
	std::string _id;			          //ѧ��
	std::string _academe;			      //ѧԺ
	std::vector<std::string> _borrow_book;//������Ϣ	
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
	std::string _user_name;			//�û���
	std::string _password;		    //��������
	std::string _job_num;			//����
	std::vector<std::string>_borrow_book;//������Ϣ	
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
private://Ϊ����Ƶ�����ļ���д
	std::string _password;//��������
	//book_source������class LibMat����
	std::vector<std::string> _student_id;//student_data�ļ�����
	std::vector<std::string> _student_name;
	std::vector<std::string> _student_academe;
	std::vector<std::vector<std::string> > _student_book;

	std::map<std::string,std::string> _student_password;//student_password
	                                                   // �ļ�����
	std::vector<std::string> _teacher_id;//teacher_data�ļ�����
	std::vector<std::string> _teacher_name;
	std::vector<std::vector<std::string> > _teacher_book;

	std::map<std::string, std::string> _teacher_password;//teacher_password
	                                                    //�ļ�����
};
