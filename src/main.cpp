#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <cctype>

bool isPidDirectory(const std::string& name){
  for(char c : name){
    if(!std::isdigit(static_cast<unsigned char > (c))){
      return false;
    }
  }
  return true;
}

std::string getProcessName(const std::string& pid){
  std::string path{};
  path = "/proc/" + pid + "/comm";

  std::ifstream file{path};
  std::string name{};

  if(file.is_open()){
    std::getline(file, name);
  } 
  return name;
}

int main(){
  std::string procPath{};
  procPath = "/proc";

  for(const auto& entry : std::filesystem::directory_iterator(procPath)){
    if(!entry.is_directory()){
      continue;
    }
    std::string pidStr{};
    pidStr = entry.path().filename().string();

    if(!isPidDirectory(pidStr)){
      continue;
    }
    std::string processName{};
    processName = getProcessName(pidStr);

    if(!processName.empty()){
      std::cout << "PID: " << pidStr << " | Name: " << processName << '\n';
    }
  }
  return 0;
}
