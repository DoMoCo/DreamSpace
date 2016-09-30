#include<vector>
#include<string>
#include<map>

class LibMat {
public:
	LibMat();
	void display();
	bool find_book(std::string book_name);
	bool find_autor(std::string autor_name);
	std::string a_find_b(std::string autor_name);
	std::string b_find_a(std::string book_name);
	int num_of_book(std::string book_name);
	void borrow_book(std::string book_name) { _num_of_book[book_name]--; }
	void return_book(std::string book_name) { _num_of_book[book_name]++; }
	void add_book(std::string book_name, std::string autor_name, int sum);
	void change_book(std::string old_name,const std::string new_name, 
		             const std::string autor_name, int sum);
	void remove_book(std::string book_name);
	void delete_all_data();
	void check_out();
private:
	std::vector<std::string> _all_book;
	std::vector<std::string> _all_autor;
	std::map<std::string, int> _num_of_book;
};
