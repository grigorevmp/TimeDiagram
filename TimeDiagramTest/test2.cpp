#include "pch.h"

#include "..//..///TimeDiagram/Project1/diagram_2.cpp"
TEST(TimeDiagramConstructors, EmptyConstractor) {

	//StandartEmpty

	Prog3_1::Diagram diagram_empty;
	std::ostringstream output;
	output << diagram_empty;

	ASSERT_EQ(0, diagram_empty.getCurrTime());
	ASSERT_EQ(0, diagram_empty.getEnd());
	EXPECT_EQ("Stack is empty\n", output.str());
}

TEST(TimeDiagramConstructors, InitConstractor) {

	//X init

	Prog3_1::Diagram diagram_init1(-1);
	std::ostringstream output_1;
	output_1 << diagram_init1;
	ASSERT_EQ(50, diagram_init1.getCurrTime());
	ASSERT_EQ(1, diagram_init1.getEnd());
	EXPECT_EQ("**************************************************\n", output_1.str());

	//"_" init

	Prog3_1::Diagram diagram_init2(0);
	std::ostringstream output2;
	output2 << diagram_init2;
	ASSERT_EQ(50, diagram_init2.getCurrTime());
	ASSERT_EQ(1, diagram_init2.getEnd());
	EXPECT_EQ("__________________________________________________\n", output2.str());

	//"-" init

	Prog3_1::Diagram diagram_init3(1);
	std::ostringstream output3;
	output3 << diagram_init3;
	ASSERT_EQ(50, diagram_init3.getCurrTime());
	ASSERT_EQ(1, diagram_init3.getEnd());
	EXPECT_EQ("--------------------------------------------------\n", output3.str());

	//ASCII init

	Prog3_1::Diagram diagram_init4("-----_______--__---_____****--____");
	std::ostringstream output4;
	output4 << diagram_init4;
	ASSERT_EQ(34, diagram_init4.getCurrTime());
	ASSERT_EQ(9, diagram_init4.getEnd());
	EXPECT_EQ("-----_______--__---_____****--____\n", output4.str());

	//ASCII error init

	Prog3_1::Diagram diagram_init6("-----_______--__---_____****--____&&&&&----___");
	std::ostringstream output6;
	output6 << diagram_init6;
	ASSERT_EQ(34, diagram_init6.getCurrTime());
	ASSERT_EQ(9, diagram_init6.getEnd());
	EXPECT_EQ("-----_______--__---_____****--____\n", output6.str());

	//ASCII overflow init

	Prog3_1::Diagram diagram_init5("-----_______--__---_____****--____-----_______--__---_____****--____");
	std::ostringstream output5;
	output5 << diagram_init5;
	ASSERT_EQ(50, diagram_init5.getCurrTime());
	ASSERT_EQ(13, diagram_init5.getEnd());
	EXPECT_EQ("-----_______--__---_____****--____-----_______--__\n", output5.str());

}

TEST(TimeDiagramMethods, input) {

	//With error input

	Prog3_1::Diagram diagram_input1;

	std::istringstream input1("----------__________---***::::::::\n");
	std::cin.rdbuf(input1.rdbuf());
	std::cin >> diagram_input1;

	std::ostringstream output1;

	ASSERT_EQ(26, diagram_input1.getCurrTime());
	ASSERT_EQ(4, diagram_input1.getEnd());
	output1 << diagram_input1;
	EXPECT_EQ("----------__________---***\n", output1.str());

	//Overflow input

	Prog3_1::Diagram diagram_input2;

	std::istringstream input2("-----_______--__---_____****--____-----_______--__---_____****--____\n");
	std::cin.rdbuf(input2.rdbuf());
	std::cin >> diagram_input2;

	std::ostringstream output2;

	ASSERT_EQ(50, diagram_input2.getCurrTime());
	ASSERT_EQ(13, diagram_input2.getEnd());
	output2 << diagram_input2;
	EXPECT_EQ("-----_______--__---_____****--____-----_______--__\n", output2.str());

}

