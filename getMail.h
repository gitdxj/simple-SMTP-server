#ifndef GET_MAIL
#define GET_MAIL

#include <vector>
#include <string>
#include <io.h>

//获取该路径下的所有文件  
void getFiles(std::string path, std::vector<std::string>& files); 
//只读取某给定路径下的当前文件名 e.g. C:/mail
void getJustCurrentDir(std::string path, std::vector<std::string>& files) ;
//只读取某给定路径下的当前文件名
void getJustCurrentFile(std::string path, std::vector<std::string>& files);

#endif