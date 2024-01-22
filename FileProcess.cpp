#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

std::string process(const std::string& text)
{
	std::string result;
	for(auto c : text)
	{
		if(c == '\n')
		{
			result.push_back(',');
		}
		result.push_back(c);
	}
	return result;
}
int main(int argc,char** argv)
{
	std::string text {};
	std::stringstream content;
	std::ifstream fin;
	if(argc > 1)
	{
		std::cout << "opening : " << argv[1] << std::endl;
		fin.open(argv[1]);
		content << fin.rdbuf();
	}
	else
	{
		std::cout << "Please input : " << std::endl;
		content << std::cin.rdbuf();
	}
	text = content.str();
	text = process(text);
	std::cout << "-------------------" << std::endl;
	std::cout << text << std::endl;
	if(argc > 1)
	{
		fin.close();
		std::ofstream fout(argv[1],std::ios::out | std::ios::trunc);
		fout << text;
		fout.close();
	}
	system("pause");
	return 0;
}
