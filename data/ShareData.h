//
// Created by madhav on 1/3/20.
//

#ifndef TESTING_SHAREDATA_H
#define TESTING_SHAREDATA_H

#include "PQDataProvider.h"

unique_ptr<SecureTable> ShareData(const UnsecureTable *input_table, int party);

#endif // TESTING_SHAREDATA_H
