OPTS=-g -O0
TEST_LD= -lgtest_main
GTEST_DIR=/opt/google/gtest-1.5.0
GTEST_INC=-I$(GTEST_DIR) -I$(GTEST_DIR)include $(GTEST_DIR)/src/gtest-all.cc
LD=$(TEST_LD)
TEST_INCLUDE=$(GTEST_INC)
NOTIFY=&& notify-send Test success! -i ~/themes/ok_icon.png || notify-send Test failed... -i ~/themes/ng_icon.png
target:test
target:test_do
target:specific_test
#target:specific_test_do

test_do:test
	./test $(NOTIFY)
specific_test_do:specific_test
	./specific_test $(NOTIFY)
test:test.o gtest.o
	g++ -I$(GTEST_DIR)/include test.o gtest.o -o $@ $(OPTS) -pthread $(LD)
specific_test:specific_test.o gtest.o
	g++ -I$(GTEST_DIR)/include specific_test.o gtest.o -o $@ $(OPTS) -pthread $(LD)
specific_test.o:specific_test.cc
	g++ -c specific_test.cc -o $@ $(OPTS)

test.o:test.cc yak_msgpack.hpp
	g++ -c test.cc -o test.o -O0 -g
gtest.o:
	g++ -c -I$(GTEST_DIR)/include -I$(GTEST_DIR) $(GTEST_DIR)/src/gtest-all.cc -o $@