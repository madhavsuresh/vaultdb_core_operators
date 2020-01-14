//
// Created by madhav on 1/13/20.
//

#ifndef TESTING_DUMMYFLAG_H
#define TESTING_DUMMYFLAG_H

#include "emp-tool/emp-tool.h"


class DummyFlag {
private:
    bool unencrypted_flag;
    emp::Bit encrypted_flag;
    bool is_encrypted;
public:
};


#endif //TESTING_DUMMYFLAG_H
