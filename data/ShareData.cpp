//
// Created by madhav on 1/3/20.
//
#include "PQDataProvider.h"
#include "emp-tool/emp-tool.h"
#include "emp-sh2pc/emp-sh2pc.h"

unique_ptr<SecureTable> share_data(const UnsecureTable *input_table, int party) {

    unique_ptr<emp::Batcher> batcherAlice = make_unique<emp::Batcher>();
    unique_ptr<emp::Batcher> batcherBob = make_unique<emp::Batcher>();
    int alice_size = input_table->num_tuples();
    int bob_size = input_table->num_tuples();

    for (int i = 0; i < alice_size; i++) {
        for (int j = 0; j < input_table->get_schema()->get_num_fields(); j++) {
            if (party == emp::ALICE) {
                auto bits = input_table->get_tuple(i).get_field(j)->get_as_bits();
                assert(bits.size() == input_table->get_schema()->get_field(j)->get_field_size());
                for (int c = 0; c < input_table->get_schema()->get_field(j)->get_field_size(); c++) {
                    batcherAlice->add<emp::Bit>(bits[c]);
                    std::cout << bits[c];
                }
                batcherAlice->add<emp::Bit>(input_table->get_tuple(i).is_dummy);
            } else if (party == emp::BOB) {
                for (int c = 0; c < input_table->get_schema()->get_field(j)->get_field_size(); c++) {
                    //Ensure the length is the same as what Alice is inputting.
                    batcherAlice->add<emp::Bit>(0);
                }
                batcherAlice->add<emp::Bit>(0);
            }
        }
    }
    batcherAlice->make_semi_honest(emp::ALICE);

    for (int i = 0; i < bob_size; i++) {
        for (int j = 0; j < input_table->get_schema()->get_num_fields(); j++) {
            if (party == emp::ALICE) {
                for (int c = 0; c < input_table->get_schema()->get_field(j)->get_field_size(); c++) {
                    //Ensure the length is the same as what Bob is inputting.
                    batcherBob->add<emp::Bit>(0);
                }
                batcherBob->add<emp::Bit>(0);
            } else if (party == emp::BOB) {
                auto bits = input_table->get_tuple(i).get_field(j)->get_as_bits();
                assert(bits.size() == input_table->get_schema()->get_field(j)->get_field_size());
                for (int c = 0; c < input_table->get_schema()->get_field(j)->get_field_size(); c++) {
                    batcherBob->add<emp::Bit>(bits[c]);
                    std::cout << bits[c];
                }
                batcherBob->add<emp::Bit>(input_table->get_tuple(i).is_dummy);
                std::cout << std::endl;
            }
        }
    }
    batcherBob->make_semi_honest(emp::BOB);
    auto st = make_unique<SecureTable>();
    st->set_schema(input_table->schema.get());
    BaseData *bd = st->get_base_data();
    std::cout << "Alice (" << batcherAlice->size() << "), (" << batcherBob->size() << std::endl;
    for (int i = 0; i < batcherAlice->size(); i++) {
        auto b = batcherAlice->next<emp::Bit>();
        bd->copy_and_append(&b);
    }

    for (int i = 0; i < batcherBob->size(); i++) {
        auto b = batcherBob->next<emp::Bit>();
        bd->copy_and_append(&b);
    }
    st->set_num_tuples(alice_size + bob_size);
    return st;
}