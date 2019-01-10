// -*-C++-*-
/*!
 * @file  ActionManageSVC_impl.cpp
 * @brief Service implementation code of ActionManage.idl
 *
 */

#include "ActionManageSVC_impl.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>

using namespace std;

/*
 * Example implementational code for IDL interface Action::ActionManage
 */
Action_ActionManageSVC_impl::Action_ActionManageSVC_impl()
{
  // Please add extra constructor code here.
}


Action_ActionManageSVC_impl::~Action_ActionManageSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
void Action_ActionManageSVC_impl::read(const char* actionid)
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  #warning "Code missing in function <void Action_ActionManageSVC_impl::read(const char* actionid)>"
  vector<string> data;
  std::ifstream ifs("../../data.csv");
  std::string str;
  
  while(getline(ifs, str)){
    istringstream stream(str);
    string field;
    while(getline(stream, field, ',')){
      data.push_back(field);
    }
  }
  for(vector<string>::size_type i = 22; i < data.size(); i+=22){
    if(data[i] == actionid){
      Rarm0 = atof(data [i+1].c_str());
      Rarm1 = atof(data [i+2].c_str());
      Rarm2 = atof(data [i+3].c_str());
      Rarm3 = atof(data [i+4].c_str());
      Rarm4 = atof(data [i+5].c_str());
      Rarm5 = atof(data [i+6].c_str());
      Rarm6 = atof(data [i+7].c_str());
      Larm0 = atof(data [i+8].c_str());
      Larm1 = atof(data [i+9].c_str());
      Larm2 = atof(data [i+10].c_str());
      Larm3 = atof(data [i+11].c_str());
      Larm4 = atof(data [i+12].c_str());
      Larm5 = atof(data [i+13].c_str());
      Larm6 = atof(data [i+14].c_str());
      handpara = atof(data [i+15].c_str());
      neckyoo = atof(data [i+16].c_str());
      neckpich = atof(data [i+17].c_str());
      neckrole = atof(data [i+18].c_str());
      waistyoo = atof(data [i+19].c_str());
      waistpich = atof(data [i+20].c_str());
      waistrole = atof(data [i+21].c_str());
      Flag = 1;

      std::cout << "Rarm0 : " << Rarm0 << std::endl;
      std::cout << "Rarm1 : " << Rarm1 << std::endl;
      std::cout << "Rarm2 : " << Rarm2 << std::endl;
      std::cout << "Rarm3 : " << Rarm3 << std::endl;
      std::cout << "Rarm4 : " << Rarm4 << std::endl;
      std::cout << "Rarm5 : " << Rarm5 << std::endl;
      std::cout << "Rarm6 : " << Rarm6 << std::endl;
      std::cout << "Larm0 : " << Larm0 << std::endl;
      std::cout << "Larm1 : " << Larm1 << std::endl;
      std::cout << "Larm2 : " << Larm2 << std::endl;
      std::cout << "Larm3 : " << Larm3 << std::endl;
      std::cout << "Larm4 : " << Larm4 << std::endl;
      std::cout << "Larm5 : " << Larm5 << std::endl;
      std::cout << "Larm6 : " << Larm6 << std::endl;
      std::cout << "handpara : " << handpara << std::endl;
      std::cout << "neckyoo : " << neckyoo << std::endl;
      std::cout << "neckpich : " << neckpich << std::endl;
      std::cout << "neckrole : " << neckrole << std::endl;
      std::cout << "waistyoo : " << waistyoo << std::endl;
      std::cout << "waistpich : " << waistpich << std::endl;
      std::cout << "waistrole : " << waistrole << std::endl;
    }
  }

#endif
}



// End of example implementational code



