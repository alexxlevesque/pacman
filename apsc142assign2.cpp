#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

// SUBMIT THIS FILE

// this includes the function signatures (prototypes) from ceab.h
extern "C" {
#include "ceab.h"
};


////////////////////////////////////////
// don't edit anything above this line!
////////////////////////////////////////

/* tests for aus_remaining */
TEST_SUITE_BEGIN("aus_remaining tests");
// aus_remaining checks for each area code, organized

TEST_CASE("Testing aus_remaining for MA"){ // Necessary checks for MA
    CHECK(aus_remaining(MA, 0) == 195); // if no AUs taken, return required amount
    CHECK(aus_remaining(MA, REQUIRED_MA_NS) == 0); // if all necessary AUs taken, return 0
    CHECK(aus_remaining(MA, 10) == REQUIRED_MA_NS - 10); // if set amount of AUs taken, return required minus set amount
    CHECK(aus_remaining(MA, 196) == 0); // if more than enough Aus taken, return 0
    CHECK(aus_remaining(MA, 194) == 1); // testing incorrect threshold behaviour
}

TEST_CASE("Testing aus_remaining for NS"){ // Necessary checks for NS
    CHECK(aus_remaining(NS, 0) == 195); // if no AUs taken, return required amount
    CHECK(aus_remaining(NS, REQUIRED_MA_NS) == 0); // if all necessary AUs taken, return 0
    CHECK(aus_remaining(NS, 15) == REQUIRED_MA_NS - 15); // if set amount of AUs taken, return required minus set amount
    CHECK(aus_remaining(NS, 196) == 0); // if more than enough Aus taken, return 0
    CHECK(aus_remaining(NS, 194) == 1); // testing incorrect threshold behaviour
}

TEST_CASE("Testing aus_remaining for ES"){ // Necessary checks for ES
    CHECK(aus_remaining(ES, 0) == 225); // if no AUs taken, return required amount
    CHECK(aus_remaining(ES, REQUIRED_ES_ED_CS) == 0); // if all necessary AUs taken, return 0
    CHECK(aus_remaining(ES, 23) == REQUIRED_ES_ED_CS - 23); // if set amount of AUs taken, return required minus set amount
    CHECK(aus_remaining(ES, 226) == 0); // if more than enough Aus taken, return 0
    CHECK(aus_remaining(ES, 224) == 1); // testing incorrect threshold behaviour
}

TEST_CASE("Testing aus_remaining for ED"){ // Necessary checks for ED
    CHECK(aus_remaining(ED, 0) == 225); // if no AUs taken, return required amount
    CHECK(aus_remaining(ED, REQUIRED_ES_ED_CS) == 0); // if all necessary AUs taken, return 0
    CHECK(aus_remaining(ED, 64) == REQUIRED_ES_ED_CS - 64); // if set amount of AUs taken, return required minus set amount
    CHECK(aus_remaining(ED, 226) == 0); // if more than enough Aus taken, return 0
    CHECK(aus_remaining(ED, 224) == 1); // testing incorrect threshold behaviour
}

TEST_CASE("Testing aus_remaining for CS"){ // Necessary checks for CS
    CHECK(aus_remaining(CS, 0) == 225); // if no AUs taken, return required amount
    CHECK(aus_remaining(CS, REQUIRED_ES_ED_CS) == 0); // if all necessary AUs taken, return 0
    CHECK(aus_remaining(CS, 32) == REQUIRED_ES_ED_CS - 32); // if set amount of AUs taken, return required minus set amount
    CHECK(aus_remaining(CS, 226) == 0); // if more than enough Aus taken, return 0
    CHECK(aus_remaining(CS, 224) == 1); // testing incorrect threshold behaviour
}
TEST_SUITE_END();

/* tests for can_graduate */
TEST_SUITE_BEGIN("can_graduate tests");

TEST_CASE("Testing can_graduate general cases"){ // testing general cases
    // if individual requirements are met but not the combined requirements, return CANNOT_GRADUATE
    CHECK(can_graduate(195, 195, 225, 225, 225) == CANNOT_GRADUATE);
    // if individual and combined requirements are met, but not total requirement, return CANNOT_GRADUATE
    CHECK(can_graduate(210, 210, 450, 450, 225) == CANNOT_GRADUATE);
    // if individual, combined, and total requirements are met, return CAN_GRADUATE
    CHECK(can_graduate(210, 210, 450, 450, 530) == CAN_GRADUATE);
    // if one area lacks, return CANNOT_GRADUATE
    CHECK(can_graduate(210, 210, 450, 450, 529) == CANNOT_GRADUATE);
    // if no AUs at all are taken, return CANNOT_GRADUATE
    CHECK(can_graduate(0, 0, 0, 0, 0) == CANNOT_GRADUATE);
}

TEST_CASE("Testing can_graduate for MA"){ // testing can_graduate cases in terms of MA
    // if no AUs taken for specified area code, even if combined requirements are met, return CANNOT_GRADUATE
    CHECK(can_graduate(0, 420, 450, 450, 530) == CANNOT_GRADUATE);
    // if all requirements met, including exact requirement for specified are code, return CAN_GRADUATE
    CHECK(can_graduate(195, 225, 450, 450, 530) == CAN_GRADUATE);
    // if specified area code lacks, and all other requirements are met, return CANNOT_GRADUATE
    CHECK(can_graduate(194, 226, 450, 450, 530) == CANNOT_GRADUATE);
    // if specified are code value overshoots, and all other requirements are met, return CAN_GRADUATE
    CHECK(can_graduate(196, 224, 450, 450, 530) == CAN_GRADUATE);
}

