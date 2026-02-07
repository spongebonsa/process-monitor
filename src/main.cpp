#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>

bool is_pid_folder(const std::string& name){
  return std::all_of(name.begin(), name.end(), [](unsigned char c){
      return std::isdigit(c);
      });
}

std::string get_processed_name(const std::string& pid){
  std::string path = "/proc/" + pid + "/comm";
  std::ifstream file(path);
  std::string name;
  if(file.is_open()){
    std::getline(file, name);
  }
  return name;
}

int main(){

  const std::string proc_path = "/proc";
  for (const auto& entry : std::filesystem::directory_iterator(proc_path)){
    if(!entry.is_directory()) continue;

    std::string pid_str =  entry.path().filename().string();

    if(!is_pid_folder(pid_str)) continue;

    std::string process_name = get_processed_name(pid_str);

    if(!process_name.empty()){
      std::cout << "PID: " << pid_str << " | Name: " << process_name <<'\n';
    }
  }
  return 0;
}