TEST(TimeDiagramMethods, unit) {

	//Unit with same elements

	Prog3_1::Diagram diagram_unit1("-----_______-_");
	Prog3_1::Diagram diagram_unit2("____---");

	ASSERT_EQ(14, diagram_unit1.getCurrTime());
	ASSERT_EQ(4, diagram_unit1.getEnd());

	ASSERT_EQ(7, diagram_unit2.getCurrTime());
	ASSERT_EQ(2, diagram_unit2.getEnd());

	diagram_unit1 += diagram_unit2;

	std::ostringstream output;
	output << diagram_unit1;
	ASSERT_EQ(21, diagram_unit1.getCurrTime());
	ASSERT_EQ(5, diagram_unit1.getEnd());
	EXPECT_EQ("-----_______-_____---\n", output.str());

	//Standart init

	Prog3_1::Diagram diagram_unit3("-_-_-_");
	Prog3_1::Diagram diagram_unit4("-_-_-_");

	diagram_unit3 += diagram_unit4;

	std::ostringstream output2;
	output2 << diagram_unit3;
	ASSERT_EQ(12, diagram_unit3.getCurrTime());
	ASSERT_EQ(12, diagram_unit3.getEnd());
	EXPECT_EQ("-_-_-_-_-_-_\n", output2.str());

	//Unit with overflow

	Prog3_1::Diagram diagram_unit5("--------");
	Prog3_1::Diagram diagram_unit6("___________________________________________________________");

	diagram_unit5 += diagram_unit6;

	std::ostringstream output3;
	output3 << diagram_unit5;
	ASSERT_EQ(50, diagram_unit5.getCurrTime());
	ASSERT_EQ(2, diagram_unit5.getEnd());
	EXPECT_EQ("--------__________________________________________\n", output3.str());

}

TEST(TimeDiagramMethods, change) {
	Prog3_1::Diagram diagram_change("---___---");
	diagram_change({ -1, 4 });

	std::ostringstream output;
	output << diagram_change;
	EXPECT_EQ("---_*_---\n", output.str());
}

TEST(TimeDiagramMethods, copy) {

	//Standart copy
	Prog3_1::Diagram diagram_copy("--__--");
	diagram_copy *= 5;

	std::ostringstream output;
	output << diagram_copy;
	ASSERT_EQ(13, diagram_copy.getEnd());
	ASSERT_EQ(36, diagram_copy.getCurrTime());
	EXPECT_EQ("--__----__----__----__----__----__--\n", output.str());

	//Copy with overflow
	Prog3_1::Diagram diagram_copy2("-----_____");
	diagram_copy2 *= 5;

	std::ostringstream output2;
	output2 << diagram_copy2;
	ASSERT_EQ(10, diagram_copy2.getEnd());
	ASSERT_EQ(50, diagram_copy2.getCurrTime());
	EXPECT_EQ("-----_____-----_____-----_____-----_____-----_____\n", output2.str());
}

TEST(TimeDiagramMethods, shift) {

	//Shift Left
	Prog3_1::Diagram diagram_copy("-----__-----");
	ASSERT_EQ(3, diagram_copy.getEnd());
	ASSERT_EQ(12, diagram_copy.getCurrTime());

	diagram_copy < 5;

	ASSERT_EQ(2, diagram_copy.getEnd());
	ASSERT_EQ(12, diagram_copy.getCurrTime());

	std::ostringstream output;
	output << diagram_copy;

	EXPECT_EQ("__----------\n", output.str());

	//Shift Right
	Prog3_1::Diagram diagram_copy2("-----_____");

	ASSERT_EQ(2, diagram_copy2.getEnd());
	ASSERT_EQ(10, diagram_copy2.getCurrTime());

	diagram_copy2 > 4;

	std::ostringstream output2;
	output2 << diagram_copy2;
	ASSERT_EQ(3, diagram_copy2.getEnd());
	ASSERT_EQ(10, diagram_copy2.getCurrTime());
	EXPECT_EQ("____-----_\n", output2.str());
}

TEST(TimeDiagramMethods, exeptions) {

	Prog3_1::Diagram diagram_exp(1);

	ASSERT_ANY_THROW(diagram_exp *= (-3));

	ASSERT_ANY_THROW(diagram_exp < -4);

	ASSERT_ANY_THROW(diagram_exp < -5);

	ASSERT_ANY_THROW(diagram_exp({ -2, 4 }));
	ASSERT_ANY_THROW(diagram_exp({ 5, 6 }));
	ASSERT_ANY_THROW(diagram_exp({ 1, 664 }));
}