TEST_CASE("Testing can_graduate for NS"){ // testing can_graduate cases in terms of NS
    // if no AUs taken for specified area code, even if combined requirements are met, return CANNOT_GRADUATE
    CHECK(can_graduate(420, 0, 450, 450, 530) == CANNOT_GRADUATE);
    // if all requirements met, including exact requirement for specified are code, return CAN_GRADUATE
    CHECK(can_graduate(225, 195, 450, 450, 530) == CAN_GRADUATE);
    // if specified area code lacks, and all other requirements are met, return CANNOT_GRADUATE
    CHECK(can_graduate(226, 194, 450, 450, 530) == CANNOT_GRADUATE);
    // if specified are code value overshoots, and all other requirements are met, return CAN_GRADUATE
    CHECK(can_graduate(224, 196, 450, 450, 530) == CAN_GRADUATE);
}

TEST_CASE("Testing can_graduate for ES"){ // testing can_graduate cases in terms of ES
    // if no AUs taken for specified area code, even if combined requirements are met, return CANNOT_GRADUATE
    CHECK(can_graduate(210, 210, 0, 900, 530) == CANNOT_GRADUATE);
    // if all requirements met, including exact requirement for specified are code, return CAN_GRADUATE
    CHECK(can_graduate(210, 210, 225, 675, 530) == CAN_GRADUATE);
    // if specified area code lacks, and all other requirements are met, return CANNOT_GRADUATE
    CHECK(can_graduate(210, 210, 224, 676, 530) == CANNOT_GRADUATE);
    // if specified are code value overshoots, and all other requirements are met, return CAN_GRADUATE
    CHECK(can_graduate(210, 210, 226, 674, 530) == CAN_GRADUATE);
}

TEST_CASE("Testing can_graduate for ED"){ // testing can_graduate cases in terms of ED
    // if no AUs taken for specified area code, even if combined requirements are met, return CANNOT_GRADUATE
    CHECK(can_graduate(210, 210, 900, 0, 530) == CANNOT_GRADUATE);
    // if all requirements met, including exact requirement for specified are code, return CAN_GRADUATE
    CHECK(can_graduate(210, 210, 675, 225, 530) == CAN_GRADUATE);
    // if specified area code lacks, and all other requirements are met, return CANNOT_GRADUATE
    CHECK(can_graduate(210, 210, 676, 224, 530) == CANNOT_GRADUATE);
    // if specified are code value overshoots, and all other requirements are met, return CAN_GRADUATE
    CHECK(can_graduate(210, 210, 674, 226, 530) == CAN_GRADUATE);
}

TEST_CASE("Testing can_graduate for CS"){ // testing can_graduate cases in terms of CS
    // if no AUs taken for specified area code, even if combined requirements are met, return CANNOT_GRADUATE
    CHECK(can_graduate(475, 475, 450, 450, 0) == CANNOT_GRADUATE);
    // if all requirements met, including exact requirement for specified are code, return CAN_GRADUATE
    CHECK(can_graduate(475, 475, 450, 450, 225) == CAN_GRADUATE);
    // if specified area code lacks, and all other requirements are met, return CANNOT_GRADUATE
    CHECK(can_graduate(475, 475, 450, 451, 224) == CANNOT_GRADUATE);
    // if specified are code value overshoots, and all other requirements are met except COMBINED_ES_ED, return CANNOT_GRADUATE
    CHECK(can_graduate(475, 475, 450, 449, 226) == CANNOT_GRADUATE);
}

TEST_CASE("Testing can_graduate for MA_NS"){ // testing can_graduate cases in terms of COMBINED_MA_NS
    // if total requirement is met, but not COMBINED_MA_NS, return CANNOT_GRADUATE
    CHECK(can_graduate(209, 210, 477, 477, 477) == CANNOT_GRADUATE);
    // if all requirements are met except amount of MA, return CANNOT_GRADUATE
    CHECK(can_graduate(194, 226, 477, 477, 477) == CANNOT_GRADUATE);
    // if all requirements are met except amount of NS, return CANNOT_GRADUATE
    CHECK(can_graduate(226, 194, 477, 477, 477) == CANNOT_GRADUATE);
    // if all requirements are met except total, return CANNOT_GRADUATE
    CHECK(can_graduate(210, 210, 450, 450, 529) == CANNOT_GRADUATE);
}

TEST_CASE("Testing can_graduate for ES_ED"){ // testing can_graduate cases in terms of COMBINED_ES_ED
    // if total requirement is met, but not COMBINED_ES_ED, return CANNOT_GRADUATE
    CHECK(can_graduate(317, 317, 449, 450, 318) == CANNOT_GRADUATE);
    // if all requirements are met except amount of ES, return CANNOT_GRADUATE
    CHECK(can_graduate(407, 407, 224, 407, 407) == CANNOT_GRADUATE);
    // if all requirements are met except amount of ED, return CANNOT_GRADUATE
    CHECK(can_graduate(407, 407, 407, 224, 407) == CANNOT_GRADUATE);
}
TEST_SUITE_END();

