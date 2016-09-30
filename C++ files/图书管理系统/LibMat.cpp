#include"LibMat.h"
#include"func.h"
#include<fstream>
#include<iostream>
#include<iomanip>
#include<map>
#define space "\t\t\t\t\t\t"
using namespace std;

LibMat::LibMat()
{
	ifstream infile("book_resource.txt");
	if (!infile)
		cerr << space << "Oops!Cannot open the resource file!";
	else
	{
		string ch;
		string book_name;
		string autor_name;
		int num;
		while (infile >> ch&&(!ch.empty()))
		{
			infile >> book_name;
			infile >> autor_name;
			infile >> num;
			_all_book.push_back(book_name);
			_all_autor.push_back(autor_name);
			_num_of_book[book_name] =num;
		}
	}
}

bool LibMat::find_book(string book_name)
{
	vector<string>::iterator beg = _all_book.begin();
	vector<string>::iterator end_it = _all_book.end();
	for (; beg != end_it; ++beg)
	{
		if (book_name == *beg)
			return true;
	}
	return false;
}

bool LibMat::find_autor(std::string autor_name)
{
	vector<string>::iterator beg = _all_autor.begin();
	vector<string>::iterator end_it = _all_autor.end();
	for (; beg != end_it; ++beg)
	{
		if (autor_name == *beg)
			return true;
	}
	return false;
}

void LibMat::display()
{
	int sum_book=0;
	int number = 0;
	vector<string>::iterator beg_book = _all_book.begin();
	vector<string>::iterator beg_autor = _all_autor.begin();
	vector<string>::iterator end_it = _all_book.end();
	cout << space << "┌─────────────┬──────────┬────┐\n"
		 << space << "│           书名           │        作者        │ 馆藏量 │\n";
	for (; beg_book != end_it; ++beg_book,++beg_autor)
	{
		cout << space << "├─────────────┼──────────┼────┤\n"
			 << space << "│";
		print_table(*beg_book, 26);
		print_table(*beg_autor, 20);
		int sum = _num_of_book[*beg_book];
		print_table(sum, 8);
		cout << endl;
		sum_book += sum;
		number++;
	}
	cout << space << "├─────────────┼──────────┴────┤\n"
		 << space << "│    存书量    ";
	print_table(number, 12);
	cout << "    库存总量    ";
	print_table(sum_book, 14);
	cout <<'\n'
		 << space << "└─────────────┴───────────────┘"
		 << endl;
}

string LibMat::a_find_b(string autor_name)
{
	vector<string>::iterator beg = _all_autor.begin();
	vector<string>::iterator end_it = _all_autor.end();
	vector<string>::iterator beg_1 = _all_book.begin();
	for (; beg != end_it; ++beg,++beg_1)
	{
		if (autor_name == *beg)
			return *beg_1;
	}
	return 0;
}

string LibMat::b_find_a(string book_name)
{
	vector<string>::iterator beg = _all_book.begin();
	vector<string>::iterator end_it = _all_book.end();
	vector<string>::iterator beg_1 = _all_autor.begin();
	for (; beg != end_it; ++beg,++beg_1)
	{
		if (book_name == *beg)
			return *beg_1;
	}
	return 0;
}

int LibMat::num_of_book(string book_name)
{
	map<string,int>::iterator it = _num_of_book.find(book_name);
	if (it != _num_of_book.end())
		return it->second;
	else
		return 0;
}

void LibMat::add_book(std::string book_name, std::string autor_name, int sum)
{
	_all_book.push_back(book_name);
	_all_autor.push_back(autor_name);
	_num_of_book[book_name] = sum;
}

void LibMat::change_book(std::string old_name, const std::string new_name, 
	                     const std::string autor_name, int sum)
{
	vector<string>::iterator beg = _all_book.begin();
	vector<string>::iterator end_it = _all_book.end();
	vector<string>::iterator beg_1 = _all_autor.begin();
	for (; beg != end_it; ++beg, ++beg_1)
	{
		if (old_name == *beg)
		{
			if (!new_name.empty())
				*beg = new_name;
			else if (!autor_name.empty())
				*beg_1 = autor_name;
			else if (sum != -1)
				_num_of_book[*beg] = sum;
			break;
		}
	}
}

void LibMat::remove_book(string book_name)
{
	vector<string>::iterator beg = _all_book.begin();
	vector<string>::iterator end_it = _all_book.end();
	vector<string>::iterator beg_1 = _all_autor.begin();
	for (; beg != end_it; ++beg, ++beg_1)
	{
		if (book_name == *beg)
		{
			_all_book.erase(beg);
			_all_autor.erase(beg_1);
			map<string, int>::iterator it;
			it = _num_of_book.find(book_name);
			_num_of_book.erase(it);
			break;
		}	
	}
}

void LibMat::delete_all_data()
{
	_all_book.clear();
	_all_autor.clear();
	_num_of_book.clear();
}

void LibMat::check_out()
{
	ofstream outfile("book_resource.txt");
	if (!outfile)
		cerr << space << "Oops!Cannot open the resource file!";
	else
	{
		vector<string>::iterator beg = _all_book.begin();
		vector<string>::iterator end_it = _all_book.end();
		vector<string>::iterator beg_1 = _all_autor.begin();
		for (int index = 1; beg != end_it; ++beg, ++beg_1, ++index)
			outfile << left << setw(5) << index << ' '
			<< setw(30) << *beg << ' ' << setw(30) << *beg_1 << ' '
			<< setw(5) << _num_of_book[*beg] << endl;
	}
}