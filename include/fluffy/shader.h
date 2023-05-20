#ifndef INCLUDE_FLUFFY_SHADER_H_
#define INCLUDE_FLUFFY_SHADER_H_
#include <glad/glad.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
// Copyright 2023 Elias Rammos
class Shader {
 public:
  Shader();
  inline unsigned int _id() const { return id_; }
  void use();
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;

 private:
  unsigned int id_;
  void checkCompileErrors(unsigned int shader, std::string type);
};

#endif  // INCLUDE_FLUFFY_SHADER_H_
